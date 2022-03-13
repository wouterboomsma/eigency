import os

from Cython.Build import cythonize
from setuptools import setup
from setuptools.extension import Extension

import eigency

extensions = [
    Extension(
        "eigency_tests.eigency_tests",
        ["eigency_tests/eigency_tests.pyx"],
        include_dirs=[".", "eigency_tests"] + eigency.get_includes(),
        extra_compile_args=["-std=c++11", "-pthread", "-DEIGEN_MPL2_ONLY", "-Wno-unknown-pragmas"],
    ),
]

os.environ["CFLAGS"] = "-Og -Wall -march=haswell -mtune=skylake"

setup(
    name="eigency_tests",
    version="0.0.0",
    ext_modules=cythonize(
        extensions,
        compiler_directives=dict(
            language_level="3",
        ),
    ),
    packages=["eigency_tests"],
)
