/*
Syed Ali
COSC 504 Program 6 Binary Search Tree
Assignment Due 06/23/2020
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "BST.h"
using namespace std;

BST::BST()																			// defining a constructor binary search tree				
{
	root = NULL;																	// setting the root null
};

BST::node* BST::CreateLeaf(int key)													// allowing the user to create leaf nodes
{
	node* n = new node;																// setting a node pointer n and making that a new node
	n->key = key;																	// setting the left and right of the tree to null and making the user insert a key
	n->left = NULL;
	n->right = NULL;

	return n;
}

void BST::AddLeaf(int key)															// adding leaf nodes
{
	AddLeafPrivate(key, root);
}


void BST::AddLeafPrivate(int key, node* Ptr)										// defining the add leaf
{
	if (root == NULL)																// if the root is null
	{
		root = CreateLeaf(key);														// then create the leaf
	}
	else if (key < Ptr->key)														// else if the key is less than the pointer 
	{
		if (Ptr->left != NULL)														// and if the left is not null
		{
			AddLeafPrivate(key, Ptr->left);											// then add the leaf to the left
		}
		else
		{
			Ptr->left = CreateLeaf(key);											// else just create a leaf
		}
		
	}

	else if (key > Ptr->key)														// similarly do the same to the right of the tree
	{
		if (Ptr->right != NULL)
		{
			AddLeafPrivate(key, Ptr->right);
		}
		else
		{
			Ptr->right = CreateLeaf(key);
		}

	}
	else
	{
		cout << "the key " << key << 
			" has already been added to the tree\n";
	}
}

void BST::PrintInOrder()															// print the tree traversals in order
{
	PrintInOrderPrivate(root);
}

void BST::PrintInOrderPrivate(node* Ptr)											// defining the print in order variable
{
	if (root != NULL)																// if the root is not null
	{
		if (Ptr->left != NULL)														// and if the left of the ptr is not null
		{
			PrintInOrderPrivate(Ptr->left);											// print the tree traversals in order to the left
		}
		cout << Ptr->key << " ";													// spacing out the tree
		if (Ptr->right != NULL)														// if the right if the ptr is not null
		{
			PrintInOrderPrivate(Ptr->right);										// print the tree traversals in order to the right						
		}
	}
	else
	{
		cout << "the tree is empty\n";												// if none of the conditions are true then print the statement
	}
}

void BST::PrintPostOrder()															// similarly traverse the tree in post order
{
	PrintPostOrderPrivate(root);
}

void BST::PrintPostOrderPrivate(node* Ptr)											// defining the post order traversal similar steps are taken as post order traversal
{
	if (Ptr != NULL)
	{
		PrintPostOrderPrivate(Ptr->left);
		PrintPostOrderPrivate(Ptr->right);
		cout << Ptr->key << " ";
	}
}

void BST::PrintPreOrder()															// similarly traverse the tree in pre order
{
	PrintPreOrderPrivate(root);
}

void BST::PrintPreOrderPrivate(node* Ptr)											// defining the post order traversal similar steps are taken as pre order traversal
{
	if (Ptr != NULL)
	{
		cout << Ptr->key << " ";
		PrintPreOrderPrivate(Ptr->left);
		PrintPreOrderPrivate(Ptr->right);
	}
}

int BST::maxDepth()																	// return the height of the tree
{
	return maxDepthPrivate(root);
}

int BST::maxDepthPrivate(node* Ptr)													// defining the height of the tree
{
	if (Ptr == NULL)																// if the ptr is null
	{
		return 0;																	// then return 0
	}
	else
	{
		int leftHeight = 0, rightHeight = 0;										// setting integer values of left height of the tree and right height of the tree to 0

		if (Ptr->left != NULL)														// if the ptr to the left is not null
		{
			leftHeight = maxDepthPrivate(Ptr->left);								// Recursive call to calculate the height of left subtree of root node
		}

		if (Ptr->right != NULL)														// similary if the ptr to the right is not null
		{
			rightHeight = maxDepthPrivate(Ptr->right);								// Recursive call to calculate the height of right subtree of root node
		}
		int max = (leftHeight > rightHeight) ? leftHeight : rightHeight;

		return (max + 1);															// return the height of the tree

	}

}

int BST::LeafCount()																// counts the number of leaf nodes in the tree
{
	return LeafCountPrivate(root);
}

int BST::LeafCountPrivate(node* Ptr)												// defining the leaf count function
{
	if (Ptr == NULL)																// if the ptr is null
	{
		return 0;																	// return nothing 
	}
	if (Ptr->left == NULL && Ptr->right == NULL)									// if ptrs to the left and right are null
	{
		return 1;																	// then return a 1
	}
	else
	{
		return LeafCountPrivate(Ptr->left) + LeafCountPrivate(Ptr->right);			// else add the left and right of the leaves to return the number of nodes in each leaf
	}
}

BST::node* BST::ReturnNode(int key)													// return the children in each node
{
	return ReturnNodePrivate(key, root);
}

BST::node* BST::ReturnNodePrivate(int key, node*Ptr)							    // Not used in this assignment built for practice purposes
{
	if (Ptr != NULL)
	{
		if (Ptr->key == key)
		{
			return Ptr;
		}
		else
		{
			if (key < Ptr->key)
			{
				return ReturnNodePrivate(key, Ptr->left);
			}
			else
			{
				return ReturnNodePrivate(key, Ptr->right);
			}
		}
	}
	else
	{
		return NULL;
	}
}

int BST::ReturnRootKey()														  // Not used in assignment built for practice purposes
{
	if (root != NULL)
	{
		return root->key;
	}
	else
	{
		return -1000;
	}
}

void BST::PrintChildren(int key)												// prints the children inside the binary search tree
{
	node* Ptr = ReturnNode(key);												// setting a ptr for return node

	if (Ptr != NULL)															// if the ptr is not null
	{
		cout << "Parent Node =" << Ptr->key << endl;							// then print the parent node
		
		Ptr->left == NULL ?														// if the left child is not null
			cout << "Left Child = NULL\n" :
			cout << "Left Child = " << Ptr->left->key << endl;					// print the left child

		Ptr->right == NULL ?													// if the right child is not null
			cout << "Right Child = NULL\n" :
			cout << "Right Child = " << Ptr->right->key << endl;				// then print the right child
	}

	else
	{
		cout << "Key " << key << "is not in the tree\n";
	}

}
int BST::FindSmallest()															// finds the smallest value inside the binary search tree
{
	return FindSmallestPrivate(root);
}

int BST::FindSmallestPrivate(node* Ptr)											// defining the smallest value inside the binary search tree
{
	if (root == NULL)															// if the root of the tree is null
	{
		cout << "The tree is empty\n";											// then the tree is empty
		return -1000;
	}
	else
	{
		if (Ptr->left != NULL)													// if the left of the tree is not null
		{
			return FindSmallestPrivate(Ptr->left);								// find the smallest value
		}
		else
		{
			return Ptr->key;													// else set the ptr to the key value
		}
	}
}

void BST::RemoveRootMatch()														// allows the user to remove a root from the tree not used in this assignment for practice purposes
{
	if (root != NULL)
	{
		node* delPtr = root;
		int rootKey = root->key;
		int smallestinRightSubtree;

																				// Case 0-0 children
		if (root->left == NULL && root->right == NULL)
		{
			root = NULL;
			delete delPtr;
		}
																				// Case 1-1 child
		else if (root->left == NULL && root->right != NULL)
		{
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted" <<
				"The new root contains key " << root->key << endl;
		}
		else if (root->left != NULL && root->right != NULL)
		{
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted" <<
				"The new root contains key " << root->key << endl;
		}
																				// case 2-2 Children
		else
		{
			smallestinRightSubtree = FindSmallestPrivate(root->right);
			RemoveNodePrivate(smallestinRightSubtree, root);
			root->key = smallestinRightSubtree;
			cout << "The root key containing key " << rootKey <<
				"was overwritten with key " << root->key << endl;
		}
	}
	else
	{
		cout << "Cannot remove root. the tree is empty\n ";
	}
}

void BST::RemoveMatch(node* parent, node* match, bool left)						// not used in the assignment for practice purposes					
{
if (root != NULL)
{
	node* delPtr;
	int matchKey = match->key;
	int smallestInRightSubtree;

	// Case 0-0 children

	if (match->left == NULL && match->right == NULL)
	{
		delPtr = match;
		left == true ? parent->left = NULL : parent->right = NULL;
		delete delPtr;
		cout << "The node containing key " << matchKey << " was removed\n";
	}
	else if (match->left == NULL && match->right != NULL)
	{
		left == true ? parent->left = match->right : parent->right = match->right;
		match->right = NULL;
		delPtr = match;
		delete delPtr;
		cout << "The node containing key " << matchKey << " was removed\n";
	}
	else if (match->left != NULL && match->right == NULL)
	{
		left == true ? parent->left = match->right : parent->right = match->left;
		match->left = NULL;
		delPtr = match;
		delete delPtr;
		cout << "The node containing key " << matchKey << " was removed\n";
	}
	//Case 2-2
	else
	{
		smallestInRightSubtree = FindSmallestPrivate(match->right);
		RemoveNodePrivate(smallestInRightSubtree, match);
		match->key = smallestInRightSubtree;
	}
}
else
{
	cout << "Cannot remove match. the tree is empty\n";
}

}
void BST::RemoveNode(int key)														// removes a node from the binary search tree
{
	RemoveNodePrivate(key, root);
}

void BST::RemoveNodePrivate(int key, node* parent)									// not used in this assignment for practice purposes
{
	if (root != NULL)
	{
		if (root->key == key)
		{
			RemoveRootMatch();
		}
		else
		{
			if (key < parent->key && parent->left != NULL)
			{
				parent->left->key == key ?
					RemoveMatch(parent, parent->left, true) :
					RemoveNodePrivate(key, parent->left);
			}
			else if (key > parent->key && parent->right != NULL)
			{
				parent->right->key == key ?
					RemoveMatch(parent, parent->right, false) :
					RemoveNodePrivate(key, parent->right);
			}
			else
			{
				cout << "Key " << key << "is not in the tree\n";
			}
		}
	}
	else
	{
		cout << "The tree is empty\n";
	}
}

int BST::SingleParent()																// returns the number of nodes with one child
{
	return SingleParentPrivate(root);
}

int BST::SingleParentPrivate(node* Ptr)
{
	{
		if (Ptr == NULL)															// Check Whether the given node is Empty or Not
			return 0;

		int res = 0;
																					// Check Whether the given node is Single Child Node or Not *
		if ((Ptr->left == NULL && Ptr->right != NULL) || (Ptr->left != NULL && Ptr->right == NULL))
			res++;

		res += (SingleParentPrivate(Ptr->left) + SingleParentPrivate(Ptr->right));
		return res;
	}
}

void BST::BuildTree()																// builds a 2D tree
{
	BulidTreePrivate(root, 0);
}

void BST::BulidTreePrivate(node* Ptr, int key)										// defining the build function
{
	int COUNT = 5;
	
	if (Ptr == NULL)																// Base case  
		return;
	key += COUNT;																	// Increase distance between levels  
	BulidTreePrivate(Ptr->right, key);												// Process right child first  

	cout << endl;
	for (int i = COUNT; i < key; i++)												// Print current node after key count  
		cout << " ";
	cout << Ptr->key << "\n";
BulidTreePrivate(Ptr->left, key);													// Process left child  
	
}