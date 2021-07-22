/*

FUNCTION OVERLOADİNG TEN DEVAM

Birden fazla fonksiyona aynı isim verilebilmesine yarıyordu.
Hangi fonksiyonun çağrılacağını derleyici compile time da anlıyor.
Runtime a ek maliyet yok.

-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------
ÖNEMLİ HATIRLATMA
-----------------
int func(int);
int func(const int);   BURASI OVERLOADING DEĞIL.REDECLERATION VAR.CONST BURADA İHMAL EDİLİYOR.
					   PTR DA İHMAL EDİLMİYOR VE REFERANSLARDA İHMAL EDİLMİYOR.
-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------

Function overloading var mı ?
Kısaca tekrar.

nullptr_t = bu bir pointer türü değil ama pointer türlerine dönüşebilen bir tür.

FUNCTION OVERLOAD RESOLUTION İLE İLGİLİ ÖZEL DURUMLAR

1
void func(int x, int y = 10);
void func(int x);   func Overloading var


2
func(20) çağrılırsa hangisi çağrılır.
Sentaks hatası.
Ambigiuty
Kullanılmıyor ama hata yapılmasın diye anlatıldı.
---------------------------- -
void func(int);
void func(int&);

Çok tercih edilmiyor bu.
main
func(12); GEÇERLİ. 4. satır viable değil. 3. satır çağrılır.
func(x); Geçerli. İkiside viable. AMBIGIUTY oluşur. BURASI Çok önemli.
Call by value VS Call by reference arasında seçim kriteri yok burada.

----------------------------
void func(int);
void func(const int&);

main
func(12); burası SENTAKS HATASI.
ÇÜNKÜ 12 prvalue exp. 3. satir viable. 4. satirda const tan dolayi viable. AMBIGIUTY
ÖNERİLMİYOR.

-------------------------------- -

3
Const Overloading
void func(T * ptr)
void func(const T * ptr)  burası overloading

void func(T * ptr)
void func(T* const ptr) burası overloading değil

-------------------------- -
void func(T & ptr)
void func(const T & ptr)  burası overloading

---------------------------------------------- -

void func(int* p)
{
	std::cout << "func(int *)\n";
}

void func(const int* p)
{
	std::cout << "func(const int *)\n";
}

BURASI FUNCTION OVERLOADING.

int main()
{
	cosnt int x = 10;
	func(&x);	burada ilk function viable değil.cosnttan int e implicit dönüşüm yok
}			ikincisi viable



------------------------------------------------ -


void func(int* p)
{
	std::cout << "func(int *)\n";
}


void func(const int* p)
{
	std::cout << "func(const int *)\n";
}

BURASIDA FUNCTION OVERLOADING. ÖZEL DURUM.

int main()
{
	int x = 10;
	func(&x);	// IKISIDE EXACT MATCH
}			// AMA BURADA AMBIGIUTY YOK. INT * OLAN 1. FUNCTION ÇAĞRILIR.


	CONST NESNELER IÇIN AŞAĞIDAKI
	CONST OLMAYANLAR IÇIN YUKARIDAKI ÇAĞRILIR.

	----------------------------------------------

	REFERANS SEMANTİĞİ KARŞILIĞI

	void func(int& p)
	{
		std::cout << "func(int &)\n";
	}


	void func(const int& p)
	{
		std::cout << "func(const int &)\n";
	}

	BURASI FUNCTION OVERLOADING.

		int main()
	{
		int x = 10;
		const int y = 20;
		func(x); birincisi çağrılır.
		func(y); ikincisi çağrılır.
	}


NOT: C de function definitionda isim vermemek SENTAKS HATASI

C++ ta definitionda isim vermemek GEÇERLİ.
NASIL kullanacağız ? Kullanamayacağız : D : D : D
Neden yapılıyor ? İleride görülecek.


KISACA
Brace init/ uniform inite değindi.Soru sorulduğu için.
her türlü initialize için kullanılabilir.

int x; Default İnit.Refler hata, constlar hata
int y{}; Value init.burada y zero initialize edilir.y = 0 yani :D
int z{ 20 }; Uniform / Brace
int t(12); Direct init.
int k = 23; Copy init.
int x(); Function Decleration

Mülakat sorusu
auto x{ 10 }; x in türü int

auto x = { 10 };  buradaki tür Initializer list deniyor.Daha görülmedi.
std::initializer_list<int>

auto z{ 10,20 }; c++17 de artık sentaks hatası
auto z = { 10,20 }; init list oldu.Geçerli.

NOT!!!!
ileride aggregate init görülecek

NOT : C / C++ dillerinde local düzeyde fonksiyon tanımlanamaz.
BUNLARIN ARASINDAKİ FARKLILIKLAR CLASS LARA GELİNCE ANLAŞILACAK.


-------------------------------------------------------------- -

OVERLOADING ten Devam

void func(T&);
void func(T&&);
Yukarıda Overloading var.

void func(int&)
{
	cout "func(int&)"
}

void func(int&&)
{
	cout "func(int&&)"
}



int main

int x{ 12 };
func(x); alttaki viable değil.Üstteki çağrılır
func(123); üstteki viable değil.alttaki çağrılır


------------------------------------------------------ -



void func(const int&)
{
	cout "func(cosnt int&)"
}

void func(int&&)
{
	cout "func(int&&)"
}



int main
{
	int x{24};
	func(x); 1. FUNCTION ÇAĞRILIR
	func(20); IKI FUNCTIONDA VIABLE. 1. FUNC CONSTTAN DOLAYI.
		// BURADA ÜSTÜNLÜK SAĞ TARAF REFERANS DEĞERINDEN ÖTÜRÜ
		// 2. FUNCTION ÇAĞRILIR.
}

------------------------------------------------------ -
------------------------------------------------------ -
------------------------------------------------------ -

BURASI ÇOK AYDINLATICI.
-----------------------

void func(int&)
{
	cout "func (int&)"
}

void func(const int&)
{
	cout "func(cosnt int&)"
}

void func(int&&)
{
	cout "func(int&&)"
}

int x = 10
const int y = 202;
func(x); 1. çağrılır (1. ve 2. functionlar viable)
func(y); 2. çağrılır.
func(5); 3. çağrılır. (2. ve 3. functionlar viable)


---------------------------------------------------------------------

	NULLPTR_T NIN DILE EKLENMESINDEKI AMAÇ

	void func(int* p);
	void func(int);

	main
		int x{ 26 };
		func(x); Üstteki değil alttaki viable.
		func(0) Null pointer conversion.
		ama hem üstteki hemde altaki viable.Exact match var.
		ALTTAKİ ÇAĞRILIR.



	void func(double* p);
	void func(double);

	func(0);
	Burada da ambigiuty var.İkiside standart conversion.Çok tehlikeli.


	NULLPTR nin dile eklenmesinin sebebi bu tip hataların önüne geçmek.
	func(nullptr) ile çağırırsam pointer parametreli function çağrılacak.
	nullptr den basit türlere dönüşüm yok ama pointer türlerine dönüşüm var


	void func(nullptr_t);
	void func(bool);

	int main()
	{	
		int x{ 10 };
		func(&x); İkinci çağrılır bool olan. Adresten bool türüne dönüşüm var.
		func(nullptr); birincisi çağrılır.
	}

	----------------------------------------

	ÖZEL DURUM

	void func(void* vptr);
	void func(bool);

	main
	int x{ 10 };
	func(&x);  ikiside viable.

	ÖZEL DURUM BU
	Çağrılan function void* parametreli olan.

	-----------------------------------------

	ÖZEL DURUM
		
	void func(void *);
	void func(bool);

	func(0);	BURASI AMBIGIUTY.Özel durum
	func(nullptr); 1. çağrılır
	func(&x); 1. çağrılır
	func(x); 2. çağrılır.

	--------------------------------------------

	SON ÖZEL DURUM
	3 tane argüman var.
	HANGİSİNE BAKILACAK ?

	void func(int, double, int);
	void func(long, int, char);


	KURAL:
	Bu durumlarda fonksiyonun seçilebilmesi için, aşağıdaki durumu sağlaması gerekiyor.
		a - en az bir parametrede diğer overloadlara üstün gelecek.
		b - Üstün gelmediği parametrelerde daha kötü olmayacak.Eşit olabilir.

		Birinde biri daha iyi, diğerinde de diğeri daha iyi ise AMBIGIUTY.


		ÖR :

	void func(int, double, long);
	void func(long, int, bool);
	void func(double, float, int);

	func(12, 5u, 2.3); 1. fonksiyon seçilir.
		12 üstün. 5u da conversion var 2.3 te de conversion var.
		1. parametrede de üstün diğerlerinde daha kötü değil.


	-------------------------------------------------------------------------- -

	ÖDEV SORULARINA BAKILDI BİRAZ.

	No Match eşleşme ok.
	Ambigiuty ise birden fazla eşleşen var ama aralarından seçim yapamadım demek.

	======================================================================
	======================================================================
	======================================================================
	======================================================================
	======================================================================
	======================================================================

	CLASSES / SINIFLAR
	------------------
	Data abstraction yapmak için kullanılıyor ve daha birsürü şey.
	Problem domainindeki varlıklar artık sınıflarla temsil edilecek.
	10 - 15 ders görülecek :D:D:D

	C de struct enum ve union lar vardı.
	C++ ta struct ve union ların ortak kategorisi class type.
	Enum bir class type değil.
	Yani struct ile de yapsak class ilede belirtsek hepsi class.
	struct demek class demek.


	struct Nec
	{
	};

	Buna Nec sınıfı dersek şaşırmayalım.

	NOT : TEKRAR - Enum bir class type değil

	--------------------------------------

	SENTAKS

	class Nec {

	};

	Nec burada tag ismi.
	Küme parantezi içerisinde(Declerative Region) bildirilen varlıklara sınıfın elemanları deniyor
	class members ingilizcesi.

	Bu memberlar 3 kategoriye ayrılır.

	1 - Data members(veri elemanları)
		a - static
		b - nonstatic

	2 - Member function(üye fonksiyon)
		a - static
		b - nonstatic

	10 sene önce C++ ta metod kullanılmıyordu ama
	3 - 4 yıldır C++ tada metod diyenler var.

	3 - Member Type - Type Member - Nested Type(Tür elemanları)

	typedef int Word; bu bir member mesela
	class Data {}; gibi bir sınıf olabilir yada enum türü olabilir.

	--------------------------------------------------------------------------

	class ları boş şekilde tanımlarsak empty class olur.Çok kullanılıyor.

	Not : Empty class türden nesneler memory de 1 byte yer kaplar.

	- Data members
		non-static data members
		static data members

	class Nec {
		int mx; // nonstatic data member
		static int y; // static data member.
	}

	Nonstatic ler sınıf sizeof unu artırıyor.fiziksel olarak class içinde yer alıyorlar.
	Static olanlar sınıf sizeof una girmiyor.

	Sınıf türden yeni bir nesne yaratılınca bu sınıf türden instance yaratılmış oluyor.
	Nec n1; // instantiate nesne oluşturmaya karşılık gelen terim.


	class Point {
		double mx, my, mz;
	};

	int main()
	{
		Point a, b, c;
	}

	-------------------------------------------------------------------------- -

	Sınıfın Üye fonksiyonları

	struct Point {
		void func123(int, int);
	};

	func123 member functiondur burada.
	java c # ta global function olayı yok. Sınıfa üye olmak zorunda.

	C++ ta member functionlar veya global / free / stand - alone fonksiyonlar var.
	Member functionlar sınıfın içinde bildiriliyor ama içinde yer kaplamıyor.

	------------------------------------------------

	SINIFLARLA HAYATIMIZA YENİ SCOPE TÜRLERİDE GİRİYOR.

	C DE
	-BLOCK -FİLE -FUNCTION -FUNCTION PROTOTYPE

	C++ TA
	-BLOCK -NAMESPACE -FUNCTION -FUNCTION PROTOTYPE -CLASS SCOPE


	------------------------------------------------

	HAYATIMIZA GİRECEK YENİ TERİM

	ACCESS CONTROL - ERİŞİM KONTROLÜ
	Sınıfın herhangibir memberı erişim kontrolü açısından 3 kategoriden birine ait olmalı

	a - Public member : Herkese açık kodlar
	b - Private member : Sadece sınıfın kendisinin kullanacağı kodlar
	c - Protected members : Inheritance konusunda görülecek.Client lara yasak
							Ama kalıtım yoluyla elde edilen sınıflara açık.

	BURASI ÇOK ÖNEMLİ.SIRALAMAYA DİKKAT.!!!!!!!!!!!!!!!!!!!!!!!!!
	===========================
	===========================
	Name lookup 	    1. adım
	context control		2. adım
	access control  	3. adım
	===========================
	===========================


	Classlarda özel isim arama kuralları var.

	struct data {  // struct - class aynı artık C++ ta
		int mx;
		void func();
	};


	int main()
	{
		mx = 5; // burada sentaks hatası var.
	}


	--------------------------------------------------

	. / dot operatörünün sol tarafı class olmalı.

	int main()
	{
		data mydata;
		mydata.mx;  // mydata içindeki scope ta aradı. 
	}


	---------------------------------------- -

	Ok Operatörü

	int main()
	{
		data mydata;
		data* ptr = &mydata;
		ptr->mx;
	}

	--------------------------------------------------------------------------------

	:: Bu bir Operatör. SCOPE RESOLUTION Operatörü. Çözünürlük Operatörü.

	ÇÖZÜNÜRLÜK OPERATÖRÜNÜN SOL OPERANDI BIR DEĞIŞKEN ISMI OLAMAZ!!
	SADECE NAMESPACE VEYA CLASS İSMİ OLUR

	unary olarak kullanırsak
	::x bu direk Namespace scope ta arıyor.

	Binary olarak kullanırsak
	Nec::x
	1 - Nec bir Namespace olabilir.
	2 - Nec bir class olabilir.

	
	NOT!!!!!!!!!
	class türden bir değişken yaratıp bunu :: ile nitelemek hata.Değişkenler :: operandı olamıyor.
	. ile içerisindeki nesnelere ulaşılabiliyor.Public olarak varsayarsak memberları.


	class nec {
		int x;
	};

	int main()
	{
		nec mynec;
		mynec::x gibi.burada amaç olayı anlamak sentaks hatası. Public olasaydı mynec.x ile erişirdik.
	}

	ÖNEMLİ!!!!
	Burada x i kullanabilmesi için ACCESS CONTROL DEN GEÇMELİ.
	Private olursa yukarıda altını çizebilir.
	Hata olarak yani.

	access specifier - erişim belirteci

	class Myclass
	{
	public:
		int a;
		int b;
		int c;
		int foo(int);


	//buraya kadar public
	private:
		int d;
		typedef int Word;


	//buraya kadar private
	protected:
		void f();


	//buraya kadar protected.
	};

	--------------------------------------------------------------------------------

	Burada public private protected sıralaması önemli değil.istenilen sırada yazılır.

		tercih edilen
		public yukarıda
		private aşağıda olan


	SORU :

	class Myclass
	{
		int x
	public:
		..
		..
		..
	};

	Class kullanılırsa x in erişim böylesi private

		--------

	struct Mystruct
	{
		int x;
	public:
		..
		..
		..
	};

	x in erişim bölgesi burada public

	structlarda private yapılıyormuş.Ama structkar public kullanım amaçlı olarak kullanılıyor.
		


	NOT!!!!!!

	Aşağısı geçerli.

	class myclass
	{
	public:
		//kodlar

	private:
		//kodlar

	public:
		//kodlar

	private:
		//kodlar


	}


	NOT!!!!!!!!!!!!

	SINIFIN PUBLIC PRIVATE VEYA PROTECTED BÖLÜMLERİ AYRI SCOPE LAR OLUŞTURMAZ.
	SADECE ERİŞİM KONTOLLERİ BUNLAR.

	Aşağısı SENTAKS HATASI.AYNI SCOPE TA BİR İSİM BİRDEN FAZLA VARLIĞA VERİLEMEZ.
	class myclass
	{
	public:
		int x;
	private:
		int x;
	}


	NOT!!!!!!!!!!
	SINIFIN ÜYE FONKSİYONLARI REDECLERATION EDİLEMEZ.SENTAKS HATASI.

	class mydata
	{
		void func(int);
		void func(int);
	};


	AŞAĞIDA HİÇBİR HATA YOK. OVERLOADING VAR.
	class mydata
	{
		void func(int);
	public:
		void func(double);
	};

	NOT: PRIVATE VEYA PUBLIC FARKLI BIR SCOPE DEĞİL.

	---------------------------------------------------------------------- -

	C de tüm struct elemanları public idi.

	C++ ta farklı dedik

	class Fighter
	{
	public:
		void kill();
		void sleep();
		void jump();

	};


	Bu sınıfı kullanan programcılar bunların nasıl yapıldı ile ilgilenmiyor.
	sadece istediği işi yaptırıyor.

	Fighter myfighter;

	myfighter.run();
	myfighter.kill();
	myfighter.jump();

	Bunlar fonksiyonlar.Client kodu yazan hangi fonksiyon ne iş yapıyor bunu biliyor.
	nasıl yaptığı ile ilgilenmiyor.


	C#ve Javadan farkı Fonksiyonlar diyince ?
	hem sınıf üyesi fonksiyonlar hemde global fonksiyonlar işin içine giriyor.

	Sınıf tanımları genelde başlık dosyasından gelecek.

	Veri gizlemek için private kullanılıyordu

	class Myclass
	{
	public:
		void func();

	private:
		int mx, my;

	}

	C kütüphanelerini kullanırken herşeyi bilmek gerekiyordu.
	Yapının birsürü elemannı öğren gibi.Mesela Struct* tm :D
	Hata yapma riskini çok artırıyor.

	C++ ta tüm fonksiyonun yapısını bilmeme gerek yok.
	public kısmında yer alan fonksiyonların ne iş yaptığını bilmem yeterli.

	BURADA Public private protected biraz örnekler verildi ve C ile kıyaslandı.

	class Myclass {
		void func(int x);
	};

	void foo(int x);

	Farkları ne ?
		1 - Scope lar farklı.
		2 - Class ın nonstatic üye fonksiyonu gösterilmeyen gizli bir parametre değişkenine
		daha sahip.Bu ilgili sınıf türünden pointer.
		Aslında

		void func(Myclass * p, int x);   2 Adet parametre değişkeni var.

	AŞIRI ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!
	Yani sınıfın nonstatik fonksiyonların gösterilmeyen/gizli ek bir parametre değişkenine sahip.
	Bu değişken ilgili sınıfın türünden bir pointer değişkeni. Böylece adres yoluyla bu nesneye 
	erişecek aslında.

	--------------------------------------------------------------------------------------------

	class Data {
	public:
		void func();
	private:
		int a, b, c;
	};

	int main()
	{
		Data mydata;
		mydata.func(); // burada data * türden bir nesne argüman olarak gönderiliyor.
	}					// bunu gizli olarak yapıyor.


	--------------------------------------------------------------------------------------

	class figher {
	//
	public:
		void kill(fighter&);
	};

	//ÖRNEK KAFA KARIŞTIRMASIN.SADECE KAVRAMI ANLAMAK ÖNEMLİ.
	int main()
	{
		fighter myfighter;
		fighter enemy_fighter;

		myfighter.kill(enemy_fighter); // artık kimin kimi öldürdüğü belli :D
		C de iki tane adres döndermek gerekiyordu.C++ bu adres göndrme işini
		gizli bir şekilde yapıyor zaten.
	}	
	---------------------------------------------- -

	KURAL
	-----
	class Myclass {
	public:
		void func();
		void foo();
	};

	int main()
	{
		mycolor m;

		m.func(); // burada Myclass * türden bir obje gönderiliyor
		m.foo();	// aynısı burada da var.

		//Eğer class adresi varsa bu seferde  ok ->  operatörü.Klasik struct gibi.



	}

	------------------------------------------------------------------------------ -
	------------------------------------------------------------------------------ -
	------------------------------------------------------------------------------ -


	SINIFLARIN ÜYE FONKSİYONLARININ TANIMLANMASI VE ÜYE FONKSİYONLAR İÇİNDE
	NAME LOOKUP

	Başlık dosyası yarattık date.h ve imp.dosyası date.cpp

	date.h içinden klasik mult.inc.guard
	pragma once standart değil.


*/

#include <iostream>

class Ali
{
public:
	int a = 4;
	int b;

};

int main()
{



}
