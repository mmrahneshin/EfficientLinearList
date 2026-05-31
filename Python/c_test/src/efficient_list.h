#ifndef EFFICIENT_LIST_H
#define EFFICIENT_LIST_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "indexed_PPS23RB_binaryTree.h"

    typedef struct EfficientLinearList
    {
        IPPRBBT *mIPPS23RBbt;
    } EfficientLinearList;

    EfficientLinearList *efficient_list_new(void)
    {
        EfficientLinearList *el = (EfficientLinearList *)malloc(sizeof(EfficientLinearList));
        if (!el)
        {
            return nullptr;
        }

        el->mIPPS23RBbt = ipps23rbbt_new();
        if (!el->mIPPS23RBbt)
        {
            return nullptr;
        }

        return el;
    }

    void efficient_list_free(EfficientLinearList *el)
    {
        ipps23rbbt_free(el->mIPPS23RBbt);
        free(el);
    }

    static inline IPPS23RBBTN *getNodeWithUpdateLeftSize(IPPRBBT *mIPPS23RBbt, int idx, int status)
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

    void efficient_list_insert(EfficientLinearList *el, int idx, int data)
    {
        IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
        if (idx < 0 || idx > mIPPS23RBbt->mSize)
        {
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

    void efficient_list_remove(EfficientLinearList *el, int idx)
    {
        IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
        if (idx < 0 || idx >= mIPPS23RBbt->mSize)
        {
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

    int efficient_list_get_item(EfficientLinearList *el, int idx)
    {
        IPPRBBT *mIPPS23RBbt = el->mIPPS23RBbt;
        if (idx < 0 || idx >= mIPPS23RBbt->mSize)
        {
            return -1;
        }
        IPPS23RBBTN *node = getNodeWithUpdateLeftSize(mIPPS23RBbt, idx, 0);

        return node->mData;
    }

    int efficient_list_size(EfficientLinearList *el)
    {
        return el->mIPPS23RBbt->mSize;
    }

#ifdef __cplusplus
}
#endif
#endif
