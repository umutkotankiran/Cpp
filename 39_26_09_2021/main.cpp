/*

Biraz sohbet. Git - valgrind - make - gbd - clang tidy...

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE PTR DEN DEVAM
Özet : Bu bir move only type.move memberları tanımlayınca zaten copy ler delete edilecek. Ama daha sık kullanılan onlarıda fiilen delete etmek. Dİkkat çekmesi için.

Unique ptr nesnesi bir kaynağın tek sahibi. Böyle bir avantajı var. 
C# Java gibi dillerde olduğu gibi garbage collectore benziyor ama değil tabi. Bunu 2. template parametresi yapıyor ve buna deleter deniyor. Bir tür argümanı belirttmezsek
default delete dediğimiz standart tür şablonu açılımı kullanıyor ....

Kaynağın sonlandırılması delete edilsin fakat bir loglamada yapılsın, file kapatılsın, database bağlantısı sonlandırılsın gibi şeyler varsa kendi deleter türümüzü kullanacağız.

Maliyeti var mı? Maliyeti yok. Böyle bir endişeye gerekte yok. Çok ekstrem bir durum olabilir, çok özel bir deleter olabilir ve bellekte yer kaplayabilir 
bundan ötürü olabilir bu ekstrem bir durum.

int main()
{
	std::cout << "sizeof(vector<int>::iterator)" = " << sizeof(vector<int>::iterator)<< "\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE PTR NİN DİĞER ÖZELLİKLERİ

int main()
{
	auto ptr = make_unique<string>("umut kotankiran");
	std::cout << uptr << "\n";
	std::cout << uptr.get() << "\n"; // yazdırma sözkonusu ise ikisi arasında fark yok

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	x = y ; doğrudan atamayı böyle yapamayız.

	x = std::move(y); // Böyle olabilir dedik dün
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Otomatik ömürlü nesneler ile return ettiğimizde 

class Myclass{

};

Myclass func()
{
	Myclass m;

	return m;
}

İhtimaller
1 - Named return value optimization. Copy ellision yapar derleyici
2 - Move memberlar çağrılır

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::unique_ptr<std::string> foo(const char *p)
{
	auto ptr = std::make_unique<std::string>(p); 

	return uptr; // mandatory copy ellision 

	return std::move(uptr); // BU YAPILMAMALI.COPY ELLISIONU BOZAR.
}

int main()
{
	unique_ptr<string> up;
	
	up = foo("neco");
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using usptr = std::unique_ptr<std::string>;

void func(usptr up) 
{
	std::cout << "up : " << (up ? "dolu" : "bos") << "\n"; 
}

int main()
{
	usptr ptr = new string("Necati"); // UNIQUE PTR IN T* PARAMETRELI CTORU EXPLICIT. BU SEBEPLE BURASI HATA. AŞAĞIDAKI GIBI OLMALI.
	
	usptr uptr{new string("necati")};// BÖYLE OLUR

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	func(uptr); // HATA COPY YE KARŞI KAPALI
	
	func(std::move(uptr)); // BURADA MOVE EDILIR VE KAYNAK ÇALINIR.GEÇERLİ.UPTR DE BOŞ HALE GELDİ

	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n"; // boş

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	PARAMETRESI UNIQUE PTR OLAN FUNC I PR VALUIE EXPRESSION ILE ÇAĞIRIRIZ.ÇÜNKÜ COPY OLMAMALI :D:D MOVE OLMALI

	func(unique_ptr<string>{new string{"mustafa aksoy"}});

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	2. ihtimal bir func ın return değerinin unique ptr olması

	func(make_unique<string>("haydar"));

	Hangisini çalıştırırsak çalıştıralım kaynak func kodunun çalışmasıyla sonlanacak. Bu nedenle buna sink deniyor. 

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using usptr = std::unique_ptr<std::string>;

void func(usptr up)
{
	std::cout << "up : " << (up ? "dolu" : "bos") << "\n";
}

using namespace std;

int main()
{
	func(unique_ptr<string>{new string{ "mustafa aksoy" }});
	func(make_unique<string>("haydar")); // Üsttekinde de bunda da hangisi çalışırsa çalışsın kaynak func kodunun çalışmasıyla sonlanacak. Buna isnk deniyor.
										 // Herb sutter bu yapının daha uygun olduğunu düşünüyor. 
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Scott Meyers ise aşağıdakini öneriyor.

using usptr = std::unique_ptr<std::string>;

void foo(usptr &&up) // burada rvalue reference var. Up kullanıldığında buraya gleen nesne kulanılacak.Ama burada bir mülkiyet devri yok.
{
	std::cout << "up : " << (up ? "dolu" : "bos") << "\n";
}

using namespace std;

int main()
{
	usptr uptr{new string("necati")};
	
	foo(std::move(uptr));
	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n";

}

Çıktıda ikiside dolu çıkar.Herhangibir taşıma olmadı.

Fark : Parametreyi referans yapmazsak taşıma yapmış oluyoruz. 
&& de ise sadece bildirime bakarak kaynağı çalıp çalmadığını bilme şansımız yok


==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================


UNIQUE POINTERIN CONTAINERLARDA TUTULMASI
-----------------------------------------

Modern C++ ta move only typeların containerlarda tutulmasını engelleyen senaryo yok ama bazı engellemeler var.Ama genelde bir engel yok.

using usptr = std::unique_ptr<std::string>;

int main()
{
	std::vector<usptr> vec; // vectoru default init edebiliriz.

	vector<usptr> vec(100); // size_t parametreli ctor kullanabiliriz.

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	for(auto : vec) // SENTAKS HATASI ÇÜNKÜ KOPYALAMA YAPMAYA ÇALIŞIYOR.
	{
		std::cout << "up : " << (up ? "dolu" : "bos") << "\n"; 
	}

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	for(auto& : vec) // OK
	{
		std::cout << "up : " << (up ? "dolu" : "bos") << "\n"; 
	}

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	for(auto&& : vec) // OK
	{
		std::cout << "up : " << (up ? "dolu" : "bos") << "\n"; 
	}
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------

	KISITLAMALARDAN BIRI INITIALIZER LIST CTOR KULLANAMIYOR OLMAMIZ. İNIT LIST KULLANINCA ISTESEKTE ISTEMESEKTE KOPYALAMA YAPIYORUZ.

	vector<usptr> vec{usptr{new string{"Ali"}}, usptr{new string{"Ali"}}}; // SENTAKS HATASI
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖĞE EKLEMEK
-----------
Pushback veya insert olsun bunların rvalue reference ve const lvalue refeence overload u var.

using usptr = std::unique_ptr<std::string>;

int main()
{
	using namespace std;

	vector<usptr> vec;

	auto up = make_unique<string>("ali");

	vec.push_back(std::move(up)); // BU GÖNDERİLEBİLİR.
	vec.push_back(usptr{new string{"ali"})}); // BUDA GÖNDERİLEBİLİR.
	vec.push_back(make_unique<string>("ali")); //BÖYLEDE OLABILIR.
	vec.emplace_back(new string{"yusuf yilmaz"}); // HEPSİ OK
}

Böyle bırakırsak bir kaynak sızıntısı olmaz.Nedeni vector nesnesinin hayatı bitince vectorun destructorunun vectorde tutulan öğelerin  destructorlarını çağırması. 
Buradaki öğelerde unique ptr olduğu için bunların dtoru çağrılınca buradaki öğeler delete ediliyor.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bir listemiz olsa,vectordeki öğeleri listeye taşımak istesem bunu nasıl yapabilirim.

vector<usptr> vec;

vec.push_back(std::move(up)); 
vec.push_back(usptr{new string{"ali"})}); 
vec.push_back(make_unique<string>("ali"));
vec.emplace_back(new string{"yusuf yilmaz"});

list<usptr> mylist;

1. yol
------
for(auto &up : vec)
{
	mylist.push_back(std::move(up)); bu şekilde vectördeki öğeleri listeye taşıyabilirim.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. yol
------
list<usptr>mylist{vec.begin(), vec.end()}; //SENTAKS HATASI. ÇÜNKÜ KOPYALAMA YAPIYOR RANGE CTOR

copy(vec.begin(), vec.end(),mylist.begin()); // KOPYALAMA VAR YİNE SENTAKS HATASI

Aşağıda çözümü var
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Hoca Copy in template kodunu yazdı ben yazmıyorum.
copy de kopyalama adımında *destbeg = *beg; gibi bir adım var. burada *destbeg = std::move(*beg); yapsak bir hata olmaz.
Bu amaçla kütüphaneye eklenemiş bir iterator adapter var. Biz mvoe iteratoru dereference ettiğimizde, onu move a argüman olarak gönderiyor.

auto ptr = std::move(*vec.begin()); // Sentaks hatası olmayacak yani.

MAKE_MOVE ITERATOR
------------------
unique_ptr<string> x = *make_move_iterator(vec.begin()); 
Return değeri ayrı bir iterator sınıfı aslında

copy algoritmasında 1. template tür parametresi	normal iterator değilde move iterator olsaydı o zaman copy algoritmasında sorun çıkmayacaktı.
Benzer şekilde range ctorda move iterator kullansaydık bir sorun çıkmayacaktı.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Yola devam
-------------

list<usptr>mylist{make_move_iterator(vec.begin()), make_move_iterator(vec.end())}; // ŞİMDİ GEÇERLİ. MOVE VAR

copy(make_move_iterator(vec.begin()), make_move_iterator(vec.end()),mylist.begin()); // ŞİMDİ GEÇERLİ ARTIK MOVE VAR. Dikkat. mylist make_move_iterator yapılmadı :D:D:D

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. Yol
------
Move ALgoritması	

move(vec.begin(), vec.end(),mylist.begin()); // COPY İLE AYNI İŞİ YAPIYOR AMA *DESTBEG = STD::MOVE(*BEG); İŞLEMİ YAPAN MOVE

DİKKAT : STD::MOVE TÜR DÖNÜŞTÜRME FONKSİYONU İLE KARIŞTIRMA

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

==========================================================================
==========================================================================
==========================================================================
==========================================================================

copy -> kopyalıyor.
copy_backward -> sondan başa doğru kopyalıyor.


move -> taşıyor
move_backward -> Sondan başa doğr taşıyor.

==========================================================================
==========================================================================
==========================================================================
==========================================================================

Move iterator kullandığımız yerde sözkonusu algoritma bir iterator konumundaki nesneyi bir kere kullanacak aksi takdirde çoğunlukla UNDEFINED BEHAVIOR.
İnput iteratorde bu garanti var.(tek sefer kullanma garantisi)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Unique ptr nin en önemli varlık nedenlerinden birini konuşmadık.
Exception Handling

#include "triple.h"

void foo()
{
	throw std::runtime_error{"foo hatasi"};
}

void func()
{
	auto ptr = new Triple{12,56,78}; BURADASI İÇİN DTOR ÇAĞRILMIYORDU
	
	//kodlar ..

	foo();
}

void func()
{

	auto ptr = new Triple{12,56,78};

	try{
		func(); // exception olduğunda dinamik ömürlü nesne delete edilmemiş olacak.
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught " << ex.what() << "\n";
	}
}

ÇIKTI
-----
(12, 56, 78) degerinde 00884EC0 adresinde triple nesnesi hayata geldi
exception caught foo hatasi

Smart pointers burada çok işe yarıyor.Aşağıda smart pointers ile yapıldı.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STACK UNWINDING SÜRECİ ÇOK ÖNEMLİ
SMART POİNTERS KULLANINCA OTOMATİK ÖMÜRLÜ NESNENİN HAYATIDA SONA ERDİRİLDİ

void foo()
{
	throw std::runtime_error{"foo hatasi"};
}

void func()
{

	//auto ptr = new Triple{12,56,78}; Bu olunca DTOR ÇAĞRILMIYOR

	auto ptr = std::make_unique<Triple>{12,56,78};  // BURADA TRIPLE NESNESININ HAYATI SONA ERDİ

	foo();
}

int main()
{
	try{
		func();
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught " << ex.what() << "\n";
	}
}

ÇIKTI
-----
(12, 56, 78) degerinde 00CC4EC0 adresinde triple nesnesi hayata geldi
(12, 56, 78) degerindeki 00CC4EC0 adresindeki triple nesnesinin hayati sona erdi  //DİKKAT !!!
exception caught foo hatasi

==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================


DELETER
-------
Unique Ptr template ine kısaca bakalım

template <typename T, typename D = std::default_delete<T>>
class UniquePtr{
public:
	~UniquePtr()
	{
		D{}(mp);
	}
private:
	T* mp;
};


template <typename T>
struct DefaultDelete{

	void operator()(T *p)
	{
		delete p;
	}
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DELETER YAZALIM

struct TripleDeleter
{
	void operator()(Triple *p)
	{
		std::cout << p << " adresindeki nesneyi delete ediyorum\n";
		delete p;
	}
};

int main()
{
	using namespace std;

	{
		unique_ptr<Triple, TripleDeleter> uptr(new Triple{1,2,3});
	}

	std::cout << "Main devam ediyor\n";
}

ÇIKTI
-----
(1, 2, 3) degerinde 00914EC0 adresinde triple nesnesi hayata geldi
00914EC0 adresindeki nesneyi delete ediyorum
(1, 2, 3) degerindeki 00914EC0 adresindeki triple nesnesinin hayati sona erdi
Main devam ediyor

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++ 20 İLE GELEN BİR ÖZELLİK ÇOK ÖNEM KAZANIYOR.
C++20 çncesinde lambda ifadeleri için oluşturulan closure typeların default ctoru ve copoy assignment funcları delete edilmişti.


int main()
{
	using namespace std;

	auto f = [](Triple *){
		std::cout << p << " adresindeki nesneyi delete ediyorum\"
		delete p;
	};

	{
		unique<Triple, decltype(f)> uptr(new Triple{1,2,3}); // C++ 20 ile geldi C++17 sentaks hatası çünkü arkadaki kod decltype(f) ile bu nesneyi default init ediyor.
	}


	C++17 lambdaların closure typelarınında default ctor yok.C++17 de aşağıdaki gibi yazılabilir.C++20 dede geçerli.
	unique<Triple, decltype(f)> uptr(new Triple{1,2,3},f);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİ DURUMA BAKALIM

int main()
{
	auto f = [](int x){ return x * x;}
	
	auto g = f; // Bu her standarda göre legal. Burada çağrılan copy ctor

	auto h = std::move(f); // Buda eskiden beri geçerli.Move ctoruda var lambdaların

	g = f; // C++20 öncesinde geçersizdi ama şimdi geçerli çünkü copy assignment var.
}

in main()
{
	auto f = [](int x){ return x * x;}

	decltype(f) demek derleyicinin yazdığı closure türü demek

 	decltype(f) y; // bu 2017 standartlarında sentaks hatası çünkü default ctor delete edilmiş.Yukarıdaki durumda buydu
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SETE BAKALIM

int main()
{
	auto f = [](int x, int y){return x % 10 < y % 10;}

	set<int,decltype(f)> myset; // C++17 ile geçerli değil C++20 ile geçerli.

	set<int,decltype(f)> myset(f); // Setin bir overload u argüman olarak callable nesnesinin kendisini istiyor. Bu hem C++ 17 hemde C++20de geçerli.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİ GERÇEK FUNC OLSAYDI

function objeleri ile karıştırma onlar sınıftı. less greater... doğrudan type giriliyordu.

bool mycomp(int x, int y)
{
	return x < y;
}

int main()
{
	set<int,decltype(mycomp)> myset(mycomp); // Burada da yine ilgili func ın adresini argüman olarak göndermemiz gerekiyor.
}

decltype(mycomp) bu türden nesnenin kullanılması demek onun adresinin mycompun değeri olması demek ama mycompu argüman olarak almadan bunu yapamıyor
Function pointer ise başka bir imkan yok. Func adresini argüman olarak göndermemiz gerekiyor.

==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================


New değilde array new ile oluşturulan bir pointer nasıl yönetilir.Bir specialization var bu array delete yapıyor.

#include "triple"
#include <iostream>
#include <memory>

int main()
{
	using namespace std;

	unique_ptr<Triple[]>upr(new Triple[5]);



	//partial specialization kullanmak istemezsek o zaman deleter yazabiliriz.

	auto fdel = [](Triple *p){delete[]p;};
	unique_ptr<Triple, decltype(fdel)> uptr(new Triple[5]); // C++20
	unique_ptr<Triple, decltype(fdel)> uptr(new Triple[5],fdel); // C++20 öncesi

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RUNTIME POLYMORPHISMDE PROBLEM YOK

Bizim car.h den örnek bu

int main()
{
	for(;;)
	{
		unique_ptr<Car> uptr{create_random_car()};
		uptr->start(); //devreye giriyor.Polimorfik sınıflarda da virtual dispatch olanağı devam ediyor. Bir farkı yok
		(void)getchar();
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Myclass;

int main()
{
	std::unique_ptr<Myclass> uptr; // sentaks hatası çünkü incomplete type nesne, hayatı bitince deelte etmesi gerekiyor fakt delete in operandı olması için 
}									// complete type olmalı

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PIMPLE IDIYOMU

class Nec{
	
private:
	struct Pimpl;
	std::unique_ptr<Pimpl> uptr; // Burada bir sorun oluşacak ama onuda aşacağız sonra.Şimdilik bir gönderme
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

En çok kullanıldığı yer fabrika functionları Yani nesne üreten funclar

Car içinden create_random_car üstünde çalıştı.

Smart Pointerlar virtual dispatch mekanizmasını bloke etmiyor.


std::unique_ptr<Car> create_random_car()
{
	switch (rand() % 8)
	{
	case 0: return std::unique_ptr<Bmw>(new Bmw); 
	case 1: return make_unique<Mercedes>();
	...
	...
	... diğerleride yazılabilir.

	}

	return nullptr;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TİPİK YAPILAN HATALAR.
---------------------

int main()
{
	auto p = new Triple{1,4,54};

	unique_ptr<Triple> px{ p };
	unique_ptr<Triple> py{ p };

	std::cout << *px << "\n";
	std::cout << *py << "\n"; // ikiside aynı nesneyi gösteriyor.Bİrinin hayatı biterse diğeri dangling hale gelir. UNDEFINED BEHAVIOR
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto p = new Triple{1,4,54};

	unique_ptr<Triple> px{ p };
	
	auto ptr = px.get(); // px in adresi ptr de.Burası aslında Triple *ptr = px.get() oldu

	unique_ptr<Triple> py{ ptr };  // Aynı durum. 2 sahibi var artık p nin. UNDEFINED BEHAVIOR
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto p = new Triple{1,4,54};

	unique_ptr<Triple> px{ p };

	auto ptr = px.get(); // px in adresi ptr de. Triple *ptr = px.get() oldu burası 

	cout << *ptr << "\n";
	ptr->set(1,3,6);

	BURADA HATA YOK
}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto p = new Triple{1,4,54};

	unique_ptr<Triple> px{ p };

	auto ptr = px.release(); // px mülkiyeti bıraktı ve return değeri tuttuğu adresi ptr ye atandı.

	cout << *ptr << "\n";
	ptr->set(1,3,6);

	BURADA HATA VAR ÇÜNKÜ KİMSE DELETE ETMEDİ BUNU.DELETE EDİLMESİ LAZIMDI
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto p = new Triple{1,4,54};

	unique_ptr<Triple> px{ p };

	auto ptr = px.get(); 

	cout << *ptr << "\n";
	ptr->set(1,3,6);
	delete ptr;

	std::cout << *px << "\n"; // DANGLING POINTER.NEDEN? ÇÜNKÜ PX İN HAYATI BİTİNCE P Yİ DELETE EDECEK AMA BİZ ZATEN PTR YANİ GÖSTERDİĞİ P Yİ KENDİMİZ DELETE ETTİK.
}								// DOUBLE DELETİON. BUDA UNDEFINED BEHAVIOR

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PROGRAMCILARIN EKSİK KALDIĞI YER

BUNU ÖĞRENENLER İLLAHA NEW OPERATORU İLE HAYATA GETİRİLMESİ GEREKTİĞİNİ SANIYORLAR

using namespace std;

int main()
{
	auto ptr = make_unique<Triple>(1,2,3);

	Triple *p = uptr.release();

	p->set(2,4,7);

	std::cout << "*p = " << *p << "\n"; // BURADA HATA YOK AMA EKSIK OLAN TARAF DELETE EDILMEMIŞ.
										// 1. DESTRUCTOR ÇAĞRILMAYACAK, 
										// 2. SIZEOF TRIPLE KADAR OPERATOR NEW FUNC ILE ELDE EDILEN BELLEK BLOĞU GERI VERILMEYECEK.

	std::cout << *uptr << "\n"; // UNDEFINED BEHAVIOR. BURASIDA 2. BÜYÜK HATA
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOK ÖNEMLİ BİR HATA

int main()
{
	auto ptr = make_unique<Triple>(1,2,3);

	unique_ptr<Triple>upx;

	Triple * = uptr.release(); //BU GEÇERLİ

	upx = uptr.release(); // SENTAKS HATASI. ATAMA OPERATÖRÜNÜN SAĞ OPERANDI BİR UNİQUE PTR DEĞİL RAW POINTER.

	BUNU YAPMAK İÇİN
	upx.reset(uptr.release()); // BURASI GEÇERLİ. 
	upx = std::move(uptr); // YUKARIDAKİ İLE AYNI
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE PTR NEW OPERATORLERİYLE OLUŞTURULMUŞ DİNAMİK ÖMÜRLÜ NESNEYİ KONTROL ETMEK ZORUNDA DEĞİL. 
EN ÇOK KULLANILDIĞI YERLERDEN BİRİ C APILERINI SARMALAMAK

C de ctor gibi yapılar yok ama handle sistemi var.C de doğrudan destroy riskini elemine etme şansımız yok. Kontrol edeceğiz.
Handle bir pointer olduğundan bunun bir kopyasını çıkartabiliriz.Buda bir sorun oluşturabilir.

int main()
{
	FILE *f = fopen("haydar.txt","w");
	fprintf(f,"necati");
	//...
	fclose(f);
}


C apileri için unique_ptr kullanabiliriz.

int main()
{
	auto fdel = [](FILE *f){fclose(f);};

	std::unique_ptr<FILE,decltype(fdel)> uptr{fopen("haydar.txt","w")}; // artık güvendeyiz. uptr nin hayatı birince destructoru yukarıdaki fclose u çağıracak.

	std::unique_ptr<FILE, decltype(fdel)> uptr{ fopen("haydar.txt","w"),fdel }; //C++20 öncesi yazım bu
}

C apilerini embedded ve linuxta çok kullanıyoruz

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bir func var return değeri handle. get funclarının varlık sebebi bu. Neden var ? Çünkü pointer parametre isteyen c funclarına çağrı yaparken geti kullanacağız.

int main()
{
	auto fdel = [](FILE *f){fclose(f);};

	std::unique_ptr<FILE,decltype(fdel)> uptr{fopen("haydar.txt","w")};

	fprintf(uptr.get(),"Ali"); // böyle senaryolarda get olmazsa işimizi göremeyiz

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PSUDO CODE

auto mydeleter = [](Handle h){ Destroy_Object(h);};

unique_ptr<Handle, decltype(mydeleter)> uptr(create_object());

foo(uptr.get());
func(uptr.get());

GENEL OLARAK YAPI BÖYLE KURGULANMALI

==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================


LAMBDALARA GERİ DÖNDÜK
----------------------
BURADA EKSİK KALAN YERLER ANLATILACAK

Derleyici lambda ifadeleri karşılığında bir pr value expression oluşturuyordu. Türü closure type, bu türü derleyici isimlendiriyor.
Derleyiciye aslında bir sınıf kodu yazdırıyoruz. Bizim süslü parantez içine yuazdığımız kod sınıfın func call operator functionu.

[](int x){}

[](auto){} derleyici func call operator func ı bir member template olarak yazacak.

[](auto&){} Burada da lvalue reference oldu parametresi
[](auto&&){} Universal/forwarding reference.Dolayısıyla func şablonlarında olduğu gibi böyle bir lambda da aldığımız argümanı perfect forwarding edebiliriz.


PERFECT FORWARDING TE ÇOK ÇOK ÖNEMLİ GÖZDEN KAÇAN DETAY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--------------------------------------------------------------------------------------------
auto f = [](auto&&x){
	
	foo(std::forward<decltype(x)>(x)); // Bu şekilde çağrılır.constluk value category korunur
	
};

auto f = [](auto&& ...args){
	
	foo(std::forward<decltype(args)>(args)...); // Bu şekilde çağrılır.constluk value category korunur
	
};

EN ÖNEMLI KISIM - TEMPLATE OLSAYDI DECLTYPE OLMAYACAKTI ZATEN TÜR T OLACAK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
----------------------------------------------------------------------------------------------------------------
template <typename T>
void func(T &&x)
{
	foo(std::forward<T>(x)); // Dİkkat decltype yok çünkü T ye gelen tür belli
}

template <typename Args>
void func(Args... &&args)
{
	foo(std::forward<Args>(args)...); // Burasıda variadic.
}

==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================

THIS CAPTURE

Lambda ile tanışanlar this keywordunu yanlış kullanıyor.Düşünce biçimi doğru ama kural farklı.
{} içerisinde this kullanınca bunu aslında ilgili closure object in adresini kullanacağım sanıyor ama bu sentaks hatası.

int main()
{
	int x = 10;

	auto f = [](int x){
		std::cout << this->x << "\n"; // SENTAKS HATASI.this->x ile x arasında bir fark olmamalı diye düşünüyor programcı
	};
}

THIS YUKARIDAKI GIBI KULLANILAMAZ.

BIR LAMBDA IFADELERINI FUNCTIONLARIN IÇINDE KULLANIYORUZ GENELDE AMA GLOBAL SCOPETA DA KULLANABILIRIZ.ÇOK BÜYÜK ÇOĞUNLUKJLA FUNC IÇINDE KULLANIRIZ.
BU FUNCLAR GLOBAL FUNCLAR DA OLABILIR VE BIRÇOK DURUMDA LAMBDA IFADESININ BULUNDUĞU FUNCTION BIR SINIFIN MEMBER FUNC I OLACAK.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Nec{
public:
	Nec(int val) : mx {val} { }
	
	void set(int val)
	{
		mx = val;
	}

	void print()const
	{
		std::cout << "("  << x <<  ")";
	}

	--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//void func()
	//{
	//	[]() {mx = 23;}; // BURASI SENTAKS HATASI
	//}


	BUNUN İÇİN BİR SENTAKSA İHTİYAÇ VAR. NESNEYİ CAPTURE ETMEMİZ GEREKİYOR
	----------------------------------------------------------------------
	void func()
	{
		// Bu func hangi nesne için çağrıldıysa onun adresini capture ediyoruz. Compilerın oluşturduğu sınıf türünden nesne adresi değil
		// Bunu yakalamanın yolları var. "This_Capture.jpg" isimli dosyayı proje dosyasına koydum orada yazıyor.

		auto f = [this](int val) {return mx + val;};  // Bu durumda this i copy yoluyla capture ettik. Artık doğrudan mx i kullanabilirim
													  // Buradaki mx, capture edilen Nec sınıf nesnesinin mx i.

	--------------------------------------------------------------------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------------------------------------------------
	NOT: HANGİ STANDARTLARDA GELDİĞİ KAYNAK DOSYASINA KOYDUĞUM RESİMDE YAZIYOR
	[this] ---> *this referans yoluyla yakalanıyor
	[*this] ----> *this kopyalama yoluyla yakalanıyor
	[&] -----> yerel değişkenler + *this referans capture et
	[&,this] -----> yerel değişkenler referans capture et + *this referans capture et
	[&,*this] -----> yerel değişkenler referans capture et + *this copy ile capture et
	[=] ----> herşey + *this referans yoluyla ama depricated oldu *this için olan özellik
	[=,this] ---> Herşey copy + *this referans yoluyla
	[=,*this] ----> Herşey copy, *this te copy

	Tabloya baptıpğımda hep *this capture ediliyor. Koplayama veya referans yoluyla.this in kendisi edilmiyor.
	--------------------------------------------------------------------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------------------------------------------------

		auto f = [this](int val) {return this->mx + val;}; // ister mx istersekte this->mx kullanabiliriz.
		
		f(20); // mx + 20 yi döndürecek mesela
		
	--------------------------------------------------------------------------------------------------------------------------------------------------------

		auto f = [mx](int val) {return mx + val;}; // BU şekilde mx capture edilemez çünkü yerel değişken değil.

	--------------------------------------------------------------------------------------------------------------------------------------------------------
		
		ÖNEMLİ!!!

		[=] görülen her ismi copy  this i ise referans yoluyla capture et C++2020 de this ile ilgili olan depricated
		[&] görülen her ismi referans yoluyla capture et + this te referans

		C++17 ye kadar yukarıdaki ikiside tamamen aynı anlama geliyordu. Bu bir pointer olduğu için this objesi fark yoktu.
		Fakat C++17 de [=] depricated edildi.this capture ederken kullanılmamalı artık. [=] budan sonraki standartlarda sentaks hatası olacak.
		[=] geçerli ama depricated

		Yani this capture ederken [this] veya [&] yapacağız.BU ikiside geçerli. [=] this capture etmek için kullanılmamalı çünkü depricated edildi.

	--------------------------------------------------------------------------------------------------------------------------------------------------------
		
		THIS DEĞILDE *THIS I KOPYALAMA YOLUYLA CAPTURE ETMEK ISTERSEK

		C++11 de yolu yoktu. C++14 te lambda init capture ile yapıyoruz

		auto f = [startthis = *this](){ starthis } ;  // Burada nesnenin kendisini değil kopyasını kullanmış oluyoruz. Bazen gerekiyor. Çünkü bu lambdayı dışarıya vermek
												  //istersek o nesnenin hayatı bittiğinbde this dangling hale gelebilir.

	--------------------------------------------------------------------------------------------------------------------------------------------------------

		C++17 DE BIR EK GELDI. AŞAĞIDAKİ GİBİ KOPYALAMA YOLUYLA CAPTURE EDEBİLİRİZ

		auto f = [*this]()mutable { return ++mx}; // Buradaki mx bu fonksiyon hangi nesne için çaüğrıldıysa onun mx i değil.Ondan COPY YOLUYLA OLUŞTURULMUŞ
													// BAĞIMSIZ BİR MX

	}	
	
private:
	int mx;
};

MOLA

==============================================================================================================================================================================
==============================================================================================================================================================================
==============================================================================================================================================================================


int main()
{
	Nec mynec{12};
	mynec.print();

	mynec.func();
	mynec.print(); // değeri değişmedi ama auto f = [this](){++mx}; böyle olsaydı bu durumda (mutable olmasınada gerek yok çünkü referans yapacak işi) şimdi mx değişir.

}


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

auto f = [this](){
	auto x = *this; // buda legal
};

f();

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA INIT CAPTURE NEDEN EKLENDİ

Move only typeları lambda functionuna doğrudan taşımak mümkün değildi.

#include <memory>

int main()
{
	auto uptr = make_unique<string>("Necati Ergin");
	
	auto f = [&uptr](){std::cou << *uptr<< "\n";}; // Burada uptr yi taşımadık o halen dolu durumda

	f();

	if(uptr)
		std::cout << "Dolu";
	else
		std::cout << "Bos";
		
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UPTR Yİ TAŞIMAK İSTERSEK YANİ MÜLKİYETİNİ LAMBDA İÇERİSİNDEKİ DEVRETMEYİ YAPSIN
C++14 te Lambda İnit capture eklendi. BUrada yapılbiliyor

#include <memory>

int main()
{
	auto uptr = make_unique<string>("Necati Ergin");

	auto f = [uptr = std::move(uptr)](){std::cou << *uptr<< "\n";}; // Şuanda uptr yi taşıdık.

	f(); // artık func scope taki uptr boş durumda.capture dan dolayı

	if(uptr)
		std::cout << "Dolu";
	else
		std::cout << "Bos"; // artık boş çıkacak


ALTERNATİF
----------
auto f = [&uptr](){ 
					auto up  = std::move(uptr); //İçeride move ettik
					std::cout << *uptr<< "\n";
				  };

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN SIK YAPILAN HATALARDAN BİRİ ÖZDEŞ CLOSURE TYPELARI AYNI TÜRDEN SANMAK

auto f = [](int x){ return x + 5; };
auto g = [](int x){ return x + 5; };

Bunlar aynı türden olsaydı

f = g; //SENTAKS HATASI OLMAZDI AYNI OLSAYDI.AYNI TÜRDEN DEĞİLLER

typeid(f) == typeid(g) false verir.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++ 20 ile COPY CTOR VEYA DEFAULT INIT EDEBİLİRİM

int main()
{
	auto f = [](int x){ return x + 5; };
	
	auto g = f; // GEÇERLİ

	decltype(f) g; //C++20 de geçerli eğer stateless değilse yani capture işlemi yapmadıysa.

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	int ival{};
	auto f = [ival](int x){ return x + ival; };

	decltype(f) g; // SENTAKS HATASI ÇÜNKÜ STATELESS DEĞİL. C++20 DE BİLE SENTAKS HATASI

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	auto uptr = make_unique<string>("Necati Ergin");

	auto f = [uptr = std::move(uptr)](){std::cout << *uptr<< "\n";};

	auto g = f; // SENTAKS HATASI.ÇÜNKÜ MOVE ONLY MEMBER VAR SINIFTA. UNIQUE PTR :D:D:D COPY CTOR UNIUE PTR LERİ BİRBİRİNİ COPY EDERKEN HATA ALINCA 
				// COPY CTORU DELETE EDECEK. DELETE EDİLMİŞ FUNC A ÇAĞRI SENTAKS HATASI :D:D:D:

	auto g = std::move(f); // BURADA GEÇERLİ.

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++ 20 İLE GELEN LAMBDA İFADELERİ İÇİN 3 TANE TEMEL DEĞİŞİKLİK VAR

Özdeş lambda ifadeleri farklı closure type üretiyor. C++2020 ile birlikte gelen lambda ifadeleri için 3 tane önemli değişiklik var.

1. STATELES OLAN LAMBDALAR DEFAULT CONSTRUCTIBLE VE COPY ASSIGNABLE.YAZMIŞTIK

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. LAMBDA IN UNEVALUATED CONTEXT.ÖNEMLI BIR EKLENTI.C++20 DER KI EĞER BIR LAMBDA IFADESINI IŞLEM YUAPILMAYAN CONTEXT TE KULLANIRSAN ARTIK BIR SENTAKS HATASI DEĞIL.

int main()
{
	auto fcomp = [](int a, int b){ return a > b; };

	set<int,decltype(fcomp)> myset;// burası C++20 öncesinde lambda lar default constructible olmadığından bu sentaks hatası
	
	set<int,decltype(fcomp)> myset(fcomp);// burası C++20 öncesinde bu geçerli.Kullanım buydu

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	FCOMPU BIR KERE KULLANACAĞIM DEĞŞKEN NEDEN OLUŞTURAYIM.C++20 İLE GELDİ

	set<int,decltype([](int a, int b){ return a > b;})> myset; //GEÇERLİ.C++20 İLE GELDİ. DEĞİŞKEN YARATMADAN YAPTIK.

	--------------------------------------------------------------------------------------------------------------------------------------------------------
	
	MESELA:
	sizeof([](int x){return x*x;});  // SETAKS HATASI DEĞİL.SIZEOF OPERANDI UNEVALUATED CONTEXT OLDUĞUNDAN
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. TEMPLATED LAMBDA

[]() ||"constexpr","noexcept","-> int trailing return type","mutable" || { }  gelebilir

auto f = [](auto x) {} member template yazıyordu.

[]<typename T>(T x, T y){}

Derleyicinin yazacağı template olan operator func ının parametresinin türü oluyor. Burada yine deduction mekanizması devreye giriyor.
Auto ya göre ne farkı var.

int main()
{
	auto f = [](auto x, auto y){
		return x + y;
	};

	f(12,45);
	f(12,4.5); // GEÇERLİ.HER AUTO İÇİN AYRI BİR TEMPLATE PARAMETRESİ YAZIYOR COMPILER. BURADA GÖNDERİLEN ARGÜMANLARIN AYNI TÜRDEN OLMA ZORUNLULUĞU YOK.
				// BUNU YAPMAK İSTESEK ESKİDEN YOKTU.

	VEYA BU FUNC A VECTOR GÖNDERMEK ZORUNLU OLSA DESEK BUNUDA YAPAMAYIZ.

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	ARTIK YAPILIYOR

	auto f = []<typename T>(T x, T y){
		return x + y;
	};

	f(12,23);

	f(12,2.43); //SENTAKS HATASI.AMBIGIUTY

	--------------------------------------------------------------------------------------------------------------------------------------------------------

	MESELA BURADA SADECE VECTOR KABUL EDİYOR.

	auto f = []<typename T>(std::vector<T> x){
		return x;
	};

	f(vector olmalı burası artık)

}


ÖNEMLİ NOT DAHA ÖNCE YAZMIŞTIM. FORWARD EDERKENKİ FARKLILIK


auto f = []<typename T>(T&& x){
		return x + y;
	};
	
func(std::forward<T>(f)); //DİKKAT



auto f = [](auto&& x){
	return x + y;
};

func(std::forward<decltype(x)>(x)); //DİKKAT


*/ 