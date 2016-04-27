#include <Eigen/Dense>

#include <iostream>
#include "conversions_api.h"

#ifndef EIGENCY_CPP
#define EIGENCY_CPP

namespace eigency {

template<typename Scalar>
PyArrayObject *_ndarray_view(Scalar *, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride);
template<typename Scalar>
PyArrayObject *_ndarray_copy(const Scalar *, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride);

template<>
PyArrayObject *_ndarray_view<double>(double *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_double_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_double_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<double>(const double *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_double_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_double_F(data, rows, cols, outer_stride, inner_stride);
}

template<>
PyArrayObject *_ndarray_view<float>(float *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_float_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_float_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<float>(const float *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_float_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_float_F(data, rows, cols, outer_stride, inner_stride);
}

template<>
PyArrayObject *_ndarray_view<long>(long *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_long_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_long_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<long>(const long *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_long_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_long_F(data, rows, cols, outer_stride, inner_stride);
}

template<>
PyArrayObject *_ndarray_view<int>(int *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_int_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_int_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<int>(const int *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_int_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_int_F(data, rows, cols, outer_stride, inner_stride);
}

template<>
PyArrayObject *_ndarray_view<short>(short *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_short_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_short_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<short>(const short *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_short_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_short_F(data, rows, cols, outer_stride, inner_stride);
}

template<>
PyArrayObject *_ndarray_view<char>(char *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_char_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_char_F(data, rows, cols, outer_stride, inner_stride);
}
template<>
PyArrayObject *_ndarray_copy<char>(const char *data, long rows, long cols, bool is_row_major, long outer_stride, long inner_stride) {
    if (is_row_major)
        return ndarray_copy_char_C(data, rows, cols, outer_stride, inner_stride);
    else
        return ndarray_copy_char_F(data, rows, cols, outer_stride, inner_stride);
}

template <typename Derived>
inline PyArrayObject *ndarray(Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _ndarray_view(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.cols(), m.rows());
}
template <typename Derived>
inline PyArrayObject *ndarray(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _ndarray_copy(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.cols(), m.rows());
}
template <typename Derived>
inline PyArrayObject *ndarray_view(Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _ndarray_view(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.cols(), m.rows());
}
template <typename Derived>
inline PyArrayObject *ndarray_view(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _ndarray_view(const_cast<typename Derived::Scalar*>(m.data()), m.rows(), m.cols(), m.IsRowMajor, m.cols(), m.rows());
}
template <typename Derived>
inline PyArrayObject *ndarray_copy(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _ndarray_copy(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.cols(), m.rows());
}

template <typename Derived, int MapOptions, typename Stride>
inline PyArrayObject *ndarray(Eigen::Map<Derived, MapOptions, Stride> &m) {
    import_eigency__conversions();
    return _ndarray_view(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.outerStride(), m.innerStride());
}
template <typename Derived, int MapOptions, typename Stride>
inline PyArrayObject *ndarray(const Eigen::Map<Derived, MapOptions, Stride> &m) {
    import_eigency__conversions();
    // Since this is a map, we assume that ownership is correctly taken care
    // of, and we avoid taking a copy
    return _ndarray_view(const_cast<typename Derived::Scalar*>(m.data()), m.rows(), m.cols(), m.IsRowMajor, m.outerStride(), m.innerStride());
}
template <typename Derived, int MapOptions, typename Stride>
inline PyArrayObject *ndarray_view(Eigen::Map<Derived, MapOptions, Stride> &m) {
    import_eigency__conversions();
    return _ndarray_view(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.outerStride(), m.innerStride());
}
template <typename Derived, int MapOptions, typename Stride>
inline PyArrayObject *ndarray_view(const Eigen::Map<Derived, MapOptions, Stride> &m) {
    import_eigency__conversions();
    return _ndarray_view(const_cast<typename Derived::Scalar*>(m.data()), m.rows(), m.cols(), m.IsRowMajor, m.outerStride(), m.innerStride());
}
template <typename Derived, int MapOptions, typename Stride>
inline PyArrayObject *ndarray_copy(const Eigen::Map<Derived, MapOptions, Stride> &m) {
    import_eigency__conversions();
    return _ndarray_copy(m.data(), m.rows(), m.cols(), m.IsRowMajor, m.outerStride(), m.innerStride());
}




template <template<class,int,int,int,int,int> class DenseBase,
          typename Scalar,
          int _Rows, int _Cols,
          int _Options = Eigen::AutoAlign |
#if defined(__GNUC__) && __GNUC__==3 && __GNUC_MINOR__==4
    // workaround a bug in at least gcc 3.4.6
    // the innermost ?: ternary operator is misparsed. We write it slightly
    // differently and this makes gcc 3.4.6 happy, but it's ugly.
    // The error would only show up with EIGEN_DEFAULT_TO_ROW_MAJOR is defined
    // (when EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION is RowMajor)
                          ( (_Rows==1 && _Cols!=1) ? Eigen::RowMajor
                          : !(_Cols==1 && _Rows!=1) ?  EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION
                          : ColMajor ),
#else
                          ( (_Rows==1 && _Cols!=1) ? Eigen::RowMajor
                          : (_Cols==1 && _Rows!=1) ? Eigen::ColMajor
                          : Eigen::EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION ),
#endif
          int _MapOptions = Eigen::Unaligned,
          int _StrideOuter=0, int _StrideInner=0,
          int _MaxRows = _Rows,
          int _MaxCols = _Cols>
class FlattenedMap: public Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>, _MapOptions, Eigen::Stride<_StrideOuter, _StrideInner> >  {
public:
    typedef Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>, _MapOptions, Eigen::Stride<_StrideOuter, _StrideInner> > Base;

    FlattenedMap()
        : Base(nullptr, 0, 0) {}
    
    FlattenedMap(Scalar *data, long rows, long cols, long outer_stride=0, long inner_stride=0)
        : Base(data, rows, cols,
               Eigen::Stride<_StrideOuter, _StrideInner>(outer_stride, inner_stride)) {
    }

    FlattenedMap(PyArrayObject *object)
        : Base((Scalar *)((PyArrayObject*)object)->data,        
        // : Base(_from_numpy<Scalar>((PyArrayObject*)object),
               (((PyArrayObject*)object)->nd == 2) ? ((PyArrayObject*)object)->dimensions[0] : 1,
               (((PyArrayObject*)object)->nd == 2) ? ((PyArrayObject*)object)->dimensions[1] : ((PyArrayObject*)object)->dimensions[0],
               Eigen::Stride<_StrideOuter, _StrideInner>(_StrideOuter != Eigen::Dynamic ? _StrideOuter : (((PyArrayObject*)object)->nd == 2) ? ((PyArrayObject*)object)->dimensions[0] : 1,
                                                         _StrideInner != Eigen::Dynamic ? _StrideInner : (((PyArrayObject*)object)->nd == 2) ? ((PyArrayObject*)object)->dimensions[1] : ((PyArrayObject*)object)->dimensions[0])) {

        if (!PyArray_ISONESEGMENT(object))
            throw std::invalid_argument("Numpy array must be a in one contiguous segment to be able to be transferred to a Eigen Map.");
    }
    FlattenedMap &operator=(const FlattenedMap &other) {
        // Replace the memory that we point to (not a memory allocation)
        new (this) FlattenedMap(const_cast<Scalar*>(other.data()),
                                other.rows(),
                                other.cols(),
                                other.outerStride(),
                                other.innerStride());
        return *this;
    }
    
    operator Base() const {
        return static_cast<Base>(*this);
    }

    operator Base&() const {
        return static_cast<Base&>(*this);
    }

    operator DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>() const {
        return DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>(static_cast<Base>(*this));
    }
};


template <typename MatrixType>
class Map: public Eigen::Map<MatrixType> {
public:
    typedef Eigen::Map<MatrixType> Base;
    typedef typename Base::Scalar Scalar;

    Map()
        : Base(nullptr, 0, 0) {
    }
    
    Map(Scalar *data, long rows, long cols)
        : Base(data,
               ((Base::RowsAtCompileTime!=Eigen::Dynamic && Base::RowsAtCompileTime==cols) &&
                (Base::ColsAtCompileTime!=Eigen::Dynamic && Base::ColsAtCompileTime==rows))?cols:rows,
               ((Base::RowsAtCompileTime!=Eigen::Dynamic && Base::RowsAtCompileTime==cols) &&
                (Base::ColsAtCompileTime!=Eigen::Dynamic && Base::ColsAtCompileTime==rows))?rows:cols) {
    }

    Map(PyArrayObject *object)
        : Base((Scalar *)object->data,
               // ROW: If 1D numpy array, set to 1 (column vector)
               (object->nd == 1) ? 1
               // ROW: otherwise, if array is in row-major order, transpose (see README)
               : (PyArray_IS_C_CONTIGUOUS(object) ? object->dimensions[1] : object->dimensions[0]),
               // COLUMN: If 1D numpy array, set to length (column vector)
               (object->nd == 1) ? object->dimensions[0]
               // COLUMN: otherwise, if array is in row-major order: transpose (see README)
               : (PyArray_IS_C_CONTIGUOUS(object) ? object->dimensions[0] : object->dimensions[1])) {
        if (!PyArray_ISONESEGMENT(object))
            throw std::invalid_argument("Numpy array must be a in one contiguous segment to be able to be transferred to a Eigen Map.");        
    }
    
    Map &operator=(const Map &other) {
        // Replace the memory that we point to (not a memory allocation)
        new (this) Map(const_cast<Scalar*>(other.data()),
                       other.rows(),
                       other.cols());
        return *this;
    }
    
    operator Base() const {
        return static_cast<Base>(*this);
    }

    operator Base&() const {
        return static_cast<Base&>(*this);
    }

    operator MatrixType() const {
        return MatrixType(static_cast<Base>(*this));
    }    
};


}

#endif



