cimport numpy as np

cdef api np.ndarray[double, ndim=2] ndarray_double_C(double *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[double, ndim=2] ndarray_double_F(double *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[double, ndim=2] ndarray_copy_double_C(const double *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[double, ndim=2] ndarray_copy_double_F(const double *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[float, ndim=2] ndarray_float_C(float *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[float, ndim=2] ndarray_float_F(float *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[float, ndim=2] ndarray_copy_float_C(const float *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[float, ndim=2] ndarray_copy_float_F(const float *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[long, ndim=2] ndarray_long_C(long *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[long, ndim=2] ndarray_long_F(long *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[long, ndim=2] ndarray_copy_long_C(const long *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[long, ndim=2] ndarray_copy_long_F(const long *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[int, ndim=2] ndarray_int_C(int *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[int, ndim=2] ndarray_int_F(int *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[int, ndim=2] ndarray_copy_int_C(const int *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[int, ndim=2] ndarray_copy_int_F(const int *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[short, ndim=2] ndarray_short_C(short *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[short, ndim=2] ndarray_short_F(short *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[short, ndim=2] ndarray_copy_short_C(const short *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[short, ndim=2] ndarray_copy_short_F(const short *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[char, ndim=2] ndarray_char_C(char *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[char, ndim=2] ndarray_char_F(char *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[char, ndim=2] ndarray_copy_char_C(const char *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[char, ndim=2] ndarray_copy_char_F(const char *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[np.complex128_t, ndim=2] ndarray_complex_double_C(np.complex128_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex128_t, ndim=2] ndarray_complex_double_F(np.complex128_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex128_t, ndim=2] ndarray_copy_complex_double_C(const np.complex128_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex128_t, ndim=2] ndarray_copy_complex_double_F(const np.complex128_t *data, long rows, long cols, long outer_stride, long inner_stride)

cdef api np.ndarray[np.complex64_t, ndim=2] ndarray_complex_float_C(np.complex64_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex64_t, ndim=2] ndarray_complex_float_F(np.complex64_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex64_t, ndim=2] ndarray_copy_complex_float_C(const np.complex64_t *data, long rows, long cols, long outer_stride, long inner_stride)
cdef api np.ndarray[np.complex64_t, ndim=2] ndarray_copy_complex_float_F(const np.complex64_t *data, long rows, long cols, long outer_stride, long inner_stride)

