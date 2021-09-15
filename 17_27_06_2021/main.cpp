/*

İSİM ALANLARINDAN DEVAM
-----------------------

Global isimlerin birbiriyle çakışması gibi durumları engelliyordu.
namespace içinde bildirilen isimler ayrı bir scopetadır ve başka scopetaki
isimlerle çakışmıyor.
:: operatörü ile kullanılıyor.

Namespace in kümülatif olduğundan bahsedildi.
Geçen derste gösterildi bu.

namespace nec{
	int x = 10;
}

namespace nec{
	int y = 20;
}

int main()
{
	nec::x; // bu şekilde erişilir.
}

--------------------------------------------------------------------------------------


Nested namespace ler çok kullanılıyor.

namespace nec{
	namespace pro{
	}
}

C++17 de ekleme yapıldı dile.

eskiden şöyleydi

namespace A{
	namespace B{
		namespace C{

		}
	}
}


YENİSİ
------

namespace A::B::C{
	int x = 10;  // x burada a nın içindeki b nin içindeki c nin içinde :DD:D:
}

namespace A::B{
	int y;
}

namespace A{
	int z;
}

int main()
{
	A::z = 10;
	A::B::y = 20;
	A::B::C::x = 123;
}


=======================================================================================================================
=======================================================================================================================
=======================================================================================================================

Bir namespace içindeki isimlerin, bir namespace ismiyle nitelenmeden ilgili namespace te aranıp bulunmasını sağlayan
3 adet araç var.

1 - Using Decleration
2 - Using Namespace Decleration
3 - ADL(Argument Depended Lookup)

-----------------------------------------

1 - USING DECLERATION
---------------------
Bu çok yerde overload edilmiş bir keyword.Farklı amaçlarlada kullanılıyor.
Biz type alias olarak kullanıldığını gördük
using word = int;

using in yapıp typedef in yapamadığı şeyler var. bunlar tempalte lerde ve generic programlamada önemli oluyor.

Bir de using in sınıf içinde kullanımı var.
class{
	using base::x;
};



SENTAKS
using namespace_name::object_name;
Bu artık namespace nin içindeki objenin direk ismi ile kullanılabilmesini sağlıyor.


namespace Ali{
	int x;
}

using Ali::x; // artık x yazınca Ali::x e erişiriz.

int main()
{
	x = 5;
}

-------------------------------------------------------

using bildiriminin bir kapsamı var. using bildiriminin kapsamı, namespace içinde kullanılırsa namespace scope,
block içinde kullanılırsa block scopetur.

ÖR:

namespace Ali{
	int x;
}

using Ali::x; // artık x yazınca Ali::x e erişiriz. 

void func()
{
	x = 35;
}

void foo()
{
	x = 22;
}


int main()
{
	x = 5;
}

hepsinde x e erişilir.Derleyici isim aramayla using bildirimini görecek.Bunun ali namespace i içinde olan x olduğunu anlayacak.

----------------------------------------------------------------------

namespace Ali{
	int x;
}


void func()
{
	using Ali::x;
	x = 35; BU SCOPETA x BULUNUR. LEGAL KOD.
}

void foo()
{
	x = 22; SENTAKS HATASI
}


int main()
{
	x = 5; SENTAKS HATASI
}

using bildirimini block veya namespace scopeta yapılabilir. blockta yapılırsa ilgili blockta o isme ulaşılır
global yapılırsa heryerden ulaşılabilir.

-----------------------------------------------------------

En uygunu hiç kullanmamak.
Kullanılacaksa local (en dar) scopeta kullanmak
En son ihtimnal namespace scopeta kullanmak.

--------------------------------

Using bildirimninin 2. önemli özelliği, bildirilen isim, bildirimin yapıldığı isim alanına inject ediyor.
Enjekte etmesi nedemek?

namespace Ali{
	int x;
}

void func()
{
	using Ali::x;
	int x = 25;	// burası doğrudan SENTAKS HATASI.Zaten x değişkeni var. using sanki bu scopeta x i bildirmiş gibi davranıyor
}

---------------------------------------

Aşağıdaki gibi olsaydı sorun yoktu

namespace Ali{
	int x;
}

using Ali::x;
void func()
{
	int x = 25;	// Burası geçerli.
	x = 44;	//ismi bulacak ve arama yerel değişken olan x e yapıldı.içerideki x dışarıdakini maskeledi.
	
	Ali::x = 55; yine kullanılabilir.
}

------------------------------


namespace Ali {
	int x;
}

int x = 25;	
using Ali::x; // Bu bildirim artık hata oldu.

void func()
{

}

---------------------
namespace Ali {
	int x;
	int y;
}

Eskiden
using Ali::x;
using Ali::y

YENİ - C++17
using Ali::x,Ali::y;

int main()
{
	x = 23;
	y = 98;
}

NOT !
Başlık dosyası içinde asla using bildirimi veya using namespace bildirimi yapmayın.
Bunu include eden herkeste de bu bildirim olur.Bu durumda da namespace lerin varlık sebebi ortadan kalkar.

===================================================================================================================

2 - USING NAMESPACE BİLDİRİMİ
-----------------------------
Aşağıdaki isimlerin herbirini nitelemeden kullanmak istiyoruz

namespace Ali{
	int x;
	int y;
	int z;
	////

}


2 yol var.
1 - tek tek using bildirimi.
2 - using namespace i kullanmak.

Hoca bunu anlatmak için şekil çizdi.İnsanlar zorlanıyormuş anlamakta :D:D

namespace Ali{
	int x;
	int y;
	double z;
}

using namespace Ali; // Bunu yazınca artık, nerede bu bildirim yapıldıysa, o scopeta x,y ve z direkt olarak görünür durumda.

void func()
{
	x = 5;
}

void foo()
{
	x = 56;
}

int main()
{
	x = 234;
}

Sanki Ali namespace i yorum satırı yapıldı ve içindekiler dışarı çıkartımış gibi.

-----------------------------------------------------------------------------

namespace Ali{
	int x;
	int y;
	double z;
}


void func()
{
	using namespace Ali; // func scope ta artık ali namespace içindeki isimlere ulaşırım.
	x = 5;
}

void foo()
{
	x = 56; //SENTAKS HATASI. Bu scope ta değil. bunu kapsayan scope tada değil.o yüzden sentaks hatası
}

int main()
{
	x = 234; //SENTAKS HATASI. Yukarıdaki ile aynı.
}

----------------------------------------------------------------

DİKKAT!!!!!!!!!!!!!!!!!
BURADA 186. SATIRDAKİ USİNG BİLDİRİMİ İLE FARKLI DAVRANIYOR. !!!!!!!!!!!
DİKKAT ET !!!!!!!!!

namespace Ali{
	int x;
	int y;
	double z;
}


void func()
{
	using namespace Ali; 
	int x = 10;	// HATA YOK.Buradaki x diğerini maskeliyor.  using Ali::x; olsaydı 186. satırdaki gibi. SENTAKS HATASI.
	x = 5; // buda yerel x

	Ali::x; burada da Alideki x e erişiyoruz.
}

------------------------------------------------------------

#include module_a
#include module_b

a dan gelen 
namespace a{
	int ax;
	int x;
}

b den gelen
namespace b
{
	int bx;
	int x;
}

using namespace A;
using namespace B;

int main()
{
	ax++;
	bx--; //ikiside nitelemeden kullanılabilir.
	
	x; //Burada ambigiuty hatası olur. İkisinde de x var.

	A::x;
	B::x; // ile bunlar aşılabilir.
}

USING BILDIRIMLERI BOL KESEDEN KULLANILMAMALI.


-----------------------------------------------------------------

class Myclass
{
	void func()
	{
		using namespace std;   // belki böyle kullanılır ama önermiyor hoca.
	}
}

--------------------------------------------------------------------

NOT !!!
CLASS DEFIBITION İÇİNDE USING NAMESPACE STD; BİLDİRİMİ YAPILAMAZ.
YA LOCAL DÜZEYDE YA DA NAMESPACE İÇİNDE YAPILIYOR.

--------------------------------------------------------------------
--------------------------------------------------------------------

// ali.h
namespace ali{
	class Myclass
	{
	public:
		Myclass& operator=(const Myclass&other);

	};

	void func(Myclass);
	void foo(Myclass);

}

//ali.cpp
#include "ali.h"

void ali::func(Myclass x) // Myclass ismini nitelemeden kullandık ve sentaks hatası yok.Parametrenin içi ilgili namespace de kabul ediliyor.
{
	
}

ali::Myclass& ali::Myclass::operator=(const Myclass&other)
{
	//...
	return *this;
}

--------------------------------------------------------

Bu isimleri nitelemeden kullanmanın 2 yolu var.

1. madem namespace kümülatif.Bunları aynı namespace e alabiliriz.zaten header file içinde de namespace vardı.
	onunla burayı kümülatif olarak ele alacak.


namespace ali{

	void func(Myclass x) 
	{
	
	}

	Myclass& Myclass::operator=(const Myclass&other)
	{
		//...
		return *this;
	}
}




2. using namespace ali; bildirimi yapılabilir cpp file da.
	ali namespace i burada artık doğrudan kullanılabilir.

void func(Myclass x) // Myclass ismini nitelemeden kullandık ve sentaks hatası yok.Parametrenin içi ilgili namespace de kabul ediliyor.
{

}

Myclass& Myclass::operator=(const Myclass&other)
{
	//...
	return *this;
}

Genel olarak hoca bunu kullanma taraftarı değil.Buraya başka bir dosya include edilince çakışma yine olabilir.
1. seçenek daha iyi diyor hoca.


----------------------------------------------------------

int main()
{
	using namespace std; sadece bu blokta bunu yazabiliriz.
}

----------------------------------------------------------

3 - ADL(ARGUMENT DEPENDENT LOOKUP)

namespace nec{
	class Myclass{
		///
	};

	void foo();
	void func(int);
}

int main()
{
	foo(); // ismi arar bulamaz hata verir.
	nec::foo(); // ismi arar ve bulur hata yok.

	func(12); //sentaks hatası.Bulamadı yine
}

---------------------------------------------------------------------------

KRİTİK KISIM

namespace Nec{
	class Myclass{
		///
	};

	void foo(Myclass m);
	void func(int);
}

int main()
{
	Nec::Myclass m;
	
	foo(m); // SENTAKS HATASI DEĞİL. :D:D	Nec::foo() diye çağrılmadığı halde sentaks hatası değil.

	func(4); //SENTAKS HATASI.
}


KURAL: EĞER BİR FONKSİYON ÇAĞRISINDA FONKSİYONA ARGÜMAN OLARAK GÖNDERİLEN İFADE, BİR NAMESPACE İÇİNDE TANIMLANAN
		TÜRLERDEN BİRİNE İLİŞKİN İSE, O ZAMAN BU İSİM NORMAL ARANDIĞI YERİN DIŞINDA BU İSMİN AİT OLDUĞU TÜRÜN
		AİT OLDUĞU NAMESPACE İÇİNDE DE ARANIR.

		BU DURUMDA İSİM NEREDE DE ARANACAK? BU İSMİN AİT OLDUĞU SINIFIN TANIMLANDIĞI NAMESPACE İÇİNDE.


------------------------------------------------------------------------------------------------------------

func(a,b,c);
diyelimki a, a namespace içinde, b b namespacei içinde, c  c namespace i içinde tanımlanan türlerden olsun.
bu durumda func ismi 3 namespace içinde de aranır.

------------------------------------------------------------------------------------------------------------

Çok kritik biryer!!

#include <vector>

namespace Nec{
	class Myclass{
		///
	};

	void foo(Myclass m);
	void func(std::vector<Myclass>);
}

int main()
{
	// Func ın parametresi Myclass türünden mi ? hayır Vector türünden
	std::vector<Nec::Myclass> myvec;
	//foo yu myvec ile çağırırsam ADL ile foo ismi bulunur mu bulunmaz mı?
}

NEDEN BULUNDU?
Tanıma dikkat!
Bir fonksiyona gönderilen argüman bir namespace içinde tanımlanan türdense demedik.
bir namespace içinde tanımlanan türe ilişkin ise dedik. Bu sebeple bulundu

---------

ÖR:

namespace Nec{
	class Myclass{
		///
	};

	enum color {Red,Green,White};
	void func(color);
}

int main()
{
	func(nec::color::black); //SENTAKS HATASI YOK.GEÇERLi.
}

Bir öncekinde de bunda da namespace içinde var olan bir tür kullanıldı parametrede.Adı geçti.
Dolayısı ile türe ilişkin oldu. Bu sebeple o türü argüman verince bulunduğu namespace de de arıyor yani
ADL oluyor.

-----------------------------------------------------------------

namespace Nec{
	class Myclass{
		///
	};

	typedef int Word;
	void foo(Word);
}

int main()
{
	nec::Word myword{};
	foo(myword);		// SENTAKS HATASI
}

ADL typedef isimleri için geçerli değil.Burada yeni bir tür tanımlamıyoruz çünkü. buradaki int türü.

-----------------------------------------------------------------

namespace Nec{
	class Myclass{
		///
	};

	typedef Myclass Ctype;
	void foo(Myclass);
}

int main()
{
	nec::Ctype mx;
	foo(mx);		// ŞİMDİ GEÇERLİ.
}

typedef ismi eğer sınıf içinde belirlenen türe ilişkin ise ADL DEVREYE GİRER.
Eğer int veya double gibi bir türe ilişkin ise ADL devreye girmez bir öncekinde olduğu gibi.

typedef tanımlanan bir türe ilişkin olmalı.

--------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------

ŞIMDIYE KADAR ADL KULLANDIK ZATEN.

int main()
{
	std::cout << "Hello world\n"; // SORU BURADA ADL KULLANILMIŞ MI? KESİNLİKLE VAR
	// operator<<(std::cout ,"Hello word"); böyle çağrılır.
	// operator<< ta std namespace i içinde bildirilmiş.
	// std::cout std namespace i içinde tanımlanmış bir sınıfa ilişkin. ismi ostream olan sınıf.
	// bu sebeple ADL VAR.
}

--------------------------------------------------------------------------------------------

include iostream
include vector
include string
include algorithm

int main()
{
	std::vector<std::string> svec;
	// code
	auto iter = find(next(svec.begin()),prev(svec.end()),"ali"); 
	auto iter = std::find(std::next(svec.begin()),std::prev(svec.end()),"ali"); //Normalde böyle olmalıydı ama nasıl oldu da 
																				// yukarıdaki çalıştı.

}

Nedeni?
next i svec.begin() ile çağırdık, bu func ın return dğeeri türü vector<string>::iterator tür olduğuna göre
bu türde std namespace i içinde tanımlanan bir türe ikişkin olduğu için std namespace i içinde de arayacak.
aynısı prev içinde geçerli.

Peki next(svec.begin()) in geri dönüş değeri türü ne ?
bununda return değeri bir iterator türü. o zaman finda da gönderidğim argümanda std namespace i için tanımlanan bir 
türe ilişkin olduğu için find isminide std namespace i içinde arar.

------------------------------------------------------------------------------------------

namespace A
{
	class Myclass{	}
	void func(Myclass);
}

void func(A::Myclass);

int main()
{
	A::Myclass ax;
	func(ax);		//BURADA AMBIGIUTY VAR. FUNC İSMİ HEM GLOBALDA HEMDE NAMESPACE A İÇİNDE BULUNDU.
					// ÖNCELİK YOK BURADA. İKİ TANE FUNC BULDU.
}

=======================================================================================================

ADL NEDEN VAR?

operator overloading için var. cout<< "asd"; burada bile ADL VAR.

std::cout << "merhaba" << endl; // endl ismi adl ile bulunur mu bulunmaz mı? BULUNMAZ
endl bir func ismi ve bu bir func a argüman olarak gönderiliyor. 
operator<<(std::cout, "Merhaba Dunya").operator<<(std::endl)

endl(std::cout); // endl ismi bulunur. endl std namespace içinde tanımlanan function. ona gönderdiğimiz argüman
std namespace içindeki bir türe ilişkin olduğundan, endl ismi std namespace içinde de arancaak.

-------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------

ENDL NEDEN SIK KULLANILMAMALI
endl std namespace i içinde bulunan bir fonksiyon. endl bir maniplator.
std::cout << "Merhab Dunya" << endl; // std::endl denmeyince hata olur neden?

operator<<(std::cout, "merhaba dunya").operator<<(std::endl); // açılmış hali bu.
endl yi fonksiyona gönderiyoruz bu yüzden std::endl olarak yazmamız gerekiyor.

fonksiyonu endl ye argüman olarak gönderelim
endl(std::cout); endl ismi bulunru mu bulunmaz mı? BULUNUR çünkü endl std namespace i içinde bildirilen bir function
Ona gönderdiğim argüman std namespace i içindeki türe ilişkin olduğu için endl ismi std namespaceinde de arancak.
ADL yani.

endl orijinalinde function template
std::ostream& Endl(std::ostream& os)
{
	os.put('\n');
	os.flush(); C deki gibi flush işlemi yapıyor.

	return os;
}

yukarısı <<"\n"; bununla aynı işlemi yapmıyor. endl her kullanıldığında buffer flush ediliyor.
hatta << '\n'; eb iyi yolu bu. "\n" bu bir string literali ve static ömürlü bir dizi.

endl de verim kaybıda var.

Eğer
cout << endl; dersek veya 
cout.operator<<(endl); //Derleyicinin burada inline expansion yapma şansıda yok. Ciddi verim kaybı.endl kullanma !! :D:D:D:D
endl(cout); demiş oluyoruz.


---------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------


//.h
namespace A
{
	class Myclass
	{
	public:
		void func();
		//member func

	};

	void foo(Myclass);
}

//.cpp
int main()
{
	A::Myclass ax;
	ax.func(); // geçerli
	foo(ax);  //geçerli.
}

===========================================================================================================
===========================================================================================================
===========================================================================================================

INLINE NAMESPACE C++17 DE GELDİ.
--------------------------------

namespace A
{
	namespace B
	{
		namespace C
		{
			int x;
		}
		using namespace C;
	}
	using namespace B;
}
using namespace A;

int main()
{
	x = 25; artık bu durumda direkt görür.
	
	// using namespace A; olmasaydı A::x = 40; olurdu
	// using namespace A ve B; olmasaydı A::B::x = 40; olurdu
	// using namespace A ve B ve C; olmasaydı A::B::C::x = 40; olurdu
}


---------------------------------------------------

BİRDE BU GARİP ÖRNEK VAR.

namespace A{
	namespace B
	{
		class Myclass {
		};
	}
	void func(B::Myclass);
}

int main()
{
	A::B::Myclass x;
	func(x); // SENTAKS HATASI.Çünkü x b namespace i içinde ama b functionu A namespace içinde tanımlanmış.Burası garip.
	
	//B den sonra using namespace B; yapsak bile yine hata devam ediyor.
}	

-----------------------------------------------------------------------------------------------------------------

INLINE A DİKKAT

namespace A
{
	int a;
	namespace B
	{
	inline namespace C
		{
			int x;
		}
	}
}

int main()
{
	A::B::x = 23; //geçerli
	A::x = 33; // geçeli
}

inline namespace C bildirimde adeta sanki biz bu namespace çıkışında using namespace c yazmışım gibi 
c namespace içindeki isimler doğrudan B namespace içinde visible hale geldiler.

B yide inline yazarsak öncekindeki gibi olur. b namespace içindekiler A içinde doğrudan görülür.

A da yapılabilir....

Artık MODERN C++ ta bir çok kütüphanenin inline tanımlandığını görüyoruz.
----------------------------------------------------------

GARİP ÖRNEĞİ INLINE İLE ÇÖZÜYORUZ.

namespace A{
	int a,b;
	inline namespace B
	{
		int x,y;
		class Myclass {
		};
	}

	void func(B::Myclass);
}

int main()
{
	A::Myclass m;
	func(m); // inline yazmayınca ilk örneklerde bu hata idi.

}


-------------------------------

#include <string>
#include <chrono>

int main()
{
	std::literals::string_literals::s; s bir nesne, diğerleri nested namespace
	std::literals::s; bunlarda nested namespace. hatta inline namespace kanıtı da s in kullanılabilmesi.
	std::s; burada bile görülüyor :D:D
	std::chrono::milliseconds
}

literals namespace ve string_literals namespace inline namespace

AÇık açık yazmadım. hoca iç içe namespaceler yazıp inline yazdı başlarına.

--------------------------------------------------------------------------

namespace A
{
	inline namespace B{
	void func();
	}
	inline namespace C{
	void foo();
	}

}

int main()
{
	A::func();
	A::foo(); ikiside geçerli.
}

-----------------------------------------------------------------------------------------------------------

INLINE NAMESPACELERİN BİR AVANTAJIDA VERSION KONTROLUNDE KULLANILMASI
---------------------------------------------------------------------
Biz belirli kodlarda  belirli kodsal varlıkları versiondan versiona değiştirmek istiyoruz.
Gerekirse bir versiondakini gerekirse diğer versiondakini kodları değiştirmeden kullanmak istiyruz.
Bunu sağlıyor.

namespace project{
	
	namespace Version1
	{
		class Myclass{
		
		};
	}

	namespace Version2
	{
		class Myclass{
		
		};
	}

}

int main()
{
	Project::Version1::Myclass
	Project::Version2::Myclass
	// bu şekildede ikisinede erişilir.

}


-----------------------------------------

Şimdi kullanmak istediğimiz versionun namespaceini inline olarak tanımlarsak
kapsayan namespacetede visible hale gelir artık bu.


namespace project{

	inline namespace Version1
	{
		class Myclass{

		};
	}

	namespace Version2
	{
		class Myclass{

		};
	}

}

int main
{
	project::Myclass m; // inline tanımlandığı için namespace version1, içindeki tüm isimler onu kapsayan namespacede visibledır.
}						// tam terside yapılabilirdi. version2 inline olursa bu seferde version2 deki myclass ı kullanabiliriz.
						// ikiside aynı anda inline olsaydı, ambigiuty olurdu.

-----------------------------------------------------------------------------------------------------

Conditional compiling ilede birleştirilip kullanılabilir.
-----------------------------------------------------------


#define Version_1 // dersem 1. ifdef koşulu doğru version1 inline olacaktı.
#define Version_2 // dersem 2. ifdef koşulu doğru version2 inline olacaktı.


#define Version_1   // ben version1 i inline ederek onun myclass sınıfını kullandım

namespace project{
	

	#ifdef VERSION_1
		inline
	#endif
	namespace Version1
	{
		class Myclass{

		};
	}

	#ifdef VERSION_2
		inline
	#endif
	namespace Version2
	{
		class Myclass{

		};
	}

}

int main()
{
	Project::Myclass m;
}

----------------------------------------------------------------------

namespace A{
	namespace B{
		namespace C{
			int x;		
		}	
	}	
}

int main()
{
	A::B::C::x = 5; geçerli
	A::B::x = 23; //har
	A::x = 123; // hata
	x = 5; // hata
}

AMA !!!!

inline namespace A{
	inline namespace B{
		inline namespace C{
			int x;
		}
	}
}

int main()
{
	A::B::C::x = 5; Artık hepsi geçerli
	A::B::x = 23; ok
	A::x = 123;  ok
	x = 5;   ok
}

------------------------------------------------------------------------------------------

namespace A::B::C //c++17 
{
	int x = 20;
}

inline namespace A::B::C //c++20. Bazı derleyiciler implemente etmiş, bazıları etmemiş.
{
	int x = 20;
}

----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------

UNNAMED NAMESPACE
------------------

Sadece ilgili kaynak dosyada geçerli olan ve bir using bildirimi olmadan doğrudan sanki inline keyword ile tanımlanmış gibi,
bu namespacedeki isimleri bunu kapsayan namespacede yani global namespacede kullanabileceğimiz bir özellik.

namespace{
	int x;
	double dval;
}

int main()
{
	x = 6; // derleyince hata vermedi.
}

1. kural : ilgili kaynak dosyada global namespacede visible hale geliyor.
			modern c++ öncesinde de kullanılan bir araç.
Ne işe yarıyor?
Bu namespace in ismi var sayalım. hemen çıkışında using namespace ismi; olduğunu varsayalım.
Ör:

namespace name1
{
	int x;
	double dval;
}
using namespace std;

int main()
{
	x = 5;
}ait 

Bunları yapıyor aslında unnamed namespace

Neden kullanalım?
UNNAMED NAMESPACE LER INTERNAL LINKAGE A AIT.
EXTERNAL LINKAGE = FARKLI KAYNAK DOSYALARDA BİR İSİM AYNI VARLIĞA İŞARET EDİYORSA BUNA EXTERNAL LİNKAGE DENİR.
INTERNAL LİNKAGE = O İSİM SADECE O KAYNALK DOSYADA KULLANILDIĞINDA AYNI VARLIĞI GÖSTERİYOR.AYNI İSİM BAŞKA KAYNAK DOSYADA
					BAŞKA BİR VARLIK OLABİLİR.

C DEN BİLDİĞİMİZ LINKAGE OLAYLARINA UFAKTAN GİRDİ.YAZMIYORUM.


Modern c++ öncesinde eklenildi.
static in kullanılıp internal linkage a ait demek deprecated oldu
Bunun yerine isimsiz namespace kullanıytoruz.

namespace
{
	//artık namespacedeki tüm isimler iç bağlantı internal linkage a ait.
}

değişken function tür isimleri konulabiliyor.
Not: const nesnelerde bağlantı kuralı C den farklı
const int x = 10; bu global scopeta ise,C++ ta x internal linkage a ait.


ÖR:
nutility.h
const int x = 10;

nutility.cpp
#include "nutility.h"

main.cpp
#include "nutility.h"

x external linkage a ait olsaydı linker aşamasında linker hata verebilirdi.
ama internal linkage a ait olduğundan hata vermedi.

-------------------------------------------------------------------------------------------------------------------

bunun üstüne şunu yapalım.
nutility.h
const int x = 10;
void fx();


nutility.cpp
#include "nutility.h"
#include <iostream>

void fx()
{
	std::cout << "&x = " << &x<<"\n"; //const nesnelerin adresi alındığında derleyici onlara yer ayırmak zorunda.
}					  // adresini almazsak, kod içinde sabit gibi kullanırsak compiler yer ayırmak zorunda değil.

main.cpp
#include "nutility.h"
#include <iostream>

int main()
{
	fx(); // buradaki x adres ile
	std::cout << "&x = " << x << "\n"; //buradaki x in adresi farklı çünkü bunlar ayrı nesneler.const ile tanımlanınca internal linkage
}

C ile C++ ın internal linkage olayı farklı.
C de kod file da static yapıyorduk. C++ ta header fileda bildirebiliyoruz.ama farklı nesneler oluyor bu değişkenler.

---------------------------------------------------------------------------------------------------------------

BIRDE BU DEĞIŞKENI INLINE OLARAK TANIMLAYALIM
inline const int x = 10;

-----------------
nutility.h
inline const int x = 10;

nutility.cpp
#include "nutility.h"

main.cpp
#include "nutility.h"


nutility.h
void fx();

nutility.cpp
#include "nutility.h"
#include <iostream>

void fx()
{
	std::cout << "&x = " << &x<<"\n"; //const nesnelerin adresi alındığında derleyici onlara yer ayırmak zorunda.
}										// adresini almazsak, kod içinde sabit gibi kullanırsak compiler yer ayırmak zorunda değil.

main.cpp
include ları yap

int main()
{
	fx(); // buradaki x adres ile
	std::cout << "&x = " << x << "\n"; //değişken inline olunca bu değişkenden bir tane olması garantiydi.Bu sefer aynı adresi verdi
}

------------------------------------------------------------------------------------------

ÖR:

nutility.h
int foo();
void fx();
const int x = foo();

nutility.cpp
void fx()
{
	std::cout <<"&x = " << &x << "\n";
} 

int foo()
{	
	std::cout << "foo()\n";
	return 1;
}

main.cpp
include nutility.h ve iostream
main()
{
	// bunu boş olarak çalıştırınca birkaç tane "foo()" yazısı göreceğiz.
	//çünkü internal linkage ve her include eden kendi x ini init ediyor.
	//inline olsaydı 1 adet foo() görecektim
}

Özetle = const değişkenler global olması durumunda internal linkage a ait.bir const değişekenin tanımını header file koyunca
ODR ihlali olmuyor ve bunu include eden her kod dosyasında ayrı bir değişken meydana geliyor.

--------------------------------------------------------------------------------------------------

hem main.cpp de hemde neco.cpp de aşağıdaki tanım var.
namespace
{
	int x = 23;
}

Buradaki değişkenler bu durumda farklı oluyor.

Internal linkage a konulmak istenen nesneleri isimsiz bir isim alanına koy !!!

--------------------------------------------------------------------------

namespace {
	int a,b,c;
}

namespace{
	int x,y,z;
}

int main()
{
	a = 10;
	x = 34;	İkiside visible
}



-------------------------------------------------------------------------------------------------

Modern C++ öncesinden gelen bir araç
Biz biir header file ile dışarıya sunacağımız isimleri bir namespace içinde versek
Aşağıdaki isimlerin artık çakışması riskini kesin olarak ortadan kaldırmış olur muyuz

namespace neco{
	//
}

%99 çözüyor.%1 çözemiyor :D:D

neco burada namespacein kendi ismi, bu isimde tek olmak zorunda. Kod dosyasında neco başka isimlerle çakışabilir.
Buna karşı önlem almakta mümkün. Bir eş isim alias bildirilebiliyoruz.

Türlere de eş isim bildirimi legal.Buradaki sentaksa namespace alias deniyor.

namespace neco_project
{
	int x,y;
}

namespace nec = neco_project;
tabi bu bildirimin olması için nec visible olmalı.

int main()
{
	neco_project::x = 10;
	nec::x = 20;  //aynı anlamdalar.
}


------------------------------------------------------------------------

NESTED NAMESPACELER IÇINDE ALIAS VERILEBILIYOR

int main()
{
	namespace rgc = std::regex_constants;

	std::regex_constants::egrep;
	rgc::egrep;
}

-------------------------------------------------

namespace ali::veli::hasan::huseyin
{
	int x = 10;
}

int main()
{
	ali::vel::hasan::huseyin::x;
	namespace nec = ali::vel::hasan::huseyin;
	nec::x;

}


============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================
============================================================================================================================================================


STRING SINIFI
-------------
String bir sınıf şablonu.Aslında ismi string değil.
ismi basic_string olan bir sınıf şablonu var.
Bu öyle bir kodki derleyici o koda dayanarak derleyici bizim için bir sınıfın kodunu yazabiliyor.
Şablon derleyiciye sınıf kodu yazdıran kod demek.
basic_string in 3 adet template parametresi var

#include <string>

int main()
{
	std::basic_string<char, std::char_traits<char>, std::allocator<char> std;
}

ilk eleman wchar_t açılımı yaparsak. yazının her karakteri wchar_t türünden demek. Hoca kurs boyunca char kullanacak
ikinci eleman yazının karakteriyle ilgili işlemlerin nasıl yapılacağını belirleyen sınıf.Böyle sınıflara trait sınıflar deniyor
Buna bir tür argümanı geçmeyince std library nin std::char_traits<char> ı kullanmış oluyoruz.
Üçüncü parametre, tüm containerlarda 1 istisna hariç, dinamik bellek yönetiminden sorumlu sınıf. Böyle sınıflara allocator deniyor
std::allocator<char> kullandığımızda derleyiciye bir sınıf kodu yazdırmış oluyoruz.

std::basic_string<char, std::char_traits<char>, std::allocator<char> str; // derleyiciye bir sınıf kodu yazdırmış oluyoruz ve 
ismi str olan bir değişken tanımlandı.

Biz türeş bildirimi olmasaydı biz sınıf ismini yukarıdaki gibi yazmamız gerekirdi.
Tür eş ismi olarak buna string ismini vermişler yani;

std::string str; // aşağıdaki ile aynı.
std::basic_string<char, std::char_traits<char>, std::allocator<char> str; 


----------------------------------------------------------------------------------------------

String sınıfı büyük bir interface e sahip. Çok fazla üye fonksiyon var.
Bu üye fonksiyonlarında 3-4-5 veya 6 adet overload u var.
String sınıfı bir yazıyı dinamik bir bellek adresinde tutuyor.
Yani bu yazıların kendişi heapta tutuluyor.

#include <iostream>
int main()
{
	std::string str{"Bugun hava cok sicak"};
}

tipik olarak bu dinamik dizi sınıflarında/vectorde dahil nesnemizin içinde 3 adet pointer var.
Bu implementasyon tercihi ama en az 1 ptr olacak. 

A - Pointerlardan biri dinamik bellek bloğunun adresini tutuyor.
	1 - Dinamik dizi ver iyapısının bir numaralı avantajı index bilgisiyle dinamik dizide tutulan öğelere constant time O(1) karmaşıklığında erişmek. 
	2 - Sondan ekleme ve sondan silme işlemlerininde constant time da yapılmasıda avantaj.
B - İkinci pointer yazının sonunu tutuyor.
C - üçüncü pointer ise dinamik bellek bloğunun sonunu tutuyor.

Arka planda dinamik dizi için ayrılan bellek alanının dizideki öğe sayısı cinsinden ifadesine capacity deniyor.

Dizim 120 karakter, yazı 40 ise , 80 karakter daha eklenir demek bu.
Öyle bir durum oluşacakki dinamik bellek bloğunun uzunluğu ile dinamik bellek bloğunun byte olarak büyüklüğü birbirine eşit olacak
yani kapasite değeri yazı uzunlupuna eşit olacak. Bu şu demek. clientten ekleme talebi gelince yer yok demek.
Bu durumda reallocation yapacağız demek.
Visual studiodaki implementasyonda kapasite %50 artıyor her allocationda. Bazı derleyicilerde 2 katına çıkarıyor.

Dinamik dizide tutulan öğe sayısına size diyoruz.
Dinamik dizi için ayrılan bellek bloğunun öğe sayısı cinsinden ifadesine capacity deniyor.

Modern İmplementasyonlarda sadece 3 pointer tutmuyorlar. Birde buffer tutuyorlar.
Buradaki tekniğe Small String Optimization deniyor. Eğer string nesnesindeki yazı küçükse
dinamik bellek yönetimine girmeden yazıyı bu bufferda tutuyor. Böylece bir allocation yapılmıyor.
Yazı bu bufferda tutulacak kadar kısa ise Din. Bell. Yönet. gerek kalmyor.
Yazı sonradan büyütülürse yine dinamik bellek yönetimi çalışır.

sizeof(string) değeri 24 Byte tuttu.
Gcc de wandboxta hem char * hemde stringin sizeofuna baktı.
8 byte ve 32 byte çıktı. 

C deki char dizilerden farklı olarak burada sınıf yazıyı dinamik olarak büyütebiliyor.
NE zaman bellek alanı yetersiz olursa yeni bellek alanı allocate edilip eskisi free ediliyor.

Yazının nihai uzunlupu belliyse ve yazıyı yavaş yavaş büyütürsek ciddi maliyet demektir.


ÖNEMLİ !!!!!

Mülakat sorusu
1. Kritik nokta Aynı zamanda
Baştan yazı uzunluğu belliyse, o uzunluğa göre allocate edilme yapılabilir.Reserve isimli function.
Vectorde de var stringde de var.

2. Kritik nokta
Dinamik dizide kapasite büyür otomatik olarak, ama kapasite otomatik olarak küçültülmez.
Yazının karakteri 100000, ama artık ufalttık 2000 e indirdik. Arka taraftaki o kapasitenin geri verilimi yapılmıyor.

Fazla kapasiteyi geri kendimiz verebiliriz. Bu bir member function ile yapılır.Adı shrinktofit


MOLA
========================================================================================================================


Şimdi String sınıfının interface ini göreceğiz.
Yani global funcları member funcları göreceğz...

Bu konu operator overloading mekanizmasındanda sonuna kadar faydalanıyor.

----------------------------------------------------------------------------------------------------------------------

#include <string>

int main()
{
	string s;
	// s. yazıp buradan kaç tane functionı olduğuna baktı hoca. Baya bir var.Hatta member functionların bolbol overloadları var.

}

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

String sınıfı aynı zamanda STL containerı.
Stringin amacı yazıları manipüle etmekte olsa aslında container.
Container nedir? Container veri yapılarını implemente eden temsil eden sınıflara verilen isim.
dinamik dizi, bağlı liste, ikili arama ağacı ... bunlar bir containerdır.

STL bir Acronim aslında. Standart template library.Kursun çok büyük bir kısmı STL i anlatıyor.
Bunu ne kadar bilirsek o kadar iyi.Bilmemek diye birşey sözkonusu değil.
STL kütüphanesi yazılımsak varlıklardan oluşuyor. Bunlardan biride containerlar.
Mesela, vector, deque, list, forward_list, string, array,set...  Bunlar STL in container sınıfları.
Bunların ortak arayüzü var. yani öyle fonksiyonlar varki tüm container sınıfları için aynı anlama geliyor.

Sequence Container
	vector, deque, list, forward_list, string, array

Associative containers
	set,multiset,map, multimap

Unordered Associative containers
	Unordered ile başlayan containerlar

Bazı fonksiyonlar sadece sequence containersta ortak iken bazılarıda tüm containerlarda var.
Yazı işlemlerin bir kısmını string sınıfının member functionları yapıyor.
Bazı işlemleride algorithm denilen containerlar üzerinde işlemler yapan global functonlarla(aslında func. templatei) gerçekleştirilmesi

Bir string işlemi yaparken neleri kullanıyoruz.
1 - Sınıfın member functionları
2 - Global Functionlar(string headerı içinde)
3 - Algoritma functionları

================================================================================================================
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str; // henüz yazı tutmayan, yazı uzunluğu 0, boş bir string nesnesi.
}

---------------------------------------------

size
----
2 adet üye function var.const member func.tutulan yazının uzunluğunu get ediyor.
Birinin ismi size. Bu bir const member function. Nesnenin tuttuğu yazının uzunluğunu verir.
string sınıfı içinde tanımlanan nested typelardan biri string::size_type isimli sınıf.
Bu aslında işaretsiz tamsayı türünün eş ismi. String sınıfı için bu tür size_t türü.

Yazının uzunlupunu bir değişkende tutmak istesem string::size_type ama bu da size_t nin eşismi
olunca doğrudan size_t yide kullanabiliriz.

int main()
{
	string str; // henüz yazı tutmayan, yazı uzunluğu 0, boş bir string nesnesi.
	string::size_type len = str.size();
	size_t len = str.size(); // yukarıdaki ile aynı.Tercih yukarıdaki.
	auto len = str.size(); // buda olabilir.
}

cout << "uzunluk = " << str.size(); bu şekilde yazdırılabilir. veya len göndererek.

--------------------------------------------------------------------------------------

lenght
------
Uzunluğu get eden diğer functionda lenght functionu.size ın amacı generic programlama tarafı.
Ama yazı işlemlerinde size veya lenght çağırmanın farkı yok.İkiside yazı uzunluğunu verir.

cout << "uzunluk = " << str.lenght();

--------------------------------------------------------------------------------------------

empty
-----
Bu boolean döndürüyor. Boşmu sorusuna cevap veriyor.Yazı 0 uzunluğunda ise true döndürecek.
bu bir predicate yani boolean döndürüyor.

std::cout << boolalpha << str.empty() << "\n";

--------------------------------------------------------------------------------------------

capacity
--------

Stringin kapasitesini get ediyor.

int main()
{
	string str{"Alican buraya gel hemen"};

	std::cout << "Uzunluk = " << str.size() << "\n";
	std::cout << "Kapasite  = " << str.capacity() << "\n";
	// uzunluk 23 kapasite 31 

	str+= "01234567";	

	std::cout << "Uzunluk = " << str.size() << "\n";
	std::cout << "Kapasite  = " << str.capacity() << "\n";
	// uzunluk 31 kapasite 31 
	
	str.push_back('A');
	std::cout << "Uzunluk = " << str.size() << "\n";
	std::cout << "Kapasite  = " << str.capacity() << "\n";
	// uzunluk 32 kapasite 47  	

}

-------------------------------------------------------------------

Reallocation kodunu yazalım

int main()
{
	strint str{"Alican Hemen Buraya gel"};

	size_t cap = str.capacity();

	while(true)
	{
		str+= 'x';
		if(str.capacity() > cap)
		{
			std::cout << "uzunluk =  : " << str.size() << "kapasite = " << std.capacity() << "\n";
			cap = str.capacity();
			(void)getchar();
		}
	}
}

Buradada görülür nasıl artırıldığını gösteriyor.

----------------------------------------------------------------------------------------------------------

Kaç kere reallocate dildiğini göstermek için aşağıdaki kodu yazıyoruz.

int main()
{
	strint str{"Alican Hemen Buraya gel"};
	size_t cap = str.capacity();
	int cnt{};

	while(str.size() < 1'000'000)
	{
		str+= 'x';
		if(str.capacity() > cap)
		{
			std::cout << ++cnt << "uzunluk =  : " << str.size() << "kapasite = " << std.capacity() << "\n";
			cap = str.capacity();			
		}
	}
}

Yukarıdaki kod 1 milyona çıkana kadar kaç kere reallocation yaptığını gösteriyor.Bürsürü reallocation var.
Bulun olmaması için

-----------------------------------------------------

koda str.reserve(1'000'000); satırını ekleyeceiz.

int main()
{
	string str{"Alican Hemen Buraya gel"};
	str.reserve(1'000'000);

	size_t cap = str.capacity();
	int cnt{};

	while(str.size() < 1'000'000)
	{
		str+= 'x';
		if(str.capacity() > cap)
		{
			std::cout << ++cnt << "uzunluk =  : " << str.size() << "kapasite = " << std.capacity() << "\n";
			cap = str.capacity();
		}
	}
}

=======================================================================================================================

Görülen fonksiyonlar
--------------------
size
lenght
capacity
empty

reserve henüz görülmedi sadece bahsettik.

Nasıl ilerleyeceğiz?
Constructorlar.
string str{}; burada ctor çağrıldı zaten 
string str(); bu fonksiyon decleration :D

---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------

CSTRING PARAMETRELI CONSTRUCTOR
---------------------------------
Bu C deki gibi bir yazı demek. Null terminated byte stream.
Sadece Ctor değil, string sınıfının member fonksiyonlarının bazı üye fonksiyonların overloadları const char * parametreye sahip.
Eğer const char * görürsek ve buna eşlik eden parametre yoksa bu her zaman, ilgili function Null character görene kadar
bu adresteki yazıyı kullanacak.

int main()
{
	string s{"Nevzat Can Samur"};
	std::cout << "s = " << s << " lenght = " << s.lenght()<<"\n";
}

Cstring parametreli tüm member functionlar için yazının sonunda null character olmasından biz sorumluyuz.
Olmazsa Tanımsız Davranış.

int main()
{
	char str[]{'A','B','C','D'};
	string s{str};
	std::cout << "s = " << s << "\n"; //UNDEFINED BEHAVIOR
}


*/

#include <string>
#include <iostream>

int main()
{
	using namespace std;
	string str(20, 'a');
	std::cout << "str.size() = " << str.size() << "\n"; //20
	str.resize(40, 'X'); //string size 20 den 40 a çıkar.Sonuna X ler ekler.
	std::cout << "str.size() = " << str.size() << "\n";// 40
	std::cout << "str.capacity = " << str.capacity() << "\n";// 47
}
