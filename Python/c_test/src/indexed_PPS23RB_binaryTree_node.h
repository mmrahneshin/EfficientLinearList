#ifndef INDEXED_PPS23RB_BINARYTREE_NODE_H
#define INDEXED_PPS23RB_BINARYTREE_NODE_H
#ifdef __cplusplus
extern "C"
{
#endif

    // Enum for node color
    typedef enum
    {
        RED = 0,
        BLACK = 1
    } COLOR;

    typedef struct IndexedPPS23RBBinaryTreeNode
    {
        COLOR mColor;
        int mData;
        int mLeftSize;

        struct IndexedPPS23RBBinaryTreeNode *mLeftChild;
        struct IndexedPPS23RBBinaryTreeNode *mRightChild;
        struct IndexedPPS23RBBinaryTreeNode *mParent;
    } IndexedPPS23RBBinaryTreeNode;

    IndexedPPS23RBBinaryTreeNode *ipps23rbbt_new_node(int data)
    {
        IndexedPPS23RBBinaryTreeNode *node = (IndexedPPS23RBBinaryTreeNode *)malloc(sizeof(IndexedPPS23RBBinaryTreeNode));

        if (!node)
        {
            return nullptr;
        }

        node->mLeftChild = nullptr;
        node->mRightChild = nullptr;
        node->mParent = nullptr;
        node->mLeftSize = 0;
        node->mColor = BLACK;
        node->mData = data;

        return node;
    }

    void ipps23rbbt_node_free(IndexedPPS23RBBinaryTreeNode *node)
    {
        free(node);
    }

#ifdef __cplusplus
}
#endif
#endif // INDEXED_PPS23RB_BINARYTREE_NODE_H
