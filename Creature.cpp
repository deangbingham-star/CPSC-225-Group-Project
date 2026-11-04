#include <iostream>
#include "Creature.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;

Creature::Creature()
{
    cout<<"Creature spawned"<<endl;
    name = "Basic Creature";
    maxHP = 50;
    currentHP = 50;
    baseDamage = 10;
    attackBuff = 15;
    defenseBuff = 0;
    captureRate = 0;
}

void Creature::takeDamage(int x)
{
    currentHP -= x;
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
    
    return os;
}