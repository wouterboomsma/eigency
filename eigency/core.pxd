cimport cython
cimport numpy as np

ctypedef fused dtype:
    char
    short
    int
    long
    float
    double

ctypedef fused DenseType:
    Matrix
    Array

ctypedef fused Rows:
    _1
    _2
    _3
    _4
    _5
    _6
    _7
    _8
    _9
    _10
    _11
    _12
    _13
    _14
    _15
    _16
    _17
    _18
    _19
    _20
    _21
    _22
    _23
    _24
    _25
    _26
    _27
    _28
    _29
    _30
    _31
    _32
    Dynamic

ctypedef fused Cols:
    _1
    _2
    _3
    _4
    _5
    _6
    _7
    _8
    _9
    _10
    _11
    _12
    _13
    _14
    _15
    _16
    _17
    _18
    _19
    _20
    _21
    _22
    _23
    _24
    _25
    _26
    _27
    _28
    _29
    _30
    _31
    _32
    Dynamic

ctypedef fused DenseTypeShort:
    Vector1i
    Vector2i
    Vector3i
    Vector4i
    VectorXi
    RowVector1i
    RowVector2i
    RowVector3i
    RowVector4i
    RowVectorXi
    Matrix1i
    Matrix2i
    Matrix3i
    Matrix4i
    MatrixXi
    Vector1f
    Vector2f
    Vector3f
    Vector4f
    VectorXf
    RowVector1f
    RowVector2f
    RowVector3f
    RowVector4f
    RowVectorXf
    Matrix1f
    Matrix2f
    Matrix3f
    Matrix4f
    MatrixXf
    Vector1d
    Vector2d
    Vector3d
    Vector4d
    VectorXd
    RowVector1d
    RowVector2d
    RowVector3d
    RowVector4d
    RowVectorXd
    Matrix1d
    Matrix2d
    Matrix3d
    Matrix4d
    MatrixXd
    Vector1cf
    Vector2cf
    Vector3cf
    Vector4cf
    VectorXcf
    RowVector1cf
    RowVector2cf
    RowVector3cf
    RowVector4cf
    RowVectorXcf
    Matrix1cf
    Matrix2cf
    Matrix3cf
    Matrix4cf
    MatrixXcf
    Vector1cd
    Vector2cd
    Vector3cd
    Vector4cd
    VectorXcd
    RowVector1cd
    RowVector2cd
    RowVector3cd
    RowVector4cd
    RowVectorXcd
    Matrix1cd
    Matrix2cd
    Matrix3cd
    Matrix4cd
    MatrixXcd

