from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import eigency
import numpy as np

extensions = [
    Extension("eigency_tests.eigency_tests", ["eigency_tests/eigency_tests.pyx"],
        include_dirs = [".", "eigency_tests"] + eigency.get_includes()
        # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    ),
    # Extension("eigency_tests.eigency_tests", ["eigency_tests/eigency_tests.pyx"],
    #     include_dirs = [".", "eigency_tests", np.get_include(), "../eigency", "../eigen", ".."] 
    #     # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    # ),




    # Extension("eigency_tests.eigency", ["../eigency.pyx"],
    #           include_dirs = [".", np.get_include(), "../eigency", "../eigen", ".."],
    #     runtime_library_dirs=["/Users/wb/Library/Python/2.7/lib/python/site-packages/eigency"]      
    #     # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    # )

    # WORKS
    # Extension("eigency_tests.eigency", ["..//eigency.pyx"],
    #     include_dirs = [".", "eigency_tests", np.get_include(), "../eigency", "../eigen", ".."] 
    #     # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    # )




    # Extension("eigency.eigency", ["../eigency.pyx"],
    #     include_dirs = [".", np.get_include(), "../eigency", "../eigen", ".."] 
    #     # include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    # )
]

setup(
    name = "eigency_tests",
    ext_modules = cythonize(extensions),
    packages = ["eigency_tests"]
    # ,package_dir = {'eigency':'..'}
)
