import os.path

import numpy as np
from pkg_resources import resource_filename

__eigen_dir__ = resource_filename(__name__, "eigen_3.2.8")


def get_includes(include_eigen=True):
    root = os.path.dirname(__file__)
    path = [root, np.get_include()]
    if include_eigen:
        path.append(os.path.join(root, __eigen_dir__))
    return path
