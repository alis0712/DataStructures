/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

Queue::Queue()																					// constructor
{
	front = rear = nullptr;																		// making the front and rear point to NULL
};

void Queue::insert(int n)																		// creating a list that allows the user to insert values in it
{
	Node* temp = new Node;																		// creating a temporary node pointer called new node

	if (temp == nullptr)																		// if the temporary pointer is set to null
	{

		cout << "no values exist in the list " << endl;											// then print no values exists in the cell

		return;

	}

	else
	{
		temp->data = n;																			// otherwise temporary data is set to n

		temp->next = nullptr;																	// and the next data in the list is set to null
	}

	

	if (front == nullptr)																		// if the front is null
	{

		front = rear = temp;																	// then the front and rear pointers point to null

	}

	else 
	{

		rear->next = temp;																		// otherwise they point to temp

		rear = temp;																			// and the rear would equal to temp

	}

}


void Queue::display()																			// allows the user to display the list
{
	if (front == nullptr)																		// if the front of the list is point to null then no list exixts
	{
		cout << "no list is present" << endl;
		return;
	}

	Node* temp = front;																			// if not then create a node ptr temp which would equal to the front of the list
	
	while (temp)																				// while in temp list print out the data
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

void Queue::deleteitem()																		// Allowing the user delete an item 
{
	if (front == nullptr)																		// if front of the list is null then print out the list
	{
		cout << "no list is present" << endl;													
	}
	return;

	if (front == rear)																			// if the front of the list equals to rear
	{
		front = rear = nullptr;																	// then the front and rear would equal to null
	}
	
	else
	{
		front = front->next;																    // keep moving to the next value
	}
}

Queue::~Queue()																					// destructor, allows the user to delete a value in the queue
{
	while (front != nullptr)																	// while the front is not null
	{
		Node* temp = front;																		// set the temporary node pointer to front
		front = front->next;																	// go onto the next value
		delete temp;																			// delete the temp
	}
	rear = nullptr;																				// set the rear to null
}
