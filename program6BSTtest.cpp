/*
Syed Ali
COSC 504 Program 6 Binary Search Tree
Assignment Due 06/23/2020
*/

#include <iostream>
#include <string>
#include "BST.h"
using namespace std;

int main()
{
	int n;																												// intializing variables
	int x;
	cout << "Enter the number of nodes you wish to have to build the tree: " << endl;
	cin >> n;																											// allowing the user to enter the number of nodes they wish to see in the tree

	BST Program6;

	cout << "Enter the values to build a tree: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> x;																										// inserting the values																				
		Program6.AddLeaf(x);																							// adds a branches or nodes to the left and right of the tree
	}

	cout << "based on the values provided, the build tree is as follows: " << endl;
	Program6.BuildTree();																								// builds a 2D tree
	cout << endl;

	cout << "Printing the tree using PrintInOrder Function: " << endl;
	Program6.PrintInOrder();																							// prints the tree traversals in order
	cout << endl;

	cout << "Printing the tree using PrintPreOrder Function: " << endl;													// prints the tree traversals in pre-order
	Program6.PrintPreOrder();
	cout << endl;

	cout << "Printing the tree using PrintPostOrder Function: " << endl;												// prints the tree traversals in post order
	Program6.PrintPostOrder();
	cout << endl;

	cout << "The root node and the root node's children are: " << endl;													// prints out the children in the tree
	Program6.PrintChildren(Program6.ReturnRootKey());
	cout << endl;

	cout << "The height of the tree is: " << Program6.maxDepth() << endl;												// prints the out the maximum height of the tree

	cout << "The number of leaf nodes in tree are: " << Program6.LeafCount() << endl;									// prints out the leaf nodes

	cout << "The number of leaves with only one child are: " << Program6.SingleParent() << endl;						// returns the number of leaf nodes with one child only

	system("PAUSE");
	return 0;

}