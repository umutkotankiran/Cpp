/*

Kalıtımdan devam

Multiple Inheritance tan devam. Diğer OOP dillerden biraz farklı idi bu işlem.
Birden fazla taban sınıfın interface ini alma işlemi. Bugün Private ve Protected Inheritance da var.

Multiple Inheritance ın OOP deki amacı birden fazla taban sınıfın interfacesini devralmak.
İleri C++ ta biraz daha detaylı ele alınacak.

Son kısmın ufak tekrarı.

class A{
public:
	void afunc();
	virtual void afunc1();
};

class B{
	void bfunc();
	virtual void bfunc1();
};

class C : public A, public B{ // Dikkat public A,B dersek olmaz.A public B ise Private inheritance ile elde edilmiş olacak
								// struct ise zaten public defaultta
	
	void afunc1()override;
	void bfunc1()override;

};

--------------------------------------------
Single / Multiple İnheritance Arası farklar
--------------------------------------------------------------------------------------------
- Daha önce öğrendiğimiz single inheritance kurallar her iki taban sınıf içinde geçerli.
--------------------------------------------------------------------------------------------
- Yazmıştım zaten. Burada C, A ve B den gelen memberları kendi interfacesine katar.
--------------------------------------------------------------------------------------------
C cx;
cx.afunc();
cx.bfunc(); // her ikiside çağrılabilir.
--------------------------------------------------------------------------------------------
- Base classtan gelen virtual functionlar tekli kalıtımda olduğu gibi override edilebilir.
C içerisinde yazdık
--------------------------------------------------------------------------------------------
Upcasting C den A yada B yede geçerli.
int main()
{
	C cx;
	A* pa = &cx; // referans ilede olur A &pa = cx; gibi..
	B* pb = &cx;
}

Runtime polimorfizmden iki taban sınıf içinde faydalanabilirim.
void foo(B& br) // buraya argüman olarak bir C nesnesi gönderip virtual dispatch ten faydalanmabilirim.
{				//Aynı durum B ve A sınıfı için geçerli. Yine object slicing ten kaçınılmalı.
	
	br.bfunc();
}

C cx;
func(cx) gibi... Örnek yazılabilir.

--------------------------------------------------------------------------------------------

Polimorfik sınıflarda kopyalama pek geçerli değil.Ya kopyalama tamamen yasaklanacak ya da 
bunlar delete edilmeyecek, sınıfın protected memberları yapılacak, türemiş sınıflar bunları
çağırabilecek ve clone idiyomu / virtual ctor idiyomu çağrılacak.Taban sınıf clone fonk veriyor
türemiş sınıflar bunu override edip kendi türünden nesne oluşturuyorlar.Tabi bunun için eğer
nesnenin aynısı oluşturulacaksa bir kopyalama gerekecek. Bu durumda copy ctor ve copy assignment 
kullanılacaksa, bunların türemiş sınıflar tarafından çağrılabilir olması gerekiyor, ama client
kodlar tarafından çağrılmasını istemiyoruz.Protected yapabiliriz dedik
Yani kopyalamalar polimorfik olarak yapılacak.

Bazen kestirme çözüm, clone da istemiyorum, copy cttor ve copy assignemnt ı delete etmek gerekiyor.

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

Çoklu kalıtımda türemiş sınıf nesnesi içinde birden fazla taban sınıf olacak.
Ctor / Dtor çağrıldığında içindekiler içinde çağrılacak.

Bunların çağrılma sırası, çoklu kalıtımda taban sınıfların yazılma sırası ile alakalı.

class Base1{
public:
	Base1()
	{
		std::cout << "Base1 Ctor\n";
	}

	~Base1()
	{
		std::cout << "Base1 Dtor\n";
	}
};

class Base2{
public:
	Base2()
	{
		std::cout << "Base2 Ctor\n";
	}

	~Base2()
	{
		std::cout << "Base2 Dtor\n";
	}
};


class Der : public Base1, public Base2{

};

int main()
{
	der myder;
	//Base1 ctor
	//base2 ctor
	//base2 dtor
	//base1 dtor
}


--------------------------------------------------------------------------------------------

SIRAYI DEĞIŞTIR.DIKKAT!!!!

class Der : public Base2, public Base1{

};

int main()
{
	der myder;
	//Base2 ctor
	//base1 ctor
	//base1 dtor
	//base2 dtor     oldu .
}

=======================================================================================================================
=======================================================================================================================
=======================================================================================================================

NAME LOOKUP
-----------
Biraz tahminlerin dışında.
Türetilmiş sınıfın ilk önce kendisinde aranır yoksa parent classlarda aranır ama sıralama yok.
İkisinde birden aynı anda aranır.Ambigiuty olma durumu çok yaygın bu bağlamda.
BURADAKİ FUNCTİONLAR FUNCTION OVERLOADİNG DEĞİL.!!!

class A{
public:
	void func(int);
};

class B{
public:
	void func(int,int);
};

class C : public A, public B{

};

int main()
{
	C cx;
	cx.func(1,5); // BU SENTAKS HATASI.
	cx.func(1);   // BUDA SENTAKS HATASI.
}

BURADAKİ FUNCTİONLAR FUNCTION OVERLOADİNG DEĞİL.!!!
Birden fazla taban sınıf bulunması durumunda isim arama her taban sınıf içinde yapılır
Bir sıra sözkonusu değildir. Burada Ambigiuty var.Birde argümanla alaklı durum değil.
İsmi gördüğü anda ambigiuty dedi.
Aynı isim her iki sınıfta birden aranıyor ve ambigiuty oluşuyor.


AŞAĞIDAKI GIBI OLSAYDI SORUN YOKTU
class A{
public:
	void func(int);
};

class B{
public:
	void func(int,int);
};

class C : public A, public B{
public:
	void func(int);
};

int main()
{
	C cx;
	cx.func(1);   // BURASI GEÇERLİ. İlk önce C de aradı zaten ve buldu.
	cx.func(1,2); // SENTAKS HATASI. C deki func ı buldu ve argüman fazla geldi.
}

------------------------------------------------------------------------------

AMBIGIUTY OLDUĞU DURUMDA BUNUN OLMAMASINI NASIL SAĞLARIZ :: ile

class A{
public:
	void func(int);
};

class B{
public:
	void func(int,int);
};

class C : public A, public B{

};

int main()
{
	C cx;
	cx.B::func(1,2); // GEÇERLİ 
	cx.A::func(1); // GEÇERLİ
}

------------------------------------------------------------------------------

USING BILDIRIMI ILE YAPILIR

class A{
public:
	void func(int);
};

class B{
public:
	void func(int,int);
};

class C : public A, public B{
public:
	using A::func;
	using B::func;
};

int main()
{
	C cx;
	cx.func(1,2); // GEÇERLİ
	cx.func(1); // GEÇERLİ
}

------------------------------------------------------------------------------

TÜREMIŞ SINIF IÇERISINDE EK FUNC YAZARAK

class A{
public:
	void func(int);
};

class B{
public:
	void func(int,int);
};

class C : public A, public B{
public:
	void foo()
	{
		// func(12); // BURADA YINE AMBIGIUTY VAR.FUNC OVERLOADING DEĞİL.
		
		//Aşağıdakiler gibi kullanıp aşarız bunu
		A::func(12);
		A::func(1,2);
	}
};

int main()
{
	
}

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------


MULTIPLE INHERITANCE DA KULLANILAN DAHA ÇOK ABSTRACT SINIFLARIN INTERFACE INI ALMAK.

class Shape{
public:
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual ~Shape() = default; // Bu func ya virtual olacak yada protected nonvirtual olacaktı.
};

class Drawable{
public:
	virtual void draw() = 0;
};

class Paintable{
public:
	virtual void paint() = 0;
};

class Circle : public Shape,public Drawable, public Paintable{
public:
	// double get_area()const override; // sadece bunu tanımlarsak halen abstract class. tüm pure virtualları override etmeliyiz.
	// double get_perimeter()const override; bunlar yorum satırı.Açıklamak için
	// burada Circle 3 adet sınıftan türetildi.
};

int main()
{
		
}

NOT : Design Pattern e çalış.

Diamond formation işin en zor yeri.Oraya geldik.

=======================================================================================================================================
=======================================================================================================================================

DIAMOND FORMATION - ELMAS FORMASYONU
------------------------------------

DDD (Dreaded Diamond of Derivation)

Base den 2 adet sınıf elde edilsin.Ayrı sınıflar Der1 ve Der2.
Sonrasında Der1 ve Der2 nin iterfacesini alıp multiple inheritance ile MDer i elde edelim. Hoca çizdi.


class Base{
};

class Der1 : public Base{
};

class Der2 : public Base{
};

class Mder : public Der1, public Der2{

};

Problem nedir? 
Compile time a yönelik ambigiuty durumları
Semantik yapıya yani runtime a ilişkin problemler

Der1 ve Der2 içinde Base nesnesi var.Mder ise Der1 ve Der2 den elde edilmiş türetilmiş sınıf.
Yine şekil. Mder içerisinde 2 adet Base nesnesi oluşacak.
A - Burada ambigiuty oluşacak.Nitelemezsek anlama şansı yok.Compile time a yönelik.
B - Asıl sorun, modelin yanlış olması.

-----------------------------------------------------------------------------------------

Şimdi burada gerçek bir projeymiş gibi bir izlenim vermek için bir örnek.

struct Person{
	virtual ~Person() = default;
	virtual void speak() { }
};

struct Student : Person{
	virtual void learn() {}
};

struct Worker : Person{
	virtual void work() {}
};

struct TeachingAssistant : Student ,Worker{ };


Compile time problemleri gösterilecek ama burada semantikte bir problem var.
Assistant içerisinde 2 adet person nesnesi var. Bu aynı anda iki person olamaz.
Speak functionu student tan gelen Person içinde çağrılabilir, Workerdan gelen person
içinde çağrılabilir.Burada bir uyumsuzluk var.

Başka bir problemde runtime da multiple inheritance ile elde edilmiş sınıf nesnesi 
içinde 2 adet person olduğundan, bir person içinde bir değişiklik yapınca
diğer person bunu anlamayacak.

Buradaki amaç bir tane base(burada Person) olsun iki adet olmasın. Bir araç var bunu sağlayan.
Default durum bu araç değil. Virtual Inheritance sağlıyor bunu.

Öyle bir araçki, normalde elmas formasyonu oluşacak yerde, çoklu kalıtımla elde edilen sınıf içinde
ortak taban sınıf türünden 2 adet nesne olması yerine 1 adet nesne olmasını sağlayan araç.
Bu dilin zor kısımlarından biri

------------------------------------------------------------------------------------------

AMBIGIUTY NEDEN OLUŞUYOR BUNU ANLAMAMIZ LAZIM.
 
class Base{
public:
	void foo();
};

class Der1 : public Base{
};

class Der2 : public Base{
};

class Mder : public Der1, public Der2{
public:
	void bar()
	{
		//foo();  //Ambigiuty var
		Der1::foo();  // Bu şekilde sorun aşılır.GEÇERLİ.
		Der2::foo();  // GEÇERLİ.İsteğe bağlı hangisi istenirse seçilir.
	}
};

int main()
{
	Mder md;
	md.foo(); //SENTAKS HATASI.AMBIGIUTY
}

AÇIKLAMA GÜZEL OKU
------------------
Mder md; şeklinde nesne oluştursam, normalde base taban sınıfım olduğu için foo func ı çağırabilirim.
Burada sentaks hatası oldu deneyince.Basedeki foo() nun, nonstatic member function olduğu için gizli bir Base * parametresi var.
Dolayısıyla nrmalde biz türemiş sınıf nesnesi ile taban sınıfın member func ını çağırınca, türemiş sınıf içerisindeki taban
sınıf nesnesinin adresini this pointer olarak gönderiyoruz.Fakat şimdi ortada bir tane değil 2 adet base nesnesi var.
Derleyici Der1 den gelen Base in adresini mi yoksa Der2 den gelen Base in adresini kullanacak bilme şansı yok.
YINE AMBIGIUTY HATASI VAR.

------------------------------------------------------------------------------------------------------------------------------------

Buradaki Ambigiuty aşağıdaki gibi ismi niteleyerek aşılır.

int main()
{
	Mder md;
	md.Der1::foo(); //Böyle aşabiliriz.Yukarıda zaten gösterilmişti.
	md.Der2::foo(); //Böyle aşabiliriz.Yukarıda zaten gösterilmişti.

	

	Mder x;
	Base* baseptr = &x; // Yine sentaks hatası.Hangi base bu ? Der1 den gelen mi Der2 den gelen mi :D
	Base& baseptr = x; // Yine sentaks hatası.Aynı şekilde
	
	//Amaç compile time da legal kod oluşturmak ise onun yolu hep var
	Base *baseptr = static_cast<Der1 *>(&x); //Burada mesela ambigiuty aşıldı.Ama İsmi hep nitelemek gerekecek.
}

----------------------------------------------------------

Yada
void func(Base& baseref)
{

}

int main()
{
	Mder mx;
	func(mx); // Yine ambigiuty
	func(static_Cast<Der1&>(mx)); // Şuanda legal oldu.
}

Bunlar compile time a yönelik durumlar çözmek mümkün.

------------------------------------------------------------------------------------------

PROBLEM DAHA ÇOK MODELE VE RUNTIME A ILIŞKIN.

Dilin kurallarına göre çoklu kalıtımla elde türemiş sınıf nesnesi içinde, ortak taban sınıf türünden
2 adet nesne olsada, genellikle(her zaman değil) bizim istediğimiz 1 adet nesne olması.Çünkü model onu
zorluyor. Mesela fax modem örneği öyle.

Model diyorki fax modem bir cihaz. Ben onu bir interface i ile kullanacağım ama fiziksel olarak karşılığı
aslında onu ben tek cihaz olarak görmek istesem bile 2 adet cihaz var içinde. Mesela ben onu fax tarafı için açacağım
modem tarafında bu kapalı görünecek çünkü orada da ayrı bir nesne var.

Böyle durumlarda ortak taban türünden 1 nesne oluşturmak gerekiyor.

class Device{
public:
	void turnon()
	{
		std::cout << "Cihaz acildi\n";
		on_flag = true;
	}
	void turnoff()
	{
		std::cout << "Cihaz kapandi\n";
		on_flag = false;
	}
	bool is_on()const
	{
		return on_flag;
	}
	virtual ~Device() = default;
private:
	bool on_flag{false};
};

class Printer : public Device{
public:
	virtual void print()
	{
		if(!is_on()) 
		{
			std::cout << "Cihaz kapali oldugundan print yapilamiyor\n";
		}
		else
		{
			std::cout << "Print islemi yapildi\n";
		}
	}
	//..
};

class Scanner : public Device{
public:
	virtual void scan()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan scan yapilamiyor\n";
		}
		else
		{
			std::cout << "Scan islemi yapildi\n";
		}
	}
	//..
};

class Combo : public Printer, public Scanner{
	
};

int main()
{
	Combo cx;
	//cx.turnon(); // Ambigiuty hatası verdi.Compile time problemi.Kimin turnon u bu?
	cx.Printer::turnon(); // bu şekilde devam edelim ama biz bunu istemiyoruz 
	cx.print();
	cx.scan(); //burada da cihaz kapalı olduğu için tarama yapamadı diyor :DD:D:D:D:D::D
	cx.Printer::turnoff();
	cx.scan(); // Cihaz kapalıyken scan edememesi lazım ayrıca.
}	

BURADA VERİLEN MESAJLAR TUHAF.Cİhazı açtık diyorki cihaz kapalı falan filan ...
3. mesajda tuhaflık var. 4. de de var.SEMANTİK HATALAR

ÇÖZÜM: Virtual Inheritance

========================================================================================================================
========================================================================================================================
========================================================================================================================
========================================================================================================================


VIRTUAL INHERITANCE
-------------------
Mülakatlarda buradan soru geliyor.

Eğer ortak taban sınıf nesnesinden(birden fazla taban sınıf nesnesinden), çoklu kalıtım yoluyla yeni bir sınıf elde ettiğimizde,
onun içine ortak taban sınıf nesnesinden 2 adet değilde 1 tane olmasını istiyorsak, çoklu kalıtımda kullanılacak taban sınıfları 
sanal kalıtım dediğimiz biçimde oluşturacağız.

Sanal kalıtım, önce hangi sınıflarda uygulanıyor?
Ortak taban sınıfa virtual base class diyeceğiz. Bu sınıftan kalıtım yoluyla elde edilcek ve daha sonra çoklu kalıtımda
taban sınıf rolü oynayacak sınıflarda, kalıtımda virtual keywordü kullanılıyor.
Yani hem printer hemde scannerda virtual kullanılacak.


//virtual base class
class Device{
public:
	void turnon()
	{
		std::cout << "Cihaz acildi\n";
		on_flag = true;
	}
	void turnoff()
	{
		std::cout << "Cihaz kapandi\n";
		on_flag = false;
	}
	bool is_on()const
	{
		return on_flag;
	}
	virtual ~Device() = default;
private:
	bool on_flag{false};
};

class Printer : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public:
	virtual void print()	
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan print yapilamiyor\n";
		}
		else
		{
			std::cout << "Print islemi yapildi\n";
		}
	}
	//..
};

class Scanner : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public: 
	virtual void scan()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan scan yapilamiyor\n";
		}
		else
		{
			std::cout << "Scan islemi yapildi\n";
		}
	}
	//..
};

class Combo : public Printer, public Scanner{

};

int main()
{
	Combo cx;
	
	cx.turnon(); // HATA ARTIK YOK
	//cx.Printer::turnon(); // Gerek kalmadı
	cx.print();
	cx.scan();
	cx.turnoff(); 
	cx.scan(); //Kapalı olduğundan yapmadı işlemi. herşey artık olması gerektiği gibi
}

Virtual yapınca içerisindeki Base nesnesi artık 1 adet.
Hiçbir ambigiuty sözkonusu değil. Runtime a bakınca herşey mantıklı.

Artık derleyicinin scannerdan gelen mi printerdan gelen mi device kullanılacak gibi soru sözkonusu değil.
O da Combonun kendi device ı. 

Amaç, printer scanner gibi sınıfları device tan kalıtım yoluyla elde ettiğimnizde ve daha sonra böyle sınıfları
çoklu kalıtımda taban sınıf olarak kullandığımızda bir tane device olmasını sağlamak.Bu durumda kalıtımı 
Virtual Inheritance ile yapıyoruz. Bunun olması için : tokenından sonra virtual yazılması gerekiyor.
Artık combonun içinde 1 device var.Bu da Combonun kendi device ı.

=========================================================================================================================
=========================================================================================================================

Virtual Inheritance ta farklı Initializer kuralları var.

İlk olarak Virtual Base hayata gelecek.Önemli bir kural.
Bunu Kim initialize edecek? En dipteki türemiş sınıf.

Eğer multilevel inheritance varsa. A dan B, B den C, C den D elde edilmişse yani, Burada
herkes kendi taban sınıfını(direct base class) initialize eder.Bu kuraldı geçen derslerde yazdık.

AMA VIRTUAL INHERITANCE VARSA
-----------------------------
BIZIM ÖRNEKTEN GIDELIM.BIR SINIF NESNESI IÇERISINDE BIR VIRTUAL BASE VARSA, ARTIK DEVICE I INITIALIZE EDEN COMBO TÜRÜNDEN
BIR NESNE OLUŞTURDUĞUMUZDA, COMBONUN CONSTRUCTORU DEVICE I INITIALIZE ETMEK ZORUNDA.(DEVICE = VIRTUAL BASE CLASS BURADA).
HER ZAMAN HAYATA ILK GELEN NESNE VIRTUAL BASE OLACAK. YANI COMBONUN CTORU IÇINDE DEVICE IN CTORUNA ÇAĞRI YAPMAK ZORUNDAYIZ.
YANI DEFAULT CTORU VARSA DEFAULT ÇAĞRILIR.AŞAĞIDAKILER EKLENDI KODA.

Device()
{
	std::cout << "Device Ctor\n";
}

Printer()
{
	std::cout << "Printer Ctor\n"
}

Scanner()
{
	std::cout << "Scanner Ctor\n"
}

EKLENMİŞ HALİ

//virtual base class
class Device{
public:
	Device()
	{
		std::cout << "Device Ctor\n";
	}
	void turnon()
	{
		std::cout << "Cihaz acildi\n";
		on_flag = true;
	}
	void turnoff()
	{
		std::cout << "Cihaz kapandi\n";
		on_flag = false;
	}
	bool is_on()const
	{
		return on_flag;
	}
	virtual ~Device() = default;
private:
	bool on_flag{false};
};

class Printer : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public:
	Printer()
	{
		std::cout << "Printer Ctor\n"
	}
	virtual void print()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan print yapilamiyor\n";
		}
		else
		{
			std::cout << "Print islemi yapildi\n";
		}
	}
	//..
};

class Scanner : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public:
	Scanner()
	{
		std::cout << "Scanner Ctor\n"
	}
	virtual void scan()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan scan yapilamiyor\n";
		}
		else
		{
			std::cout << "Scan islemi yapildi\n";
		}
	}
	//..
};

class Combo : public Printer, public Scanner{
	Combo()
	{
		std::cout << "Combo Ctor\n"
	}
};

int main()
{
	Combo cx;
}

Sırayla Ctorlar çağrıldı.
Device ctor
Printer ctor
Scanner ctor
Combo Ctor

Burada Device Ctorunu çağıran, printer yada scanner ctoru değil, Combonun Ctoru çağırdı.

----------------------------------------------------------------------------------------------------

Birde multicombo ekliyorum. Eklenmiş uzun halini yazmayacağım

class MultiCombo : public Combo{
public:
	MultiCombo()
	{
		std::cout << "MultiCombo Ctor\n"
	}
};

int main()
{
	MultiCombo c;
}

Çıktı
-----
Device Ctor
printer Ctor
Scanner Ctor
Combo Ctor
MultiCombo Ctor

Device Ctor ilk çağrıldı.Bunu çağıran multicombonun Ctoru.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

EN ÖNEMLI ÖRNEK !!!!!!!!!!!!!!!!!!

Şimdi device a int parametreli ctor ekledi 
printera da int parametreli ctor eklendi, bunun ctor init listinde Device(x) var.
Scanner içinde de int parametreli ctor eklendi.Buda ctor init list ile Device(x) çağırdı.
Combo nun default ctoruna Device(3), Printer(4), Scanner(5)


//virtual base class
class Device{
public:
	Device(int x)
	{
		std::cout << "Device Ctor x = "<< x << "\n";
	}
	void turnon()
	{
		std::cout << "Cihaz acildi\n";
		on_flag = true;
	}
	void turnoff()
	{
		std::cout << "Cihaz kapandi\n";
		on_flag = false;
	}
	bool is_on()const
	{
		return on_flag;
	}
	virtual ~Device() = default;
private:
	bool on_flag{false};
};

class Printer : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public:
	Printer(int x) : Device(x)
	{
		std::cout << "Printer Ctor\n"
	}
	virtual void print()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan print yapilamiyor\n";
		}
		else
		{
			std::cout << "Print islemi yapildi\n";
		}
	}
	//..
};

class Scanner : virtual public Device{  //BURAYA DİKKAT. VİRTUAL GELDİ
public:
	Scanner(int x) : Device(x)
	{
		std::cout << "Scanner Ctor\n"
	}
	virtual void scan()
	{
		if(!is_on())
		{
			std::cout << "Cihaz kapali oldugundan scan yapilamiyor\n";
		}
		else
		{
			std::cout << "Scan islemi yapildi\n";
		}
	}
	//..
};

class Combo : public Printer, public Scanner{
	Combo() : Device(3), Printer(4), Scanner(5)
	{
		std::cout << "Combo Ctor\n"
	}
};

class MultiCombo : public Combo{
	MultiCombo() : Device(4)				// yanına Printer(4), Scanner(5) yazılamaz çünkü direct base class değil.İndirect base class
	{
		std::cout << "MultiCombo Ctor\n"
	}
};

int main()
{
	MultiCombo cx;
}

Çıktı
-----
Device Ctor x = 4
printer ctor
scanner ctor
combo ctor
Multicombo ctor

----------------------

Combo ile çağıralım

int main()
{
	Combo cx;
}

Çıktı
-----
Device Ctor x = 3   
printer ctor
scanner ctor
combo ctor


---------------------

printer ile çağır

int main()
{
	Pritner px{345};
}

Device Ctor x = 345
Printer ctor

Yani virtual base ctor hep ilk çağrılmak zorunda.Sonra diğerleri çağrılır.

KALITIMLA İLGİLİ BAŞKA BAŞLIKLARDA VAR. EXCEPTİON HANDLİNGE GİRİLECEĞİ İÇİN SONRASINDA GİRİLECEK BU KONULARA

MOLA

=========================================================================================================================
=========================================================================================================================
=========================================================================================================================
=========================================================================================================================

Standart kütüphane çoklu ve sanal kalıtımı giriş çıkış sınıfları hiyerarşisinde kullanıyor.
Standart library deki giriş çıkış işlemleri, OOP ilkeleri ile bir sınıf hiyerarşisi içinde
bulunan sınıflar tarafından yönetiliyor.

En tepede bir taban sınıf var bunun adı IOS_BASE.Bu sınıf şablonu değil en tepedeki taban sınıf.
Burada akımın giriş yada çıkışından bağımsız olarak ortak interface var.Akımdaki kararkter türünden de bağımsız.

IOS_BASE den kalıtım yoluyla BASIC_IOS elde edilmiş.Aslında bu bir sınıf şablonu.
BASIC_IOSTAN ise BASIC_ISTREAM sınıfı elde edilmiş. Bu giriş/okuma işlemlerini yapmaya yönelik interface e sahip.
Bizim cin nesnesi bu sınıf türünden. Biz istream kullanmıştık. Bu bir sınıf şablonu, istream ise bu şablondan elde edilen
bir sınıfın türeş ismi. Bizimki bundan elde edilmiş. Yazma işlemleri için yazma interface ine sahip BASIC_OSTREAM isimli sınıf
oluşturulmuş, BASIC_OSTREAM de aynı şekilde BASIC_IOS tan elde edilmiş. << bu basic_ostream interface inden geliyor,
>> ise basic_istream interface inden geliyor.Birde hem okuma hem yazma işlemi yapmaya yönelik bir sınıf oluşturulmuş.
Burada oluşturulan sınıf multiple inheritance ile oluşturulmuş.Bunun adı BASIC_IOSTREAM. Yani bu interface e sahip sınıflar
hem okuma hemde yazma işlemi yapabiliyorlar.

cout isimli değişken basic_ostream sınıfı türünden,
cin isimli global nesne basic_istream sınıfı türünden. 
Aşağıda da elmas formasyonu var.Burada da virtual inheritance var.


			|------------|
			|  ios_base  |
			|------------|
			      ^
			      |
			      |
			|------------|
			|  basic_ios |
			|------------|

			 ^	     ^
			/	      \	
Virtual	inheritance   /			\ Virtual inheritance
		    /			  \
                  /			    \
	|-------------|			|-------------|
	|basic_istream|			|basic_istream|
	|-------------|			|-------------|
		   ^                 	     ^
		    \			    /
		     \			   /	
		      \			  /
		       \		 /
		        \	    	/
			|--------------|
			|basic_iostream|
			|--------------|



basic_iostream, basic istream ve basic ostream den virtual inheritance yoluyla elde edilmiş.

int main()
{
	fstream f;
	int x;

	f << 12; // nasıl oluyor bu? bu ostream sınıfından gelen function.
	f>>x; //bu ise basic_istream den gelen function.
}
Bazıları ise en tepeden basic_ios tan geliyor

Anlatılmak istenen virtual inheritance.

============================================================================================================================
============================================================================================================================

Final Contexual Keyword
-----------------------
Modern C++ ile birlikte override var birde final var.
Belirli bağlamlarda keyword belirli bağlamlarda isim identifier olarak kullanılan objelere verilen isim. Geriye dönük uyumluluktan
ötürü bunlar kullanılabiliyor.

class Base{
public:
	virtual void override();
};

class override : public Base{
public:
	void override()override; // SENTAKS HATASI YOK.
};

Çünkü bir tanesi isim diğeri ise contexual keyword.Geriye dönük uyumluluktan ötürü hem keyword hemde
isim olarak kullanılabiliyor.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

2. Contexual keyword final
İki farklı anlamda kullanılıyor final. final class ve final override

final class = Bu sınıftan birdaha kalıtım yapılmayacak demek. Kalıtımda taban sınıf olarak kullanılamaz demek.
Multilevela ekleme istemiyor.Bazı durumlarda derleyicinin daha iyi optimizasyon yapmasını sağlıyor. : den önce final yazılır.

final override = Kalıtım yoluyla sınıf elde edilebilir ama o sınıf kendi taban sınıfının sanal fonksiyonunu artık override edemez demek.

1. KULLANIM
-----------
class Base{
};

class Der final : public Base{ // final ile kalıtım sonlandırıldı.
public:
};

class Nec : public Der{ // Der final olarak belirtildiği için base class yapılamaz burada
						// SENTAKS HATASI.
};


2. KULLANIM
-----------
Kalıtım yoluyla sınıf elde edilebilir ama o sınıf kendi taban sınıfının sanal fonksiyonunu artık override edemez.
Hiyerarşideki yeni kalıtım yoluyla elde edilecek sınıflar kendi taban sınıfının override ının implementasyonunu kullanmak zorunda.

class Base{
public:
	virtual void func(int);
};

class Der : public Base{
public:
	void func(int)override final; // bunu yazdık.Artık bu sınıftan türetilen sınıfların virtual funcları, bu func ı override edilemez.
};									// final ile override yeri değiştirilebilir.

class Nec : public Der{
public:
	void func(int)override; // burada SENTAKS HATASI VERDİ.
};

Derleyici burada final a güvenerek devirtualization denen optimizasyonu yapabiliyor.


===============================================================================================================
===============================================================================================================
===============================================================================================================

PRIVATE / PROTECTED INHERITANCE
-------------------------------

Biz sadece public inheritance gördük. OOP de java c# taki inheritance karşılığı bizde sadece public inheritance.Yani is a ilişkisi.
Yani bir sınıf türünden nesne aynı zamanda başka sınıf türünden nesne gibi kullanılabiliyor.

Diğer 2 kalıtım biçimi (private protected) nin varlık sebebi is a relationship değil.
Bunların kullanımındaki temel fikir compositiona alternatif oluşturması.

Containment yoluyla composition yaptığımızda bir sınıf nesnesi içinde başka sınıf nesnesi var.Bu member object
A sınıfı kalıtım yoluyla B den elde edildiyse, yine A nesnesi içinde B var.Bu base class object
İki tipte de A içinde B var.

Dolayısı ile birnesneye eleman olarak başka bir sınıf türden nesne kazandırsam,(Yani A nın B türünden memberı olsa)
ona birbaşka alternatif B yi member olarak almak değil, A yı kalıtım yoluyla B den oluşturmak.Fakat buradaki kalıtım 
public private protected olabilir. Public yapılmasının sebebi "is a" ilişkisini gerçekleştirmek.
AMA PRIVATE VE PROTECTED KALITIMI DAHA ÇOK COMPOSITION İLİŞKİSİNİ GERÇEKLEŞTİRMEK İÇİN KULLANILIYOR.

NEDEN A NIN ELEMANI OLAN B KULLANMAK YERINE, ALTERNATIF OLARAK A NIN B DEN KALITIM YOLUYLA ELDE EDILMESINI NEDEN TERCIH EDEYIM ???
ÖNCE GENEL KURALLARA BAKALIM

class Base{

};

class Der : private Base{ // private yazmasam classlarda defaultta private
	
};

int main()
{
	Der myder;
	//Base *baseptr = &myder; SENTAKS HATASI
	//Base &baseptr = myder; SENTAKS HATASI
}

KALITIMIN BİÇİMİ NE OLURSA OLSUN DER İÇERİSİNDE BİR BASE NESNESİ OLACAK.PUBLİC PRİVATE PROTECTED FARKETMEZ.
PRİVATE, PROTECTEDA GÖRE ÇOK DAHA FAZLA KULLANILIYOR.

----------------------------------------------------------------------------------------------------------------------------------------

BİLGİLER
--------
1 - Clientlar için her Der bir Base olarak ele alınmayacak.Der den Base e otomatik dönüşüm sözkonusu değil.Ama clientlar için
	Der myder;
	Base *baseptr = &myder; // SENTAKS HATASI. public kalıtım olsaydı Geçerli. Ama Burada her Der bir Base deil bu sepeble sentaks hatası
	Base &baseptr = myder;  // SENTAKS HATASI. Aynı şekilde

------------------------------------------------------------------------------------------------------
2 - Burada upcasting clientlara legal değil ama member functionlara legal.ÇOK ÖNEMLİ!!!!!

	class Base{

	};

	class Der : private Base{ // private yazmasam classlarda defaultta private
		void foo()
		{
			Der myder;
			Base*ptr = &myder; GEÇERLİ
		}
	};

----------------------------------------------------------------------------------------------------------

3 - Friend Bildirimde de geçerli.Friend bildirilmiş func içinde uplasting Legal. Buda diğer istisna !!!!!!
	Yani türemiş sınıfın kendi implementasyonu içinde ve türemiş sınıflara friend olan functionlar içerisinde is a ilişkisi var.
	Bu sebeple upcasting legal.

	class Base{
	};

	class Der : private Base{ // private yazmasam classlarda defaultta private
		friend void foo();
	};

	void foo()
	{
		Der myder;
		Base*baseptr = &myder; // GEÇERLİ.
	}

----------------------------------------------------------------------------------------------------------------
4 - Normalde Base sınıfının public memberları aynı zamanda türemiş sınıfın interfaceine katılıyordu.
	ARTIK Taban sınıfın public/protected bölümü artık türemişin public değil, private interfacesine ele alınacak.
	Böylece bunlar türemiş sınıfın clientlarına kapatılmış olacak fakat türemiş sınıf implementasyonuna açık 
	hale gelecek.

	class Base{
	public:
		void foo();
	};

	class Der : private Base{  //Artık foo der sınıfının bir private öğesi gibi ele alınacak.
	public:
		void func()
		{
			foo(); // BUrada çağrılablir ama clientlar çağıramaz.Aşağıda var örnek.
		}
	};

	void foo()
	{
		Der myder;
		myder.foo(); //SENTAKS HATASI.Artık private bölümünde.
	}

	BUNUN AYNISI PROTECTED IÇINDE GEÇERLI

----------------------------------------------------------------------------------------------------------------
5 - Kalıtım biçimi ne olursa olsun Public Private Protected, taban sınıfın private bölümü her zaman
	türemiş sınıfa kapalı.

	class Base{
		void foo();
	public:
	};

	class Der : private Base{ // public private protected olsada kapalı.İki durumda da SENTAKS HATASI
	public:
		void func()
		{
			foo(); // SENTAKS HATASI
		}
	};

	void foo()
	{
		Der myder;
		myder.foo(); //SENTAKS HATASI.Artık private bölümünde.
	}

-----------------------------------------------------------------------------------------------------------------------------

6 - Kalıtımın private veya protected olması sanal sınıfların override edilmesi noktasında fark oluşmuyor.

class Base{
public:
	virtual void foo();
};

class Der : private Base{ // protectedta da fark yok
public:
	void foo()override; // override edebilir.
};

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

EN ÖNEMLİ YER!!!!!!!!!!!!!!!

CONTAINMENT YOLUYLA COMPOSITIONLA, PRIVATE KALITIM YOLUYLA SINIFI ELDE ETMEK ARASINDA NE FARK VAR? VE NE BENZERLIKLER VAR?
--------------------------------------------------------------------------------------------------------------------------
Containment demek yani A sınıfı B sınıfını member olarak almış.

AYNI/BENZER OLAN KISIMLAR
-------------------------
class Member{
public:
	void foo();
};

class Owner{ 
public:
	void foo() // 3. maddeye istinaden yazıldı.
	{
		mx.foo();
	}
private:
	Member mx;
};

1. Owner Memberın interface ini kendi interface sine katmıyor.
2. Owner içerisinde bir Member nesnesi var.
3. Owner (isterse) Member functionlarını kendi arayüzüne ekler !!!
   func yazılır ve bu da foo yu çağırır.kodu ekledim. mx.foo() ile.
   Member::foo() ile olmaz çünkü bu nonstatic member func.


Buradaki Maddeleri aşağıdaki private inheritance maddeleriyle
kıyasla.
---------------------------------------------------------------------------------------------

class Base{
public:
	void foo();
};

class Der : private Base{
public:
	using Base::foo; // 3. madde için KISA YOL.
	void foo() // 3. maddeye istinaden yazıldı.UZUN YOL
	{
		Base::foo();
	}
private:
};

1. Der, Base interface sini kendi interfacesine katmıyor.
2. Der içerisinde Base nesnesi var.
3. Der isterse base in functionlarını kendi interfacesine ekler.
   2 yolu var,
   a - Uzun yol forwarding function 
   b - Kısa yol using bildirimi.



---------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------

FARKLILIKLAR
------------

1 - Her owner bir member olarak kullanılabilir mi ? Hayır. İçinde member taban nesnesi yok.

2 - Normalde Der içerisinde bir Base nesnesi var, ama her Der bir base olarak kullanılamaz!!!
	İstisnai durum bir altta yazıldı.
    Der in member funcları içinde ve friend functionlar içerisinde her Der bir Base olarak kullanılabilir.

3 - Owner, memberın sanal functionlarını override edebilir mi? HAYIR

4 - Der base in sanal functionlarını override edebilir mi ? Evet

5 - Owner memberın protected bölümünü kullanabilir mi ? HAYIR

6 - Der Base in protected bölümüne erişebilir.EVET


---------------------------------------------------------------------------------------------------------------


Aslında member almakla kalıtım kullanmakla aynı avantajları elde edebiliyoruz ama kalıtım kullanarak fazladan 
elde ettiğimiz yaptıklarımızda var.

KALITIMLA FAZLADAN YAPABİLDİKLERİMİZ
------------------------------------
1 - Taban sınıfın virtual functionları override edebilirim
2 - Taban sınıfın protected bölümdeki öğeleri kullanabiliyorum.
3 - İs a ilişkisinden kısıtlıda olsa Der member funcları ve	friend functionları için faydalanabilirim.
	(Türemiş sınıftan taban sınıfa kısıtlıda olsa dönüşüm yapabileceğim yani upcasting ten faydalanabileceğim.)
	Herb Sutter ın makalesinde yazdığı kodda bu iyi gösteriliyor.Onu aşağıda yazdım.

Private kalıtım compositiona alternatif oldu. Baya iyi bir alternatif.

---------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------


Adaptor Pattern(Uyumlandırıcı)
------------------------------
DESIGN PATTERN DA VAR BU.
Private inheritance ın biraz daha idiyomatik kullanımları var

EBO -> Empty Base Optimization
Çok sık kullanılıyor bu.

class Empty{
public:
	void func();
};

class Myclass{
private:
	Empty e;
};

int main()
{
	sizeof empty değeri 1 byte çıkar.
	sizeof Myclass ta 1 çıkar.
}

------------------------------------------------------------------


class Myclass{
private:
	Empty e;
	int mx; 
};

sizeof u 8 çıkar. alignment tan ötürü.padding bytelar var.
Hem Empty sınıfı bomboş içinde birşey yok, hemde size ı 
2 katına çıkardı. O zaman bunu private kalıtım yoluyla kullanırız
Aşağıda yapıldı.Avantajıda vardı yukarıda gördük

------------------------------------------------------------------

class Empty{
public:
	void func();
};


class Myclass : private Empty{
private:
	Empty e;
	int mx;
};

int main()
{
	sizeof myclass 4 yazar.şimdi.Compilerlar ya optimizasyon yapar 
	yada base için myclass içerisinde yer ayırmıyorlar.
}

Yukarıda eleman olarak alınca 8 byte olduğunu gördük ama burada 
private kalıtım yoluyla devraldık hem avantajları var hemde 4 byte oldu
Empty nesnesi için yer ayırmadı compiler. Empty Base Optimization

BURADA PADDING BYTES - ALIGNMENT REQUIREMENTS KISMINA GİRDİ BİR SORU ÜZERİNE
alignof(short); -> short 2 nin tamkatı olan yerlere yerleştirilebilir demek
alignof(int); -> int 4 ün tamkatları olan adreslere yerleştirilebilir ...

alignas ile alignment requiremets daha büyük bir değer olabilir.
Ama bunu küçültmek işlemcinni destek vermediği durum olabilir
yada işlemlerin çok daha yavaş yapılması anlamına gelebilir.

------------------------------------------------------------------------------------------

Bir kullanımı daha var.
Herb Sutter ın bir makalesinde tanıttığı kullanım.
Buna Restricted Polymorphism demiş.

class Base{
public:
	virtual void vfunc();
};

class Der : private Base{
public:
	void vfunc()override;
	friend void foo1();
};

void gfunc(Base&r)
{
	r.vfunc();
}

void foo1()
{
	Der der;
	gfunc(der); // GEÇERLİ.foo1 içindeyiz ve bu friend function.Friend içinde upcasting yapılabiliyor.
}				// Base &r  = der oldu artık. Aşağıda ise hata var.friend değil.

void foo2()
{
	Der der;
	gfunc(der); //GEÇERSİZ
}


==========================================================================================================================================
==========================================================================================================================================
==========================================================================================================================================

PROTECTED INHERITANCE
---------------------
Private ile arasında pek fark yok. Tek fark protected inheritance ı kullanacağımız senaryoları belirliyor.

- Public kalıtımda taban sınıfın public interface indeki öğeler türemiş sınıfın public interface ine geliyor
- Private kalıtımda, taban sınıfın public interface indeki öğeler türemiş sınıfın private interface ine geliyor
- Protected kalıtımda, taban sınıfın public/protected interface indeki öğeler türemiş sınıfın Protected interface ine geliyor

Bu durumda Der sınıfının clientları ve kendi sınıfı açısından fark yok.Fark Der den bir kalıtım daha yapıldığında ortaya çıkacak.

class Base{
public:
	void func();
};

class Der : private Base{

};

class Nec : public Der{
	void bar{
		func(); //SENTAKS HATASI
	}	
};

-----------------------------------------

Protected olsaydı

class Base{
public:
	void func();
};

class Der : protected Base{

};

class Nec : public Der{
	void bar{
		func(); //GEÇERLİ. Çünkü Der protected olarak Base i almış. func Der in protected ına geldi.Burasıda alır bu durumda
	}	
};


Private ile Protected aynı amaçlarda kullanılabilir.
Privatta fark, kalıtım yoluyla elde edilmiş child class tan yeni bir sınıf elde edilince o artık taban sınıfın public functionunu kullanamayacak.
Protected ta ise türemiş sınıf taban sınıfın protected bölümüne erişebildiği için bu erişim legal olacak.

=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================

EXCEPTION HANDLING

Burada kullanılan terim türkçede doğrudan oturmuş bir karşılığa sahip değil.
Herkes farklı terimler kullanıyor.Hoca Olağan dışı durumların işlenmesi.
Burada kastedilen runtime da oluşan programın işini görmesini engelleyecek durumların ele alınması ve yönetilmesi.

Runtime daki hataları 2 ye ayırıyoruz.Bazı hatalara programlama hataları diyoruz. Program runtime da hata oluşturuyor, mesela func doğru
şekilde çalışmıyor. Bunu nedeni kodun yanlış yazılması. Bunun ilacı kodun düzeltimesi.
Mesela veritabanı bağlantısı veya dosya açılması gerekiyor, bunun için birtakım string maniplasyon işlemleri yapılıyor.
string elde edilip o isimde dosyayı açmaya çalıştı ama o isimde dosya yok. Hata verdi... gibi.

C de bu assertionlarla yapılıyordu. Bunlar kendi içinde 2 ye ayrılıyor.
Static Assertion - compile time assertion.
Dynamic Assertions - runtime assertion.

Seert doğrulamak demek.Biz işgrören kodun yanı sıra kodlama hatalarını bulmak içinde kod ekliyoruz.Mesela 0 a bölme hatası yapıldıysa onu bulmak için
her bölme işleminde böyle operatörünün sağ operandının 0 olup olmadığını kontrol etsen ve 0 olduğunu görünce hata akımına yazı yazdıran bir fonksiyon 
çağrısı eklesek ve programıda abnormal terminate edecek şekilde abort functionu ile sonlandırsak. Bu dynamic assertion.

C de assert.h deki assert macrosu var.Bu runtime da gerekli koşul sağlanmamışsa ekrana hata bulgusu hazdırıyor.Bizde ona göre düzeltiyoruz.
Daha sonra bu hatalar ayıklandıktan sonra assert macrolarının karşılığı bu kontrol kodlarının kaynak koda dahil edilmemesi için asert.h nin include
edilmesinden önce NDEBUG macrosu define edilir.Böylece assert macroları devre dışı bırakılır.

Static assertion ise compoile time da yapılan doğrulamalar.
Derleme zamanında doğru olması gereken koşul sağlanmadıysa derleyici sentaks hatası verecek. Biz bazı koşulların sağlanmadığını anlayıp kodda
düzenleme yapacağız. Static Assertion C ye 11 standartlarıyla eklendi. C++ ta var. Keywordler farklı. _Static_assert diye geçiyor C de.
C++ ta ise static_assert() in kendisi birt keyword. Parantez içindekinin constant expr olması gerekiyor.

static_assert(sizeof(int) >= 4); Bu doğrulanırsa ok. ama doğrulanmazsa sentaks hatası verecek.
static assert aslında bir argğman daha alıyor ama bu daha sonra opsiyonel hale getirildi.

static_assert(sizeof(int) >= 4,"int degeri 4 ten buyuk esit olmali");
Bunun önemli olduğu yer generic programlama.

--------------------------------------------

Birde runtime hataları var.
Temel birimlerden biri function. C ve C++ ta da belirli bir iş yapan bir görevi olan kod birimi function.
Öyle durumlar oluyorki function kodu çalışınca üstelendiği işi yapamayacağını anlayabiliyor runtime da.MEsela function dinamik bir bellek alanı
allocate etmeye çalışsın ama bunu elde edemezse işi yapma şansı olmasını istemiyoruz.Bu durumda fonksiyon ne yapacak? Kritik soru.

Basit bir soru ama programlamanın en önemli sorularından biri. Bu sorunun en radikal cevabı şu olabilir. Programın çalışmasını sonlandıralım.
Genel anlamda birçok senaryoda fonksiyonun böyle bir karar veremez.Bunuda çağıran bir func var. O bu functan hizmet almak için bunu çağırmış.
Dolayısı ile bu fonksiyon karar verme yetkisine sahip değil. Func diyorki ben işimi yapamadım ama ne yapacağımın kararını verme yetkisi bende değil.

Belki func ı çağıran f1, onu çağıran f2, f2 yi çağıran f3...
Dolayısı ile func kendisini çağıran koda ben bir hatayla karşılaştım , sende kendini buna göre ayarla diyor.

Burada kullanılan yöntemlere hata işleme deniyor. Bunlar için geleneksel yöntemler var. Veya birçokdilde bunun için kullanılan araç veya araçlar var.
Exception handling deniyor bunlara.Ne işe yarar nası kullanılır öğreneceğiz.

Bu araç setinin faydalarını varlık sebebini kullanım fikirlerini anlamamız için buna sahip olmayan C de bu nasıl yapılıyor.
Bunu anladıysak zaten çok daha rahat işimiz.

Geleneksel yöntemler 2 tane.
İşini yapamayan functionun kendisini çağıran koda return değeri mekanizmasıyla iini yapamadığını anlatan bir değer dönmesi.
int fclose(FILE *) mesela
int fseek(...) 

Buradaki return değerler başarı bilgisi anlamında kullanılıyor. function 0 dönerse  işini yaptığını söylüyor.Nonzero ise yapamadım diyor.
Bazı functonlarda negatif değer hata olduğunu söylüyor.

Bazılarında ise functionun geri dönüş değeri 2 amaca birden hizmet ediyor. 
functionu çağıranın functiondan elde ettiği değer hemde başarısızlık bilgisi iletiyor.
long ftell(FILE*); başka parametrelerde olabilir
-1 döndürürse işini yapamadı demek.
return değeri 20 ise file pointer değeri 20. -1 ise başarısız oldu function.

Bazı functionlar başarılı olunca nesne adresi, başarısız oluncada NULL ptr döndürmesi.
FILE* FOPEN(const char *p,const char *pmode); Dosya açılırsa bir struct adresi, açılamazsa NULL pointer.
mallocta böyle.calloc realloc, setlocal...

Gerek 3 parti kütüphanelerde global değişkenin hata bilgisi amaçlı kullanılması.C nin std library sinde "errno.h" var.

#include "errno.h"
errno global değeri var. Hata yoksa 0. bir func çağırınca ve işini yapamazsa errno değişkenini ilgili hataya ait hata koduyla set edsiyor.
errno yu yazdırınca da, her tamsayı değeri ayrı bir hataya denk geliyor.stdio daki perror() bu hata mesajını stdout a yazdırıyor.
Aynı şekilde strerror(errno) ile hataya bakıyoruz.


*/
