""" This module is responsible for computing the dependencies (graph) for a given entry
point, which could be both a user conanfile or an installed one
"""
from conans.model.requires import Requirements
from collections import namedtuple
from conans.model.ref import PackageReference
from conans.model.info import ConanInfo
from conans.errors import ConanException, format_conanfile_exception
from conans.client.output import ScopedOutput
import time
from conans.util.log import logger
from collections import defaultdict


class Node(namedtuple("Node", "conan_ref conanfile")):
    """ The Node of the dependencies graph is defined by:
    ref: ConanFileReference, if it is a user space one, user=channel=none
    conanfile: the loaded conanfile object withs its values
    """
    def __repr__(self):
        return "%s => %s" % (repr(self.conan_ref), repr(self.conanfile)[:100].replace("\n", " "))

    def __cmp__(self, other):
        if other is None:
            return -1
        elif self.conan_ref is None:
            return 0 if other.conan_ref is None else -1
        elif other.conan_ref is None:
            return 1

        if self.conan_ref == other.conan_ref:
            return 0
        if self.conan_ref < other.conan_ref:
            return -1

        return 1

    def __gt__(self, other):
        return self.__cmp__(other) == 1

    def __lt__(self, other):
        return self.__cmp__(other) == -1

    def __le__(self, other):
        return self.__cmp__(other) in [0, -1]

    def __ge__(self, other):
        return self.__cmp__(other) in [0, 1]


