#include <iostream>
#include "Creature.h"
#include "Player.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	cout<<"Welcome!"<<endl;

	Player p("Karl");
	p.shop();
	p.battle();
    
	return 0;
}