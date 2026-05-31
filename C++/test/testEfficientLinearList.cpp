// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2024 (1404 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi, Mohammad Mahdi Rahneshin

#include <iostream>
#include <stack>
#include <sstream>

#include "../src/IndexedPPS23RBBinaryTreeNode.h"
#include "../src/IndexedPPS23RedBlackBinaryTree.h"
#include "../src/EfficientLinearList.h"

#include <iostream>

using namespace std;

char inOrder[] = {'g', 'd', 'k', 'h', 'l', 'b', 'a', 'e', 'i', 'c', 'f'};
char deleted[] = {'g', 'd', 'k', 'l', 'b', 'a', 'i', 'c'};
char deletedIndexedList[] = {'g', 'd', 'k', 'l', 'b', 'i', 'c'};

bool insertEfficientLinearListCheck(EfficientLinearList<char> *ill)
{
	//                                                     a
	//												/		      \
	//											l		            c
	//										/		\        	/   	\
	//								  	   d		 b         e          f
	//							         g    h                 i
	//									 	 k

	ill->insert(0, 'a');
	ill->insert(1, 'c');
	ill->insert(2, 'f');
	ill->insert(0, 'l');
	ill->insert(0, 'd');
	ill->insert(0, 'g');
	ill->insert(2, 'h');
	ill->insert(2, 'k');
	ill->insert(5, 'b');
	ill->insert(7, 'e');
	ill->insert(8, 'i');

	ill->drawTree();
	cout << endl;
	cout << endl;

	bool result = true;
	cout << "\n**efficient linear list :\nYours\tCorrect" << endl;

	for (int i = 0; i < ill->size(); i++)
	{
		cout << (*ill)[i] << "\t" << inOrder[i] << endl;
		if ((*ill)[i] != inOrder[i])
		{
			result = false;
			break;
		}
	}

	return result;
}

bool deleteEfficientLinearListCheck(EfficientLinearList<char> *ill)
{
	//                                                     a
	//												/		      \
	//											l		            c
	//										/		\        	/   	\
	//								  	   d		 b         e          f
	//							         g    h                 i
	//									 	 k

	ill->remove(3);
	ill->remove(9);
	ill->remove(6);
	ill->remove(5);

	ill->drawTree();
	cout << endl;
	cout << endl;

	bool result = true;
	cout << "\n**efficient linear list :\nYours\tCorrect" << endl;

	for (int i = 0; i < ill->size(); i++)
	{
		cout << (*ill)[i] << "\t" << deletedIndexedList[i] << endl;
		if ((*ill)[i] != deletedIndexedList[i])
		{
			result = false;
			break;
		}
	}

	return result;
}

int main()
{
	int input;
	bool result = false;
	EfficientLinearList<char> *ill = new EfficientLinearList<char>;

	for (input = 0; input < 2; input++)
	{
		switch (input)
		{
		case 0:
			cout << endl
				 << "1: test efficient linear list insert" << endl;
			result = insertEfficientLinearListCheck(ill);
			break;
		case 1:
			cout << endl
				 << "2: test efficient linear list remove" << endl;
			result = deleteEfficientLinearListCheck(ill);
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

	delete ill;
	return 0;
}
