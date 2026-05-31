#ifndef INDEXED_PPS23RB_BINARYTREE_H
#define INDEXED_PPS23RB_BINARYTREE_H

#include <Python.h> // For PyObject*
#include "indexed_PPS23RB_binaryTree_node.h"

typedef struct IndexedPPS23RBBinaryTree
{
    Py_ssize_t mGlobalLeftSize;
    Py_ssize_t mSize;

    IndexedPPS23RBBinaryTreeNode *mRevInOrderEnd;
    IndexedPPS23RBBinaryTreeNode *mInOrderEnd;
    IndexedPPS23RBBinaryTreeNode *mNilSentinel;
    IndexedPPS23RBBinaryTreeNode *mLastInOrderNode;
    IndexedPPS23RBBinaryTreeNode *mFirstInOrderNode;

} IndexedPPS23RBBinaryTree;

typedef IndexedPPS23RBBinaryTreeNode IPPS23RBBTN;
typedef IndexedPPS23RBBinaryTree IPPRBBT;

// Function declarations
IPPRBBT *ipps23rbbt_new(void);
int ipps23rbbt_has_left_child(IPPS23RBBTN *node, IPPS23RBBTN *mNilSentinel);
int ipps23rbbt_has_right_child(IPPS23RBBTN *node, IPPS23RBBTN *mNilSentinel);
void ipps23rbbt_free(IPPRBBT *tree);
Py_ssize_t ipps23rbbt_size(IPPRBBT *tree);
int ipps23rbbt_is_empty(IPPRBBT *tree);
// insert functions
void ipps23rbbt_insert_root_node(IPPRBBT *tree, PyObject *data);
void ipps23rbbt_insert_last_inorder_node(IPPRBBT *tree, PyObject *data);
void ipps23rbbt_insert_first_inorder_node(IPPRBBT *tree, PyObject *data);
void ipps23rbbt_insert_left_child(IPPRBBT *tree, IPPS23RBBTN *parentNode, PyObject *data);
void ipps23rbbt_insert_right_child(IPPRBBT *tree, IPPS23RBBTN *parentNode, PyObject *data);
// delete functions
void ipps23rbbt_delete_node(IPPRBBT *tree, IPPS23RBBTN *theNode);
void ipps23rbbt_delete_last_inorder_node(IPPRBBT *tree);
void ipps23rbbt_delete_first_inorder_node(IPPRBBT *tree);

#endif