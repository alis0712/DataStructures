/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>

using namespace std;

class Stacks														// setting up a class called stacks
{

private:

	struct item														// creatng a structure called item which holds a value
	{

		int value;

		item* prev;													// holds a previous value

	};

	item* stackPtr;													// pointing the item to a stack pointer

public:

	void Push(int value);											// allows the user to push a value

	void Pop();														// allows the user to pop a value

	void ReadItem(item* r);											// allows the user to read an item from the list

	void Print();													// allows the user to print the item in the list

	Stacks();														// constructor

	~Stacks();														// destructor

};