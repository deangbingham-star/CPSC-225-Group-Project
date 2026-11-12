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
	if(defenseBuff>0)
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

void Creature::grantXP(int x)
{
	curXP+=x;
	if(curXP>=xpToLevel)
	{
		levelUp();
	}
}

void Creature::levelUp()
{
	level++;
	cout<<"Congratulations, "<<name<<" has reached level "<<level<<endl;
	curXP = 0;
	xpToLevel += 50;
	baseDamage += 10;
	setHP(maxHP+=25);
}

void Creature::Attack(Creature* c)
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