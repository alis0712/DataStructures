/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>
#include "SingleLinkedList.h"

using namespace std;

SingleLinkedList::SingleLinkedList()								// constructor setting the head and tail to null
{
	head = nullptr;
	tail = nullptr;
}

void SingleLinkedList::insert(int n)								// allowing the user to insert in a value
{
	node* tmp = new node;											// setting the temporary pointer to a new node
	tmp->data = n;													// adding the data
	tmp->next = nullptr;											// setting the next data to null

	if (head == nullptr)											// if the head is null
	{
		head = tmp;													// then set the head to the temp along with tail to temp
		tail = tmp;
	}

	else
	{
		tail->next = tmp;											// otherwise set the next value in the tail to temp
		tail = tail->next;											// keep moving
	}
}

void SingleLinkedList::display()									// display the results
{
	node* ptr = head;												// setting the nodeptr ptr to head	
	while (ptr != nullptr)											// while the ptr does not equal to null
	{
		cout << ptr->data << " ";									// then print out the data
		ptr = ptr->next;											// keep progressing in the list
	}
	cout << endl;
}


