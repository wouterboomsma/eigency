from __future__ import absolute_import
import unittest

import numpy as np
import eigency_tests

class TestEigency(unittest.TestCase):

    # def test_call_vec(self):
    #     eigency_tests.function_w_vec_arg(np.array([1., 2., 3., 4.]))

    def test_call_vec_no_ref(self):
        eigency_tests.function_w_vec_arg_no_ref(np.array([1., 2., 3., 4.]))

    # def test_call_mat(self):
    #     eigency_tests.function_w_mat_arg(np.array([1., 2., 3., 4.]).reshape([2,2]))

    # def test_full_specification(self):
    #     eigency_tests.test_full_specification(np.array([1., 2., 3., 4.]))
        
    # def test_modify_vec_in_place(self):
    #     x = np.array([1., 2., 3., 4.])
    #     eigency_tests.set_first_zero_inplace(x)
    #     self.assertAlmostEqual(x[0], 0.)

    # def test_vec_retval(self):
    #     retval = eigency_tests.function_w_vec_retval()
    #     print retval
    #     self.assertEqual(len(retval), 4)

    # def test_mat_retval(self):
    #     retval = eigency_tests.function_w_mat_retval()
    #     print retval
    #     self.assertEqual(retval.shape, (3,3))
        
if __name__ == '__main__':
    unittest.main(buffer=False)        
