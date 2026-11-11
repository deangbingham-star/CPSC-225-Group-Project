#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Creature.h"
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
	Player* p;

	cout<<"Welcome!"<<endl;

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
	while(bossCleared == false)
	{
		cout<<"What would you like to do?"<<endl
		    <<"(1) View Status\n(2) Battle\n(3) Visit Shop\n(4) Challenge Boss"
		    <<endl;
		decision = getChoice(1,2,3,4);

		if(decision==1)
		{
			/*viewStatusFunction
			p->viewStatus();
			    inside function will also be ability to restore creature status
			     (heal HP, reset buff/debuff status to default)
			    Also will be ability to output current status to PlayerData.txt
			*/
		}
		else if(decision==2)
		{
			p->battle();
		}
		else if(decision==3)
		{
			p->shop();
		}
		else if(decision==4)
		{
			//bossBattle
			//bossCleared = p->challengeBoss();
			//function with boolean return type, will return true if boss is cleared, else return false.
			bossCleared = true;
		}
	}
	
	p->savePlayerData();
	
	delete p;
	return 0;
}