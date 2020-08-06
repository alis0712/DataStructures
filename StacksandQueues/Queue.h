/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int data;												// creating an integer called data
	Node* next;												// creating a node ptr called next
};

class Queue													// creating a class called queue
{
public:

	Node* front;											// creating a pointer point to the front of the list
	Node* rear;												// creating a pointer point to the rear of the list												

	Queue();												// constructor
	void insert(int n);										// Allows the user insert a node
	void deleteitem();										// Allows the user to delete a node
	void display();											// Allows the user to display the list											
	~Queue();												// destructor			
};