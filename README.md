# Eigency
Eigency is a Cython interface between Numpy arrays and Matrix/Array
objects from the Eigen C++ library. It is intended to simplify the
process of writing C++ extensions using the Eigen library. Eigency is
designed to reuse the underlying storage of the arrays when passing
data back and forth, and will thus avoid making unnecessary copies
whenever possible. Only in cases where copies are explicitly requested
by your C++ code will they be made (see example below)

Below is a description of a range of common usage scenarios. A full working
example of both setup and these different use cases is available in the
`test` directory distributed with the this package.

## Setup
To import eigency functionality, add the following to your `.pyx` file:
```
from eigency.core cimport *
```
In addition, in the `setup.py` file, the include directories must be
set up to include the eigency includes. This can be done by calling
the `get_includes` function in the `eigency` module:
```
import eigency
...
extensions = [
    Extension("module-dir-name/module-name", ["module-dir-name/module-name.pyx"],
              include_dirs = [".", "module-dir-name"] + eigency.get_includes()
              ),
]
```
Eigency includes a version of the Eigen library, and the `get_includes` function will include the path to this directory. If you
have your own version of Eigen, just set the `include_eigen` option to False, and add your own path instead:

```
    include_dirs = [".", "module-dir-name", 'path-to-own-eigen'] + eigency.get_includes(include_eigen=False)
```

## From Numpy to Eigen
Assume we are writing a Cython interface to the following C++ function:

```c++
void function_w_mat_arg(const Eigen::Map<Eigen::MatrixXd> &mat) {
     ...
}
```

Note that we use `Eigen::Map` to ensure that we can reuse the storage
of the numpy array, thus avoiding making a copy. Assuming the C++ code
is in a file called `functions.h`, the corresponding `.pyx` entry could look like this:

```
cdef extern from "functions.h":
     cdef void _function_w_mat_arg "function_w_mat_arg"(Map[MatrixXd] &)

# This will be exposed to Python
def function_w_mat_arg(np.ndarray array):
    return _function_w_mat_arg(Map[MatrixXd](array))
```

The last line contains the actual conversion. `Map` is an Eigency
type that derives from the real Eigen map, and will take care of
the conversion from the numpy array to the corresponding Eigen type.


## Writing Eigen Map types in Cython

Since Cython does not support nested fused types, you cannot write types like `Map[Matrix[double, 2, 2]]`. In most cases, you won't need to, since you can just use Eigens convenience typedefs, such as `Map[VectorXd]`. If you need the additional flexibility of the full specification, you can use the `FlattenedMap` type, where all type arguments can be specified at top level, for instance `FlattenedMap[Matrix, double, _2, _3]` or `FlattenedMap[Matrix, double, _2, Dynamic]`. Note that dimensions must be prefixed with an underscore.

Using full specifications of the Eigen types, the previous example would look like this:
```
cdef extern from "functions.h":
     cdef void _function_w_mat_arg "function_w_mat_arg" (FlattenedMap[Matrix, double, Dynamic, Dynamic] &)

# This will be exposed to Python
def function_w_mat_arg(np.ndarray array):
    return _function_w_mat_arg(FlattenedMap[Matrix, double, Dynamic, Dynamic](array))
```

`FlattenedType` takes four template parameters: arraytype, scalartype,
rows and cols.  Eigen supports a few other template arguments for
setting the storage layout and Map strides. Since cython does not
support default template arguments for fused types, we have instead
defined separate types for this purpose. These are called
`FlattenedMapWithOrder` and `FlattenedMapWithStride` with five and eight
template arguments, respectively. For details on their use, see the section
about storage layout below.

## From Numpy to Eigen (insisting on a copy)

Eigency will not complain if the C++ function you interface with does
not take a Eigen Map object, but instead a regular Eigen Matrix or
Array. However, in such cases, a copy will be made. Actually, the
procedure is exactly the same as above. In the `.pyx` file, you still
define everything exactly the same way as for the Map case described above.

For instance, given the following C++ function:
```c++
void function_w_vec_arg_no_map(const Eigen::VectorXd &vec);
```

The Cython definitions would still look like this:

```
cdef extern from "functions.h":
     cdef void _function_w_vec_arg_no_map "function_w_vec_arg_no_map"(Map[VectorXd] &)

# This will be exposed to Python
def function_w_vec_arg_no_map(np.ndarray array):
    return _function_w_vec_arg_no_map(Map[VectorXd](array))
```

