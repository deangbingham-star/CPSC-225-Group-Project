/*
Dean Bingham- Fred Washington
main function
PSEUDOCODE

*/

#include <iostream>
#include "Creature.h"
#include "Player.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
    bool hasBeatenBoss = false;
    int userSelect;
    
    
    
	cout<<"Welcome!"<<endl;

	Player p("Karl");
	cout<<"pre-battle"<<endl;
	p.battle();
	cout<<"post battle"<<endl;
    p.battle();
    
    
    
    /*
    while (hasBeatenBoss == false)
    {
        //ask user what they want to do
        cin>> userSelect;
        
        if(userSelect == 1)
        {
        //do battle function
        }
        
        if(userSelect == 2)
        {
            //do shop function
        }
        
        if(userSelect == 3)
        {
            //do boss function
        }
    }
    
    */
    
    
	return 0;
}
