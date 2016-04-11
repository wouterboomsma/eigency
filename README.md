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
In addition, in the `setup.py`, the include directories must be set up
to include the eigency includes. This can be done by calling the `get_includes`
function in the `eigency` module:
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
    return _function_w_mat_arg(Map[MatrixXd](from_numpy(array)))
```

The last line contains the actual conversion. Due to limitations in
Cython, for the conversions in this direction, the type
`Map[MatrixXd]` must be specified both in the definition and the
conversion call (the other direction is slightly simpler - see below).


## Writing Eigen Map types in Cython

Since Cython does not support nested fused types, you cannot write types like `Map[Matrix[double, 2, 2]]`. In most cases, you won't need to, since you can just use Eigens convenience typedefs, such as `Map[VectorXd]`. If you need the additional flexibility of the full specification, you can use the `FlattenedMap` type, where all type arguments can be specified at top level, for instance `FlattenedMap[Matrix, double, _2, _3]` or `FlattenedMap[Matrix, double, _2, _Dynamic]`. Note that dimensions must be prefixed with an underscore.

Using full specifications of the Eigen types, the previous example would look like this:
```
cdef extern from "functions.h":
     cdef void _function_w_mat_arg "function_w_mat_arg" (FlattenedMap[Matrix, double, Dynamic, Dynamic] &)

# This will be exposed to Python
def function_w_mat_arg(np.ndarray array):
    return _function_w_mat_arg(FlattenedMap[Matrix, double, Dynamic, Dynamic](from_numpy(array)))
```


## From Numpy to Eigen (insisting on a copy)

Eigency will not complain if the C++ function you interface with does
not take a Eigen Map object, but instead a regular Matrix or
Array. However, in such cases, a copy will be made. Actually, the
procedure is exactly the same as above. In the `.pyx` file, you still
everything exactly the same way as for the Map case described above.

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
    return _function_w_vec_arg_no_map(Map[VectorXd](from_numpy(array)))
```

Cython will not mind the fact that the argument type in the extern
declaration (a Map type) differs from the actual one in the `.h` file,
as long as one can be assigned to the other. Since Map objects can be
assigned to their corresponding Matrix/Array types this works
seemlessly. But keep in mind that this assignment will make a copy of
the underlying data.

## Eigen to Numpy

C++ functions returning a reference to an Eigen Matrix/Array can
also be transferred to numpy arrays without copying their content.
In this case the syntax is even simpler than above. Assume we have
a class with a single getter function, returning an Eigen matrix
member:

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
        return to_numpy(self.thisptr.get_matrix())
```

This last line contains the actual conversion. Note that the Eigen to
Numpy direction, only a single function call to `to_numpy` is
necessary.

Due to limitations in Cython, Eigency cannot deal with full
Matrix/Array template specifications as return types
(e.g. `Matrix[double, 4, 2]`). However, as a workaround, you can use
`PlainObjectBase` as a return type in such cases (or in all cases if
you prefer):

```
         PlainObjectBase &get_matrix()
```

## Eigen to Numpy (non-reference return values)

Functions returning a Eigen object (not a reference), are specified
in a similar way. 

For instance, given the following C++ function:

```c++
Eigen::Matrix3d function_w_mat_retval();
```

The Cython code could be written as:

```
cdef extern from "functions.h":
     cdef Matrix3d _function_w_mat_retval "function_w_mat_retval" ()

# This will be exposed to Python
def function_w_mat_retval():
    return to_numpy(_function_w_mat_retval())
```

As mentioned above, you can always replace `Matrix3d` with
`PlainObjectBase`, which is especially relevant when working with
Eigen object that do not have an associated convenience typedef.


## Overriding default behavior

The `to_numpy` function will attempt do guess whether you want a copy
or a view, depending on the return type. Most of the time, this is
probably what you want. However, there might be cases where you want
to override this behavior. For instance, functions returning const
references will result in a copy of the array, since the const-ness
cannot be enforced in Python. However, you can always override the
default behavior by using the `to_numpy_copy` or `to_numpy_view`
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
        return to_numpy(self.thisptr.get_const_matrix())
```

While this would force it to return a view

```python
cdef class MyClass:
    ...
    def get_const_matrix(self):
        return to_numpy_view(self.thisptr.get_const_matrix())
```


