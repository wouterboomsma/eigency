# distutils: language = c++

cimport cython
from cython.operator cimport dereference as deref
import numpy as np

# @cython.boundscheck(False)
# cdef np.ndarray[np.double_t, ndim=2] to_numpy_impl(void *data, int rows):
#     cdef double[:] mem_view = <double[:rows]>data
#     return np.asarray(mem_view)

# @cython.boundscheck(False)
# cdef np.ndarray[np.double_t, ndim=2] to_numpy(DenseTypeShort &v):
#     to_numpy_impl(v.data(), v.rows())

# @cython.boundscheck(False)
# cdef api np.ndarray[np.double_t, ndim=2] to_numpy2(double *data, int rows, int cols):
#     cdef double[:,:] mem_view = <double[:rows,:cols]>data
#     return np.asarray(mem_view)     

# @cython.boundscheck(False)
# cdef np.ndarray[np.double_t, ndim=2] to_numpy(VectorXd &v):
#     cdef VectorXd *v_ptr = &v;
#     cdef nrows = deref(v_ptr).rows()
#     cdef double[:] mem_view = <double[:nrows]>deref(v_ptr).data()
#     return np.asarray(mem_view)     

# @cython.boundscheck(False)
# cdef np.ndarray[np.double_t, ndim=2] to_numpy_copy(VectorXd v):
#     return(np.copy(to_numpy(v)))

@cython.boundscheck(False)
cdef MapSettings from_numpy_1d(double[:] array_data_mview):
    # cdef double[:] array_data_mview = array_data
    cdef double *array_data_raw = &array_data_mview[0]
    return MapSettings(array_data_raw, max(1, array_data_mview.shape[0]), max(1, array_data_mview.shape[1]))

@cython.boundscheck(False)
cdef MapSettings from_numpy_2d(double[:,:] array_data_mview):
    # cdef double[:,:] array_data_mview = array_data
    cdef double *array_data_raw = &array_data_mview[0,0]
    return MapSettings(array_data_raw, max(1, array_data_mview.shape[0]), max(1, array_data_mview.shape[1]))


# cdef np.ndarray[double, ndim=2] test(DenseType *data):
#      pass


cdef class _MapSettings:

    def to_numpy_copy(self):
        pass

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] to_numpy_old(MapSettings &settings):
    cdef void *data = settings.data();
    cdef nrows = settings.rows();
    cdef ncols = settings.cols();
    cdef double[:,:] mem_view = <double[:nrows,:ncols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] to_numpy_copy_old(MapSettings settings):
    return(np.copy(to_numpy_old(settings)))


# @cython.boundscheck(False)
# cdef np.ndarray[double, ndim=2] to_numpy_copy_direct2(DenseBase &&base):
#     to_eigency(base);