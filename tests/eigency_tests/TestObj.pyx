# distutils: language = c++

from eigency.core cimport *

from eigency_tests.TestObject cimport TestObject


cdef class TestObj:

    cdef TestObject to

    def __cinit__(self):
        self.to = TestObject()

    @property
    def data(self):
        return ndarray(self.to.data)
