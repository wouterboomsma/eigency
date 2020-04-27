project(eigency)
set(PROJECT_VERSION 1.77)
set(PROJECT_DESCRIPTION "Python Wrapper for eigen")
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)


include(FindPkgConfig)
pkg_check_modules(EIGEN
  eigen3
)

message(STATUS "Found Eigen in: ${EIGEN_INCLUDE_DIRS}")
execute_process(COMMAND python -c "import os.path; print(os.path.relpath('${EIGEN_INCLUDE_DIRS}', '${CMAKE_SOURCE_DIR}'), end='')" OUTPUT_VARIABLE EIGEN_REL_PATH)
message(STATUS "  Relative: ${EIGEN_REL_PATH}")
execute_process(COMMAND python -c "import sys; print('${CMAKE_INSTALL_PREFIX}/lib/python'+str(sys.version[0])+'.'+str(sys.version[2])+'/site-packages', end='')" OUTPUT_VARIABLE PYTHON_INSTALL_DIR)
message(STATUS "Installing to: ${PYTHON_INSTALL_DIR}")

set(APROOT $ENV{AUTOPROJ_CURRENT_ROOT})
configure_file(eigency/__init__.py.in ${CMAKE_SOURCE_DIR}/eigency/__init__.py @ONLY)
configure_file(MANIFEST.in.in ${CMAKE_SOURCE_DIR}/MANIFEST.in @ONLY)
configure_file(install.sh.in ${CMAKE_SOURCE_DIR}/install.sh @ONLY)

add_custom_target(python ALL
    COMMAND python setup.py bdist_wheel --dist-dir=${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM )

install(CODE "execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/install.sh)")