class DepsGraph(object):
    """ DAG of dependencies
    """
    def __init__(self):
        self.nodes = set()
        self._neighbors = defaultdict(set)
        self._inverse_neighbors = defaultdict(set)

    def add_node(self, node):
        self.nodes.add(node)

    def add_edge(self, src, dst):
        assert src in self.nodes and dst in self.nodes
        self._neighbors[src].add(dst)
        self._inverse_neighbors[dst].add(src)

    def neighbors(self, node):
        """ return all connected nodes (directionally) to the parameter one
        """
        return self._neighbors[node]

    def inverse_neighbors(self, node):
        """ return all the nodes which has param node has dependency
        """
        return self._inverse_neighbors[node]

    def public_neighbors(self, node):
        """ return nodes with direct reacheability by public dependencies
        """
        neighbors = self.neighbors(node)
        _, conanfile = node

        public_requires = [r.conan_reference for r in conanfile.requires.values() if not r.private]
        result = [n for n in neighbors if n.conan_ref in public_requires]
        return result

    def private_inverse_neighbors(self, node):
        """ return nodes connected to a given one (inversely), by a private requirement
        """
        neighbors = self.inverse_neighbors(node)
        result = []
        for n in neighbors:
            _, conanfile = n
            for req in conanfile.requires.values():
                if req.conan_reference == node.conan_ref:
                    if req.private:
                        result.append(n)
        return result

    def __repr__(self):
        return "\n".join(["Nodes:\n    ",
                          "\n    ".join(repr(n) for n in self.nodes)])

    def propagate_info(self):
        """ takes the exports from upper level and updates the imports
        right now also the imports are propagated, but should be checked
        E.g. Conan A, depends on B.  A=>B
        B exports an include directory "my_dir", with root "/...../0123efe"
        A imports are the exports of B, plus any other conans it depends on
        A.imports.include_dirs = B.export.include_paths.
        Note the difference, include_paths used to compute full paths as the user
        defines export relative to its folder
        """
        ordered = self.by_levels()
        for level in ordered:
            for node in level:
                _, conanfile = node
                neighbors = self.neighbors(node)
                direct_reqs = []  # of PackageReference
                indirect_reqs = set()   # of PackageReference, avoid duplicates
                for nref, nconan in neighbors:
                    package_id = nconan.info.package_id()
                    package_reference = PackageReference(nref, package_id)
                    direct_reqs.append(package_reference)
                    indirect_reqs.update(nconan.info.requires.refs())
                    conanfile.options.propagate_downstream(nref, nconan.info.full_options)
                    # Might be never used, but update original requirement, just in case
                    conanfile.requires[nref.name].conan_reference = nref

                # Make sure not duplicated
                indirect_reqs.difference_update(direct_reqs)
                # There might be options that are not upstream
                conanfile.options.clear_unused(indirect_reqs.union(direct_reqs))

                non_devs = self.non_dev_nodes(node)
                conanfile.info = ConanInfo.create(conanfile.settings.values,
                                                  conanfile.options.values,
                                                  direct_reqs,
                                                  indirect_reqs,
                                                  non_devs)

                # Once we are done, call conan_info() to narrow and change possible values
                conanfile.conan_info()
        return ordered

    def ordered_closure(self, node, flat):
        closure = set()
        current = self.neighbors(node)
        while current:
            new_current = set()
            for n in current:
                closure.add(n)
                new_neighs = self.public_neighbors(n)
                to_add = set(new_neighs).difference(current)
                new_current.update(to_add)
            current = new_current

        result = [n for n in flat if n in closure]
        return result

    def _inverse_closure(self, references):
        closure = set()
        current = [n for n in self.nodes if str(n.conan_ref) in references or "ALL" in references]
        closure.update(current)
        while current:
            new_current = set()
            for n in current:
                closure.add(n)
                new_neighs = self.inverse_neighbors(n)
                to_add = set(new_neighs).difference(current)
                new_current.update(to_add)
            current = new_current
        return closure

    def build_order(self, references):
        levels = self.inverse_levels()
        closure = self._inverse_closure(references)
        result = []
        for level in reversed(levels):
            new_level = [n.conan_ref for n in level if (n in closure and n.conan_ref)]
            if new_level:
                result.append(new_level)
        return result

    def by_levels(self):
        """ order by node degree. The first level will be the one which nodes dont have
        dependencies. Second level will be with nodes that only have dependencies to
        first level nodes, and so on
        return [[node1, node34], [node3], [node23, node8],...]
        """
        current_level = []
        result = [current_level]
        opened = self.nodes.copy()
        while opened:
            current = opened.copy()
            for o in opened:
                o_neighs = self._neighbors[o]
                if not any(n in opened for n in o_neighs):
                    current_level.append(o)
                    current.discard(o)
            current_level.sort()
            # now initialize new level
            opened = current
            if opened:
                current_level = []
                result.append(current_level)
        return result

    def inverse_levels(self):
        """ order by node degree. The first level will be the one which nodes dont have
        dependencies. Second level will be with nodes that only have dependencies to
        first level nodes, and so on
        return [[node1, node34], [node3], [node23, node8],...]
        """
        current_level = []
        result = [current_level]
        opened = self.nodes.copy()
        while opened:
            current = opened.copy()
            for o in opened:
                o_neighs = self._inverse_neighbors[o]
                if not any(n in opened for n in o_neighs):
                    current_level.append(o)
                    current.discard(o)
            current_level.sort()
            # now initialize new level
            opened = current
            if opened:
                current_level = []
                result.append(current_level)

        return result

    def private_nodes(self, built_private_nodes):
        """ computes a list of nodes living in the private zone of the deps graph,
        together with the list of nodes that privately require it
        """
        closure = set()
        nodes_by_level = self.by_levels()
        open_nodes = nodes_by_level[-1]
        closure.update(open_nodes)
        while open_nodes:
            new_open_nodes = set()
            for node in open_nodes:
                if node in built_private_nodes:
                    neighbors = self.public_neighbors(node)
                else:
                    neighbors = self.neighbors(node)
                new_open_nodes.update(set(neighbors).difference(closure))
                closure.update(neighbors)
            open_nodes = new_open_nodes

        private_nodes = self.nodes.difference(closure)
        result = []
        for node in private_nodes:
            result.append(node)
        return result

    def non_dev_nodes(self, root):
        if not root.conanfile.scope.dev:
            # Optimization. This allow not to check it for most packages, which dev=False
            return None
        open_nodes = set([root])
        result = set()
        expanded = set()
        while open_nodes:
            new_open_nodes = set()
            for node in open_nodes:
                neighbors = self.neighbors(node)
                requires = node.conanfile.requires
                for n in neighbors:
                    requirement = requires[n.conan_ref.name]
                    if not requirement.dev and n not in expanded:
                        result.add(n.conan_ref.name)
                        new_open_nodes.add(n)
                        expanded.add(n)

            open_nodes = new_open_nodes
        return result


