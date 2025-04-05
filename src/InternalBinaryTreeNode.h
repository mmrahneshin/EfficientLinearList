// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T, class IBTN>
class BinaryTree;

template <class T, class IBTN>
class InternalBinaryTreeNode
{
public:
	InternalBinaryTreeNode(void)
	{
		this->mLeftChild = 0;
		this->mRightChild = 0;
		this->mParent = 0;
	}

	virtual ~InternalBinaryTreeNode(void)
	{
	}

	virtual T &getData()
	{
		return this->mData;
	}

	virtual IBTN *getLeftChild()
	{
		return this->mLeftChild;
	}

	virtual IBTN *getRightChild()
	{
		return this->mRightChild;
	}

	virtual IBTN *getParent()
	{
		return this->mParent;
	}

	friend class BinaryTree<T, IBTN>;

protected:
	T mData;
	IBTN *mLeftChild;
	IBTN *mRightChild;
	IBTN *mParent;
};
