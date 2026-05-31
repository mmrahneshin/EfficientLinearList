#include <stdlib.h>
#include <Python.h>
#include "indexed_PPS23RB_binaryTree.h"

static inline void updateAfterRR(IPPS23RBBTN *node)
{
    IPPS23RBBTN *A = node->mLeftChild;
    node->mLeftSize += A->mLeftSize + 1; // B->mLeftSize = [C->mLeftSize + 1](is B->mLeftSize) + A->mLeftSize + 1

    COLOR c = node->mColor;
    node->mColor = node->mLeftChild->mColor;
    node->mLeftChild->mColor = c;
}

static inline IPPS23RBBTN *RR(IPPS23RBBTN *A, IPPS23RBBTN *mNilSentinel)
{
    IPPS23RBBTN *B = A->mRightChild;
    A->mRightChild = B->mLeftChild;

    if (ipps23rbbt_has_left_child(B, mNilSentinel))
    {
        B->mLeftChild->mParent = A;
    }

    if (A->mParent->mLeftChild == A)
    {
        A->mParent->mLeftChild = B;
    }
    else
    {
        A->mParent->mRightChild = B;
    }

    B->mParent = A->mParent;
    A->mParent = B;
    B->mLeftChild = A;

    updateAfterRR(B);

    return B;
}

static inline void updateAfterLL(IPPS23RBBTN *node)
{
    IPPS23RBBTN *A = node->mRightChild;
    A->mLeftSize -= node->mLeftSize + 1;

    COLOR c = node->mColor;
    node->mColor = node->mRightChild->mColor;
    node->mRightChild->mColor = c;
}

static inline IPPS23RBBTN *LL(IPPS23RBBTN *A, IPPS23RBBTN *mNilSentinel)
{
    IPPS23RBBTN *B = A->mLeftChild;
    A->mLeftChild = B->mRightChild;

    if (ipps23rbbt_has_right_child(B, mNilSentinel))
    {
        B->mRightChild->mParent = A;
    }
    if (A->mParent->mLeftChild == A)
    {
        A->mParent->mLeftChild = B;
    }
    else
    {
        A->mParent->mRightChild = B;
    }

    B->mParent = A->mParent;
    A->mParent = B;
    B->mRightChild = A;

    updateAfterLL(B);
    return B;
}

static inline void put_bottom_up_pass(IPPS23RBBTN *mInOrderEnd, IPPS23RBBTN *deficientNode, IPPS23RBBTN *mNilSentinel)
{
    IPPS23RBBTN *parentNode, *siblingNode;
    while (1) // deficientNode->mColor is certainly BLACK
    {
        parentNode = deficientNode->mParent;
        if (parentNode->mColor == RED)
        {
            if (parentNode == parentNode->mParent->mLeftChild)
            {
                if (deficientNode == parentNode->mRightChild) // Rule (b.2)
                {
                    deficientNode = parentNode;
                    parentNode = RR(parentNode, mNilSentinel);
                }
                parentNode = LL(parentNode->mParent, mNilSentinel); // Rule (b.1)
            }
            else
            {
                if (deficientNode == parentNode->mLeftChild) // Rule (b.2)
                {
                    deficientNode = parentNode;
                    parentNode = LL(parentNode, mNilSentinel);
                }
                parentNode = RR(parentNode->mParent, mNilSentinel); // Rule (b.1)
            }
        }
        siblingNode = (deficientNode == parentNode->mLeftChild) ? parentNode->mRightChild : parentNode->mLeftChild;

        if (siblingNode->mColor == RED) // Rule (a.2)
        {
            siblingNode->mColor = BLACK;
            deficientNode = parentNode;
        }
        else if (parentNode->mColor == BLACK)
            break;
    }
    if (deficientNode != mInOrderEnd->mLeftChild)
    {
        deficientNode->mColor = RED; // Rule (a.1)
    } // x->mColor is certainly BLACK
}

