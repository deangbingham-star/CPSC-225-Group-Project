#include <iostream>
#include <fstream>
#include "Creature.h"
#include "Player.h"
#include "Color.h"
#include "CustomUtilities.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

//Player Initialization//
/******************************************************************************/
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
    string error = "Error while reading from PlayerData.txt";
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
        string CreatureType;
        fin>>CreatureType;
        
		//calls corresponding creature type's constructor and passes in the ifstream
		if(CreatureType == "Basic_Creature")
			creatures[x] = new Creature(fin);
		else if(CreatureType == "Tank")
			creatures[x] = new Tank(fin);
		else if(CreatureType == "Fighter")
			creatures[x] = new Fighter(fin);
			
		else if(CreatureType == "Mage")
			creatures[x] = new Mage(fin);
			
		else if(CreatureType == "Boss_Creature")
			creatures[x] = new Boss(fin);
		else
		    throw error;
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
			Colorize(BOLDRED, "invalid input, please try again");
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
/******************************************************************************/

//Player Status Management//
/******************************************************************************/
void Player::viewStatus()
{
	int decision;
	Colorize(BOLDCYAN, "Current player status:");
	wait(1);
	cout<<"Currency: $"<<currency<<endl;
	wait(1);
	cout<<"\nCurrently carrying:"<<endl;
	wait(1);
	cout<<"Healing Items: "<<healingItems<<endl;
	wait(1);
	cout<<"Attack Boosters: "<<attackBuffItems<<endl;
	wait(1);
	cout<<"Defense Boosters: "<<defenseBuffItems<<endl;
	wait(1);
	cout<<"\nOwned creatures: "<<numCreatures<<endl;
	wait(1);

	for(int x = 0; x<numCreatures; x++)
	{
		cout<<BOLDCYAN;
		cout<<"("<<x+1<<") "<<creatures[x]->getName()<<endl;
		cout<<DEFAULT;
		wait(1);
	}
	Colorize(BOLDYELLOW, "\nWhat would you like to do?");
	cout<<"(1) View Creature Status\n(2) Switch Active Creature\n(3) Return"<<endl;

	decision = getChoice(1,2,3);
	if(decision==1)
	{
		/*Asks user which creature they'd like to display info for,
		then calls viewStatus for selected creature*/
		cout<<"Which creature would you like to view?"<<endl;
		decision=getChoice(1,2,3);
		while(decision>numCreatures)
		{
			Colorize(BOLDRED, "invalid input, please try again");
			decision = getChoice(1,2,3);
		}
		cout<<creatures[decision-1];

		Colorize(BOLDYELLOW, "\nWould you like to restore this creature's status? Cost: $50");
		Colorize(RED, "(Doing so will restore currentHP to max value and reset all buff/debuff effects)");
		cout<<"(1) Yes\n(2) No"<<endl;
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
				Colorize(BOLDRED, "invalid input");
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

	Colorize(BOLDYELLOW, "Which creature would you like to set active?");
	wait(1);
	cout<<BOLDCYAN;
	for (int x = 0; x < numCreatures; x++)
	{
		cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}
	cout<<DEFAULT;
	//cin >> inp;
	inp = getChoice();

	if (inp > numCreatures || inp <= 0)
		throw inp;
	if (creatures[inp-1]->getCurHP()<=0)
		throw unavailable;

	activeCreature = creatures[inp - 1];
	wait(1);
	cout<<"Your active creature is now "<<activeCreature->getName()<<endl;
}

void Player::setActiveCreature(int n)
{
	int inp;
	Colorize(BOLDYELLOW, "Which creature would you like to set active?");
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
	Colorize(BOLDYELLOW, "Which creature would you like to remove?");

	for (int x = 0; x<numCreatures; x++)
	{
		cout<<x+1<<": "<<creatures[x]->getName()<<endl;
	}
	//cin>>inp;
	inp=getChoice();

	if(creatures[inp-1]==activeCreature)
	{
		bool successful = false;
		Colorize(BOLDRED, "You are attempting to delete your currently active creature");
		Colorize(BOLDYELLOW, "Please set a different active creature before proceeding");
		
		while(successful==false)
		{
			try
			{
				setActiveCreature(inp);
				successful = true;
			}
			catch(int x)
			{
				Colorize(BOLDRED, "invalid input, please try again");
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

/******************************************************************************/

//Player actions//
/******************************************************************************/

bool Player::catchCreature(Creature* c)
{

	if(c->getCurHP() <= float(c->getMaxHP())*c->getCaptureRate() || getRandNum(1,20)==20)
	{
		int decision;
		try
		{
			addCreature(c);
			return true;
		}
		catch (int x)
		{
			cout << "You are carrying the max number of creatures." << endl
			     << "Would you like to remove a creature to make room?" << endl
			     <<"(1) Yes\n(2) No"<<endl;

			decision = getChoice(1,2);

			if(decision==1)
			{
				try
				{
					removeCreature();
					addCreature(c);
					return true;
				}
				catch(int x)
				{
					cout<<"There are no creatures to remove."<<endl;
				}
			}
		}
	}
	else
	{
		cout<<"Capture attempt failed"<<endl;
		return false;
	}
	return false;
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
			Colorize(BOLDRED, "invalid input, please try again");
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
			Colorize(BOLDRED, "ERROR");
		}
	}
}

bool Player::battle(bool boss)
{
	bool continueBattle = true;
	int decision;
	Creature* opp;
	
	wait(1);

	if(boss == false)
	{
		int enemyType = getRandNum(1,4);

		switch(enemyType)
		{
		case 1:
			opp = new Creature();
			break;
		case 2:
			opp = new Tank();
			break;
		case 3:
			opp = new Fighter();
			break;
		case 4:
			opp = new Mage();
			break;
		default:
			opp = new Creature();
		}

		Colorize(BOLDYELLOW, "An enemy creature has appeared!");
		wait(1);
		opp->setName("Enemy");
	}
	else
	{
		opp = new Boss();
		Colorize(BOLDYELLOW, "You approach the boss and prepare for battle");
		wait(1);
	}

	while (continueBattle == true)
	{
		bool turnEnd = false;

		if (opp->getCurHP() <= 0)
		{
			if(boss == true)
			{
				Colorize(BOLDGREEN, "The boss has been defeated!");
				wait(1);
			    Colorize(YELLOW, "Your creatures are awarded with 1000xp");
				for(int x = 0; x<numCreatures; x++)
				{
					creatures[x]->grantXP(1000);
				}
			}
			else
			{
				Colorize(BOLDGREEN, "The opposing creature has been defeated!");
			    Colorize(YELLOW, "Your creatures are awarded with 100xp");
				for(int x = 0; x<numCreatures; x++)
				{
					creatures[x]->grantXP(100);
				}
			}
			continueBattle = false;
			delete opp;
			return true;
		}

		if(activeCreature->getCurHP() <= 0)
		{
			bool canSwitch = false;

			cout<<BOLDRED<<activeCreature->getName()<<" has been knocked out"<<DEFAULT<<endl;

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
						Colorize(BOLDRED, "invalid input, please try again");
					}
					catch(string s)
					{
						Colorize(BOLDRED, s);
					}
				}
			}
			else
			{
				Colorize(BOLDRED, "All of your creatures have been knocked out");
				wait(1);
                Colorize(YELLOW, "You are forced to retreat from the battle");
				Colorize(YELLOW, "$100 are spent to restore your creatures");
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
		    wait(1);
			Colorize(BOLDYELLOW, "\n(1) Attack, (2) Capture, (3) Switch Active Creature, (4) Use Item, (5) Escape");
			//cin >> decision;
			decision = getChoice(1,2,3,4,5);

			if (decision == 1)
			{
				activeCreature->Attack(opp, true);
				cout << opp;
				if (opp->getCurHP() <= 0)
				{
					if(boss == true)
					{
						cout<<"The opposing creature has been defeated"<<endl
						    <<"Your creatures are awarded with 1000xp"<<endl;
						for(int x = 0; x<numCreatures; x++)
						{
							creatures[x]->grantXP(1000);
						}
					}
					else
					{
						cout<<"The opposing creature has been defeated"<<endl
						    <<"Your creatures are awarded with 100xp"<<endl;
						for(int x = 0; x<numCreatures; x++)
						{
							creatures[x]->grantXP(100);
						}
					}
					continueBattle = false;
					delete opp;
					return true;
				}
				turnEnd = true;
			}
			else if (decision == 2)
			{
				cout<<"You attempt to capture "<<opp->getName()<<endl;
				bool success = catchCreature(opp);
				if(success==true)
				{
					cout<<"Capture Successful"<<endl;
					opp->Restore();
					return true;
				}
				turnEnd = true;
			}
			else if (decision == 3)
			{
				try {
					setActiveCreature();
				}
				catch (int x)
				{
					Colorize(BOLDRED, "invalid input");
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
			else if (decision == 5)
			{
				if(getRandNum(1,20)==20)
					cout<<"Escape attempt failed"<<endl;
				else
				{
					cout<<"You escaped successfully"<<endl;
					delete opp;
					return true;
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
	Colorize(BOLDYELLOW, "How many would you like to purchase?");
	//cin>>quantity;
	quantity = getChoice();

	if(quantity<0)
	{
		Colorize(BOLDRED, "You can not purchase a negative quantity");
		return 0;
	}
	else if(currency < x*quantity)
	{
		Colorize(BOLDRED, "You do not have enough currency to complete this purchase.");
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
		Colorize(BOLDYELLOW, "How many would you like to sell?");
		quantity = getChoice();
		if(healingItems < quantity || quantity < 0)
			throw quantity;
		healingItems -= quantity;
		currency += 250*quantity;
		break;
	case 2:
		if(attackBuffItems <= 0)
			throw quantity;
		Colorize(BOLDYELLOW, "How many would you like to sell?");
		quantity = getChoice();
		if(attackBuffItems < quantity || quantity < 0)
			throw quantity;
		attackBuffItems -= quantity;
		currency += 75*quantity;
		break;
	case 3:
		if(defenseBuffItems <= 0)
			throw quantity;
		Colorize(BOLDYELLOW, "How many would you like to sell?");
		quantity = getChoice();
		if(defenseBuffItems < quantity || quantity < 0)
			throw quantity;
		defenseBuffItems -= quantity;
		currency += 75*quantity;
		break;
	default:
		Colorize(BOLDRED, "ERROR");
	}
}

void Player::shop()
{
	bool stayInShop = true;
	int inp;

	while(stayInShop == true)
	{
		cout<<BOLDCYAN<<"You currently have $"<<currency<<DEFAULT<<endl;
		Colorize(BOLDYELLOW, "Would you like to buy or sell items?");
		cout<<"(1) Buy"<<endl<<"(2) Sell"<<endl;
		//cin>>inp;
		inp = getChoice(1,2);

		if (inp==1)
		{
			Colorize(BOLDYELLOW, "Which type of item would you like to purchase?");
			   cout <<"(1) Healing Item - $500"<<endl<<"(2) Attack Booster - $150"
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
					Colorize(BOLDRED, "ERROR");
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
/******************************************************************************/

//Player deletion//
/******************************************************************************/
Player::~Player()
{
	for (int x = numCreatures; x > 0; x--)
	{
		delete creatures[x-1];
		numCreatures--;
	}
}
/******************************************************************************/