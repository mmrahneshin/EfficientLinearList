// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T>
class EfficientLinearList
{
public:
	typedef IndexedPPS23RedBlackBinaryTree<T> BT;
	typedef IndexedPPS23RBBinaryTreeNode<T> IPPS23RBBTN;

	EfficientLinearList(void)
	{
		mIPPS23RBbt = new BT();
	}

	virtual ~EfficientLinearList(void)
	{
		delete mIPPS23RBbt;
	}

public:
	virtual void insert(const int &idx, const T &data)
	{
		if (idx < 0 || idx > mIPPS23RBbt->size())
		{
			throw std::runtime_error("out_of_range");
		}

		if (idx == mIPPS23RBbt->size())
		{
			mIPPS23RBbt->insertLastInOrderNode(data);
			return;
		}

		IPPS23RBBTN *node = getNode(idx);
		if (!mIPPS23RBbt->hasLeftChild(node))
		{
			mIPPS23RBbt->insertLeftChild(node, data);
		}
		else
		{
			node = node->mLeftChild;
			while (mIPPS23RBbt->hasRightChild(node))
				node = node->mRightChild;
			mIPPS23RBbt->insertRightChild(node, data);
		}
	}

	virtual T &operator[](const int &idx)
	{
		IPPS23RBBTN *node = getNode(idx);
		return node->mData;
	}

	virtual void remove(const int &idx)
	{
		if (idx < 0 || idx >= mIPPS23RBbt->size())
		{
			throw std::runtime_error("out_of_range");
		}

		if (idx == mIPPS23RBbt->size() - 1)
		{
			mIPPS23RBbt->deleteLastInOrderNode();
			return;
		}

		IPPS23RBBTN *node = getNode(idx);
		mIPPS23RBbt->deleteNode(node);
	}

	virtual int size() const
	{
		return mIPPS23RBbt->size();
	};

	// virtual int depth() const
	// {
	// 	return mIPPS23RBbt->depthCalc(mIPPS23RBbt->getRootNode(), 1);
	// };
	// virtual void drawTree()
	// {
	// 	mIPPS23RBbt->draw(cout);
	// }
	// void iterateInOrder()
	// {
	// 	typename BT::InOrderIterator itrInOrder = mIPPS23RBbt->inOrderBegin();
	// 	typename BT::InOrderIterator endInOrder = mIPPS23RBbt->inOrderEnd();
	// 	while (itrInOrder != endInOrder)
	// 	{
	// 		cout << "left size: " << itrInOrder.getBinaryTreeNode()->mLeftSize
	// 			 << " / value: " << *itrInOrder << "   ";
	// 		++itrInOrder;
	// 	}
	// 	cout << endl;
	// }

private:
	virtual IPPS23RBBTN *getNode(int idx)
	{
		IPPS23RBBTN *node = mIPPS23RBbt->mInOrderEnd;
		while (node->mLeftSize != idx)
		{
			if (idx < node->mLeftSize)
			{
				node = node->mLeftChild;
			}
			else
			{
				idx = idx - node->mLeftSize - 1;
				node = node->mRightChild;
			}
		}

		return node;
	}

	BT *mIPPS23RBbt;
};
