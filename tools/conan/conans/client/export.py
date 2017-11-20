""" manages the movement of conanfiles and associated files from the user space
to the local store, as an initial step before building or uploading to remotes
"""

import shutil
import os
from conans.util.files import save, load, rmdir
from conans.paths import CONAN_MANIFEST, CONANFILE, DIRTY_FILE
from conans.errors import ConanException
from conans.model.manifest import FileTreeManifest
from conans.client.output import ScopedOutput
from conans.client.file_copier import FileCopier


def export_conanfile(output, paths, file_patterns, origin_folder, conan_ref, short_paths,
                     keep_source):
    destination_folder = paths.export(conan_ref)

    previous_digest = _init_export_folder(destination_folder)

    _export(file_patterns, origin_folder, destination_folder, output)

    digest = FileTreeManifest.create(destination_folder)
    save(os.path.join(destination_folder, CONAN_MANIFEST), str(digest))

    if previous_digest and previous_digest.file_sums == digest.file_sums:
        digest = previous_digest
        output.info("The stored package has not changed")
        modified_recipe = False
    else:
        output.success('A new %s version was exported' % CONANFILE)
        output.info('Folder: %s' % destination_folder)
        modified_recipe = True

    source = paths.source(conan_ref, short_paths)
    dirty = os.path.join(source, DIRTY_FILE)
    remove = False
    if os.path.exists(dirty):
        output.info("Source folder is dirty, forcing removal")
        remove = True
    elif modified_recipe and not keep_source and os.path.exists(source):
        output.info("Package recipe modified in export, forcing source folder removal")
        output.info("Use the --keep-source, -k option to skip it")
        remove = True
    if remove:
        output.info("Removing 'source' folder, this can take a while for big packages")
        try:
            # remove only the internal
            rmdir(source)
        except BaseException as e:
            output.error("Unable to delete source folder. "
                         "Will be marked as dirty for deletion")
            output.warn(str(e))
            save(os.path.join(source, DIRTY_FILE), "")


def _init_export_folder(destination_folder):
    previous_digest = None
    try:
        if os.path.exists(destination_folder):
            if os.path.exists(os.path.join(destination_folder, CONAN_MANIFEST)):
                manifest_content = load(os.path.join(destination_folder, CONAN_MANIFEST))
                previous_digest = FileTreeManifest.loads(manifest_content)
            # Maybe here we want to invalidate cache
            rmdir(destination_folder)
        os.makedirs(destination_folder)
    except Exception as e:
        raise ConanException("Unable to create folder %s\n%s" % (destination_folder, str(e)))
    return previous_digest


def _export(file_patterns, origin_folder, destination_folder, output):
    file_patterns = file_patterns or []
    try:
        os.unlink(os.path.join(origin_folder, CONANFILE + 'c'))
    except:
        pass

    copier = FileCopier(origin_folder, destination_folder)
    for pattern in file_patterns:
        copier(pattern)
    package_output = ScopedOutput("%s export" % output.scope, output)
    copier.report(package_output)

    shutil.copy2(os.path.join(origin_folder, CONANFILE), destination_folder)
