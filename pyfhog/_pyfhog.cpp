#include <Python.h>
#include <numpy/arrayobject.h>

#include "gradient.hpp"

static PyObject *_pyfhog_fhog(PyObject *self, PyObject *args);

static PyMethodDef fhogFunctions[] = {
    {"fhog", _pyfhog_fhog, METH_VARARGS,
     "Computes the Histogram of Gradients."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef fhogModule = {
    PyModuleDef_HEAD_INIT,
    "_pyfhog",
    "Python wrapper for fhog from Piotr Dollar's Matlab toolbox.",
    -1,
    fhogFunctions,
    NULL,
    NULL,
    NULL,
    NULL,
};

extern "C" PyObject *PyInit__pyfhog(void) {
  PyObject *module = PyModule_Create(&fhogModule);
  if (module == NULL) {
    return NULL;
  }
  import_array();
  return module;
}

static PyObject *_pyfhog_fhog(PyObject *self, PyObject *args) {
  PyObject *inObj = NULL;
  int binSize, nOrients, softBin;
  float clip;

  if (!PyArg_ParseTuple(args, "Oiiif", &inObj, &binSize, &nOrients, &softBin,
                        &clip)) {
    return NULL;
  }

  PyObject *inArray =
      PyArray_FROM_OTF(inObj, NPY_FLOAT, NPY_ARRAY_F_CONTIGUOUS);
  if (inArray == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Failed to access input array.");
    Py_XDECREF(inArray);
    return NULL;
  }

  // get dimensions of input array
  int ndim = PyArray_NDIM(inArray);
  int h = (int)PyArray_DIM(inArray, 0);
  int w = (int)PyArray_DIM(inArray, 1);
  int d = ndim == 3 ? (int)PyArray_DIM(inArray, 2) : 1;

  // Create output arrays for gradient computation
  npy_intp gradDims[] = {h, w};
  npy_intp histDims[] = {h / binSize, w / binSize, nOrients * 3 + 5};
  PyObject *magArray = PyArray_ZEROS(2, gradDims, NPY_FLOAT, 1);
  PyObject *oriArray = PyArray_ZEROS(2, gradDims, NPY_FLOAT, 1);
  PyObject *histArray = PyArray_ZEROS(3, histDims, NPY_FLOAT, 1);
  if (magArray == NULL || oriArray == NULL || histArray == NULL) {
    PyErr_SetString(PyExc_RuntimeError, "Failed to create output arrays.");
    Py_DECREF(inArray);
    Py_XDECREF(magArray);
    Py_XDECREF(oriArray);
    Py_XDECREF(histArray);
    return NULL;
  }

  float *inData = (float *)PyArray_DATA(inArray);
  float *magData = (float *)PyArray_DATA(magArray);
  float *oriData = (float *)PyArray_DATA(oriArray);
  float *histData = (float *)PyArray_DATA(histArray);

  gradMag(inData, magData, oriData, h, w, d, true);
  fhog(magData, oriData, histData, h, w, binSize, nOrients, softBin, clip);

  Py_DECREF(inArray);
  Py_DECREF(magArray);
  Py_DECREF(oriArray);

  return histArray;
}