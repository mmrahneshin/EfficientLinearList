
import java.util.Iterator;

@SuppressWarnings({ "rawtypes", "unchecked" })
public class BinaryTreeForwardInOrderIterator<T, IPPS23RBBTN extends IndexedPPS23RBBinaryTreeNode>
		implements Iterator<T> {
	private IPPS23RBBTN mCurrentNode;
	private IndexedPPS23RedBlackBinaryTree<T, IPPS23RBBTN> mBinaryTree;

	public BinaryTreeForwardInOrderIterator() {
	}

	public BinaryTreeForwardInOrderIterator(IndexedPPS23RedBlackBinaryTree<T, IPPS23RBBTN> binaryTree) {
		mBinaryTree = binaryTree;
		mCurrentNode = binaryTree.mFirstInOrderNode;
	}

	@Override
	public T next() {
		T data;
		data = (T) mCurrentNode.mData;
		if (mCurrentNode.mRightChild != null) {
			mCurrentNode = (IPPS23RBBTN) mCurrentNode.mRightChild;
			while (mCurrentNode.mLeftChild != null) {
				mCurrentNode = (IPPS23RBBTN) mCurrentNode.mLeftChild;
			}
		} else {
			IPPS23RBBTN lastNode = mCurrentNode;
			do {
				lastNode = mCurrentNode;
				mCurrentNode = (IPPS23RBBTN) mCurrentNode.mParent;
			} while (mCurrentNode.mLeftChild != lastNode);
		}

		return data;
	}

	@Override
	public boolean hasNext() {
		return mCurrentNode != mBinaryTree.mInOrderEnd;
	}

	public T getData() {
		return (T) mCurrentNode.mData;
	}
}
