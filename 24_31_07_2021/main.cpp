/*
Exception Handlingten Devam

Exception gönderildiğinde bu yakalanmazsa terminate functionu çağrılıyor bu da abort
çalıştırılıyor ve program sonlanıyor.Uncought exception durumu oluşursa abort func çağrılıyor demek istiyoruz.

Hatta set_terminate ile abort değilde başka bir func çağrılabilirdi.

Eğer Exception rethrow edilirse fakat rethrow statement bir catch bloğu içinde çağrılmıyorsa bu durumda yine terminate çağrılıyor.
yani mainden func çağırırsak bununda içinde rethrow; varsa, abort çağrılır.

stack unwinding te kaldık.

=============================================================================================================================================
=============================================================================================================================================
=============================================================================================================================================

Stack Unwinding
-----------------------------

Exception gönderildiğinde ve bu yakalanırsa bu hatayı işleyecek(handle edecek) catch bloğuna yönlendiriliyor.
Bu bağlamda birsürü otomatik ömürlü sınıf nesnesi olabilir.F1 en son f20 ye kadar
kümülatif çağrılarla dolu. arada birsürü otomatik ömürlü sınıf var.Exception f20 de
çıkarsa ve  bu f1 de yakalanırsa, arada otomotik ömürlü nesneler için Destructor çağrılacak.Dil yapıyor bunu.Kural.

Bu otomatik ömürlü sınıf nesneleri için geçerli.RAII nesneleriyse korkumuz yok.
Dinamik ömürlüye girince kaynak sızıntısı oluşturan durumlar olabilir.Geçen ders görüldü.

Kaynakları pointerlara bağlamak yerine RAII idiyomunu kullanıyoruz. yani sınıf
değişkenine bağlayabiliriz.

class Myclass{};
void foo();

void func()
{
	Myclass m;
	foo();  
}
Burada programın akışı try bloğuna gidecek hata oluşursa ve yakalandığında destructor çağrılacak.RAII

------------------------------------------------------------------------------------------------------

Raw pointerlarla kaynak yönetimi exception handlingte çok büyük bir risk.

class Myclass{};
void foo();

void func()
{
	Myclass *p = new Myclass;
	
	foo();
	
	delete p; // foo hata yakalayınca bu satır çalışmayacak. Burada memory leak oluştu.
}

sınıfları raw pointerlara bağlamanın böyle bir riski var.
Sadece dinamik ömürlü sınıf nesneleri için değil, raw pointer ile tutulan herşey için geçerli.
Geçen ders FILE * lı bir örnek vermiştik. Dosya hiç kapanmıyordu exception throw edildiğinde.Onu yazmıyorum. 9:30
Burada da RAII den faydalanabiliriz.File nesnesini tutan bir class nesnesi ile nesneyi tutabilirdik.O da kapatabilirdi.

RAW POINTERLARLA KAYNAK YÖNETIMI EXCEPTION HANDLING ACISINDAN ÇOK BÜYÜK BİR RİSK.
NEW OPERATÖRÜ İLE OLUŞTURULMUL SINIF NESNELERİDE DAHİL.
BUNUN ILACI SMART POINTER SINIFLARI. İLERIDE GÖRÜLECEK.
UNIQUE PTR VE SHARED PTR DE AYRINTILI GÖRÜLECEK.

------------------------------------------------------------------------------------------------------------------------

#include <iostream>

class Resource {
	int m_x;
public:
	Resource(int x) : m_x{ x }
	{
		std::cout << "Resource (" << x << ") kaynak edinildi\n";
	}
	~Resource()
	{
		std::cout << "Resource nesnesi icin kaynaklar geri verildi " << m_x << "\n";
	}
};

void f4()
{
	std::cout << "f4 cagrildi\n";
	Resource r{ 4 };
	throw 1;
}
void f3()
{
	std::cout << "f3 cagrildi\n";
	Resource r{ 3 };
	f4();
}
void f2()
{
	std::cout << "f2 cagrildi\n";
	Resource r{ 2 };
	f3();
}

void f1()
{
	std::cout << "f1 cagrildi\n";
	Resource r{ 1 };
	f2();
}

int main()
{
	try {
		f1(); 
	}
	catch (int) {
		std::cout << "hata yakalandi\n";
	}
}


ÇIKTI
-----
f1 cagrildi
Resource (1) kaynak edinildi
f2 cagrildi
Resource (2) kaynak edinildi
f3 cagrildi
Resource (3) kaynak edinildi
f4 cagrildi
Resource (4) kaynak edinildi
Resource nesnesi icin kaynaklar geri verildi 4
Resource nesnesi icin kaynaklar geri verildi 3
Resource nesnesi icin kaynaklar geri verildi 2
Resource nesnesi icin kaynaklar geri verildi 1
hata yakalandi

---------------------------------------------------------------------------

EĞER try catch  kullanılmasaydı destructorlar çağrılmadan abort edilecekti.
int main()
{
	f1();
}

ÇIKTI 
-----
f1 cagrildi
Resource (1) kaynak edinildi
f2 cagrildi
Resource (2) kaynak edinildi
f3 cagrildi
Resource (3) kaynak edinildi
f4 cagrildi
Resource (4) kaynak edinildi

---------------------------------------------------------------------------

Nesneler DİNAMİK ÖMÜRLÜ olsaydı

Class tanımını varsay

void f4()
{
	std::cout << "f4 cagrildi";
	auto pr = new Resource(4);
	throw 1;
	delete pr;
}
void f3()
{
	std::cout << "f3 cagrildi";
	auto pr = new Resource(3);
	f4();
	delete pr;
}
void f2()
{
	std::cout << "f2 cagrildi";
	auto pr = new Resource(2);
	f3();
	delete pr;
}
void f1()
{
	std::cout << "f1 cagrildi";
	auto pr = new Resource(1);
	f2();
	delete pr;
}

int main()
{
	try{
		f1();
	}
	catch(int){
		std::cout << "hata yakalandi\";
	}
}

Dinamik ömürlü nesneler için Dtor çağrılmadı.

ÇIKTI
-----
f1 cagrildiResource (1) kaynak edinildi
f2 cagrildiResource (2) kaynak edinildi
f3 cagrildiResource (3) kaynak edinildi
f4 cagrildiResource (4) kaynak edinildi
hata yakalandi


BURADA PROGRAMCI SMART POINTER KULLANMALIYDI.

---------------------------------------------------------------------------

#include <iostream>
#include <memory>


Class tanımını varsay

void f4()
{
	std::cout << "f4 cagrildi";
	std::unique_ptr<Resource>uptr(new Resource(4));
	throw 1;
}
void f3()
{
	std::cout << "f3 cagrildi";
	std::unique_ptr<Resource>uptr(new Resource(3));
	f4();
}
void f2()
{
	std::cout << "f2 cagrildi";
	//std::unique_ptr<Resource>uptr(new Resource(2)); //Böylede yazılabilir
	auto uptr = std::make_unique<Resource>(4); // bir sınıf nesnesi oluşturdu.uptr

	f3();
}
void f1()
{
	std::cout << "f1 cagrildi";
	std::unique_ptr<Resource>uptr(new Resource(1));
	f2();
}

int maib()
{
	try{
		f1();
	}
	catch(int){
		std::cout << "hata yakalandi\";
	}
}

ÇIKTI
-----
f1 cagrildiResource (1) kaynak edinildi
f2 cagrildiResource (4) kaynak edinildi
f3 cagrildiResource (3) kaynak edinildi
f4 cagrildiResource (4) kaynak edinildi
Resource nesnesi icin kaynaklar geri verildi 4
Resource nesnesi icin kaynaklar geri verildi 3
Resource nesnesi icin kaynaklar geri verildi 4
Resource nesnesi icin kaynaklar geri verildi 1
hata yakalandim


Modern C++ ta new operatörünü sayılı durumlar dışında kullanmıyoruz.
Raw pointer düşük seviyeli kodlarda kullanılıyor. Smart pointerlarla dinamik ömülü nesnelerin hayatı kontrol ediliyor artık.


=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================


NOEXCEPT SPECIFIER AND NOEXCEPT OPERATOR
----------------------------------------
Bu ikisi birbiriyle ilişkili ama aynı şey değil. Sınıfların exception safety ile ilgili bazı güvenceler vardı.

Önce bir hatırlatma.Bu geçen ders detaylı anlatıldı.
Exception safety ile ilgili verilen garantiler/güvenceler var.

Basic Guarantee : State değişebilir ama herhangibir resource memory leak yok.Invalidation yok
Strong Guarantee : Basic + Herhangibir state değişikliğide olmuyor.Commit or rollback
Nothrow Guarantee : Exception throw etmeyecek.garanti veriyor.Buna güvenerek kod yazılabilir
					A - Buna güvenebilir.
					B - Derleyici buna güvenebilir

B Şıkkını açıklayalım:
Derleyiciler code optimization yapıyor. 2 tane optimizasyon karıştırılıyor.
C de bu kod üretme aşamasında optimizer modülü bunu yapıyordu.for içindeki
değişkenin döngü dışına alınması, bazı kodların tamamen çıkarılması dead code elemination, döngü açılımı loop unrolling ... gibi.

NOT : C++ Abstract Machine bir derste anlatılacak.

2. Generic programlama paradigmasıyla beraber verilen ikicni bir optimizasyon var.
Derleyici compile time de bizim için code yazabilen bir program. Henüz tanışmadığımız bir optimizasyon var.
Derleyici compile time da edindiği bilgilere göre farklı kodlar yazabiliyor bizim için.
Mesela belirli güvenceler varsa kopyalama yerine taşıma işlemi yapıyor, ama belirli güvenceler yoksa kopyalama yapabiliyor...

Kopyalama yerine Taşıma semantiği kullanılması yani.

--------------------------------------------------------------------------------------------------------------------------------------

Exception Specification vardı ama C++17 ile kaldırıldı. Bu sebeple bu konu detaylı anlatılmayacak.

void func()throw(); Mesela bu geçmişe ait.
void func()throw(std::bad_alloc); Buda öyle
Hangi türlerden hata gönderebileceğini anlatıyordu.

void func()throw(); bu ise exception göndermeme garantisi veriyordu.
bunlar artık bitti.Artık yok.

ÖNERİ : Bu konuyu hiç öğrenmeyin diyor hoca !!! 

Modern C++ ta noexcept keyword eklendi.
Bu hem belirleyici hemde operator

======================================================================================================================================
======================================================================================================================================
======================================================================================================================================


NOEXCEPT SPECIFIER
------------------

Bir function bildirildiğinde noexcept keywordünü parametre parantezinden sonra kullanırsak
bu keyword functionun exception göndermeme garantisi verdiğini anlatıyor.

void func()noexcept;

İster global ister static/nonstatic member olsun ister special member func olsun,
noexcept ile nitelersek bu functionun exception throw etmeyeceğini derleyice ve okuyana söylemiş ouyoruz.

class Myclass
{
public:
	void foo()const noexcept; // noexcept garantisi verilmiş
	static int sf()noexcept; // noexcept garantisi verilmiş
};

--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------


BUNU KULLANMANIN 2 YOLU VAR.
----------------------------

1. DOĞRUDAN NOEXCEPT YAZMAK
-----------------------------
void bar(); // bu noexcept garantisi vermiyor.Exception throw etme ihtimali var.
void bar() noexcept; // Bu ise garanti veriyor.Exception throw etmeyecek.


2. NOEXCEPTTEN SONRA PARANTEZ VE IÇINE CONSTANT EXPRESSION
----------------------------------------------------------
Derleme zamanı ifadesi. Boolean veya booleana compile time da dönüşebilecek ifade olacak.
Bu ifade true ise exception vermeme garantisi veriyor, false ise exception verebilir, herhangibir garanti yok.
Yani exception verip vermemesini bir koşula bağlamış oluyoruz.

void func()noexcept(true);
void func()noexcept; Bu yukarıdaki ile aynı anlamda. Exception throw etmeme garantisi verdi

void foo()noexcept(false);
void foo();	Böyle yazmaklada arasında fark yok.Exception throw etmeme garantisi vermedi.
			exception veredebilir, vermeyedebilir.


class Myclass {};
void foo()noexcept(std::is_nothrow_assignable_v<Myclass>);   Böyle birşey de olabilirdi.

Şu ana kadar noexcept bir specifier olarak kullanıldı sırada operator olarak kullanılması var.

======================================================================================================================================
======================================================================================================================================
======================================================================================================================================

NOEXCEPT OPERATOR
-----------------
Operand olarak bir ifade alıyor.İfadenin Nothrow garantisi verilip verilmediğine bakılıyor.

int main()
{
	int x = 10;
	noexcept(x+10); // Bu bir compile time operatorü.Bir logic değer üretiyor. Aynı zamanda sabit ifadesi.
					// Aynı zamanda operand yine UNEVALUATED CONTEX. decytype ve sizeof gibi.
}

-----------------------------------------------
NOT : Unevaluated context oluşturan operatorler
      sizeof
      decltype
      noexcept
      typeid (sonraki ders görülecek)
-----------------------------------------------


noexcept in operandı olan ifade unevaluated contex
noexcept(x++); x 1 artırılmaz

constexpr auto b = noexcept(x++);  //noexcept constant expr olmasaydı/aynı zamanda compile time operatörü, constexpr b ye atanamazdı zaten.
b nin değeri true.


constexpr auto b = noexcept(Myclass{});
Myclass ın Default Ctoru, noexcept garantisi verirse true. B true çıktı demekki bu garantiyi veriyor.
Myclass ın default ctoru noexcept olduğu ortaya çıktı.

constexpr auto b = noexcept(std::cout << x); burada ise garanti verilmiyor.
b nin üstüne imleci getirince görülüyor.

class Myclass{
public:
	//Myclass(int);  Noexcept garantisi yok
	//Myclass(int)noexcept;  Burada noexcept garantisi var
	//Myclass(int)noexcept(noexcept(std::cout << 1)); Burada da yok.Myclass ın exception throw edip etmeyeceği noexcept(std::cout << 1) buraya bağlı.
	//Myclass(int)noexcept(noexcept(std::is_nothrow_assignable<std::string>::value) && noexcept(std::cout << 1)); Koşul baya karmaşık.Argüman az verildi çokta önemli değil
};


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


SINIFIN SPECIAL MEMBER FUNCLARI
-------------------------------
Burada noexcept garantisini derleyici kendi saptıyor.

class Myclass{
private:
	int x;
	std::string ms;
};

Bu sınıfın default ctorunun noexcept garantisi verip vermediğini kendisi saptayacak. 
Derleyici compile time da elemanlara bakacak, elemanların hepsi default init edildiğinde bu işlemlerin
nothrow garantisi varsa, derleyicinin oluşturduğu default ctorda nothrow / noexcept garantisi verir.

BUna bakabiliriz.

int main()
{
	cout << is_nothrow_constructible_v<Myclass> <<"\n"; // true ise Myclass için compilerın yazdığı Default Ctor noexcept edilecek.
														// Bu garanti aslında elemanlara bağlı.

	cout << is_nothrow_copy_constructible_v<Myclass> <<"\n"; // Bu garantiyi vermediğini yazdırdık.Neden vermiyor çünkü stringin Copy Ctoru noexcept garantisi vermiyor.

	cout << is_nothrow_move_constructible_v<Myclass> <<"\n"; // Burada ise verdiğini gördük.
}

Nothrow garantisi vermesi derleyicinin ürettiği kodun performansı açısından hayati önem taşıyor.
move ctor ve move assignment konusu

------------------------------------------------------------------------------------------------------------------------------------

NOT !!!!!
Special member func ı biz bildirirsek artık bunun noexcept olup olmamasından biz sorumluyuz.
Derleyici kendisi default ediyorsa bu garantiyi derleyici verecek yada vermeyecek. 

class Myclass{
public:
	Myclass();
	Myclass(Myclass&&)noexcept;
private:
	int x;
	std::string ms;
};

int main()
{
	std::cout << is_nothrow_move_constructible_v<Myclass> <<"\n"; //true değerini verir.Çünkü nothrow garantisini verdik.
}

------------------------------------------------------------------------------------------------------------------------------------

class Myclass{
public:
	Myclass();
	Myclass(Myclass&&) = default; //dikkat
private:
	int x;
	std::string ms;
};

int main()
{
	constexpr auto b = std::is_nothrow_move_constructible_v<Myclass>; // true verir

	std::cout << std::is_nothrow_move_constructible_v<Myclass> <<"\n"; //yine true değerini verir.2 şekilde de kontrol ettik.
}

string sınıfının move ctoru nothrow garantisi verdiği için, myclass ında move ctoruda nothrow 
garantisi veriyor.

------------------------------------------------------------------------------------------------------------------------------------

class A{
public:
	A();
	A(A&&);
};

class Myclass{
public:
	Myclass();
	Myclass(Myclass&&) = default; //dikkat
private:
	int x;
	A ax;
};

int main()
{
	constexpr auto b = std::is_nothrow_move_constructible_v<Myclass>; // Şimdi false oldu çünkü A yı biz tanımladık ve move ctoru
																		// noexcept değil.

	std::cout << std::is_nothrow_move_constructible_v<Myclass> <<"\n"; //2 şekilde de kontrol ettik.
}


------------------------------------------------------------------------------------------------------------------------------------


C++20 de kural geldi.
Hem default edip hemde noexcept garantisini yine verilmesini talep edebiliyoruz.

class A{
public:
	A();
	A(A&&);
};

class Myclass{
public:
	Myclass();
	Myclass(Myclass&&)noexcept = default; //dikkat
private:
	int x;
	A ax;
};


Hem noexcept edip hemde default edebiliyoruz. C++ 20 ile geldi buda

-------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------


1.
Bazı functionların nothrow vermesi gerekiyor.Vermemesi anormal durum.
Destructor mesela böyle.noexcept herzaman.Bunu değiştiremeyiz.
Destructor istesekte istemesekte yazsakta yazmasakta her zaman noexcept

class Myclass{
public:
	~Myclass(); // bunu yorum satırı yapsakta yapmasakta nothrow
};

int main()
{
	constexpr auto f = std::is_nothrow_destructible_v<Myclass>; //burada her iki durumda görülür.true
}

---------------------------------------------------------------------------

2.
Move Ctor , swap 
Aksi bir mecvuriyet olmadığı sürece noexcept olmalı yukarıdakiler.
Cppreference dan bazu sınıfların bazı funclarına bakıldı.

Bunlar neden noexcept olmalı?
Derleyicinin ürettiği kodda belirli yerlerde kopyalama yapılacak ama belirli sınıflar için 
kopyalama yerine daha verimli olması taşıma yapılacak. 

Öyle yerler varki derleyici bizim için kod üretiyor(daha çok generic programlama paradigmasında)
ürettiği kodda kopyalama mı taşımamı yapsın ? Özel durum yoksa taşıma daha verimli olur.

Öyle durumlar varki kopyalama yerine taşıma yapılası strong exception garantiyi bozuyor.
Çünkü derleyici strong exp garanti vermesi için o taşımaya konu sınıfın move ctorunun 
compile time da noexcept olup olmadığına bakıyor.compile time da yapıyor.
Çünkü strong garanti için, eğer taşıma yapacaksak, taşımaya konu sınıfın move ctorununda 
noexcept olması gerekiyor.Eğer noexcept değilse, bende strong garanti veremem diyor compiler.
Move yerine copy ctor kullanacağım diyor.


ÖR:Bilinmeyen araçlar kullanılabilir bu örnekte.


class Person {
private:
	std::string name_;

public:
	Person(const char* pname) : name_{ pname } { }
	std::string getName()const
	{
		return name_;
	}
	Person(const Person& p) : name_{ p.name_ }
	{
		std::cout << "COPY " << name_ << '\n';
	}
	Person(Person&& p) : name_{ std::move(p.name_) }
	{
		std::cout << "MOVE " << name_ << '\n';
	}
};

int main()
{
	using namespace std;

	vector<Person> pvec{ "Cahit sitki taranci","Ahmet musip diranas","fazil husnu daglarca" };

}

ÇIKTI
-----
COPY Cahit sitki taranci
COPY Ahmet musip diranas
COPY fazil husnu daglarca

3 defa copy ctor çağrıldı. isimlerden person nesnesi oluşturuldu ve bu oluşturulan person nesneleride
copy ctor ile vector ün sağladığı bellek alanına kopyalandı


---------------------------------------------------------------------------------------------------------

class tanımlı varsay

int main()
{
	using namespace std;

	vector<Person> pvec{ "Cahit sitki taranci","Ahmet musip diranas","fazil husnu daglarca" };

	pvec.push_back("Ahmet hamdi tanpinar"); // bunu ekledik
}

NOt: taşımada sadece ptr kopyalanıyordu. kopyalamada deep copy yapılıyor.

Vectorümüzün size ve capacity si 3. pushback işlemini yapınca yeni bir bellek alanı allocate edilecek
kapasite 3 ten 6 ya çıkmış olsun diyelim.Move ctor noexcept değil.
Derleyici vector sınıfı için Copy Ctoru kullanacak bir kod üretecek çünkü move ctor çağrılırsa ve exception
throw ederse strong garanti verme ihtimali kalmıyor push_back in.

Dolayısı ile taşıma yerine kopyalama yaptığını göreceğiz.

ÇIKTI
-----
COPY Cahit sitki taranci
COPY Ahmet musip diranas
COPY fazil husnu daglarca
MOVE Ahmet hamdi tanpinar
COPY Cahit sitki taranci
COPY Ahmet musip diranas
COPY fazil husnu daglarca

---------------------------------------------------------------------------------------------------------


Kodda değişiklik yapacağız. move ctoru noexcept yapalım.

class Person {
private:
	std::string name_;

public:
	Person(const char* pname) : name_{ pname } { }
	std::string getName()const
	{
		return name_;
	}
	Person(const Person& p) : name_{ p.name_ }
	{
		std::cout << "COPY " << name_ << '\n';
	}
	Person(Person&& p) noexcept : name_{ std::move(p.name_) } // bu satıra dikkat.
	{
		std::cout << "MOVE " << name_ << '\n';
	}
};

int main()
{
	using namespace std;

	vector<Person> pvec{ "Cahit sitki taranci","Ahmet musip diranas","fazil husnu daglarca" };

	pvec.push_back("Ahmet hamdi tanpinar"); // bunu ekledik
}

ÇIKTI
-----
COPY Cahit sitki taranci
COPY Ahmet musip diranas
COPY fazil husnu daglarca
MOVE Ahmet hamdi tanpinar
MOVE Cahit sitki taranci
MOVE Ahmet musip diranas
MOVE fazil husnu daglarca

Ciddi fark var.Bu vector 100000 tane person tutsaydı ve reallocation olsaydı move ctor noexcept olmadığı zaman eski bellek alanındaki 100000 string nesnesinin
yenisine aktarılması için person sınıfının copy ctoru çağrılacaktı ama şimdi move ctor çağrılmış oldu.Bunu sağlayan move ctorun noexcept olması.

Person sınıfının move ctorunu derleyici yazmış olsaydı o zaman derleyici noexcept garantisi verecek miydi?
O zaman derleyici elemanlara bakacaktı, elemanların move ctoru noexcept garantisi verirse bizimkide noexcept garantisi verecekti.


==================================================================================================================================================================
==================================================================================================================================================================


Constructor ve Exception Handling
---------------------------------
1 - Ctorun bir nesneyi hayata getiriyor ve return değeri kavramı yok. CTor işini yapamazsa, return değeriyle
hatayı bildirme şansı yok. 

2 - Global bir nesne veya bir out parametreye yazabilir dersek,
bu durumda ctorun kodu tamamlandığı için nesne hayata gelmiş olacak(Bir nesnenin hayata gelmiş olması için ctor kodu sonuna kadar çalışacak), 
nesne hayata gelmiş statütüsünde ama işlevini yerine getiremeyecek bir sınıf nesnesi olacak. Zombie object deniyor buna.
Teorik olarak hayatta ama ctor işlevini yerine getirecek şekilde oluşturamadığı için kullanılamaz durumda.
Bu nesneyi kullananlar ya tanımsız davranış olur yada sınıf query function verecek ve her nesne yaratıldığında onun zombie olup olmadığını test edecek.
Mecbur değilsek başka seçeneklere, Ctor exception throw etmeli. 


Ctor exception throw ettiğinde nesne hayata gelmemiş oluyor ama veri elemanları hayatta.Nesne hayatta olmadığı için exception yakalansa dahi destructor çağrılmayacak.

class Myclass{
public:
	Myclass()
	{
		std::cout << "Myclass Ctor\n";
		throw 1;
	}
	
	~Myclass()
	{
		std::cout << "Myclass Dtor\n";
	}
};

int main()
{
	try{
		Myclass m; // Burada hayata gelmiş bir nesne yok.couttaki yazar ama başarılı birşekilde sonuna kadar çalışmadığı için dtor çalışmaz
	}
	catch(int)
	{
		std::cout <<"hata yakalandi\n"; 
	}
	// main bitince dtor çağrılmaz.
}

ÇIKTI
-----
Myclass Ctor
hata yakalandi

ÖNEMLİ : Böyle bir ctorda kaynaklar edindiysek ve bunları sınıf nesnelerine bağlamak yerine pointerlara bağlarsak
ve bu pointerları destructor bir şekilde delete ediyorsa, dtor burada çağrılmayacak.Memmory leak oluşuyor yine.Aşağıda örnek var



------------------------------------------------------------------------------------------------------------------------------------

struct A{
	A()
	{
		std::cout << "Ctor kaynak edindi";
	}
	~A()
	{
		std::cout << "Dtor kaynakları geri verdi";
	}
};

class Myclass{
public:
	Myclass() : mp {new A}
	{
		std::cout << "Myclass Ctor\n";
		throw 1;
	}

	~Myclass()
	{
		std::cout << "Myclass Dtor\n";
		if(mp)
			delete mp;
	}
private:
	A *mp;
};

int main()
{
	try{
		Myclass m; // Burada hayata gelmiş nesne yok.couttaki "Myclass Ctor" yazar ama başarılı birşekilde çalışmadığı için dtor çalışmaz
	}
	catch(int)
	{
		std::cout <<"hata yakalandi\n";
	}
	// main bitince dtor çağrılmaz.
}

ÇIKTI
-----
Ctor kaynak edindi
Myclass Ctor
hata yakalandi


Myclassın ctoru dinamik ömürlü bir A nesnesi oluşturdu ama ctorun ana bloğundaki kodlar exception throw etti.
Bu durumda dtor çağrılmadı ve buradaki dinamik ömürlü nesne delete edilmemiş olacak yani dtoru çağrılmamış olacak.
Ctor içinde edindiğimiz kaynakları bu şekilde ptr lara bağlamak riskli.Exception throw edilince nesne hayata gelmemiş olacak,
nesnenin dtoru çağrılmamış durumda olacak ve hataya kadar alınan kaynaklar geri verilmemiş olacak

Bu durumda ya ctor içinde kontrollü kod yazıp, nesneyi kaynağa exception throw etmeden geri vereceğiz yada kaynağı
smart pointera bağlamak mantıklı.

------------------------------------------------------------------------------------------------------------------------------------

Smart Pointer ile yapıyoruz

struct A {
	A()
	{
		std::cout << "Ctor kaynak edindi";
	}
	~A()
	{
		std::cout << "Dtor kaynakları geri verdi";
	}
};

class Myclass{
public:
	Myclass() : uptr {new A}
	{
		std::cout << "Myclass Ctor\n";
		throw 1;
	}

	~Myclass() // smart pointer kullanınca destructor içinde delete gerekte kalmadı artık.
	{
		std::cout << "Myclass Dtor\n";
	}
private:
	std::unique_ptr<A> uptr;
};

int main()
{
	try{
		Myclass m; // Burada hayata gelmiş nesne yok.couttaki yazar ama başarılı birşekilde çalışmadığı için dtor çalışmaz
	}
	catch(int)
	{
		std::cout <<"hata yakalandi\n";
	}
	
}

ÇIKTI
-----
Ctor kaynak edindi
Myclass Ctor
Dtor kaynaklari geri verdi
hata yakalandi

Bu durumda myclass sınıfının ctoru, elemanlar initialize edildikten sonra, anabloğu içinde exception throw ederse , eleman sınıf nesnesi olduğu için
STACK UNWINDING sürecinde eleman olan sınıf nesnesi için destructor çağıracak.Unique ptr nin dtorunun çağırması onun hayatını kontrol ettiği dinamik
ömürlü A nesnesi için destructor çağrılması anlamına geliyor.



------------------------------------------------------------------------------------------------------------------------------------

A nın ctoru exception throw etseydi

struct A{
	A()
	{
		throw 1;
	}
	~A()
	{
		std::cout << "Dtor A\n";
	}
};

class Myclass{
public:
	Myclass()
	{
		throw 1;
	}

	~Myclass()
	{
		std::cout << "Myclas Dtor\n";
	}
private: 
	A mp; //dikkat
};

int main()
{
	try{
		Myclass m; 
	}
	catch(int)
	{
		std::cout <<"hata yakalandi\n";
	}
}

ÇIKTI
-----
hata yakalandi

Myclass veya A nın destuctoru çağrılmadı. Çünkü daha A da iken exception throw etti. A bile yaratılmadı. Bu sebeple Myclassta
yaratılmadı ve destructor çağrılmadı ikisi içinde.


------------------------------------------------------------------------------------------------------------------------------------

BUNU BEN EKSTRADAN YAPTIM

class A {
public:
	A()
	{
		std::cout << "A default ctor\n";
	}
	~A()
	{
		std::cout << "A default dtor\n";
	}
};

class Myclass {
public:
	Myclass()
	{
		std::cout << "Myclass default ctor\n";
		throw 1;
	}
	~Myclass()
	{
		std::cout << "Myclass default dtor\n";
	}

private:
	A ax;
};

int main()
{
	try {
		Myclass m;
	}
	catch (int)
	{
		std::cout << "Hata yakalandi\n";
	}
}

A default ctor
Myclass default ctor
A default dtor
Hata yakalandi		

Burada ise A yaratıldı ama Myclass nesnesi yaratılamadı çünkü exception throw etti.
Bizde yakaladık bunu ve catch e girmeden A nesnesi için Dtor çağrıldı. STACK UNWINDING

------------------------------------------------------------------------------------------------------------------------------------

class A{};
class B{};
class C{};


class Myclass{
private:
	A ax;
	B bx;
	C cx;
};

Myclass::Myclass() : ax(expr), bx(expr), cx(expr)
{
	throw 1;
}


Bu durumda ax bx ve cx hayata gelmiş olacaktı ve hepsi içinde destructor çağrılacaktı.

C nin desturctoru throw etseydi, ax ve bx hayata gelmiş olacaktı ve ax bx için destructor çağrılacaktı cx ve myclass için çağrılmayacaktı.

Yani ctor içindeki elemanları raw pointerlara değilde smart pointerlara bağlayın, ctor exception throw etse dahi stack unwinding sürecinde
hayata gelmiş elemanlar için dtor çağrılacak.



--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR BELLEK SIZINTISI OLUR MU?

int main()
{
	Myclass m;
}

Diyelim ki ctor exception throw etti. Bu nesne için ayrılan bellek alanı geri verilecek mi? Evet bu derleyicinin ürettiği kodun sorumluluğunda.

-------------------------------------------------------

Bu dinamik ömürlü nesneler içinde önemli.

#include <iostream>
#include <vector>

class Myclass {
public:
	Myclass()
	{
		throw 1;
	}
	~Myclass()
	{
		std::cout << "Myclass Dtor\n";
	}
private:
	unsigned char buffer[1024];
};

int main()
{
	try {
		auto p = new Myclass; //burada operator new func sonrada constructor çağrılıyordu kısaca.
	}
	catch (int)
	{
		std::cout << "Hata yakalandi\n";
	}
}

YUKARIDA CTOR KODUNDAN ÖNCE OPERATOR NEW FUNC ÇALIŞIR VE SIZEOF(MYCLASS) I ARGÜMAN GÖNDERIR VE BU KADAR YER AYIRIR, BU ALLOCATE EDEN YERI GERI VEREN
OPERATOR DELETE FUNCTIONU, BU NE ZAMAN ÇAĞRILIR, BU NESNE DELETE EDILDIĞINDE. PEKI CTOR EXCEPTION THROW EDERSE OPERATOR DELETE FUNC ÇAĞRILACAK MI? EVET BUDA 
YINE DILIN GARANTISI ALTINDA.

ÇIKTI
----
Hata yakalandi   

Bir alttakinde daha iyi görülecek.

----------------------------------------------------------------------------------------------------------

Buradan sonra operator new ve operator delete overload ediliyor böylece bunların çağrıldığını göreceğiz.

void* operator new(std::size_t sz)
{
	std::cout << "Operator New called\n";
	if(sz == 0)
	{
		++sz;
	}

	if(void *pd = std::malloc(sz))
		return pd;

	throw std::bad_alloc{};

}

void operator delete(void *vp)noexcept
{
	std::cout << "Operator delete called\n";
	free(vp);
}

class A{
public:
    A()
    {
        std::cout << "A Called\n";
    }
    ~A()
    {
        std::cout << "~A Called\n";
    }
};

class Myclass {
public:
    Myclass()
    {
        std::cout << "Myclass Ctor\n";
        throw 1;
    }
    ~Myclass()
    {
        std::cout << "Myclass Dtor\n";
    }
private:
    A ax;
};

int main()
{
	try {
		auto p = new Myclass; 
	}
	catch (int)
	{
		std::cout << "Hata yakalandi\n";
	}
}


ÇIKTI
-----
Operator New called
A Called
Myclass Ctor
~A Called
Operator delete called
Hata yakalandi


Bazıları bu kuralı bilmediği için buradaki bellek bloğunu geri vermeye çalışıyorlar.
Eğer ctor exp throw ederse fakat nesne dinamik olarak oluşturulduysa, Dtor çağrılmasada operator new tarafından elde edilen sizeof sınıf türü kadar
bellek bloğu(biz delete çağırmasakta) derleyicinin ürettiği kodda operator delete func çağrılacak.

Dil bunu garanti ediyor.Yani tekrar free etmeye gerek yok.

----------------------------------------------------------------------------------------------------------

BU ÖRNEĞİDE BEN EXTRADAN YAPTIM

class A {
public:
	A()
	{
		std::cout << "A default ctor\n";
	}
	~A()
	{
		std::cout << "A default dtor\n";
	}
};

class Myclass {
public:
	Myclass()
	{
		std::cout << "Myclass default ctor\n";
		throw 1;
	}
	~Myclass()
	{
		std::cout << "Myclass default dtor\n";
	}

private:
	A ax;
};

void* operator new (std::size_t size)
{
	std::cout << "operator new called\n";

	void* vp = std::malloc(size);
	if (!vp)
	{
		exit(EXIT_FAILURE);
	}

	return vp;
}

void operator delete(void* vp) noexcept
{
	std::cout << "operatoe delete\n";
	free(vp);
}


int main()
{
	try {
		Myclass *my = new Myclass;
	}
	catch (int)
	{
		std::cout << "Hata yakalandi\n";
	}
}

ÇIKTI
-----
operator new called
A default ctor
Myclass default ctor
A default dtor
operatoe delete
Hata yakalandi



=============================================================================================================================================================
=============================================================================================================================================================
=============================================================================================================================================================

DESTRUCTOR
----------
Destructor is noexcept.Doğuştan böyle.
Nothrow/Noexcept garantisi veren bir func eğer exception throw(yani bu koşulu sağlamazsa) ederse TERMİNATE ÇAĞRILIR.


Eğer noexcept garantisi veren bir fonksiyon kodu çalıştığında exception throw edilirse, bu durumda terminate çağrılır.Hangi func olursa olsun böyle
	a - Derleme zamanı kontrolüne tabi değil.Runtime ile ilgili
	b - Bu durumda eğer exception throw edilirse terminate çağrılır.


void my_terminate()
{
	std::cout << "myfunc cagrildi, myfunc abortu cagiracak\n";
	abort();
}

void foo();

void func()noexcept
{
	std::cout << "func cagrildi\n";
	foo();	
}

void foo()
{
	throw 1;
}

int main()
{
	set_terminate(&my_termiate);
	try{
		func();
	}
	catch(int)
	{
		std::cout <<"hata yakalandı";
	}
}

ÇIKTI
-----
func cagrildi
myfunc cagrildi, myfunc abortu cagiracak

PROBLEM UNCOUGHT GARANTISI DEĞIL. EXCEPTION GÖNDERMEYECEĞI GARANTI EDILEN BIR FUNC EXCEPTION GÖNDERIRSE TERMINATE ÇAĞRILIYOR.

Mülakat sorusu:
Destructor exception throw edilirse ne olur?
Eski C++ ile modern C++ Farklı.
Modern C++ : Dtor noexcept olarak kabul edilir.Exception throw ederse noexcept garantisini violate etmiş olunur ve terminate func çağrılır.

--------------------------------------------------------------------

emit ve propagate 


void my_terminate()
{
	std::cout << "myfunc cagrildi, myfunc abortu cagiracak\n";
	abort();
}

void foo()
{
	throw 1;
}

struct Nec{
	~Nec()
	{
		std::cout << "Nec Dtor\n";
		foo(); // Dtorun noexcept garantisi çiğnendi. Terminate çağrılacak.
	}
};

void func()
{
	Nec nec;
}

int main()
{
	set_terminate(my_terminate);
	try {
		func();
	}
	catch (int) {
		std::cout << "Hata yakalandi\n";
	}
}

Destructor içinde hata yakalanmazsa emit ediyor.
noexcept i ihlal ettiğimiz için terminate çağrılır.

ÇIKTI
-----
Nec Dtor
myfunc cagrildi, myfunc abortu cagiracak


Biz zten exception yakaladıysak ve bunu işleyeyim derken bir exception daha çıkma ihtimali var.Bu yüzden eskiden beri noexcept garantisi veriliyor ve ihlal
edilirse terminate func çağrılıyor.

1 - Ya desturctordan hiç exception throw edilmeyecek.
2 - yada exception throw edildiyse bunu kendi içinde yakalayacağız ve kendi içinde handle edeceğiz.


--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

Bir önemli soru daha !!!!!!!!!!!!

Diyelimki bir sınıf kodu yazmak istiyoruz fakat sınıfın ismi A olan sınıf türden bir veri elemanı var.
Myclass sınıfı için bir Ctor yazıyoruz.Myclass ın ctoru çalışırken onun elemanının ctorunun gönderdiği exceptionu Myclass içerisinde yakalayabilir miyim?

class A{
public:
	A(int x);
};

class Myclass{
public:
	Myclass() : ax{10} // Eğer ax için çağrılan ctor exception throw ederse onu yakala ve şunu yap.Ben bunu yapabilir miyim ? Hem evet hem hayır :D:D
	{

	}
private:
	A ax;
};

-----------------------------------------------------------------------------
-----------------------------------------------------------------------------

HAYIR CEVABININ KODU
--------------------

class A{
public:
	A(int)
	{
		throw 1;
	}
};

class Myclass{
public:
	Myclass() : ax{10}
	{
		try{ // buradaki try bloğu elemanın ctorundan gönderilen exceptionu yakalamaz.Ama bunu yakalayıp başka bir özel hata göndereceksem ne yapacağım?
		}
		catch(int)
		{
			
		}
	}
private:
	A ax;
};


-----------------------------------------------------------------------------
-----------------------------------------------------------------------------

EVET CEVABI - FUNCTION TRY BLOCK
----------------------------------
Bunun temel varlık sebebi az önceki problemi çözmek.Elemanların ctorlarından 
gönderilen exceptionu, o elemana sahip sınıf ctoru içinde yakalanabilmesini sağlıyor.

Dilin kuralları ctor olmayan bir func için bunun kullanılmasını yasaklamıyor ama
çokta kullanılmıyor.Pratikte ihtiyaç duymayacağız yani.

SENTAKS:

void func()
try {            // buradaki blok hem function anabloğu hemde try bloğu oluyor.
				// izleyen catch bloğunda da hata yakalanıyor.
}
catch(int ){

}


--------------------------------------------------------

void func()
try {            
	std::cout << "func cagrildi\n";
	throw 1;
}
catch(int){
	std::cout << "hata yakalandi\n";
}

int main()
{
	func();
}

Çıktı
-----
func cagrildi
hata yakalandi

--------------------------------------------------------

int func()
try {
	std::cout << "func cagrildi\n";
	throw 1;
}
catch(int){
	std::cout << "hata yakalandi\n";
	
	return 10;  //böylede olabilir
}

int main()
{
	func();
}


--------------------------------------------------------

int func(int x)
try {
	std::cout << "func cagrildi\n";
	if(x > 10)
		throw 1;
	return 5;
}
catch(int){
	std::cout << "hata yakalandi\n";
	return 10;	
}

int main()
{
	auto x = func(345);
	std::cout << "x = " << x << "\n";
}

func cagrildi
hata yakalandi
x = 10

--------------------------------------------------------

FUNC PARAMETRESI CATCH VE TRY BLOKLARINDA GEÇERLI !!!!!!

--------------------------------------------------------------------------------------------------------

FUNC TRY BLOK PARAMETRE TÜRÜ SINIF TÜRÜNDENSE,  BU SINIF TÜRÜNDEN GÖNDERILEN EXCEPTIONU YAKALAMAZ !!!!!!

ÖR:
class A{ };
int func(A ax)  // A ax; için ctor çağrıldığında hata oluşursa bu hata burada yakalanamaz
try {
	std::cout << "func cagrildi\n";
	if(x > 10)
		throw 1;
	return 5;
}
catch(int){
	std::cout << "hata yakalandi\n";
	return 10;
}

int main()
{
	auto x = func(345);
	std::cout << "x = " << x << "\n";
}




===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================


CTOR INIT LISTI DE FUNC TRY ILE YAKALIYORUZ.
SENTAKS

class A{ };

class Myclass{
public:
	Myclass() try : ax(10) // buradaki kodlardan exception gelirse artık bu try bloğu içinde kabul ediliyor.Catch hatayı yakalayacak.
	{
	
	}
	catch(int x)
	{
		std::cout << "hata yakalandi x = " << x << "\n";
	}
private:
	A ax;
};



CTOR IÇIN FUNC TRY BLOK OLUŞTURDUĞUMUZDA EĞER EXCEPTION THROW EDERSE VE PROGRAMIN AKIŞI CATCH BLOĞUNA GIRERSE, CATCH BLOĞUNDAN PROGRAMIN AKIŞI DEVAM ETMEYECEK,
BIZ BURAYA BIR KOD YAZMASAK DAHI BU EXCEPTION DERLEYICININ YAZDIĞI KODDA RETHROW EDILIYOR.



Yani aşağıdaki ile
------------------
catch(int x)
{
	std::cout << "hata yakalandi x = " << x << "\n";
}

Buradaki aynı
-------------
catch(int x)
{
	std::cout << "hata yakalandi x = " << x << "\n";
	throw;
}

Böyle bir durum oluşursa
1 - Program sonlandırılacak
2 - Bu exception rethrow edilecek
3 - Başka bir exception gönderilecek.


---------------------------------------------------------------------------------------------------------------------------------------

rethrow edilen exception yakalanırsa ok, yakalanmazsa terminate func çağrılır.

class A {
public:
	A(int) { throw 1; }
};

class Myclass {
public:
	Myclass() try : ax(10) // buradaki kodlardan exception gelirse artık bu try bloğu içinde kabul ediliyor.Catch hatayı yakalayacak.
	{

	}
	catch (int x)
	{
		std::cout << "hata yakalandi x = " << x << "\n";
		//aslında birşey yazmadık ve bu şekilde rethrow etmiş olduk.rethrow da mainden yakalanmadı ve terminate çağrıldı.
	}
private:
	A ax;
};

int main()
{
	set_terminate(my_terminate);
	Myclass m;
}


ÇIKTI
-----
hata yakalandi x = 1
myfunc cagrildi, myfunc abortu cagiracak



=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================


RTTI
----
Runtime Type Information
Programın runtime da türlerin saptanmasına yönelik araç setini göreceğiz.

Runtime polimorfizminin hayatımıza girmesiyle static tür kavramının dışında birde dinamik tür kavramıyla tanıştık.
Car.h sınıfı hiyerarşisine baktıyoruz.

void car_game(Car* p)
{
	//Buraya gelen araba bir Mercedes mi ? Bunu öğrenmek istiyoruz.
}

C++ ta bir nesnenin türünü öğrenmek büyük ihtimalle kötü bir tasarımın sonucu olabilir.Virtual dispatch zaten bunu bilmeden
kullanması olanağını sağlıyor.Runtime polimorfizminin sağladığı temel avantaj bu. Yukarıdaki kodlar aşağıdakilere
bağımlı hale de gelmemiş oluyor.

Ama öyle durumlar varki nesnenin dinamik türünü sorgulamamız gerekiyor. Ya tasarımsal durum ya da belirli kodların bize
sunulmamış olmasından ötürü olabilir.İstediğimizi yapmak için başka bir araç olmayabilir.

Bu araç başlarda tepkiyle karşılaşmış ama bu durumlar için dile eklenmesinde sakınca görülmemiş.
Tek araç bu olabilir can simidi görevi görebilir, bizi çok kod yazmaktan da kurtarabilir...

runtime da tür saptandığı için bir maliyeti de var.

Bazı durumlarda kullanılabilir ama özünde polimorphic sınıflar sözkonusu olduğunda bir nesnenin dinamik türünün programın runtime da
anlaşılması ve sorgulanmasını sağlıyor.

void car_game(Car* p)
{
	//Buraya gelen araba bir Audi ise, Audinin cam tabanının açılması gereksin. Diğer arabaların sunroof u olmak zorunda değil.
	//opensunroof() Car sınıfının interface indeki sanal sınıflardan biri olsaydı zaten cam tabanın açılmasını p->opensunroof() şeklinde
	//sağlayabilirdik.Yani Audi için cam taban açılacak Audi olmayanlar için bu olmak zorunda değil

	//Eğer *p nin dinamik türü audi ise *p i Audi olarak kullan ve opensunroof fonksiyonu ile sunroof u aç.
}


C++ ta nesnelerin türlerinin çalışma zamanında anlaşılmasına yönelik 3 adet araç seti var.
dynamic_cast -> tür dönüştürme operatorü
typeid -> bir operator
typeinfo -> bu da bir sınıf


-------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------

DYNAMIC CAST
------------
Parent classtan child class a dönüşüm var mı yok mu buna bakıyor.Yani yapılabilir mi diye bakıyor.

Sentaks:
dynamic_cast<target type>(expr);

Programın çalışma zamanında bir down-casting in güvenli olarak yapılıp yapılamadığını test ediyor.

DİKKAT !!!!!!!!!!!!!!!!!!!!!
Dynamic cast operatrünün kullanımında operandı olan ifade polymorphic bir türden olmak zorunda aksi takdirde compile time hatası !!!!!!!!!

Der ve Base nesneleri olsun. Der, Base den kalıtım yoluyla elde edildi. child class tan parent class
a yapılan dönüşümler otomatik olarak yapılıyordu zaten.Buna upcasting deniyordu. burada object slicing e dikkat ediliyordu hatta.

Biz bunu türemiş sınıftan tabana doğru değil, tabandan türemişe doğru yapmak istiyoruz. Bu öncelikle doğal bir durum değil.

void car_game(Car* p)
{
	*p
}

*p yukarıda Car türünden ama dinamik olarak bakıldığında bir mercedes olabilir.
Burada Car sınıfından, Mercedes sınıfına dönüşüm yapmak istiyoruz.Buna down-casting deniyor.

Diyelimki buraya gelen arabanın Mercedes olarak kullanılmasını istiyorum ama ya mercedes değilde Bmw ise
buradaki kod onu mercedes olarak kullanmaya kalkarsa runtime da hata oluşur. Dynamic cast tabandan türemişe
dönüşümün güvenli olarak yapılıp yapılamadığına bakıyor. Yani runtime da buraya gelen aslında Mercedesmi diye bakmak istiyoruz
ve bundan emin olmak istiyoruz. Bunu dynamic cast yapıyor.


Mercedes *p = dynamic_cast<Mercedes *>(carptr);

Runtime da bu kod çalıştığında 2 ihtimal var. 
1 - Carptr nin değeri gerçekten bir mercedes nesnesinin adresiyse dynamic cast operatörü başarılı olacak ve bize
	mercedes nesnesinin adresini üretecek. ve p yi bir mercedes olarak kullanabileceğiz
2 - Diyelimki buraya gelen araba Mercedes değilde skoda olsun, burada dynamic_cast başarısız olacak ve nullptr geri döndürecek.


Aşağıdakini yazabiliriz yani

Mercedes *p = dynamic_cast<Mercedes *>(carptr);
if(p != nullptr) // yada if(p)
{
	// burada mercedes değil demekki
}


---------------------------------------------------------------------------------------

Aşağıdaki araç Modern C++ ile gelmedi veya if with initializer ile ilişkisi yok.
if içerisinde değişken bildirimi.Scope leakage ı engelliyor.
Kullanıldığı birkaç yer

int foo();

int main()
{
	if(int x = foo())
	{
		
	}
	//x burada kullanılamaz
}

---------------------------------------------------------------------------------------


int* foo();

int main()
{
	if(int *p = foo())
	{

	}
}


---------------------------------------------------------------------------------------

İdiyom
if(Mercedes *p = dynamic_cast<Mercedes *>(carptr))
{
	
}
//veya aşağıdaki gibi
if(auto *p = dynamic_cast<Mercedes *>(carptr))
{
	
}


---------------------------------------------------------------------------------------

DİKKAT !!!!!!!!!!!!!!!!!!!!!
Dynamic cast operatrünün kullanımında operandı olan ifade polymorphic bir türden olmak zorunda aksi takdirde compile time hatası.

---------------------------------------------------------------------------------------

class Base{

};
class Der : public Base
{
	
}

void func(Base *baseptr)
{
	if(Der* derp = dynamic_cast<Der*>(baseptr)) // burada baseptr yi kırmızı gösteriyor çünkü compile time hatası var. 
	{											// Baseptr polimorfik sınıf türünden değil.Ya virt func olacak ya da böyle bir functan kalıtımla elde edilecek.
		//
	}
}

---------------------------------------------------------------------------------------

Base polimorfik yapılırsa bundan türetilenlerde polimorfik olacak

class Base{
	~virtual Base();
};
class Der : public Base
{
}
void func(Base *baseptr)
{
	if(Der* derp = dynamic_cast<Der*>(baseptr))  { }   // artık sentaks hatası yok. çünkü baseptr polimorfik bir sınıf türü.
}

---------------------------------------------------------------------------------------

dynamic cast i runtime da gösterecek kod yazalım. vakit kaybı olmasın diye car sınıfını include edelim

#include <iostream>
#include <vector>
#include "car.h"

void car_game(Car* carptr)
{
	carptr->start();
	if (Fiat* p = dynamic_cast<Fiat*>(carptr))
	{
		p->activate_aebs();	//Arabanın Fiattan kalıtım yoluyla elde edilen sınıflarıda kapsıyor.Yani Fiat124 olsada içerisine girecek.
	}
	carptr->run();
	carptr->stop();
}

//NOT : Fiat sınıfına car sınıfında olmayan bir function ekleyelim.activate_aebs yi ekledik.Bir arkadaş önerdi bu ismi

int main() {

	srand((unsigned)time(nullptr));

	for (;;)
	{
		Car* p = create_random_car();
		p->vprint(std::cout);
		car_game(p);
		(void)getchar();
		delete p;
	}
}

Çıktı
-----
This is Fiat
Fiat has just started
aebs activated for fiat
Fiat is running
Fiat has stopped

This is Fiat124
Fiat124 has just started
aebs activated for fiat
Fiat is running
Fiat124 has stopped

This is Mercedes
Mercedes has just started
Mercedes is running
Mercedes has stopped

---------------------------------------------------------------------------------------

ÖNEMLİ BİR NOT
EĞER TÜR DÖNÜŞÜMÜ HEDEF TÜR OLARAK REFERANS TÜRÜNE YAPILIRSA(NULL REFERASNS OLMADIĞI İÇİN) 
BAD_CAST TÜRÜNDEN EXCEPTION THROW EDER.

Fiat &fr = dynamic_cast<Fiat &>(carref); //burası ok
auto &fr = dynamic_cast<Fiat &>(carref); //burası ok

Eğer gerçekten Fiat nesnesiyse bunu fiat referansı olarak kullanabiliriz.
Değilse bad_cast türünden exception throw edilir. bad_cast, exception sınıfından public
kalıtımıyla elde edilmiş.

Önceki örneği buraya uyarlarsak.


#include <iostream>
#include <vector>
#include "car.h"

void car_game(Car& carref)
{
	carref.start();

	try {
		Fiat& fr = dynamic_cast<Fiat&>(carref);
		fr.activate_aebs();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Hata yakalandi : " << ex.what() << "\n";
	}

	carref.run();
	carref.stop();

}

//NOT : Fiat sınıfına car sınıfında olmayan bir function ekleyelim.activate_aebs yi ekledik.Bir arkadaş önerdi bu ismi

int main() {

	srand((unsigned)time(nullptr));

	for (;;)
	{
		Car* p = create_random_car();
		p->vprint(std::cout);
		car_game(*p);
		(void)getchar();
		delete p;
	}
}


ÇIKTI
-----

This is Fiat
Fiat has just started
aebs activated for fiat
Fiat is running
Fiat has stopped

This is Fiat124
Fiat124 has just started
aebs activated for fiat
Fiat is running
Fiat124 has stopped	

This is Mercedes
Mercedes has just started
Hata yakalandi : Bad dynamic_cast!
Mercedes is running
Mercedes has stopped


*/

#include <iostream>
#include <vector>
#include "car.h"

void my_terminate()
{
	std::cout << "myfunc cagrildi, myfunc abortu cagiracak\n";
	abort();
}


