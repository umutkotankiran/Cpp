/*

Programın çalışma zamanında tür belirlenmesinde kaldık.Yani runtime da dinamik türün ne olduğunu öğreniyorduk
RTTI -> Runtime Type Information. bu acronim kullanılıyor.Özel durumlarda kullanılıyor.
any sınıfında karşımıza çıkacak. 

dynamic_cast downcasting in güvenilir olarak yapılabilirliğini test ediyor.
Pointer yada referans yoluyla yapılabiliyordu.Pointer yoluyla yapınca hedef adres 
child class/türemiş sınıf türden bir adres, operand olarak kullanılan adres taban sınıf 
nesnesi adresi.Eğer gerçenten carptr, MErcedesi gösteriyorsa ifadenin değeri Mercedes *
türündendi.Değilse nullptr idi.

dynamic cast operatörünü referans semantiği ile kullanılırsa bu durumda nullreferans olmadığından
başarısızlık durumu farklı şekilde ele alınıyor. std library nin exeption sınıfından
kalıtım youyla elde edilen bad_cast sınıfı türünden hata nesnesi gönderiliyor.
Pointer nullptr vardı zaten.Aradaki fark bu.

Car * nesnesini Mercedes * nesnesine dönüştürürsek bu dönüşüm sadece Mercedes * için değil,
Mercedes sınıfından kalıtım yoluyla elde edilmiş S500, Coupe,Maybach içinde geçerli.

BURASI ÇOK ÖNEMLİ !!!!!
DİKKAT!!!!
Dynamic cast in operandı olan ifade polymorphic sınıf türünden olmalı !!!!!!!!!!! 
Aksi takdirde sentaks hatası.Polymorphic sınıf türünden olmadığını görürse compile time da sentaks hatası verir.Compile time da kontrol ediliyor.


============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================


TYPEID
------
typeid

Bu enteresan bir operator.
Bu operatörün operandı ya bir ifade olacak ya da bir tür olacak. sizeof gibi.

<typeinfo>  başlık dosyasında bulunuyor.

typeid(expr)
typeid(int)		Operand olarak bir tür veya bir ifade alabilir.

typeid nin oluşturduğu ifade aslında bir referans.İsmi typeinfo olan bir sınıf nesnesine const referans !!!!!!!!!!!!

Yani 
typeid(x) --> bu typeonfo header file da tanımlanan typeinfo isimli sınıf türünden referans.
yani typeid yazınca aslında typeinfo nesnesi kullanmış oluyoruz dolayısı ile bunu . operatörünün operandını yapabiliriz.


int main()
{
	int x = 10;

	typeid(x).    burada typeinfonun member funcları görünüyor
}

--------------------------------------------------------------------------------

typeinfo türünden nesne oluşturma şansımız yok.Çünkü default Constructoru yok.

int main()
{
	typeinfo t; SENTAKS HATASI
}

--------------------------------------------------------------------------------

Kopyalama yoluylada elde edemeyiz.Copy Ctor delete edilmiş.

int main()
{
	int x = 5;
	typeinfo t(typeid(x)); //Bu da copy ctor delete edildiğinden sentaks hatası.
}

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

DİKKAT!!!!!!!!!!!
TYPEINFO ÖYLE BİR SINIFKİ BU TÜRDEN NESNE OLUŞTURMAK DOĞRUDAN MÜMKÜN DEĞİL.
ÇÜNKÜ BU SINIFIN DEFAULT CTORU YOK COPY CTORU DELETE EDİLMİŞ.
TYPEINFO SINIFINI KULLANMANIN YOLU TYPEID İLE BİR İFADE OLUŞTURMAK

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

DYNAMIC CAST İN OPERANDININ POLYMORPHIC OLMASI ZORUNLUYDU AMA TYPEİD OPERATORUNUN
OPERANDI OLAN İFADE İÇİN BÖYLE BİR ZORUNLULUK YOK !!!!!!!!!!!!!

int main()
{
	int x = 5;
	typeid(std::string); Doğrudan int türünden bir ifadeyle veya sınıf türden ifade
							ile kullanabiliriz.Herhangibir tür de olabilir.
}

--------------------------------------------------------------------------------

2 TYPEINFO NESNESINI KARŞILAŞTIRABILIRIZ.

int main()
{
	int x = 5;
	typeid(x) == typeid(int) //ifadelerin türleri aynıysa o zaman boolean true döndürecek
}							 // cout ile yazdırabiliriz.

--------------------------------------------------------------------------------

int main()
{
	int x = 45;
	int y = 55;
	int z = 4.4;

	cout << boolalpha << (typeid(x) == typeid(y)); TRUE DÖNDÜRÜR
	cout << boolalpha << (typeid(x) == typeid(z)); FALSE DÖNDÜRÜR
}

--------------------------------------------------------------------------------

Sınıfın name isimli const member func ı var.typeinfo sınıfının member func ı bu.
cstring döndürüyor.const char * yani. Bu yazı türü betimleyen bir yazı.
Bu yazı Implementation Defined.Tamamen anlaşılabilir bir yazı da değil.

Visual studio da farklı, wandboxta farklı bir yazı elde ettik mesela.


typeid(x).name() 

int main()
{
	int x = 45;
	int y = 77;

	std::cout << typeid(x).name() << "\n";
	std::cout << typeid(y).name() << "\n";
	std::cout << typeid(Myclass).name() << "\n";
	std::cout << typeid(std::string{}).name() << "\n";
}

ÇIKTI
-----
int
int
class Myclass
class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >

-----------------------------------------------------------------------

En önemli functionları == != ve name functionları
cppreference tan baktık biraz.

-----------------------------------------------------------------------

Polymorphic olmayan türler için aşağıdakiler compile time ifadesi.

int main()
{
	int x = 45;
	cout << typeid(x++).name() << "\n"; //Unevaluated Contex
	std::cout << "x = " << x << "\n"; 45 çıktı.İşlem kodu üretmiyor.
}

-----------------------------------------------
NOT : Unevaluated context oluşturan operatorler
      sizeof
      decltype
      noexcept
      typeid

----------------------------------------------------------------------

EĞER BIR SINIF POLYMORPHIC DEĞILSE !

class Base{

};

class Der : public Base{

};

void func(Base * baseptr)
{
	std::cout << typeid(*baseptr).name()<<"\n";
	std::cout << std::boolalpha <<(typeid(*baseptr) == typeid(Der))<<"\n";
}

void foo(Base& baseref)
{
	std::cout << typeid(baseref).name()<<"\n";
	std::cout << std::boolalpha <<(typeid(baseref) == typeid(Der))<<"\n";
}

int main()
{
	Der myder;

	foo(myder);

	func(&myder);
}

ÇOK ÖNEMLİ !!!
--------------
Burada typeid nin operandı olan ifade polimorfik bir sınıf türünden mi? HAYIR
O zaman typeid nin ürettiği typeinfo nesnesi bilgileri tamamen static türe ilişkin olacak.
Yani name functionu base sınıfını anlatan bir ifade döndürecek ve == operator func ı
false değer döndürecek. Hem Pointer hemde referans semantiğinde aynı şeyler görülür.

ÇIKTI
-----
class Base
false
class Base
false

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

SINIF POLYMORPHIC YAPILDI !!!

class Base {
public:
	virtual ~Base() {};
};

class Der : public Base {

};

void func(Base* baseptr)
{
	std::cout << typeid(*baseptr).name() << "\n";
	std::cout << std::boolalpha << (typeid(*baseptr) == typeid(Der)) << "\n";
}

void foo(Base& baseref)
{
	std::cout << typeid(baseref).name() << "\n";
	std::cout << std::boolalpha << (typeid(baseref) == typeid(Der)) << "\n";
}

int main()
{
	Der myder;

	foo(myder);

	func(&myder);
}

ÇIKTI
-----
class Der
true
class Der
true

------------------------------------------------------------------------------------------
TEKRAR!!!
- typeid polimorfik türler için kullanma mecburiyeti yok. Polimorfik olmayan türler 
  için typeid operatörü tamamen static tür bilgisine yönelik bir typeinfo nesnesi döndürüyor.

- Polymorphic türler sözkonusu olunca typeid operatörün eriştiği typeinfo bilgisi  
  dinamik türe ilişkin.
-------------------------------------------------------------------------------------------

DÜNKÜ ÖRNEĞİ HATIRLAYALIM
-------------------------

#include "car.h"

void car_game(Car* ptr)
{
	ptr->start();
	
	if(typeid(*ptr) == typeid(Fiat)) {				// burada runtime da if in içine, *ptr a gelen araba Fiat ise girecek.Açıklama aşağıda
		static_cast<Fiat *>(ptr)->activate_aebs();	// type bilgisi eğer fiat olursa bunu static cast ile cast edebiliriz.Fiat124 e girmeyecek.Açıklama aşağıda.
	}

	ptr->run();
	ptr->stop();
	(void)getchar();
}

int main()
{
	srand((unsigned int)time(NULL));

	for(;;)
	{
		Car *p = create_random_car();
		p->vprint(std::cout);
		car_game(p);
		delete p;
	}
}

ÇOOOOK ÖNEMLİ !!!!!!!!!!!
-------------------------
DYNAMIC CAST İLE CİDDİ FARK VAR.FİATTAN TÜREMİŞ OLAN FIAT124 GELDİĞİNDE VE BUNU
TYPEID NİN OPERATÖRÜ YAPTIĞIMIZDA FİAT İLE KARŞILAŞTIRINCA TRUE DÖNDÜRMÜYOR YANİ
typeid(*ptr) == typeid(Fiat) BURADA *ptr YERİNE FİAT124 BİLE GELSE TRUE
DÖNDÜRMÜYOR. DYNAMIC CASTTE İSE BUNU KULLANARAK EŞİTLEME YAPILIYORDU. ÇOK KRİTİK BİR FARK BU.
YANİ TÜREMİŞ SINIFLAR BU TÜRDEN KABUL EDİLMİYOR. TAMAMEN AYNI OLMALI.


ÇIKTI
-----
This is Fiat
Fiat has just started
aebs activated for fiat		// FİATTA AEBS ACTIVATE EDILDI
Fiat is running	
Fiat has stopped

This is Fiat124
Fiat124 has just started	//FIAT 124 FIATTAN TÜREMİŞ SINIF OLMASINA RAĞMEN AEBS ACTİVATE EDİLMEDİ.DYNAMIC CAST İLE FARK BURADA
Fiat is running
Fiat124 has stopped

This is BMW
BMW has just started
BMW is running
BMW has stopped


-----------------------------------------------------------------------------------

DİYELİMKİ FUNCTİONU NULLPTR İLE ÇAĞIRDIK !!!

void car_game(Car* ptr)
{
	ptr->start();

	if(typeid(*ptr) == typeid(Fiat)) {				
		static_cast<Fiat *>(ptr)->activate_aebs();	
	}

	ptr->run();
	ptr->stop();
	(void)getchar();
}


int main()
{
	set_terminate(my_terminate);

	car_game(nullptr);		// doğru çalışmadı
}

typeid nin operandı bir pointer olduğunda o pointer *ptr nin dinamik türüne bakıyor.
ptr burada nullptr olmaması gerekiyor. Bu durumda bad type id türünden exception throw eder.

------------------------------------------------------------------------------------

BAD TYPE ID ÖRNEĞİ. cpp referenceden alıdı bir kod onu yazmıyorum.benzer örnek aşağıda
 
int main()
{
	Car *p = nullptr;
	
	try{
		std::cout << typeid(*p).name() << "\n"; //exception throw edecek.
	}
	catch(const std::bad_typeid& ex)  // const std::exception &ex ilede yakalayabiliriz.
	{
		std::cout << "exception caught : " << ex.what() << "\n"; // burada da yakalanır.
	}
}

ÇIKTI
-----
exception caught : Attempted a typeid of nullptr pointer!

------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------

POLIMORHIC TÜRLER SÖZKONUSU OLDUĞUNDA DİNAMİK TÜR BİLGİSİ NASIL ELDE EDİLİYOR

Polimorhic türler için virtual function table var. Virtual dispatch mekanizmasını 
derleyiciler bu şekilde implemente ediyordu. Her polimorfik nesne içinde bir virtual pointer var.
Bu pointer bir veri yapısının adresini tutuyor derleyicinin oluşturduğu kodda. Adresteki veri yapısına virtual
function table deniyordu.Bu da aslında bir veri yapısı. Her indexte ilgili sınıfın bir sanal functionunun adresi var.

Böyle bir tablo varsa buradaki bir indexi de type_info türünden nesne adresi için kullanabiliriz. 
Mesela 0 indexli elemana bunu yazıyor diyelim. Derleyici özgür ama tipik implementasyon bu.
virtual pointer yoluya bu veri yapısına erişince bu veri yapısının belirli indexinden ilgili type infonun adresine erişebiliyorum.
Dolayısı ile runtime da tür bu şekilde belli oluyor.

Tür belirlenmesi Dynamic Cast ile mi yoksa Typeid ile mi yapsak maliyet daha düşük olur ? 
Duruma göre değişir ama typeid. Hiyerarşinin derinliğine bağlı olarakta değişebilir.
Ama typeid doğru. Çünkü typeid türemiş sınıflara bakmıyordu ama dynamic cast türemiş sınıflara da bakıyordu.
typeid de sorgulama sayısı daha az.

type_info sınıfına daha sonra std::any yi incelediğimzde geri döneceğiz.
STL incelendiğinde de geri dönülecek.

Soru soruldu cevap veriliyor.
C++17 den sonra noexcept türün bileşeni olarak kabul ediliyor.Öncesinde kabul edilmiyordu.
Overloading açısından imza farklılığı oluşmuyor.Ama function pointer olarak
bakıldığında noexcepte ait pointerda ona uygun olmalı.

void func(int)noexcept;
void func(int);	//Böyle bir overloading yapılamaz demek.Redefinition hatası

noexcept func pointera, noexcept olmayan func adresi önderilemiyor.
noexcept olmayan func pointera ise noexcept func adresi gönderilebiliyor.

-------------------------------------------------------------------------------------

void func(int)noexcept;
void foo(int);

void(*pf)(int)noexcept = &func;	//Geçerli
void(*pf)(int)= &func;	//Geçerli
void(*pf)(int)= &foo;		//Geçerli

void(*pfoo)(int)noexcept = &foo; //SENTAKS HATASI.

-------------------------------------------------------------------------------------

void foo(int(*f)(int)noexcept); buna except olmayan bir func gönderirsek yine hata 

AMA TERSİ YİNE HATA DEĞİL.

void foo(int(*f)(int));  BUna noexcept garantisi veren yada vermeyen func geçilebilir.

İleri C++ ta anlatılıyor.

-------------------------------------------------------------------------------------

class Base{
public:
	virtual void func(int)noexcept;
}

class Der : public Base{}
public:
	void func(int)override; SENTAKS HATASI
};

void foo(Base &r)
{
	r.func(12);	GEÇERSİZ
}

Taban sınıfın sanal func ı nothrow garantisi vermişse, bunu override eden türemiş sınıfın functionuda 
nothrow garantisi vermeli.

polimorfik işlem yapan func sözkonusu olduğunda bu func, ilgili func a virtual dispatch ile çağrı yaptığında
o func ın exception throw etmediği garantisine güvenmiş olabilir.Ama biz override ederken nothrow garantisi vermezsek
bu taahhütü çüğnemiş olacaktık. Tam tersi olsaydı sıkıntı yoktu.


-----------------------

taban sınıfta noexcept yok ama türemiş sınıfta noexcept var ise bu şekilde virtual dispatch devreye girer sorun olmaz.

class Base{
public:
	virtual void func(int);
}

class Der : public Base{}
public:
	void func(int) noexcept override; //Burada sorun yok artık
};

void foo(Base &r)
{
	r.func(12); GEÇERLİ
}


========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================




GENERIC PROGRAMMING - TEMPLATES
-------------------------------

Generic demek türden bağımsız anlamında.
Öyle kod varki farklı veri türleri için kullanılabilir.
Programlamanın çok önemli alanlarından biri. C++ ın en güçlü olduğu alan belkide bu.

C++ diğer dillerden önde bu konuda.
C de yapmıştık zaten. memcmp memmove memcpy bunlar türden bağımsız işlemler yapıyorlar
qsort ... Nesnenin türünü dikkate almadan nesneyi bellekteki bir byte dizisi olarak ele alınıyor burada.
C ve C++ ta bunun aracı void pointerlar.

hata gswap ı biz yazmıştık.Tekrar gsawp ve greverse yazıldı. Bunlar C de görüldüğü için yazmıyorum.

C++ ın ana araç seti başka bir biçimde implemente edilen generic programlamaya bağlı çalışıyor.
Derleyicinin compile time da bizim için kod yazmasına dayanıyor.Böyle kodlara template deniyor
C++ terminolojisinde.

Yazdığımız metacode türden bağımsız, compiler bunu compiletime da kullanarak gerçek kodu yazıyor.

Biz kod yazmak yerine template leri yazıyoruz, compilerda bunları kullanarak gerçek kodu
yazıyor. C++ ın bel kemiği bu konu.

Template kodun kendisi değil, derleyiciye kod yazdıran bir kod. Bunlar özel sentaksla oluşturuluyor.
Bazıları buna metacode deniyor.Kod yazdıran kod.
Kod formülü de deniyor.

Türkçe olarak şablon denebilir. C++ sentaksının yarısı template lere ilişkin.

C98-03
C++11
C++14
C++17
C++20 Sürekli eklemeler yapılan bir araç seti.

C++ 20 ile gelen major eklentiler var. Mesela Concept geldi.Bu major.

-----------------------------------------------------------------------------

Temel Kategorilere ayrılıyor.

- Function Templates
- Class Templates
- Alias Template		C++11 ile geldi
- Variable Template		C++11 ile geldi
- Concept Template		C++20 ile geldi

MOLA

=================================================================================================================================
=================================================================================================================================
=================================================================================================================================


C++ ın çok büyük kısmını STL oluşturuyor.
STL bir acronim. Standart Template Library

C++ library sinin neredeyse tamamı metacode lardan oluşuyor. 
Derleyici bu motacodelardan kodları oluşturuyor ve sonra derliyor. 
Standart kütüphane %98-99 oranında şablonlardan oluşuyor.

string vector unique_ptr  bunların hepsi sınıf şablonundan derleyicinin derleme zamanında
yazdığı koddan oluşturulan sınıflar.

sort isimli function aslında bir function şablonu.
swap bir function şablonu ...

Template aracıyla işimiz 2 biçimde.
1 - Kullanıcı kodları yazıyoruz.std library nin vector veya algorithm deki func şablonlarını kullanacağız.bunların kullanıcısıyız
2 - Kendi şablonlarımızı oluşturuyoruz.

C++ ta en çok kullanılan projelerde %70-80 kullanılan Boost kütüphanesi var. Bu da template bazlı bir kütüphane.
Algoritmalar çoğu zaman türden bağımsız. Dİziyi reverse eden fonksiyon veya swap functionu ... 

Bunların yazılmasını sağlayacak bir metacode oluşturacağız. Compiler bunu yazıyor.
Genel olarak veri yapıları C++ gibi dillerde sınıflarla temsil ediliyor.
Dİnamik dizi int tutacaksa ayrı bir sınıf double tutacaksa ayrı bir sınıf...
BUnları ayrı ayrı yazmak yerine, ek bir maliyet oluşturmak yerine bir metacode/template
code oluşturarak derleyicinin böyle bir sınıf kodu yazdırmasını tercih ediyoruz.

int main()
{
	using namespace std;
	vector <int>x; 
}

Standart vector sınıfını kullanırken ismi vector olan sınıf şablonundan tür olarak int türünü
kullanması ve bizim için bir sınıf kodu yazması talebinde bulunuyoruz.

---------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------

FONKSIYON VE SINIF ŞABLONLARI
-----------------------------

Ortada bir template varsa keyword olarakta template olmak zorunda.Derleyici buradan anlıyor
template olduğunu. Template den sonra açısal parantez <> var. Açısal parantez içinde bildirilen 
varlıklara template parametreleri deniyor.

Template parametreleri,
	a - Type/Tür parametresi olabilir
		Bir isim kullanıyoruz ve bu bir türe karşılık geliyor.
	
	b - non-type parameter olabilir.(sabit parametre)
	
	c - template template parameter olabilir. Bu kurs kapsamında değil.

template <typename T >  veya template <class T >  

template <typename T, typename U>

------------------------------------------------------------

Tür parametresi = Derleyici ben bir isim kullanıyorum ve bu isim bir türe karşılık geliyor.	
Sen bu şablondan gerçek kodu yazarken bu ismin yerine, onun temsil ettiği türü kullanacaksın

Tür parametresi geçerken kullanılabilecek 2 adet keyword var.
1. class
2. typename

C++ ın ilk zamanlarında tek keyword class idi.

template <class T>   T ismi burada sınıf veya primitive bir türü temsil ediyor

Daha sonra eklenen ise typename keyword. Neden Bu eklendi?
Çünkü class çok uygun bir keyword değil.Mesela T burada bir int veya pointer veya enum türü olabilir.
Bunlar sınıf türü değil. Ama başında class var. Çok uygun bir keyword olmadığı için typename eklendi.

template <typename T>
template <class T>		ikiside geçerli artık. Hoca class ı tercih etmiyor.

typename i başka yerlerde de kullanacağız. Hatta sadece typename kullanacağız.

compiler template <typename T> burada T türünün ne olduğunu bilmek zorunda.

template <typename T> // buradaki T, int olursa int, yada başka birşey olursa onu yazacak yazdığı kodda
class Myclass{
	T x;
};


------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------

1. TYPE/TÜR PARAMETRESİ
-----------------------
Derleyici T yi bilmek zorunda dedik.Nasıl bilecek bunu?
Template tür parametresinin yerine gelecek türün ne olduğunu compilera biz söyleyeceğiz.

int main()
{
	vector<int>     burada birinci template tür parametresi yerine derleyicinin yazacağı kodda int türünü
}					kullanmasını istiyoruz.

- Bu parametreyi açıkça kendimiz söyleyebiliriz.

- Birçok yerde olduğu gibi deduction mekanizması devreye girebilir.

- Template tür parametresi denen isim istediğimiz gibi seçebileceğimiz bir isim.
	template <typename Neco>
	template <typename type>
	template <typename x>

- Konvensiyonel olarak bazı isimler yoğun kullanılıyor. Mesela T - Type, iter - İterator ün kısaltması gibi.

- Bir şablonda birden fazla Template tür parametresi olabilir.
	template <typename T, typename U>
	void func(T x, U y);

Şablon parametresini function parametresi ile karıştırma !!!!!

- template <typename Neco, class X>		Bu bile sentaks hatası değil ama pek tercih edilmez

- template <typename Neco, X,Y>		SENTAKS HATASI. Burada hepsinin başında class veya typename olacak.
 
--------------------------------------------------------------------------------------------------------

2. NON-TYPE PARAMETRE
---------------------
İsmi kötü. Constant parameter olmalıydı aslında. Çünkü burada bir sabit kullanılıyor.
tamsayı sabiti, adres sabiti func adres sabiti ...

Burada doğrudan sabitin türünü yazıyoruz.

template <int x>	Burada x int türden sabit olmak üzere anlamında
					Burada x i kullanınca func yada sınıf kodunu yazarken bir tamsayı sabiti kullanacak.
					
int main()
{
	std::array<int, 2> ar;		arrayde ilk argüman tür argümanı ikincisi ise sabit parametreye karşılık gelen sabit argümanı.
}

array sınıf şablonu aağıdaki gibi.

template <typename T, size_t size> birincisi tür ikincisi boyut olarak kullanılacak
struct array{

};

- Sadece nontype parametresi olan template te olabilir.
	template<int x>			non-type parameter bu
	template<typename x>	bu ise type parameter

	template <typename U, typename T, int low, int high>
	Burada 2 type 2 de nontype parametre var.


===============================================================================================================================
===============================================================================================================================
===============================================================================================================================

FONKSİYON ŞABLONLARI
--------------------
Derleyicinin function kodu yazmasını sağlayacak bir metacode

template <typename T>	//Dikkat!!! buradaki parametreye template parametre
T& func(T& x)			// buradaki parametreye function parametre deniyor.karıştırılmamalı.
{
	//..
}

template tür parametresi functionun bildirimi ya da tanımı içinde heryerde kullanılabilir.
Mesela function parametresi T *x olabilir, T& olabilir.
Func kodunda yerel değişkenler olabilir bu türden T x; 
diziler olabilir. T a[10];
functionun return değer T& olabilir

Şablonlar başlık dosyalarında yer alıyor. Çünkü derleyicinin kod üretebilmesi için bu şablonların
tanımlarını görmesi gerekiyor. Mesela vector headerını include ettiğimizde vector header içindeki
func şablonlarının kodunu kendi dosyamıza yapıştırmış oluyoruz.


-------------------------------------------------------------------------------------------------------------
NOT !!!
Başlık dosyasına template kodları konulunca ODR ihlal edilmemiş oluyor.
Token by token aynı olmalı tabiki. zaten include edildikleri zaman heryere aynı tanımlar yapıştırıldığı için
token by token aynı oluyor.
-------------------------------------------------------------------------------------------------------------

template <typename T>
void func(T x)
{
	x++;
	T y = 10;

	if(x == y)
		x.foo();
}

Burası compile edilirse hata vermez. Çünkü derleyici T nin ne olduğunu bilmiyor.Compile time da çok
kısıtlı kontrl ediyor kodu. Mesela T nin ne olduğunu bilse ve x++ için ++ operatörünü için overload yoksa
hata ile karşılaşabilirdi.

Hangi kontroler yapılıyor burada
Açılan kapanan küme parantezleri uyumlumu gibi..

T türüne bağlı kontrollerinin bu aşamada yapılma şansı yok.


Mesela z(); yazsam 
function içine z yi bulamadığı için hata verir.

template <typename T>
void func(T x)
{
	z(); SENTAKS HATASI
}

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

Derleyici Şablon Tür Parametresi Yerine Hangi Türün Kullanılacağını Nasıl Anlayacak
----------------------------------------------------------------------------------

template <typename T>  // T template parametresi
void func(T x)		// x ise function paramete veya  call parametre deniyor.
{
	x.foo();
}

Nasıl Anlayacak?
Buna yönelik 3 temel araç var.

1. Deduction(çıkarım). Biz buradan başlıyoruz.
---------------------------------------------
T yerine int kullan anlamında açıkça yazmasakta koda bakarak dilin kuralları gereği T int, string, double
olmalı gibi çıkarımlar yapacak.Function şablonlarında bu hakim mekanizma. %90 bu kullanılıyor.

C++17 ye kadar çıkarım sadece func şablonları için geçerliydi. Sınıf şablonlarında bu mekanizma yoktu.
C++17 de önemli bir araç eklendi. Popüler bir acronim ile temsil ediliyor.
CTAD = Class Template Argument Deduction. Bu sınıf şablonlarında kısıtlıda olsa deduction mekanizması var.

2. Explicit Olarak Programcının Argümanı Yazması
------------------------------------------------

template<typename T>
void func(T x)
{
}
int main()
{
	func<int>(10); // burada < > içine yazılan tür, şablon tür parametresine karşılık geliyor.
}					// Burada biz compilera, bir çıkarım yapma, int i al diyoruz.

Artık derleyici bu şablondan kod yazarken T nin int olduğunu bilip ona göre kod yazacak.
Yada sentaks hatası olacak...


-------------------

Çıkarım mekanizmasıyla explicit argüman bildirimi mekanizması birliktede kullanılıyor.


template<typename T, typename U>
void func(T x, U y)
{
}
int main()
{
	func<int>(10, 4.5); // Burada compiler, birinci template tür parametresini <> içindeki tür bilgisinden anladı		
}						// ikinci template parametresi için çıkarım mekanizmasını kullanıyor.



3. Default Tür Argümanı Kullanımı
---------------------------------
template<typename T, typename U = int>
void func(T x, U = U{})
{
}

Eğer U türünün ne olduğu konusunda bilgi verilmezse, derleyici U türü karşılığında argüman olarak int kullanacak.
Kendim söylemezsem U = int olacak.

int main()
{
	func<double>(1,0.); // burada T double, U ise int (<double> verilmiş sadece tür bilgisi olarak ) olacak
}

==========================================================================================================================
==========================================================================================================================
==========================================================================================================================


1. DEDUCTION MEKANIZMASI
------------------------
Template tür parametresinin ne olduğunu derleyici, func şablonundan yazılacak functiona yapılan çağrıda,
kullanılan argümanların türünden hareketle karar verecek.

Biz buradaki kuralları auto type deduction aracında öğrendik.
Bir istisna hariç tamamen aynı.

template <typename T>
void func(T x);

int main()
{
	func(10); // T burada int. Burada func çağrısından template tür parametresi olan T nin ne olduğunu anlamaya çalışacak.
	auto y = 10; // Burada auto yerine tür gelecek. ='in
	sağından anlaşılacak bu. Biz öğrenmiştik bunları.

}

Auto da kurallar 3 e ayrılmıştı.
auto x = expr;
auto &x = expr;
auto &&x = expr;
Kurallar burada da aynı fark yok.


template <typename T>
func(expr);

template <typename& T>
func(expr);

template <typename&& T>
func(expr);			yine aynı şekilde T için tür çıkarılacak hepsinde.

-------------------------------------------------------------------------------

ÖRNEKLER

Not : Hoca bir hile gösterecek. Derleyicinin T için yaptığı çıkarımın ne olduğu compile time hata mesajında görülecek.
İleride de ayrıca görülecek bu.

template <typename T> // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan
class TypeTeller;	 // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan

template <typename T>
void func(T)
{
	TypeTeller<T> x;	// Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan.Bunu yorum satırı yaparak test edip.
}						// yorum satırından çıkarınca hata verdirip, vermesi gerek türü output kısmından öğrenebiliriz.

int main()
{
	func(12); // Burada argüman olan tür ne ise derleyici T yi o tür olarak alacak. İNT olacak.
	
	//------------------------------------------------------------------------------------------------------
	
	const int a = 5;
	func(a); // int olacak. const luk düşüyor.auto daki gibi.
	
	//------------------------------------------------------------------------------------------------------
	
	const volatile int b = 10;
	func(b) // yine int. volatile ve const düştü
	
	//------------------------------------------------------------------------------------------------------
	
	int i = 3;
	int &r = i;
	func(r); // T nin türü int olacak. & düştü.
	
	//------------------------------------------------------------------------------------------------------
	
	int i = 3;
	const int &r = i;
	func(r) ; // T türü yine int. hem int hemde & düştü.
	
	//------------------------------------------------------------------------------------------------------
	
	int a[] = {1,2,3,4,5};
	func(a); // T türü int *
	
	//------------------------------------------------------------------------------------------------------
	
	const int a[] = {2,5,7,8};
	func(a); // türü const int *
	
	//------------------------------------------------------------------------------------------------------
	
	func("haydar"); // const char *
	
	//------------------------------------------------------------------------------------------------------

	int foo(int);
	int main()
	{
		func(foo); // int(*)(int);
	}

	//------------------------------------------------------------------------------------------------------

}

=======================================================================================================================

2. Durum T&

BURAYA DİKKAT.ÖRNERLERDE AÇIKLAMASINI YAPACAĞIM.


template <typename T> // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan
class TypeTeller;	 // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan

template <typename T>
void func(T&)
{
	TypeTeller<T> x;	// Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan.Bunu yorum satırı yaparak test edip.
}						// yorum satırından çıkarınca hata verdirip, vermesi gerek türü output kısmından öğrenebiliriz.


int main()
{
	
	//------------------------------------------------------------------------------------------------------

	int x = 10;
	func(x); // T türü int.		Func ın içi func(int&) oldu yani
	//------------------------------------------------------------------------------------------------------

	const int x = 10;
	func(x); // T türü const int.		Func ın içi func(const int &) oldu.

	//------------------------------------------------------------------------------------------------------

	int a[5] = {0};
	func(a); // T türü int [5].		Func ın içi func(int (&r)[5]) oldu.

	//------------------------------------------------------------------------------------------------------

	const int a[5] = {0};
	func(a); // T türü const int [5].		Func ın içi func(const int (&r)[5]) oldu.

	//------------------------------------------------------------------------------------------------------

	func("Haydar"); // T türü const char [7] .		func ın içi func(const char (&r)[7])

	//------------------------------------------------------------------------------------------------------

	int foo(int);
	int main()
	{
		func(foo); // T türü int (int).			Func ın içi  func(int(&)(int));
	}

	//------------------------------------------------------------------------------------------------------




=================================================================================================================================

3. Durum T&&

Burada bir fonksiyon parametresine asla doğrudan sağ taraf referansı dememeliyiz.

void foo(int &&); //Burada sağ taraf referansı demeliyiz burası ok Çıkarım olmayan senaryolarda böyle 

Ama çıkarım olan senaryolarda yani templatelerde

template <typename T>
void func(T &&)
{
	
}

Buradaki func(T&&) parametresine kesinlikle sağ taraf referansı demiyoruz.

Standartların kullandığı terminolojiye göre buradaki parametreye FORWARDING REFERENCE DENIYOR.
Aynı anlamda kullanılan 2. bir terim ise UNIVERSAL REFERENCE. Scott Meyers uydurmuş yine.

HATIRLATMALAR
---------------
Buradaki çıkarım mekanizması tamamen farklı.
C++ ta reference to reference yok. Ama öyle yerler varki oluşan kodda reference to reference oluşuyor.
Eğer böyle durumlarda referansa referans oluşursa oluşturulan değişkenin türünün ne olduğunu belirleyen
kurallara refeence collapsing kuralları deniyor.

T&		 &		&
T&		 &&		&
T&&		 &		&
T&&		 &&		&&

Bu kurallar zaten ok. Daha öncede yazmıştık.

autoda && && durumu oluşmuyor.

-----------------------------------------------------------------

ÖRNEKLER
--------

using mref = Myclass&;  // mref burada Myclass&

-----------------------------------------------------------------

DİKKAT !!!

using MRef = Myclass&;
Myclass mx;

MRef& x = mx; //  Myclass& & gelmiş. & ve & gelince sonuc = & tir. yani x türü Myclass&

Kanıtı
decyltype(x) a; // x Myclass& gösterir ama burası sentaks hatası çünkü ref initialize aşamasında bağlanmalı.

-----------------------------------------------------------------

using MRef = Myclass&;
Myclass mx;

Mref&& r = mx;  // Burada Mreften & geliyor, && te bildirimde var zaten. & + && --> &. yani r nin türü Myclass&
				// yani Myclass & && -> Myclass& oldu

-----------------------------------------------------------------

using MRef = Myclass&&;
Myclass mx;

Mref&& r = mx; // Myclass && && gelmiş && + && --> &&.  r türü Myclass&& = mx oldu ama rvalue reference lvalue expression atanamaz
												Sentaks hatası oluşur bu sebeple.

-----------------------------------------------------------------

class Myclass{
};

using Type = Myclass&;
using Nec = Type&;		// Myclass & & geliyor. & + & --> &; Nec in türü Myclass&

using Type = Myclass&&;
using Nec = Type&;		// Myclass& yine

using Type = Myclass&&;
using Nec = Type&&;		//  Myclass&& + && --> &&. Nec türü Myclass&&



MOLA																					

========================================================================================================================
========================================================================================================================

3. Durum T&& ÖRNEKLERİ
----------------------

template <typename T> // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan
class TypeTeller;	 // Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan

template <typename T>
void func(T&&)
{
	TypeTeller<T> x;	// Tür çıkarımını göstermesi için yardımcı kod eklendi sonradan.Bunu yorum satırı yaparak test edip.
}						// yorum satırından çıkarınca hata verdirip, vermesi gerek türü output kısmından öğrenebiliriz.


int main()
{

	//------------------------------------------------------------------------------------------------------

	func(10); // T nin türü int.			Func ın içi func(int&&) oldu
	
	AÇIKLAMA
	auto &&x = 10 dersek
	auto burada int oldu.
	T ye karşılık int geldi
	func(T&&) yani func(int&&) oldu
	

	//------------------------------------------------------------------------------------------------------

	int x = 10;
	func(x); // T nin türü int&.			Func ın içi &+&& -> &. func(int&) oldu

	AÇIKLAMA
	auto &&x = x dersek
	auto burada int& oldu.
	T ye karşılık int& geldi
	int & && --> Sonuç int& çıktı.
	func(T&&) yani func(int& &&)--> func(int&)


	//------------------------------------------------------------------------------------------------------

}


===================================================================================================================================
===================================================================================================================================


Template argument deduction her zaman başarılı olamayabilir.
Derleyici her zaman çıkarımı çıkaramayabilir.Bu herzaman sentaks hatası.
Peki Derleyici neden tür çıkaramı yapamaz.

TIPIK 2 AYRI NEDENI VAR.

1 - derleyicinin function çağrısında kullanılan argümanlardan yola çıkarak template tür parametresinin ne olduğunu anlama şansı olmaz

template <typename T>

T foo()
{
	
}

int main()
{
	foo(); // func parametresi yok derleyici T türünün ne olduğunu anlayamayabilir.Argüman yok çünkü. 
}

Eğer şablon tür parametresi sadece func return türünde kullanılmışsa veya func tanımı içindeki yerel bir değişkende
kullanıılmışsa derleyicinin func call dan hareketle argument deduction yapma şansı yok.

could not deduce template argument for T ... gibi bir hata alınıyor

Ama 

int main()
{
	foo<int>(); // İşte burada func int olarak alınacak.Sonuçta çıkarım tek yol değil.
}

------------------------------------

2 - Ambigiuty

Bu nasıl oluşur.Tipik olarak functionun birden fazla parametre değişkeni var.dolayısı ile functionun birden fazla argümanı var.
Bu durumda her argüman için çıkarımın aynı şekilde yapılması gerekiyor.Mesela T türünün 1 argüman için int, diğer argüman için double
olması gerekiyorsa bu sefer derleyici int mi double mı? karar veremeyecek.Ambigiuty hatası oluşur.


template <typename T>
void func(T x, T y);

int main()
{
	func(1,2); // GEÇERLİ. int int
	func("ali","veli"); //GEÇERLİ. const char *, const char *
	func(3.4,2.44); // GEÇERLİ double double

	func(2,3.4); //SENTAKS HATASI. int double. int mi double mı ? Ambigiuty.
		
}

-----------

Mülakat sorusu

template <typename T>
void func(T &x, T &y);

int main()
{
	int a[5]{}, b[5]{},c[4]{};

	func("Ali","Can"); //Geçerli
	func("Umut","Haydar"); //Geçersiz çünkü const char [5] , cosnt char [7]
	func(a,b);	//GEÇERLİ
	func(a,c); //GEÇERSİZ çünkü int [5] , int [4]
}


template <typename T>
void func(T &&x, T &y);

int main()
{
	int i = 10;

	//----------------------------------------------------

	ÇOK ÖNEMLİ !!!
	
	func(i,i); 	//SENTAKS HATASI

	- birinci parametre için, karışık kısım bu
	auto &&x = i dersek 
	auto burada int& oldu.
	Tye karşılık int& geldi
	func(T&&,diğer param) için func(int& &&, diğer param) --> func(int&, diğer param)
	

	- ikinci parametre için
	auto &y = i dersek
	auto burada doğrudan int çıkar. 
	T ye int geldi yani
	func(birinci param, T&) --> func(birinci param, int&)

	BURADAKİ SIKINTI T BİRİNDE İNT İKEN DİĞERİNDE İNT&.AMBIGIUTY !!!!
	int&, int  AMBIGIUTY. T ikisi arasında seçilemez

	//----------------------------------------------------

	//BUDA ÇOK ÖNEMLİ
	
	func(15,25); // int, int GEÇERLİ.
	
	-Birinci parametre
	auto &&x = 15 dersek
	auto burada int çıkar
	T ye int geldi 
	func(T&& , ...) --> func(int && , ...)
	
	-İkinci Parametre
	auto &x = 25;
	auto doğrudan int
	T ye int geldi
	func(...,T&) --> func(...,int&)

	function şöyle oldu. func(int&&, int&)
	AYNI ZAMANDA İKİSİNDE DE T YE İNT DENK GELDİ.HATA YOK
	
	int,int  GEÇERLİ

	//----------------------------------------------------
}

==================================================================================================================================================================
==================================================================================================================================================================

ÖZEL DURUMLAR
-------------

Buradaki sorular mülakat soruları

Burada önişlemci macroları gibi suni bir çıkarım yok.
Çok daha komplex olabilir çıkarım.

template <typename T>
void func(T**)
{

}

int main()
{
	int x{};
	int *ptr{&x};
	int **p{&ptr};

	func(p); // Burada T burada int türü olur.

	// void func(T*) olsaydı 
	
	func(p); // Burada T burada int* türü olur

	// void func(T) olsaydı 

	func(p); // burada da int** olur.
}

---------------------------------------------------------------

template <typename>
class TypeTeller;

template <typename T, int size>
void func(T (&)[size])
{
	TypeTeller<T> x;
}

int main()
{
	int a[10];

	func(a); // T nin türü burada int.  func parametre değişkeni ise int (&r)[10] olacak.
}

---------------------------------------------------------------

Dizi boyutunu compile time da elde etmek için constexpr bir func template yazalım

template <typename T, int n>
constexpr int Size(const T(&)[n])
{
	return n;
}

int main()
{
	int a[10];
	double b[10];
	double c[] = {1.f, 2.f, 4.f};

	constexpr auto size_a = Size(a);
	constexpr auto size_b = Size(b);
	constexpr auto size_c = Size(c); hepsinin üzerine gelerek boyutlarını görüyoruz.

}

------------------------------------------------------------------

template <typename>
class TypeTeller;

template<typename T, typename U>

void func(T (*)(U))
{
	TypeTeller <T> x;
	TypeTeller <U> y;
}

int foo(double);

int main()
{
	func(foo); // T int olur U da double
}



*/


#include <iostream>
#include <typeinfo>
#include "car.h"

#include <utility>

class Myclass {

};

int main()
{
	using MRef = Myclass&;
	Myclass mx;

	MRef&& r = mx;

	
}
