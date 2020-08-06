/*
Syed Ali
COSC 504 Program 1
May 28th, 2020
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string candidate[5];                                                                                                                                         // Intilializing variables
int votes[5];
double sum = 0;
double percentage[5];
int win = votes[0];
	

int main()
{
	for (int i = 0; i < 5; i++)
	{																																						// Allowing the user to enter candidates names
		cout << "Enter candidate's name: ";
		cin >> candidate[i];																																
		cout << "Enter " << candidate[i]  <<"'s"<<  " number of votes: ";																					// Allowing the user to enter the amount of votes he/she received
		cin >> votes[i];
		sum = sum + votes[i];																																// summing all the votes
	}
	
	cout << endl << left << setw(20) << "Candidate: " << right << setw(15) << "Votes Received: " << setw(21) << "% of Total Votes: " <<  endl;				// setting columns (Reference: http://www.cplusplus.com/forum/beginner/15577/)
	

	for (int i = 0; i < 5; i++)
	{
		percentage[i] = votes[i] / sum * 100.0;																												// calculating the votes received by each candidate
		cout << left << setw(15) << candidate[i] << right << setw(15) << votes[i] << setw(20) << setprecision(2) << fixed << percentage[i] << "%" << endl;	// printing out the proportion of votes received by each candidate
	}
	cout << "Total " << right << setw(25) << sum << endl;																									// printing out total or sum of votes
	
	int max = sizeof(votes) / sizeof(votes[0]);																												// The size of the array

	for (int i = 2; i < max; i++)
	{
		if (votes[i] > win)																																	// Goes through the array and find the greatest value
		{
			win = votes[i];
			cout << "The Winner of the Election is " << candidate[i] << endl;																				// Prints out the candidate with the highest vote
		}
		
	}

	return 0;
	system("PAUSE");
}
