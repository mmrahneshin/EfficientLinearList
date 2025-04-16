// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode
{
private:
	enum COLOR
	{
		RED = 0,
		BLACK = 1
	};

public:
	BinaryTreeNode(void)
	{
		this->mLeftChild = 0;
		this->mRightChild = 0;
		this->mParent = 0;
		this->mLeftSize = 0;
		this->mColor = BLACK;
	}

	virtual ~BinaryTreeNode(void)
	{
	}

	virtual T &getData()
	{
		return this->mData;
	}

	virtual BinaryTreeNode *getLeftChild()
	{
		return this->mLeftChild;
	}

	virtual BinaryTreeNode *getRightChild()
	{
		return this->mRightChild;
	}

	virtual BinaryTreeNode *getParent()
	{
		return this->mParent;
	}

	virtual int getLeftSize()
	{
		return this->mLeftSize;
	}

	virtual COLOR getColor() const
	{
		return this->mColor;
	}

	enum COLOR mColor;
	T mData;
	int mLeftSize;
	BinaryTreeNode *mLeftChild;
	BinaryTreeNode *mRightChild;
	BinaryTreeNode *mParent;
};
