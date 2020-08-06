/*
Syed Ali
COSC 504 Program 4 Binary Search Test File
June 16th, 2020
*/

#include<iostream>
#include<string>
#include "LinkedListSingle.h"
using namespace std;

int n;                                                                                    // Initializing variables
int s;
int fl;



int main()
{
    cout << "Enter the amount of numbers to be in the list" << endl;                      // prompt the user to enter the amount of numbers n Ex:3,4,5 and so forth                           
    cin >> n;

    LinkedListSingle Program4;
    cout << "Random numbers to be displayed forward on the list are" << endl;             // Enter postive numbers, which will be displayed forward on the list
    for (int i = 0; i < n; i++)
    {
        Program4.buildListForward(fl);
    }
    cout << endl;
    Program4.PrintListForward();                                                          // print the values
    cout << endl;

    cout << "The sorted list becomes: " << endl;
    Program4.SortLinkedList();                                                            // sort the list
    Program4.PrintListForward();                                                          // print the sorted list
    cout << endl;

  for (int i = 0; i < 5; i++)
    {
        cout << "enter a value to search in the linked list " << endl;                    // promt the user to enter a value they wish to find using binary searc
        cin >> s;
        if (Program4.binarySearch(s) == NULL)                                             // if the value is not found in the linkedlist then print the statement below            
        {
            cout << "searchedItem was not found in the list" << endl;
        }
        else
        {
            cout << "searchedItem is found at location: " << Program4.location(s) << endl; // if found then print the location of where the value is 
        }

    }
}