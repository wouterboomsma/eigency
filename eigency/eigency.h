#ifndef EIGENCY_TYPEDEFS
#define EIGENCY_TYPEDEFS

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
EIGENCY_MAKE_TYPEDEFS(Type, TypeSuffix, ::Eigen::Dynamic, X)

EIGENCY_MAKE_TYPEDEFS_ALL_SIZES(long double,                 ld)
EIGENCY_MAKE_TYPEDEFS_ALL_SIZES(::std::complex<long double>, cld)

#undef EIGENCY_MAKE_TYPEDEFS_ALL_SIZES
#undef EIGENCY_MAKE_TYPEDEFS

//
// Array
//

#define EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix)             \
typedef ::Eigen::Array<Type, Size, Size> Array##SizeSuffix##SizeSuffix##TypeSuffix; \
typedef ::Eigen::Array<Type, Size, 1>    Array##SizeSuffix##TypeSuffix;

#define EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, Size)                   \
typedef ::Eigen::Array<Type, Size, ::Eigen::Dynamic> Array##Size##X##TypeSuffix;    \
typedef ::Eigen::Array<Type, ::Eigen::Dynamic, Size> Array##X##Size##TypeSuffix;

#define EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(Type, TypeSuffix)     \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 2, 2)                 \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 3, 3)                 \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, 4, 4)                 \
EIGENCY_MAKE_ARRAY_TYPEDEFS(Type, TypeSuffix, ::Eigen::Dynamic, X)  \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 2)              \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 3)              \
EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS(Type, TypeSuffix, 4)

EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(long double,                 ld)
EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES(::std::complex<long double>, cld)

#undef EIGENCY_MAKE_ARRAY_TYPEDEFS_ALL_SIZES
#undef EIGENCY_MAKE_ARRAY_FIXED_TYPEDEFS
#undef EIGENCY_MAKE_ARRAY_TYPEDEFS

}

#endif
