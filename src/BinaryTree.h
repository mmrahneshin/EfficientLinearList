// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2016 (1395 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T, class IBTN>
class BinaryTree
{
public:
	class BinaryTreeNode
	{
	public:
		virtual ~BinaryTreeNode(void) {}
		virtual T &getData() { return mActualNode->getData(); }
		virtual void setData(const T &data) { mActualNode->mData = data; }
		virtual BinaryTreeNode getLeftChild() const { return BinaryTreeNode(mActualNode->getLeftChild()); }
		virtual BinaryTreeNode getRightChild() const { return BinaryTreeNode(mActualNode->getRightChild()); }
		virtual BinaryTreeNode getParent() const { return BinaryTreeNode(mActualNode->getParent()); }
		virtual bool operator==(BinaryTreeNode &btn) { return mActualNode == btn.mActualNode; }
		virtual bool operator!=(BinaryTreeNode &btn) { return mActualNode != btn.mActualNode; }

	private:
		friend class BinaryTree<T, IBTN>;
		BinaryTreeNode(IBTN *node) { mActualNode = node; }

		IBTN *mActualNode;
	};

public:
	class Iterator
	{
	public:
		Iterator(IBTN *currentNode, IBTN *nil) : mCurrentNode(currentNode), mNilSentinel(nil) {}
		virtual T &operator*() { return mCurrentNode->mData; }
		virtual T *operator->() { return &mCurrentNode->mData; }
		virtual bool operator==(Iterator &itr) { return mCurrentNode == itr.mCurrentNode; }
		virtual bool operator!=(Iterator &itr) { return mCurrentNode != itr.mCurrentNode; }
		virtual void operator++() = 0;
		virtual void operator--() = 0;
		virtual BinaryTreeNode getBinaryTreeNode() { return BinaryTreeNode(mCurrentNode); }

	protected:
		IBTN *mCurrentNode;
		IBTN *mNilSentinel;

		friend class BinaryTree<T, IBTN>;
	};

	class InOrderIterator : public Iterator
	{
	public:
		InOrderIterator(IBTN *currentNode, IBTN *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;
			if (theNode->mRightChild != this->mNilSentinel)
			{
				theNode = theNode->mRightChild;
				while (theNode->mLeftChild != this->mNilSentinel)
				{
					theNode = theNode->mLeftChild;
				}
			}
			else
			{
				IBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mLeftChild != lastNode);
			}
			this->mCurrentNode = theNode;
		}

		virtual void operator--()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;

			if (theNode->mLeftChild != this->mNilSentinel)
			{
				theNode = theNode->mLeftChild;
				while (theNode->mRightChild != this->mNilSentinel)
				{
					theNode = theNode->mRightChild;
				}
			}
			else
			{
				IBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mRightChild != lastNode);
			}
			this->mCurrentNode = theNode;
		}
	};

	class PreOrderIterator : public Iterator
	{
	public:
		PreOrderIterator(IBTN *currentNode, IBTN *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;

			if (theNode->mLeftChild != this->mNilSentinel)
			{
				theNode = theNode->mLeftChild;
			}
			else if (theNode->mRightChild != this->mNilSentinel)
			{
				theNode = theNode->mRightChild;
			}
			else
			{
				IBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mLeftChild != lastNode || theNode->mRightChild == this->mNilSentinel);
				theNode = theNode->mRightChild;
			}
			this->mCurrentNode = theNode;
		}

		virtual void operator--()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;

			IBTN *theParent = theNode->mParent;
			if (theParent->mLeftChild == theNode || (theParent->mRightChild == theNode && theParent->mLeftChild == this->mNilSentinel))
				theNode = theParent;
			else
			{
				theNode = theParent->mLeftChild;
				while (true)
				{
					if (theNode->mRightChild != this->mNilSentinel)
					{
						theNode = theNode->mRightChild;
					}
					else if (theNode->mLeftChild != this->mNilSentinel)
					{
						theNode = theNode->mLeftChild;
					}
					else
						break;
				}
			}
			this->mCurrentNode = theNode;
		}
	};

	class PostOrderIterator : public Iterator
	{
	public:
		PostOrderIterator(IBTN *currentNode, IBTN *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;
			IBTN *theParent = theNode->mParent;

			if (theParent->mRightChild == theNode || (theParent->mLeftChild == theNode && theParent->mRightChild == this->mNilSentinel))
				theNode = theParent;
			else
			{
				theNode = theParent->mRightChild;
				while (true)
				{
					if (theNode->mLeftChild != this->mNilSentinel)
					{
						theNode = theNode->mLeftChild;
					}
					else if (theNode->mRightChild != this->mNilSentinel)
					{
						theNode = theNode->mRightChild;
					}
					else
						break;
				}
			}
			this->mCurrentNode = theNode;
		}

		virtual void operator--()
		{
			// Write your code here
			IBTN *theNode = this->mCurrentNode;

			if (theNode->mRightChild != this->mNilSentinel)
			{
				theNode = theNode->mRightChild;
			}
			else if (theNode->mLeftChild != this->mNilSentinel)
			{
				theNode = theNode->mLeftChild;
			}
			else
			{
				IBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mRightChild != lastNode || theNode->mLeftChild == this->mNilSentinel);
				theNode = theNode->mLeftChild;
			}
			this->mCurrentNode = theNode;
		}
	};

