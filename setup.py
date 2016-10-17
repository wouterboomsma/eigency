import os
from setuptools import setup
from distutils import dir_util, file_util
from setuptools.extension import Extension
from Cython.Build import cythonize
import glob

import eigency
import numpy as np

__package_name__ = "eigency"
__eigen_dir__ = eigency.__eigen_dir__

extensions = [
    Extension("eigency.conversions", ["eigency/conversions.pyx"],
              include_dirs = [np.get_include(), __eigen_dir__],
              language="c++"
    ),
    Extension("eigency.core", ["eigency/core.pyx"],
              include_dirs = [np.get_include(), __eigen_dir__],
              language="c++"
    )
]

try:
    import pypandoc
    long_description = pypandoc.convert('README.md', 'rst')
except(IOError, ImportError):
    long_description = open('README.md').read()

datafiles = [(d, [os.path.join(d,f) for f in files])
    for d, folders, files in os.walk('eigency/eigen_3.2.8')]

datafiles2 = []
os.chdir('eigency')
for d, folders, files in  os.walk('eigen_3.2.8'):
    the_files=[os.path.join(d,f) for f in files]
    datafiles2.extend(the_files)
os.chdir('..')

print(datafiles2[:40])    
    
dist = setup(
    name = __package_name__,
    version = "1.70",
    description = "Cython interface between the numpy arrays and the Matrix/Array classes of the Eigen C++ library",
    long_description=long_description,
    author = "Wouter Boomsma",
    author_email = "wb@bio.ku.dk",
    url = "https://github.com/wouterboomsma/eigency",
    download_url = "https://github.com/wouterboomsma/eigency/tarball/1.70",
    include_package_data = True,
    package_data={'eigency':datafiles2},
    ext_modules = cythonize(extensions),
    data_files=datafiles,
    packages = [__package_name__]
)

# if 'install' in dist.command_obj:
#     destination_path = dist.command_obj['install'].install_lib
#     package_path = os.path.join(destination_path, __package_name__)
#     # Copy cython files
#     file_util.copy_file('eigency/core.pxd', package_path, update=1, preserve_mode=0)
#     file_util.copy_file('eigency/core.pyx', package_path, update=1, preserve_mode=0)
#     file_util.copy_file('eigency/conversions.pxd', package_path, update=1, preserve_mode=0)
#     file_util.copy_file('eigency/conversions.pyx', package_path, update=1, preserve_mode=0)

#     # Copy C++ file
#     file_util.copy_file('eigency/eigency_cpp.h', package_path, update=1, preserve_mode=0)
#     file_util.copy_file('eigency/conversions_api.h', package_path, update=1, preserve_mode=0)
    
#     # Copy Eigen header files
#     eigen_path = os.path.join(package_path, __eigen_dir__)
#     dir_util.copy_tree(__eigen_dir__, eigen_path, update=1, preserve_mode=0)

#https://en.wikipedia.org/wiki/Inverse_trigonometric_functions
