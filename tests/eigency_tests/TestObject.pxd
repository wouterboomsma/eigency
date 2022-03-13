from eigency.core cimport *
from libcpp.vector cimport vector


cdef extern from "TestObject.cpp":
    pass

# Declare the class with cdef

cdef extern from "TestObject.h" :
    cdef cppclass TestObject:
        TestObject() except +
        TestObject(FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&,
                   FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&,
                   FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&,
                   FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&,
                   FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&,
                   FlattenedMapWithOrder[Matrix, double, Dynamic, Dynamic, RowMajor]&) except +
        void initialize(Map[VectorXd]&)
        void predict(Map[VectorXd]&)
        void update(Map[VectorXd]&)
        Map[VectorXd] x_hat
