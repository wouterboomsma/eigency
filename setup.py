import os
from os.path import basename, join
from setuptools import setup, find_packages
from setuptools.extension import Extension
from Cython.Build import cythonize

import eigency
import numpy as np

__package_name__ = "eigency"
__eigen_dir__ = eigency.__eigen_dir__
__eigen_lib_dir__ = join(basename(__eigen_dir__), 'Eigen')

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

eigen_data_files = []
for root, dirs, files in os.walk(join(__eigen_dir__, 'Eigen')):
    for f in files:
        if f.endswith('.h'):
            eigen_data_files.append(join(root, f))

dist = setup(
    name = __package_name__,
    description = "Cython interface between the numpy arrays and the Matrix/Array classes of the Eigen C++ library",
    long_description=long_description,
    author = "Wouter Boomsma",
    author_email = "wb@bio.ku.dk",
    url = "https://github.com/wouterboomsma/eigency",
    use_scm_version = True,
    setup_requires = ['setuptools_scm'],
    ext_modules = cythonize(extensions),
    packages = find_packages(),
    package_data = {__package_name__: [
        '*.h', '*.pxd',
        join(__eigen_lib_dir__, '*'),
    ] + eigen_data_files},
    install_requires = ['numpy', 'cython']
)

