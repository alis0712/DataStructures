/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>
#include "Stacks.h"

using namespace std;

Stacks::Stacks()													// This is constructor
{
	stackPtr = NULL;												// setting the stack ponter to null
}

Stacks::~Stacks()													// This is the deconstructor
{
	item* p1;														// creating two item pointers
	item* p2;

	p1 = stackPtr;													// setting p1 to stackPtr
	while (p1 != NULL)												// while p1 does equal to NULL
	{
		p2 = p1;													// setting p2 equal to p1
		p1 = p1->prev;												// setting p1 to previous
		p2->prev = NULL;											// setting p2 previous to NULL
		delete p2;													// deleting p2
	}
}

void Stacks::Push(int value)										// creating a list that allows the user to select a series compatible values
{
	item* n = new item;												// setting the item ptr to new item
	n->value = value;												// adding a value
	
	if (stackPtr == NULL)											// if the stack pointer is set to NULL
	{	
		stackPtr = n;												// then make stackptr point to n
		stackPtr->prev = NULL;										// and make the previous pointer set to null
	}
	else
	{
		n->prev = stackPtr;											// otherwise make the previous point to the stackptr
		stackPtr = n;												// and make stackptr equal to n
	}
}

void Stacks::ReadItem(item* r)										// allows the user to read an item
{
	cout << r->value << " ";										// prints out the value
	
}

void Stacks::Pop()													// delete items or removes the top elements
{
	if (stackPtr == NULL)											// if the stack pointer is set to null
	{
		cout << "There is nothing on the stack" << endl;			// print this statement
	}
	
	else
	{
		item* p = stackPtr;											// otherwise make the item pointer p equal to the stack pointer
		ReadItem(p);												// read the item
		stackPtr = stackPtr->prev;									// make the stackptr go to the previous value
		p->prev = NULL;												// set the previous value to null
		delete p;													// then delete it
	}
}

void Stacks::Print()												// allows the user to print the value
{
	item* p = stackPtr;												// set the item pointer p to the stack pointer
	
	while (p != NULL)												// while p does not equal to null
	{
		ReadItem(p);												// then read the item p
		p = p->prev;												// set p to the previous value
	}
}