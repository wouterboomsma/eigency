cimport numpy as np

cdef api np.ndarray[double, ndim=2] ndarray_double(double *data, long rows, long cols)
cdef api np.ndarray[double, ndim=2] ndarray_copy_double(const double *data, long rows, long cols)

cdef api np.ndarray[float, ndim=2] ndarray_float(float *data, long rows, long cols)
cdef api np.ndarray[float, ndim=2] ndarray_copy_float(const float *data, long rows, long cols)

cdef api np.ndarray[long, ndim=2] ndarray_long(long *data, long rows, long cols)
cdef api np.ndarray[long, ndim=2] ndarray_copy_long(const long *data, long rows, long cols)

cdef api np.ndarray[int, ndim=2] ndarray_int(int *data, long rows, long cols)
cdef api np.ndarray[int, ndim=2] ndarray_copy_int(const int *data, long rows, long cols)

cdef api np.ndarray[short, ndim=2] ndarray_short(short *data, long rows, long cols)
cdef api np.ndarray[short, ndim=2] ndarray_copy_short(const short *data, long rows, long cols)

cdef api np.ndarray[char, ndim=2] ndarray_char(char *data, long rows, long cols)
cdef api np.ndarray[char, ndim=2] ndarray_copy_char(const char *data, long rows, long cols)

