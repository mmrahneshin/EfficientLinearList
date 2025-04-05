// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

template <class T>
class EfficientLinearList
{
public:
	typedef IndexedPPS23RedBlackBinaryTree<T, InternalIndexedPPS23RedBlackBinaryTreeNode<T>> BT;

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
		if (idx < 0 || idx > this->size())
		{
			throw std::runtime_error("out_of_range");
		}

		typename BT::BinaryTreeNode node = getNode(idx);
		if (!mIPPS23RBbt->hasLeftChild(node))
		{
			mIPPS23RBbt->insertLeftChild(node, data);
		}
		else
		{
			node = node.getLeftChild();
			while (mIPPS23RBbt->hasRightChild(node))
				node = node.getRightChild();
			mIPPS23RBbt->insertRightChild(node, data);
		}
	}

	virtual T &operator[](const int &idx)
	{
		typename BT::BinaryTreeNode node = getNode(idx);
		return node.getData();
	}

	virtual void remove(const int &idx)
	{
		if (idx < 0 || idx >= this->size())
		{
			throw std::runtime_error("out_of_range");
		}

		typename BT::BinaryTreeNode node = getNode(idx);
		mIPPS23RBbt->deleteNode(node);
	}

	virtual int size() const
	{
		return mIPPS23RBbt->size();
	};

	virtual int depth() const
	{
		return mIPPS23RBbt->depthCalc(mIPPS23RBbt->getRootNode(), 1);
	};

	virtual void drawTree()
	{
		mIPPS23RBbt->draw(cout);
	}

	void iterateInOrder()
	{
		typename BT::InOrderIterator itrInOrder = mIPPS23RBbt->inOrderBegin();
		typename BT::InOrderIterator endInOrder = mIPPS23RBbt->inOrderEnd();

		while (itrInOrder != endInOrder)
		{
			cout << "left size: " << mIPPS23RBbt->getLeftSize(itrInOrder.getBinaryTreeNode())
				 << " / value: " << *itrInOrder << "   ";
			++itrInOrder;
		}
		cout << endl;
	}

private:
	virtual typename BT::BinaryTreeNode getNode(int idx)
	{
		typename BT::BinaryTreeNode node = mIPPS23RBbt->getHeaderRootNode();
		while (mIPPS23RBbt->getLeftSize(node) != idx)
		{
			if (idx < mIPPS23RBbt->getLeftSize(node))
			{
				node = node.getLeftChild();
			}
			else
			{
				idx = idx - mIPPS23RBbt->getLeftSize(node) - 1;
				node = node.getRightChild();
			}
		}

		return node;
	}

protected:
	BT *mIPPS23RBbt;
};
