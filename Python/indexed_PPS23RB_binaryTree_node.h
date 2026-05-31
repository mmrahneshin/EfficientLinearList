#ifndef INDEXED_PPS23RB_BINARYTREE_NODE_H
#define INDEXED_PPS23RB_BINARYTREE_NODE_H

#include <Python.h> // For PyObject*

// Enum for node color
typedef enum
{
    RED = 0,
    BLACK = 1
} COLOR;

typedef struct IndexedPPS23RBBinaryTreeNode
{
    COLOR mColor;
    PyObject *mData; // Python object (use Py_INCREF / Py_DECREF)
    Py_ssize_t mLeftSize;

    struct IndexedPPS23RBBinaryTreeNode *mLeftChild;
    struct IndexedPPS23RBBinaryTreeNode *mRightChild;
    struct IndexedPPS23RBBinaryTreeNode *mParent;
} IndexedPPS23RBBinaryTreeNode;

IndexedPPS23RBBinaryTreeNode *ipps23rbbt_new_node(PyObject *data);
void ipps23rbbt_node_free(IndexedPPS23RBBinaryTreeNode *node);

#endif // INDEXED_PPS23RB_BINARYTREE_NODE_H
