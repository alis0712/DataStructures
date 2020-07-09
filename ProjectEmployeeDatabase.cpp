/*
Syed Ali
COSC 504 Project Employee Database
Assignment Due: 06/24/2020
Code References: http://www.cplusplus.com/forum/beginner/244327/
				 Student Management Project COSC 503

*/

#include <iostream>
#include <string>
#include <sstream>																																		// goes through the string to add it in a list																														
#include <iomanip>																																		// needed to set the widths (spacing) within each string or values
#include <fstream>																																		// needed to read in the text file EmployeeList
#include "Employee.h"																																	// calling the header file Employee.h
#include "EmployeeList.h"																																// calling header file EmployeeList

using namespace std;


const int BY_LAST_NAME = 0;																																// Constants to be used
const int BY_ID = 1;
const int BY_SALARY = 2;
const int BY_FIRST_NAME = 3;

const int DISPLAY_ALL = 0;


void sortList(EmployeeList* employeeList, int sortType)																								    // Sort the employee depending on given sort type
{
	for (int i = 0; i < employeeList->size() - 1; i++)																									// for the size of the list												
	{
		for (int j = i + 1; j < employeeList->size(); j++)																								// for each element
		{
			if ((sortType == BY_FIRST_NAME && employeeList->get(i)->getFirstName().compare(employeeList->get(j)->getFirstName()) > 0) ||				// sort the index for the first name per the selection sort algorithm			
				(sortType == BY_LAST_NAME && employeeList->get(i)->getLastName().compare(employeeList->get(j)->getLastName()) > 0) ||					// sort the index for the last name per the selection sort algorithm		
				(sortType == BY_ID && employeeList->get(i)->getID() > employeeList->get(j)->getID()) ||													// sort the index for the ID per the selection sort algorithm
				(sortType == BY_SALARY && employeeList->get(i)->getSalary() > employeeList->get(j)->getSalary()))										// sort the index for the salary per the selection sort algorithm
			{
				Employee* temp = employeeList->get(i);																									// set the employee pointer temp to get employee list																					
				employeeList->update(i, employeeList->get(j));																							// update the list in accordance with selection sort
				employeeList->update(j, temp);
			}
		}
	}
}


void sortList(EmployeeList* employeeList)																											    // Sort the employee either by name, ID, or Salary
{
	cout << "CHOOSE SORT TYPE" << endl;																													// print out the options
	cout << "1 - By First Name" << endl;
	cout << "2 - By ID" << endl;
	cout << "3 - By Salary" << endl;
	cout << "Option: ";

	string option;																																		
	getline(cin, option);																																// allow the user to input an option

	if (option.compare("1") == 0)																														// if option 1 is picked sort the list by first name
	{
		sortList(employeeList, BY_FIRST_NAME);
	}
	else if (option.compare("2") == 0)																													// if option 2 is picked sort the list by ID
	{
		sortList(employeeList, BY_ID);
	}
	else if (option.compare("3") == 0)																													// if option 3 is picked sort the list by salary
	{
		sortList(employeeList, BY_SALARY);
	}
}


EmployeeList* createEmployeeList()																														// Load the list of Employee from file and sort it by name
{
	EmployeeList* employeeList = new EmployeeList();																									// create a new employee list

	ifstream inFile;
	inFile.open("EmployeeList.txt");																													// open file EmployeeList.txt

	while (!inFile.eof())																																// while not in end of file
	{
		string firstName;																																// in the new list create these parameters
		string lastName;
		int id;
		double salary;
		string phone1;
		string phone2;
		string phone3;

		if (inFile >> firstName >> lastName >> id >> salary >> phone1 >> phone2 >> phone3)																// in the file set each of the parameters as defined above
		{
			string phone = phone1 + " " + phone2 + " " + phone3;																						// divide the phone numbers as three separate strings
			employeeList->add(new Employee(id, salary, firstName, lastName, phone));																	// add it to the new list
		}
	}

	inFile.close();

	sortList(employeeList, BY_LAST_NAME);																												// sort the list by last name
	return employeeList;
}