static inline IPPS23RBBTN *getActualDeleteNode(IPPRBBT *tree, IPPS23RBBTN *theNode)
{
    IPPS23RBBTN *actualDeleteNode = theNode;
    if (ipps23rbbt_has_left_child(theNode, tree->mNilSentinel))
    {
        theNode->mLeftSize--;
        actualDeleteNode = theNode->mLeftChild;
        while (ipps23rbbt_has_right_child(actualDeleteNode, tree->mNilSentinel))
        {
            actualDeleteNode = actualDeleteNode->mRightChild;
        }
        PyObject *old_data = theNode->mData;
        theNode->mData = actualDeleteNode->mData;
        Py_XINCREF(theNode->mData);
        Py_XDECREF(old_data);
        if (ipps23rbbt_has_left_child(actualDeleteNode, tree->mNilSentinel))
        {
            PyObject *old_data = actualDeleteNode->mData;
            actualDeleteNode->mData = actualDeleteNode->mLeftChild->mData;
            Py_XINCREF(actualDeleteNode->mData);
            Py_XDECREF(old_data);

            actualDeleteNode->mLeftSize--;
            actualDeleteNode = actualDeleteNode->mLeftChild;
        }
        if (actualDeleteNode == tree->mFirstInOrderNode)
        {
            tree->mFirstInOrderNode = actualDeleteNode->mParent;
        }
    }
    else if (ipps23rbbt_has_right_child(theNode, tree->mNilSentinel))
    {
        actualDeleteNode = theNode->mRightChild;
        if (actualDeleteNode == tree->mLastInOrderNode)
        {
            tree->mLastInOrderNode = theNode;
        }
        PyObject *old_data = theNode->mData;
        theNode->mData = actualDeleteNode->mData;
        Py_XINCREF(theNode->mData);
        Py_XDECREF(old_data);
    }

    return actualDeleteNode;
}

static inline IPPS23RBBTN *deleteNodeAndGetParent(IPPRBBT *tree, IPPS23RBBTN *theNode)
{
    IPPS23RBBTN *theParent = theNode->mParent;

    if (theParent->mRightChild == theNode)
        theParent->mRightChild = tree->mNilSentinel;
    else
        theParent->mLeftChild = tree->mNilSentinel;

    ipps23rbbt_node_free(theNode);
    tree->mSize--;
    return theParent;
}

static inline IPPS23RBBTN *fixUp(IPPRBBT *tree, IPPS23RBBTN *x, IPPS23RBBTN *z)
{
    if (z->mLeftChild->mColor == RED || z->mRightChild->mColor == RED)
    {
        if (z == x->mRightChild)
        {
            if (z->mRightChild->mColor == BLACK) // Fixing rule (a)
                LL(z, tree->mNilSentinel);
            x = RR(x, tree->mNilSentinel); // Fixing rule (b)
        }
        else
        {
            if (z->mLeftChild->mColor == BLACK) // Fixing rule (a)
                RR(z, tree->mNilSentinel);
            x = LL(x, tree->mNilSentinel); // Fixing rule (b)
        }
        x->mLeftChild->mColor = BLACK;     // Fixing rule (c)
        x->mRightChild->mColor = BLACK;    // Fixing rule (c)
        x = tree->mInOrderEnd->mLeftChild; // terminate the bottom up pass
    }
    return x;
}

static inline IPPS23RBBTN *applyParitySeekingRules(IPPRBBT *tree, IPPS23RBBTN *x)
{
    IPPS23RBBTN *p = x->mParent;
    IPPS23RBBTN *y = x == p->mLeftChild ? p->mRightChild : p->mLeftChild;
    if (y->mColor == RED) // Parity-seeking Rule (c): Rotate to have a black sibling
        if (x == p->mLeftChild)
            RR(p, tree->mNilSentinel);
        else
            LL(p, tree->mNilSentinel);
    else
    { // Parity-seeking Rule (b): Make the sibling red
        y->mColor = RED;
        x = p;
        x = fixUp(tree, x, y);
    }
    return x;
}

static inline void remove_bottom_up_pass(IPPRBBT *tree)
{
    IPPS23RBBTN *x = tree->mNilSentinel;
    while (x != tree->mInOrderEnd->mLeftChild && x->mColor == BLACK)
    {
        x = applyParitySeekingRules(tree, x);
    }
    x->mColor = BLACK; // Parity-seeking Rule (a)
}

