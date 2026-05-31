#ifndef EFFICIENT_LIST_H
#define EFFICIENT_LIST_H

#include <Python.h> // For PyObject*
#include "indexed_PPS23RB_binaryTree.h"

typedef struct EfficientLinearList
{
    IPPRBBT *mIPPS23RBbt;
} EfficientLinearList;

EfficientLinearList *efficient_list_new(void);
void efficient_list_free(EfficientLinearList *self);
void efficient_list_insert(EfficientLinearList *el, Py_ssize_t idx, PyObject *data);
void efficient_list_remove(EfficientLinearList *el, Py_ssize_t idx);

PyObject *efficient_list_get_item(EfficientLinearList *el, Py_ssize_t idx);
Py_ssize_t efficient_list_size(EfficientLinearList *el);
#endif
