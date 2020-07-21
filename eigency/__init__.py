from pkg_resources import resource_filename
import numpy as np
import os.path
import pkgconfig

__eigen_dir__ = os.path.relpath(pkgconfig.cflags('eigen3')[2:])

def get_includes(include_eigen=True):
    root = os.path.dirname(__file__)
    path = [root, np.get_include()]
    if include_eigen:
        path.append(__eigen_dir__)
    return path
