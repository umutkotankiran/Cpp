#include "date.h"
#include <iostream>

Date::Date(int d, int m, int y) : md{ d }, mm{ m }, my{ y }
{
	// bu blok mutlaka olmalı. boş olsa bile.
}

void Date::set( int d, int m, int y )
{
	md = d;
	my = y;
	mm = m;
}

void Date::print()const
{
	std::cout << md << "-" << mm << "-" << my << "\n";
}
