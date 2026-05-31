// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include <assert.h>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <queue>

#include "../src.generate.drawings/IndexedPPS23RBBinaryTreeNode.h"
#include "../src.generate.drawings/IndexedPPS23RedBlackBinaryTree.h"
#include "../src.generate.drawings/EfficientList.h"

using namespace std;
int *values;
int *indexes;
int *deleteIndexes;

void insertToEfficientList(EfficientList<int> *ell, int size)
{
    for (int i = 0; i < size; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        ell->insert(indexes[i], values[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
}

void removeFromEfficientList(EfficientList<int> *ell, int deleteIndexesSize)
{
    for (int i = 0; i < deleteIndexesSize; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        ell->remove(deleteIndexes[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
}

int main()
{

    int input;
    int size = 20;
    values = new int[size];
    indexes = new int[size];
    deleteIndexes = new int[2];
    for (int i = 0; i < size; i++)
    {
        values[i] = i + 1;
        indexes[i] = i;
    }

    EfficientList<int> *ell;

    cout << "The test has started now with " << size << " insertions and " << size / 2 << " deletions:" << endl;
    for (input = 4; input < 6; input++)
    {
        switch (input)
        {
        case 0: // insert tests
            cout << endl
                 << "1: test efficient list push_back insert" << endl;
            ell = new EfficientList<int>;
            insertToEfficientList(ell, size);
            break;
        case 1: // remove tests
            cout << endl
                 << "2: test efficient list pop_back" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = size - (i + 1);
            }
            removeFromEfficientList(ell, size / 2);
            break;
        case 2: // insert tests
            cout << endl
                 << "3: test efficient list push_front" << endl;
            ell = new EfficientList<int>;
            for (int i = 0; i < size; i++)
            {
                indexes[i] = 0;
            }
            insertToEfficientList(ell, size);
            break;
        case 3: // remove tests
            cout << endl
                 << "4: test efficient list pop_front" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = 0;
            }
            removeFromEfficientList(ell, size / 2);
            break;
        case 4: // insert tests
            cout << endl
                 << "5: test efficient list random indices insert" << endl;
            ell = new EfficientList<int>;
            for (int i = 0; i < size; i++)
            {
                indexes[i] = rand() % (i + 1);
            }
            insertToEfficientList(ell, size);
            break;
        case 5: // remove tests
            cout << endl
                 << "6: test efficient list random indices remove" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = rand() % (size - (i + 1));
            }
            removeFromEfficientList(ell, size / 2);
            break;
        }
    }

    cout << "Your code passed all the tests." << endl;
    // int dummy;
    // cin >> dummy;

    delete ell;
    // delete vec;
    // delete lst;
    return 0;
}
