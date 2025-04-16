// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <string>
#include <stack>
#include <sstream>

#include "../src/InternalBinaryTreeNode.h"
#include "../src/InternalInOrderPreservingBinaryTreeNode.h"
#include "../src/InternalIndexedBinaryTreeNode.h"
#include "../src/InternalPureParitySeeking-23RedBlackBinaryTreeNode.h"
#include "../src/InternalIndexedPPS23RedBlackBinaryTreeNode.h"

#include "../src/BinaryTree.h"
#include "../src/InOrderPreservingBinaryTree.h"
#include "../src/IndexedBinaryTree.h"
#include "../src/PureParitySeeking-23RedBlackBinaryTree.h"
#include "../src/IndexedPPS23RedBlackBinaryTree.h"

#include <iostream>

using namespace std;
typedef IndexedPPS23RedBlackBinaryTree<char, InternalIndexedPPS23RedBlackBinaryTreeNode<char>> CharBinaryTree;

char inOrder[] = {'g', 'd', 'h', 'l', 'a', 'e', 'i', 'k', 'c'};
char preOrder[] = {'l', 'd', 'g', 'h', 'e', 'a', 'k', 'i', 'c'};
char postOrder[] = {'g', 'h', 'd', 'a', 'i', 'c', 'k', 'e', 'l'};
char deleted[] = {'d', 'h', 'e', 'i', 'k'};

int leftSize[] = {0, 1, 0, 3, 0, 1, 0, 1, 0};
int leftSizeAfterDelete[] = {0, 1, 0, 1, 0};

int color[] = {1, 1, 1, 1, 1, 1, 1, 0, 1};
int colorAfterDelete[] = {1, 1, 1, 0, 1};

int arrSize = 9;
int arrSizeAfterDelete = 5;

