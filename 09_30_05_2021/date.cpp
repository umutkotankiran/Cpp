#include "date.h"
#include <iostream>

void Date::print()const
{
	std::cout << md << "-" << mm << "-" << my << "\n";
}
