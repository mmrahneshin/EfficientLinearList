// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class IndexedPPS23RedBlackBinaryTree;

template <class T>
class InternalIndexedPPS23RedBlackBinaryTreeNode
    : public InternalIndexedBinaryTreeNode<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>>,
      public InternalPureParitySeeking23RedBlackBinaryTreeNode<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>>
{
public:
  InternalIndexedPPS23RedBlackBinaryTreeNode(void)
      : InternalIndexedBinaryTreeNode<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>>(),
        InternalPureParitySeeking23RedBlackBinaryTreeNode<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>>() {}

  virtual ~InternalIndexedPPS23RedBlackBinaryTreeNode(void) {}

  friend class IndexedPPS23RedBlackBinaryTree<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>>;
};