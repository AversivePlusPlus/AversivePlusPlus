from generator import Generator

def indent(multiline_string):
    lines = multiline_string.split('\n')
    ret = []
    for l in lines:
        ret.append("  " + l)
    return "\n".join(ret)

class CppMatrixType:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
    def __str__(self):
        return "double[{r}*{c}]".format(
            r=self.rows,
            c=self.cols
        )

class CppGenerator(Generator):
    def matrix_type(self, rows, cols):
        return CppMatrixType(rows, cols)
    real_type = "double"
    integer_type = "int"
    void_type = "void"
    def param(self, name, type, default_value = None):
        if default_value == None:
            return "{type} {name}".format(
                name=name,
                type=str(type),
            )
        return "{type} {name} = {val}".format(
            name=name,
            type=str(type),
            val=str(default_value)
        )
    def ref_type(self, type):
        return "{type}&".format(type=str(type))
    def const_type(self, type):
        return "const {type}".format(type=str(type))
    def list_type(self, type):
        return "{type}*".format(type=str(type))
    def call(self, name, params):
        return "{name}({params})".format(
            name=name,
            params=", ".join(map(lambda p: str(p), params))
        )
    def assign(self, var, val):
        return "{var} = {val}".format(
            var=var,
            val=val
        )
    def matrix_get(self, name, type, i,j):
        return "{matrix}[{index}]".format(
            matrix = name,
            index = str(i*type.cols+j),
        )
    def nested(self, *names):
        return "::".join(names)
    def list_get(self, name, i):
        raise NotImplementedError()
    
class CppBlockGenerator(CppGenerator):
    def __init__(self, header):
        self.source = []
        self.header = header
    def __enter__(self):
        return self
    def __exit__(self, type, value, traceback):
        pass
    def add_instruction(self, instr):
        self.source += [instr + ";"]
        return self
    def add_variable(self, name, type, default_value = None):
        self.source += [ self.param(name, type, default_value) + ";" ]
        return self
    def add_constant(self, name, type, value):
        return self.add_variable(name, self.const_type(type), value)
    def define_if_block(self, cond):
        header = "if({})".format(cond)
        ret = CppBlockGenerator(header)
        self.source += [ret]
        return ret
    def define_for_block(self, size):
        template = "for({init} ; {end} ; {inc})"
        header = template.format(
            init = "int i = 0",
            end = "i < " + str(size),
            inc = "i++"
        )
        ret = CppBlockGenerator(header)
        self.source += [ret]
        return ret
    def __str__(self):
        ret  = [self.header + " {"]
        ret += [indent("\n".join(map(lambda i: str(i), self.source)))]
        ret += ["}"]
        return "\n".join(ret)
    
class CppModuleGenerator(CppGenerator):
    def __init__(self, name):
        self.name = name
        self.header = []
        self.source = []
    def __enter__(self):
        return self
    def __exit__(self, type, value, traceback):
        pass
    def add_constant(self, name, type, value):
        template = "#define {name} (({type}){value})"
        self.header += [
            template.format(name=name, type=str(type), value=str(value))
        ]
        return self
    def add_instruction(self, instr):
        self.header += [instr + ";"]
        return self
    def define_function(self, name, ret_type, params):
        template = "{ret} {name}({params})"
        header_signature = template.format(
            ret=str(ret_type),
            name=name,
            params=", ".join(params)
        )
        signature = template.format(
            ret=str(ret_type),
            name=self.nested(self.name, name),
            params=", ".join(params)
        )
        ret = CppBlockGenerator(signature)
        self.header += [header_signature + ";"]
        self.source += ["", ret]
        return ret
    def define_main_function(self):
        return self.define_function(
            "main",
            self.integer_type,
            [
                self.param("", self.integer_type),
                self.param("", "char**")
            ]
        )
    def __str__(self):
        ret  = ["// MODULE : " + self.name]
        if self.header != []:
            ret += ["//// HEADER"]
            ret += ["#ifndef IK_{}_HPP".format(self.name.upper())]
            ret += ["#define IK_{}_HPP".format(self.name.upper()), ""]
            ret += ["namespace {} {{".format(self.name), ""]
            for i in self.header:
                ret += [str(i)]
            ret += ["", "}", ""]
            ret += ["#endif//IK_{}_HPP".format(self.name.upper())]
            ret += [""]
        if self.source != []:
            ret += ["//// SOURCE"]
            ret += ["//#include <{}.hpp>".format(self.name)]
            ret += ["#include <math.h>"]
            for i in self.source:
                ret += [str(i)]
            ret += [""]
        return "\n".join(ret)
    def __iter__(self):
        if self.header != []:
            yield self.name + ".hpp"
        if self.source != []:
            yield self.name + ".cpp"
    def __getitem__(self, fname):
        ret = []
        if fname == self.name + ".hpp":
            ret += ["#ifndef IK_{}_HPP".format(self.name.upper())]
            ret += ["#define IK_{}_HPP".format(self.name.upper()), ""]
            ret += ["namespace {} {{".format(self.name), ""]
            for i in self.header:
                ret += [str(i)]
            ret += ["", "}", ""]
            ret += ["#endif//IK_{}_HPP".format(self.name.upper())]
            ret += [""]
        elif fname == self.name + ".cpp":
            ret += ["#include <{}.hpp>".format(self.name)]
            ret += ["#include <math.h>"]
            for i in self.source:
                ret += [str(i)]
            ret += [""]
        else:
            raise Exception()
        return "\n".join(ret)

class CppProjectGenerator(CppModuleGenerator):
    def __init__(self):
        CppModuleGenerator.__init__(self, "main")
        self.modules = []
    def define_module(self, name):
        ret = CppModuleGenerator(name)
        self.modules += [ret]
        return ret
    def __str__(self):
        ret = ""
        ret += CppModuleGenerator.__str__(self)
        ret += '\n'
        for m in self.modules:
            ret += "////////////////////////////////\n"
            ret += str(m)
            ret += '\n'
        return ret
    def __iter__(self):
        for e in CppModuleGenerator.__iter__(self):
            yield e
        for m in self.modules:
            for e in m:
                yield e
    def __getitem__(self, fname):
        for e in CppModuleGenerator.__iter__(self):
            if e == fname:
                return CppModuleGenerator.__getitem__(self, fname)
        for m in self.modules:
            for e in m:
                if e == fname:
                    return m[e]
