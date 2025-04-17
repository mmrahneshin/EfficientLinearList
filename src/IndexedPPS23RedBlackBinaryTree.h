// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T>
class IndexedPPS23RedBlackBinaryTree
{
	typedef IndexedPPS23RBBinaryTreeNode<T> IPPS23RBBTN;

public:
	//
	IPPS23RBBTN *mInOrderPreBegin;
	IPPS23RBBTN *mPostOrderPreBegin;
	IPPS23RBBTN *mRevInOrderPreBegin;
	IPPS23RBBTN *mPreOrderPreBegin;
	IPPS23RBBTN *mRevPreOrderPreBegin;
	IPPS23RBBTN *mRevPostOrderPreBegin;

	IPPS23RBBTN *mRevInOrderEnd;
	IPPS23RBBTN *mRevPostOrderEnd;
	IPPS23RBBTN *mInOrderEnd;
	IPPS23RBBTN *mRevPreOrderEnd;
	IPPS23RBBTN *mPreOrderEnd;
	IPPS23RBBTN *mPostOrderEnd;
	IPPS23RBBTN *mNilSentinel;
	IPPS23RBBTN *mLastInOrderNode;
	int mSize;

	IndexedPPS23RedBlackBinaryTree(void)
	{
		mSize = 0;
		mNilSentinel = new IPPS23RBBTN;
		mRevInOrderEnd = new IPPS23RBBTN;
		mRevPostOrderEnd = new IPPS23RBBTN;
		mInOrderEnd = new IPPS23RBBTN;
		mRevPreOrderEnd = mRevPostOrderEnd;
		mPreOrderEnd = new IPPS23RBBTN;
		mPostOrderEnd = mRevInOrderEnd;

		mRevPostOrderEnd->mParent = mRevInOrderEnd;
		mRevPostOrderEnd->mLeftChild = mNilSentinel;
		mRevPostOrderEnd->mRightChild = mNilSentinel;

		mRevInOrderEnd->mLeftChild = mRevPostOrderEnd;
		mRevInOrderEnd->mRightChild = mNilSentinel;
		mRevInOrderEnd->mParent = mInOrderEnd;

		mInOrderEnd->mRightChild = mPreOrderEnd;
		mInOrderEnd->mLeftChild = mRevInOrderEnd;

		mPreOrderEnd->mParent = mInOrderEnd;
		mPreOrderEnd->mLeftChild = mNilSentinel;
		mPreOrderEnd->mRightChild = mNilSentinel;

		mInOrderPreBegin = mRevInOrderEnd;
		mPostOrderPreBegin = mRevPostOrderEnd;
		mRevInOrderPreBegin = mInOrderEnd;
		mPreOrderPreBegin = mRevPreOrderEnd;
		mRevPreOrderPreBegin = mPreOrderEnd;
		mRevPostOrderPreBegin = mPostOrderEnd;

		mLastInOrderNode = mPostOrderEnd;

		mInOrderEnd->mLeftSize = 0;
		mPostOrderEnd->mLeftSize = -1;
	}

	// caution: don't interpret virtual destructor as an ordinary virtual function!
	virtual ~IndexedPPS23RedBlackBinaryTree(void)
	{
		DeleteSubtree(mInOrderEnd);
		delete mNilSentinel;
	}

	int size() { return mSize; }
	void DeleteSubtree(IPPS23RBBTN *node)
	{
		if (node->mLeftChild != mNilSentinel)
			DeleteSubtree(node->mLeftChild);
		if (node->mRightChild != mNilSentinel)
			DeleteSubtree(node->mRightChild);
		delete node;
	}

	bool isEmpty()
	{
		return mPostOrderEnd->mRightChild == mNilSentinel;
	}

	virtual bool hasLeftChild(IPPS23RBBTN *node) const { return node->mLeftChild != mNilSentinel; }

	virtual bool hasRightChild(IPPS23RBBTN *node) const { return node->mRightChild != mNilSentinel; }

