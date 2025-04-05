// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "../src/InternalBinaryTreeNode.h"
#include "../src/InternalInOrderPreservingBinaryTreeNode.h"
#include "../src/InternalPureParitySeeking-23RedBlackBinaryTreeNode.h"
#include "../src/BinaryTree.h"
#include "../src/InOrderPreservingBinaryTree.h"
#include "../src/PureParitySeeking-23RedBlackBinaryTree.h"

#include <iostream>
#include <string>

using namespace std;
typedef PureParitySeeking23RedBlackBinaryTree<float, InternalPureParitySeeking23RedBlackBinaryTreeNode<float>> StringBinaryTree;

string inOrder[] = {"g", "d", "h", "l", "a", "e", "i", "k", "c"};
string preOrder[] = {"l", "d", "g", "h", "e", "a", "k", "i", "c"};
string postOrder[] = {"g", "h", "d", "a", "i", "c", "k", "e", "l"};
string deleted[] = {"d", "h", "e", "i", "k"};
int balanceFactor[] = {1, 1, 1, 1, 1, 1, 1, 0, 1};
int balanceFactorAfterDelete[] = {1, 1, 1, 0, 1};
int arrSize = 9;
int arrSizeAfterDelete = 5;

bool insertCheck(StringBinaryTree *bt)
{
    //                                                     l
    //												/		      \
    //											d		            e
    //										/		\        	  /   \
    //								  	   g		 h           a      k
    //                                                                i   c
    bool result = true;
    StringBinaryTree::BinaryTreeNode btnHeaderRoot = bt->getHeaderRootNode().getRightChild();

    //------------------------------------
    bt->insertRootNode(1.1);
    StringBinaryTree::BinaryTreeNode btna = bt->getRootNode();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btna) << endl;
    //------------------------------------
    bt->insertLeftChild(btna, 1);
    StringBinaryTree::BinaryTreeNode btnl = btna.getLeftChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btnl) << endl;
    //------------------------------------
    bt->insertLeftChild(btnl, 1);
    StringBinaryTree::BinaryTreeNode btnd = btnl.getLeftChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btnd) << endl;
    if (btnd.getParent() != btnl || btnl.getParent() != btnHeaderRoot || btna.getParent() != btnl)
    {
        result = false;
        return result;
    }
    //------------------------------------
    bt->insertRightChild(btna, 1);
    StringBinaryTree::BinaryTreeNode btnc = btna.getRightChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btnc) << endl;
    //------------------------------------
    bt->insertLeftChild(btnc, 1);
    StringBinaryTree::BinaryTreeNode btne = btnl.getRightChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btne) << endl;
    if (btnc.getParent() != btne || btna.getParent() != btne)
    {
        result = false;
        return result;
    }
    //------------------------------------
    bt->insertLeftChild(btnc, 1);
    StringBinaryTree::BinaryTreeNode btni = btnc.getLeftChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btni) << endl;
    //------------------------------------
    bt->insertLeftChild(btnd, 1);
    StringBinaryTree::BinaryTreeNode btng = btnd.getLeftChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btng) << endl;
    //------------------------------------
    bt->insertRightChild(btnd, 1);
    StringBinaryTree::BinaryTreeNode btnh = btnd.getRightChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btnh) << endl;
    //------------------------------------

    try
    {
        bt->insertLeftChild(btnd, 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //------------------------------------
    bt->insertRightChild(btni, 1);
    StringBinaryTree::BinaryTreeNode btnk = btne.getRightChild();
    // bt->draw(cout);
    // cout << endl;
    // cout << bt->getColor(btnk) << endl;
    if (btni.getParent() != btnk || btnc.getParent() != btnk)
    {
        result = false;
        return result;
    }
    //------------------------------------

    cout << bt->testAmountOfBlackNode(bt->getRootNode(), 1) << endl;
    return result;
}

// bool deleteCheck(StringBinaryTree *bt)
// {

//     bool result = true;
//     //                                                     l
//     //												/		      \
//     //											d		            e
//     //										/		\        	  /   \
//     //								  	   g		 h           a      k
//     //                                                                i   c
//     StringBinaryTree::BinaryTreeNode mInOrderEnd = bt->getHeaderRootNode().getRightChild();
//     StringBinaryTree::BinaryTreeNode btnl = bt->getRootNode();
//     StringBinaryTree::BinaryTreeNode btne = btnl.getRightChild();
//     StringBinaryTree::BinaryTreeNode btna = btne.getLeftChild();
//     StringBinaryTree::BinaryTreeNode btnk = btne.getRightChild();
//     StringBinaryTree::BinaryTreeNode btni = btnk.getLeftChild();
//     StringBinaryTree::BinaryTreeNode btnc = btnk.getRightChild();
//     StringBinaryTree::BinaryTreeNode btnd = btnl.getLeftChild();
//     StringBinaryTree::BinaryTreeNode btnh = btnd.getRightChild();
//     StringBinaryTree::BinaryTreeNode btng = btnd.getLeftChild();

//     bt->deleteLeftChild(btne);
//     // bt->draw(cout);
//     // cout << endl;
//     // cout << bt->getColor(btnk) << endl;
//     // cout << bt->getColor(btni) << endl;

//     if (btnk.getParent() != btnl || btne.getParent() != btnk ||
//         btni.getParent() != btne || bt->getColor(btni) != 0)
//     {
//         result = false;
//         return result;
//     }

//     bt->deleteLeftChild(mInOrderEnd);
//     btnh = btnl;
//     // bt->draw(cout);
//     // cout << endl;
//     // cout << bt->getColor(btng) << endl;
//     // cout << bt->getColor(btnh) << endl;
//     if (btnh.getParent() != mInOrderEnd || btnk.getParent() != btnh ||
//         bt->getColor(btng) != 0 || bt->getColor(btnk) != 0)
//     {
//         result = false;
//         return result;
//     }

//     bt->deleteRightChild(btnk);
//     // bt->draw(cout);
//     // cout << endl;
//     // cout << bt->getColor(btni) << endl;
//     // cout << bt->getColor(btne) << endl;
//     // cout << bt->getColor(btnk) << endl;
//     if (btni.getParent() != btnh || btnk.getParent() != btni ||
//         btne.getParent() != btni || bt->getColor(btni) != 0 ||
//         bt->getColor(btne) != 1 || bt->getColor(btnk) != 1)
//     {
//         result = false;
//         return result;
//     }

//     bt->deleteLeftChild(btnd);
//     // bt->draw(cout);
//     // cout << endl;

//     if (bt->hasLeftChild(btnd) || bt->hasRightChild(btnd))
//     {
//         result = false;
//         return result;
//     }

//     int i;
//     cout << "\n**Inorder Iteration after delete some nodes:\nYours\tCorrect" << endl;

//     StringBinaryTree::InOrderIterator itr = bt->inOrderBegin();
//     StringBinaryTree::InOrderIterator end = bt->inOrderEnd();
//     for (i = 0; itr != end; ++itr, ++i)
//     {
//         cout << *itr << "\t" << deleted[i] << endl;
//         if (*itr != deleted[i])
//         {
//             result = false;
//             break;
//         }
//     }

//     if (i != arrSizeAfterDelete)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     cout << bt->testAmountOfBlackNode(bt->getRootNode(), 1) << endl;

//     return result;
// }

// bool inOrderCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**Inorder Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::InOrderIterator itr = bt->inOrderBegin();
//     StringBinaryTree::InOrderIterator end = bt->inOrderEnd();
//     for (i = 0; itr != end; ++itr, ++i)
//     {
//         cout << *itr << "\t" << inOrder[i] << endl;
//         if (*itr != inOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }
//     if (i != arrSize)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool inOrderReverseCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**Inorder Reverse Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::InOrderIterator itr = bt->inOrderReverseBegin();
//     StringBinaryTree::InOrderIterator end = bt->inOrderReverseEnd();
//     for (i = arrSize - 1; itr != end; --itr, --i)
//     {
//         cout << *itr << "\t" << inOrder[i] << endl;
//         if (*itr != inOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }

//     if (i != -1)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool preOrderCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**PreOrder Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::PreOrderIterator itr = bt->preOrderBegin();
//     StringBinaryTree::PreOrderIterator end = bt->preOrderEnd();
//     for (i = 0; itr != end; ++itr, ++i)
//     {
//         cout << *itr << "\t" << preOrder[i] << endl;
//         if (*itr != preOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }
//     if (i != arrSize)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool preOrderReverseCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**PreOrder Reverse Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::PreOrderIterator itr = bt->preOrderReverseBegin();
//     StringBinaryTree::PreOrderIterator end = bt->preOrderReverseEnd();
//     for (i = arrSize - 1; itr != end; --itr, --i)
//     {
//         cout << *itr << "\t" << preOrder[i] << endl;
//         if (*itr != preOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }

//     if (i != -1)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool postOrderCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**PostOrder Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::PostOrderIterator itr = bt->postOrderBegin();
//     StringBinaryTree::PostOrderIterator end = bt->postOrderEnd();
//     for (i = 0; itr != end; ++itr, ++i)
//     {
//         cout << *itr << "\t" << postOrder[i] << endl;
//         if (*itr != postOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }

//     if (i != arrSize)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool postOrderReverseCheck(StringBinaryTree *bt)
// {
//     int i;
//     cout << "\n**PostOrder Reverse Iteration:\nYours\tCorrect" << endl;
//     bool result = true;

//     StringBinaryTree::PostOrderIterator itr = bt->postOrderReverseBegin();
//     StringBinaryTree::PostOrderIterator end = bt->postOrderReverseEnd();
//     for (i = arrSize - 1; itr != end; --itr, --i)
//     {
//         cout << *itr << "\t" << postOrder[i] << endl;
//         if (*itr != postOrder[i])
//         {
//             result = false;
//             break;
//         }
//     }
//     if (i != -1)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

// bool colorCheck(StringBinaryTree *bt, int status)
// {
//     int i;
//     bool result = true;

//     StringBinaryTree::InOrderIterator itr = bt->inOrderBegin();
//     StringBinaryTree::InOrderIterator end = bt->inOrderEnd();
//     cout << "\n**balance factor:\nYours\tCorrect" << endl;

//     for (i = 0; itr != end; ++itr, ++i)
//     {
//         if (status == 0)
//         {
//             cout << bt->getColor(itr.getBinaryTreeNode()) << "\t" << balanceFactor[i] << endl;
//             if (bt->getColor(itr.getBinaryTreeNode()) != balanceFactor[i])
//             {
//                 result = false;
//                 break;
//             }
//         }
//         else
//         {
//             cout << bt->getColor(itr.getBinaryTreeNode()) << "\t" << balanceFactorAfterDelete[i] << endl;
//             if (bt->getColor(itr.getBinaryTreeNode()) != balanceFactorAfterDelete[i])
//             {
//                 result = false;
//                 break;
//             }
//         }
//     }
//     if (status == 0 && i != arrSize)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }
//     else if (i != arrSizeAfterDelete && status == 1)
//     {
//         result = 0;
//         cout << "Iteration terminated immaturely.\n";
//     }

//     return result;
// }

int main()
{
    int input;
    bool result = false;
    StringBinaryTree *bt = new StringBinaryTree;

    for (input = 0; input < 10; input++)
    {
        switch (input)
        {
        case 0:
            cout << endl
                 << "0: insert" << endl;
            result = insertCheck(bt);
            bt->setNodeDisplayWidth(1); // we can delete mNodeDisplayWidth
            bt->draw(cout);
            cout << endl;
            break;
            // case 1:
            //     cout << endl
            //          << "1: inOrder Iteration" << endl;
            //     result = inOrderCheck(bt);
            //     break;
            // case 2:
            //     cout << endl
            //          << "2: inOrder Reverse Iteration" << endl;
            //     result = inOrderReverseCheck(bt);
            //     break;
            // case 3:
            //     cout << endl
            //          << "3: preOrder Iteration" << endl;
            //     result = preOrderCheck(bt);
            //     break;
            // case 4:
            //     cout << endl
            //          << "4: preOrder Reverse Iteration" << endl;
            //     result = preOrderReverseCheck(bt);
            //     break;
            // case 5:
            //     cout << endl
            //          << "5: postOrder Iteration" << endl;
            //     result = postOrderCheck(bt);
            //     break;
            // case 6:
            //     cout << endl
            //          << "6: postOrder Reverse Iteration" << endl;
            //     result = postOrderReverseCheck(bt);
            //     break;
            // case 7:
            //     cout << endl
            //          << "7: balance factor check" << endl;
            //     result = colorCheck(bt, 0);
            //     break;
            // case 8:
            //     cout << endl
            //          << "8: delete nodes" << endl;
            //     result = deleteCheck(bt);
            //     bt->draw(cout);
            //     cout << endl;
            //     break;
            // case 9:
            //     cout << endl
            //          << "9: balance factor check after delete" << endl;
            //     result = colorCheck(bt, 1);
            //     break;
        }

        if (result)
            cout << "** That was correct!" << endl;
        else
        {
            cout << "** Doesn't match." << endl;
            cout << "Your code did not pass the tests." << endl;
            int dummy;
            cin >> dummy;
            return 0;
        }
    }

    cout << "Your code passed all the tests." << endl;
    int dummy;
    cin >> dummy;

    delete bt;
    return 0;
}
