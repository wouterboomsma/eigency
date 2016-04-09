from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import eigency

extensions = [
    Extension("eigency_tests.eigency_tests", ["eigency_tests/eigency_tests.pyx"],
        include_dirs = [".", "eigency_tests"] + eigency.get_includes()
    ),
]

setup(
    name = "eigency_tests",
    version = "1.0",
    ext_modules = cythonize(extensions),
    packages = ["eigency_tests"]
)
