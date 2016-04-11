import unittest

import numpy as np
import eigency_tests

class TestEigency(unittest.TestCase):

    def test_function_w_vec_arg(self):
        x = np.array([1., 2., 3., 4.])
        eigency_tests.function_w_vec_arg(x)
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.)

    def test_function_w_vec_arg_no_map1(self):
        x = np.array([1., 2., 3., 4.])
        eigency_tests.function_w_vec_arg_no_map1(x)
        # No shared memory test: Verify that first entry was NOT altered by C++ code.
        self.assertAlmostEqual(x[0], 1.)

    def test_function_w_vec_arg_no_map2(self):
        x = np.array([1., 2., 3., 4.])
        eigency_tests.function_w_vec_arg_no_map2(x)
        # No shared memory test: Verify that first entry was NOT altered by C++ code.
        self.assertAlmostEqual(x[0], 1.)

    def test_function_w_mat_arg(self):
        x = np.array([1., 2., 3., 4.])
        eigency_tests.function_w_mat_arg(x.reshape([2,2]))
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.)        

    def test_funcion_w_fullspec_arg(self):
        x = np.array([1., 2., 3., 4.])
        eigency_tests.function_w_fullspec_arg(x)
        # Shared memory test: Verify that first entry was set to 0 by C++ code.
        self.assertAlmostEqual(x[0], 0.)        
        
    def test_vec_retval(self):
        retval = eigency_tests.function_w_vec_retval()
        # Consistent with Eigen, return values always have two dimensions - even when it's a vector
        print retval
        # No Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0,0] = 0.
        retval = eigency_tests.function_w_vec_retval()
        self.assertAlmostEqual(retval[0,0], 4.)        

    def test_mat_retval(self):
        retval = eigency_tests.function_w_mat_retval()
        print retval
        # No Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0,0] = 0.
        retval = eigency_tests.function_w_mat_retval()
        self.assertAlmostEqual(retval[0,0], 4.)        

    def test_mat_ref_retval(self):
        my_object = eigency_tests.MyClass()
        retval = my_object.get_matrix()
        # Shared memory test: Set first entry to zero and get matrix again to check that this change is maintained
        retval[0,0] = 0.
        retval = my_object.get_matrix()
        self.assertAlmostEqual(retval[0,0], 0.)        
        
if __name__ == '__main__':
    unittest.main(buffer=False)        
