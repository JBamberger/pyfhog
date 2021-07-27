"""
PyFHoG - Python wrapper for Felzenszwalb et al.'s HOG feature extractor.

    Python library for fast and accurate dense HoG feature extraction.
    The library uses the fhog implementation by Piotr Dollar's Matlab toolbox.
"""

__version__ = "0.1.0"
__author__ = 'Jannik Bamberger'

import numpy as np
import _pyfhog

def fhog(I, bin_size=8, num_orients=9, clip=0.2, soft_bin = -1):
    in_arr = I.astype(np.float32)
    H = _pyfhog.fhog(in_arr, bin_size, num_orients, soft_bin, clip)
    return H