from Cython.Build import cythonize
from setuptools import setup
from setuptools.extension import Extension

import eigency

extensions = [
    Extension(
        "eigency_tests.eigency_tests",
        ["eigency_tests/eigency_tests.pyx"],
        include_dirs=[".", "eigency_tests"] + eigency.get_includes(),
    ),
]

setup(
    name="eigency_tests",
    version="0.0.0",
    ext_modules=cythonize(extensions),
    packages=["eigency_tests"],
)
