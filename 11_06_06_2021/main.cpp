/*

COPY ELISION
------------

Ellision, elide fiilinin isim hali. bu kopyalamanın elemine edilmesi demek.
Kopyalamadan kaçınmak demek. Derleyici bazı durumlarda koda bakarak kopyalama gereken yerde daha etkin
bir kod üretmek için kopyalama kodu yerine, kopyalama yapmayan bir kod üretiyor.Buna Copy Elision deniyor.

C++ 2017 ye kadar bir optimizasyon tekniğiydi.Compiler belirli durumlarda bir optimizasyon yapıp kodu yeniden düzenliyordu
mesela copy ctor veya move ctor çağrılması gereken yerlerde bir optimizasyon ile bunları çağırmıyordu, böylece daha etkin bir 
kod üretiyordu.

C++ 2017 den sonra bu dilin kuralı haline geldi. Copy elision olmak zorunda.
2017 de MANDATORY COPY ELISION deniyor. Bu C++ 17 kuralları gereği yapmak zorunda olduğu kodsal düzenleme.

Bu classı buraya rahat kopyalamak için koyuyorum.
ÖR:
class Myclass{
public:
	Myclass()
	{
		std::cout << "Myclass()\n";
	}

	~Myclass()
	{
		std::cout << "~Myclass()\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x = "<< x << "\n";
	}

	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
};


COPY ELISIONDAN ÖNCE GEÇİCİ NESNELERE BAKILACAK.
-------------------------------------------------
Geçiçi nesnelere ve R-X Value Category ye giriş.

Bir grafik var mediumda ondan ilerliyoruz.Hatırlatma gibi oldu.
VALUE CATEGORY
Lvalue - PR Value - X value

PR value + X Value = R Value ==> Bu ifadeler taşıma semantiği ile taşınmasında bir problem olmayacak.
				Yani kaynak çalabilirim ve bir problem olmaz demek.Bu garantiyi vermesinin sebebi
				bu nesnenin artık başka bir kod tarafından kullanılmayacak oluşu.

Lvalue ise bellekte bir yere karşılık geliyor demek.

Not : Compiler, sınıf türden nesnelerin r value olup olmadığını anlıyor çünkü bu compile time da elde ediliyor.

BIZIM SINIF TÜRDEN RVALUE EXP OLUŞTURMA TÜRLERIMIZ.

ÖR:
Myclass func();
int main()
{
	func(); // burası PR Value expr.Yani taşınabilir nesneye karşılık geliyor.
}		// sözkonusu nesneyi başka bir nesnenin kullanma ihtimali yok, bu kaynak çalınabilir.


ÖR:
Myclass&& func();
int main()
{
	func(); // Func geri dönüş değeri sağ taraf referansı. Bu ifade X value expr.Buda R value exp demek. Kaynak çalınabilir.
}


ÖR:
int main()
{
	Myclass m;
	std::move(m); // Burası X value exp yani R value expr.Kaynak yine çalınabilir.	
}


============================================================================================================
============================================================================================================


Geçici Nesneler(Temporary Objects)
----------------------------------
Kısaca temporary de deniyor.

Ne değildir ?
Bazı değişken isimleri temp olabiliyor. Bu temporary object değil.
Adam swap func yazarken temp diyor değşkene. o temp bu temp değil :D:D

Temporary Object ayrı bir kategori.
Öyle bir nesneki kaynak kodda bir isme sahip değil ama yinede o bir nesne.
C++ dili temp nesnelere özel kuralları var.Temp objects Pr value expression.

Geçici nesneler bilerek isteyerek özel bir sentaks ile oluşturulabiliyorlar.

Sentaks:
SınıfTürü( Ctora gönderilecek argüman veya argümanlar ) 
SınıfTürü{ Ctora gönderilecek argüman veya argümanlar }

---------------------------------------------------------

class Myclass{
public:
	Myclass()
	{
		std::cout << "Myclass()\n";
	}

	~Myclass()
	{
		std::cout << "~Myclass()\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x = "<< x << "\n";
	}

	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
};

int main()
{
	std::cout <<"main basladi\n"

	Myclass(10); // bu bir geçici nesne.Bir ifade içinde kullanılıyor.
		     // ifadenin çalıştırılması süresinde kullanılıyorlar.Yani ; e kadar denebilir.

	std::cout << "Main devam ediyor\n";
}

ÇIKTI:
main basladi
Myclass(int x) x = 10
~Myclass()
Main devam ediyor

Çıktısına bakınca Myclass(10) bir constructor çağırıyor.
ifade yürütültüğü sürece yaşıyor.ifade bitince(; e kadar) nesnenin hayatıda bitiyor yani destructor çağrılıyor

------------------------------------------------------------------------------------------------------------------

Aynı şekilde
Myclass(); buda default ctor çağırdı. geçici nesnedir.bitince destructor
Myclass{}; value initte edilebilir.
Myclass{10}; aynı şekilde.

GEÇICI NESNELER PR VALUE EXPRESSIONDUR !!!!!!!!!!!!!!!!!!!!!!!!!!

Yani bu ifadeyi bir functiona argüman olarak gönderebiliyoruz.

void f1(Myclass);
void f2(const Myclass&);
void f3(Myclass&&);
void f4(Myclass&);

int main()
{
	std::cout << "main basladi\n";
	f1(Myclass{});
	f2(Myclass{});
	f3(Myclass{});	 YUKARIDAKİLERDEN HİÇBİRİ SENTAKS HATASI DEĞİL.

	f4(Myclass{});   BURASI SENTAKS HATASI.KURALLARDAN GELİYOR.
	std::cout << "main devam ediyor\n";
}

BUNLARI NEDEN YAPALIM:
Daha etkin kod ve scope leakage engellemek.

---------------------------------------------------

Geçici nesne olmasa
int main()
{
	std::cout << "main basladi\n";
	Myclass m{12};
	f1(m);

	std::cout << "main devam ediyor\n";
}

Yukarıda m main bitene kadar yaşıyor.
Scope leakage var. Bunu engelliyor geçici nesneler.
C++ ta bu kaliteli kod oluşturmanın yollarından biri.

---------------------------------------------------

Geçici nesne kullanırsak

int main()
{
	std::cout << "main basladi\n";

	f1(Myclass {12});

	std::cout << "main devam ediyor\n";
}


----------------------------------------------------

İSTİSNA 1:
Eğer bir geçici nesneyi(prvalue), bir referansa bağlarsak,
o ifadenin yürütülmesi bitse dahi nesnenin hayatı devam ediyor.
BUNA LIFE EXTENSION DENIYOR.

ÖR:
int main()
{
	std::cout << "main basladi\n";

	const Myclass &r = Myclass {};

	std::cout << "main devam ediyor\n";
	getchar(); // bekletmek için
}

Normalde ifadeden sonra geçici nesne Myclass{} nin hayatı bitecekti.
Destructor çağrılacaktı ama çağrılmadı. Burası istisna.
Hayatı ne zaman bitecek ? Referans olan ismin scope u sonlandığında, 
bu referansa bağlanan geçici nesneninde hayatı bitecek.Örnek 1 örnek sonra

ÇIKTI
-----
main basladi
Myclass()
main devam ediyor

~Myclass()

------------------------------

İSTİSNA 2:

int main()
{
	std::cout << "main basladi\n";

	Myclass &&r = Myclass {}; // DİKKAT

	std::cout << "main devam ediyor\n";
	getchar(); // bekletmek için
}

Sağ taraf referansında da aynı şekilde hayatı bitmiyor.

ÇIKTI
-----
main basladi
Myclass()
main devam ediyor

~Myclass()

--------------------------------------------------------------

Hayatı ne zaman bitecek ?
Referans olan ismin scope u sonlandığında,
bu referansa bağlanan geçici nesneninde hayatı bitecek.


int main()
{
	std::cout << "main basladi\n";

	{
		Myclass &&r = Myclass {}; // DİKKAT
	}   // r referansının hayatı bitince geçici nesnede ölüyor.
	    // hem const Myclass &r hemde Myclass &&r için geçerli.

	std::cout << "main devam ediyor\n";
	getchar(); // bekletmek için
}

Not : Narrowing conversionu engelleme burada da kullanılabilir.
Not : Bazı durumlarda compiler implicitly geçici nesne oluşturuyor zaten.Görülecek

======================================================================================================
======================================================================================================
======================================================================================================
======================================================================================================

ŞİMDİ COPY ELLISION DAN DEVAM
-----------------------------

1. MANDATORY COPY ELLİSİON DURUMU.
----------------------------------

class Myclass{
public:
	Myclass()
	{
		std::cout << "Default Ctor\n";
	}

	~Myclass()
	{
		std::cout << "Destructor\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x = "<< x << "\n";
	}

	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
};


void func(Myclass x)
{
	std::cout <<"func cagrildi\";
}


int main()
{
	Myclass mx; // burada default ctor çağrılacak.

	func(mx); // burada copy ctor çağrıldı. 
}

ÇIKTI
-----
Default Ctor
copy ctor
func cagrildi
Destructor
Destructor


BURAYA DİKKAT !!!!!!!!!!!!!!!!
int main()
{
	func(Myclass()); Geçici nesne yazıldı. Ama Burada func(mx) te olduğu gibi
			 Copy Ctor çağrılmadı. Default Ctor çağrıldı.
			 sınıfın move ctoru yok.tablodan baktık.
		 	 Buradaki durum Copy Elision.

}

ÇIKTI
-----
Default Ctor . BURAYA DİKKAT !!!!! Geçici nesne argüman olduğundan copy değil, default ctor çağrıldı !!!!!!!!!!!!!!!!!!
func cagrildi
Destructor

Buradaki duruma COPY ELLISION deniyor.
--------------------------------------
Assembly olarak,
Parametre değişkeninin yaratılacağı memory alanı stackte belli.Derleyici koda bakıyor ve
kopyalamak yerine buradaki geçici nesneyi parametre değişkeni için stackte ayrılan 
bellek alanına oluşturuyor. Ekstra kopyalama önleniyor.

C++17 öncesinde Compiler optimization ile mümkündü,
Şimdi kural olarak geldi. Mandatory Copy Elision deniyor.

Mandatory mi ?  değil mi ? test için aşağıdaki yapılabilir.
visual studio da Debug modda optimizasyon minimize ediyor.  
Standartları 17 öncesine çekip debug moda çekersek optimizasyon yapmayabilir.

Ama 17 den sonra artık bu kural, Kesin yapacak.

---------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------

MOVE CTOR YAZIYORUZ

class Myclass{
public:
	Myclass()
	{
		std::cout << "Default Ctor\n";
	}

	~Myclass()
	{
		std::cout << "Destructor\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x = "<< x << "\n";
	}

	Myclass(Myclass&&)
	{
		std::cout << "Move Ctor\n";
	}

	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
};

void func(Myclass x)
{
	std::cout <<"func cagrildi\";
}

int main()
{
	func(Myclass(23)); Move Ctor var ama yine çağrılmadı.Mandatory Copy Ellision Yapılacak
}						Move ctorun olması mandatory copy ellisionu etkilemedi.


MOVE CTORU DELETE ETTİK AMA HATA VERMEDİ.
ÇÜNKÜ MANDATORY COPY ELLISION VAR.

-------------------------------------------------------------------------------------------------------

Myclass x = Myclass{}; BURADA DA DEFAULT CTOR ÇAĞRILDI.

func(Myclass(Myclass(23)));  BURADA HALEN MAND. COPY ELLISION ÇALIŞACAK.

SONUC:
FONKSIYONUN PARAMETRESI SINIF TÜRÜNDEN, BU GEÇICI NESNE ILE ÇAĞRILDIĞI ZAMAN BİR CTOR
ÇAĞRILMASI YERINE DEFAULT CTOR ÇAĞRILIYOR.


-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------

2. MANDATORY COPY ELLISION DURUMU.
----------------------------------

RETURN VALUE OPTIMIZATION
-------------------------

Aynı class tanımı varmış gibi kabul et.

Myclass func()
{
	return Myclass{}; // Burada da geçici bir nesneyi return value ya kopyalama işlemi var normalde.
}

int main()
{
	Myclass x = func(); 
}

BEKLENTI
Önce return ifadesi olan gecici nesne için default ctor çağrılması.
Sonrada maindeki değşken için copy ctor çağrılması.

AMA ÖYLE DEĞİL
Derleyici aslında func return değerinin bellek alanını bildiği için, x nesnesini func ın return değerinin
tutulacağı yerde oluşturdu.Kopyalama yine elemine edildi. c++ 17 ye kadar optimizasyon, C++ 17 den sonra ise KURAL.

ÇIKTI
Default Ctor
Destructor

Bunlar Mandatory Copy Ellision.Move Ctor yazsaydım çağrılmayacaktı, delete etseydim yine sentaks hatası yoktu.
Exception Handling de de var bu.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

3. MANDATORY COPY ELLISION OLMAYAN DURUM
----------------------------------------

NAMED RETURN VALUE OPTIMIZATION - NRVO
--------------------------------------
İsimlendirilmiş geri dönüş değeri optimizasyonu.
BURADA OPTIMIZATION MANDATORY DEĞIL.

Visual Studio Release Modda

Myclass func()
{
	std::cout << "func cagrildi";
	Myclass mx;
	std::cout << "func devam ediyor";
	//..

	return mx;
}

int main()
{
	std::cout << "main basladi\n";
	Myclass x = func();
}

ÇIKTI - Optimizasyon var- Release Mode
-------------------------------------
main basladi
func cagrildi
Default Ctor
func devam ediyor
Destructor


ÇIKTI- Optimizsyon Yok - Debug Mode
-----------------------------------
main basladi
func cagrildi
Default Ctor
func devam ediyor
copy ctor // Move ctoru classtan bu örnek için sildim.Yoksa move ctor geliyor.func sağ taraf değeri. myclass return ediyor.
Destructor
Destructor


bunda move ctor koyduk, Bu seferde Move Ctor çağrıldı.
Myclass x = func(); func sağ taraf değeri olduğu için 

----------------------------------------------------------------------------------------------------------------------------

Birde delete edip yazdı. Delete edince 

Class a alttakini ekle.

Myclass(Myclass&&) = delete;

Myclass func()
{
	std::cout << "func cagrildi\n";
	Myclass mx;
	std::cout << "func devam ediyor\n";
	//..

	return mx;
}

int main()
{
	std::cout << "main basladi\n";
	Myclass x = func();	// debug modda optimizasyon yapmayacak ve move ctoru çağırır. MOVE CTOR DELETE EDİLDİĞİ İÇİN SENTAKS HATASI.

}
SENTAKS HATASI.

------------------------------------------------------------------------------------------------------------------------------

NOT:

#include <string>
std::string foo();

int main()
{
	std::string s = foo(); // fonksiyon geri dönüş değeri bir tür.Yani Rvalue exp. Bu durumda Move ctor çağrılır.
						// Bunlar kullanılıyor.
}


=====================================================================================================================
=====================================================================================================================
=====================================================================================================================
=====================================================================================================================

MOLADAN SONRASI
Ders başında Mandatory copy ellision konusuna girildi.


CONVERSION CONSTRUCTOR
----------------------

class Myclass{
public:
	Myclass();
	Myclass(int);
};

int main()
{
	int ival = 10;
	Myclass m;

	m = ival;  Sentaks Hatası Yok. Myclass(int) olmadan önce vardı.
}		       ama yazdıktan sonra HATA YOK.Compile edince hata yok. 
			   Run edince hata verdi çünkü tanımları yok, bildirimler var sadece.																						   


Derleyici Myclass(int) bunun varlığına güvenip,
aşağıdakini yazıyor

- Önce sınıfın int parametreli ctorunu kullanarak geçici nesne oluşturur.
- Sonra bu geçici nesneyi m değişkenine atamak için sınıfın COPY ASSIGNMENT
fonksiyonunu kulanıyor

m = ival; yazdığımız yerde

m = Myclass{ival};  Derleyici bunu anlıyor

Bunu Myclass(int); Ctoru yapıyor. Buna Conversion constructorda denir.
Kendi amacından başka bir amaca daha hizmet veriyor. Tür dönüşümü yapıyor
adeta. Bunu implicit olarak yapıyor. Geçici nesne oluşturduğunu unutma.

---------------------------------------------------------------------------

Yazdırarakta görürüz.

class Myclass {
public:
	Myclass()
	{
		std::cout << "default ctor this : " << this << "\n";
	}

	~Myclass()
	{
		std::cout << "destructor this : " << this << "\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x : " << x << " - this = " << this << "\n";
	}
};

int main()
{
	int ival = 10;
	Myclass m;

	m = ival;

	std::cout << "main devam ediyor";
}

Burada int parametreli ctor kopyalama işini yapıyor.
m = ival de, düşük seviyede yaratılan geçici nesne m ye atanıyordu.Bunu biliyoruz.
m = ival; adımından sonra bu geçici nesnenin hayatı bitecek.
Yani destructor çağrılacak.

ÇIKTI
-----
default ctor this : 003BFDA7  // m hayata geldi.
Myclass(int x) x : 10 - this = 003BFCDB  // Geçici nesne yaratıldı.Bunu m = ival adımında implicit yaptı.Adreste farklı,
					 // Bu nesne, m değil.Temp nesne.Bu geçici nesneden sonra COPY ASSIGNMENTTA ATAMA İŞLEMİNİ YAPAR.
					 // Bu copy assignment derleyici tarafından default edilen. İstersek kendimizinkini yazarız ve o çağrılır.
destructor this : 003BFCDB		 // geçiçi nesnenin hayatı burada bitiyor.
main devam ediyor 
destructor this : 003BFDA7

--------------------------------------------------------------------------------------------------------------------

YUKARIDA BAHSEDİLEN COPY ASSIGNMENT BURADA YAZILACAK VE IMPLICIT OLARAK ÇAĞRILACAK

class Myclass {
public:
	Myclass()
	{
		std::cout << "default ctor this : " << this << "\n";
	}

	~Myclass()
	{
		std::cout << "destructor this : " << this << "\n";
	}

	Myclass(int x)
	{
		std::cout << "Myclass(int x) x : " << x << " - this = " << this << "\n";
	}

	Myclass& operator=(const Myclass& other)
	{
		std::cout << "copy assignment this : " << this << " - &other = "<< &other << "\n";
		return *this;
	}
};

int main()
{
	int ival = 10;
	Myclass m;

	m = ival;

	std::cout << "main devam ediyor\n";
}

ÇIKTI
-----
default ctor this : 00EFF987
Myclass(int x) x : 10 - this = 00EFF8BB
copy assignment this : 00EFF987 - &other = 00EFF8BB
destructor this : 00EFF8BB
main devam ediyor
destructor this : 00EFF987

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

SONUÇLAR:

A - Compiler ne zaman int, myclass türünden bir değişkene dönüşmesi gerekiyorsa, bu durumdan vazife çıkaracak,
Myclass(int); Constructor ile geçiçi nesne yaratıp daha sonra da Copy Assignment/Move assignment func ile atama yapacak.

	Neler Dahil
	---------------
	1 Myclass mx;
	  mx = 10;  Conversion Ctor(CC) geçerli.

	2 void func(Myclass x);
	  int main()
	  {
		func(12); fonksiyona argüman olarak gönderince de Conversion Constructor geçerli
	  }

	3 void func(const Myclass &r);
	  int main()
	  {
		func(12); Burada da geçerli.
	  }

B - Bu Hayırlı bir durum mu ?
	ÇOK TEHLİKELİ BİR DURUM BU ÇÜNKÜ FARKINDA OLMADAN HATALI BİR CONVERSİON TETİKLENEBİLİR.
	Myclass mx;
	Myclass my;

	int i{};
	mx = i;  kural olmasa sentaks hatası. Kurallardan ötürü hatalı bir işlem yapsak bile atama olabilir.

C - Bu dönüşüm sadece int ler için mi geçerli ?
	double dval = 23.3;
	Myclass mx;
	mx = dval;  BURASI GEÇERLİ. DAHA TEHLİKELİ.

	NEDEN ?
	User Defined Conversion

--------------------------------------------------------------------------------------------------------

USER DEFINED CONVERSION
------------------------
Normalde dilin kurallarına göre olan bir dönüşüm değil fakat,
dilin kuralları bazı fonksiyonların varlığı durumunda bu fonksiyonlara yapılan çağrıyla bu
dönüşümün olmasını sağlıyor.Böyle dönüşümlere User defined conversion deniyor.

User Defined Conversion 2 ye ayrılıyor.
	Conversion Constructor
	Type-cast Operator Function

Standart Conversion 
Zaten var olan dönüşümler. 
Ör int --> double 


KURAL
Eğer bir dönüşüm aşağıdaki gibi olabiliyorsa

Standart dönüşüm + User defined dönüşüm  derleyici bu dönüşümü gerçekleştrmek zorunda.Conversion Ctor
User defined dönüşüm + Standart dönüşüm  Aynı şekilde bunuda gerçekleştirmek zorunda. Conversion Ctor

ÖR
double dval = 23.3;
Myclass mx;
mx = dval;   // Bunun olması için önce dval in int e sonra da, intten de Myclass türüne dönüşüm olmalı.
	     // standart conversion ile double dan int e, sonrada User defined conversion ile int ten Myclass
	     // türüne sınıfın conversion ctor ının çağrılmasıyla dönüşüm gerçekleşiyor.
	

Yani Myclass(int); yanlışlıkla bir dönüşüme sebep olabilir.
int e dönüşen tüm ifadelerin myclass türüne dönüşmesini sağlayacak.

ÖR:
Myclass mx;
bool is_ok{true};
mx = is_ok;  GEÇERLİ YİNE. KURALA GÖRE GEÇERLİ ÇÜNKÜ.
			  true 1 e dönüşüyor(standart conver.), 1 de myclass türüne dönüşüyor.(user defined conver)

ÇIKTI:
------
default ctor this : 00AFF75B
Myclass(int x) x : 23 - this = 00AFF68F
copy assignment this : 00AFF75B  other = 00AFF68F
destructor this : 00AFF68F
destructor this : 00AFF75B


ÖR:
Myclass foo()
{
	int ival {2143};
	return ival;
}

void func(Myclass);

int main()
{
	int ival{};
	double dval{};

	func(ival);
	func(dval);
}
	HİÇBİR HATA YOK. SADECE CONVERSION LOSS OF DATA UYARISI GELİR.
	BURASI HAYIRLI BİR DÖNÜŞÜM DEĞİL :D:D

BAZI SINIFLARIN BUNU IMPLICIT OLARAK YAPMASI TERCIH EDİLİYOR.
MESELA STRING SINIFI, İLERİDE GÖRÜLECEK, SINIFIN CTORLARINDAN BİRİ AŞAĞIDAKİ GİBİ

class string{
	string(const char *);
};

STRİNG TÜRÜNDEN BİR NESNEYE CONST CHAR * TÜRÜNDEN BİR İFADE KOPYALANDIĞINDA BİZ BUNU IMPLICIT OLARAK
YAPILMASINI TERİH EDERİZ.COMPILERDA BUNU CONVERSION CTOR DAN ÖTÜRÜ CONVERT EDECEK.

int main()
{
	string str;
	str = "Ali bak ali";   ATAMA LEGAL. const char * dan string e.
							BÖYLE DURUMLARIN SAYISI ÇOK AZ.
}

C++ TA CONVERSION CTOR BAŞIMIZI BELAYA BU DURUMDAN ÖTÜRÜ SOKMASIN DİYE BİR ARAÇ VAR.
ADI EXPLICIT CONSTRUCTOR

===============================================================================================================
===============================================================================================================


EXPLICIT CONSTRUCTOR
--------------------
Explicit constructor, sadece ctorların özel bir keyword ile tanımlanması durumunda kazandığı nitelik.
Buda explicit keyword ile oluyor.

class Neco{
public:
	explicit Neco(int); // Explicit constructor
};

fonksiyon inline yazılıyorsa explicit keyword bulunmalı.
Sınıfın dışında yazılıyorsa explicit keywordü definitionda yazmak hata, yine class içindeki declerationda yazılır.

NE İŞE YARAR.
explicit iyi seçilmiş keyword değil aslında. Implicitin tersi idi.
Sınıfın conversion ctorunu explicit olarak bildirirsek, Bu ctor tür dönüşümü yapar ama explicit olarak yapar.
Daha önceki tehlikeli olan implicit conversionu engeller. Explicit olarak yapmaya zorlar.Yani type-casting ile yapacaz.

class Neco {
public:
	Neco() = default;
	Neco(int x);
};


int main()
{
	Neco nec;
	int ival{ 123 };
	nec = ival;		//BURADA HATA YOK.
}

ŞİMDİ EXPLİCİT KEYWORD YAZALIM

class Neco {
public:
	Neco() = default;
	explicit Neco(int x);
};


int main()
{
	Neco nec;
	int ival{ 123 };
	nec = ival;		//SENTAKS HATASI
}

ŞİMDİ DE STATIC_CAST İLE DENEYELİM.

class Neco {
public:
	Neco() = default;
	explicit Neco(int x);
};


int main()
{
	Neco nec;
	int ival{ 123 };
	nec = static_cast<Neco>(ival);		//GEÇERLİ.BUNU YAPMAYA ZORLUYOR ZATEN
}
Yukarıda ival dval li örnekte explicit ine tanımlansaydı ctor, hepsi hata olurdu.

BENCE OLAY ANLAŞILDI

-----------------------------------------------------------------------------------------

ör:
void func(Myclass)
{

}

int main()
{
	func(12); 12 geçici nesne olduğu için Mandatory Copy Ellision var.
	func(Myclass{}); Bu da geçici nesne. Özel sentaks ile yapıldı.Gördük bugün.
}

---------------------------------------
Vector Örneği yaptı 2:26 - 2:27
---------------------------------------

int x; default
int y(10); direct 
int z{}; value 
int t{10}; direct list
int m = 64; copy init

----------------------------------------


class Nec {
public:
	Nec();
	explicit Nec(int);
};


int main()
{
	Nec nec = 200;  // Eğer bu dönüşümü yapan function explicit olarak belirtilirse, copy init geçersiz hale geliyor.
					// Sentaks hatası. Burada da aslında copy ellision var hata olmasaydı.
}

ÖNEMLİ:
EĞER BU DÖNÜŞÜMÜ YAPAN FUNCTION EXPLICIT OLARAK BELIRTILIRSE, COPY INIT GEÇERSIZ HALE GELIYOR.
TEST ETTİM. COPY INIT DERKEN BİR İNT SAYIYA ATAMA OLMUYOR. YİNE AYRI TÜRDEN OBJEYLE İNİTİALİZATİON VAR.
ÖR:
	Myclass x;
	Myclass y = x; BURASI GEÇERLİ.

	Myclass x;
	Myclass y = 23; BURASI GEÇERSİZ.



GENELDE SINIF TÜRLERININ TEK PARAMETRELI CTORLARI EXPLICIT ILE TANIMLANMIŞ.

-----------------------------------------------------------------------------------------------

unique_ptr<int> uptr(new int);  GEÇERLİ.SINIFIN CTORUNA ARGÜMAN OLARAK GÖNDERILIYOR.
unique_ptr<int> uptr = new int; BURASI SENTAKS HATASI ÇÜNKÜ POINTER PARAMETRELI CTOR EXPLİCİT

------------------------------------------------------------------------------------------------

class Myclass{
public:
	explicit Myclass(int);
	Myclass(double);
};

int main()
{
	Myclass x = 10; // EXPLICIT VIABLE OLMASINI BOZUYOR BIR FONKSIYONUN. SENTAKS HATASI YOK. 2. ÇALIŞIR.
}					// ARTIK 1. OVERLOAD SETTE DEĞIL.



========================================================================================================================================================
========================================================================================================================================================
========================================================================================================================================================
========================================================================================================================================================
========================================================================================================================================================



DİNAMİK ÖMÜRLÜ NESNELER
------------------------

Static Storage Class
Automatic Storage Class
Dynamic Storage Class

------------------------

Hayata istenildiği zaman getirilip istenildiği zaman bitirilen nesneler dinamik ömürlü nesnelerdir.

Yakında classların static ömürlü değişkenlerini göreceğiz.

Dinamik ömürlü nesneler ile dinamik bellek yönetimini çok karıştırıyorlar.
Dinamik bellek yönetimi, allocate edilen bellek bloklarının runtime da yapılması demektir.

malloc dinamik ömürlü nesnenin memorydeki yerini temin ediyor.

------------------------------------------------------

C++ ta ise dinamik ömürlü nesneyi oluşturan operatörler var.
Mantığı C ile aynı.
Zorunda değilsen dinamik ömürlü nesne oluşturma.
Normalde otomatik ömürlü kullanırız, mecbur kalırsak dinamik ömürlü kullanırız

Neden?
1 - Dinamik ömürlüler çok daha yüksek maliyetli.
2 - Kullanımı otomatik ömürlüye göre daha zor, hata yapmak daha kolay.
3 - Test-Debug-Değişiklik daha zor.


-----------------------------------------------------------------------------

Nasıl oluşturulur?

NEW OPERATÖRÜ
-------------
-C++'ta Dinamik ömürlü nesne oluşturan operatorler var. Bunlara new operatörleri deniyor. 1 den fazla var bunlardan.

Standartlar new expression diyor. Ama insanlar operator olarak kullanıyor.

-Dinamik Ömürlü nesnenin hayatını nasıl sonlandırırız?
delete operatörleri ile. functionların delete edilmesindeki delete keyword ile alakası yok.
overload etmişler keywordü.

SENTAKS
-------
new istenen_tür 

new Myclass
new int
new vector<int>

new ile oluşturulan ifadeler birer pointer.Hayata başlamış nesnenin adresi.
mesela new Myclass ın türü Myclass *

class Myclass{};

int main()
{
	Myclass *p = new Myclass;
	Myclass *p(new Myclass);
	Myclass *p{ new Myclass };  

	auto p = new Myclass;
	auto p(new Myclass);
	auto p{new Myclass};  HEPSİ GEÇERLİ

}


-----------------------------------------------

ÖR:

class Myclass {
public:
	void func();
	void foo();
private:
	char buffer[100];
};


int main()
{
	auto p = new Myclass;
	p->foo();
	p->func();

	delete p;
}

DERLEYICI NEW VE DELETE YAZDIĞIMIZDA NASIL BIR KOD ÜRETIR.
----------------------------------------------------------
Burada ihtiyaç duyulan bellek bloğunun büyüklüğü sizeof myclass kadar.
Derleyici C++ ın standart bir fonksiyonuna bir çağrı yaparak bu yeri elde ediyor.Malloc değil.
Burada çağrılan function, operator new.

void * operator new(size_t n); C++ ın global functionu. Mallocla aynı parametrik yapıda

new Myclass yazıldığında, derleyici ürettiği kodda ismi operator new olan functiona çağrı yapıyor. 
Bu functiona argüman olarak new ifadesinin operandı olan sınıf türününü sizeof değeri geçiyor.

//new Myclass
//operator new(sizeof(Myclass))
//operator new başarısız olursa std::bad_alloc türünden exception throw ediyor.
//başarılı olursa derleyici void * türden adres elde eder.
//derleyici operatör new den aldığı adresi Myclass * türüne dönüştürüyor.
// ve bu adreste Constructoru çağırıyor.

Neden Malloc çağrılmıyor.?
Malloc exception handlingden anlamaz. C fonksiyonu.
C++ ta operator new functionu kullanmak mantıklı.

NOT:
new operator ile operator new functionu ayrı şeyler.

New operatörü kullanıldığı zaman, önce operatör new fonksiyonunun çağrılmasını, dinamik bir bellek bloğunun
elde edilmesini, ve bu dinamik bellek bloğunun adresinin, nesnenin adresi olmak üzere this pointer olarak kullanılıp
sınıfın CTORUNA çağrı yapılmasını sağlıyoruz.



-------------------------------------------------------------------------------------------------

class Myclass {
public:
	Myclass()
	{
		std::cout << "Myclass default ctor\n";
	}
};


int main()
{
	Myclass *p = new Myclass; // Ctor çağrıldı ama Destructor çağrılmadı, Delete etmek gerekecek sonunda.

	//..

	delete p; //Bunlar ayrı ayrı fonksiyonlarda olabilir. Memory Leak olmaması çok önemli tabi.
}


DELETE P; YAZILINCA DERLEYICI NASIL BIR KOD ÜRETIR
----------------------------------------------------
Önce delete operatörünün operandı olan adresini this pointerı olarak kullanıp sınıfın destructorunu çağırır.
Burada operator delete isimli function çağrılıp bellek adresi geri verilmeli.

void operator delete(void *);

memory yi heap e geri veriyor.

psudo code
//p->~Myclass();
//operator delete(p);

yine delete operator ile operator delete functionu farklı

Sınıf nesnesi oluştururken malloc calloc realloc free kullanma.
Dİğer işlerde kullanabilirsin.


ÖR:

class Myclass {
public:
	Myclass()
	{
		std::cout << "Myclass default ctor\n";
	}

	~Myclass()
	{
		std::cout << "Myclass Destructor\n";
	}
};

int main()
{
	std::cout << "1\n";
	Myclass *p = new Myclass;
	std::cout << "2\n";
	delete p; //Bunlar ayrı ayrı fonksiyonlarda olabilir. Memory Leak olmaması çok önemli tabi.
	std::cout << "3\n";
}

ÇIKTI:
1
Myclass default ctor
2
Myclass Destructor
3

ÇOOK ÖNEMLİ!!!!!!!!!!!!!
----------------------------------------------------------------------------
Nesne delete edilmezse, destructor çağrılmamış olur ve hayatı bitmemiş olur.
Birtakım kaynaklar geri verilmemiş olur. Buna Resource Leak deniyor.

Bir problem daha var. delete ile hayatını sonlandırmazsam, operator delete functa çağrılmayacak.
Yani operator new le ayrılan sizeof myclass kadar bellek bloğu allocate edilecek ama deallocate edilmeyecek.
Memory leak oluşacak 1. dezavantaj

hem destructor çağrılmıyor 
hemde delete çağrılmamış oluyor. 2 adet dezavantaj.



*/

#include <iostream>


int main()
{
	
}