	virtual void insertLastInOrderNode(T data)
	{
		IPPS23RBBTN *childNode = new IPPS23RBBTN;
		childNode->mData = data;
		childNode->mParent = mLastInOrderNode;
		childNode->mLeftChild = mNilSentinel;
		childNode->mRightChild = mNilSentinel;
		mLastInOrderNode->mRightChild = childNode;
		mSize++;
		mLastInOrderNode = childNode;

		// IndexedBT updateAfterInsert(node);
		mInOrderEnd->mLeftSize++;
		// PPS23RB updateAfterInsert(node);
		put_bottom_up_pass(childNode);
	}
	// error if a left child already exists.
	virtual void insertLeftChild(IPPS23RBBTN *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mLeftChild == mNilSentinel)
			{
				IPPS23RBBTN *childNode = new IPPS23RBBTN;
				childNode->mData = data;
				childNode->mParent = parentNode;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentNode->mLeftChild = childNode;
				mSize++;
				updateAfterInsert(childNode);
			}
			else
				throw std::runtime_error("Can't insert a left child for a node which already has a left child.");
		}
		else
			throw std::runtime_error("Invalid Pointer.");
	}

	// error if a right child already exists.
	virtual void insertRightChild(IPPS23RBBTN *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mRightChild == mNilSentinel)
			{
				IPPS23RBBTN *childNode = new IPPS23RBBTN;
				childNode->mData = data;
				childNode->mParent = parentNode;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentNode->mRightChild = childNode;
				mSize++;
				updateAfterInsert(childNode);
			}
			else
				throw std::runtime_error("Can't insert a right child for a node which already has a right child.");
		}
		else
			throw std::runtime_error("Invalid Pointer.");
	}

	void updateLeftSize(IPPS23RBBTN *iNode, int diff)
	{
		while (iNode->mParent)
		{
			if (iNode == iNode->mParent->mLeftChild)
				iNode->mParent->mLeftSize += diff;
			iNode = iNode->mParent;
		}
	}

	virtual void updateAfterRR(IPPS23RBBTN *node)
	{
		// IndexedPPS23RB updateAfterRR(node);
		IPPS23RBBTN *A = node->mLeftChild;
		node->mLeftSize += A->mLeftSize + 1; // B->mLeftSize = [C->mLeftSize + 1](is B->mLeftSize) + A->mLeftSize + 1

		// PPS23RB updateAfterRR(node);
		typename IPPS23RBBTN::COLOR c = node->mColor;
		node->mColor = node->mLeftChild->mColor;
		node->mLeftChild->mColor = c;
	}

	IPPS23RBBTN *RR(IPPS23RBBTN *A)
	{
		// write your code here
		IPPS23RBBTN *B = A->mRightChild;
		A->mRightChild = B->mLeftChild;

		if (B->mLeftChild != 0)
		{
			B->mLeftChild->mParent = A;
		}

		if (A->mParent->mLeftChild == A)
		{
			A->mParent->mLeftChild = B;
		}
		else
		{
			A->mParent->mRightChild = B;
		}

		B->mParent = A->mParent;
		A->mParent = B;
		B->mLeftChild = A;

		updateAfterRR(B);

		return B;
	}

	virtual void updateAfterLL(IPPS23RBBTN *node)
	{
		// IndexedPPS23RB updateAfterLL(node);
		IPPS23RBBTN *A = node->mRightChild;
		IPPS23RBBTN *C = A->mLeftChild;
		A->mLeftSize = 0;

		while (C != this->mNilSentinel)
		{
			A->mLeftSize += C->mLeftSize + 1;
			C = C->mRightChild;
		}

		// PPS23RB updateAfterLL(node);
		typename IPPS23RBBTN::COLOR c = node->mColor;
		node->mColor = node->mRightChild->mColor;
		node->mRightChild->mColor = c;
	}

	IPPS23RBBTN *LL(IPPS23RBBTN *A)
	{
		// write your code here
		IPPS23RBBTN *B = A->mLeftChild;
		A->mLeftChild = B->mRightChild;

		if (B->mRightChild != 0)
		{
			B->mRightChild->mParent = A;
		}
		if (A->mParent->mLeftChild == A)
		{
			A->mParent->mLeftChild = B;
		}
		else
		{
			A->mParent->mRightChild = B;
		}

		B->mParent = A->mParent;
		A->mParent = B;
		B->mRightChild = A;

		updateAfterLL(B);
		return B;
	}

	IPPS23RBBTN *getActualDeleteNode(IPPS23RBBTN *node)
	{
		IPPS23RBBTN *actualDeleteNode = node->mLeftChild;
		while (actualDeleteNode->mRightChild != this->mNilSentinel)
		{
			actualDeleteNode = actualDeleteNode->mRightChild;
		}
		return actualDeleteNode;
	}

	virtual void put_bottom_up_pass(IPPS23RBBTN *deficientNode)
	{
		IPPS23RBBTN *parentNode, *siblingNode;
		while (true) // deficientNode->mColor is certainly BLACK
		{
			parentNode = deficientNode->mParent;
			if (parentNode->mColor == IPPS23RBBTN::RED)
			{
				if (parentNode == parentNode->mParent->mLeftChild)
				{
					if (deficientNode == parentNode->mRightChild) // Rule (b.2)
					{
						deficientNode = parentNode;
						parentNode = this->RR(parentNode);
					}
					parentNode = this->LL(parentNode->mParent); // Rule (b.1)
				}
				else
				{
					if (deficientNode == parentNode->mLeftChild) // Rule (b.2)
					{
						deficientNode = parentNode;
						parentNode = this->LL(parentNode);
					}
					parentNode = this->RR(parentNode->mParent); // Rule (b.1)
				}
			}
			siblingNode = (deficientNode == parentNode->mLeftChild) ? parentNode->mRightChild : parentNode->mLeftChild;
			if (siblingNode->mColor == IPPS23RBBTN::RED) // Rule (a.2)
			{
				siblingNode->mColor = IPPS23RBBTN::BLACK;
				deficientNode = parentNode;
			}
			else if (parentNode->mColor == IPPS23RBBTN::BLACK)
				break;
		}
		if (deficientNode != this->mPostOrderEnd->mRightChild) // x->mColor is certainly BLACK
			deficientNode->mColor = IPPS23RBBTN::RED;		   // Rule (a.1)
	}

	void remove_bottom_up_pass(IPPS23RBBTN *x)
	{
		while (x != this->mPostOrderEnd->mRightChild && x->mColor == IPPS23RBBTN::BLACK)
		{
			x = applyParitySeekingRules(x);
		}
		x->mColor = IPPS23RBBTN::BLACK; // Parity-seeking Rule (a)
	}

	IPPS23RBBTN *applyParitySeekingRules(IPPS23RBBTN *x)
	{
		IPPS23RBBTN *p = x->mParent;
		IPPS23RBBTN *y = x == p->mLeftChild ? p->mRightChild : p->mLeftChild;
		if (y->mColor == IPPS23RBBTN::RED) // Parity-seeking Rule (c): Rotate to have a black sibling
			if (x == p->mLeftChild)
				this->RR(p);
			else
				this->LL(p);
		else
		{ // Parity-seeking Rule (b): Make the sibling red
			y->mColor = IPPS23RBBTN::RED;
			x = p;
			x = fixUp(x, y);
		}
		return x;
	}

	IPPS23RBBTN *fixUp(IPPS23RBBTN *x, IPPS23RBBTN *z)
	{
		if (z->mLeftChild->mColor == IPPS23RBBTN::RED || z->mRightChild->mColor == IPPS23RBBTN::RED)
		{
			if (z == x->mRightChild)
			{
				if (z->mRightChild->mColor == IPPS23RBBTN::BLACK) // Fixing rule (a)
					this->LL(z);
				x = this->RR(x); // Fixing rule (b)
			}
			else
			{
				if (z->mLeftChild->mColor == IPPS23RBBTN::BLACK) // Fixing rule (a)
					this->RR(z);
				x = this->LL(x); // Fixing rule (b)
			}
			x->mLeftChild->mColor = IPPS23RBBTN::BLACK;	 // Fixing rule (c)
			x->mRightChild->mColor = IPPS23RBBTN::BLACK; // Fixing rule (c)
			x = this->mPostOrderEnd->mRightChild;		 // terminate the bottom up pass
		}
		return x;
	}

	virtual void updateAfterInsert(IPPS23RBBTN *node)
	{
		// IndexedBT updateAfterInsert(node);
		updateLeftSize(node, 1);
		// PPS23RB updateAfterInsert(node);
		put_bottom_up_pass(node);
	}

	virtual void updateBeforeDelete(IPPS23RBBTN *node)
	{
		// IndexedBT updateBeforeDelete(node);
		updateLeftSize(node, -1);
		// PPS23RB updateBeforeDelete(node);
		IPPS23RBBTN *parentNode = node->mParent;
		this->mNilSentinel->mParent = parentNode;
		if (node->mLeftChild != this->mNilSentinel || node->mRightChild != this->mNilSentinel)
		{
			IPPS23RBBTN *theChild = (node->mLeftChild != this->mNilSentinel) ? node->mLeftChild : node->mRightChild;
			theChild->mColor = IPPS23RBBTN::BLACK;
		}
	}

	virtual void updateAfterDelete(IPPS23RBBTN *node)
	{
		if ((node->mLeftChild != this->mNilSentinel && node->mRightChild == this->mNilSentinel) ||
			(node->mLeftChild == this->mNilSentinel && node->mRightChild != this->mNilSentinel))
		{
			remove_bottom_up_pass(this->mNilSentinel);
		}
		this->mNilSentinel->mParent = 0;
	}

	virtual void deleteDeg2Node(IPPS23RBBTN *node)
	{
		IPPS23RBBTN *actualDeleteNode = getActualDeleteNode(node);
		node->mData = actualDeleteNode->mData; // از استاد در مورد جایگاه این کد پرسیده شود
		this->deleteNode(actualDeleteNode);
	}
	// If a degree-1 node is deleted, it is replaced by its subtree.
	virtual void deleteNode(IPPS23RBBTN *theNode)
	{
		IPPS23RBBTN *theParent = theNode->mParent;
		// Write your code here
		if (theNode->mLeftChild == mNilSentinel || theNode->mRightChild == mNilSentinel)
		{
			updateBeforeDelete(theNode);
			IPPS23RBBTN *theChild;
			if (theNode->mRightChild != mNilSentinel)
			{
				theChild = theNode->mRightChild;
				theChild->mParent = theParent;
			}
			else if (theNode->mLeftChild != mNilSentinel)
			{
				theChild = theNode->mLeftChild;
				theChild->mParent = theParent;
			}
			else
				theChild = mNilSentinel;

			if (theParent && theParent->mRightChild == theNode)
				theParent->mRightChild = theChild;
			else if (theParent)
				theParent->mLeftChild = theChild;

			delete theNode;
			mSize--;
			updateAfterDelete(theParent);
		}
		else
		{
			deleteDeg2Node(theNode);
		}
	}

	virtual void deleteLastInOrderNode()
	{
		IPPS23RBBTN *theParent = mLastInOrderNode->mParent;

		// IndexedBT updateBeforeDelete(node);
		mInOrderEnd->mLeftSize--;

		// PPS23RB updateBeforeDelete(node);
		this->mNilSentinel->mParent = theParent;
		IPPS23RBBTN *theChild;
		if (mLastInOrderNode->mLeftChild != mNilSentinel)
		{
			theChild = mLastInOrderNode->mLeftChild;
			theChild->mColor = IPPS23RBBTN::BLACK;
			// delete last inorder node
			theChild->mParent = theParent;
			delete mLastInOrderNode;
			mLastInOrderNode = theChild;
		}
		else
		{
			theChild = mNilSentinel;
			delete mLastInOrderNode;
			mLastInOrderNode = theParent;
		}

		theParent->mRightChild = theChild;
		mSize--;

		if ((theParent->mLeftChild != this->mNilSentinel && theParent->mRightChild == this->mNilSentinel) ||
			(theParent->mLeftChild == this->mNilSentinel && theParent->mRightChild != this->mNilSentinel))
		{
			remove_bottom_up_pass(this->mNilSentinel);
		}
		this->mNilSentinel->mParent = 0;
	}

	// class Iterator
	// {
	// public:
	// 	Iterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : mCurrentNode(currentNode), mNilSentinel(nil) {}
	// 	virtual T &operator*() { return mCurrentNode->mData; }
	// 	virtual T *operator->() { return &mCurrentNode->mData; }
	// 	virtual bool operator==(Iterator &itr) { return mCurrentNode == itr.mCurrentNode; }
	// 	virtual bool operator!=(Iterator &itr) { return mCurrentNode != itr.mCurrentNode; }
	// 	virtual void operator++() = 0;
	// 	virtual void operator--() = 0;
	// 	virtual IPPS23RBBTN *getBinaryTreeNode() { return mCurrentNode; }
	// protected:
	// 	IPPS23RBBTN *mCurrentNode;
	// 	IPPS23RBBTN *mNilSentinel;
	// 	friend class IndexedPPS23RedBlackBinaryTree<T>;
	// };
	// class InOrderIterator : public Iterator
	// {
	// public:
	// 	InOrderIterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : Iterator(currentNode, nil) {}
	// 	virtual void operator++()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		if (theNode->mRightChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mRightChild;
	// 			while (theNode->mLeftChild != this->mNilSentinel)
	// 			{
	// 				theNode = theNode->mLeftChild;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			IPPS23RBBTN *lastNode = theNode;
	// 			do
	// 			{
	// 				lastNode = theNode;
	// 				theNode = theNode->mParent;
	// 			} while (theNode->mLeftChild != lastNode);
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// 	virtual void operator--()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		if (theNode->mLeftChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mLeftChild;
	// 			while (theNode->mRightChild != this->mNilSentinel)
	// 			{
	// 				theNode = theNode->mRightChild;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			IPPS23RBBTN *lastNode = theNode;
	// 			do
	// 			{
	// 				lastNode = theNode;
	// 				theNode = theNode->mParent;
	// 			} while (theNode->mRightChild != lastNode);
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// };
	// class PreOrderIterator : public Iterator
	// {
	// public:
	// 	PreOrderIterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : Iterator(currentNode, nil) {}
	// 	virtual void operator++()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		if (theNode->mLeftChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mLeftChild;
	// 		}
	// 		else if (theNode->mRightChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mRightChild;
	// 		}
	// 		else
	// 		{
	// 			IPPS23RBBTN *lastNode = theNode;
	// 			do
	// 			{
	// 				lastNode = theNode;
	// 				theNode = theNode->mParent;
	// 			} while (theNode->mLeftChild != lastNode || theNode->mRightChild == this->mNilSentinel);
	// 			theNode = theNode->mRightChild;
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// 	virtual void operator--()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		IPPS23RBBTN *theParent = theNode->mParent;
	// 		if (theParent->mLeftChild == theNode || (theParent->mRightChild == theNode && theParent->mLeftChild == this->mNilSentinel))
	// 			theNode = theParent;
	// 		else
	// 		{
	// 			theNode = theParent->mLeftChild;
	// 			while (true)
	// 			{
	// 				if (theNode->mRightChild != this->mNilSentinel)
	// 				{
	// 					theNode = theNode->mRightChild;
	// 				}
	// 				else if (theNode->mLeftChild != this->mNilSentinel)
	// 				{
	// 					theNode = theNode->mLeftChild;
	// 				}
	// 				else
	// 					break;
	// 			}
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// };
	// class PostOrderIterator : public Iterator
	// {
	// public:
	// 	PostOrderIterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : Iterator(currentNode, nil) {}
	// 	virtual void operator++()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		IPPS23RBBTN *theParent = theNode->mParent;
	// 		if (theParent->mRightChild == theNode || (theParent->mLeftChild == theNode && theParent->mRightChild == this->mNilSentinel))
	// 			theNode = theParent;
	// 		else
	// 		{
	// 			theNode = theParent->mRightChild;
	// 			while (true)
	// 			{
	// 				if (theNode->mLeftChild != this->mNilSentinel)
	// 				{
	// 					theNode = theNode->mLeftChild;
	// 				}
	// 				else if (theNode->mRightChild != this->mNilSentinel)
	// 				{
	// 					theNode = theNode->mRightChild;
	// 				}
	// 				else
	// 					break;
	// 			}
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// 	virtual void operator--()
	// 	{
	// 		// Write your code here
	// 		IPPS23RBBTN *theNode = this->mCurrentNode;
	// 		if (theNode->mRightChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mRightChild;
	// 		}
	// 		else if (theNode->mLeftChild != this->mNilSentinel)
	// 		{
	// 			theNode = theNode->mLeftChild;
	// 		}
	// 		else
	// 		{
	// 			IPPS23RBBTN *lastNode = theNode;
	// 			do
	// 			{
	// 				lastNode = theNode;
	// 				theNode = theNode->mParent;
	// 			} while (theNode->mRightChild != lastNode || theNode->mLeftChild == this->mNilSentinel);
	// 			theNode = theNode->mLeftChild;
	// 		}
	// 		this->mCurrentNode = theNode;
	// 	}
	// };

	// virtual void insertRootNode(T data)
	// {
	// 	IPPS23RBBTN *root;
	// 	if (mPostOrderEnd->mRightChild != mNilSentinel)
	// 		throw std::runtime_error("Error: Root already exists.");
	// 	root = new IPPS23RBBTN;
	// 	root->mData = data;
	// 	root->mParent = mPostOrderEnd;
	// 	mPostOrderEnd->mRightChild = root;
	// 	root->mLeftChild = mNilSentinel;
	// 	root->mRightChild = mNilSentinel;
	// 	mSize = 1;
	// 	updateAfterInsert(mPostOrderEnd->mRightChild);
	// }
	// virtual IPPS23RBBTN *getRootNode() { return mPostOrderEnd->mRightChild; }
	// virtual IPPS23RBBTN *getHeaderRootNode() { return mInOrderEnd; }

	// virtual void deleteLeftChild(IPPS23RBBTN *node)
	// {
	// 	IPPS23RBBTN *theParent = node;
	// 	IPPS23RBBTN *theNode = theParent->mLeftChild;
	// 	deleteNode(theNode, theParent);
	// }
	// virtual void deleteRightChild(IPPS23RBBTN *node)
	// {
	// 	IPPS23RBBTN *theParent = node;
	// 	IPPS23RBBTN *theNode = theParent->mRightChild;
	// 	deleteNode(theNode, theParent);
	// }

	// virtual InOrderIterator inOrderBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mInOrderPreBegin;
	// 	InOrderIterator itr(theNode, mNilSentinel);
	// 	++itr;
	// 	return itr;
	// }
	// virtual InOrderIterator inOrderEnd()
	// {
	// 	return InOrderIterator(mInOrderEnd, mNilSentinel);
	// }
	// virtual InOrderIterator inOrderReverseBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mRevInOrderPreBegin;
	// 	InOrderIterator itr(theNode, mNilSentinel);
	// 	--itr;
	// 	return itr;
	// }
	// virtual InOrderIterator inOrderReverseEnd()
	// {
	// 	return InOrderIterator(mRevInOrderEnd, mNilSentinel);
	// }
	// virtual PreOrderIterator preOrderBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mPreOrderPreBegin;
	// 	PreOrderIterator itr(theNode, mNilSentinel);
	// 	++itr;
	// 	return itr;
	// }
	// virtual PreOrderIterator preOrderEnd()
	// {
	// 	return PreOrderIterator(mPreOrderEnd, mNilSentinel);
	// }
	// virtual PreOrderIterator preOrderReverseBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mRevPreOrderPreBegin;
	// 	PreOrderIterator itr(theNode, mNilSentinel);
	// 	--itr;
	// 	return itr;
	// }
	// virtual PreOrderIterator preOrderReverseEnd()
	// {
	// 	return PreOrderIterator(mRevPreOrderEnd, mNilSentinel);
	// }
	// virtual PostOrderIterator postOrderBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mPostOrderPreBegin;
	// 	PostOrderIterator itr(theNode, mNilSentinel);
	// 	++itr;
	// 	return itr;
	// }
	// virtual PostOrderIterator postOrderEnd()
	// {
	// 	return PostOrderIterator(mPostOrderEnd, mNilSentinel);
	// }
	// virtual PostOrderIterator postOrderReverseBegin()
	// {
	// 	// Write your code here
	// 	IPPS23RBBTN *theNode = mRevPostOrderPreBegin;
	// 	PostOrderIterator itr(theNode, mNilSentinel);
	// 	--itr;
	// 	return itr;
	// }
	// virtual PostOrderIterator postOrderReverseEnd()
	// {
	// 	return PostOrderIterator(mRevPostOrderEnd, mNilSentinel);
	// }

	// // This function is solely written to work on small binary trees.The code has many other known limitations.
	// void draw(std::ostream &out)
	// {
	// 	if (mSize == 0)
	// 		return;
	// 	int maxDepth = 9;
	// 	int depth = depthCalc(mPostOrderEnd->mRightChild, 1);
	// 	depth = depth * 2 - 1;
	// 	if (depth > maxDepth)
	// 	{
	// 		out << "Can't draw, the height of the tree is greater than " << (maxDepth + 1) / 2 << "\n";
	// 		return;
	// 	}
	// 	T **dataMap = new T *[depth];
	// 	char **linesMap = new char *[depth];
	// 	for (int i = 0; i < depth; i++)
	// 	{
	// 		dataMap[i] = new T[80];
	// 		linesMap[i] = new char[80];
	// 		for (int j = 0; j < 80; j++)
	// 		{
	// 			dataMap[i][j] = T();
	// 			linesMap[i][j] = ' ';
	// 		}
	// 	}
	// 	recursiveDraw(mPostOrderEnd->mRightChild, dataMap, linesMap, 40, 0);
	// 	for (int i = 0; i < depth; i++)
	// 		for (int j = 0; j < 80; j++)
	// 		{
	// 			if (dataMap[i][j] != T())
	// 			{
	// 				out << dataMap[i][j];
	// 			}
	// 			else
	// 			{
	// 				out << linesMap[i][j];
	// 			}
	// 		}
	// 	for (int i = 0; i < depth; i++)
	// 	{
	// 		delete[] dataMap[i];
	// 		delete[] linesMap[i];
	// 	}
	// 	delete[] dataMap;
	// 	delete[] linesMap;
	// }
	// string toString()
	// {
	// 	std::ostringstream stream;
	// 	this->draw(stream);
	// 	return stream.str();
	// }
	// int depthCalc(IPPS23RBBTN *root, int depth)
	// {
	// 	if (mSize == 0)
	// 	{
	// 		return 0;
	// 	}
	// 	int res = depth;
	// 	if (root->mRightChild != mNilSentinel)
	// 	{
	// 		int rightDepth = depthCalc(root->mRightChild, depth + 1);
	// 		res = (res > rightDepth) ? res : rightDepth;
	// 	}
	// 	if (root->mLeftChild != mNilSentinel)
	// 	{
	// 		int leftDepth = depthCalc(root->mLeftChild, depth + 1);
	// 		res = (res > leftDepth) ? res : leftDepth;
	// 	}
	// 	return res;
	// }
	// void recursiveDraw(IPPS23RBBTN *root, T **dataMap, char **linesMap, int x, int y)
	// {
	// 	int des = 1;
	// 	for (int i = 0; i < y / 2 + 2; i++)
	// 		des *= 2;
	// 	des = 80 / des;
	// 	// root:
	// 	dataMap[y][x - 1 / 2] = root->mData; // we can delete mNodeDisplayWidth
	// 	// left child:
	// 	if (root->mLeftChild != mNilSentinel)
	// 	{
	// 		for (int i = 0; i < des; i++)
	// 			linesMap[y + 1][x - i] = '-';
	// 		linesMap[y + 1][x] = '|';
	// 		recursiveDraw(root->mLeftChild, dataMap, linesMap, x - des, y + 2);
	// 	}
	// 	// right child:
	// 	if (root->mRightChild != mNilSentinel)
	// 	{
	// 		for (int i = 0; i < des; i++)
	// 			linesMap[y + 1][x + i] = '-';
	// 		linesMap[y + 1][x] = '|';
	// 		recursiveDraw(root->mRightChild, dataMap, linesMap, x + des, y + 2);
	// 	}
	// }
};
