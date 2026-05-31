
import java.util.Iterator;

@SuppressWarnings({ "rawtypes", "unchecked" })
public class IndexedPPS23RedBlackBinaryTree<T, IPPS23RBBTN extends IndexedPPS23RBBinaryTreeNode> {

    protected IPPS23RBBTN mRevInOrderEnd;
    protected IPPS23RBBTN mInOrderEnd;

    protected IPPS23RBBTN mNilSentinel;
    protected IPPS23RBBTN mLastInOrderNode;
    protected IPPS23RBBTN mFirstInOrderNode;
    protected int mGlobalLeftSize;

    protected int mSize;

    protected IndexedPPS23RedBlackBinaryTree() {
        mSize = 0;
        mGlobalLeftSize = 0;
        mNilSentinel = createInternalBinaryTreeNodeInstance();
        mRevInOrderEnd = createInternalBinaryTreeNodeInstance();
        mInOrderEnd = createInternalBinaryTreeNodeInstance();

        mRevInOrderEnd.mRightChild = mInOrderEnd;
        mRevInOrderEnd.mLeftChild = mNilSentinel;

        mInOrderEnd.mLeftChild = mNilSentinel;
        mInOrderEnd.mRightChild = mNilSentinel;

        mLastInOrderNode = mInOrderEnd;
        mFirstInOrderNode = mInOrderEnd;

        mRevInOrderEnd.mLeftSize = -1;
        mInOrderEnd.mLeftSize = 0;
    }

    protected IPPS23RBBTN createInternalBinaryTreeNodeInstance() {
        return (IPPS23RBBTN) new IndexedPPS23RBBinaryTreeNode<T>();
    }

    protected int size() {
        return mSize;
    }

    protected boolean isEmpty() {
        return mInOrderEnd.mLeftChild == mNilSentinel;
    }

    protected boolean hasLeftChild(IPPS23RBBTN node) {
        return node.mLeftChild != mNilSentinel;
    }

    protected boolean hasRightChild(IPPS23RBBTN node) {
        return node.mRightChild != mNilSentinel;
    }

    protected void insertRootNode(T data) throws IllegalAccessException {
        IPPS23RBBTN root;
        if (hasLeftChild(mInOrderEnd))
            throw new IllegalAccessException("Error: Root already exists.");
        root = createInternalBinaryTreeNodeInstance();
        root.mData = data;
        root.mParent = mInOrderEnd;
        mInOrderEnd.mLeftChild = root;

        root.mLeftChild = mNilSentinel;
        root.mRightChild = mNilSentinel;

        mLastInOrderNode = root;
        mFirstInOrderNode = root;

        mGlobalLeftSize = 0;
        mRevInOrderEnd.mLeftSize = -1;
        mInOrderEnd.mLeftSize = 0;
        mSize = 1;
        mInOrderEnd.mLeftSize++;
    }

    protected void insertLastInOrderNode(T data) {
        IPPS23RBBTN childNode = createInternalBinaryTreeNodeInstance();
        childNode.mData = data;
        childNode.mParent = mLastInOrderNode;
        childNode.mLeftChild = mNilSentinel;
        childNode.mRightChild = mNilSentinel;
        mLastInOrderNode.mRightChild = childNode;
        mSize++;
        mLastInOrderNode = childNode;

        mInOrderEnd.mLeftSize++;
        put_bottom_up_pass(childNode);
    }

    protected void insertFirstInOrderNode(T data) {
        IPPS23RBBTN childNode = createInternalBinaryTreeNodeInstance();
        childNode.mData = data;
        childNode.mParent = mFirstInOrderNode;
        childNode.mLeftChild = mNilSentinel;
        childNode.mRightChild = mNilSentinel;
        mFirstInOrderNode.mLeftChild = childNode;
        mSize++;
        mFirstInOrderNode = childNode;

        // update mGlobalLeftSize
        mGlobalLeftSize++;

        mFirstInOrderNode.mLeftSize -= mGlobalLeftSize;
        put_bottom_up_pass(childNode);
    }