protected:
	/*
									mInOrderPreBegin
					----------------------|-------------
					|									|
			mPostorderPreBegin			mRevInOrderPreBegin=mPreorderPreBegin
									 -------------------|-------------------
									|                                       |
								ActualTree				mRevPreorderPreBegin=mRevPostorderPreBegin
	*/

	/*
									mRevInOrderEnd
					----------------------|---------------------
					|											|
			   mRevPostorderEnd						mInOrderEnd=mRevPreorderEnd
											 -------------------|-------------------
											|                                       |
										ActualTree					    mPreorderEnd=mPostorderEnd
	*/

	IBTN *mInOrderPreBegin;
	IBTN *mPostorderPreBegin;
	IBTN *mRevInOrderPreBegin;
	IBTN *mPreorderPreBegin;
	IBTN *mRevPreorderPreBegin;
	IBTN *mRevPostorderPreBegin;

	IBTN *mRevInOrderEnd;
	IBTN *mRevPostorderEnd;
	IBTN *mInOrderEnd;
	IBTN *mRevPreorderEnd;
	IBTN *mPreorderEnd;
	IBTN *mPostorderEnd;
	IBTN *mNilSentinel;
	int mNodeDisplayWidth; // we can delete mNodeDisplayWidth
	int mSize;

public:
	BinaryTree(void)
	{
		mNodeDisplayWidth = 1; // we can delete mNodeDisplayWidth
		mSize = 0;
		mNilSentinel = new IBTN();
		mRevInOrderEnd = new IBTN();
		mRevPostorderEnd = new IBTN();
		mInOrderEnd = new IBTN();
		mRevPreorderEnd = mInOrderEnd;
		mPreorderEnd = new IBTN();
		mPostorderEnd = mPreorderEnd;

		mRevPostorderEnd->mParent = mRevInOrderEnd;
		mRevPostorderEnd->mLeftChild = mNilSentinel;
		mRevPostorderEnd->mRightChild = mNilSentinel;

		mRevInOrderEnd->mLeftChild = mRevPostorderEnd;
		mRevInOrderEnd->mRightChild = mInOrderEnd;

		mInOrderEnd->mRightChild = mPreorderEnd;
		mInOrderEnd->mParent = mRevInOrderEnd;
		mInOrderEnd->mLeftChild = mNilSentinel;

		mPreorderEnd->mParent = mInOrderEnd;
		mPreorderEnd->mLeftChild = mNilSentinel;
		mPreorderEnd->mRightChild = mNilSentinel;

		mInOrderPreBegin = mRevInOrderEnd;
		mPostorderPreBegin = mRevPostorderEnd;
		mRevInOrderPreBegin = mInOrderEnd;
		mPreorderPreBegin = mInOrderEnd;
		mRevPreorderPreBegin = mPreorderEnd;
		mRevPostorderPreBegin = mPreorderEnd;
	}

	// caution: don't interpret virtual destructor as an ordinary virtual function!
	virtual ~BinaryTree(void)
	{
		DeleteSubtree(mRevInOrderEnd);
		delete mNilSentinel;
	}

	int size() { return mSize; }
	void DeleteSubtree(IBTN *node)
	{
		if (node->mLeftChild != mNilSentinel)
			DeleteSubtree(node->mLeftChild);
		if (node->mRightChild != mNilSentinel)
			DeleteSubtree(node->mRightChild);
		delete node;
	}

	bool isEmpty()
	{
		return mInOrderEnd->mLeftChild == mNilSentinel;
	}

	virtual bool hasLeftChild(const BinaryTreeNode &node) const { return node.mActualNode->mLeftChild != mNilSentinel; }

	virtual bool hasRightChild(const BinaryTreeNode &node) const { return node.mActualNode->mRightChild != mNilSentinel; }

	virtual void insertRootNode(T data)
	{
		IBTN *root;
		if (mInOrderEnd->mLeftChild != mNilSentinel)
			throw std::runtime_error("Error: Root already exists.");
		root = new IBTN();
		root->mData = data;
		root->mParent = mInOrderEnd;
		mInOrderEnd->mLeftChild = root;

		root->mLeftChild = mNilSentinel;
		root->mRightChild = mNilSentinel;
		mSize = 1;
		updateAfterInsert(mInOrderEnd->mLeftChild);
	}

	virtual BinaryTreeNode getRootNode() { return BinaryTreeNode(mInOrderEnd->mLeftChild); }

	virtual BinaryTreeNode getHeaderRootNode() { return BinaryTreeNode(mRevInOrderEnd); }

	// error if a left child already exists.
	virtual void insertLeftChild(const BinaryTreeNode &parentNode, T data)
	{
		// Write your code here
		IBTN *parentIBTN = parentNode.mActualNode;
		if (parentIBTN)
		{
			if (parentIBTN->mLeftChild == mNilSentinel)
			{
				IBTN *childNode = new IBTN();
				childNode->mData = data;
				childNode->mParent = parentIBTN;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentIBTN->mLeftChild = childNode;
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
	virtual void insertRightChild(const BinaryTreeNode &parentNode, T data)
	{
		// Write your code here
		IBTN *parentIBTN = parentNode.mActualNode;
		if (parentIBTN)
		{
			if (parentIBTN->mRightChild == mNilSentinel)
			{
				IBTN *childNode = new IBTN();
				childNode->mData = data;
				childNode->mParent = parentIBTN;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentIBTN->mRightChild = childNode;
				mSize++;
				updateAfterInsert(childNode);
			}
			else
				throw std::runtime_error("Can't insert a right child for a node which already has a right child.");
		}
		else
			throw std::runtime_error("Invalid Pointer.");
	}

	virtual void deleteLeftChild(const BinaryTreeNode &node)
	{
		IBTN *theParent = node.mActualNode;
		IBTN *theNode = theParent->getLeftChild();
		deleteNode(theNode, theParent);
	}

	virtual void deleteRightChild(const BinaryTreeNode &node)
	{
		IBTN *theParent = node.mActualNode;
		IBTN *theNode = theParent->getRightChild();
		deleteNode(theNode, theParent);
	}

	virtual InOrderIterator inOrderBegin()
	{
		// Write your code here
		IBTN *theNode = mInOrderPreBegin;
		InOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	virtual InOrderIterator inOrderEnd()
	{
		return InOrderIterator(mInOrderEnd, mNilSentinel);
	}

	virtual InOrderIterator inOrderReverseBegin()
	{
		// Write your code here
		IBTN *theNode = mRevInOrderPreBegin;
		InOrderIterator itr(theNode, mNilSentinel);
		--itr;
		return itr;
	}

	virtual InOrderIterator inOrderReverseEnd()
	{
		return InOrderIterator(mRevInOrderEnd, mNilSentinel);
	}

	virtual PreOrderIterator preOrderBegin()
	{
		// Write your code here
		IBTN *theNode = mPreorderPreBegin;
		PreOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	virtual PreOrderIterator preOrderEnd()
	{
		return PreOrderIterator(mPreorderEnd, mNilSentinel);
	}

	virtual PreOrderIterator preOrderReverseBegin()
	{
		// Write your code here
		IBTN *theNode = mRevPreorderPreBegin;
		PreOrderIterator itr(theNode, mNilSentinel);
		--itr;
		return itr;
	}

	virtual PreOrderIterator preOrderReverseEnd()
	{
		return PreOrderIterator(mRevPreorderEnd, mNilSentinel);
	}

	virtual PostOrderIterator postOrderBegin()
	{
		// Write your code here
		IBTN *theNode = mPostorderPreBegin;
		PostOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	virtual PostOrderIterator postOrderEnd()
	{
		return PostOrderIterator(mPostorderEnd, mNilSentinel);
	}

	virtual PostOrderIterator postOrderReverseBegin()
	{
		// Write your code here
		IBTN *theNode = mRevPostorderPreBegin;
		PostOrderIterator itr(theNode, mNilSentinel);
		--itr;
		return itr;
	}

	virtual PostOrderIterator postOrderReverseEnd()
	{
		return PostOrderIterator(mRevPostorderEnd, mNilSentinel);
	}

	void setNodeDisplayWidth(int width) // we can delete mNodeDisplayWidth
	{
		mNodeDisplayWidth = width; // we can delete mNodeDisplayWidth
	}

	// This function is solely written to work on small binary trees.
	// The code has many other known limitations.
	void draw(std::ostream &out)
	{
		if (mSize == 0)
			return;

		int maxDepth = 9;
		int depth = depthCalc(getRootNode().mActualNode, 1);
		depth = depth * 2 - 1;

		if (depth > maxDepth)
		{
			out << "Can't draw, the height of the tree is greater than " << (maxDepth + 1) / 2 << "\n";
			return;
		}

		T **dataMap = new T *[depth];
		char **linesMap = new char *[depth];
		for (int i = 0; i < depth; i++)
		{
			dataMap[i] = new T[80];
			linesMap[i] = new char[80];
			for (int j = 0; j < 80; j++)
			{
				dataMap[i][j] = T();
				linesMap[i][j] = ' ';
			}
		}

		recursiveDraw(getRootNode().mActualNode, dataMap, linesMap, 40, 0);

		for (int i = 0; i < depth; i++)
			for (int j = 0; j < 80; j++)
			{
				if (dataMap[i][j] != T())
				{
					out << dataMap[i][j];
				}
				else
				{
					out << linesMap[i][j];
				}
			}

		for (int i = 0; i < depth; i++)
		{
			delete[] dataMap[i];
			delete[] linesMap[i];
		}
		delete[] dataMap;
		delete[] linesMap;
	}

	string toString()
	{
		std::ostringstream stream;
		this->draw(stream);
		return stream.str();
	}

	int depthCalc(const BinaryTreeNode &node, int depth)
	{
		return depthCalc(node.mActualNode, depth);
	}

protected:
	virtual void updateAfterInsert(IBTN *node) { return; }

	virtual void updateBeforeDelete(IBTN *node) { return; }

	virtual void updateAfterDelete(IBTN *node) { return; }

	virtual void deleteDeg2Node(IBTN *node) { throw std::runtime_error("error, can't delete degree-2 node"); }
	// If a degree-1 node is deleted, it is replaced by its subtree.
	virtual void deleteNode(IBTN *theNode, IBTN *theParent)
	{
		// Write your code here
		if (theNode->mLeftChild == mNilSentinel || theNode->mRightChild == mNilSentinel)
		{
			updateBeforeDelete(theNode);
			IBTN *theChild;
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

	int depthCalc(IBTN *root, int depth)
	{
		if (mSize == 0)
		{
			return 0;
		}

		int res = depth;
		if (root->mRightChild != mNilSentinel)
		{
			int rightDepth = depthCalc(root->mRightChild, depth + 1);
			res = (res > rightDepth) ? res : rightDepth;
		}
		if (root->mLeftChild != mNilSentinel)
		{
			int leftDepth = depthCalc(root->mLeftChild, depth + 1);
			res = (res > leftDepth) ? res : leftDepth;
		}
		return res;
	}

	void recursiveDraw(IBTN *root, T **dataMap, char **linesMap, int x, int y)
	{
		int des = 1;
		for (int i = 0; i < y / 2 + 2; i++)
			des *= 2;
		des = 80 / des;
		// root:
		for (int i = 0; i < mNodeDisplayWidth; i++)					 // we can delete mNodeDisplayWidth
			dataMap[y][x + i - mNodeDisplayWidth / 2] = root->mData; // we can delete mNodeDisplayWidth
		// left child:
		if (root->mLeftChild != mNilSentinel)
		{
			for (int i = 0; i < des; i++)
				linesMap[y + 1][x - i] = '-';
			linesMap[y + 1][x] = '|';
			recursiveDraw(root->mLeftChild, dataMap, linesMap, x - des, y + 2);
		}
		// right child:
		if (root->mRightChild != mNilSentinel)
		{
			for (int i = 0; i < des; i++)
				linesMap[y + 1][x + i] = '-';
			linesMap[y + 1][x] = '|';
			recursiveDraw(root->mRightChild, dataMap, linesMap, x + des, y + 2);
		}
	}

protected:
	virtual IBTN *getActualNode(const BinaryTreeNode &node) { return node.mActualNode; }
};
