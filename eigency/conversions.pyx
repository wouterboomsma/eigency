cimport cython
import numpy as np

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] to_numpy_double(double *data, long rows, long cols):
    cdef double[:,:] mem_view = <double[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] to_numpy_copy_double(const double *data, long rows, long cols):
    cdef double[:,:] mem_view = <double[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] to_numpy_float(float *data, long rows, long cols):
    cdef float[:,:] mem_view = <float[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] to_numpy_copy_float(const float *data, long rows, long cols):
    cdef float[:,:] mem_view = <float[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] to_numpy_long(long *data, long rows, long cols):
    cdef long[:,:] mem_view = <long[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] to_numpy_copy_long(const long *data, long rows, long cols):
    cdef long[:,:] mem_view = <long[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] to_numpy_int(int *data, long rows, long cols):
    cdef int[:,:] mem_view = <int[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] to_numpy_copy_int(const int *data, long rows, long cols):
    cdef int[:,:] mem_view = <int[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] to_numpy_short(short *data, long rows, long cols):
    cdef short[:,:] mem_view = <short[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] to_numpy_copy_short(const short *data, long rows, long cols):
    cdef short[:,:] mem_view = <short[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] to_numpy_char(char *data, long rows, long cols):
    cdef char[:,:] mem_view = <char[:rows,:cols]>data
    return np.asarray(mem_view)     

@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] to_numpy_copy_char(const char *data, long rows, long cols):
    cdef char[:,:] mem_view = <char[:rows,:cols]>data
    return np.copy(np.asarray(mem_view))


