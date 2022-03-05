#ifndef EIGENCY_CPP
#define EIGENCY_CPP

#include <Eigen/Dense>

namespace eigency {

//
// Matrix
//

#define EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)           \
typedef ::Eigen::Matrix<Type, Size, Size> Matrix##SizeSuffix##TypeSuffix;   \
typedef ::Eigen::Matrix<Type, Size, 1>    Vector##SizeSuffix##TypeSuffix;   \
typedef ::Eigen::Matrix<Type, 1, Size>    RowVector##SizeSuffix##TypeSuffix;

#define EIGENCY_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix)   \
EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2)               \
EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3)               \
EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4)               \
EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, Dynamic, X)

EIGENCY_MAKE_TYPEDEFS_ALL_SIZES(long double,               ld)
EIGENCY_MAKE_TYPEDEFS_ALL_SIZES(std::complex<long double>, cld)

#undef EIGENCY_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGENCY_MAKE_TYPEDEFS

//
// Array
//

#define EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)     \
typedef Array<Type, Size, Size> Array##SizeSuffix##SizeSuffix##TypeSuffix;  \
typedef Array<Type, Size, 1>    Array##SizeSuffix##TypeSuffix;

#define EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, Size)   \
typedef Array<Type, Size, Dynamic> Array##Size##X##TypeSuffix;      \
typedef Array<Type, Dynamic, Size> Array##X##Size##TypeSuffix;

#define EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 2, 2)             \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 3, 3)             \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 4, 4)             \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, Dynamic, X)       \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 2)          \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 3)          \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 4)

EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(long double,               ld)
EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(std::complex<long double>, cld)

#undef EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES
#undef EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS
#undef EIGENCY_MAKE_ARRAY_TYPEDEFS

}

#endif