Cython will not mind the fact that the argument type in the extern
declaration (a Map type) differs from the actual one in the `.h` file,
as long as one can be assigned to the other. Since Map objects can be
assigned to their corresponding Matrix/Array types this works
seemlessly. But keep in mind that this assignment will make a copy of
the underlying data.

## Eigen to Numpy

C++ functions returning a reference to an Eigen Matrix/Array can also
be transferred to numpy arrays without copying their content.  Assume
we have a class with a single getter function that returns an Eigen
matrix member:

```c++
class MyClass {
public:
    MyClass():
        matrix(Eigen::Matrix3d::Constant(3.)) {
    }
    Eigen::MatrixXd &get_matrix() {
        return this->matrix;
    }
private:
    Eigen::Matrix3d matrix;
};
```

The Cython C++ class inteface is specified as usual:

```
     cdef cppclass _MyClass "MyClass":
         _MyClass "MyClass"() except +
         Matrix3d &get_matrix()
```

And the corresponding Python wrapper:

```python
cdef class MyClass:
    cdef _MyClass *thisptr;

    def __cinit__(self):
        self.thisptr = new _MyClass()

    def __dealloc__(self):
        del self.thisptr

    def get_matrix(self):
        return ndarray(self.thisptr.get_matrix())
```

This last line contains the actual conversion. Again, eigency has its
own version of `ndarray`, that will take care of the conversion for
you.

Due to limitations in Cython, Eigency cannot deal with full
Matrix/Array template specifications as return types
(e.g. `Matrix[double, 4, 2]`). However, as a workaround, you can use
`PlainObjectBase` as a return type in such cases (or in all cases if
you prefer):

```
         PlainObjectBase &get_matrix()
```

## Overriding default behavior

The `ndarray` conversion type specifier will attempt do guess whether you want a copy
or a view, depending on the return type. Most of the time, this is
probably what you want. However, there might be cases where you want
to override this behavior. For instance, functions returning const
references will result in a copy of the array, since the const-ness
cannot be enforced in Python. However, you can always override the
default behavior by using the `ndarray_copy` or `ndarray_view`
functions.

Expanding the `MyClass` example from before:

```c++
class MyClass {
public:
    ...
    const Eigen::MatrixXd &get_const_matrix() {
        return this->matrix;
    }
    ...
};
```

With the corresponding cython interface specification
The Cython C++ class inteface is specified as usual:

```
     cdef cppclass _MyClass "MyClass":
         ...
         const Matrix3d &get_const_matrix()
```

The following would return a copy

```python
cdef class MyClass:
    ...
    def get_const_matrix(self):
        return ndarray(self.thisptr.get_const_matrix())
```

while the following would force it to return a view

```python
cdef class MyClass:
    ...
    def get_const_matrix(self):
        return ndarray_view(self.thisptr.get_const_matrix())
```

## Eigen to Numpy (non-reference return values)

Functions returning an Eigen object (not a reference), are specified
in a similar way. For instance, given the following C++ function:

```c++
Eigen::Matrix3d function_w_mat_retval();
```

The Cython code could be written as:

```
cdef extern from "functions.h":
     cdef Matrix3d _function_w_mat_retval "function_w_mat_retval" ()

# This will be exposed to Python
def function_w_mat_retval():
    return ndarray_copy(_function_w_mat_retval())
```

As mentioned above, you can replace `Matrix3d` (or any other Eigen return type) with
`PlainObjectBase`, which is especially relevant when working with
Eigen object that do not have an associated convenience typedef.

Note that we use `ndarray_copy` instead of `ndarray` to explicitly
state that a copy should be made. In c++11 compliant compilers, it
will detect the rvalue reference and automatically make a copy even if
you just use `ndarray` (see next section), but to ensure that it works
also with older compilers it is recommended to always use
`ndarray_copy` when returning newly constructed eigen values.


## Corrupt data when returning non-map types
The tendency of Eigency to avoid copies whenever possible can lead
to corrupted data when returning non-map Eigen arrays. For instance,
in the `function_w_mat_retval` from the previous section, a temporary
value will be returned from C++, and we have to take care to make
a copy of this data instead of letting the resulting numpy array
refer directly to this memory. In C++11, this situation can be
detected directly using rvalue references, and it will therefore
automatically make a copy: 
```
def function_w_mat_retval():
    # This works in C++11, because it detects the rvalue reference
    return ndarray(_function_w_mat_retval()) 
```

However, to make sure it works with older compilers,
it is recommended to use the `ndarray_copy` conversion:

