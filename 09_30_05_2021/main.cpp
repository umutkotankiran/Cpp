/*

BUGÜN SINIFLARIN ÖZEL ÜYE FONKSİYONLARINA GİRİLECEK ASLINDA
ÖNCESİNDE BAZI BOŞLUKLAR DOLDURULACAK.

DELETE FUNCTION ÖZETİ YAPILDI

========================================================================================================
========================================================================================================
========================================================================================================
========================================================================================================
========================================================================================================

FUNCTION DEFAULT EDİLMESİ
-------------------------
FUNCTION DEFAULT EDİLMESİ SADECE SINIFIN ÖZEL ÜYE FONKSİYONU İÇİN GEÇERLİ.
BUNLAR 6 TANE İDİ. 
- DEFAULT CONSTRUCTOR
- DESTRUCTOR
- COPY CONSTRUCTOR
- MOVE CONSTRUCTOR
- COPY ASIGNMENT
- MOVE ASIGNMENT

DERLEYICI BU FONKSIYONUN KODUNU BENIM IÇIN YAZ DEMEK BU.
BUNU YAPMASAYDIK DERLEYICI YINE DEFAULT ETMEYECEK MIYDI?
BELIRLI KOŞULLAR VAR GÖRÜLECEK BUGÜN


Sentaks
-------
class Myclass{
public:
	Myclass() = default;
};


------------------------------------------------

default bildirimi public te olmak zorunda değil.
private bölümünde de olabilir.

class Myclass{
	Myclass() = default;
public:

};


==============================================================================================================
==============================================================================================================

BU GÜNÜN KONULARINDAN BAZILARI
------------------------------

1 - C++ dilinin tür dönüştürme öperatörleri(type operators)
2 - Extern C bildirimleri

Biri sordu açıklanıyor.

class Myclass{
public:
	void print()const
	{
		std::cout << x << y << z << "\n";
	}
private
	int x,y,z;
}

int main()
{	
	Ctor yazsakta yazmasakta;
	Myclass m; // Bu default initializer. Otomatik ömürlü primitive değişkenler bu durumda Indetermined value olarak başlar
		   // default ctor yoksa sentaks hatası olur.
		   // derleyici ctoru yazdıysa elemanları default init eder.

	EĞER Ctor u derleyici yazarsa;(Myclass() = default demekte derleyiciye yazdırmak aslında.Aynı şey.)
	Myclass x{}; // value init
			 // burada elemanlarıda value init eder.
			 // primitive türden türleri value init edersek 0 ile başlar hayata


	EĞER Boş ctor yazarsak;
		Myclass x{}; // value init
				// bu sefer yine Indetermined value ile başlar hayata.
}



--------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------

Type Conversion ile Type cast farklı şeylerdir.

1. TİP
Type conversion : Bir ifadenin türünün bir işleme sokulmadan önce dönüştürülmesine deniyor.
		  1. implicit type conversion
			 ival + dval; burada implicit type conversion var mesela

		  2. explicit type conversion
		     Aşağıdaki ( ) operatörüne type cast operator deniyor.
			 (double)ival + dval; buda explicit


C-Style cast deniyor bunlara

C++ ta bu tip tür dönüştürme operatörlerinin kullanılması istenmiyor.
Neden istenmediğini C++ taki tür dönüştürme operatörlerini gördüğümüzde göreceğiz.

---------------------------------------------------------------------------------------------------------------------------------

Her tür dönüşümünda amaç aynı değil.

i1 * i2
(double)i1 / i2

ival = dval; yazılmaz ama isteyerek yapıyorsak yine tür dönüştürme operatörü.
ival = (int)dval; yazılır

const nesne adresinin const olmayan nesne adresine dönüştürülmesi.Bu tanımsız davranış
C de dönüşüm var. ama veriyi değiştirince UB olur. C örnekleri
int x = 10;
const int *p = &x;
*p = 20; UNDEFINED BEHAVIOR


-------------------------------------------------------------------

2. TİP
PHYSICAL CONSTNESS VE CONTRACTUAL CONSTNESS OLARAK IKIYE AYIRIYOR CONSTLUĞU HOCA

Veriyi tutan pointerın const int * p ile tanımlanması sözleşme constu :D
const int x ise fiziksel olarak const


int * func(const int *ptr)
{
	return (int *)ptr; // Legal. böyle yapılan işlemlere const cast deniyor.
}

------------------------------

C den strchr örneği verdi.

------------------------------

const T *p = expr;

T *ptr = (T *)p;

----------------------------------------------------------------------

3. TİP
Farklı tür dönüşümü amacı 
Bir nesnenin adresini sanki o nesne başka türdenmiş gibi, farklı türden adrese dönüştürüyoruz.


double dval = 2.3;
int *p = (int*)dval;   SENTAKS HATASI YOK AMA UNDEFINED BEHAVIOR VAR.
						ama istisnaları var. Strict Aliasing Rules

char *p = (char *)&dval; MESELA BURASI UB DEĞİL.

endiannes a falan baktık. casting yapıldığı için.

--------------------------------------

SONUÇ
C DE BİR ŞEKİLDE YAPILIYOR BU TÜR DÖNÜŞTÜRME
C++ TA 4 FARKLI KEYWORD VAR.

1 - static_cast : int ten double a, char dan double a gibi...
2 - const_cast : const t * dan t * a gibi.
3 - reinterpret_cast : Adresler ile ilgili yapılan dönüşüm.int * dan double * a gibi
4 - dynamic_cast, C de karşılığı yok.Inheritance, runtime polymorphism ile ilgili.

Bunları yerinde kullanmak şart. const yerine static kullanılamaz.
her biri tam olarak uygun kullanılmalı.


ÇOK ÖNEMLİ AVANTAJI
Debug işlemleri.Tür dönüşümü programlama hatalarının en önemli sebeplerinden biridir.
En risklileri reinterpret_cast. Kodda bunları ararız. C de ise parantezleri ara ki
bulasın.

<> = angular bracket

SENTAKS
keyword<hedef tür>(operand)

ÖRNEKLER
static_cast<int>(dval)
const_cast<int *>(ptr)

BURADAKİ ÖRNEKLER HATALI
ÖR:
main
	int x = 10;
	double dval = 2.8;
	x = reinterpret_cast<int>(dval);  GEÇERSİZ.SENTAKS HATASI.


	const int *ptr = nullptr;
	reinterpret_cast<int *>(ptr)	  GEÇERİZ BURASI CONST CAST ÇÜNKÜ.

-------------------------------------------------------------------

İKİ ADET CAST NASIL YAPILABİLİR

const int x = 10;
char *p = reinterpret_cast<char *>(&x); neden hata ? const int * dan char * a hata.
					const var çünkü

const ile yapsanda yine olmaz. bu seferde reinterpret cast var.
ikisini birden uygulamak gerekebilir.


char *p = reinterpreted_cast<char *>(const_cast <int *>(&x));  burada değiştirilmiş hali.
char *p = const_cast<char *>(reinterpret_cast <const char *>(&x)); burada farklı bir hali var.

------------------------------------------------------------------------------------------------------------

enum türleri ile aritmetik türler arasındaki cast static ile yapılıyor.

enum Color {White,Red,Green};

int main()
{
	Color mycolor { Red };
	int ival = mycolor; // BU LEGAL. GENÇLIK HATASI LEGAL OLMASI IDI
	mycolor = ival; burası SENTAKS HATASI
	mycolor = static_cast<color>(ival); GEÇERLİ.
}

enum class yazsakta aynı şekilde dönüşüm var.

------------------------------------------------------------------------------------

VOID * DÖNÜŞÜMLERI IÇIN HEM STATIC CAST HEMDE REINTERPRET CAST KULLANILABILIR.

+
#include cstdlib

std::size_t n = 20;
int *p1 = std::malloc(n * sizeof(int);   burası SENTAKS HATASI
int *p2 = static_cast<int *>(std::malloc(n * sizeof(int)));   GEÇERLİ
int *p3 = reinterpret_cast<int *>(std::malloc(n * sizeof(int))); GEÇERLİ


==============================================================================
==============================================================================
==============================================================================


Extern "C" Bildirimleri.

Sentaks
extern "C" func_bildirimi;		 1. tip

extern "C" {					 2. tip.

	//fonksiyon1
	//fonksiyon2
	//..
}


C derleyici ile derlenmiş kodların kodlarının C++ ile derlenen kodlardan çağrılması tipik bir durum.

C++ ta yazılırsa
#include "nutility.h"

int main()
{
	int x = 201;
	int y = isprime(x);  Hata 
}

Burada compile edince linker hatası verdi.
Linkerın objeyi bulamama hatası.
nedeni ?
C de derlenmiş bir fonksiyonun C++ tan derlenen bir kod içinden çağrılması.

C de function overloading yok.
C++ ta func overloading var.

C de linkera bunun ismini yazarken fonksiyonun parametrik yapısına hiç bakmaz.
C++ ta ise parametrelerde önemli çünkü func overloading var.
name mangling : obje koda referans isim yazılma metodu demek.

Amaç kodda yazılan isimler farklı yani.Link aşamasında uymsuzluk oluşuyor.
Bunu çözmek için aşağıdaki bildirim yapılıyor.

C++ ta yazılıyor aşağısı

extern "C" int isprime(int ); 		Böyle garip bir bildirim

int main()
{
	int x = 201;
	int y = isprime(x);		Artık hata yok.
}

--------------------------------------------------------------------------------------

veya toplu halde aşağıdaki gibi yapılır.

extern "C" {

	//fonksiyon1
	//fonksiyon2
	//..
}


Şimdi Kullanım Nasıl olacak ?

Bu başlık dosyalarının hem C hemde C++ tan kullanılmasını istersek koşullu derleme komutlarını
kullanacağız.

__STDC__  PREDEFINED SYMBOLIC CONSTANT. C dilinde bu defined kabul edilir.

Bunun C++ ta karşılığı __cplusplus .Sonda __ yok.
Bu C++ derleyicilerde defined kabul edilecek.

C buraya girmeyecek.
C++ buraya girer

extern "C" içerisine sadece fonksiyonlar olacak.

Çok yaygın bu kullanım.
#ifdef __cplusplus

extern "C" {

#endif

	int isprime(int);
	int ndigit(int);
	void swap(int *, int *);

}
#ifdef __cplusplus

}

#endif


============================================================================
============================================================================
============================================================================
============================================================================
============================================================================


MOLADAN SONRASI
Bir soru soruldu bu zaten açıklanmıştı 50. satırda.
CPPREFERANSTAN ALINDI
1) if T is a class type with no default constructor or with a user-provided or deleted default constructor, the object is default-initialized;
2) if T is a class type with a default constructor that is neither user-provided nor deleted (that is, it may be a class with an implicitly-defined or defaulted default constructor),
the object is zero-initialized and then it is default-initialized if it has a non-trivial default constructor;

-----------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------


ŞİMDİ CLASS LARDAN DEVAM 

class Nec {
public:
	Nec()
	{
		std::cout << "Nec default ctor this = "<< this << "\n";
	}
	~Nec()
	{
		std::cout << "Nec destructor this = "<< this<< "\n";
	}
};

int main()
{
	Nec nec;

	Nec x = nec;	
}
	
Yukarıda 1 adet ctor, 2 adet destructor çağrılıyor.
Destructor dan gelen adreslerde farklı. Ctor 1 kere çağrıldı ama iki nesne hayata geldi.

ÇIKTI
-----
Nec default ctor this = 0115FE47
Nec destructor this = 0115FE3B
Nec destructor this = 0115FE47


-------------------------------------------------------------

Diğer örnek

class Nec {
public:
	Nec()
	{
		std::cout << "Nec default ctor this = "<< this << "\n";
	}
	~Nec()
	{
		std::cout << "Nec destructor this = "<< this<< "\n";
	}
};

void func(Nec a)
{
	std::cout << "func cagrildi\n";
	std::cout << "func sona erdi\n";
}

int main()
{
	Nec x;
	func(x);
	getchar();
}

ÇIKTI
-----
Nec default ctor this = 00EFFE4F
func cagrildi
func sona erdi
Nec destructor this = 00EFFD74

Nec destructor this = 00EFFE4F

BU 2 ÖRNEKTE BİR CTOR ÇAĞRILIYOR AMA BUNLAR DEFAULT CTOR DEĞİL.
COPY CTOR(CC).

===================================================================================================================
===================================================================================================================
===================================================================================================================
===================================================================================================================
===================================================================================================================

COPY CONSTRUCTOR

C++ dilinde eğer bir sınıf nesnesi değerini(kopyalama yoluyla) aynı türden
başka sınıf nesnesinden alarak hayata gelecek ise, sınıfın copy constructor denen
özel bir ctor çağrılır.

Hangi Durumlarda copy ctor çağrılmasını bekleriz.

T x; olsun

T y = x; 
T y(x);
T y{x};

auto y = z;
auto y(z);
auto y{z};

void func(T x); burada parametre değişkenini hayata getirmek için copy ctor devreye girer
T y;		T burada sınıf
func(y);

ÖR:
Myclass foo()
{
	return g;
}

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

class Nec {
public:
	Nec()
	{
		std::cout << "Nec default ctor this = "<< this << "\n";
	}
	~Nec()
	{
		std::cout << "Nec destructor this = "<< this<< "\n";
	}
};

Burada copy ctoru biz yazmadık.
Copy ctorlar derleyici tarafından implicitly olarak yazılıyor.
Bizde yazabilirdik zaten.Derleyicinin yazdığı copy ctor işimizi görüyorsa onu kullanmalıyız ama
görmediği durumlarda kendimiz yazacağız.


DERLEYİCİNİN YAZDIĞI(DEFAULT ETTİĞİ) COPY CTOR(CC)
  A - SINIFIN PUBLIC
  B - NONSTATIC
  C - INLINE FUNCTION  OLMAK ZORUNDA


DEFINITION:
-----------
class Myclass{
public:
	Myclass(const Myclass &other) : ax(other.ax), bx(other.bx),cx(other.cx)
	{  }
private:
	A ax;
	B bx;
	C cx;
	// ..
};

Myclass x = y;
x, y den copy ctor ile değerlerini alacak nesne
y ise other işe eşleşecek 


---------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------

Burada Date.h ve Date.cpp yi artık kullanıyorum. İçeriklerine bak.

int main()
{
	Date x;
	x.print();

	Date y = x; // Date y{x}; buda aynıdır.auto y = x; buda öyle.
	y.print();
}

ÇIKTI
-----
1-1-1998
1-1-1998

-------------------------------------------------------------------------------------------------------------

DAHA GÜZEL BİR ÖRNEK.

class Myclass
{
public:
	Myclass(int val = 0) : mx{ val }	ÇOOOOK ÖNEMLİ NOT: BU ŞEKİLDE DEFAULT PARAMETER ALINCA DA DEFAULT CTOR OLUR.TANIMINDA VARDI BU.
	{														PARAMETRESİ OLMAYAN VEYA TÜM PARAMETRELERİ DEFAULT ARG OLAN.
		std::cout << "Myclass default Ctor this = " << this << "\n";
	}

	Myclass(const Myclass &other) : mx{other.mx}
	{
		std::cout << "Myclass copy Ctor  this = " << this << " &other = " << &other<<"\n";
	}

	~Myclass()
	{
		std::cout << "Myclass default destructor this = " << this << "\n";
	}
private:
	int mx;
};

int main()
{
	Myclass a(10);
	Myclass b = a;

	std::cout << "&a = " << &a << "\n";
	std::cout << "&b = " << &b << "\n";
}

ÇIKTI
-----

Myclass default Ctor this = 0054FA04
Myclass copy Ctor  this = 0054F9F8 &other = 0054FA04
&a = 0054FA04
&b = 0054F9F8
Myclass default destructor this = 0054F9F8
Myclass default destructor this = 0054FA04

COPY CTORU BU ÖRNEKTE HEM ANLAMAK HEMDE İÇERİSİNDE COUT YAZDIRMAK İÇİN YAZDIK.

SPECİAL MEMBER FUNCTIONLARIN DERLEYİCİ TARAFINDAN YAZILMASI TERCİH EDİLİR.
RULE OF ZERO DENİYOR BUNA. ÖYLE DURUMLAR VAR Kİ DERLEYİCİNİN YAZDIĞI CTOR İŞİMİ GÖRMÜYOR.
BU DURUMLARDA KENDİM YAZMAM GEREKİYOR.

----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------


BAZI SINIF NESNESİ ELEMANLARI POİNTER OLUYOR. BURADA POİNTER COPY DEN SONRA, PTR FREE EDİLİRSE
KOPYALADIĞIMIZ ADRESTE KENDİSİDE DANGLING HALE GELİR.
UZUN UZUN ANLATTI BUNU 2.25 TEN SONRA OLMALI.
SHALLOW COPY / DEEP COPY OLAYLARI BURADA ÖNEMLİ OLUYOR.

---------------------------------------------------
BİRİNCİ ÖRNEKTE DERLEYİCİYE BIRAKILACAK BU İŞ.
İKİNCİ ÖRNEKTE İSE COPY CONSTRUCTORU BİZ YAZACAĞIZ.
---------------------------------------------------

BİRİNCİ ÖRNEK
sentence.h içerisinde inline olarak yazılacak functionlar
---------------------------------------------------------
class Sentence {
public:
	Sentence(const char *p);
	~Sentence();
	void print()const;
	int lenght()const // // lenght i inline olarak yazıyoruz
	{
		return mlen;
	}
private:
	char* mp;
	size_t mlen;
};

====================================================================================================================

sentence.cpp içine yazılacaklar.
-------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "sentence.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

Sentence::Sentence(const char* p) : mlen{ strlen(p) }
{
	mp = static_cast<char*>(malloc((mlen + 1) * sizeof(char)));
	if (!mp)
	{
		std::cout << "Bellek yetersiz\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "Edinilen bellek blogunun adresi = " << static_cast<void*>(mp) << "\n";
	strcpy(mp, p);
}

void Sentence::print()const
{
	std::cout << "(" << mp << ")"<< "\n";
}

Sentence::~Sentence()
{
	std::cout << static_cast<void *>(mp) << " adresindeki blok free ediliyor\n";
	free(mp);
}

// lenght i inline olacak yazdık.

====================================================================================================================

main içinden
------------

void foo(Sentence s)	
{
	std::cout << "foo islevi cagrildi\n";
	s.print();							
	std::cout << "foo islevi sone erdi\n";

}  // ÇOK ÇOK ÖNEMLİ.BURAYA ARGÜMANDAN KOPYALANAN s PARAMETRESİ BLOK BİTİMİNDE FREE EDİLDİ.


int main()
{
	Sentence s1{ "Sabah kalkip malum kisiyi izledik" };
	s1.print();
	auto len = s1.lenght();
	foo(s1);	// burada copy ctor çağrılıyor. argümandan parametreye.
	getchar();
	s1.print(); // ÇOK ÖNEMLİ. foo(s1); kodu copy ctor fonkunu çalıştırır. Bunu compiler yazdı ama burada şu var. kopyalanan nesne nin içindeki
}				// pointer bloktan çıkılınca free ediliyor.Aynı adres s1 de halen var.Pointer INVALID/DANGLING hale geldi.Kullanmak UNDEFINED BEHAVIOR.
				// BU yüzden kendi copy ctorumuzu yazacağız.Bunu anlatmak için concat fonksiyonu yazdı ve yazı sonuna bir yazı ekleyince ikside
				// etkileniyor mu buna baktı.Derleyicinin yazdığı ctor hem runtime hatasına sebep oldu hemde value semantics ortadan kalktı.
				// free edilen ptr tekrar free edilmeye çalışılmış bir de free edilen yazılmaya çalışıldı.2 adet UB.
				// NOT : CONCAT i geri sildi.Bu yüzden ben yazmadım. 3:00

ÇIKTI
-----
Edinilen bellek blogunun adresi = 01204EA8
(Sabah kalkip malum kisiyi izledik)
foo islevi cagrildi
(Sabah kalkip malum kisiyi izledik)
foo islevi sone erdi
01204EA8 adresindeki blok free ediliyor

(¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦)
01204EA8 adresindeki blok free ediliyor

====================================================================================================================


BU KODDA COPY CTORU KENDİMİZ YAZDIK. DANGLING PTR ENGELLENECEK ŞEKİLDE YAZDIK.
EKLEMELER

sentence.h
------------
class Sentence {
public:
	Sentence(const char *p);
	Sentence(const Sentence& other);
	~Sentence();
	void print()const;
	int lenght()const // // lenght i inline olarak yazıyoruz
	{
		return mlen;
	}
private:
	char* mp;
	size_t mlen;
};


======================================================================================

sentence.cpp
------------

Sentence::Sentence(const Sentence& other) : mlen{other.mlen}
{
	mp = reinterpret_cast<char*>(malloc((other.mlen + 1) * sizeof(char)));
	if (!mp)
	{
		std::cout << "bellek yetersiz\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Edinilen bellek blogu adresi = " << reinterpret_cast<void *>(mp) << "\n";
	strcpy(mp, other.mp);

}

ÇIKTI
-----
Edinilen bellek blogunun adresi = 011D4F48
(Sabah kalkip malum kisiyi izledik)
Edinilen bellek blogu adresi = 011DFCB8
foo islevi cagrildi
(Sabah kalkip malum kisiyi izledik)
foo islevi sone erdi
011DFCB8 adresindeki blok free ediliyor

(Sabah kalkip malum kisiyi izledik)
011D4F48 adresindeki blok free ediliyor
SORUN KALMADI ARTIK

==================================================================================================================================

İLERİDE KOPYALAMAYA KARŞI KAPALI SINIFLAR GÖRECEĞİZ

Std kütüphanenin belli sınıfları kopyalamaya kapalı durumda.

cout bir nesne. nesnenin türü osteam isimli sınıf.

using namespace std;
int main()
{
	ostream mycout(cout);
}

Burada hata alınıyor, kopyalamaya karşı kapalı.
Sınıfın Copy Ctoru delete edilmiş.


------------------------------------------------------------------------------------------------------------------

Örneği değiştiriyoruz.


int main()
{
	Sentence s1{ "C++ cok guzel bir dil" };
	s1.print();
	auto len = s1.lenght();
	std::cout << "len = " << len << "\n";

	if (len > 10)
	{
		Sentence s2{ "Python da guzel bir dil bence" };
		s2.print();
	}
	s1.print();
}
Böyle olsaydı hiç sıkıntım yoktu. Blokta Sentence türden nesne yarattı s2 adı.çıkarken destructor girdi devreye...

ÇIKTI
-----
Edinilen bellek blogunun adresi = 01044F48
(C++ cok guzel bir dil)
len = 21
01044F48 adresindeki blok free ediliyor

--------------------------------------------------------------------

AMA aşağıdaki gibi olunca.

int main()
{
	Sentence s1{ "C++ cok guzel bir dil" };
	s1.print();
	auto len = s1.lenght();
	std::cout << "len = " << len << "\n";

	if (len > 10)
	{
		Sentence s2{ "Python da guzel bir dil bence" };
		s2.print();
		s2 = s1;	//BURAYA DİKKAT. Yine Dangling Pointer. COPY ASSIGNMENT :D:D
		s2.print();
	}
	getchar();
	s1.print();
}

C++ ta iki sınıfın birbirine atanmasını sağlayan sınıfın özel bir fonksiyonu.
Myclass a,b;
a = b;   bunu yapmak için bir fonksiyon çağrılır. a İÇİN SPECIAL MEMBER FUNCTION ÇAĞRILIR.
operatör değilde function ismi sentaksı ilede çağrılır

Burada çağrılan fonksiyona COPY ASSIGNMENT FUNCTION denir.

DERLEYİCİNİN YAZDIĞI(DEFAULT ETTİĞİ) COPY ASSIGNMENT FUNCTION
  A - SINIFIN PUBLIC
  B - NONSTATIC
  C - INLINE FUNCTION  OLMAK ZORUNDA

Bazı fonksiyonlar operator keyword ile oluşturuluyor.
Bu bir CTOR değil. Special Member func ama Ctor değil.


class Myclass;
{
public:
	Myclass& operator=(const Myclass &other);
};

Biz normalde a = b yazdığımız zaman bu a.operator=(b) olmuş oluyor.
aklıma pythondaki __eq__ veya __repr__ gibi fonksiyonlar geldi. Mantık çok benziyor.


YANi
class Nec
{
	void func();
};

int main()
{
	Nec a,b;
	a = b;
	a.operator=(b);  yukarıdaki ile bunun arasında fark yok.
	geri dönüş değeri de *this. yani a nın kendisi.
	
	a.func();
	(a = b).func();
	a.operator=(b).func();    Hepsi aynı.
}

-------------------------------------------------------------------------------

YAPILAN ŞEY

class Myclass{
public:
	Myclass(const Myclass &other) : ax(other.ax), bx(other.bx),cx(other.cx)
	{  }

	Myclass& operator=(const Myclass &other)
	{
		ax = other.ax;
		bx = other.bx;
		cx = other.cx;
		// ...				Yapılan işler bunlar.
		return *this;
	}
private:
	A ax;
	B bx;
	C cx;
	// ..
};

-------------------------------------------------------------------------------

int main()
{
	Date mydate{ 1,2,1950 };
	Date xdate;

	mydate.print();
	xdate.print();

	xdate = mydate;
	xdate.print();

	ÇIKTI
	------------
	1 - 2 - 1950
	1 - 1 - 1998
	1 - 2 - 1950


	Burada işimizi gördü ama data memberlar eğer pointerlarsa yine DANGLING ptr olma durumu var.
	o zaman yine kendimiz yazacağız.

}












*/

#include <iostream>
#include "date.h"
#include "sentence.h"



int main()
{
	Date mydate{ 1,2,1950 };
	Date xdate;

	mydate.print();
	xdate.print();

	xdate = mydate;
	xdate.print();

}
