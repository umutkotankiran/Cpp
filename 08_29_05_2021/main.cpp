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

#ifndef DATE_H
#define DATE_H


class Date {
public:
	Date(int, int, int);
	void set(int d, int m, int y);
	void print()const;
private:
	int md, mm, my;
};


#endif
/*

CONSTRUCTOR VE DESTRUCTOR DAN DEVAM
KISACA TEKRAR.
SPECIAL MEMBER FUNCTIONLAR NEDİR ? ÖZET
KAÇ TANEDİR ? 6 TANE
HIZLICA CONSTRUCTOR TEKRARI.
MADDELERİ VARDI KISACA TEKRAR.

--------------------------------------------------------------------

CONSTRUCTOR NEDEN VAR ?
BİR SINIF NESNESİ HAYATA GELDİĞİNDE ONUN ELEMANLARIDA HAYATA GELİYOR.
CONSTRUCTOR IN EN ÖNEMLİ ÖZELLİKLERİNDEN BİRİ,
SINIF NESNESİ ELEMANLARINA İLK DEĞER VERİYOR.
CONSTRUCTOR BİR SINIFI KULLANILABİLİR HALE GETİRİYOR DENEBİLİR.

DESTUCTOR İSE
SINIFIN HAYATI SONA ERDİĞİNDE YAPILMASI GEREKEN İŞLER VAR.
CONSTUCTOR BİR KAYNAK KULLANIYOR.DESTRUCTOR İSE KAYNAĞI GERİ VERİYOR.
İHMAL EDİLEMEZ OLUYOR ARTIK.

CONSTRUCTOR KURALLARI
---------------------

1 - CONSTRUCTOR İSMİ SINIF İSMİYLE AYNI OLMALIDIR.
2 - GLOBAL FONKSİYON OLAMAZ.
3 - SINIFIN STATİC ÜYE FONKSİYONU OLAMAZ(non-static)
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.

ÖR:
class Myclass{
public:
	Myclass();	İSMİ SINIF İSMİYLE AYNI.
};				BAŞINA VOİD-STATIC-CONST YAZARSAK SENTAKS HATASI

5 - CONST ÜYE FONKSIYON OLAMAZ.
6 - SINIFIN PUBLIC, PRIVATE, PROTECTED FONKSIYONLARI OLABILIR.
	PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.
7 - CONSTRUCTOR OVERLOAD EDILEBILIYOR

class Myclass{
public:
	Myclass();
	Myclass(int);
	Myclass(int,double);
};

8 - BIR SINIFIN
	A - PARAMETRE DEĞIŞKENI OLMAYAN
	B - TÜM PARAMETRELERI DEFAULT ARGÜMAN ALAN
		CONSTRUCTORLARA DEFAULT CONSTRUCTOR DENIR.

	class Myclass{
	public:
		Myclass();	Bu Default Constructor
	};

9 - CONSTRUCTOR İSMİ İLE ÇAĞRILAMAZ. YANİ . -> OPERATÖRLERİYLE ÇAĞRILAMAZ.


DESTRUCTOR KURALLARI
--------------------

1 - İSMİ SINIF ~İSMİYLE AYNI OLAN FONKSİYONLAR
	~Myclass();
2 - GLOBAL FONKSİYON OLAMAZ.
3 - SINIFIN STATIC ÜYE FONKSİYONU OLAMAZ.
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.
5 - CONST ÜYE FONKSIYON OLAMAZ.
6 - SINIFIN PUBLIC, PRIVATE,PROTECTED FONKSIYONLARI OLABILIR.
	PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.
7 - DESTRUCTOR OVERLOAD EDILEMEZ. !!!!!!  FARK BURADA
	PARAMETRESI OLMAYAN BIR FONKSIYON OLMAZ ZORUNDA.
8 - DESTRUCTOR İSMİ İLE ÇAĞRILABİLİR.ÇOK ÖZEL BİR DURUMDA YAPILACAK BU.
	ASLA BİR DESTRUCTORU İSİMLE ÇAĞIRMAYIN.



------------------------------------------------------------
RAII İDİYOMU DENEN BİR İDİYOM VAR.BU BİR ACRONIM.
RESOURCE ACQUISITION IS INITIALIZATION.
BU KAYNAK EDİNİMİ İLK DEĞER VERME YOLUYLA OLUR ANLAMINDA.
------------------------------------------------------------

File diye sınıf olsun bir dosya açıyor.Destructoru ise dosya kapatıyor
Database - constuctoru db bağlantısı kurup, destructoru kapatıyor.
DynamicArray - dizi allocate edip, destructoru diziyi sisteme geri veriyor.

Class Date üzerinden örnek verildi.

------------------------------------------------------------------ -

CONSTRUCTOR INITIALIZER LIST
Diğer tabir ise
MEMBER INITIALIZER LIST(MIL)

Bir sınıf var.Bu ise standart kütüphanedeli sınıflardan birinin ismi.Karıştırma.
std::initializer_list(since C++11)

------------------------------------------------------------------
------------------------------------------------------------------

CONSTRUCTOR TANIMI NASIL YAPILIR ?

//.h
class Myclass {
public:
	Myclass();
	void print()const;
private:
	int m_a, m_b;
};

//myclass.cpp
Myclass::Myclass() : m_a(0), m_b(0) // burada m_a ve m_b  = 0 olacak
{ 									// m_a(5), m_b(10)  deseydik bu 5 ve 10 olacaktı.

	std::cout << "Myclass default ctor\n";
	//ctor = constuctor	
}

void Myclass::print()const
{
	std::cout << "m_a = " << m_a << "     mb = " << m_b << "\n";
}

int main()
{
	Myclass x; // constructor devreye gireceği için içindeki yazı yazdırılır.
	x.print();
}

------------------------------------------------------------------------ -

C++ 11 E KADAR INIT EDERKEN PARANTEZ DEĞER VERIRKEN ZORUNLUYDU.
C++ 11 DEN SONRA ARTIK KÜME PARANTEZI KULLANILABILIR. {}

Myclass::Myclass() : m_a{ 0 }, m_b{ 0 }
{
	std::cout << "Myclass default ctor\n";
	//ctor = constuctor	
}

------------------------------------------------------------------------ -
Not: Uniform init kullanılırken veri kaybı olursa sentaks hatası veriyor.
Narrowing conversionu engelliyor.
------------------------------------------------------------------------ -

Burada bir veri kaybı olduğu için SENTAKS HATASI. Burası önemli.

Myclass::Myclass() : m_a{ 2.3 }, m_b{ 5.5 } // HATIRLATMA : Burası Constructor Initializer List tir. Veya Member Initializer list. MIL
{
	std::cout << "Myclass default ctor\n";
	//ctor = constuctor
}

Hoca Küme parantezini kullanıyor genelde.

------------------------------------------------------------------------------

Elemanların hepsine değer vermek zorunda değiliz.

Myclass::Myclass() : m_a{ 0 }
{
}	Böylede olabilir.

--------------------------------------------------------------------------
--------------------------------------------------------------------------

KÖTÜ KOD !!!!!!!!

Myclass::Myclass()
{
	m_a = 10;
	m_b = 20;
}

HATA YOK AMA AYNI ŞEY DEĞIL.
BURADA ATAMA VAR.
DIĞERINDE INITIALIZATION VARDI.

Burası Çok geniş bir konu
Fakrlılıklar
primitive türden elemanlarda çok fark etmiyor.

Önemi nerde başlıyor.
Bazı varlıkların init. edilmesi zorunlu.
Constuctor init list ile ilk değer verilmezse, derleyici default init olacak şekilde kod üretiyor.
Burada değerler garbage değerler ile hayata gelir. Bu primitive türlerden olduğunda böyle.

ÖR:
Myclass::Myclass()
{

}

int main()
{
	Myclass x;
	x.print();  // Yukarıdaki durumda garbage value lar yazar.
}

------------------------------------------------------------------------

Value init edilseydi.
Myclass x{};
Yine çöp değerer ile başlayacaktı.

Global nesneler olsaydı 0 ile başlayacaklardı.

------------------------------------------------------------------------

Value init edilseydi Myclass x{};
ve Constructor Compiler Tarafından Yazılsaydı
o zaman primitive türlerin değerleri 0 olacaktı.

------------------------------------------------------------------------

SINIFIN VERI ELEMANI REFERANS ISE DEFAULT INIT EDILEMEZ.

class Myclass {
public:
	Myclass();
	void print()const;
private:
	int& mr;
};

Myclass::Myclass()
{
	// SENTAKS HATASI . REFERANSLAR DEFAULT INIT OLMAZ.
}	// CTOR INIT LİST OLUŞTURMAMIZ GEREKİYOR.

int main()
{

}


------------------------------------------------------------------------

CONST DEĞIŞKENLERDE DE AYNI ŞEKILDE C++ TA HATA. ÇÜNKÜ CONST ILE NITELENEN ISIMLER INITIALIZE EDILMELI.

class Myclass {
public:
	Myclass();
	void print()const;
private:
	const int mx;

};

Myclass::Myclass()
{
				// YİNE SENTAKS HATASI.CONST NESNEYE İLK DEĞER VERİLMEMİŞ.
	
	mx = 10;    // deseydik yine SENTAKS HATASI. Cosnt nesneye atama yapılamaz.Burası atama satırı.
				// ctor init list yapılmalı.
}

int main()
{

}

-------------- -

OLMASI GEREKEN KOD 

Myclass::Myclass() : mx{ 20 }
{

}

------------------------------------------------------------------------------ -
------------------------------------------------------------------------------ -

#include <iostream>
#include "date.h"

//.h 
class Date {
public:
	Date(int, int, int);
	void set(int d, int m, int y);
	void print()const;
private:
	int md,mm,my;
};

/.cpp
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
	std::cout << md << "-" << mm << " - " << my << "\n";
}

int main()
{
	Date mydate(15, 12, 1955);
	mydate.print();
}

--------------------------------------------------------------

class Nec {
public:
	Nec(int, int, int);
	void print()const;
private:
	int x, y, z;
}

Nec::Nec(int x, int y, int z) : x{ x }, y{ y }, z{ z }
{				buradaki x ler class scope ta aranacak x, { x } ise parametrelerden gelenler
				HATA YOK.
}

void Nec::print()const
{
	std::cout << x << y << z << "\n";
}

int main()
{
	Nec mynec{ 1,3,7 };
	mynec.print(); SENTAKS HATASI YOK.
}

------------------------------------------------------------------------------

Nec::Nec(int x, int y, int z) : x( x + 5 ), y( y * 2 ), z( x+y+z )   BURADA DA HATA YOK.
{

}

------------------------------------------------------------------------------

Nec::Nec(int x, int y, int z) : x(foo())  burası da legal
{

}

------------------------------------------------------------------------------

Mülakat sorusu

class Nec {
public:
	Nec(int, int);
	void print()const;
private:
	int mx, my;
}

Nec::Nec(int a, int b) : my{ a }, mx{ b }
{

}

Hayata gelmesindeki sıra önemli değil.
Soru, ilk hangisi hayata gelecek ?
Cevap : classtaki member nesne hangi sırada yazılmışsa o sırada hayata gelir.Yani bildirim sırası.

yani mx gelecek.o Yüzden mx = my / 5 UB DİR.


ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!

Nec::Nec(int a) : my{ a }, mx{ my / 5 }   // UNDEFINED BAHAVIOR. Çünkü my garbage value da iken mx = my / 5 yapılmış.
{

}

------------------------------------------------------------------
------------------------------------------------------------------

M.I.L   veri elmanlarına ilk değer vermek için her zaman birinci tercihimiz olmalı.

A - Elemanları MIL ile init ediyorum
B - Elemana MIL ile init etmiyorum ama ana blok içinde atama yapıyorum

BURADAKİ DURUMLAR

1 - Hiçbir farklılık olmaz.Sadece görsel çirkinlik.
2 - Sentaks hatası oluşabilir.veri elemanı & veya const ise veya başka bir sınıf ise SENTAKS HATASI
3 - Ciddi verim farkı oluşabilir.

class Nec {	
public:
	Nec(const char* p);
private:
	std::string m_str;
};

Bu bir seçenek
Nec::Nec(const char* p)
{
	m_str = p;		//GEÇERLİ HATA YOK AMA VERIMSIZ
}

Buda bir seçenek
Nec::Nec(const char* p) : m_str(p)      //GEÇERLİ HATA YOK AMA ÇOK DAHA VERIMLI.
{
	
}

----------------------------------------------------------------------------
----------------------------------------------------------------------------

PARAMETRELI CONSTRUCTORLARI ÇAĞIRMAK

// .h
class Myclass {
public:
	Myclass(int);
};

// .cpp
Myclass::Myclass(int x)
{
	std::cout << "Myclass(int x) = " << x << "\n";
}

int main()
{
	Myclass a(12); // Direct init.
	Myclass b{ 17 }; // Direct list init{brace} c++ 11
	Myclass c = 23; // Copy init. 
}

FARK NEDİR ?
Şuanda bildiğimiz
Direct list initte, narrowing conversion engelleniyor idi.Diğerlerinde yok.	
İleride başka şeyler gelecek.
explicit keyword ile oluşturulan constructorlara, explicit ctor deniyor
bu durumda copy init sentaks hatası olacak mesela.


======================================================================================================================
======================================================================================================================
======================================================================================================================
======================================================================================================================
======================================================================================================================


ÇOK ÖNEMLİ !!!!!!!!!!!!!!

EĞER BIR SINIFA DEFAULT CONSTRUCTOR YAZMAZSAK DERLEYICININ KENDISI YAZAR BUNU.
class myclass{
		burası boş kalırsa compiler kendisi default constructor yazar.default ctor parametresi olmayan ctor veya 
		tüm parametreleri default olan demek.Ama derleyicinin özel üye fonksiyonunu default etmesi demek ise 
		onu kendisinin yazması demek.
};

Buna default ctor un compiler tarafından default edilmesi deniyor.	Kafa karıştırmasın.

myclass my; dediğimde hata yok. Default ctor olmasaydı hata olurdu, yukarıda ben yazmadım ama derleyici kendi yazdı bunu.
Yani compiler default constructoru default etti.

DIKKAT!!!
Eğer default ctor olmadan 1 veya 2 ... parametre alan ctor yazarsak, artık derleyici bizim için ctor yazmaz.

class myclass{
public:
	myclass(int);
};

int main()
{
	myclass m;   BURASI SENTAKS HATASI. Çünkü biz 1 parametre alan ctor yazdık, artık derleyici default ctor(Parametre almayan) yazmaz
}				 Burada Default ctor hatası yok hatası alınır.


----------------------------------------------------------------------------

DIKKAT!!!
Bir sınıfın default ctoru olmayabilir ama bu çok doğal durum değil.
Çok seyrek çıkar karşımıza.

ÖR:
class myclass{
public:
	myclass(int);
};

int main()
{
	myclass a[10];	// dizi default init ediliyor. bu durumda elemanlarda default init edilecek.
					// default ctor burada yok ve olmadığından SENTAKS HATASI.
}

İLERİDE CONTAINERLARDA GÖRÜLECEK. MESELA DİNAMİK DİZİ CONTAİNERDA GÖRÜLECEK.


==================================================================================================================
==================================================================================================================
==================================================================================================================
==================================================================================================================
==================================================================================================================


MOLADAN SONRASI

Derleyici tarafından yazılan(default edilen)constructor aşağıdaki özelliklere sahip üye fonksiyonudur.

a - Sınıfın Non-static
b - Inline
c - Public   

Derleyicinin yazdığı default ctor sınıfın tüm veri elemanlarını default init eder.
Yani primitive türler çöp değerde olacak.

------------------------------------------------------------------------------ -
------------------------------------------------------------------------------ -

DEFAULT MEMBER INITIALIZER(C++11)
in-class initializer de deniyor.
class içinde init etmeye deniyor.

class Myclass {
public:
	void print()const;
private:
	int mx{ 10 };
	int my = 20;
	int mz(30);  //BU SON INIT SENTAKS HATASI. PARANTEZ KULLANILAMIYOR.	
};

BU ŞU DEMEK,
Derleyici, ctoru sen yazsanda elemanları default init etmeyeceksin.İnitializer olarak private kısmındaki expr leri kullanacaksın.

-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------
ÖR:
class Myclass {
public:
	void print()const;
private:
	int mx{ 10 };
	int my = 20;
	// burada parantez kullanmak sentaks hatası demiştik.
};

ÇOK ÖNEMLİ !!!!!!!!!!!!!!
BU SINIFIN DEFAULT CTORUNU COMPILER YAZDI.YAZARKENDE BENIM PRIVATE KISMINDA YAZDIĞIM IFADELERI/EXPRESSIONLARI KULLANDI.
BU SAYEDE DERLEYİCİ CTOR YAZARKEN BU BİLDİRİMLERİ KULLANIYOR.

void Myclass::print()const
{
	std::cout << "mx = " << mx << " my = " << my << "\n";
}

int main()
{
	Myclass a;
	a.print();
}

ASLINDA CTOR OLARAK AŞAĞIDAKİNİ YAZDI.
Myclass():mx(10),my(20) {}  BUNUN GIBI BIR IFADEYE ÇEVIRDI ÇÜNKÜ PRIVATE KISMINDA BIZ BUNU BELIRTTIK.

-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------

ÇOK ÖNEMLI !!!!!!!!!!!!
AYNI ZAMANDA ŞUNUDA YAPIYOR.
BİZ BİR CTOR YAZARSAK VE X,Y DEĞİŞKENLERİNİ İNİTİALİZER LİST İLE İNİTİALİZE ETMEZSEM,
BENİM YAZDIĞIM CTORLARADA BU İLK DEĞER VERME İFADELERİNİ EKLER

ÖR:
class Myclass {
public:
	void print()const;
	Myclass();
private:
	int mx{ 10 };
	int my = 20;
};

void Myclass::print()const
{
	std::cout << "mx = " << mx << " my = " << my << "\n";
}

AŞAĞIDA CTOR INITIALIZER LIST KULLANMADIK AMA YUKARIDA DEFAULT MEMBER INITIALIZER KULLANDIK.
BU KOD DEFAULT MEMBER INITIALIZER DA BELIRTILEN IFADELERIN DEFAULT CTORA YAZILMASINI SAĞLIYOR.
KENDİMİZ YAZMAK YERİNE DERLEYİCİYE EKLETTİRİYORUM.


Myclass::Myclass()
{

}

int main()
{
	Myclass a;
	a.print();   // mx = 10    my = 20 
}

--------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------

Eğer hem Ctor Initializer List hemde default member init kullanılsaydı,
Ctor init list öncelikli oluyor.

class Myclass {
public:
	void print()const;
	Myclass();
private:
	int mx{ 10 };
	int my = 20;
};

void Myclass::print()const
{
	std::cout << "mx = " << mx << " my = " << my << "\n";
}

Myclass::Myclass() : mx {12345}
{

}

int main()
{
	Myclass a;
	a.print();		// mx = 13245   my = 20 çıkar.
}


--------------


Myclass::Myclass() : mx {12345} , my {321} olsaydı değeeler 12345 ve 321 olacaktı. default member init kullanılmayacaktı.
{

}

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

2 adet ctor varken.

class Myclass {
public:
	void print()const;
	Myclass();
	Myclass(int);
private:
	int mx{ 10 };
	int my = 20;
};

void Myclass::print()const
{
	std::cout << "mx = " << mx << " my = " << my << "\n";
}

Myclass::Myclass() 
{

}

Myclass::Myclass(int a) : mx{a}
{
	// ..kodlar..
}

}int main()
{
	Myclass a(100);
	a.print();		 100 ve 20 yazdırılır. 
}


---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------

HATIRLATMA

class Myclass {
public:
	void print()const;
private:
	int mx;
	int my;
	// burada parantez kullanmak sentaks hatası idi.
};

Myclass my;
Bu durumda garbage value da olacak değerler

---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
HATIRLATMA

class Myclass {
public:
	void print()const;
private:
	int mx{ 10 };
	int my = 20;
};

Burada derleyici ctor yazarken bunu nasıl yazacağını belirtiyoruz.

====================================================================================================================================
====================================================================================================================================
====================================================================================================================================
====================================================================================================================================


ODR
---
Bu bir acronim.
ONE DEFINITION RULE

Belirli varlıkların bildirimi birden fazla kez yazılabilir ama tanımı tek olmalı.
Bu ihlal edilmemeli.

Mesela class/function definition tek olmak zorunda

int x = 10;
int x = 20;  Mesela burası sentaks hatası.

class ve func larda da aynı.

MESELA BİR HEADER FİLE A BİR FONK UN DEFİNİTİONUNU YAZDIK. NORMALDE YAPILMAMALI BU.

Header içinde bunu tanımlarsak one definition rule bozmaya çok açık hale geliyor kod.
bunu aynı projede 2 yada daha fazla kaynak dosya include ederse, aynı varlığın birden fazla tanımı olaacak.Bu da UNDEFINED BEHAVIOR.

void func(int x)
{
	
}

Ali.cpp de ve veli.cpp de bu tanımın olması UNDEFINED BEHAVIOR. Linker time hatasıda alınabilir.

DIĞER TARAFTAN BUNUN BAZI ISTISNALARI VAR !!!!!!!!!!!!!!!!!
BIR TANESI CLASS DEFINITION !!!!!!!!!!!!!!!!!!!
Projeyi oluşturan kaynak dosyaların birinde aynı isimli sınıfı birden fazla kez tanımlarsak bu zaten SENTAKS HATASI.

Eğer class token by token diğer kaynak dosyalarda da varsa one definition rule ihlal edilmemiş oluyor.
ÖR : Class definition header file a konursa ve bunu diğer modüller include ederse burada one definition rule ihlal edilmemiş oluyor.
	 AYNI ŞEYİ İNCLUDE ETTİKLERİ İÇİN TOKEN BY TOKEN AYNI OLACAK ZATEN :D:D:D

---------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKİ VARLIKLARIN BİRDEN FAZLA KEZ FARKLI KAYNAK DOSYALARDA TANIMLANMASI DURUMUNDA EĞER TÜM TANIMLAR TOKEN BY TOKEN AYNI İSE
ONE DEFİNİTİON RULE/ODR İHLAL EDİLMEMİŞ SAYILIR. 

A - CLASS DEFİNİTİON
B - İNLİNE FUNCTİONS
C - İNLİNE VARİABLES (C++17)
BAŞKALARIDA VAR SONRA GÖRÜLECEK.

BU VARLIKLARIN TANIMI BAŞLIK DOSYASINA KOYABİLİRSİNİZ DEMEK İSTENİYOR BURADA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

INLINE FONKSIYONLARI 10 KİŞİDEN 7 Sİ YANLIŞ ANLIYOR.
---------------------------------------------------------------------------------------------------------------------------------------

COMPILER OPTIMIZATION
---------------------
C / C++ DİLLERİ DİĞER DİLLERE GÖRE OPTIMAZING COMPILERS OLMASI, AVANTAJ SAĞLIYOR.
DERLEYİCİ YAZDIĞIMIZ KODUN SEMANTİK KARŞILIĞINI DEĞİŞTİRMEDEN, YENİ BELİRLİ KOŞULLARA UYARAK YENİDEN DÜZENLEME HAKKINA SAHİP.
TAHMİN EDİLENDEN ÇOK DAHA İYİ YAPIYOR OPTİMİZASYON İŞİNİ.

UNDEFINED BEHAVIORUN TEMEL SEBEPLERINDEN BİRİ COMPILER OPTIMIZATION. COMPİLER IN TEK TALEBİ UNDEFINED BEHAVIOR OLMAMASI.

C DE YAPILAN OPTİMİZASYONLARDAN BİR KISMINI BAHSETTİ.
VİMEO DA C DERNEĞİNİN VİDEOSU VARMIŞ. OĞUZ KARAN SANIRIM.OPTİMİZASYON İLE ALAKALI.

BURADAKİ TEKNİKLERE İNLİNE EXPANSİON DENİYOR.
İNLİNE EXPANSİON  = BİR FONKSİYON ÇAĞRISI YAPILMIŞ FAKAT DERLEYİCİ NORMALDE FONKSİYON ÇAĞRISI KARŞILIĞINDA, 
FONKSİYONA GİRİŞ(STACK DURUMU, FONKSİYONLARIN ARGÜMANLARININ PARAMETRELERE GEÇİRELECEĞİ DEĞİŞKENLERİ, FONKSİYONUN RETURN DEĞERİNİN ADRESİ...), 
FONKSİYONDAN ÇIKIŞ(STACK İN ESKİ HALE GETİRİLMESİ GİBİ ...) VE LİNKERDA BİR REFERANS İSİM YAZIYOR.

a = func(x); 

DERLEYİCİ ANALİZ YAPIYOR VE BU FONKSİYONUN DERLENMİŞ KODUNU DOĞRUDAN func(x) YERİNE YAZIYOR. LİNKERI BYPASS ETMİŞ OLUYOR.
NEREDE FAYDA SAĞLIYOR ? 
KODU KÜÇÜK VE SIK ÇAĞRILAN FONKSİYONLARDA ÇOK İŞE YARIYOR.
C'DE FUNCTIONAL MACROLAR VARDI. NE KADAR DA GÜZELDİ AMA BURADAKİ ARAÇ FARKLI.

KOŞULLAR VAR
------------
A - DERLEYİCİ FONKSİYONUN TANIMINI GÖRMEK ZORUNDA
B - YAPTIĞI ANALİZ SONUCUNDA AVANTAJ ELDE EDECEĞİNİ ANLAYIP BUNA GÖRE KARAR VERECEK.
	DERLEYİCİYE DE BAĞLI. BİRİNİN BUNU YAPIP DİĞERİNİN YAPAMADIĞI DURUMLAR VAR.
	DERLEYİCİNİN SWİTCH LERİ İLE İLGİSİ DE VAR.BU SWİTCHLER İLE KONTROL EDİLEBİLİYOR.
C - TEKNİK OLARAK BUNU YAPABİLİYOR OLACAK.
D - SWİTCHLERİ BUNA İZİN VERECEK.


C++ TA BU inline KEYWORD İLE TANIMLANIR.

Bu bir inline fonksiyon.
inline void func(int x)
{
	return x * x + 5;
}

Bildirimde veya tanımda olması yeterli. 
Bildirimde olup tanımda olmayabilir.
Her ikisinde de olabilir.

REGİSTER KEYWORD GİBİ İNLİNE DA AYNI
------------------------------------
DERLEYİCİ SENDE UYGUN GÖRÜRSEN, FONKSİYONUN DERLENMİŞ HALİNİ, ÇAĞRININ YAPILDIĞI YERE YERŞLEŞTİR.


BURASI ENTERESAN
----------------
İNLİNE IN PEK ÖNEMİ KALMIYOR ASLINDA.
İNLİNE KULLANMAZSAK BİLE COMPİLER İNLİNE OPTİMİZASYONU YAPABİLİR AMA İNLİNE KULLANIRSAK TA YAPMA GARANTİSİ YOK. :D:D:D:D

DERLEYİCİNİN MUTLAKA FONKSİYONUN TANIMINI GÖRMELİ.BİLDİRİM DEĞİL.TANIM !!!!!!!!!!!!!!!!!!!!!!!

İNLİNE FONKSİYONLAR İNLİNE KEYWORD İLE HEADER FİLE İÇERİSİNDE KULLANILIYORLAR.
BUNU KAÇ KAYNAK DOSYA İNCLUDE EDERSE ETSİN, FUNC FONKSİYONU HEPSİNDE OLACAK AMA ONE DEFİNİTİON RULE İHLAL EDİLMİYOR.
BÖYLECE BİR İNLİNE FONKSİYONUNU BAŞLIK DOSYASINA KOYARAK
	A - TANIMSIZ DAVRANIŞ ENGELLENİYOR.
	B - DERLEYİCİYE İNLİNE OPTİMİZASYON YAPMA SEÇENEĞİ SUNUYORUZ.

TANIMINI ESKİSİ GİBİ CODE FİLE DA YAPSAYDIK, DERLEYİCİ BU OPTİMİZASYONU YAPAMAYACAKTI.

SONUC OLARAK INLINE FONKSIYONLAR: 
	1 - TİPİK OLARAK BAŞLIK DOSYASINDA TANIMLANAN
	2 - ONE DEFİNİTİON RULE İHLALİ YAPMAYAN.
	3 - DERLEYİCİDE DE İNLINE OPTİMİZASYON İMKANI SAĞLAYAN AMA BUNA MECBUR BIRAKMAYAN FONKSİYONLARDIR.

	BU OPTİMİZASYONU YAPIP YAPMADIĞINI ASSEMBLY KODDAN ANLAYABİLİRİZ.


DEZAVANTAJLARI DA OLABİLİR.
1 - FONKSİYONUN TANIMI TAMAMEN GÖRÜLÜYOR. 
2 - RETURN DEĞERİ OLARAK USER DEFİNED TÜR KULLANIRSAK, BU TÜRLERE İLİŞKİN BİLDİRİMLERİDE DERLEYİCİNİN GÖRMESİ LAZIM.
	BU DURUMDA FAZLADAN BAŞLIK DOSYASI İNCLUDE ETMEK GEREKEBİLİR.


KESİNLİKLE YAPTIĞI ŞEY ŞU, HEADER FİLE İÇERİSİNDE BİR FONKSİYON TANIMI YAPTIĞIMIZDA BUNU DA DİĞER FONKSİYONLAR İNCLUDE ETTİĞİNDE 
NORMALDE ŞARTLARDA SENTAKS HATASI OLURDU. INLINE İLE NİTELERSEK SENTAKS HATASI OLMUYOR. KULLANILABİLMESİNİ SAĞLIYOR.

YAPMA İHTİMALİ OLDUĞU ŞEY DE ŞU, OPTİMİZATİON YAPIP FONKSİYON ÇAĞRISININ OLDUĞU YERE, FONKSİYONUN DERLENMİŞ HALİNİ YAPIŞTIRABİLİR VE
LİNKER DEVREDEN ÇIKARILMIŞ OLUR. SONUÇTA DAHA MALİYETSİZ BİR İŞ YAPILMIŞ OLUR.BU COMPİLER SWİTCH VEYA ALT SEVİYEDEKİ ALGORİTMA İLE ALAKALI.


İNLİNE FONKSİYONUN TANIMLANMASI
-------------------------------

GLOBAL SCOPETA AŞAĞIDAKİ GİBİ.

#ifndef DATE_H
#define DATE_H


class Date {
public:
	Date(int, int, int);
	void set(int d, int m, int y);
	void print()const;
private:
	int md, mm, my;
};

inline int func(int x)
{
	// bu şekilde olabilir.
}

#endif

-----------------------------------------------------

ASIL HİKAYE SINIFIN ÜYE FONKSİYONLARINDA BUNU YAPMAK.
ÇOK ÇAĞRILDIKLARI İÇİN OPTİMİZASYON ÇOK ÖNEMLİ OLUYOR.

BUNU YAPMANIN İKİ YOLU VAR. !!!!!!!!!
//.h
class Date {
public:
	Date(int, int, int);
	inline void set(int d, int m, int y); // TANIM / BILDIRIM / YADA HER IKISINDE DE INLINE BULUNMASI GEÇERLI. !!!!!!!!!
	void print()const;
private:
	int md, mm, my;
};

void Date::set(int d, int m, int y)
{
	md = d;
	mm = m;
	my = y;
}


DİĞER YOL İSE FONKSİYONUN TANIMINI DİREKT SINIFIN TANIMININ İÇİNDE YAPMAK !!!!!!!!!!!!!!!!!

//.h
class Date {
public:
	Date(int, int, int);
	inline void set(int d, int m, int y)  // İNLİNE KULLANMASAKTA KULLANSAKTA DAHA YİNEDE İNLİNE OLARAK İŞLEM GÖRÜR
	{
		md = d;
		mm = m;
		my = y;
	}
	void print()const;
private:
	int md, mm, my;
};

----------------------

VEYA İNLİNE YAZMADAN DA OLUR. BU CLASS DEFİNİTİONDA GEÇERLİ !!!!!!!!!!!!!!!!!!
//.h
class Date {
public:
	Date(int, int, int);
	void set(int d, int m, int y)  // İNLİNE KULLANMASAKTA KULLANSAKTA DAHA YİNEDE İNLİNE OLARAK İŞLEM GÖRÜR
	{
		md = d;
		mm = m;
		my = y;
	}
	void print()const;
private:
	int md, mm, my;
};

-------------------------------------------------------------------------------------------------------------

MEMBER FUNCTİON İNLİNE YAPMAK İÇİN HOCA İNLİNE KULLANMADAN YAPMAYI TERCİH EDİYOR.
DİĞER SPECİAL MEMBER FUNCTIONLARDA İNLİNE OLARAK TANIMLANABİLİR.

AŞAĞIDA İNLİNE FUNCTİONLARI İNLİNE İLE NİTELEMEDEN YAZDIK MESELA.İNLİNE DA YAZILABİLİRDİ.AYNI ŞEY OLUYOR.

//.h
class Date {
public:
	Date() : md{1}, mm{8},my{1950} {}
	Date(int d, int m, int y) : md{d},mm{m},my{y} {}
	void set(int d, int m, int y)  // İNLİNE KULLANMASAKTA KULLANSAKTA DAHA YİNEDE İNLİNE OLARAK İŞLEM GÖRÜR
	{
		md = d;
		mm = m;
		my = y;
	}
	void print()const
	{
		std::cout << " ....\n"; 		iostream include edilmeli.tercih pek edilmez ama edilecekse include şart.Dezavantajlardan biri.
	}
private:
	int md, mm, my;
};

-----------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------

MOLADAN SONRASI

C++ ın en iyi kaynaklarından biri "C++ faqs iscpp"
C++ Core Guideliness. github linki ile giriliyor.

Büyük koda sahip fonksiyonların inline olarak açılması çok avantajlı olmayabilir.
Inline değişkenler C++ 17 ile dile eklendi.

//erdem.h
int g = 10;
Burada ONE DEFINITION RULE / ODR ihlal edilir.
eskiden extern int g = 10 yapardık. C de halen böyle.

artık 
inline int g = 10; dersek artık bunu kim include ederse etsin ODR ihlal edilmeyecek.

Header-Only library
C++ ta sadece tek bir başlık dosyasından oluşan modüller oluşturma imkanı veriyor bize.


===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================

MODERN C++ TA FONKSİYONLARIN DELETE VE DEFAULT EDİLMESİ
-------------------------------------------------------

Çok iyi anlamak gerekiyor burayı !!!
Not: Inline fonksiyon var, inline variable var ve inline namespace var. inline keywordü de overload edilmiş.
	 7 - 8 yerde auto keyword kullanılıyor. Using 4-5 yerde kullanılıyor.


C++ ta bir sınıfın üye fonksiyonu delete edilebilir. Dinamik ömürlü nesneler ile alakalı değil burası.
Bir fonksiyonun delete edilmesi, bir foksiyonun bildirilmesi fakat fonksiyona yapılan çağrının compiler tarafından 
SENTAKS HATASI OLUŞTURMASI demek.

SENTAKS:
int (foo)(int) = delete;     Burada foo isimli fonksiyon delete edildi.
Bu fonksiyon var ama yapılan çağrı sentaks hatası oluşturacak demek.

ÖR:
int (foo)(int) = delete;

int main()
{
	foo(12);     // HATA : Severity	Code	Description	Project	File	Line	Suppression State
				 //	Error(active)	E1776	function "foo(int)" (declared at line 994) cannot be referenced -- it is a deleted function	08_29_05_2021	D : \CSD\C++\08_29_05_2021\08_29_05_2021\main.cpp	998

}

------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------

Special member funcitons larda delete edilmiş olabilir.

class Myclass{
public:
	Myclass(int) = delete;	
	void func(int) = delete;
};


----------------------------------------------------------------------------------------------------------------

DELETE EDİLMİŞ FUNCTIONLAR FUNC OVERLOAD RESOLUTIONA KATILMAYA DEVAM EDER.


void func(int);
void func(double) = delete; // DELETE EDİLSE BİLE FUNC OVERLOAD RESOLUTIONA KATILIR.
void func(unsigned);
void func(const char *);

int main()
{
	func(12);		// 4 candidate functiton.Viable func sayısı 3. 1 parametre seçilir. EXACT MATCH
}

int main()
{
	func(12u);		// 4 candidate functiton.Viable func sayısı 3. 3 parametre seçilir. EXACT MATCH
}


int main()
{
	func(1.2);		// 4 candidate functiton.Viable func sayısı 3. SENTAKS HATASI. Delete edildi ama var kabul ediliyor. 
}					// çağrı yapıldığında SENTAKS HATASI OLUŞUR.


----------------------------------------------------------------------------------------------------------------

EĞER BİR FONKSİYONUN TAMSAYI TÜRLERİNDEN ARGÜMANLA ÇAĞRILMASINI İSTEMEZSEK MESELA(GENERİC PROGRAMLAMADA DAHA KOLAY)

void func(double);
void func(int) = delete;

int main()
{
	int ival{3};
	func(ival);		// ŞUANDA SENTAKS HATASI VERİR.
}

----------------------------------------------------------------------------------------------------------------

SIK SORULAN MÜLAKAT SORUSU
--------------------------
BİR FONKSİYONUN SADECE BELİRLİ TÜRDEN ARGÜMANLA ÇAĞRILMASINI İSTİYORUZ.
Sadece int ile çağrılsın istiyoruz. Bunun dışında ne olursa olsun illegal olmalı.

Burada template/şablonu oluşturmak gerekiyor.
Fonksiyon şablonu derleyiciye fonksiyon yazdırıyor.

ÖR:

void func(int);

template<typename T>
void func(T x) = delete;

int main()
{
	func(12);
}


KONU ASLINDA SPECIAL MEMBER FUNCTIONSLARIN DELETE EDILMESI ŞUANDA
YARIN DEVAM EDILECEK.


*/
