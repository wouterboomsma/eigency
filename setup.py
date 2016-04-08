import os
from distutils import file_util
from distutils import dir_util
from distutils import sysconfig
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import numpy as np

__packagename__ = "eigency"
dist = setup(
    name = __packagename__,
    version = '0.1',
    packages = [__packagename__],
    package_data={'': ['*.h']}
)

extensions = [
    Extension("eigency.core", ["eigency/core.pyx"],
              include_dirs = [".", "eigency_tests", np.get_include(), "../eigency", "eigen_3.2.8", ".."]
              # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    ),
    Extension("eigency.conversions", ["eigency/conversions.pyx"],
              include_dirs = [".", "eigency_tests", np.get_include(), "../eigency", "eigen_3.2.8", ".."]
              # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    )
]

setup(
    name = "eigency",
    ext_modules = cythonize(extensions),
    packages = ["eigency"]
    # ,package_dir = {'eigency':'..'}
)


destination_path = dist.command_obj['install'].install_lib
package_path = os.path.join(destination_path, __packagename__)

# Copy cython files
file_util.copy_file('eigency/core.pxd', package_path, update=1, preserve_mode=0)
file_util.copy_file('eigency/core.pyx', package_path, update=1, preserve_mode=0)
file_util.copy_file('eigency/conversions.pxd', package_path, update=1, preserve_mode=0)
file_util.copy_file('eigency/conversions.pyx', package_path, update=1, preserve_mode=0)

# Copy Eigen header files
eigen_path = os.path.join(package_path, 'eigen')
dir_util.copy_tree('eigen', eigen_path, update=1, preserve_mode=0)

