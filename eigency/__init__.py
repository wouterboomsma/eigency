import os
import numpy as np

def get_includes():
    root = os.path.dirname(__file__)
    parent = os.path.join(root, "..")
    return [root, parent, np.get_include(), os.path.join(root, 'eigen')]

