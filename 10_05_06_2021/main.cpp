/*

KISACA COPY CTOR ÖZET YAPTI

İDEALİ COPY CTORU COMPİLERIN YAZMASI
VERİ ELEMANLARI POİNTER İSE SORUN ÇIKIYOR.
POINTER DANGLING HALE GELİYORDU.

GEÇEN DERS YAZILAN SINIF
--------------------------
class Sentence {
public:
	Sentence(const char* p);
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


SONRADA COPY ASSIGNMENT SPECIAL FUNCTIONA GELMİŞTİK.
BU BİR CONSTRUCTOR DEĞİLDİ.
İKİ SINIFIN BIRBIRINE ATANMASINI SAĞLAYAN FUNCTIONA COPY ASSIGNMENT FUNCTION DENIYOR
Fonksiyonun adı "operator="

Derleyici aşağıdakini yazar.
----------------------------
class Myclass {
public:
	Myclass& operator=(const Myclass& other)
	{
		ax = other.ax;
		bx = other.bx;

		return *this; 	nesnenin kendisini return ediyor.
	}
private:
	A ax;
	B bx;
};

m1 = m2;
m1.operator=(m2);  İkiside aynı.


Eğer pointerlar varsa yine sorun oluşabilir.


ÖR:
int main()
{
	Sentence sx{ "Bugun Cumartesi" };
	sx.print();

	if (...)
	{
		...
		Sentence a{ "Necati hoca C++ anlatiyor" };
		a.print();
		a = sx;			İŞTE BURADA HATA OLUŞACAK.BLOK BİTİMİNDE free ediliyor zaten a,
	}					AMA a aynı zamanda sx e eşitlendi ve aynı pointerı bir daha free
						etmeye çalışacağı için.UNDEFINED BEHAVIOR.Aynı zamanda ilk
						adreste tutulan dinamik memoryu bloğu da kaybedildi ve free
						edilmeden adres kaybedildi. MEMORY LEAK !!!!!

	sx.print();  // UB artık burası

}


UNDEFINED BEHAVİOR VE MEMORY LEAK OLUŞTU.

KENDİMİZ COPY ASSIGNMENT YAZACAĞIZ.
NOT: EĞER BİR SINIFA DESTRUCTOR YAZACAKSAK DEMEKKİ SEBEBİMİZ VAR, KAYNAK GERİ VERİLECEK MUHTEMELEN,
BU DURUMDA COPY CONSTRUCTOR YAZMAMIZ GEREKİYOR.COPY CTOR YAZMA DURUMUNDA DA (BU DEEP COPY YAPACAK),
BU DURUMDA COPY ASSIGNMENT FUNCTION DA YAZMAMIZ GEREKİYOR. YAPILMAZSA FELAKET OLUŞABİLİR.
C++11 ÖNCESİNDE BUNA BIG 3 DENİYORDU. BUNLA LOGİC AÇIDAN BİRBİRİNE BAĞLI 3 ÖZEL FUNCTİON.
BİRİ VARSA DİĞER 2 TANESİNİDE BİZ TANIMLAMALIYIZ.

C++11 SONRASINDA BU ARTIK BIG 5(RULE OF FIVE) OLDU.
MOVE CTOR VE MOVE ASSIGNMENTTA VAR ARTIK.

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------

ŞİMDİ SINIFA COPY ASSIGNMENT FUNCTION YAZIYORUZ.
------------------------------------------------

KENDİ KAYNAĞINI VERİP, DEEP COPY YAPILACAK.

//.h
class Sentence {
public:
	Sentence(const char* p);
	Sentence(const Sentence& other);
	Sentence& operator=(const Sentence&);
	~Sentence();
	void print()const;
	int lenght()const // lenght i inline olarak yazıyoruz
	{
		return mlen;
	}
private:
	char* mp;
	std::size_t mlen;
};


//.cpp 
Sentence& Sentence::operator=(const Sentence&)
{
	std::cout << static_cast<void*>(mp) << " Adresindeki blok free ediliyor."; // burası destination address.İçindeki veri temizlendi ilk.
	free(mp);
	mlen = other.mlen;

	mp = static_cast<chat*>(::malloc(mlen + 1));
	if (!mp)
	{
		//kontrol ...
	}
	strcpy(mp, other.mp);

	return *this;
}


DİKKAT!!!!!!!
ATAMA OPERATOR / COPY ASSIGNMENT YAZIMINDA ÇOK SIK KULLANILAN IDIYOM COPY SWAP IDIYOMU
COPY& SWAP ILERIDE GÖRÜLECEK
BIZ BURADA GELENEKSEL OLARAK ILERLEDIK


#include <iostream>
#include "sentence.h"

int main()
{
	Sentence sx{ "Bugun Cumartesi" };
	sx.print();

	// boş blok
	{
		Sentence a{ "Necati hoca C++ anlatiyor" };
		a.print();
		a = sx;
	}

	sx.print();  // ARTIK HATA YOK. GEÇERLİ.

}


--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

x = x;     self assignment deniyor buna.Bir nesnenin kendine atanması.
Çok seyrekte olsa hiç beklenmeyen bir yerde karşımıza çıkabilir.Nasıl olsa olmaz diyemeyiz.


int x = 10;
int* p = &x;
int& r = x;

*p = r;	     // x = x; oldu burada 	


BİZIM YAZDIĞIMIZ COPY ASSIGNMENT, SELF ASSIGNMENT OLURSA NE OLUR(Aşağıda örnek) ?
BUNUN TEST KODUNU

int main()
{
	Sentence a{ "C++ anlatiyor" };
	a.print();
	a = a;
	a.print();	// UNDEFINED BEHAVİOR YAZDIRINCA GÖRDÜK.Çünkü fonksiyon ilk önce free ediyor parametreden geleni.
}

NASIL ÖNLENEBİLİR ?

burada other ile * this aynı nesne çıkabilir.

DÜZELTİLMİŞ HALİ.
---------------- -

Sentence &Sentence::operator=(const other&)
{
	if (this == &other) // self assignment  BUNU EKLEDİK.
		return *this;

	std::cout << static_cast<void*>(mp) << " Adresindeki blok free ediliyor."
	free(mp);
	mlen = other.mlen;

	mp = static_cast<chat*>(::malloc(mlen + 1));
	if (!mp)
	{
		//kontrol ...
	}
	strcpy(mp, other.mp);

	return *this;
}

-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------

C de atama operatörünün ürettiği değer nesneye atanan değer.
int x = 10;
int a, b, c;

a = b = c = x;
Öncelik tablosuna göre sağdan sola doğru işlemler devam eder.
Bunu C++ ta korumaya çalışmışlar.Bunun içinde copy assignment functionunun return değeri kendi türünden referans(Sentence &)
Bir farklılık var. C++ ta (a = b) bu bir lvalue expression.

---------------------------

Sentence s{ "Ali okuyor" };
Sentence x{ "xyz" };

(x = s).print(); BURASI LEGAL.NEDEN ? Çünkü burada bir lvalue exp olan return değer var.

x = s;
x.print(); aynı şey.

aynı zamanda
x.operator=(s);

COPY ASSIGNMENT UYARISI !!!!!!!!!!!
a - return değerini çok değiştirme.
b - Parametrik yapısında değişiklik yapılacaksa Copy swap idiyomunu implemente etmek için bunu yapmalıyız.
bunların dıuşında asla değişiklik yapmamalıyız.

C++ TA EN ÖNEMLI HATALAR, CLASS IÇIN DESTRUCTORU YAZMASI AMA COPY ASSIGNMENT VE COPY CTOR U YAZMAMASI.BIG 3 ü yazmamak yani.

======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================


MOVE SEMANTICS / TAŞIMA SEMANTİĞİ

MOVE CONSTRUCTOR VE MOVE ASSIGNMENT
BU KONU EN ZOR KONU


ÖYLE DURUMLAR VAR Kİ ASLINDA BİR BİR SINIF NESNESİNİN HAYATININ  BİTECEĞİNİ VE
HİÇBİR KODUN BU SINIF NESNESİNİ KULLANAMAYACAĞINI BİLİYORUZ.BÖYLE DURUMLAR VAR.

A x = hayatı birazdan bitecek(hiçbir kod tarafından kullanılmayacak) nesne;
VEYA
x = hayatı birazdan bitecek(hiçbir kod tarafından kullanılmayacak) nesne;

Bu durumda copy ctor veya copy assigment kullanılsa ne olur?
Yine kaynağı kopyalarız(hayatı bitecek nesne yani) ve yeni bir kaynak elde ederiz. C++ 11 den önce
compiler özel optimizasyon yapmazsa böyle durumlara çok rastlanıyordu. Yani nesne ölecek buna rağmen
nesneyi kopyalıyoruz ve sonrada destructor kaynağı geri veriyor.

Burada nasıl kod çalışırsa yüksek verim elde edilir ? 
Gereksiz kopyalama engellenirse. NASIL?
Nesnenin hayatı bitiyor eminiz. başka hiçbir kod bunu kullanamayacak bundan da eminiz.
O zaman bu kaynağı iade etmek yerine hayata gelen nesne bu kaynağı çalsın.

Ölecek olan nesnenin kaynağını devralan nesne ile alakalı fıkrayı dinle : D:D:D:D	54:45
Burada da hayata gelen nesne diyorki sen kaynağı verme ben onu senden devralayım.
Verim artışı oluyor.Gereksiz kopyalamalardan kaçınmış oluyoruz.

C++ 11 den önce compiler bunu anlayamıyordu, kaynak kopyalıyordu.Dilin araçları compile time da bunun hayatını biteceğini anlayıp 
alternatif bir kod çalıştırmaya yeterli değildi. Sentaks izin vermiyordu.


A x = expr;		EXPR ÖLECEKSE BIR KOD ÇALIŞACAK, ÖLMEYECEKSE BAŞKA BIR KOD ÇALIŞIYOR.!!!!!!!!!!!
Bunu yapabilmek için dile eklenen sentaks aracı SAĞ TARAF REFERANSI eklendi.

Expr R value exp veya L value exp olabilir. 2 ihtimal var.

Eğer L value exp ise, bu sınıf nesnesi halen kullanılabilir.Kaynağını çalamayız.Kopyalamak zorundayız.
Eğer çalarsak değerini kullanan kodlar UB olur.

Eğer R value exp ise, hayatı bitecek başka kodun bunu kullanma ihtimali yok.
O yüzden kaynağı çalınabilir. :D:D İşte buna taşıma semantiği deniyor. Move Semantics

class Myclass() { }
void func(const Myclass&); // const sol taraf referansı
void func(Myclass && r); // sağ taraf referansı.

func(lval) 1. çalışır
func(rval) 1 - 2 viable ama 2. çalışır

Böyle bir overloading yaparsak yine aynı kurallar geçerli.
bunu constructor yazarken kullanacağız.


class Myclass {
public:
	Myclass(const Myclass& other); // copy ctor
	Myclass(Myclass&& other); // move ctor. Burada kaynak çalma yapılacak :D:D
};

-----------------------------------------------------------------------------

class Myclass {
public:
	Myclass() { }
	Myclass(const Myclass& other) // Amacı diğer nesneden kopyalama yapmak
	{
		std::cout << "copy ctor cagrildi kaynak kopyalanacak\n";
	}

	Myclass(Myclass&& other) // Amacı diğer nesneden çalmak :D
	{
		std::cout << "move ctor cagrildi kaynak calinacak\n";
	}

};

int main()
{
	Myclass x;
	Myclass y(x);  // x lvalue olduğu için copy ctor cagrilacak
	Myclass z(Myclass{}); // BURADA DAHA SONRA GÖRÜLECEK OLAN MANDATORY COPY ELISION ÇALIŞACAK VE DEFAULT CTOR ÇAĞRILACAK.
	Myclass t(std::move(x)); // rvalue exp(std::move(x) X VALUE EXPRESSİON İLERİ C++TA GÖRÜLDÜ) olduğu için move ctor cagrilacak
}

Move constructor ın amacı gereksiz kopyalamalardan kaçınmak.
NOT: move() sonra görülecek.

-----------------------------------------------------------------------------------------
CPPREFERENCE
std::move is used to indicate that an object t may be "moved from", 
i.e. allowing the efficient transfer of resources from t to another object.

In particular, std::move produces an xvalue expression that identifies its argument t. 
It is exactly equivalent to a static_cast to an rvalue reference type.
-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------


Move ctor olmasa bile
Myclass x = Rvalue exp; geçerli oluyor.Copy ctor da viable çünkü : D:D:D
-----------------------------------------------------------------------------------------

ÇOK ÇOK ÖNEMLİ KURALLAR!!!!!
------------------------------
A x = expr;
L value exp ise copy ctor
R value exp ise move varsa move, yoksa copy ctor cagrılır.
verim problemi oluyor UB değil.Her sınıfın Move constructorı olmak zorunda değil.
Ama eğer Move Constructor yazmadıysa, hayatı bitecek nesnenin değerini çalamayacağım.Kopyalama yapabilirim.


DİĞER SORUN !!!!!!!
A x;
x = expr; 	Burada da atama functionu overload edeceğiz. :D:D

Sentence& operator=(const Sentence&); kaynak kopyalayacak şekilde
Sentence& operator=(Sentence&&);	çalacak şekilde yazacağız.

------------------------------------------------------------------------------------------------------------

DESTRUCTORDA DEĞIŞIKLIK
BIR NESNENIN KAYNAĞI ÇALINMIŞSA FREE ETMEYECEĞIZ.
ÇALINMAMIŞSA FREE EDECEĞIZ.

Sentence::~Sentence()
{
	if(mp) // mp != nullptr ile aynı
		free(mp);
}

KAYNAĞINI ÇALDIĞIM NESNENİN POİNTERINI NULL POINTER YAZARSAM ARTIK BURASI DÜZGÜN ÇALIŞIR

------------------------------------------------------------------------

MOVE CONSTRUCTOR
----------------
Sentence::Sentence(Sentence && other) : mp(other.mp), mlen(other.mlen)
{
	other.mp = nullptr; // Kaynağı çalınmış nesnenin destructoru çağrıldığında onu free etmeye çalışmayacak artık.
}

---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------

MOVE ASSIGNMENT
---------------
Sentence& Sentence::operator=(Sentence && other)
{
	if(this == &other)
		return *this;

	free(mp);
	mp = other.mp;	//hayatını çalma aşaması :D
	mlen = other.mlen; //burasıda öyle

	other.mp = nullptr; // çalındığı için nullptr a atanmış.

	return *this;
}



================================================================================================================
================================================================================================================
================================================================================================================


MOLADAN SONRASI

class A
{

};

void func(A&&)
{
	std:cout << "func(A&&)\n";
}

void func(const A&)
{
	std:cout << "func(const A&)\n";
}

int main()
{
	A ax;
	func(ax);  //2. func çağrılır
	func(std::move(ax));  //Bu sefer 1. çağrılır
}


----------------------------------------------------------------------------------------------------

&& li ifadeyi nasıl çağırırız. ?

type casting ile yaptı
func(static_cast<A&&>(ax)); Böyle de yapılabilir. Bildiğimiz yol bu idi.

birde std::move var.    İsimlendirmeyi hoca beğenmiyor. : D : D : D : D 
C++ ın diğer günahı. İsmi kötü :D:D:D:D
ismi move olduğuna göre bu fonksiyon move işlemi yapıyor gibi düşünülebilir ama değil.
Bu bir tür dönüşümü yapıyor. Lvalue exp i Rvalue exp e dönüştürüyor.Rvalue exp ise yine Rvalue exp olarak dönüyor
std::move() bunun oluşturduğu ifade bir rvalue exp.

func(std::move(ax));

-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------

Scott Meyers in Modern Effective C++ ını oku
Most vexing parse ı da bu adam uydurmuş zaten :D

move doesn't move diyor aynı zamanda.

Myclass a(x); copy ctor
Myclass a(move(x));  move(x) rvalue exp.MOVE CTOR cagrilacak


ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!
--------------------------------
x = y; COPY ASSIGNMENT
x = move(y); MOVE ASSIGNEMNT CALISACAK

---------------------------------------------------------------------------

KAYNAĞIN ÇALINMASI IÇIN MOVE CTOR VE YA MOVE ASSIGNENT ÇAĞRILMALI
BURADA RVALUE EXPR GÖNREREREK OLUR
buda std::move(x) ile oluyor.
AMAÇ: BURADAKİ OLAY ŞU, NESNE MADEM ÖLECEK ONU KOPYALAYIP MALİYETİ ARTIRMAYALIM, ONUN DEĞERİNİ ÇALALIM :D

--------------------------------------------------------------------------------------------------

class Myclass{

};

void func(Myclass&& x)
{
	x; nedir ?		Lvalue Expression ve Rvalue Reference. Value Category ve Data Type karıştırılmasın.
					yani argüman olarak buna RVALUE EXP bağlanabilir.
					x burada hatadır çünkü lvalue exp, std::move(x); burası GEÇERLİ ARTIK.

	Myclass y(x); // Dersek burada Copy Ctor devreye girer. Biz move Ctor istiyoruz.Hırsızlık yapacağız.
	Myclass y(std::move(x)); //burası artık move ctoru çalıştırır. Ne kadar mükemmel :D:D:D

	VEYA

	Myclass m;
	//m nin kaynağını çalmak için.
	m = std::move(x); // çünkü burada MOVE ASSIGNMENT DEVREYE GİRİYOR.

}

---------------------------------------------------------------------------

SORU: % 80 i Yanlış anlıyor.KESİN !!! :D:D

BİR FONKSİYONUN PARAMETRE DEĞİŞKENİ NEDEN RVALUE REFERENCE OLUR ?
CEVAP :	Taşımak için

---------------------------------------------------------------------------

class Myclass { };

void func(Myclass && r);

int main()
{
	func(sağ taraf değeri);
}

func cagrilacak.Bunu böyle bir ifade ile çağırırsak
kaynak çalacak diye birşey yok.Bu taşıma, fonksiyon içerisinde yapılıyor.
Yani fonksiyonu nasıl yapılandırdığın ile alakalı.Programcılar buna kesin kaynak çalma gözüyle bakıyor ama öyle değil.
Yani aşağıdaki kod yazılınca artık kaynak çalma yapılıyor denebilir.

void func(Myclass && r)
{
	//Myclass m(std::move(r)); nesne hayata gettirerek yapılabilir

	Myclass x;
	x = std::move(r); // Assignemnt yapılarak yapılabilir. 
}			 // ikisinden biri yoksa yapmaya gerek yok zaten.

Eğer move kullanıp Rvalue expr e çevirmeyeceksek zaten myclass &&r gibi bir parametreye ihtiyaç yoktur.
Muhtemelen gereksiz veya hatalı bir iş yapıyoruz.

SONUÇ:
Myclass && r,  burada r ye Rvalue exp bağlanır.Bu nesne artık ölmek üzere kimse kullanmayacak bundan eminim.
Bu durumda bu kaynağı çalabilirim.Çalmak içinde ya bir nesne hayata getirip yada atama yaparak(2 adet move yani) yapabilirim.

-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------

ÇOK ÖNEMLİ!!!!!!!!!

ÖYLE FONKSIYON ÇAĞRILMAK ISTENIYOR KI SOL TARAF DEĞERIYLE ÇAĞRILIRSA
lvalue exp ile çağrılırsa fonksiyon içinde bir kopyalama yapılacak,
rvalue exp ile çağrılırsa kaynağını çalarak işlem yapacak.En çok çıkan senaryo

FUNCTION OVERLOADING İLE YAPILIR.

class Myclass{
public:
	Myclass() = default;
	Myclass(const Myclass& other)
	{
		std::cout << "copy ctor\n";
	}
	Myclass(Myclass&& other)
	{
		std::cout << "move ctor\n";
	}

};

void func(const Myclass &r)
{
	Myclass x(r); // copy ctor çağrılır
}


void func(Myclass && r)
{
	Myclass x(std::move(r)); // kaynağını çalmış oluyoruz.
}

int main()
{
	Myclass m;
	func(m); // birinci çağrılır
	func(std::move(m)); // ikinci çağrılır
}

Atamalı örnekte yapılabilirdi.
Biz move ctor ile yazdık burada.Hoca Move assignmentlı da yazdı. 2:07:50

x = std::move(m) gibi birşey yapılıyor. bu da MOVE ASSIGNMENT.

AŞAĞISI ÇOK ÇOK ÖNEMLİ !!!!!!!!!!

============================================================================================================
============================================================================================================
============================================================================================================
============================================================================================================
============================================================================================================
============================================================================================================
============================================================================================================

Special Member Functions
DERLEYİCİ DEFAULT OLARAK NASIL YAZIYOR BUNLARI
-----------------------------------------------

class Myclass {
public:
	Myclass() //Derleyici ax ve bx i default init ediyor. // DEFAULT CONSTRUCTOR
	{

	}
	~Myclass() // Derleyicinin yazdığı ctor da, sınıfın veri elemanları başka sınıflar türünden ise onlar içinde
	{							// destructor çağrılır 
		psudo code
		bx -> ~B();  
		ax -> ~A();
	}

	Myclass(const Myclass& other) : ax(other.ax), bx(other.bx)  // COPY CONSTRUCTOR
	{
		//burada derleyici yukarıdaki gibi init ediyor.
	}

	Myclass(Myclass&& other) : ax(std::move(other.ax)), bx(std::move(other.bx)) // MOVE CONSTRUCTOR
	{
		// derleyici çalma yapacağı için move çağırıyor.Muhtemelen diğer işlemlerde var ama yazmadık.
	}

	Myclass& operator=(const Myclass& other) //	COPY ASSIGNMENT 
	{
		ax = other.ax;
		bx = other.bx;		//derleyici bunu yapıyor.
	}

	Myclass& operator=(Myclass&& other) // MOVE ASSIGNMENT
	{
		ax = std::move(other.ax);
		bx = std::move(other.bx);
	}

private:
	A ax; // A ve B başka sınıf 
	B bx;
};

SONUÇ:
BU FONKSİYONLAR İŞİMİZİ GÖRÜYORSA BIRAK DERLEYİCİ YAZSIN BU ŞEKİLDE(RULE OF ZERO)
GENELDE BİZ BUNLARI YAZMAYACAĞIZ. ÇOK DÜŞÜK İHTİMALLE BİZ YAZACAĞIZ.
AMA BUNLARI BİLİYOR OLMALIYIZ.BİZ BU KÜTÜPHANELERİN KULLANICISI OLACAĞIZ MUHTEMELEN.
BİR İMAGE PROCESSING KÜTÜPHANESİNİN MESELA KULLANICISI OLACAĞIZ O YÜZDEN BUNLARI İYİ BİLMEMİZ GEREKİR.

=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================
=======================================================================================================


2:24

NE ZAMAN DERLEYİCİ BİZİM İÇİN SPECİAL MEMBER FUNCTİON FUNCTİON YAZAR NE ZAMAN YAZMAZ ?
Belirli koşullar oluştuğunda compiler special member functionların yazılmasını garanti ediyor.
Compiler bunu ne zaman yazar veya yazmaz buna bakacağız.
Howard Hinnant sunumunda var malum tablo :D

Bu special member functionlar aşağıdaki gibi olabilir.

------------------------------------------------------------------------------------------------------

NOT DECLARED(Yok - Bildirilmemiş)
Ör:
Aşağıda Default Ctor Not Declared mesela

class Myclass{
public:
	Myclass(int);	
};

NOT: Tabloyu bu ders dosyasının içine Excel file olarak koydum.
C++SPECIALFUNCTIONS.xlsx.

-------------------------------------------------------------------------------------------------------

IMPLICITLY DECLARED (Derleyicinin bu fonksiyonu kendisinini bildirmesi.Yukarıdaki classın copy ctoru bu kategoride)
- Defaulted (Derleyici durumdan vazife çıkarıp fonk. kodunu kendisinin yazması demek)
- Deleted (Belirli durumlarda derleyici kurallar gereği bir özel fonksiyonu yazıyor / default ediyor ama)
		  (default ettiğinde dilin kurallarını çiğneyen bir sentaks hatası oluşunca, o fonksiyonu delete ediyor)
		  (ÖR: func var ama compiler tarafından delete edildiyse, bu fonk çağrılınca sentaks hatası mesajı alınır.)
		  (c++11 te geldı deleted)

ÖR:
class Myclass{
public:

private:
	const int x;
};

Mükemmel Örnekler !!!!
Burada compilerın normalde kendisinin default constructor yazması lazım. Kurallar böyle.Default constructor
elemanları default initialize eder. const nesneler default initialize edilemez. 
Bu durumda sentaks hatası oluşacak. Bu durumda compiler bunu delete ediyor.
Myclass() = delete; yaptı aslında. İspat için Mylass my; yazınca deleted func a çağrı yapıldı hatası verir.
Bunu tam anlamıyor programcılar.

ÖR2:
class A{
public:
	A(int);
};

class B{
	A ax;
};

Burada A için default constructor yazılmıyor. B için ise yazılıyor/implicitly declared.
Derleyicinin yazdığı default ctor memberları default initialize eder. Bu durumda sınıf
türlerinden memeberların default init edilmesi demek bunların default ctorlarının çağrılması demek.
AMA !!!
Derleyici A ax; te default ctor çağırırsa SENTAKS HATASI OLUR çünkü A classının default ctoru yok.
BU DURUMDA COMPILER B NIN DEFAULT CTORUNU DA DELETE EDER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int main()
{
	B bx;   burası A da default ctor olmadığından SENTAKS HATASI OLUR.Çünkü B class içinde
			A ax; satırında Default Ctor çağırıyor ve hata alıyor. A dan gelen hata B ninde default ctorunu Delete ediyor.
			ÇOK ÖNEMLİ VE İLGİNÇ.
}

Bir örnek daha var A public değilde private default ctora sahip olursa.
O da sentaks hatası.Access control hatası

Örnekler aşağıdaki gibi olabilir.
---------------------------------
- Olmayan fonksiyona çağrı 
- Private fonksiyona çağrı
- Default init edilemeyen nesneyi default init etmeye çalışmak. gibi.

------------------------------------------------------------------------------------------------------

USER DECLARED
- User declared(Defined)
- Defaulted (programcı bildirir ama default eder.) 
- Deleted (Programcı bildirir ama delete eder.)

ÖR1:
class Myclass{
public:
	//Myclass(); Bu user declared (defined)
	//Myclass() = default; // Default ctor bildirilmiş ama derleyicinin default edilmesi istenmiş.Yani kodunu derleyici yazacak.
	//Myclass() = deleted; // Fonksiyon var ama çağrı yapılırsa deleted edildiği için SENTAKS HATASI.

};

------------------------------------------------------------------------------------------------------
Soru : 2:47  Default Ctor çağrılmadan önce zero initialize edilecek konusu...
==========================================================================
==========================================================================
==========================================================================

MOLADAN SONRASI
Birtablo var.Ezberlenecek :D
Bu tablo proje içerisinde C++SPECIALFUNCTIONS.xlsx olarak yer alıyor.

Buradan sonrasında tamamen bu tabloyu anlattı.

TABLOYU ANLATTIKTAN SONRA BAZI İDİYOMLAR GÖSTERİLECEK.


1 - SINIFIN COPY CTORUNU VE COPY ASSIGN LARINI BİLEREK İSTEYEREK DELETE EDECEĞİZ.

class Myclass{
public:
	Myclass(const Myclass&) = delete;
	Myclass& operator=(const Myclass&) = delete;
};

Bu durumda copy memberlar delete edildiği için sınıf türden nesneler ne kopyalanabilir ne de taşınabilir.
Sonuçta copy memberlarla ilgili bir bildirim var. Copy memberlar için bildirim olması, move memberlar için 
not declared olmasına yetiyor.

TABLODAN BAKILABİLİR.

---------------------------------------------------------------------------------------------------------------

2 - AŞAĞIDAKI TÜRDEN CLASS OBJELERINI KOPYALAYAMAYIZ AMA TAŞIYABILIRIZ.

class Myclass{
public:
	Myclass(const Myclass&) = delete;
	Myclass& operator=(const Myclass&) = delete;
	Myclass(Myclass&&);
	Myclass& operator=(Myclass&&);
};

---------------------------------------------------------------------------------------------------------------

mesela
thread sınıfında da var böyle nesneler.
#include <thread>

thread tx;
thread ty(tx); SENTAKS HATASI
ty = tx ;  SENTAKS HATASI.

Eğer
thread ty = std::move(tx); TAMAMEN GEÇERLİ.
ty = std::move(tx);

---------------------------------------------------------------------------------------------------------------

3 - cout global bir sınıf nesnesi. türü ostream sınıfı

ostream mycout(cout); BURADA SENTAKS HATASI VAR ÇÜNKÜ COPY CONSTRUCTOR/ASSIGNMENT DELETE EDİLMİŞ BURADA.
ostream sınıfı kopyalamaya karşı kapalı.


4 - Birbiriyle çakışan durumlar olduğunda ne olacak?
	Eğer bir fonksiyonun var olmasını çağrılabilmesini istersek onu delete etmeyeceğiz,
	Derleyici tarafından da çağrılıyorsa, derleyicinin onu delete etmeyceği bir koşul oluşturmalıyız.
	Test ettim. derleyici veya programcı delete ettiyse hiçbir türlü çağrılamıyor.
	
	class Myclass{
	public:
		Myclass();
		Myclass(const Myclass&);
	};

	


5 - 3:24 teki örnek. ÖZEL DURUM.

Defaulted Move members defined as deleted, actually behave as not declared.


class A{
public:
	A() = default;
	A(const A&);
	A(A&&) = delete;
	// 
};

class B{
public:
	
private:
	A ax;
};

Derleyici B için move ctor yazacak. Bu move ctor elemanlar içinde çağrılacağına göre ve A sınıfının move ctoru da
delete edildiğine göre, Derleyici B sınıfının move ctorunu delete etmesi gerekiyor.

hata vermiyor test ettik.

class B{
public:
	B();	
private:
	A ax;
};

int main()
{
	B bx;
	B by = std::move(bx); compiler bunu deleted olarak görmüyor.Normalde B sınıfının move ctoru delete edilmeli. A sınıfından dolayı.
							delete edilen functiona yapılan çağrı sentaks hatasıdır.ama hata vermiyor.Move ctor bildirilmemiş 
							kabul ediliyor.
}


Yani move memberlar delete edilirse, not declared gibi davranıyor.



*/

#include <iostream>
#include "sentence.h"

int main()
{
	Sentence sx{ "Bugun Cumartesi" };
	sx.print();
	
	{
		Sentence a{ "Necati hoca C++ anlatiyor" };
		a.print();
		a = sx;
	}

	sx.print();  // ARTIK HATA YOK. GEÇERLİ.

}
