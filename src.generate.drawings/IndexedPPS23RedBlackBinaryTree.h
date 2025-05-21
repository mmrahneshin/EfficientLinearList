// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#pragma once

using namespace std;

template <class T>
class IndexedPPS23RedBlackBinaryTree
{
	typedef IndexedPPS23RBBinaryTreeNode<T> IPPS23RBBTN;
	friend class EfficientLinearList<T>;

public:
	IndexedPPS23RedBlackBinaryTree(void)
	{
		mSize = 0;
		mGlobalLeftSize = 0;
		mNilSentinel = new IPPS23RBBTN();
		mRevInOrderEnd = new IPPS23RBBTN();
		mRevPostOrderEnd = new IPPS23RBBTN();
		mInOrderEnd = new IPPS23RBBTN();
		mRevPreOrderEnd = mRevPostOrderEnd;
		mPreOrderEnd = new IPPS23RBBTN();
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
		mFirstInOrderNode = mPostOrderEnd;

		mInOrderEnd->mLeftSize = 0;
		mPostOrderEnd->mLeftSize = -1;

		seqNo = 0;
	}

	// caution: don't interpret destructor as an ordinary function!
	~IndexedPPS23RedBlackBinaryTree(void)
	{
		DeleteSubtree(mInOrderEnd);
		delete mNilSentinel;
	}

	int size() { return mSize; }

	bool isEmpty()
	{
		return mPostOrderEnd->mRightChild == mNilSentinel;
	}

	bool hasLeftChild(IPPS23RBBTN *node) const { return node->mLeftChild != mNilSentinel; }

	bool hasRightChild(IPPS23RBBTN *node) const { return node->mRightChild != mNilSentinel; }

	void insertRootNode(T data)
	{
		IPPS23RBBTN *root;
		if (mPostOrderEnd->mRightChild != mNilSentinel)
			throw std::runtime_error("Error: Root already exists.");
		root = new IPPS23RBBTN();
		root->mData = data;
		root->mParent = mPostOrderEnd;
		mPostOrderEnd->mRightChild = root;

		root->mLeftChild = mNilSentinel;
		root->mRightChild = mNilSentinel;

		mLastInOrderNode = root;
		mFirstInOrderNode = root;

		mSize = 1;
		mInOrderEnd->mLeftSize++;
		drawTreeAndSave("insert/", "Insert" + to_string(data) + "-After-top-down-pass", data);
		put_bottom_up_pass(root);
	}

	void insertLastInOrderNode(T data)
	{
		IPPS23RBBTN *childNode = new IPPS23RBBTN();
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
		drawTreeAndSave("insert/", "Insert" + to_string(data) + "-After-top-down-pass", data);
		put_bottom_up_pass(childNode);
	}

	void insertFirstInOrderNode(T data)
	{
		IPPS23RBBTN *childNode = new IPPS23RBBTN();
		childNode->mData = data;
		childNode->mParent = mFirstInOrderNode;
		childNode->mLeftChild = mNilSentinel;
		childNode->mRightChild = mNilSentinel;
		mFirstInOrderNode->mLeftChild = childNode;
		mSize++;
		mFirstInOrderNode = childNode;

		// update mGlobalLeftSize
		mGlobalLeftSize++;
		mFirstInOrderNode->mLeftSize -= mGlobalLeftSize;
		// PPS23RB updateAfterInsert(node);
		drawTreeAndSave("insert/", "Insert" + to_string(data) + "-After-top-down-pass", data);
		put_bottom_up_pass(childNode);
	}

