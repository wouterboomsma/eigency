import os
from os.path import basename, join
from setuptools import setup, find_packages
from setuptools.extension import Extension

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

# This hack delays importing cythonize until after setup_requires ensures that it exists.
# ext_modules is expecting a list, so just wait to actually make the list until the first
# time iter is called on it.
class cythonize(list):
    def __init__(self, ext):
        self.ext = ext

    def __iter__(self):
        if self.ext is not None:
            from Cython.Build import cythonize
            list.__init__(self, cythonize(self.ext))
            self.ext = None
        return list.__iter__(self)

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
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: C++',
        'Programming Language :: Cython',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
    ],
    license = "MIT",
    author = "Wouter Boomsma",
    author_email = "wb@di.ku.dk",
    url = "https://github.com/wouterboomsma/eigency",
    use_scm_version = True,
    setup_requires = ['setuptools>=38','setuptools_scm', 'cython'],
    ext_modules = cythonize(extensions),
    packages = find_packages(),
    include_package_data=True,
    package_data = {__package_name__: [
        '*.h', '*.pxd', '*.pyx',
        join(__eigen_lib_dir__, '*'),
    ] + eigen_data_files},
    exclude_package_data = {__package_name__: [join(__eigen_lib_dir__, 'CMakeLists.txt')]},
    install_requires = ['numpy', 'cython']
)

