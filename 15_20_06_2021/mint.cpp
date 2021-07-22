#include "mint.h"
#include <ostream>
#include <istream>

std::ostream& operator<<(std::ostream&os, const Mint&m)
{
	return os << "(" << m.mval << ")"; // burada çağrılanlar ostream sınıfının member funcları ya da global functionlar.
	//buradan çağrılan en son functionda os i referans yoluyla döndürdüğü için bunu return edebiliriz.main de kabaca ostream ne döndürüyor
	// yazmıştık. ostream& döndürüyordu.

	//return os; // normalde bu döndürülecek.İdiyomatik olarak yukarıdaki yazıldı
}
// burada return değeri ostream türden referans. Çünkü kendinden sonra çağrılacak olan functiona da bu parametre argğman olarak gönderiliyor.
// Neden 1. parametre const & değil ? os için sadece const üye functionları çağırabilirdik ama os için çağrılan funclar const member func değil.
// HEr yazdırmada bu nesne değişiyormuş - ileride görülecek.

std::istream& operator>>(std::istream& is, Mint& m)
{
	return is >> m.mval; 
}