	// error if a left child already exists.
	void insertLeftChild(IPPS23RBBTN *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mLeftChild == mNilSentinel)
			{
				IPPS23RBBTN *childNode = new IPPS23RBBTN();
				childNode->mData = data;
				childNode->mParent = parentNode;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentNode->mLeftChild = childNode;
				mSize++;
				drawTreeAndSave("insert/", "Insert" + to_string(data) + "-After-top-down-pass", data);
				updateAfterInsert(childNode);
			}
			else
				throw std::runtime_error("Can't insert a left child for a node which already has a left child.");
		}
		else
			throw std::runtime_error("Invalid Pointer.");
	}

	// error if a right child already exists.
	void insertRightChild(IPPS23RBBTN *parentNode, T data)
	{
		// Write your code here
		if (parentNode)
		{
			if (parentNode->mRightChild == mNilSentinel)
			{
				IPPS23RBBTN *childNode = new IPPS23RBBTN();
				childNode->mData = data;
				childNode->mParent = parentNode;
				childNode->mLeftChild = mNilSentinel;
				childNode->mRightChild = mNilSentinel;
				parentNode->mRightChild = childNode;
				mSize++;
				drawTreeAndSave("insert/", "Insert" + to_string(data) + "-After-top-down-pass", data);
				updateAfterInsert(childNode);
			}
			else
				throw std::runtime_error("Can't insert a right child for a node which already has a right child.");
		}
		else
			throw std::runtime_error("Invalid Pointer.");
	}

	class Iterator
	{
	public:
		Iterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : mCurrentNode(currentNode), mNilSentinel(nil) {}
		T &operator*() { return mCurrentNode->mData; }
		T *operator->() { return &mCurrentNode->mData; }
		bool operator==(Iterator &itr) { return mCurrentNode == itr.mCurrentNode; }
		bool operator!=(Iterator &itr) { return mCurrentNode != itr.mCurrentNode; }
		void operator++() = 0;
		void operator--() = 0;
		IPPS23RBBTN *getBinaryTreeNode() { return mCurrentNode; }

	protected:
		IPPS23RBBTN *mCurrentNode;
		IPPS23RBBTN *mNilSentinel;
		friend class IndexedPPS23RedBlackBinaryTree<T>;
	};
	class InOrderIterator : public Iterator
	{
	public:
		InOrderIterator(IPPS23RBBTN *currentNode, IPPS23RBBTN *nil) : Iterator(currentNode, nil) {}
		void operator++()
		{
			// Write your code here
			IPPS23RBBTN *theNode = this->mCurrentNode;
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
				IPPS23RBBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mLeftChild != lastNode);
			}
			this->mCurrentNode = theNode;
		}
		void operator--()
		{
			// Write your code here
			IPPS23RBBTN *theNode = this->mCurrentNode;
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
				IPPS23RBBTN *lastNode = theNode;
				do
				{
					lastNode = theNode;
					theNode = theNode->mParent;
				} while (theNode->mRightChild != lastNode);
			}
			this->mCurrentNode = theNode;
		}
	};

	//  void deleteLeftChild(IPPS23RBBTN *node)
	// {
	// 	IPPS23RBBTN *theParent = node;
	// 	IPPS23RBBTN *theNode = theParent->mLeftChild;
	// 	deleteNode(theNode, theParent);
	// }
	//  void deleteRightChild(IPPS23RBBTN *node)
	// {
	// 	IPPS23RBBTN *theParent = node;
	// 	IPPS23RBBTN *theNode = theParent->mRightChild;
	// 	deleteNode(theNode, theParent);
	// }

	InOrderIterator inOrderBegin()
	{
		// Write your code here
		IPPS23RBBTN *theNode = mInOrderPreBegin;
		InOrderIterator itr(theNode, mNilSentinel);
		++itr;
		return itr;
	}

	InOrderIterator inOrderEnd()
	{
		return InOrderIterator(mInOrderEnd, mNilSentinel);
	}

