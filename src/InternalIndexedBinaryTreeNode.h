// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class IndexedBinaryTree;

template <class T, class IBTN>
class InternalIndexedBinaryTreeNode : virtual public InternalBinaryTreeNode<T, IBTN>
{
public:
	InternalIndexedBinaryTreeNode(void) : InternalBinaryTreeNode<T, IBTN>()
	{
		this->mLeftSize = 0;
	}

	virtual ~InternalIndexedBinaryTreeNode(void)
	{
	}

	virtual int getLeftSize()
	{
		return this->mLeftSize;
	}

	friend class IndexedBinaryTree<T, IBTN>;

protected:
	int mLeftSize;
};
