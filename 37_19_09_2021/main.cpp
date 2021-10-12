﻿/*

Bitseti inceliyorduk.Bitleri birarada tutan vector gibi. Amaç bir interface te bitleri birarada tutmak
Burada daha çok unsigned int türden değişkenler kullanılıyor.

Nontype template parametreli bir sınıf şablonu var.
Bitset sınıfını kullanmak ile C deki gibi kullanmak arasında performans farkı yok.

Burada bir sınıf sözkonusu ama template ler kodlar inline olarak açılıyorlar.

CTORLAR?
DEFAULT
UNSIGNED LONG LONG
STRING PARAMETRELİ CTOR yada CONST CHAR * PARAMETRELİ CTORLARI VAR

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	string str{"101011101001"};

	bitset<32> bs{"1010111001"}; // const char * parametreli ctor

	bitset<32> bs{str}; // String parametreli Ctor
	bitset<32> bsx{str,3}; // 3 ten başlayarak geri kalan hepsi
	bitset<32> bsy{str,3,5}; // 3 ten başlayarak 5 karakter demek

	cout << bs << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Dün dalgınlıkla yanlış anlattığı bir şeyi düzeltiyor hoca

"murat"s --> Burası Rvalue, lvalue değil.

"murat"s = "ali"; // atama olabilmesi bunun lvalue olduğu anlamına gelmesin

myclass mx;

myclass{} = mx; // mesela myclass{} rvalue expr ama atama yapılabilmiş.

HATTA BUNU REFERENCE QUAILIFER KONUSU ILE ÇÖZÜLÜYOR ŞUANDA BUNU ANLATTI HOCA
ZATEN ILERI C++ VE TEMEL C++ TA GÖRDÜK. YAZMIYORUM :D 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	bitset<16> bs{101101101};

	std::cout << bs.to_ullong() << "\n"; // return değeri unsigned long long türden
	std::cout << bs.to_ulong() << "\n"; // return değeri unsigned long türden
	
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BITSEL OPERATORLER OVERLOAD EDILMIŞ

int main()
{
	bitset<16> bx{5423u};
	bitset<16> bx{5912423u};

	std::cout << bx << "\n";
	std::cout << by << "\n";

	cout << (bx << 3) << "\n"; // left shift operatörleri yanyana overload edilmişler.
	cout << (bx >> 4) << "\n"; // Buda right shift
	
	cout << (bx & by) << "\n"; // bitsel & yutuyordu
	cout << (bx | by) << "\n"; // bitsel veya birleştiriyordu
	cout << (bx ^ by) << "\n"; // özel veya . farklıysa sonuç 1 aynıysa sonuç 0

	bx |= by; // işlemli atama operatörleride overload edilmiş.

}

soldan veya sağdan besleme tamamen 0 ile yapılır.bitset<16> bx{5423u}; bruada
ctor unsigned olduğundan hep 0.Çünkü burada C deki gibi bir sayı da değil sınıf üzerinden bu işlemleri yapıyoruz.

STL E VEDA

===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================

ITERATOR ADAPTER - BIND
-----------------------

Bind, bize bir callable veriyoruz o callable dan hareketle bize başka bir callable veriyor. Bİzim istediğimiz çağrı biçimine göre adapte ediyor.

Bir callable çağrıldığında biz buna argüman geçmeden önceden belirlenmiş argümanların geçilmesini istiyorum
Default argüman değil bu.

void foo(int x, int y, int z)
{
	std::cout << "x = " << x << " y = " << y << " z = " << z << "\n";
}

int main()
{
	std::bind(foo,std::placeholders::_1,std::placeholders::_2 .. ); // ilk argüman func adı, diğerleri func a geçilecek argümanlar

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	using namespace placeholders;

	auto f = std::bind(foo,_1,20,30); //Burada f e bir tane parametre göndereceğim, 2. ve 3. --->  20 ve 30 
	f(99) demek ----> f(99,20,30)

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	auto f = std::bind(foo,20,30,_1); //
	f(99) ---> f(20,30,99); demek

	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto f = std::bind(foo,_1,_1,50); //
	f(99) ---> f(99,99,50); demek
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto f = std::bind(foo,_1,_2,777); //
	f(10,20) ---> f(10,20,777); demek

	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto f = std::bind(foo,_3,_1,_2); //
	f(10,20,30) ---> f(30,10,20); demek
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto f = std::bind(foo); // Bu yapı mümkün değil :D:D

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Functor{
public:
	int operator()(int x, int y)
	{
		std::cout << "x =" << x << "\n";
		std::cout << "y =" << y << "\n";
	} 
};

int main()
{
	using namespace placeholders;

	auto fptr = &foo;

	auto f = bind(fptr,_1,_1,_1);
	f(12); --> f(12,12,12);

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	auto f = bind(Functor{},_1,90);
	f(12); --> f(12,90);

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	auto f = [](int a, int b, int c){return a * b * c;};

	auto fb = std::bind(f, _1, 20, _2)

	std::cout << fb(5,9) << "\n"; // f(5,20,9);

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ZOR KISIM - MÜLAKAT SORUSU

void foo(int &r1, int &r2)
{
	r1 += 10;
	r2 *= 20;
}


int main()
{
	using namespace placeholders;

	int x = 5;
	int y = 7;

	auto f = std::bind(foo,x,y);
	f(); // f(5,7); çağrılır

	std::cout << "x = " << x << "\n";
	std::cout << "y = " << y << "\n"; // DEĞERLER DEĞİŞMEDİ NEDEN

	BIZIM GÖNDERDIĞIMIZ ARGÜMANLARIN KOPYASINI ÇIKARTTIĞI IÇIN X VE Y YI KOPYALAMA SEMANTIĞI ILE ALIYOR.

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	DÜZELTELIM

	auto f = std::bind(foo,ref(x),ref(y)); // reference wrapper ile kullanılırsa değerler değişir.
	f(); // f(5,7); çağrılır

	std::cout << "x = " << x << "\n";
	std::cout << "y = " << y << "\n"; // Değerler değişti.


}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

void myprint(std::ostream &os, int x, int y)
{
	os << x << " " << y << "\n";
}

int main()
{
	myprint(std::cout,23,78);

	auto f = std::bind(myprint,std::cout,std::placeholders::_1,std::placeholders::_2); // bu sefer uzun yazdık
	
	//SENTAKS HATASI ÇÜNKÜ COUT OSTREAM SINIFI TÜRÜNDEN NESNE VE BU SINIF KOPYALAMAYA KAPALI.
	//BIND BUNU KOPYALAMAYA ÇALIŞIYOR. YINE REF ILE AŞARIZ BUNU

	auto f = std::bind(myprint,ref(std::cout),std::placeholders::_1,std::placeholders::_2); //GEÇERLİ
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIND SINIFIN ÜYE FONKSİYONLARIYLADA KULLANILIR

FUNCTION ŞUANDA STATIC

class Myclass{
public:
	static void set(int a,int b) // DİKKAT
	{
		std::cout << "Myclass::set(int a, int b)";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
	}
};

int main()
{
	using namespace std;
	using namespace placeholders;

	auto f = std::bind(&Myclass::set, _1, 90); // HATA YOK
	f(3); // GEÇERLi

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NONSTATIC ŞİMDİ

class Myclass{
public:
	void set(int a,int b) // DİKKAT
	{
		std::cout << "Myclass::set(int a, int b)";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
	}
};

int main()
{
	using namespace std;
	using namespace placeholders;

	Artık nesne gerekiyor çünkü sınıfın nonstatic func ı çağrılacak

	Myclass m;

	auto f = std::bind(&Myclass::set, _1, 10, 20); // HATA YOK
	
	f(m); 
	
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto f = std::bind(&Myclass::set, m, 10, _1); // HATA YOK

	f(33); 

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	Pointerda kullanılabilir.

	Myclass m;
	Myclass *pm = &m;

	auto f = std::bind(&Myclass::set, pm, 10, _1); // pm pointer olmasına rağmen düzgün çalışıyor.
	
	f(33); // Compile time da pointer mı nesnes mi diye kendisi anlıyor.Çağrıyı kullanırken . veya -> ile çağrıyı yapıyor.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : BIND DA İLAVE BİR MALİYET VAR.HOCA ÇOK KULLANMIYOR. BIND A GÖRE DAHA İYİ ALTERNATIF VARSA ONU KULLANIYOR.
BİND İLE LAMBDA ARASINDA SEÇİM YAPILACAĞI ZAMAN LAMBDA KULLANIYOR HOCA

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIND IN KULLANILMAYA ADAY SENARYOSU
MESELA BİR CALLABLE IN İNTERFACE İNİ ADAPTE ETMEK 

int main()
{
	using namespace std;
	vector<int> ivec(100);

	randomize(); // nutility de
	generate(ivec.begin(), ivec.end(), []{return rand() % 1000;});

	int ival;
	std::cout << "kactan buyuk olanlar yazdirilsin : ";
	cin>>ival;

	copy_if(ivec.begin(),ivec.end(),ostream_iterator<int>{cout, " "},[ival](int x){ return x > ival});  // Düzgün çalıştı
	
	// BURADA HOCAYI DINLE. DERS TEKRAR ETME MANTIĞI :D:D:D:D

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	using namespace placeholders;

	copy_if(ivec.begin(),ivec.end(),ostream_iterator<int>{cout, " "}, std::bind(std::greater<int>{}, _1,ival) ); 
	
	//Biraz karmaşık ama zor değil.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void func(int x, int y , int y)
{
	std::cout << x << " " << y << " " << z << "\n";  
}

int main()
{
	//bind(func,_1,30,50) bu ifade bir func object
	bind(func,_1,30,50)(90); // bu şekilde çağrılabilir.
}


====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================

MEM_FN

Bir sınıfın member functionunun çağrılması için kullanılan adapter

class Myclass{
public:
	Myclass() = default;
	void print()const{
		std::cout << "(" << mx << ")";
	}

	void set(int val)
	{
		mx = val;
	}
private:
	int mx{};
};

int main()
{
	using namespace std;

	Myclass mx;
	mx.print();

	auto f = mem_fn(&Myclass::set);

	f(mx,20); // set edildi mx. mx.set(20) ye dönüştürüyor
	mx.print(); 

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	auto pf = mem_fn(&Myclass::print);
	pf(mx); // mx.print() cagrildi.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MEM FN KULLANIM SENARYOSU

Mesela transform algoritması. Bu rangedeki öğeleri bir functiona gönderip onun geri dönüş değerini bir range e yazıyor.

int foo(const Date &d)
{
	return d.month_day();
}

int main()
{
	vector<Date> myvec;

	rfill(myvec,100,Date::random);

	transform(myvec.begin(), myvec.end(), ostream_iterator<int>{cout}, &Date::month_day)); // BU şekilde yazılırsa SENTAKS HATASI olur.ÇÜnkü month_day func parametresi date değil.
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	transform(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, " "),&foo); // Bu durumda foo nun parametresi Date olduğundan bu çalışır.
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	transform(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, " "),[](const Date &d){return d.year_day();});  // BUDA OLUR

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	transform(myvec.begin(), myvec.end(), ostream_iterator<int>(cout, " "), mem_fn(&Date::year_day) });  // buda mem_fn ile yapıldı

}

====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================


NOT_FN ADAPTER

Algoritmayı callable ın true değilde false verdiği değerler üzerinde çalıştırmamız gerekiyor.
Bu durumda bizim predicate ı sarmalayan ama predicate ın return değeri değilde bunun logic değerini döndüren bir adapter.


int main()
{
	std::cout << "bir tamsayi girin\n";
	int x;

	cin>>x;
	
	auto f = not_fn(&isprime);

	cout << boolalpha << f(x) << "\n";


}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KULLANILDIĞI YER ALGORITMALARIN PREDICATE PARAMETRELERI

vector<int> ivec;

rfill(ivec,100,Irand{0,10000});

copy_if(ivec,begin(),ivec.end(),ostream_iterator<int>{cout, " " }, isprime); // tam tersi prime olmayanları istiyoruz.boolean true değeri

copy_if(ivec,begin(),ivec.end(),ostream_iterator<int>{cout, " " }, not_fn(isprime)); // Prime olmayanlar burada.Return değeri boolean false değeri


====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================



MEMBER FUNCTION POINTER  /  MEMBER DATA POINTER
-----------------------------------------------

Function pointerları global funcların adreslerini tuttu şimdiye kadar.Üye functionların adresini tutan pointerlara değinmedik.
Global member func pointerı ile sınıfın static member func pointerı arasında fark yok.

class Myclass{
public:
	static void func(int)
	{
		std::cout << "Myclass::func(int x) x = "<< x << "\n";
	}
};

int main()
{
	void (*fp)(int) = Myclass::func;
	void (*fpx)(int) = &Myclass::func;
	auto fpy = &Myclass::func;

	fp(12);
	fpx(13);
	fpy(14); // Hepsi geçerli

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA NONSTATIC MEMBER FUNC A BAKILDI

SINIFIN NONSTATIC MEMBER FUNC POINTERLARI, STATIC MEMBER FUNC POINTERLARI VEYA GLOBAL FUNC POINTERLARINDAN FARKLI ŞEKİLDE TANIMLANIYORLAR.

class Myclass{
public:
	void func(int) // DİKKAT
	{
		std::cout << "Myclass::func(int x) x = "<< x << "\n";
	}
	int foo(int,int);
};

int main()
{
	void (*fp)(int) = Myclass::func; // BUNLAR SENTAKS HATASI ARTIK. GEÇERLI DEĞIL
	void (*fpx)(int) = &Myclass::func; //SENTAKS HATASI
}



int main()
{
	auto fp = &Myclass::func;
	//Burada türe bakalım. void (Myclass::*fp)(int x)

	void (Myclass::*fp)(int) = &Myclass::func; //GEÇERLİ
	
	int (Myclass::*fptr)(int,int) = &Myclass::foo; // GEÇERLİ

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ELIMIZDE BU POINTER VARSA BUNUN TUTTUĞU FUNCTIONU NASIL ÇAĞIRIRIZ.

class Myclass{
public:
	void func(int x) // DİKKAT
	{
		std::cout << "Myclass::func(int x) x = "<< x << "\n";
	}
	int foo(int,int);
};

using Mfptr = void (Myclass::*)(int);

int main()
{
	void (Myclass::*fp)(int) = &Myclass::func; // GEÇERLİ

	Mfptr fptr = &Myclass::func; //BURASIDA GEÇERLİ
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MEMBER FUNCTION POINTER ARRAY YAZALIM

class Myclass{
	int f1(int);
	int f2(int);
	int f3(int);
	int f4(int);
	int f5(int);
};

//typedef int (Myclass::*MFPTR)(int);

using MFPTR = int (Myclass::*)(int); //BURADA İKİSİDE GEÇERLİ TABİ

int main()
{
	int (Myclass::*fp[])(int) = { &Myclass::f1, &Myclass::f2, &Myclass::f3,&Myclass::f4,&Myclass::f5 };

	MFPTR fa[] = { &Myclass::f1, &Myclass::f2, &Myclass::f3,&Myclass::f4,&Myclass::f5 };
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN ÇOK KARIŞTIRILAN NOKTA 

class Myclass{
public:
	void func(int x)
	{
		std::cout << "Myclass::func(int x) x \n";
		std::cout << "x = " << x << "\n";
		std::cout << "this = " << this << "\n";
	}
	int mx;
};

int main()
{
	Myclass m;

	auto p = &m.mx; // int *

	auto p1 = &Myclass::mx;  // int myclass::*p1 = &Myclass::mx;   şeklinde tanımlanırdı auto olmasaydı.

	int Myclass::* p2 = &Myclass::mx; // auto kullanmadan yazdık aslındayukarıda da yazmıştım. // DİKKAT!!! DATA MEMBER POINTER BU

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	HEM MEMBER FUNC POINTER HEMDE DATA MEMBER POINTER IÇIN ELIMIZDE SADECE POINTER OLMASI YETERLI DEĞIL, NESNEYEDE IHTIYAÇ VAR.

	Myclass m;

	std::cout << "&m = " << &m << "\n";

	m.func(34); // OK
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	void (Myclass::*fp)(int) = &Myclass::func;
	
	fp(34); // Burada sentaks hatası var çünkü this pointer yok. gizli sınıf nesnesi nerede ?Nonstatic member func var ve nesne olmadan çağırmaya çalıştık

	m.fp(23); // m nesnesinin içinde böyle bir func yok. Yine hata.Name lookup hatası

}

AŞAĞIDAKİ ŞEKİLDE ÇAĞRILABİLİR.YENİ OPERATORLER VAR BUNLAR İÇİN

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

.* ve ->* OPERATORLERİ


class Myclass{
public:
	int mx;
	void func(int x)
	{
		std::cout << "Myclass::func(int x) x \n";
		std::cout << "x = " << x << "\n";
		std::cout << "this = " << this << "\n";
		std::cout << "------------------------------------\n";
	}
	
	void foo(int x)
	{
		std::cout << "Myclass::func(int x) x \n";
		std::cout << "x = " << x << "\n";
		std::cout << "this = " << this << "\n";
		std::cout << "------------------------------------\n";
	}
};

int main()
{
	Myclass m; // değişken tanımlandı

	std::cout << "&m = " << &m << "\n";

	void (Myclass::*fp)(int) = &Myclass::func; // Function pointer ile init edildi.

	m.*fp(12); // BURADA DA SENTAHS HATASI VAR AMA SEBEBİ OPERATOR ÖNCELİĞİ.BURADAKİ FUNC POİNTER THİS POİNTER OLARAK KULLANILACAK M NİN ADRESİYLE BİRLEŞTİRİYOR.


	(m.*fp)(10); // ARTIK ÇALIŞTI :D:D:D:D !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	fp = Myclass::foo; // Geçersiz.& olması lazım. Global veya static olsaydı fucntion to ptr conversiondan ötürü
	
	fp = &Myclass::foo; // GEÇERLİ

	(m.*fp)(20); // GEÇERLİ
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

->* OPERATÖRÜNE BAKALIM

Buradaki fark sol operand myclass nesnesi değilde bu nesneyi tutan bir adres olacak.

int main()
{
	void (Myclass::*fp)(int) = &Myclass::func;

	Myclass *mp = new Myclass;
	std::cout << "mp = " << mp << "\n";

	(mp->*fp)(20);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MEMBER FUNCTION POINTER ARRAY OLUŞTURUYORUZ

class Myclass{
public:
	int mx;
	void func(int x)
	{
		std::cout << "Myclass::func(int x) x \n";
		std::cout << "---------------------------------- \n";
	}

	void foo(int x)
	{
		std::cout << "Myclass::foo(int x) x \n";
		std::cout << "---------------------------------- \n";
	}
	
	void bar(int x)
	{
		std::cout << "Myclass::bar(int x) x \n";
		std::cout << "---------------------------------- \n";
	}
};


int main()
{
	Myclass m;

	void (Myclass::*fpa[])(int) = { &Myclas::func, &Myclas::foo, &Myclas::bar }; 

	for(auto fptr : fpa)
	{
		(m.*fptr)(2);
	}

	for(int i = 0; i < std::size(fpa); ++i )
	{
		(m.*fpa[i])(i);
	}

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR FUNC IN PARAMETRESİ MEMBER FUNC OLABİLİR.

void g(Myclass &r, void (Myclass::*fp)(int))
{
	(r.*fp)(0);
}

int main()
{
	Myclass m;

	g(m, &Myclass::func);
	g(m, &Myclass::foo);
	g(m, &Myclass::bar);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİRAZ DAHA KARMAŞIK BİR ÖRNEK

Sınıfın elemanıda olabilir

class Myclass{
public:
	Myclass() = default;

	Myclass(void(Myclass::*fp)(int)) : mfp{fp} { }

	void set(void(Myclass::*fp)(int)) 
	{
		mfp = fp;
	}

	void g()
	{
		(this->*mfp)(15);
		//((*this).*mfp)(15); böylede olabilirdi.
	}

	void func(int x)
	{
		std::cout << "Myclass::func(int x) x  = " << x << "\n";
		std::cout << "---------------------------------- \n";
	}

	void foo(int x)
	{
		std::cout << "Myclass::foo(int x) x  = " << x << "\n";
		std::cout << "---------------------------------- \n";
	}

	void bar(int x)
	{
		std::cout << "Myclass::bar(int x)  = " << x << "\n";
		std::cout << "---------------------------------- \n";
	}

private:
	void(Myclass::*mfp)(int) = &Myclass::foo; // BURADA &MYCLASS İLE NİTELENMEZSE ÇALIŞMAZ YANİ !!!!!
	
	// void(Myclass::*mfp)(int) = Myclass::foo; // BURASI ÇALIŞMAZ ÇÜNKÜ & YOK !!!!!!
	// void(Myclass::*mfp)(int) = &foo; // BURASI ÇALIŞMAZ !!!!!!

};

int main()
{
	Myclass m;

	m.g(); // foo çağrılır

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	Myclass m {&Myclass::baz};

	m.g(); // baz çağrılır

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	m.set(&Myclass::foo);
	m.g(); // foo çağrıldı

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DATA MEMBER POINTER

struct Myclass {
	int x = 234;
	int y = 912;
};

int main()
{
	Myclass mx;

	int Myclass::*ptr = &Myclass::x; // DATA MEMBER PTR OLUŞTURDUK.

	std::cout << "mx.x = " << mx.x << "\n";
	std::cout << "mx.y = " << mx.y << "\n";
	
	mx.*ptr= 1111;
	std::cout << "mx.x = " << mx.x << "\n";
	
	--------------------------------------------

	ptr = &Myclass::y;

	m.*ptr = 333;

	std::cout << "mx.y = " << mx.y << "\n";
}


====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================

INVOKE
------

BİR CALLABLE VE O CALLABLE A GÖNDERILECEK ARGÜMANLARI ALIYOR VE BIZIM YERIMIZE CALLABLE I O ARGÜMANLARLA ÇAĞIRIYOR.
BURADA .* VEYA ->* FARKETMİYOR.KENDİSİ ANLAYIP ONA GÖRE ÇAĞRI YAPIYOR.ARKA PLANDA TEMPLATE BU ŞEKİLDE COMPİLE TİMEDA ANLIYOR.
BİND BİR CALLABLE VERİYORDU. INVOKE İSE DOĞRUDAN FUNCTION ÇAĞIRIYOR

void gfunc(int x, int y)
{
	std::cout << "gfunc cagrildi\n";

	std::cout << "x = " << x << \n";
	std::cout << "y = " << y << \n";
}


int main()
{
	std::invoke(gfunc,10,20); // bizim için gfunc ı 10 ve 20 argümanlarıyla çağırdı

	auto flam = [](int x){ return x * 5 - 3; };

	std::cout << std::invoke(flam,10) << "\n"; // Sonuc 47. Bu seferde flam çağrıldı

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

class Functor
{
public:
	Functor(int x) : mx{x} { }
	int operator()(int x,int y)const
	{
		return mx * (x + y);
	}

private:
	int mx;
};

int main()
{
	std::cout << std::invoke(Functor{5}, 10,20) << "\n"; 
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ ÖRNEK

class Nec
{
public:
	int func(int x, int y)
	{
		std::cout << "Nec::func(int,int)"

		return x * x + y * y;
	}
}

int main()
{
	Nec Mynec;

	std::cout << std::invoke(&Nec::func,mynec,5,9) << "\n"; // Member pointer function ile nesne birleşip func çağırırdı. Burada ekstradan 5 ve 9 argüman olarak
															// gönderilmiş.

	----------------------------------------------------------------------------------------------------------------------------------------------------------------

	Nec Mynec;
	
	int(Nec::*fptr)(int,int);

	std::invoke(fptr, mynec, 10, 20); //SENTAKS HATASI. POINTER NULLPTR VEYA GARBAGE OLURSA SENTAKS HATASI OLUŞUR.BİR FUNC İLE İLİŞKİLENDİRİLMELİ

	----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Nec Mynec;
	
	Nec *Necptr = &Mynec;

	int(Nec::*fptr)(int,int) = Nec::func;

	std::invoke(fptr, Necptr, 10, 20); // Burada ->* ile çağırması gerekti.

}


====================================================================================
====================================================================================

NOT :
int(Nec::*fptr)(int,int) --> Bu sınıfın nonstatic member func adresini tutacak.
int(*fptr)(int) --> Bu ise sınıfın static veya global funcların adresini tutar.

====================================================================================
====================================================================================

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DATA MEMBER POINTER ÖRNEĞİ

struct Nec{
	int x;
};

int main()
{
	int Nec::*ptr = &Nec::x;
	
	Nec mynec;

	mynec.*mptr = 98;	// bu şekilde data member pointer ile erişedebiliriz.

	std::invoke(mptr,mynec) = 99; //data memberlar içinde kullanılabilir.
}

====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================




DİNAMİK BELLEK YÖNETİMİ
-----------------------
Dinamik ömürlü nesne nedir: Runtime da istnedildiği zaman oluşturabileceğimiz istediğimiz zaman hayatını bitirebileceğimiz nesneler.

Dinamik ömürlü nesnelerin kullanıması için , runtime da bunların storage larının elde edilmesi gerekiyor.
Bunların storage larının elde edilmesi farklı, allocate edilen bellek bloğunun kullanılabilmesi başka.

C olsaydı
---------

struct Data{
	int a, b, c;
	double d;
	char str[40];
};


int main()
{
	struct Data *p = (struct Data *)malloc(sizeof(struct Data));

	if(!p)
	{
		//..	
	}

	p->...


	//işimiz bitince
	free(p);
}

Gerek c gerek C++ için temel ilkeleri unutmamak gerekiyor.En tipik hatalar java ve c# tan gelenler yaşıyor bunu, zannediyorlarki bizdeki dinamik ömürlü nesne kullanımı ile
onlardaki aynı. Mesela new Myclass javada. C#ve javada sınıf türlerinden nesneler dinamik ömürlü olmak zorunda.Biz C++ ta bunun maliyetine katlanmak istemiyoruz. Çünkü allocation
maliyeti çok çok fazla. Deallocationda çok maliyetli. Dolayısı ile otomatik ömürlü nesne ile işimizi görecek yerde dinamik ömürlü ile çalışırsak bu 50 kat belkide daha maliyetli demek.

- Dinamik ömürlü nesnelerin kullanılmasına ilişkin seenaryo yoksa dinamik ömürlü nesne kullanma !!!!!!
- Kod çok daha karmaşık hale gelir!!!!! Karmaşık senaryolarda ipin ucu kaçarsa memory leak oluşabilir !!!!!!

Bazende öyle temalar varki nesne dinamik ömürlü olarak hayata getirilmek zorunda. Runtime polymorphism bunlardan biri.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Dinamik ömürlü nesneler new ifadeleriyle/operatörleriyle oluşturuluyor. Operator seviyesinde bir işlem.
Dinamik ömürlü nesnelerin hayatını sonlandırmak için delete operatörünü kullanmak gerekiyor

new Myclass
						new Myclass[n]
new (address)Myclass
						new (address)Myclass[n]
new (nothrow)Myclass
						new (nothrow)Myclass[n]


delete p
						delete[]p


Sol grupta bir tane nesne için işlem yapılıyor sağ taraftaki grupta elemanları myclass türünden olan bir dinamik dizi hayata getiriyoruz.
Bu operatörleri hiç kullanmayacağız yada çok az kullanacağız

====================================================================================================================================================================================
====================================================================================================================================================================================
====================================================================================================================================================================================

NEW MYCLASS
-----------
New operatorü derleyici tarafında operator new isimli func a gönderilen nesnenin sizeof değerini argüman olarak yazıyor ve 
return edilen adresi construct edeceği sınıfın this adresi olarak kullanıp bu adresle constructor çağırıyor.
operator new başarısız olursa std::exceptiondan kalıtımla elde edilen std::bad_alloc türünden nesne throw eder.
Başarılı olursa buradan elde ettiği adresi void * ı Myclass * türüne dönüştürür. Bu adres için sınıfın Ctorunu çağırıyor zaten

void* operator new(size_t)


DELETE
------
delete ptr;

Bu sefer sınıfın destructoru çağrılır ve daha sonrasında operator delete çağrılır ve bellek bloğu geri verilir.

Dİğer biçimlerinde de fark yok
new Myclass[n] dersek operator new[]() çağrılır. Bu da yine operator new i n * sizeof(myclass) kere çağırıyor.
Yani burada ctor bir kez değilde n tane dinamik ömürlü nesnenin herbiri için çağrılır.

new Myclass[n] --> operator new[]() 

int main()
{
	auto p = new string{"Mustafa Tahsin Aksoy"}; // dinamik ömürlü string nesnesi

	delete p;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

New ifadesi overload edilemez. Operator New func overload edilebilir.Operator new in birsürü overloadu var. Bir tanesi sadece overload edilemiyor bizim tarafımızdan
void operator new(void *, size_t); Bunu yazmak yasaklanmış. Diğerlerini kendimiz yazabiliriz.

%100 doğru olmayan ama anlaşılması için operator new ve operator delete functionlarını overload edeceğiz.

Operator New
------------

void *operator new(size_t n)
{
	std::cout << "My operator new called\n";
	std::cout << "n = " << n << "\n";

	void *p = std::malloc(n);
	if(!p) // Burası bu kadar basit değil aslında görülecek 
	{
		throw std::bad_alloc{};
	}

	std::cout << "The adress of the allocated block : " << p << "\n";
	return p;
}

class Myclass{
public:
	Myclass()
	{
		std::cout << "Myclass Default Ctor\n";
		std::cout << "This = " << this << "\n";
	}
private:
	unsigned char buffer[1024]{};
};

int main()
{
	std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n"; // Burada adrese baktık

	Myclass *p = new Myclass; // myclass sizeof 1024 zaten onuda yazdırdık operator new içinden

	std::cout << "p = " << p << "\n"; //Buradan da adrese baktık aynı.
}

ÇIKTI
-----
sizeof(Myclass) = 1024
My operator new called
n = 1024
The adress of the allocated block : 0103FC88
Myclass Default Ctor
This = 0103FC88
p = 0103FC88


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Operator Delete
---------------

void operator delete(void *vp)
{
	std::cout << "My operator delete called\n";
	std::cout << "vp = " << vp << "\n";
	std::free(vp); //free ye nullptr geçmek etkisiz kod
	std::cout << " block deallocated\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DAHA ÖNCE GÖRMEDİKLERİMİZE BAKALIM. OPERATOR NEW BU ŞEKİLDE YAZILMIYOR   :D:D:D:D:D

#include <new>
new içinde bir typedef ismi var. Adı new_handler. C de yazmıştık biz bunu.

typedef void (*new_handler)(void); // return değeri olmayan parametresi olmayan function adresinin türeş ismi new_handler
using new_handler = void(*)(void); // Buda using ile yapıldı.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SET_NEW_HANDLER
---------------

set_new_handler new içinde bildirilmiş. Buna bir adres verdiğimizde, gp nin değerini(aşağıda) bizim verdiğimiz adres ile set ediyor ve
gp nin eski değerinide get(return olarak gönderiyor yani) ediyor.

new_handler set_new_handler(new_handler p)
{
	auto fp = gp;
	gp = p;
	return fp;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Global bir function pointer var. Bu nullptr adresi ile initialize edilmiş.

new_handler gp = nullptr;

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GET_NEW_HANDLER

Birde C++11 ile gelen get_new_handler functionu var.Sadece global func pointerı get ediyor.

new_handler get_new_handler()
{
	return gp;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OPERATOR NEW BAŞARISIZ OLDUĞUNDA BAD_ALLOC THROW EDIYOR DEMIŞTIK AMA GERÇEK BÖYLE DEĞIL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GERÇEK HALLERİ 

void* operator new(size_t n)
{
	while(true)
	{
		void *vp = std::malloc(n); // malloc kullanmak zorunda değil burada
		if(vp)
			return vp;
		else
		{
			auto fptr = std::get_new_handler();
			if(!fptr)
				throw std::bad_alloc{};
		
			fptr();
		}
	}	
}

ÇOK ÖNEMLİ !!!!
---------------
1. Bu döngüden çıkmamız için 2 ihtimal var. 1. ihtimal global func pointerı kimse set etmemiş olacak, malloc başarısız olduğunda fptr nin değeri nullptr olacak 
ve bu döngüden çıkacak

2. Malloc başarısız oldu ama benim functionum çağrıldı(set_new_handler ile set edilen func), benim func ım bir şekilde dinamik bellek alanı elde etmenin yolunu bulursa,
bu döngüden başarılı olduğundan çıkacak.
Eğer bu durumda yer allocate edemezse, (mallocun sonunda yer allocate etmesi gerekiyor) döngüden çıkamıyor.Malloc eninde sonunda yer elde etmek zorunda.

	Bu durumda döngüden çıkma yolları şunlar
	a - Global func göstericisini kendi func ımıza set edeceğiz ve bu func başarılı olacak.bizimkinde malloc başarılı olmalı.ne kullanılırsa
	b - Bizim çağırdığımız func fptr ı yine null ptr yapacak o zaman yine döngüden çıkacak.
	c - set edilen function başka bir function ile set_new handler çağıracak bu seferde new handler olarak o func şansı deneyecek.
	d - Yada terminate çağrılacak
	e - Tam tersi new_handler func ımız exception throw edecek.


	Standartlar diyorki throw edilecek exception y bad alloc türünden olmalı, yada bundan kalıtımla elde edilmiş sınıf türünden olacak.
	Başka türden exception throw etmek yasaklanmış.


BURADA İMKANLARIMIZ NELER
-------------------------
a - Programcı set_new_handler işlevini çağırır set_new_handler(my_new_handler);
	my_new_handler aşağıdakileri yapacak

	void my_new_handler()
	{
		1 - başarılı olmasını sağlayacak koşulları oluşturur.Mesela baştan bir alanı reserve edebilir.Bunun için Hocayı aradım.
			Baştan dinamik olarak bir alan allocate edilebilir, benim handlerımda o alanı free edebilir.Free den sonra yer açıldığı için
			malloc çağrısında yeri allocate etme şansım olur.ÇOK ÖNEMLİ !!!!!!
		2 - Doğrudan bad_alloc throw et.Bad_alloctan kalıtımla elde edilmiş bir sınıfta olabilir.
		3 - set_new_handler ı nullptr ile çağır
		4 - std::terminate i çağır
		5 - set_new_handler ile başka bir new handlerı set et.
		BUNLARDAN BİRİNİ YAPMAK ZORUNDA
	}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖRNEK İLE AÇIKLAYALIM

class Myclass{
private:
	unsigned char buffer[1024]{};
};

Myclass *p;

int main()
{
	try{
		while(true) // bir süre sonra yer ayıramayıp bad_alloc throw edecek.
		{
			p = new Myclass;		
			std::cout << '.';		
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	} // BİRYERDE BAD ALLOC THROW ETTİ
}


ÇIKTI
----
.................................................
.................................................
.................................................
.............exception caught : bad allocation


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HANDLER YAZDIK

class Myclass{
private:
	unsigned char buffer[1024]{};
};

void myhandler()
{
	std::cout << "myhandler called...\n";
	(void)getchar();
}

Myclass *p;

int main()
{
	std::set_new_handler(&myhandler);
	try{
		while(true)
		{
			p = new Myclass;
			std::cout << '.';
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	} 
}

ÇIKTI
-----
.....................................................
.....................................................
................................................
myhandler called...

myhandler called...

myhandler called...

myhandler called...

myhandler called...

myhandler called...

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//1. YAPILACK

class Myclass{
private:
	unsigned char buffer[1024]{};
};

void myhandler() 
{
	static int count = 0;

	std::cout << "myhandler called...\n";
	if(++count == 5)
	{
		throw std::bad_alloc{};
	}
	(void)getchar();
}

Myclass *p;

int main()
{
	std::set_new_handler(&myhandler);
	try{
		while(true)
		{
			p = new Myclass;
			std::cout << '.';
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}

ÇIKTI
-----
.....................................
.....................................
.....................................
.....................................
....
myhandler called...

myhandler called...

myhandler called...

myhandler called...

myhandler called...
exception caught : bad allocation


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//2. YAPILACAK

class Myclass{
private:
	unsigned char buffer[1024]{};
};

void myhandler() 
{
	static int count = 0;

	std::cout << "myhandler called...\n";
	if(++count == 5)
	{
		std::terminate();
	}
	(void)getchar();
}

Myclass *p;

int main()
{
	std::set_new_handler(&myhandler);
	try{
		while(true)
		{
			p = new Myclass;
			std::cout << '.';
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}

Çıktı
-----
.......................................................
.......................................................
....................................
myhandler called...

myhandler called...

myhandler called...

myhandler called...

myhandler called...

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//3. YAPILACK

class Myclass{
private:
	unsigned char buffer[1024]{};
};

void myhandler() 
{
	static int count = 0;

	std::cout << "myhandler called...\n";
	if(++count == 5)
	{
		std::set_new_handler(nullptr);
	}
	(void)getchar();
}

Myclass *p;

int main()
{
	std::set_new_handler(&myhandler);
	try{
		while(true)
		{
			p = new Myclass;
			std::cout << '.';
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}


ÇIKTI
-----
.......................................................
.......................................................
....................................
myhandler called...

myhandler called...

myhandler called...

myhandler called...

myhandler called...

exception caught : bad allocation

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//4. YAPILACK. SON İHTİMAL
Başka bir handler olabilir.

class Myclass{
private:
	unsigned char buffer[1024]{};
};

void another_handler() 
{
	std::cout << "another handler called\n";
}

void myhandler() 
{
	static int count = 0;

	std::cout << "myhandler called...\n";
	if(++count == 5)
	{
		std::set_new_handler(another_handler);
	}
	(void)getchar();
}

Myclass *p;

int main()
{
	std::set_new_handler(&myhandler);
	try{
		while(true)
		{
			p = new Myclass;
			std::cout << '.';
		}
	}
	catch(const std::bad_alloc &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}

ÇIKTI
------
.......................................................
.......................................................
....................................
another handler called
another handler called
another handler called
another handler called
another handler called
another handler called
another handler called
another handler called
another handler called
another handler called
Sonsuza kadar çağrılacak çünkü another handlerda birşeyu yapmadık

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MEKANİZMA
Operator new başarısız olursa exception throw ederim ama istersen sen bunu değiştirebilirsin.
Operator new başarısız olursa doğrudan exception throw etmesini istemezsen set_new_handler funcını çağıracaksın ve ona kendi handler fonksiyonunun(return değeri olmayan func ın)
adresini geçeceksin. O fonksiyonda az önceki yöntemlerden birini kullanacak.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : New ifadesini otomatik ömürlü const bir nesne oluştururkende kullanabiliriz.

class Myclass{
	void foo();
private:
	unsigned char buffer[1024]{};
}

int main()
{
	auto ptr = new const Myclass;
	ptr->foo(); // sentaks hatası çünkü nesne const function değil :D:D AMA nesne yaratıldı
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ARRAY NEW

Bu operator new[] çağırıyor o da operator new çağırıyor.

class A{
public:
	A()
	{
		std::cout << "Default Ctor\n";
	}

};

int main()
{
	A* p = new A[10];

	delete[] p;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOK ÖNEMLİ !!!!!!!!

EĞER ARRAY DELETE YERINE, DELETE KULLANIRSAK TANIMSIZ DAVRANIŞ   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
EĞER DELETE YERİNE, ARRAY DELETE KULLANIRSAK TANIMSIZ DAVRANIŞ YİNE  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

ÖR:

A* p = new A[10];

delete p; // TANIMSIZ DAVRANIŞ

------------------------------
veya

A* p = new A;

delete p[]; //TANIMSIZ DAVRANIŞ



*/