    protected void insertLeftChild(IPPS23RBBTN parentNode, T data)
            throws IllegalAccessException {
        if (parentNode != null) {
            if (!hasLeftChild(parentNode)) {
                IPPS23RBBTN childNode = createInternalBinaryTreeNodeInstance();
                childNode.mData = data;
                childNode.mParent = parentNode;
                childNode.mLeftChild = mNilSentinel;
                childNode.mRightChild = mNilSentinel;
                parentNode.mLeftChild = childNode;
                mSize++;
                put_bottom_up_pass(childNode);
            } else {
                throw new IllegalAccessException(
                        "Can't insert a left child for a node which already has a left child.");
            }
        } else {
            throw new IllegalAccessException("Invalid Pointer.");
        }
    }

    protected void insertRightChild(IPPS23RBBTN parentNode, T data)
            throws IllegalAccessException {
        if (parentNode != null) {
            if (!hasRightChild(parentNode)) {
                IPPS23RBBTN childNode = createInternalBinaryTreeNodeInstance();
                childNode.mData = data;
                childNode.mParent = parentNode;
                childNode.mLeftChild = mNilSentinel;
                childNode.mRightChild = mNilSentinel;
                parentNode.mRightChild = childNode;
                mSize++;
                put_bottom_up_pass(childNode);
            } else {
                throw new IllegalAccessException(
                        "Can't insert a left child for a node which already has a left child.");
            }
        } else {
            throw new IllegalAccessException("Invalid Pointer.");
        }
    }

    // protected void deleteLeftChild(IndexedPPS23RBBinaryTreeNode<T, IPPS23RBBTN>
    // parent) throws IllegalAccessException // Only
    // // leaf

    // {
    // IPPS23RBBTN parentNode = parent.mActualNode;
    // IPPS23RBBTN theNode = (IPPS23RBBTN) parent.getLeftChild().mActualNode;
    // deleteNode(parentNode, theNode);
    // }

    // protected void deleteRightChild(IndexedPPS23RBBinaryTreeNode<T, IPPS23RBBTN>
    // parent) throws IllegalAccessException // Only

    // {
    // IPPS23RBBTN parentNode = parent.mActualNode;
    // IPPS23RBBTN theNode = (IPPS23RBBTN) parent.getRightChild().mActualNode;
    // deleteNode(parentNode, theNode);
    // }
    private void updateAfterRR(IPPS23RBBTN node) {
        // IndexedBT updateAfterRR(node);
        IPPS23RBBTN A = (IPPS23RBBTN) node.mLeftChild;
        node.mLeftSize += A.mLeftSize + 1; // B.mLeftSize = [C.mLeftSize + 1](is B.mLeftSize) + A.mLeftSize + 1

        // PPS23RB updateAfterRR(node);
        IPPS23RBBTN.COLOR c = node.mColor;
        node.mColor = node.mLeftChild.mColor;
        node.mLeftChild.mColor = c;
    }

    private IPPS23RBBTN RR(IPPS23RBBTN A) {
        // write your code here
        IPPS23RBBTN B = (IPPS23RBBTN) A.mRightChild;
        A.mRightChild = B.mLeftChild;

        if (hasLeftChild(B)) {
            B.mLeftChild.mParent = A;
        }

        if (A.mParent.mLeftChild == A) {
            A.mParent.mLeftChild = B;
        } else {
            A.mParent.mRightChild = B;
        }

        B.mParent = A.mParent;
        A.mParent = B;
        B.mLeftChild = A;

        updateAfterRR(B);

        return B;
    }

    private void updateAfterLL(IPPS23RBBTN node) {
        // IndexedBT updateAfterLL(node);
        IPPS23RBBTN A = (IPPS23RBBTN) node.mRightChild;
        A.mLeftSize -= node.mLeftSize + 1;

        // PPS23RB updateAfterLL(node);
        IPPS23RBBTN.COLOR c = node.mColor;
        node.mColor = node.mRightChild.mColor;
        node.mRightChild.mColor = c;
    }

