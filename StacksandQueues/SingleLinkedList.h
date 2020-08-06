/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>

using namespace std;

class SingleLinkedList								// creating a class called single linked list
{
private:

	struct node										// creating a struct called node
	{
		int data;									// adding data
		node* next;									// going to the next value
	};

	node* head;										// setting node ptr to head
	node* tail;										// setting node ptr to tail

public:
	SingleLinkedList();								// constructor
	void insert(int n);								// allows the user to insert a node to the end of a list
	void display();									// allows the user to display list
	
};