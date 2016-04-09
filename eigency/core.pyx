# distutils: language = c++

cimport cython
from cython.operator cimport dereference as deref
import numpy as np

# @cython.boundscheck(False)
# cdef MapSettings from_numpy_1d(double[:] array_data_mview):
#     # cdef double[:] array_data_mview = array_data
#     cdef double *array_data_raw = &array_data_mview[0]
#     return MapSettings(array_data_raw, max(1, array_data_mview.shape[0]), max(1, array_data_mview.shape[1]))

# @cython.boundscheck(False)
# cdef MapSettings from_numpy_2d(double[:,:] array_data_mview):
#     # cdef double[:,:] array_data_mview = array_data
#     cdef double *array_data_raw = &array_data_mview[0,0]
#     return MapSettings(array_data_raw, max(1, array_data_mview.shape[0]), max(1, array_data_mview.shape[1]))


@cython.boundscheck(False)
cdef MapSettings from_numpy(np.ndarray array_data):
    print array_data.ndim
    if array_data.ndim == 1:
        array_data = array_data.reshape(1, array_data.shape[0])
    cdef double[:,:] array_data_mview = array_data
    cdef double *array_data_raw = &array_data_mview[0,0]
    return MapSettings(array_data_raw, array_data_mview.shape[0], array_data_mview.shape[1])