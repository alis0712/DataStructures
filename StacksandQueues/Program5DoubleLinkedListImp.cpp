/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>
#include "DoubleLinkedList.h"

using namespace std;

DoubleLinkedList::DoubleLinkedList()								// constructor
{
	head = nullptr;													// making the head point to NULL
}

void DoubleLinkedList::insert_front(int data)						// inserting a node to the front of the node
{
	node* n = new node;												// creating a new node														
	n->data = data;													// inserting the data
	n->next = head;													// making the next value in the list point to head
	n->prev = nullptr;												// and making the previous value in the list to null

	if (head != nullptr)											// if the head is not null
	{
		head->prev = n;												// then make the front and previous value point to n
		head = n;
	}
}

void DoubleLinkedList::insert_end(int data)							// inserting a node to the end of the list
{
	node* n = new node;												// creating a new node
	n->data = data;													// inserting the data
	node* last = head;												// make the last value in the list point to head
	n->next = nullptr;												// make the next value point to NULL

	if (head == nullptr)											// if the head is null
	{
		n->prev = nullptr;											// then the previous value is null
		head = n;													// and the head value is the data
		return;
	}

	while (last->next != nullptr)									// while the very last value in the list is not null
	{ 
		last = last->next;											// then the next value after the last value is the data
		last->next = n;
		n->prev = last;												// and the previous value is the last value
	}
}

void DoubleLinkedList::display()									// printing out the list
{
	node* n = head;													// setting the head pointer to n

	while (n != nullptr)											// while n is not null
	{
		cout << n->data << "  ";									// print the list
		n = n->next;
	}

	cout << endl;
}