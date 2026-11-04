#include <iostream>
#include "Creature.h"
#include "Player.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int Player::numCreatures = 0;

Player::Player(string n = "Joe") : NAME(n)
{
    cout << "" << endl;
    addCreature();
    activeCreature = creatures[0];
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

    creatures[numCreatures] = c;
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
    cin >> inp;
    if (inp > numCreatures)
        throw inp;

   activeCreature = creatures[inp - 1];
}

void Player::removeCreature()
{
    if (numCreatures <= 0)
        throw numCreatures;
    numCreatures--;
    delete creatures[numCreatures];
}

void Player::catchCreature(Creature* c)
{
    try
    {
        addCreature(c);
    }
    catch (int x)
    {
        cout << "You are carrying the max number of creatures." << endl
            << "Would you like to remove a creature to make room?" << endl;
    }
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
        cout << "(0)Attack, (1)Capture, (2)Switch Active Creature" << endl;
        cin >> decision;
        if (decision == 0)
        {
            activeCreature->Attack(opp);
            cout << opp;
            if (opp->getCurHP() <= 0)
            {
                continueBattle = false;
                delete opp;
            }
        }
        else if (decision == 1)
        {
            catchCreature(opp);
            continueBattle = false;
        }
        else if (decision == 2)
        {
            try {
                setActiveCreature();
            }
            catch (int x)
            {
                cout<<"invalid input" << endl;
            }
        }

        if (continueBattle == true)
        {
            opp->Attack(activeCreature);
            cout << activeCreature;
        }

    }
}

Player::~Player()
{
    for (int x = numCreatures; x > 0; x--)
        removeCreature();
}