#pragma once

#include <iosfwd>
#include <stdexcept>

class Mint {
public:
	explicit Mint(int x = 0) : mval{ x } { } // bu nesneye direkt bir sayı atanamayacak.explicit engelledi
	friend std::ostream& operator<<(std::ostream&, const Mint&);
	friend std::istream& operator>>(std::istream&, Mint&);
	friend bool operator<(const Mint& x, const Mint& y)
	{
		return x.mval < y.mval; // sınıfa friend olduğundan private bölüme erişim bir hata değil.ADL var yine muhtemelen
	}
	friend bool operator==(const Mint& x, const Mint& y)
	{
		return x.mval == y.mval;
	}
	//diğerlerini sınıf içinde değilde cpp file da tanımlayacağız.

	Mint& operator+=(const Mint& r)
	{
		mval += r.mval;
		return *this;// kendisine atama yapılan nesneyi ref semantiği ile döndürdü
	}

	Mint& operator-=(const Mint& r)
	{
		mval -= r.mval;
		return *this;// kendisine atama yapılan nesneyi ref semantiği ile döndürdü
	}

	Mint& operator*=(const Mint& r)
	{
		mval *= r.mval;
		return *this;// kendisine atama yapılan nesneyi ref semantiği ile döndürdü
	}

	Mint& operator/=(const Mint& r)
	{
		if (r.mval == 0)
			throw std::runtime_error("Sifira bolme hatasi\n");

		mval /= r.mval;
		return *this;// kendisine atama yapılan nesneyi ref semantiği ile döndürdü
	}


	Mint operator+()const   // return değeri sağ taraf değeri olduğundan referans yapmadık
	{
		return *this;
	}

	Mint operator-()const   // return değeri sağ taraf değeri olduğundan referans yapmadık
	{
		return Mint{ -mval }; // Mint türünden geçici nesne ama bunu mval değil -mval ile oluşturup return ettik.
	}


	Mint& operator++() //prefix
	{
		++mval;
		return *this;
	}

	Mint operator++(int) //postfix. dummy int. biz değil derleyici kullanacak
	{
		Mint temp{ *this }; // nesneyi temp isimli değişkende sakladı yani kopyasını çıkardı

		++* this; // bu Mint sınıuf türden bir nesne. Bu aslında bir üstteki Mint& operator++() //prefix fonksiyonunu çağıracak. 
		//operator++(); buda aynı şey bir üstteki ile.
		//istersek this->operator++(); yap
		//Eğer operator++(0); deseyedik recursive çağrı olacaktı.

		return temp; // ama kopyayı return et. klasik x++;
	}


	Mint& operator--() //prefix
	{
		--mval;
		return *this;
	}

	Mint operator--(int) //postfix. dummy int. biz değil derleyici kullanacak
	{
		Mint temp{ *this }; // bir kopyasını al

		--* this; // kendisini bir azalt. Bu aslında bir üstteki Mint& operator--() //prefix fonksiyonunu çağıracak.
		//operator--(); buda aynı şey bir üstteki ile.

		return temp; // ama kopyayı return et. klasik x--;
	}


private:
	int mval;
};

inline bool operator>=(const Mint& x, const Mint& y)
{
	return !(x < y); // >= demek küçük değil demek 
	// return !operator<(x, y);  yukarıdaki ile aynı anlamda
}

inline bool operator>(const Mint& x, const Mint& y)
{
	return y < x;  
	//return operator<(y,x); Aynı anlamda 
}

inline bool operator<=(const Mint& x, const Mint& y)
{
	return !(y < x);
}

inline bool operator!=(const Mint& x, const Mint& y)
{
	return !(x == y);
	//return !operator(x,y); böylede olur.
}


inline Mint operator+(Mint left, const Mint& right) // en son bunu koyduk
{
	return left += right;
	//1. parametresine geçici nesne gönderilirse doğrudan copy elision oluşacak.
}

inline Mint operator-(Mint left, const Mint& right) // en son bunu koyduk
{
	return left -= right;
	//1. parametresine geçici nesne gönderilirse doğrudan copy elision oluşacak.
}

inline Mint operator*(Mint left, const Mint& right) // en son bunu koyduk
{
	return left *= right;
	//1. parametresine geçici nesne gönderilirse doğrudan copy elision oluşacak.
}

inline Mint operator/(Mint left, const Mint& right) // en son bunu koyduk
{
	return left /= right;
	//1. parametresine geçici nesne gönderilirse doğrudan copy elision oluşacak.
}
