// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <stack>
#include <sstream>
#include <optional>
#include <cstdlib>
#include <cstddef>
#include "../src/efficient_list.h"

#include <vector>
#include <list>

using namespace std;
int *values;
int *indexes;
int *deleteIndexes;
clock_t start, end_clock;
double timeTaken;

void insertToEfficientList(EfficientList *ell, int size)
{
    start = clock();
    for (int i = 0; i < size; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        efficient_list_insert(ell, indexes[i], values[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken efficient list: " << timeTaken << endl;
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

void pushFrontToList(int i, list<int> *lst, int size)
{
    start = clock();
    for (; i < size; i++)
    {
        lst->push_front(values[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken list (push_front): " << timeTaken << endl;
}

void pushBackToList(int i, list<int> *lst, int size)
{
    start = clock();
    for (; i < size; i++)
    {
        lst->push_back(values[i]);
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "insert time taken list (push_back): " << timeTaken << endl;
}

bool valueCheck(EfficientList *ell, vector<int> *vec, int size)
{

    bool result = true;
    // cout << "\n**efficient list :\nYours\tCorrect" << endl;
    double ellTimeTaken = 0;
    double vectorTimeTaken = 0;
    int ellValue, vectorValue;
    for (int i = 0; i < size; i++)
    {
        // cout << efficient_list_get_item(ell, i) << "\t" << (*vec)[i] << endl;
        start = clock();
        ellValue = efficient_list_get_item(ell, i);
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

bool valueCheck(EfficientList *ell, list<int> *lst, int size)
{
    bool result = true;
    double ellTimeTaken = 0;
    double listTimeTaken = 0;
    int ellValue, listValue;

    auto listIt = lst->begin(); // Iterator for the list
    for (int i = 0; i < size; i++, ++listIt)
    {
        start = clock();
        ellValue = efficient_list_get_item(ell, i);
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

void removeFromEfficientList(EfficientList *ell, int deleteIndexesSize)
{
    start = clock();
    for (int i = 0; i < deleteIndexesSize; i++)
    {
        // cout << "index: " << indexes[i] << "\t value:"
        //      << values[i] << endl;

        efficient_list_remove(ell, deleteIndexes[i]);
        // ell->drawTree();
        // ell->iterateInOrder();
        // cout << "===============" << endl;
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken efficient list: " << timeTaken << endl;
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

void popFrontFromList(int i, list<int> *lst, int deleteIndexesSize)
{
    start = clock();
    for (; i < deleteIndexesSize; i++)
    {
        lst->pop_front();
    }
    end_clock = clock();
    timeTaken = double(end_clock - start) / double(CLOCKS_PER_SEC);
    cout << "remove time taken list (pop_front): " << timeTaken << endl;
}

void popBackFromList(int i, list<int> *lst, int deleteIndexesSize)
{
    start = clock();
    for (; i < deleteIndexesSize; i++)
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
    int size = 1000000;
    values = new int[size];
    indexes = new int[size];
    deleteIndexes = new int[size / 2];
    for (int i = 0; i < size; i++)
    {
        values[i] = i + 1;
        indexes[i] = i;
    }

    bool result = true;
    EfficientList *ell;
    vector<int> *vec;
    list<int> *lst;

    double ellUpdateTimeTaken = 0;
    double ellRemoveTimeTaken = 0;

    cout << "The test has started now with " << size << " insertions and " << size / 2 << " deletions:" << endl;
    for (input = 0; input < 16; input++)
    {
        switch (input)
        {
        case 0: // insert tests
            cout << endl
                 << "1: test efficient list vs list push_back insert" << endl;
            ell = efficient_list_new();
            lst = new list<int>();
            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushBackToList(0, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 1: // remove tests
            cout << endl
                 << "2: test efficient list vs list pop_back" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = size - (i + 1);
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popBackFromList(0, lst, size / 2);
            result = valueCheck(ell, lst, lst->size());

            break;
        case 2: // insert tests
            cout << endl
                 << "3: test efficient list vs vector push_back insert" << endl;
            ell = efficient_list_new();
            lst = new list<int>();
            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushBackToList(0, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 3: // remove tests
            cout << endl
                 << "4: test efficient list vs vector pop_front" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = 0;
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popFrontFromList(0, lst, size / 2);
            result = valueCheck(ell, lst, lst->size());

            break;
        case 4: // insert tests
            cout << endl
                 << "5: test efficient list vs list push_front" << endl;
            ell = efficient_list_new();
            lst = new list<int>();
            for (int i = 0; i < size; i++)
            {
                indexes[i] = 0;
            }
            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushFrontToList(0, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 5: // remove tests
            cout << endl
                 << "6: test efficient list vs list begin pop_front" << endl;
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popFrontFromList(0, lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            break;
        case 6: // insert tests
            cout << endl
                 << "7: test efficient list vs list push_front" << endl;
            ell = efficient_list_new();
            lst = new list<int>();

            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushFrontToList(0, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 7: // remove tests
            cout << endl
                 << "8: test efficient list vs list begin pop_back" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = size - (i + 1);
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popBackFromList(0, lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            break;
        case 8: // insert tests
            cout << endl
                 << "9: test efficient list vs vector push_back" << endl;
            ell = efficient_list_new();
            vec = new vector<int>();
            for (int i = 0; i < size; i++)
            {
                indexes[i] = i;
            }
            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            insertToVector(vec, size);
            result = valueCheck(ell, vec, size);
            break;
        case 9: // remove tests
            cout << endl
                 << "10: test efficient list vs vector random indices remove" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = rand() % (size - (i + 1));
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            removeFromVector(vec, size / 2);
            result = valueCheck(ell, vec, size / 2);
            break;
        case 10: // insert tests
            cout << endl
                 << "11: test efficient list vs vector random indices insert" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                indexes[i] = rand() % (i + 1);
            }
            insertToEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            insertToVector(vec, size / 2);
            result = valueCheck(ell, vec, size);
            break;
        case 11: // remove tests
            cout << endl
                 << "12: test efficient list vs vector random indices remove" << endl;
            for (int i = 0; i < size / 2; i++)
            {
                deleteIndexes[i] = rand() % (size - (i + 1));
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            removeFromVector(vec, size / 2);
            result = valueCheck(ell, vec, size / 2);
            break;

        case 12: // insert tests
            cout << endl
                 << "13: test efficient list vs list half push_front then push_back the other half" << endl;
            ell = efficient_list_new();
            lst = new list<int>();
            for (int i = 0; i < size / 2; i++)
            {
                indexes[i] = 0;
                indexes[i + size / 2] = i + size / 2;
            }

            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushFrontToList(0, lst, size / 2);
            pushBackToList(size / 2, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 13: // remove tests
            cout << endl
                 << "14: test efficient list vs list begin half pop_front then pop_back the other half" << endl;
            for (int i = 0; i < size / 4; i++)
            {
                deleteIndexes[i] = 0;
                deleteIndexes[i + size / 4] = size - (i + size / 4 + 1);
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popFrontFromList(0, lst, size / 4);
            popBackFromList(size / 4, lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
            break;
        case 14: // insert tests
            cout << endl
                 << "15: test efficient list vs list half push_back then push_front the other half" << endl;
            ell = efficient_list_new();
            lst = new list<int>();
            for (int i = 0; i < size / 2; i++)
            {
                indexes[i] = i;
                indexes[i + size / 2] = 0;
            }

            insertToEfficientList(ell, size);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            pushBackToList(0, lst, size / 2);
            pushFrontToList(size / 2, lst, size);
            result = valueCheck(ell, lst, size);
            break;
        case 15: // remove tests
            cout << endl
                 << "16: test efficient list vs list begin half pop_back then pop_front the other half" << endl;
            for (int i = 0; i < size / 4; i++)
            {
                deleteIndexes[i] = size - (i + 1);
                deleteIndexes[i + size / 4] = 0;
            }
            removeFromEfficientList(ell, size / 2);
            // cout << "a1LeftInsertion: " << ell->mIPPS23RBbt->a1LeftInsertion << endl;
            // cout << "a1RightInsertion: " << ell->mIPPS23RBbt->a1RightInsertion << endl;
            // cout << "a2LeftInsertion: " << ell->mIPPS23RBbt->a2LeftInsertion << endl;
            // cout << "a2RightInsertion: " << ell->mIPPS23RBbt->a2RightInsertion << endl;
            // cout << "b1LeftInsertion: " << ell->mIPPS23RBbt->b1LeftInsertion << endl;
            // cout << "b1RightInsertion: " << ell->mIPPS23RBbt->b1RightInsertion << endl;
            // cout << "b2LeftInsertion: " << ell->mIPPS23RBbt->b2LeftInsertion << endl;
            // cout << "b2RightInsertion: " << ell->mIPPS23RBbt->b2RightInsertion << endl;
            popBackFromList(0, lst, size / 4);
            popFrontFromList(size / 4, lst, size / 2);
            result = valueCheck(ell, lst, size / 2);
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
