// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class InOrderPreservingBinaryTree;

template <class T, class IBTN>
class InternalInOrderPreservingBinaryTreeNode : virtual public InternalBinaryTreeNode<T, IBTN>
{
public:
    InternalInOrderPreservingBinaryTreeNode(void) : InternalBinaryTreeNode<T, IBTN>() {}

    virtual ~InternalInOrderPreservingBinaryTreeNode(void) {}

    friend class InOrderPreservingBinaryTree<T, IBTN>;
};