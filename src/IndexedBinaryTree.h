// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T, class IBTN>
class IndexedBinaryTree : virtual public BinaryTree<T, IBTN>
{
public:
	IndexedBinaryTree(void) : BinaryTree<T, IBTN>()
	{
		this->mInOrderEnd->mLeftSize = 0;
		this->mPostOrderEnd->mLeftSize = -1;
	}

	virtual ~IndexedBinaryTree(void) {}

	virtual void updateAfterInsert(IBTN *node)
	{
		updateLeftSize(node, 1);
	}

	virtual void updateBeforeDelete(IBTN *node) { updateLeftSize(node, -1); }

	virtual int getLeftSize(const typename BinaryTree<T, IBTN>::BinaryTreeNode &node)
	{
		return this->getActualNode(node)->getLeftSize();
	}

protected:
	void updateLeftSize(IBTN *iNode, int diff)
	{
		while (iNode->mParent)
		{
			if (iNode == iNode->mParent->mLeftChild)
				iNode->mParent->mLeftSize += diff;
			iNode = iNode->mParent;
		}
	}
};