    private IPPS23RBBTN LL(IPPS23RBBTN A) {
        // write your code here
        IPPS23RBBTN B = (IPPS23RBBTN) A.mLeftChild;
        A.mLeftChild = B.mRightChild;

        if (hasRightChild(B)) {
            B.mRightChild.mParent = A;
        }
        if (A.mParent.mLeftChild == A) {
            A.mParent.mLeftChild = B;
        } else {
            A.mParent.mRightChild = B;
        }

        B.mParent = A.mParent;
        A.mParent = B;
        B.mRightChild = A;

        updateAfterLL(B);
        return B;
    }

    private void put_bottom_up_pass(IPPS23RBBTN deficientNode) {
        IPPS23RBBTN parentNode, siblingNode;
        while (true) // deficientNode.mColor is certainly BLACK
        {
            parentNode = (IPPS23RBBTN) deficientNode.mParent;
            if (parentNode.mColor == IPPS23RBBTN.COLOR.RED) {
                if (parentNode == parentNode.mParent.mLeftChild) {
                    if (deficientNode == parentNode.mRightChild) // Rule (b.2)
                    {
                        deficientNode = parentNode;
                        parentNode = this.RR(parentNode);
                    }
                    parentNode = this.LL((IPPS23RBBTN) parentNode.mParent); // Rule (b.1)
                } else {
                    if (deficientNode == parentNode.mLeftChild) // Rule (b.2)
                    {
                        deficientNode = parentNode;
                        parentNode = this.LL(parentNode);
                    }
                    parentNode = this.RR((IPPS23RBBTN) parentNode.mParent); // Rule (b.1)
                }
            }
            siblingNode = (deficientNode == parentNode.mLeftChild) ? (IPPS23RBBTN) parentNode.mRightChild
                    : (IPPS23RBBTN) parentNode.mLeftChild;

            if (siblingNode.mColor == IPPS23RBBTN.COLOR.RED) // Rule (a.2)
            {

                siblingNode.mColor = IPPS23RBBTN.COLOR.BLACK;
                deficientNode = parentNode;
            } else if (parentNode.mColor == IPPS23RBBTN.COLOR.BLACK)
                break;
        }
        if (deficientNode != this.mInOrderEnd.mLeftChild) {
            deficientNode.mColor = IPPS23RBBTN.COLOR.RED; // Rule (a.1)
        } // x.mColor is certainly BLACK
    }

    private IPPS23RBBTN fixUp(IPPS23RBBTN x, IPPS23RBBTN z) {
        if (z.mLeftChild.mColor == IPPS23RBBTN.COLOR.RED || z.mRightChild.mColor == IPPS23RBBTN.COLOR.RED) {
            if (z == x.mRightChild) {
                if (z.mRightChild.mColor == IPPS23RBBTN.COLOR.BLACK) // Fixing rule (a)
                    this.LL(z);
                x = this.RR(x); // Fixing rule (b)
            } else {
                if (z.mLeftChild.mColor == IPPS23RBBTN.COLOR.BLACK) // Fixing rule (a)
                    this.RR(z);
                x = this.LL(x); // Fixing rule (b)
            }
            x.mLeftChild.mColor = IPPS23RBBTN.COLOR.BLACK; // Fixing rule (c)
            x.mRightChild.mColor = IPPS23RBBTN.COLOR.BLACK; // Fixing rule (c)
            x = (IPPS23RBBTN) this.mInOrderEnd.mLeftChild; // terminate the bottom up pass
        }
        return x;
    }

    private IPPS23RBBTN applyParitySeekingRules(IPPS23RBBTN x) {
        IPPS23RBBTN p = (IPPS23RBBTN) x.mParent;
        IPPS23RBBTN y = x == p.mLeftChild ? (IPPS23RBBTN) p.mRightChild : (IPPS23RBBTN) p.mLeftChild;
        if (y.mColor == IPPS23RBBTN.COLOR.RED) // Parity-seeking Rule (c): Rotate to have a black sibling
            if (x == p.mLeftChild)
                this.RR(p);
            else
                this.LL(p);
        else { // Parity-seeking Rule (b): Make the sibling red
            y.mColor = IPPS23RBBTN.COLOR.RED;
            x = p;
            x = fixUp(x, y);
        }
        return x;
    }

