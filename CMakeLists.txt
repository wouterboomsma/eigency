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
set(PYTHON_INSTALL_DIR "$ENV{PYTHONPATH}") #"${CMAKE_INSTALL_PREFIX}")
message(STATUS "Installing to: ${PYTHON_INSTALL_DIR}")

configure_file(eigency/__init__.py.in ${CMAKE_SOURCE_DIR}/eigency/__init__.py @ONLY)
configure_file(MANIFEST.in.in ${CMAKE_SOURCE_DIR}/MANIFEST.in @ONLY)

install(CODE "execute_process(COMMAND python setup.py install --prefix=${CMAKE_INSTALL_PREFIX}  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})")
