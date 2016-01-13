/*---------------------------------------------------------------------------------//
// Program: Pirate Stool Loop Solution											   //
// Description: This program is a solution to the pirate barstool problem		   //
// posed by Google																   //
//																				   //
// Author: Joshua Thibado														   //
// Date 1/13/2016																   //
//																				   //
//---------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

//Functions
void randomArray();//Randomizes array within limit of number of pirates
int randomInt(int maxsize);//Generates random int
void findLoop(int position);//Finds loop in pirate array
void PiratesInLoop();//Enumerates loop in pirate array
void clearInfo();//Clears info so user can start again with diff # pirates

//Stores  pirates info
int stools[5000];
int color[5000];

//Stores user input
int numberOfPirates = 0;
char achar = 'y';

//Stores loop info
int numPiratesInLoop = 0;
int loopStartsAt;
string pirateList = "(S)";//Stores list of pirates in loop as string

int pirateRandNum;	//Rand num for placing in array

int prevRandNum;	//Previous random number to prevent tons of repeats
					//Not truly random but it is better than nine 12's
					//in a row :D

int main()
{
	while (achar == 'y' || achar == 'Y')
	{
		cout << "Welcome to the Scurvy Dog Pirate Bar!\n"
			<< "How many pirates are there in here?\n";

		cin >> numberOfPirates;
		if (numberOfPirates > 1 && numberOfPirates <= 5000)
		{
			randomArray();//Randomizes values into the array using time

			findLoop(0);//Finds loop starting from position 0

			PiratesInLoop();//Counts the number of pirates in the loop

			for (int s = 0; s < numberOfPirates; s++)//Prints out original list of pirates
			{
				if (s % 20 == 0)//New line every 20 bar stools
				{
					cout << endl;
				}

				cout << stools[s] << " ";//Space between stools
			}

			cout << "\n\nPirates in Loop: " << numPiratesInLoop << endl;//Outputs the number of pirates in loop
			cout << "Order of Pirates in loop: " << pirateList;//Outputs the list of pirates in said loop

			clearInfo();//Resets info before asking to go again

			cout << "\n\nWould you like to try again?";
			cin >> achar;
			cout << endl;

		}//Endif 1 < num Pirates <= 5000

	}//End while achar == y/Y
	return 0;
}

//This function creates psuedorandom array of numbers
//In the array of stools
void randomArray()
{
	prevRandNum = 0;//Sets the previous random num to zero

	for (int j = 0; j < numberOfPirates; j++)//For every stool there is a pirate at
	{
		do
		{
			pirateRandNum = randomInt(numberOfPirates);//Random number for the pirate = random integer
			
		} while (pirateRandNum == j || pirateRandNum == prevRandNum);
		//If that number is the same as the one before
		//Generates a new "random" integer. This is to combat multiple same random numbers in a row,
		//Due to the function being called so quickly(same millisecond) with the core i5 Processor
		//


		stools[j] = pirateRandNum;//Stools at i = randomNumber
		prevRandNum = pirateRandNum;//Now previous random num is this one
	}//End for
}

//This function generates a pseudo random int based on the time
int randomInt(int maxsize)
{
	int xRan;
	srand(time(0)); // This will ensure a really randomized number by help of time.

	xRan = rand() %maxsize;//Random number mod maxsize to get number between 0 and max

	return xRan;//Returns number
}

//Uses DFS to find at what barstool the loop starts at.
void findLoop(int position)
{
	int nextPirate = stools[position];

	color[position] = 1;//Colors vertex as grey(1)/visited

	if (color[nextPirate] == 0)//If color is white for that vertex, hasnt been visited
	{
		findLoop(nextPirate);//Perform a dfs on it
	}
	else if (color[nextPirate] == 1)//If node has been visited before & is gray
	{
		loopStartsAt = nextPirate;//This is where the loop must start!!!
	}
	color[position] = 2;
}

//This function goes through the list starting at the position the loop starts at
//As calculated above and counts the pirates in the loop and concats them to a string
void PiratesInLoop()
{
	int nextPirate = stools[loopStartsAt];//netpirate is the data 
										  //held in loopstarts at (to begin)
	numPiratesInLoop++;//Increments # pirates in the loop

	pirateList.append(to_string(loopStartsAt));
	pirateList.append("->");

	pirateList.append(to_string(nextPirate));
	pirateList.append("->");

	do
	{
		nextPirate = stools[nextPirate];
		numPiratesInLoop++;

		pirateList.append(to_string(nextPirate));
		pirateList.append("->");

	} while (nextPirate != loopStartsAt);//While we haven't come back to loop starts at

	pirateList.pop_back();//Removes last ">"
	pirateList.pop_back();//Removes last "-"
	pirateList.append("(S)");//Appends (S) to inidcate start

}

//This function will clear the colors of the last list of pirates.
//The pirate stools themselves don't need to be cleared as they will be written over
//With new random numbers, but I did anyways
void clearInfo()
{
	for (int i = 0; i <= 5000; i++)
	{
		color[i] = 0;
		stools[i] = 0;
	}
	pirateList = "(S)";
	numPiratesInLoop = 0;
}