private:
	int seqNo;
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
	IPPS23RBBTN *mFirstInOrderNode;
	int mGlobalLeftSize;
	int mSize;

	virtual string drawTree(string operation, int selectedKey, void *deficiencyParent, char deficiencyDirection)
	{
		string nodeName;
		string style;
		string color;
		IPPS23RBBTN *parent;
		IPPS23RBBTN *node;
		char direction;
		IPPS23RBBTN *root = mPostOrderEnd->mRightChild;

		string result = "digraph structs { \n";
		if (root->mData == selectedKey)
			style = ";style=dashed";
		if (mPostOrderEnd == deficiencyParent && deficiencyDirection == 'R')
			style = ";shape=box;style=dashed";
		result += "\"" + operation + "\"" + "[color = blue; shape = none];\n";
		color = (root->mColor == IPPS23RBBTN::RED ? "red" : "black");
		result += to_string(root->mData) + " [color=" + color + style + "];\n";
		queue<pair<IPPS23RBBTN *, char>> q;
		q.push(pair<IPPS23RBBTN *, char>(mPostOrderEnd, 'R'));

		while (q.empty() == false)
		{
			pair<IPPS23RBBTN *, char> p;
			p = q.front();
			q.pop();
			parent = p.first;
			direction = p.second;
			if (direction == 'L')
				node = parent->mLeftChild;
			else
				node = parent->mRightChild;
			// cout << node->mColor << endl;
			color = (node->mColor == IPPS23RBBTN::RED ? "red" : "black");
			style = "";
			if (node != mNilSentinel)
			{
				nodeName = to_string(node->mData);
			}
			else
			{
				nodeName = "N_";
				nodeName += direction + to_string(parent->mData);
				style = ";shape = point; label=\"\"";
			}

			if (parent != mPostOrderEnd)
				result += to_string(parent->mData) + " -> " + nodeName + " [color=" + color + style + "];\n";

			if (node != mNilSentinel)
			{
				string nodeLeftName, nodeRightName;
				color = (node->mLeftChild->mColor == IPPS23RBBTN::RED ? "red" : "black");
				style = "";
				if (node->mLeftChild != mNilSentinel)
					nodeLeftName = to_string(node->mLeftChild->mData);
				else
				{
					nodeLeftName = "N_L" + to_string(node->mData);
					style = ";shape = point; label=\"\"";
				}
				if (node->mLeftChild != mNilSentinel && node->mLeftChild->mData == selectedKey)
					style = ";style=dashed";

				if (node == deficiencyParent && deficiencyDirection == 'L')
					style = ";shape=box;style=dashed";

				result += nodeLeftName + " [color=" + color + style + "]; \n";

				color = (node->mRightChild->mColor == IPPS23RBBTN::RED ? "red" : "black");
				style = "";
				if (node->mRightChild != mNilSentinel)
					nodeRightName = to_string(node->mRightChild->mData);
				else
				{
					nodeRightName = "N_R" + to_string(node->mData);
					style = ";shape = point; label=\"\"";
				}
				if (node->mRightChild != mNilSentinel && node->mRightChild->mData == selectedKey)
					style = ";style=dashed";

				if (node == deficiencyParent && deficiencyDirection == 'R')
					style = ";shape=box;style=dashed";

				result += nodeRightName + " [color=" + color + style + "]; \n";

				result += "{rank = same; " + nodeLeftName + " ; " + nodeRightName + " };\n";

				// result += drawTree(node->left, node, 'L');
				// result += drawTree(node->right, node, 'R');
				q.push(pair<IPPS23RBBTN *, char>(node, 'L'));
				q.push(pair<IPPS23RBBTN *, char>(node, 'R'));
			}
		}

		result += "}";
		return result;
	}
	bool draw_disabled = false;
	void drawTreeAndSave(string insertOrRemove, string operation, int selected, IPPS23RBBTN *deficiencyParent = NULL, char deficiencyDirection = '-')
	{
		if (!draw_disabled)
		{
			draw_disabled = true;
			return;
		}
		string out = drawTree(operation, selected, deficiencyParent, deficiencyDirection);
		string fileName = "/home/sepehr/uni/DS/paper/EfficientLinearList/doc/" + insertOrRemove + to_string(seqNo++) + operation;
		fstream fout;
		fout.open(fileName + ".dot", ios::out);
		fout << out;
		fout.close();
		string cmd;
		cmd = "dot -Gdpi=300 -Tpng \"" + fileName + ".dot\"" + " -o \"" + fileName + ".png\"";
		cout << cmd << endl;
		system(cmd.c_str());
		cmd = "rm  \"" + fileName + ".dot\"";
		cout << cmd << endl;
		system(cmd.c_str());
	}

	void DeleteSubtree(IPPS23RBBTN *node)
	{
		if (node->mLeftChild != mNilSentinel)
			DeleteSubtree(node->mLeftChild);
		if (node->mRightChild != mNilSentinel)
			DeleteSubtree(node->mRightChild);
		delete node;
	}

	inline void updateLeftSize(IPPS23RBBTN *iNode, int diff)
	{
		while (iNode->mParent)
		{
			if (iNode == iNode->mParent->mLeftChild)
				iNode->mParent->mLeftSize += diff;
			iNode = iNode->mParent;
		}
	}

	inline void updateAfterRR(IPPS23RBBTN *node)
	{
		// IndexedPPS23RB updateAfterRR(node);
		IPPS23RBBTN *A = node->mLeftChild;
		node->mLeftSize += A->mLeftSize + 1; // B->mLeftSize = [C->mLeftSize + 1](is B->mLeftSize) + A->mLeftSize + 1

		// PPS23RB updateAfterRR(node);
		typename IPPS23RBBTN::COLOR c = node->mColor;
		node->mColor = node->mLeftChild->mColor;
		node->mLeftChild->mColor = c;
	}

	inline IPPS23RBBTN *RR(IPPS23RBBTN *A)
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

	inline void updateAfterLL(IPPS23RBBTN *node)
	{
		// IndexedPPS23RB updateAfterLL(node);
		IPPS23RBBTN *A = node->mRightChild;
		IPPS23RBBTN *C = A->mLeftChild;
		A->mLeftSize -= node->mLeftSize + 1;

		// PPS23RB updateAfterLL(node);
		typename IPPS23RBBTN::COLOR c = node->mColor;
		node->mColor = node->mRightChild->mColor;
		node->mRightChild->mColor = c;
	}

	inline IPPS23RBBTN *LL(IPPS23RBBTN *A)
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

	inline IPPS23RBBTN *getActualDeleteNode(IPPS23RBBTN *node)
	{
		IPPS23RBBTN *actualDeleteNode = node->mLeftChild;
		while (actualDeleteNode->mRightChild != this->mNilSentinel)
		{
			actualDeleteNode = actualDeleteNode->mRightChild;
		}
		return actualDeleteNode;
	}

	inline void put_bottom_up_pass(IPPS23RBBTN *deficientNode)
	{
		IPPS23RBBTN *parentNode, *siblingNode;
		char overfullDirection;
		while (true) // deficientNode->mColor is certainly BLACK
		{
			parentNode = deficientNode->mParent;
			if (parentNode->mColor == IPPS23RBBTN::RED)
			{
				if (parentNode == parentNode->mParent->mLeftChild)
				{
					if (deficientNode == parentNode->mRightChild) // Rule (b.2)
					{
						overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
						drawTreeAndSave("insert/", "Rule (b.2)", deficientNode->mData, deficientNode->mParent, overfullDirection);
						deficientNode = parentNode;
						parentNode = this->RR(parentNode);
					}
					overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
					drawTreeAndSave("insert/", "Rule (b.1)", deficientNode->mData, deficientNode->mParent, overfullDirection);
					parentNode = this->LL(parentNode->mParent); // Rule (b.1)
				}
				else
				{
					if (deficientNode == parentNode->mLeftChild) // Rule (b.2)
					{
						overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
						drawTreeAndSave("insert/", "Rule (b.2)", deficientNode->mData, deficientNode->mParent, overfullDirection);
						deficientNode = parentNode;
						parentNode = this->LL(parentNode);
					}
					overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
					drawTreeAndSave("insert/", "Rule (b.1)", deficientNode->mData, deficientNode->mParent, overfullDirection);
					parentNode = this->RR(parentNode->mParent); // Rule (b.1)
				}
			}
			siblingNode = (deficientNode == parentNode->mLeftChild) ? parentNode->mRightChild : parentNode->mLeftChild;

			if (siblingNode->mColor == IPPS23RBBTN::RED) // Rule (a.2)
			{
				overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
				drawTreeAndSave("insert/", "Rule (a.2)", deficientNode->mData, deficientNode->mParent, overfullDirection);
				siblingNode->mColor = IPPS23RBBTN::BLACK;
				deficientNode = parentNode;
			}
			else if (parentNode->mColor == IPPS23RBBTN::BLACK)
				break;
		}
		if (deficientNode != this->mPostOrderEnd->mRightChild)
		{
			overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
			drawTreeAndSave("insert/", "Rule (a.1)", deficientNode->mData, deficientNode->mParent, overfullDirection);
			deficientNode->mColor = IPPS23RBBTN::RED; // Rule (a.1)
		}
		else
		{
			overfullDirection = deficientNode == deficientNode->mParent->mLeftChild ? 'L' : 'R';
			drawTreeAndSave("insert/", "No rule matches", deficientNode->mData, deficientNode->mParent, overfullDirection);
		} // x->mColor is certainly BLACK
	}

	inline void remove_bottom_up_pass(IPPS23RBBTN *x)
	{
		while (x != this->mPostOrderEnd->mRightChild && x->mColor == IPPS23RBBTN::BLACK)
		{
			x = applyParitySeekingRules(x);
		}
		char deficiecyDirection = x == x->mParent->mLeftChild ? 'L' : 'R';
		if (x != this->mPostOrderEnd->mRightChild)
			drawTreeAndSave("remove/", "Parity-Seeking Rule (a)", x->mData, x->mParent, deficiecyDirection);
		x->mColor = IPPS23RBBTN::BLACK; // Parity-seeking Rule (a)
	}

	inline IPPS23RBBTN *applyParitySeekingRules(IPPS23RBBTN *x)
	{
		IPPS23RBBTN *p = x->mParent;
		IPPS23RBBTN *y = x == p->mLeftChild ? p->mRightChild : p->mLeftChild;
		char deficiecyDirection = x == x->mParent->mLeftChild ? 'L' : 'R';
		if (y->mColor == IPPS23RBBTN::RED) // Parity-seeking Rule (c): Rotate to have a black sibling
			if (x == p->mLeftChild)
			{
				drawTreeAndSave("remove/", "Parity-Seeking Rule (c)", p->mData, x->mParent, deficiecyDirection);
				this->RR(p);
			}
			else
			{
				drawTreeAndSave("remove/", "Parity-Seeking Rule (c)", p->mData, x->mParent, deficiecyDirection);
				this->LL(p);
			}
		else
		{ // Parity-seeking Rule (b): Make the sibling red
			drawTreeAndSave("remove/", "Parity-Seeking Rule (b)", -1, x->mParent, deficiecyDirection);
			y->mColor = IPPS23RBBTN::RED;
			x = p;
			x = fixUp(x, y);
		}
		return x;
	}

	inline IPPS23RBBTN *fixUp(IPPS23RBBTN *x, IPPS23RBBTN *z)
	{
		char deficiecyDirection = x == x->mParent->mLeftChild ? 'L' : 'R';
		if (z->mLeftChild->mColor == IPPS23RBBTN::RED || z->mRightChild->mColor == IPPS23RBBTN::RED)
		{
			if (z == x->mRightChild)
			{
				if (z->mRightChild->mColor == IPPS23RBBTN::BLACK) // Fixing rule (a)
				{
					drawTreeAndSave("remove/", "Fixing Rule (a)", z->mData, x->mParent, deficiecyDirection);
					this->LL(z);
				}
				drawTreeAndSave("remove/", "Fixing Rule (b)", x->mData, x->mParent, deficiecyDirection);
				x = this->RR(x); // Fixing rule (b)
			}
			else
			{
				if (z->mLeftChild->mColor == IPPS23RBBTN::BLACK) // Fixing rule (a)
				{
					drawTreeAndSave("remove/", "Fixing Rule (a)", z->mData, x->mParent, deficiecyDirection);
					this->RR(z);
				}
				drawTreeAndSave("remove/", "Fixing Rule (b)", x->mData, x->mParent, deficiecyDirection);
				x = this->LL(x); // Fixing rule (b)
			}
			drawTreeAndSave("remove/", "Fixing Rule (c)", x->mData, x->mParent, deficiecyDirection);
			x->mLeftChild->mColor = IPPS23RBBTN::BLACK;	 // Fixing rule (c)
			x->mRightChild->mColor = IPPS23RBBTN::BLACK; // Fixing rule (c)
			x = this->mPostOrderEnd->mRightChild;		 // terminate the bottom up pass
		}
		return x;
	}

	inline void updateAfterInsert(IPPS23RBBTN *node)
	{
		// IndexedBT updateAfterInsert(node);
		// updateLeftSize(node, 1);
		// PPS23RB updateAfterInsert(node);
		put_bottom_up_pass(node);
	}

	inline void updateBeforeDelete(IPPS23RBBTN *node)
	{
		// IndexedBT updateBeforeDelete(node);
		// updateLeftSize(node, -1);
		// PPS23RB updateBeforeDelete(node);
		IPPS23RBBTN *parentNode = node->mParent;
		this->mNilSentinel->mParent = parentNode;
		if (node->mLeftChild != this->mNilSentinel || node->mRightChild != this->mNilSentinel)
		{
			IPPS23RBBTN *theChild = (node->mLeftChild != this->mNilSentinel) ? node->mLeftChild : node->mRightChild;
			theChild->mColor = IPPS23RBBTN::BLACK;
		}
	}

	inline void updateAfterDelete(IPPS23RBBTN *node)
	{
		if ((node->mLeftChild != this->mNilSentinel && node->mRightChild == this->mNilSentinel) ||
			(node->mLeftChild == this->mNilSentinel && node->mRightChild != this->mNilSentinel))
		{
			remove_bottom_up_pass(this->mNilSentinel);
		}
		this->mNilSentinel->mParent = 0;
	}

	inline void deleteDeg2Node(IPPS23RBBTN *node)
	{
		IPPS23RBBTN *actualDeleteNode = getActualDeleteNode(node);
		node->mData = actualDeleteNode->mData; // از استاد در مورد جایگاه این کد پرسیده شود
		this->deleteNode(actualDeleteNode);
	}
	// If a degree-1 node is deleted, it is replaced by its subtree.
	void deleteNode(IPPS23RBBTN *theNode)
	{
		// Write your code here
		if (theNode->mLeftChild == mNilSentinel || theNode->mRightChild == mNilSentinel)
		{
			int data = theNode->mData;
			updateBeforeDelete(theNode);
			char deficiecyDirection = theNode == theNode->mParent->mLeftChild ? 'L' : 'R';
			IPPS23RBBTN *theParent = deleteNodeAndGetParent(theNode);
			drawTreeAndSave("remove/", "Remove" + to_string(data) + "-After-top-down-pass", data, theParent, deficiecyDirection);
			updateAfterDelete(theParent);
		}
		else
		{
			deleteDeg2Node(theNode);
		}
	}

	inline IPPS23RBBTN *deleteNodeAndGetParent(IPPS23RBBTN *theNode)
	{
		IPPS23RBBTN *theParent = theNode->mParent;
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
		return theParent;
	}

	void deleteLastInOrderNode()
	{
		drawTreeAndSave("remove/", "Remove" + to_string(mLastInOrderNode->mData) + "-Start", mLastInOrderNode->mData);
		char deficiecyDirection = mLastInOrderNode == mLastInOrderNode->mParent->mLeftChild ? 'L' : 'R';
		int data = mLastInOrderNode->mData;
		// start = clock();

		// IndexedBT updateBeforeDelete(node);
		mInOrderEnd->mLeftSize--;

		// PPS23RB updateBeforeDelete(node);
		IPPS23RBBTN *parentNode = mLastInOrderNode->mParent;
		this->mNilSentinel->mParent = parentNode;
		IPPS23RBBTN *theChild = nullptr;
		if (mLastInOrderNode->mLeftChild != this->mNilSentinel)
		{
			theChild = mLastInOrderNode->mLeftChild;
			theChild->mColor = IPPS23RBBTN::BLACK;
		}

		IPPS23RBBTN *theParent = deleteNodeAndGetParent(mLastInOrderNode);

		if (theChild != nullptr)
		{
			mLastInOrderNode = theChild;
		}
		else
		{
			mLastInOrderNode = theParent;
		}
		drawTreeAndSave("remove/", "Remove" + to_string(data) + "-After-top-down-pass", data, mLastInOrderNode, deficiecyDirection);

		// end_clock = clock();
		// removeTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

		// start = clock();
		updateAfterDelete(theParent);
		drawTreeAndSave("remove/", "Remove" + to_string(data) + "-After-Bottom-up-pass", data);

		// end_clock = clock();
		// timeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);
	}

	void deleteFirstInOrderNode()
	{
		drawTreeAndSave("remove/", "Remove" + to_string(mFirstInOrderNode->mData) + "-Start", mFirstInOrderNode->mData);
		char deficiecyDirection = mFirstInOrderNode == mFirstInOrderNode->mParent->mLeftChild ? 'L' : 'R';
		int data = mFirstInOrderNode->mData;
		// start = clock();

		// IndexedBT updateBeforeDelete(node);
		mGlobalLeftSize--;

		// PPS23RB updateBeforeDelete(node);
		IPPS23RBBTN *parentNode = mFirstInOrderNode->mParent;
		this->mNilSentinel->mParent = parentNode;
		IPPS23RBBTN *theChild = nullptr;
		if (mFirstInOrderNode->mRightChild != this->mNilSentinel)
		{
			theChild = mFirstInOrderNode->mRightChild;
			theChild->mColor = IPPS23RBBTN::BLACK;
		}

		IPPS23RBBTN *theParent = deleteNodeAndGetParent(mFirstInOrderNode);

		if (theChild != nullptr)
		{
			mFirstInOrderNode = theChild;
		}
		else
		{
			mFirstInOrderNode = theParent;
		}
		drawTreeAndSave("remove/", "Remove" + to_string(data) + "-After-top-down-pass", data, mFirstInOrderNode, deficiecyDirection);

		// end_clock = clock();
		// removeTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

		// start = clock();
		updateAfterDelete(theParent);
		drawTreeAndSave("remove/", "Remove" + to_string(data) + "-After-Bottom-up-pass", data);

		// end_clock = clock();
		// timeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);
	}
};
