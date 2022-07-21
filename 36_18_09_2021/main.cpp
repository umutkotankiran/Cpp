/*

std::functionda kalmıştık.

Parametrik yapısı herhangibir türden olan callable ı sarmalıyor.
Bir function pointera doğrudan bir function object atanamıyor.Duruma göre atanabilir.

Bir func pointera doğrudan function objesini atayamayız mesela.

std::function ile hertürlü callable sarmalanabiliyor. Bu sayede genel yapıları birbirinden farklı olan
callable ları bir containerda tutabiliriz.Genneleştirilmiş bir callback yapısında function oluşturabiliriz.

#include<iostream>
#include<function>

int square(int x)
{
	return x * x;
}

class Functor{
public:
	int operator()(int x)const
	{
		return x * x * x - 1;
	}
};

int main()
{

	std::function<int(int)> f{square};
	//Açısal parantez içerisinde bir function türü int(int). function adresi türü farklı int(*)(int)
	
	std::cout << f(123) << "\n";
	
	auto f{square}; // Burada function pointer tutar f.
	
	auto &f{square}; // Bu durumda da f bir function referansı olur.

	std::function f = square; //CTAD kullanılabilir.Ctad ctordan argümanlarından hareketle türü detect ediyor.

	---------------------------------------------------------------------------------------------------------------------------------------------------------------

	Functor fx;
	std::function<int(int)> f{fx};

	cout << f(10) << "\n";

	---------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::function<int(int)> fx{Functor{}};
	
	cout << fx(10) << "\n";

	---------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::function<int(int)> fx{Functor{}};
	std::cout << fx(10) << "\n";

	fx = square;
	std::cout << fx(10) << "\n"; // çağrılan func değişti çünkü square e atadık fx i.

	---------------------------------------------------------------------------------------------------------------------------------------------------------------

	fx = [](int a) {return a + 5};
	std::cout << fx(10) << "\n"; //15

	---------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	std::function ff = Functor{};  //Ctora gönderilen argüman olduğundan CTAD YAPILIYOR.

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

NELERDEN FAYDALANIYORUZ

1 - CTAD TAN FAYDALINILIR
2 - Default initialize edebiliyoruz
3 - Bir callable a atayabiliyoruz parametrik yapısı aynı olduğu sürece
4 - Bir lambdaya ilk değer verilebilir veya atama yapabiliyoruz.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

EXCEPTION THROW EDEBİLİR

int main()
{
	std::function<int(int)>f;

	try{
		f(12);
	}
	catch(const std::exception &ex){	// std::bad_function_call da yazılabilirdi. 
		std::cout << "exception caught : " << ex.what() << "\n";
	}

	//EXCEPTION CAUGHT BAD FUNCTION CALL THROW EDECEK.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA GENELLEŞTIRILMIŞ BIR CALLBACK YAPISI OLUŞTURULABILIR

Callback ben sana bir func gönderiyorum sende bunu çağır demekti.

void func(int(*fptr)int))
{
	auto n = fptr(12); // func(function_adi) function_adi kimin adresi ise o çağrılacak.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKI YERINE AŞAĞIDAKINE GEÇIŞ YAPTIK

void func(std::function<int(int)> f) // ARTIK CALLBACK OLARAK BEN BUNA FUNCTION ADRESI GÖNDERME MECBURIYETIM YOK AMA FUNC ADRESIDE GÖNDEREBILIRIM. HERHANGIBIR
{										// CALLABLE OLABILIR.BU HERHANGIBIR CALLABLE. FUNC OBJECT, FUNC ADRESI, FUNC ISMI, LAMBDA, BIND IFADELERI OLABILIR
	auto val = f(12);
}

int foo(int);

struct Functor{}
	int operator()(int)const;
;

int main()
{
	func(foo); // callable bir sınıfın static bir member func ta olabilir.
	func(Functor{});
	func([](int a){return a + 5;}); // Lambda expr verdiğimizde yine bir function object geçiyruz. çünkü lambda expr geçici nesne demek.
}

Function pointer bizden illahaki func adresi istiyordu
burada ise callable istiyor. func object lambda ifadesi ...
Lambda yine function object bir geçici nesne ama derleyicinin oluşturduğu geçici nesne

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

AUTO RETURN TYPE C++14 TE EKLENDI

auto func(x)
{
	//..
	return [x](int a){return a * x;}; // capture referans yoluyla olsaydı dangling referans olacaktı.
}

int main()
{
	auto f = func(2); // 
	f(10); //diyerek çağırabiliriz şimdi.

	func(12)(5); // veya böyle yapılabilir.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BÖYLE YAZILABILIR

std::function<int(int)> func(int x) // Artık return türü std::function turunden closure type değil.Çünkü std::function olarak yazıldı functa
{
	//..
	return [x](int a){return a * x;}; 
}

int main()
{
	auto f = func(2); // buradaki açıklamayaı yaz.

	func(12)(5);
}

if else yapısı içerisinde bir tanesi bir fucntor object diğeri ise bir lambda ifadesi döndürebilir.

std::functionda verim kaybı genellikle yok.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

CALLABLE NESNELERI BIR CONTAINERDA TUTMAK.

#include <vector>

double f1(double);
double f2(double);
double f3(double);
double f4(double);

using fptr = double(*)(double);

int main()
{
	using namespace std;

	vector<double(*)(double)>myvec; // myvece func pointer push back edebiliriz.Bu vectorde başka callable tutulamaz

	vector<fptr>myvec; // böylede yazılabilir

	myvec.push_back(f1);
	myvec.push_back(f2);
	myvec.push_back(f3);
	myvec.push_back(f4);

	for(auto f : myvec)
	{
		auto dval = f(12);
	}
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <vector>

double f1(double);
double f2(double);
double f3(double);
double f4(double);

using MyFunctionType = std::function<double(double)>;

int main()
{
	using namespace std;

	std::vector<std::function<double(double)>> myvec; //VECTOR CALLABLE LARI TUTUYOR.BIR ÖĞESI BU TÜRDEN BIR FUNC OBJECT, DIĞERI LAMBDA, DIĞERI FUNC POINTER OLABILIR.
														// NOT : FUNC POINTER TEST EDİLDİ :D:D
	
	YADA BÖYLE YAZILIR USİNG BİLDİRİMİ SAYESİNDE
	std::vector<MyFunctionType> myvec;
	
	myvec.emplace_back(f1); // Emplace back ctorun alacağı argüman yada argümanları alıp Perfect Forwarding ile std func nesnesini oluşturuyor.
							
	myvec.emplace_back(f2);

	myvec.emplace_back([](double d){return d * d - 1.;});

	myvec.push_back(MyFunctionType{ f3 }); // pushback e vectorun tutacağı türden öğe vermek zorundayız.

	for(auto f : myvec)
	{
		auto n = f(1.4); // f her turda std::function nesnesi.ve 1.4 gönderdik hepsine
	}
}

=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================

TUPLE
-----
STL de bulunuyor.Pair gibi ama 3 - 4 - 5 öğeyi birarada tutabiliriz.C++11 ile eklendi.Bunu yapmak için sınıf yazabiliriz ama sınıf olmayı hak edecek bir 
interface olmuyor çoğu zaman.Belirli bir kod alanında belirli bir süre için arasında logic ilişki bulunmayan veriyi tutmak isteyebiliriz.
Programlamada çok sık kullanılıyor.Sadece C++ ile ilgili değil.

#include <tuple> ile eklenebilir.

tuple<int, double,long>
tuple<int, string,char>
tuple<int, bitset<16>,Date>

Hepsi geçerli 

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <tuple>
#include <string>
#include "date.h"
#include "nutility.h"

int main()
{
	using namespace std;

	NASIL OLUŞTURULUR.YOLLARDAN BİRİ DEFAULT INITIALIZATION
	tuple<int,double,long>t; 
	//pairde first ve second ile erişirdik öğelere, burada gobal bir func şablonu kullanılıyor. Adı get
	// get<index>(tuple_değişken_adı) şeklinde kullanılır.

	cout << get<0>(t) << "\n";
	cout << get<1>(t) << "\n";
	cout << get<2>(t) << "\n"; // hepsi 0 şuanda
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	PARAMETRELİ CTORUDA KULLANABİLİRİM

	tuple<int,double,long>t{12,4.5,56L};

	cout << get<0>(t) << "\n";
	cout << get<1>(t) << "\n";
	cout << get<2>(t) << "\n";
	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	BURADA CTAD TA KULLANILABİLİR

	tuple t{12,4.5,56L}; //GEÇERLİ

	BURADA PROGRAMCILARIN YANLIŞ ANLADIĞI ŞEYLER VAR
	Tür argümanı belirtmeyip string literali kullanırsak, mesela aşağıdaki gibi 3. parametre const char * oluyor.string değil
	tuple t{12,4.5,"Mustafa"}; 
	NOT : User defined literal denen bir araç var.Bunu ileride anlatacak hoca.Yada İleri C++ ta anlatacak
	tuple t{12,4.5,"Mustafa"s}; // bu şekilde string olmasını sağlayabiliriz.Bu bir Rvalue expr
	hatta "mustafa"s = "ali"; // geçerli. :D 


	cout << get<0>(t) << "\n";
	cout << get<1>(t) << "\n";
	cout << get<2>(t) << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

GET FUNCTION
Return değeri bir referans.bir value değil.

int main()
{
	tuple<int,double,long>t{12,4.5,"mustafa"s};

	get<0>(t) += 23; // return değeri sol taraf referansı o yüzden hem okuma hemde yazma amaçlı kullanılabilir.

	get<2>(t).append("can"); // mustafacan oldu 2. indexteki

	auto n = get<3>(t); // BURADA 3 OLMADIĞINDAN SENTAKS HATASI. EXCEPTION THROW YOK
}

3 indexini compiler compile time da kontrol edebiliyor.Bir constant expr çünkü.

--------------------------------------------------------------------------------------------------------------------------------------------------------------

C++14 TE GET E TÜR ARGÜMANIDA VEREBILIYORUZ. SON DERECE YAHŞİ BİR ARAÇMIŞ :D:D:D

INDEX VERMIYORUZ TÜR ILE ERIŞIYORUZ.TUPLE DA O TÜRDEN BİRDEN FAZLA NESNE VARSA SENTAKS HATASI

int main()
{
	tuple t{12,4.5,"mustafa"s};
	 
	get<int>(t) = 34;
	get<double>(t) = 4.8;
	get<string>(t) = "mehmet";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

BİRDEN FAZLA AYNI TÜR ÖRNEĞİ

int main()
{
	tuple<int, double,int string> tx{12,4.4,85,"ali"};
	
	auto n = get<int>(tx); //SENTAKS HATASIDIR
}


--------------------------------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKİ GİBİDE KULLANILABİLİR

using Age = int;
using Name = std:string;
using Wage = double;
using BirthDate = Date;

using PersonInfo = std::tuple <Age,Name,Wage,BirthDate>;

int main()
{
	PersonInfo info;	

	get<Age>(info);
	get<Name>(info);
	get<Wage>(info);
	get<BirthDate>(info);
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

MODERN C++ İLE TUPLE AŞAĞIDAKİ GİBİDE KULANILABİLİYOR.BU KULLANIM PAIRDE DE VARDI.

std::tuple<int,double,string>foo(int x, double dval, const char *p)
{
	///
	return {x,dval,p};
}

int main()
{
	tuple tx{12,5.6,3.4F};
	
	tx = {23,3.3,5.6f}; //pairde de {1,3} gibi şeyler return ediyorduk
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

MAKE TUPLE VAR

int main()
{
	int x = 10;
	double dval = 23.45;
	Date mydate{12,4,1998};
	
	auto t = make_tuple(x, dval,mydate); //make_pair de vardı

	cout << get<Date>(t);
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int x = 10;
	string str = "murat";

	auto p = make_pair(x,str);

	p.first = 354;
	p.first += "can";

	std::cout << x << " " << str << "\n"; // 10 ve murat
}

NASIL DEĞIŞMESINI SAĞLARIZ.
int main()
{
	int x = 10;
	string str = "murat";

	auto p = make_pair(ref(x),ref(str));

	p.first = 354;
	p.first += "can";

	std::cout << x << " " << str << "\n"; // 354 ve muratcan
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

EN ÇOK KULLANILDIĞI YER FUNCTIONLARIN RETURN DEĞERLERI

std::tuple<int,double, string> func()
{
	return {625, 33.333, "Neco"};
}

int main()
{
	auto t = func(); // t bir tuple nesnesi. Programcı bunların ayrı değişkenlere aktarılmasını ister
					 // structured binding ile yapılır.

	int ival = get<0>(t);
	double dval = get<1>(t);
	string sval = get<2>(t);
	//YUKARISI ESKİ

	
	//YENİ KISIM AŞAĞIDA
	auto [id,wage,name] = func(); //Bu gibi senaryolar için structural binding dile eklendi zaten.C++17 eklendi structural binding

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

TIE 
---
C++11 de eklendi.Variadic func şablonu
Tie ın return değeri tuple referans açılımı

std::tuple<int,double, string> func()
{
	return {625, 33.333, "Neco"};
}

int main()
{
	int age;
	double wage;
	string name;

	tie(age,wage,name); // return değeri tuple ın referans açılımı tuple<int&, double&, string&> türünden bir nesne

	tie(age, wage, name) = func(); // soldaki tuple elemanları referans olan bir tuple, bu referanslar age,wage ve name değişkenlerine bind etti.
	std::cout << age << "\n";		// bu sayede değiştirebiliriz.
	std::cout << wage << "\n";
	std::cout << name << "\n";

	//tie a argüman olarak ingore geçersek onu kullanmıyoruz.
}

Structural binding yokken bu ayrıştırma için kullanılıyordu çünkü başka araç yoktu.
Bu kötü bir teknikti. Neden kötü bir teknik ? Structural bindinte string nesnesi doğrudan initialize ediliyor.
Tie da string nesnesi için önce default ctor çağrıldı, sonrada string nesnesine atama yapıldı.

Avantajı ise değişkenleri başka yerde kullandık diyelim ama şimdi function return değerlerini bu değerlere atamak istiyoruz.
Bu tie ile olabilir ama structural binding ile olmaz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TUPLE DAKİ ÖĞELERİN IGNORE EDİLMESİ

int main()
{
	int age;
	string name;

	tie(age, ignore, name) = func(); // burada 2. elemanı gözardı ettik. Kullanmadık.Bu bir değişken ismi.std içinde.birden fazla eleman için kullanılabilir.
	std::cout << age << "\n";
	std::cout << wage << "\n";
	std::cout << name << "\n";

	//tie a argüman olarak ingore geçersek onu kullanmıyoruz.
}

Structural bindingte bu şekilde bir sentaks yok.

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TIE A DEVAM

SWAP ETMEYE ÇALIŞACAĞIZ BU ASLINDA ÖDEV OLDU

int main()
{
	int x = 10;
	int y = 45;

	tie(x,y) = {y,x};

	std:cout << "x = " << x << "\n"; //45
	std:cout << "y = " << y << "\n"; //45
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	int x = 10;
	int y = 45;

	tie(x,y) = {y,x};
	std:cout << "x = " << x << "\n"; //45
	std:cout << "y = " << y << "\n"; //45
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	int x = 10;
	int y = 45;

	tie(x,y) = tie(y,x);
	std:cout << "x = " << x << "\n"; //45
	std:cout << "y = " << y << "\n"; //45
	BUNLARI SWAP YAPABİLİR MİYİZ TIE İLE
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

2 TUPLE KARŞILAŞTIRILMASI

birinci elemanı küçükse küçük, eşitse ikinci elemana bakılıyor eşitse üçüncüye ...

int main()
{
	tuple tx{10,3.5, "Alican"s};
	tuple tx{10,3.5, "Mehmet"s};

	std::cout << boolalpha << (tx < ty); // True
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

using Person = std::tuple<int,std::string,double>;

int main()
{
	vector<Person> vec;
	vec.reserve(100);

	for(int i = 0; i < 100;++i)
	{
		//vec.push_back(Person{rand(),rname(), Drand{1.5,9.7}()}); buda olabilirdi.
		//vec.push_back({rand(),rname(), Drand{1.5,9.7}()}); buda olabilirdi.
		vec.emplace_back(rand(),rname(), Drand{1.5,9.7}()); //Perfect forwarding ile containerdaki öğelerin ctoruna geçilecek argümanları yazdık.
	}

	for(const auto &p : vec)
	{
		std::cout << get<0>(p) << " " << get<1>(p) << " " << get<2>(p) << " " <<"\n"; 
	}

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

SIRALAYALIM

using Person = std::tuple<int,std::string,double>;

int main()
{
	vector<Person> vec;
	vec.reserve(2000);

	for(int i = 0; i < 2000;++i)
	{
		//vec.push_back(Person{rand(),rname(), Drand{1.5,9.7}()}); buda olabilirdi.
		//vec.push_back({rand(),rname(), Drand{1.5,9.7}()}); buda olabilirdi.
		vec.emplace_back(rand() % 10,rname(), Drand{1.5,9.7}()); buda olabilir
	}

	sort(vec.begin(), vec.end()); // default olarak less kullanldığını hatırla.tuple ın < func çağrılacak. yukarıda yazdığım gibi 1. 2. 3. öğeler kıyaslanacak

	for(const auto &p : vec)
	{
		std::cout << get<0>(p) << " " << get<1>(p) << " " << get<2>(p) << " " <<"\n";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKİ SINIFA OPERATOR< YAZALIM
Tupleda olduğu gibi yapsın. Buarada tuple da bunu yaptığı için oradan yardım alınacak.

class Myclass{
public:
	friend bool operator<(const myclass &left, const Myclass &right)
	{
		return std::tuple {left.mx,left.str,left.dval} < std::tuple {right.mx,right.str,right.dval};
	}

private:
	int mx;
	double dval;
	std::string str;

};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int x = 10;
	int y = 20;
	int z = 30;

	std::cout << "x = " << x << " y = " << y << " z= " << z << "\n";

	int temp = x;
	x = y;
	y = z;
	z = temp;
	//YUKARIDAKİ SWAPI YAPACAK OLAN TUPLE IDIYOMU NASIL YAZILABILIR ? 

	std::cout << "x = " << x << " y = " << y << " z= " << z << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TUPLE SIZE 

tuple içinde tutulan öğe sayısı.

int main()
{
	tuple x = {12, 4.5, 'A'};	
	
	//constexpr auto n =  tuple_size<tuple<int,double>>::value;
	
	constexpr auto n1 =  tuple_size_v<tuple<int,double>>; //tamamen aynı variable template diye geçiyor _v. size = 2
	constexpr auto n2 =  tuple_size_v<decltype(x)>; // burada da size = 3

	//bu metafunction
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TUPLE ELEMENTH

type element, öğenin türünü elde ediyor.

int main()
{
	tuple x = {12, 4.5, 'A'};
	tuple_element<1,decltype(x)>::type; // elemanın türünü compile time da elde ediyor.
	
	tuple_element<0,decltype(x)>::type ival{}; //int türü.
	tuple_element<1,decltype(x)>::type ival{}; //double türü.
	tuple_element<2,decltype(x)>::type ival{}; //char türü.

	tuple_element_t<0,decltype(x)> ival{}; // type template buda
}

2:03
Özetle, function return değeri olabilir, func parametresi olabilir, tuple lar containerda tutulabilir, tuple karşılaştırma operator func ını kullanabilirim,
pairdeki gibi tuple da da karşılaştırma işlemleri önce ilk öğe, eşitse ikinci öğe eşitse sonrakilere bakılıyor...

==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================

STD::ARRAY
Bir sınıf şablonu ama varlık sebebi C dizilerini sarmalamak.
Bir diziyi doğrudan kullanmak yerine bunu eleman olarak alan bir yapı nesnesi kullanmak.
Sınıf şeklinde sarmalamak.

Kullanım sebepleri
------------------
STL e daha iyi uyum sağlıyor.
Exception throw edebilir duruma göre.
Bir interface e sahip
Array decay sözkonusu değil.
Kopyalama semantiğine sahip.(dizilerde bu yok.)

array header file içerisinde yer alıyor.

template <typename T, size_t n>
struct Array
{
	T ar[n];
};

int main()
{
	Array<int, 10> ax{1,3,5,7};// 10 elemanlı bir int array. aggregate initialization. Bu initializer list değil :D 
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	array<int,5> ar; // default init edildiğinde bu şekilde elemanlar çöp değerde.Indetermined value garbage value
	int a[5]; gibi ama hiç maliyeti yok.Çünkü inline olarak açılıyor.

	array<int,5> ar{}; //Burada durum farklı test et 0 çıkacak.boolean da false, pointerda nullptr olacaktı.Value init
	int a[5]; //gibi ve bir ekstra maliyet yok.
	
	array<int,5> ar{4,6,8,2,9};

	for(auto i : ar)	// range base for loop destekliyor.
	{
		std::cout << i << " "; 
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	array<int ,5> ar{1,3,5,7,8};
	array<string ,3> ar{"ali","veli","hamdi"};

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

[] Overload edilmiş. 
[] in return değeri tabiki referans

int main()
{
	array<int,5> ar{1,2,32,4,789};
	ar[0] = 9; // ilk eleman 9 oldu

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

SIZE FUNCTIONU ARRAY SIZE RETURN EDIYOR.

int main()
{
	array<int,5> ar{1,2,32,4,789};
	ar[0] = 9; // ilk eleman 9 oldu
	
	for(int i = 0; i < ar.size(); ++i)
	{
		std::cout << ar[i] << " ";
	}
	std::cout << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

ITERATOR İLE DOLAŞALIM

int main()
{
	array<int,5> ar{1,2,32,4,789};
	ar[0] = 9;
	ar[4] = 22;

	for(auto iter = ar.begin(); iter != ar.end(); ++iter)
	{
		std::cout << *iter << "\n";
	}

	REVERSE ITERLERİDE VAR
	for(auto iter = ar.rbegin(); iter != ar.rend(); ++iter)
	{
		std::cout << *iter << "\n";
	}

	Array random access iterator

	Range base ffor loopta yazılabilir.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

OLMAYAN INDEX ERİŞİMİ

int main()
{
	array<int,0>ar; // C dizisi olarak 0 size veremeyiz.Burada legal

	cout << "ar.size() = " << ar.size() << "\n";

	auto x = ar[0]; //UB çünkü size 0
	auto y = ar[5]; //UB çünkü size 0
	
	auto y = ar.front(); // ilk öğeye referans. Ama boyut 0 bu sebeple UB
	auto y = ar.back(); // son öğeye referans. Ama boyut 0 bu sebeple UB

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	array<int,5> ar{17,2,32,4,567};

	try{
		//auto val = ar[7]; // BURASI UB
		auto val = ar.at(7); // Exception throw eder.
	}
	catch(const std::out_of_range &ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

FILL 
Tüm elemanları belirli bir değerle dolduruyor.

int main()
{
	array<int,5> ar{17,2,32,4,567};

	ar.fill(12);  // tüm elemanlar 12 oldu

	for(auto val : ar)
		std::cout << val << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : AYNI TEMPLATE İN FARKLI AÇILIMLARI BİRBİRİNE ASSIGNABLE DEĞİL.
array<int,65>ar;
array<double,65>dar;

ar = dar; //SENTAKS HATASI

YİNE
array<int,5> arx{1,3,5,7,8};
array<int,8> ary;
arx = ary; //SENTAKS HATASI

AMA ITERATORLER İLE YAPILABİLİR.

copy(arx.begin(), arx.end(),ary.begin());

--------------------------------------------------------------------------------------------------------------------------------------------------------------

SWAP
Linear complexity de yapılıyor bu.

array<int,5> arx{1,3,5,7,8};
array<int,5> ary{4,6,8,10,12};

swap(arx,ary);
arx.swap(ary);

Tüm containerlar karşılaştırılabilir. < ile . Bu karılaştırma lexicographical. Tüm öğeler karşılaştırılacak ilk küçük olan küçük olacak.
C++ 20 ile spaceship operatörüne dönüştürüldü.

--------------------------------------------------------------------------------------------------------------------------------------------------------------

STANDART LIBRARY DE ARRAY IÇIN INSERTER YOK.
BUNU KENDİMİZ YAZACAĞIZ

template <typename T, size_t n>
std::ostream& operator<<(std::ostream&os, const std::array<T,n> &ar)
{
	os<< "[" << ar.size() << "] |";
	
	for(size_t i{}; i < ar.size() - 1; ++i)
	{
		os << ar[i] << ", ";	
	}

	return os << ar.back() << "|";
}

int main()
{
	array<int,5> arx{1,2,3,4,56,76,95};
	std::cout << arx;

	array x = {1.1,2.2,3.3,4.4,5.5}; //CTAD kullanabiliriz.

	std::cout << x << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

ARRAY GET INTERFACE İNİ DESTEKLİYOR.

int main()
{
	array<double,5>x = {1.1,2.2,3.3,4.4,5.5};
	
	get<0>(x) = 4.5;
	get<1>(x) = 9.5;
	
	std::cout << x[0] << "\n";
	std::cout << x[1] << "\n";

	------------------------------------------------------------------------------------------------------------------------------------------------

	TÜR VE SİZE BİLGİSİ

	constexpr auto n = std::tuple_size_v<decltype(x)>;  // tuple_size dizinin boyutunu veriyor.
	std::tuple_element_t<0,decltype(x)> dval{};  // tür bilgisini veriyor.X in 0. index tür bilgisi.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

STRUCTURAD BINDING ÖRNEĞİ

array<int,3> foo(int x, iny y, int z)
{
	return {x,y,z};
}

int main()
{
	auto [a,b,c] = foo(10,20,30);

	std:cout << "a = "<< a <<"\n";
	std:cout << "b = "<< b <<"\n";
	std:cout << "c = "<< c <<"\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

YAZDIĞIMIZ TEMPLATE KULLANARAK AŞAĞIDAKİ DE YAZILABİLİR.

int main()
{
	array<array<int,3>,4> ar{{{1,1,1},{2,2,2},{3,3,3},{4,4,4,}}};

	ar[2][1]; //erişilebilir

	std::cout << ar; // Yazılabilir. Geçerli. Bİzim yazdığımız template ten 2 tane func yazacak compiler. biri array<array<int,3>,4> için 
					 // diğeri array<array<int,3>,4> için.
}

MOLA

==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================

2:51

CTAD GEÇERLI AMA AŞAĞIDAKI SENTAKS GEÇERSIZ

int main()
{
	array<int> ax = {1,2,3,4,5}; // tür var ama boyut verilmemiş.
	array<> ax = {1,2,3,4,5}; // Buda hata
	array ax = {1,2,3,4,5}; // GEÇERLİ
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TAŞIMA SEMANTİĞİNİ DESTEKLİYOR

Ama bunu desteklemesini vector ve deque gibi sınıflarla karıştırmayalım. Vectorde mesela pointer değerleri değişiyor.
pointer değerleri move edilmiyor sadece atanıyor. Bu sebeple vectorde karmaşıklık O(1)

Dizilerde bunu yapma imkanı yok. çünkü dizi başka bir heap bellek alanında blok tutmuyor. Burada taşıma karşılıklı elemanların taşınması ile oluyor.

class Myclass{
public:
	Myclass() = default;
	Myclass(const Myclass&)
	{
		std::cout << "copy ctor called\n";
	}
	Myclass(Myclass &&)
	{
		std::cout << "move ctor called\n";
	}
};

int main()
{
	array<Myclass,5> arx;
	array<Myclass,5> ary = arx; //copy ctorlar çağırıldı

	array<Myclass,5> ary = std::move(arx); // move ctor çağrıldı.Move primitive tür için farketmiyor birinde int ler diğerinde
											// int * lar kopyalanacak(move da)

}

Vectorde elemanlar karşılıklı olarak kopyalanmayacaktı.

--------------------------------------------------------------------------------------------------------------------------------------------------------------

VECTOR IÇIN YAPALIM

int main()
{
	std::vector<Myclass> arx;
	std::vector<Myclass> ary = arx; //copy ctorlar çağırıldı

	std::vector<Myclass> ary = std::move(arx); // move ctorlar çağrıldı ve 3-4 pointer(artık kaç tane ise begin, size ve capacity tutan pointerlar) copy edilecek.
}


--------------------------------------------------------------------------------------------------------------------------------------------------------------

ARRAY DECAY YOK

int main()
{
	array<int, 5> ar{};
	int a[5] = {};

	int *p = a; // array decay geçerli.
	int *ptr = ar; // Sentaks hatası.
	 
	int *ptr1 = &ar[0]; // bu 3 tanesi geçerli.
	int *ptr2 = ar.data();
	int *ptr3 = &*ar.begin();
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

DATA

İlk elemanın pointerı/adresi verir.

void set_array_random(int *p, size_t size); // c de yazılmış bir api idi.

int main()
{
	array<int,10> ax{1,2,4,5,6,7,8,9};
	set_array_random(ax.data(), ax.size());
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

CONSTEXPR OLABİLİR ÇÜNKÜ CONSTRUCTORU CONSTEXPR

int main()
{
	constexpr array<int,5> ax = {11,22,33,44,55};

	constexpr auto val = ax[2]; // operator[] da constexpr
}


==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================
==============================================================================================================================================================

3:08

BITSET
------

STL in en çok kullanılan sınıf şablonlarından biri.Bitsel işlemleri daha rahat yapmak bunun amacı
header file bitset. Bitset bir container değil yani begin end gibi funcları yok.Bitset bize dinamik bellek yöetimi olmadan
bir tamsayının bitlerine erişme imkanı veriyor. Bitsel işlemleri hangi amaçla kullanıyorsak bunuda o amaçla kullanacağız.
Nontype parametreye sahip tek parametreli bir sınıf şablonu

Ctorlar unsigned long long parametreli

#include <bitset>

int main()
{
	using namespace std;

	bitset<32> bs; // 32 bitim var
	bitset<16> bs; // 16 bitim var.

	--------------------------------------------------------------------------------------------------------------------------------------------------

	Default ctor tüm bitleri 0 ile başlayıyor.
	bitset<16> bs; 
	std::cout << bs << "\n";
	
	--------------------------------------------------------------------------------------------------------------------------------------------------

	bitset<16> bs{}; // Burada da durumda değişiklik olmaz aynı şekilde 
	std::cout << bs << "\n";

	--------------------------------------------------------------------------------------------------------------------------------------------------

	bitset<32> bs(9823); 
	std::cout << bs<<"\n"; // bitsel değeri neyse yazdırılır.

	--------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << "bir tmsayi girin\n";
	int x;
	cin>>x;

	std::cout << bitset<64>{x} << "\n"; //ctor unsigned long bu sebeple narrwoing conversion sentaks hatası :D
	std::cout << bitset<64>(x) << "\n"; //Geçerli.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------


int main()
{

	bitset<32> x(9823u);
	std::cout << typeid(x[5]).name() << "\n"; // proxy class kullanılmış. std::bitset<32>::reference isimli bir tür
												// Bu türünde bir interface i var.
	

	BU PROXY CLASS INTERFACE INDE NELER VAR
	---------------------------------------

	(constructor)		constructs the reference. Accessible only to std::bitset itself
						(private member function)
	

	(destructor)		destroys the reference
						(public member function)


	operator=			assigns a bool to the referenced bit
						(public member function)


	operator bool		returns the referenced bit
						(public member function)


	operator~			returns inverted referenced bit
						(public member function)
	

	flip				flips the referenced bit
						(public member function)


	--------------------------------------------------------------------------------------------------------------------------------------------------

	bitset<32>x{12345U};
	bool b = x[5];
	bool b = x[5].operator bool(); // Bir yukarıdaki ile aynı.Yani [] operatörünün return değeri olan ürün oprator bool func ı var.cppreference tan
									// interaface e baktık

	--------------------------------------------------------------------------------------------------------------------------------------------------

	if(x[5]) ile  if(x[5].operator bool()) bunun arasında fark yok.
	
	x[3] = true;
	x[5] = false;

	Burada bir tamsayı kullansakta boola otomatik dönüştüğünden, önce tamsayıdan boola sonrada atama işlemi yapılacak.

	x[3] = 1; veya x[3] = 254; yazılabilir.

	--------------------------------------------------------------------------------------------------------------------------------------------------

	Flip Function
	-------------
	Biti ters çevirir.

	cout << x << "\n";
	cout << x[5] << "\n";
	x[5].flip();
	cout << x[5] << "\n";

	BITSETIN AYRI FLIP FUNC I VAR BIRDE ONUN NESTED TYPE OLAN REFERENCE IN AYRI FLIP FUNC I VAR !!!!!!!!!!
	Reference ~ overload edilmiş.

	x[2] = ~x[5]; // 5. indexin tersini 2 . ye atamış.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	unsigned int uval;

	std::cout << "bir tamsayi girin : ";
	cin>>uval;

	bitset<32> bs{uval};
	std::cout << bs << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

SET BIT COUNT

TAMSAYININ SET EDİLMİŞ BİT SAYISINI VERİYOR

int main()
{

	unsigned int uval;

	std::cout << "bir tamsayi girin : ";
	cin>>uval;

	bitset<32> bs{uval};
	std::cout << bs << "\n";

	cout << bs.count() <<"\n"; // kaç tane biri 1 olmuş ise onu döndürüyor.Yani kaç tanesi set edilmiş 

	--------------------------------------------------------------------------------------------------------------------------------------------------

	ANY - ALL - NONE
	-----------------

	cout << boolalpha;

	std::cout << "bs.any() = " << bs.any() << "\n"; // Herhangibir biti 1 ise true döndürür

	std::cout << "bs.all() = " << bs.all() << "\n"; // tüm bitleri 1 ise true döndürür.

	std::cout << "bs.none() = " << bs.none() << "\n"; // hepsi 0 ise true döndürür.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

TIPIK BIR BITSET IDIYOMU VAR. DIYELIMKI BITSET NESNESI BIT VECTOR OLARAK KULLANILACAK.
Çok sık kullanılıyor bu idiyom.

enum color{
	
	White,Gray,Red,Blue,Brown,Black,no_of_colors

};

int main()
{
	bitset<no_of_colors> colors;

	colors[Brown] = true;
	colors[Gray] = false;
	colors[Red] = true;

	------------------------------------------------------------------------------------------------------------------------------------------------

	SET
	---

	colors.set() ; // Sete argüman göndermezsem tüm bitleri set edecek. hepsi 1 oldu
	std::cout << colors;

	------------------------------------------------------------------------------------------------------------------------------------------------
	
	colors.set(2,false); // 2. bitin set edilmesini istedik şimdi. [] ilede yapılabilir tabi.
	std::cout << colors;

	colors[2] = false; //buda aynısı.

	------------------------------------------------------------------------------------------------------------------------------------------------

	RESET
	-----
	Bitleri sıfırlıyor

	bitset<32>bs{123124U};

	std::cout << bs << "\n";

	bs.reset(); // tüm bitleri sıfırlarladı

	std::cout << bs << "\n";

	------------------------------------------------------------------------------------------------------------------------------------------------

	FLIP
	----
	Bitin değerini tersine çevirir.
	index vermezsek hepsini, verirsek sadece o indexteki biti ters çevirir.

	bitset<32>bs{123124U};

	std::cout << bs << "\n";

	bs.flip(); // tüm bitleri ters çevirir.
	bs.flip(5); // 5. indexteki bit flip edildi.

	std::cout << bs << "\n";

}
	
*/
