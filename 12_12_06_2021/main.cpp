/*

Hoca soru soracaksanız telegramdan sorun diyor :D
Bir konu karmaşık olabilir ama tekrar gelmeyeceğimiz anlamına gelmiyor.
Dil karmaşık. Bunlar normal Diyor :D:D:D
Bjarne ben dilin % 70 ine hakimim diyor.
Biz ise productionda kod yazacak seviyede olacağız.

Hocaya sorulan sorular?

1 -
const Myclass& foo()
{
	//
	return Myclass{};  //Bu legal Ama Yapılmaması gerekir. UNDEFINED BEHAVIOR
};			   // geri dönüş değeri referans.Dangling pointer gibi.
			   // Yerel nesne ile dönünce ömrü bitmiş oluyor ve UB.

2 -
Life Extension konusu
class Myclass{

};

Myclass foo();

int main()
{
	const Myclass& r = foo();
	Myclass&& rr = foo();  Bu ikisinde de değişkenin değeri ne zaman biterse, buradaki geçici nesneninde hayatı o zaman bitecek.

}

3 -
Standart Move functionu. Function templateler ile alakalı aslında.
Bu Derleyiciye fonksiyon kodu yazdırıyordu.
Move utility header file da bildirilmiş.

Bu koşulsuz bir dönüşüm yapıyor.İfadeyi rvalue value categorisine dönüştürüyor.
Aslında bu X value, o da R value demek.

Move doesnt move. Move only cast

void func(int &&r)
{
	std::cout << "func(int &&r)\n";
}


void func(const int &r)
{
	std::cout << "func(const int &r)\n";
}

int y;
const int x{};

std::move(x);  Bunun çağıracağı overload void func(const int& r) i çağıracak.

func(move(y)); üstteki çağrılır. int&& olan

func(move(x)); Burada && değil & olan ifade çağrılacak. consttan ötürü.Alttaki çağrılır.


---------------------------------------------------

const int&& r; bu teknik olarak mümkün ama nesne değiştirilemez.
Burada çalma işlemleri yapılabilir ama bu durumda bu nesnede değişecek.
Burada hata olur.Pek kullanım amacı yok.

Hatırla !!!
mp = other.mp;
other.mp = nullptr;   Burada hata oluşur.Çünkü const. Bu sebeple uygun olmayabilir.
Legal bir durum ama uygun olmayabilir.

EĞER !!!!

void func(const int &&r)
{
	std::cout << "func(const int &&r)\n";
}

Yukarıdaki tanım olsaydı aşağıdaki olurdu.

const int x{};
func(move(x));   // func(const int &&r) çağrılırdı
 


========================================================================
========================================================================
========================================================================
========================================================================

DİNAMİK ÖMÜRLÜ NESNELERDEN DEVAM EDİYORUZ.
------------------------------------------

New operatörü ile oluşturulmuş kodlar genellikle tercih edilmiyor.
Bunun yerine smart pointerlar kullanılıyor.Çok yoğun kullanılıyorlar.
unique_ptr ve shared_ptr bunlar çok kullanılıyor.

class Myclass{
	Myclass();
	Myclass(int);
};

int main()
{
	// new Myclass // default init edilir.
	// new Myclass() // value init
	// new Myclass{} // value init
	// new Myclass(10) // ctor
	// new Myclass{2} // ctor

	Myclass *p = new Myclass{2}; //bu şekillerde kullanılabilir.
	auto p = new Myclass{2};

	Aşağıdaki gibide mümkün
	Myclass &r = *new Myclass{2}; //bu da mümkün.Delete ederken
	delete &r; // bu şekilde kullanılır buda görsel çirkinlik.
}

-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------

NEW OPERATÖRÜ BAŞKA,  OPERATOR NEW FUNCTION BAŞKA.
YAZMIŞTIM ÖNCEKI DERS.

new Myclass(2); ne yapıyor
Derleyici malloc ile aynı yapıda ismi operator new olan fonksiyonuna çağrı yapıyor, bu fonkisyona argüman olarak sizeof Myclass
gönderiyor ve bu fonksiyonun geri dönüş değeri olan void * türünden adresi myclass * türüne dönüştürerek ve bunu this adresi olarak kullanıp,
sınıfın ilgili Constructoruna çağrı yapıyor :D:D:D:D:D

2 Ayrı işlem yapıyor yani
-------------------------
1 - operator new function ile bellek alanı elde eder.
2 - Elde edilen bellek alanında bir nesne hayata getirir.

------------------------------------------------
İşlem sıralaması.Aşağıdada yazdım.
new ifadesi = operator new() --> constructor   
delete ifadesi = destructor --> operator delete
-------------------------------------------------

operator new i kendimizde çağırabiliriz.

#include <new>

int main()
{
	operator new(); // çağrılabilir.Bununda overloadları var.
}

-------------------------------------------------------------------------------

ör:

#include <new>

int main()
{
	size_t n;
	std::cout << "kac tamsayi\n";
	cin >> n;

	int *p = static_cast<int *>(operator new(n * sizeof(int)));
	//malloctan farklı olarak başarısız olması durumunda NULL pointer döndürmeyecek.
	//C++ taki EXCEPTION HANDLING araçları devreye girecek. Hata olması durumunda bad_alloc türünden exception throw ediyor.

	
	for(size_t i{}; i < n; ++i)
	{
		p[i] = i;
	}

	for(size_t i{}; i < n; ++i)
	{
		std::cout << p[i] << " ";
	}

	operator delete(p);
	// freeye benziyor. Operator delete hata throw döndürmüyor.Başarılı kabul ediliyor.

}


//Sırası aynı değil.Dikkat !!!
new ifadesi = operator new() --> constructor
delete ifadesi = destructor --> operator delete


new / delete operatörüne overload edilemez.
AMA 
operator new functionu overload edilebilir. overload edersek compiler bizim
overload ettiğimiz functionunu çağıracak.
Aynı şekilde operator delete functionu içinde var. İleride görülecek.

Not: Dinamik olarak hayata getirilen nesnelerin delete edilmesinden biz sorumluyuz.

C#,Java gibi dillerde Garbage Collector var. C++ ta Garbage Collector olmaması seçim.

----------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------


BURASI ARKA PLANDA NE OLDUĞUNU ANLATIYOR. 
OPERATOR NEW VE OPERATOR DELETE OVERLOAD EDİLİYOR.
--------------------------------------------------

ÖZEL DURUM. PARAMETRIK YAPISI AYNISI TANIMLANSA BILE OVERLOAD EDILIYOR

// new operatörü değil, operator new func overload ediliyor.
void* operator new(size_t n)
{
	std::cout << "Operator new called n = " << n << "\n";
	void *vp = std::malloc(n);
	if(!vp)
	{
		throw std::bad_alloc{}; // Bunu henüz öğrenmedik.Sorun değil.
	}

	std::cout << "the address of the allocated block = " << vp << "\n";
	return vp;
}


void operator delete(void *vp)
{
	if(!vp)
		return;

	std::cout << "operator delete called... vp = " << vp << "\n";
	std::free(vp);

}

int main()
{

	auto p = new int;
	delete p;
}

ÇIKTI
-----
Operator new called n = 4	(sizeof(int) i argüman olarak yazdı compiler.Kural zaten new ile yaratılan nesnenin sizeof unu argüman yazmak.)
the address of the allocated block = 00870550
operator delete called... vp = 00870550


--------------------------------------------------------------------------------------------------------------------------------------------


CLASS EKLENİYOR.

class Myclass{
	char buffer[1024]{};

};

// new operatörü değil, operator new func overload ediliyor.
void* operator new(size_t n)
{
	std::cout << "Operator new called n = " << n << "\n";
	void *vp = std::malloc(n);
	if(!vp)
	{
		throw std::bad_alloc{};
	}

	std::cout << "the address of the allocated block = " << vp << "\n";
	return vp;
}

void operator delete(void *vp)
{
	if(!vp)
		return;

	std::cout << "operator delete called... vp = " << vp << "\n";
	std::free(vp);

}

int main()
{
	std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n";
	Myclass *p = new Myclass;
	delete p;
}


ÇIKTI
-----
sizeof(Myclass) = 1024
Operator new called n = 1024
the address of the allocated block = 00AAF630
operator delete called... vp = 00AAF630




------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------

CLASSA CONSTRUCTOR EKLENİYOR.

Bu Kod Saklanacak.Kütüphanenin dinamik bellek yönetimi
kullandığını ispatlamak için bunu kullanacağız

class Myclass{
public:
		Myclass()
		{
			std::cout << "Myclass def ctor called this = "<< this << "\n";
		}
		~Myclass()
		{
			std::cout << "Myclass destructor called this = "<< this << "\n";
		}

private:
	char buffer[1024]{};

};

// new operatörü değil, operator new func overload ediliyor.
void* operator new(size_t n)
{
	std::cout << "Operator new called n = " << n << "\n";
	void *vp = std::malloc(n);
	if(!vp)
	{
		throw std::bad_alloc{};
	}

	std::cout << "the address of the allocated block = " << vp << "\n";
	return vp;
}

void operator delete(void *vp)
{
	if(!vp)
		return;

	std::cout << "operator delete called... vp = " << vp << "\n";
	std::free(vp);

}

int main()
{
	std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << "\n";

	Myclass *p = new Myclass;	// default init. new Myclass(12) olsaydı value init olacaktı.Dersin başında yazdım
	std::cout << "p = " << p << "\n";

	delete p;
}

CTOR içindeki this ile p aynı adres olmalı.

ÇIKTI
-----
sizeof(Myclass) = 1024
Operator new called n = 1024
the address of the allocated block = 0172F610
Myclass def ctor called this = 0172F610
p = 0172F610
Myclass destructor called this = 0172F610
operator delete called... vp = 0172F610


----------------------------------------------------------------------------------------------------------

int main()
{
	std::string str{"Burak Yagiz Balci bir soru sordu ve ben cevap verecegim"};
	// Yazı heapte tutuluyor. 
	// Bir allocation yapması gerekece.Bunuda new ile yapacak.
	// Ama ortada new operatörüne çağrı görünmüyor.
}

İLERİDE GÖRÜLECEK
ÇIKTI - DEBUG MODDA
-------------------
Operator new called n = 8
the address of the allocated block = 00AEE000
Operator new called n = 64
the address of the allocated block = 00AE4CC0
operator delete called... vp = 00AE4CC0
operator delete called... vp = 00AEE000

ÇIKTI - RELEASE MODDA
---------------------
Operator new called n = 64
the address of the allocated block = 00F94B70
operator delete called... vp = 00F94B70



SONUÇTA BİR ALLOCATİON VAR. BUNU İSPATLAMAYA ÇALIŞTIK.
NEW ÇAĞRISI YOK, GÖRÜNÜRDE KULLANILMIŞTA DEĞİL.DELETE TE 
AYNI ŞEKİLDE.KULLANILMADI AMA ÇAĞRILDI.BLOK SONUNDA ÇAĞRILDI.


Tekrar çalıştırıyoruz.

int main()
{
	std::string str{"Burak"};
}

ÇIKTI
-----
BOŞ.Ekranda birşey yok.


Sebebi Small String Optimization.Zorunluluk değil.
Modern string sınıfı optimizasyonlarında küçük yazıların kullanımlarını daha verimli hale getirmek için string
nesnesinin kendi içinde buffer tutuluyor, yazı buffera sığacak kadar ufaksa, hiç Dinamik Bellek alanı allocate edilmiyor.

Bunlar String sınıfında incelenecek.

operator new ve operator delete overload edilebilir.Böyle senaryolar var.
İleride görülecek. Hatta operator new ve operator delete sınıfın üye fonksiyonları için
overload edilebilecek. Kursun 2. Yarısında daha detaylı girilecek.

-----------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------


Bazı Detaylar
new operatörü ile const bir nesne oluşturulabilir.

auto p = new const int {1200};

const Myclass *p = new const Myclass{12};

auto p = new int[4]; // array new deniyor.
delete[] p; Buda dizi için delete sentaks.Array delete.
delete p ise yalın olan.Başka nesneler içindi buda.

------------------------------------------------------


class Myclass {
public:
	Myclass()
	{
		std::cout << "Default Ctor called  this = "<< this<< "\n";
	}
	~Myclass()
	{
		std::cout << "Destructor called  this = " << this << "\n";
	}

private:
	char buffer[16];
};

int main()
{
	auto p = new Myclass[4];
	// sizeof myclass 16 adreslerdeki artış görülür
	delete[] p; //BURAYA DİKKAT. SENTAKS BU. ARRAY DELETE
}


ÇIKTI
-----
Default Ctor called  this = 01044B74
Default Ctor called  this = 01044B84
Default Ctor called  this = 01044B94
Default Ctor called  this = 01044BA4
Destructor called  this = 01044BA4
Destructor called  this = 01044B94
Destructor called  this = 01044B84
Destructor called  this = 01044B74


new int [3]{1,2,3} te olabilir. Bunlar kursun 2. kısmında.


BU KONULAR VAR SIRADA
-----------------------
STATIC MEMBERS
STATIC MEMBER FUNCTIONS
FRIEND BİLDİRİMLERİ
OPERATOR OVERLOADING


MOLA

===================================================================================================================
===================================================================================================================
===================================================================================================================
===================================================================================================================


STATIC DATA MEMBERS - STATIC MEMBER FUNCTIONS
-----------------------------------------
Static ve nonstatic olarak 2 ye ayrılır.
Biz şimdiye kadar nonstatic olanları gördük.

----------------------------------------------------------------------------------------------------------------------------
NOT: Static member functionlar :: . -> operatörleri ile çağrılabiliyor. Nonstaticler ise :: operatörü ile çağrılamıyor.
Çünkü Nesne gerekli nonstaticte . veya -> operatörleri kullanılabilir.

NOT2: Sınıfın static member funclar, nonstatic data membersları(func+data) kullanamazlar.Çünkü static member funcların this
	  Nesnesi yok AMA !! Static member func içinden bir class nesnesi yaratırsak o nesnenin this ptr olacak ve o nesne ile 
	  nonstatic elemanlara duruma göre gidilir.Örnekler ders bitmeye yakın yapıldı. Line 1210!!!!
----------------------------------------------------------------------------------------------------------------------------

Şimdi staticleri göreceğiz.

class Myclass{
	int a,b,c;
};
Nonstatic veri elemanları instance ları ilgilendirir.
Sınıfın storage ihtiyacınıda belirler. C de olduğu gibi.
Mesela Myclass türden nesneler olsa herbirinin a,b ve c değişkeni farklı olabilir.


//Myclass.h
class Myclass{
	static int a;
};

ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!

NOT: static keyword sadece bildirimde olacak.Tanımda değil.Yoksa hata alınır. inline hariç :D

static int Myclass::a{10}; //HATA



static veri elemaları fiilen class nesnesinin içinde değil.Her sınıf için bir tane.
C deki global değişkenler gibi. Sadece class scope a alınmış. static ömürlü,
programın başından sonuna kadar hayatı devam edecek.Staticler mainden önce hayata gelirdi.
Aynen burada da böyle.

Global yerine static değişken kullanmak avantaj olabiliyor.
1 - Diğer isimlerle karışmıyor ve üye fonksiyonlar içinde bulunmasını sağlıyor.
2 - Access control sözkonusu.Duruma göre client kodlardan gizlenebilir.

	NOT: BUNUN BIR TANIMA IHTIYACI VAR. STATIC INT A; BIR BILDIRIM.
		 HENÜZ TANIMLANMIŞ DEĞIL. ÇALIŞTIRINCA LINKER HATA VERIR.

	class Myclass{
	public:	
		static int x;  // Bildirildi ama tanımlanmadı.Compile time da hata yok.Çalıştırınca Linker time da hata alınır.
	};

	int main()
	{
		Myclass::x = 10; // compile da hata yok. Run edersek linker time da hata alınır.
	}

	BU DURUMDA STATIC VERI ELEMANLARI DEFINE EDILMELI.
	Normalde sınıf içinde bildirmek ve Cpp dosyasında tanımlamak şeklinde yapılıyordu.

	Diğer yöntemde 2017 de inline variable geldi. bunlada tanımlanabilir.
	Henüz anlatmadı.Anlatılacak.


Aşağıda header içinde bildirip cpp içinden define ediliyor.

//Myclass.h
class Myclass{
	static int x;  // Bildirim.
};

//Myclass.cpp
int Myclass::x; //zero init demek bu.
int Myclass::x{}; //veya
int Myclass::x{10}; // ...

NOT : static ömürlü değişkenler defult init olduğunda zero init olurlar.
NOT : Bildirimde static yazıldı ama tanımda static yazılmayacak.

--------------------------------------------------------------------------
--------------------------------------------------------------------------

static int a; bir incomplete type olabilir.

Şuanda bilmeyenler için Incomplete - Incomplete type a girildi.

ICOMPLETE İLE NELER YAPILIR ? C ile aynı 
class Myclass;

Myclass* p = nullptr; ptr yada referans değişken tanımlanabilir.
Myclass func(Myclass x); //bildirimi tanımı değil.
extern int x; // Extern bildirimi yapılabilir.
typedef Myclass c1; // tür eş ismi bildirimleri.
using c1 = Myclass*; // using ile de olur

değişken veya instance tanımlanamaz
pointer dereference edilemez
sizeof operandı yapılamaz
Myclass *p = new Myclass; olamaz.(storage ihtiyacı belli değil :D:D)
Çözünürlük operatörü operandı da olamıyor Incomplete type.

class Neco;
class Myclass{
	Neco nec;	BURASI SENTAKS HATASI.INCOMPLETE TYPE HATASI VERIR.Static olsaydı başında olurdu çünkü bildirim olurdu.
};


NOT : BIR SINIFIN NONSTATIC ELEMANI KENDI TÜRÜNDEN OLAMAZ AMA STATIC OLUYOR :D

class Myclass{
	static Myclass x;  // GEÇERLİ. Çünkü bildirim oldu artık. Bildirimlerde Incomplete type zaten geçerli :D:D:D
};

NOT: Sınıf içindeki static veri elemanları sınıf türünden olabiliyor.

En önemli olduğu yer başlık dosyaları. Ekstra şeyler include etmemek
için incomplete type tanımlanır.


class A; // #include "class_A.h" gibi birşeye gerek yok.

class Myclass{
	static A ax; // incomplete type ile yazılabilir.
};

----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------

BAZI DURUMLARDA SINIFIN ELEMANLARINI GİZLEMEK İSTİYORUZ.
--------------------------------------------------------

Pimpl idiyomu , Pointer implementation dan kısaltma bir sözcük
client kodların, sınıfın private üyelerini gizlemek için kullanılan idiyom.
1 - Belki yazdığımız kodun başkaları tarafından görünmesini istemezsek yapabiliriz
2 - Sınıfın private bölümünü gizleyerek bazı başlıkların include edilmemesini sağlıyor.Önemli sebep bu.


class A;
class B;
class C;

class Myclass{
private:
	A ax;	// Burada incomplete kurtarmıyor bizi.Static değil.Yukarıda yazmıştık kuralda.
	B bx;
	C cx;    HATA

};


-------------------------------

#include "a.h"
#include "b.h"
#include "c.h"

class Myclass{
private:
	A ax;
	B bx;  //ŞİMDİ GEÇERLİ.Çünkü A, B, C classları bir complete type.
	C cx;

};


2 seçenek var
1. tüm başlık dosyalarını include edeceğiz.Dezavantajları var.birsürü header include edip compile time + recompile etmek gerekebilir.
2. pimpl idiyomu kullanılıp sınıfın private bölümünü gizleriz, başlık dosyasında bu elemanlar görünmediğine göre include edilme 
   zorunluluğu ortadan kalkar.

----------------------------------------------------------------------

PIMPL idiyomu ile sınıfın private bölümünü gizleyerek bazı başlıkların
include edilmemesini sağlıyor.

PIMPL İdiyomu henüz görülmedi.

----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------


SINIFIN STATIC VERI ELEMANLARINDAN DEVAM.
-----------------------------------------

//.h
class Myclass{
	static int a[]; // static veri elemanı olduğu için boyut yazmaya gerek yok.Incomplete type
	static double dval;

};

//.cpp
int Myclass::a[10]; // cpp file dan TANIMLANABİLİR.

-----------------------------------------------------------------------------------

SINIFIN STATIC VERI ELEMANLARININ KAYNAK KODDA CLIENT KODLAR TARAFINDAN KULLANILMASI
------------------------------------------------------------------------------------
Bunun için 2 durumun sağlanması lazım


1 - Name lookup 
--------------
İlk öne static veri elemanının ismini Class scope unda bulmamız gerekiyor.Name lookup başarılı olmalı yani.

class Myclass{
public:
		static int x;
};

// x i bir kaynak dosyada tanımlanmış farzet
int main(){
	Myclass::x = 10;  // GEÇERLİ. Qualified name deniyor. AMA x = 10 olsaydı isim aramadan sentaks hatasına düşer.
}

Bu veri static elemanını kullanmak için Myclass türden nesneye create ihtiyacı yok.
Biz nesne oluşturmasakta sınıfın static veri elemanı hayatta.


2 - Access Control.
-------------------
Veri elemanları public private protected olabilir.
x private olduğunda sentaks hatası. Access control hatası yani.
Access controlüde geçmesi için public olmalı.

class Myclass{
private:
		static int x;
};

int main(){
	Myclass::x = 10;  // ACCESS CONTROL HATASI ALINIR.
}



-------------------------------------------------

class Myclass{
public:
		static int x;
};

//cpp de x tanımlandı gibi düşün.

int main()
{
	Myclass m;
	Myclass *p = &m;

	Myclass::x = 50;       //geçerli

	p->x = 20;              //geçerli     BU ve altındaki kullanılınca nonstatic veri elemanı(aşağıdan devam)
	
	m.x = 10;               //geçerli     kullanılmış gibi oluyor.Okuyanı şaşırtabilir.SENTAKS HATASI DEĞİL.
						   //koda bakınca instance ın bir elemanına erişiyor hissi yaratıyor.x nonstatic gibi görünüyor
}						   //aslında biz classın static veri elemanına ulaşıyoruz.Herhangibir yaratılan nesne ile alaklı durum değil.
						   


----------------------------------------------------------------------

class Myclass{
	public:
	static int sa;
	int a;
};

int main()
{
	Myclass m;
	m.sa = 10; // SENTAKS HATASI YOK.Static veri elemanı bu şekilde kullanılıyor demek isteniyor.İnstance lada alakası yok.
	m.a = 20; // YİNE SENTAKS HATASI YOK.
}


Bu örnekte sadece sa ya erişmek için instance kullanıldı.
Static nesneyi scope resolution ile çağırmak mantıklı.Çünkü bir obje yaratmaya ihtiyaç yok.
Class ın kendisi ile alakalı bir değişken/fonksiyon static ile tanımlananlar. . ve -> için obje lazım.
obje yaratarakta static veriye yada fonksiyona erişilir ama çok anlamsız oluyor.

-------------------------------------------------------------------------

class Myclass{
	public:
	static int sa;
	void func()
	{
		sa = 12;
		Myclass::sa = 12; bunla arasında bir fark yok
		this->sa = 34; Burada da hata yok ama yanıltabilir.
	}
};

Üye fonksiyonlar isimleri doğrudan kullanabilirler.Private olsada kullanılabilir.

---------------------------------------------------------------------------

NELER STATIC VERİ ELEMANLARIDIR ? 
Öyle değişken olacakki instance ı değilde sınıfın genelini ilgilendirecek.
Yani hangi nesne olursa olsun aynı öğeyi kullanacak.

Bir alternatif ise CPP file da global bir değişken yapmak.
1- Bu durumda buna herkes erişir. Erişim kontrolü yok.
2- Class scope ta da olmamış olur bu değişken.

---------------------------------------------------------------------------

ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!

NOT: static keyword sadece bildirimde olacak.Tanımda değil.Yoksa hata alınır.

static int Myclass::sa{10}; //HATA


----------------------------------------------------------------------------

class Account{
private:
	double m_interest_rate; //herkese farklı faiz.
};


class Account{
public:
	static double m_interest_rate; //herkese aynı faiz.
};

Sınıfın tüm üye fonksiyonları ve global functionlar bunu kullanabilir. BUNU TEST ET.


STATIC VERI ELEMANLARININ BIR LOOKUP TABLE OLMASI ÇOK YAYGIN BIR DURUM
ÖZEL BIR DURUM YOKSA SINIFIN STATIC VERI ELEMANLARI MUTABLE OLACAKSA BUNU GIZLEMEKTE FAYDA VAR.
PUBLIC OLURSA HERKES DEĞIŞTIRIR, KONTROL ETMEK ZORLAŞABILIR.

READ ONLY OLARAK KULLANILACAKSA
BUNU PUBLIC YAPMAKTA BIR SAKINCA YOK.
BURADA CONST OLARAK TANIMLARIZ YADA CONSTREXPR ILE TANIMLAYABILIRIZ.COMPILE TIME SABITI = CONSTREXPR


--------------------------------------------------------------------------------------------------------

ÖRNEK.

class Myclass{
	Myclass() : x{234} { }	//SENTAKS HATASI. STATIC VERI ELEMANI CTOR INIT LIST ile init edilemez.
	static int x;			// zaten mainden önce hayata geliyor x.
};



--------------------------------------------------------------------------------------------------------

static veri elemanlarına default member init olmuyor.
class Myclass{

	static int x = 20;   //BURASI SENTAKS HATASI!!!! INCLASS INIT veya DEFAULT MEMBER INIT(C++ 11 de geldi) deniyor buna
			     //Burası Ctor init liste ekleniyordu hatırlarsak.Derleyici default ctora
	 		     //bunu ekler.Def Ctor çağrılırsa SENTAKS HATASI OLUŞUR.BU NONSTATIC VERİ ELEMANLARI
			     //İÇİN GEÇERLİ. STATICLER İÇİN DEĞİL.
};


BUNU UYGULAYABİLECEĞİMİZ YERLER VEYA KURALLAR
----------------------------------------------
1 - SINIFIN CONST OLAN VE INTEGRAL TYPE OLAN VERI ELEMANLARINA BU ŞEKILDE ILK DEĞER VERILEBILIR.
	
class Myclass{
	static int x = 10; // GEÇERSİZ
};

class Myclass{
	const static int x = 20; // GEÇERLİ
};

class Myclass{
	const static double dx = 2.0;  //GEÇERSİZ. TAMSAYI TÜRÜNDEN OLMADIĞINDAN GEÇERSİZ.
};

class Myclass{
	static constexpr int x = 10;  //GEÇERLİ
};

class Myclass{
	static constexpr double x = 2.3;  //GEÇERLİ
};



MOLA VERİLDİ

===============================================================================================================================
===============================================================================================================================
===============================================================================================================================
===============================================================================================================================
===============================================================================================================================

INLINE
------
C++ 2017 Bazı kuralları önemli ölçüde değiştirdi.
Burada değişen önemli bir eklenti Inline Variables.

ODR ve Inline function ları hatırlayalım.
Aynı kaynak dosyada aynı 2 tanım sentaks hatası, farklı kaynak dosyalarda aynı varlığın birden fazla tanımı doğrudan undefined behavior.
Eğer inline keywordünü yazarsak inline statüsüne girer yani link aşamasında linker bundan sadece 1 tane görecek ve ODR bozulmayacak

//.h
int x = 10;  
void func()   
{				// bu tanımlarda ODR ihlal ediliyor.ODR ihlal edilmesi Undefined behavior.
				// bildirim birden çok olabilir ama tanım tek olmalı.
}

Öyle varlıklar varki tanımlarının token by token aynı olması durumunda ODR ihlal edilmiyor.
Inline functions,class definition,Inline variables... tamamı değil ama bir kısmı

1. İstisna
//.h
class Myclass // BURADA UB OLUŞMUYOR.Çünkü Bu bir istisna.Projedeki diğer definitionlarla token by token aynı olmalı koşulu var.
{																						//zaten include edilince bu .h dosyası hepsi aynı olur

};

2. İstisna
// .h
inline void func( int x )  // Burada da function inline olarak tanımlandığı için ODR ihlal edilmedi. Yine token by token aynı olmalı
{																						//zaten include edilince bu .h dosyası hepsi aynı olur			
	x * x;
}

C++17 ye kadar sadece functionlar INLINE olabiliyordu.
C++17 de dile INLINE VARIABLES eklendi.

3. İstisna
//.h
int x = 20; //ODR ihlal edilir
inline int x = 35; // ODR İHLAL EDİLMEZ.Token by token aynı olursa diğer dosyadakiler sorunsuz çalışır.
					//zaten include edilince bu .h dosyası hepsi aynı olur

Bu şu demek

- Bunu yapmak yerine
//ali.h
extern int x;
//ali.cpp
int x = 20;

- Aşağıdaki şekilde yapmak daha mantıklı olabilir 
//ali.h
inline int x = 20;  TAMAMEN GEÇERLİ.Sadece header file da tanımlandı.


Burası Header Only library lerde avantaj sağlıyor.
Normalde modüller bir header ve bir kaynak file dan oluşuyor.Bu derleniyor ve biz bunun derlenmiş halini kullanıyoruz.

Header only de modülün kendisi doğrudan başlık dosyası halindedir.Bir kod file a gerek yok.

// .h
class{
public:
	inline static int sx = 10;
	void func()
	{
	}
	void foo()
	{
	}
};

inline foo()
{

}

Mesela yukarıda cpp file a gerek yok.

Eskiden header only library yi engelleyen, int g = 30; gibi global bir değişkenin header file da extern bildirimi
ve bunun için bir cpp de tanımının olması gerekiyordu.

Aynı durum sınıfın static veri elemanlarında da geçerliydi.Yukarıdaki örnekte sx mesela.Eğer "static int x;" olsaydı,
sx bir bildirim, bunun içinde cpp dosyasına ihtiyaç var.Bunu başlıkta tanımlasak ODR ihlal edilecekti.
ŞİMDİ ise hepsi inline olarak tanımlanabiliyor.Şuanda yazıldığı gibi. "inline static int sx = 10;" GEÇERLİ.

Yukarıda const olan integral type olanlar içinde ilk değer verilmesi gereken durumları yazmıştık ama
onlar inline değildi. Inline olunca sınıf türünden de değişken tanımlanabilir.Inline olan hertürden olabilir özeti. :D:D


ÖR:
#include <string>

class Myclass{
public:
private:
	static std::string str{"Alican"}; //SENTAKS HATASI
	inline static std::string str{"Alican"}; //SENTAKS HATASI DEĞİL C++17 de dile geldi. Öncesinde SENTAKS HATASI.
};


------------------------------------------------------------------------------------

CONSTEVAL
----------
consteval C++20 de geldi
Burada kastedilen compile timeda hesaplama.Konu constexpr funclar ile ilgili.
consteval ile tanımlanan funcların değeri kesinlikle compile time da elde edilmeli.
constexpr da compile/runtime olabilirdi.Burada seçenek bırakılmıyor.Sadece sabit ifadesi gönderilebilir.

NOT: HEM CONSTEXPR HEMDE CONSTEVAL FUNCTIONLAR IMPLICITLY INLINE !!!!!
	İNLİNE YAZSAKTA YAZMASAKTA HEADER İÇİNDE DOĞRUDAN TANIMLAMAK İNLİNE DEMEK !!!
	ANLAM FARKLILIĞIDA YOK 



constexpr örneği.
constexpr int foo(int, int)
{
	return x*x;
}
Bu fonksiyona yapılan çağrılarda func ın tüm parametresine gönderilen ifade constant expr ise
fonksiyonun değeri compile time da elde edilecek demek.

int main()
{
	
	foo(12,56);	//constant expr ler kullanıldı (12 ve 56) o yüzdne compile time da elde edilecek.
	
	int a = 23, b = 57;
	foo(a,b); // ifadeler constant expr olmadığı için hata değil ama compile time da elde edilmeyecek değeri.
	
}

-------------------------------------

consteval örneği

consteval int foo(int, int)
{
	return x*x;
}

int main()
{
	foo(23,55); //Burası geçerli zaten istenen bu

	int a = 23, b = 33;
	foo(a,b); //SENTAKS HATASI. Çünkü Constant expr kullanmak zorunlu consteval funclarda.
}


================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================




STATIC MEMBER FUNCTIONS
-----------------------
Sınıf içerisinde static keyword ile bildirilen functionlar.

Class scope içerisinde olan ve sınıfın private data memberslarına erişim hakkı olan fakat
this pointerı olmayan yani bir sınıf nesnesi için çağrılmayacak, bir sınıf nesnesinin örtülü olarak
adresini talep etmeyecek, instance ile ilgili olmayan ve sınıfın geneliyle ilgili olan functions.
Global func a alternatiftir.Class nesnesi için değil Class ın kendisi için var bu functionlar.


class Myclass{
	public:
	void foo(int); //nonstatic member func
	static void func(int); //static member func
};

int main()
{
	Myclass::foo(10); // SENTAKS HATASININ SEBEBİ İSİM ARAMA DEĞİL. Bu fonksiyon için bir myclass nesnesine ihtiyaç var
						// bu sebeple sentaks hatası

	Myclass m;	// foo aşağıdaki gibi çağrılır.Mutlaka nesneye ihtiyaç var.
	Myclass* = &m;
	m.foo();	
	p->foo(12);
}

int main()
{

	Myclass::func(12); // Bu şekilde çağrılabilir. Sınıf nesnesine ihtiyaç duymuyor.This Pointerları yok.
					   // sınıf nesnesi değil sınıf için çağrılıyor.Zaten this te yok.
}

NONSTATIC MEMBER FUNCTIONSTA GIZLI BIR SINIF TÜRDEN POINTER PARAMETRE EKSTRADAN VARDI.
STATIC MEMBER FUNCTIONSTA BU PARAMETRE YOK.Bu araç olmasaydi global functionslar kullanilabilirdi.
Global olmasiyla static member func olmasi arasindaki farkliliklar aşağidaki gibidir.


GLOBAL VS STATIC MEMBER
-----------------------
1- Global funclar namespace scope - Static Member funclar class scope
	Static member funclar ya :: ya . yada -> operatörleriyle kullanılmalı

2- Global funclar sınıfın private kısmına erişemez - Static Member funclar erişir
	
3- Global funclar access controle tabi değil - ... Static Member funclar access kontrole tabi.
	mesela static member func private olsaydı kullanılamayacaktı ama publicte kullanılır.


STATIC ÜYE FONKSIYONLAR NASIL TANIMLANIR
a - inline olarak tanımlanabilir
b - cpp file da implemente edilebilir.

// .h
class Myclass{
	static void foo(int x);
};

//.cpp
void myclass::void(int x)
{
	//... Böyle tanımlanabilir.TANIMLAMADA BAŞINA STATIC KOYARSAK SENTAKS HATASI OLUR.
}

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------


NOT : STATİC MEMBER FUNCLARIN BİR THİS PTR YOK VE BİR SINIF NESNESİ İÇİN ÇAĞRILMIYOR BU SEBEPLE
SINIFIN NONSTATİC VERİ ELEMANLARINI, SINIFIN STATİC ÜYE FUNCLARI İÇİNDE KULLANMAM SENTAKS HATASI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

1. Durum

// .h
class Myclass{
	static void foo(int x);
private:
	int a,b; // no static
};

void Myclass::foo()
{
	a = 10; //SENTAKS HATASI. Bu hata namelookup hatası değil.
}

Hata ŞU: 
Derleyici a ismini aradı ve bunun nonstatic veri elemanı olduğunu anladı.
Dolayısıyla bu bir Myclass nesnesine ilişkin olmalı, bu fonksiyon nonstatic member func olsaydı 
derleyici bu fonksiyon hangi nesne için çağrıldıysa onun a sı olarak alacaktı yani this->a olarak alacaktı.
Ama this pointer yok :D:D  Bu doğrudan sentaks hatası

ÖZET: Sınıfın static member funcları, nonstatic data membersları kullanamazlar.Çünkü this ptr yok.

------------------------------------------------------------------------------------------------------

2. Durum

class Myclass{
	void foo();
	void func();
	static void foo2();
private:
	int a,b;
};

void Myclass::foo()
{
	func(); //BURASI GEÇERLİ.

}


void Myclass::foo2()
{
	func(); // BURASI SENTAKS HATASI.Çünkü func nonstatic üye fonksiyon.this ptr var.Nesneye ile ilişkili ve nesne için çağrılıyor 
			// AMA ortada nesne yok :D:D.  foo2 ise static ve this ptr yok class ile ilişkili.

}



SONUÇ
-----
1 - SINIFIN STATIC MEMBER FUNC, SINIFIN NONSTATIC VERI ELEMANLARINI DOĞRUDAN ISMIYLE KULLANAMAZLAR.
2 - SINIFIN STATIC MEMBER FUNC, SINIFIN NONSTATIC MEMBER FUNCLARINI DOĞRUDAN ISMIYLE ÇAĞIRAMAZLAR.

NOT: CONST MEMBER FUNCLAR İLE KARIŞTIRMA
1 - CONST ÜYE FUNC.LAR İÇİNDE SINIFIN NONCONST VERİ ELEMANLARINI DEĞİŞTİREMEYİZ AMA ERİŞEBİLİRİZ (DERS 7)
2 - CONST ÜYE FUNC.LAR İÇİNDE SINIFIN NONCONST CONST OLMAYAN FUNC. LARINI ÇAĞIRAMAYAZ.
3 - CONST SINIF NESNELERİ İÇİN SINIFIN NONCONST ÜYE FOKSİYONLARI ÇAĞRILAMAZ.

ÖNEMLİ !!
SINIFIN VERI ELEMANLARI STATIC OLSAYDI VE ÇAĞIRDIĞI FONKSIYONDA STATIC OLSAYDI HIÇ HATA YOKTU.

ÖR:
class Myclass{
	static void foo();
	static void func();
private:
	static int a,b;
};

void Myclass::foo()
{
	func(); //BURASI GEÇERLİ.
	a = 20;  //BURASIDA GEÇERLİ.
}

----------------------------------------------------
ÖR:

ÖR:
class Myclass{
	static void foo();
	void func();
private:
	int a,b;
};

void Myclass::foo() // burada access control görevini yapıyor. this ptr ise aşağıdaki x ten gelecek 
{
	Myclass x;

	x.a = 20; // GEÇERLİ.
	x.func(); // GEÇERLİ.
}

AÇIKLAMA
----------
Static member func, nonstatic membersları kullanamaz derken, this olmadığı için kullanamaz dedik.
Burada Myclass x; ile bir tanımlama yapılmış. x e ait a ve func a gidilebilir. Burada static function,
access member dan geçilmesini sağlıyor. İsim arama başarılı ve erişim var.Bunu sağlıyor.this ise yeni tanımlanan x ten geldi


AŞAĞIDAKİ DE AYNI ŞEKİLDE GEÇERLİ.AYNI MANTIK.
---------------------------------------------

ÖR:
class Myclass{
	static void foo(Myclass x);
	void func();
private:
	int a,b;
};

void Myclass::foo(Myclass x)
{
	x.a = 20; // GEÇERLİ.
	x.func(); // GEÇERLİ.

	// NOT : BURADA THIS KULLANILAMAZ.STATIC MEMBER FUNCTA BÖYLE BİR PARAMETRE YOK.
}

-----------------------------------------------------------------------------------------------------------------------

ÖR:

SORU: CONST AŞAĞIDAKİ GİBİ BİLDİRİLSE, SENTAKS HATASI OLUR MU?

class Myclass{
	//static void foo()const;  //SENTAKS HATASI
private:
};

Static member func ın const olması sözkonusu değil. Çünkü buradaki const nonstatic member funclarda 
bu func ın gizli parametresi myclass * değilde const myclass* demektir. Static member func ın böyle bir 
parametresi olmadığından constta kullanılamaz.

-----------------------------------------------------------------------------------------------------------------------

class Myclass{
	//static void foo();  
private:
};

int main()
{
	Myclass m1,m2,m3;
	
	Myclass::foo() //geçerli.
	Myclass *p{&m1};

	m1.foo(); //geçerli.
	m2.foo(); //geçerli.
	m3.foo(); //geçerli.
	p->foo(); //geçerli.
}

ÖZETLE
------
m1,m2,m3 burada konu mankeni.Çağrılan static member func. Her seferinde aynı function.
Sınıfların static member funcları -> . veya :: operatörleri ile çağrılabilir


-------------------------------------------------------------------------------------------------------
ÖR:
class Myclass{
	static void foo();
	void func();
private:
};

int main()
{
	Myclass mx;

	mx.func(); // yanlışlıkla bunu foo yazarsak sentaks hatası olmaz ama bunun mx nesnesiyle alakasıda olmaz.
	
	mx.foo(); // Staticler nesne ile ilgili değildi.this yoktu.Class ile ilgili.Sentaks hatası yok ama mantıksal açıdan hata var.
		
}

// İSIMLERIN BENZER SEÇILMESI VEYA IDE LERDEKI INTELLISENSE ARAÇLARI BU HATALARI TETIKLIYOR.

---------------------------------------------------------------------------------------------------------------------------------------

STATIC VE NONSTATIC FUNCLAR AYNI ISIMLI OLUR MU ? EVER OLUR AMA GENELLİKLE MANTIKLI DEĞİL
Duruma Göre sentaks hatası oluşabilir ama doğrudan bir sentaks hatası değil.Parametreleri ile alaklı


class Myclass{
	static void func();
	void func();
private:
};

HATA VERDİ : Severity	Code	Description	Project	File	Line	Suppression State
Error	C2686	cannot overload static and non-static member functions with the same parameter types
12_12_06_2021	D:\CSD\C++\12_12_06_2021\12_12_06_2021\main.cpp	1309


-------------------------------------------------------------------------------------------------------

static member func ın çağrılmasını engellemek mümkün mü? böyle bir araç doğrudan yok.




*/

#include <iostream>

// new operatörü değil, operator new func overload ediliyor.


