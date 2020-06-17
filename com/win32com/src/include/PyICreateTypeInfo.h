// This file declares the ICreateTypeInfo Interface for Python.
// Generated by makegw.py
// ---------------------------------------------------
//
// Interface Declaration

class PyICreateTypeInfo : public PyIUnknown {
   public:
    MAKE_PYCOM_CTOR(PyICreateTypeInfo);
    static ICreateTypeInfo *GetI(PyObject *self);
    static PyComTypeObject type;

    // The Python methods
    static PyObject *SetGuid(PyObject *self, PyObject *args);
    static PyObject *SetTypeFlags(PyObject *self, PyObject *args);
    static PyObject *SetDocString(PyObject *self, PyObject *args);
    static PyObject *SetHelpContext(PyObject *self, PyObject *args);
    static PyObject *SetVersion(PyObject *self, PyObject *args);
    static PyObject *AddRefTypeInfo(PyObject *self, PyObject *args);
    static PyObject *AddFuncDesc(PyObject *self, PyObject *args);
    static PyObject *AddImplType(PyObject *self, PyObject *args);
    static PyObject *SetImplTypeFlags(PyObject *self, PyObject *args);
    static PyObject *SetAlignment(PyObject *self, PyObject *args);
    static PyObject *SetSchema(PyObject *self, PyObject *args);
    static PyObject *AddVarDesc(PyObject *self, PyObject *args);
    static PyObject *SetFuncAndParamNames(PyObject *self, PyObject *args);
    static PyObject *SetVarName(PyObject *self, PyObject *args);
    static PyObject *SetTypeDescAlias(PyObject *self, PyObject *args);
    static PyObject *DefineFuncAsDllEntry(PyObject *self, PyObject *args);
    static PyObject *SetFuncDocString(PyObject *self, PyObject *args);
    static PyObject *SetVarDocString(PyObject *self, PyObject *args);
    static PyObject *SetFuncHelpContext(PyObject *self, PyObject *args);
    static PyObject *SetVarHelpContext(PyObject *self, PyObject *args);
    static PyObject *SetMops(PyObject *self, PyObject *args);
    static PyObject *SetTypeIdldesc(PyObject *self, PyObject *args);
    static PyObject *LayOut(PyObject *self, PyObject *args);

   protected:
    PyICreateTypeInfo(IUnknown *pdisp);
    ~PyICreateTypeInfo();
};