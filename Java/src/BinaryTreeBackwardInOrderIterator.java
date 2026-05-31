
import java.util.Iterator;

@SuppressWarnings({ "rawtypes", "unchecked" })
public class BinaryTreeBackwardInOrderIterator<T, IPPS23RBBTN extends IndexedPPS23RBBinaryTreeNode>
		implements Iterator<T> {
	private IPPS23RBBTN mCurrentNode;
	private IndexedPPS23RedBlackBinaryTree<T, IPPS23RBBTN> mBinaryTree;

	public BinaryTreeBackwardInOrderIterator() {
	}

	public BinaryTreeBackwardInOrderIterator(IndexedPPS23RedBlackBinaryTree<T, IPPS23RBBTN> binaryTree) {
		mBinaryTree = binaryTree;
		mCurrentNode = mBinaryTree.mLastInOrderNode;
	}

	@Override
	public T next() {
		T data;
		data = (T) mCurrentNode.mData;
		if (mCurrentNode.mLeftChild != null) {
			mCurrentNode = (IPPS23RBBTN) mCurrentNode.mLeftChild;
			while (mCurrentNode.mRightChild != null) {
				mCurrentNode = (IPPS23RBBTN) mCurrentNode.mRightChild;
			}
		} else {
			IPPS23RBBTN lastNode = mCurrentNode;
			do {
				lastNode = mCurrentNode;
				mCurrentNode = (IPPS23RBBTN) mCurrentNode.mParent;
			} while (mCurrentNode.mRightChild != lastNode);
		}

		return data;
	}

	@Override
	public boolean hasNext() {
		return mCurrentNode != mBinaryTree.mRevInOrderEnd;
	}

	public T getData() {
		return (T) mCurrentNode.mData;
	}
}
