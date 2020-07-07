project(eigency)
set(PROJECT_VERSION 1.77)
set(PROJECT_DESCRIPTION "Python Wrapper for eigen")
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)


include(FindPkgConfig)
pkg_check_modules(EIGEN
  eigen3
)

if(PYTHON_EXECUTABLE)
    message(STATUS "Defined python executable is: ${PYTHON_EXECUTABLE}")
    set(Python_EXECUTABLE ${PYTHON_EXECUTABLE})
elseif("$ENV{PYTHON}" STREQUAL "")
    # https://cmake.org/cmake/help/v3.12/module/FindPython.html
    find_package(Python COMPONENTS Interpreter)
else()
    set(PYTHON $ENV{PYTHON})
    message(STATUS ${PYTHON})
endif()

if("$ENV{CYTHON}" STREQUAL "")
    find_program(CYTHON
        NAMES cython cython3
    )
else()
    set(CYTHON $ENV{CYTHON})
    message(STATUS ${CYTHON})
endif()

message(STATUS "Using python: ${Python_EXECUTABLE}")
message(STATUS "Detected python version: ${Python_VERSION}")
message(STATUS "Using cython: ${CYTHON}")

message(STATUS "Found Eigen in: ${EIGEN_INCLUDE_DIRS}")
execute_process(COMMAND ${Python_EXECUTABLE} -c "import os.path; print(os.path.relpath('${EIGEN_INCLUDE_DIRS}', '${CMAKE_SOURCE_DIR}'), end='')" OUTPUT_VARIABLE EIGEN_REL_PATH)
message(STATUS "  Relative: ${EIGEN_REL_PATH}")
execute_process(COMMAND ${Python_EXECUTABLE} -c "import sys; print('${CMAKE_INSTALL_PREFIX}/lib/python'+str(sys.version[0])+'.'+str(sys.version[2])+'/site-packages', end='')" OUTPUT_VARIABLE PYTHON_INSTALL_DIR)
message(STATUS "Installing to: ${PYTHON_INSTALL_DIR}")

set(APROOT $ENV{AUTOPROJ_CURRENT_ROOT})
configure_file(eigency/__init__.py.in ${CMAKE_SOURCE_DIR}/eigency/__init__.py @ONLY)
configure_file(MANIFEST.in.in ${CMAKE_SOURCE_DIR}/MANIFEST.in @ONLY)

add_custom_target(python ALL
    COMMAND ${Python_EXECUTABLE} setup.py install --prefix=${CMAKE_INSTALL_PREFIX}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM )
