/*

Lambda ifadelerinde kaldık. C++ ın en önemli araçlarından biri. Modern C++ ta dile eklendi.

Öyle bir ifadeki, Derleyici bu ifadenin karşılığında, bu ifadenin bulunduğu yerde bir sınıf tanımlıyor ve bu sınıfa function cağrı operatör functionunu yazıyor,
dolayısıyla derleyicinin oluşturduğu sınıf bir functor class ve bu lambda ifadesinin bulunduğu yerde ilgili ifadeyi bir geçici nesneye dönüştürüyor.

Lambda varsa sınıf türünden geçici nesne oluşturuyoruz. Değer kategorisi PR value expression.

Bir ifadeye argüman olarak göndeirlebilir, yada ifadenin bulunduğu yerde func call operator func ını çağırabiliriz veya auto specifier ile isim verilebilir.

C++ 20 standartlarına kadar default ctor ve copy assignment delete edilmişiti.
C++ 20 den sonra stateless/captureless ise bunlarda artık mevcut. yani copy assignment ve default ctor var.Delete edilmemiş.

En çok kullanılan yer bir algotirmaya argüman olarak gönderilmesi.

[] -> bu olamzsa olmaz bileşen
() -> olabilirde olmayabilirde. Derleyicinin yazdığı sınıfın func çağrı operator func ının parantezi. BU parantezin mecburi olmadığı durumlar aşağıda
	  Eğer trailing return type, mutable, noexcept, constexpr, ve C++20 ile gelen template sentaksını kullanmazsak, ve functionun parametre değişkeni yoksa
	  bu parantezi kullanmak mecburi değil. Ama bir veya daha çok parametresi varsa ve bu belirteçlerden herhangibiri varsa parantez zorunlu.

				constexpr	
[]<typename>()			mutable		{} 
				noexcept
				->int

{} -> Derleyicinin yazacağı functionun ana bloğunu temsil ediyor.


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DERLEYICININ LAMBDA IFADELERINDE YAZDIĞI SINIFLAR BIRBIRINDEN FARKLI SINIFLAR / DISTINCT SINIFLAR

int main()
{
	auto x = []() {};
	auto y = []() {}; // Bu ile yukarıdaki farklı sınıf türden nesneler.
	
	std::cout <<typeid(x).name()<< "\n";
	std::cout <<typeid(y).name()<< "\n"; //farklı türler yazıyor.
}

x = y; // bu C++20 bile olsa sentaks hatası çünkü türleri farklı.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PARANTEZIN IÇI BOŞSA YAZILMIYOR

int main()
{
	auto x = [](){
		
	};
}

Normalde closure objecttir nesne tipide closure type tır, ama insanlar lambda function diyorlar.
Teknik olarak tam doğru değil ama pratik olarak doğru kabul edilebilir.

C/C++ de nested function yok.Gcc nin extensionu var bu konuda ama standart C++ ta yok nested function.
Lambda ifadeleri nested function olarak düşünülebilir.Bir functiona argüman olarak func göndermek istiyoruz, doğrudan functionu kodu yazdığımız yerde local düzeyde
tanımlamamız mümkün. Bu bir func değil tabi ama func olarak kullanabiliyoruz.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Derleyicinin yazdığı türün return değeri deduction yoluyla elde ediliyor.
return değeri auto ile belirleniyor gibi düşünülebilir

[](int x, double y){return x * y;} // .Dİkkat çağrı yapılmadı henüz bu ifadeye.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

En son [] yani capture kısmındaydık.
[] içine bir bazı ifadeler yazdığımızda aslında biz lambda ifadesi içinde functionun anabloğu içinde bazı değişkenleri kullanma hakkı elde ediyoruz.
Görünür durumdaki static ömürlü değişkenler için bir yakalamaya gerek yok. Static ömürlü değişkeni yakalamaya çalışırsak sentaks hatası

Geçen derste örnekleri verildi.

int main()
{
	int x = 10;

	[x]() { cout << "Hello\n";}
	[cout]() { cout << "Hello\n";} // SENTAKS HATASI
}

Otomatik ömürlü değişkenleri lambda ifadesi içinde kullanmanın yolu [] içine yazmak.
içine x yazınca, derleyici bu sınıf için oluşturduğu ctorda, sınıfa auto type deduction ile bu türden bir veri elemanı koyup,[] içinde ismini verdiğimiz değişkenle 
initialize ediyor.

DIKKAT : LAMBDA IÇINDE X I KULLANDIĞIMIZ ZAMAN, MAIN IÇINDEKI X I DEĞIL, O X TEN KOPYALANMIŞ SINIFIN VERI ELEMANI OLAN X I KULLANMIŞ OLUYORUZ.
LAMBDA IÇIN COMPILERIN YAZDIĞI MEMBER FUNC HERZAMAN CONST MEMBER FUNC.

int main()
{
	int x = 10;
	[x](){x += 10;} // SENTAKS HATASI
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA MUTABLE KEYWORD DEVREYE GIRIYOR.
Burada mutable lambda için yazılan member func ı const olmaktan çıkarıyor.Nonconst member func içinden sınıfın veri elemanı değiştirilebilir.

int main()
{
	int x = 10;
	[x]()mutable{x+= 20; } //GEÇERLİ.
}

Önceki mutable gibi değil.Buradaki mutable derleyiciye func ı const olarak yazdırmıyor.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	mt19937 eng;
	[eng]() {eng();} //SENTAKS HATASI OLUR. Çünkü bunun çağrılmasını sağlayacak olan func call operator functionu const member func, ama eng() ifadesi ise const değil
}						// Bunu yapmak istiyorsam const member func olmaktan çıkarmam gerekiyor.	

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA IÇERISINDE DOĞRUDAN THIS POINTER KULANILAMIYOR. THIS POINTER CAPTURE EDILEBILIYOR GÖRÜLECEK.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	int x = 10;
	auto f = [x](int a)mutable {x *=15}; // henüz çağrılmadı ifade.Sonuna (50) yazsaydım çağırmış olurdum veya aşağıdaki gibi.
	
	f(50);
	
	std::cout << "x = " << x << "\n"; // x değişmedi.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ELEMANI DEĞİŞTİRMEM GEREKİRSE REFERANS KULLANMALIYIM.
En çok karıştırılan yerlerden biri.

class Myclass
{
public:
	Myclass(int &r) : mr {r}{ };
	void func()
	{
		mr *= 10; // mr kime bağlandıysa onu değiştirecek
	}

private:
	int &mr;
}

int main()
{
	int ival = 60;
	Myclass mx{ival};
	mx.func();
	cout << ival<<"\n"; // artık 600. Dangling referansa dikkatet.Burada yok.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDA FUNC CONST OLURSA SENTAKS HATASI DEĞIL.

class Myclass
{
public:
	Myclass(int &r) : mr {r}{ }
	void func()const
	{
		mr *= 10; // mr kime bağlandıysa onu değiştirecek.mr değişmiyor zaten bu yüzden const olsa bile member func hata yok. Pointerlar gibi.
	}

private:
	int &mr;
}

int main()
{
	int ival = 60;
	Myclass mx{ival};
	mx.func();
	cout << ival<<"\n"; // artık 600. Dangling referansa dikkatet.Burada yok.
}

Referans assembly olarak pointerdan farklı birşey değil. Bu kodu pointer gibi düşünelim, *mr , myclass(int*r) gibi...
*mp *= 10; burada sentaks hatası yok.Biz veri elemanını değiştirmedik. Onun gösterdiği nesneyi değiştirdik.

Referans semantiğinde de bir fark yok.

SORU : DERLEYICIYE YUKARIDAKI GIBI BIRŞEY YAZDIRABILIR MIYIZ.EVET CEVABI AŞAĞIDA 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CAPTURE BY REF

int main()
{
	int x = 20;
	[x] // CAPTURE BY COPY
	[&x] // CAPTURE BY REF.burada adres operatörü anlamında değil x i referans semantiği ile yakala demek.
  		 // yazdığın sınıfı referansla başlat ve onu x e bağla.

	auto f = [&x](int a){x *= a;}; // DİKKAT ÇOK ÖNEMLİ. MUTABLE DEĞİL.CONST MEMBER FUNC AMA SENTAKS HATASI YOK.YUKARIDA AÇIKLANMIŞTI
	f(5); // ARTIK SENTAKS HATASI YOK 

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR
int main()
{
	string name = "dogus";

	[name]() {name += "can";} //SENTAKS HATASI
	[name]() mutable {name += "can";} //GEÇERLİ
	[&name]() {name += "can";} //GEÇERLİ YİNE. & a dikkat
	[&name]() {name.assign("can");} //GEÇERLİ
}

============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================

CAPTURE İFADELERİ SENTAKSI
--------------------------

int main()
{
	int x = 20;
	int y = 20;

	auto f = [x,y,z](int a){x *= a;}; // kopyalama yoluyla böyle capture ediliyor.
	
	auto f = [&x,&y,&z](int a){x *= a;}; // Referans yoluylada capture ediyor.
	
	auto f = [&x,&y,z](int a){x *= a;}; // Bir kısmı referans bir kısmıda kopyalama yoluyla capture ediyor.
	
	auto f = [=]() {} ; // Hepsini copy yoluyla yakala demek.
	auto f = [=](int a) {return a * (x+y+z)}; // GEÇERLİ.

	auto f = [&]() {++x;++y;++z}; // Hepsini referans semantiği ile yakala

	auto f = [=,&x]() {++x;++y;++z}; // Hepsini kopyalama yoluya ama x i referans yoluyla yakala

	auto f = [&,x]() {++x;++y;++z}; // Hepsini referans yoluyla ama x i kopyalama yoluyla yakala

	auto f = [](int a = 5){return a * 10;}; // Function default arguman alabilir.
	f(10); // çağrılabilir.

	NOT : Lambda ifadeleri C++11 de eklendi ama o zamanlar çok kısıtlıydı
	C++ 14 ve 17 de baya birşey elendi.Hoca C++17 ve C++20 ye göre anlatıyor

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HEM REFERANS YOLUYLA YAKALAYIP HEMDE DEĞIŞIKLIK OLMASIN ISTIYORUZ.
Doğrudan bir yolu yok ama ileride görülecek. Yani const & ile yakalama yok. Dolaylı bir araç var. Görülecek.

int main()
{
	string name = "dogus";

	[&name]() {name.assign("can");} //BURADAKİ DEĞİŞİKLİĞİN SENTAKS HATASI OLMASINI İSTİYORUZ YANİ.Doğrudan const & yakalama yok. Dolaylı yoldan yöntem var.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRAILING RETURN TYPE NEDIR ? GEREKLI MIDIR ?

int main()
{
	auto f = [](int x){return x * 5;}; // return değeri auto type deduction ile oluyor ama bunu istemiyoruz diyelim.
	
	Biz bunu istediğimiz biçimde veya belli tür olmasını istiyoruz.	Trailing return type kullanmak gerekiyor.

	auto x = f(12); // tür int. Double olsun istersek
}

int main()
{
	auto f = [](int x)->double {return x * 5;}; // burada double oldu return türü
	auto x = f(12);	
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRAILING RETURN TYPE MECBURI SENARYO

int main()
{
	auto f = [](int x) {
		if(x > 10)
			return x;
		else
			return 1.5*x;
	}						
}

// SENTAKS HATASI. ilk return türü int .İkincisi double
// ifadenin türü aynı olmalı.Bu durumda trailing tet kulanarak aşabiliriz bunu.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRAILING RETURN TYPE EKLENDİ

Açıkça return türünü biz belirledik.Birden fazla return deyemi var ve türleri farklı. Buda zaten sentaks hatası.Bu şekilde aşılabilir.

int main()
{
	auto f = [](int x) -> double {
		if(x > 10)
			return x;
		else
			return 1.5*x; 
	}						
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA IFADELERI EĞER STATELESS ISE DOĞRUDAN ILGILI FUNC IN ADRESI TÜRÜNE OTOMATIK DÖNÜŞÜM VAR

int main()
{
	[](int x) {return x * 5;} // bir func olsaydı int(*)(int)
	
	int(*fptr)(int) = [](int x) {return x * 5;} // bir func olsaydo int(*)(int) , ama stateless olacak.
												
	int(*fptr)(int) = [5](int x) {return x * 5;} // SENTAKS HATASI.Stateless değil. Değer Capture edilmiş
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void func(int(*p)(int))
{
}

int tmain()
{
	func([](int x){ return x * 5;}); //GEÇERLİ.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İLGINÇ BIR IDIYOM, POZITIF LAMBDA IDIYOM.

int tmain()
{
	auto f = [](int x){ return x * 5;}; // f burada closure type

	auto g = +[](auto x){return x * 5;}; // IDE sentaks hatası veriyor ama değil.
										 // pozitif lambda idiyom. f in türü burada function pointer type
										 // + burada bir türdönüşümüne neden oluyor.Burası bir function adresine dönüşüyor.


	std::cout << typeid(f).name()<< "\n"; // closure type
	std::cout << typeid(g).name()<< "\n"; // func pointer
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Yukarıdaki TEMPLATELERDE ÖNEM KAZANIYOR.

İstersek T yi func pointer type yaparız istersekte closure type yapabiliriz.

tempalte <typename T>
void func(T x)
{

}

int main()
{
	func([](int x){return x * 5;}); // Bu bir closure type
	func(+[](int x){return x * 5;}); // Function pointer type
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOEXCEPT DURUMU

				constexpr
[]<typename>()	mutable		{}
				noexcept
				->int

Noexcept keyword kullanılırsa nasıl bir func noexcept belirleyici ile noexcept hale getiriyorsak, lambdalarda da bu şekilde kullanabiliriz.
Noexcept yazılmazsa default olarak noexcept değil. noexcept yazarsakta noexcept garantisi veriyor.Veya koşulada bağlanabilir



----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CONSTEXPR DURUMU

lambda nın member func ın constexpr olduğunu anlatıyor.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto f = [](int a){return a + 5;};
	constexpr auto x = f(4); //SENTAKS HATASI YOK.
}

STANDARTLARDA SENTAKS HATASIYDI
LAMBDA IFADELERI STATELESS OLDUĞUNDA CONSTEXPR FUNC OLMA KOŞULLARINI EZMIYORSA IFADE DEFAULT OLARAK CONSTEXPR KABUL EDILIYOR !!!!!!!!!!!!

CONSTEXPR FUNCTION OLMA KOŞULLARI
---------------------------------
- Func parametreleri literal type olacak.
- Func return değeri türü literal type olacak.
- Func anablok içinde literal type olmayan herhangibir türden değişken olmayacak.
- Static ömürlü değişken tanımlanmayacak


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

int main()
{
	int ival = 45;
	auto f = [ival](int a){return a + ival;}; // Dikkat !!! constexpr lik bozuldu. Çünkü ival capture edildi
	constexpr auto x = f(4); //SETNAKS HATASI ARTIK.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int ival = 45;
	auto f = [ival](int a)constexpr {return a + ival;}; // Dikkat!!! Bu durumda bu functionun herhangibir şekilde constexpr olmasını engelleyen senaryoda 
														 // SENTAKS HATASI olacak.static yazınca mesela sentaks hatası içeride
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : BURADA EN ÇOK MUTABLE VE TRAILING RETURN TYPE KULLANILIYOR.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GENERALIZED LAMBDA EXPRESSION VE LAMBDA INIT CAPTURE

Bu araçlar daha sonradan eklendi ve önemli. Derleyicinin kodu template kod olarak yazmasını sağlayabiliriz.

class Myclass {
public:
	tempalte <typename T>
	void func(T x);
};

int main()
{
	Myclass m;
	m.func(12);
	m.func(3.4);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FUNCTION CALL OPERATOR FUNCTIONUDA BIR FUNC ŞABLONU OLABILIRDI

class Myclass {
public:
	template <typename T>
	int operator()(T x);
};

int main()
{
	Myclass m;
	m(1); // her çağrı için ayrı func çağrılır
	m(3.4);
	m("a");
}

DERLEYICININDE LAMBDA IFADESI KARŞILIĞI YAZACAĞI FUNC CALL OPERATOR FUNCTIONUNU BIR TEMPLATE OLARAK YAZDIRMAMIZ MÜMKÜN
PARAMETRE DEĞİŞKENİ İÇİN AUTO KULLANMAMIZ GEREKİYOR.BUNA GENERALIZED LAMBDA EXPRESSION DENIYOR.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GENERALIZED LAMBDA EXPRESSION ÖRNEĞİ.

int main()
{
	auto f = [](auto x){return x * x;};
	auto a = f(12); // Derleyici yazacağı func parametresi int türden ve return değeride int olacak.
	auto a = f(4.5); // double olarak çağırırsak, derleyicinin yazacağı func ın parametresi double olacak, return değeride double olacak.

	auto f = [](auto &x){return x * x;}; //LEGAL
	auto f = [](const auto &x){return x * x;}; //LEGAL
	auto f = [](auto &&x){	// LEGAL HATTA PERFECT FORWARDINGTE UYGULANABİLİR.AŞAĞIDA UYGULANDI
		return x * x;
	}; 

	auto f [](auto&&x){
		func(forward<decltype(x)>(x)); 
	};
}

BUNLARA GENERALIZED LAMBDA EXPRESSION DENIYOR.
Faydaları var. 
Aynı isme sahip değişkeni kullanarak farklı funcları çağırabiliriz.
Birde bizi yazma zahmetinden kurtarabiliyor.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BURADA GÖRMEDİKLERİMİZ VAR.

#include <algorithm>
#include <vector>

int main()
{
	vector<pair<int,double>> vec; // bunun rangeinde algoritma çalıştırmak istiyoruz.

	//count_if(vec.begin(), vec.end(),[](pair<int,double> x) { }) yazabiliriz.
	count_if(vec.begin(), vec.end(),[](const auto &x) { }) // bunu tercih ettik. daha karmaşık senaryo olsaydı daha zor olurdu çünkü.
	
	//KARMAŞIK OLSA
	vector<pair<int>::iterator, vector<int>::iterator>> vec;
	count_if(begin(vec),end(vec),[](auto){}) // diğer avantajıda vec te değişiklik yapınca auto kısmını değiştirmek zorunda kalmayacağız.


}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto f = [](auto x, auto y){return x + y;}; // x ve y nin türü aynı olma koşulu yok
	f(12,4.5); // x int, y double
	
	auto f = [](auto x, decltype(x) y){return x + y;}; // ikincinin türü ilkinin türünden
	f(12,4.5); // ikicide veri kaybı olacağından uyarı verdi.


	C++20 ILE GELEN BIR ARAÇ.

	auto f = []<typename T>(T x, T y){ return x + y;}; //ileri C++ ta anlatılıyor
	f(12,5.6); //ambigiuty oluştu. tür çıkarımı yapıldığıdan trün aynı olması lazım bu örnek için
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++20 ile geldi.

int main()
{
	auto f = []<typename T>(vector <T> x, const T &t) { x.push_back(t); };
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA INIT CAPTURE
-------------------

Bazı türler var move-only types diye geçiyor.Daha görülmedi.Salt taşınabilir türler demek.Kopyalamaya kapalı ama taşımaya açık türler
ostream, thread, unique_ptr ... bunlar böyle.

int main()
{
	unique_ptr<int> uptr(new int(54));
	
	auto x = uptr; // Kopyalamaya kapalı bir sınıf. SENTAKS HATASI

	//UPTR yi capture etmek istesek
	auto f = [uptr](){}; //SENTAKS HATASI. Çünkü kopyalama yoluyla capture var.Kopyalama kapatılmış.
	auto f = [&uptr](){}; //GEÇERLİ


	//UPTR MOVE EDILIRSE.C++11 DE BU YOKTU. LAMBDA INIT CAPTURE DENIYOR.
	unique_ptr<int> uptr(new int(54));

	[up = move(uptr)]() {  // C++11 de bunu yapmanın yolu yoktu.
		auto x = *up;
	};
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKI GIBI KODLARDA YAZILABILIR

int main()
{
	int a = 19;

	auto f = [a = a + 6] (){  //Dikkat!!
		a
	};
	
	int *ptr;
	auto f = [x = *ptr] (){ }; 

	auto f = [&x = *ptr] (){ };  // buradaki x referans
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DAHA ÖNCE BÖYLE BIR HILE ILE YAPILIYORDU

class Myclass{
	void func()
	{
		[*this](){} // C++17 ile geldi

	}
	
	//yukarıdaki olmadan önce
	void func()
	{
		[star_this = *this] // Önceden böyle yapılıyordu.
	}	
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	string str(100'000,'A');
	[str = str]() {} // hata yok yine

	auto f = [str = move(str)] () {} // copy yerine taşıma semantiği kullanılmış oldu.str artık move from state. Yani move edilmiş.

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA İFADELERİNİN AVANTAJLARI
-------------------------------
- Lambda ifadeleri daha okunabilir ve daha anlaşılır bir kod oluşturuyor.

- Çağrılan fonksiyonun kodunu görmek için başka bir dosyada başka bir yere gitmek zorunda kalmıyoruz.

- Function pointerlara göre daha verimli bir kod oluşturabiliyor(INLINE EXPANSION DAN ÖTÜRÜ)

- Lambda ifadesi yazmak function nesnesi yazmaktan daha kolay, karmaşık işlev uyumlandırıcılarını yazmak zorunda kalmıyoruz

- Bir fonksiyondan return değeri olarak alabiliriz.

- Function çağrısı için bir değişken oluşturmak zorunda değiliz, lambda ifadesini yazdığımız yerde functionu çağırabiliriz.IIFE(Immediately Invoked Function Expression)

- std::function yoluyla bir başka functiona argüman olarak geçebiliriz.Genel bir call back olarak kullanabiliyoruz.

- Bir fonksiyon şablonuna argüman olarak geçebiliriz.(Algoritmalara argüman olarak geçebiliriz.)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA İFADELERİYLE İLGİLİ EN DİKKATLİ OLUNMASI GEREKEN YER

auto func(int x)
{
	return [x](int a) {return a * x;}; // return değeri böyle
}

int main()
{
	auto f = func(12);
	auto x = f(5);

	std::cout << "x = "<< x << "\n";
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
AYNI ÖRNEĞİ REFERANS YOLUYLA CAPTURE ETSEYDİM

auto func(int x)
{
	return [&x](int a) {return a * x;}; // return değeri böyle
}

int main()
{
	auto f = func(12); //bu çağrıldıktan sonra artık içerisindeki x değişkeninin hayatı bitti.
	auto x = f(5); // şuanda sınıf nesnesi, hayatı bitmiş olan x i referans tutuyor.Buradaki çağrıda bir DANGLING REFERANS KULLANILMIŞ OLACAK. UNDEFINED BEHAVIOR

	std::cout << "x = "<< x << "\n";
}


MOLA

============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================


FIND IF ÖRNEĞİ - ALGORITMALAR LAMBDALARIN EN ÇOK KULLANILDIĞI YERLERDEN BİRİ.
Yani algoritmaya lambda ifadesini argüman olarak geçmekten bahsediliyor.

#include <nutility>
#include <vector>
#include "date.h"

using namespace std;

int main()
{
	vector<string> svec;
	rfill(svec,100,rname); // bu hocanın kendi functionu
	print(svec);

	char c;
	cout << "Bir karakter girin ";
	cin>>c;

	//findif kullanılacak.Vectorde c karakteri olan ilk öğenin konumunu döndürecek.

	if(auto iter = find_if(begin(svec), end(svec),
		[c](const string &s){return s.find(c) != string::npos;}); iter != end(svec)){
		
		std::cout << "bulundu ..." << iter - svec.begin() << " indisli oge(" << *iter << ")\n";	
	}
	else
	{
		std::cout << "bulunamadi\n";	
	}
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

COUNT IF ÖRNEĞİ - BURADA KULLANILAN DATE HOCANIN VERDIĞI ÖDEV OLAN DATE. 

int main()
{
	vector <Date>dvec;
	rfill(dvec,1000,Date::random);
	//print(dvec,"\n"); // yazdırmak uzun sürüyor yorum yapıldı

	//ayın belirli günü kaç tane
	
	int mday;
	cout << "ayin kacinci gunu";
	cin>>mday;

	auto n = count_if(dvec.begin(),dvec.end(),[mday](const Date &date){ return date.month_day() == mday;})
	std::cout << n << " tane bulundu\n";
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SORT ALGORITMASI ÖRNEĞI

using namespace std;

int main()
{
	vector<string> svec;
	rfill(svec,100,rname);
	print(svec);

	sort(svec.begin(), svec.end()); // kucukten buyüğe sıralama yapar.

	//büyükten kucuğe sıralaama için
	sort(svec,begin(), svec.end(),
	[](const string s1, const string &s2) { return s1 > s2; } ); // s1<s2 yazarsak küçükten büyüğe sıralar
	print(svec);

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PREDICATE ALAN SORT
using namespace std;

int main()
{
	vector<string> svec;
	rfill(svec,100,rname);
	print(svec);


	auto f = [](const string s1, const string &s2) {
	return s1.length() < s2.length() || (s1.length() == s2.length()) && s1 < s2;}; // birinci ikinciden küçük uzunlukta veya uzunlukları eşit ama birinci ikinciden küçükse
																					// yani s1 < s2 derken asci table daki numaralarına göre. 

	sort(svec.begin(), svec.end(),f);
	print(svec);

	
	//Yukarıdaki lambdayı functionun 3. ifadesine de gönderebilirdik. Uzun görünüyor biraz.

	sort(svec.begin(), svec.end(),  [](const string s1, const string &s2) {
	return s1.length() < s2.length() || (s1.length() == s2.length()) && s1 < s2;});

	print(svec);
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using namespace std;

int main()
{
	list<int> mylist;

	rfill(mylist,100'000,Irand{0,100'000});

	int n; 
	std::cout << "kaca tam bolunenler :";
	cin>> n;

	cout << count_if(mylist.begin(), mylist.end(), [n](int x){ return x % n == 0;}) << "\n"
}

ITERATORLERE GERİ DÖNÜYORUZ.

============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================


ITERATORLER VE CONSTLUK
-----------------------

int main()
{
	vector<int> ivec{2,4,5,6,7,8};

	const vector<int>::iterator iter = iter.begin(); //Dikkat!!! const bir sınıf nesnesi değeri değiştirilemez.Low level const a karşılık gelmiyor.
	// BURADA ITERATOR CONST OLARAK NİTELENMİŞ. YANİ İTERATOR DEĞİŞEMEZ. ++ITER SENTAKS HATASI OLUR !!!!!!!!!!!!!!!
	// DAHA AŞAĞIDAKİ ÖRNEKTE İSE CONST_ITERATOR DENMİŞ. BURADA İSE *ITERATOR = 234 GİBİ BİR EŞİTLEME SENTAKS HATASI !!!!!!!!!!!!!!!!!!!
	
	++iter;// SENTAKS HATASI OLUR
	*iter = 45; //SENTAKS HATASI DEĞİL.
	
	ivec diyorki benim değerim değişmeyecek.Bir sınıf burada ivec. 	 
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NESNEYE SALT OKUMA AMAÇLI ERIŞIM ISTERSEK NE YAPACAĞIZ

++iter olmalı veya iter +2 olmalı, *iter yine olmalı

*iter = 54; BU SENTAKS HATASI OLMALI.

Low level const semantiği const keyword ile değil bir adaptör sınıfla elde edilmiş.Böyle sınıfların ismi const iterator sınıfı.
Bunlarda containerların nested type ı.

ÖR:
vectore<int>::const_iterator iter = ivec.begin();
cout << *iter << "\n";
*iter = 23; // SENTAKS HATASI OLDU ŞİMDİ.Sadece okuma amaçlı kullanılacak.
 
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 MODERN C++ ILE AŞAĞIDAKI GELDI.

 Eski C++ ta sınıfların begin ve end functionları vardı. Modern C++ auto type deduction gelmesiyle containerlara cbegin ve cend funclarıda eklendi.
 beginin return değeri vectorun<int>::iterator u ise vectorun<int>::const_iterator u.
 aynı şekilde cend de öyle

 int main()
 {
	using namespace std;

	vector<int> ivec{2,34,5,6,7,8,9};

	for(auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter)
	{
		*iter // yani sadece okuma amaçlı erişim var.
	}
 
 }

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 GLOBAL KARŞILIKLARIDA VAR.

 auto iterbeg = cbegin(ivec);
 auto iterend = cend(ivec);

 int main()
 {
	using namespace std;

	vector<int> a{2,34,5,6,7,8,9};

	for(auto iter = cbegin(a); iter != cend(a); ++iter)
	{
		std::cout << *iter << "\n";
	}
 }

 C dizilerinde memberfunc olmadığından global funclar kullanılıyor.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 ITERATÖRLERI ELEMAN OLARAK ALIP ONLARIN INTRFACE INI DEĞIŞTIREN (ELEMAN OLARAK ALARAK YADA KALITIMLA YAPABILIR.) SINIFLARA ITERATOR ADAPTÖRÜ DENIYOR
 DOlAYISIYLA CONST İTERATÖRLER ASLINDA BİR İTERATOR ADAPTÖRÜ DİYEBİLİRİZ.
 
 ===========================================================================================================================================================================
 ===========================================================================================================================================================================
 ===========================================================================================================================================================================

 STL IN COPY ALGORITMASINI YAZALIM ÖNCE

 NOT : STL algoritmalarının en az %80 i ezbere bilinmeli!!! STL algoritmasının olduğu yerde asla kendimiz onun yerine bir şey yazmamalıyız.!!!!!
	   ÖR : Kopyalama için copy algoritmasını kullanacağız, döngü deyimi yapmayacağız. 

 template <typename InIter, typename OutIter>
 OutIter Copy(InIter beg, InIter end, OutIter destbeg)
 {
	while(beg != end)
	{
		*destbeg++ = *beg++;
	}
	return destbeg;
 }

 int main()
 {
	using namespace std;
	vector<int>x{3,5,6,7,8};
	vector<int>y;

	Copy(x.begin(),x.end(), y.begin()); // UNDEFINED BEHAVIOR. Y de 5 tane öğe yok çünkü.burada x ten yazılacak öğe sayısı kadar y de yer olmalı.Exception throw ta yok.
 }										// Y de 4 öğe bile olsa UB.

 BUNU AŞAĞIDAKİ ÖRNEKTE AŞIYORUZ.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 ÖYLE BIR HILE YAPIYORUZ KI BIR ARLGORITMAYI HIÇ DEĞIŞTIRMEDEN VAROLAN NESNENIN ÜZERINE YAZMASI YERINE BIR CONTAINERA EKLEME YAPACAK ŞEKILDE ALGORITMA ÇALIŞTIRMASI MÜMKÜN

 int main()
 {
	using namespace std;
	vector<int>x{3,5,6,7,8};
	vector<int>y;

	std::cout << "y.size " << y.size() << "\n"; 
	
	Copy(x.begin(),x.end(), back_inserter(y)); //Y nin size ı arttı.
	
	std::cout << "y.size " << y.size() << "\n";

	print(y); // Gerçekten Y deki öğelerin X tekilerle aynı olduğunu göreceğiz.
 }


 BU IŞ NASIL OLUYOR.
 -------------------
 Outiter öyle bir tür olsunki destbegi * ve ++ nın operandı yapınca destbegin kendisini elde edelim.
 Yani OutIter öyle bir tür olsunki, *destbeg = destbeg veya ++destbeg = destbeg olmalı !!!
 Aynı zamanda copy asisgnment yazmamız lazım, bu atama operator func containera push_back yapacak.


 template <typename C>
 class BackInsertIterator	 
 {
 public:
	BackInsertIterator(C &c) : mc{c} { }
	BackInsertIterator& operator*() { return *this; }				// *destbeg ile destbeg aynı olması için
	BackInsertIterator& operator++() { return *this; }				// ++destbeg ile destbeg aynı olması için
	BackInsertIterator& operator++(int) { return *this; }			// destbeg++ ile destbeg aynı olması için
	BackInsertIterator& operator=(const typename C::value_type &val) // integral_constant tan hatırla. value_type tür bilgisi.C ye bağlı tür olduğundan typename geldi.
	{							        // C::value_type neden yazıldı? push edilecek değer int. C ise vector<int>. C::value_type ile int türüne
		mc.push_back(val);					// erişebildik.
		return *this;
	}
 private:
	C &mc;	// Bu sınıf türden nesne bir containerı referans tutuyor olacak. Bu sınıfın kodları mc yi kullandığında, referans yoluyla bağlanan containerı kullanmış olacak.
 }
 
 
 //Bu function template ten sonra kullanımı biraz daha kolaylaştı
 template <typename C>
 BackInsertIterator<C> BackInserter(C &x)
 {
	return BackInsertIterator<vector<int>>{x};
 }


 int main()
 {
	vector<int> x{1,3,5,7,9};
	vector<int> y;

	Copy(x.begin(), x.end(), y.begin()); // BURASI UNDEFINED BEHAVIOR OLACAKTI

	Copy(x.begin(), x.end(), BackInsertIterator<vector<int>>{y}); // TAMAMEN GEÇERLİ.

	//FUNC TEMPLATE YAZDIKTAN SONRA KOLAY KULLANIM
	Copy(x.begin(), x.end(), BackInserter(y)); 

	print(y); 
 }

 STL DE GERÇEKTEN BUNLAR VAR.BACKINSERTITERATOR ISIMLI SINIF VE BACKINSERTER ISIMLI FUNCTION VAR.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 YUKARIDAKİNİN ORİGİNALİNİ KULLANABİLİRİZ.

int main()
 {
	vector<int> x{1,3,5,7,9};
	vector<int> y; // boş olması gerekmiyor. {2,2,2} verseydik. Sonuna ekleyecketi {2,2,2,1,3,5,7,9} olacaktı.
	
	Copy(x.begin(), x.end(), back_inserter(y)); // original olanı buydu
	
	//print edilebilir.
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FRONT INSERTER ITERATOR YAPSAYDIK YUKARIDAKINI PUSH_FRONT KULLANSAYDIK BU SEFER BAŞTAN EKLEME YAPACAKTI.
VE BUDA LİBRARY DE VAR. AŞAĞI YUKARI AŞAĞIDAKİ GİBİ. HATA OLABİLİR.

template <typename C>
 class FrontInsertIterator 
 {
 public:
	FrontInsertIterator(C &c) : mc{c} { }
	FrontInsertIterator& operator*() { return *this; }				// *destbeg ile destbeg aynı olması için
	FrontInsertIterator& operator++() { return *this; }				// ++destbeg ile destbeg aynı olması için
	FrontInsertIterator& operator++(int) { return *this; }			// destbeg++ ile destbeg aynı olması için
	FrontInsertIterator& operator=(const typename C::value_type &val) // integral_constant tan hatırla. value_type tür bilgisi.C ye bağlı tür olduğundan typename geldi.
	{																 // C::value_type neden yazıldı? push edilecek değer int. C ise vector<int>. C::value_type ile int türüne
		mc.push_front(val); //DİKKAT !!!!!							 // erişebildik.
		return *this;
	}
 private:
	C &mc;	// Bu sınıf türden nesne bir containerı referans tutuyor olacak. Bu sınıfın kodları mc yi kullandığında, referans yoluyla bağlanan containerı kullanmış olacak.
 }


 //Bu function template ten sonra kullanımı biraz daha kolaylaştı
 template <typename C>
 FrontInsertIterator<C> FrontInserter(C &x)
 {
	return FrontInsertIterator<vector<int>>{x};
 }

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 INSERTER

 int main()
 {
	list<int> x{1,3,5,7,9}; // VECTORDE FRONT INSERTER YOK LİSTTE VAR !!!!
	list<int> y{2,2,2};

	copy(x.begin(),x.end(),front_inserter(y)); // LİSTTE VAR VECTORDE YOK 

	copy(x.begin(),x.end(),back_inserter(y)); // LİST VE VECTORDE VAR

	auto iter = y.begin();
	++iter;

	copy(x.begin(),x.end(),inserter(y,iter)); // LİST VE VECTORDE VAR.

	print(y);
 }


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SONUÇ : BACK INSERTER, SONDAN EKLEME YAPIYOR
		FRONT INSERTER, BAŞTAN EKLEME YAPIYOR(LİSTTE VAR VECTORDE YOK)
		INSERTER, BENİM VERDİĞİM KONUMDAN EKLEME YAPIYOR.


SADECE COPY ALGORİTMASI İÇİN DEĞİL YAZMA AMAÇLI TÜM ALGORİTMALAR İÇİN GEÇERLİ.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

COPY IF ALGORİTMASI ÜZERİNDE DE GÖRÜLEBİLİR.
Belirli koşulu sağlayanları başka range e yazıyordu copy_if

template <typename InIter, typemane OutIter, typename Pred>
OutIter CopyIf(InIter beg, InIter end, OutIter destbeg, Pred f)
{
	while(beg != end)
	{
		if(f(*beg))
			*destbeg++ = *beg;
			
		++beg;
	}
	return destbeg;
}


int main()
{
	using namespace std;
	vector<string> townvec;
	rfill(townvec,100,rtown);
	print(townvec);

	size_t len;
	std::cout << "uzunlugu kac olanlar kopyalansin\n";
	cin >> len;
	
	list<string> slist; // listede 100 öğe olsaydı doğrudan yazabilirdik ama şimdi inserter kullanacağız.
	
	copy_if(begin(townvec), end(townvec), back_insert(slist),[len](const string& str) {return str.length() == len;});
	//BUrada 100 adet şehir isminden uzunluğu yukarıdan len ile aldığımız ile eşit olanları slist e yazacağız.
	//kopyalama push back ile sondan yapılıyor.

	std::cout << slist.size();
	print(slist); // print func şablonu. bunu hoca yazdı test için bende yazacağım.

}


 MOLA

 ===========================================================================================================================================================================
 ===========================================================================================================================================================================
 ===========================================================================================================================================================================
 ===========================================================================================================================================================================
 ===========================================================================================================================================================================


 REVERSE ITERATOR ADAPTER
 ------------------------

 reverse_iterator iteratör adaptörü.Bilmeyene dehşet veren bir adaptör :D:D

 DAHA İYİ ANLAŞILMASI İÇİN ÖNCE ÖRNEĞİ YAZIYORUM
 -----------------------------------------------

 template <typename Iter>
 void print(Iter beg, Iter end)
 {
	while(beg != end)
		std::cout << *beg++ << " ";

	std::cout << "\n\n";
 }


 using namespace std;

 int main()
 {
	vector<int> ivec{1,4,5,7,9,4,5,6,3,2};

	print(ivec.begin(), ivec.end()); // BAŞTAN SONA YAZIYOR

	print(ivec); // Bunuda hoca yazmış.. Baştan sona yazdırdı

	print(ivec.rbegin(),ivec.rend()); // SONDAN BAŞA YAZDIRDI

 }

 NASIL OLUYORDA BIRI SONDAN BAŞA, DIĞERI ISE BAŞTAN SONA YAZDIRIYOR?
 Bunun cevabı Reverse Iterator Adapter yani reverse_iterator iterator adaptörü

 Sınıfların iterator türü dışında birde reverse iterator isimli nested type ı var. Mesela vector sınıfının reverse_iteratör sınıfı türünden bir nesne oluşturabiliriz.
 vector<int>::reverse_iterator iter = ivec.rbegin();	bu şekilde oluşturulur

 NOT : Reverse iteratör türüne sahip olması için en az bidirectional iterator ü desteklemesi gerekiyor.
 
 Sınıfın rbegin func ve rend functionu reverse iterator döndürüyor.begin değil, rbegin.

 auto iter = ivec.rbegin(); // auto yazılabilir.

 auto iter = ivec.rend(); // auto yazılabilir.

 Sınıfın rend functionuda yine reverse iteratör döndürüyor demiştik.

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 BURASI ÇOK AŞIRI ÖNEMLİ!!!!!
 ----------------------------

 BU KISIM TAMAMEN MÜLAKAT SORULARIYLA DOLU

 rbegin func ının return değeri olan iterator, aslında vectordeki son öğeden bir sonraki konumu tutuyor.Burada bir hile var ama
 bu şu demek, 

 auto iter = ivec.rbegin();
 stc::cout << *iter; // bu boş değilse vectordeki son öğeye eriştirecek.
 
 ÇOK ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!
 -------------------------------
 Bu biraz ters bir iterator :D:D
 ++iter yapınca aslında tam tersi -- işlemi yapıyor. Normal iteratörün tam tersi gibi davranıyor.* ile bir önceki nesneye eriştiriyor.

 Yani
 vector<int> ivec{10,20,30,40,50};
 
 for(auto iter = ivec.rbegin(); iter != iter.rend(); ++iter)
 {
	std::cout << *iter << " "; // 50 40 30 20 10
 }


 ARKA PLANDA ÇALIŞAN KODU İNCELEYELİM !!!!!!
 -------------------------------------------
 REVERSE ITERATÖR SINIF BIR ADAPTÖR SINIF YANI BU SINIF GERÇEK BIR ITERATÖR KULLANIYOR IÇINDE. BU DA GERÇEK KONUMU TUTUYOR.
 DİKKAT!!!! 
 REVERSE ITERATÖR, ITER KONUMUNU TUTTUĞUNDA FIZIKSEL OLARAK, * FUNCTIONU ONDAN BIR ÖNCEKI NESNENIN KONUMUNA ERIŞTIRIYOR.
 YANI RBEGIN GERÇEK OLARAK CONTAINERDAKI END KONUMUNU TUTUYOR AMA * / IÇERIK / DEREFERENCE / INDIRECTION OPERATÖRÜ O KONUMDAKI NESNEYE DEĞIL
 O KONUMDAN BIR ÖNCEKI NESNEYE ERIŞTIRIYOR.HILE BU !!!!!!!!!!!!

 NEDEN BÖYLE BİR HİLE VAR?
 BU OLMASAYDI DIZILERLE ILGILI KULLANIMDA ŞÖYLE BIR SORUN OLURDU, DIZININ BITTIĞI YERIN ADRESINI KULLANMAK LEGAL, DEREFERENCE ETMEDIĞIMIZ SÜRECE LEGAL.
 AMA!!! DIZININ ILK ELEMANINDAN ÖNCE OLMAYAN ELEMANIN ADRESINI KULLANMAK DIYE BIRŞEY YOK. REVERSE ITERATÖR NE YAPIYOR ? RBEGIN FUNCTIONUNU ÇAĞIRDIĞIMIZDA
 ASLINDA KULLANDIĞIMIZ ITERATÖR FIZIKSEL OLARAK SON ÖĞEDEN SONRASINI TUTAN ITERATOR.DOĞRUDAN DEREFERENCE ETMEK UB. REVERSE ITERATÖRÜN DEREFERENCE OPERATÖRÜ
 TUTTUĞU NESNE DEĞILDE ONDAN BIR ÖNCEKINE ERIŞTIRIYOR.(TEKRAR YAZDIM)

 BU DURUMDA END FUNCTIONU!!!!!!
 REND FUNCTIONU ILK ÖĞENIN KONUMUNU TUTUYOR, * / DEREFERENCE OPERANDI YAPILDIĞINDA, OLMAYAN YANI DIZININ BAŞLADIĞI YERDEN BIR ÖNCEKI NESNEYE GIDIP DEREFERENCE EDECEK
 UNDEFINED BEHAVIOR. 

 SINIFIN IMPLEMENTASYONUNDA REVERSE ITERATÖR SINIFI, NORMAL ITERATÖR SINIFINDAN KALITIMLA ELDE EDILIYOR. SINIFA BASE ISIMLI BIR FUNC KOYMUŞLAR, BU FUNC REVERSE ITERATÖRÜN
 SARMALADIĞI GERÇEK ITERATÖRÜ DÖNDÜRÜYOR.YANİ DEREFERENCE EDİNCE BİR TANE GERİ GELİP DEREFERENCE ETMİYOR. TUTTUĞU YERİ DÖNDÜRÜYOR. BİLDİĞİMİZ GERÇEK İTERATÖR ARTIK BU.

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 int main()
 {
	vector<int> ivec{10,20,30,40,50};

	auto riter = ivec.rbegin(); // riter, end konumunu tutuyor
	std::cout << *riter<< "\n"; // bir önceki nesneye erişim sağladığı için UB yok. end i tutuyordu.end ten bir öncekine gelip dereference edilir. 50 yazar

	auto iter = riter.base(); //  reverse iteratör yerine normal iteratör alacağım.end konumunu tutuyor 
	std::cout << *iter<< "\n"; // burada end konumunda dereference eder ve UNDEFINED BEHAVIOR
 
	std::cout << boolalpha << (iter = ivec.end()); // true yazdırır.

 }

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 ÖR:

 int main()
 {
	vector<int> ivec{10,20,30,40,50};
	auto riter = ivec.rbegin(); // end i tutuyor
	++riter;	// dizinin son öğesinde şuanda

	std::cout << *riter<< "\n"; // bir önceki öğeye gelip dereference eder.Yani 40
	auto iter = riter.base(); // Halen gerçek konumu 50 nin konumu
	std::cout << *iter<< "\n"; // bu konumu dereference ederse 50 yazar.Reverse iteratordeki gibi bir önceye gelip dereference etmiyor.

 }

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 NEDEN BÖYLE BİR TASARIM YAPMIŞLAR?

 EĞER BIR REVERSE ITERATÖR RANGE'INI BIR ALGORITMAYA ARGÜMAN OLARAK GÖNDERIRSEK, ALGORITMA O RANGE I SONDAN BAŞA DOĞRU IŞLER.
 AYNI RANGE IN BASE INI AYNI ALGORITMAYA GÖNDERIRSEK BAŞTAN SONA O RANGE I DOLAŞMIŞ OLURUZ.

 int main()
 {
	vector<int> ivec{10,20,30,40,50};

	auto rbeg = ivec.rbegin();
	auto rend = ivec.rend();

	print(rbeg, rend); // print sondan başa doğru yazdırır.

	print(rend.base(), rbeg.base()); // Bu sefer range in tersini oluşturmuş oluyorum.

 }


 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 MÜLAKAT SORUSU 
 Verilen değerden en sonuncusunu vectorden sil.

 int main()
 {
	vector<int> ivec{2,4,5,7,8,4,5,6,2,4};
	int ival = 2; // 2 yi containerdan sil

	auto iter = find(ivec.rbegin(),ivec.rend(),ival); // buradaki return değerde reverse iterator
	if(iter != ivec.rend())
	{
		ivec.erase(iter); // BURASI SENTAKS HATASI. ERASE VECTÖRÜN ITERATOR TÜRÜNDEN, REVERSE İTERATÖR TÜRÜNDEN DEĞİL. GERÇEK İTERATÖR
		std::cout << *iter << "\n"; // 2 YAZDIRDIĞINI GÖRÜRÜZ.(REVERSE ITERATÖR KULLANIYORUZ ŞUANDA)

		ivec.erase(iter.base()); // ŞİMDİ GERÇEK İTERE DÖNDÜ AMA FİND EDERKEN BİR ÖNCEKİ OPERATÖRÜ BULMUŞUK, DEREFERENCE EDİNCE O BİR ÖNCEKİNİ EDİYORDU. YANİ GERÇEK KONUM
								 // BİR SONRAKİ İTERATÖR.YANİ 4 Ü SİLDİK.
	
		ivec.erase(iter.base() - 1); // ŞİMDİ OLDU.

		print(ivec);
		
	}	
 }

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 4 TANE BEGİN FUNCTIONUMUZ OLDU. HEPSİNİ YAZALIM.
 Container con olsun

 con.begin ->								return değeri : container::iterator
 con.cbegin -> const iterator				return değeri : container::const_iterator
 con.rbegin -> Reverse itetator				return değeri : container::reverse_iterator
 con.crbegin -> const reverse iterator		return değeri : container::const_reverse_iterator

 YUKARIDAKİLER ITERATOR ADAPTORLAR
 AŞAĞIDAKİLERDE TÜM LİSTE
 
reverse_iterator
 
iterator adaptor for reverse-order traversal
(class template)
make_reverse_iterator
  
(C++14)
 
creates a std::reverse_iterator of type inferred from the argument
(function template)
move_iterator
  
(C++11)
 
iterator adaptor which dereferences to an rvalue reference
(class template)
move_sentinel
  
(C++20)
 
sentinel adaptor for use with std::move_iterator
(class template)
make_move_iterator
  
(C++11)
 
creates a std::move_iterator of type inferred from the argument
(function template)
common_iterator
  
(C++20)
 
adapts an iterator type and its sentinel into a common iterator type
(class template)
default_sentinel_t
  
(C++20)
 
default sentinel for use with iterators that know the bound of their range
(class)
counted_iterator
  
(C++20)
 
iterator adaptor that tracks the distance to the end of the range
(class template)
unreachable_sentinel_t
  
(C++20)
 
sentinel that always compares unequal to any weakly_incrementable type
(class)
back_insert_iterator
 
iterator adaptor for insertion at the end of a container
(class template)
back_inserter
 
creates a std::back_insert_iterator of type inferred from the argument
(function template)
front_insert_iterator
 
iterator adaptor for insertion at the front of a container
(class template)
front_inserter
 
creates a std::front_insert_iterator of type inferred from the argument
(function template)
insert_iterator
 
iterator adaptor for insertion into a container
(class template)
inserter
 
creates a std::insert_iterator of type inferred from the argument
(function template)

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 int main()
 {
	vector<int> ivec{2,4,5,7,8,4,5,6,2,4};

	vector<int>::const_reverse_iterator iter = ivec.crbegin(); // böyle yazıalbilir ama auto kullanılıyor genelde
	auto iter = ivec.crbegin();  // Bunların global karşılıklarıda var 
	auto iter = crbegin(ivec);  // Bunların global karşılıklarıda var 

	//crbegin e C dizisi de gönderilebilir.
 }

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 int main()
 {
	vector<string> svec;
	rfill(svec,10,rname);
	print(svec);
	sort(svec.begin(), svec.end()); // yazılar küçükten büyüğe sıralandı
	print(svec);

 }



 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 DİKKAT BURADA RBEGIN VE REND KULLANILDI

 int main()
 {
	vector<string> svec;
	rfill(svec,10,rname);
	print(svec);
	sort(svec.rbegin(), svec.rend()); //Burada ise büyükten küçüğe yapıldı sıralama
	print(svec);

 }

 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 ITERATORLER ÜZERİNDE İŞLEM YAPAN ALGORİTMALAR
 ---------------------------------------------
 Bunlar çok sık kullanılıyor STL de.Bunlar aşağıdakiler

 advance
 distance
 next
 prev
 iter_swap

 Bunlar iterator header fileda tanımlanan function şablonları

 Diyelimki bir iteratörü artırmak istiyorsam bunun için += operator functionu kullanabilirim.


 int main()
 {
	vector<int>svec{12,2,5,4,6,7,8,9,2,4}; 
	auto iter = ivec.begin();
	iter += 3; //GEÇERLi
	cout << *iter << "\n";

	list<int>ilist{12,2,5,4,6,7,8,9,2,4};
	auto iter = ivec.begin();
	iter += 3; //SENTAKS HATASI.+= bidirectional iteratorler tarafından desteklenmiyor

	++iter;
	++iter;
	++iter; // başka bir şans yok
	
	advance(iter,3);


	advance(iter,n);  // Eğer bu iter eğer random access iterator ise beg+=3 çalışacak ama random access iterator değilse beg n kez artırılması koduna dönüşecek

 }

 Bu durumlarda compile timeda kullanılan metaprogramming hileleri ile aslında iteratörü 3 kere artırmak yerine advance(iter,3); yazacağız.
 Advance compile timeda kod seçecek eğer iterator random access iterator ise burada çalışan kod iter += 3 kodu olacak ama iter random access iterator dğeilse
 bir döngü içinde iteratörü n kez artıracak. Bu sayede ++ veya += operandı yapmak yerine compile timedaki seçilen kodla en düşük maliyetle uygun kod çalışacak.

 Özellikle template kodlarda bu çok daha önemli.

 Yarın bunlar görülecek.


*/


#include <iostream>
#include <vector>