void printList(EmployeeList* employeeList, int displayType)																								// Display the employee's list
{	
	cout << fixed;																																		// using iomanip header file set the widths of each of the parameters defined
	cout << setw(15) << "First Name";						
	cout << setw(15) << "Last Name";
	cout << setw(10) << "ID";
	cout << setw(15) << "Salary";
	cout << setw(15) << "Phone";
	cout << setw(25) << "Annual Salary";
	cout << endl;

	int count = 0;																																		// set the counter to 0

	for (int i = 0; i < employeeList->size(); i++)																										// for the size of the employee list
	{
		Employee* employee = employeeList->get(i);																										// call the parameters defined in the header file

		if (displayType == DISPLAY_ALL) 
		{
			cout << setw(15) << employee->getFirstName();																								// using iomanip header set the widths of each of the parameters defined																						
			cout << setw(15) << employee->getLastName();
			cout << setw(10) << employee->getID();
			cout << setw(10) << setprecision(1) << "$" << employee->getSalary() << "/hr";
			cout << setw(20) << employee->getPhone();
			cout << setw(10) << setprecision(1) << "$" << employee->getSalary() * 2080 << "/year";														// calculating the annual salary 
			cout << endl;
			count++;																																	// counting the number of employees in the list
		}
	}
	sortList(employeeList, BY_LAST_NAME);
	cout << "Total Number of Employee: " << count << endl;
}


void insertToList(EmployeeList* employeeList)																									        // Insert a new employee to the list
{
	string firstName;																																	// defining parameters
	string lastName;
	string phoneNumber;
	string temp;

	int id;
	double salary;

	cout << "Enter First Name: ";																														// allowing the user to enter their first name
	getline(cin, firstName);

	cout << "Enter Last Name: ";																														// allowing the user to enter their last name
	getline(cin, lastName);

	cout << "Enter ID: ";																																// allowing the user to enter an ID
	getline(cin, temp);
	stringstream(temp) >> id;

	cout << "Enter Salary: ";																															// allowing the user to enter in their salary
	getline(cin, temp);
	stringstream(temp) >> salary;

	cout << "Enter Phone Number: ";																														// allowing the user to enter their phone number 
	getline(cin, phoneNumber);

	employeeList->add(new Employee(id, salary, firstName, lastName, phoneNumber));																		// adding in the new employee
	sortList(employeeList, BY_LAST_NAME);																												// sort the list by their last name
}


int searchEmployee(EmployeeList* employeeList, int id)																								    // Search the employee who has the ID
{
	for (int i = 0; i < employeeList->size(); i++)
	{
		if (employeeList->get(i)->getID() == id)																										// get their ID
		{
			return i;																																	// return their ID
		}
	}

	return -1;
}


void deleteFromList(EmployeeList* employeeList)																									         // Delete a employee from list
{
	cout << "CHOOSE DELETE TYPE" << endl;																												 // print out the statement to ask the user how they would like to delete
	cout << "1 - By First and Last Name" << endl;																										 // either by first name and last name
	cout << "2 - By ID" << endl;																														 // or by ID
	cout << "Option: ";

	string option = "";
	getline(cin, option);

	if (option.compare("1") == 0)																														// if option 1 is selected 
	{
		string firstName;
		string lastName;
		
		cout << "Enter First Name: ";																													// enter their first name
		getline(cin, firstName);

		cout << "Enter Last Name: ";																													// enter their last name
		getline(cin, lastName);

		int targetIndex = -1;

		for (int i = 0; i < employeeList->size(); i++)																									// go through the list to see if the name exists
		{
			if ((employeeList->get(i)->getFirstName().compare(firstName) == 0) && 
				(employeeList->get(i)->getLastName().compare(lastName) == 0))
			{
				targetIndex = i;
				break;
			}
		}

		if (targetIndex == -1)
		{
			cout << "Error: The employee does not exist." << endl;																						// if it does not exists then print this statement
		}
		else
		{
			employeeList->remove(targetIndex);																											// if it exists then remove that person
			cout << "Ok: employee deleted." << endl;
		}
	}
	else if (option.compare("2") == 0)																													// if option 2 is selected then delete by ID and follow a similar procedure as above
	{
																																				
		string temp;
		int id = 0;
		int index = 0;

		cout << "Enter ID: ";
		getline(cin, temp);

		if (!(stringstream(temp) >> id) || (index = searchEmployee(employeeList, id)) == -1)
		{
			cout << "Error: The employee does not exist." << endl;
			return;
		}

		employeeList->remove(index);
		cout << "Ok: Employee deleted." << endl;
	}
}


