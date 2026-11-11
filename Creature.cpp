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
    name = "Basic Creature";
    maxHP = 50;
    currentHP = 50;
    baseDamage = 10;
    attackBuff = 0;
    defenseBuff = 0;
    captureRate = 0;
}

Creature::Creature(ifstream& fin)
{
    cout<<"Saved creature spawned"<<endl;
    fin>>name;
    fin>>maxHP;
    fin>>currentHP;
    fin>>baseDamage;
    fin>>attackBuff;
    fin>>defenseBuff;
}

void Creature::takeDamage(int x)
{
    if(defenseBuff>0)
        currentHP -= (x/defenseBuff);
    else if(defenseBuff<0)
        currentHP -= (x-(defenseBuff*5));
    else
        currentHP -= x;
}

void Creature::applyAttackBuff(int x)
{
    attackBuff += x;
}

void Creature::applyDefenseBuff(int x)
{
    defenseBuff += x;
}

void Creature::Attack(Creature* c)
{
    cout<<"Attacking!"<<endl;
    c->takeDamage(baseDamage);
}

Creature::~Creature()
{
	cout<<"Creature deleted"<<endl;
}

ostream& operator<<(ostream& os, Creature* c)
{
    os<<c->name<<endl;
    os<<"Current HP = "<<c->currentHP<<endl;
    os<<"Attack buff status: "<<c->attackBuff<<endl;
    os<<"Defense buff status: "<<c->attackBuff<<endl;
    
    return os;
}