/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>

using namespace std;

class DoubleLinkedList							// Defining class called Double Linked List
{
private:
	
	struct node
	{
		int data;								// calling an integer data
		node* prev;								// making a node pointing to previous element
		node* next;								// making a node pointing to next element in the list
	};

	node* head;
	
public:
	DoubleLinkedList();							// constructor
	void insert_front(int data);				// allows the user insert a node in front of the list
	void insert_end(int data);					// allows the user to add a node to the end of a list
	void display();								// allows the user to display or print the double linked list

};
