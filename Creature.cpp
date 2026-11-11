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
}

Creature::~Creature()
{
	cout<<"Creature deleted"<<endl;
}

ostream& operator<<(ostream& os, Creature* c)
{
    os<<c->name<<endl;
    os<<"Type: "<<c->creatureType<<endl;
    os<<"Current HP = "<<c->currentHP<<endl;
    os<<"Attack buff status: "<<c->attackBuff<<endl;
    os<<"Defense buff status: "<<c->attackBuff<<endl;
    
    return os;
}