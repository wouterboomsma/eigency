cimport numpy as np

cdef api np.ndarray[double, ndim=2] to_numpy_double(double *data, long rows, long cols)
cdef api np.ndarray[double, ndim=2] to_numpy_copy_double(const double *data, long rows, long cols)

cdef api np.ndarray[float, ndim=2] to_numpy_float(float *data, long rows, long cols)
cdef api np.ndarray[float, ndim=2] to_numpy_copy_float(const float *data, long rows, long cols)

cdef api np.ndarray[long, ndim=2] to_numpy_long(long *data, long rows, long cols)
cdef api np.ndarray[long, ndim=2] to_numpy_copy_long(const long *data, long rows, long cols)

cdef api np.ndarray[int, ndim=2] to_numpy_int(int *data, long rows, long cols)
cdef api np.ndarray[int, ndim=2] to_numpy_copy_int(const int *data, long rows, long cols)

cdef api np.ndarray[short, ndim=2] to_numpy_short(short *data, long rows, long cols)
cdef api np.ndarray[short, ndim=2] to_numpy_copy_short(const short *data, long rows, long cols)

cdef api np.ndarray[char, ndim=2] to_numpy_char(char *data, long rows, long cols)
cdef api np.ndarray[char, ndim=2] to_numpy_copy_char(const char *data, long rows, long cols)

