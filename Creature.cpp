#include <iostream>
#include "Creature.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

Creature::Creature()
{
    cout<<"Creature spawned"<<endl;
}

void Creature::Attack()
{
    
}

Creature::~Creature()
{
	cout<<"Creature deleted"<<endl;
}