cdef extern from "eigency_cpp.h" namespace "eigency":

     cdef cppclass _1 "1":
          pass
          
     cdef cppclass _2 "2":
          pass

     cdef cppclass _3 "3":
          pass
          
     cdef cppclass _4 "4":
          pass

     cdef cppclass _5 "5":
          pass
          
     cdef cppclass _6 "6":
          pass

     cdef cppclass _7 "7":
          pass
          
     cdef cppclass _8 "8":
          pass

     cdef cppclass _9 "9":
          pass
          
     cdef cppclass _10 "10":
          pass

     cdef cppclass _11 "11":
          pass
          
     cdef cppclass _12 "12":
          pass

     cdef cppclass _13 "13":
          pass
          
     cdef cppclass _14 "14":
          pass

     cdef cppclass _15 "15":
          pass
          
     cdef cppclass _16 "16":
          pass

     cdef cppclass _17 "17":
          pass
          
     cdef cppclass _18 "18":
          pass

     cdef cppclass _19 "19":
          pass
          
     cdef cppclass _20 "20":
          pass

     cdef cppclass _21 "21":
          pass
          
     cdef cppclass _22 "22":
          pass

     cdef cppclass _23 "23":
          pass
          
     cdef cppclass _24 "24":
          pass

     cdef cppclass _25 "25":
          pass
          
     cdef cppclass _26 "26":
          pass

     cdef cppclass _27 "27":
          pass
          
     cdef cppclass _28 "28":
          pass

     cdef cppclass _29 "29":
          pass
          
     cdef cppclass _30 "30":
          pass

     cdef cppclass _31 "31":
          pass
          
     cdef cppclass _32 "32":
          pass

     cdef cppclass PlainObjectBase:
          pass
          # void *data() nogil

          # int rows() nogil
          # int cols() nogil

     cdef cppclass MapSettings:
         MapSettings() except +
         MapSettings(void *, long rows, long cols) except +
         MapSettings(PlainObjectBase &&) except +
         void *data()
         long rows()
         long cols()

     cdef cppclass Map[DenseTypeShort](PlainObjectBase):
          # pass
     #     Map() except +
     #     Map(void *bla, long rows, long cols) except +
         Map(MapSettings &) except +

     cdef cppclass CopyMap[DenseTypeShort]:
         CopyMap(MapSettings &) except +

     cdef cppclass FlattenedMap[DenseType, dtype, Rows, Cols]:
         FlattenedMap() except +
         FlattenedMap(dtype *, long rows, long cols) except +
         FlattenedMap(MapSettings &) except +

     # cdef MapSettings Eigency(DenseBase &&)
     # cdef MapSettings to_eigency(DenseBase &&)
     cdef np.ndarray[np.double_t, ndim=2] to_numpy(PlainObjectBase &&)
     cdef np.ndarray[np.double_t, ndim=2] to_numpy_copy(PlainObjectBase &&)

# cdef extern from "conversions.h" namespace "CythonEigen":
#      cdef void test(DenseBase &&)

# cdef extern void test(DenseBase &&)

# cdef extern from "core_api.h":
#      pass

cdef class _MapSettings:
     cdef MapSettings *thisptr;

