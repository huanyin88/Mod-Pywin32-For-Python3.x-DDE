// This file implements the IEnumSTATSTG Interface and Gateway for Python.
// Generated by makegw.py

#include "stdafx.h"
#include "PythonCOM.h"
#include "PythonCOMServer.h"
#include "PyIEnumSTATSTG.h"

// @doc - This file contains autoduck documentation

// ---------------------------------------------------
//
// Interface Implementation

PyIEnumSTATSTG::PyIEnumSTATSTG(IUnknown *pdisp) : PyIUnknown(pdisp) { ob_type = &type; }

PyIEnumSTATSTG::~PyIEnumSTATSTG() {}

/* static */ IEnumSTATSTG *PyIEnumSTATSTG::GetI(PyObject *self) { return (IEnumSTATSTG *)PyIUnknown::GetI(self); }

// @pymethod (<o STATSTG>, ...)|PyIEnumSTATSTG|Next|Retrieves a specified number of items in the enumeration sequence.
PyObject *PyIEnumSTATSTG::Next(PyObject *self, PyObject *args)
{
    long celt = 1;
    // @pyparm int|num|1|Number of items to retrieve.
    if (!PyArg_ParseTuple(args, "|l:Next", &celt))
        return NULL;

    IEnumSTATSTG *pIESTATSTG = GetI(self);
    if (pIESTATSTG == NULL)
        return NULL;

    STATSTG *rgVar = new STATSTG[celt];
    if (rgVar == NULL)
        return PyErr_Format(PyExc_MemoryError, "Unable to allocate %d bytes", celt * sizeof(STATSTG));
    ZeroMemory(rgVar, celt * sizeof(STATSTG));

    int i;
    ULONG celtFetched;
    PyObject *result;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATSTG->Next(celt, rgVar, &celtFetched);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        result = PyCom_BuildPyException(hr);
    else {
        result = PyTuple_New(celtFetched);
        if (result != NULL) {
            for (i = celtFetched; i--;) {
                PyObject *ob = PyCom_PyObjectFromSTATSTG(&rgVar[i]);
                if (ob == NULL) {
                    Py_DECREF(result);
                    result = NULL;
                    break;
                }
                PyTuple_SET_ITEM(result, i, ob);
            }
        }
    }

    for (i = celtFetched; i--;)
        if (rgVar[i].pwcsName != NULL)
            CoTaskMemFree(rgVar[i].pwcsName);

    delete[] rgVar;
    return result;
}

