#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Creature.h"
#include "Player.h"
#include "CustomUtilities.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
    srand(time(NULL));
	cout<<"Welcome!"<<endl;
	
	Player p("Karl");
	p.shop();
	p.battle();
    
    
	return 0;
}