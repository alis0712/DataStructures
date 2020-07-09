/*
Syed Ali
COSC 504 Project Employee Database
Assignment Due: 06/24/2020
Code References: http://www.cplusplus.com/forum/beginner/244327/
				 Student Management Project COSC 503

*/
#ifndef EMPLOYEELIST_H																									// contains two classes so define it to EmployeeList
#define EMPLOYEELIST_H

#include <iostream>
#include <string>
#include "Employee.h"																									// calling the header file Employee.h

using namespace std;



class EmployeeNode																										// A node to be used to linked to form a employee list
{
public:
	Employee* employee;																									// defining a pointer employee
	EmployeeNode* next;																									// defining a pointer employee node which points to the next element in the list

	EmployeeNode(Employee* employee);																					// constructor 
};

EmployeeNode::EmployeeNode(Employee* employee)																			// constructor - setting the next element in the list to null
{
	this->employee = employee;
	next = NULL;
}


class EmployeeList																										// A class to linked employee nodes to form a linked list
{
public:
	EmployeeList();																										// constructor
	~EmployeeList();																									// deconsturctor

	void add(Employee* employee);																						// allows the user to add an element to the list
	void remove(int index);																								// allows the user to remove an element from the list
	void update(int index, Employee* employee);																			// allows the user to update the list
	int size();																											// allows the user to modify the size of the list
	Employee* get(int index);																							// allows the user to import data from the text file

private:
	EmployeeNode* head;																									// setting the employee node pointer to head
};

EmployeeList::EmployeeList()																							// constructor - setting the head to NULL
{
	head = NULL;
}


EmployeeList::~EmployeeList()																						   // destructor or destroy list
{
	EmployeeNode* temp = NULL;																						   // setting the EmployeeNode pointer temp to NULL				
	EmployeeNode* current = head;																					   // setting the EmployeeNode pointer current to head

	while (current != NULL)																							   // while current is set to null
	{
		temp = current->next;																						   // making the temp equal to current to next
		delete current;																								   // deleting the current
		current = temp;																								   // setting the current to temp
	}

	head = NULL;																									   // making the head equal to NULL
}


void EmployeeList::add(Employee* employee)																			  // Add a new employee at the end of the list
{
	if (head == NULL)																								  // if the head is null
	{
		head = new EmployeeNode(employee);																			  // set the head equal to new Employee Node
		return;
	}

	EmployeeNode* current = head;																					  // set the EmployeeNode pointer current to head

	while (current->next != NULL)																					  // while the current element in the list is not pointing to null
	{
		current = current->next;																					  // then make the current point to next
	}

	current->next = new EmployeeNode(employee);																		  // then create a new node for EmployeeNode list
}


void EmployeeList::remove(int index)																			      // Remove a Employee given the index
{
	if (index < 0 || index >= size())																				  // if the index is less than zero or greater than the size of the list
	{
		return;																										  // then return
	}

	EmployeeNode* previous = NULL;																					  // create a employee node pointer previous and set that to null
	EmployeeNode* current = head;																					  // make the current employeee node pointer to head

	for (int i = 0; i < index; i++)																					  // for all the elements in the list
	{
		previous = current;																							  // make the previous point to the current
		current = current->next;																					  // and make the current point to the next element in the list
	}

	if (previous == NULL)																							  // if the head is null
	{
		
		head = head->next;																						      // Case deleting from the head
	}
	else
	{																											      // otherwise
		previous->next = current->next;																			      // Case deleting in between
	}

	delete current;																									  // delete the current element in the list
}


void EmployeeList::update(int index, Employee* employee)														      // Update a employee from the specified index
{
	if (index < 0 || index >= size())																				  // if the index is less than zero or greater than the size of the list
	{
		return;																										  // then return
	}

	EmployeeNode* current = head;																					  // set the employeenode pointer current to head

	for (int i = 0; i < index; i++)																					  // for all the elements in the list
	{
		current = current->next;																					  // set the current to next
	}

	current->employee = employee;																					  // set the current point to employee
}


int EmployeeList::size()																						      // Count the number of employee's stored
{
	int count = 0;																									  // set the counter to 0

	EmployeeNode* current = head;																					  // set the EmployeeNode pointer current to head

	while (current != NULL)																							  // while the current does not equal to null
	{
		count++;																									  // keep counting
		current = current->next;																					  // and point the current to next
	}

	return count;																									  // return the number of elements
}


Employee* EmployeeList::get(int index)																		          // Get the employee at the specified index
{
	if (index < 0 || index >= size())																				  // if the index is less than zero or greater than the size of the list
	{
		return NULL;																								  // set the current pointer to null
	}

	EmployeeNode* current = head;																					  // set the EmployeeNode pointer current to head

	for (int i = 0; i < index; i++)																					  // for the size of the list
	{
		current = current->next;																					  // set the current pointer to next
	}

	return current->employee;																						 // return the position of where the employee is located
}

#endif