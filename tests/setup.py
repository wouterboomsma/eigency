from setuptools import setup
from setuptools.extension import Extension
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

