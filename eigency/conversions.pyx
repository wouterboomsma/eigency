cimport cython
import numpy as np
from numpy.lib.stride_tricks import as_strided

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] ndarray_double_C(double *data, long rows, long cols, long row_stride, long col_stride):
    cdef double[:,:] mem_view = <double[:rows,:cols]>data
    cdef int itemsize = np.dtype('double').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] ndarray_double_F(double *data, long rows, long cols, long row_stride, long col_stride):
    cdef double[::1,:] mem_view = <double[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('double').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] ndarray_copy_double_C(const double *data, long rows, long cols, long row_stride, long col_stride):
    cdef double[:,:] mem_view = <double[:rows,:cols]>data
    cdef int itemsize = np.dtype('double').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[double, ndim=2] ndarray_copy_double_F(const double *data, long rows, long cols, long row_stride, long col_stride):
    cdef double[::1,:] mem_view = <double[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('double').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] ndarray_float_C(float *data, long rows, long cols, long row_stride, long col_stride):
    cdef float[:,:] mem_view = <float[:rows,:cols]>data
    cdef int itemsize = np.dtype('float').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] ndarray_float_F(float *data, long rows, long cols, long row_stride, long col_stride):
    cdef float[::1,:] mem_view = <float[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('float').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] ndarray_copy_float_C(const float *data, long rows, long cols, long row_stride, long col_stride):
    cdef float[:,:] mem_view = <float[:rows,:cols]>data
    cdef int itemsize = np.dtype('float').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[float, ndim=2] ndarray_copy_float_F(const float *data, long rows, long cols, long row_stride, long col_stride):
    cdef float[::1,:] mem_view = <float[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('float').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] ndarray_long_C(long *data, long rows, long cols, long row_stride, long col_stride):
    cdef long[:,:] mem_view = <long[:rows,:cols]>data
    cdef int itemsize = np.dtype('long').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] ndarray_long_F(long *data, long rows, long cols, long row_stride, long col_stride):
    cdef long[::1,:] mem_view = <long[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('long').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] ndarray_copy_long_C(const long *data, long rows, long cols, long row_stride, long col_stride):
    cdef long[:,:] mem_view = <long[:rows,:cols]>data
    cdef int itemsize = np.dtype('long').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[long, ndim=2] ndarray_copy_long_F(const long *data, long rows, long cols, long row_stride, long col_stride):
    cdef long[::1,:] mem_view = <long[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('long').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] ndarray_int_C(int *data, long rows, long cols, long row_stride, long col_stride):
    cdef int[:,:] mem_view = <int[:rows,:cols]>data
    cdef int itemsize = np.dtype('int').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] ndarray_int_F(int *data, long rows, long cols, long row_stride, long col_stride):
    cdef int[::1,:] mem_view = <int[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('int').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] ndarray_copy_int_C(const int *data, long rows, long cols, long row_stride, long col_stride):
    cdef int[:,:] mem_view = <int[:rows,:cols]>data
    cdef int itemsize = np.dtype('int').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[int, ndim=2] ndarray_copy_int_F(const int *data, long rows, long cols, long row_stride, long col_stride):
    cdef int[::1,:] mem_view = <int[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('int').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] ndarray_short_C(short *data, long rows, long cols, long row_stride, long col_stride):
    cdef short[:,:] mem_view = <short[:rows,:cols]>data
    cdef int itemsize = np.dtype('short').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] ndarray_short_F(short *data, long rows, long cols, long row_stride, long col_stride):
    cdef short[::1,:] mem_view = <short[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('short').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] ndarray_copy_short_C(const short *data, long rows, long cols, long row_stride, long col_stride):
    cdef short[:,:] mem_view = <short[:rows,:cols]>data
    cdef int itemsize = np.dtype('short').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[short, ndim=2] ndarray_copy_short_F(const short *data, long rows, long cols, long row_stride, long col_stride):
    cdef short[::1,:] mem_view = <short[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('short').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] ndarray_char_C(char *data, long rows, long cols, long row_stride, long col_stride):
    cdef char[:,:] mem_view = <char[:rows,:cols]>data
    cdef int itemsize = np.dtype('char').itemsize
    return as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize])
@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] ndarray_char_F(char *data, long rows, long cols, long row_stride, long col_stride):
    cdef char[::1,:] mem_view = <char[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('char').itemsize
    return as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize])

@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] ndarray_copy_char_C(const char *data, long rows, long cols, long row_stride, long col_stride):
    cdef char[:,:] mem_view = <char[:rows,:cols]>data
    cdef int itemsize = np.dtype('char').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="C"), strides=[row_stride*itemsize, col_stride*itemsize]))
@cython.boundscheck(False)
cdef np.ndarray[char, ndim=2] ndarray_copy_char_F(const char *data, long rows, long cols, long row_stride, long col_stride):
    cdef char[::1,:] mem_view = <char[:rows:1,:cols]>data
    cdef int itemsize = np.dtype('char').itemsize
    return np.copy(as_strided(np.asarray(mem_view, order="F"), strides=[row_stride*itemsize, col_stride*itemsize]))


