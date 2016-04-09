# distutils: language = c++
# distutils: sources = eigency_tests/eigency_tests_cpp.cpp

from eigency.core cimport *
# cimport eigency.conversions
# from eigency_tests.eigency cimport *


# import eigency
# include "../eigency.pyx"
 
cdef extern from "eigency_tests/eigency_tests_cpp.h":

     cdef void _function_w_vec_arg "function_w_vec_arg"(Map[VectorXd] &)

     cdef void _function_w_mat_arg "function_w_mat_arg"(Map[MatrixXd] &)

     cdef void _set_first_zero_inplace "set_first_zero_inplace" (Map[VectorXd] &)
     
     cdef void _function_w_1darray_arg "function_w_1darray_arg" (FlattenedMap[Array, double, Dynamic, _1] &)

     cdef VectorXd _function_w_vec_retval "function_w_vec_retval" ()

     cdef Matrix3d _function_w_mat_retval "function_w_mat_retval" ()



# Function with vector argument. 
def function_w_vec_arg(np.ndarray[np.double_t, ndim=1] array):
    return _function_w_vec_arg(Map[VectorXd](from_numpy_1d(array)))

# Function with matrix argument. 
def function_w_mat_arg(np.ndarray[np.double_t, ndim=2] array):
    return _function_w_mat_arg(Map[MatrixXd](from_numpy_2d(array)))

# Function setting first entry to zero
def set_first_zero_inplace(np.ndarray[np.double_t, ndim=1] array):
    return _set_first_zero_inplace(Map[VectorXd](from_numpy_1d(array)))

# Function using a full Map specification, rather than the convenience typedefs
# Note that since cython does not support nested fused types, the Map has been
# flattened to include all arguments at once
def test_full_specification(np.ndarray[np.double_t, ndim=1] array):
    return _function_w_1darray_arg(FlattenedMap[Array, double, Dynamic, _1](from_numpy_1d(array)))

# Function returning vector (copy is made)
def function_w_vec_retval():
    return to_numpy_copy(_function_w_vec_retval())
    # return to_numpy_copy_old(to_eigency(_function_w_vec_retval()))

# Function returning matrix (copy is made)
def function_w_mat_retval():
    # _MapSettings(_function_w_mat_retval()).to_numpy_copy()
    # Eigency(_function_w_mat_retval()).to_numpy_copy();
    # return to_numpy_copy_old(to_eigency(_function_w_mat_retval()))
    return to_numpy_copy (_function_w_mat_retval())
    # return to_numpy_copy()


    # return function_w_arg(FlattenedMap[Matrix, double, Dynamic, _1](from_numpy(array)))
    # return _function_w_arg(FlattenedMap[Matrix, double, Dynamic, _1](&array[0]))

