// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class PureParitySeeking23RedBlackBinaryTree;

template <class T, class IBTN>
class InternalPureParitySeeking23RedBlackBinaryTreeNode : public InternalInOrderPreservingBinaryTreeNode<T, IBTN>
{
protected:
    enum COLOR
    {
        RED = 0,
        BLACK = 1
    };
    enum COLOR mColor;

public:
    InternalPureParitySeeking23RedBlackBinaryTreeNode(void) : InternalInOrderPreservingBinaryTreeNode<T, IBTN>()
    {
        this->mColor = BLACK;
    }

    virtual ~InternalPureParitySeeking23RedBlackBinaryTreeNode(void) {}

    virtual COLOR getColor() const
    {
        return this->mColor;
    }

    friend class PureParitySeeking23RedBlackBinaryTree<T, IBTN>;
};