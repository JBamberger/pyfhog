from setuptools import setup
from distutils.core import setup, Extension
from numpy.distutils import misc_util

setup(
    name='pyfhog',
    version='0.1.0',
    description='Python wrapper for the fhog implementation of Piotr Dollars Matlab toolbox',
    url='https://github.com/JBamberger/pyfhog',
    author='Jannik Bamberger',
    author_email='mail@jbamberger.de',
    license='BSD 2-clause',
    packages=['pyfhog'],
    install_requires=['numpy', ],
    ext_modules=[Extension("_pyfhog", ["pyfhog/_pyfhog.cpp", "pyfhog/gradient.cpp"])],
    include_dirs=misc_util.get_numpy_include_dirs(),
    classifiers=[
        'Development Status :: 1 - Planning',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
    ],
)
