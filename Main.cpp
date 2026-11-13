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

int main()
{
	srand(time(NULL));

	int decision;
	bool bossCleared = false;
	bool quit = false;
	Player* p;

	Colorize(BOLDMAGENTA, "Welcome");
	wait(1);

	Colorize(BOLDYELLOW, "Would you like to import data?");
	cout<<"(1) Yes"<<endl<<"(2) No"<<endl;

	decision = getChoice(1,2);
	if(decision==1)
	{
		ifstream fin("PlayerData.txt");
		if(fin.is_open())
		{
			Colorize(BOLDGREEN, "PlayerData.txt successfully opened");
			p = new Player(fin);
		}
		else
		{
			Colorize(BOLDRED, "Could not find PlayerData.txt");
			wait(1);

			Colorize(BOLDYELLOW,"\nCreating a new player profile");
			wait(1);
			p = new Player("Karl");
		}
		fin.close();
	}
	else
	{
		Colorize(BOLDYELLOW,"\nCreating a new player profile");
		wait(1);
		p = new Player("Karl");
	}

	//Main gameplay loop
	while(bossCleared == false && quit==false)
	{
		Colorize(BOLDYELLOW, "\nWhat would you like to do?");
		cout<<"(1) View Status\n(2) Battle\n(3) Visit Shop\n(4) Challenge Boss\n(5) Quit"
		    <<endl;
		decision = getChoice(1,2,3,4,5);
		if(decision==1)
		{
			//allows user to view current status and restore creature status
			p->viewStatus();
			wait(1);
		}
		else if(decision==2)
		{
			bool b = p->battle();
			wait(1);
		}
		else if(decision==3)
		{
			p->shop();
			wait(1);
		}
		else if(decision==4)
		{
			bossCleared = p->battle(true);
			wait(1);
		}
		else if(decision==5)
			quit = true;
		wait(1);
	}

	if(bossCleared==true)
	{
		Colorize(BOLDGREEN, "Congratulations! You successfully cleared the boss battle!");
	}

	Colorize(BOLDYELLOW, "Would you like to save player data before leaving?");
	Colorize(RED, "Any existing data in PlayerData.txt will be overwritten");
	cout<<"(1) Yes\n(2) No"<<endl;
	
	decision=getChoice(1,2);
	if(decision==1)
		p->savePlayerData();

	delete p;
	return 0;
}