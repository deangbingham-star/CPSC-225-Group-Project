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
    attackBuff = 0;
    defenseBuff = 0;
}

void Creature::Attack(Creature* c)
{
    cout<<"Attacking!"<<endl;
    c->takeDamage(25);
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