// @doc
#include "stdafxdde.h"
#include "ddemodule.h"


PythonDDEStringItem *PyDDEStringItem::GetItem(PyObject *self)
{
    return (PythonDDEStringItem *)ui_assoc_object::GetGoodCppObject(self, &type);
}

// @pymethod |PyDDEStringItem|SetData|Sets an items data, and causes any underlying notification.
PyObject *PyDDEStringItem_SetData(PyObject *self, PyObject *args)
{
    WCHAR *val;
    PyObject *obval;
    PythonDDEStringItem *pItem = PyDDEStringItem::GetItem(self);
    if (!pItem)
        return NULL;
    // @pyparm string|data||The data to set.
    if (!PyArg_ParseTuple(args, "O:SetData", &obval))
        return NULL;
    if (!PyWinObject_AsWCHAR(obval, &val, FALSE))
        return NULL;
    int nLen = WideCharToMultiByte(CP_ACP, 0, val, -1, NULL, 0, NULL, NULL);
    if (nLen == 0) {
        RETURN_NONE;
    }
    TCHAR *pResult = new TCHAR[nLen];
    WideCharToMultiByte(CP_ACP, 0, val, -1, (LPSTR)pResult, nLen, NULL, NULL);
    GUI_BGN_SAVE;
    pItem->SetData(pResult);
    GUI_END_SAVE;
    PyWinObject_FreeTCHAR(val);
    delete pResult;
    RETURN_NONE;
}

// @pymethod |PyDDEStringItem|Destroy|Destroys an item
PyObject *PyDDEStringItem_Destroy(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":Destroy"))
        return NULL;
    GUI_BGN_SAVE;
    PythonDDEStringItem *pItem = PyDDEStringItem::GetItem(self);
    GUI_END_SAVE;
    if (!pItem)
        return NULL;
    delete pItem;
    RETURN_NONE;
}

// @object PyDDEStringItem|A DDE string item.
static struct PyMethodDef PyDDEStringItem_methods[] = {
    {"Destroy", PyDDEStringItem_Destroy, 1},
    {"SetData", PyDDEStringItem_SetData,
     1},          // @pymeth SetData|Sets an items data, and causes any underlying notification.
    {NULL, NULL}  // sentinel
};

ui_type_CObject PyDDEStringItem::type("PyDDEStringItem", &ui_assoc_CObject::type, RUNTIME_CLASS(CDDEStringItem),
                                      sizeof(PyDDEStringItem), PYOBJ_OFFSET(PyDDEStringItem), PyDDEStringItem_methods,
                                      GET_PY_CTOR(PyDDEStringItem));
