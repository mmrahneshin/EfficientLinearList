#include <stdlib.h>
#include <Python.h>
#include "indexed_PPS23RB_binaryTree_node.h"

IndexedPPS23RBBinaryTreeNode *ipps23rbbt_new_node(PyObject *data)
{
    IndexedPPS23RBBinaryTreeNode *node = (IndexedPPS23RBBinaryTreeNode *)malloc(sizeof(IndexedPPS23RBBinaryTreeNode));

    if (!node)
    {
        PyErr_NoMemory();
        return NULL;
    }

    node->mLeftChild = NULL;
    node->mRightChild = NULL;
    node->mParent = NULL;
    node->mLeftSize = 0;
    node->mColor = BLACK;
    node->mData = data;

    Py_XINCREF(node->mData); // Safe for NULL data
    return node;
}

void ipps23rbbt_node_free(IndexedPPS23RBBinaryTreeNode *node)
{
    Py_XDECREF(node->mData);

    free(node);
}
