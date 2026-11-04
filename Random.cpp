/*
Dean Bingham
RANDOM FUNCTION
*/

//#include <stdlib>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <iostream>

using namespace std;

int genRandNum(int min, int max)
{
	//srand(time(NULL));
	
	//get rand num between min and max
	int randNumGenerated = rand()  % (max-min+1);
	randNumGenerated += min;
	return randNumGenerated;
}


int main()
{
	srand(time(NULL));
	for(int i = 0; i < 5; i++)
	{
		int random = genRandNum(5,20);
		cout<< random<<endl;;
	}


	return 0;
}



