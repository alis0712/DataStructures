/*
Syed Ali
COSC 504 Program 5 Stacks and Queues
Assignment Due: 06/18/2020
*/

#include <iostream>
#include <string>
#include "Stacks.h"
#include "Queue.h"
#include "DoubleLinkedList.h"
#include "SingleLinkedList.h"


using namespace std;

int main()
{
	Queue QueueListDiv3;
	
	Stacks StackDiv3and5;
	
	DoubleLinkedList DoubleListDiv5;

	SingleLinkedList LeftOverList;

	int MyArray[30];
	int lower = 0;
	int upper = 30;

	
	for (int i = 0; i < 30; i++)
	{
		 MyArray[i] = (rand() % (upper - lower + 1)) + lower;			// creates 30 random elements										
		
	}
	
	cout << "Random Array elements are:" << endl;
	for (int i = 0; i < 30; i++)
	{
		cout << MyArray[i] << " ";									   // prints Random Array elements 
	}
		cout << endl;

	for (int i = 0; i < 30; i++)
	{
		int flag = 0;

		if (MyArray[i] % 3 == 0)										// if number is divisible by 3
		{
			QueueListDiv3.insert(MyArray[i]);
			flag = 1;
		}

		if (MyArray[i] % 5 == 0)
		{
			DoubleListDiv5.insert_end(MyArray[i]);						// if number is divisible by 5 
			flag = 1;
		}
		if (MyArray[i] % 3 == 0 && MyArray[i] % 5 == 0)
		{
			StackDiv3and5.Push(MyArray[i]);								// if number is divisible by 3 and 5 both
			flag = 1;				
		}
		if (flag == 0)
		{
			LeftOverList.insert(MyArray[i]);							// if number is neither divisible by 3 nor by 5
		}
	}

	cout << "Stack elements by 3 and 5 are: \n";						// printing out elements that are divisible by 3 and 5 using stacks

	StackDiv3and5.Print();
	cout << endl;

	cout << "Queue elements that are divisble by 3 are: \n";			// printing out elements in a queue that are divisible by 3

	QueueListDiv3.display();

	cout << "Doubly linked elements that are divisible by 5 are\n";		// printing out doubly linked elements that are divisble by 5

	DoubleListDiv5.display();

	cout << "Singly linked elements that aren't divisble by 3 and 5\n";	// printing out Single Linked List elements that aren't divisible by 3 and 5

	LeftOverList.display();

	system("PAUSE");
	return 0;
}