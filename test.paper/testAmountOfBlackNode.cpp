// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>

#include "../src/InternalBinaryTreeNode.h"
#include "../src/InternalInOrderPreservingBinaryTreeNode.h"
#include "../src/InternalPureParitySeeking-23RedBlackBinaryTreeNode.h"
#include "../src/BinaryTree.h"
#include "../src/InOrderPreservingBinaryTree.h"
#include "../src/PureParitySeeking-23RedBlackBinaryTree.h"

#include "../test.sepehr/TrueInternalBinaryTreeNode.h"
#include "../test.sepehr/TrueInternalInOrderPreservingBinaryTreeNode.h"
#include "../test.sepehr/TrueInternalPureParitySeeking-23RedBlackBinaryTreeNode.h"
#include "../test.sepehr/TrueBinaryTree.h"
#include "../test.sepehr/TrueInOrderPreservingBinaryTree.h"
#include "../test.sepehr/TruePureParitySeeking-23RedBlackBinaryTree.h"

#include "../test.sepehr/TestPPSBTIteration.h"
#include "../test.sepehr/TestInsertionPPS23RBBT.h"
#include "../test.sepehr/TestDeletionPPS23RBBT.h"

using namespace std;

typedef PureParitySeeking23RedBlackBinaryTree<string, InternalPureParitySeeking23RedBlackBinaryTreeNode<string>> PPS23BTStudent;
typedef TruePureParitySeeking23RedBlackBinaryTree<string, TrueInternalPureParitySeeking23RedBlackBinaryTreeNode<string>> PPS23BBTTrue;

int main()
{
    clock_t start, end;
    int n = 10000;
    int deleteCount = 9000;

    PPS23BBTTrue *pps23rbBtTrue = new PPS23BBTTrue;
    PPS23BTStudent *pps23rbBtStudent = new PPS23BTStudent;

    int result = testInsertionPPS23RBBT(pps23rbBtTrue, pps23rbBtStudent, n);

    int depth = pps23rbBtStudent->depthCalc(pps23rbBtStudent->getRootNode(), 1);
    cout << "size: " << pps23rbBtStudent->size() << endl;
    cout << "depth: " << depth << endl;
    cout << "amount of black nodes: " << pps23rbBtStudent->testAmountOfBlackNode(pps23rbBtStudent->getRootNode(), 1) << endl;

    if (result == 100)
    {
        result = testDeletionPPS23RBBT(pps23rbBtTrue, pps23rbBtStudent, deleteCount);
    }

    depth = pps23rbBtStudent->depthCalc(pps23rbBtStudent->getRootNode(), 1);
    cout << "size: " << pps23rbBtStudent->size() << endl;
    cout << "depth after delete: " << depth << endl;
    cout << "amount of black nodes after delete: " << pps23rbBtStudent->testAmountOfBlackNode(pps23rbBtStudent->getRootNode(), 1) << endl;

    delete pps23rbBtTrue;
    delete pps23rbBtStudent;
    return 0;
}