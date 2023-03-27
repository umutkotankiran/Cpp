/*
SORU: EKRANA NE YAZDIRIR?
		
#include <iostream>

class A {
public:
	A()
	{
		std::cout << "1";
	}

	A(const A&)
	{
		std::cout << "2";
	}

	~A()
	{
		std::cout << "3";
	}
};

class B
{
public:
	B(A)
	{
		std::cout << "4";
	}

	~B()
	{
		std::cout << "5";
	}
};

int main()
{
	B b(A());
	// 'B b(A (__cdecl *)(void))': //prototyped function not called (was a variable definition intended?)
}

CEVAP: EKRANA HİÇBİRŞEY YAZDIRMAZ.
Most Vexing Parse ile ilgili. Uniform initializer adı altında geçmişti bu konu.
Most vexing Parse a karşı önlem amaçlı uniform initialization kullanılıyor.
Most Vexing parse : Bir cpp cümlesi hem sınıf türden bir değişken tanımlama hemde 
fonksiyon bildirimi anlamına geliyorsa dilin kurallarına göre FONKSIYON BILDIRIMININ 
ÖNCELIĞI VAR.

Burada bir fonksiyon bildirimi var.Nedir bu fonksiyon bildirimi.
ismi b olan, geri dönüş değeri sınıf türden B olan, parametresi bir function pointer olan
bir fonksiyon.

void func(int[]) ; buradaki parametre pointer.dizi değil

Aynı şekilde
B b(A());  burada A() dilin kurallarına göre function pointer parametre.
		   Parametre değişkeni olmayan geri dönüş değeri türü A sınıfı olan
		   bir pointer adresini tutan pointer.
		   Derleyincre zaten gösteriyor. // 'B b(A (__cdecl *)(void))':
		   function pointer ifade görülür. A(*)(void) gibi birşey.

----------------------------------------------------------------------------

MOST VEXING PARSEDAN NASIL ÇIKARILIR?
Eski yöntem;
ifadeyi tekrar parantez içine alırız
B b((A()));

Diğer yöntem;
küme paramtezi kullanmak
B b(A{});
B b{A()};
B b{A{}}; Hİçbirinde most vexing parse yok. Hata yok yani bu örnekte.


===========================================================================================


TRAILING RETURN TYPE
GENERIC PROGRAMLAMADA GEÇIYOR

auto func()->int // buradaki int return değeri anlamında kullanılıyor.
{

}

auto main()-> int  böyle yazanlar var maini.
{
}

Bir yerde belki avantajı olur belki
Belki function return type func ptr olduğunda bir typedef kulanılmadığında faydalı olabilir.
biraz func ptr decleration olaylarına girildi.C den.
Biraz karmaşıkl geliyor programcılara bu tip bildirimler/taınmlamalar.
auto func() -> int(*)(int) belki böyle yazılırsa daha anlaşılır olabilir.burada faydalı olabilir

----------------------------------------------------------------------------------------------

BIRDE AUTO RETURN TYPE VAR. 
Not : Trailing return type ile auto return type aynı şey değil.
Compiler burada return değere bakarak türü anlıyor.

auto func(int x)
{
	return x * x;
}

Notlar
auto ve trailing daha çok templatelarla ilgili kullanılan araçlar.
Generic programlamaya daha girmedik.

Template olmayan functionlarda genel olarak hoca tavsiye etmiyor ama bazaı durumlar varki
func tanımı kaynak dosyada yazılınca return değeri türü zahmetli oluyor.
Bu tip yerlerde kulanılabilir.

ör:
std::vector<std::string>::iterator func(int x)
{
}

birde tuzak durum var yaz onu.Tür çıkarımı beklediğimiz gibi çıkmayabilir.
Ör: Proxy sınıflar kullanınca tür çıkarımında problem çıkabilir.
Mesela vector<bool> vec;    vec[0];  Mesela bu bool türünden değil. Böyle beklerken, çıkmayabilir
Gerekmedikçe kullanmayı uygun bulmuyor hoca.Bunlar Templateler ile ilgili kullanımda avantaj
sağlayabilir.

============================================================================================
============================================================================================
============================================================================================
============================================================================================
============================================================================================

NESTED TYPES / TYPE MEMBERS
---------------------------
Sınıfların memberları 3 temel kategoriye ayrılır.
Data Members
Member Functions
Type Members - Nested Type - Member Type

Bildirimi sınıfın içinde yapılan türlere o sınıfın memberı olan tür deniyor.
C++ ta std kütüphane olmak üzere çok sık kullanılıyor.

	Sınıfın içinde bildirimi yapılan türler,
a - Başka bir sınıf olabilir.
b - Enum type olabilir. enum Color {red,blue};
c - Bir tür eş ismi olabilir. typedef veya using olabilir.
	typedef int word;
	using word = int;
	Func ptr da daha kolay oluyor
	
	NOT: Using bildirimlerinin dile eklenmesinini gerçek nedeni, 
	bu şekilde yapılan bildirimerin	template hale getirilebilmesidir.
	Böyle template lere	Alias template deniyor.
		
----------------------------------------------------------------------------------------

1. İkinci classı namespace yerine class içinde bildirince fark oluyor mu? Evet

class Myclass{
	public:
	class Nested{
		
	};
};
		
Burada artık myclass türünü nitelememiz lazım.
int main()
{
	Nested nx; // Burası sentaks hatası.
	Myclass::Nested nx;	// Burası Geçerli.
}


2. Access control Burada sözkonusu tabiki.
class Myclass{
		
	class Nested{
		
	};
};

Myclass::Nested x: SENTAKS HATASI.Private eleman çünkü.Access controle takıldık.

========================================================================================
========================================================================================
========================================================================================


BAZI KARMAŞIK ISIM ARAMA KURALLARI VAR BURADA
---------------------------------------------

1 - Class definition için de isim ararsan kullandığın ismi kod alanın başından 
bildirime kadar olan kısma bakıyor.Bulamazsa namespace scopetan classa kadar bakıyor.

class Myclass{
	word wx;		hata.isim arama hatası.
	typedef int word;

};

-------------------------------------------

class Myclass{
	typedef int word;
	word wx; ARTIK HATA DEĞİL.
	
};

--------------------------------------------

struct Word{
};

class Myclass{
	
	Word wx;   // burası wordu yukarı doğru arar. struct olan Word türünden wx oldu. int değil.
	typedef int word; // burası yukarıda olsaydı eğer, word wx bildiriminde, word int olacaktı.

};


---------------------------------------------

struct Word{
};

class Myclass{

	typedef int word;
	::Word wx; // burada namespace scopetaki struct olan Word tür.

};

------------------------------------------------------------------------------
------------------------------------------------------------------------------

2 - İnline olarak tanımlanan functionlar buna kurala dahil değil.

class Myclass{
	void func()
	{
		Word w; //Burası geçerli. İnline funclar kurala dahil değil demiştik.
	}

	typedef int Word;
};

------------------------------------------------------------------------------

Daha güzel örnek

typedef long Word;

class Myclass{
	
	Word wx;	// buradaki Word, long 
	
	void func()
	{
		Word w; //Ama buradaki w ise int türden.
	}

	typedef int Word;
};

---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------

3 - Bir sınıfın bir başka sınıf türü elemanı olması, bu türden bir veri elemanına
sahip olduğu anlamına gelmiyor.

Yani A nın herhangibir data memberı yok.

class A{
	class Nested{
	
	};
};

----------------------------------------------------
Ama A nın nested türden bir memberıda olabilirdi.

class A{
	class Nested{

	};

	Nested nx; //burası artık veri elemanı.
};

---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------

4 - NESTED TYPE A SAHIP SINIF, BU TYPE IN PRIVATE BÖLÜMÜNE ERIŞEBILIR MI?

Enclosing class = Nestedin tanımına sahip olan sınıfa enclosing class deniyor.

class A{
	class Nested{
	private:
		void func();
	};

	void foo()
	{
		Nested nx;
		nx.func(); // BURASI SENTAKS HATASI.NESTED OLSA BİLE PRIVATE BÖLÜMÜ KORUMA ALTINDA
	}
};

----------------------------------------------------------------------------------------

İÇERIDEKI CLASS TAN ENCLOSING CLASS IN PRIVATE KISMINA ERIŞMEYE ÇALIŞACAĞIZ. 
BURADA ACCESS CONTROL UYGULANMIYOR.

class A{

	void foo();
	static void sf();
	static int sx();

	class Nested{
	private:
		void func()
		{
			A ax;
			
			ax.foo();
			sf();	
			sx = 5;
		}
	};

};
 
Enclosing type ın private memberlarına erişebliyorum ve burada acess
Control uygulanmıyor.Modern C++ öncesinde bu kodlar sentaks hatasıydı.

-----------------------------------------------------------------------------------

class A{

	class Nested{
	private:
		void func()
		{
			A ax;

			ax.foo(); // Memberlar aşağı alındı ve isim arama halen daha geçerli.
			sf();
			sx = 5;
		}
	};

	void foo();
	static void sf();
	static int sx();
};

-----------------------------------------------------------------------------------

class A{
	
	int mx;

	class Nested{
	private:
		void func()
		{
			auto n = sizeof(mx); // GEÇERLİ.sizeof unevaluated contex olduğu için geçerli.
		}							// mx normalde static olması lazımdı.sınıf nesnesine ihtiyaç vardı
	};
};

ÖZETLE:
NESTED CLASS, ENCLOSİNG CLASS IN PRİVATE BÖLÜMÜNE ERİŞEBİLİR.ORADAKİ İSİMLERİ KULLNABİLİR.
DİLİN DİĞER SENTAKS KURALLARINI EZMEDİĞİ SÜRECE.

-----------------------------------------------------------------------------------

 
class A{
	class Nested{
		
	};

public:
	static Nested foo();
};

int main()
{
	auto x = A::foo(); // GEÇERLİ.Nested private ama kullanmıyoruz. Sadece function return type 
						// olarak auto tarafından algılanıyor.İsmi kullanmadık.Kullansaydık bir access control uygulanacaktı.

	A::Nested y = A::foo(); // burası sentaks hatası mesela.
}						 

NOT: Erişim kontrölü uygulanması için ismin kullanılması gerekiyor.


===========================================================================================================
===========================================================================================================

NESTED CLASSLARDA FONKSİYON TANIMLARI 
-------------------------------------

INLINE YAPILABİLİR
------------------
class A{
	class Nested{
		void foo()
		{
		
		}
	};

public:
};


BİR CPP FİLEDA YAPILABİLİR
--------------------------
class A{
	class Nested{
		void foo();		
	};

public:
};


//.cpp
void A::Nested::foo()
{
	Nested nx; // sınıfın içinde direkt nested türünü kullanabilirim.
}

----------------------------------------------------------------------

class A{
	class Nested{
		void foo(Nested); //parametreye nested geldi
	};

public:
};

//.cpp
void A::Nested::foo(Nested x)
{
	
}

----------------------------------------------------------------------


class A{
	class Nested{
		Nested foo(Nested); //Return value değeride geldi şimdi
	};

public:
};

A::Nested A::Nested::foo(Nested)
{
	Nested nx; // sınıfın içinde direkt nested türünü kullanabilirim.
}

//.cpp
Nested A::Nested::foo(Nested x) // Bu durumda burası SENTAKS HATASI.Çünkü buradaki return olan Nested func içinde kullanılmadığı için
{								// standart isim arama kurallarına göre kullanılacak.

}

--------------------------------------------------------------------------------------------------------------------------------------

A::Nested A::Nested::foo(Nested x) // BURASI GEÇERLİ.
{

}
--------------------------------------------------------------------------------------------------------------------------------------

A::Nested A::Nested::foo(A::Nested x) // BURASI DA GEÇERLİ.PARAMETREDE DE :: KULLANILABİLİR.ZORUNLU DEĞİL. RETURN VALUE DA GEÇERLİ.
{

}

--------------------------------------------------------------------------------------------------------------------------------------

COPY CTOR İÇİN YAZALIM.


class A{
	class Nested{
		Nested& operator=(const Nested& other)
		{
		
		}
	};

public:
};

A::Nested& A::Nested::operator=(const Nested& other)
{
//..
}

--------------------------------------------------------------------------------------------------------------------------------------

ENUM TYPE

class A{
public:
	enum{size = 100};
};

int main()
{
	int x = A::size;// GEÇERLİ
}

--------------------------------------------------------------------------------------------------------------------------------------

INCOMPLETE TYPE

class Myclass{
	class Nested;  sınıfın dışında bildirmekle sınıfın içinde kullanmak aynı anlama gelmiyor.Erişimde faklılık oluyor.
	Nested *mp;
};


======================================================================================================================

PIMP IDIOM
Handle body idiom veya cheshire cat idiyom opaq pointer idiom diye söyleyenler var

Adı pointer implementationdan geliyor.
Bir geleneksel birde smart pointer idiyomu var.
Sınıfın Private bölümünü gizliyor. NEden gizlemek isteyelim?

1. Neden, Gereksiz başlık dosyaları include edilmesini engellemek.

#include "Mint.h"
#include "Date.h"
#include "Counter.h"

class nec
{
private:
	Mint mx;	// Eğer bu şekilde nesne oluşturacaksak bu sınıfı incomplete type olarak tanımlayamayız.
	Date dx;	// complete type olmalı. Pointer olsalardı, incomplete decleration ile çalışır.
	Counter cx; // static olsalardı, bu bir bildirim olacağından incomplete type olabilirdi.
};

--------------------------------
STATIC OLSUN

class Mint;
class Date;
class Counter;

class nec
{
private:
	static Mint mx;	    //	Mint &mx; 
	static Date dx;		//	Date &dx;
	static Counter cx; 	//	Counter &cx; bunlarda olabilirdi incomplete type ile.
};

Yani static dğilse pointer veya referans değilse, tanımları tam olarak/Complete type olarak görmeli.
Yoksa çok maliyet artırır

-----------------------------------------------------------------------

Pimple a geri dönelim
Hoca pimple ı her sınıf için önermiyor.


//.h
class Nec{
	Nec();
	~Nec();
	void func();
	void foo();
private:
	struct Pimpl;
	Pimpl *mp;
};

//.cpp
#include "neco.h"
#include "mint.h"
#include "date.h"
#include "counter.h"	

struct Nec::Pimple{
	Mint mx;
	Date dx;
	Counter cx;
};

void Nec::Nec() : mp {new Pimpl}
{
	//..
}

void Nec::~Nec() : mp {new Pimpl}
{
	//..
}


void Nec::func()
{
	//... artık neler yapıacaksa
	mp->dx; //uyduruorum buralarda
	++mp->mx;
		
}

Dinamik ömürlü nesne yaratıldı. fiziksel olarakta struct nec içerisindeki veri elemanları ayrı yerde.
sizeof a girmiyor. destructor falanda buna göre tanımlanmalı. pimpl deletede edilmeli

SONUÇ : NESTED TYPE İLE İLİŞKİSİNİ GÖRMEK. 
	BUNUN DAHA MODERN HALİNİ GÖRECEĞİZ. ESKİ OLANDI BU. GÜNÜMÜZDE TERCİH EDİLEN
	SMART POINTER OLACAK.

-------------------------------------------------------------------------------

NESTED TYPELARIN KARŞIMIZA ÇIKTIĞI BİR İKİ YER

vector<int> ivec;
vector<int>::iterator iter = ivec.begin();  // iterator public bir nested type.

auto iter = ivec.begin();   // auto ile de kullanılır.

---------------------

string str{"ali"};
string::size_type len = str.lenght();

auto len = str.lenght();


MOLA

=========================================================================================================================
=========================================================================================================================
=========================================================================================================================
=========================================================================================================================


COMPOSITION
-----------

Nesne yönelimli programlamada, problem domainindeki varlıkları temsil eden sınıflar ile temsil etmeye deniyor.
Prosedürel programlama paradigmasında(C) ayrıştırma functionlara yönelik, ama nesne yönelimlide arıştırma classlara/sınıflara yönelik

Bazı terimler var. Bunlar sınıflar arasındaki ilişkileri betimliyor.

UML Konusunu öğrenmekte fayda var.Modelleme.
Nesne yönelimli modellemeye bak. Modelleme dili ? UML?
Bunlar diagramatic diller, programlama dilleri değil.
Diagramlar var, sınıf diagramları, akış diagramları.
Aşağıdaki ilişki türleride UML de karşımıza çıkacak.

Dependancy

Association : Sistemdeki 2 sınıf birbiriyle işbirliği halinde kullanılıyorsa bu sınıflar arasında association vardır.
	Aggregation : Eğer bu ilişki içindeki sınıflardan biri, diğerinin sahibi olarak onu kulanıyorsa, buna aggregation deniyor. Her aggregation bir association
					Bir futbolcu bugün fenerde yarın Gs de. gibi.					
		composition : Yine bir nesne diğerinini sahibi fakat sahip olan ile olunan nesne arasında ömürsel birliktelik var.Sahip hayata gelince, olunan da gelir.
					  Sahip ölürse, sahip olunanda ölüyor. Araba perte çıktı motoru da kullanılamaz kendide ise arada composition var.
					  ama eğer motorunu başka yerde kullanabileceksek aggregation var.


Containment : bir nesne diğerini eleman olarak alması durumuna deniyor.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

Composition bir interface edinme ilişkisi değil. Bir sınıf başka sınıf türden bir ver ielemanına  sahip olunca
o veri elemanının interface ini kendi interface ine katmıyor.

class A{
private:
	void func();
	void foo();
	void f();
};

class B{
private:
	A ma;
};

int main()
{
	B bx;

	bx.func(); //BURASI HATA.İNTERFACE DEVRALINMAZ. KALITIMDA INTERFACE DEVRALINIR.
}				en fazla B ye func yazıp. bu func ın diğer class nesnesi ile func çağırması olabilir.


Aşağıdaki gibi.
class B{
private:
	A ma;
public:
	void func()
	{
		ma.func
	}
};

-----------------------------------------------

ERİŞİM KONTROLÜ

B sınıfı A sınıfı türden bir elemana sahipse, B nin üye functionları içinde elemanı olan A nın private bölümüne erişebilir miyiz?

class A{
private:
	void func();
	void foo();
	void f();
};

class B{
private:
	A ma;
public:
	void g()
	{
		ma.func(); //Burası hata. Private bölümüne erişim hakkı verilmedi
		ma.ival; // aynı şekilde hata.
	}
};

ELEMANIN PRİVATE BÖLÜMÜ KAPATILMIŞ DURUMDA.FRİENDLİK VEREBİLİR.

--------------------------------------------------------------------------------------------------------------------

FRİENDLİK DURUMU

class A{
	void func();
	void foo();
	void f();
	friend class B;	
};

class B{
private:
	A ma;
public:
	void g()
	{
		ma.func(); // HATA YOK
		ma.ival; // Legal. hata yok.
	}
};

--------------------------------------------------------------------------------------------------------------------

class Member{
public:
	Member()
	{
		std::cout << "Member default ctor\n";
	}
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner
{

private:
	Member mx;
}


int main()
{
	Owner ox;
}

Burada owner sınıfının yazdığı default constructor elemanlar default init ettiğine göre, member türünden mx in default init edilmesi,
default ctorunun çağrılması demek. Derleyicinin yazdığı destructor ise sınıf türden hayata gelenlerin nesnelerin hayata sırayla veda etmesi demek.
Mesela yukarıda
member ctor
destructor   yazdı 

-----------------------------------------------------------------------------------------------

Sınıfın birden fazla elemanı olsaydı

class Ownber{
	A ax;
	B bx;
	C cx;   //hayata gelme sırası buradaki bildirimdeki sıra

};

--------------------------------------------------------------------------------------

DEFAULT CTOR PROGRAMCI TARAFINDAN YAZILMIŞSA

member class tanımlı say

class Owner
{
public:
	Owner()
	{
		std::cout << "Owner Ctor\n";
	}
private:
	Member mx;
}


int main()
{
	Owner ox;
}

ÇIKTI
-----
Member default ctor
Owner Ctor
member Destructor

---------------------------------------------------------------------------

DESTRUCTOR YAZILIRSA

member class tanımlı say

class Owner
{
public:
	Owner()
	{
		std::cout << "Owner Ctor\n";
	}
	~Owner()
	{
		std::cout << "Owner Destructor\n";
	}
private:
	Member mx;
}


int main()
{
	Owner ox;
}

Burada önce elemanlar mı destroy ediliyor yoksa önce destructor anabloğundaki kod çalışıyorda, bu kodun çalışmasından sonramı
elemanlar destroy ediliyor. 2. olan

Yani destructor anabloğundaki kodlar çağrılıyor. sonrasında hayata gelmesiyle ters sırada elemanlarında destructoru çağrılıyor.

ÇIKTI
-----
Member default ctor
Owner Ctor
Owner Destructor
Member Destructor


--------------------------------------------------------------------------------------------------------------------------------

Eğer derleyicinin default ettiği special member func bir sentaks hatası olursa compiler o special member func ı delete ediyordu.

class Member{
Member()  // Private kısma alındı
{
	std::cout << "Member default ctor\n";
}
public:	
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner
{
public:
		// compiler funcları yazacak ama elemanlar default init edilecekler. ama default ctor yazılınca hata alınır çünkü 
		// memberda defaultctor private olmuş. Bu durumda ctoru delete eder.
private:
	Member mx;
};

int main()
{
	Owner ox; //Sentaks hatasının sebebi delete edilmiş ctora çağrı.
}

--------------------------------------------------------------------------------

class Member{
public:
	Member(int)  
	{
		std::cout << "Member Ctor\n";
	}
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner{
public:
private:
	Member mx;
};

int main()
{
	Owner ox; //Sentaks hatası yine.Yİne member default ctor çağrılamayacak.bu sebeple Owner default Ctor delete edilecek.
}

--------------------------------------------------------------------------------------------------

class Member{
public:
	Member() = delete;
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

Yine aynı kodlar ve aynı durum. Ownerında default ctoru delete edilecek.
Çağrılınca Sentaks hatası.

Memberın Default ctoru yoksa, erişim problemi varsa, delete edilmişse, Ownerında default ctoru burada delete edilecek.

--------------------------------------------------------------------------------------------------


class Member{
public:
	Member() = delete;
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner
{
public:
	Owner() = default;	
private:
	Member mx;
};


int main()
{
	Owner ox; //BUADA ELLE DEFAULT ETSEK BİLE COMPİLER BUNU DELETE EDER.
}

--------------------------------------------------------------------------------

class Member{
public:
	Member()
	{
		std::cout << "Member Default Constructor\n";
	}
	Member(int x) 
	{
		std::cout << "Member(int x) x = "<< x << "\n";
	}
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner{
public:
	Owner() // burada Member için default ctor çağrılacak.
	{
		std::cout << "Owner Default Ctor\n";
	}
private:
	Member mx;
};

int main()
{
	Owner ox; //GEÇERLİ
}

ÇIKTI
-----
Member Default Constructor
Owner Default Ctor
Member Destructor

----------------------------------------------------------------------------------

diğer kodları yazmadım. Eğer parametreli ctor çağrılsın istersek

class Owner{
public:
	Owner() : mx(10)  // int parametreli ctor veya mx{10}
	{
		std::cout << "Owner Default Ctor\n";
	}
private:
	Member mx;
};

------------------------------------------------------------------------------------------------

Diğer yöntemde

class Owner{
public:
	Owner()  
	{
		std::cout << "Owner Default Ctor\n";
	}
private:
	Member mx{20}; //Artık cotor initializer liste bunu ekleyecek. Yİne int parametreli ctor çağrılır.
};					//Ctor init listte mx ile ilgili birşey yazmazsak, bu yazılmış kabul ediliyor ctor init listte.


------------------------------------------------------------------------------------------------

Böylede olabilir.

class Owner{
public:
	Owner(int val) : mx{val}  // ownerdan gelen argüman mx e verildi.
	{
		
	}
private:
	Member mx;
};


-------------------------------------------------------------------------------------------------

class Owner{
public:
	Owner() : ax(12) , bx(20)   // eğer cx unutulursa default ctor çağrılır cx için. Default mmeber init ten ctor init liste yazılır
	{
		
	}
private:
	A ax;
	B bx;
	C cx;
};

Bİrth Date li örneğini yazmadım. O da aynı mantıkta.

---------------------------------------------------------------------------------------------------

class Person{
public:
	Person(const char *pname)
	{
		mname = pname;
	}
private:
	std::string mname;
};

Yukarıdaki kod eleştirilebilir. initialization is not an assignment.
assignment yapılmış burada. halbuki ctoruna bu işi yaptırabilirdik.
Maliyet artıyor.2 ayrı func çağrısı var
mname için default init ediliyor yani bunun için ctor çağrılacak
ve mname=pname deki atama için ilgili func çağrılması.

Halbuki ctor init liste konabilirdi.Çok ciddi verim farkı var.


OLMASI GEREKEN
class Person{
public:
	Person(const char *pname) : mname(pname)
	{
	}
private:
	std::string mname;
};

-----------------------------------------------------------------------------------------------

İleride görülecek olan zor bir soru?
Yazım nasıl olmalı?

class Person{
public:
	Person(const std::string &name) : mname(name)
	{
	}
private:
	std::string mname;
};

Bunun dezavantajı : Copy elisiondan istifade etme şansım yok.
Taşıma semantiğini biraz daha detaylı incelediğimizde çok daha farklı seçeekler çıkacak karşımıza.


Diğer alternatif
class Person{
public:
	Person(const std::string name) : mname(move(name)) // & yok.
	{
	}
private:
	std::string mname;
};

Avantajı copy ellisiondan faydalanmak.

Birde small string optimization var. Sınıf nesnesinin içinde küçük yazı varsa onları kendi içindeki dizide tutuyor.


BUNLAR STRİNG SINIFINDA GÖRÜLECEK.
BIR IKI TANE DAHA CONSTLU FALAN ÖRNEK VERDI AMA BUNLAR STRING SINIFINDA IŞLENECEK.

-------------------------------------------------------------------------------------------------------------------------------

ŞİMDİ COPY CTORA BAKALIM
DEFAULT CTOR VE PARAMETRELİ CTORA BAKILDI
-----------------------------------------
3 TANE İHTİMAL VAR.
1 - DERLEYİCİ TARAFINDAN DEFAULT EDİLMESİ
2 - PROGRAMCI TARAFINDAN YAZILMASI
3 - DELETE EDİLMESİ.


class Owner{
public:
	Owner(const Owner &other) : a(other.a) , b(other.b), c(other.c)  // HER BIR ELEMAN IÇINDE AYRI AYRI COPY CTOR ÇAĞRILIYOR
	{ 
	
	}
private:
	A a;
	B b;
	C c;

};

-------------------------------------------------------------------------------

class Member{
public:
	Member() = default;
	Member(const Member&)
	{
		std::cout << "Member copy ctor\n";
	}
};

class Owner{
private:
	Member m;
};

int main()
{
	Owner a;

	Owner b = a;
}

Çıktı
Member copy ctor 

b nin içindeki member için çağrıldı bu.


-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------

Bu örnek güzel

class Member{
public:
	Member()
	{
		std::cout << "Default ctor\n";
	}
	Member(const Member&)
	{
		std::cout << "Member copy ctor\n";
	}
};

class Owner{
public:
	Owner() = default;
	Owner(const Owner& other)
	{
		std::cout << "Owner copy ctor\n";
	}
private:
	Member m;
};

int main()
{
	Owner a;

	Owner b = a;
}

Buradaki programcı hatası memberdaki Ownerdaki copy ctorun elemanları kopyalamaması.
default init, default ctor çağırır(Member m;). default Ctoru da memberda programcı eksik,
kopyalama işlemi yapmadan yazmış.

SONUÇ: EĞER BIR SINIF IÇIN COPY CTORU KENDIMIZ YAZIYORSAK, ELEMANLAR BAŞKA SINIF TÜRDENSE,
ELEMANLARI O SINIFIN COPY CTORU ILE HAYATA GELMESINI SAĞLAMAK IÇIN CTOR INIT LISTE BUNLARI YAZMALIYIZ.
EĞER YAZMASAK ELEMAN HAYATA DEFAULT CTOR OLARAK GELECEK.


DÜZELTMEK IÇIN !!
Owner(const Owner& other) : m(other.m)  // sondaki eklendi.Burası ctor init list. init işlemi oluyor burada. yani kopyalama.
	{
		std::cout << "Owner copy ctor\n";
	}


MOLA
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================

COPY ASSIGNMENT İÇİN BAKALIM
----------------------------

class Owner{
public:
	Owner& operator=(const Owner &other) // DERLEYICININ YAZDIĞI SELF ASSIGNMENT KONTROLÜ YAPMAZ.
	{
		a = other.a;
		b = other.b;
		c = other.c; // elemanlar sınıf türdense yine kendi içinde de copy assignment çağıracak.

		return *this;
	}
private:
	A a;
	B b;
	C c;

};

-------------------------------------------------------------------------------------------------------

class Member{
public:
	Member& operator=(const Member&)
	{
		///
		std::cout << "Member copy assignment\n";
		return *this;
	}
};

class owner{	
	
private:
	Member mx;
};

int main()
{
	Owner a,b;
	
	a = b;	// burada derleyicinin yazdığında a.mx ine b nini mx ini atayacak.
}

-----------------------------------------------------------------------------------------

Ama copy asignment ı biz yazarsak elemanların birbirine atanmasından biz sorumluyuz.

class Member{
public:
	Member& operator=(const Member&)
	{
		///
		std::cout << "Member copy assignment\n";
		return *this;
	}
};

class owner{
public:
	Owner& operator=(const Owner&other)
	{
		std::cout << "Owner copy assigment\n";
		mx = other.mx; // bunu yazmadanda yaptı hoca.birşey çıkmadı. hiçbir iş yapmadı. 
		return *this;
	}
private:
	Member mx;
};

int main()
{
	Owner a,b;

	a = b;	// burada derleyicinin yazdığında a.mx ine b nini mx ini atayacak.
}


-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------

MOVE CONSTRUCTOR
----------------
Derleyici aşağıdaki gibi yazar kodunu.

class Owner{
public:
	Owner(Owner &&other) : a(std::move(other.a)) , b(std::move(other.b)), c(std::move(other.c))
	{

	}
private:
	A a;
	B b;
	C c;

};


Derleyicinini yazdığı fonksiyonlar zaten bizim istediğimiz biçimde. Elemanlarda diğer sınıflar türdense zaten % 98-99 
bizim istediğimiz gibi.Yazacaksan ciddi nedenimiz olmalı.

----------------------------------------------------------

ÖZEL DURUM

class Member{
public:
	Member() = default;
	Member(const member&);
private:
	Member(Member&&);
};

class Owner{
public:

	Member m;
};

int main()
{
	Owner ox;
	Owner oy(move(ox));
}

BİR SENTAKS HATASI YOK.OWNER SINIFI İÇİN DERLEYİCİ MVOE CTOR YAZACAK. ELEMANLAR SINIF TÜRDEN OLUNCA DERLEYİCİNİN YAZDIĞI MOVE CTORDA
CTOR INIT LISTTE YİNE MOVE KULLANILIYOR. AMA MEMBER SINIFININ MOVE CTORU PRIVATE. BU DURUMDA OWNER SINIFININ MOVE CTORU DELETE EDİLECEK.
DELETE EDİLEN MOVE CTOR NOT DECLARED KABUL EDİLİYORDU. DAHA ÖNCE DEĞİNMİŞTİ. BU DURUMDA DA MOVE DEĞİL COPY CTOR ÇAĞRILIR.


--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------

MOVE ASSIGNMENT

class Owner{
public:
	Owner& operator=(Owner &&other) 
	{
		a = std::move(other.a);
		b = std::move(other.b);
		c = std::move(other.c);

		return *this;
	}
private:
	A a;
	B b;
	C c;
};

İLERİDE KAYNAĞI ÇALINMIŞ OBJELERİDE İNCELEYECEĞİZ.
Bunlara moved-from object deniyor.

================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================


NAMESPACES / İSİMALANLARI
-------------------------
İsimalanı, global isimalanında oluşturabileceğimiz ve isimlerin birbirleriyle karışmasını engellemeye yönelik ve bu isimleri
birarada tutan bir paket/container gibi bir yapı.

İsimalanında bildirilen isimler özel bir scope ait.Bu namespace scope.
İsimlerin birbirleriyle çakışmasını engellemeye yönelik bir mekanizma bu.

C de olsaydı, include edilen kütüphaneden gelen isimler global isimalanına enjekte edilecekti ve bunların çakışma riski var.
Bir global alan var ve herkes oraya yazıyordu.

C++ ta ise bu isimleri doğrudan enjekte etmek yerine biz bu namespacelere boşaltıyoruz. isimler aynı olsa namespace ler farklı olsa bile
isimler çakışmıyor.

Pc lerdeki farklı dizinlerde varolan aynı isimli dosyalar gibi düşün.

c:\cdr\ali.txt
c:\cdr\folder\ali.txt   dosyalar aynı isimli ama çakışma yok.Aynı isimalanları/namespaces gibi.

-----------------------------------------------------------------------------------------------------------------------

Artık file scope diye birşey yok.
Global namespace var. tüm namespacelerde bunun içerisinde.
Nested namespacelerde olabilir. Erişim ise scope resolution :: operatörleri ile yapılıyor. 

Tüm standart kütüphaneden egelen isimler ismi std olan bir namespace içinde.
Genellikle namespace kullanmayacağız ama kullandığımız kütüphaneler namespace içinde olduğundan bilmemeiz gerekiyor.
Bazende bizim yazmamız gerekecek.

SENTAKS
-------
namespace Nec{

}

Sonda ; yok. Koyarsakta hata olmaz çünkü null statement olmuş olur.Ama standart sentaksta yok.

Unnamed Namespace
-----------------
namespace {

}

İsimsiz isimalanı.Sonra görülecek bu. Özel bir araç bu.

-----------------------------------------------------------------

Namespace içinde func tanımı, değişken tanımı class tanımı... herşey mümkün.

-----------------------------------------------------------------------------

namespace nec{
	int a = 10;
	double a = 20.2;   SENTAKS HATASI.a ismi aynı scopeta iki defa kullanılmış.Farklı namespacelerde hata olmazdı.
}

----------------------------------------------------------------------------------------------------------------

namespace nec{
	int a = 10;
}

namespace ali{
	double a = 20.2;   LEGAL. GEÇERLİ ARTIK.
}

-------------------------------------------------------------------------------------------------------------

Farklı scopelar func overloading olmaz

namespace Ali{
	void func(int);
}

namespace Nec{
	void func(double); Overloading yok.
}   

------------------------------------------------------------------------------------------------------------

Burası ise func overloading 

namespace Nec{
	void func(int);
}

namespace Nec{
	void func(double); Func OVerloading burası

------------------------------------------------------------------------------------------------------------

İsim alanındaki ismi bulmak için scope resolution operatörü kullanılır.

int g = 20;

namespace Nec{
	int g =10;
}

int main()
{
	int g = 30;

	g;        değeri 30 olan ilk bulunan g bu.
	nec::g;   Bu şekilde nec namespace e erişilir.
	::g;      Buda global namespacede arar.
}


----------------------------------------------------

NOT: NAMESPACE LERDE PUBLIV PRIVATE PROTECTED YOK.

----------------------------------------------------

Nested namespacelerde var.

namespace Nec{
	namespace Ali{
			namespace Veli{
				int x = 10;
			}
	}

}

int main()
{
	Nec::Ali::Veli::x = 23;  // bu şekilde erişilir. Çok yaygın std library kullanıyor.
}

-------------------------------------------------------------------------------------

Nestedlar baya kullanılıyor std library de

std::regex_constant
std::chrono
std::string_literals
std::literals::string_literals

-----------------------------------------------------------------------------------------

string std; neden sentaks hatası ? Çünkü string sınıfı std namespace içinde bildirilmiş.
std::string std; olmalıydı.

-----------------------------------------------------------------------------------------

Namespacelerde kümülatif etki var

namespace ali{
	int x = 10;
}

namespace ali{
	int y = 21;
}

int main()
{
	ali::x = 25;
	ali::y = 35;
}

Derleyici bir namespaceden sonra tekrar aynı tanımı görürse bunları otomatik birleştirir.

-----------------------------
namespace ali{
	int x = 10;
}

namespace ali{
	int x = 21;  SENTAKA HSTASI. Aynı namespacede aynı tanım 2 defa yapılmış.
}

Neden namespaceler birden fazla kez oluşturulabilip birleştiriliyorlar?
Birsürü library var. Farklı librarylerin hepsini kendi başlık dosyası içinde aynı namespacelere koyuyor bunları.

std::string x; string header file
std::vector<int>vec; vector header filedan
... birsürü library var. hepsinin std içinde olması için kümülatif olarak toplanması gerekiyor.

namespace std{
	class string ...
}

namespace std{
	class vector ...
}

Hepsini std namespace ine koyuyor dil standartları.

---------------------------------------------

//.h
namespace prog{
	class Nec{
		void func();
		void foo();
	};
}

#include "///.h"

1. ihtimal
//cpp filedan aşağıdaki gibi tanımlıyoruz.
void Nec::prog:Nec()
{
	//
}

2. ihtimal ise cp file da da bunu prog namespace içinde tanımlayabiliriz.
Bildirim ile tanım aynı namespace içinde oluyor artık bu durumda.
namespace prog{
	void Nec::func()
	{
	///
	}
}

başka ihtimallerde var. Birsonraki derste görülecek.

*/

#include <iostream>

class Member {
public:
	Member()
	{
		std::cout << "Member Default Constructor\n";
	}
	Member(int x)
	{
		std::cout << "Member(int x) x = " << x << "\n";
	}
	~Member()
	{
		std::cout << "Member Destructor\n";
	}
};

class Owner {
public:
	Owner() // burada Member için default ctor çağrılacak.
	{
		std::cout << "Owner Default Ctor\n";
	}
private:
	Member mx;
};

int main()
{
	Owner ox; //Sentaks hatası yine.Yİne member default ctor çağrılamayacak.bu sebeple Owner default Ctor delete edilecek.
}
