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
	healingItems = 0;
	attackBuffItems = 0;
	defenseBuffItems = 0;
}

Player::Player(ifstream& fin)
{
	int test = 0;
	cout<<"Data constructor called"<<endl;

	//reads in and sets values
	fin>>currency;
	fin>>healingItems;
	fin>>attackBuffItems;
	fin>>defenseBuffItems;

	fin>>numCreatures;
	cout<<numCreatures<<endl;

	for(int x = 0; x<numCreatures; x++)
	{
		//throws away the newline character so the next line can be read
		string junk;
		getline(fin, junk);

		//gets the creature type from the player data
		string CreatureType;
		getline(fin, CreatureType);

		//calls corresponding creature type's constructor and passes in the ifstream
		if(CreatureType == "Basic Creature")
			creatures[x] = new Creature(fin);
		else if(CreatureType == "Boss Creature")
		    creatures[x] = new Boss(fin);
		else
			cout<<"Error"<<endl;
	}

	bool successful = false;
	while(successful==false)
	{
		try
		{
			setActiveCreature();
			successful = true;
		}
		catch(int x)
		{
			cout<<"Invalid Option, please try again"<<endl;
		}
		catch(string s)
		{
			cout<<s<<endl;
		}
	}
}

void Player::savePlayerData()
{
	ofstream fout("PlayerData.txt");

	if(fout.is_open() == false)
		throw 0;

	//follow print order: currency, healing items, attackBuffItems, defenseBuffItems, numCreatures
	fout<<currency<<endl;
	fout<<healingItems<<endl;
	fout<<attackBuffItems<<endl;
	fout<<defenseBuffItems<<endl;
	fout<<numCreatures<<endl;

	//loop through saving creature data for numCreatures
	for(int x=0; x<numCreatures; x++)
	{
		creatures[x]->saveCreatureData(fout);
	}

	fout.close();
}

void Player::viewStatus()
{
	int decision;
	cout<<"Current player status: "<<endl<<"Currency: $"<<currency<<endl
	    <<"Currently carrying:\nHealing Items: "<<healingItems<<endl
	    <<"Attack Boosters: "<<attackBuffItems<<endl<<"Defense Boosters: "
	    <<defenseBuffItems<<endl<<"\nOwned creatures: "<<numCreatures<<endl;

	for(int x = 0; x<numCreatures; x++)
	{
		cout<<"("<<x+1<<") "<<creatures[x]->getName()<<endl;
	}

	cout<<"What would you like to do?"<<endl
	    <<"(1) View Creature Status\n(2) Switch Active Creature\n(3) Return"<<endl;
	decision = getChoice(1,2,3);
	if(decision==1)
	{
		//Asks user which creature they'd like to display info for, then calls viewStatus for selected creature
		cout<<"Which creature would you like to view?"<<endl;
		decision=getChoice(1,2,3);
		while(decision>numCreatures)
		{
			cout<<"invalid input, please try again"<<endl;
			decision = getChoice(1,2,3);
		}
		cout<<creatures[decision-1];

		cout<<"Would you like to restore this creature's status? Cost: $50"<<endl
		    <<"(Doing so will restore currentHP to max value and reset all buff/debuff effects)"
		    <<endl<<"(1) Yes\n(2) No"<<endl;
		int confirmation = getChoice(1,2);

		if(confirmation==1)
		{
			creatures[decision-1]->Restore();
			currency-=50;
		}
	}
	else if(decision==2)
	{
		bool successful = false;
		while(successful == false)
		{
			try
			{
				setActiveCreature();
				successful = true;
			}
			catch(int x)
			{
				cout<<"Invalid option"<<endl;
			}
			catch(string s)
			{
				cout<<s<<endl;
			}
		}
	}
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
	string unavailable = "That creature is currently knocked out";

	cout<<"Which creature would you like to set active?" << endl;
	for (int x = 0; x < numCreatures; x++)
	{
		cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}
	//cin >> inp;
	inp = getChoice();

	if (inp > numCreatures || inp <= 0)
		throw inp;
	if (creatures[inp-1]->getCurHP()<=0)
		throw unavailable;

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
	int inp, selection;

	if(healingItems==0&&defenseBuffItems==0&&attackBuffItems==0)
		throw 0;
	cout<<"What type of item would you like to use?"<<endl
	    <<"(1) Healing Item\tYou Have: "<<healingItems<<endl
	    <<"(2) Attack Booster\tYou Have: "<<attackBuffItems<<endl
	    <<"(3) Defense Booster\t You Have: "<<defenseBuffItems<<endl
	    <<"(4) Cancel"<<endl;
	inp = getChoice(1,2,3,4);

	if(healingItems==0 && inp==1)
		throw 0;
	if(attackBuffItems==0 && inp==2)
		throw 0;
	if(defenseBuffItems==0 && inp==3)
		throw 0;

	if(inp!=4)
	{
		cout<<"Which creature would you like to use the item on?"<<endl;
		for(int x = 0; x<numCreatures; x++)
		{
			cout<<"("<<x+1<<") "<<creatures[x]<<endl;
		}

		selection=getChoice(1,2,3);

		while(selection>numCreatures)
		{
			cout<<"invalid input, please try again"<<endl;
			selection=getChoice(1,2,3);
		}

		switch(inp)
		{
		case 1:
			creatures[selection-1]->setHP(creatures[selection-1]->getMaxHP());
			healingItems--;
			break;
		case 2:
			creatures[selection-1]->applyAttackBuff(1);
			attackBuffItems--;
			break;
		case 3:
			creatures[selection-1]->applyDefenseBuff(1);
			defenseBuffItems--;
			break;
		default:
			cout<<"This is bad"<<endl;
		}
	}
}

