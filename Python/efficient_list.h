#ifndef EFFICIENT_LIST_H
#define EFFICIENT_LIST_H

#include <Python.h> // For PyObject*
#include "indexed_PPS23RB_binaryTree.h"

typedef struct EfficientList
{
    IPPRBBT *mIPPS23RBbt;
} EfficientList;

EfficientList *efficient_list_new(void);
void efficient_list_free(EfficientList *self);
void efficient_list_insert(EfficientList *el, Py_ssize_t idx, PyObject *data);
void efficient_list_remove(EfficientList *el, Py_ssize_t idx);

PyObject *efficient_list_get_item(EfficientList *el, Py_ssize_t idx);
Py_ssize_t efficient_list_size(EfficientList *el);
#endif
