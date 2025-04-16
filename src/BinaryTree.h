// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T>
class BinaryTree
{
public:
	class Iterator
	{
	public:
		Iterator(BinaryTreeNode<T> *currentNode, BinaryTreeNode<T> *nil) : mCurrentNode(currentNode), mNilSentinel(nil) {}
		virtual T &operator*() { return mCurrentNode->mData; }
		virtual T *operator->() { return &mCurrentNode->mData; }
		virtual bool operator==(Iterator &itr) { return mCurrentNode == itr.mCurrentNode; }
		virtual bool operator!=(Iterator &itr) { return mCurrentNode != itr.mCurrentNode; }
		virtual void operator++() = 0;
		virtual void operator--() = 0;
		virtual BinaryTreeNode<T> *getBinaryTreeNode() { return mCurrentNode; }

	protected:
		BinaryTreeNode<T> *mCurrentNode;
		BinaryTreeNode<T> *mNilSentinel;

		friend class BinaryTree<T>;
	};

	class InOrderIterator : public Iterator
	{
	public:
		InOrderIterator(BinaryTreeNode<T> *currentNode, BinaryTreeNode<T> *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			BinaryTreeNode<T> *theNode = this->mCurrentNode;
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
				BinaryTreeNode<T> *lastNode = theNode;
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
			BinaryTreeNode<T> *theNode = this->mCurrentNode;

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
				BinaryTreeNode<T> *lastNode = theNode;
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
		PreOrderIterator(BinaryTreeNode<T> *currentNode, BinaryTreeNode<T> *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			BinaryTreeNode<T> *theNode = this->mCurrentNode;

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
				BinaryTreeNode<T> *lastNode = theNode;
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
			BinaryTreeNode<T> *theNode = this->mCurrentNode;

			BinaryTreeNode<T> *theParent = theNode->mParent;
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
		PostOrderIterator(BinaryTreeNode<T> *currentNode, BinaryTreeNode<T> *nil) : Iterator(currentNode, nil) {}
		virtual void operator++()
		{
			// Write your code here
			BinaryTreeNode<T> *theNode = this->mCurrentNode;
			BinaryTreeNode<T> *theParent = theNode->mParent;

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
			BinaryTreeNode<T> *theNode = this->mCurrentNode;

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
				BinaryTreeNode<T> *lastNode = theNode;
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

	BinaryTreeNode<T> *mInOrderPreBegin;
	BinaryTreeNode<T> *mPostOrderPreBegin;
	BinaryTreeNode<T> *mRevInOrderPreBegin;
	BinaryTreeNode<T> *mPreOrderPreBegin;
	BinaryTreeNode<T> *mRevPreOrderPreBegin;
	BinaryTreeNode<T> *mRevPostOrderPreBegin;

	BinaryTreeNode<T> *mRevInOrderEnd;
	BinaryTreeNode<T> *mRevPostOrderEnd;
	BinaryTreeNode<T> *mInOrderEnd;
	BinaryTreeNode<T> *mRevPreOrderEnd;
	BinaryTreeNode<T> *mPreOrderEnd;
	BinaryTreeNode<T> *mPostOrderEnd;
	BinaryTreeNode<T> *mNilSentinel;
	int mSize;

	BinaryTree(void)
	{
		mSize = 0;
		mNilSentinel = new BinaryTreeNode<T>();
		mRevInOrderEnd = new BinaryTreeNode<T>();
		mRevPostOrderEnd = new BinaryTreeNode<T>();
		mInOrderEnd = new BinaryTreeNode<T>();
		mRevPreOrderEnd = mRevPostOrderEnd;
		mPreOrderEnd = new BinaryTreeNode<T>();
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
	}

	// caution: don't interpret virtual destructor as an ordinary virtual function!
	virtual ~BinaryTree(void)
	{
		DeleteSubtree(mInOrderEnd);
		delete mNilSentinel;
	}

	int size() { return mSize; }
	void DeleteSubtree(BinaryTreeNode<T> *node)
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

	virtual bool hasLeftChild(BinaryTreeNode<T> *node) const { return node->mLeftChild != mNilSentinel; }

	virtual bool hasRightChild(BinaryTreeNode<T> *node) const { return node->mRightChild != mNilSentinel; }

	virtual void insertRootNode(T data)
	{
		BinaryTreeNode<T> *root;
		if (mPostOrderEnd->mRightChild != mNilSentinel)
			throw std::runtime_error("Error: Root already exists.");
		root = new BinaryTreeNode<T>();
		root->mData = data;
		root->mParent = mPostOrderEnd;
		mPostOrderEnd->mRightChild = root;
		root->mLeftChild = mNilSentinel;
		root->mRightChild = mNilSentinel;
		mSize = 1;
		updateAfterInsert(mPostOrderEnd->mRightChild);
	}

	virtual BinaryTreeNode<T> *getRootNode() { return mPostOrderEnd->mRightChild; }

	virtual BinaryTreeNode<T> *getHeaderRootNode() { return mInOrderEnd; }

	// error if a left child already exists.
	virtual void insertLeftChild(BinaryTreeNode<T> *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mLeftChild == mNilSentinel)
			{
				BinaryTreeNode<T> *childNode = new BinaryTreeNode<T>();
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
	virtual void insertRightChild(BinaryTreeNode<T> *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mRightChild == mNilSentinel)
			{
				BinaryTreeNode<T> *childNode = new BinaryTreeNode<T>();
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

	virtual void deleteLeftChild(BinaryTreeNode<T> *node)
	{
		BinaryTreeNode<T> *theParent = node;
		BinaryTreeNode<T> *theNode = theParent->getLeftChild();
		deleteNode(theNode, theParent);
	}

	virtual void deleteRightChild(BinaryTreeNode<T> *node)
	{
		BinaryTreeNode<T> *theParent = node;
		BinaryTreeNode<T> *theNode = theParent->getRightChild();
		deleteNode(theNode, theParent);
	}

	virtual InOrderIterator inOrderBegin()
	{
		// Write your code here
		BinaryTreeNode<T> *theNode = mInOrderPreBegin;
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
		BinaryTreeNode<T> *theNode = mRevInOrderPreBegin;
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
		BinaryTreeNode<T> *theNode = mPreOrderPreBegin;
		PreOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	virtual PreOrderIterator preOrderEnd()
	{
		return PreOrderIterator(mPreOrderEnd, mNilSentinel);
	}

	virtual PreOrderIterator preOrderReverseBegin()
	{
		// Write your code here
		BinaryTreeNode<T> *theNode = mRevPreOrderPreBegin;
		PreOrderIterator itr(theNode, mNilSentinel);
		--itr;
		return itr;
	}

	virtual PreOrderIterator preOrderReverseEnd()
	{
		return PreOrderIterator(mRevPreOrderEnd, mNilSentinel);
	}

	virtual PostOrderIterator postOrderBegin()
	{
		// Write your code here
		BinaryTreeNode<T> *theNode = mPostOrderPreBegin;
		PostOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	virtual PostOrderIterator postOrderEnd()
	{
		return PostOrderIterator(mPostOrderEnd, mNilSentinel);
	}

	virtual PostOrderIterator postOrderReverseBegin()
	{
		// Write your code here
		BinaryTreeNode<T> *theNode = mRevPostOrderPreBegin;
		PostOrderIterator itr(theNode, mNilSentinel);
		--itr;
		return itr;
	}

	virtual PostOrderIterator postOrderReverseEnd()
	{
		return PostOrderIterator(mRevPostOrderEnd, mNilSentinel);
	}

	// This function is solely written to work on small binary trees.
	// The code has many other known limitations.
	void draw(std::ostream &out)
	{
		if (mSize == 0)
			return;
		int maxDepth = 9;
		int depth = depthCalc(getRootNode(), 1);
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
		recursiveDraw(getRootNode(), dataMap, linesMap, 40, 0);
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

	int depthCalc(BinaryTreeNode<T> *root, int depth)
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

protected:
	virtual void updateAfterInsert(BinaryTreeNode<T> *node) { return; }

	virtual void updateBeforeDelete(BinaryTreeNode<T> *node) { return; }

	virtual void updateAfterDelete(BinaryTreeNode<T> *node) { return; }

	virtual void deleteDeg2Node(BinaryTreeNode<T> *node) { throw std::runtime_error("error, can't delete degree-2 node"); }
	// If a degree-1 node is deleted, it is replaced by its subtree.
	virtual void deleteNode(BinaryTreeNode<T> *theNode, BinaryTreeNode<T> *theParent)
	{
		// Write your code here
		if (theNode->mLeftChild == mNilSentinel || theNode->mRightChild == mNilSentinel)
		{
			updateBeforeDelete(theNode);
			BinaryTreeNode<T> *theChild;
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

	void recursiveDraw(BinaryTreeNode<T> *root, T **dataMap, char **linesMap, int x, int y)
	{
		int des = 1;
		for (int i = 0; i < y / 2 + 2; i++)
			des *= 2;
		des = 80 / des;
		// root:
		dataMap[y][x - 1 / 2] = root->mData; // we can delete mNodeDisplayWidth
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
};
