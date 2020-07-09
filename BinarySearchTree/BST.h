/*
Syed Ali
COSC 504 Program 6 Binary Search Tree
Assignment 06/23/2020
*/

#include <iostream>
#include <string>

using namespace std;

class BST														// defining a class binary search tree
{
private:

	struct node													// defining a structure called node
	{
		int key;												// defining an integer key
		node* left;												// defining node pointer left
		node* right;											// defining node pointer right
	};
	
	node* root;													// defining a node pointer root
	void AddLeafPrivate(int key, node* Ptr);					// private variables that are going to define the functions 
	void PrintInOrderPrivate(node* Ptr);
	void PrintPostOrderPrivate(node* Ptr);
	void PrintPreOrderPrivate(node* Ptr);
	int maxDepthPrivate(node* Ptr);
	node* ReturnNodePrivate(int key, node* Ptr);
	int FindSmallestPrivate(node* Ptr);
	void RemoveNodePrivate(int key, node*parent);
	void RemoveRootMatch();
	void RemoveMatch(node* parent, node* match, bool left);
	int  LeafCountPrivate(node* Ptr);
	int SingleParentPrivate(node* Ptr);
	void BulidTreePrivate(node* Ptr, int key);
public:
	
	BST();													    // constructor
	node* CreateLeaf(int key);									// creates a leaf nodes
	void AddLeaf(int key);										// connects all the leaf nodes
	void PrintInOrder();										// prints the binary tree in order 
	void PrintPostOrder();										// prints the binary tree in post order
	void PrintPreOrder();										// prints the binary tree in pre order
	node* ReturnNode(int key);									// returns a node 
	int ReturnRootKey();										// returns a node with its children
	void PrintChildren(int key);								// prints the node and its children
	int FindSmallest();											// finds the smallest value in the binary tree
	void RemoveNode(int key);									// allows the user to remove a node
	int maxDepth();												// prints the height of the tree
	int LeafCount();											// counts the leaf nodes
	int SingleParent();											// returns the number of nodes with one child
	void BuildTree();											// builds the tree
};