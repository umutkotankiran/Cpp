#include "date.h"

void Date::set(int d, int m, int y)
{
	m = mm;
	d = md;
	y = my;
}

/*
 
EĞER AŞAĞIDAKİ GİBİ TANIMLANIRSA GLOBAL FUNCTION OLUR
Derleyici class member function olan set function olduğunu yukarıdaki gibi anlar.
Aşağıdaki gibi olursa GLOBAL FUNCTION olur.

void set(int d, int m, int y)
{

}

*/