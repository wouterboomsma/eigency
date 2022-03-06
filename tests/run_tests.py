import unittest

import eigency_tests
import numpy as np
from numpy.testing import assert_array_equal


class TestEigency(unittest.TestCase):
    def test_function_w_vec_arg(self):
        x = np.array([1.0, 2.0, 3.0, 4.0])
        cpp_size = eigency_tests.function_w_vec_arg(x)
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.0)
        self.assertEqual(cpp_size, 4)

    def test_function_w_1darr_arg(self):
        x = np.array([1, 2, 3, 4], dtype=np.int32)
        cpp_size = eigency_tests.function_w_1darr_arg(x)
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0)
        self.assertEqual(cpp_size, 4)

    def test_function_w_vec_arg_no_map1(self):
        x = np.array([1.0, 2.0, 3.0, 4.0])
        eigency_tests.function_w_vec_arg_no_map1(x)
        # No shared memory test: Verify that first entry was NOT altered by C++ code.
        self.assertAlmostEqual(x[0], 1.0)

    def test_function_w_vec_arg_no_map2(self):
        x = np.array([1.0, 2.0, 3.0, 4.0])
        eigency_tests.function_w_vec_arg_no_map2(x)
        # No shared memory test: Verify that first entry was NOT altered by C++ code.
        self.assertAlmostEqual(x[0], 1.0)

    def test_function_w_mat_arg(self):
        x = np.array([1.1, 2.2, 3.3, 4.4])
        eigency_tests.function_w_mat_arg(x.reshape([2, 2]))
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.0)

    def test_function_w_ld_mat_arg(self):
        x = np.array([1.1, 2.2, 3.3, 4.4], dtype=np.longdouble)
        eigency_tests.function_w_ld_mat_arg(x.reshape([2, 2]))
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.0)

    def test_function_w_complex_mat_arg(self):
        x = np.array([1.0 + 1.0j, 2.0 + 1.0j, 3.0 + 1.0j, 4.0 + 1.0j])
        eigency_tests.function_w_complex_mat_arg(x.reshape([2, 2]))
        # Shared memory test: Verify that first entry was set to 0.+0.j by C++ code.
        self.assertAlmostEqual(x[0], 0.0 + 0.0j)

    def test_function_w_complex_ld_mat_arg(self):
        x = np.array([1.0 + 1.0j, 2.0 + 1.0j, 3.0 + 1.0j, 4.0 + 1.0j], dtype=np.clongdouble)
        eigency_tests.function_w_complex_ld_mat_arg(x.reshape([2, 2]))
        # Shared memory test: Verify that first entry was set to 0.+0.j by C++ code.
        self.assertAlmostEqual(x[0], 0.0 + 0.0j)

    def test_funcion_w_fullspec_arg(self):
        x = np.array([1.0, 2.0, 3.0, 4.0])
        eigency_tests.function_w_fullspec_arg(x)
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.0)

    def test_vec_retval(self):
        retval = eigency_tests.function_w_vec_retval()
        # Consistent with Eigen, return values always have two dimensions - even when it's a vector
        # No Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0, 0] = 0.0
        retval = eigency_tests.function_w_vec_retval()
        self.assertAlmostEqual(retval[0, 0], 4.0)

    def test_mat_retval(self):
        retval = eigency_tests.function_w_mat_retval()
        # No Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0, 0] = 0.0
        retval = eigency_tests.function_w_mat_retval()
        self.assertAlmostEqual(retval[0, 0], 4.0)

    def test_empty_mat_retval(self):
        retval = eigency_tests.function_w_empty_mat_retval()
        self.assertEqual(retval.size, 0)

    def test_mat_ref_retval(self):
        my_object = eigency_tests.FixedMatrixClass()
        retval = my_object.get_matrix()
        # Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0, 0] = 0.0
        retval = my_object.get_matrix()
        self.assertAlmostEqual(retval[0, 0], 0.0)

    def test_mat_constref_retval(self):
        my_object = eigency_tests.FixedMatrixClass()
        retval = my_object.get_const_matrix()
        # No shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0, 0] = 0.0
        retval = my_object.get_const_matrix()
        self.assertAlmostEqual(retval[0, 0], 4.0)

    def test_mat_constref_retval_force_view(self):
        my_object = eigency_tests.FixedMatrixClass()
        retval = my_object.get_const_matrix_force_view()
        # Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0, 0] = 0.0
        retval = my_object.get_const_matrix_force_view()
        self.assertAlmostEqual(retval[0, 0], 0.0)

    def test_storage_order1(self):
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]])
        y = eigency_tests.function_filter1(x)
        # y is transposed
        assert_array_equal(x, y.transpose())

    def test_storage_order2(self):
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]])
        # C++ function explicitly uses C-storage order
        y = eigency_tests.function_filter2(x)
        assert_array_equal(x, y)
        # print x
        # print y

    def test_storage_order3(self):
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]])
        # C++ function explicitly uses C-storage order map stride
        y = eigency_tests.function_filter3(x)
        assert_array_equal(x, y)

    def test_storage_order4(self):
        # Explicitly use F-storage order in numpy array
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], order="F")
        y = eigency_tests.function_filter1(x)
        assert_array_equal(x, y)

    def test_mat_ref_retval_array(self):
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], order="F")
        my_object = eigency_tests.DynamicArrayClass(x)
        y = my_object.get_array()
        # Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        y[0, 0] = 0.0
        y = my_object.get_array()
        self.assertAlmostEqual(y[0, 0], 0.0)
        assert_array_equal(x, y)

    def test_mat_ref_retval_array_row_major(self):
        x = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]])
        my_object = eigency_tests.DynamicRowMajorArrayClass(x)
        y = my_object.get_array_copy()
        assert_array_equal(x, y)

    def test_function_type_float64(self):
        # C++ double
        mat_in = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], order="F", dtype=np.float64)
        mat_out = eigency_tests.function_type_float64(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_float32(self):
        # C++ float
        mat_in = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], order="F", dtype=np.float32)
        mat_out = eigency_tests.function_type_float32(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_int(self):
        # C++ long - Note that this is the standard Python integer
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F")
        # # equivalent to:
        # mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order='F', dtype=np.int_)
        mat_out = eigency_tests.function_type_long(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_long(self):
        # C++ long - Note that this is the standard Python integer
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=int)
        # # equivalent to:
        # mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order='F', dtype=np.int_)
        mat_out = eigency_tests.function_type_long(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_ulong(self):
        # C++ ulong
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.uint)
        mat_out = eigency_tests.function_type_ulong(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_intc(self):
        # C++ int
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.intc)
        mat_out = eigency_tests.function_type_intc(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_uintc(self):
        # C++ uint
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.uintc)
        mat_out = eigency_tests.function_type_uintc(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_short(self):
        # C++ short
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.short)
        mat_out = eigency_tests.function_type_short(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_unsigned_short(self):
        # C++ ushort
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.ushort)
        mat_out = eigency_tests.function_type_ushort(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_signed_char(self):
        # C++ char
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.int8)
        mat_out = eigency_tests.function_type_int8(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_unsigned_char(self):
        # C++ unsigned char
        mat_in = np.array([[1, 2, 3, 4], [5, 6, 7, 8]], order="F", dtype=np.uint8)
        mat_out = eigency_tests.function_type_uint8(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_complex128(self):
        # C++ char
        mat_in = np.array(
            [
                [1.0 + 1.0j, 2.0 + 2.0j, 3.0 + 3.0j, 4.0 + 4.0j],
                [5.0 + 5.0j, 6.0 + 6.0j, 7.0 + 7.0j, 8.0 + 8.0j],
            ],
            order="F",
            dtype=np.complex128,
        )
        mat_out = eigency_tests.function_type_complex128(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_type_complex64(self):
        # C++ char
        mat_in = np.array(
            [
                [1.0 + 1.0j, 2.0 + 2.0j, 3.0 + 3.0j, 4.0 + 4.0j],
                [5.0 + 5.0j, 6.0 + 6.0j, 7.0 + 7.0j, 8.0 + 8.0j],
            ],
            order="F",
            dtype=np.complex64,
        )
        mat_out = eigency_tests.function_type_complex64(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_single_col_matrix(self):
        # Issue #11
        mat_in = np.zeros((2, 3), order="F")
        mat_out = eigency_tests.function_single_col_matrix(mat_in)
        assert_array_equal(mat_in, mat_out)
        mat_in = np.zeros((1, 3), order="F")
        mat_out = eigency_tests.function_single_col_matrix(mat_in)
        assert_array_equal(mat_in, mat_out)

    def test_function_map_holds_reference(self):
        # Tests error fixed by 4ee448a in pull request #18
        mat_in = np.array([[1.0, 2.0, 3.0, 4.0], [5.0, 6.0, 7.0, 8.0]], order="F", dtype=np.float64)
        mat_out = eigency_tests.function_map_holds_reference(mat_in)
        assert_array_equal(mat_in, mat_out)


if __name__ == "__main__":
    unittest.main(buffer=False)