```
def function_w_mat_retval():
    # Explicit request for copy - this always works
    return ndarray_copy(_function_w_mat_retval()) 
```



## Storage layout - why arrays are sometimes transposed

The default storage layout used in numpy and Eigen differ. Numpy uses
a row-major layout (C-style) per default while Eigen uses a
column-major layout (Fortran style) by default.  In Eigency, we prioritize to
avoid copying of data whenever possible, which can have unexpected
consequences in some cases: There is no problem when passing values
from C++ to Python - we just adjust the storage layout of the returned
numpy array to match that of Eigen. However, since the storage layout
is encoded into the _type_ of the Eigen array (or the type of the
Map), we cannot automatically change the layout in the Python to C++ direction. In
Eigency, we have therefore opted to return the transposed array/matrix
in such cases. This provides the user with the flexibility to deal
with the problem either in Python (use order="F" when constructing
your numpy array), or on the C++ side: (1) explicitly define your
argument to have the row-major storage layout, 2) manually set the Map
stride, or 3) just call `.transpose()` on the received
array/matrix). 

As an example, consider the case of a C++ function that both receives
and returns a Eigen Map type, thus acting as a filter:

```c++
Eigen::Map<Eigen::ArrayXXd> function_filter(Eigen::Map<Eigen::ArrayXXd> &mat) {
    return mat;
}
```

The Cython code could be:

```
cdef extern from "functions.h":
    ...
    cdef Map[ArrayXXd] &_function_filter1 "function_filter1" (Map[ArrayXXd] &)

def function_filter1(np.ndarray array):
    return ndarray(_function_filter1(Map[ArrayXXd](array)))

```

If we call this function from Python in the standard way, we will
see that the array is transposed on the way from Python to C++, and
remains that way when it is again returned to Python:

```python
>>> x = np.array([[1., 2., 3., 4.], [5., 6., 7., 8.]])
>>> y = function_filter1(x)
>>> print x
[[ 1.  2.  3.  4.]
 [ 5.  6.  7.  8.]]
>>> print y
[[ 1.  5.]
 [ 2.  6.]
 [ 3.  7.]
 [ 4.  8.]]
```

The simplest way to avoid this is to tell numpy to use a
column-major array layout instead of the default row-major
layout. This can be done using the order='F' option:

```python
>>> x = np.array([[1., 2., 3., 4.], [5., 6., 7., 8.]], order='F')
>>> y = function_filter1(x)
>>> print x
[[ 1.  2.  3.  4.]
 [ 5.  6.  7.  8.]]
>>> print y
[[ 1.  2.  3.  4.]
 [ 5.  6.  7.  8.]]
```

The other alternative is to tell Eigen to use RowMajor layout. This
requires changing the C++ function definition:

```c++
typedef Eigen::Map<Eigen::Array<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > RowMajorArrayMap;

RowMajorArrayMap &function_filter2(RowMajorArrayMap &mat) {
    return mat;
}
```

To write the corresponding Cython definition, we need the expanded version of
`FlattenedMap` called `FlattenedMapWithOrder`, which allows us to specify
the storage order:

```
cdef extern from "functions.h":
    ...
    cdef PlainObjectBase _function_filter2 "function_filter2" (FlattenedMapWithOrder[Array, double, Dynamic, Dynamic, RowMajor])

def function_filter2(np.ndarray array):
    return ndarray(_function_filter2(FlattenedMapWithOrder[Array, double, Dynamic, Dynamic, RowMajor](array)))
```

Another alternative is to keep the array itself in RowMajor format,
but use different stride values for the Map type:

```c++
typedef Eigen::Map<Eigen::ArrayXXd, Eigen::Unaligned, Eigen::Stride<1, Eigen::Dynamic> > CustomStrideMap;

CustomStrideMap &function_filter3(CustomStrideMap &);
```

In this case, in Cython, we need to use the even more extended
`FlattenedMap` type called `FlattenedMapWithStride`, taking eight
arguments:

```
cdef extern from "functions.h":
    ...
    cdef PlainObjectBase _function_filter3 "function_filter3" (FlattenedMapWithStride[Array, double, Dynamic, Dynamic, ColMajor, Unaligned, _1, Dynamic])

def function_filter3(np.ndarray array):
    return ndarray(_function_filter3(FlattenedMapWithStride[Array, double, Dynamic, Dynamic, ColMajor, Unaligned, _1, Dynamic](array)))
```

In all three cases, the returned array will now be of the same shape
as the original.


