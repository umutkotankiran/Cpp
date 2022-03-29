/*
Sınıfın Static Üye fonksiyonlarında kalmıştık.Statik veri elemanlarını işlemiştik zaten.
hatırlatma
this ptr olmayan static keywod ile bildirilen sınıfların funcları.
Member olduğu için private lara erişim var.Erişim kontolüne tabiler çünkü sınıfın memberı.
Sınıfın public private protected üyeleri olabilir.

Kodlarında this kullanılamaz, const keyword ile nitelenemez.	
Static func içinden sınıfın nonstatic veri elemanlarını isimleriyle kullanamayız
Sınıfın nonstatic veri elemanlarını ismiyle kullanamayız ve nonstatic üye functionları isimleriyle çağıramayız.


ÖRNEKLER
---------

class CarFactory{
	static int ms_count; // bu mutabledır.
public:
	static int number_of_manufactured_cars(); //yukarıdaki değeri get edebiliriz.
};


---------------------------------------------------------------------------------------

Static üye elemanı lookup table olabilir. static member func o table kullanarak değer oluşturuyor olabilir.

------------------------------------------------------------------------------------------------------------
Banka her hesaba yıllık faiz uyguluyor.

class Account{
public:
	static double get_intrest_rate(); // faiz oranını çağırıyor olabilir.

};

-------------------------------------------------------------------------------------------------------------

// sınıf türden üretilen nesnelerin sayısını saymak olabilir.live olanlar veya total

class Person{
public:
	Person()
	{
		++live_object_count;
		++total_object_count;
	}
	//Diğer CTORLARDA AYNI ŞEKİLDE ...

	~Person()
	{
		--live_object_count;
	}

	static size_t get_live_count()
	{
		return live_object_count;
	}

private:
	inline static std::size_t live_object_count{};
	inline static std::size_t total_object_count{};

};

--------------------------------------------------------------------------------------

NOT: Başlık dosyasında using bildirimi yapma.Çok kaba bir hata !!!!!

//fighter.h
using namespace std;

Burası yapılmamalı.Sebebini yazacağız.namespace konusunda görülecek.
Yapılırsa bizim başlık dosyalarını include eden tüm kod dosyaları bu using
bildirimini include eder ve buda birsürü soruna yol açabilir.

NAMESPACE KONUSUNDA GÖRÜLECEK.

-------------------------------------------------------------------------------------------------------------------

BAŞKA TEMA MÜLAKAT SORUSU
Sınıf nesnelerinin birbirlerine erişimlerini sağlamak
Bunun en kolay yolu hayata gelen nesne adreslerni bir kapta tutmak, ctor
yeni bir adres hayata getirdiğinde ınun adresini bir containera ekleyecek.
Üye functionlar bu containera erişecek, Destructor da hayatı biten nesnenin adresini 
bu containerdan çıkaracak.

Görmediğimiz araçlar var ama eldekilerle idare edeceğiz

Örneğe devam:

//fighter.h

#include <iostream>
#include <string>
#include <vector>
class Fighter {
public:
	Fighter(std::string name) : m_name{ std::move(name) } // ilk seçenek ise Fighter(const std::string name) : m_name{name}. iki seçenek olabilir.
	{													// Avantajları ve dezavantajları var tabi.hoca en son const std:.. olanı seçti.
		m_svec.push_back(this);
	}
	// buradaki parametreler ileride görülecek.Profesyonel seviyede zorlanılan kısımlar.şimdilik ok diyoruz.
	// referans semantiği deyip düşük maliyet dersek.Bazı avantajları yok etmiş oluyoruz.
	// parametrenin sınıf türden olması seçeneklerden birisi.Faydası Copy Elision.
	// const char * da yazılıp 2 overload yazılabilir.Burayı biraz inceledik.
	// parametreyi string türünden yazıp move ile rvalue a dönüştürdük.
	// hayata gelen this nesneleri vectore sondan ekleriz.


	~Fighter(); //BIG 3 ü de yazmak gerekir burada.
	//..

	void ask_help();
	// hayatta olan savaşıları çağıracak ve yardım isteyecek
	// diğer nesnelerede erişmesi lazım

	std::string Name()const
	{
		return m_name;
	}

private:
	std::string m_name; //savaşçı ismi

	inline static std::vector<Fighter*>m_svec; 
	
	// dinamik dizide tutulan veriler Fighter * olacak. değişken adı m_svec
	// containerlar C++ a C#tan falan daha sonra geldi.
	// Aynı türden verileri birarada tutacak veriyapılarını temsil eden sınıflara container sınıf deniyor C++ ta.
	// C dizileri container, bağlı liste sınıfı container...
	// Savaşçıların adresini tutmak için vector tutacağız.

};

//fighter.cpp

#include <algorithm>

//std::vector<Fighter*>Fighter::m_svec; YORUM SATIRI YAPILDI ÇÜNKÜ CLASS İÇİNDE INLINE KULLANILDI.
// static yazarsak yine sentaks hatası UNUTMA
// C++17 den önce böyle yapılırdı.Çünkü sınıf tanımı içinde inline olarak yazmak geldi artık.
// inline kullanıyoruz.Bu satırı yoksay


Fighter::~Fighter()
{
	//std::vector<Fighter*>::iterator iter = std::find(m_svec.begin(),m_svec.end,this);
	//Fonksiyonun return değerini tutacak tür bilgisi = std::vector<Fighter*>::iterator

	//Daha kolayı için auto kullanılır.
	auto iter = std::find(m_svec.begin(), m_svec.end(), this); //bunu tercih ettik.

	if (iter != m_svec.end())
	{
		m_svec.erase(iter); //containerdan silinmesini sağladı.
	}

}
//thisi arayıp bulup silecek.
// <algorithm> generic türden bağımsız func template lar var. En sık kullanılanklar bunlar
// ismi find olan algoritmaya çağr yapılacak.find linear search algo.



void Fighter::ask_help()
{
	std::cout << "ben savasci " << m_name << " dusmanlar oldurecek beni, yetisin!!!" << "\n";

	for (auto p : m_svec)  // bunu ileride göreceğiz.range base for loop.foreach gibi birşey
	{
		if (p != this) // kendi ismini kullanmamak için.Yani kendisinden yardım istememesi için yapıldı.
		{
			std::cout << p->m_name << " ";
		}
	}

	std::cout << "\n";
}


//main

int main()
{
	Fighter f1{ "Yunus" };
	Fighter f2{ "Selami" };
	auto pf1 = new Fighter("Ayse"); // dinamik memory ile yaratıldı
	auto pf2 = new Fighter("Zeliha"); //dinamik memory ile yaratıldı

	Fighter f3{ "Muhittin" };

	delete pf1;

	pf2->ask_help();

	delete pf2;
}


---------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------

ÇOK SIK KULLANILAN NAMED CONSTRUCTOR IDIOM LAR

Biz constructorun client kodlar tarafından doğrudan çağrılması yerine
clientlara nesne oluşturması için static bir üye fonksiyon vermek istiyoruz.

class Myclass{
private:
	Myclass();  // Myclass m; sentaks hatası olur normalde

};



class Myclass{
public:
	static Myclass* createObject() // Bu şekilde static üye functiona çağrı yaparak yapmış oluruz. return değeri Myclass ta olabilirdi.
	{								// bu fonksiyon static olmalı ama bu durumda.private kısmada erişiyor zaten.
		return new Myclass;
	}
private:
	Myclass();

};
Bu tip fonksiyonlara factoryu function deniyyor


----------------------------------------------------------------------


class Complex{ // complex std sınıf zaten :D biz büyük harfli yazdık
public:
	Complex(double r, double i); //cartesian
	Complex(double angle, double distance); //polar
	//sorun imzalar aynı.Redecleration zaten class ta yok.
	// çözüm aşağıda
};

------------------

class Complex{ // complex std sınıf zaten :D biz büyük harfli yazdık
private:
	Complex(double r, double i,int ); //cartesian. dummy değişkene isim vermedik
	Complex(double angle, double distance); //polar
public:
	static Complex createPolar(double angle, double distance)
	{
		return Complex{angle,distance};
	}

	static Complex createCartesian(double r, double i)
	{
		return Complex(r,i,0); // 0 dummy değer. dummy değerlere ASLA İSİM VERME.Uyarı mesajı tetikler.
	}

};

int main()
{
	auto c1 = Complex::createPolar(0.23,0.66);
	auto c2 = Complex::createCartesian(1.12, -0.45);
}



--------------------------------------------------------------------------------------

SINGLETON İDİYOMU
-----------------

Object Oriented Design Pattern
Pattern = Öyle bir kalıp ki birden fazla prblemde bunu kullanabiliyoruz.
		  Dilden bağımsızdır.
		  helm
		  gamma
		  jhonson
		  vlissides  bu adamlar design pattern adında bir kitap yazmışlar.
		  Çok sık karşılaşılan problemlere genel bir çözüm demek tasarım kalıbı.
		  gang of four - dörtlü çete

		  Mesela uzun uzun ne yapacağımızı anlatmak yerine Bridge patternini kullanalım
		  dediğimizde ne yapmak istediğimiz anlaşılıyor.Bunlara bakmak lazım.
		  Bazıları iş görüşmelerinde soruluyor bunlar.Bilmemek kötü etki yaratabilir.
		  Bu kurstan sonra design patterna bak.

idiom = dile bağımlı.
		mesela C++ ın birsürü idiyomu var.
		C++ idioms diye bir site var. wikibooksta var.
		96 tane idiom var.



-----------------------------------------------------

Birçoğuna göre Singleton anti-pattern.Bu ayrı bir tartışma.

Öyle durumlar varki sınıf türünden tek bir nesnenin oluşturulmasına izin verilecek.
Bu nesneye global bir access te sağlamak gerekecek.
Ör: Bir printer var, bir güneş var. Birsınıf nesnesi var herkes onu kullanacak. :D
Bu singleton. C++ ta 5-6 yolu var bunun.

Hoca static member func contex te bir örnek olarak kullanacak

Neden anti-pattern? 
Bu early commitment.Başlangıçta singleton olduğunu düşünmüşler sonrada koşullar değişmiş ve
singleton olma modeli ortadan kalkmış.Değiştirmekte mümkün olmuyor.

----------------------------------------------------------------------------------------------------

Singleton olması sınıfın interface i ile ilgili değil.
Tek bir nesne olacak ve global access olacak.

class Singleton{

private:
	Singleton();	//client kodlar nesne oluşturulamaz.Ama tek bir nesne varsa kopyası çıkarılabilir.
};

int main()
{
	Singleton s(expr); // böyle kopyalanır. Copy ctor delete edilmeli.
}


-------------------------------------------------------------------------------------------------------------

/.h
class Singleton{
public:
	static Singleton& get_instance() // Global bir access verildi.
	{
		if(!mp) // func ilk kez çağrıldığında mp nullptr olacak ve nesneyi yaratıp return etti.
		{		// ikinci kez çağrılınca artık if e girmeyecek ve nesne olusmayacak.hayattakini return edecek.
			mp = new Singleton;
		}
		return *mp;
	}

	// ÇOK ÖNEMLİ NOT
	// Nesnenin hayatını bitirmek için tekrar destructor yazmadık.
	// delete yazıldığında ilgili pointerın point ettiği nesnenin ilk öne destructoru sonrada operator delete functionu çağrılıyor.
	// Burada ~Singleton() { delete mp;} yazdığımızı farzedelim. delete obje yaparsak -> destructor çalışır, destructor içinde yine delete var.
	// yine destructor -> operator delete geliyor. 2 defa iç içe destructor -> operator delete işlemi olacak. Burası Büyük hata.UNDEFINED BEHAVIOR
	// Destructor recursive olarak çağrılıyor. Bu yüzden düzeltildi yani silindi bu satır.

	Singleton(const Singleton&) = delete; //copy ctoru bildirirsek(delete edersek) sınıfın atama operatör func ta defaulted yazılıyor.Onuda delete edelim
	Singleton &operator=(const Singleton&) = delete;  // delete edildi
	void func();
	void foo();

private:
	Singleton();
	inline static Singleton *mp{}; // mp = nullptr ile aynı.cpp file içinde de tanımlanabilirdi tabi.
};


int main()
{
	Singleton::get_instance().foo(); 
	Singleton::get_instance().func(); // bu tipte yazılır

	auto &rs = Singleton::get_instance(); //böylede yazılır
	rs. .... //	 yazılabilir.
		
}


---------------------------------------------------------------------

BİRDE MEYERS SİNGLETON VAR

class Singleton{
public:
	static Singleton& get_instance() // Global bir access verildi.
	{
		static Singleton instance; // Default CTor çağrıldı.Statik ömürlü bir Singleton nesnesi yaratıldı.
					   // Tekrar çağrılsa bile yine aynı nesne dönecek.Varsa yaratmayacak tekrar.

		return instance;	//BUDA MEYERS SINGLETON :D:D:D:D:D
	}

	Singleton(const Singleton&) = delete;
	Singleton &operator=(const Singleton&) = delete;
	void func();
	void foo();

private:
	Singleton();
};


int main()
{
	Singleton::get_instance().foo(); 
	Singleton::get_instance().func();

	auto &rs = Singleton::get_instance();

}

MOLA

==============================================================================
==============================================================================
==============================================================================
==============================================================================


class Singleton {
public:
	static Singleton& get_instance() // Global bir access verildi.
	{
		static Singleton instance; // Default CTor çağrıldı.Statik ömürlü bir Singleton nesnesi yaratıldı.
					   // Tekrar çağrılsa bile yine aynı nesne dönecek.Varsa yaratmayacak tekrar.

		return instance;	//BUDA MEYERS SINGLETON :D:D:D:D:D
	}

	~Singleton()
	{
		std::cout << "Destructor cagrildi\n";
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void func()
	{
		std::cout << "func called\n";
	}

	void foo()
	{
		std::cout << "foo called\n";
	}

private:
	Singleton()
	{
		std::cout << "Default Constructor Called\n";
	}
};


int main()
{
	auto& rs = Singleton::get_instance();
	rs.foo();
	rs.func();
}

ÇIKTI
-----
Default Constructor Called
foo called
func called
Destructor cagrildi



AMAÇ STATIC MEMBERFUNCLARA ÖRNEK VERMEK.
KAFA KARIŞMASIN

---------------------------------------------------------------------------------------

MÜLAKAT SORUSU

class Myclass{
public:
	static int foo()
	{
		std::cout << "1";
		return 1;
	}

	static int x; // bu bildirim.UNUTMA.
};

int foo()
{
	return 2;
}

//bu tanım.
int Myclass::x = foo(); //foo önce class scope ta arandı.Bildiriminin yapıldığı scope. Bulundu. myclass içindeki x 1 oldu
//int Myclass::x = ::foo(); //Böyle olsaydı namespace scopeta aranacaktı. 2 olurdu


int main()
{
	std::cout << Myclass::x << "\n";
}

EKRANA 1 yazar. NEDEN ?
SINIFIN STATIC VERI ELEMANLARINA ILK DEĞER VEREN IFADELER DE YINE CLASS SCOPETA ARANIR.
FOO ISMI BU SEBEPLE ÖNCE CLASS SCOPETA ARANDI.BULUNDUĞU IÇIN NAMESPACE SCOPEA BAKILMADI


-----------------------------------------------------------------------------------------------


class Myclass{
public:
	static int foo(int x)
	{
		std::cout << "1";
		return 1;
	}

	static int x;
};

int foo()
{
	return 2;
}

int Myclass::x = foo();  // isim arama aranan isimin bulunmasıyla bitti.Parametreler argümanlarla uyuşmuyor.
						 // overloading te değil. global foo gizlendi.
						 // parametre değişkenide uyuşmuyor.SENTAKS HATASI.
int main()
{
	std::cout << Myclass::x << "\n";
}


=================================================================================
=================================================================================
=================================================================================


FRIEND BİLDİRİMLERİ.
--------------------

class Myclass{
private:
	int x;
	void func();
};

int main()
{
	Myclass m; 
	m.func(); //SENTAKS HATASI
}

-----------------------------------------------------------------------------------

FRİEND BİLDİRİMİNİN PUBLİC PRİVATE PROTECTED ERİŞİM ALANLARINDAN YAPILMASININ ÖNEMİ YOK.

BU KONU BİR SIFININ PRİVATE BÖLÜMÜNE KENDİSİ DIŞINDA BAŞKA KODLARINDA ERİŞMESİNİDE SAĞLAMAK İLE ALAKALI.

Bunlar client değil sınıfın kendi kodları için kullanılıyor.ÖNEMLİ!!!

Diğer dillerden farklı olarak global funclar c++ ta var.

//myclass.h
class Myclass{
	//
public:
	void func();
};

void g(Myclass &)
{

}

Global funclar normalde sınıfın private bölümüne erişimeez.
Öyle durumlar varki erişmesini istiyoruz.Burada friend bildirimi yaparak bunu sağlıyoruz.

class Myclass{
	//
public:
	void func();
};


class HelperClass{
	//normalde myclass ın private bölümüne erişemez.Dilin kuralı.Friend bildirimiyle bu hak verilir.

};


MÜLAKAR SORUSU? FRIEND BİLDİRİMİ DATA HIDING İHLALİ YAPITYORMU ? 
DURUMA GÖRE EVET. Gerektiği senaryolar dışında kullanılırsa evet eder.

Burağın sorusunu yaz.
Neden gloabal funclar, static olmuyor ?
İleride görülecek. Bazıları funclar static olamıyor, yasaklanmış.
İleride öğrenilecek.

--------------------------------------------------------------------------------------------------------


Friend Bildirimi

a - Bir global(namespace) func için yapılabilir.

b - Bir başka sınıfın üye functionu için yapılabilir.
	(Sınıf Complete type olarak tanımlanmalı.Incomplete type ile bildirilirse SENTAKS HATASI OLUR.ÖRNEKLERDE VAR)

c - Bir sınıf için yapılabilir.
	(BURADA INCOMPLETE TYPE GEÇERLİ)

Friend sadece bildirimde olacak.Function tanımında değil !!!

SADECE FUNC BILDIRIMINDE OLUR.
TANIMDA YAPILIRSA SENTAKS HATASI OLUR.


1. SENARYO

class Myclass{
public:
	friend int gfunc(); //gfunc isimli function, myclass ın private kısmına erişebilir demek.
private:
	int mx;
	void foo();
};

int gfunc()
{
	Myclass m; // bu global olsaydı da yine erişirdi.

	m.mx = 10; sentaks hatası yok.
	m.foo();
}


--------------------------------------

Myclass m; // global yaptık erişti.

int gfunc()
{
	m.mx = 10; sentaks hatası yok.
	m.foo();
}

------------------------------------------------------------------------------------------------

class Myclass{
public:
	friend int gfunc(); //gfunc isimli function, myclass ın private kısmına erişebilir demek.
private:
	int mx;
	static void foo();
};

int gfunc()
{
	Myclass::foo(); Yine geçerli.
}

------------------------------------------------------------------------------------------------

class Myclass{
public:
	friend int gfunc(Myclass); //gfunc isimli function, myclass ın private kısmına erişebilir demek.
private:
	int mx;
	static void foo();
};

int gfunc(Myclass m)
{
	m.mx = 10; YİNE GEÇERLİ.
}


SONUÇ:
Friend olan function private kısmına erişim hakkı vermiş oluyoruz.

--------------------------------------------------------------------------------------------------

class Myclass{
public:
	friend int foo(int);
private:
	int mx;
};

int main()
{
	foo(12);    //SENTAKS HATASI.Bildirime dayanarak bu function bu şekilde kullanılamaz.
				// friend bildirimi sentaks hatası değil burada.
}				//Namespace konusunda detaylı bir konuya girilecek.
				//İstisnai durum var. ADL durumu.Argument Dependent Lookup



-------------------------------------------------------------------------------

2. SENARYO
----------

class Myclass{   
public:
	friend int Data::func(int); //SENTAKS HATASI. Başka bir sınıfın member funcına 
private:						 // yaparken böyle yazılamıyor.
	int mx;
	void foo();
};


-------------------------------------------------------------------------------------

//Incomplete type için bile yukarıdaki bildirim yapılamıyor.

class data;

class Myclass{
public:
	friend int data::func(int); //INCOMPLETE TYPE SENTAKS HATASI.Functiona yapıldığı için Complete type olmalı.
private:						// Sınıflar arası friendlik incomplete ile oluyor ama member func olmuyor.
	int mx;
};

Incomplete type olan sınıf üye fonksiyonlarına friend bildirimi yapılamaz.

--------------------------------------------------------------------------------------

class Data{
public:	// burası private olsaydı access kontrol hatası.yani SENTAKS HATASI olurdu.
	int func(int);
};

class Myclass{
public:
	friend int Data::func(int); //GEÇERLİ.
private:
	int mx;
	void foo();
};

int Data::func(int x)
{
	Myclass m;
	m.mx = 20;	//GEÇERLİ. Friendlik verilmeseydi sentaks hatasıydı.
}

---------------------------------------------------------------------------------------------------------------

FRİEND BİLDİRİMİNİN PUBLİC PRİVATE PROTECTED ERİŞİM ALANLARINDAN YAPILMASININ ÖNEMİ YOK.HİÇBİR FARK YOK.


class Myclass{
private:
	friend void foo();
	int mx;
	void foo();
};

-------------------------------------------------------------

class Data{
public:
	Data();
};

class Myclass{
	friend Data::Data(); // special member funclarada friendlik verilebilir.
};

2. Senaryo çok seyrek karşımıza çıkar.

-------------------------------------------------------------------------------------------------------------

3. SENARYO

FRİENDLİK BİR SINIFA KOMPLE VERİLDİ.BU DURUMDA INCOMPLETE TYPE OLMASINDA DA SAKINCA YOK.

class Myclass{
public:
	friend class Data; // Burada data sınıfının tüm functionlarına erişim hakkı veriliyor.
private:
	int mx;
};

class Data{
	void func(Myclass m)
	{
		m.mx = 10; //ERİŞİR ÇÜNKÜ SINIFTA BU SININA ERİŞİM VERİLDİ.
	}
	void foo(Myclass m)
	{
		m.mx = 10; // BURADA DA GEÇERLİ ÇÜNKÜ YUKARIDAN TÜM SINIFA ERİŞİM/FRIENDLİK VERİLDİ.
	}
};

NOT : BURADA INCOMPLETE TYPE GEÇERLİ. 2. SENARYODA GEÇERLİ DEĞİLDİ !!!!!!!!!!

--------------------------------------------------------------------------------------------

SADECE BELIRLI PRIVATE ÖĞELERE ERIŞIM HAKKI VERMEK İÇİN İDİYOMLAR KULLANILIR.
DOĞRUDAN BİR ARAÇ YOK.ATTORNEY CLIENT İDİYOMU BUNLARDAN BİRİ

class Myclass{
private:
	int mx,my;
	void foo();
	void func();
	void f();
};

--------------------------------------------------------------------------------------------


FRİENDLİK GEÇİŞLİ BİRŞEY DEĞİL.

A-----> B ----->C  A, B YE ERİŞİYORSA, B DE C YE ERİŞİRSE, A, C YE ERİŞİR DİYE BİRŞEY YOK.

ÖRNEĞİ YAZ.


------------------------------------------------------------------------------------------

class A{
	friend class B;
	void foo();
};

class B{
	int bx;
};


void A::foo()
{
	B b;
	b.bx = 23; // SENTAKS HATASI
}


B, A ya erişiyor diye, A da B ye erişir diye birşey yok.


----------------------------------------------------------------------------------

NOT : KALITIMLADA ARKADAŞLIK DEVRALINMIYOR.

class Car{
	friend int foo();
};

class Mercedes : class Car{

};


foo içinden Car sınıfının private ına erişiriz ama Mercedes sınıfının private kısmına erişemeyiz.


==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================




OPERATOR OVERLOADING
--------------------

Hemen her projede her classta karşımıza çıkan temel özellik.
Marjinal heryerde görülmeyen bir araç değil.

Operator overloading function çağırmanın bir başka yolu aslında.
Bir sınıf nesnesi bir operatörün operandı yapıldığında, derleyici operatörün operandı olmuş
sınıf nesnesini bir fonksiyon çağrısına dönüştürüyor.

ör:
a ve b class object

a + b   Derleyici bunu bir fonksiyona çağrılan çağrıya dönüştürüyor.
Burada çağrılan functionlara operator functions deniyor.
Bunların birtakım kuralları var. Görülecek.


ÇAĞRILAN FUNCTION GLOBAL ISE -> GLOBAL OPERATOR FUNCTIONS
EĞER NONSTATIC CLASS MEMBER FUNC ISE -> MEMBER OPERATOR FUNCTIONS DENIYOR.
OPERATOR FUNCTIONLARI SINIFLARIN STATIC ÜYE FUNCTIONU OLAMIYOR.

---------------------------------------------------------------------------------------------------------------

Neden var ?
-----------
Buradaki temel fikir programcıların işini kolaylaştırmak.
Daha kolay daha anlaşılır kod yazmasını sağlamak.
++count
i + j
++mydate ... daha anlaşılır kılıyor kodu.


s1 ve s2 string
s1 > s2 karşılaştırılabilir.
s1.is_greater(s2) bu mu kolay s1 > s2 bu mu?  :D:D:D:D

if(a * b + c == x){

}
if(is_eq(a.multiply(b).add(c),x))  Bunu kullanmak daha zor tabiki
{

}

bir anlam ifade etmiyorsa operator overloading yapma.


Matrix m1,m2;
m1 + m2  toplanabilir

---------------------------------------------------------------------------------------------------------------

Runtime a maliyeti var mı ?
---------------------------
Compile time mekanizması. Runtime maliyeti yok.


----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------

MOLADAN SONRASI
---------------

KURALLAR
--------
1- C++ ın operator kümesinde olmayan bir operatör overload edilemez.
	a @ b  Bu mümkün değil. Olmayan operator yüklenemez.

2- Operandlardan en az birinin bir class type olması yada bir enum type olması gerekiyor
	i1 * i2  bunlar int ise olmaz.Bir function çağrılmaz.
	unary ise sınıf türden
	binary ise en az birinin sınıf türden olması gerekiyor.

	Yani sadece primitive türlerden oluşturulan ifade func çağrısına dönüştürülemiyor.

3- Bazı operatörler overload edilemiyor.
	::  	scope resolution
	. 		member selection(dot operator)
	? : 	ternary operator
	sizeof  sizeof operator
	.*  	member pointer. C de yok.C++ ta var.
	typeid  buda overload edilemiyor.


Operator Overloading isimlendirmesi keyfi değil
------------------------------------------------
operator operator_keyword

operator+  	+ operatörünün isimlendirmesi
operator!  	! operatörünün isimlendirmesi
operator<  	< operatörünün isimlendirmesi
operator[] 	[] operatörünün isimlendirmesi
operator= 	= operatörünün isimlendirmesi


Bazı operatorler Global Operator Function ı ile overload edilemiyor.
--------------------------------------------------------------------
Yani bazı operatörler için global operator functionu yazılamıyor.

operator[]
operator()
type-cast operator function
operator->
operator=     Bunlar Member Function olmak zorunda.Global Function olamaz.



Tüm operatörler Operator Sentaksıyla Çağrılabileceği Gibi İsimleriylede çağrılabilir.
-------------------------------------------------------------------------------------

ÖR:
operator<(x,y);  // bu bir free/global operator func
x.operator+(y);	 // member operator function

ÖR:
class Myclass{

};

int main()
{
	Myclass x,y;

	x = y; // aşağıdaki ile aynı.
	x.operator=(y);
}

veya

main()
{
	vector<int>ivec(10);

	int a = ivec[5]; // Aşağıdaki ile aynı.
	int a = ivec.operator[](5);
}

----------------------------------------------------------------


(Biri hariç) Operator functionları default argument alamıyor.
Sadece () func call operator default argument alabiliyor.


-----------------------------------------------------------
STATİC ÜYE FUNCTION OLAMAZ. !!!!!!!!!!!!!!!!!!!!!
YA GLOBAL FUNCTON OLACAK YADA SINIFIN MEMBER FUNC OLACAK.
-----------------------------------------------------------


OPERATÖR FUNCTIONLARINDA OPERATÖRLERIN (ARITY ) DEĞIŞTIREMEYIZ.
BU OPERATÖRÜN UNARY VEYA BINARY OLMASI DEMEK.BIR TANEDE ISTISNA TERNARY OPERATOR

a < b	binary
!a		unary 
~x		unary	
...		

----------------------------------------------------------------------------------------------------------------

				Global Func
!x 				operator!(x)		1 PARAMETRESI VAR
a>b				operator>(a,b)		2 PARAMETRESI VAR


ÖR:
class Myclass{

};

//GLOBAL/NAMESPACE SCOPE
bool operator!(Myclass); //SENTAKS HATASI YOK
bool operator!(); //SENTAKS HATASI VAR. PARAMETREDEN ÖTÜRÜ. ! BIR PARAMETRE ALIR ÇÜNKÜ

bool operator>(Myclass,Myclass); //SENTAKS HATASI YOK
bool operator>(Myclass); //SENTAKS HATASI VAR. PARAMETREDEN ÖTÜRÜ. > 2 PARAMETRE ALIR
bool operator>(); //SENTAKS HATASI VAR. YİNE PARAMETREDEN ÖTÜRÜ 


---------------------------------------------------------------------------------------------------------

			Nonstatic Member Func
!x				x.operator!()				PARAMETRESİ YOK.		x*this olarak kullanıldı
a>b				a.operator>(b)				1 PARAMETRESİ VAR.		 a *this olarak kullanıldı


class Myclass{
public:
	bool operator!(); // SENTAKS HATASI YOK.LEGAL OLUP OLMAMASINA BAKTI SADECE BURADA. !X GIBI IFADE YAZIDLI
	bool operator!(Myclass); // SENTAKS HATASI VAR 

	bool operator>(Myclass); // SENTAKS HATASI YOK
	bool operator>(); // SENTAKS HATASI VAR. PARAMETREDEN ÖTÜRÜ
	bool operator>(Myclass,Myclass); // SENTAKS HATASI VAR. PARAMETREDEN ÖTÜRÜ

}

---------------------------------------------------------------------------------------------------------------

TOPLAMA OPERATÖRÜ OVERLOAD EDILDIĞINDE ÜYE OPERATÖR FUNC OLMASI DURUMUNDA KAÇ PARAMETRESI OLMALI?

class A{
public:
	A operator+()const; // Neden sentaks hatası olmadı ? Bu toplama operatörü overload değil. sign operatörü bu.

};

a + b  buradaki toplama operator
+a  sign operator

class A{
public:
	A operator+()const;		// İşaret/sign operatorü
	A operator+(B)const;	// Toplama operatorü
};

--------------------------------------------------------------------------------------

ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

a + b -> Toplama			+a -> sign/artı
a - b -> Çıkarma			-a -> sign/eksi 
a * b -> Çarpma				*a -> Dereference/Indirection
a & b -> Bitwise and		&a -> Address Operator


++x		Prefix		Bunlarda ayrı ayrı overload edilebiliyor.
x++		Postfix

---------------------------------------------------------------------------------------

OPERATÖRLERİN ÖNCELİK SEVİYESİNİ(PREDECENCE - PRIORITY)
-------------------------------------------------------
ÖNCELIK YÖNÜ / ASSOCIATIVITY 
----------------------------

BUNLAR DEĞİŞTİRİLEMEZ!!!!!!!!!!!!!!!!!!!!!!!

ÖR:
Atama Operatörü Dışındaki Tüm Nesneler Global
x = !a * b + c > d;

Derleyici bunları fonksiyon çağrılarına dönüştürecek.
x.operator=(operator>(operator+(operator*(operator!(a),b),c),d));


ÖR:
Tüm Nesneler Class Member Func
x = !a * b + c > d;

Derleyici bunları fonksiyon çağrılarına dönüştürecek.
x.operator=(a.operator!().operator*(b).operator+(c).operator>(d));

NOT: BURALARDA KULLANILAN a,b,c,d,x  BUNLAR SINIF NESNESİ.BİR TANESİ İNT OLSA SENTAKS HATASI !!!!!!!!!!!

---------------------------------------------------------------------------------------------------------

STANDART KÜTÜPHANEDEN BİRKAÇ ÖRNEK VERECEĞİZ

Std library çok yoğun olarak kullanıyor operator overloadingi.

ÖR:
int main()
{
	int x{};
	std::cout << x; // buradaki << overload edilmiş. Bitwise left shift aynı zamanda.
}


-------------------------

int main()
{
	string s1("Ali"),s2("Can");
	s1+=s2;
	auto s3 = s1+s2+"oglu"; // + operator overloding
	
	//..

	if(s1 == s2) // == operator overloding
	{
		s1 += 'a'; // += operator overloding
	}
	
}


-------------------------


ÖR:
int main()
{
	int x{};
	std::cin >> x; // >> Bitwise right shift operator overloading ile alakalı yine.
}





*/

#include <iostream>
