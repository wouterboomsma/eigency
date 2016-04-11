# distutils: language = c++
# distutils: sources = eigency_tests/eigency_tests_cpp.cpp

from eigency.core cimport *
# cimport eigency.conversions
# from eigency_tests.eigency cimport *


# import eigency
# include "../eigency.pyx"
 
cdef extern from "eigency_tests/eigency_tests_cpp.h":

     cdef void _function_w_vec_arg "function_w_vec_arg"(Map[VectorXd] &)

     cdef void _function_w_vec_arg_no_map1 "function_w_vec_arg_no_map1"(Map[VectorXd])

     cdef void _function_w_vec_arg_no_map2 "function_w_vec_arg_no_map2"(Map[VectorXd] &)

     cdef void _function_w_mat_arg "function_w_mat_arg"(Map[MatrixXd] &)

     cdef void _function_w_fullspec_arg "function_w_fullspec_arg" (FlattenedMap[Array, double, Dynamic, _1] &)

     cdef VectorXd _function_w_vec_retval "function_w_vec_retval" ()

     cdef Matrix3d _function_w_mat_retval "function_w_mat_retval" ()

     cdef PlainObjectBase _function_w_mat_retval_full_spec "function_w_mat_retval_full_spec" ()

     cdef cppclass _MyClass "MyClass":
         _MyClass "MyClass"() except +
         Matrix3d &get_matrix()

# Function with vector argument. 
def function_w_vec_arg(np.ndarray array):
    return _function_w_vec_arg(Map[VectorXd](from_numpy(array)))

# Function with vector argument - no map - no ref. 
def function_w_vec_arg_no_map1(np.ndarray array):
    return _function_w_vec_arg_no_map1(Map[VectorXd](from_numpy(array)))

# Function with vector argument - no map. 
def function_w_vec_arg_no_map2(np.ndarray array):
    return _function_w_vec_arg_no_map2(Map[VectorXd](from_numpy(array)))

# Function with matrix argument. 
def function_w_mat_arg(np.ndarray array):
    return _function_w_mat_arg(Map[MatrixXd](from_numpy(array)))

# Function using a full Map specification, rather than the convenience typedefs
# Note that since cython does not support nested fused types, the Map has been
# flattened to include all arguments at once
def function_w_fullspec_arg(np.ndarray array):
    return _function_w_fullspec_arg(FlattenedMap[Array, double, Dynamic, _1](from_numpy(array)))

# Function returning vector (copy is made)
def function_w_vec_retval():
    return to_numpy(_function_w_vec_retval())

# Function returning matrix (copy is made)
def function_w_mat_retval():
    return to_numpy(_function_w_mat_retval())

# Function returning matrix (copy is made)
def function_w_mat_retval_full_spec():
    return to_numpy(_function_w_mat_retval_full_spec())


cdef class MyClass:
    cdef _MyClass *thisptr;
    def __cinit__(self):
        self.thisptr = new _MyClass()
    def __dealloc__(self):
        del self.thisptr
    def get_matrix(self):
        return to_numpy(self.thisptr.get_matrix())