void searchEmployee(EmployeeList* employeeList)																											// Search an employee and display its information
{
	cout << "CHOOSE SEARCH TYPE" << endl;																												// either search it by their first and last name
	cout << "1 - By First and Last Name" << endl;
	cout << "2 - By ID" << endl;																														// or by ID
	cout << "Option: ";

	string option = "";
	getline(cin, option);

	if (option.compare("1") == 0)																														// if option 1 is selected
	{
		string firstName;
		string lastName;

		cout << "Enter First Name: ";																													// enter their first name
		getline(cin, firstName);

		cout << "Enter Last Name: ";																													// enter their last name
		getline(cin, lastName);

		int targetIndex = -1;

		for (int i = 0; i < employeeList->size(); i++)
		{
			if ((employeeList->get(i)->getFirstName().compare(firstName) == 0) &&																		// go through the list to see if the name exists
				(employeeList->get(i)->getLastName().compare(lastName) == 0))
			{
				targetIndex = i;
				break;
			}
		}

		if (targetIndex == -1)
		{
			cout << "Error: The employee does not exist." << endl;																						// if it doesn't exists then print this statement
		}
		else
		{
			Employee* employee = employeeList->get(targetIndex);
			cout << "First Name: " << employee->getFirstName() << endl;																					// if it exists then print their first, last names along with ID, salary and phone number
			cout << "Last Name : " << employee->getLastName() << endl;
			cout << "Salary       : " << "$" << employee->getSalary() << "/hr" << endl;
			cout << "Phone     : " << employee->getPhone() << endl;
		}
		
	}
	else if (option.compare("2") == 0)
	{
		string temp;
		int id = 0;
		int index = 0;

		cout << "Enter ID: ";																														   // if option 2 is selected then delete by ID and follow a similar procedure as above
		getline(cin, temp);

		if (!(stringstream(temp) >> id) || (index = searchEmployee(employeeList, id)) == -1)
		{
			cout << "Error: The employee does not exist." << endl;
			return;
		}

		if (!(stringstream(temp) >> id) || (index = searchEmployee(employeeList, id)) == -1)
		{
			cout << "Error: The employee does not exist." << endl;
			return;
		}


		Employee* employee = employeeList->get(index);
		cout << "First Name: " << employee->getFirstName() << endl;
		cout << "Last Name : " << employee->getLastName() << endl;
		cout << "Salary       : " << "$" << employee->getSalary() << "/hr" << endl;
		cout << "Phone     : " << employee->getPhone() << endl;
	}
}


void updateEmployee(EmployeeList* employeeList)																									    // Update a employee
{
	cout << "Enter ID: ";																														    // first enter their ID
	string temp;
	getline(cin, temp);

	int id = 0;
	int index = 0;

	if (!(stringstream(temp) >> id) || (index = searchEmployee(employeeList, id)) == -1)															// go through their ID and see if they exist and if they exist then print the statement below										
	{
		cout << "Error: The employee does not exist." << endl;
		return;
	}

	Employee* employee = employeeList->get(index);

	double salary;
	string phone;

	cout << "Enter new hourly rate (" << employee->getSalary() << "): ";																			// allow the user to enter their new salary 																
	getline(cin, temp);
	stringstream(temp) >> salary;

	cout << "Enter new phone (" << employee->getPhone() << "): ";																					// allow the user to enter their phone number
	getline(cin, phone);

	employee->setSalary(salary);																													// then set the salary
	employee->setPhone(phone);																														// then set the phone number

	cout << "Ok: Employee Update" << endl;
	cout << "First Name: " << employee->getFirstName() << endl;																						// then re-print out the first name, last name, hourly rate, and phone number 
	cout << "Last Name : " << employee->getLastName() << endl;
	cout << "Salary       : " << "$" << employee->getSalary() << "/hr" << endl;
	cout << "Phone     : " << employee->getPhone() << endl;
}

