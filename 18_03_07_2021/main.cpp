/*
STRINGLERDEN DEVAM.
Aslında stringler sınıf şablonundan üretilen bir sınıf.
Bir string birde cstring başlık dosyası var.
cstring, C deki string.h başlık dosyası.

Bu sınıf aynı zamanda STL containerlarının sağlaması gereken tüm özelliklerini sağlıyor.
STL containerlarını 3 e ayırıyorduk.
Sequencial containers
	vector
	deque
	list
	forward_list
	array
diğerlerini yazmadık.Geçen derste yazmıştık.
string_size::size_type --> bu aynı zamanda size_t türünün eşismi.
capacity() hem vectorde var hemde stringde var. ikisinin ortak özelliği.

size_type Nerelerde kullanılıyor?
	a - Yazı Uzunluğu.
	b - Index Türü (bir fonksiyonun yazı karakterinini indexi gibi düşünülebilir.)
	c - Tane/Adet değeri(Şu kadar şu karakterden)
		size_type türünden sınıfın static constexpr veri elemanı var.Adı npos

		class string{
		public:
			static constexpr size_type npos; // gibi düşünülebilir.
		};

npos değeri size_type değerinin en büyük değeri.4 byte ise değeri, 4 byte lık enbüyük değer
std::cout << std::string::npos; 
ÇIKTI
4294967295     4 bytelık unsigned maximum değer

---------------------------

Buradan da görülür.
#include <limits>

int main()
{
	using namespace std;
	cout << (numeric_limits<size_t>::max()) << "\n"; // aynı değer.
}

---------------------------------------------------------------------------------------------
int main()
{
	using namespace std;
	cout << (numeric_limits<unsigned long long>::max()) << "\n"; // buda unsigned long long verir.
}
---------------------------------------------------------------------------------------------

endl fonksiyonuna girdi. Bunu geçen ders yazmıştım. yine yazıyorum.

biz cout << endl; yazınca aslında endl(cout); yazmış oluyoruz.
endl new line verip aldığı akımın bufferını flush ediyor. 

//kısaca tanımı
std::ostream& endl(std::ostream& os) 
{
	os.put('\n');
	os.flush();
	return os;
}

---------------------------------------------------------------------------------------------

npos, string::size_type ın en büyük değeriydi.
Bu ne işe yarar?
1. %95 olan senaryo. 
	Yazıda arama yapan çok sayıda fonksiyon var.Arama fonksiyonları index döndürüyorlar.
	Dolayısı ile arama fonksiyonlarının geri dönüş değeri türü size_type. Bulamazsa string::npos
	döndürüyor. npos bir stringin olamayacağı bir değer.Dolayısı ile başka bir index ile karışma ihtimali yok.

int main()
{
	using namespace std;

	string str;
	cout << "Bir yazi girin\n";
	getline(cin, str); // bu fonksiyon boşluk karakteri dahil \n a kadar herşeyi alıyor. ve str nesnesini set ediyor.

	if (auto idx = str.find('k'); idx != string::npos)
		cout << "bulundu " << idx << "\n";
	else
		cout << "bulunamadi\n";
}

---------------------------------------------------------------------------------------------

2.	Parametre Örüntüleri.
	func(string&str, size_type idx, size_type n);
	Bu fonksiyona bir yazı gönderiyoruz. stringin idx inden başlayarak, n karakterlik kısmı.
	Bunun özelliği, diyelimki bunu çağırdık, index ve tamsayı değeri geçtik.
	s.func(str,idx,40); Ya 40 karakteri yoksa bu UB mi? DEĞİL. Bu well-defined behavior.
	Bu durumda Ub yok exception yok. Geriye kalan karakterlerin hepsi kullanılıyor.
	Yani 5 karakter var ama daha büyük sayı gönderdik, geriye kalan hepsini kulanmış oluyoruz.

	Ben böyle bir bağlamda, index geçip, indexten sonraki karakterlerin tamamının kullanılmasını istiyorum.
	Burada ya 100 dersek ve 100 den fazla karakter varsa ? 1000 dersek ve daha çok varsa?
	burada string::npos geçilir :D Tüm karakterlerin kullanılmasını istiyorum demek.


=============================================================================================================
=============================================================================================================
=============================================================================================================

STRING FONKSIYONLARIN TİPİK PARAMETRİK YAPILARI
-----------------------------------------------

1a - func(const std::string &str); 
Gönderilen yazı kullanılacak demek. Normal zaten bu.

1b - func(const std::string &str, size_t idx);
Subsring Constructor
str stringin idx indexinden başlayarak tüm karakter kullanılacak demek

1c - func(const std::string &str, size_t idx, size_t n); 
Subsring Constructor
str stringin idx indexinden başlayarak n tane karakter kullanılacak demek.
Burada n değerinin idx ten sonra kalan karakter sayısından büyük olması UB değil.
Exception throw etmiyor.Geriye kalan karakterlerin tamamı kullanılıyor.


2 - func(const char *p); 
cstring. 
Fonksiyon bizden null terminated byte stream istiyor demek.
Yani yazı sonunda '\0' yoksa UB. exception da göndermez.Yani cstring gönderilecek demek.


3 - func(const char *p, size_type n); 
Data parametre deniyor. 
burada null char olayı yok.çok karıştırılıyor.
Anlamı p adresinden başlayarak n kadar karakter demek.Burada null karakterin özel bir anlamı yok. 
Ama p nin n kadar elemanı( hatta n + 1 '\0' den ötürü denebilir.) olmasından biz sorumluyuz.UB konusunda riskli
char str[] = "Nevzat";
str,6 ok, str+7 ok,   str+10 UB mesela


4 - func(size_type n, char c);
fill parametre
n tane, c karakterinden demek. func(20,'a'); bu 20 tane a oluşturur mesela


5 - func(char c);
Fonksiyon tek parametre istiyor.Bu da char türden.


6 - func(std::initializer_list<char>);
INITIALIZER LIST KONUSU AŞAĞIDA ANLATILIYOR.İLK ÖNCE ORAYI OKU :D
function çağrısı yaparken, küme parantezi içinde virgüllerle ayrılmış liste geçmeliyiz.
str.deneme({'A','L','I'});


7 - func(konum1, konum2);
Range Parametre
Functionun parametresi 2 adet konum ise(ptr demedik konum dedik, ptr da olabilir.) bunlara STL de range parametre deniyor.
Range iki konumdan oluşan bir birim.
[Konum1 Konum2) ----> Konum1 dahil, Konum2 hariç. Konum1 den konum2 ye kadar olan nesnelerin tamamı.
BURADA RANGE OLMANIN KOŞULUNA BAK.AŞAĞIDA


===========================================================================================================================
===========================================================================================================================


INITIALIZER LIST
----------------
headerfile initializer_list
C++ ta küme parantezi içinde virgüllerle ayrılmış bir liste oluşturursanız ( {2,5,55,66,42,1} gibi ), bu liste
birçok yerde initializer list denilen sınıf türünden bir nesneye dönüştürülerek kullanılıyor.

Bu listedeki öğeler int ise, init listin int açılımı, double ise double açılımı ...
Bu türden nesneleri yaratmenın yolları var.
initializer_list<int> mylist {2,4,6,8,15};
initializer_list<double> mylist {2.2,4.43,6.2,8.6,15.12};

Eğer auto specifier kullaılırsa ve değişkene isim verilirse ve eşittirin sağ tarafına aynı türden 
öğelerden oluşan küme parantezi içinde list yazarsak burada tür çıkarımı initializer listin içindeki elemanlara göre yapılır.

auto x = {1,2,3,4}; init listin int açılımı olacak
auto y = {'a','b','x','q'}; init listin char açılımı olacak

auto x = {12}; init listin int açılımı
auto x = {}; SENTAKS HATASI

auto x{12};	Burada initializer listin bir açılımı yok!! direk türü int.	C++ 11 den sonra kural değişikliği oldu.
auto x{12,24}; SENTAKS HATASI. Burada init list çıkarımı yok. C++ 11 de sentaks hatası değildi.init list idi eskiden.Artık hata

Constructor init list ile init list karıştırılmamalı!!!!!!!!! 
Farklı şeyler.

----------------------------

ör
void func(std::initializer_list<int> x)
{
	
}

int main()
{
	func({1,2,3,4}); // argüman olarak bunu geçeriz.
	std::initializer_list<int> a{123,412,762};
	func(a); //bunuda geçebiliriz.
}

initializer listler bazı overloadları oluşturuyor.Burası gerçekten önemli.

---------------------------------------------------------------------------


class myclass{
public:
	Myclass(std::initializer_list<int>)
	{
		std::cout << "initializer_list\n";
	}
	Myclass(int)
	{
		std::cout << "Myclass(int)\n";
	}
	Myclass(int,int)
	{
		std::cout << "Myclass(int,int)\n";
	}
};
int main()
{
	Myclass m1{1,2}; init list
	Myclass m2 = {1,2}; init list
	Myclass m3{4};  Normalde int çağrılamsı beklenebilir.Küme parantezi ile ilk değer verilince İNİT LİST OLAN CTORUN DİĞERLERİNE
					ÜSTÜNLÜĞÜ VAR. İNİT LİST ÇAĞRILIR. İnit listi yorum yapıp dene istersen

	Myclass m4(1,2); Burada init list ctoru kullanılmayacak.int param kulanılır
	Myclass m5(1); burada da int param kulanılır.
}

INIT LIST ISTERSEM KÜME KULLANIRIM. INT PARAMETRELI ISTERSEM NORMAL PARANTEZ KULLANIRIM.
Myclass m3{4}; burada ctor init list olan function çağrılır
Myclass m5(1); burada da int param olan function çağrılır.

ÖR:
string str(57,'A'); bu 57 adet A yazdırır.
string str{57,'A'}; Burada ise 57 nin ascideki karşılığı ve A karakterini yazdırır.

------------------------

init list,in bazı member funcları var.
size mesela

void func(std::initializer::list<int> x)
{
	cout << x.size() << "\n";
}

int main()
{
	func({1,5,7,8}); // 4 yazdırır.
	func({ }); // 0 yazdırır.
}

------------------------------------------
init listi for ile dolaşabiliriz.

using namespace std;
void func(std::initializer_list<int> x)
{
	for (auto iter = x.begin(); iter != x.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << "\n";
}

int main()
{
	func({ 1,5,7,11,15,22 }); //burada tüm listeyi dolaştığını görürüz.
}

----------------------------------------------------------------------------

void func(int a)
{
	cout << "func cagrildi a = " << a;
}

int main()
{
	int x{12},y{23},z{41};
	for(auto val : {111,222,333,x,y,z}) //burada init listteki öğelerden her turda birini kullanırız.
	{
		func(val);
	}
}

===================================================================
===================================================================
===================================================================

ÇOK ÖNEMLİ!!!!!!!!!!!!!!!!!!!!

Derleyici aslında init list karşılında bir dizi oluşturuyor.

void func(initializer_list<int> x) //referans decleratörü yok
{
	
}

int main()
{
	initializer_list<int> y{1,4,5,7,8,9}; 

	func(y);	
	yukarıda ref decleratörü yok. call by value olmalıydı ama öyle değil.
	Initializer list her zaman referans semantiği ile geçiyor.Kopyalama gibi görünsede referans semantiği var.
	Initializer listteki öğeleri değiştiremiyoruz.Her zaman const zaten.

}

auto iter = x.begin();
*iter = 55; //SENTAKS HATASI

----------------------------------------------------------

class Myclass
{
public:
	Myclass() = default;
	Myclass(int) { }
	Myclass(const Myclass&)
	{
		std::cout << "copy ctor\n";
	}
	void foo()
	{
	
	}
};

int main()
{
	Myclass a[10];
	for(auto x : a) // Burada copy ctor çağrılır.Aslında açılımı Myclass R = a[...] 
	{
		x.foo();		
	}
}

Referans decleratörü kullanırsam
for(auto &x : a) // Kopyalama yok sadece her döngüde bir elemana referans olacak.
{
	x.foo();
}

ARTIK BURADAN SONRA STRING SINIFINDA KULLANILAN FUNCTIONLARDAN 7. Cİ OLANA GEÇTİK.YUKARIDA


===========================================================================================================
===========================================================================================================


RANGE OLMANIN KOŞULU
--------------------
[a,b) a ve b konum belirtecek. a yı sürekli artırdığımızda belirli bir noktada bunların eşit olması gerekiyor.

int a[] = {1,2,3,4,5};
a başlangıç konumu
a+5 dizinin bittiği yerin adresi.SON ELEMANIN ADRESİ DEĞİL.C DEN GELEN OLAY

func(a,a+5); // a dahil, a+5 dahil değildi zaten.UB de oluşmaz.
func(a+1,a+3); // 2 ve 3 ü kapsar

STL Containerlarının bazı member functionları ve global functionlar range için bize başlangıç ve son konumu veriyorlar.
vector<int> ivec{2,4,6,7};

ivec.begin(); // containerdaki ilk öğenin konumunu gönderiyor.
ivec.end(); // sondan bir sonraki adresi yani bittiği yerin konumunu döndürür.

Stringde bir container olduğundan begin ve end geçerli.
string str{"Alican"};
str.begin(), str.end()

Modern C++ ta global begin ve global end geldi.
begin(str)   end(str) // burada da ADL var.String türünden bir isim argüman olarak verilmiş.
						// end ve beginde aynı namespace içinde aranıp bulundu

global nesneler diziler içinde kullanılabilir.diziler sınıf olmadığından member functionu yok.
global functionlar kullanılır diziler için.

int a[] = {1,4,2,5,6,7,4,3};

sort(a,a+sizeof(a)/sizeof(*a)); //Bunu kullanmak yerine
sort(begin(a),end(a)); // bunu kullanabiliriz.

for(val : a)
{
	cout << val<< " ";
}

Hoca daha faydalı olduğunu düşündüğü global functionları kullanıyor. Burası gri alan.

--------------------------------------------------------------------------------------

Bazı işleri member functionlar ile.
Bazı işleri global string header functionlar ile
Bazı işleride argoritma global functionları ile yapacağız.

#include <algorithm> ile include edilir.
algoritmalar c++20 öncesinde range ile çalışıyorlar.
En sık kullanılanlardan biri sort algoritması.

int main()
{
	using namespace std;

	string str{"alican"};
	cout << str << "\n";
	
	sort(str.begin(),str.end())
	cout << str << "\n";
}


MOLA

===============================================================================================================================
===============================================================================================================================
===============================================================================================================================
===============================================================================================================================

İLK OLARAK CONSTRUCTORLAR İLE BAŞLIYORUZ.
-----------------------------------------

Yazdırma kodu
void print(const std::string &str)
{
	std::cout << "[" << str.length() << "]  [" << str << "]\n";
}


1 - Default Constructor
-----------------------
string s; // default Ctor.Uzunluğu 0.
string s{}; // default Ctor.Uzunluğu 0.

2 - Cstring Parametreli Constructor
-----------------------------------

using namespace std;
char str[] = "Recep Akman";
string s{"Mustafa"};
string str1{ s };
print(str1);


3 - Copy Constructor
--------------------
string s1{"Mustafa Aksu"};
auto s2 = s1; copy ctor
auto s3(s1); copy ctor

move ctor ile yaparsak
using namespace std;
string s1{ "Ali" };
string s2{ move(s1) }; //move ctor
cout << s2;


4 - Data Constructor
---------------------
using namespace std;
char str[] = "NecatiErgin";
string s{ str,5 };
print(s); //Necat

using namespace std;
char str[] = "NecatiErgin";
string s{ str + 6,3 }; // string s{ str + 6,30 }; 30 olunca UB. 
print(s); //Erg


5 - Range Constructor
---------------------
using namespace std;
char str[] = "NecatiErgin";
string s{ str + 3 , str + 7}; // 2. verilen konum dahil değildi.
print(s); //[atiE]

list<char> ile başlayan örneği yazmadım.


6 - Fill Constructor
--------------------
using namespace std;

size_t n;
std::cout << "Kac karakter : ";
cin >> n;

string str(n, '*'); // n tane * karakteri  
print(str); Kac karakter : 32 		[32][********************************]


string str{65, '*'}; // init list ile yapsaydım 65*
string str(65, '*'); // init list ile yapsaydım 65 tane * yazar.

NOT: Yazının herhangibir karakteri '\0' olabilir. C deki gibi değil artık.
string s(20,'\0'); 20 adet null char olabilir.


7 - Substring Constructor
-------------------------

using namespace std;
string name{ "Dogus Ural" };
print(name); // [Dogus Ural]

string str{ name,3 };
print(str); // [us Ural]


using namespace std;
string name{ "Dogus Ural" };
print(name); // [Dogus Ural]

string str{ name,3,2 }; //argümana dikkat
print(str); // [us]

---------------------------------------------------------------------------------
---------------------------------------------------------------------------------
---------------------------------------------------------------------------------

Parametresi char olan bir ctor yok
string a('A'); SENTAKS HATASI

Yapmanın yolları
string str{'A'}; // parantezlerin türüne dikkat.
string str{"A"};
string str(1,'A');

atama operator functionunda char parametreli var, ama constructorda yok.
string a('A'); bunun olmamasından bahsediyoruz.

CONSTRUCTOR GRUBU BİTTİ.


==========================================================================================================
==========================================================================================================

ÖNEMLİ ÜYE FONKSİYONLAR 

begin ve end 
Begin functionları containerdaki ilk öğenin konumunu verir. end ise en sonun bir sonrasındaki olmayan öğe konum unu verir.
begin ve end in oluştrudduğu range i geçersek, containerdaki öğelerin tamamını geçmiş olurum.

Burada begin ve endi i herhangibir STL algoritmasına argüman olarak geçilebilir.

cout << "Bir yazi girin";
getline(cin,str);
count(begin(str),end(begin),'a'); // Bu range de 'a' dan kaç tane var. count algoritmadan gelen global bir func şablonu.
ankara dersek mesela 3 verir.

crbegin ler falan template lerde görülecek

----------------------------------------------------------------------------

Reserve
-------
Reserve sadece capacity yi değiştiriyor. Size değil.
Mantıklı olanda bu.

string str;
str.reserve(2000); // en az 2000 karakterlik yer allocate et.Implementation defined olan ise tam 2000 değil. en az 2000 reserve eder compiler
cout << str.size(); // 0
cout << str.capacity(); //2015


Reserve i capacity den daha küçük değerle çağırmak non-binding shrink request.Yani derleyici bunu yerine getirmek zorunda değil.
Fazla olan kapasiteyi küçültmek İmplementation defined ve derleyiciler tipik olarak bunu dikkate almıyor.

----------------------------------------------------------------------------

Resize
------
Resize ise size ı artırıyor.

string str(20,'a');
std::cout << "str.size() = "<< str.size() << "\n"; //20
str.resize(40); //string size 20 den 40 a çıkar.yeni size oluşturacak kadar burada null char eklenecek
std::cout << "str.size() = "<< str.size() << "\n";// 40

----------------------------------------------------------------------------

Size artırıp sonuna karakter ekleme

string str(20,'a');
std::cout << "str.size() = "<< str.size() << "\n"; //20
str.resize(40,'X'); //string size 20 den 40 a çıkar.Sonuna X ler ekler.
std::cout << "str.size() = "<< str.size() << "\n";// 40
std::cout << "str.capacity = " << str.capacity() << "\n";// 47

----------------------------------------------------------------------------

const char * türünden string türüne otomatik dönüşüm var.
Ama string ten const char * a otomatik dönüşüm yok

using namespace std;
string s{"Necati"};
print(s);
s = "husamettin";
print(s); // husamettin oldu

----------------------------------------------------------------------------

using namespace std;
strint s{"Ahmet Aksoy"};
strlen(s); // burası hata. cstring istenen yerde string kullanılamaz.

----------------------------------------------------------------------------

c_str
-----
const char *

bunu yapmaya yönelik doğrudan bir araç yani func var.
s.c_str(); // dinamik bellek alanında tutulan dizinin adresini verecek ve sonunda '\0' olacak şekilde olacak bir yazı adresi verecek.
strlen(s.c_str()); // çok sık kullanılıyor c_str
cout << strlen(s.c_str()) << "\n";

----------------------------------------------------------------------------

using namespace std;
strint s{"Ahmet Aksoy"};
const char *p = s.c_str(); // yazı başka yere taşınırsa pointer dangling hale gelecek.Dikkatli olmak lazım.
puts(p);
s+="buraya geldi bugun";
cout << s << "\n";
puts(s); // tanımsız davranış.ÇÜNKÜ REALLOCATİON OLDU.

----------------------------------------------------------------------------

Data
----

c_str den farkı o const char * dı. ama stringin kendisi const char* ise const char * döndürür.
Sınıfın data functionu dinamik bellek alanının adresini veriyor.Bu bir çok containerdaki ortak function.

using namespace std;
string str{"Kaya"};
char *p = str.data();
*p = 'M';
print(str); // Maya oldu. Dİkkat edilmesi gereken durum burada yazı adresi değişmemeli yoksa UB oluşur.

----------------------------------------------------------------------------

[] operator func
----------------
using namespace std;
string str{"Kaya"};
str[0]; //yazının ilk karakterini referans semaniği ile verir


------------------------

TOPLU HALDE YAZIYORUM.HEPSİ OLMAYABİLİR

string str{"nuri"};

//str.c_str(); // const char *.  dinamik bellek alanında tutulan dizinin adresini verecek ve sonunda '\0' olacak şekilde olacak bir yazı adresi verecek.
//str.data(); // char * ama string in kendisi const olsaydı return değeri const char * olacaktı
//str[0]; // yazının ilk karakterini verecek referans semantiği ile ve adresini alırsak başlangıç adresi alınmış olur.
//str.begin(); //containerdaki ilk öğenin konumunu verecek. bunu *str.begin(); ilk elemana ref semantiği ile erişir.
//&*str.begin(); ilk elemanın adresi.
//str.end(); // bittiği yerin adresi.
//str.resize(); // string içindeki yazının uzunluğunu artırır.karakter verilmezse \0 ile verirse, verilen karakter ile doldurur.
//str.reserve(); // dizi capacity allocate eder.

===============================================================================================================================
===============================================================================================================================
===============================================================================================================================


YAZININ KARAKTERLERİNE ERİŞMEK VE YAZIYI DOLAŞMAK
-------------------------------------------------

using namespace std;
string str{"Cumhuriyet"};

1. köşeli paranter operator func ile
for(size_i = 0; i < str.size();++i)
{
	cout << str[i] << " ";
}

string const değilse yazıda bu şekilde değiştirilir.
str[0] = A;
str[1] = B;

-----------------------------------------------------------

Aşağıdaki gibi yapılabilir
for(auto iter = str.begin(); iter != str.end(); iter++)
{
	cout << *iter<< " ";
}

-----------------------------------------------------------

Aynı şekilde range base for loopta kullanılabilir.
for(char c: str ) // auto da kullılabilirdi.
{
	cout << c;
}

-----------------------------------------------------------

Aşağıdaki örnek önemli
for(auto c: str ) // Öğeler sınıf türdense copy ctor çağrlacak ayrıca
{
	c = 'A'; // değiştirir mi ? Hayır. C yerel deişken. Referans decleratörü olmalıydı
}

for(auto &c: str )
{
	c = 'A'; // değiştirir mi ? Evet.Çünkü yazıyı temsil eden referans decleratörü var.
}

NOT: stringe geçersiz index geçilmesi tanımsız davranış.Exception throw etmiyor.
hatayı yakalayamayız çünkü exception throw etmiyor.Ub çünkü.
hoca try catch yazdı. Gerek görmedim yazmaya

-----------------------------------------------------------

At
---

[] ile aynı işi yapıyor. İndexin geçersiz olması durumunda standart library nin out of range türünden exception throw ediyor.


===============================================================================================================================
===============================================================================================================================
===============================================================================================================================
===============================================================================================================================

Arama Fonksiyonları
Set Fonksiyonları  - Insert/Erase Fonksiyonları
-----------------------------------------------

Karşılaştırma İşlemleri
-----------------------

string s1{"ali"};
string s1{"can"};

s1 > s2;
s1 < s2;
s1 == s2; Hepsi Global func. operator==(s1,s2); Aynı şey

NOT : C++20 de treeway comparasion eklendi.

Buradaki kıyaslama Lexicographical

if(s1 == "ali") // string ile char * veya const char * kıyaslanabilir.

s.compare() bu strcmp gibi çalışıyor.s1 büyükse pozitif, küçükse negatif, eşitse 0 döndürecek.

------------------------------------------------------------------------------------------------

Yazının Büyütülme/Ekleme İşlemleri
-----------------------------------

Sequence containerların front isimli fonksiyonu containerdaki ilk öğeye referans döndürürler.
back ise containerdaki son öğeye referans döndürürler.begin containerdaki ilk öğenin konumunu
end ise son öğenin konumunu gönderir. Referans demiyorum dikkat et.Konum diyorum.

using namespace std;
string str{"necati"};
str.front() = 'X'; // ilk karkater X yapıldı. yazı boş değilse
str.back() = 'W'; // son karkater W yapıldı.yazı boş değilse


YAZI BOS DEGILSE HEPSİ YAZININ SON KARAKTERİNE REFERANS SEMANTİĞİ İLE ERŞMEMİZİ SAĞLAR
--------------------------------------------------------------------------------------
str[str.size() -1 ] 
str.at(str.size() - 1) 
str.back(); 
*(str.end() -1 ); // bittiği yerden 1 çıkar dereference et. son eleman
*str.rbegin(); // son adresi vereiyor rbegin. dereference et.


------------------------------------------------------------------------------------------------

PUSHBACK fonksiyonu vector liste stringde ... sondan tek bir öğe ekleyen fonksiyondur.
string str{"ali"};
print(str);
str.push_back('c');
print(str);
str.push_back('a');
print(str);
str.push_back('n');


Sınıfın += fonksiyonuyla yazının sonuna ekleme yapılabilir.
bunun overloadları var.

string str{"ali"};
string str2{"nuri"};
print(str);

str =+ 'x';
print(str);

str =+ "345";
print(str);

str += str2;
print(str);

str += {'A','B','C'};
print(str);

------------------------------------------------------------------------------------------------

INSERT FONKSİYONLARI
--------------------

Ekleme ve silme işlemleri için string sınıfında 2 ayrı interface var.
biri containerlardan gelen interface
	buradaki ekleme ve silme iterator ile çalışıyor.

String sınıfının kendi ekleme silme fonksiyonu var
	Bunların parametresi index

İndex parametreli overloadlar bir index istiyor. Birde ne ekleneceğini istiyor.
Birden fazla overloadları var.

NOT : İNDEX PARAMETRELİ İNSERT FONKSİYONLARI *THIS DÖNDÜRÜR.

using namespace std;
string str{"nuri"};
str.insert(0, "ayse"); //0 indexine bu cstringi insert etti. 2 geçseydik 2 ye insert edecekti.
print(str);

-------------------------------------------------------------------

str.insert(0,10,'a'); //0 indexine 10 adet a karakteri ekleyecek.

-------------------------------------------------------------------
using namespace std;
string str{"nuri"};
string name{"Mustafa"};
print(str);
str.insert(0,name); // nuriye mustafayı ekledi 0. indexten.
print(str);

-------------------------------------------------------------------

using namespace std;
string str{"nuri"};
string name{"Mustafa"};
print(str);
str.insert(0,name,4); // nuriye mustafayı 4 nolu indisinden sonraki kısmını insert edecek.
print(str); //afanuri yazacak yani.

-------------------------------------------------------------------

using namespace std;
string str{"nuri"};
string name{"Mustafa"};
print(str);
str.insert(0,name,4,1); // nuriye mustafayı 4 nolu indisinden sonra 1 karakter insert edecek.
print(str); //anuri yazacak 

-------------------------------------------------------------------

using namespace std;
string str{"nuri"};
string name{"Mustafa"};

str.insert(0,name). // insert funclar *this çevirdiği için . dan sonra birsürü func görülür.fluent api deniyor

-------------------------------------------------------------------

MOLA

============================================================================================================
============================================================================================================
============================================================================================================
============================================================================================================

Jossutis in kitabının 667. sayfasından devam ediyor.
İndex interface inden iterator interface ine geçiyoruz.

string str{ "yunusemre" };
string s{ "orhan" };

print(str);
str.insert(str.begin(),'!'); //1. parametreye artık index değil iterator vereceğiz.tablodan neler yapılabildiğine baktık zaten
print(str); //!yunusemre

str.insert(str.begin(), {'q','u','w'}); // init list
print(str); 

str.insert(str.begin(), 10, 'A'); // fill. 10 adet a
print(str); 

str.insert(str.begin(), s.begin(),s.end()); // fill. s range i içindekileri insert ettik.
print(str);

--------------------------------------

APPEND
------

using namespace std;
string str{ "yunusemre" };
string name{ "veli" };

str.append('A'); //append sadece burada hata veriyor.
str.append(5,'A');
str.append("ali");
str.append(name,5); // 5. indexten sonrasını ekliyor
str.append(name,0,5); // name in 0. indexinden 5 karakter ekleyecek.


--------------------------------------

ASSIGN
------

Sadece char parametreli assign yok. Hepsi tabloda var.resource içersine koydum table.jpg yi

using namespace std;
string str{ "yunusemre" };

str.assign("ali");
print(str); // yunusemre gitti.ali oldu :D

const char *p = "0123456789";
str.assign(p,3); // 012. p den başlayarak 3 karakter. daha önce 3 indexli char dan sonra kopyala falan gibi şeyler vardı. Karışabilir.
str.assign(p+3,5); // 34567
str.assign(p+2,p+7); // 234567

------------------------------------------------------

Karşılaştırma Operator Functionlarına bakalım
---------------------------------------------

Tablodan bakıldı...


------------------------------------------------------

Silme Fonksiyonları
-------------------

ERASE
------

Hem index hemde iter interface i var.
İndex interface çok kolay.

using namespace std;
string str{ "yunusemre" };

str.erase(3,4); // 3 indexinden başlayıp 4 karakter silecek. yunre yazar
str.erase(0,1); // yazının ilk karakterini sildik.

EN Tipik HATA
str.erase(3); // bu indexten başlayıp geriye kalan hepsini siler.
str.erase(0); // Tüm yazıyı siler.
str.erase(); // birinci parametre 0, ikincisi npos. TÜm karakterleri siler.

str.erase(str.size() - 1); // son karakteri siler.
str.pop_back();  // yine son karakteri siler.


-----------------------------------------------------------------------------

Birde İterator İnterface i ile silmek var.
Bu bütün containerlar için ortak. array hariç

a - iterator alan  bir silme func var. İterator konumundakini siliyor.
b - range alan silme func var. Bu iterator range dekileri siliyor.

using namespace std;
string str{ "MAJID" };
print(str);

str.erase(str.begin()); // ilk karakteri silecek. İndexte indexten sonrasını silerdi.
print(str);

str.erase(str.begin + 1, str.end() - 1); // yazının 2. 3. 4. karakterlerini siler. MD yazar.
print(str);

--------------------------------------

Mülakat sorusu. Stringin içindeki tüm karakterleri sil? ama tek değil. kaç farklı şekilde yapabilirsen?

Containerların clear functionları containerdaki tüm öğeleri siler. Array hariç tüm containerlar için geçerli.
str.clear();

str.erase();
str.erase(0);
str.erase(0,std::npos);

str.erase(str.begin(),str.end());
str = "";
str = {};

str.assign("");
str.assign({});

str = string{};

Daha yazılabilir.

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

NOT : STL DE ITERATOR INTERFACE I ILE EKLEME VEYA SILME YAPAN FONKSIYONLAR ITERATOR DÖNDÜRÜRLER !
	  EKLEME YAPAN FONKSIYONLAR EKLENMIŞ ILK ÖĞENIN KONUMUNU ITERATOR OLARAK ÖDNDÜRÜRLER
	  SILME YAPAN FONKSIYONLAR SILINEN SON ÖĞEDEN SONRAKI ÖĞENIN KONUMUNU ITERATOR DÖNDÜRÜRLER.

	  INDEX ILE BUNLAR YAPILINCA RETURN DEĞERI *THIS IDI.

=================================================================================================================

ARAMA FONSİYONLARI
------------------

Find
----

İçinde sürekli bir find kelimesi geçiyor.
Hepsinin return değeri bir index. Bulunamazsa npos dönüyor.

string str;
stc cout << "yazi girin";
getline(cin,str); //cin >> kullanırsak o bışluğa gelince almıyor. boşluk seperator görevi görüyor. getline tün yazıyı \n a kadar alır.

print(str);

str.find('a'); // ilk argüman hep aranacak varlık.Yazının başından itibaren arar.
Dikkat : ASlında bu func ın 2. parametresi var. O index deffault arg olarak 0 değerini alıyor.

auto idx = str.find(a,5); // Artık arama 5 nolu indexten sonra başlayacak.

if(auto idx = str.find(a,5); idx != string::npos) // kahramanmaraş girince 6 verir çünkü 5 ten sonra aramaya başlayacak.diğer varyasyonlar denenebilir.
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}

-----------------------------------------------------------------------------	

YAZI IÇINDE YAZI ARAMA

string A{"ali"};

if(auto idx = str.find(A); idx != string::npos) // mustafaalihakan girince. Burada ali nin olduğu indexi verir.str.find(A,3) te denebilirdi
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}

-----------------------------------------------------

find_first_of
-------------

str.find_first_of("aeuoi"); // strpbrk ya benziyor. string te geçilebilir. bunlardan herhangibiri bulunduğunda döndürecek.

str.find_last_of(s); // str içinde s yazısının karakterlerinden biri olan son karakteri arıyor.
str.find_last_of("0132456789"); // str içinde 0123456789 lerden hangisi yazıda en son bulunduysa o


if(auto idx = str.find_first_of("0123456789"); idx != string::npos) // aliveli4587huseyin gir. index verir: 7
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}

if(auto idx = str.find_last_of("0123456789"); idx != string::npos) // aliveli4587huseyin gir. index verir: 10
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}



İÇINDE KARAKTER GEÇMEYEN ILK INDEX
if(auto idx = str.find_first_not_of("0123456789"); idx != string::npos) // 145abc789  girilirse a nın indexi olan 3 döndürür.
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}


İÇINDE KARAKTER GEÇMEYEN SONDAN ILK INDEX
if(auto idx = str.find_first_not_of("0123456789"); idx != string::npos) // asdbd789456  girilirse c nin karakteri olan tersten d nin indexini bulur
{
	std::cout << "bulundu idx : " << idx << "\n";
}
else
{
	std::cout << "Bulunamadi\n";
}



RFIND
-----

Aramaya baştan sona yapıyor.

string str{"velialiasd213"};

str.rfind("ali");


*/

#include <iostream>
#include <string>
#include <limits>

void print(const std::string &str)
{
	std::cout << "[" << str.length() << "]  [" << str << "]\n";
}

int main()
{
	
}
