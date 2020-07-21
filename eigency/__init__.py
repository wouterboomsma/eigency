from pkg_resources import resource_filename
import numpy as np
import os.path
import pkgconfig

__eigen_dir__ = @EIGEN_REL_PATH@

def get_includes(include_eigen=True):
    root = os.path.dirname(__file__)
    path = [root, np.get_include()]
    if include_eigen:
        path.append(__eigen_dir__)
    return path
