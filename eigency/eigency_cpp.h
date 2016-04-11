#include <Eigen/Dense>

#include <iostream>
#include "conversions_api.h"

#ifndef EIGENCY_CPP
#define EIGENCY_CPP

namespace eigency {

template<typename Scalar>
PyArrayObject *_to_numpy_view(Scalar *, long rows, long cols);
template<typename Scalar>
PyArrayObject *_to_numpy_copy(const Scalar *, long rows, long cols);

template<>
PyArrayObject *_to_numpy_view<double>(double *data, long rows, long cols) {
    return to_numpy_double(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<double>(const double *data, long rows, long cols) {
    return to_numpy_copy_double(data, rows, cols);
}

template<>
PyArrayObject *_to_numpy_view<float>(float *data, long rows, long cols) {
    return to_numpy_float(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<float>(const float *data, long rows, long cols) {
    return to_numpy_copy_float(data, rows, cols);
}

template<>
PyArrayObject *_to_numpy_view<long>(long *data, long rows, long cols) {
    return to_numpy_long(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<long>(const long *data, long rows, long cols) {
    return to_numpy_copy_long(data, rows, cols);
}

template<>
PyArrayObject *_to_numpy_view<int>(int *data, long rows, long cols) {
    return to_numpy_int(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<int>(const int *data, long rows, long cols) {
    return to_numpy_copy_int(data, rows, cols);
}

template<>
PyArrayObject *_to_numpy_view<short>(short *data, long rows, long cols) {
    return to_numpy_short(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<short>(const short *data, long rows, long cols) {
    return to_numpy_copy_short(data, rows, cols);
}

template<>
PyArrayObject *_to_numpy_view<char>(char *data, long rows, long cols) {
    return to_numpy_char(data, rows, cols);
}
template<>
PyArrayObject *_to_numpy_copy<char>(const char *data, long rows, long cols) {
    return to_numpy_copy_char(data, rows, cols);
}

template <typename Derived>
inline PyArrayObject *to_numpy(Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _to_numpy_view(m.data(), m.rows(), m.cols());
}
template <typename Derived>
inline PyArrayObject *to_numpy(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _to_numpy_copy(m.data(), m.rows(), m.cols());
}
template <typename Derived>
inline PyArrayObject *to_numpy_view(Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _to_numpy_view(m.data(), m.rows(), m.cols());
}
template <typename Derived>
inline PyArrayObject *to_numpy_view(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _to_numpy_view(const_cast<typename Derived::Scalar*>(m.data()), m.rows(), m.cols());
}
template <typename Derived>
inline PyArrayObject *to_numpy_copy(const Eigen::PlainObjectBase<Derived> &m) {
    import_eigency__conversions();
    return _to_numpy_copy(m.data(), m.rows(), m.cols());
}



struct MapSettings {
public:
    MapSettings():
        _data(nullptr),
        _rows(0),
        _cols(0) {}
    
    MapSettings(void *data, long rows, long cols):
        _data(data), _rows(rows), _cols(cols) {}

    // template <typename Derived>
    // MapSettings(Eigen::PlainObjectBase<Derived> &&m):
    //     _data(m.data), _rows(m.rows), _cols(m.cols) {}

    void *data() const {
        return _data;
    }

    long rows() const {
        return _rows;
    }

    long cols() const {
        return _cols;
    }
private:
    void *_data;
    long _rows;
    long _cols;
};

template <template<class,int,int,int,int,int> class DenseBase,
          typename Scalar, int _Rows, int _Cols,
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
         int _MaxRows = _Rows,
         int _MaxCols = _Cols>
class FlattenedMap: public Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >  {
public:
    typedef Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> > Base;

    FlattenedMap()
        : Base(nullptr, 0, 0) {}
    
    FlattenedMap(Scalar *data, long rows, long cols)
        : Base(data, rows, cols) {
    }

    FlattenedMap(const MapSettings &settings)
        : Base((Scalar *)settings.data(), settings.rows(), settings.cols()) {
    }

    FlattenedMap &operator=(const FlattenedMap &other) {
        // Replace the memory that we point to (not a memory allocation)
        new (this) FlattenedMap(const_cast<Scalar*>(other.data()),
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

    operator DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>() const {
        return DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>(static_cast<Base>(*this));
    }
};

// template <template<class,int,int,int,int,int> class DenseBase,
//           typename Scalar, int _Rows, int _Cols,
//           int _Options = Eigen::AutoAlign |
// #if defined(__GNUC__) && __GNUC__==3 && __GNUC_MINOR__==4
//     // workaround a bug in at least gcc 3.4.6
//     // the innermost ?: ternary operator is misparsed. We write it slightly
//     // differently and this makes gcc 3.4.6 happy, but it's ugly.
//     // The error would only show up with EIGEN_DEFAULT_TO_ROW_MAJOR is defined
//     // (when EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION is RowMajor)
//                           ( (_Rows==1 && _Cols!=1) ? Eigen::RowMajor
//                           : !(_Cols==1 && _Rows!=1) ?  EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION
//                           : ColMajor ),
// #else
//                           ( (_Rows==1 && _Cols!=1) ? Eigen::RowMajor
//                           : (_Cols==1 && _Rows!=1) ? Eigen::ColMajor
//                           : Eigen::EIGEN_DEFAULT_MATRIX_STORAGE_ORDER_OPTION ),
// #endif
//          int _MaxRows = _Rows,
//          int _MaxCols = _Cols>
// class FlattenedCopyMap: public Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >  {
// public:
//     typedef Eigen::Map<DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> > Base;

//     FlattenedCopyMap()
//         : Base(nullptr, 0, 0) {}
    
//     FlattenedCopyMap(Scalar *data, long rows, long cols)
//         : Base(data, rows, cols) {
//     }

//     FlattenedCopyMap(const MapSettings &settings)
//         : Base((Scalar *)settings.data(), settings.rows(), settings.cols()) {
//     }

//     FlattenedCopyMap &operator=(const FlattenedCopyMap &other) {
//         // Replace the memory that we point to (not a memory allocation)
//         new (this) FlattenedCopyMap(const_cast<Scalar*>(other.data()),
//                                     other.rows(),
//                                     other.cols());
//         return *this;
//     }

//     operator DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>() const {
//         return DenseBase<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>(static_cast<Base>(*this));
//     }
    
// };


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
               ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==cols) &&
                (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==rows))?cols:rows,
               ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==cols) &&
                (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==rows))?rows:cols) {
    }

    Map(const MapSettings &settings)
        : Base((Scalar *)settings.data(),
               ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==settings.cols()) &&
                (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==settings.rows()))?settings.cols():settings.rows(),
               ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==settings.cols()) &&
                (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==settings.rows()))?settings.rows():settings.cols()) {
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

// template <typename MatrixType>
// class CopyMap: public Eigen::Map<MatrixType> {
// public:
//     typedef Eigen::Map<MatrixType> Base;
//     typedef typename Base::Scalar Scalar;

//     CopyMap()
//         : Base(nullptr, 0, 0) {
//     }
    
//     CopyMap(Scalar *data, long rows, long cols)
//         : Base(data,
//                ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==cols) &&
//                 (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==rows))?cols:rows,
//                ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==cols) &&
//                 (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==rows))?rows:cols) {
//     }

//     CopyMap(const MapSettings &settings)
//         : Base((Scalar *)settings.data(),
//                ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==settings.cols()) &&
//                 (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==settings.rows()))?settings.cols():settings.rows(),
//                ((Base::RowsAtCompileTime==Eigen::Dynamic || Base::RowsAtCompileTime==settings.cols()) &&
//                 (Base::ColsAtCompileTime==Eigen::Dynamic || Base::ColsAtCompileTime==settings.rows()))?settings.rows():settings.cols()) {
//     }

//     CopyMap &operator=(const CopyMap &other) {
//         // Replace the memory that we point to (not a memory allocation)
//         new (this) CopyMap(const_cast<Scalar*>(other.data()),
//                        other.rows(),
//                        other.cols());
//         return *this;
//     }
    
//     operator MatrixType() const {
//         return MatrixType(static_cast<Base>(*this));
//     }

// };

}

#endif



