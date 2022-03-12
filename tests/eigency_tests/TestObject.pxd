from eigency.core cimport *


cdef extern from "TestObject.cpp":
    pass

cdef extern from "TestObject.h" :
    cdef cppclass TestObject:
        TestObject() except +
        Map[VectorXd] data
