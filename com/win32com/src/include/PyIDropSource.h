// This file declares the IDropSource Interface and Gateway for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyIDropSource : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR(PyIDropSource);
    static IDropSource *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *QueryContinueDrag(PyObject *self, PyObject *args);
    static PyObject *GiveFeedback(PyObject *self, PyObject *args);

   protected:
    PyIDropSource(IUnknown *pdisp);
    ~PyIDropSource();
};
// ---------------------------------------------------
//
// Gateway Declaration

class PyGDropSource : public PyGatewayBase, public IDropSource {
   protected:
    PyGDropSource(PyObject *instance) : PyGatewayBase(instance) { ; }
    PYGATEWAY_MAKE_SUPPORT2(PyGDropSource, IDropSource, IID_IDropSource, PyGatewayBase)

    // IDropSource
    STDMETHOD(QueryContinueDrag)(BOOL fEscapePressed, DWORD grfKeyState);

    STDMETHOD(GiveFeedback)(DWORD dwEffect);
};
