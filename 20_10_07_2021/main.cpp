/*
Kalıtımda kalmıştık oradan devam

Bu aslında OOP de kullanılan genel terim.Sınıflar arası ilişki biçimini belirliyor.
Araba türden sınıf yerine, mercedes türünden türemiş sınıfı kullanıyoruz.Her mercedes bir arabadır.
Is a relationship ilişkisini vurguluyor.Bu bir türden nesnenin başka bir türden kullanılabildiğini söylüyor.
Is a relationship compositiona alternatif olarak düşünülebilir.Composition ile yapılabiliyorsa, composition daha 
avantajlı çünkü daha az bağımlılık oluşturuyor.

Kalıtımın OOP deki ile C++ taki anlamı farklı. C++ ta public private protected kalıtımlar var.
C++taki public kalıtımı, OOP deki kalıtım olarak isimlendiriliyor.
Private ve protected kalıtım is a ilişkisini göstermiyor.

Birde C++ ta kalıtım compile time a ilişkin bir araç olarakta kullanılıyor.

OOP açısından kalıtımı neden kullanıyoruz?
Temel fikirler ne. 2 adet temel fikir var.

1. Eski kodların yeni kodları kullanması.Yani runtime polymorphism
Çalışma zamanı çok biçimliliği.BU MAJOR FIKIR.

Mesela, tetris oyununu yazsak.Bunu C de yazmak istesek.Mantığınıda biliyoruz
bu oyunun.Bunları C de düşünsek Yer şekli ayrı ayrı structlar olarak düşünüp
herbirinin kodunu ayrı ayrı yazacağız.Sonra müşteriden talep geldi.Eskiden olmayan
yeni bir şekil istendi.biz kodun genelinde switch else if lerde değişiklik yapmak
zorunda kalırız.

OOP de kalıtımdan faydalansak.Tetris teki elemanların şekli ve yetenekleri / dönme şekilleri belli.
Bir genel bir sınıf yazsak, diğer tüm objeleride bu sınıftan türetsek nasıl olur.
Kalıtımda oluşturunca eskiden oluşturduğumuz if else switchlerde değişiklik yapmayacağız.

NOt : C++ ta kalıtıma alternatif başka araçlarda var. Çoğu durumda kalıtımdan daha avajtajlı olabiliyor.
kalıtımın dezavantajlarınıda içermiyorlar.Mesela Static Polymorphism. Yada duruma göre Variant isimli sınıf.


2. Code Reuse.Kodun yeniden kullanımı.Kodu tekrar yazmak yerine varolan kodun kulanımı ile oluyor bu. 
Mesela Student sınıfının Person sınıfından kalıtım yoluyla türetilmesi gibi.BU MINOR FIKIR.


====================================================================================================================
====================================================================================================================


KALITIMDA ÖZEL ÜYE FONKSİYONLARIN ROLÜ
---------------------------------------
En son burada kalmıştık.Default Ctoru görmüştük hatta.Hayata gelme ve sonlandırma sıralarını görmüştük geçen ders.
Eğer türemiş sınıfa default ctor yazmazsak, derleyicinin bizim için default edeceği default ctor
taban sınıf alt nesnesinide default init ediyor. Destructor derleyici tarafından yazılırsa, tıpkı bizimki gibi, önce elemanları 
sonra taban sınıf alt nesnesini destroy ediyor.İlk hayata gelen son veda ediyor.

Constructor çalıştırıldığında ---> Base class nesnesi hayata gelir sonrada elemanlar hayata gelir.
Destructor çalıştırıldığında ---> Önce elemanların hayatı bitiyor sonrada base class nesnesinin hayatı biter.

Burayı yazmıştık zaten önceki ders
Hatırlatma.Tercih edilen rule of zero

class Base {

};

class Member {

};

class Der : public Base {
public:
	Der(const Der& other) : Base(other), mx(other.mx)  //Bunu yazmazsak, taban sınıf copy ctor olmaz default init edilir.Yani Def. Ctor cağrılır.
	{  }												// iki nesne kopyalanınca bunların içerisindeki taban sınıf nesneleride kopyalanmalı.
private:												// Derleyici Base alt nesnesini hayata getirirken, other ın içindeki Base i kullanacak.
	Member mx;
};

Format yukarıdaki gibi 

-------------------------------------------------------------------------------------------

Bunu yazdıran kodda aşağıda.

class Base {
public:
	Base()
	{
		std:cout << Base ctor;
	}
	Base(const Base &other)
	{
		std:cout << Base copy constructor;
	}
};

class Der : public  Base {

}

int main()
{
	Der x;  // base ctor 
	Der y(x); // copy cotr çalışır eğer compilera bırakırsak.
}


--------------------------------------------------------------------------------------------------

Der için ctoru ben yazsaydım 

class Base {
public:
	Base()
	{
		std:cout << base ctor;
	}
	Base(const Base &other)
	{
		std:cout << Base copy constructor;
	}
};

class Der : public  Base {
public:
	Der() = default;
	Der(const Der& other) : Base(other) //burada da upcasting vardı
	{									// base hayata gelirken other içindeki base kullanılacak.
										// Base(other) eklenmezse copy ctor değil bunun için default ctor çağrılır.Dikkat et.
										// Derleyici Base alt nesnesini hayata getirirken, other ın içindeki Base i kullanacak.
								
	}
}

int main()
{
	Der x;  // base ctor 
	Der y(x); // copy ctor çalışır eğer compilera bırakırsak.
}


============================================================================================================================================
============================================================================================================================================

COPY ASSIGNMENT
---------------
Burada da taban sınıf alt nesnesine, diğer nesne içindeki taban sınıf alt nesnesini atayacak.

class Base {
public:
	Base& operator=(const Base& other)
	{
		//.. kodlar
		std::cout << "base copy assignemnt\n";
		return *this;
	}
};


class Der : public  Base {
public:

}

int main()
{
	Der x, y;
	x = y; // burada derleyici yazdı ve base in copy asisgnmentını çağırdı
}

-------------------------------------------------------------------------------------------------

COPY ASSIGNMENTI BIZ YAZALIM
---------------------------

class Base {
public:
	Base& operator=(const Base& other)
	{
		//.. kodlar
		std::cout << "base copy assignemnt\n";
		return *this;
	}
};


class Der : public  Base {
public:
	Der& operator=(const Der& other)
	{
		// Aşağıdakiler recursive çağrı oluşturur.DİKKAT!!! 
		// operator=(other);
		// *this = other;    // Bu ikisi bu fonksiyonun kendi kendisini çağırmasını sağlar.
							 // Ama bizim amacımız taban sınıfın copy assignment functionunu çağırmak.

		//Aşağıdakiler geçerli !!!!
		Base::operator=(other);		//Base nesnesini içinde copy assignment çağrılıyor.
		static_cast<Base&>(*this) = other; //Bu da geçerli.
		*static_cast<Base*>(this) = other; //Bu da geçerli.

		return *this;
	}
}

int main()
{
	Der x, y;
	x = y; // yine çalışır.
}


-------------------------------------------------------

Aynı durum move Ctor içinde geçerli.

class Der: public Base{
public:
	Base& operator=(Base&& other)
	{
		Base::operator=(std::move(other));
	}
};


Derleyicinin yazdıkları zaten % 99 ihtiyacı karşılıyor.
Biz yazarsak, bunların ilgili kodlarından biz sorumluyuz.

=========================================================================
=========================================================================

Using Bildiriminin Kullanılması
------------------------------ -
3 adet kullanım gördük.
2 si namespacelerde diğeri ise alias verirken.

using iptr = int*;
using fcmp = int(*)(const void*, const void*); bunlar türeş ismi verirken.


Using in eklenmesi generic programlşama tarafı için asıl.
ileride görülecek.

std::pair<int, int>x; buradaki int ler template arguman

using epair = std::pair<T, T>;
int main()
{
	epair<int> x; // böylede kullanılır ileride görülecek.
}


------------------------------------------------------------------------------

class Base {
public:
	void func(int); //overloading değil

};

class Der : public Base {
public:
	void func(double); //overloading değil
};

int main()
{
	Der myder;

	myder.func(12);// sentaks hatası yok ama double parametreli func çağrılır.
}					// 2 double parametre olsaydı sentaks hatası olurdu

-------------------------------------------------------------------------------

Öyle bir kod yazki bu bir func overloading etkisi yaratsın.

class Base {
public:
	void func(int)
	{
		std::cout << "Base::func(int)\n";
	}

};

class Der : public Base {
public:
	void func(double)
	{
		std::cout << "Der::func(double)\n";
	}
};


int main()
{
	Der myder;

	myder.func(12);
	myder.func(1.2); // nasıl çalışacak ikisi birden ?
}

------------------------------------------------------------------

BIR FONKSIYON EKLEYEREK.

class Base {
public:
	void func(int)
	{
		std::cout << "Base::func(int)\n";
	}

};

class Der : public Base {
public:
	void func(int x) // bu şekilde çağırmış olduk.
	{
		Base::func(x);
	}

	void func(double)
	{
		std::cout << "Der::func(double)\n";
	}
};
int main()
{
	Der myder;

	myder.func(12);
	myder.func(1.2);
}

---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------

BUNU YAZMAMIZA GEREK YOK.BUNUN YERINE USING KULLANABILIRIZ.
SINIF IÇI USING BILDIRIMI YAPIYORUZ.

class Der : public Base {
public:
	using Base::func; // Bu bildirim sayesinde, base in içindeki func ismi Der içerisinde doğrudan visible hale geldi.

	void func(double)
	{
		std::cout << "Der::func(double)\n";
	}
};

----------------------------------------------------------------------------------------------

BUNUNDA İŞİMİZİ GÖRMEYECEĞİ BİR SENARYO VAR
class Base {
public:
	void func(int)
	{
		std::cout << "Base::func(int)\n";
	}

};

class Der : public Base {
public:

	using Base::func; //hem bu var

	void func(int) //hemde bu
	{
		std::cout << "Der::func(int)\n";
	}

	void func(double)
	{
		std::cout << "Der::func(double)\n";
	}
};
int main()
{
	Der myder;

	myder.func(12); // Bu durumda ambigiuty oluşmayacak. Türemiş sınıfın func ı çağrılacak.
	myder.func(1.2);
}


-----------------------------------------------------------------------------------------------------

SINIFIN PROTECTED FUNCTIONU VAR DIYELIM
---------------------------------------
Protected funclar, türemiş sınıfın implementasyonu tarafından kullanılabilen fonksiyonlardır.
Zaten kalıtım yoluyla elde edilecek sınıflar için yazılmış protected. Kalıtım yoluyla elde edilen
türemiş sınıf base sınıfın protected interface ini kendi public interface ine katmıyor.

class Base {
protected:
	void func(int)
	{
		std::cout << "Base::func(int)\n";
	}
};

class Der : public Base {
public:

};

int main()
{
	Der Myder;
	myder.func(23); hata
}

------------------------------------------------------------


Bunu nasıl mümkün kılarız?

//base class yukarıda yazılı

class Der : public Base {
public:
	void func(int x) // bu olur
	{
		Base::func(x);
	}
};


USING ilede olur
class Der : public Base {
public:
	using Base::func;
};

int main()
{
	Der Myder;
	myder.func(23); //ARTIK İKİ ŞEKİDLE DE HATA YOK.
}


-----------------------------------------------------------------------------------------------------------------
MODERN C++ ILE INHERITED CTOR GELDI.C++11 den de sonra. 17 ile gelmiş olabilir.
İleride görülecek

using Base::Base; Böyle bir using bildirimi yapınca taban sınıfın ctorları türemiş sınıfta görülür hale geliyor.


================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================




RUNTIME POLYMORPHISM / ÇALIŞMA ZAMANI ÇOKBİÇİMLİLİĞİ  48:00
-----------------------------------------------------------
OOP paradigmasına destek veren programlama dillerinin araç seti sentaksı farklı olabilir.

Kalıtımda taban sınıfımız olsun.Airplane sınıfı. Taban sınıfın interafce indeki funcionlar 3 e ayrılabilir

Airplane
1)Hem bir arayüz / interface, hemde bir kod / implementation veriyor.
Burada airplane den, airbus türetildiğinde, uçma kodu airplane den alınma kod olacak.

2)Hem bir arayüz / interface, hemde bir kod / Default implementation veriyor.
Airplane diyorki tüm uçaklar uçar.Ama hangi kodla uçaçak siz seçeceksiniz.
İSterseniz ben vereyim istersenizde siz kendi kodunuzu kullanacaksınız.

Ben default kodu istemiyorum, kendi kodumu oluşturacağım, runtime da bu kod kullanılsın anlamında yapılan eyleme
bu fonksiyonu OVERRIDE etmek deniyor. Overload değil, override.

3) bir arayüz / interface veriyor ama kod / implementation vermeyen.
Kodun türemiş sınıf tarafından oluşturması bekleniyor.Burada mecbur kod oluşturmak
gerekiyor.Burada ilgili functionu override etmek deniyor.Hem 2. durumda hemde 3. de var.


2. si override edebilirim veya taban sınıfın kodunu alabilirim.
3. de zaten implementation yok.Dolayısı ile kendi kodumuzu oluşturmalıyız.
Yine override.



C++ TA BIR SINIF
----------------
2. KATEGORIDEN EN AZ BIR FONKSIYONA SAHIPSE BÖYLE SINIFLARA POLIMORPHIC SINIF DENIYOR.
HEM BÖYLE SINIFLARA HEMDE BU SINIFLARDAN KALITIM YOLUYLA ELDE EDILEN SINIFLARA DENIYOR.
3. KATEGORIN EN AZ BIR FONKSIYON VARSA BÖYLE SINIFLARADA ABSTRACT / SOYUT CLASS DENIYOR.

C++ TA BIR SINIF YA ABSTRACT / SOYUT,  VEYA CONCRETE / SOMUT TUR.
C++ TA SOYUT SINIFLAR TÜRDEN NESNE OLUŞTURMAK BIR SENTAKS HATASI. NESNE OLUŞTURULACAKSA O SINIF SOMUT OLMALI.

-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------

SENTAKS

1. Kategori
-----------

class Base {	// bildiğimiz class. 1. kategori
public:
	void func(int);
};


2. Kategori
--------------

class Airplane {
public:
	void takeoff(); 
	virtual void land(); //DİKKAT !!!!!!!!!
};

virtual 2. kategoriyi temsil ediyor. Bu tür funclara sanal member function deniyor.
İster benim kodumu kulanırsın ister kendi kodunu kullanırsın. Land için türemiş sınıfın kendi kodunu kullanmasına, override etmesi deniyor.
Override ta overload gibi isim anlamında da kullaılıyor.
Türemiş sınıfın bir override ı denir. Şu kadar sayıda override ı var da denebilir.
Hem isim hem fiil

virtual void land(); olmasaydı airplane sınıfı nonpolimorphic olacaktı.
En az bir sanal functiona sahipse, şimdi artık polimorphic sınıf oldu.Airplane den kalıtım yoluyla elde edilen
tüm sınıflarda polimorphic sınıflar olacaklar.


3. Kategori(interface veren implementation vermeyen)
----------------------------------------------------

Sentaksı garip.Diğer dillerde abstract keyword kullanılıyor.
Burada sentaks ile yapılıyor.Abstract sınıftan kalıtım yapılınca tüm pure virtual functionların somut olması için
override etmek gerekiyor. Override edilmezse soyut sınıf olacak.


class Airplane {
public:
	void takeoff(); 		//Nonvirtual function. Buna dokunmamak lazım
	virtual void land(); 	// Virtual Function /sanal.Buna ister yaz override et, istersende verileni kullan
	virtual void fly() = 0; //Pure virtual function / saf sanal.func ı Override etmek gerekir.Yoksa soyut sınıf olur ve nesne üretilemez.
};

AIRPLANE SINIFI POLIMORPHIC SINIF AYNI ZAMANDA ABSTRACT BIR SINIF.AIRPLANE DEN KALITIMLA BIR SINIF ELDE EDILDIĞINDE EĞER O SINIF
BU FONKSIYONU OVERRIDE ETMEZSE O SINIFTA SOYUT BIR SINIF OLACAK.

SENTAKS
--------
virtual void fly() = 0;

0 a eşitleniyor.İmplementasyonu yok demek bu.
Sentaks bu : D

--------------------------------------------------------------------------------

virtual void land(); -- > buna ister dokunurum ister kullanırım direk
virtual void fly() = 0; -- > burada ise implementasyon yazacağız.

1. Burada en az 1 tane pure virtual functiona sahip olması sınıfı abstract yapıyor.
2. Abstract sınıftan kalıtım yapınca, abstract sınıfın tüm pure virtual functionlarını override etmek gerekiyor.
	Gerekiyor derken somut sınıf olması için. 1 tane bile functionu bile override etmezsek, kalıtım yoluyla elde ettiğimiz sınıfta
	yine soyut bir sınıf olacak.

SOYUT OLUNCA NE OLUYOR ?
NESNE OLUŞTURMAK SENTAKS HATASI OLUYOR AMA BU SINIFI POINTER VEYA REFERANS SEMANTIĞI ILE KULLANABILIYORUZ.

NOT : GLOBAL FUNCLAR VE STATIC MEMBER FUNCTION SANAL FUNCTION OLAMAZLAR.

----------------------------------------------------------------
ÖR:
class Airplane {
public:
	void takeoff();
	virtual void land();
	virtual void fly() = 0;
};

int main()
{
	Airplane ax; //SENTAKS HATASI.Çünkü Abstract class türden nesne oluşturulamaz.
}

Bu sınıfı pointer veya referans semantiği ile kullanabiliyoruz.

void flight_game(Airplane*);
void flight_game(Airplane&); Bu ikisi olabilir.

------------------------------------------------------------------

SONUÇ:
takeoff diyorki herkes bu kodu kullanacak.
fly diyorki ister benim kodumu kullanın ister kendi kodlarınızı oluşturun.
land diyorki kendi kodlarınızı oluşturmanız gerekiyor.

NOT : TEKRAR. GLOBAL FUNCLAR VE STATIC MEMBER FUNCTION SANAL FUNCTION OLAMAZLAR.

class Airplane {
public:
	void takeoff();
	static int virtual foo(); // SENTAKS HATASI

	virtual void fly() = 0;
	virtual void land();
};

virtual int foo(); // SENTAKS HATASI

Sınıfın nonstatic member functionları sanal olabiliyor.
Veri elemanları veya nested typelar için virtual kullanılamıyor.

Override edince ne oluyor ? avantajlar neler ? nasıl yapılıyor ? ? ? ...
Tüm sorular açıklanacak ?

============================================================================================================================
============================================================================================================================
============================================================================================================================
============================================================================================================================


VIRTUAL - POLYMORPHIC DISPATCH / SANAL GÖNDERİM
-----------------------------------------------

Araba yarışı düşünelim şimdi.Car sınıfı kalıtımda kullanılacak taban sınıf olsun.
Aşağıdaki fonksiyonda Car türünden kalıtımla elde edilmiş tüm sınıf nesnelerini aşağıdaki fonksiyona gönderebilirim.
Upcastingden ötürü bu olur.Car dan türemişlerin içerisindeki car nesnesinin adresi ile işlemler yapılır.
Bundan bahsedildi önceki derste.Upcasting.

void game(Car &car)
{
	car.start();
	car.run();
	car.accelerate();
	car.stop();
}

Burada arabaya özgü start run ... kodların çalıştığını düşünelim.
Burada hangi fonksiyonun çağrılacağı runtime da belli oluyor. Buna runtime polymorpism deniyor.

Hangi fonksiyonun çağrıldığı runtimeda anlaşılacak. Hangi araba modeli gelecekse ona göre function çağrılacak.
Eski kodların yeni kodları kullanması olayı bu. Eskiden olmayan bir skoda sınıfını Car sınıfından kalıtım yoluyla elde edersem,
game koduna skoda nesnesi gönderilirse, skodanın nesnesinin fonksiyonu çağrılabilir.Buna runtime polymorphism deniyor.

----------------------------------------------------------------------------------------------------------------

Virtual Dispatch Ne demek?
--------------------------

class Car {
public:
	void start()  // virtual olmasaydı
	{
		std::cout << "Car has started\n";
	}
};

class audi : public Car {
public:
	void start()	// buradaki start, Car dakini maskeler.
	{
		std::cout << "Audi has started\n";
	}
};

void car_game(Car &car)
{
	car.start();
}

int main()
{
	Audi myaudi;
	car_game(myaudi); //car sınıfının üye fonksiyonu çağrılacak burada.
}						//burada early / static binding var.hangi func ın çağrıldığı
						// burada compile time da belli olur.

early binding / static binding compile timeda,
late binding / dynamic binding te runtime da belli oluyor.

------------------------------------------------------------------------------------------

Virtualı koyunca ne oluyor ?
Anlatılacak hepsi

class Car {
public:
	virtual void start()
	{
		std::cout << "Car has started\n";
	}
};

class audi : public Car {
public:
	void start()
	{
		std::cout << "Audi has started\n";
	}
};

void car_game(Car &car)
{
	car.start();
}

int main()
{
	Audi myaudi;
	car_game(myaudi); //RUNTİME POLYMORPHİSMDEN ÖTÜRÜ audi has started yazacak.
}

Audi has started yazdı.Burada kullanılan mekanizmaya virtual dispatch deniyor.


-------------------------------------------------------- -

ŞİMDİ arabalar ekleniyor

class Car {
public:
	virtual void start()
	{
		std::cout << "Car has started\n";
	}
};

class Audi : public Car {
public:
	void start()
	{
		std::cout << "Audi has started\n";
	}
};

class fiat : public Car {
public:
	void start()
	{
		std::cout << "fiat has started\n";
	}
};

class mercedes : public Car {
public:
	void start()
	{
		std::cout << "Mercedes has started\n";
	}
};

void car_game(Car & car)
{
	car.start();
}

int main()
{
	Audi myaudi;
	Fiat myfiat;
	Mercedes mymercedes;
	car_game(myaudi); // audi has started
	car_game(myfiat); // fiat has started
	car_game(mymercedes); //mercedes has started
}

ÇIKTI
-----
Audi has started
fiat has started
Mercedes has started

---------------------------------------------------------------------------

Programın runtimeda mı çağırıyor?İSPATI


Car* create_car()
{
	switch(rand() % 4)
	{
		switch 0; return new Audi;
		switch 1; return new Fiat;
		switch 2; return new Mercedes;
		switch 3; return new Volvo; //volvoyuda kalıtım yoluyla elde etmek lazım. alta yazdığım kodu ekliyorum.

	}
}

class Volvo : public Car{ // bunuda kalıtım yoluyla elde ettiğimizi düşünelim. Çeşitlilik için yazdık.
public:
	void start()
	{
		std::cout << "Volvo has started\n";
	}
}


EKLENMİŞ HALİ
-------------
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
class Car {
public:
	virtual void start()
	{
		std::cout << "Car has started\n";
	}
};

class Audi : public Car {
public:
	void start()
	{
		std::cout << "Audi has started\n";
	}
};

class Fiat : public Car {
public:
	void start()
	{
		std::cout << "fiat has started\n";
	}
};

class Mercedes : public Car {
public:
	void start()
	{
		std::cout << "Mercedes has started\n";
	}
};

class Volvo : public Car { // bunuda kalıtım yoluyla elde ettiğimizi düşünelim. Çeşitlilik için yazdık.
public:
	void start()
	{
		std::cout << "Volvo has started\n";
	}
};


void car_game(Car& car)
{
	car.start();
}

Car* create_car()
{
	switch (rand() % 4)
	{
		case 0: std::cout << "Audi Case\n"; return new Audi;
		case 1: std::cout << "Fiat Case\n"; return new Fiat;
		case 2: std::cout << "Mercedes Case\n"; return new Mercedes;
		case 3: std::cout << "Volvo Case\n"; return new Volvo; //volvoyuda kalıtım yoluyla elde etmek lazım. alta yazdığım kodu ekliyorum.

	}
}

int main()
{
	srand((unsigned int)time(nullptr));

	for (;;)
	{
		auto p = create_car();
		car_game(*p);
		_getch();
		delete p;
	}
}



================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================



VIRTUAL DISPATCH MEKANIZMASI
----------------------------

Türemiş sınıfın taban sınıfın üye fonksiyonunu override etmesi için, hem geri dönüş değeri türü aynı,
hemde parametrik yapısı(imzası) aynı olan bir fonksiyon bildirmesi gerekiyor.

class base {
public:
	virtual void func(int, int);
};

class Der : public Base {
public:
	void func(int, int); // Bu func ı bildirerek base sınıfın func isimli fonksiyonunu override etmiş oldum
						 // modern C++ ta asla bu şekilde override etmeyeceğiz.Halen geçerli ama tercih edilmiyor.
						 // Alttaki tercih edilir.

	void func(int, int)overide; // bu override keyword değil. contexual keyword
};								// yazmazsak sentaks hatası olmaz.Ama yazılmalı.Yoksa birtakım kötü hata senaryoları oluşabilir.


----------------------------------------------------------------------------------------------------------------------------------

KURAL
-----
Base deki func sanal olmasaydı, int func(int, int) türemiş sınıf içinde tanımlanabilirdi.
Ama base deki virtual olarak define edilince(sanal fonksiyon olunca) farklı bir return değer bildiremez.SENTAKS HATASI
Türemiş sınıf taban sınıfın sanal fonksiyonu ile aynı imzaya sahip, fakat geri dönüş değeri türü farklı bir fonksiyon bildiremez.
Bu sentaks hatası oluşturur.

ÖR:
class base {
public:
	virtual void func(int, int);
};

class Der : public Base {
public:

	int func(int, int);  BURASI SENTAKS HATASI.Return değer farklı
};


AŞAĞISI ISE GEÇERLI.
class base {
public:
	void func(int, int);
};

class Der : public Base {
public:

	int func(int, int);  BURASI GEÇERLİ.Çünkü base classtaki virtual değil.
};

---------------------------

ÇOK ÖNEMLİ
Geri dönüş değeri türü aynı veya farklı ama parametrik yapısı(imzası) farklı bir fonksiyon bildirmem bir SENTAKS HATASI DEĞİL ama 
override da değil.

class base {
public:
	virtual void func(int, int);
};

class Der : public Base {
public:

	void func(int);  //GEÇERLİ AMA OVERRIDE DEĞİL.Return değeri aynı ama imzası farklı.
};

---------------------------

OVERRIDE OLMASI IÇIN HEM RETURN DEĞERI TÜRÜ HEMDE IMZASI AYNI FONKSIYON BILDIRMELIYIZ.

class base {
public:
	virtual void func(int, int);
};

class Der : public Base {
public:

	void func(int,int)override;  //Olması gereken bu. Override yazılmış.
};



-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

OVERRIDE OLUNCA ELİMİZE NE GEÇER?
--------------------------------
Türemiş sınıf, taban sınıfının func isimli virtual fonksiyonunu override ederek, virtual dispatch mekanizmasından faydalanma hakkını
elde etti.

Virtual Dispatch nedir : Eğer taban sınıfın bir sanal foksiyonu, bir taban sınıf pointerı ya da bir
taban sınıf referansı ile çağrılırsa çalışma zamanında çağrılan fonksiyon o pointer yada referans 
hangi türden sınıf nesnesini gösteriyorsa, o sınıfın üye fonksiyonu olacak.

class base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}
};

class Der : public Base {
public:
	void func()override //Burada da virtual yazabilirdik.Arada fark yok. virtual void func()override ... yazabilirdik yani.
	{
		std::cout << "Der::func()\n";
	}

};

Burada override etti.Türemiş sınıfta func başına virtual yazıladabilir yazılmayadabilir.
Allah yazandan da yazmayandan da razı olsun :D:D

Virtual dispatch - Yukarıda da yazmıştım
-------------------------------------------
Eğer taban sınıfın bir sanal foksiyonu, bir taban sınıf pointerı ya da bir
taban sınıf referansı ile çağrılırsa çalışma zamanında çağrılan fonksiyon o pointer yada referans 
hangi türden sınıf nesnesini gösteriyorsa, o sınıfın üye fonksiyonu olacak.
Bunu bir örnek ile görelim.

1. BİÇİMİ
---------

ÖR:
class base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}
};

class Der : public Base {
public:
	void func()override
	{
		std::cout << "Der::func()\n";
	}

};

int main()
{
	Der myder;
	Base* baseptr = &myder;
	baseptr->func(); // der:func() çağrıldı.
	//veya (*baseptr).func(); yine çalışır.

	//referans semantiği ilede çalışır.
	//Base &baseref = myder;
	//baseref.func(); yine geçerli. 

}

TEKRAR
Eğer çağrı taban sınıf ptr ile yapılıyorsa, taban sınıf hangi türden(hangi türemiş sınıf nesnesi) nesneyi gösteriyorsa,
o sınıfın func fonksiyonu çağrılacak.O sınıfın override ı çağrılacak. Eğer override etmemişse taban sınıfın func ı çağrılacak


----------------------------------------------------------

2. BİÇİM

En çok karşımıza çıkan senaryolardan biri, sanal fonksiyona yapılan çağrının bir fonksiyonun parametresi yoluya yapılması.

class base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}
};

class Der : public Base {
public:
	void func()override
	{
		std::cout << "Der::func()\n";
	}

};

void gfoo(Base *p) // referansta olabilirdi parametre. void gfoo(Base& baseref) olabilirdi.
{
	p->func();
}

int main()
{
	auto pder = new Der;
	gfoo(pder); // "Der::func()"
}

------------------------------------------------------

Eğer çağrı Taban sınıf pointerı veya referansı değilde, taban sınıf değişkeni yoluyala yapılırsa asla
sanallık mekanizması devreye girmiyor. Sınıf türünden değişkenle yapılan çağrılarda bu devreye girmiyor.



int main()
{
	Der myder;
	Base mybase = myder; //tercih edilmiyor.object slicing deniyor
	mybase.func(); // artık virt dispatch olmayacak burada.Compile time da belli oluyor çünkü.
}					// taban sınıfın func fonksiyonunu çağıracak.

Vİrtual Dispatch devreye girmesi için, fonksiyon çağrısının taban sınıf pointer veya referansı ile yapılması gerekiyor. 

--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------

3. BİÇİM
--------
Sanallık mekanizmasının devreye girdiği çok önemli bir senaryo daha var.
Hatta bu design pattern ile alaklı.

class Base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}

	void foo() // bu sayede virtual func çağrılmış olur.
	{
		func();
	}
};

class Der : public Base {
public:
	void func()override
	{
		std::cout << "Der::func()\n";
	}

};

int main()
{
	Der Myder;
	myder.foo();// Der::func() çağrıldı.
}

Aslında burada this ile yapılıyor gizli parametre. İçerideki çağrıda taban sınıf pointerı ile yapıldığı için
Virtual dispatch gerçekleşiyor. Taban sınıf pointerı hangi türden nesneyi gösteriyorsa, onun override ı çağrıldı.

3 Biçimide yazalım
------------------
1 - Taban sınıf ptr/referans ile doğrudan yapılan çağrılar
2 - Taban sınıf referans/ptr ile doğrudan yapılan fonksiyon çağrıları
3 - Sanal olmayan member func içinde taban sınıfın sanal olan üye fonksiyon çağrıldığında virtual dispatch devreye giriyor.


============================================================================================================================
============================================================================================================================
============================================================================================================================
============================================================================================================================



ÖNEMLİ SENTAKS KURALLARI
------------------------
Taban sınıfın virtual fonksiyonunu, override eden türemiş sınıf fonksiyonu,
bildirimde virtual keyword kullanılsada kullanılmasada sanaldır.

class base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}

	void foo()
	{
		func();
	}
};

class Der : public Base {
public:
	virtual void func()override // burada virtual yazabilir yada yazmayabilir. fark yok.(override içinde geçerli ama yazmak doğru kullanım)
	{
		std::cout << "Der::func()\n";
	}

};


--------------------------------------------------------------------------

Geçen derslerde multilevel inheritance terimin kullanmıştık.
Elde ettiğimiz bir türemiş sınıftan, onu taban sınıf olarak kullanıp başka bir türemiş sınıf oluşturabiliriz !!!!!!!!!!

class base {
public:
	virtual void func()
	{
		std::cout << "Base::func()\n";
	}
};

class Der : public Base {
public:
	void func()override // burada virtual yazabilir yada yazmayabilir. fark yok.
	{
		std::cout << "Der::func()\n";
	}

};

class NecDer : public Der {
public:
	void func()override // NecDer de func ı override ettiği için virtual dispatch ten faydalanabilecek.
	{
		std::cout << "NecDer::func()\n";
	}
};

void gfoo(Base &baseref) // dikkat hep Base class obhe adresi ile işlemler yapılıyor.
{
	baseref.func();
}

int main()
{
	NecDer nd;

	gfoo(nd); //necder::func() çağrıldı.
}

Not : Her Der nesnesi bir base nesnesidir.
	  Her Necder nesnesi o da bir base nesnesidir.
	  Aynı zamanda her Necder aynı zamanda Der sınıfı türünden bir nesnedir.


=================================================================================================================================
=================================================================================================================================

Modern C++ ta  Contexual Keyword / bağlamsak anahtar sözcük eklendi.

2 tane var şuanda.
override ve final

Belirli bir contextte kullanılınca keyword gibi çalışıyor ama onun dışında kullanıldığında identifier olarak ele kullanılıyor

int main()
{
	int for;			//for değişken ismi yapılamaz
	int override = 1;	//burası geçerli ama kötü bir fikir.
}


Sebebi,
Geriye dönük uyumluluk.Eskiden bunlar isim olarak kullanılmış olabilir.Geçmişe dönük kodların legal olarak kalması için var.
Şuanda keyword.Bu sebeple iki anlamda da kullanılıyor.

Override Sözcüğü ne yapıyor.ÇOK ÖNEMLİ !!!!
Eğer taban sınıfın bir üye fonksiyonunu override ederken, override keywordünü kullanmazsam, derleyici böyle bir 
sanal fonksiyon var mı kontrolünü yapmıyor.Bunun çok kötü sonuçları var.
Bu kötü sonuç senaryolarına bakalım


1. SENARYO
-----------
class Base {
public:
	virtual void foo()const;

};

class Der : public Base {
public:
	void foo(); //sentaks hatası değil. Override değil. Yeni bir function.
};				// Bildirirken başına virtual koysam yeni bir sanal function olacak.Yukarıdaki sanal func ile alakasıda yok.
				// Eğer Modern C++ta void foo()override; deseydik SENTAKS HATASI olacaktı. Artık bu taban sınıftaki bir üye fonksiyonun
				// override ı olduğunu söylediğimiz için, derleyiciye bir kontrol yükümlülüğü geliyor.

Yani Override edeyim derken, yanlış bir imza kullanmak sentaks hatası haline geliyor.

---------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------

2. SENARYO
-----------

class GuiWidget
{
public:
	void set_text(const std::string& msg);
};

class NecoWidget : public GuiWidget {
public:
	void set_text(const std::string& msg)override; //SENTAKS HATASI.virtual function yok çünkü
};												   //Eğer burada override yazılmasaydı SENTAKS HATASI OLMAYACAKTI.


---------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------

3. SENARYO
-----------

class Car{
public:
	virtual void run(float speed);
};

//header.h
class Dacia : public Car {
public:
	void run(float speed);
};


Diyelim ki run ın parametresi float idi, ama artık double oldu.Bu durumda artık derived class taki func override değil.
Çünkü farklı bir imzaya sahip.Eğer override kullanılmış olsalardı, burada bir interface değişikliğinde proje recompile edildiğinde
SENTAKS HATASI OLURDU.Çünkü run artık override değil.

AŞAĞIDA YAZDIM

class Car
{
public:
	virtual void run(double speed);
};

//header.h
class Dacia : public Car {
public:
	void run(float speed);  // artık override yok.SENTAKS HATASI DA YOK.
};



Ama burada override kullanılsaydı.
class Car
{
public:
	virtual void fun(double speed);
};

//header.h
class Dicia : public Car {
public:
	void run(float speed)override;  // SENTAKS HATASI OLDU
};

--------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------

CPP file HEADER file kullanımında,
Virtual bildirimde yer alır ama tanımda yer alamaz. İnline tanımlanırsa tanımda yazılabilir tabi.
AYnı şekilde override keywordde bildirimde olmalı.inline yazınca yazılabilir yine.

--------------------------------------------------------------------------------------------------

Örneklerde fazla zaman kaybetmemek için başlık dosyası ekledi.

class Car { // bıradaki I, pure virtual funclar var interface anlamında.
public:
	virtual void start() = 0; // Pure virtual func .Bu tip classlara abstract class deniyor.
	virtual void run() = 0;
	virtual void stop() = 0;
};



==================================
==================================
==================================

BU KISIM HEADER FILE İÇERİSİNE KONULACAK.

//car.h
class Car {
public:
	virtual void start()
	{
		std::cout << "Car has just started\n";
	}
	virtual void run()
	{
		std::cout << "Car is running\n";
	}
	virtual void stop()
	{
		std::cout << "Car has stopped\n";
	}

	virtual ~Car() {} //Birsonraki derste anlatılacak.
};


class Bmw : public Car {
public:
	virtual void start()override
	{

		std::cout << "BMW has just started\n";
	}
	virtual void run()override
	{
		std::cout << "BMW is running\n";
	}
	virtual void stop()override
	{
		std::cout << "BMW has stopped\n";
	}
};


class Audi : public Car {
public:
	virtual void start()override
	{
		std::cout << "Audi has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Audi is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Audi has stopped\n";
	}
};


class Mercedes : public Car {
public:
	virtual void start()override
	{

		std::cout << "Mercedes has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Mercedes is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Mercedes has stopped\n";
	}
};

class Fiat : public Car {
public:
	virtual void start()override
	{

		std::cout << "Fiat has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Fiatis running\n";
	}
	virtual void stop()override
	{
		std::cout << "Fiat has stopped\n";
	}
};


class Fiat124 : public Fiat { //DİKKAT!!!!!!!!
public:
	virtual void start()override
	{

		std::cout << "Fiat124 has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Fiat124 is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Fiat124 has stopped\n";
	}
};

Car* create_random_car()
{
	switch (rand() % 8)
	{
	case 0: return new Bmw; // bunların hepsinde upcasting var.
	case 1: return new Mercedes;
	case 2: return new Audi;
	case 3: return new Fiat;
	case 4: return new Volvo;
	case 5: return new Fiat124;
	case 6: return new Renault;
	case 7: return new Skoda;
	}

	return nullptr;
}


HEADER BURADA BİTTİ

==============================================================================================================
==============================================================================================================
==============================================================================================================
==============================================================================================================


MAIN İÇERİSİ

i#include <iostream>
#include "car.h"
#include <conio.h>
#include <ctime>

void car_game(Car* p)
{
	p->start();
	p->run();
	p->stop();
	std::cout << "----------------------------------------\n";
}

int main()
{
	srand((unsigned int)time(nullptr));
	for (;;)
	{
		auto p = create_random_car();
		car_game(p);
		_getch();
		delete p;
	}
}

17 Dakikalık kısmı hoca kaydetmeyi unuttu. Çok öneli değil. Sadece örnek çalıştırıldı birde fiat124 e bak.
17 Dakikalık Kısım 1. ve 2. madde.Birde kütüphaneye koyduğu kodu çalıştırıp gösterdi.

Özet
----
1 - Fonksiyon çağrısı taban sınıf türünden bir değişkenle yapılırsa bu durumda sanallık mekanizması devreye girmiyor.

2 - Fonksiyon çağrısında nitelenmiş isim kullanılırsa, ÖR: carptr->run(); BURADA SANALLIK DEVREYE GIRECEK ama
	carptr->Car::run(); BURADA SANALLIK DEVREYE GIRMEYECEK. Olay Base olan sınıfın adresi/referanslı olan çağrılarda bitiyor.
	muhtelemen Car carptr = new bmw; carptr->run(); yapınca devreye girdi. Bu kısma bak test et.

3 - Ctor içinde yapılan Virtual func çağrıları.
	Bir mercedes nesnesi oluşturduğumda ve Mercedes nesnesi içindeki car nesnesi için ctor
	çağrıldı, ama çağrılan car sınıfının run functionu oldu, mercedes sınıfının değil.
	
	Car Constructor
	Car is running yazdırdı
	NEDEN? 

	Biz bir türemiş sınıf nesnesi hayagetirdiğimizde önce onun base classı/tabansınıf nesnesi hayata gelir.
	Mercedes mymercedes; yazdığımızda ilk önce base classın ctoruna girer. buradaki işlemlerden sonra mercedes için 
	ctor çağıracak. Şuanda Base in ctorunda iken mercedes henüz hayatta değil.Bu noktada sanal fonksiyon çağrılsaydı 
	ve sanallık mekanizması devreye girseydi çağrılan mercedesin run functionu olsaydı, oluşmamış mercedesin fonksiyonunu çağırmaya
	çalışmış olacaktık.BU UNDEFINED BEHAVIOR.

	TEKRAR: TABAN SINIF CTORU IÇINDE YAPILAN SANAL FUNCTIONA ÇAĞRIDA VIRTUAL DISPATCH OLMUYOR. UYGULANSAYDI TÜREMIŞ SINIF NESNESI
	HAYATTA DEĞILKEN ONUN RUN FONKSIYONUNU KULLANMAYA ÇALIŞMIŞ OLACAKTIK.TANIMSIZ DAVRANIŞ OLACAKTI.
	TABAN SINIF CONSTRUCTORI IÇINDEN, TABAN SINIFIN SANAL FUNCTIONALARINA ÇAĞRI YAPMA.YAPARSANDA DEVREYE GIRMIYOR.

4 - Taban sınıf destructoru için düşünelim. 
	int main()
	{
		{
			Mercedes mymercedes;
		}
		std::cout << "main devam ediyor\n";
	}

	Programın akışı mercedesin destructoruna gelecek.Destuctorın sonunda da taban sınıf alt nesnesi için destructor çağrılacak
	ve taban sınıf nesnesi için çağrılan destructorda sanal function çağrıldı.Virt dispatch devreye girseydi mercedesin run
	functionuna yapılan çağrı görünecekti.

	Çıktı
	------
	Car Constructor
	Car is running
	Car Destructor
	main devam ediyor

	TABAN SINIFIN DESTRUCTORU IÇINDE SINIFIN SANAL BIR FUNCTIONUNA ÇAĞRI YAPILIRSA VIRTUAL DISPATCH DEVREYE GIRMEZ.
	ÇAĞRILAN TABAN SINIFIN KENDİ FUNCTIONU OLUR.

	TÜREMİŞ SINIFIN DESTRUCTORU ÇAĞRILDIĞINDA İÇİNDEKİ TÜM KODLAR ÇALIŞIYOR.YANİ TÜM KAYNAKLAR GERİ VERİLİYOR DEMEK.ELEMANLARDA
	DESTROY OLMUŞ DURUMDA. YANİ TABAN SINIF ALTNESNESİ İÇİN ÇAĞRILAN DESTRUCTORA GELİNCE SIRA, TÜREMİŞ SINIF İÇİN NESNE KALMADI.
	SANALLIK MEKANİZMASI DEVREYE GİRSE HAYATI BİTMİŞ OLAN BİR NESNE İÇİN FUNC ÇAĞRILMIŞ OLURDU.UNDEFINED BEHAVIOR.

	-----------------------------------------------------------------------------------------------------------------------------
	-----------------------------------------------------------------------------------------------------------------------------

	ÖZET:
	1 - DEĞİŞKEN YOLUYLA YAPILAN SANAL FONKSİYON ÇAĞRILARINDA VİRTUAL DİSPATCH YOK.OBJECT SLİCİNG KONUSU
	2 - ÇÖZÜNÜRLÜK OPERATÖRÜYLE FONKSİYONUN İSMİ YAZILIRSA YİNE SANALLIK MEKANİZMASI YOK.
	3 - CONSTRUCTOR İÇİNDE YAPILAN SANAL FUNCTİON ÇAĞRILARINDA VİRTUAL DİSPATCH YOK.
	3 - DESTRUCTOR İÇİNDE YAPILAN SANAL FUNCTİON ÇAĞRILARINDA VİRTUAL DİSPATCH YOK.



===========================================================================================================================

TİPİK YANLIŞ ANLAŞILMALAR.
--------------------------
Destructoru boş duruma getirdi yarınki ders için.
Bu örneklerden yürüyeceğiz.:D

ÖR:Bmw nin startını yorum satırı yapıp private bölüme koyduk.

class Bmw : public Car {
public:
	virtual void run()override
	{
		std::cout << "BMW is running\n";
	}
	virtual void stop()override
	{
		std::cout << "BMW has stopped\n";
	}
private:
	//virtual void start()override
	//{
	//	std::cout << "BMW has just started\n";
	//}

};

void car_game(Car* p)
{
	p->start();
	p->run();
	p->stop();
	std::cout << "----------------------------------------\n";
}

int main()
{
	//srand((unsigned int)time(nullptr));
	//for (;;)
	//{
	//	auto p = create_random_car();
	//	car_game(p);
	//	_getch();
	//	delete p;
	//}
}

1. soru bmw nin start functionunu sınıfın private bölümüne yazarsam Sentaks hatası olurmu ? değilse main içindeki kodu derleyince 
sentaks hatası olur mu? yine hayırsa, runtimede car_game e bir bmw geldiğinde sonuç ne olur?

Cevap : 
Private bölümde olabilir hiçbir hata yok.Virtual funcionu sınıfın private bölümünde override edebiliriz.

Maindeki kod çalışır hata olmaz. cargame argümanı base class türden.Hata yok.Eğer bmw türden olsaydı
burada compile time a ilişkin bir durum oluşacaktı ve access kontrole takılacaktı.Çok önemli.Ayrıca Car nesnesinin
içindeki start ta private olsaydı access controle takılırdı.Ama private değil.Access control compile time ile alakalı

Runtime da ise virtual dispatch mekanizması devreye girer.Kodlar sorunsuz çalışır.

Hiçbir hata yok.Ne compile time ne de runtime.

Taban sınıfın sanal functionu türemişin privateında override edilebilir.


AMA
Bmw *p = new Bmw;
Car *cp = p;

cp->start(); //HİÇBİR HATA YOK.Acces control burada car sınıfına göre yapılır ve start çağrılır.
p->start(); //BURASI SENTAKS HATASI.ACCESS CONTROLE TAKILIR. PRİVATE KISMINA ALMIŞTIK.

delete p;


------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

Programlama dillerinde tür kavramı sözkonusu olunca bazı diller static tür kavramına sahip,
bazı dillerde dinamik tür kavramına sahip. C static tür kavramına sahip. Python dinamik türkavramına sahip.

Ne demek bu Static tür ve dinamik tür?
Statik tür, değişkenlerin türü çevirici program tarafından koda bakarak anlaşılıyorsa buna statik tür denir.compile time belli oluyor
Dinamik tür, türün ne olduğunun programın runtime da belli olmasıdır.

C++ java C# static tür kavramına sahip ama bazı koşullarda dinamik tür kavramınıda destekliyorlar.
C++ ta dinamik tür kavramı polimorfik sınıflarda devreye giriyor.

Car *p;

*p nin türü nedir? Car dır.Buna statik tür denilecek.

Birde runtimeda davranışa esas tür var
p->start() denildiğinde kimin start fonksiyonunun çağrılacağı, runtimeda o anda hangi nesne gösteriliyorsa o nesnenin ait olduğu
sınıfın start fonksiyonu çağrılacak.

Compile time açısından bakarsak *p, Car türünden
Davranışsal açıdan bakarsak *p, programın çalışma zamanında buraya gelen Mercedes ise, *p mercedes gibi davranacak, audi ise
*p bir audi olacak. Buda dinamik tür.
 
ÇOK ÖNEMLİ!!!!!!!!!!!!!!!!!!!!!!!!!
VIRTUAL DISPATCH TE DAVRANIŞI BELIRLEYEN DINAMIK TÜR AMA ISIM ARAMA VE ACCESS CONTROL STATIC TÜRE ILIŞKIN !!!!!!!!!!!!!!!!!!!
Static tür compile time daki kontroller açısından derleyicinin koda static olarak çeviri sürecinde bakması durumunda kullanılan tür.

Soru:
Neden p->start() ifadesi için derleyici sentaks hatası vermedi?
Access control compile time a ilişkin.Dolayısı ile access kontrolede her zaman static tür kullanılıyor.
Ama start functionu car sınıfının private sınıfı yaptığımızda sentaks hatası olur.

Bir ÖR:
Bmw nin start fonksiyonunu yine sınıfın public kısmına aldık.
Bmw sınıfına open_sunroof ekliyoruz.
void open_sunroof(); bu car sınıfında olan bir funtion değil.Yani ortak interface te yok.
Ama bmw de olduğundan bmw nin cam tabanını bu fonksiyona çağrı yaparak açabiliriz.

p->open_sunroof(); //p, Car* nesnesi. Burası Compile time hatası. Çünkü static tür olarak bakıyoruz.İsim arama hatası verir.


Mülakat Sorusu
--------------
class Base{
public:
	virtual void func(int x = 77)
	{
		std::cout << "Base x = " << x << "\n";
	}
};

class Der : public Base{
public:
	virtual void func(int x = 33)override
	{
		std::cout << "Der x = " << x << "\n";
	}
};

void foo(Base *p)
{
	p->func();
}

int main()
{
	foo(new Der);
}
Ne yazar ? 
Der x = 77

Sanallık devreye girer ama varsayılan argüman static türe göre yapılıyor.Tıpkı isim aramada olduğu gibi.
Ok operatörünün solundaki base türünden ptr olduğu için buradaki 77 olan varsayılan alınacak.

Değişiklik
Der *dp = new Der;

foo(dp); //burada taban sınıfın varsayılan argümanı kullanıldı

dp->func(); // burada ise static tür der olduğu için der sınıfının varsayılan argümanı 33 kullanıldı.


==================================================================================================================
==================================================================================================================
==================================================================================================================
==================================================================================================================

YARINKİ KONULAR
NOT: Standartlar Virtual Dispatch mekanizmasının nasıl implemente edileceğini yazmıyor.Derleyiciye bırakıyor.

Virtual Dispatch mekanizması
Virtual Destructor
NVI idiyomu
polimorfik listeler
virtual constructor idiyom(clone)



*/

#include <iostream>
#include "car.h"
#include <conio.h>
#include <ctime>

void car_game(Car* p)
{
	p->start();
	p->run();
	p->stop();
	std::cout << "----------------------------------------\n";
}

int main()
{
	{
		Mercedes mymercedes;
	}
	std::cout << "main devam ediyor\n";
}
