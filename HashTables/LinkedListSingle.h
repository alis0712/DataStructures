/*
Syed Ali
COSC 504 Program 4 Binary Search Header File
June 16th, 2020
*/

#include <iostream>
#include <string>

using namespace std;

class LinkedListSingle											// Declaring a class called SingleLinkedList which will allow the user to pick specific set of inputs
{
private:

	typedef struct node											// The struct contains a node since a node contains the actual list
	{
		int data;												// This will hold some integer value 
		node* next;												// create a node pointer								
	}*nodePtr;													// Avoids the use "*" 

	nodePtr head;												// pointing to the head of the linked list
	nodePtr curr;												// pointing to the current value in the list
	nodePtr temp;												// pointing to the temporary 
	
	

public:															// This is where the functions go
	LinkedListSingle();
	void buildListForward(int addData);							// Returns the list in the following form 1->2->3->4...
	void PrintListForward();									// Allows the user to print the values forward on the console
	void SortLinkedList();										// sorts the linked list (Reference: https://stackoverflow.com/questions/44211730/c-how-do-i-create-a-copy-of-a-linked-list-as-a-class-object)
	int middle(nodePtr start, nodePtr end);						// To find the middle node of linked list (to be used as helper function in binary search)
	int binarySearch(int key);									// conducts the binary search or is the binary search implementation
	int location(int key);										// returns the index of where the value is located
};