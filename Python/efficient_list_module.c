#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "efficient_list.h"

// Define Python wrapper object
typedef struct
{
    PyObject_HEAD EfficientList *el;
} EfficientListObject;

// Deallocation
static void EfficientList_dealloc(EfficientListObject *self)
{
    efficient_list_free(self->el);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

// Constructor
static PyObject *EfficientList_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    EfficientListObject *self;
    self = (EfficientListObject *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->el = efficient_list_new();
        if (self->el == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *)self;
}

// insert method
static PyObject *EfficientList_insert(EfficientListObject *self, PyObject *args)
{
    Py_ssize_t idx;
    PyObject *data;
    if (!PyArg_ParseTuple(args, "nO", &idx, &data))
        return NULL;

    efficient_list_insert(self->el, idx, data);
    Py_RETURN_NONE;
}

// remove method
static PyObject *EfficientList_remove(EfficientListObject *self, PyObject *args)
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx))
        return NULL;

    efficient_list_remove(self->el, idx);
    Py_RETURN_NONE;
}

// __getitem__
static PyObject *EfficientList_getitem(EfficientListObject *self, Py_ssize_t idx)
{
    return efficient_list_get_item(self->el, idx); // Already returns PyObject*
}

// __len__
static Py_ssize_t EfficientList_len(EfficientListObject *self)
{
    return efficient_list_size(self->el);
}

// Method table
static PyMethodDef EfficientList_methods[] = {
    {"insert", (PyCFunction)EfficientList_insert, METH_VARARGS, "Insert at index"},
    {"remove", (PyCFunction)EfficientList_remove, METH_VARARGS, "Remove at index"},
    {NULL} // Sentinel
};

// Sequence protocol
static PySequenceMethods EfficientList_sequence_methods = {
    (lenfunc)EfficientList_len, // __len__
    0,                          // __add__, etc.
    0,
    (ssizeargfunc)EfficientList_getitem, // __getitem__
    0,
    0,
    0,
    0,
    0,
    0};

// Type object
static PyTypeObject EfficientListType = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "efficient_list.EfficientList",
    .tp_basicsize = sizeof(EfficientListObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "EfficientList backed by custom RBTree",
    .tp_new = EfficientList_new,
    .tp_dealloc = (destructor)EfficientList_dealloc,
    .tp_methods = EfficientList_methods,
    .tp_as_sequence = &EfficientList_sequence_methods,
};

// Module definition
static PyModuleDef efficient_list_module = {
    PyModuleDef_HEAD_INIT,
    "efficient_list",
    "Efficient list using a custom red-black tree",
    -1,
    NULL, NULL, NULL, NULL, NULL};

// Module init
PyMODINIT_FUNC PyInit_efficient_list(void)
{
    if (PyType_Ready(&EfficientListType) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&efficient_list_module);
    if (!m)
        return NULL;

    Py_INCREF(&EfficientListType);
    PyModule_AddObject(m, "EfficientList", (PyObject *)&EfficientListType);
    return m;
}