static inline void updateAfterDelete(IPPRBBT *tree, IPPS23RBBTN *parentNode)
{
    if ((ipps23rbbt_has_left_child(parentNode, tree->mNilSentinel) && !ipps23rbbt_has_right_child(parentNode, tree->mNilSentinel)) ||
        (!ipps23rbbt_has_left_child(parentNode, tree->mNilSentinel) && ipps23rbbt_has_right_child(parentNode, tree->mNilSentinel)))
    {
        tree->mNilSentinel->mParent = parentNode;
        remove_bottom_up_pass(tree);
        tree->mNilSentinel->mParent = 0;
    }
}

IPPRBBT *ipps23rbbt_new(void)
{
    IPPRBBT *tree = (IPPRBBT *)malloc(sizeof(IPPRBBT));
    if (!tree)
    {
        PyErr_NoMemory();
        return NULL;
    }

    tree->mSize = 0;
    tree->mGlobalLeftSize = 0;

    tree->mNilSentinel = ipps23rbbt_new_node(NULL);
    if (!tree->mNilSentinel)
    {
        free(tree);
        return NULL;
    }
    tree->mInOrderEnd = ipps23rbbt_new_node(NULL);
    if (!tree->mInOrderEnd)
    {
        ipps23rbbt_node_free(tree->mNilSentinel);
        free(tree);
        return NULL;
    }
    tree->mRevInOrderEnd = ipps23rbbt_new_node(NULL);
    if (!tree->mRevInOrderEnd)
    {
        ipps23rbbt_node_free(tree->mInOrderEnd);
        ipps23rbbt_node_free(tree->mNilSentinel);
        free(tree);
        return NULL;
    }

    tree->mRevInOrderEnd->mRightChild = tree->mInOrderEnd;
    tree->mRevInOrderEnd->mLeftChild = tree->mNilSentinel;

    tree->mInOrderEnd->mLeftChild = tree->mNilSentinel;
    tree->mInOrderEnd->mRightChild = tree->mNilSentinel;

    tree->mLastInOrderNode = tree->mInOrderEnd;
    tree->mFirstInOrderNode = tree->mInOrderEnd;

    tree->mRevInOrderEnd->mLeftSize = -1;
    tree->mInOrderEnd->mLeftSize = 0;

    return tree;
}

int ipps23rbbt_has_left_child(IPPS23RBBTN *node, IPPS23RBBTN *mNilSentinel) { return node->mLeftChild != mNilSentinel; }

int ipps23rbbt_has_right_child(IPPS23RBBTN *node, IPPS23RBBTN *mNilSentinel) { return node->mRightChild != mNilSentinel; }

static void DeleteSubtree(IPPS23RBBTN *node, IPPS23RBBTN *mNilSentinel)
{
    if (ipps23rbbt_has_left_child(node, mNilSentinel))
        DeleteSubtree(node->mLeftChild, mNilSentinel);
    if (ipps23rbbt_has_right_child(node, mNilSentinel))
        DeleteSubtree(node->mRightChild, mNilSentinel);
    ipps23rbbt_node_free(node);
}

void ipps23rbbt_free(IPPRBBT *tree)
{
    DeleteSubtree(tree->mRevInOrderEnd, tree->mNilSentinel);
    ipps23rbbt_node_free(tree->mNilSentinel);
    free(tree);
}

Py_ssize_t ipps23rbbt_size(IPPRBBT *tree) { return tree->mSize; }

int ipps23rbbt_is_empty(IPPRBBT *tree)
{
    return tree->mInOrderEnd->mLeftChild == tree->mNilSentinel;
}

void ipps23rbbt_insert_root_node(IPPRBBT *tree, PyObject *data)
{
    IPPS23RBBTN *root = ipps23rbbt_new_node(data);
    if (!root)
    {
        PyErr_NoMemory();
        return;
    }
    root->mParent = tree->mInOrderEnd;
    tree->mInOrderEnd->mLeftChild = root;

    root->mLeftChild = tree->mNilSentinel;
    root->mRightChild = tree->mNilSentinel;

    tree->mLastInOrderNode = root;
    tree->mFirstInOrderNode = root;

    tree->mGlobalLeftSize = 0;
    tree->mRevInOrderEnd->mLeftSize = -1;
    tree->mInOrderEnd->mLeftSize = 0;
    tree->mSize = 1;
    tree->mInOrderEnd->mLeftSize++;
}

