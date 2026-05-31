#include <Python.h>
#include "efficient_list.h"

EfficientList *efficient_list_new(void)
{
    EfficientList *el = (EfficientList *)malloc(sizeof(EfficientList));
    if (!el)
    {
        PyErr_NoMemory();
        return NULL;
    }

    el->mIPPS23RBbt = ipps23rbbt_new();
    if (!el->mIPPS23RBbt)
    {
        PyErr_NoMemory();
        return NULL;
    }

    return el;
}

void efficient_list_free(EfficientList *el)
{
    ipps23rbbt_free(el->mIPPS23RBbt);
    free(el);
}

static inline IPPS23RBBTN *getNodeWithUpdateLeftSize(IPPRBBT *mIPPS23RBbt, Py_ssize_t idx, int status)
{
    IPPS23RBBTN *node = mIPPS23RBbt->mInOrderEnd;
    node->mLeftSize += status;

    node = node->mLeftChild;
    int leftOnly = 1;
    int leftSize = node->mLeftSize + mIPPS23RBbt->mGlobalLeftSize;
    while (leftSize != idx)
    {
        if (idx < leftSize)
        {
            node->mLeftSize += status;
            node = node->mLeftChild;
        }
        else
        {
            leftOnly = 0;
            idx = idx - leftSize - 1;
            node = node->mRightChild;
        }
        leftSize = node->mLeftSize + (mIPPS23RBbt->mGlobalLeftSize * leftOnly);
    }
    return node;
}

void efficient_list_insert(EfficientList *el, Py_ssize_t idx, PyObject *data)
{
    IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
    if (idx < 0 || idx > mIPPS23RBbt->mSize)
    {
        PyErr_SetString(PyExc_IndexError, "out_of_range");
        return;
    }

    if (mIPPS23RBbt->mSize == 0)
    {
        ipps23rbbt_insert_root_node(mIPPS23RBbt, data);
        return;
    }

    if (idx == mIPPS23RBbt->mSize)
    {
        ipps23rbbt_insert_last_inorder_node(mIPPS23RBbt, data);
        return;
    }

    if (idx == 0)
    {
        ipps23rbbt_insert_first_inorder_node(mIPPS23RBbt, data);
        return;
    }

    IPPS23RBBTN *node = getNodeWithUpdateLeftSize(mIPPS23RBbt, idx, 1);
    node->mLeftSize++;

    if (!ipps23rbbt_has_left_child(node, mIPPS23RBbt->mNilSentinel))
    {
        ipps23rbbt_insert_left_child(mIPPS23RBbt, node, data);
    }
    else
    {
        node = node->mLeftChild;
        while (ipps23rbbt_has_right_child(node, mIPPS23RBbt->mNilSentinel))
            node = node->mRightChild;
        ipps23rbbt_insert_right_child(mIPPS23RBbt, node, data);
    }
}

void efficient_list_remove(EfficientList *el, Py_ssize_t idx)
{
    IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
    if (idx < 0 || idx >= mIPPS23RBbt->mSize)
    {
        PyErr_SetString(PyExc_IndexError, "out_of_range");
        return;
    }

    if (idx == mIPPS23RBbt->mSize - 1)
    {
        ipps23rbbt_delete_last_inorder_node(mIPPS23RBbt);
        return;
    }

    if (idx == 0)
    {
        ipps23rbbt_delete_first_inorder_node(mIPPS23RBbt);
        return;
    }

    IPPS23RBBTN *node = getNodeWithUpdateLeftSize(mIPPS23RBbt, idx, -1);
    ipps23rbbt_delete_node(mIPPS23RBbt, node);
}

PyObject *efficient_list_get_item(EfficientList *el, Py_ssize_t idx)
{
    IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
    if (idx < 0 || idx >= mIPPS23RBbt->mSize)
    {
        PyErr_SetString(PyExc_IndexError, "out_of_range");
        return NULL;
    }
    IPPS23RBBTN *node = getNodeWithUpdateLeftSize(mIPPS23RBbt, idx, 0);
    Py_XINCREF(node->mData);
    return node->mData;
}

Py_ssize_t efficient_list_size(EfficientList *el)
{
    return el->mIPPS23RBbt->mSize;
}
