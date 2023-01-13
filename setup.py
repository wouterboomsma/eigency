import os
import sys
from os.path import basename, join

import numpy as np
from setuptools import find_packages, setup
from setuptools.extension import Extension

sys.path.append(".")


__package_name__ = "eigency"

include_dirs = [np.get_include()]
if "EIGEN_INC" in os.environ:
    useSystemEigen = True
    include_dirs.append(os.environ["EIGEN_INC"])
else:
    useSystemEigen = False
    import eigency  # noqa: E402
    __eigen_dir__ = eigency.get_eigency_eigen_dir()
    __eigen_lib_dir__ = join(basename(__eigen_dir__), "Eigen")
    include_dirs.append(__eigen_dir__)
# Not all users may have cython installed.  If they only want this as a means
# to access the Eigen header files to compile their own C++ code, then they
# may not have cython already installed.  Therefore, only require cython
# for cases where the user will need to build the .cpp files from the .pyx
# files (typically from a git clone) and not for other pip installations.
# cf. discussion in PR #26.

# Follow the pattern recommended here:
# http://cython.readthedocs.io/en/latest/src/reference/compilation.html#distributing-cython-modules
try:
    from Cython.Build import cythonize

    # Maybe make this a command line option?
    USE_CYTHON = True
    ext = ".pyx"
except ImportError:
    USE_CYTHON = False
    ext = ".cpp"

extensions = [
    Extension(
        "eigency.conversions",
        ["eigency/conversions" + ext],
        include_dirs=include_dirs,
        language="c++",
    ),
    Extension(
        "eigency.core",
        ["eigency/core" + ext],
        include_dirs=include_dirs,
        language="c++",
    ),
]

if USE_CYTHON:
    extensions = cythonize(extensions)

long_description = open("README.md").read()

eigen_data_files = []
exclude_package_data = {}
if not useSystemEigen:
    for root, dirs, files in os.walk(join(__eigen_dir__, "Eigen")):
        for f in files:
            if f.endswith(".h"):
                eigen_data_files.append(join(root, f))
    eigen_data_files.append(join(__eigen_lib_dir__, "*"))
    exclude_package_data = {__package_name__: [join(__eigen_lib_dir__, "CMakeLists.txt")]}

setup(
    name=__package_name__,
    description="Cython interface between the numpy arrays and the Matrix/Array classes of the Eigen C++ library",
    long_description=long_description,
    long_description_content_type="text/markdown",
    classifiers=[
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: C++",
        "Programming Language :: Cython",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
    ],
    license="MIT",
    author="Wouter Boomsma",
    author_email="wb@di.ku.dk",
    url="https://github.com/wouterboomsma/eigency",
    use_scm_version=True,
    ext_modules=extensions,
    packages=find_packages(),
    include_package_data=True,
    package_data={__package_name__: ["*.h", "*.pxd", "*.pyx"] + eigen_data_files},
    exclude_package_data=exclude_package_data,
    python_requires=">=3.5",
    install_requires=["numpy"],
)