// @pymethod |PyIEnumSTATSTG|Skip|Skips over the next specified elementes.
PyObject *PyIEnumSTATSTG::Skip(PyObject *self, PyObject *args)
{
    long celt;
    if (!PyArg_ParseTuple(args, "l:Skip", &celt))
        return NULL;

    IEnumSTATSTG *pIESTATSTG = GetI(self);
    if (pIESTATSTG == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATSTG->Skip(celt);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod |PyIEnumSTATSTG|Reset|Resets the enumeration sequence to the beginning.
PyObject *PyIEnumSTATSTG::Reset(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Reset"))
        return NULL;

    IEnumSTATSTG *pIESTATSTG = GetI(self);
    if (pIESTATSTG == NULL)
        return NULL;

    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATSTG->Reset();
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    Py_INCREF(Py_None);
    return Py_None;
}

// @pymethod <o PyIEnumSTATSTG>|PyIEnumSTATSTG|Clone|Creates another enumerator that contains the same enumeration state
// as the current one
PyObject *PyIEnumSTATSTG::Clone(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Clone"))
        return NULL;

    IEnumSTATSTG *pIESTATSTG = GetI(self);
    if (pIESTATSTG == NULL)
        return NULL;

    IEnumSTATSTG *pClone;
    PY_INTERFACE_PRECALL;
    HRESULT hr = pIESTATSTG->Clone(&pClone);
    PY_INTERFACE_POSTCALL;
    if (FAILED(hr))
        return PyCom_BuildPyException(hr);

    return PyCom_PyObjectFromIUnknown(pClone, IID_IEnumSTATSTG, FALSE);
}

// @object PyIEnumSTATSTG|An enumerator for elements contained in a <o PyIStorage> object
static struct PyMethodDef PyIEnumSTATSTG_methods[] = {
    {"Next", PyIEnumSTATSTG::Next,
     1},  // @pymeth Next|Retrieves a specified number of items in the enumeration sequence.
    {"Skip", PyIEnumSTATSTG::Skip, 1},    // @pymeth Skip|Skips over the next specified elementes.
    {"Reset", PyIEnumSTATSTG::Reset, 1},  // @pymeth Reset|Resets the enumeration sequence to the beginning.
    {"Clone", PyIEnumSTATSTG::Clone,
     1},  // @pymeth Clone|Creates another enumerator that contains the same enumeration state as the current one.
    {NULL}};

PyComEnumTypeObject PyIEnumSTATSTG::type("PyIEnumSTATSTG",
                                         &PyIUnknown::type,  // @base PyIEnumStatSTG|PyIUnknown
                                         sizeof(PyIEnumSTATSTG), PyIEnumSTATSTG_methods,
                                         GET_PYCOM_CTOR(PyIEnumSTATSTG));

// ---------------------------------------------------
//
// Gateway Implementation

STDMETHODIMP PyGEnumSTATSTG::Next(
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ STATSTG __RPC_FAR *rgVar,
    /* [out] */ ULONG __RPC_FAR *pCeltFetched)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Next", &result, "i", celt);
    if (FAILED(hr))
        return hr;

    if (!PySequence_Check(result))
        goto error;
    int len;
    len = PyObject_Length(result);
    if (len == -1)
        goto error;
    if (len > (int)celt)
        len = celt;

    if (pCeltFetched)
        *pCeltFetched = len;

    int i;
    for (i = 0; i < len; ++i) {
        PyObject *ob = PySequence_GetItem(result, i);
        if (ob == NULL)
            goto error;

        if (!PyCom_PyObjectAsSTATSTG(ob, &rgVar[i])) {
            Py_DECREF(result);
            return PyCom_SetCOMErrorFromPyException(IID_IEnumSTATSTG);
        }
    }

    Py_DECREF(result);

    return len < (int)celt ? S_FALSE : S_OK;

error:
    PyErr_Clear();  // just in case
    Py_DECREF(result);
    return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumSTATSTG, "Next() did not return a sequence of objects");
}

STDMETHODIMP PyGEnumSTATSTG::Skip(
    /* [in] */ ULONG celt)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Skip", NULL, "i", celt);
}

STDMETHODIMP PyGEnumSTATSTG::Reset(void)
{
    PY_GATEWAY_METHOD;
    return InvokeViaPolicy("Reset");
}

STDMETHODIMP PyGEnumSTATSTG::Clone(
    /* [out] */ IEnumSTATSTG __RPC_FAR *__RPC_FAR *ppEnum)
{
    PY_GATEWAY_METHOD;
    PyObject *result;
    HRESULT hr = InvokeViaPolicy("Clone", &result);
    if (FAILED(hr))
        return hr;

    /*
    ** Make sure we have the right kind of object: we should have some kind
    ** of IUnknown subclass wrapped into a PyIUnknown instance.
    */
    if (!PyIBase::is_object(result, &PyIUnknown::type)) {
        /* the wrong kind of object was returned to us */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumSTATSTG);
    }

    /*
    ** Get the IUnknown out of the thing. note that the Python ob maintains
    ** a reference, so we don't have to explicitly AddRef() here.
    */
    IUnknown *punk = ((PyIUnknown *)result)->m_obj;
    if (!punk) {
        /* damn. the object was released. */
        Py_DECREF(result);
        return PyCom_SetCOMErrorFromSimple(E_FAIL, IID_IEnumSTATSTG);
    }

    /*
    ** Get the interface we want. note it is returned with a refcount.
    ** This QI is actually going to instantiate a PyGEnumSTATSTG.
    */
    Py_BEGIN_ALLOW_THREADS hr = punk->QueryInterface(IID_IEnumSTATSTG, (LPVOID *)ppEnum);
    Py_END_ALLOW_THREADS

        /* done with the result; this DECREF is also for <punk> */
        Py_DECREF(result);

    return PyCom_SetCOMErrorFromSimple(hr, IID_IEnumSTATSTG);
}
