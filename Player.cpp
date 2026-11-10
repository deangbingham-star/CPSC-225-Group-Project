#include <iostream>
#include <fstream>
#include "Creature.h"
#include "Player.h"
#include "CustomUtilities.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
//using std::ifstream;

Player::Player(string n = "Joe") : NAME(n)
{
	cout << "" << endl;
	numCreatures = 0;
	addCreature();
	activeCreature = creatures[0];
	currency = 1000;
	attackBuffItems = 0;
	healingItems = 0;
	defenseBuffItems = 0;
}

Player::Player(ifstream& fin)
{
    int test = 0;
    cout<<"Demo constructor called"<<endl;
    fin>>test;
    cout<<test<<endl;
}

void Player::addCreature()
{
	if (numCreatures >= 3)
		throw numCreatures;

	creatures[numCreatures] = new Creature();
	numCreatures++;
}

void Player::addCreature(Creature* c)
{
	if (numCreatures >= 3)
		throw numCreatures;

	string creatureName;
	cout<<"What would you like to name this creature?"<<endl;
	cin>>creatureName;

	creatures[numCreatures] = c;
	creatures[numCreatures] -> setName(creatureName);
	numCreatures++;
}

void Player::setActiveCreature()
{
	int inp;
	cout<<"Which creature would you like to set active?" << endl;
	for (int x = 0; x < numCreatures; x++)
	{
		cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}
	//cin >> inp;
	inp = getChoice();
	
	if (inp > numCreatures)
		throw inp;

	activeCreature = creatures[inp - 1];
	cout<<"Your active creature is now "<<activeCreature->getName()<<endl;
}

void Player::setActiveCreature(int n)
{
	int inp;
	cout<<"Which creature would you like to set active?" << endl;
	for (int x = 0; x < numCreatures; x++)
	{
		if(x!=n-1)
			cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}

	//cin >> inp;
	inp = getChoice();
	
	if (inp > numCreatures || inp == n || inp < 1)
		throw inp;

	activeCreature = creatures[inp - 1];
	cout<<"Your active creature is now "<<activeCreature->getName()<<endl;
}

void Player::removeCreature()
{
	if (numCreatures <= 0)
		throw numCreatures;

	int inp;
	cout<<"Which creature would you like to remove?" << endl;

	for (int x = 0; x<numCreatures; x++)
	{
		cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}
	//cin>>inp;
    inp=getChoice();

	if(creatures[inp-1]==activeCreature)
	{
		bool successful = false;
		cout<<"You are attempting to delete your currently active creature"<<endl
		    <<"Please set a different active creature before proceeding"<<endl;
		while(successful==false)
		{
			try
			{
				setActiveCreature(inp);
				successful = true;
			}
			catch(int x)
			{
				cout<<"Invalid option. Please try again."<<endl;
			}
		}
	}

	delete creatures[inp-1];

	if(inp-1<numCreatures-1)
	{
		for(int x = inp-1; x<numCreatures-1; x++)
			creatures[x] = creatures[x+1];
	}

	numCreatures--;
}

void Player::catchCreature(Creature* c)
{
	int decision;
	try
	{
		addCreature(c);
	}
	catch (int x)
	{
		cout << "You are carrying the max number of creatures." << endl
		     << "Would you like to remove a creature to make room?" << endl
		     <<"(1) Yes\n(2) No"<<endl;

		decision = getChoice(1,2);
		//cin>>decision;

		if(decision==1)
		{
			try
			{
				removeCreature();
				addCreature(c);
			}
			catch(int x)
			{
				cout<<"There are no creatures to remove."<<endl;
			}
		}
	}
}

