// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T, class IBTN>
class IndexedPPS23RedBlackBinaryTree
    : public IndexedBinaryTree<T, IBTN>,
      public PureParitySeeking23RedBlackBinaryTree<T, IBTN>
{
public:
  IndexedPPS23RedBlackBinaryTree(void)
      : IndexedBinaryTree<T, IBTN>(),
        PureParitySeeking23RedBlackBinaryTree<T, IBTN>() {}

  virtual ~IndexedPPS23RedBlackBinaryTree(void) {}

  virtual void deleteNode(const typename BinaryTree<T, IBTN>::BinaryTreeNode &node)
  {
    BinaryTree<T, IBTN>::deleteNode(this->getActualNode(node), this->getActualNode(node)->mParent);
  }

protected:
  void updateAfterInsert(IBTN *newNode) override
  {
    IndexedBinaryTree<T, IBTN>::updateAfterInsert(newNode);
    PureParitySeeking23RedBlackBinaryTree<T, IBTN>::updateAfterInsert(newNode);
  }

  void updateBeforeDelete(IBTN *node) override
  {
    IndexedBinaryTree<T, IBTN>::updateBeforeDelete(node);
    PureParitySeeking23RedBlackBinaryTree<T, IBTN>::updateBeforeDelete(node);
  }

  void updateAfterLL(IBTN *node) override
  { // node is B and C is the B's rightChild before the rotation
    IBTN *A = node->mRightChild;
    IBTN *C = A->mLeftChild;
    A->mLeftSize = 0;

    while (C != this->mNilSentinel)
    {
      A->mLeftSize += C->mLeftSize + 1;
      C = C->mRightChild;
    }

    PureParitySeeking23RedBlackBinaryTree<T, IBTN>::updateAfterLL(node);
  }

  void updateAfterRR(IBTN *node) override
  { // node is B and C is the B's leftChild before the rotation
    IBTN *A = node->mLeftChild;
    node->mLeftSize += A->mLeftSize + 1; // B->mLeftSize = [C->mLeftSize + 1](is B->mLeftSize) + A->mLeftSize + 1

    PureParitySeeking23RedBlackBinaryTree<T, IBTN>::updateAfterRR(node);
  }
};
