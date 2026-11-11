#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "CustomUtilities.h"
using namespace std;

//********************************************
void wait(int x)
{
    //takes int argument and pauses program for X seconds
	this_thread::sleep_for(chrono::seconds(x));
}
//*********************************************

int getRandNum(int min, int max)
{
	//get rand num between min and max
	int randNumGenerated = rand() % (max-min+1);
	randNumGenerated += min;
	return randNumGenerated;
}

int getChoice()
{
	int x;
	cin>>x;
	while(!cin)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"invalid input, please try again"<<endl;
		cin>>x;
	}
	cin.clear();
	return x;
}

int getChoice(int a, int b)
{
	int x;
	cin>>x;
	while(!cin||x!=a&&x!=b)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"invalid input, please try again"<<endl;
		cin>>x;
	}
	return x;
}

int getChoice(int a, int b, int c)
{
	int x;
	cin>>x;
	while(!cin||x!=a&&x!=b&&x!=c)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"invalid input, please try again"<<endl;
		cin>>x;
	}
	return x;
}

int getChoice(int a, int b, int c, int d)
{
	int x;
	cin>>x;
	while(!cin||x!=a&&x!=b&&x!=c&&x!=d)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"invalid input, please try again"<<endl;
		cin>>x;
	}
	return x;
}

int getChoice(int a, int b, int c, int d, int e)
{
	int x;
	cin>>x;
	while(!cin||x!=a&&x!=b&&x!=c&&x!=d&&x!=e)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout<<"invalid input, please try again"<<endl;
		cin>>x;
	}
	return x;
}