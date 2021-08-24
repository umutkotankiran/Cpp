/*
Template lerin sonlarına geldik
son kaldığımız yerden devam ediyoruz.
Alias template. Modern C++ ile geldi
variable template C++ 14 ile geldi.

Alias Template Hatırlatma
-------------------------
Eş isim bildirimini bir parametreye bağlıyor ve STL de de yoğun kullanılıyor

struct Neco{
	using type = int; //burada nested type olmasını istedik
};

Neco::type // türe erişebiliyoruz. 

--------------------------------------------------------------------------------------------------------------------------

AMA NECO DA BIR TEMPLATE ISE

template <typename T>
struct Neco{
	using type = T *; // int idi T * yaptık. Buda olabilir çünkü
};

int main()
{
	Neco<int>::type // böyle yazmam gerekir
}
--------------------------------------------------------------------------------------------------------------------------

BUNU TEMPLATE BAĞLAMINDA YAPIYORSAK

template <typename T>
struct Neco{
	using type = T *; // int idi T * yaptık. Buda olabilir çünkü
};

template <typename T>
void func()
{
	typename Neco<T>::type .. // burada template tür parametresine bağlı olduğundan typename kullanmak zorundayız
}

--------------------------------------------------------------------------------------------------------------------------

YUKARIDAKILERIN YERINE TÜR EŞ ISIMI BILDIRIMI YAPSAYDIM

template <typename T>
struct Neco{
	using type = T *; // int idi T * yaptık. Buda olabilir çünkü
};

template <typename T>
using Neco_t = typename Neco<T>::type;

int main()
{
	Neco_t<int> ; // typename Neco<int>::type demek
}

DİKKAT ÇOK ÖNEMLİ!!!!!!!!!!!!!!!!
STRUCT NECO IÇINDEKI T* BIR TÜR, BIR VALUE DEĞIL. BU DURUMDA ALIAS TEMPLATE KULLANACAĞIZ VE TYPENAME KEYWORD OLACAK.
EĞER BIR VALUE OLSAYDI TYPENAME KULLANMAYACAKTIM. ZATEN ORADA VARIABLE TEMPLATE IŞIN IÇINE GIRECEK.

--------------------------------------------------------------------------------------------------------------------------

YAZIM KOLAYLIĞI VEYA TEMPLATE ARGÜMAN SAYISINI AZALTMAK IÇIN ÇOĞUNUKLA ALIAS TEMPLATE TERCIH EDILIYOR.

int main()
{
	map<int, greater<int>>; yazmak ile bunu alias template ile daha kolay hale getirilebilir.
}

Aşağısı daha pratik.
template  <typename T>
using gmap = std::map<T, std::greater<T>>;

int main()
{
	gmap<double>; // std::map<double>, std::greater<double>>; oldu
}

====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================


VARIABLE TEMPLATE 
-----------------

Modern C++ ta Variable template geldi. Değişken şablonları.Kitaplarda anlatılan variable template anlatımları asıl kullanımı anlatmıyor.%99 böyle.
Alias template ile karıştırma.Alias template ta tr bilgisi vardı, burada doğrudan value var.

template <typename T>
auto pi = (T)(3.14159);  // TÜm kitaplar bu örneğe benzer örnek veriyor.

int main()
{
	pi<double>t; //sabit double oldu
	pi<float>t; //sabit float oldu // Buradan elde edilecek fayda yüksek bir fayda değil.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------

BU VARIABLE TEMPLATE DAHA ÇOK CREATE SINIFLARINDA VE TEMPLATE METAFUNCTION TARAFINDA FAYDA SAĞLIYOR.

template <typename T>
constexpr bool int x = sağ tarafta bir template in static veri elemanı kullanılıyor ilk değer olarak.

ÖR:
struct Neco{
	//..
	constexpr static bool value = true; // tmp kütüphanelerinde value nun bu şekilde kullanılması çok yaygın.
};

constexpr bool x = Neco::value; // Bu şekilde olabilir.

-------------------------------------------------------------------------------------------------------------------------------------------------------

ARTIK CLASS TEMPLATE

template <typename T>
struct Neco{
	//..
	constexpr static bool value = true; // tmp kütüphanelerinde value nun bu şekilde kullanılması çok yaygın.
};


Neco<int>::value; // her seferinde böyle yazmak yerine başka nasıl yazabiliriz.
Bunu yapmanın yolu VARIABLE TEMPLATE

-------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
struct Neco{
	//..
	constexpr static bool value = true; // tmp kütüphanelerinde value nun bu şekilde kullanılması çok yaygın.
};

template <typename T>
constexpr bool Neco_v = Neco<T>::value;

int main()
{
	Neco_v<int>; // Artık bu kullanılabilir. Bu Neco<int>::value ile aynı.
	Senaryo constexpr static elemanlarda bu elemanlara daha rahat ulaşmak.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------

Bunun çok sayıda örneği ile karşılaşacağız.

include <type_traits>

int main()
{
	std::is_integral<int>::value ; // Şuanda bir sınıfın constexpr static veri elemanını kullandık.
	std::is_integral_v<int>; //bununla yukarıdaki aynı anlamda.
}
Burada variable template kullanılmış.

-------------------------------------------------------------------------------------------------------------------------------------------------------

Yukarıdakini biz yazalım.

template <typename T>
constexpr bool isIntegral_v = std::is_Integral<T>::value

Bunların genelde kullanıcısı olacağız.
Ne zaman kendimiz yazacağız. Metafunction oluşturduğumuzda yazacağız.


===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================
===================================================================================================================================================================

METAFUNCTION
------------
Bu en zor anlaşılan konu. Bu terimi bazı insanlar farklı anlamda kullanıyor.Compile time da değer üreten yapılara deniyor. Compile time da değer üretiyor.
Bu bir function değil hatta implementasyonda yapılar kullanılıyor.

İKİYE AYRILIYOR.
Compile timeda bir tür üreten/elde eden metafunclar
compile timeda değer/birsabit elde eden metafunctionlar.

Bir func şablonumuz var. T türüne bağlı olarak tür elde etmek istiyoruz.T referans ise referanslığı ortadan kaldırmak istiyoruz diyelim.
Ör:
T int& ise biz int türünü kullanacağız.
T int&& ise biz yine int türünü kullanacağız.

template <typename T>
void func(T x)
{
	// yani ne olursa olsun türün referans içermeyen biçimini kullanacağız.	
}

Bunu nasıl elde edeceğiz.

template <typename T>
struct remove_reference
{
	using type = T;
}

remove_reference<int>::type --> int türüdür.
remove_reference<int&>::type --> int& türüdür.   // Dİkkat decution yok.Deduction olduğunda & lik düşüyordu.burada explicit verilmiş.

Burada partial specialization yazılacak artık.

-------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
struct Remove_reference
{
	using type = T;
}

template <typename T>
struct Remove_Reference<T&>
{
	using type = T;	
}

template <typename T>
struct Remove_Reference<T&&>
{
	using type = T;	
}

template <typename T>
void func(T)
{
	typename Remove_Reference<T>::type ; // Buradaki T bir referans olsa bile referans olmayacak.
}										 // T nin int& olduğu anlaşılırsa.Remove_Reference<int&>::type = int türü olacak
											referanslık siliniyor.

int main()
{
	Remove_Reference<int&>::type x; // Burada int& değil int türünü kullanmış olacağım
	Remove_Reference<int&&>::type x; // Burada int&& değil int türünü kullanmış olacağım yine
										// her seferinde kullandığım specialization değişiyor.Bu sebeple int 
}

-------------------------------------------------------------------------------------------------------------------------------------

Burada alias template kullanılacak.

template <typename T>
struct remove_reference
{
	using type = T;
}

template <typename T>
struct Remove_Reference<T&>
{
	using type = T;
}

template <typename T>
struct Remove_Reference<T&&>
{
	using type = T;
}

template <typename T>
using Remove_Reference_t = typename Remove_Reference<T>::type;

template <typename T>
void func()
{
	Remove_Reference_t<T>;
	typename Remove_Reference<T>::type;  // Bu ikisi arasında bir fark yok.
}

BU tip fonksiyonlar metafonksiyonlar. type traits te birsürü tür veren metafunc var.

-------------------------------------------------------------------------------------------------------------------------------------

#include <type_traits>

int main()
{
	std::remove_reference_t<int &>; // referanslık düştü. türü int
	std::remove_reference_t<const int &> x; // Sentaks hatası.Burası int değil const int türü
											// const değişkene ilk değer vermemek sentaks hatası

	std::remove_const<int>::type; // burası int													
	std::remove_const<const int>::type; // burası da int												
	std::remove_const_t<const int>; // burası da int yukarıdaki açılımla aynı anlamda												

}

-------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void func()
{
	std::remove_const_t<T> x; // const int ise T, tür int olacak, const string ile string olacak
}								

-------------------------------------------------------------------------------------------------------------------------------------

METAFUNCTION, FUNCTION DEMEK DEĞIL.COMPILE TIMEDA HESAPLAMA YAPAN BIR ARAÇ DEMEK.BU ARAÇ IÇIN YAPILAR KULLANILIYOR GENELDE.

template <typename T> // const olmayanlar için bu özelleştirme oluşacak
struct RemoveConst{
	using type = T;
};

template <typename T>
struct RemoveConst<const T> // const türler için bu özelleştirme 
{
	using type = t;
}


-----------------------------------------------------------------------------

Birde add_cv add_const add_volatile var. Bunlarda tam tersini yapıyor.
Buda ekleme yapıyor. Mesela constluk yok ama ekliyor gibi.

34:00
https://github.com/necatiergin/cpp-kursu-kodlar/tree/main/templates/type_traits/transformation

Bunlar zaten standart kütüphane tarafından oluşturulmuş.

-------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void func(T x)
{
	// Acaba T türü bir tamsayı türü mü
	// Acaba T türü bir gerçek sayı türü mü
	// Acaba T türü bir const türü mü
	// Acaba T türü bir pointer türü mü
	// Birüsü soru sorulabilir.
}

- Sadece tamsayı türleri için kullanılacak template i, gerçek sayı ile açtığımızda sentaks hatası vermesini sağlayabiliriz.
- T türünün belirli özelliklerine göre farklı şablonlar sağlayabiliriz.Tamsayı olunca ayrı, ptr olunca ayrı kod kullanılmasını sağlayailiriz

-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------


Birtakım programlama tekniklerini kullanarak compile time da T türünün belirli bir özelliği sağlayıp sağlamadığını
test edebilir miyiz? Runtime değil. Compile time.Bunu yapabilirsek compile time de türe bağlı olarak if deyimi
oluşturabiliriz. T ptr ise bir kod, değilse başka bir kod gibi...

Dolayısı ile bir türün bir özelliği sağlayıp sağlamadığını anlamak çok önemli.
Önce primitive bir şekilde oluşturacağız sonrada type traits anlatılınca özü aynı ama biraz daha profesyonel bir araç kullanılacak.

-------------------------------------------------------------------------------------------------------------------------------------------------

BIR TÜRÜN VOID TÜRÜ OLUP OLMADIĞINI ANLAYAN BIR METAFUNC YAZACAĞIZ.

template <bool x>
struct Neco;

Neco<false>; // bu ayrı
Neco<true>; //bu da ayrı tür

-------------------------------------------------------------------------------------------------------------------------------------------------

template <bool x>	// template type parameter
struct bool_constant{
	static constexpr bool value = x;
};

int main()
{
	bool_constant<true>::value; // bu doğrudan true değeri
	bool_constant<false>::value; // bu doğrudan false değeri
}

-------------------------------------------------------------------------------------------------------------------------------------------------

KALITIM YOLUYLA YUKARIDAKİ SINIFTAN KALITIM GERÇEKLEŞTİRELİM.

template <bool x>
struct bool_constant{
	static constexpr bool value = x;
};

template <typename T>
struct Neco : bool_constant<false>{		// burada taban sınıfın öğeleri aynı zamanda türemiş sınıfında öğeleri
										// NOT : STL de kalıtım var ama rutime polymorphism yok.
};

int main()
{
	Neco<int>::value;  // bu bool_constant<false>::value oluyor buda false demek.Çünkü false açılımından kalıtımla elde edilmiş
}

-------------------------------------------------------------------------------------------------------------------------------------------------

BIR TÜRÜN VOID OLUP OLMADIĞINI NASIL ANLAYACAĞIZ

template <typename T>
struct is_void : bool_constant<false>{

};

int main()
{
	is_void<int>::value // hangi türle açarsak açalım false olacak.Çünkü false açılımından kalıtımla elde edilmiş
}

-------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKINI ÖZELLEŞTIRIRSEK.
is_void yapısını void türleri için excplicit specialization a tabi tutsak ve onlarıda bool_constant<true> ile elde etsek


template <bool x>
struct bool_constant{
	static constexpr bool value = x;
};

template <typename T>
struct is_void : bool_constant<false>{ };

template <>
struct is_void<void>: bool_constant<true>{ };

template <>
struct is_void<volatile void>: bool_constant<true>{ };

template <>
struct is_void<const void>: bool_constant<true>{ };

template <>
struct is_void<const volatile void>: bool_constant<true>{ };

template <typename T>
void func()
{
	is_void<T>::value
}

int main()
{
	is_void<int>::value // false 
	is_void<void>::value // true 
	is_void<const void>::value // true 
}


------------------------------

template <bool x>
struct bool_constant{
	static constexpr bool value = x;
};

template <typename T>
struct is_void : bool_constant<false>{ };

template <>
struct is_void<void>: bool_constant<true>{ };

template <>
struct is_void<volatile void>: bool_constant<true>{ };

template <>
struct is_void<const void>: bool_constant<true>{ };

template <>
struct is_void<const volatile void>: bool_constant<true>{ };

template <typename T>
constexpr bool is_void_v = is_void<T>::value; // BURADA TYPENAME YOK ÇÜNKÜ BU BIR ALIAS TEMPLATE DEĞIL !!!!!

int main()
{
	is_void_v<int> //false yani void değil.
}

type traits altında bu sorgulamaları yapacak 10larca template var.
Bir kısmı library geliştirenleri ilgilendiriyor olabilir.


====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================


TYPE TRAITS
-----------

template <typename T, typename U>
void func()
{
	//T ve U aynı türler ise 
}

HOCA BURADA TYPE TRAITS İ CPPREFERENCE TAN GÖSTERDİ.
BURASI ÇOK ÖNEMLİ.

is_enum
is_array
is_function
is_rvalue_reference 
.... birsürü var.


int main()
{
	is_pointer<int>::value; //false
	is_pointer<int*>::value; //true
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

Bunuda bir template e bağlayabiliriz.

template <typename T>
void func()
{
	std::is_pointer<T>::value ; veya
	std::is_pointer_v<T>; // variable template kullanarak oldu bu.
}

int main()
{
	is_array_v<int[]>;// bu true
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

BAZI TEMPLATELERDE BELİRLİ BİR OPERASYONUN DESTEKLENİP DESTEKLENMEDİĞİNİ GÖSTERİYOR.

is_copy_assignable -> copy assign funct ı var mı demek.

struct Neco{ };

int main()
{
	is_copy_assignable_v<Neco> ; //Derleyici Neco için bu func ı yazıyor. True
}								 // class template gönderince hata aldım.

--------------------------------------------------------------------------------------------------------------------------------------------------------

struct Neco{
private:
	A& operator=(const &A);
};

int main()
{
	is_copy_assignable_v<Neco> ; //Artık False
}

=========================================================================================================================================================
=========================================================================================================================================================
=========================================================================================================================================================

BU KISIM ÇOK ÇOK ÖNEMLİ !!!!!!!!!!

TYPE TRAITS TE 
TRANSFORMATİON TEMPLATE VAR.TÜRLERİ MODİFİYE EDEN CONST EKLEYEN ÇIKARAN ...
BELİRLİ İŞLEMLERİN DESTEKLENİP DESTEKLENMEDİĞİNİ TEST EDEN METAFUCNTIONLAR VAR
BİRDE TÜRLERİN TEMEL ÖZELLİKLERİNİ DESTEKLEYİP DESTEKLEMEDİĞİNİ GÖSTEREN METAFUNCLAR VAR.

BELLİ TİP NESNELER BELLİ TİP ARGÜMANLARLA CONSTRUCT EDİLEBİLİR Mİ DE KONTROL EDİLEBİLİR.


Kendimiz bir metafunc yazacağiz.çok zekice bir tasarim var.
Bütün metafuncların türlerle ilgili bilgi veren aslında kalıtım yoluyla kullandığı integral_constant isimli bir template var.
Cppreference tan alındı

template<class T, T v>				// T = int, v = 5
struct integral_constant {
	static constexpr T value = v;	// value = 5 oldu
	
	using value_type = T;			// int
	
	using type = integral_constant; // type = integral_constant<int,5>. sadece struct adını yazınca aslında açılımı yazılmış gibi davranıyordu.
	
	constexpr operator value_type() const noexcept { return value; } // casting operator func. value type a dönüştürüyor. 
																	 // integral_constant<int,5>{} bunu değer bekleyen yerde kullanırsak 5 e dönüşecek.
																	 // constexpr olduğunu için sabit ifadesi.Gerekli yerde 5 e dönüşecek.
	
	constexpr value_type operator()() const noexcept { return value; } // func call operator func. return 5 o da. integral_constant<int,5>{}() bu da 5 i döndürür.
};

int main()
{
	integral_constant<int,5>;
}

=========================================================================================================================================================

BIR TYPEDEF BILDIRIMI YAPILMIŞ LIBRARY İÇİNDE

using true_type = integral_constant<bool,true>; 
using false_type = integral_constant<bool,false>; 

int main()
{
	true_type::value;	// true
	false_type::value;	// false demek.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
struct is_void : std::false_type{

};

burada is_void u hangi tür argümanı ile açarsam value değeri false olacak.

--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
struct isVoid : std::false_type{ };

template<>
struct isVoid<void> : std::true_type { };

template <typename T>
constexpr bool isVoid_v = isVoid<T>::value;


int main()
{
	isVoid<int>::value; // false olacak.
	isVoid<void>::value; // true olacak.

	isVoid_v<int>;  yukarısı ile aynı aslında
	isVoid_v<void>;
}

METAFUNCTION ALTINDA BİZ ZATEN BENZER ŞEYLERİ YAPTIK.

--------------------------------------------------------------------------------------------------------------------------------------------------------

IS_SAME IKI TEMPLATE TÜR PARAMETRESININ AYNI OLUP OLMADIĞINA BAKIYOR.

#include <type_traits>
#include <iostream>
#include <cstdint>

//is_same tür ilişkisi trait'inin gerçekleştirimi

template<class T, class U>
struct IsSame : std::false_type {};

template<class T>
struct IsSame<T, T> : std::true_type {};

template<typename T, typename U>
inline constexpr bool IsSame_v = IsSame<T, U>::value;

int main()
{
	std::cout << std::boolalpha;
	std::cout << IsSame_v<int, int> << "\n"; //true
	std::cout << IsSame_v<int, const int> << "\n"; //false
	std::cout << IsSame_v<int, unsigned> << "\n"; //false	
	std::cout << IsSame_v<int, std::int32_t> << "\n"; //true or false
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

isVoid i biraz daha değiştiriyoruz. 

#include <type_traits>
#include <iostream>

template <typename T>
struct IsVoid : std::is_same<void, std::remove_cv_t<T>> {}; // constluk ve volatilelik silindi. dikkat _t var. Olmasaydı ::type ekleyecektik.

template<typename T>
constexpr bool IsVoid_v = IsVoid<T>::value;

int main()
{
	std::cout << std::boolalpha;
	std::cout << IsVoid_v<int> << "\n"; //false
	std::cout << IsVoid_v<void> << "\n"; //true
	std::cout << IsVoid_v<const void> << "\n"; //true
}

============================================================================================================================================================

TAG DISPATCH
------------
Tamsayı türleri için başka bir kod, 
tamsayı olmayan türler için başka bir kod oluşturmak istiyoruz.


template<typename T>
void func_impl(T x, std::true_type)
{
	std::cout << "tamsayi türleri icin olan kod\n";
}

template<typename T>
void func_impl(T x, std::false_type)
{
	std::cout << "tamsayi olmayan turler icin olan kod\n";
}

template<typename T>
void func(T x)
{
	func_impl(x, std::is_integral<T>::type()); // 2. arguman burada geçici nesne yapıldı aynı zamanda sabit ifadesi.compile timeda elde ediliyor.
}

int main()
{
	func(12);
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

is_pointer idiyom

#include <type_traits>

template<typename T>
struct is_pointer_helper : std::false_type {   };

template<typename T>
struct is_pointer_helper<T*> : std::true_type {   };

template<typename T>
struct is_pointer : is_pointer_helper< typename std::remove_cv<T>::type > {    }; //constluk ve volatile lık silindi. ::type olmasaydı remove_cv_t olacaktı

NOT: Eğer bir template içinde kulandığım bir tür template tür parametresine bağlıysa typename yazmak zorunlu. 
	 Yani burada T nin ne olduğuna bağlı olarak değer değişebilir.

	 Bu örneği hoca burada bıraktı.

--------------------------------------------------------------------------------------------------------------------------------------------------------

Başka türlüde yazılabilir.
Herbir değer için ayrı bir specialization

#include <type_traits>

template<typename T>
struct ispointer : std::false_type {   };

template<typename T>
struct ispointer<T *> : std::true_type{   };

template<typename T>
struct ispointer<const T *> : std::true_type{   };

template<typename T>
struct ispointer<volatile T *> : std::true_type{   };

template<typename T>
struct ispointer<const volatile T *> : std::true_type {   };

template <typename T>	// variable template
constexpr bool ispointer_v = ispointer<T>::value;	// dikkat variable template te typename kullanılmadı hiç.

int main()
{
	ispointer<int>::value; //false
	ispointer<int *>::value; //true
	ispointer<const int *>::value; //true

	ispointer_v<int> ; //false
	ispointer_v<int *> ; //true
	....
}

--------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------

CONSTEXPR IF DAHA SONRA İŞLENECEK ŞİMDİ GİRİŞ YAPTIK. BURADA COMPILE TIMEDA KONTROL YAPIYOR.

template <typename T>
void func(T x)
{
	if constexpr (std::is_integral_v<T>) {	// if constexpr nin içindeki ifade de sabit olmalı.
		std::cout << "tamsayi turleri\n";
	}
	else if constexpr (std::is_floating_point_v<T>)
	{
		std::cout << "reel turleri\n";
	}
	else
	{
		std::cout << "tamsayi ve gercek sayi olmayan turler\n";
		//x.foo(); //derleyince burası hata vermeyor.kontrol yapmıyor çünkü.Çalıştırıncada kod buraya girince hata veriyor.
	}
}

int main()
{
	func(12);
	func(1.2);
	func(nullptr);
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
auto get_value(T x)
{
	if constexpr (std::is_pointer_v<T>)
	{
		return *x;
	}
	else
		return x;
}

int main()
{
	int x = 10;
	int y = 45;
	int* p = &y;

	std::cout << get_value(x) << "\n";
	std::cout << get_value(p) << "\n";
}


MOLA

================================================================================================================================
================================================================================================================================
================================================================================================================================

STATIC ASSERTION
----------------

Derleme zamanı sorgulamalarında static assertionlarda da faydalanabiliyoruz.Doğrulama anlamında kullanılıyor. 
Eğer doğrulama gerçekleşirse kod legal olacak, ama gerçekleşmezse sentaks hatası. Böyle assertionlara static assertion deniyor.

static_assert bir keyword. 2017 std ye kadar 2 tane argümanı olması gerekiyordu
static_assert(sizeof(int) == 2, "Sizeof(int) değeri 2 olmali");

2017 standartlarında bir hata yazmama opsiyonuda var.Sadece hata olduğunu yazıyor.
Template tür parametresinin belirli bir koşulu sağlamaması durumunda sentaks hatası vermesini sağlayabiliyoruz.

template <typename T>
voidfunc(T)
{
	//...
	static_assert(std::is_integral<T>::value, "template argument must be of an integral type\n") //yada std::is_integral_v<T>; variable template kullanıldığında böyle.
}

int main()
{
	func(12); //hatayok
	func('A'); //hata yok
	func(1.2); // burada hata var.integral değil çünkü.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void func(T&&)	//forwarding ref parametre
{
	if constexpr(std::is_lvalue_reference_v<T>)
	{
		std::cout << "lvalue\n";	
	}
	else
	{
		std::cout << "rvalue\n";	
	}
}

int main()
{
	func(12); // rvalue
	
	int x = 23;
	
	func(x); // lvalue
}

--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
T&& forward(typename std::remove_reference<T>::type& param) // std::remove_reference_t<T>::type& param şeklinde de yazabiliriz.Baştaki typename de gitti.
{
	return static_cast<T&&>(param);
}

Remove reference referanslığı ortadan kaldırıyor.argüman T& ise artık remove olduğunda T oldu. func parametresinde yine & var.yani referans türü
func parametresi sol taraf referans parametresi oldu. Static cast te de T türü referans olduğundan & && = & olur yani sol taraf referansına cast eder.


========================================================================================================================================================
========================================================================================================================================================
========================================================================================================================================================

VARIADIC TEMPLATES
------------------
Variadic funclarla karıştırmamak gerekiyor.Bir sınıf şablonu, func şablonu veya alias şablonu variadic olabilir.
Bu özel bir sentaksla tanımlanan template parametresine sahip olması demek.

... elipsis token

SENTAKS
template <typename T, typename ...Args> // template parameter pack. Bu N tane türü içinde barındıran bir paket. 
Burada 0......N tane tür var.

Template parametre tek olabilir yada başka template parametre paketleriyle beraber olabilir.

template <typename T, typename ...Args> // template tür parametre pakedi
void func(T x, Args... args) // function parametre pakedi.
{
	
}

int main()
{
	func(1,2,4,5); 
	//void func(int p1,int p2, int p3, int p4) derleyici buna açıyor.
	//func parametre pakedinde 4 tane parametre, template tür pakedinde ise 4 tane tür olacak
	
	
	func(1,3.5,4L); 
	// void func(int p1,double p2, long p3) derleyici bunu yazacak.

	func(); // burada da derleyici parametre değişkeni olmayan bir func yazacak.
}

Bunlar C deki variadic funclara göre alternatif oluşturuyor ama tür güvenliği olarak çok daha sağlam.
C deki variadic funcların dezavantajları
1. tür açısından güvenli değil.
2. Kaç argüman gönderdiğimizi bir şekilde bildirmek zorundayız

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Args> // 
void func(Args&... args) // Dikkat & . Functionun herbir parametresi Lvalue reference olacak.
{
}

template <typename ...Args> // 
void func(Args&&... args) // Dikkat && . Functionun herbir parametresi Rvalue reference olacak.
{
}

template <typename ...Args> // 
void func(Args... args) // Dikkat. Functionun herbir parametresi bir türden olacaktı, reference olmayacak.
{
}

Args bir keyword değil. konvensiyonel isim. Types ta yazılabilirdi.
Kurs boyunca, Args template parametre pakedi ismi olarak, args ise function parametre pakedi olarak kullanılacak.

-------------------------------------------------------------------------------------------------------------------------------------------------

SIZEOF...

sizeof...(Args) veya sizeof...(args),  bu bir compile sabiti olarak template paramete pakedinde veya 
func parameter packte kaç öğe olduğunu size_t cinsinden söylüyor. Bu compile time sabiti yani constant expression.


template <typename ...Args>
void func(Args ...args)
{
	constexpr auto n = sizeof...(Args);
	constexpr auto m = sizeof...(args);
}

int main()
{
	func(1,2,3,4); // bunun derlenebilmesi constexpr den dolayı compile time sabiti olduğunu söylüyor func içindekilerin
}

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Args>
void func(Args ...args)
{
	std::cout << sizeof...(Args) << "\n" << sizeof...(args) << "\n";
}

int main()
{
	func(1, 2, 3, 4, 45, 5, 6, 7); // 8
	func(1, 2, 3, 4, 45, 5); // 6
	func(1, 2, 3, 4); // 4
}

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Args>
void func(Args ...args)
{
	if constexpr(sizeof...(args) == 1)
	{
		std::cout << "1 arguman\n";
	}
}

int main()
{
	func(5); //1 arguman
}

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Args>
void func(Args ...args)
{
	if constexpr(sizeof...(args) == 1)
	{
		std::cout << "1 arguman\n";
	}
}

int main()
{
	func<int,int,int>(5,5); // SENTAKS HATASI. 3 tane func parametre değişkeni olduğunu söylüyoruz ama 2 adet giriyoruz.
	func<int,int,int>(5,5,5); // GEÇERLİ.
}

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Args> //
void func(Args&... args) // Dikkat & . Functionun herbir parametresi Lvalue reference olacak.
{
}


int main()
{
	int x{};
	double y{};
	long z{};
	
	func(x,y,z); 
	//void func(int&,double&,long &) yazacak derleyici
	
	// Yukarıda func parametre pakedi const Args& ...args olsaydı
	//void func(const int&,const double&,const long &)  yazacaktı derleyici.

}

-------------------------------------------------------------------------------------------------------------------------------------------------

FUNC PARAMETRE PAKEDININ FUNC KODU IÇINDE ÖZEL BAZI FORMLARA UYGUN KULLANILMASINA PACK EXPANSION DENIYOR.

template <typename T>
void func(Args ...args)
{
	args... // Derleyici bunu virgüllerle ayrılan listeye döndürüyor.Bunu ya func çağrısında argüman olarak kullanmam
			// yada küme parantezi içinde bir nesne olarak kullanmam gerekiyor.

	{args...} --> {p1,p2,p3}
	foo(args...) --> foo(p1,p2,p3)

	Args... --> int,double,long
	Neco<Args...> x; --> Neco<int,double,long> x;

	Yani Args... tür bilgilerini tutuyor. (template tür parametre)
	args...		parametreleri tutuyor (function parametre pakedi)

	int a[] = {args...}; burada da aynı func parametre değişkenler olacak

	std::initializer_list<int> x = {args...}; yine benzer

	DİKKAT!!!!!!
	foo(args)... --> foo(p1), foo(p2), foo(p3)
	foo(args...) --> foo(p1,p2,p3)

	foo(&args)... --> foo(&p1), foo(&p2), foo(&p3) şeklinde açılır


	Args<args>(...) --> tür olarak int argüman olarak 1. parametre ... pefect fowardingte çok kullanılıyor.İlgili örnek aşağıda.

}

-------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, typename ...Args>
void foo(T x, Args&&...args)
{
	f(std::forward<Args>(args)...); //aşağıdakilere açar.

	f(std::forward<int>p1);
	f(std::forward<double>p2);
	f(std::forward<long>p3);

}

-------------------------------------------------------------------------------------------------------------------------------------------------

class Myclass {
public:
	Myclass(int&, int, double&&);
};

template<typename ...Args>
void foo(Args&& ...args)
{
	Myclass x{ std::forward<Args>(args)... };
}


int main()
{
	int ival{ 10 };
	foo(ival, 20, 3.4); // foo aldığı argümanların constluğunu value kategorisini değiştirmeden Myclass sınıfının Ctoruna argüman olarak geçecek.
						// containerlardaki emplace functionlar böyle yazılmış.
}

-------------------------------------------------------------------------------------------------------------------------------------------------

NOT: 
f(args...)			f(p1,p2,p3)			demek
f(args)...			f(p1),f(p2),f(p3)	demek

f1(f2(args))...     f1(f2(p1)), f1(f2(p2)), f1(f2(p3))

static_cast<int>(args)...    static_cast<int>p1,static_cast<int>p2,static_cast<int>p3

------------------------------------------------------------

template <typename ...Types>
void foo(Types&& ...params)
{
	
}

template <typename ...Types>
void func(Types&& ...params)
{
	foo(std::forward<Types>(params)...); // aldığı tüm argümanları perfect forward ediyor.
}

------------------------------------------------------------

En fazla fabrikla funclarında kullanılıyor

Make unique memory header file da.

#include <memory>
using nemaespace std;

int main()
{
	make_unique<int>(12); // unique_ptr nin int açılımı türünden nesne
	make_unique<Data>(12); //unique_ptr nin data açılımı türünden nesne verecek.
}


--------------------------------------------------------------------------------


class Myclass{
public:
	Myclass(int,int,double){
		std::cout << "Myclass::Myclass(int,int,double)\n";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
		std::cout << "d = " << d << "\n";
	}
};

int main()
{
	Myclass m{12,3,7.8};
	
}

ÇIKTI
-----
Myclass::Myclass(int,int,double)
a = 12
b = 3
d = 7.8

--------------------------------------------------------------------------------

class Myclass {
public:
	Myclass(int a, int b, double d) {
		std::cout << "Myclass::Myclass(int,int,double)\n";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
		std::cout << "d = " << d << "\n";
	}
};

int main()
{
	Myclass m{ 12,3,7.8 };

	std::unique_ptr<Myclass>uptr(new Myclass{1,3,4.5});

	auto uptr2 = std::make_unique<Myclass>(12, 4, 5.6);

}

ÇIKTI
-----
Myclass::Myclass(int,int,double)
a = 12
b = 3
d = 7.8
Myclass::Myclass(int,int,double)
a = 1
b = 3
d = 4.5
Myclass::Myclass(int,int,double) //make unique kısmı
a = 12
b = 4
d = 5.6


-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------

MAKE UNIQUE IÇIN
Ortada new operatörü yok, aslında make unique new operatörü ile myclass türünden nesne oluşturup ctoruna gönderdiğimiz argümanları geçecek.
Nasıl oluyorda bizim gönderdiğimiz argüamanları dinamik ömürlü nesne oluşturmada kullanıyor. 
1. Cevap perfect forwarding
2. Kaç argüman gönderirsek onları gönderecek. Yani make unique variadic parametreye sahip olması gerekiyor.

Make unique görülecek sonra
Make unique nasıl yazılmış olabilir.

class Myclass {
public:
	Myclass(int a, int b, double d) {
		std::cout << "Myclass::Myclass(int,int,double)\n";
		std::cout << "a = " << a << "\n";
		std::cout << "b = " << b << "\n";
		std::cout << "d = " << d << "\n";
	}
};

template <typename T, typename ...Args>
std::unique_ptr<T> MakeUnique(Args&& ...args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); // std::forward<int>(p1), std::forward<double>(p2) ... gibi gider.
}

int main()
{
	auto uptr = MakeUnique<Myclass>(1, 2, 3.4);
}

ÇIKTI
-----
Myclass::Myclass(int,int,double)
a = 1
b = 2
d = 3.4


MOLA

===================================================================================================================================================


VARIADIC FUNC ŞABLONLARINDA 3 TANE TEMEL TEKNİK VAR.

1. Compile time da recursive bir yapı oluşturmak. Eksitlme diyor hoca
2. Küme parantezi içinde bir liste
3. if constexpr 

---------------------------------------------------------------------------------------------------------------

1. Recursive yapı
-----------------

template<typename T> // 2. maddeden bahsedilen recursive çağrıyı durdurmak için kullanılan template.Sonradan eklendi.
void print(const T& t)
{
	std::cout << t << "\n";
}

template <typename T,typename ...Args>
void print(const T&t, const Args& ...args)
{
	// print  çağırırsak burada runtime da olsaydı bu recursive bir func olacaktı ama compile time da olduğu için her seferinde farklı bir imza olduğundan
	// yeni bir şablon yazacak.

	std::cout << t << "\n";
	print(args...);
}

int main()
{
	int x = 12;
	double dval = 4.5;
	string name{"haydar"};

	//print(x,dval,name,76,"alican"); // ne yazarsak hepsini yazdıracak bir func istiyoruz.
	
	//BURASI ÇOK ÖNEMLİ İYİ OKU!!!
	
	print(x,dval,name);
	
	//1 - yazdığı print in birinci parametresi int türden olacak ve func parametre pakedine 2 öğe kaldığı için, 2 öğe bulunacak burada da.
	//	  yani print func ına 2 argümanla çağrı yapılacak.
	//2 - Bu sefer yeni yazdığı printin 1. parametresi double türden, parametre pakedine de 1 adet parametre kaldı.Bu duruöda çağrılan print 1 argümanla çağrılacak.
	//    Bu recursive mekanizmayı sonlandırmaya da ihtiyacımız var. Ekliyoruz.
	//3 - En son bir elemanlar çağrı yapınca. 2 aday var. biri şablondan yeni bir func yazacak. 
	//    Diğeri ise tek parametreli. Tek parametreli daha iyi bir match. 1. kullanılacak.

	//bitset<16> yıda ekledi ve func çağrıldı. ben onu yazmadım.aynı şey.
}

ÇIKTI
-----
12
4.5
haydar

--------------------------------------------------------------------------------

FUNCTION IMZALARINI YAZDIRIYORUZ. HER SEFERİNDE FARKLI OLACAĞINI GÖRECEĞİZ

__FUNCSIG__ visual studioda bu var. gcc de farklı

template<typename T>
void print(const T& t)
{
	std::cout << __FUNCSIG__ << "\n";
	std::cout << t << "\n";
}

template <typename T,typename ...Args>
void print(const T&t, const Args& ...args)
{
	std::cout << __FUNCSIG__ << "\n";
	std::cout << t << "\n";
	print(args...);
}

int main()
{
	int x = 12;
	double dval = 4.5;
	long l = 123213;
	
	print(x,dval,l);

}

ÇIKTI - ÇOK AÇIKLAYICI
----------------------
void __cdecl print<int,double,long>(const int &,const double &,const long &)
12
void __cdecl print<double,long>(const double &,const long &)
4.5
void __cdecl print<long>(const long &)
123213

HER SEFERINDE YENI BIR FUNC YAZILIYOR VE EN SON BASE CASE DURUMU.

-----------------------------------------------------------------------------------------------------------------

https://github.com/necatiergin/cpp-kursu-kodlar/blob/main/templates/variadic_templates/recursive_3.cpp

Burada da yukarıdaki gibi birşey yazılmış.Hoca açıkladı burayı. 3:05
Teknik aynı.

-----------------------------------------------------------------------------------------------------------------

2. KÜME PARANTEZI IÇINDE BIR LISTE

template <typename ...Types>
void print(const Types& ...params)
{
	int a[] = {1,2,3,4}; // 4 elemanlı bir dizi bu.

	int a[] = {(12,4),(2,5),(,8,21)}; // Buda 3 elemanlı bir dizi. (a,b) nin ürettiği değer b.yani , ün değeri sağ operandının değeridir.
	
	int a[] = {(expr1,4),(expr2,5),(expr3,21)}; // expr1 çalışır ve 4 üretilir, expr2 çalışır ama 5 değeri üretilir... C konuları. , bir Sequence point oluşturuyordu.

}


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename ...Types>
void print(const Types& ...params)
{

	//(std::cout << params, 0)...
	// yukarısı aslında (std::cout << p1,0), (std::cout << p2,0) dizi içine yazarsak.

	//int a[] = { (std::cout << p1,0), (std::cout << p2,0)... };
	// int türen diziye 0 değerleri verilecek ama , ama sol operandlarda çalıştırılacağı için herbir initializerda elemanlar ekrana yazdırılmış olacak.

	int a[] = { (std::cout << params,0)... };

}

int main()
{
	print(12,4.5,"Ali");
}

ÇIKTI
-----
12
4.5
Ali

--------------------------------------------------------

INIT LIST ILE DE YAPILABILIR.

template <typename ...Types>
void print(const Types& ...params)
{
	(void)(std::initializer_list)<int>{(std::cout << params << "\n",0)...}; // uyarı verilmesin diye void a cast ettik.
}

int main()
{
	print(12, 4.5, "Ali");
}


-------------------------------------------------------------------------------------------------------------------------------------------

3. IF CONSTEXPR
---------------

Hocanın github reposunda daha önce yazılmış buradan alıyoruz aşağıdaki kodu.

#include <ostream>

template <typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args& ...rest) // ostream yerine doğrudan coutta kullanılabilirdi.
{
	os << t;

	if constexpr (sizeof...(rest) > 0) // if true ise parametre pakedinde en az bir argüman var demek.
		os << ", ";
	else
		os << "\n";

	if constexpr(sizeof...(rest) != 0) // parametre pakedindeki öğe sayısı 0 değilse print i aşağıdaki gibi çağırıyor.
		print(os, rest...);

	return os;
}

#include <iostream>

int main()
{
	print(std::cout, 45, "ali", 3.87, 'A');
}

Burada t ile ilk eleman os e gönderildi. geriye kalanlar için tekrar func(os,rest...) .......
her seferinde bir eleman eksiliyor.


Bu konu baya geniş ama bizimde bir zamanımız var. Uygulama programcısı için bu kadarı yeterli.
İlerisi ileri C++ ta :D:D

=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================
=========================================================================================================================================================================


STL - STANDART TEMPLATE LIBRARY
-------------------------------

Bu konuyu bilmemek diye birşey söz konusu değil.Her C++ Programmer bilecek bunu.
STL bir acronim.Açılımı başlıkta zaten. Burada kastedilen aslında dilin standart kütüphanesinin template olan bileşenleri.

Func template
Class template
Variable template
Alias template

Günümüzde STL dendiğinde C++ ı standart kütüphanesinin tamamını kastediyor ama STD library nin template olmayan bileşenleride var.
C den gelen funclar veya trigonometri functionları.

BU OBJECT ORIENTED BİR LIBRARY DEĞİL.
Özellikle runtime polymorphism burada hiç yer almıyora yakın denebilir. exception daki what var.

Burada kodlar template, Derleyici kodları yazıp sonra derleyecek.
Veri yapısı implemente eden sınıfları düşünelim, dinamik dizide int double ... tutulacak türe bağlı derleyici compile timeda sınıf kodunu yazıyor.
Yada algoritma denen func şablonlarını düşünürsek sort isimli func kodunu compile timeda bizim için yazıyor.

Template in en büyük dezavantajı hata mesajlarının çok açık olmaması. Çok basit bir hatada 200-300 satır hata alabiliriz.
Deneyimsiz programcılar hata karşısında zorluk çekmeleri normal. Çünkü hatayı açık açık yazmıyor. Bunun için yardımcı programlarda var.

Generic programlamanın en tipik örneği STL.
Bu kütüphanede neler var?

En önemlileri = CONTAINERS, ITERATORS, ALGORITHMS
Diğerleri = Container Adapters, Iterator Adapters, Function Adapters, Function Objects

Containers = Veri yapılarını implemente eden sınıf şablonları.Örneğin dinamik dizi, doubly linked list...

Iterators = Pointerların genelleştirilmiş, soyutlanmış hali.Bunlar öyne nesnelerki containerlardaki tutulan öğelerin konum bilgilerini tutuyorlar.
Pointerda bir iterator olarak kullanılıyor.Bir pointer adres tutuyor, iterator ise pointer olabilir sınıf nesnesi olabilir. Varlık sebebi bir veri yapısındaki
öğelerin konumunu tutmak.Containerda tutulan öğelere iterator denen nesneler yoluyla erişebiliriz. Bunlar pointer-like sınıflar.
Bir pointerı * operatörünün operandı yapınca o adresteki nesneye erişiyorsa, iterator bir sınıf nesnesi ise, o sınıfın * func ı, bizi o konumdaki nesneye eriştirecek.

Pointer-like pointer benzeri arayüze sahip sınıflar. *ptr, ++ptr, ptr-> , ptr[3] ...
Yani aslında kendisi bir pointer olmayan ama pointer interface i ile kullanılan sınıflar, pointer like sınıflar.
Her pointer like nesneye smart pointer denmiyor.Pointer interface ine sahip sınıflar 2 farklı amaç için kullanılabilir.

1 - Dinamik ömürlü nesnelerin ömürlerini kontrol etmek.unique_ptr, shared_ptr bunlar smart pointerlar
2 - Containerlarda/kaplarda tutulan öğelerin konumlarını tutan nesneler.
	bunlarda *ptr şeklinde kullanılabilir ama varlık nedeni konum tutmak. İkiside pointerlike ama varlık sebepleri farklı.


*/