class DepsBuilder(object):
    """ Responsible for computing the dependencies graph DepsGraph
    """
    def __init__(self, retriever, output, loader):
        """ param retriever: something that implements retrieve_conanfile for installed conans
        param loader: helper ConanLoader to be able to load user space conanfile
        """
        self._retriever = retriever
        self._output = output
        self._loader = loader

    def get_graph_updates_info(self, deps_graph):
        """
        returns a dict of conan_reference: 1 if there is an update,
        0 if don't and -1 if local is newer
        """
        return {conan_reference: self._retriever.update_available(conan_reference)
                for conan_reference, _ in deps_graph.nodes}

    def load(self, conan_ref, conanfile):
        """ compute the dependencies graph for:
        param conan_ref: ConanFileReference for installed conanfile or path to user one
                         might be None for user conanfile.py or .txt
        """
        dep_graph = DepsGraph()
        # compute the conanfile entry point for this dependency graph
        root_node = Node(conan_ref, conanfile)
        dep_graph.add_node(root_node)
        public_deps = {}  # {name: Node} dict with public nodes, so they are not added again
        # enter recursive computation
        t1 = time.time()
        loop_ancestors = []
        self._load_deps(root_node, Requirements(), dep_graph, public_deps, conan_ref, None,
                        loop_ancestors)
        logger.debug("Deps-builder: Time to load deps %s" % (time.time() - t1))
        t1 = time.time()
        dep_graph.propagate_info()
        logger.debug("Deps-builder: Propagate info %s" % (time.time() - t1))
        return dep_graph

    def _load_deps(self, node, down_reqs, dep_graph, public_deps, down_ref, down_options,
                   loop_ancestors):
        """ loads a Conan object from the given file
        param node: Node object to be expanded in this step
        down_reqs: the Requirements as coming from downstream, which can overwrite current
                    values
        param settings: dict of settings values => {"os": "windows"}
        param deps: DepsGraph result
        param public_deps: {name: Node} of already expanded public Nodes, not to be repeated
                           in graph
        param down_ref: ConanFileReference of who is depending on current node for this expansion
        """
        # basic node configuration
        conanref, conanfile = node
        new_reqs, new_options = self._config_node(conanfile, conanref, down_reqs, down_ref,
                                                  down_options)

        # Expand each one of the current requirements
        for name, require in conanfile.requires.items():
            if require.override or require.conan_reference is None:
                continue
            if require.conan_reference in loop_ancestors:
                raise ConanException("Loop detected: %s"
                                     % "->".join(str(r) for r in loop_ancestors))
            new_loop_ancestors = loop_ancestors[:]  # Copy for propagating
            new_loop_ancestors.append(require.conan_reference)
            previous_node = public_deps.get(name)
            if require.private or not previous_node:  # new node, must be added and expanded
                new_node = self._create_new_node(node, dep_graph, require, public_deps, name)
                if new_node:
                    # RECURSION!
                    self._load_deps(new_node, new_reqs, dep_graph, public_deps, conanref,
                                    new_options.copy(), new_loop_ancestors)
            else:  # a public node already exist with this name
                if previous_node.conan_ref != require.conan_reference:
                    self._output.werror("Conflict in %s\n"
                                        "    Requirement %s conflicts with already defined %s\n"
                                        "    Keeping %s\n"
                                        "    To change it, override it in your base requirements"
                                        % (conanref, require.conan_reference,
                                           previous_node.conan_ref, previous_node.conan_ref))
                dep_graph.add_edge(node, previous_node)
                # RECURSION!
                self._load_deps(previous_node, new_reqs, dep_graph, public_deps, conanref,
                                new_options.copy(), new_loop_ancestors)

    def _config_node(self, conanfile, conanref, down_reqs, down_ref, down_options):
        """ update settings and option in the current ConanFile, computing actual
        requirement values, cause they can be overriden by downstream requires
        param settings: dict of settings values => {"os": "windows"}
        """
        try:
            conanfile.requires.output = self._output
            if hasattr(conanfile, "config"):
                if not conanref:
                    self._output.warn("config() has been deprecated."
                                      " Use config_options and configure")
                conanfile.config()
            conanfile.config_options()
            conanfile.options.propagate_upstream(down_options, down_ref, conanref, self._output)
            if hasattr(conanfile, "config"):
                conanfile.config()
            conanfile.configure()

            conanfile.settings.validate()  # All has to be ok!
            conanfile.options.validate()

            # Update requirements (overwrites), computing new upstream
            conanfile.requirements()
            new_options = conanfile.options.values
            new_down_reqs = conanfile.requires.update(down_reqs, self._output, conanref, down_ref)
        except ConanException as e:
            raise ConanException("%s: %s" % (conanref or "Conanfile", str(e)))
        except Exception as e:
            msg = format_conanfile_exception(str(conanref or "Conanfile"),
                                             "config, config_options or configure", e)
            raise ConanException(msg)
        return new_down_reqs, new_options

    def _create_new_node(self, current_node, dep_graph, requirement, public_deps, name_req):
        """ creates and adds a new node to the dependency graph
        """
        conanfile_path = self._retriever.get_recipe(requirement.conan_reference)
        output = ScopedOutput(str(requirement.conan_reference), self._output)
        dep_conanfile = self._loader.load_conan(conanfile_path, output)
        if dep_conanfile:
            new_node = Node(requirement.conan_reference, dep_conanfile)
            dep_graph.add_node(new_node)
            dep_graph.add_edge(current_node, new_node)
            if not requirement.private:
                public_deps[name_req] = new_node
            # RECURSION!
            return new_node
        else:
            self._output.error("Could not retrieve %s" % requirement.conan_reference)
