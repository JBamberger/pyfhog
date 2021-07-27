from setuptools import setup

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

    classifiers=[
        'Development Status :: 1 - Planning',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
    ],
)
