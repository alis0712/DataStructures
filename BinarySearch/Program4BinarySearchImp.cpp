/*
Syed Ali
COSC 504 Program 4 Binary Search Implementation File
June 16th, 2020
*/

#include <iostream>
#include <string>
#include "LinkedListSingle.h"										// including the header file which calls the functions defined previously

using namespace std;

LinkedListSingle::LinkedListSingle()								// default constructor
{
	head = NULL;													// Listing the private data members
	curr = NULL;													// Calibrating the private members to NULL to achieve desirable results
	temp = NULL;
}

void LinkedListSingle::buildListForward(int addData)				// Allows the user to define the list forward
{
	nodePtr n = new node;											// Creating a new node,  and make node * point to it
	n->data = rand() % 100 + 1;										// Fill the new node with random numbers

	if (addData < 0)												// if data < 0 return back
	{
		cout << "The list must be a positive set of integers" << endl;
		return;
	}
	else
	{

		n->next = NULL;												// Find the node that n is pointing to access its next element and make that point to NULL
	}

	if (head != NULL)												// head is a private pointer and is pointing to object
	{
		curr = head;												// make the current list point to the header. Since the list is already set up, we will set the head equal to the front of the list
		while (curr->next != NULL)									// Checking to see if the last node is in the list or not
		{
			curr = curr->next;										// Set the last node to the next value, if the last value does not exist it will set to null
		}
		curr->next = n;												// Otherwise if a value is present go and print the next value
	}
	else
	{
		head = n;													// If nothing is in the list then we are just going to make the new node that we created in this function to be the front head and it will point to the new node

	}

}

void LinkedListSingle::PrintListForward()							// This allows the user to print the list
{
	curr = head;													// Setting the current pointer to head
	while (curr != NULL)											// Setting the current pointer to NULL since it will point somewhere in the list

	{
		cout << curr->data << "->";									// This will print out the list
		curr = curr->next;
	}
	if (curr == NULL)												// If no value proceeds after the last value then set it to NULL
	{
		cout << "NULL" << endl;
	}
}

void LinkedListSingle::SortLinkedList()								// sorts the linked list from lowest to greatest (Reference: https://stackoverflow.com/questions/35914574/sorting-linked-list-simplest-way)																			// sorting the linked list
{
	int tempvar;													// setting a temperorary variable
	curr = NULL;													// use curr for stopping the comparison
	while (head != curr)											// if the list is not empty 
	{
		temp = head;												// setting the temp to head
		while (temp->next != curr)									// while the temp value is not equal current value
		{
			if (temp->data > temp->next->data)						// compare the data of the nodes
			{
				tempvar = temp->data;								// then the place it in temperorary value variable
				temp->data = temp->next->data;						// swap the data
				temp->next->data = tempvar;
			}
			temp = temp->next;										// move to the next element 
		}
		curr = temp;												// modify the current value
	}
}


 int LinkedListSingle::middle(nodePtr start,nodePtr end)			// helps in finding the middle node of the linked list (Reference: http://ijcsit.com/docs/Volume%205/vol5issue02/ijcsit20140502215.pdf)
{
	 if (start == NULL)												// if the start of the list is NULL
	 {
		 start = head;												// then the head and the end of the list will be set to NULL						
		 end = NULL;
	 }
		nodePtr temp = start;										// setting the temperorary pointer to start
		int elementCount = 0;										// setting the element counter to 0

		while (temp != end)											// while the temperorary is not the end
		{
			elementCount++;											// keep counting
			temp = temp->next;										// go to the next value in the list
			{
				int mid = elementCount/2;							// find the middle value 
				return mid;											// return the middle value
			}
			
		}
		
	}

int LinkedListSingle::binarySearch(int key)							// finding the item that the user wishes to search for (Reference: http://ijcsit.com/docs/Volume%205/vol5issue02/ijcsit20140502215.pdf)
{
	nodePtr start = head;											// setting start pointer to head
	nodePtr end = NULL;												// and the end pointer to NULL
	do
	{
		int m = this->middle(start, end);							// once the middle value is found
		nodePtr mid = start;										// make that the start of the list
		if (mid == NULL)											// if the value from the linkedlist does not exist then return nothing
		{
			return NULL;											
		}
		if (mid->data == key)										// if a value is found return the value
		{
			return mid->data;															
		}
		else if (mid->data < key)									// if the value is not found keep progressing in the linkedlist until the value is found
		{
			start = mid->next;
		}
		else
		{
			end = mid;
		}
	} while (end == NULL || end != start);							// while end is set to NULL and is not equal to the start value
	return NULL;
}

	
int LinkedListSingle::location(int key)								// find the location of where the value exists in the linked list
{
	int count = 1;													// setting the counter equal to 1
	nodePtr temp = head;											// while the temporary pointer is set to head
	while (temp->data != key)										// if the value inserted is not found in the linked list
	{
		count++;													// then keep moving in the list
		temp = temp->next;
	}
	return count;													// if found return the location
}

