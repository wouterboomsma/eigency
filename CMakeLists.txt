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

configure_file(eigency/__init__.py.in ${CMAKE_SOURCE_DIR}/eigency/__init__.py @ONLY)
configure_file(MANIFEST.in.in ${CMAKE_SOURCE_DIR}/MANIFEST.in @ONLY)

add_custom_target(${PROJECT_NAME} ALL python setup.py install WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} VERBATIM)
