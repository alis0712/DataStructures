/*
Syed Ali
COSC 504 Project Employee Database
Assignment Due: 06/24/2020
Code References: http://www.cplusplus.com/forum/beginner/244327/
				 Student Management Project COSC 503
*/
#ifndef EMPLOYEE_H																									// since the class employee list contains two classes therefore needed to call this variable
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;


class Employee																										// A employee class to store employee information
{
public:
	Employee(int id, double salary, string firstName, string lastName, string phone);								// calls in employees ID, salary, first name, lastname, and phone number

	
	int getID();																									// gets employees ID
	double getSalary();																								// gets Salary
	string getFirstName();																							// gets employees first name 
	string getLastName();																							// gets employees last name																			
	string getPhone();																								// gets employees phone numbers

	
	void setSalary(double salary);																					// sets employees salary
	void setPhone(string phone);																					// sets employees phone number

private:
	int id;																											// defines a variable ID
	double salary;																									// defines a variable salary

	string firstName;																								// defines the first name as a string
	string lastName;																								// similarly defines last name as a string
	string phone;																									// defines a phone number as a sting
};


Employee::Employee(int id, double salary, string firstName, string lastName, string phone)							// Create a new employee
{
	this->id = id;																									// calls or copies in ID from text
	this->salary = salary;																							// calls in salary
	this->firstName = firstName;																					// calls in first name as a sting
	this->lastName = lastName;																						// calls in last name
	this->phone = phone;																							// calls in phone number
}


int Employee::getID()																								// Get employee's ID
{
	return id;
}


double Employee::getSalary()																						// Get employees's Salary
{
	return salary;
}


string Employee::getFirstName()																						// Get the employee's firstname
{
	return firstName;
}


string Employee::getLastName()																						// Get the employee's lastname
{
	return lastName;
}


string Employee::getPhone()																							// Get the employee's phone
{
	return phone;
}


void Employee::setSalary(double salary)																				// Update the employee's salary
{
	this->salary = salary;
}


void Employee::setPhone(string phone)																				// Update the employee's phone
{
	this->phone = phone;
}
#endif