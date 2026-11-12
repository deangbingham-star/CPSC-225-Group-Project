#include <iostream>
#include <fstream>
#include "Creature.h"
#include "CustomUtilities.h"
using std::string;
using std::cout;
using std::endl;
using std::ostream;

Creature::Creature()
{
	cout<<"Creature spawned"<<endl;
	name = "Basic_Creature";
	creatureType = "Basic Creature";
	maxHP = 50;
	currentHP = 50;
	baseDamage = 10;
	attackBuff = 0;
	defenseBuff = 0;
	captureRate = 0;

	level = 1;
	xpToLevel = 100;
	curXP = 0;
}

Creature::Creature(ifstream& fin)
{
	cout<<"Saved creature spawned"<<endl;
	creatureType = "Basic Creature";
	fin>>name;
	fin>>maxHP;
	fin>>currentHP;
	fin>>baseDamage;
	fin>>attackBuff;
	fin>>defenseBuff;

	fin>>level;
	fin>>xpToLevel;
	fin>>curXP;
}

void Creature::takeDamage(int x)
{
    if(x<=0)
    {
        cout<<"The attack's damage is nullified"<<endl;
        cout<<name<<"takes 0 damage!"<<endl;
    }
	else if(defenseBuff>0)
	{
		currentHP -= (x/defenseBuff);
		cout<<name<<" takes "<<x/defenseBuff<<" damage!"<<endl;
	}
	else if(defenseBuff<0)
	{
		currentHP -= (x-(defenseBuff*5));
		cout<<name<<" takes "<<x-(defenseBuff*5)<<" damage!"<<endl;
	}
	else
	{
		currentHP -= x;
		cout<<name<<" takes "<<x<<" damage!"<<endl;
	}
}
/*
void Creature::applyAttackBuff(int x)
{
    cout<<"Applying attack buff"<<endl;
	attackBuff += x;
}

void Creature::applyDefenseBuff(int x)
{
    cout<<"Applying defenes buff"<<endl;
	defenseBuff += x;
}
*/
void Creature::grantXP(int x)
{
	curXP+=x;
	while(curXP>=xpToLevel)
	{
		levelUp();
	}
}

void Creature::levelUp()
{
	level++;
	cout<<"Congratulations, "<<name<<" has reached level "<<level<<endl;
	curXP -= xpToLevel;
	xpToLevel += 50;
	baseDamage += 10;
	setHP(maxHP+=25);
}

void Creature::Attack(Creature* c, bool isOwned)
{
	cout<<endl<<name<<" is attacking!"<<endl<<endl;
	c->takeDamage(baseDamage + (attackBuff*5));
}

void Creature::saveCreatureData(ofstream& fout)
{
	//prints Creature stats to fout in order: Creature Type, Creature Name, maxHP, currentHP, baseDamage, attackBuff, defenseBuff
	fout<<creatureType<<endl;
	fout<<name<<endl;
	fout<<maxHP<<endl;
	fout<<currentHP<<endl;
	fout<<baseDamage<<endl;
	fout<<attackBuff<<endl;
	fout<<defenseBuff<<endl;

	fout<<level<<endl;
	fout<<xpToLevel<<endl;
	fout<<curXP<<endl;
}

Creature::~Creature()
{
	cout<<"Creature deleted"<<endl;
}

ostream& operator<<(ostream& os, Creature* c)
{
	os<<c->name<<endl;
	os<<"Type: "<<c->creatureType<<endl;
	os<<"Level: "<<c->level<<endl;
	os<<"Level progress: "<<c->curXP<<"/"<<c->xpToLevel<<endl;
	os<<"Current HP = "<<c->currentHP<<"/"<<c->maxHP<<endl;
	os<<"Attack buff status: "<<c->attackBuff<<endl;
	os<<"Defense buff status: "<<c->attackBuff<<endl;

	return os;
}

/******************************************************************************/
Boss::Boss()
{
    cout<<"Boss creature spawned"<<endl;
	name = "Boss";
	creatureType = "Boss Creature";
	maxHP = 500;
	currentHP = 500;
	baseDamage = 100;
	attackBuff = 0;
	defenseBuff = 0;
	captureRate = 0;

	level = 1;
	xpToLevel = 1000;
	curXP = 0;
}

void Boss::Attack(Creature* c, bool isOwned)
{
    int action;
    //checks whether or not this creature is owned by the player
    //if false actions are randomly selected, if true, user selects action
    if(isOwned == false)
        action = getRandNum(1,5);
    else
    {
        cout<<"Which action would you like to take?"<<endl
            <<"(1) Normal Attack\n(2) Stat Boost\n(3) Reckless Attack"
            <<"\n(4) HP Restore\n(5) Debuff Opponent"<<endl;
        action = getChoice(1,2,3,4,5);
    }
    
    switch(action)
    {
        case 1:
            cout<<name<<" is attacking!"<<endl;
            c->takeDamage(baseDamage + (attackBuff*5));
            break;
        case 2:
            cout<<name<<" boosted it's attack and defense"<<endl;
            defenseBuff++;
            attackBuff++;
            break;
        case 3:
            cout<<name<<" uses a reckless attack!"<<endl;
            c->takeDamage(baseDamage*2 + (attackBuff*5));
            currentHP-=100;
            break;
        case 4:
            cout<<name<<" restores 200 HP"<<endl;
            if((currentHP+200)>maxHP)
                currentHP=maxHP;
            else
                currentHP+=200;
            break;
        case 5:
            cout<<"case 5"<<endl;
            break;
        default:
            cout<<"Error -> boss attack function"<<endl;
    }
}

void Boss::levelUp()
{
    level++;
	cout<<"Congratulations, "<<name<<" has reached level "<<level<<endl;
	curXP -= xpToLevel;
	xpToLevel += 500;
	baseDamage += 100;
	setHP(maxHP+=250);
}

Boss::Boss(ifstream& fin)
{
	cout<<"Saved boss creature spawned"<<endl;
	creatureType = "Boss Creature";
	fin>>name;
	fin>>maxHP;
	fin>>currentHP;
	fin>>baseDamage;
	fin>>attackBuff;
	fin>>defenseBuff;

	fin>>level;
	fin>>xpToLevel;
	fin>>curXP;
}