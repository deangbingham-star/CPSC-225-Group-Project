/*
Stores, manages text colors
*/



/*
COLORS TO BE USED

Dark colors: For console related output
Dark Yellow -- Console errors
Dark Red -- Delete creature
Dark Grey -- Less important stuff

bright colors: Player related input
Light green -- player creatures
light red -- enemy creatures

*/

#include <iostream>
#include <string>
#include "Color.h"

using namespace std;


void Colorize(string color, string text)
{
    cout<<color<<text<<DEFAULT<<endl;
}
