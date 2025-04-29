// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <stack>
#include <sstream>
#include <optional>

#include "../src/IndexedPPS23RBBinaryTreeNode.h"
#include "../src/IndexedPPS23RedBlackBinaryTree.h"
#include "../src/EfficientLinearList.h"

#include <vector>
#include <list>

using namespace std;
int *values;
int *indexes;
int *deleteIndexes;
clock_t start, end_clock;
double timeTaken;

void insertToEfficientLinearList(EfficientLinearList<int> *ell, int size)
{
    start = clock();
    for (int i = 0; i < size; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        ell->insert(indexes[i], values[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken efficient linear list: " << timeTaken << endl;
}

void insertToVector(vector<int> *vec, int size)
{
    start = clock();
    int i;
    for (i = 0; i < size; i++)
    {
        vec->insert(vec->begin() + indexes[i], values[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken vector: " << timeTaken << endl;
}

void pushFrontToList(list<int> *lst, int size)
{
    start = clock();
    for (int i = 0; i < size; i++)
    {
        lst->push_front(values[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken list (push_front): " << timeTaken << endl;
}

void pushBackToList(list<int> *lst, int size)
{
    start = clock();
    for (int i = 0; i < size; i++)
    {
        lst->push_back(values[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken list (push_back): " << timeTaken << endl;
}

bool valueCheck(EfficientLinearList<int> *ell, vector<int> *vec, int size)
{

    bool result = true;
    // cout << "\n**efficient linear list :\nYours\tCorrect" << endl;
    double ellTimeTaken = 0;
    double vectorTimeTaken = 0;
    int ellValue, vectorValue;
    for (int i = 0; i < size; i++)
    {
        // cout << (*ell)[i] << "\t" << (*vec)[i] << endl;
        start = clock();
        ellValue = (*ell)[i];
        end_clock = clock();
        ellTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

        start = clock();
        vectorValue = (*vec)[i];
        end_clock = clock();
        vectorTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

        if (ellValue != vectorValue)
        {
            result = false;
            break;
        }
    }
    cout << "ell get time taken: " << ellTimeTaken << endl;
    cout << "vector get time taken: " << vectorTimeTaken << endl;

    return result;
}

bool valueCheck(EfficientLinearList<int> *ell, list<int> *lst, int size)
{
    bool result = true;
    double ellTimeTaken = 0;
    double listTimeTaken = 0;
    int ellValue, listValue;

    auto listIt = lst->begin(); // Iterator for the list

    for (int i = 0; i < size; i++, ++listIt)
    {
        start = clock();
        ellValue = (*ell)[i];
        end_clock = clock();
        ellTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

        start = clock();
        listValue = *listIt;
        end_clock = clock();
        listTimeTaken += double(end_clock - start) / double(CLOCKS_PER_SEC);

        if (ellValue != listValue)
        {
            result = false;
            break;
        }
    }

    cout << "ell get time taken: " << ellTimeTaken << endl;
    cout << "list get time taken: " << listTimeTaken << endl;

    return result;
}

void removeFromEfficientLinearList(EfficientLinearList<int> *ell, int deleteIndexesSize)
{
    start = clock();
    for (int i = 0; i < deleteIndexesSize; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        ell->remove(deleteIndexes[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken efficient linear list: " << timeTaken << endl;
}

void removeFromVector(vector<int> *vec, int deleteIndexesSize)
{
    start = clock();
    int i;
    for (i = 0; i < deleteIndexesSize; i++)
    {
        vec->erase(vec->begin() + deleteIndexes[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken vector: " << timeTaken << endl;
}

void popFrontFromList(list<int> *lst, int deleteIndexesSize)
{
    start = clock();
    for (int i = 0; i < deleteIndexesSize; i++)
    {
        lst->pop_front();
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken list (pop_front): " << timeTaken << endl;
}

void popBackFromList(list<int> *lst, int deleteIndexesSize)
{
    start = clock();
    for (int i = 0; i < deleteIndexesSize; i++)
    {
        lst->pop_back();
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken list (pop_back): " << timeTaken << endl;
}

int main()
{

    int input;
    int size = 100000;
    values = new int[size];
    indexes = new int[size];
    deleteIndexes = new int[size / 2 + size / 4];
    for (int i = 0; i < size; i++)
    {
        values[i] = i + 1;
        indexes[i] = i;
    }

    bool result = true;
    EfficientLinearList<int> *ell;
    vector<int> *vec;
    list<int> *lst;

    double ellUpdateTimeTaken = 0;
    double ellRemoveTimeTaken = 0;

    cout << "The test has started now with " << size << " insertions and " << size / 2 << " deletions:" << endl;
    for (input = 0; input < 2; input++)
    {
        switch (input)
        {
        case 0: // insert tests
            cout << endl
                 << "1: test efficient linear list vs vector push_back insert" << endl;
            ell = new EfficientLinearList<int>;
            lst = new list<int>();
            insertToEfficientLinearList(ell, size);
            pushBackToList(lst, size);
            // result = valueCheck(ell, lst, size);
            break;
        case 1: // remove tests
            cout << endl
                 << "2: test efficient linear list vs vector pop_back" << endl;
            for (int i = 0; i < size / 2 + size / 4; i++)
            {
                deleteIndexes[i] = size - (i + 1);
            }
            removeFromEfficientLinearList(ell, size / 2 + size / 4);
            popBackFromList(lst, size / 2 + size / 4);
            // result = valueCheck(ell, lst, size / 2 + size / 4);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;

            for (int i = 0; i < size; i++)
            {
                indexes[i] = i + size / 4;
            }
            insertToEfficientLinearList(ell, size);
            pushBackToList(lst, size);
            // result = valueCheck(ell, lst, size);

            for (int i = 0; i < size / 2 + size / 4; i++)
            {
                deleteIndexes[i] = ell->size() - (i + 1);
            }
            removeFromEfficientLinearList(ell, size / 2 + size / 4);
            popBackFromList(lst, size / 2 + size / 4);
            // result = valueCheck(ell, lst, size / 2 + size / 4);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken() - ellUpdateTimeTaken;
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken() - ellRemoveTimeTaken;
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();

            // for (int i = 0; i < size; i++)
            // {
            //     indexes[i] = i + size / 2;
            // }
            // insertToEfficientLinearList(ell, size);
            // insertToVector(vec, size);
            // result = valueCheck(ell, vec, size);
            break;
        case 2: // insert tests
            cout << endl
                 << "3: test efficient linear list vs list push_front" << endl;
            ell = new EfficientLinearList<int>;
            lst = new list<int>();
            for (int i = 0; i < size; i++)
            {
                indexes[i] = 0;
            }
            insertToEfficientLinearList(ell, size);
            pushFrontToList(lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 3: // remove tests
            cout << endl
                 << "4: test efficient linear list vs list begin pop_front" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = 0;
            }
            removeFromEfficientLinearList(ell, size / 2);
            popFrontFromList(lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;

            insertToEfficientLinearList(ell, size);
            pushBackToList(lst, size);
            result = valueCheck(ell, lst, size);
            cout << ell->size() << " " << lst->size() << endl;

            removeFromEfficientLinearList(ell, size / 2);
            popFrontFromList(lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken() - ellUpdateTimeTaken;
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken() - ellRemoveTimeTaken;
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();

            insertToEfficientLinearList(ell, size);
            pushBackToList(lst, size);
            result = valueCheck(ell, lst, size);
            cout << ell->size() << " " << lst->size() << endl;

            removeFromEfficientLinearList(ell, size / 2);
            popFrontFromList(lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken() - ellUpdateTimeTaken;
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken() - ellRemoveTimeTaken;
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();

            insertToEfficientLinearList(ell, size);
            pushBackToList(lst, size);
            result = valueCheck(ell, lst, size);
            cout << ell->size() << " " << lst->size() << endl;

            removeFromEfficientLinearList(ell, size / 2);
            popFrontFromList(lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            cout << ell->size() << " " << lst->size() << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken() - ellUpdateTimeTaken;
            // cout << "updateAfterDelete time taken: " << ellUpdateTimeTaken << endl;
            // ellUpdateTimeTaken = ell->getTimeTaken();
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken() - ellRemoveTimeTaken;
            // cout << "remove process time taken: " << ellRemoveTimeTaken << endl;
            // ellRemoveTimeTaken = ell->getRemoveTimeTaken();
            break;
        case 4: // insert tests
            cout << endl
                 << "5: test efficient linear list vs vector random indices insert" << endl;
            ell = new EfficientLinearList<int>;
            vec = new vector<int>();
            for (int i = 0; i < size; i++)
            {
                indexes[i] = rand() % (i + 1);
            }
            insertToEfficientLinearList(ell, size);
            insertToVector(vec, size);
            result = valueCheck(ell, vec, size);
            break;
        case 5: // remove tests
            cout << endl
                 << "6: test efficient linear list vs vector random indices remove" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = rand() % (size - (i + 1));
            }
            removeFromEfficientLinearList(ell, size / 2);
            removeFromVector(vec, size / 2);
            result = valueCheck(ell, vec, size / 2);
            break;
        }

        if (result)
            cout << "** That was correct!" << endl;
        else
        {
            cout << "** Doesn't match." << endl;
            cout << "Your code did not pass the tests." << endl;
            // int dummy;
            // cin >> dummy;
            return 0;
        }
    }

    cout << "Your code passed all the tests." << endl;
    // int dummy;
    // cin >> dummy;

    // delete ell;
    // delete vec;
    // delete lst;
    return 0;
}
