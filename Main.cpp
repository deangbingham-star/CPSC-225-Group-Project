#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Creature.h"
#include "Color.h"
#include "Player.h"
#include "CustomUtilities.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
//using std::ifstream;

int main()
{
	srand(time(NULL));

	int decision;
	bool bossCleared = false;
	bool quit = false;
	Player* p;

	Colorize(YELLOW, "Welcome");
	wait(1);

	cout<<"Would you like to import data?"<<endl
	    <<"(1) Yes"<<endl<<"(2) No"<<endl;

	decision = getChoice(1,2);
	if(decision==1)
	{
		ifstream fin("PlayerData.txt");
		if(fin.is_open())
		{
			cout<<"PlayerData.txt successfully opened"<<endl;
			p = new Player(fin);
		}
		else
		{
			cout<<"Could not find PlayerData.txt"<<endl
			    <<"Creating a new player profile"<<endl;
			p = new Player("Karl");
		}
		fin.close();
	}
	else
	{
		cout<<"Creating a new player profile"<<endl;
		p = new Player("Karl");
	}

	//Main gameplay loop
	while(bossCleared == false && quit==false)
	{
		cout<<"What would you like to do?"<<endl
		    <<"(1) View Status\n(2) Battle\n(3) Visit Shop\n(4) Challenge Boss\n(5) Quit"
		    <<endl;
		decision = getChoice(1,2,3,4,5);
		if(decision==1)
		{
		    //allows user to view current status and restore creature status
			p->viewStatus();
		}
		else if(decision==2)
		{
			bool b = p->battle();
		}
		else if(decision==3)
		{
			p->shop();
		}
		else if(decision==4)
		{
			bossCleared = p->battle(true);
		}
		else if(decision==5)
		    quit = true;
	}
	
	if(bossCleared==true)
	{
	    cout<<"Congratulations! You successfully cleared the boss battle!"<<endl;
	}
	
	cout<<"Would you like to save player data before leaving?"<<endl
	    <<"Any existing data in PlayerData.txt will be overwritten"<<endl<<"(1) Yes\n(2) No"<<endl;
	decision=getChoice(1,2);
	if(decision==1)
    	p->savePlayerData();
	
	delete p;
	return 0;
}