    private void remove_bottom_up_pass(IPPS23RBBTN x) {
        while (x != this.mInOrderEnd.mLeftChild && x.mColor == IPPS23RBBTN.COLOR.BLACK) {
            x = applyParitySeekingRules(x);
        }
        x.mColor = IPPS23RBBTN.COLOR.BLACK; // Parity-seeking Rule (a)
    }

    private void updateAfterDelete(IPPS23RBBTN parentNode) {
        if ((hasLeftChild(parentNode) && !hasRightChild(parentNode)) ||
                (!hasLeftChild(parentNode) && hasRightChild(parentNode))) {
            this.mNilSentinel.mParent = parentNode;
            remove_bottom_up_pass(this.mNilSentinel);
            this.mNilSentinel.mParent = null;
        }
    }

    private IPPS23RBBTN getActualDeleteNode(IPPS23RBBTN theNode) {
        IPPS23RBBTN actualDeleteNode = theNode;
        if (hasLeftChild(theNode)) {
            theNode.mLeftSize--;
            actualDeleteNode = (IPPS23RBBTN) theNode.mLeftChild;
            while (hasRightChild(actualDeleteNode)) {
                actualDeleteNode = (IPPS23RBBTN) actualDeleteNode.mRightChild;
            }
            theNode.mData = actualDeleteNode.mData;
            if (hasLeftChild(actualDeleteNode)) {
                actualDeleteNode.mData = actualDeleteNode.mLeftChild.mData;
                actualDeleteNode.mLeftSize--;
                actualDeleteNode = (IPPS23RBBTN) actualDeleteNode.mLeftChild;
            }
            if (actualDeleteNode == mFirstInOrderNode) {
                // mGlobalLeftSize--;
                mFirstInOrderNode = (IPPS23RBBTN) actualDeleteNode.mParent;
            }
        } else if (hasRightChild(theNode)) {
            actualDeleteNode = (IPPS23RBBTN) theNode.mRightChild;
            if (actualDeleteNode == mLastInOrderNode) {
                mLastInOrderNode = theNode;
            }
            theNode.mData = actualDeleteNode.mData;
        }
        return actualDeleteNode;
    }

    protected IPPS23RBBTN deleteNodeAndGetParent(IPPS23RBBTN theNode) {
        IPPS23RBBTN theParent = (IPPS23RBBTN) theNode.mParent;

        if (theParent.mRightChild == theNode)
            theParent.mRightChild = mNilSentinel;
        else
            theParent.mLeftChild = mNilSentinel;

        mSize--;
        return theParent;
    }

    protected void deleteNode(IPPS23RBBTN theNode) throws IllegalAccessException {

        IPPS23RBBTN actualDeleteNode = getActualDeleteNode(theNode);

        IPPS23RBBTN theParent = deleteNodeAndGetParent(actualDeleteNode);
        updateAfterDelete(theParent);
    }

    protected void deleteLastInOrderNode() {
        IPPS23RBBTN actualDeleteNode = getActualDeleteNode(mLastInOrderNode);

        mInOrderEnd.mLeftSize--;

        IPPS23RBBTN theParent = deleteNodeAndGetParent(actualDeleteNode);
        mLastInOrderNode = theParent;

        updateAfterDelete(mLastInOrderNode);
    }

    protected void deleteFirstInOrderNode() {

        IPPS23RBBTN actualDeleteNode = getActualDeleteNode(mFirstInOrderNode);
        if (actualDeleteNode != mFirstInOrderNode) {
            mFirstInOrderNode.mLeftSize++;
        }

        mGlobalLeftSize--;

        IPPS23RBBTN theParent = deleteNodeAndGetParent(actualDeleteNode);
        mFirstInOrderNode = theParent;

        updateAfterDelete(mFirstInOrderNode);
    }

    protected Iterator<T> forwardInOrderIterator() {
        Iterator<T> itr = new BinaryTreeForwardInOrderIterator(this);
        itr.next();
        return itr;
    }

    protected Iterator<T> backwardInOrderIterator() {
        Iterator<T> itr = new BinaryTreeBackwardInOrderIterator(this);
        itr.next();
        return itr;
    }
}
