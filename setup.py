import os
from setuptools import setup
from distutils import dir_util, file_util
from setuptools.extension import Extension
from Cython.Build import cythonize


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

datafiles2 = []
os.chdir('eigency')
for d, folders, files in  os.walk('eigen_3.2.8'):
    the_files=[os.path.join(d,f) for f in files]
    datafiles2.extend(the_files)
os.chdir('..')

    
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
    packages = [__package_name__]
)