void Player::useItem()
{
	int inp;

	if(healingItems==0&&defenseBuffItems==0&&attackBuffItems==0)
		throw 0;
    /*
	else
	{
		cout<<"Which item would you like to use?"<<endl;
		if(healingItems>0)
			cout<<"(1) Healing Item - Available: "<<healingItems<<endl;
		if(defenseBuffItems>0)
			cout<<"(2) Defense Booster - Available: "<<defenseBuffItems<<endl;
		if(attackBuffItems>0)
			cout<<"(3) Attack Booster - Available: "<<attackBuffItems<<endl;
	}
	cin>>inp;
	
	if(inp<0||inp>3)
		cout<<"invalid input"<<endl;
	else
	{
	    cout<<"Which creature would you like to use the item on?"<<endl;
		for (int x = 0; x < numCreatures; x++)
		{
			cout<<x+1<<": "<<creatures[x]<<endl;
		}
		cin>>inp;
		
		if(inp<0||inp>numCreatures)
		    cout<<"invalid input"<<endl;
		else
		{
		    switch inp:
		        case 1:
		            
		            break;
		        case 2:
		            break;
		        case 3:
		            break;
		}
		    
	}
    */
}

void Player::battle()
{
	bool continueBattle = true;
	int decision;
	cout << "An enemy creature has appeared!" << endl;

	Creature* opp = new Creature();
	opp->setName("Enemy");

	while (continueBattle == true)
	{
		bool turnEnd = false;
		while(turnEnd == false)
		{
			cout << "(1)Attack, (2)Capture, (3)Switch Active Creature, (4)Use Item" << endl;
			//cin >> decision;
			decision = getChoice(1,2,3,4);
			
			if (decision == 1)
			{
				activeCreature->Attack(opp);
				cout << opp;
				if (opp->getCurHP() <= 0)
				{
					continueBattle = false;
					delete opp;
				}
				turnEnd = true;
			}
			else if (decision == 2)
			{
				catchCreature(opp);
				turnEnd = true;
				continueBattle = false;
			}
			else if (decision == 3)
			{
				try {
					setActiveCreature();
				}
				catch (int x)
				{
					cout<<"invalid input" << endl;
				}
			}
			else if (decision == 4)
			{
				try
				{
					useItem();
				}
				catch(int x)
				{
					cout<<"You have no items available to use"<<endl;
				}
			}
		}

		if (continueBattle == true)
		{
			opp->Attack(activeCreature);
			cout << activeCreature;
		}

	}
}

int Player::buyItem(int x)
{
	int quantity = 0;
	cout<<"How many would you like to purchase?"<<endl;
	//cin>>quantity;
    quantity = getChoice();
    
	if(currency < x*quantity)
	{
		cout<<"You do not have enough currency to complete this purchase."<<endl;
		quantity = 0;
	}
	else
	{
		currency -= x*quantity;
		cout<<"You have $"<<currency<<" remaining."<<endl;
	}

	return quantity;
}

int Player::sellItem()
{
	//sell item
	return 0;
}

void Player::shop()
{
	bool stayInShop = true;
	int inp;

	while(stayInShop == true)
	{
		cout<<"You currently have $"<<currency<<endl;
		cout<<"Would you like to buy or sell items?"<<endl
		    <<"(1) Buy"<<endl<<"(2) Sell"<<endl;
		//cin>>inp;
        inp = getChoice(1,2);

		if (inp==1)
		{
			cout<<"Which type of item would you like to purchase?"<<endl
			    <<"(1) Healing Item - $500"<<endl<<"(2) AttackBuff - $150"
			    <<endl<<"(3) DefenseBuff - $150"<<endl<<"(4) Cancel"<<endl;
			//cin>>inp;
            inp = getChoice(1,2,3,4);

			switch(inp)
			{
			case 1:
				healingItems += buyItem(500);
				break;
			case 2:
				attackBuffItems+= buyItem(150);
				break;
			case 3:
				defenseBuffItems+=buyItem(150);
				break;
			case 4:
				break;
			default:
				cout<<"Invalid input (or something bad happened)"<<endl;
			}
		}

		else if(inp==2)
		{
			sellItem();
		}

		cout<<"Are you ready to leave the shop?"<<endl
		    <<"(1) Yes"<<endl<<"(2) No"<<endl;
		//cin>>inp;
		inp = getChoice(1,2);
		if(inp == 1)
			stayInShop = false;
	}
}

Player::~Player()
{
	for (int x = numCreatures; x > 0; x--)
	{
		delete creatures[x-1];
		numCreatures--;
	}
}