
public class IndexedPPS23RBBinaryTreeNode<T> {
    protected enum COLOR {
        RED,
        BLACK
    };

    public IndexedPPS23RBBinaryTreeNode() {
        this.mLeftChild = null;
        this.mRightChild = null;
        this.mParent = null;
        this.mLeftSize = 0;
        this.mColor = COLOR.BLACK;
    }

    protected COLOR mColor;
    protected T mData;
    protected int mLeftSize;
    protected IndexedPPS23RBBinaryTreeNode<T> mParent;
    protected IndexedPPS23RBBinaryTreeNode<T> mLeftChild;
    protected IndexedPPS23RBBinaryTreeNode<T> mRightChild;

}
