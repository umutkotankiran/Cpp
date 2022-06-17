/*

C++'IN EN ZOR VE EN ÖNEMLİ KISMI GENERIC PROGRAMLAMA PARADIGMASI VE TEMPLATELER
-------------------------------------------------------------------------------

Auto deduction ile template deduction neredeyse aynı.
Bunları konuştuk.

Buradaki ambigiuty sorunlarına dikkat etmemiz gerekiyor.

template <typename T>
void func(T x, T &&y);

Burada tür çıkarımı yaparken, tüm argümanlar için T çıkarımı aynı olmalı.

int main()
{
	int x = 10;

	func(x,x); // Biri int diğeri ise int& olduğundan SENTAKS HATASI.
	func(x,+x); // İkiside int. GEÇERLİ.
}

--------------------------------------------------------------------------------

Telegramdan Sorulan Bir sorudan devam ediliyor.

class Person{

};

int foo();
Person func();

int main()
{
	foo() = 10; // BU LEGAL DEĞİL AMA 
	
	Person per;
	func() = per; // BURASI LEGAL
}

NEDEN LEGAL?

foo() ifadesi sağ taraf değeri dolayısı ile atama yapmak sentaks hatası.
func() Neden legal? Mülakat sorusu.

Burada fundemental type ile class type lar arasında fark var. Bir func ın return değeri referans değilse
bu ifade tabiki sağ taraf değeri. Aynı durum func() içinde geçerli. 

AMA !!! Burada çağrılan bir func var. bu func sınıfın copy assignment functionı.

func()=per ile func().operator=(per); arasında bir fark yok. func ın return değeri Person türünden Dikkat et buna.
func() ın return değeri sağ taraf değeri olmasına rağmen ben bunun için copy assingment func ını çağırabilirim, bu normal durum aslında.


struct A{
	void func();
};

int main()
{
	A ax;

	ax.func(); // LEGAL

	A{}.func(); // LEGAL 
}

Atama operator func ta buradaki func gibi. Bunu hem lvalue ex hemde rvalue expr ile çağırabiliriz.

-----------------

ÖNEMLİ !!!!!!!!!!

Öyle bir function istiyorum ki bu sağ taraf değerleri için çağrılamasın.
Yada sadece sağ taraf değeri olan sınıf nesneleri için çağrılabilsin

Bunu Referans Niteleyici/Qualifier ile yapıyoruz.

struct A{
	void func();  // 1.     // Hem sol hemde sağ taraf değeri olan sınıf nesneleri için çağrılabilir demek
	void func()&; // 2.     // Sadece sol taraf değeri olan sınıf nesneleri için çağrılabilir demek.
	void func()&&;// 3.     // Sadece sağ taraf değeri olan sınıf nesneleri için çağrılabilir demek.

 };

int main()
{
	A ax;

	ax.func(); // 1. VE 2. DURUMLARDA GEÇERLİ

	A{}.func(); // 1. VE 3. DURUMLARDA GEÇERLİ
}

---------------------------

AYNI DURUM COPY ASSIGNMENT İÇİNDE GEÇERLİ !!!

struct A{
	A& operator=(const A&);
};

A foo(); // func decleration
int main()
{
	A ax;
	foo() = ax; // Bu durumda geçerli
}

--------------------------------------------------------------------------

struct A{
	A& operator=(const A&)&; // Dikkat 
};

A foo(); // func decleration
int main()
{
	A ax;
	A ay;
	
	ax = ay; // GEÇERLİ

	foo() = ax; // GEÇERSİZ.
}				// Copy assignment sağ taraf değerleri için çağrılamaz.

--------------------------------------------------------------------------

REFERENCE QUALIFIER İLE OVERLOADING TE YAPILIR

struct A{
	void foo()&;		// Sol taraf değeri olan sınıf nesneleri için
	void foo()const &;  // Const Sol taraf değeri olan sınıf nesneleri için
	void foo()&&;		// Sağ taraf değeri olan sınıf nesneleri için
	void foo()const &&; // Const Sağ taraf değeri olan sınıf nesneleri için
};

--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------

Argument Deduction Konusundaki İstisnaya bakalım

template <typename T>
void foo(T x);

int main()
{
	auto x = expr;
	foo(expr) ; Buradaki tür çıkarımları aynı.
}


---------------------------------

BIR DEĞIŞIKLIK VAR. BUNA BAKALIM.

#include <initializer_list>

template <typename T>
void f(T);

int main()
{
	auto x = {1, 2, 3, 4};  // Burada çıkarım initializer list in int açılımı olarak yapılır.

	Kurallar aynı olsaydı.
	f({1,2,3,4}); //Burada da argument deduction başarılı olacaktı ve f parametresi olan t nin initializer list in int
					// açılımı olması gerekecekti. AMA DEĞİL. SENTAKS HATASI
}

-----------------------------------

Bu tüm senaryolarda geçerli.
#include <initializer_list>

template <typename T>
void f(T&&x);

int main()
{
	foo(13); // T nin çıkarımı burada int 
	auto &&x = 13; // Burada da auto karşılığı int
}

------------------------------------

template <typename T>
void f(T&&x);

int main()
{
	int y = 5;
	auto &&x = y; // int & && -> int & oldu artık burası	
}


----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------

BIR TEMPLATE YAZILIRKEN, DERLEYICI KODU YAZARKEN BAŞKA BIR TEMPLATE IN KODUNU YAZMAK ZORUNDA KALABILIR
------------------------------------------------------------------------------------------------------

template <typename T>
void f2(T &&x)
{
	
}

template <typename T>
void f1(T y)
{
	//
	f2(y + 5);
}

template <typename T>
void foo(T x)
{
	//
	f1(x);
}

int main()
{
	foo(12);
}

Açıklama
--------
- foo(12) den derleyici T nin çıkarımını int olarak yaptı.
- bu durumda func parametre değişkeninin türü de int oldu.
- f1(x) çağrısı yapıldığında, derleyici f1 inde bir func şablonu olduğunu gördü ve çıkarımı int olarak yaptı.
- f2(y+5) işleminde, f2 arandı ve bunun bir func şablonu olduğunu gördü, argüman olan ifadeden bir sağ taraf değeri olduğundan
  T türünün çıkarımını int olarak yaptı.Burada f2 nin parametresi bir sağ taraf referansı oldu.


--------------------------------------------------------------------------------------------------------------------------


ÇOK TİPİK YAPILAN BİR HATA
--------------------------

void func(int &&r)
{
	r -> Bu ifade bir Rvalue expr DEĞİL. Bu Lvalue expression ve Rvalue reference.
}

---------------------------------------------

ör:
void foo(int &)
{
	std::cout << "int &";
}

void foo(int &&)
{
	std::cout << "int &&";
}

void func(int&& r)
{
	foo(r);
}

int main()
{
	func(12); // int & yazar çıktıya.
}

Bunlar ilk derslerde görülmüştü zaten.

Template ler başka bir template in açılmasını sağlayabilir.

------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------

ŞIMDI SWAP TEMPLATE INI DÜŞÜNELIM.

template <typename T>
void Swap(T &x, T &y)
{
	T temp = x;
	x = y;
	y = temp;
}

Bu şekilde yapılırsa
copy ctor
copy assingment
copy assingment çağrılır sırasıyla
Yani gereksiz bir kopyalama oluşur.


Ama bu sefer swap functionunu aşağıdaki şekilde çağrıldığını düşünelim.
template <typename T>
void Swap(T &x, T &y)
{
	T temp = std::move(x);
	x = std::move(y);
	y = std::move(temp);
}

Artık taşıma ile işlemleri yapmış oluyoruz.Eski C++ ile Modern C++ arasındaki farklılıklardan biri.
Modern implementasyon bu. Taşıma çok daha verimli oluyor.

-------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------

Function template lerle ilgili bizi ilgilendiren çok önemli bir yapı var.
STL de Algorithm denilen STD func şablonlarını öğrenince burası çok önemli olacak.

template <typename T>
void func(T x)
{
	//
	x();  
}

int main()
{

}

SORU:
Bu template ten derleyicinin yazacağı kodun geçerli olabilmesi için T nin hangi türler olma ihtimali var ?
1. Cevap, T türünün bir function pointer olması olabilir.
2. Functor objesi olabilir.
3. Lambda Expression olabilir.

-----------------------------------------------

1. Function Pointer Durumu
--------------------------

template <typename T>
void func(T x)
{
	//
	x();
}

void foo()
{
	std::cout << "foo()\n";
}

int main()
{
	func(foo);
}


Derleyicinin yazdığı func aşağıdaki gibi olacak
void func(void(*x)())
{
	x();
}

Çıktı
-----
foo()

-----------------------------------------------

2. Functor Durumu
-----------------

template <typename T>
void func(T x)
{
	//
	x();
}

class Functor{ // ismi functor ama başka birşeyde olabilirdi.
public:
	void operator()()
	{
		std::cout << "Functor::operator()()\n";
	}
};

int main()
{
	Functor f;

	func(f);
}

Burada callable bir tür gönderildiğinde, yani function çağrı operatörünün operandı olabilen türden bir nesne ise o zaman
X bir callable nesne oluyor.

Biz callable olarak
a - functionları
b - function pointerları
c - Functor sınıfları
d - İlerleyen zamanlarda da lambda ifadeleri kullanılacak.


Kısaca lambda ifadesi yazalım
func( []{std::cout << "neco";} ) 

Burada func içerisindeki bu ifadeye lambda expression deniyor.
Lambda expressionlar görülecek ileride

---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------

1 - Function Şablonları ile Gerçek funclar birbirini overload edebilir.
2 - Function Şablonları ile yine Function şablonları birbirini overload edebilir.

template <typename T>
void func(T x);

void func(int); //Bunlar overloadlar Sentaks hatası yok.

Burada Overloading Resolution Nasıl yapılıyor buna bakalım
----------------------------------------------------------

template <typename T>
void func(T x)
{
	std::cout <<"function template type is " << typeid(T).name() << "\n";
}

void func(int)
{
	std::cout << "Gercek Function\n";
}

int main()
{
	double dval{};

	func(dval);
}

Burada önce overload tek aday değilse önce derleyici func şablonuna gelince template
argument deduction yaparak bir imza elde ediyor. T türü burada double. O zaman func
overload resolutiona aday olacak function bu func şablonundan yazılacak olan void func(double) olacak.
Alttaki func ise int parametreli

Overload resolutionda 2 aday var.Burada double parametreli seçileceği için şablondan bir function yazacak.

Derleyip çalıştırınca 
function template type is double   yazar.

------------------------------

Float gönderseydim bu sefer templatten float parametreli function yazacak.

------------------------------

Gönderdiğimiz argüman int olursa gerçek function seçilecek

int main()
{
	func(24); // Burada derleyici int parametreli bir funcion yazmaz.Varolan gerçek func ı kullanır.
}

------------------------------

Char argümanla çağırsaydık, promotion olmayacaktı. Doğrudan türe bakılır, func şablonundan
char parametreli function yazacaktı derleyici.

-------------------------------------------------------------------------

KURAL : Gerçek function ın, function overload resolutionda üstünlüğü var.

-------------------------------------------------------------------------

Mülakat sorusu

Öyle bir func oluşturunki, function sadece int argümanla çağrılabilsin
Bunun dışındaki herşey sentaks hatası olsun.

template <typename T>
void func(T) = delete;

void func(int);

int main()
{
	func('A');
	func(2.3);
	func(2U);
	func(2); // Birtek bu geçerli.
}

-------------------------------------------------------------------------

AYNI ISIMLI BIRDEN FAZLA FUNCTION ŞABLONU OLABILIR MI? EVET

template<typename T> // bu başka bir overload
void func(T x)
{
}

template<typename T> // bu da başka bir overload
void func(T x, T y)
{
}

int main()
{
	func(12);		// üstteki şablondan func yazılacak
	func(1, 2);		// alttaki şablondan func yazılacak.
}

--------------------------------------------------------

template<typename T, typename U> // yine bu bir overload
void func(T x, U y)
{
}

template<typename T> // buda başka bir overload
void func(T x, T y)
{
}

int main()
{

}

============================================================================================================================
============================================================================================================================
============================================================================================================================


DİLİN KURALLARININ EN KARMAŞIK OLDUĞU YER BURASI. COMPİLERLAR BİLE DÜZGÜN İMPLEMENTE EDEMEMİŞ OLABİLİYORLAR.
------------------------------------------------------------------------------------------------------------

template <typename T>
void func(T x)
{
	std::cout << "1";
}

template <typename T>
void func(T *x)
{
	std::cout << "2";
}

int main()
{
	func(12); // Bu çağrıda üstteki viable ve üstteki template ten kod üretilir.12 Adres değil çünkü.

	int x{};
	func(&x); // burada üstteki template ten T nin çıkarımı int *, alttaki template ten int olurdu. İkiside legal
			  // Bu durumda uygulanan kurallara PARTIAL ORDERING RULES deniyor.Bunlar biraz karmaşık.
}

Çok detaya girmeden pratik cevap
- Function parametresi daha spesifik olan seçilecek.
Yukarıda bir func T türünden diğeri T* türünden.
T* daha spesifik. Bu sebeple T* olan seçilecek.

çalıştırırsak func(&x) olanı "2" çıktısını verir. 


---------------------------------------------------------

Daha spesifikten kasıt için bir örnek daha.

template <typename T>
void func(T x)
{
	std::cout << "1";
}

template <typename T>
void func(T *x)
{
	std::cout << "2";
}

template <typename T>
void func(T **x)
{
	std::cout << "3";
}

int main()
{
	int x{};
	int *p{&x};

	func(**p);

}

Burada 3 template te legal.Ama en fazla niteleyiciyi içeren hangisiyle o seçilecek.
T** en fazla niteleyiciyi içeren yani en spesifik bu sebeple o seçilecek.
"3" yazacak.

------------------------------------------------------------------------------------------------------------

DİLİN GERÇEK KURALI AŞAĞIDAKİ GİBİ.DAHA DETAYLI OLAN. PARTIAL ORDERING RULES

Derleyici şablonlardan biri için bir tür alıyor.Mesela T nin türü int olsun.veya myclass ta olur.
bu durumda bu türü aldığımızda func(int x) çıkacak.(1. func üzerinden gidiyoruz şuanda)

2. func için yine bir unique tür alalım.Bu durumda da T nin türü char olsun. Parametre char * olması gerekti.

1 - func(int x);
2 - func(char *c);

Burada kural diyorki, buradaki char * türünü(2. func parametre) template argüman olarak kullanınca
(1.ci functaki void func(T x)) T için çıkarımı yapılabiliyor mu? Ever burada T char * olarak çıkarılabilir.

Diğer durumda,
func(int x) buradaki parametrenin, void func(T *x) için tür çıkarımı yapılmaya çalışılsa herhangibir şekilde
tür çıkarımı legal olmayacak. 

BURADA DAHA SPESİFİK OLAN TÜR HATA VERDİ. SPESİFİK OLAN TÜR SEÇİLİR


---------------------------------------------------

template <typename T>
void func(T&);

template <typename T>
void func(T(&)[5]);

int main()
{
	int a[5]{};

	//func(a); // Bu her iki template tende çağrılabilir. Daha spesifik olan seçilecek yani ikincisi T(&)[5] parametreli seçilir.
}

Bir soru üzerine uzun açıklama yine anlatıldı ama ben yazmıyorum.

-------------------------------------------------------------------------------------------

FUNCTION ŞABLONLARINDA ŞABLON ARGÜMANI EXPLICIT OLARAK FUNCTION ÇAĞRISINDA BELIRTILEBILIYOR

template <typename T>
void func(T x)
{
	
}

int main()
{
	func(12); // burada deduction yapılır

	func<double>(12); // burada deduction yok. Türü biz veriyoruz. T nin double olmasını istiyoruz demiş oluyoruz
}

--------------------------------------------


template <typename T,typename U>
void func(T x, U y)
{

}

int main()
{

	func<double>(12,5); // T türü double, U türü deductiondan int olarak çıkarılır.
	func<double,int>(12,5); // T türü double, U türü int olarak programcı tarafından verilmiş.
}

---------------------------------------------


#include <memory>

int main()
{
	std::make_unique<int>(23); // mesela make unique isimli func şablonunda birinci template tür parametresininin çıkarımı yapılamıyor.
}								// Açıkça yazmak gerekiyor

----------------------------------------------

TÜR ÇIKARIMI YAPILAMAYAN BIR DURUM OLABILIR.

template <typename T>
T func(int x); //bu şekilde yazarsak argümanı açıkça belirtmek gerelir. Tür çıkarımı yapılamaz burada.

int main()
{
	
}

----------------------------------------------

FUNCTION TEMPLATELERDE NONTYPE PARAMETER KULLANIMI

template <typename T, int x>
void func(T(&r)[x])
{
	std::cout << "size = " << x << "\n";
}


int main()
{
	double d[15] = { 0 };
	func(d);

}

----------------------------------------------
YUKARIDAKİNDEN DAHA BASİT BİR NONTYPE ÖRNEĞİ

template <typename T, int a>
void func(T x)
{
	std::cout << typeid(T).name() << "\n";
	std::cout << a;
}

int main()
{
	func<int,5>(39); // 5 yazar
}

----------------------------------------------

template <typename T>
void func(T x, int a)
{
	std::cout << a ;
}


int main()
{
	func(10,5); // 5 İ YAZAR.
}

----------------------------------------------


int main()
{
	usint mytype = int&&;
	mytype &&x = 10;
}

Burada int&& &&x durumu oluşur buda reference collapsinge göre
int&&x = 10; olur en son durumda.


----------------------------------------------

int main()
{
	int y;
	usint mytype = int&;
	mytype &&x = y;
}

int & && x = y; 
int & = y;  olur en son


------------------

template <typename T>
void func(T&& x)
{

}

int main()
{
	func<int&&>(12); // T nin türünü int&& yaptık. func artık böyle yazıldı --> void func(int&& &&) --> void func(int&&)

	int i{};
	func<int&>(i); //burası da geçerli. void func(int& && x)--A> void func(int &)
}

---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------

TİPİK YANLIŞ ANLAŞILMA

template <typename T>
void func(T x)
{
	std::cout << typeid(T).name() << "\n";	
}

int main()
{
	func(1.2);
	func(1.2f);
	func(1u);
	func(1);
	func('A');
	func(true);
}

BURADA DOUBLE YAZDI DİYE BİRSONRAKİ FLOAT PROMOTE OLUP DOUBLE PARAMETRESİYLE ÇAĞRILMAYACAK.
HEPSİ AYRI AYRI YAZILACAK.

ÇIKTI
-----
double
float
unsigned int
int
char
bool




AMA !!!
AŞAĞIDAKI GIBI ÇAĞRILSAYDI DURUM FARKLI OLURDU

int main()
{
	func(1.2);
	func<double>(1.2f); // buralarda double argüman gönderilmiş ve aşağıdakilerde aynı. Buralarda double parametreli func çağrılır.
	func<double>(1u);
	func<double>(1);
	func<double>('A');
	func<double>(true);
}

-------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------

DIYELIMKI 2 SAYININ TOPLAMINI YAZDIRAN BIR FUNC TEMPLATE YAZACAĞIZ

template<typename T>
T sum(T x, T y)
{
	return x + y;
}

int main()
{
	auto x = sum(12,45);   // T değeri int
	auto x = sum(1.2,4.5); // T değeri double
	string s1{"veli"},s2{"ali"};
	auto z = sum(s1,s2); // T burada string

	auto x = sum(4, 4.5); //BURASI SENTAKS HATASI.
}



Farklı 2 türden değerin toplanması nasıl olabilir. Nasıl Bir template oluşturmak gerekir?

template<typename T, typename U>
T sum(T x, U y)
{
	return x + y;
}

int main()
{
	auto z = sum(3, 3.4); //Z nin türü burada return değeri T olduğundan ve o da INT olarak çıkarım yapıldığından İNT olur.
							// değer 6 çıkar. Veri kaybı oluşur.
}

-------------------------------------------------------------------

Template return değerini U yapsak yukarıdaki örnek için olur ama elemanlar yer değiştirirse yine veri kaybı oluşur
ÖR:
template<typename T, typename U>
U sum(T x, U y)
{
	return x + y;
}

int main()
{
	auto z = sum(3, 3.4); // return değeri U template parametresi. O da double olarak çıkarılır. Bu örnek düzgün çalışır ama

	auto z = sum(3.4, 3); // Bu seferde burada veri kaybı var. 6.4 değil 6 yazar.
}

-------------------------------------------------------------------

Burada 3. bir tür seçilir.Bu return değeri programcı explicit olarak yazar.

template<typename Result,typename T, typename U>
Result sum(T x, U y)
{
	return x + y;
}

int main()
{
	auto y = sum<double>(3.4,2); //	 bu şekilde result türünü belirtebiliriz.
}

Tek yol bu değil.

-------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------


TEMPLATES VE AUTO RETURN TYPE  
BIR DIĞER ARAÇ TRAILING RETURN TYPE
-----------------------------------

TRAILING RETURN TYPE TAN BAŞLAYALIM
Gerçek funclarda trailing return type kullanmanın çok bir önemi yok.

auto main()-> int  gibi kullananlar var.Burada hiç gerek yok.
{ 

}

auto foo() -> int (*)(int)  gibi bir durumda ise gerek olabilir.
{

}

-------------------------------------------

Templatelere geri dönersek.
Biz burada geri dönüş türünün x + y nin türü olmasını istiyoruz.


template <typename T,typename U>
decltype(x+y) sum(T x, U y)  // BURADA HATA VAR. Func parametre isimleri x ve y decltype kısmında kullanılamaz.
{								//  x ve y nin scope u orası değil.
	
}

Aşağıdaki gibi yazılabilir.
template <typename T,typename U>
auto sum(T u, U y) -> decltype(x+y) // ARTIK LEGAL
{
	
}

-------------------------------------------------------

DİĞER İMKAN AUTO RETURN TYPE. C++14 ile geldi

Hem gerçek func lar hemde func şablonları için kullanılabiliyor.

auto (int x, double y)
{
	return x * y -1;
}

Template larda çok kullanılıyor. Template olmayan yapılarda çok kullanılmıyor.

-------------------------------------------------------

Templateler için tür çıkarımı yapılır.Yoğun olarakta kullanılacak.


template <typename T,typename U>
auto foo(T x, U y)
{
	return x * y;  
}


Return değeri auto&& olabilir.Neden auto && biçiminde yazılır 
Perfect forwardingte göreceğiz.

-------------------------------------------------------

BIRDE DECLTYPE(AUTO) VAR.

Burada func return değeri türü çıkarımında decyltype
kuralları uygulanacak demek.

template <typename T>
auto &func(T &x)
{
	return x;
}

int main()
{
	int x = 10;
	auto i = func(x); // bu bildiğimiz auto örneği.
}


------------------------------------------------------------

template <typename T>
decltype(auto) foo(T x)
{
	return (x);   // decltype kurallarına göre tür çıkarımı yapılırsa decyltype((x)); int& çıkar	
}

===================================================================================================
===================================================================================================
Decltype kurallarını ben 4. derste yazmıştım. Tekrar yazayım.
1 - İsim formunda ise
Bu isim hangi türden declere edildiyse bizim elde ettiğimizde o tür

2 - İsim formunda ifade değilse
Bu durumda decltype karşılığı elde edilen tür parantez içindeki ifadenin value kategorisine bağlı.
a - eğer ifade pr value expr ise, decltype yerine gelen tür 	T türü
b - eğer ifade L value exp.ise decltype yerine geşen tür 	T & türü
c - eğer ifade X value exp.ise decltype yerine geşen tür 	T && türü
===================================================================================================
===================================================================================================

------------------------------------------------------------


DECLTYPE AUTO YA GERI DÖNELIM.

template <typename T>
decltype(auto) foo(T x)
{
	return (x);   // decltype kurallarına göre tür çıkarımı yapılırsa decltype((x)); int& çıkar

	int *ptr;
	return *ptr; // burada ise decltype(*ptr); int& çıkar türü.
}

int main()
{
	foo(12);	
}

SONUÇ : AUTO VARSA RETURN TÜR ÇIKARIMI AUTO YA GÖRE DECLTYPE(AUTO) VARSA DECLTYPE AUTOYA GÖRE YAPILIR !!!!

auto func()
{
	const int x = 10;
	return x;  // burada bunun çıkarımı auto ya göre INT olur
}
//main

decyltype(auto) func()
{
	const int x = 10;
	return x;  // Budrada ise decyltype(auto) ya göre CONST INT olur.
}
//main


MOLA

===============================================================================================================================================
===============================================================================================================================================
===============================================================================================================================================

template <typename T>
void Swap(T &x, T &y)
{
}
Sadece swap için değil dizi reverse içinde yazabiliriz.

template <typename Iter>
void Reverse(Iter &x, Iter &y)
{
	... yazılır kodu.cppreferenste zaten hazır kütüphanenin koduna bakılabilir.
}

STL de bunlar hazır zaten.

----------------------------------------------------------------------------------

Bir Örnek

#include <iostream>
#include <algorithm>
#include <vector>

template <typename Iter>
void print(Iter beg, Iter end) 
{
	while(beg != end)
		std::cout << *beg++ <<" ";

	std::cout << "\n";		
}
int main()
{
	int a[] = {1,5,6,4,3,7,9,4,3};

	sort(begin(a),end(a)); //algoritma header file da var sort. iter int* a denk geldi.

	sort(a, a + sizeof(a) / sizeof(*a)); //aynı şekilde begin ve ende karşılık geldi. C style yazdık

	print(a, a + sizeof(a) / sizeof(*a)); 
}

Burada sadece dizi değil, vector bağlı liste verilerinide yazdırabiliriz.

int main()
{
	vector<int>a = {1,2,5,6,3,4,5,7,8};

	sort(begin(a), end(a));  // bu seferde vector için sıralama
	
	print(begin(a), end(a)); // vector için yazdırdık.

}

----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------

TYPENAME YERINE CLASS TA KULLANILABILIR.AMA TYPENAME IN KULANILDIĞI ÖYLE BIR YER VARKI CLASS KEYWORD BURADA KULLANILAMIYOR
--------------------------------------------------------------------------------------------------------------------------

template <typename T>
int func(T x, int y)
{
	typename T::Nec;
}

ÇOK ÖNEMLİ !!!!!!!!!!!!!!
Diyelim ki T ye bağlı bir nested type oluşturmak istiyoruz.Normalde T::Nec a; gibi yazılabiliyordu
BU şekilde yazdığımızda dilin kurallarına göre burada öncelik bunun bir nested type olması yönünde değil,
bunun sınıfın static bir veri elemanı olması yönünde. DOlayısıyle dilin kurallarının çözünürlük operatörünün
sağ tarafında(Eğer sol tarafı bir template parametresi ise) ki ismin bir tür ismi olarak alınmasını istersek
burada typename keyword ünü kullanmak zorundayız.



Yani T türünün bir nested type olan Nec i bir tür  bilgisi olarak kullanacaksak başına typename koyacağız. 
Aşağıdaki gibi olacak

template <typename T> // buradaki typename yerine class gelebilir
typename T::value_type func(T x, int y)
{
	typename T::Nec; // Buradaki typename yerine class keyword gelemez.
}

Eğer template tür parametresine bağlı bir türden bahsediyorsak, bunu çözünürlük operatörü ile niteliyorsak, bunun bir tür bilgisi olduğunu
başka bir anlamda ele alınmaması gerektiğini belirtmek için typename keyword kullanmak zorunlu.


------------------------------------------------------------------------------------------------

ÖR:
template <typename T> // buradaki typename yerine class gelebilir
typename T::value_type func(T x)

int main()
{
	func(12); //  SENTAKS HATASI. Burada T in türü. int in nested type ı olarak belirtilmiş 
				// ama böyle bir tür yok.Olamaz çünkü int primitive tür.class değil. 
}

------------------------------------------------------------------------------------------------

ÖR:
template <typename T> 
typename T::value_type func(T x);

class Myclass{
public:
	typedef int value_type;
};

int main()
{
	Myclass mx; 

	func(mx); // GEÇERLI çünkü Myclass ın value_type isimli türü var 


============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================

SUBSTITUTION İŞLEMİ
-------------------

OVERLOAD RESOLUTIONA KATILACAK FUNCTIONUN IMZASININ, PARAMETRIK YAPISININ ANLAŞILMASI AŞAMASINA DENİYOR.

1.Argument Deduction
2.Substitution 

template <typename T>
T func(T x);

void func(double);

int main()
{
	func(12);	
}

Burada func(12); çağrıldığında int func(int) olacak ve overload resolution a katılacak function bu function.

------------------------------------------------------------------------------------------------

BURAYA DİKKAT !!!!

template <typename T>
typename T::Nec func(T x);

void func(double);

int main()
{
	func(12); //SENTAKS HATASI YOK. NEDENİ AŞAĞIDA YAZILDI
}

Burada dilin en önemli kurallarından biri var.Bir acronim ile ifade ediliyor bu. 
SFINAE !!!!!!!!!!!!!!!!!!!!!!!
SUBSTITUTION FAILURE IS NOT AN ERROR !!!!!!!!!!!!

Bu kural karmaşık gelebilir.

EĞER BIR TEMPLATE TE SUBSTITUTION AŞAMASINDA YANI OVERLOAD RESOLUTIONA KATILACAK 
FUNCTIONUN IMZASININ, PARAMETRIK YAPISININ ANLAŞILMASI AŞAMASINDA BIR SENTAKS HATASI OLUŞURSA,
BU BIR SENTAKS HATASI OLARAK KABUL EDİLMEZ, SADECE OVERLOAD RESOLUTİONDAN ÇIKARTILIR.
BUNA SFINAE OUTTA DENİYOR

Yukarıdaki örnekte T türü int. İnt in Nec diye bir türü olmadığından substitution hatası oluşacak
ama sentaks hatası olması yerine bu func ın overload setten çıkartılmasını sağlayacak.

İlk örnekte bu function tek başına olduğu için, başkada func kalmadığı için sentaks hatası olmuştu :D
Bu örnekte double parametreli function overload resolutionda kalacak.

------------------------------------------------------------------------------------------------

ÖR:

template <typename T>
void func(T x, typename T::Nec *y = nullptr);

int main()
{
	func(12); // aynı şekilde int in Nec türü olmadığından, Bu overload setten çıkarılır.
}				// Varsa başka bir func çağrılır, Yoksa SENTAKS HATASI.SFINAE

-----------------------------------------------------------------------------------------

template <typename T, typename U = typename T::Nec>  // bu şekilde de kullanılabilir.
void func(T x, U y);

-----------------------------------------------------------------------------------------

SFINAE, bir function şablonunun belirli türler için kullanımını devre dışı bırakmak için
kullanılan bir teknik aynı zamanda.

SFINAE yi destekleyecek enable_if isimli template var.
Bunlar ilerleyen derslerde görülecek ama daha çok İleri C++ konusu.

Belirli func şablonları için belirli türleri o func veya sınıf şablonunda kullanılmasını 
engellemeye yönelik bir araç

C++ 20 de Concept dile eklendi. En önemli araçlardan birisi Concept.

Template tür parametresine bağlı bir türden bahsediyorsak typename keywordü kullanmak zorunlu
yoksa sentaks hatası olabilir ve typename yerine burada class keyword kullanılamaz.

-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------

STL E GIRDIĞIMIZDE ALGORITHM DENEN FUNCTION ŞABLONLARINI GÖRECEĞIZ.
Bunlar veriyapıları üzerinde çalıştırılacak algoritmaların kodlarının yazılması için kullanılan function şablonları.

STD C++ library deki en önemli öğelerinden biri bu algoritmalar.
Bunların çoğunu göreceğiz.STL de bu hep karşımıza çıkacak.

STL in en önemli bileşenleri
Containers   (class templates)
Iterators	 (class templates)	
Algorithms	 (function templates)

-----------------------------------------------------------------------------------------------------------------------------------

BIR SINIFIN BIR ÜYE FONKSIYONUDA FUNC ŞABLONU OLABILIR.

class Myclass{
public:
	template <typename T>
	void func(T x);
};


int main()
{
	Myclass mx;

	mx.func(10);  // compiler burada int parametreli bir func yazacak
	mx.func(10.4);  // compiler burada double parametreli bir func yazacak
	mx.func("ali");  // compiler burada string parametreli bir func yazacak
}

Myclass sınıf şablonu değil ama myclass ın func isimli functionu bir function şablonu.
Myclass tan bir nesne tanımladığımda, func isimli functionu bir argümanla çağırınca derleyici sınıfa bu parametreli bir func functionu yazacak.
başka argüman verirsek başpa bir parametreli function yazacak.

-----------------------------------------------------------------------------------------------------------------------------------

BU CTORDA OLABİLİR

class Myclass{
public:
	template <typename T>
	Myclass(T x);
};

int main()
{
	Myclass mx{13}; //Derleyici burada int parametreli bir ctor yazacak.
	Myclass mx{1.3}; //Derleyici burada double parametreli bir ctor yazacak.
}

Böyle templatelere member template deniyor. 

Bir şablondan derleyicinin gerçek kodu yazmasına derleyicinin o şablonunu instantiate etmesi deniyor. Oluşturulan fonksiyona template specialization deniyor


==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================



CLASS TEMPLATES / SINIF ŞABLONLARI
----------------------------------
Burada oluşturacağımız şablondan hareketle amaç derleyiciye bir sınıfın kodunu yazdırmak.
Yine bir metacode var ama bu sefer sınıf kodu yazdırmak için var.Func kodu için değil. Func şablonlarına benziyor. template keyword zorunlu.

Sentaks
-------
template <typename T>
class Myclass{

};

YUKARIDAKI BIR SINIF DEĞIL. BIR SINIF ŞABLONU!!!!!!!!!!!!!!
Compiler bunu kullanarak bize sonsuz sayıda sınıf yazabilir. T int olursa ayrı, double olursa ayrı bir sınıf.

Sınıf ise aşağıdaki
Myclass<int>    İşte bunların herbiri bir specialization.
Myclass<double>   bu ise başka bir sınıf. T için her argüman farklı sınıf kodu demek.

------------------------------------------------------------------------------------------------------------------------------

T yi func şablonlarında kendimiz yazabilirdik veya deduction ile belli oluyordu.
Sınıf şablonlarında C++17 ye kadar deduction mekanizması yoktu.C++17 de geldi bu özellik.
Sınırlı bir contex te mümkün. Bu konuya ilişkin kural setine CTAD deniyor.
CLASS TEMPLATE ARGUMENT DEDUCTION demek. C++ 2017 de geldi.

int main()
{
	Myclass<int> x;
	Myclass<double> y;   // x ile y farklı sınıflar
	
	x = y; // bu atama yapılamaz çünkü aynı sınıf türünden değil.
}

------------------------------------------------------------------------------------------------------------------------------

SENTAKSA BAKALIM
----------------

template <typename T>
class Myclass{
public:
	T f(T x); //  T int ise int f(int x );		data olsaydı data atüründen olacaktı ...
	int foo(const T&); // burada da türe göre yazılır.
private:
	T mx;
};

Template parametreleri sınıf kodu içinde heryerde kullanılabilir. public private... 


----------------------------------------------------------------------------------------------------------------

EĞER SINIFI SINIF ŞABLONU BIÇIMINDE YAZARSAK
--------------------------------------------

NOT : SINIFIN ÜYE FONKSIYONLARI ÇAĞRILMADIĞI SÜRECE YAZILMAYACAK !!!!!!!!!!!!

template <typename T>
class Myclass{
public:
	T f(T x); 
	int foo(T x);
	T f();

private:
	T mx;
};

int main()
{
	Myclass <int> mx;  // şuanda foo func veya f kodu yazılmayacak

	mx.foo(); // Artık burada foo functionu yazılacak.Çünkü çağrılmış.
}

---------------------------------------------------------------------------------------------

Bu string için çok önemli çünkü birsürü functionu var.

int main()
{
	string str{"Ali"}; // Burada sadece Ctor ve Dtor yazıldı çağrıldı.
}						// Çünkü çağrıldıklarında yazılıyorlardı.


================================================================================================================================================
================================================================================================================================================
================================================================================================================================================

MEMBER FUNCTION SENTAKSI
------------------------
Member functionların belirli bir sentaksi var

1. SINIF ŞABLONUNUN MEMBER FUNCLARINI DOĞRUDAN SINIF TANIMI IÇINDE INLINE OLARAK YAZABILIRIZ.
---------------------------------------------------------------------------------------------

template <typename T>
class Myclass{
public:
	void func();
	
	T foo(T x)
	{
		x.func();
		return x;
	}

private:
	T mx;
};


2. SINIFIN DIŞINDA BU FUNC IN TANIMINI YAZABILIR.
-------------------------------------------------
Bu Cpp de yazabiliriz demek değil çünkü derleyicinin kodu yazabilmesi için kodu görmesi lazım. 
Her durumda bunların tanımını derleyici görmeli yoksa yazamaz. Yine Header file içinde sınıf dışında yazılabilir.

//.h
template <typename T>
class Myclass{
public:
	void func();
	
	T foo(T x);
	
	T f1(T x);
	T f2(T x);
	T f3(T x, T y);
private:
	T mx;
};

template<typename T>   // buradan başlıyor tanım
T Myclass<T>::foo(T x)
{
	//...
}

template<typename U>    // her bir tanımda burası yazılacak.Ayrıca Burada U gibi farklı bir isimde kullanabilirim
U Myclass<U>::f1(U x)		// Aynı olacak diye birşey yok ama programcılar aynı ismi kullanıyorlar.
{
}

template<typename T>   // yine yazıldı.
T Myclass<T>::f1(T x, T y)
{
}

MOLA

=============================================================================================================================================================
=============================================================================================================================================================
=============================================================================================================================================================


DİKKAT : EĞER FUNC IÇINDE SINIFIN ISMINI DOĞRUDAN KULLANIRSAK HANGI AÇILIMSA O AÇILIMI KULLANMIŞ OLURUZ.

template <typename T>
class Myclass{
public:
	void func(T)
	{
		Myclass x; //bu olur. Buda zaten Myclass <T> demek.
		Myclass<T> x; // buda olur.İkiside aynı.
	}
};


--------------------------------------------------------------------------------------------------------------------

FUNC TANIMINI SINIF DIŞINDA YAZINCADA AYNI DURUM VAR.

template<typename U>    // her bir tanımda burası yazılacak.Ayrıca Burada U gibi farklı bir isimde kullanabilirim
U Myclass<U>::func(U x)		// Aynı olacak diye birşey yok ama programcılar aynı ismi kullanıyorlar.
{
	Myclass a; // dendiği zaman bu da Myclass<U> a; demek aslında
}

--------------------------------------------------------------------------------------------------------------------

EĞER RETURN DEĞERI SINIF TÜRÜNDENSE

template <typename T>
class Myclass{
public:
	Myclass func(T);
};

template<typename T>
Myclass<T> Myclass<T>::func(T x) // Bu şekilde yazılır. Return değerine Sadece Myclass yazarsak SENTAKS HATASI.
{
	
}

--------------------------------------------------------------------------------------------------------------------

HER AÇILIM IÇIN DERLEYICININ AYRI BIR SINIF TANIMI VAR.

template<typename T>
class Myclass{
public:
	Myclass()
	{
		std::cout << typeid(*this).name() << "\n";
	}
};

int main()
{
	Myclass<int> mx; // bu bir specialization. HErbiri tanesi böyle ifade ediliyor zaten.
	Myclass<double> my; // buda öyle
}

class Myclass<int>
class Myclass<double>

Çıktıları farklı olur çünkü farklı sınıflar. Aralarında tür dönüşümü sözkonusu değil.

my = mx; Yapılamaz yani.

Aynı durum nontype parametrelerde de var.
Myclass<3>x;
Myclass<5>y;
x == y; SENTAKS HATASI. Örneği uzun uzun yazmadım.

CONVERSION CONSTRUCTOR YAZILIRSA IŞLER DEĞIŞEBILIR !!!!!!!!!!!!! 

---------------------------------------------------------------------

Şimdi Vector e bakalım

int main()
{
	std::vector<int>x; // Bu bir sınıf. Bu durumda vector bir şablon.
	std::vector<double>y ; // bu ise ayrı bir sınıf.
}

---------------------------------------------------------------------

template <typename T>
class Myclass{

};

bool operator==(const Myclass<int>&, cosnt Myclass<int>&); // bu bir şablon değil.

template <typename T>	// Burası şablon
bool operator==(const Myclass<T> &left , cosnt Myclass<T> &right);
{
}

int main()
{
	Myclass <int>x,y;
	auto b = x == y; // yukarıda derleyici x in türüne bakacak ve Myclass<int> olduğunu anlayacak ve T nin çıkarımını int olarak yapacak
					 // T nin çıkarımı int olarak yapıldığında derleyicinin oluşturduğu func parametreleri Myclass<int> ve Myclass<int> olacak
						// double olsaydı Myclass<double> olacaktı
}


-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------

FUNCTION ŞABLONLARINDA DERLEYICI BIR ÇIKARIM YAPTIĞINDA, ÇIKARIM SONUCU FUNCTIONUN PARAMETRELERI BIR SINIF ŞABLONUNDAN ELDE EDILEN SINIF TÜRÜNDEN OLABILIR
----------------------------------------------------------------------------------------------------------------------------------------------------------
Başlık kontrol edildi :)
Güzel bir örnek

template <typename T>
class Counter {
public:
	Counter() = default;

	Counter(T val) : mval{ val } { }

	Counter& operator++()
	{
		++mval;
		return *this;
	}

	Counter& operator++(int)
	{
		Counter temp{ *this };
		++* this; //++mval ile aynı olabilir ama bu yukarıdakini çağırdı o da ++mval yaptı zaten.
		return temp;
	}

	void print()const
	{
		std::cout << "(" << mval << ")";
	}

	// İkinci ve daha mantıklı olan bu yazıldı.	Hoca get diye bir func yazdırıp oradan get etti değeri.Ben operator overloading ile devam ettim.
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const Counter<T>& c)
	{
		return os << "(" << c.mval << ")";
	}

private:
	T mval{};
};


// İlk bu yazıldı.İkincisi inline yazıldı yukarıda. Bir global inserter yazmak istesek böyle
// std::ostream& operator<<(std::ostream &os, const Counter<int>& c);

int main()
{
	Counter<int> cnt{ 12 };

	std::cout << cnt <<"\n"; //yazıncada hata olmaz inserterdan dolayı.

	++cnt;
	cnt++;

	cnt.print(); // 14 oldu bakınca
	std::cout << "\n";

	std::cout << cnt <<"\n"; //yazıncada hata olmaz inserterdan dolayı.

		// Eğer inserter funcı bir func template olarak yazmasaydık, counter<long> olduğunda sentaks hatası olurdu.
		// çünkü overload sadece int türünden olurdu.
}

ÇIKTI
-----
(12)
(14)
(14)

--------------------------------------------------------------------------------------------------------

PROGRAMCILARIN EN FAZLA KAFASININ KARIŞTIĞI YERLERDEN BIRINE BAKACAĞIZ.

vector<int> 
Bu bir sınıf, yani bir tür.
Bu türün kendisinide sınıf şablonunda argüman olarak kullanabilir miyiz? EVET

template <typename T>
class Myclass{  
};

int main()
{
	Myclass<int> x; // derleyici T yerine int koyup bir sınıf kodu yazacak.

	Myclass<vector<double>> y; // Burada da T türü yerine  std::vector<double> bu sınıf türünü alacak.
							   // yani bir sınıf şablonundan elde edilen sınıf herhangibir template de tür argümanı olarakta kullanılabilir.

	vector<vector<int>> myvec; // Burada template argüman olarak vector<int> kullanılacak.Bunu kullanarak dıştaki sınıfın/vector ün kodunu yazdı. 									
									
}

---------------

Bunu göstereceğiz şimdi

template<typename T>
struct Myclass{
	struct()
	{
		std::cout << std::typeid(*this).name()<< "\n"	
	}
};

int main()
{
	Myclass<int> x;  // struct Myclass<int> yazısı çıkar. T türü ise int

	Myclass<Myclass<int>> x;  // struct Myclass<struct Myclass<int>> yazar.

	Myclass<Myclass<Myclass<int>>> x;  // struct Myclass<struct Myclass<struct Myclass<int>>> yazar.
}

------------------------------------------------------------------------------------------------------------------

Dİyelimki vectorde Myclass ın int açılımı cinsten nesneler tutmak istiyoruz. Buda olabilir.

template <typename T>
class Myclass{   };

int main()
{
	vector<Myclass<int>>x; //MODERN C++ öncesinde <int>>x; kısmında >> olan yerde maximum munch kuralından ötürü operator right shift operator olarak alınıyordu.
}							// Artık bu düzeltildi.Önceden arada boşluk karakteri bırakarak yazılıyordu. Yani >> yerine > > yazılıyordu.


------------------------------------------------------------------------------------------------------------------

template <typename T, typename U>
class Myclass{   
};

int main()
{
	Myclass<int,int>x;
	Myclass<int,char>y;
	Myclass<char,double>z; // bunların hepsi, ayrı birer sınıf


}

ÖR:
template <typename T,int n>
class Myclass{
};

int main()
{
	Myclass<int,5> x;
	Myclass<double,6> y; //Bunlarda aynı şekilde farklı birer sınıf
}

-----------------------------------------------------------------------------------------------

Şimdi STLden örnek verilecek.
----------------------------

#include <array> //ileride görülecek
using namespace std;

template <typename T,size_t n>
struct Array{
	T a[n];
};

int main()
{
	Array<int,20> x;  // optimizasyonla inline expansion ile extra bir maliyeti olmuyor

	//Bu gerçek array sınıfı
	array<double,5>ar;
	
	ar. dersek member funclarıda görürüz.
}

-----------------------------------------------------------------------------------------------

Bitset sınıf şablonu örneği
template <size_t n>
struct Array{
	// gibi bir implementasyonu var.
};

#include <bitset>

int main()
{
	bitset<32> bs; // nontype parametre için compilerın yazdığı kodda 32 kullanılmasını istiyoruz.
}

-----------------------------------------------------------------------------------------------

Pair sınıf şablonu
Bu baya önemli. Öyle yerler varki 2 adet farklı değeri tek bir nesne gibi kullanmak istiyoruz.
int,double 
string,long

öyle bir fonksiyon istiyoruz ki bir int birde double döndürsün. Normalde 2 return olmaz 1 olur
C yi düşünelim. C de bu bir struct içerisine int ve double(ne isteniyorsa) değer olur ve bu tür döndürülür.
Ama fonksiyon bir int bir double tutacaksa başka yapı, char ve double için başka yapı. Her bir tür çifti
için ayrı bir struct.Bunu Derleyicinin yazmasını isteriz.Bunu pair sağlıyor. utility header file içinde tutuluyor

template <typename T, typename U>
struct Pair{
	T first;
	U second;
};


int main()
{
	pair<int,double>p; // first eleman int, second eleman double olacak
}


-------------------------------------------------------

Mesela bir functionun return değerini pair yapabiliriz

std::pair<int,long> foo(); // bu func bir int birde long döndürüyor
std::pair<int,std::string> func(); // bu func bir int birde string döndürüyor

-------------------------------------------------------

int main()
{
	std::pair<int,double>px;
	px.first = 23;
	px.second= 2.3;
}

BURADAKI SINIFLARIN HEPSI AYRILTILI OLARAK IŞLENECEK ZATEN


memory header file da 

std::unique_ptr<int> p;
p. funclar görülür.

-------------------------------------------------------

ÖNEMLİ ÖZELLİKLERDEN BİRİ
hem func hemde class şablonları, default template argument alabiliyor.

template <typename T = int>
class Myclass{

};

int main()
{
	Myclass<double> x; // burada tür argümanı double
	Myclass<> y; // burada tür argümanı int olacak.
}

*/

#include <iostream>
