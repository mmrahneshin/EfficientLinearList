// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class PureParitySeeking23RedBlackBinaryTree : public InOrderPreservingBinaryTree<T, IBTN>
{
    typedef InternalPureParitySeeking23RedBlackBinaryTreeNode<T, IBTN> IPSRBBTN;

public:
    PureParitySeeking23RedBlackBinaryTree(void) : InOrderPreservingBinaryTree<T, IBTN>() {}
    virtual ~PureParitySeeking23RedBlackBinaryTree(void) {}

protected:
    virtual void updateAfterInsert(IBTN *newNode) override
    {
        put_bottom_up_pass(newNode);
    }

    virtual void put_bottom_up_pass(IBTN *deficientNode)
    {
        IBTN *parentNode, *siblingNode;
        while (true) // deficientNode->mColor is certainly BLACK
        {
            parentNode = deficientNode->mParent;
            if (parentNode->mColor == IPSRBBTN::RED)
            {
                if (parentNode == parentNode->mParent->mLeftChild)
                {
                    if (deficientNode == parentNode->mRightChild) // Rule (b.2)
                    {
                        deficientNode = parentNode;
                        parentNode = this->RR(parentNode);
                    }
                    parentNode = this->LL(parentNode->mParent); // Rule (b.1)
                }
                else
                {
                    if (deficientNode == parentNode->mLeftChild) // Rule (b.2)
                    {
                        deficientNode = parentNode;
                        parentNode = this->LL(parentNode);
                    }
                    parentNode = this->RR(parentNode->mParent); // Rule (b.1)
                }
            }
            siblingNode = (deficientNode == parentNode->mLeftChild) ? parentNode->mRightChild : parentNode->mLeftChild;
            if (siblingNode->mColor == IPSRBBTN::RED) // Rule (a.2)
            {
                siblingNode->mColor = IPSRBBTN::BLACK;
                deficientNode = parentNode;
            }
            else if (parentNode->mColor == IPSRBBTN::BLACK)
                break;
        }
        if (deficientNode != this->mInOrderEnd->mLeftChild) // x->mColor is certainly BLACK
            deficientNode->mColor = IPSRBBTN::RED;          // Rule (a.1)
    }

    virtual void updateBeforeDelete(IBTN *node) override
    {
        IBTN *parentNode = node->mParent;
        this->mNilSentinel->mParent = parentNode;
        if (node->mLeftChild != this->mNilSentinel || node->mRightChild != this->mNilSentinel)
        {
            IBTN *theChild = (node->mLeftChild != this->mNilSentinel) ? node->mLeftChild : node->mRightChild;
            theChild->mColor = IPSRBBTN::BLACK;
        }
    }

    virtual void updateAfterDelete(IBTN *parentNode) override
    {
        if ((parentNode->mLeftChild != this->mNilSentinel && parentNode->mRightChild == this->mNilSentinel) ||
            (parentNode->mLeftChild == this->mNilSentinel && parentNode->mRightChild != this->mNilSentinel))
        {
            remove_bottom_up_pass(this->mNilSentinel);
        }
        this->mNilSentinel->mParent = 0;
    }

    virtual void deleteDeg2Node(IBTN *node) override
    {
        IBTN *actualDeleteNode = this->getActualDeleteNode(node);
        node->mData = actualDeleteNode->mData; // از استاد در مورد جایگاه این کد پرسیده شود
        this->deleteNode(actualDeleteNode, actualDeleteNode->mParent);
    }

    void remove_bottom_up_pass(IBTN *x)
    {
        while (x != this->mInOrderEnd->mLeftChild && x->mColor == IPSRBBTN::BLACK)
        {
            x = applyParitySeekingRules(x);
        }
        x->mColor = IPSRBBTN::BLACK; // Parity-seeking Rule (a)
    }

    IBTN *applyParitySeekingRules(IBTN *x)
    {
        IBTN *p = x->mParent;
        IBTN *y = x == p->mLeftChild ? p->mRightChild : p->mLeftChild;
        if (y->mColor == IPSRBBTN::RED) // Parity-seeking Rule (c): Rotate to have a black sibling
            if (x == p->mLeftChild)
                this->RR(p);
            else
                this->LL(p);
        else
        { // Parity-seeking Rule (b): Make the sibling red
            y->mColor = IPSRBBTN::RED;
            x = p;
            x = fixUp(x, y);
        }
        return x;
    }

    IBTN *fixUp(IBTN *x, IBTN *z)
    {
        if (z->mLeftChild->mColor == IPSRBBTN::RED || z->mRightChild->mColor == IPSRBBTN::RED)
        {
            if (z == x->mRightChild)
            {
                if (z->mRightChild->mColor == IPSRBBTN::BLACK) // Fixing rule (a)
                    this->LL(z);
                x = this->RR(x); // Fixing rule (b)
            }
            else
            {
                if (z->mLeftChild->mColor == IPSRBBTN::BLACK) // Fixing rule (a)
                    this->RR(z);
                x = this->LL(x); // Fixing rule (b)
            }
            x->mLeftChild->mColor = IPSRBBTN::BLACK;  // Fixing rule (c)
            x->mRightChild->mColor = IPSRBBTN::BLACK; // Fixing rule (c)
            x = this->mInOrderEnd->mLeftChild;        // terminate the bottom up pass
        }
        return x;
    }

    virtual void updateAfterLL(IBTN *node) override
    {
        typename IPSRBBTN::COLOR c = node->mColor;
        node->mColor = node->mRightChild->mColor;
        node->mRightChild->mColor = c;
    }

    virtual void updateAfterRR(IBTN *node) override
    {
        typename IPSRBBTN::COLOR c = node->mColor;
        node->mColor = node->mLeftChild->mColor;
        node->mLeftChild->mColor = c;
    }

    int testAmountOfBlackNode(IBTN *root, int depth)
    {
        int rightBlack = 0;
        int leftBlack = 0;

        if (root->mRightChild == this->mNilSentinel && root->mLeftChild != this->mNilSentinel)
        {
            return root->mColor == IPSRBBTN::BLACK ? 1 : 0;
        }

        if (root->mRightChild != this->mNilSentinel)
        {
            int temp = testAmountOfBlackNode(root->mRightChild, depth + 1);
            if (temp == -1)
            {
                return -1;
            }
            rightBlack += temp;
        }

        if (root->mLeftChild != this->mNilSentinel)
        {
            int temp = testAmountOfBlackNode(root->mLeftChild, depth + 1);
            if (temp == -1)
            {
                return -1;
            }
            leftBlack += temp;
        }

        if (rightBlack != leftBlack)
        {
            return -1;
        }

        return root->mColor == IPSRBBTN::BLACK ? rightBlack + 1 : rightBlack;
    }

public:
    bool testAmountOfBlackNode(const typename BinaryTree<T, IBTN>::BinaryTreeNode &node, int depth)
    {
        if (this->mSize == 0)
        {
            return 0;
        }
        int temp = testAmountOfBlackNode(this->getActualNode(node), depth);
        std::cout << temp << std::endl;
        return temp == -1 ? false : true;
    }

    int getColor(const typename BinaryTree<T, IBTN>::BinaryTreeNode &node)
    {
        return this->getActualNode(node)->getColor();
    }
};
