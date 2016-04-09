# eigency
Eigency is a Cython interface between Numpy arrays and Matrix/Array
objects from the Eigen C++ library. It is intended to simplify the
process of writing C++ extensions using the Eigen library. Eigency is
designed to reuse the underlying storage of the arrays when passing
data back and forth, and will thus avoid making unnecessary copies
whenever possible. Only in cases where copies are explicitly requested
by your C++ code will they be made (see example below)

# Setup
To import eigency functionality, add the following to your `.pyx` file:
```
from eigency.core cimport *
```
In addition, the `setup.py` the include directories must be set up
to include the eigency include. This can be done by calling the `get_includes`
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

# From Numpy to Eigen
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

Since Cython does not support nested fused types, you cannot write types like `Map[Matrix[double, 2, 2]]`. In most cases, you won't need to, since you can just use Eigens convenience typedefs, such as `Map[VectorXd]`. If you need the additional flexibility of the full specification, you can use the `FlattenedMap` type, where all type arguments can be specified at top level, for instance `FlattenedMap[Matrix, double, _2, _3]` or `FlattenedMap[Matrix, double, _2, _Dynamic]`. Note that dimensions must be prefixed with an underscore.


# From Numpy to Eigen (insisting on a copy)

If the function you are interfacing with takes a non-Map Eigen type,
Eigency will still transform it to a Map type first, after it will be
copied by Eigen into the target Array or Matrix variable. To make it
explicit that a copy is made, Eigency uses a `CopyMap` (and
`FlattenedCopyMap`) for this scenario.

For instance, given the following C++ function:
```c++
void function_w_vec_arg_no_map(const Eigen::VectorXd &vec);
```

The Cython definitions would look like this:

```
cdef extern from "functions.h":
     cdef void _function_w_vec_arg_no_map "function_w_vec_arg_no_map"(CopyMap[VectorXd] &)

# This will be exposed to Python
def function_w_vec_arg_no_map(np.ndarray array):
    return _function_w_vec_arg_no_map(CopyMap[VectorXd](from_numpy(array)))
```