bool insertCheck(CharBinaryTree *bt)
{
    //                                                     l
    //												/		      \
    //											d		            e
    //										/		\        	  /   \
    //								  	   g		 h           a      k
    //                                                                i   c
    bool result = true;
    CharBinaryTree::BinaryTreeNode btnHeaderRoot = bt->getHeaderRootNode().getRightChild();

    //------------------------------------
    bt->insertRootNode('a');
    CharBinaryTree::BinaryTreeNode btna = bt->getRootNode();

    //------------------------------------
    bt->insertLeftChild(btna, 'l');
    CharBinaryTree::BinaryTreeNode btnl = btna.getLeftChild();

    //------------------------------------
    bt->insertLeftChild(btnl, 'd');
    CharBinaryTree::BinaryTreeNode btnd = btnl.getLeftChild();

    if (bt->getLeftSize(btnl) != 1 || bt->getLeftSize(btna) != 0 ||
        bt->getLeftSize(btna) != 0)
    {
        result = false;
        return result;
    }

    //------------------------------------
    bt->insertRightChild(btna, 'c');
    CharBinaryTree::BinaryTreeNode btnc = btna.getRightChild();
    if (bt->getLeftSize(btnc) != 0 || bt->getLeftSize(btna) != 0)
    {
        result = false;
        return result;
    }

    //------------------------------------
    bt->insertLeftChild(btnc, 'e');
    CharBinaryTree::BinaryTreeNode btne = btnl.getRightChild();
    if (bt->getLeftSize(btne) != 1 || bt->getLeftSize(btna) != 0 ||
        bt->getLeftSize(btnc) != 0)
    {
        result = false;
        return result;
    }

    //------------------------------------
    bt->insertLeftChild(btnc, 'i');
    CharBinaryTree::BinaryTreeNode btni = btnc.getLeftChild();
    if (bt->getLeftSize(btnc) != 1)
    {
        result = false;
        return result;
    }

    //------------------------------------
    bt->insertLeftChild(btnd, 'g');
    CharBinaryTree::BinaryTreeNode btng = btnd.getLeftChild();
    if (bt->getLeftSize(btnl) != 2 || bt->getLeftSize(btnd) != 1 ||
        bt->getLeftSize(btng) != 0)
    {
        result = false;
        return result;
    }

    //------------------------------------
    bt->insertRightChild(btnd, 'h');
    CharBinaryTree::BinaryTreeNode btnh = btnd.getRightChild();
    if (bt->getLeftSize(btnl) != 3)
    {
        result = false;
        return result;
    }

    //------------------------------------
    try
    {
        bt->insertLeftChild(btnd, 'q');
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    //------------------------------------
    bt->insertRightChild(btni, 'k');
    CharBinaryTree::BinaryTreeNode btnk = btne.getRightChild();
    if (bt->getLeftSize(btnk) != 1 || bt->getLeftSize(btnc) != 0 ||
        bt->getLeftSize(btni) != 0)
    {
        result = false;
        return result;
    }

    return result;
}

bool deleteCheck(CharBinaryTree *bt)
{
    bool result = true;
    //                                                     l
    //												/		      \
    //											d		            e
    //										/		\        	  /   \
    //								  	   g		 h           a      k
    //                                                                i   c
    CharBinaryTree::BinaryTreeNode mPostOrderEnd = bt->getHeaderRootNode().getLeftChild();
    CharBinaryTree::BinaryTreeNode btnl = bt->getRootNode();
    CharBinaryTree::BinaryTreeNode btne = btnl.getRightChild();
    CharBinaryTree::BinaryTreeNode btna = btne.getLeftChild();
    CharBinaryTree::BinaryTreeNode btnk = btne.getRightChild();
    CharBinaryTree::BinaryTreeNode btni = btnk.getLeftChild();
    CharBinaryTree::BinaryTreeNode btnc = btnk.getRightChild();
    CharBinaryTree::BinaryTreeNode btnd = btnl.getLeftChild();
    CharBinaryTree::BinaryTreeNode btnh = btnd.getRightChild();
    CharBinaryTree::BinaryTreeNode btng = btnd.getLeftChild();

    bt->deleteLeftChild(btne);

    if (btnk.getParent() != btnl || btne.getParent() != btnk ||
        btni.getParent() != btne || bt->getColor(btni) != 0)
    {
        result = false;
        return result;
    }

    bt->deleteRightChild(mPostOrderEnd);
    btnh = btnl;

    if (btnh.getParent() != mPostOrderEnd || btnk.getParent() != btnh ||
        bt->getColor(btng) != 0 || bt->getColor(btnk) != 0)
    {
        result = false;
        return result;
    }

    bt->deleteRightChild(btnk);

    if (btni.getParent() != btnh || btnk.getParent() != btni ||
        btne.getParent() != btni || bt->getColor(btni) != 0 ||
        bt->getColor(btne) != 1 || bt->getColor(btnk) != 1)
    {
        result = false;
        return result;
    }

    bt->deleteLeftChild(btnd);

    if (bt->hasLeftChild(btnd) || bt->hasRightChild(btnd))
    {
        result = false;
        return result;
    }

    int i;
    cout << "\n**InOrder Iteration after delete some nodes:\nYours\tCorrect" << endl;

    CharBinaryTree::InOrderIterator itr = bt->inOrderBegin();
    CharBinaryTree::InOrderIterator end = bt->inOrderEnd();
    for (i = 0; itr != end; ++itr, ++i)
    {
        cout << *itr << "\t" << deleted[i] << endl;
        if (*itr != deleted[i])
        {
            result = false;
            break;
        }
    }

    if (i != arrSizeAfterDelete)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool inOrderCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**InOrder Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::InOrderIterator itr = bt->inOrderBegin();
    CharBinaryTree::InOrderIterator end = bt->inOrderEnd();
    for (i = 0; itr != end; ++itr, ++i)
    {
        cout << *itr << "\t" << inOrder[i] << endl;
        if (*itr != inOrder[i])
        {
            result = false;
            break;
        }
    }
    if (i != arrSize)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool inOrderReverseCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**InOrder Reverse Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::InOrderIterator itr = bt->inOrderReverseBegin();
    CharBinaryTree::InOrderIterator end = bt->inOrderReverseEnd();
    for (i = arrSize - 1; itr != end; --itr, --i)
    {
        cout << *itr << "\t" << inOrder[i] << endl;
        if (*itr != inOrder[i])
        {
            result = false;
            break;
        }
    }

    if (i != -1)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool preOrderCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**PreOrder Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::PreOrderIterator itr = bt->preOrderBegin();
    CharBinaryTree::PreOrderIterator end = bt->preOrderEnd();
    for (i = 0; itr != end; ++itr, ++i)
    {
        cout << *itr << "\t" << preOrder[i] << endl;
        if (*itr != preOrder[i])
        {
            result = false;
            break;
        }
    }
    if (i != arrSize)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool preOrderReverseCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**PreOrder Reverse Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::PreOrderIterator itr = bt->preOrderReverseBegin();
    CharBinaryTree::PreOrderIterator end = bt->preOrderReverseEnd();
    for (i = arrSize - 1; itr != end; --itr, --i)
    {
        cout << *itr << "\t" << preOrder[i] << endl;
        if (*itr != preOrder[i])
        {
            result = false;
            break;
        }
    }

    if (i != -1)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool postOrderCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**PostOrder Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::PostOrderIterator itr = bt->postOrderBegin();
    CharBinaryTree::PostOrderIterator end = bt->postOrderEnd();
    for (i = 0; itr != end; ++itr, ++i)
    {
        cout << *itr << "\t" << postOrder[i] << endl;
        if (*itr != postOrder[i])
        {
            result = false;
            break;
        }
    }

    if (i != arrSize)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool postOrderReverseCheck(CharBinaryTree *bt)
{
    int i;
    cout << "\n**PostOrder Reverse Iteration:\nYours\tCorrect" << endl;
    bool result = true;

    CharBinaryTree::PostOrderIterator itr = bt->postOrderReverseBegin();
    CharBinaryTree::PostOrderIterator end = bt->postOrderReverseEnd();
    for (i = arrSize - 1; itr != end; --itr, --i)
    {
        cout << *itr << "\t" << postOrder[i] << endl;
        if (*itr != postOrder[i])
        {
            result = false;
            break;
        }
    }
    if (i != -1)
    {
        result = 0;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool colorCheck(CharBinaryTree *bt, int status)
{
    int i;
    bool result = true;

    CharBinaryTree::InOrderIterator itr = bt->inOrderBegin();
    CharBinaryTree::InOrderIterator end = bt->inOrderEnd();
    cout << "\n**color:\nYours\tCorrect" << endl;

    for (i = 0; itr != end; ++itr, ++i)
    {
        if (status == 0)
        {
            cout << bt->getColor(itr.getBinaryTreeNode()) << "\t" << color[i] << endl;
            if (bt->getColor(itr.getBinaryTreeNode()) != color[i])
            {
                result = false;
                break;
            }
        }
        else
        {
            cout << bt->getColor(itr.getBinaryTreeNode()) << "\t" << colorAfterDelete[i] << endl;
            if (bt->getColor(itr.getBinaryTreeNode()) != colorAfterDelete[i])
            {
                result = false;
                break;
            }
        }
    }
    if (status == 0 && i != arrSize)
    {
        result = false;
        cout << "Iteration terminated immaturely.\n";
    }
    else if (i != arrSizeAfterDelete && status == 1)
    {
        result = false;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

bool leftSizeCheck(CharBinaryTree *bt, int status)
{
    int i;
    bool result = true;

    CharBinaryTree::InOrderIterator itr = bt->inOrderBegin();
    CharBinaryTree::InOrderIterator end = bt->inOrderEnd();
    cout << "\n**left size:\nYours\tCorrect" << endl;

    for (i = 0; itr != end; ++itr, ++i)
    {
        if (status == 0)
        {
            cout << bt->getLeftSize(itr.getBinaryTreeNode()) << "\t" << leftSize[i] << endl;
            if (bt->getLeftSize(itr.getBinaryTreeNode()) != leftSize[i])
            {
                result = false;
                break;
            }
        }
        else
        {
            cout << bt->getLeftSize(itr.getBinaryTreeNode()) << "\t" << leftSizeAfterDelete[i] << endl;
            if (bt->getLeftSize(itr.getBinaryTreeNode()) != leftSizeAfterDelete[i])
            {
                result = false;
                break;
            }
        }
    }
    if (status == 0 && i != arrSize)
    {
        result = false;
        cout << "Iteration terminated immaturely.\n";
    }
    else if (i != arrSizeAfterDelete && status == 1)
    {
        result = false;
        cout << "Iteration terminated immaturely.\n";
    }

    return result;
}

int main()
{
    int input;
    bool result = false;
    CharBinaryTree *bt = new CharBinaryTree;

    for (input = 0; input < 12; input++)
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
        case 1:
            cout << endl
                 << "1: inOrder Iteration" << endl;
            result = inOrderCheck(bt);
            break;
        case 2:
            cout << endl
                 << "2: inOrder Reverse Iteration" << endl;
            result = inOrderReverseCheck(bt);
            break;
        case 3:
            cout << endl
                 << "3: preOrder Iteration" << endl;
            result = preOrderCheck(bt);
            break;
        case 4:
            cout << endl
                 << "4: preOrder Reverse Iteration" << endl;
            result = preOrderReverseCheck(bt);
            break;
        case 5:
            cout << endl
                 << "5: postOrder Iteration" << endl;
            result = postOrderCheck(bt);
            break;
        case 6:
            cout << endl
                 << "6: postOrder Reverse Iteration" << endl;
            result = postOrderReverseCheck(bt);
            break;
        case 7:
            cout << endl
                 << "7: color check" << endl;
            result = colorCheck(bt, 0);
            break;
        case 8:
            cout << endl
                 << "7: left size check" << endl;
            result = leftSizeCheck(bt, 0);
            break;
        case 9:
            cout << endl
                 << "8: delete nodes" << endl;
            result = deleteCheck(bt);
            bt->draw(cout);
            cout << endl;
            break;
        case 10:
            cout << endl
                 << "9: color check after delete" << endl;
            result = colorCheck(bt, 1);
            break;
        case 11:
            cout << endl
                 << "9: left size check after delete" << endl;
            result = leftSizeCheck(bt, 1);
            break;
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
