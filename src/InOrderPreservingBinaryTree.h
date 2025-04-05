// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class InOrderPreservingBinaryTree : virtual public BinaryTree<T, IBTN>
{
public:
    InOrderPreservingBinaryTree(void) : BinaryTree<T, IBTN>() {}
    virtual ~InOrderPreservingBinaryTree(void) {}

protected:
    IBTN *RR(IBTN *A)
    {
        // write your code here
        IBTN *B = A->mRightChild;
        A->mRightChild = B->mLeftChild;

        if (B->mLeftChild != 0)
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

    virtual void updateAfterRR(IBTN *node) = 0;

    IBTN *LL(IBTN *A)
    {
        // write your code here
        IBTN *B = A->mLeftChild;
        A->mLeftChild = B->mRightChild;

        if (B->mRightChild != 0)
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

    virtual void updateAfterLL(IBTN *node) = 0;

    IBTN *getActualDeleteNode(IBTN *node)
    {
        IBTN *actualDeleteNode = node->mLeftChild;
        while (actualDeleteNode->mRightChild != this->mNilSentinel)
        {
            actualDeleteNode = actualDeleteNode->mRightChild;
        }
        return actualDeleteNode;
    }

    IBTN *LR(IBTN *A)
    {
        // wirte your code here
        IBTN *B = A->mLeftChild;
        RR(B);
        return LL(A);
    }

    IBTN *RL(IBTN *A)
    {
        // wirte your code here
        IBTN *B = A->mRightChild;
        LL(B);
        return RR(A);
    }
};
