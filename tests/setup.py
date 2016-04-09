import os
from distutils import file_util
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import eigency

extensions = [
    Extension("eigency_tests.eigency_tests", ["eigency_tests/eigency_tests.pyx"],
        include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    ),
]

dist = setup(
    name = "eigency_tests",
    version = "1.0",
    ext_modules = cythonize(extensions),
    packages = ["eigency_tests"]
)

if dist.command_obj.has_key('install'):
    destination_path = dist.command_obj['install'].install_lib
    package_path = os.path.join(destination_path, "eigency_tests")

    # Copy init file
    file_util.copy_file('eigency_tests/init.py', os.path.join(package_path, "__init__.py"), update=1, preserve_mode=0)

