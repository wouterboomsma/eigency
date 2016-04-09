# eigency
Eigency is a Cython interface between Numpy arrays and Matrix/Array
objects from the Eigen C++ library. It is intended to simplify the process
of writing C++ extensions using the Eigen library.

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
    Extension(..."module-dir-name/module-name", ["module-dir-name/module-name.pyx"],
        include_dirs = [".", "module-dir-name"] + eigency.get_includes()
    ),
]
```
Eigency includes a version of the Eigen library, and the `get_includes` function will include the path to this directory. If you
have your own version of Eigen, just set the `include_eigen` option to False:

```
eigency.get_includes(include_eigen=False)
```

