/*

En son şablonların Default argument almasında kaldık.
Burada kullanıcı kod, T için kullanıcı arguman verirse kullanıcıdan gelen, kullanıcı argüman vermezse default argument kullanılacak

template <typename T = int>
struct Myclass{
	Myclass()
	{
		std::cout << typeid(T).name() << "\n";
	}
};

int main()
{
	Myclass<double> mx; //Burada template argument DOUBLE
	Myclass<> mx; //Burada template argument varsayılan İNT olacak
	Myclass mx; //Aynı şekilde int
}

Function varsayılan argüman kuralları gibi ya sonda olacak varsayılan argument yada sondan başlayarak başa doğru hepsi default olmalı.

----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T = int, typename U = double>
struct Myclass{
	Myclass()
	{
		std::cout << "type T is : " << typeid(T).name() << "\n";
		std::cout << "type U is : " << typeid(U).name() << "\n";
	}
};

int main()
{
	Myclass<char,char> m1; // T ve U double
	Myclass<char> mx; // T = char U = double(defaulttan geldi)
	Myclass<> mx; // ikiside default template argument ten	T = int  U = double
}

----------------------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKI LEGAL

Birinci template argümanı ne ise ikinci template parametresi için argüman belirtilmezse, default argüman olarak birinci template argümanı kullanılacak.

template <typename T, typename U = T> // NOT : Bu default function parameters konusunda görüldü. Functionlarda geçersizdi.Burada Geçerli.
struct Myclass{
	Myclass()
	{ 
		std::cout << "type T is : " << typeid(T).name() << "\n";
		std::cout << "type U is : " << typeid(U).name() << "\n";
	}
};

int main()
{
	Myclass <double> x; // ikiside double yazar
	Myclass <double,int> x; // double int yazar çünkü 2.ye argüman verildi
}

----------------------------------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ
template <typename T>
class Nec{

};

template <typename T, typename U = Nec<T>>
struct Myclass{
	Myclass()
	{
		std::cout << "type T is : " << typeid(T).name() << "\n";
		std::cout << "type U is : " << typeid(U).name() << "\n";
	}
};

int main()
{
	Myclass <double> x; 
}

Çıktı
-----
type T is : double
type U is : class Nec<double>

----------------------------------------------------------------------------------------------------------------------------------------------------

VECTÖR YAPISI 
vectörde de benzer bir durum var.

vector<double> dvec;  //bunu yazmakla aşağıdaki aslında aynı
vector<double, std::allocator<double>> dvec;    //gibi birşey yazıyor aslında

template <typename T, typename A = std::allocator<T>>
class vector{
	//..
};
int main()
{
	vector<int> vx; // Aslında biz yukarıdaki classtan sınıf yazdırıyruz.Parametresi double ve default template argument var
}

----------------------------------------------------------------------------------------------------------------------------------------------------

C++11 E KADAR DEFUALT ARGUMANT SADECE SINIF ŞABLONLARINA MAHSUSTU, FUNCTION ŞABLONLARINA MODERN C++ ILE BIRLIKTE GELDI.
Fonksiyonlarda bunun kullanımı biraz sınırlı

template <typename T, typename U = int>
void func(T x, U y)
{
	func(1,3.4);  // burada T int , U double olacak. Çünkü deduction yapılıyor burada.Aşağıda yazdım nedenini.
}

functionlarda default argument, template argument deductionu bloke etmiyor. Yine tür çıkarımı yapılıyor.

----------------------------------------------------------------------------------------------------------------------------------------------------

Bu durumda function şablonlarında varsayılan türü kullanmaya yönelik 2 temel fikir var 
1. Functionun hem parametresi varsayılan argüman alıyor, ayrıca parametre değişkeni de varsayılan argüman alıyor.

template <typename T, typename U = Myclass > // typename U = int te olabilirdi.
void func(T x, U = U{}) 
{
}

void func()
{
	func(2.3); // func ın 2. parametresine default Myclass nesnesi geçilmiş olacak
	func(2.3,Nec{}); // burada ise Nec sınıfı türden geçici nesne gönderiliyor.
}

Dikkat:
Default template argument genelde functionlarda kullanılıyor.Fucntionlarda kısıtlı biraz.
1 - Hem template kısmında default verilecek
2 - Hem function parametrelerinde default verilecek
3 - Hemde func call yaparken default olan boş bırakılacak.

Buradaki diğer durumda yukarıda yazmıştık, default template parameter olması deductionu engellemiyor.

----------------------------------------------------------------------------------------------------------------------------------------------------

BAZENDE FUNCTION ŞABLONLARINDA VARSAYILAN ARGÜMANLARIN KULLANILMA BIÇIMI KULLANICI KODUN EXPLICIT OLARAK TÜRÜ BELIRTMESI

template <typename T = int>
void func()
{
	std::cout << typeid(T).name() << "\n";
}

int main()
{
	func<double>(); // template argument double
	func<int>(); // template argument int
	func<>(); // burada int yazmasakta int
	func(); // <> yazmasakta yine bu örnek için int ama gerçek bir func varsa burada o çağrılır.
}

----------------------------------------------------------------------------------------------------------------------------------------------------

BU ÖRNEK KONUNUN ANLAŞILMASI İÇİN ÇOK ÖNEMLİ.

template<typename T, typename Iter, typename Pred = std::less<T>>
void algo(Iter beg, Iter end, Pred pred = Pred{})
{
	std::cout << typeid(beg).name() << "\n";
	std::cout << typeid(end).name() << "\n";
	std::cout << typeid(pred).name() << "\n";
}

int main()
{
	algo<int,int>(1,2);		// Burası beklediğimiz gibi çalışır. Sonuç = int int struct std::less<int>

	algo<int,int,int>(1,2); // BUrada explicit olarak int verildi son parametre. Sonuç =  int int int
	
	algo<int,int>(1,2,3);	// Burada da Type deduction yaptı compiler. Sonuç = int int int
}

----------------------------------------------------------------------------------------------------------------------------------------------------

uniform_int_distribution da aynı şekilde yukarıdakine benzer. 

----------------------------------------------------------------------------------------------------------------------------------------------------

VARSAYILAN ARGÜMAN TEMPLATE NONTYPE PARAMETRE IÇINDE OLABILIR.

template <int n = 20, int m = 40>
class Neco{
};

int main()
{
	Neco<10,20> x; // bu durumda 10 ve 20 kullanılacak
	neco<10> x; // Burada ise 10 ve defaulttan 40 gelecek
	Neco<> x; // 20 ve 40 açılımı demek
}

----------------------------------------------------------------------------------------------------------------------------------------------------

HATTA HEM TEMPLATE TYPE HEMDE NONTYPE PARAMETER DEFAULT ARGUMAN ALABİLİR !!!!!

template<typename T = int, int x = 20>
class Neco{
};
int main()
{
	Neco<>x; // bu int,20 açılımı olacak.
}

----------------------------------------------------------------------------------------------------------------------------------------------------

HATTA VE HATTA :D:D:D 

template<typename T = int, T x = 20>	 // T ye dikkat. T int ise diğer parametrede int türden nontype. double ise double olacak.
class Neco{

};
int main()
{
	Neco<>x; // int, 20 açılımı
}

template<typename T, T x> // Varsayılan template argüman olmasada olur.
class Neco{
...

----------------------------------------------------------------------------------------------------------------------------------------------------

NONTYPE PARAMETRE C++ 2020 YE KADAR 
INTEGRAL TYPE
OBJECT POINTER TYPE
FUNCTION POINTER TYPE YADA NULLPTR_T OLMAK ZORUNDAYDI

GERÇEK SAYI TÜRLERİ NONTYPE PARAMETRE OLARAK KULLANILAMIYORDU.

C++20 İLE TEMPLATE NONTYPE PARAMETRELERİ
GERÇEK SAYI TÜRLERİNDEN
CONSTEXPR CTORA SAHİP SINIF TÜRLERİNDEN OLABİLİYOR.

----------------------------------------------------------------------------------------------------------------------------------------------------

C++17 İLE NONTYPE PARAMETRE DOĞRUDAN AUTO KEYWORD İLE KULLANILABİLİR

template <auto n>
class Myclass{

};

int main()
{
	Myclass<10>; // burada 10 un türü int olduğundan. Template nontype parametresi int olacak
	Myclass<10L>; // Burada 10 Long olacaktı.long n olacaktı yani
}


Bir örnek daha

template <auto n>
class Myclass{

};

int g;
int main()
{
	Myclass<&g>; //auto yerine int * gelecek.
}


==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================

MEMBER TEMPLATES
----------------

template<Typename T>
class Myclass{
public:
	void func(T x);
};

Burada T nin parametresi görüldüğü gibi int

int main()
{
	Myclass <int> mx; // Myclass int açılımı. T burada int
	mx.func(1.0); // Bu adımda template type deduction yapılmayacak.
				  // Çünkü bir üst satırda zaten int açılımı verilmiş.daraltıcı dönüşümden dolayı uyarıda verir hatta
}

==================================================================================================
==================================================================================================
==================================================================================================
EN SIK YAPILAN HATA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
AŞAĞIDAKI PARAMETRE FORWARDING REFERANS MI DEĞIL MI?

template<Typename T>
class Myclass{
public:
	void func(T&& x); //BURASI FORWARDING REFERANS MI DEĞİL Mİ? FORWARDING DEĞİL.
};

NEDEN DEĞİL?
Bu functionun parametresi sağ taraf referansı. Sağ taraf referansı ayrı, forwarding referans ayrı.
Bunları birbirinden ayıran kilit nokta şu, forwarding referans olması için type deduction olmalı.

template <typename T>
void func(T&&); // forwardıng referans

auto &&r = expr; //forwarding referans

for(auto &&r : expr) // forwarding referans

AMA T TÜRÜNÜN NE OLDUĞU ZATEN BELLİYSE BU FORWARDING REFERANS DEĞİL!!!!!!!!!!!

void foo(std::vector<int> &&) //Burasıda forwarding referans değil.Bir deduction yok.
{
}

template<typename T>
void foo(std::vector<T> &&) // DEĞİL. Bu func ın parametresi sağ taraf referansı.Yani T int ise
{							// parametresi vector<int>&& olacak.Yani T yalın halde değil
}							// başka bir açılım olarak vberilmişse forwarding referans değil
							// Ancak T&& olursa forwarding referans


template <typename T>
void foo(const T&&) // Burasıda forwarding referans değil.
{					// Const gelince forwarding referanslık bozuldu
}

==================================================================================================
==================================================================================================
==================================================================================================

TEKRAR ilk örnekten devam edelim

template<Typename T>
class Myclass{
public:
	void func(T&& x); //BurasI forwarding referans değil.
};

int main()
{
	Myclass <double> x; // T burada belli oldu
	x.func(1.2); // Burada belli değil.
}


Bu STL de önemli olacak.

int main()
{
	vector<int> ivec;
	ivec.push_back(); // mouse ile üzerine gelince parametresi int&& göründü.T&& değil.
}						// forwarding referansa sahip değil. zaten yukarıda int açlımı verilmiş.


Vectörün yapısını biraz gösterdi hoca.Yazmıyorum
Alınan argümanı taşıyarak veya kpyalayarak sona ekleme olayları anlatıldı.
40:00

----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
class Myclass{
public:
	void func(Myclass); // Burada Myclass ile Myclass<T> arasında hiçbir fark yok !!!!
};

int main()
{
	Myclass<int> mx;
	mx.func(); // mouse u buraya getirdiğimizde zaten Myclass<int> gösteriyor. double olsaydı Myclass<double> olurdu.
}

----------------------------------------------------------------------------------------------------------------------------------------------------

COPY CTORU DÜŞÜNELİM

template <typename T>
class Myclass{
public:
	Myclas(const Myclass &); // BU NE DEMEK ?	 Myclass<int>x; için const Myclass<int>& demek !!!!!
};


Bunu neden yazdık ?
template <typename T>
class Myclass{
public:
	void func(Myclass);
};

int main()
{
	Myclass<double> md;
	Myclass<int> mi;

	md.func(mi); // SENTAKS HATASI.
}

Myclass<double> ile Myclass<int> açılımı birbirine atanamaz çünkü farklı türler.
Yani bu functiona mi'yi argüman olarak göndermem ile Nec sınıf türünden başka nesneyi argüman olarak göndermek arasında hiçbir fark yok.

class içindeki func Myclass şeklinde yazılmış yani aslında md için Myclass<double>, argüman olarak ise mi yani Myclass<int> gönderilmiş 
ve argüman parametreye kopyalanacağı sırada SENTAKS HATASI oluşur.

GEÇERLI OLMASI IÇIN 
template <typename T>
class Myclass{
public:
	void func(Myclass x)
	{
		std::cout << typeid(*this).name() << "\n";
		std::cout << typeid(x).name() << "\n";
	}
};

int main()
{
	Myclass<double> md;
	Myclass<double> mx;

	md.func(mx); // Artık geçerli 
}

----------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDA FARKLI TÜRLERDEN OLMASI İLE OLUŞAN HATAYI MEMBER TEMPLATE İLE AŞABİLİRİZ.
BU STL DE ÇOK KULLANILIYOR


template <typename T>
class Myclass{
public:
	template<typename U>
	void func(Myclass<U> x)  // Burası U x te olabilirdi
	{
		std::cout << typeid(*this).name() << "\n";
		std::cout << typeid(x).name() << "\n";
	}
};

int main()
{
	Myclass<double> md;
	Myclass<int> mi;

	md.func(mi); //ARTIK SENTAKS HATASI DEĞİL.
}

ÇIKTI
class Myclass<double>
class Myclass<int>

----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
class Nec{ };

template <typename T>
class Myclass{
public:
	void func(Nec<T> x)
	{
		std::cout << typeid(*this).name() << "\n";
		std::cout << typeid(x).name() << "\n";
	}
};

int main()
{
	Myclass<int> mi;
	Nec<int> ni;
	Nec<double> nd;

	mi.func(ni); // GEÇERLİ
	mi.func(nd); // SENTAKS HATASI. Legal olması için class içine member template yazacağız yine.
}

----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
class Nec{ };

template <typename T>
class Myclass{
public:
	template<typename U> // Member template eklendi
	void func(Nec<U> x)
	{
		std::cout << typeid(*this).name() << "\n";
		std::cout << typeid(x).name() << "\n";
	}
};

int main()
{
	Myclass<int> mi;
	Nec<double> nd;

	mi.func(nd); // Artık buda geçerli.
}

ÇIKTI
class Myclass<int>
class Nec<double>

----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------

PEKİŞTİRMEK İÇİN PAIR KÜTÜPHANESİNİ İLKEL SEVİYEDE İMPLEMENTE EDECEĞİZ.

STL de en sık kullanılan sınıf şablonlarından biri. Özü çok basit ama içeriği karışık.
C++ta user kodu yazan programcı olmak ile library yazan programcı olmak ayrı bir seviye. STL deki boosttaki sınıf veya func kodlarını profesyonel
seviyede oluşturmaksa bu ayrı bir seviye.Bu seviyeye gelmek kolay değil. İleri C++ ta o seviyeye yaklaşacağız.

Biz pairi birebir yazmayacağız ama primitive olarak yazacağız. Birden fazla değeri bağlamak anlamında kullanılıyor.
pair utility header file içersinde bulunuyor

int main(
{
	std::pair(int,double); // Bu int ile double birarada tutulacak demek
	std::pair(int,int); // Bu int ile int birarada tutulacak demek
	std::pair(string,int); // Bu string ile int birarada tutulacak demek
}

1 - En çok kullanıldığı yer bir fonksiyondan 2 adet değer döndürmek için.
bir functan hem int hem double döndürülecekse func return değerini pair<int,double> yapabiliriz.
std::pair<int,double> foo(); yapılabilir mesela

std::set<int> myset;
myset.insert(); bunun return değeri iterator bool değeri. STL de bazı funcların return değeri pair

2 - bir sınıfın veri elemanını pair yapabiliriz

class Person{
private:
	std::pair<std::string,int> mx;
};

3 - Container denen sınıflarda pair tutmak çok sık karşımıza çıkan yapı.
	insanların yaşlarını ve isimlerini birarada tutmak istedik ama bir nedenden ötürü sınıf yapmak istemedik
	Aşağıdaki gibi yazılabilir.

int main()
{
	std::vector<std::pair<string,int>> ivec;
}

----------------------------------------------------------------------------------------------------------------------------------------------------

PAIRI ÇOK IYI BILMEMIZ GEREKIYOR.

Şimdi biraz basit pair sınıfını yazalım.
template <typename T, typename U>
struct Pair{
	Pair() = default;
	Pair(const T& t, const U& u) : first(t), second(u) { }  // bunun sayesinde Pair<int,double> x{123,5.6}; yapabiliriz.

	T first{}; //value init edildi. Bu da zero init
	U second{};
};

int main()
{
	Pair<int,double> p;
	std::cout << p.first << " " << p.second << "\n"; // 0 0 yazar. 

	Pair<string,bitset<32>> p2; // bu sentaks string ve bitsetin default ctorlarıyla hayata gelmelerini sağlayacaktı.
}

A - Bir pairi default construct edersek first ve second value init edilecek
Pointer veri elemanlar nullptr
boolean lar false
tamsayı ve gerçek sayılar 0 ile 
sınıf türden elemanların ise default construct edilmesi demek.

class a yazılır
Pair(const T& t, const U& u) : first(t), second(u) { }


B - Burada önemli olan funclardan biride karşılaştırma functionları
Burada first ü küçük olan küçük oluyor. firstler eşitse secondları küçük olan küçüktür.
Eşitse ikiside, sonuç eşit çıkıyor. Aşağıdaki func şablonundan tüm pairlerin kıyaslanması sağlanabilir.

template <typename T, typename U>
bool operator<(const Pair<T, U> &left, const Pair<T,U>& right)
{
	return left.first < right.first || !(right.first < left.first) && left.second < right.second; //burası idiyom
}

< operatorü STL in en önemli operatörü kabul ediliyor. 
implementasyonlarda < kullanıyoruz. yukarıdaki ifade de == yazmak yerine < yazdık mesela uzun uzun.
Bazı sınıfların == olmak zorunda değil.

----------------------------------------------------------------------------------------------------------------------------------------------------

EŞİTLEME NASIL MÜMKÜN OLUYOR !!! ÖNEMLİ !!!

template <typename T, typename U>
struct Pair{
	Pair() = default;
	Pair(const T& t, const U& u) : first(t), second(u) { }  // bunun sayesinde Pair<int,double> x{123,5.6}; yapabiliriz.

	template <typename K, typename M>
	Pair(const Pair<K,M> &other) : first(other.first), second(other.second) { }  // Burada bir sentaks hatası olmaması için,
																				 // K türünden T türüne ve M türünden U türüne dönüşüm olmalı.Eşitlendiği için.
	T first{};
	U second{};
};

int main()
{
	using namespace std;
	Pair<double,double> x;
	Pair<int,int> y;
	
	x = y; // NEDEN COPY ASIGNMENT ÇAĞRILMIYOR ???? AÇIKLAMA AŞAĞIDA
}

BURAYI OKU !!!!
---------------
X = Y; AÇIKLAMASI
BURADA ATAMA OPERATÖRÜNÜN SAĞ TARAFINDAKİ DEĞER Pair<int,int>, SOL TARAFINDAKİ DEĞER İSE  Pair<double,double> 
BURADA FARKLI TÜRDEN STRUCT NESNELERİ ARASINDA BİR ASSİGNMENT İŞLEMİ YAPMAYA ÇALIŞINCA PARAMETRELİ CTOR DEVREYE GİRİYOR.
BU CONSTRUCTOR SAYESİNDE Y, X E ATANABİLİYOR.


----------------------------------------------------------------------------------------------------------------------------------------------------

PAIR İ ARAÇ OLARAK KULLANACAĞIZ.

template <typename T, typename U>
struct Pair{
	Pair() = default;
	Pair(const T& t, const U& u) : first(t), second(u) { }

	
	T first{}; 
	U second{};
};

template <typename T, typename U>
Pair<T,U> MakePair(const T& t, const U& u)
{
	return Pair<T,U>(t,u); // bu bir geçici nesne
}

int main()
{
	Pair<int,double> p; // Bu tür sınıflardan nesneler oluşturmak için template argümanlarını yazmak zorundayız.buradaki gibi 
						// C++17 deki CTAD sonra anlatılacak. CTAD olmadanda bir teknik ile template argümanlarını ortadan
						// kaldırabiliyoruz. Bir fabrika fonksiyonu kullanarak functionlarda argument deductiondan faydalanmak.
						//makepair ismiyle yukarıda tanımladık.fabrika fonksiyonu nesne oluşturan func demek.

	auto p = MakePair(12,4.5); // Derleyici compile timeda int ve double türlerini çıkaracak.Bu durumda bu func ın return değeri pair<int,double> olacak
								 //  auto ile return değerini de tutsam, burada template argümanlarını yazmadan Pair<int,double> nesnesi oluşturmuş oluruz.
}

----------------------------------------------------------------------------------------------------------------------------------------------------

BAZI KODLARIDA STD::PAIR ÜZERİNDEN YAPACAĞIZ.

#include<utility>

int main()
{
	auto x = make_pair(12,3.4); // standart librarydeki make_pair. x in türü pair<int,double>
	auto y = make_pair(x,34L); // struct std::pair< struct std::pair <int,double>,long> türünde olacak.
}
pairi kullandığımda açısal paranterleri yazmama gerek yok.
Çok profesyonel olmasada genel yapısı görüldü pair in.

----------------------------------------------------------------------------------------------------------------------------------------------------

PAIRIN BIR INSERTERI YOK. ÖYLE BIR FUNC YAZALIM KI HERTÜRLÜ PAIRI ÇIKIŞ AKIMINA VERSIN.

#include <string>
#include <bitset>
#include <iostream>

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)  //pairin elemanları struct içerisinde public interfacete. Yani friendlik vermeye gerek yok
{
	return os << "(" << p.first << ", " << p.second << ")";
}
int main()
{
	std::pair<int, double>p{ 23, 5.6 };
	std::cout << p << "\n";

	std::cout << std::make_pair(12, 4.5)<<"\n";

	std::cout << std::make_pair(std::make_pair(33, 6.7), std::make_pair(std::bitset<32>{1234u},std::string("Alican"))) << "\n";
	std::cout << std::make_pair("Veli", std::make_pair(std::bitset<32>{1234u},std::string("Alican"))) << "\n";


	//.. birsürü örnek verilebilir.
}

Bu durumda burada herbir make_pair için ayrı bir overload yazılacak. Herbirinin türü farklı çünkü.


MOLA

====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================


SINIF VE FUNCTION ŞABLONLARININ EXPLICIT SPECIALIZATION DURUMU
--------------------------------------------------------------
Şablonlara ilişkin en temel mekanizmalardan biri,
bir şablonun belirli tür açılımı için derleyicinin kod üretmesi yerine, kodu kendimizin vermesi.

Bu sınıf şablon, func şablonu veya değişken şablonu için olabilir.

template<typename T>
class Myclass{

};

int main()
{
	Myclass<int> mx; 
}						

Biz burada derleyicinin kod yazması yazması yerine benim verdiğim kodun kullanılmasını sağlayabilirim.
Buna TEMPLATE EXPLICIT SPECIALIZATION denir.Diğer adıda TEMPLATE FULL SPECIALIZATION.

Yani diyoruzki Myclass<double> için sen bu template ten kod yazma ben sana bunun kodunu burada veriyorum.
Bu özellik hem sınıf hemde function şablonları için kullanılabilir. Ama function şablonlarında
overload özelliği olduğu için explicit specialization sınırlı bir şekilde kullanılıyor.
STL birçok yerde explicit specialization kullanıyor.

SENTAKS

#include <string>
#include <bitset>
#include <iostream>


template<typename T> // burası görünür durumda olmalı.
class Myclass {
public:
	Myclass()
	{
		std::cout << typeid(*this).name() << "\n";
	}
};

template <> // bu tokena diamond da diyorlar. Burada explicit bir specialization oluşturduk.Tabi yukarıda bir template yapısı görünür durumda olmalı
class Myclass<int>
{
public:
	Myclass(){
		std::cout << "Explicit specialization for int\n";
	}

};

int main()
{
	Myclass <char> cx; // class Myclass<char> yazar. Primary template kullanıldı
	Myclass <double> dx; // class Myclass<char> yazar. Primary template kullanıldı
	Myclass <int> ix; // Burada ekrana birşey yazmaz çünkü bizim yazdığımız 2. template kullanıldı.Primary için int türüne özgü Specialization
}

Çıktı
-----
class Myclass<char>
class Myclass<double>
Explicit specialization for int

----------------------------------------------------------------------------------------------------------------------------------------------------

2 argümanlı örnek.
template<typename T, typename U> // burası görünür durumda olmalı.
class Myclass {
public:
	Myclass()
	{
		std::cout << typeid(*this).name() << "\n";
	}
};

template <> // bu tokena diamond da diyorlar. Burada explicit bir specialization oluşturduk.Tabi yukarıda bir template yapısı görünür durumda olmalı
class Myclass<int,double>
{
public:
	Myclass(){
		std::cout << "Explicit specialization for int\n";
	}

};

int main()
{
	Myclass <char,char> cx; 
	Myclass <double,double> dx; 
	Myclass <int,double> ix; // Bunun için bizim yazdığımız specialization çalışır.
}


SONUÇ : BELİRLİ BİR TÜR TEMPLATE İN ANA YAPISINA UYMUYORSA VE O TÜR İÇİN ÖZEL BİR KODA İHTİYAÇ VARSA ONU SPECİALİZATİON OLARAK VEREBİLİRİZ.

----------------------------------------------------------------------------------------------------------------------------------------------------

NOT : TEMPLATE NONTYPE PARAMETRELERİ İÇİNDE BU GEÇERLİ.

template <int n>
class Myclass{
public:
	Myclass()
	{
		std::cout << "primary template n is : " << n << "\n";
	}
};

5 değeri için explicit specialization

template<>
class Myclass<5>
{
public:
	Myclass()
	{ 
		std::cout << "Specialization for 5\n";
	}
};

int main()
{
	Myclass<1>m1;
	Myclass<2>m2;
	Myclass<3>m3;
	Myclass<4>m4;
	Myclass<5>m5;
	Myclass<6>m6;
}

ÇIKTI
-----
primary template n is : 1
primary template n is : 2
primary template n is : 3
primary template n is : 4
Specialization for 5
primary template n is : 6

----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------

Kursun başlarında bir soru vardı.
1 -100 arası sayıları ekrana döngü kodu olmadan yazdır.
Bir tanesi bir sınıf yazıp içerisinde static ömürlü bir değişken ctor her çağrıldığında değişken 1 artar
Myclass my[100]; yazarız. Burada da döngüsel bir yapı var ama biz yazmıyoruz bunu.

BIR DE BUNU TEMPLATELER ILE YAPALIM

KURAL : Bir function şablonuyla bir function bir arada bulunabilir.
		Bir sınıf şablonuyla da bir sınıfın özelleştirilmş hali birarada bulunabilir.Eğer bir sınıf şablonunun bir tür için full specialization ı 
		söz konusuysa onun kodunu derleyici yazmayıp bizim yazdığımızı kullanacak. 

template<int n>
struct A : A <n-1> { // mesela burası ne demek ? A<100>, A<99> dan kalıtım yoluyla elde edilecek. 99 da 98 den elde edilecek.
					// A<100> desek. Bu A<99> un kodunu yazacak. A<99> da A<98> n kodunu yazacak ...
					// En son A<1> de A<0> dan kalıtım yoluyla elde edilecek.

	A()
	{
		std::cout << n << " ";
	}
};

template<>
struct A<0> {		 // bu yapıda A<1> yazacak derleyici ve en son A<0> ı buradan alacak.Buna Base case deniyordu

};

int main()
{
	A<100> ax;
}

----------------------------------------------------------------------------------------------------------------------------------------------------

Benzer senaryoları düşünmek önemli.
factorial değerini constexpr kullanmadan bir compile time sabiti olarak hesaplat.hem func şabloonuyla hemde sınıf şablonuyla yapılabilir.
Aynı şekilde a üzeri b yi compile sabiti olarak derleyiciye hesaplatmaya çalışalım

Tekniklerden biri. C++ ın eski günlerinden kalma bir teknik.

template <int n>
struct Factorial
{
	const static int value = n * Factorial<n -1>::value; // artık inline var C++17 den sonra tanımlanabiliyor ama eski C++ dedik ona göre yazıyoruz.
};

template<>
struct Factorial<0>
{
	const static int value = 1;
};

int main()
{
	Factorial<6>::value; // sabit ifadesi olduğunu göstermek için bir dizinin boyutu yapalım.
	inta[Factorial<6>::value]; // mouse ile üzerine gelince 720 yazıyor.
}

Günümüzde çok daha kolay yolları var.



===================================================================================================================================================
===================================================================================================================================================
===================================================================================================================================================

FONKSİYON ŞABLONLARININ ÖZELLEŞTİRİLMESİ
----------------------------------------

Fonksiyon şablonunda diyelimki T nin int olması için func fonk kodunun kendimizin yazdığı kod olmasını istiyoruz.
Derleyicinin yazdığı kod değil.Buradaki yöntemlerden biri gerçek function yazmak. Diğeri ise EXPLICIT SPECIALIZATION.

explicit specialization olarak yazalım

template <typename T>
void func(T x)
{
	std::cout << "primary template for type " << typeid(T).name() << "\n";
}

template <>
void func(int x) //YUKARIDA T X TE REFERANS DECLERATÖRÜ OLSAYDI BURADA DA OLMAK ZORUNDAYDI.AYNI PARAMETRİK YAPIDA OLACAK.
{
	std::cout << "primary template for type\n";
}

int main()
{
	func(2.3);
	func('A');
	func(5);
}

ÇIKTI
-----
primary template for type double    // compiler tarafından yazılan func çağrıldı
primary template for type char		// compiler tarafından yazılan func çağrıldı
primary template for type			// bizim yazdığımız explicit specialization çalıştı.

----------------------------------------------------------------------------------------------------------------------------------------------------

EN ÇOK KARIŞTIRILAN YERLERDEN BİRİ MÜLAKAT SORUSU
-------------------------------------------------
FUNCTION TEMPLATELERDE EXPLICIT SPECIALIZATION, FUNCTION OVERLOAD SETE KATILMIYOR
EXPLICIT SPECIALIZATION KULLANILABİLMESİ İÇİN NORMALDE, BİZİM YAZDIĞIMIZ TEMPLATE İN SEÇİLMESİ VE
BU FUNCTAN ELDE EDİLEN İMZADA T NİN İNT OLMASI GEREKİYOR(BU ÖRNEK İÇİN İNT).

ÖR:	
template <typename T>
void func(T x)
{
	std::cout << "1\n";
}

template <>
void func(int *x) 
{
	std::cout << "2\n";
}

template <typename T>
void func(T *x)
{
	std::cout << "3\n";
}

int main()
{
	int x{};
	func(&x); // EKRANA NE YAZAR ?  
}

Herkes T parametresi var en üsttekinde, bir altında da int * var, dolayısıyla int * olan 2. seçilir diyor ama YANLIŞ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
EKRAN ÇIKTISINDA 3 YAZIYOR !!!!!!!!!!!!!!!!!!!!!
Nedeni template explicit specialization function overload sete dahil edilmiyor.(Burada definition sıralarıda önemli)
Dolayısı ile overload sette T ve T* olan template ler var.
Gönderilen argüman eğer int olsaydı derleyici T olan template i seçilseydi, derleyici kod yazmak yerine specialization kullanacaktı.
Yani int * ın seçilmesi için T nin seçilmesi gerekiyor.Bizim örnekte ise T ve T * var. T* daha spesifik. T * seçildi.

Burada hangi sıra ile yazıldıklarının önemi var. int *, T template tür parametreli function şablonunun özelleştirilmiş hali.Yani yukarıdaki(1 yazdıran) template in.

ŞİMDİ İNT * PARAMETRELİ ÖZELLEŞTİRİLMİŞ FUNCTİONU EN ALTA ALDIK.

template <typename T>
void func(T x)
{
	std::cout << "1\n";
}

template <typename T>
void func(T *x)
{
	std::cout << "3\n";
}

template <>
void func(int *x)
{
	std::cout << "2\n";
}


int main()
{
	int x{};
	func(&x); // EKRANA NE YAZAR ?
}

ŞİMDİ 2 YAZAR. NEDENİ İSE, INT * PARAMETRELİ ÖZEL FUNC,  ÖNCEKİ YAZILDIĞI YERDE GÖRÜNÜR DURUMDA OLAN T PARAMETRELİ TEMPLATE OLDUĞUNDAN,
İNT * PARAMETRELİ FUNCTİON, T PARAMETRELİ TEMPLATE İN EXPLİCİT SPECİALİZATİON FUNCTIONUYDU.YANİ İNT*, T PARAMETRELİNİN ÖZEL FUNC IYDI.

BU SEFER OLUŞTURDUĞUMUZ EXPLİCİT SPECİALİZATİON ÜSTTEKİ TEMPLATE İN DEĞİL ALTTAKİ TEMPLATE İN EXPLİCİT SPECİALİZATİONU.
T VE T * OVERLOAD RESOLUTİONA GİRDİ. T * DAHA SPECİFİK OLDUĞUNDAN KAZANDI VE DERLEYİCİ KOD YAZMAK YERİNE VAROLAN ÖZELLEŞTİRİLMİŞ FUNC I ÇALIŞTIRDI.

===================================================================================================================================================
===================================================================================================================================================
===================================================================================================================================================

PARTIAL SPECIALIZATION / KISMİ ÖZELLEŞTİRME
--------------------------------------------
Birbirine benzer gözüksede kesinlikle farklı araçlar.Bu sınıf şablonları için var. Function şablonları için yok !!!!!
PARTIAL İLE EXPLICIT SPECIALIZAION SEKTAKSINI KARIŞTIRMA !!!!!!!!!!!!
Explicit specialization ise her ikisi içinde var.
Alternatif bir template veriyoruz ve daha sınırlı bir tür kümesi için alternatif template in kullanılmasını istiyoruz.
Burada artık template kod artık bir tür için değil, bir tür ailesi için kullanılıyor.

Mesela
template <typename T>
class Myclass;

Pointer için partial specialization

Pointer olmayan T türleri için derleyici primary template kullanacak ama pointer türler için alternatif template i kullanacak.
Ya da referans türleri için bunu yapacak.
pair<t,t> açımı için yada.

----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------

SENTAKS FARKI
-------------
Explicit ile partial specialization arasındaki sentaks farklılığı çok önemli.

EXPLICIT SPECIALIZATION
-----------------------
template <typename T>
class Myclass{

};

typename<>				// Tüm int* lar için çalışacak
class Myclass<int *>
{

};

PARTIAL SPECIALIZATON
---------------------
template<typename T>
class Myclass{

};

template<typename T>	// T nin tüm pointer türleri burada çalışacak
class Myclass<T *>
{

};

FUNCTIONLAR IÇIN PARTIAL SPECIALIZATION YOK AMA EXPLICIT(FULL) SPECIALIZAION VAR!!!!

----------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------

ÖZELLIKLE BIRDEN FAZLA TEMPLATE TÜR PARAMETRESI VARSA.
Bu durumda daraltılmış bir tür kümesi oluşturmak için daha fazla fikir var.

template <typename T, typename U>
class Myclass;

tür argümanının int olması durumu.
myclass<int, ...> için alternatif template kullanılacak. ... yerine float double long ... gelebilir

Diğer tüm durumlar için derleyicinin yazdığı kodlar yani primary template kullanılacak.

----------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>

template <typename T>
class Myclass{
public:
	Myclass() 
	{
		std::cout << typeid(*this).name() << "\n";
	}
};

template <typename T>	// Bu pointer olan türler için bu template kullanılacak demek.
class Myclass<T*>
{
public:
	Myclass()
	{
		std::cout << "partial specialization for T* \n";
	}
};	

int main()
{
	Myclass<int> m1;
	Myclass<int &> m2;
	Myclass<double> m3;
	Myclass<int *> m4;
	Myclass<char *> m5;
	Myclass<double *> m6;
	Myclass<int []> m7;
}

Çıktı
-----
class Myclass<int>
class Myclass<int &>
class Myclass<double>
partial specialization for T*   Görüldüğü gibi 3 adet function pointer için yazdığımız partial specialization çalıştı.
partial specialization for T*
partial specialization for T*
class Myclass<int [0]>


----------------------------------------------------------------------------------------------------------------------------------------------------

REFERANS İÇİN BAKALIM.

template <typename T>
class Myclass{
public:
	Myclass() 
	{
		std::cout << typeid(*this).name() << "\n";
	}
};

template <typename T>	// Bu pointer olan türler için bu template kullanılacak demek.
class Myclass<T*> {
public:
	Myclass()
	{
		std::cout << "partial specialization for T* \n";
	}
};

template <typename T>	// Bu pointer olan türler için bu template kullanılacak demek.
class Myclass<T&> {
public:
	Myclass()
	{
		std::cout << "partial specialization for T& \n";
	}
};	

int main()
{
	Myclass<int> m1;
	Myclass<int &> m2;
	Myclass<double&> m3;
	Myclass<int *> m4;
	Myclass<char *> m5;
	Myclass<double *> m6;
	Myclass<int []> m7;
}

Çıktı
-----
class Myclass<int>
partial specialization for T&
partial specialization for T&
partial specialization for T*
partial specialization for T*
partial specialization for T*
class Myclass<int [0]>

NOT : ÖNEMLİ OLAN ÖZELLEŞTİRMEDE ANA TEMPLATE İN PARAMETRE SAYISI KAÇSA, ÖZELLEŞTİRMEDEKİ TÜRDE O KADAR OLACAK.
	  ÖZELLEŞTİRMEDEKİ TEMPLATE PARAMETRE SAYISI FAZLA OLABİLİR. CLASS YAZDIĞIMIZ KISIMDAKİ PARAMETREDEN BAHSEDİLİYOR.
	  KARIŞIK OLABİLİR ÖRNEK AŞAĞIDA.

----------------------------------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ ÖRNEK

template <typename T>	// BİR TANE TEMPLATE PARAMETRE VAR.
class Myclass{
public:
	Myclass()
	{
		std::cout << " Primary template " << typeid(*this).name() << "\n";
	}
};

template <typename T, typename U>	// BURADAKİ PARAMETRE SAYISI FAZLA OLABİLİR. BU SORUN DEĞİL.
class Myclass< std::pair <T,U> > {  // YUKARIDAKI AÇIKLAMADA KASTEDILEN, PRIMARY TEMPLATE TE BIR TEMPLATE PARAMETRE VAR. BU SATIRDA std::pair<T,U> VAR
public:								// BU DURUMDA GEÇERLI.SAYILARI AYNI !!!!!!!!!!!!!!!!!!!!!
	Myclass()
	{
		std::cout << "partial specialization\n";
	}
};

int main()
{
	Myclass<int>m1;
	Myclass<int *>m2;
	Myclass<std::pair<int,double>>m3;
}

Çıktı
-----
Primary template class Myclass<int>
Primary template class Myclass<int *>
partial specialization					bu bizim specialize ettiğimiz function 



ÇOOOOK ÖNEMLİ !!!!!!!!!
------------------------

primary template -> template <typename T> ... diye devam etseydi yani 1 template tür parametresi olsaydı

special template -> template < ... T...> 
					class Myclass< ...> ... yerde 2 parametre olsaydı SENTAKS HATASI. Tam tersinde de SENTAKS HATASI

					SAYILARI AYNI OLMALI !!!!!!!!

----------------------------------------------------------------------------------------------------------------------------------------------------

BİRDEN FAZLA TEMPLATE TÜR PARAMETRESİNİN OLDUĞU DURUMLARDA ÇOK DAHA ZENGİN OLANAKLAR VAR.

template <typename T, typename U>
class Myclass{
public:
	Myclass()
	{
		std::cout << "Primary Template " << typeid(*this).name() << "\n";
	}
};

template <typename T>
class Myclass<int, T>{    // Dikkat.Primary template argument sayısı ile buradaki argüman sayısı eşit
public:
	Myclass()
	{
		std::cout << "partial spec\n";
	}
};

int main()
{
	Myclass<double,int>m1;
	Myclass<double,double>m2;
	Myclass<int,double>m3;
}

Çıktı
-----
Primary Template class Myclass<double,int>
Primary Template class Myclass<double,double>
partial spec									// burada partial specialization kullanılacak


----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, typename U>
class Myclass{
public:
	Myclass()
	{
		std::cout << "Primary Template " << typeid(*this).name() << "\n";
	}
};

template <typename T>
class Myclass<T, T>{    // Bu durumda iki template argümanın aynı olması durumunda partial spec. çalışır. int-int, double-double,string-string gibi.
public:
	Myclass()
	{
		std::cout << "partial spec\n";
	}
};


----------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, typename U>
class Myclass{
public:
	Myclass()
	{
		std::cout << "Primary Template " << typeid(*this).name() << "\n";
	}
};

template <typename T>
class Myclass<T *, T *>{    // Bu durumda iki template argümanın aynı pointer türünden olması gerekiyor bunun çalışması için.int* int*, gibi...
public:
	Myclass()
	{
		std::cout << "partial spec\n";
	}
};

----------------------------------------------------------------------------------------------------------------------------------------------------

VECTORÜN BOOL AÇILIMI BIR PARTIAL SPECIALIZATION.

ÖNEMLİ NOT:
GErek sınıflar için oluşturulan explicit spec ve partial spec. te, spec olarak verilen kodlarda interface aynı olması gerekmiyor.

template<typename T>
class Myclass{
public:
	void f1();
	void f2();
	void f3();	
};

template<>
class Myclass<int>
{
public:
	void f4();
	void f5();
}

int main()
{
	Myclass<int>{}.f4();	//spec func çalışır
	Myclass<double>{}.f1();  // primary templatten yazılan kod çalışır
}
Vector sınıfında da böyle durumalr var.


==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================

STATIC VERİ ELEMANLARI
----------------------

Ayrı şablonlardan türetilen sınıfların static veri elemanlarıda birbirinden ayrı.

template<typename T>
struct A{
	static int x; // eski c++ ta böyle yenisinde inline yazıyorduk.Bu şuanda bildirim.Buna ilkdeğer vermeliyiz.
};

template<typename T>
int A<T>::x = 0;

int main()
{
	A<int>::x++;
	A<int>::x++;
	A<int>::x++;

	std::cout << A<double>::x;	// Değeri 0 çünkü double açılımındaki x ile int açılımındaki x farklı varlıklar.
}

Daha irili ufaklı birçok kural var. C++20 ile gelen özellikler var.En temel özellikler bunlar.



==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================



PERFECT FORWADING / MÜKEMMEL GÖNDERİM
-------------------------------------
nedir ? neden ihtiyaç duyuluyor?

Elimizde bir function var ve bu bir func şablonu, bu func şablonu içinde bir functionı çağıracağız.
AMA bu functionun client kodlar tarafından doğrudan çağrılmasıyla bizim fonksiyonumuz tarafından çağrılması arasında hiçbir fark olmasın istiyoruz.

void foo(int &r)
{
	
}

template <typename T>
void func(T x)
{
	foo(x);
}

int main()
{
	int ival{};
	 
	foo(ival); // burada doğrudan foo yu çağırmam ile aşağıdaki func a eleman gönderip onunda doğrudan foo yu çağırması arasında fark olmasın istiyoruz.
	func(ival); 
}

Bu ne demek?
foo ya gönderdiğim argümanların constluğu volatile liği ve value categorisi açısından hiçbir değişiklik olmayacak.

------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunu bir test edelim.

class Myclass{
};

void foo(Myclass&)
{
	std::cout << "Myclass&\n";
}

void foo(const Myclass&)
{
	std::cout << "const Myclass&\n";
}

void foo(Myclass&&)
{
	std::cout << "Myclass&&\n";
}

int main()
{
	Myclass m;
	const Myclass cm;

	foo(m); // 1. func
	foo(cm); // 2. func 
	foo(Myclass{}); // 3. func çağrılır
}


----------------------------------------

ŞIMDI BU IŞLEMI BAŞKA BIR FUNC ŞABLONU EKLEYEREK ONA YAPTIRALIM.

class Myclass{
};

void foo(Myclass&)
{
	std::cout << "Myclass&\n";
}

void foo(const Myclass&)
{
	std::cout << "const Myclass&\n";
}

void foo(Myclass&&)
{
	std::cout << "Myclass&&\n";
}

template<typename T> // Bu şimdi eklendi.
void func(T x)
{
	foo(x);
}

int main()
{
	Myclass m;
	const Myclass cm;

	//foo(m); // 1. func
	//foo(cm); // 2. func
	//foo(Myclass{}); // 3. func çağrılır

	func(m);
	func(cm);
	func(Myclass{}); // FUNCTION EKLENDI AMA SONUÇ DOĞRU DEĞIL

}
hepsinde 1. func çağrıdı. Olmadı bu. func parametresini T& yapsak mesela 3. çağrı sentaks hatası

-------------------------------------------------------------------------------------------------

BUrada yapılacaklardan biri, çok sayıda overload yazmak.

template <typename T>
void func(T &x)
{
	foo(x);
}

template <typename T>
void func(const T &x)
{
	foo(x);
}

template <typename T>
void func(const T &x)
{
	foo(std::move(x));
}

Bunları ekleyince bir hata yok. Test edildi.Burada sorun şu, 3 adet function yazdık, Eğer functionun 2 parametresi olsaydı o zaman
tam 9 tane function yazacaktım. Bunların yerine Perfect forwarding kullanılacak. Bu işi yapmanın yolu forwarding parametreye sahip bir func yazmak.

-----------------------------------------------------------------------------------------------------------------------------------------------------

#include <utility>

template <typename T>
void func(T &&x)	// buraya sol taraf referansı gönderirsem T = int& olacak ve func(int&) olcak
{					// sağ taraf değeri gönderirsem, T = int ve func(int&&) olur
	
	foo(std::forward<T>(x));	// Burada forward return değeri foo ya gönderiliyor.forward<T> açılımı yapıldıktan sonra x ile çağrı yapılmış.Dikkat et. 
								// bu argümanın constluğunu ve value kategorisini koruyarak diğer functiona geçmeyi sağlıyor.
}

Ekleyelim

class Myclass{
};

void foo(Myclass&)
{
	std::cout << "Myclass&\n";
}

void foo(const Myclass&)
{
	std::cout << "const Myclass&\n";
}

void foo(Myclass&&)
{
	std::cout << "Myclass&&\n";
}

template <typename T> //eklendi
void func(T &&x)	
{				
	foo(std::forward<T>(x));	
}

int main()
{
	Myclass m;
	const Myclass cm;

	func(m); // 1. func
	func(cm); // 2. func
	func(Myclass{}); // 3. func çağrılır
}

Çıktı
-----
Myclass&
const Myclass&
Myclass&&			doğru çalıştı

Yani biz başka bir functiona argüman gönderdik, o functionda kendi implementasyonu içerisinden
asıl çağıracağımız functiona çağrı yapınca, aldığı argümanlarda hiçbir değişiklik olmadan çağrı işlemlerini gerçekleştirdi.

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Fonksiyon argümanı 1 den fazlada olabilirdi.

template <typename T, typename U, typename K>   //aşağıdaki implementasyon ile func ın foo yu çağırması ile benim foo yu çağırmam arasında fark olmayacak.
void func(T&& t, U&& u, K&& k)
{
	foo(std::forward<T>(t),std::forward<U>(u), std::forward<K>(k));  
}

Bu 3-4-5 yada daha fazla kademede olabilir. biz sadece 1 kademeli olarak yaptık.


-----------------------------------------------------------------------------------------------------------------------------------------------------------

FORWARD FONKSİYONUNU YAZMAYA ÇALIŞALIM.
---------------------------------------
orijinali ile karışmasın diye ilk harfini büyük yapacağız.Type traits leri ezbere yapacağız. Bir sonraki dersin konusu o.

#include <iostream>
#include <utility>

class Myclass {
};

void foo(Myclass&)
{
	std::cout << "Myclass&\n";
}

void foo(const Myclass&)
{
	std::cout << "const Myclass&\n";
}

void foo(Myclass&&)
{
	std::cout << "Myclass&&\n";
}

template <typename T>
T&& Forward(typename std::remove_reference<T>::type& t) noexcept
{
	return static_cast<T&&>(t);
}

template <typename T>
T&& Forward(typename std::remove_reference<T>::type&& t) noexcept
{
	return static_cast<T&&>(t);
}

template <typename T>
void func(T&& x)
{
	foo(Forward<T>(x));

	Sol taraf değeri geldiğini düşünelim, Forward<int&> açılımı kullanılacak.Bu da yukarıdaki funclardan & olan parametrenin çağrılması demek.ilki burada.
	İlgili func içinden, parametredeki remove reference, argümanın referans türü olma özelliğini sildi ve func parametresi int& oldu. type traits te görülecek
	static cast operatörüyle de T&&, yani int& && -> int& e cast ettik.return değeri yine int& && ten int& oldu.Forward func böyle bir func
	alttaki func a dönüştü Forward
	
	int& Forward(int& t)
	{
		return t;
	}


	Sağ taraf değeri için kullanınca && parametreli func template devreye girecek.2. function
	template parametre türü int &&. sağ taraf değeri geldiğinde T int oldu. static cast ile int&& cast e edildi.
	func return değeride int&& türü.


}

int main()
{
	Myclass m;
	const Myclass cm;

	func(m);
	func(cm);
	func(Myclass{});
}

----------------------------------------------------------------------------------------------------------------------------------------------------

PERFECT FORWARDING I GERÇEK KÜTÜPHANELER ÜZERINDE GÖRELIM.

En güzel örnekler std  library deki emplace isimli function.
biz pushback yaptığımızda, argüman olarak gönderdiğimiz nesne sol taraf değeri ise, cont int & parametrelisi çalışıyor ve 
nesnenin kopyasını vectörün sağladığı bellek alanına koyuyor.

Eğer bu nesne sağ taraf değeri ise, sağ taraf referans parametreli olan, bu nesneyi taşıyor.

Emplace ne yapıyor ?
Container ın tutacağı nesneyi geçmek yerine, containerda tutulacak nesnenin constructoruna göndereceğimiz argümanları gönderiyoruz.

Mesela Vectorun emplace back func ına bakalım

class Myclass{
public:
	Myclass() = default;
	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
	Myclass(Myclass&&)
	{
		std::cout << "move ctor\n";
	}	
	Myclass(int x, int y, int z)
	{
		std::cout << "Myclass(int x, int y, int z)\n";
	}
};

using namespace std;
int main()
{
	vector<Myclass> vec;

	vec.reserve(10);

	Myclass mx;

	vec.push_back(mx); // copy ctorun çalıştığını görüyoruz.Sol taraf değeri zaten mx.

	//Sağ taraf değeriyle çağıralım
	vec.push_back(Myclass{}); // Bu sefer Myclass&&(sağ taraf referans) parametreli overload çalıştı.Buda aldığı argümanı move functionuna gönderdi.
								// Move func ın return değeri ile burada Myclass nesnesini oluşturdu.Taşıdı yani.Move Semantic

	//Emplace Functionı Perfect Forwarding yapacak.

	vec.emplace_back(1,2,3); // Myclassın ctoruna gönderilecek elemanları gönderiyoruz. Böylece bu argümanları, myclassın 3 parametreli
}							 // ctoruna geçiyor.Gönderdiğimiz argümanlar const, lvalue, rvalue olabilir ama emplace_back bunları bozmuyor.
							 
Mülakat sorusu
STL den bir move semantik örneği = push_back. const& ve t&& parametreli pushback var
Perfect forwarding örneği = vectorun emplace_back functionu örnek verilebilir.

Zaten incelenirse pushback ve emplace_back parametreleri, görülebiliyor ne oldukları.


===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================

ALIAS TEMPLATE
--------------

C++ 11 öncesinde türeş isim bildirimleri typedef kullanılıyordu. typedef ile yapılan bildirimlerin geçerliliği devam ediyor ama
tavsiye edilen using keywordü.

Sentaksı hatırlatalım
using Fcmp = int (*)(const void *, const void *)
typedef int (*Fcmp)(const void *, const void *);

typedef varken neden using eklendi?
Using bildirimleri template haline getirilebiliyor.Bu sebeple eklendi

Using keywordü ile yapılan eş isim bildirimleri için oluşturulan templatelere alias template deniyor.

SENTAKS
template <typename T>
using iptr = T*;

iptr nin kendisi bir template ve bir template argümanı istiyor.Verdiğimiz template argümanı neyse, iptr nin T açılımı (ör int açılımı)
T * türünün eş ismi oluyor.Ne demek bu ? aşağıda kod açıklıyor

Yani.
int main()
{
	iptr<int>ptr = nullptr; // yani bu int *ptr = nullptr; oldu. iptr<int> yapınca T* yerine int * geldi. Artık iptr yerine int * gelmiş oldu
}


---------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, size_t n>
using Array = T[n];

int main()
{
	int a[20];
	Array<int,20>ar; BU ikisi aynı anlamda.
}

---------------------------------------------

Aynı elemana çiftine sahip pair örneği

#include <utility>

template <typename T>
using P = std::pair<T,T>

int main()
{
	P<int> x; 
	std::pair<int,int> x; //YUkarıdaki ile aynı
}

---------------------------------------------

STL den set örneği

#include<set>
#include <iostream>

template<typename T>
using gset = std::set <T,std::greater<T>>;


int main()
{
	std::set<int, std::greater<int>>;
	gset<int> ; //yukarıdaki ile aynı anlamda


	std::set<double, std::greater<double>>;
	gset<double>; //buda bir üstteki ile aynı anlamda

}


-------------------------------------------------------------------------

EN ÇOK KULLANILDIĞI YERLER NESTED TYPELAR

Bir template e bağlı türden bahsetmek için typename keywordü kullanmam gerekiyordu

template <typename T>
struct Myclass{
	typedef int type;
};

Burada
Myclass<int>::type diyebilirim. Buradaki Nested type

-------------------------------------------------------------------------

AMA BU TEMPLATE OLSAYDI, TEMLATE DA BU NESTED TYPE KULLANABILMEM IÇIN
TYPENAME KEYWRDÜNÜ KULLANMAM GEREKIYOR.

template <typename T>
using mytype = typename Myclass<T>::type;

int main()
{
	mytype<int>; Myclass<int>::type demek

	mytype<double> ; // Myclass<int>::type demek
}



*/