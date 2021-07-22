/*
Operator Overloadingten devam ediyorduk
Smart Ptr oluşturduk.
En son Generic Programlama paradigmasına selam gönderdik
Yani özünde aynı işi yapan farklı türlere hitap eden paradigma.

template<typename T>  --> T bir tür olmak üzere
compiler bundan sonsuz sayıda function yazabilecek.bu bir metacode veya template
STL konuları.Bizim mint örneğini buna göre uyarladı.

SmartPtr<Mint>ptr{new Mint{123}}; burada derleyici bu türden bir sınıfın kodunu yazacak
SmartPtr<string>spx{new string{123}};  

Örneği yazalım

template<typename T>
class SmartPtr {
public:
	SmartPtr() : mp{ nullptr } { }  
	
	SmartPtr(T* p) : mp{ p } { }

	SmartPtr(const SmartPtr&) = delete; 
	SmartPtr& operator=(const SmartPtr&) = delete; 

	SmartPtr(SmartPtr&& other) : mp{ other.mp }
	{
		other.mp = nullptr;
	}

	~SmartPtr() 
	{
		if(mp)
			delete mp;
	}
	T& operator*()
	{
		return *mp;
	}

	T* operator->()
	{
		return mp;
	}

private:
	T* mp;
};

int main()
{
	SmartPtr<Mint> ptr{new Mint(1234)}; //Derleyici bu şablondan/temlate den faydalanarak bir sınıfın kodunu yazacak.
	//mint değilde string türünden nesnenin hayatını kontrol edecek nesne için sınıf oluştursak
	SmartPtr<string>spx{new string{"Alican"}};
}

BUNLAR STL KONULARI.KISACA GÖZATTI.

------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------


FUNCTION CALL OPERATOR OVERLOADING
----------------------------------

C ve C++ ta func call operatör seviyesinde bir işlem.

int func();
int main()
{
	func();
}

C de 3 olanak var.

func(12) func çağrı olması için ihtimaller

a - func bir functiondır
b - func bir function pointer
c - func functional macro dur.

-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------

C++ TA DURUM FARKLI

foo(12)
bunun fonksiyonu çağırması durumu farklı seçenekleri getiriyor.
Bir fonksiyonun çağrılmasını sağlayan varlıklara callable entity deniyor ya da sadece callable.

A - Gerçek func olabilirler 
B - Function ptr değişken olabilirler
C - Func çağrı opeatörünün operandı olan bir sınıf nesnesi olabilir
D - Foo bir sınıf nesnesidir bu sınıf nesnesi func call operatörünün
	operandı olmuştur, bu durumda ilgili sınıf function call operatorunu overload etmişse, aslında çağrılan sınıfın
	function çağrı operator functionudur.

Func call operatörünü overload ederek sınıf nesneleri,
Func call operatörünün operandı olarak kullanılabilen sınıflara verilen 2 populer terim var
1 - Functor class
2 - Function object


Başka ihtimallerde var.
Modern C++ ta gelen LAMBDA EXPRESSION var. Çok sık kullanılıyor.

Derleyici lambda ifadesini görünce bir sınıfın kodunu yazıyor ve ifadeyi o sınıf türden geçici nesneye dönüştürüyor.
Bunuda func call operatörününün operandı yapılıyor.

Derleyicinin lambda ifadesi karşılığı oluşturduğu sınıf türüne CLOSURE TYPE deniyor.
Bu sınıf türden geçici objeyede CLOSURE OBJECT deniyor.


int main()
{
	[]() {}();  Bu geçerli bir C++ statement.Bu lambda ifadesiyle compilera bir sınıf kodu yazdırdık.
}				Compiler sınıf türden geçici nesne oluşturdu. Bizde bu nesneyi func call operatörününü operandı yaptık.



BAŞKA CALLABLE YAPILARDA VAR.
std library nin function da
std::function<int()> f;  Bu sınıf türden nesne oluşturunca yine func call operatörünün operandı yapılabiir.

DAHASIDA VAR.TAM LISTE DEĞİL

----------------------------------------------------------------------------------------------------------------------

OVERLOADING İŞLEMİ
------------------

class Functor{
public:
	void operator()()
	{
		std::cout << "Functor::operator()() this = " << this << "\n";
	}

};

// Function call operator (). 2 adet yazdık
// const olabilir,return değeri başka olabilir.
// Fonksiyon parametresi olabilir yada olmayabilir.default arg alabilen tek operatör functiondur.
// Hatta bir sınıfın birden fazla function çağrı operatör fonksiyonuna sahip olmasını sağlayabilirim.

int main()
{
	Functor f;

	std:cout << "&f = "<< &f << "\n";

	f();
}

Aynı nesneyi gördük
ÇIKTI
-----
&f = 00DAFA2F
Functor::operator()() this = 00DAFA2F

-----------------------------------------------------------------

Soru: Default argüman alabilir demiştik?

class Functor{
public:
	void operator()(int x = 0)
	{
		std::cout << "Functor::operator()() this = " << this << " x = " << x << "\n";
	}

};

// function call operator (). 2 adet yazdık
// const olabilir,return değeri başka olabilir...
//parametre olabilir.default arg alabilen tek operatör
//functionudur.

int main()
{
	Functor f;

	std:cout << "&f = "<< &f << "\n";

	f(12); // 12 yazar
	f(); // 0 yazar default arg tan ötürü.
}


-----------------------------------------------------------------------------------------------------------------

ÖZET:
Sınfıların operator func call functionu return değeri istediğin gibi seçenekleri parametresi olabilir olmayabilir,
varsayılan arg alabilir, sınıfın nonconst veya const func olabilir.
STATIC ÜYE FONK OLMASI YASAKLANMIŞ. GLOBAL OLARAKTA OVERLOAD EDILEMEYENLERDEN BIRI.

Kilit Nokta:
neden Böyle bir araç var? Buna daha yolumuz varmış

class Functor{
public:
	void dosomething(int x)
	{
		std::cout << "Functor::operator()() this = " << this << "\n";
	}
};

int main()
{
	Functor f;
	f.dosomething(19);		NE FARK VAR??
}							GENERIC PROGRAMLAMADA ÖNEMİNİ GÖRECEĞİZ

NE FARK VAR??
GENERIC PROGRAMLAMADA ÖNEMİNİ GÖRECEĞİZ
C++ ve STL in en çok kullanılan araçlarından biri. Günlük kodlamada sıksık karşımıza çıkıyor.

BUNU OVERLOAD EDINCE NE OLUYOR?
Global bir func olsaydı(aşağıda tanımladım) bu func ın bir state bilgisi olmayacaktı
static local variable kullanabilirdik belki yada parametre değişkeni kullanırdık.

void func()
{
	//mesela bu
}

Sınıf nesnelerinini bir state i var. Bu bir üye fonksiyon olduğundan sınıfın veri elemanlarını kullanabilir.

Yine bir template örneği
Rasgele sayı üreten func yazdı

#include <iostream>
#include <functional>
#include <limits>
#include <cstdlib>


class Random{
public:
	Random() = default;
	Random(int low, int high) : m_low{low} , m_high{high} { }

	int operator()()
	{
		++m_cnt;
		return std::rand() % (m_high - m_low) + m_low; // burada rasgele sayı önemli değil ondan rand kulandık.
	}													// rasgelelik önemliyse kesinlikle C nin rand ı kullanılmamalı.

	int get_count()const
	{
		return m_cnt; // kaç kere çağırıldığı yada kaç tamsayı ürettiğinin bilgisi.
	}

private:
	int m_cnt{};
	int m_low = 0;
					// C de limits.h de INT_MAX vardı. 
					// C++ ta limits var.içinde std::numeric_limits<int>::max(); kullanılabilir. 	

	int m_high = std::numeric_limits<int>::max();
};


int main()
{
	Random rand_x{10,25};
	for(int i = 0; i < 10; i++)
	{
		std::cout << rand_x() << " ";
	}
	std::cout <<"\n";

	Random rand_y{923,987};
	for(int i = 0; i < 10; i++)
	{
		std::cout << rand_y() << " ";
	}
	std::cout <<"\n";

	auto n = rand_y.get;_count();
	std::cout <<"n = " << n << "\n" ;

}

İLERİDE GENERIC PROGRAMLAMADA ANORMAL İŞLER YAPILACAK BU ARAÇ İLE.

---------------------------------------------------------------------------------------------

Avantajları
1 - Kendisi bir func değil normalde sınıf nesnesi bu sebeple, state bilgisi tutar.
2 - İnline expansion optimizasyonu için çok daha uygun bir aday.

---------------------------------------------------------------------------------------------

TÜR DÖNÜŞTÜRME OPERATÖRLERİNİN OVERLOAD İŞLEMİ
----------------------------------------------

Static Const Reinterpret Dynamic

Sınıf türden nesneyi, sınıf türü dışında başka bir türe dönüştürmek için (otomatikte olabilir)
bir veya birden fazla fonksiyon tanımlayabilirim. Bu tanımladığım fonksiyonlara tür dönüştürme operatör func deniyor.
Sınıf türden nesneyi başka türe dönüştürmek söz konusu olunca derleyici durumdan vazife çıkarıp böyle functionalardan
birine çağrı yapıyor.

Bir sınıf türden değeri, o sınıf türden olmayan başka türe(target) dönüştürebilir.
target, pointer başka bir tür, başka bir class, bir pointer,bir referans türü olabilir...

Tür dönüşümlerinden bahsederken dönüşümleri farklı kategorilere ayırmıştık
- Standart conversion
- User defined conversion(normalde olmayan dönüşüm) bir bir fonksiyon bildiriyoruz, derleyici dönüştürme işini o fonksiyona çağrı ile yapıyor.

Conversion Ctor tek parametreli ctor.Sınıfın tek parametreli constructorları, sınıf türündenden olmayan ifadeyi sınıf türünden nesne
değişkenine dönüştürüyordu

---------------------------------------------------------------------------------------------------------------------------------------------------

2. IHTIMAL VAR.
Sınıf türden değişkeni sınıfın tür dönüştürme operatör func ile başkabir türe dönüştürebiliriz.
SINIFIN ÜYE FONKSIYONU OLMAK ZORUNDA.GLOBAL BİR FUNC İLE TÜRDÖNÜŞTÜRME OPERATÖRLERİNİ OVERLOAD EDEMEYİZ.
KURALLARDA VARDI ZATEN.

SENTAKS BİRAZ TUHAF
class Myclass{
public:
	operator hedef_tür(); //return değeri yazılmıyor ama hangi tür ise onu döndürüyor return değer olarak.
	operator hedef_tür()const;
};

int main()
{
	Myclass m;

	int ival = m; //SENTAKS HATASI
}


---------------------------------------------------------------------------

DEVAM EDELİM

SENTAKS
operator hedef_tür();

operator hedef_tür()const;  
// const olabilir olmayabilir.Doğal olan const olması çünkü casting de yan etki yok.
Değiştirmiyorsa const olmalı.

Geri dönüş türü yazılmıyor.Ama geri dönüşü olmadığı anlamında değil bu.
operator int in geri dönüşü int, operatör double return ü double dır.

Başa int yazarsak sentaks hatası
int operator hedef_tür()const;   // SENTAKS HATASI


EKLIYORUZ

class Myclass{
public:
	operator int()const; 
	//operator int&()const;
	// operator double()const; böylede olurdu.Neye dönüştürme yapılacaksa o seçilip yazılabilir.
	
};

int main()
{
	Myclass m;

	int ival = m; //SENTAKS HATASI DEĞİL. operator int()const;  sayesinde dönüşüm gerçekleşti.

	int ival = m.operator int();  // BUDA GEÇERLİ.Burada da cast ediliyor.

}


--------------------------------------------------------------------

DAHA GERÇEKÇİ ÖRNEK

ÖR: Counter sınıfı
Header only library olacak

class Counter{
public:
	explicit Counter(int val = 0) : mval{val} {}
	Counter& operator++()
	{
		++mval;
		return *this;
	}
	Counter operator++(int)
	{
		Counter temp{*this};
		operator++(); // Bir yukarıdaki overload çağrılır.Bunu ben sormuştum derste.
		return temp;
	}
	Counter& operator--()
	{
		--mval;
		return *this;
	}
	Counter operator--(int)
	{
		Counter temp{*this};
		operator--();
		return temp;
	}
	Counter& operator+=(int val)
	{
		mval += val;
		return *this;
	}
	Counter& operator-=(int val)
	{
		mval -= val;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Counter &c) //Inserter func ın kodu
	{
		return os << "[" << c.mval << "]" << "\n";
	}

	operator int()const // bunu sonradan ekledik hata verdiğini görmek için
	{
		return mval;
	}

private:
	int mval;

};


int main()
{
	Counter c{4};

	for(int i = 0; i < 10; ++i)
	{
		++c;
	}

	std::cout << "c = " << c << "\n";

	//Dikkat!!!
	//int ival = c.operator int();  //Burasıda aynı çağrı aşağısı ile.Counter türünden int türüne dönüşüm yoktu.
									//operator int()const yazınca LEGAL OLDU.
	int ival = c; // SENTAKS HATASI ŞUANDA. 
	

	std::cout << "ival = " << ival << "\n";
}

Tür dönüştürme operatör functionunun varlığı artık int gereken yerde Counter kullanmamı mümkün kılıyor.

int square(int a) // global bir func
{
	return a*a;
}

std::cout << square(c) "\n"; //yukarıda mainde içinde gibi düşün


----------------------------------------------------------------------------------------------------------------

Ben olsam yapmam diyor Hoca :D:D:D:D

Kontrol dışı bir type cast yapıyor diye.Biz Conversion Ctoru da explicit ediyorduk.Boşuna değil.
Başımızı derde sokabilir.

Conversion Sequence
-------------------
Standart conver + User defined conver şeklinde yapılabiliyorsa bunu örtülü yapar.
User defined conver + Standart conver şeklinde yapılabiliyorsa bunu örtülü yapar. 2 türlüde yapar.

user defined + user defined IMPLICIT YAPMAZ


MESELA AŞAĞIDAKILERI YAPTIK.
c burada Counter nesne değişkeni
bool b = c;		hata yok 
long double f = c;		yine hata değil.


----------------------------------------------------------------------------------------------

Buna bir önlem almak gerekecek.
Hem örtülü hemde Tür dönüştürme ile yapılabiliyor.
Yani bilerek te yapabiliriz aşağıdaki gibi.

int ival = static_cast<int>(c); //açık açık Counter ı int e dönüştürdük.Burada da compiler tür dönüştürme operatör fonksiyonunu çağırır.

C++11 e kadar explicit sadece Ctor için kullanılıyordu.
C++11 den sonra tür dönüştürme operator functionları içinde kullanılabilir hale geldi.
Çok özel durum yoksa sınıfın tür dönüştüme operatörlerini explicit keyword ile tanımlayacağız/bildireceğiz.

explicit kullanılacak ve kodda değiştirilecek bu kısım.

explicit operator int()const
{
	return mval;
}

int ival = c; artık sentaks hatası
square(c); sentaks hatası mainden test edilebilir. 1.05

static cast ile hata vermez.
int ival = static_cast<int>(c);
square(static_cast<int>(c));


NOT : Explicit olarak yazarsak operator int / double .. gibi overloadlar 
	logical ifade gereken yerlerde kullanılamaz. Explicit olarak yazarsak kullanılabilir
	ama tercih edilmemeli.BUnun için operator bool tercih edilmeli.

---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------

Type cast yerine function yazsak olmaz mı?
Olur.
int to_int() const { retun mval; } olabilir.



STD LİBRARYDE TYPE CAST IN KULLANILDIĞI BIR YER VAR. SADECE STD DEĞIL.

Cevap : operator bool

int main()
{
	int x{140};
	
	int *p = &x;

	int ival = 4;

	if(p) // bunların ne anlama geldiğini temel C bilenler biliyor zaten.
	{
	
	}

	if(ival) //buda öyle
	{
	
	}
}


-------------------------------------------------------

int main()
{
	SmartPtr p  = new ResourceUser;
	if(p){
		BÖYLE KULLANILAMAZ ÇÜNKÜ OPERATOR BOOL BU SINIFTA TANIMLANMAMIŞ
	}	BUNU KULLANABİLİYOR OLMALIYIZ.
}



NOT:
IF, LOGIC OPERATOR OPERANDLARI, KOŞUL OPERATÖRÜNÜN 1. OPERANDI OLAN IFADE,
WHILE PARANTEZI IÇINDEKI, FOR UN ; ; ARASINDAKI IFADE , 
DO WHILE IN WHILE IÇINDEKI IFADE.BUNLARDA HEP LOGIC IFADE BEKLENIYOR.

--------------------------------------------------------

ÖR: Smart Pointer sınıfının Orijinali

#include <memory>

int main()
{
	unique_ptr<int>uptr; // bos unique_ptr
	if(uptr)
		std::cout << "Bos Degil\n";
	else
		std:cout << "bu bos\n";   BOŞ ÇIKAR
}

--------------------------------------------------------

int main()
{
	unique_ptr<int>uptr{new int{546}};
	if(uptr)
		std::cout << "Bos Degil\n"; BOS DEĞİL ÇIKAR
	else
		std:cout << "bu bos\n";
}

-----------------------------------------------------------

int main()
{
	unique_ptr<int>uptr{new int{546}};
	if(uptr.operator bool()) // yazılabilir.zaten çağrılanda bu.
		std::cout << "Bos Degil\n"; BOS DEĞİL ÇIKAR
	else
		std:cout << "bu bos\n";
}

---------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------

OPERATOR BOOL UN BIR FARKI VAR.EXPLICIT OLMASI KULLANILMASINI ENGELLEMIYOR.
EXPLICIT OLARAK YAZIP YİNE İF İÇİNDE KULLANILABİLİR.
AYRICA SINIF TÜRDEN İFADEYİ BİR DEĞİŞKENE 0 VEYA 1 OLARAK YAPABİLİR.
AMA BUNUN İÇİN EXPLİCİT OLMAMASI GEREKİYOR !!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------


explicit operator bool()const  // BUNU operator int() const yerine yazdı
{
	return mval == 0 ;
}


int main()
{
	Counter cx{34};
	Counter cy{90};

	if(cx)  hata vermez.Explicit olasına rağmen
		std::cout << "cx = " << cx << "\n";

	auto n = cx ? 20 : 35;
	if(cx && cy) // hiçbiryerde sentaks hatası yok Çünkü operator bool yazıldı.
	{
		std::cout << "Dogru\";
	}

	while(--cx) //hiçbirinde sentaks hatası yok.
	{
		std::cout << cx << "\n";
	}
}

OPERATOR BOOL DEĞILDE OPERATOR INT OLSA YINE ÇALIŞIR MIYDI ?
EVET AMA KESINLIKLE SEÇILMEMESI GEREKIYOR.BU AMAÇTA OPERATOR BOOL KULLANILMALI.


----------------------------------------------------------------------------------------------------------

int main()
{
	counter c{3};

	int ival = c; //burada operator bool explicit tanımlanmış.artık bool türüne dönüşüm burada olmayacak
}					// bool a dönüşecek oradan da int e dönüşecekti.Ama explicit olduğu için SENTAKS HATASI

NOT : OPERATOR BOOL EXPLICIT OLARAK TANIMLANDIĞINDA BILE LOGIC BAĞLAMLARDA ÇALIŞIR AMA
BURADAKI ÖRNEKTE DÖNÜŞÜM YAPMAZ.

--------------------------------------------------------------------------------------------------------------


int main()
{
	int x;

	while(std::cin >> x)
		std::cout << x << "\n";

} // bunun anlaşılması için C++ a ciddi düzeyde hakim olmalı.

std::cin >> x burada çağrılan fonksiyonun return türü istream&
aslında std::cin.operator>>(x) demek bunun return değeri *this
cin in kendisi.Cin nesnesinin kendisinin kullanılması geçerli ise 
o zaman ya bool a dönüştüren operator bool functionu var yada bool türüne
dönüşebilecek bir türe dönüştüren bir operatör türdönüştürme fonksiyonu var.

ifadenin açılmış şekli Moden C++ ta aşağıdaki gibidir.

while(std::cin.operator>>(x).operator bool ())     // 1.28 de açıklaması var. Ben gerek görmedim yazmaya.true false olayı
	std::cout << x << "\n";


EXPLICIT YAPARSAK LOGIC BAĞLAMDA KULLANILIYOR AMA TÜR DÖNÜŞÜMÜ YAPMIYOR
if, while, do while, for ; ; , &&, ||, !, expr ?  ... buralarda explicit olsa dahi çalışır

DVAL = MYCOUNTER; EXPLICIT OLMASAYDI BU DA LEGAL OLACAKTI.TEHLIKELI BIR DURUM. 1 VEYA 0 OLACAKTI.

OPERATOR BOOL YERINE OPERATOR INT YAZSAK IF IÇINDE GEÇERLI OLUR MU ? HAYIR

Counter mycounter {12};
bool b = mycounter; SENTAKS HATASI ÇÜNKÜ LOGİC BAĞLAM DEĞİL VE EXPLICIT YAPILDI
yada static cast yapılacak

int ival = (bool)mycounter; Bu geçerli. static cast gibi.

-----------------------------------------------------------------------------------

class Myclass{
public:
	operator bool();
};

int main()
{
	Myclass m1,m2;
	auto n = m1 + m2; //Sentaks hatası yok.Çok tehlikeli.Explicit değilse
						// böyle bile çağrılır.Bunlar bool a dönüştürülebilir, sonrasında da implicit conversion ile int e dönüştürülür.
}						// derleyici yine vazife çıkarıp user + standart dönüşüm -> kendisi bunu dönüştürür.

MOLA

=================================================================================================================================
=================================================================================================================================

void func(int &);
void func(int &&);
void func(const int &);

//Hepsi overloading

void func(int &)
{
	std::cout << "int &\n";
}

void func(int &&)
{
	std::cout << "int &&\n";
}

void func(const int &)
{
	std::cout << "const int &\n";
}

int main()
{
	int x = 10;
	const int cx = 20;

	func(x); // 1.
	func(cx); // 3.
	func(20); // 2.
	func(move(x)); //2.
	func(move(cx)); //3.
}

Şöyle bir overload da olabilir.


void func(const int &&)
{
	std::cout << "const int &&\n";
}

func(move(cx)); //bunu çağırınca const int && çağrılır.Move da constluk gitmiyor

-----------------------------------------------------------------------------------------


class Myclass{
public:
	void func()
	{
		std::cout << "Myclass::func()\n";
	}
};


int main()
{
	Myclass m;

	m.func();
	move(m).func();		// && ile yani sağ taraf değeri ile çağrıldı
	Myclass{}.func();  //HEPSİ ÇAĞRILIR.
}


------------------------------------------------------------------------------------------

Ben üye foksiyonu lvalue exp olan bir myclass nesnesiyle çağrılınca farklı bir function
rvalue exp olan bir myclass nesnesiyle çağrılınca farklı bir func/kod çalışsın. Buda Mümkün
Alttaki Sentaksa iyi bak. Buna Ref Qualifier deniyor.


class Myclass {
public:
	void func()&
	{
		std::cout << "Myclass::func() &\n";
	}

	void func()const&
	{
		std::cout << "Myclass::func() const &\n";
	}

	void func()&&
	{
		std::cout << "Myclass::func() &&\n";
	}
};

int main()
{
	Myclass m;

	m.func(); //1. çağrılır. Lvalue exp olan sınıf nesnesi çağrıldı

	Myclass{}.func(); // 3. çağrılır.Rvalue exp olan sınıf nesnesi çağrıldı

	const Myclass cm;

	m.func(); // & çağrılır
	cm.func(); // const & çağrılır
	Myclass{}.func(); // && çağrılır
	std::move(m).func(); // && çağrılır
	std::move(cm).func(); // const & çağrılır.

}

ÇIKTI
-----
Myclass::func() &
Myclass::func() &&
Myclass::func() &
Myclass::func() const &
Myclass::func() &&
Myclass::func() &&
Myclass::func() const &


void func()const &&
{
	std::cout << "Myclass::func() const &&\n";
}

OLSAYDI
move(cm).func(); // Bu fonk çağrılırdı.

REFERENCE QUALIFIER. İleride detaylı görülecek.

--------------------------------------------------

BİR SORU ÜZERİNE ANLATILDI
--------------------------

#include <iostream>
#include <functional>
#include <limits>
#include <cstdlib>


//Aşağısı aslında bir idiyom.
class Person {
public:
	const std::string& Name()const& // bu tip örneklerde neyi get ediyorsak return değeri o türden referans olması.
	{								// maliyeti çok düşürüyor çünkü.Dangling referans olmamasına dikkat edeceğiz. Bu konulart ileride
									// yine detaylı görülecek.
		return mname;
	}

	//dangling senaryosu olabilir diye taşıma yapmak daha mantıklı olabilir.
	// referans semantiği ile değilde kopyalama semantiği ile dönülecek
	std::string Name()&& // burada return değeri mname, func return değeri ise string sınıfı.kopyalama olacağından dangling ref olmaz
	{
		return mname;
	}

private:
	std::string mname;

};


int main()
{
	Person p;
	//..
	auto& s = p.Name();
}

===================================================================================================================================
===================================================================================================================================
===================================================================================================================================
===================================================================================================================================
===================================================================================================================================




ŞİMDİ BU DİLDE BAZI EKSİK KALAN YERLER VAR.BUNLAR ANLATILACAK GÜNÜN SONUNA KADAR
--------------------------------------------------------------------------------
ENUMERATIONS.
C++ ta enumerations, C deki gibi değil.

#include <iostream>
#include <conio.h>

enum class Weekday {
	Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
};

//Global operator overloading mekanizması ile bunu sağlayabiliriz.
Weekday& operator++(Weekday& wd)
{
	return wd = wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd) + 1);
}

Weekday operator++(Weekday& wd, int)  // dummy int postfix demek :D
{
	auto temp{ wd };

	operator++(wd);

	return temp;
}

std::ostream& operator<<(std::ostream& os, const Weekday& wd)
{
	static const char* const pdays[]{
		"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday",
	};

	return os << pdays[static_cast<int>(wd)];
}

int main()
{
	Weekday wd{ Weekday::Monday };
	// ++wd;  SENTAKS HATASI. C de Direk int olarak ele alındığı için hata yoktu.
	// std::cout << wd; Burasıda sentaks hatası.Çünkü böyle bir inserter yok.
						//Operator overloading mekanizmasından faydalanıp yapabiliriz.

	//fonksiyonlar yazıldı

	while (true)
	{
		std::cout << wd++ << " ";
		_getch();
	}

}

-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------

DELEGATING CONSTRUCTOR C++11
----------------------------
Bazen sınıfın 1 den fazla ctoru var.Bunların implemente edilmesi gerekiyor ama bunların ortak bir kodu var.
Bunu tekrar etmek yerine, bu kodu bir yere koyup(refactor edip) bu ortak kodu kullanmak istiyoruz.


MODERN C++ ÖNCESİNDE AŞAĞIDAKİ GİBİ IMPLEMENTE EDİLİYORDU

class Myclass{
public:
	Myclass(int)
	{
		//başka kodlar da olabilir
		init();
	}
	Myclass(int,int)
	{
		init();
		// ... 
	}
	Myclass(int,int,int)
	{
		init();
		//..
	}
	Myclass(const char *)
	{
		init();
	}
private:
	void init();
};

BU INITI CLIENT KODLARIN ÇAĞIRMASI SAKINCALI ÇÜNKÜ NESNEYI HAYATA GETIREN FUNCTIONLARDAN BIRI.
ESKI C++ TA BUNU PRIVATE FONKSIYON YAPIYORDUK.BU ÇOK YAYGIN BIR IDIYOMDU.ALTERNATFI VAR ARTIK.

Bunun Dezavantajları
--------------------
1 - Yalan söylüyor, çünkü initialization buna gelene kadar bitiyor. ctor a girişte init oluyordu.Yoksa eğer default member init oluyor.
2 - Sınıfın kendi functionları privateları çağırabilir, yanlışlıkla herhangibir member func içinde çağırsak koruma mekanizması yok.

Modern C++ bir araç veriyor.
Bir Ctor işinin bir kısmını görmesi için başka bir Ctoru çağırabilir.
İnit yerine çağıracağımız ortak kodun kendiside bir constructor.
Ctor initializer listte başka bir Ctor olacak yani :D:D
Buna Delegating Constructor deniyor.


class Myclass{
public:
	Myclass(int a) : Myclass(a,a,a)		// işte buradaki yapı delegating constructor. Init görevini alaşıdaki ctora havale etti.
	{
		
	}
	Myclass(int a,int b) : Myclass(a,b,0)  //Buda aşağıdakine havale etti.
	{
	
	}
	Myclass(int x,int y,int z) : mx{x}, my{y}, mz{z} 
	{
	
	}
	Myclass(const char *p) : Myclass(std::atoi(p),0,0) //aynı şekilde 3 parametreli ctora havale etti bu işi. 
	{
	
	}
private:
	int mx, my, mz;
};

ÖNEMLİ KURAL
Hem delege edip hemde elemana tekrar ilk değer veremeyiz.!!!

Yukarıdan Bir örnek
Myclass(int a,int b) : Myclass(a,b,0)  , mz{10}  //Burası hem delege edip hemde initilization etmeye çalışmış SENTAKS HATASI
{

}

-----------------------------------------------------------------------------------------------

Burada default member initializer sentaki kullanilabilir.
Eğer delege ettiğimiz ctor ilk değer vermezse tabi.

class Myclass{
public:
	Myclass(int a,int b) : Myclass(a,b)  //3. parametre yok
	{

	}
	Myclass(int x,int y,int z) : mx{x}, my{y} //burada da init edilmemiş ama aşağıda default member initten buraya yazılır compiler tarafından
	{

	}
	
private:
	int mx, my, mz = 25;
};

NOT : DELEGE SAYISI 1 OLMAK ZORUNDA DEĞİL. BİRİ BİR CTORU DELEGE EDER, DELEGE ETTİĞİ İSE BİR BAŞKASINI DELEGE EDER.

NOT : RECURSİVE(RECURSIVE BİR FUNC CALL MEKANİZMASI) BİR DELEGE OLMAMASI GEREKİR. YA SENTAKS HATASI YA DA UB.


===================================================================================================================================
===================================================================================================================================
===================================================================================================================================

İF DEYİMİ

C++ IN İLK STANDARTLARINDAN BU YANA İF DEYİMİ İLE İLGİLİ C DE OLMAYAN BİR ÖZELLİK VAR
İf içerisinde değişken tanımlama olayı

int foo();
char* func();

int main()
{
	if(int x = foo()){  //Burası C++ ta geçerli.Eskiden beri var bu. x true değerlendirilirse if e girecek
	
	}

	x artık burada yok

	if(char *p = func()) // yine geçerli. true false durumuna göre ife girecek.
	{
	}
	
	if(auto p = func()) // auto geçerli.
	{
	}


}

Burada x ve p nin scope u if-else bloklarının içerisi.Scope leakage engelliyor.
if-else blokları içersinde geçerli bu. Scope leakage.Hoca code review yaparken de
buna çok dikkat ediyormuş. 


---------------------------------------------------------------------------------

if(Mercedes *pm = dynamic_cast<Mercedes *>(carptr))  // bu konular sonra görülecek 
	pm->open_sunroof();								//dynamic cast nullptr döndürürse	
													// girmez aksi halde girer

									// Bu if Modern C++ ile akalalı değil.
									// eskiden beri var.


======================================================================================================================
======================================================================================================================
======================================================================================================================


IF WITH INITIALIZER
-------------------
Bu modern C++ ta değil D++ 17 de geldi :D
Gereken yerlerde mutlaka kullanılmalı!!

Dildeki değişiklikler kategorilere ayrılıyor.
Core Syntax dilin temel sentaksı anlamında

if(T x = init_expr; x > 10) // normalde C++17 ye kadar if içinde ; kullanılamaz.Sentaks hatasıydı.C++17 den sonra değil
{							// ; burada tabiki sequence point oluşturur.
	
}


if(int x = foo(); x >10) // geçerli.
{
	
}

if(auto x = foo(); x >10) //auto da geçerli.
{

}




-------------------------------------------------------
C de ise
if(x = foo(), x >10) bu geçeliydi.initialization yok. 
{

}

--------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <conio.h>


int main()
{
	using namespace std;
	string str;
	cout << "bir yazi girin";

	std::getline(cin, str);

	auto idx = str.find('a'); // string sınıfında göreceğiz.yazı içinde a yı aradı. a karakteri yoksa function return değeri
								// size_t türünden değer olan string sıfınının bir constexpr elemanı olan nposa eşit.

	//if(idx != string::npos)
	//{
		// ..
		//idx;
	//}
	//Yukarıda idx in scope unu genişletmiş oldum bunu if with init ile yazmak daha mantıklı.

	if (auto idx = str.find('a'); idx != string::npos)
	{
		cout << "Bulundu index = "  << idx << "\n";
		str[idx] = '!';
		cout << str << "\n";
	}
}



----------------------------------------------------------------------------------------------------------------------

Aşağıdakiler birbirinin aynısı

if(int x = foo()) ---> if(int x = foo() ; x) ---> if(int x = foo() ; x != 0);   //Bunlar aynı

----------------------------------------------------------------------------------------------------------------------

Switch içinde var.Modern C++ ta geldi

switch(	int x = foo())
{
...
}

----------------------------------------------------------------------------------------------------------------------

int foo();
while(int x = foo())  Geçerli ama while(int x = foo() ; x < 45) geçerli değil.
{

}

======================================================================================================================
======================================================================================================================
======================================================================================================================



STRUCTURED BINDING C++ 17 DE GELDİ
----------------------------------
Tam anlamak için başka konularıda bilmek gerekiyor

Kısaca yazalım

struct Data {
	int a, b;
	double c;
};


//Decomposition şu anlamda kullanılıyor. yapının her elemanını bir değişkene atayacak demek.
int main()
{

	Data Mydata = { 1,2,3 };

	Structured Binding
	Burada int x = Mydata.a;   int y = Mydata.b;     double z = Mydata.c;
	Dikkat x burada Mydata.a ya referans değil. yeni bir değişken

	auto [x, y, z] = Mydata; //yine otomotik ömürlü değişkenler.Scope sonuna kadar hayatta olacaklar.
	auto [x, y, z] {Mydata};
	auto [x, y, z] (Mydata);


	------------------------------------------------------
	
	referans decleratörünü kullanırsak bu sefer refere etmiş olur
	 burada int &x = Mydata.a;   int &y = Mydata.b;     double &z = Mydata.c;
	auto &[x, y, z] = Mydata;

	std::cout << x << "\n";
	Mydata.a = 25; // artık x te değişti.
	std::cout << Mydata.a << "\n";


	------------------------------------------------------
	
	const & kullanabiliriz.
	const auto& [x, y, z] = Mydata;
	x = 4; SENTAKS HATASI OLUR


	------------------------------------------------------

	Sağ taraf ref te yapılabilir.
	auto&& [x, y, z] = Mydata;


}


--------------------------------------------------------------------------------

NELER YASAK ?

struct Data {
	int a, b;
	double c;
};

int main()
{

	Data Mydata = { 1,2,3 };
	
	Data[x,y,z] = Mydata;  //BURASI SENTAKS HATASI. auto olmalıydı
}

----------------------------------------------------------------------

Data Mydata = { 1,2,3 };

auto [x, y] = Mydata; //SENTAKS HATASI. Eleman sayısı örtüşmüyor.

auto [x, y , _ ] = Mydata; //Böyle bir konvensiyon kullanılıyor.


----------------------------------------------------------------------

Data Mydata = { 1,2,3 };

auto [x, y ,z] = Mydata; 
int x = 23; //SENTAKS HATASI.Aynı scopeta x yine tanımlandı

----------------------------------------------------------------------

Çok iyi örnek

struct Data{
	int a,b;
	double c;
};

Data func()
{
	return { 1, 3, 4.5};
}

int main()
{
	auto[x,y,z] = func();
}

----------------------------------------------------------------------

STRUCTURED BINDING, IF WITH INITIALIZER ILE BIRLIKTE DE KULLANILIYOR.

struct Person{
	std::string name;
	int age;
	double wage;
};

Person get_person()
{
	//...
	return { "Alican", 56, 90.74 };
}

int main()
{
	if(auto[name,age,salary] = get_person(); age > 40)
	{
		
	}
}

------------------------------------------------------------------------

Range Base For Loop tada kullanılabilir.


struct Person{
	std::string name;
	int age;
	double wage;
};

int main()
{
	using namespace std;

	vector<Person> pvec(100); // vector bu

	for(auto per : pvec) // döngünün her turunda per değişkeni bir baştan bir sonraki öğeyi tutar.
	{						// eğer vectordeki veriler, structured bindingte kullanılmaya uygun olan bir türdense
							// o zaman doğrudan döngüde auto[name,age,wage] : pvec yazabilirim.Örnek aşağıda
	}


	for(auto[name,age,wage] : pvec) // bunu auto veya auto& veya const auto& veya auto&&(forwarding diyor) yaparakta kullanabiliriz.
	{
		
	}

	//sadece yapılar için değil.Başka veri tipleri içinde kullanılır.

}

------------------------------------------------------------------------

DİZİLERDE KULLANIMI

double a[]{1.2, 3.4, 5.6};

auto[d1,d2,d3] = a; //GEÇERLİ.


//hatta referansta yapılabilir

auto&[d1,d2,d3] = a; //GEÇERLİ.
d1*=10;
d2*=10;
d3*=10;

diziyi yazdırırsak.Dizide etkilenmiş olur artık. 11 22 33 yazar.

for(auto val : a)
	std::cout << val << "\n"; // 11 22 33 yazar. Yukarıda referans dekleratörü olmasaydı değişmezdi.
							  

----------------------------------------------------------------------------------------------------------

C++ ın belirli sınıfları bu structured bindings interface i sunuyorlar.
Ve biz kendi sınıflarımızda olması için bunu implemente edebiliyoruz.

C yapıları C dizileri için bu doğal olarak var. Myclass isimli sınıf için bunu yapmak mümkün ama
bazı kodları yazmak gerekiyor.

Mesela C++ array sınıfı

std::array<int, 3>foo(); // foo isimli func return değeri sınıf türden

int main()
{
	using namespace std;
	auto [a, b, c] = foo(); //Geçerli.

}

-------------------------------------------------------------------

//Soru: ptr nin türü nedir? Cevap int[4] tür.

struct Nec {
	int a[4];
	double dval;
};

Nec foo();

int main()
{
	using namespace std;

	auto [ptr, d] = foo();
	//Soru: ptr nin türü nedir? Cevap int[4] tür.
	//auto kurallarına göre array decay oluyordu.Bu yanıltabilir.

}

NEDEN BÖYLE OLDUĞUNU ANLATAN KOD

struct Nec{
	int [10];
	double dval;
};

int main()
{
	using namespace std;
	
	Nec mynec= {{},2.3};

	auto[age,salary] = mynec; 
	//aslında burada bir nesne tanımlanıyor.bu int veya double türden bir nesne değil.
	// derleyici type decutionu = in sağ tarafına bakarak yazıytor.
	// Derleyici biz görmesekte alt seviyede Nec türden bir nesne oluşturdu
	// Nec object = mynec; // bu nesne değerini mynecten alan ve nec türden olan bir nesne
	// bizim age imiz aslında burada object.ival e verilmiş bir eş isim gibi.
	// compiler nec türden nesneyi kullanmamıza izin vermiyor,burada sadece eleman
	// olan değişkenin kendisini kullanmamıza izin veriyor. 
	//Yani object yarattı ve mynec e eşitledi. age e object.ival i eş isim olarak verdi.

	// NOT: typeid(mynec).name(); // bir ifadenin türünü yazdırır.

	cout << typeid(age).name(); // int [10] yazdı türüne

		
	
}	

--------------------------------------------------------------------------------------------------------------------

MÜLAKAT SORUSU
--------------

Struct Nec{
	int [10];
	double dval;
};

int main()
{
	using namespace std;

	Nec mynec= {{},2.3};

	auto[ar,salary] = mynec;

	auto p = ar; // auto tür çıkarımında array decay oluşur. int * dır p nin  türü

	cout << typeid(p).name(); // int * 

}

---------------------------------------------------------------------------------------------------------------------


int main()
{
	map<string, string> mymap;
	// ..

	for(const auto&[name,surname] : mymap)
	{
	/// .. map böyle dolaşılabilir.
	}

}

Bunlar C++ 17 ile geldi.

--------------------------------------------------

int main()
{
	map<string, string> mymap;
	// ..

	if(auto[iter,inserted] = mymap.insert({"umut","kotankiran"}); !inserted) // IF WITH INITIALIZER + STRUCTURAL BINDING
	{																		// my map e veri eklendi.mymap structural bindine sentaksına uygun
		std::cout <<"Ekleme yapilamadi\n";									// değerleri iter, inserted a atamaya çalıştı,atayamazsa if e girdi
	}

	for(const auto&[name,surname] : mymap)
	{
	/// .. map böyle dolaşılabilir.
	}

}


*/

#include <iostream>
#include <string>
#include <conio.h>
#include <array>

struct Nec {
	int a[4];
	double dval;
};

Nec foo();

int main()
{
	using namespace std;
	
	auto [ptr, d] = foo();
	//Soru: ptr nin türü nedir? Cevap int[4] tür. 
	//auto kurallarına göre array decay oluyordu.Bu yanıltabilir

}