bool Player::battle(bool boss)
{
	bool continueBattle = true;
	int decision;
	Creature* opp;

	if(boss == false)
	{
		cout << "An enemy creature has appeared!" << endl;

		opp = new Creature();
		opp->setName("Enemy");
	}
	else
	{
		opp = new Boss();
		cout<<"You approach the boss and prepare for battle"<<endl;
	}
	
	while (continueBattle == true)
	{
		bool turnEnd = false;

		if(activeCreature->getCurHP() <= 0)
		{
			bool canSwitch = false;

			cout<<activeCreature->getName()<<" has been knocked out"<<endl;

			for(int x=0; x<numCreatures; x++)
			{
				if(creatures[x]->getCurHP()>0)
				{
					canSwitch = true;
				}
				cout<<canSwitch<<endl;
			}

			if(canSwitch == true)
			{
				bool successful = false;
				while(successful == false)
				{
					try
					{
						setActiveCreature();
						successful = true;
					}
					catch(int x)
					{
						cout<<"invalid input, please try again"<<endl;
					}
					catch(string s)
					{
						cout<<s<<endl;
					}
				}
			}
			else
			{
				cout<<"All of your creatures have been knocked out"<<endl
				    <<"You are forced to retreat from the battle "<<endl
				    <<"$100 are spent to restore your creatures"<<endl;
				for(int x = 0; x<numCreatures; x++)
				{
					creatures[x]->Restore();
				}
				currency-=100;
				delete opp;
				return false;
				//continueBattle = false;
				//turnEnd = true;
			}
		}

		while(turnEnd == false)
		{
			cout << "\n(1) Attack, (2) Capture, (3) Switch Active Creature, (4) Use Item" << endl;
			//cin >> decision;
			decision = getChoice(1,2,3,4);

			if (decision == 1)
			{
				activeCreature->Attack(opp, true);
				cout << opp;
				if (opp->getCurHP() <= 0)
				{
					cout<<"The opposing creature has been defeated"<<endl
					    <<"Your creatures are awarded with 100xp"<<endl;
					for(int x = 0; x<numCreatures; x++)
					{
						creatures[x]->grantXP(100);
					}
					continueBattle = false;
					delete opp;
					return true;
				}
				turnEnd = true;
			}
			else if (decision == 2)
			{
				catchCreature(opp);
				opp->Restore();
				return true;
				//turnEnd = true;
				//continueBattle = false;
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
				catch(string s)
				{
					cout<<s<<endl;
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
			wait(2);
			opp->Attack(activeCreature, false);
			wait(2);
			cout << activeCreature;
		}
	}
	return false;
}

int Player::buyItem(int x)
{
	int quantity = 0;
	cout<<"How many would you like to purchase?"<<endl;
	//cin>>quantity;
	quantity = getChoice();

	if(quantity<0)
	{
		cout<<"You can not purchase a negative quantity"<<endl;
		return 0;
	}
	else if(currency < x*quantity)
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

void Player::sellItem(int x)
{
	int quantity = 0;
	switch(x)
	{
	case 1:
		if(healingItems <= 0)
			throw quantity;
		cout<<"How many would you like to sell?"<<endl;
		quantity = getChoice();
		if(healingItems < quantity || quantity < 0)
			throw quantity;
		healingItems -= quantity;
		currency += 250*quantity;
		break;
	case 2:
		if(attackBuffItems <= 0)
			throw quantity;
		cout<<"How many would you like to sell?"<<endl;
		quantity = getChoice();
		if(attackBuffItems < quantity || quantity < 0)
			throw quantity;
		attackBuffItems -= quantity;
		currency += 75*quantity;
		break;
	case 3:
		if(defenseBuffItems <= 0)
			throw quantity;
		cout<<"How many would you like to sell?"<<endl;
		quantity = getChoice();
		if(defenseBuffItems < quantity || quantity < 0)
			throw quantity;
		defenseBuffItems -= quantity;
		currency += 75*quantity;
		break;
	default:
		cout<<"something bad happened"<<endl;
	}
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
			    <<"(1) Healing Item - $500"<<endl<<"(2) Attack Booster - $150"
			    <<endl<<"(3) Defense Booster - $150"<<endl<<"(4) Cancel"<<endl;
			//cin>>inp;
			inp = getChoice(1,2,3,4);

			if(currency<=0)
				cout<<"You do not have enough money to make any purchases"<<endl;
			else
			{
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
		}

		else if(inp==2)
		{
			cout<<"What would you like to sell?"<<endl
			    <<"(1) Healing Items\tYou Have: "<<healingItems<<endl
			    <<"(2) Attack Boosters\tYou Have: "<<attackBuffItems<<endl
			    <<"(3) Defense Boosters\tYou Have: "<<defenseBuffItems<<endl
			    <<"(4) Cancel"<<endl;

			inp = getChoice(1,2,3,4);

			if(inp!=4)
			{
				try
				{
					sellItem(inp);
				}
				catch(int x)
				{
					cout<<"You can not sell the requested quantity of that item"<<endl;
				}
			}
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