cdef extern from "eigency_cpp.h" namespace "Eigen":

     cdef cppclass Dynamic:
          pass
          
     cdef cppclass Matrix(PlainObjectBase):
          pass
          
     cdef cppclass Array(PlainObjectBase):
          pass
          
     cdef cppclass VectorXd(PlainObjectBase):
          pass
          
     cdef cppclass Vector1i(PlainObjectBase):
          pass

     cdef cppclass Vector2i(PlainObjectBase):
          pass

     cdef cppclass Vector3i(PlainObjectBase):
          pass

     cdef cppclass Vector4i(PlainObjectBase):
          pass

     cdef cppclass VectorXi(PlainObjectBase):
          pass

     cdef cppclass RowVector1i(PlainObjectBase):
          pass

     cdef cppclass RowVector2i(PlainObjectBase):
          pass

     cdef cppclass RowVector3i(PlainObjectBase):
          pass

     cdef cppclass RowVector4i(PlainObjectBase):
          pass

     cdef cppclass RowVectorXi(PlainObjectBase):
          pass

     cdef cppclass Matrix1i(PlainObjectBase):
          pass

     cdef cppclass Matrix2i(PlainObjectBase):
          pass

     cdef cppclass Matrix3i(PlainObjectBase):
          pass

     cdef cppclass Matrix4i(PlainObjectBase):
          pass

     cdef cppclass MatrixXi(PlainObjectBase):
          pass

     cdef cppclass Vector1f(PlainObjectBase):
          pass

     cdef cppclass Vector2f(PlainObjectBase):
          pass

     cdef cppclass Vector3f(PlainObjectBase):
          pass

     cdef cppclass Vector4f(PlainObjectBase):
          pass

     cdef cppclass VectorXf(PlainObjectBase):
          pass

     cdef cppclass RowVector1f(PlainObjectBase):
          pass

     cdef cppclass RowVector2f(PlainObjectBase):
          pass

     cdef cppclass RowVector3f(PlainObjectBase):
          pass

     cdef cppclass RowVector4f(PlainObjectBase):
          pass

     cdef cppclass RowVectorXf(PlainObjectBase):
          pass

     cdef cppclass Matrix1f(PlainObjectBase):
          pass

     cdef cppclass Matrix2f(PlainObjectBase):
          pass

     cdef cppclass Matrix3f(PlainObjectBase):
          pass

     cdef cppclass Matrix4f(PlainObjectBase):
          pass

     cdef cppclass MatrixXf(PlainObjectBase):
          pass

     cdef cppclass Vector1d(PlainObjectBase):
          pass

     cdef cppclass Vector2d(PlainObjectBase):
          pass

     cdef cppclass Vector3d(PlainObjectBase):
          pass

     cdef cppclass Vector4d(PlainObjectBase):
          pass

     cdef cppclass VectorXd(PlainObjectBase):
          pass

     cdef cppclass RowVector1d(PlainObjectBase):
          pass

     cdef cppclass RowVector2d(PlainObjectBase):
          pass

     cdef cppclass RowVector3d(PlainObjectBase):
          pass

     cdef cppclass RowVector4d(PlainObjectBase):
          pass

     cdef cppclass RowVectorXd(PlainObjectBase):
          pass

     cdef cppclass Matrix1d(PlainObjectBase):
          pass

     cdef cppclass Matrix2d(PlainObjectBase):
          pass

     cdef cppclass Matrix3d(PlainObjectBase):
          pass

     cdef cppclass Matrix4d(PlainObjectBase):
          pass

     cdef cppclass MatrixXd(PlainObjectBase):
          pass

     cdef cppclass Vector1cf(PlainObjectBase):
          pass

     cdef cppclass Vector2cf(PlainObjectBase):
          pass

     cdef cppclass Vector3cf(PlainObjectBase):
          pass

     cdef cppclass Vector4cf(PlainObjectBase):
          pass

     cdef cppclass VectorXcf(PlainObjectBase):
          pass

     cdef cppclass RowVector1cf(PlainObjectBase):
          pass

     cdef cppclass RowVector2cf(PlainObjectBase):
          pass

     cdef cppclass RowVector3cf(PlainObjectBase):
          pass

     cdef cppclass RowVector4cf(PlainObjectBase):
          pass

     cdef cppclass RowVectorXcf(PlainObjectBase):
          pass

     cdef cppclass Matrix1cf(PlainObjectBase):
          pass

     cdef cppclass Matrix2cf(PlainObjectBase):
          pass

     cdef cppclass Matrix3cf(PlainObjectBase):
          pass

     cdef cppclass Matrix4cf(PlainObjectBase):
          pass

     cdef cppclass MatrixXcf(PlainObjectBase):
          pass

     cdef cppclass Vector1cd(PlainObjectBase):
          pass

     cdef cppclass Vector2cd(PlainObjectBase):
          pass

     cdef cppclass Vector3cd(PlainObjectBase):
          pass

     cdef cppclass Vector4cd(PlainObjectBase):
          pass

     cdef cppclass VectorXcd(PlainObjectBase):
          pass

     cdef cppclass RowVector1cd(PlainObjectBase):
          pass

     cdef cppclass RowVector2cd(PlainObjectBase):
          pass

     cdef cppclass RowVector3cd(PlainObjectBase):
          pass

     cdef cppclass RowVector4cd(PlainObjectBase):
          pass

     cdef cppclass RowVectorXcd(PlainObjectBase):
          pass

     cdef cppclass Matrix1cd(PlainObjectBase):
          pass

     cdef cppclass Matrix2cd(PlainObjectBase):
          pass

     cdef cppclass Matrix3cd(PlainObjectBase):
          pass

     cdef cppclass Matrix4cd(PlainObjectBase):
          pass

     cdef cppclass MatrixXcd(PlainObjectBase):
          pass


# cdef MapSettings from_numpy_1d(double[:] array_data_mview)
# cdef MapSettings from_numpy_2d(double[:,:] array_data_mview)

cdef MapSettings from_numpy(np.ndarray array)

# cdef MapSettings from_numpy(np.ndarray[np.double_t, ndim=2] array)