void Leave(EmployeeList* employeeList)																												// a function that allows the user to determine his/her salary based on their leave request
{
	cout << "Enter ID of employee who is planning to take leave: ";																					// allow the user to enter in employees ID 
	string temp;
	getline(cin, temp);

	int id = 0;
	int index = 0;

	if (!(stringstream(temp) >> id) || (index = searchEmployee(employeeList, id)) == -1)															// search through the list to find the ID, if it does not exist then print the statement below
	{
		cout << "Error: The employee does not exist." << endl;
		return;
	}

	Employee* employee = employeeList->get(index);								

	double salary;

	cout << "CHOOSE LEAVE TYPE" << endl;																											// allow the user to select if the leave is annual or sick 																							
	cout << "1 - Annual " << endl;
	cout << "2 - Sick " << endl;
	cout << "Option: ";

	string option = "";
	getline(cin, option);

	if (option.compare("1") == 0)																													// if it is annual then print the statement below
	{
		int leave;

		cout << "Enter the number of days the employee is requesting for annual leave: ";
		cin >> leave;
		if (leave > 15)																																// if the leave is greater than 15 days then print the statement below and calculate the salary based on 15 days
		{
			cout << "Since the annual leave request exceeds the annual leave policy, they will be paid two weeks of paid vacation, which is: "
				 << endl;
			cout << "$" << employee->getSalary() * 80 << "/Bi-Weekly" << endl;
		}
		else
		{
			cout << "the annual leave request is within the company's leave policy: " << endl;														// otherwise if the leave is within 15 days then print this statement
		}
	}

	if (option.compare("2") == 0)																													// if option 2 is selected then print this statement
	{
		int sick;

		cout << "Enter the number of days the employee is requesting for sick leave: ";
		cin >> sick;
		if (sick > 7)
		{
			cout << "Since the sick leave request exceeds the sick leave policy, they will be paid one week of sick leave, which is: "
				 << endl;
			cout << "$" << employee->getSalary() * 40 << "/Weekly" << endl;
		}
		else
		{
			cout << "The sick leave request is within the company's sick leave policy: " << endl;
		}
	}
}

void destroyList(EmployeeList* employeeList)																										// Delete all memory allocated employee and the list
{
	
	if (employeeList != NULL)																														// Delete memory employeeList 
	{
		for (int i = 0; i < employeeList->size(); i++)																								// for the size of the list
		{
			delete employeeList->get(i);																											// delete the entire list
		}

		delete employeeList;
	}

	employeeList = NULL;																															// set the employeelist to null
}


int main()																																			
{
	EmployeeList* employeeList = NULL;

	while (true)
	{
		cout << "MENU" << endl;																														// creating menu options to select one of the options provided
		cout << "1 - Create Employee list" << endl;
		cout << "2 - Insert" << endl;
		cout << "3 - Delete" << endl;
		cout << "4 - Sort" << endl;
		cout << "5 - Search" << endl;
		cout << "6 - Update" << endl;
		cout << "7 - Leave" << endl;
		cout << "8 - Print Employees" << endl;
		cout << "0 - Exit" << endl;
		cout << "Option: ";
		string option = "";
		getline(cin, option);

		if (option.compare("1") == 0)
		{
			
			destroyList(employeeList);																											    // if 1 is selected then delete old list, create the list from file, then print it out
			employeeList = createEmployeeList();
			printList(employeeList, DISPLAY_ALL);
		}
		else if (option.compare("2") == 0 && employeeList != NULL)
		{
			
			insertToList(employeeList);																											    // if 2 then Insert a new employee, then print it out list
			printList(employeeList, DISPLAY_ALL);
		}
		else if (option.compare("3") == 0 && employeeList != NULL)
		{
			
			deleteFromList(employeeList);																											// if 3 then Delete a employee, then print out the list
			printList(employeeList, DISPLAY_ALL);
		}
		else if (option.compare("4") == 0 && employeeList != NULL)
		{
			sortList(employeeList);																													// if 4 then sort the list by first name
			printList(employeeList, DISPLAY_ALL);
		}
		else if (option.compare("5") == 0 && employeeList != NULL)
		{
			searchEmployee(employeeList);																											// if 5 then search for a particular employee in the list
		}
		else if (option.compare("6") == 0 && employeeList != NULL)
		{
			updateEmployee(employeeList);																											// if 6 then update employee information 
		}
		
		else if (option.compare("7") == 0 && employeeList != NULL)
		{
			Leave(employeeList);																													// if 7 enter the employees leave information
		}
		
		else if (option.compare("8") == 0 && employeeList != NULL)																					// if 8 then print the list in accordance with their last name
		{
			printList(employeeList, DISPLAY_ALL);																									// print the list
		}
		else if (option.compare("0") == 0)
		{
			
			break;																																    // Quit
		}
	}

	destroyList(employeeList);
	return 0;
}