void ipps23rbbt_insert_last_inorder_node(IPPRBBT *tree, PyObject *data)
{
    IPPS23RBBTN *childNode = ipps23rbbt_new_node(data);
    if (!childNode)
    {
        PyErr_NoMemory();
        return;
    }
    childNode->mParent = tree->mLastInOrderNode;
    childNode->mLeftChild = tree->mNilSentinel;
    childNode->mRightChild = tree->mNilSentinel;
    tree->mLastInOrderNode->mRightChild = childNode;
    tree->mSize++;
    tree->mLastInOrderNode = childNode;

    tree->mInOrderEnd->mLeftSize++;
    put_bottom_up_pass(tree->mInOrderEnd, childNode, tree->mNilSentinel);
}

void ipps23rbbt_insert_first_inorder_node(IPPRBBT *tree, PyObject *data)
{
    IPPS23RBBTN *childNode = ipps23rbbt_new_node(data);
    if (!childNode)
    {
        PyErr_NoMemory();
        return;
    }
    childNode->mParent = tree->mFirstInOrderNode;
    childNode->mLeftChild = tree->mNilSentinel;
    childNode->mRightChild = tree->mNilSentinel;
    tree->mFirstInOrderNode->mLeftChild = childNode;
    tree->mSize++;
    tree->mFirstInOrderNode = childNode;

    tree->mGlobalLeftSize++;

    tree->mFirstInOrderNode->mLeftSize -= tree->mGlobalLeftSize;
    put_bottom_up_pass(tree->mInOrderEnd, childNode, tree->mNilSentinel);
}

void ipps23rbbt_insert_left_child(IPPRBBT *tree, IPPS23RBBTN *parentNode, PyObject *data)
{
    IPPS23RBBTN *childNode = ipps23rbbt_new_node(data);
    if (!childNode)
    {
        PyErr_NoMemory();
        return;
    }
    childNode->mParent = parentNode;
    childNode->mLeftChild = tree->mNilSentinel;
    childNode->mRightChild = tree->mNilSentinel;
    parentNode->mLeftChild = childNode;
    tree->mSize++;
    put_bottom_up_pass(tree->mInOrderEnd, childNode, tree->mNilSentinel);
}

void ipps23rbbt_insert_right_child(IPPRBBT *tree, IPPS23RBBTN *parentNode, PyObject *data)
{
    IPPS23RBBTN *childNode = ipps23rbbt_new_node(data);
    if (!childNode)
    {
        PyErr_NoMemory();
        return;
    }
    childNode->mParent = parentNode;
    childNode->mLeftChild = tree->mNilSentinel;
    childNode->mRightChild = tree->mNilSentinel;
    parentNode->mRightChild = childNode;
    tree->mSize++;
    put_bottom_up_pass(tree->mInOrderEnd, childNode, tree->mNilSentinel);
}

void ipps23rbbt_delete_node(IPPRBBT *tree, IPPS23RBBTN *theNode)
{
    IPPS23RBBTN *actualDeleteNode = getActualDeleteNode(tree, theNode);

    IPPS23RBBTN *theParent = deleteNodeAndGetParent(tree, actualDeleteNode);
    updateAfterDelete(tree, theParent);
}

void ipps23rbbt_delete_last_inorder_node(IPPRBBT *tree)
{
    IPPS23RBBTN *actualDeleteNode = getActualDeleteNode(tree, tree->mLastInOrderNode);

    tree->mInOrderEnd->mLeftSize--;

    IPPS23RBBTN *theParent = deleteNodeAndGetParent(tree, actualDeleteNode);
    tree->mLastInOrderNode = theParent;

    updateAfterDelete(tree, tree->mLastInOrderNode);
}

void ipps23rbbt_delete_first_inorder_node(IPPRBBT *tree)
{
    IPPS23RBBTN *actualDeleteNode = getActualDeleteNode(tree, tree->mFirstInOrderNode);
    if (actualDeleteNode != tree->mFirstInOrderNode)
    {
        tree->mFirstInOrderNode->mLeftSize++;
    }

    tree->mGlobalLeftSize--;

    IPPS23RBBTN *theParent = deleteNodeAndGetParent(tree, actualDeleteNode);
    tree->mFirstInOrderNode = theParent;

    updateAfterDelete(tree, tree->mFirstInOrderNode);
}
