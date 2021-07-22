/*
Operator Overloadingten devam
Çok hızlı bir tekrar yapıldı.

Birkaç önemli soru
Neden global operator func var ?
Hem global hem static member biraz karmaşık hale getiriyor işi.

İkisinin birden olmasının bir iki senaryosu var.

x sınıf türden
x + 10   bu ifade bir tanesi sınıf türden olduğu için işimizi görür
x.operator(10)

10 + x bu durumda sol operand sınıf türden değil.
o yüzden üye fonksiyonu çağırmak mümkün değil.
func çağrısına dönüştürülemez. 

1 - Global operator funclarda ise operator+(10,x) olabilir

2 - kullanmak istediğimiz fonksiyonlar başka sınıflara ait olabilir.

A ve B sınıfları
a + b bunu yapacak fonksiyon istiyoruz diyelim.Ama bu sınıflar bize ait değil yada 
ikiside bize ait olmayabilir.

Dolayısıyala diğer sınıfı üye operator function olarak yazmak mümkün olmayabilir.
Bugün görülecek.Tipik olarak, bir user defined type ın standart çıkış akımına
user defined type türünden nesnelerin formatlı olarak yazılması.Güzel Örnek bu.

Mesela
cout << ival;  mesela burada operator left shift functionunu kullandık

cout << mydate;   ama aynı arayüzde kendi sınıfımız olan nesneleride bu şekilde kullanmak isteyelim
bu durumda üye operator function olması için cout değişkeninin ilişkin olduğu ostream sınıfına
üye operator function yazmak gerekir.

std namespace içine belirli istisnalar dışında müdahale TANIMSIZ DAVRANIŞ.UNDEFINED BEHAVIOR

Biz ne yapıyoruz. İki parametreli bir global operator func yazıyoruz.Fonk un 1. parametresi
cout un ait olduğu tür olan ostream sınıfı türünden, 2. parametresi bizim sınıf türünden olabilir.


------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
EN ÇOK SORULANLAR?
1 - Geri dönüş değeri türü neye göre seçilmeli
2 - Operator functionlarıyla const doğruluğu arasındaki ilişki nedir
3 - Member mı olsun global mi olsun
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------


1 - Dilin kuralları bunu kendisi belirlemiyor.Sınıf veya problem domaini
ile ilgili bu. Amaç operatörlerin doğal türler için verdiği çağrışımdan sınıf türleri içinde
faydalanmak ve client programcıya kolay yazılabilir / okunabilir kodlar yazmasında yardımcı olmak. 
 
kolay kullanımları seç,doğal yapıyı taklit et.Kolay ve doğal olmuyorsa bırak bunu kullanmayı
Onuda bilirim bunuda bilirim diyip her aracı faydasız olarak kullanmak saçma.

a > b --> bool türdendir
s1 > s2 --> bool
operator>(s1,s2) --> bool
karşılaştırmaların boolean olması logic zorunluluk. İnt olsada sentaks hatası olmaz.

2 - İki tamsayıyı toplayınca tamsayı elde edersek, iki matrisi
toplayınca da matris elde etmeliyiz.

i1 + i2 --> tamsayı
m1 + m2 --> matris

Date x,y;
x - y --> bir gün sayısı elde etmek isteriz. int yani



Myclass &operator
Myclass operator
HANGISI OLSUN ?
Operatorlerle oluşturulan ifadelerin value categorisi belli.
Operatörün doğal kullanımı lvalue exp ise buradaki ifade de lvalue exp olmalı.

a = b  bu ifadenin bir lvalue exp olması için çağrılan fonk un referans / & döndürmeli.

Mesela
atama operatörleri
++x
--x
..  Bunlar lvalue exp olduğundan return değerleri referans türü olmalı.

Ama
+x
-x 	Bunlar R/Pr value exp oluşturuyorlar.Return değeri referans olmayacak

Referans olmayınca maaliyet yok mu ?
1 - taşıma semantiği  devreye girer
2 - copy elision   devreye girer
Bunlar ile maaliyetten kaçınılır.Kaçamazsakta yapacak birşey yok :D:D

MESELA 
Matrix & operator+(const Matrix &, const Matrix &)

return değerini maliyetten kaçmak için referans yaptık.Bu durumda,
return değeri otomatik ömürlüye referans olursa UB
Static ömürlü tehlikeli.Bu operator birden çok kez kullanılınca hepsi aynı nesneyi döndürür.
dinamik olursa kim delete edecek?   

Bunlara bakınca referans return değeri türünün olmaması gerekiyor.


2. CONST SEMANTİĞİNE BAKALIM
Eğer global operator func söz konusu ise ve binary / unary operatorün operandı olacak
ifadeler bu fonksiyona argüman olarak gönderilecek.Bu durumda bunun parametresini referans
yapacaksak, operatörün de yan etkisi yoksa kesinlikle const referans yapmalıyız.
Çünkü değişmeyecekler.

A operator+(const A&, const A &); //değişmeyecekse const olacak


Parametreleri Referans yapmak zorunlu değil. Bazı durumlarda 1 veya 2 sinide doğrudan tür
yapmayıda tercih ediyoruz.
A operator+(A, A&);  

Ama referans yapıyorsak ve operatörlerin yan etkisi yoksa o zaman const referans olmalı.

ÖR:
A operator<(A&, A&); Burası karşılaştırmada tamamen yanlış.Set fonksiyonu
niteliğine girer

A operator<(const A&, const A &); Bu şekilde olmalı.Değiştirme yok.Karşılaştırma var çünkü.


=================================================================================================================================
=================================================================================================================================
=================================================================================================================================
=================================================================================================================================
=================================================================================================================================


ÜYE/MEMBER OPERATOR FUNCTION
---------------------

class A{
public:
	bool operator<(const A &)const;
};

Sağdaki const sol taraftaki operandın değişmeyeceğini gösterir.
parantezdeki const ise nitelediği parametre const olmalı anlamında 
sınıf nesnesi olduğundan x.operator< gibi oluyor.


Buradaki const doğruluğu iyi saptanmalı.Mesela aşağıdaki

class A{
public:
	A& operator+=(const A&); //Neden const değil function
};

Soru : return değeri türü ne olmalı ? Referans çünkü lvalue exp +=
Soru : parametre ne olmalı ? değişmeyecek bu sebeple const olmalı.
Soru : function const member mı olacak ? hayır.Çünkü *this (x veya y veua sum) değişecek.
		*this, const olmamalı.


-------------------------------------------------------------------------------------

Bazı Operatör functionların const overload edilmesi gerekiyor.
Çünkü const ve const olmayan nesneler için 2 ayrı interface(2 ayrı func yani) olmalı.
En tipiklerinden biri operator[] functionu.

ÖR:
class Vector
{
public:
	int& operator[](size_t); //lvalue exp oduğu için int&
	const int& operator[](size_t)const;
};

vec[5]; const değil bu.bunun içinde çağrılan func const olmamalı
cvec[5]; Bu const. Bunun içinde const olan bir nesne çağrılmalı.


=================================================================================================================================
=================================================================================================================================
=================================================================================================================================
=================================================================================================================================
=================================================================================================================================


MEMBER MI GLOBAL Mİ ???
------------------------
EN ZOR SORU
Farklı tercihler var ama genellikle birtakım convensionlar var.

Genel Convensionlar
-------------------
Simertic binary operatorlerin global operator func olarak tercih ediliyor
a > b ile b > a aynı anlamdaysa yani mantıklıysa buna simetric operator deniyor.
Scott Meyers simetric diyor.


Sınıf nesnesini değiştiren/yan etkisi olan operator functionların 
member operator function olması tercih ediliyor. 

++ yı global operator func yapma
Özel durum : Enum türleri class type değil yani member func yok.Enum türleri için ++ overload
edilecekce mecbur global func olarak overload edeceğiz.


Zaten bazı operatorler globaller için yasak () [] = type cast ...


Global operator functionlar binary olursa şöyle bir problem var.
Globaller sınıfın private kısmına erişemezler.

ÖR: bu global func
Matrix opertator+(const Matrix &x, const Matrix &y)
{
	sınıfın private kısmına erişemeyiz.
	friend bildirimi yapılırsa erişir.1. tercih friend bildirimi
	get/set functionları yazılabilir sınıf içinde.
	friend yazılırsa friendler minimize edilmeli.
}

Gri alan var. İllaha belrli bir şey yapılacak diye birşey yok.

Hoca convensional yapıları gösterecek.
Belirli kurallar neden seçilmiş bunu anlamak için bjarne nin kitabı var.
the design of evolution of C++. Modern C++ değil bu buarada.

------------------------------------------------------------------------------------------------------


Operator Overloadingi, bir örnek üzerinden gösterelim
Bir sınıf oluşturacak hoca.Operator overloadingden faydalanacak.
standart intte olmayan birşeyler yazılacak.Böyle sınıflar aynı zamanda wrapper sınıflardır.
int i eleman olarak alacak ama üzerine yeni birşeyler katacak. 0 a bölme durumları taşma durumları ...
my int anlamında Mint classı implemente edeceğiz.

//mint.h
class Mint{

public:
	explicit Mint(int x = 0); // bu nesneye direkt bir sayı atanamayacak.explicit engelledi

	// Formatlı giriş çıkış işlemleri.Burası yorabilir.
	// Bu class yazılmadan öne formatlı giriş çıkış işlemlerine girdik.
private:
};

ADL ÇOK ÇOK ÖNEMLİ. SONRADAN DEĞİNDİ !!!!!!!!!!!!!!

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

FORMATLI GİRİŞ ÇIKIŞ İŞLEMLERİ
------------------------------
Bir çok durumda user defined türlerin formatlı bir şekilde yazılması ve giriş akımlarından gelen
bytelarla user defined türlerin nesnelerin set edilmesi için >> ve << fonksiyonlarının
overload ediyoruz.Böylece diğer türlerle bizim türlerimiz arasında giriş çıkış işlemlerinde
bir biçimsel farklılık olmuyor.Yani bir int i nasıl yazdırıyorsak, bir Mint i de öyle 
yazdırıyoruz.

Bunları oluşturmanın diğer faydası kalıtımdan faydalanarak, herhangibir çıkış akımına aynı
arayüzde yazdırabilmek.Dosyaya belleğe std outputa, aynı şeyler giriş akımı içinde geçerli
bellekten gelenle, std inputtan gelenle, dosyadan gelen bytelarla set etmek gibi...

Ör:
#include "Mint.h"

int main()
{
	Mint mx{10},my{20},mz; // bunu yazdırmak isteyelim.
	std::cout << mx << " " << my << " " <<  mz<< "\n"; 
	
}

bunu mümkün kılmak istiyoruz.operator overoadingden faydalanmak gerekiyor.
burada bir binary << operatörü var. bunun function çağrısına dönüşmesi için <<
overload edilmeli.bunu cout un ait olduğu sınıfa bir üye fonksiyon olarak yazmak
mümkün değil.bu durumda tek seçenek global operator function.global operator func
eğer sınıfın private bölümüne erişecekse friend olarak bildirilmeli.


ÜNLEMLER DİKKAT ÇEKSİN DİYE VAR :D:D

FRIENDIN DIĞER AVANTAJI !!!!!!!!!!!!!!!!!!!!!!!!!
SINIFIN TANIMI İÇİNDE, GLOBAL FRIEND BİR FUNCTION İNLİNE OLARAK TANIMLANABİLİR.AŞAĞIDA DAHA NET YAZDIM!!!!!!!!!!!!!!!!!
YANİ VAR OLAN GLOBAL BİR FUNCTİONA FRİENDLİK VERİP, ÜSTÜNE BUNU INLINE OLARAK SINIF İÇİNDE TANIMINI YAPABİLİYORUZ. .!!!!!!!!!!!!!!!!!
BURASI ÇOK EGZANTRİK. VAROLAN GLOBAL FOKSİYONU, SINIF İÇİNDE, FRİENDLİK VERİP YİNE TANIMLIYORUZ !!!!!!!!!!!!!!
BİLDİRİM DEĞİL TANIM !!!!!!!!!!!!!!
BUNU FRIENDLERDE GÖRMEDİK.ŞİMDİ YAZIYORUZ. !!!!!!!!!!!!!!!!!!!!!
BİZ İNLINE OLARAK YAZMADIK AMA CPP DOSYASINA YAZDIK TANIMINI. KEYFİ OLARAK

cout un ait olduğu sınıfın adı ostream.
Bizim birinci parametresi ostream türünden ikinci parametresi Mint sınıfı türden global
bir operator function bildirip tanımlamamız gerekecek.

friend std::ostream& operator<<(std::ostream & , const Mint &); //sınıf içinde yazıldı.
1 - Bunun friend olması Mint sınıfının private bölümüne erişmesi demek.
2 - İstersem bu fonksiyonun tanımını inline olarak sınıfın tanımı içinde yapılabilirim.
	(Global olmasına karşın hemde)

//Header file mint.h
---------------------
class Mint {
public:
	explicit Mint(int x = 0); 
	friend std::ostream& operator<<(std::ostream& , const Mint&);
private:
};

Bunun içinde derleyici ostream sınıfının bildirimini görmeli. Bu bildirim olmadan
yazdığımız func ın geçerli olma şansı yok. 2 seçenek var.

1 - ostream'i mint.h'de include etmek
2 - iosfwd isimli başlık dosyasında giriş çkış sınıflarının Incomplete declerationları var.
	Dolayısı ile ostream yerine kendi header file da sadece bildirim yer alacağı için
	hafif başlık dosyası olan iosfwd başlık dosyasını include etmeliyiz. ostream baya büyük.

//mint.cpp - Bu file ı biraz daha aşağıda da yazdım. Tekrar için diye yukarıda da olsun.
----------------------------------------------------------------------------------------

Sınıfa özel bu friend fonksiyonu mint.cpp de tanımlayacağız.
Mint.cpp içinden ostream den nesne kullanılacak. Incomplete type işimizi görmez.

std::ostream& operator<<(std::ostream&os, const Mint&m)
{
	return os << "(" << m.mval << ")"; // burada çağrılanlar ostream sınıfının member funcları ya da global functionlar.
	//buradan çağrılan en son functionda os i referans yoluyla döndürdüğü için bunu return edebiliriz.main de kabaca ostream ne döndürüyor
	// yazmıştık. ostream& döndürüyordu.

	//return os; // normalde bu döndürülecek.İdiyomatik olarak yukarıdaki yazıldı
}
// burada return değeri ostream türden referans. Çünkü kendinden sonra çağrılacak olan functiona da bu parametre argüman olarak gönderiliyor.
// Neden 1. parametre const & değil ? os için sadece const üye functionları çağırabilirdik ama os için çağrılan funclar const member func değil.
// HEr yazdırmada bu nesne değişiyormuş - ileride görülecek.

std::istream& operator>>(std::istream& is, Mint& m)
{
	return is >> m.mval;
}


//main.cpp
----------
int main()
{
	Mint mx{ 10 }, my{ 20 }, mz;
	std::cout << mx << " " << my << " " << mz << "\n"; // artık hata da vermiyor.

} //operator<<(operator<<(cout,mx), " ") ... gibi bir koda dönüştürüyor.	

BURADA ÇAĞRILAN FONKSIYONLAR GLOBAL OPERATOR FUNCTIONLAR.

HATIRLATMA:
OSTREAM SINIFININ OPERATÖR FUNCTIONLARINDAN BIR KISMI, ÜYE OPERATOR FUNCTION, BIR KISMI
GLOBAL OPERATOR FUNCTION.


int main()
{
	// using namespace std; gerekebilir.

	int ival{12};
	cout << ival;   // Burada çağrılan sınıfın üye operator functionu.Sınıfın int parametreli
					// bir üye operator left shift fonksiyonu var.
	cout.operator<<(ival); //yukarıdaki ile bu aynı.


	cout << "Umut Kotankiran\n"; // burada yazarken
	// yazıyı yazdıran operator functionu global operatör function.Parametresi const char * 
	operator<<(cout,"Umut Kotankiran"); // bunla yukarıdaki aynı. std::cout yazmayı unutma veya using namespace std;



	cout.operator("Umut Kotankiran\n"); //burada yazmadı.Pointer adresi yazdı.
	// üye operator functiona strig literali gönderilince burada çağrılan function parametresi void * olan member operator function.

}

Yani ostream içerisi kabaca aşağıdaki gibi.

class ostream{
public:
	ostream& operator<<(int);
	ostream& operator<<(double);
	ostream& operator<<(void *); // Buda adres yazdırıyor.Yukarıdaki adresi yazdırdı.Adresteki yazıyı yazdırmadı.
};

--------------------------------------------

Diğer örnek
int main()
{
	cout.operator<<('A'); // 65 yazdı:karakter kodu
	operator<<(cout,'A'); // Bu ise A yı yazdırdı.
}

SONUC: BAZI FUNCTİONLAR SINIFIN ÜYE FUNCTİONLARI BAZILARI İSE GLOBAL FUNCTİONLAR !!!!!!!!!!!!!!!!!!!


-----------------------------------------------------------

Şimdi Mint nesnesini yazdırıyoruz.

#include <iostream>
#include "mint.h"

int main()
{
	Mint a{ 10 }, b{ 20 }, c;
	std::cout << a << " " << b << " " << c << "\n";
}

---------------------------------------------------------------------------

Sınıfa özel bu friend fonksiyonu mint.cpp de tanımlayacağız.
Mint.cpp içinden ostream den nesne kullanılacak. Incomplete type işimizi görmez.

cpp file da using bildirimleri yapmak kişisel tercih.Hoca kullanmama taraftarı.
Header file da ise asla kullanmayacağız !!!

DOSYALARIN  SON DURUMLARI

mint.h
#pragma once
#include <iosfwd>

class Mint {
public:
	explicit Mint(int x = 0) : mval{ x } { } // bu nesneye direkt bir sayı atanamayacak.explicit engelledi
	friend std::ostream& operator<<(std::ostream&, const Mint&);
private:
	int mval;
};


mint.cpp
#include "mint.h"
#include <ostream>

std::ostream& operator<<(std::ostream&os, const Mint&m)
{
	return os << "(" << m.mval << ")"; // burada çağrılanlar ostream sınıfının member funcları ya da global functionlar.
	//buradan çağrılan en son functionda os i referans yoluyla döndürdüğü için bunu return edebiliriz.main de kabaca ostream ne döndürüyor
	// yazmıştık. ostream& döndürüyordu.

	//return os; // normalde bu döndürülecek.İdiyomatik olarak yukarıdaki yazıldı
}
// burada return değeri ostream türden referans. Çünkü kendinden sonra çağrılacak olan functiona da bu parametre argüman olarak gönderiliyor.
// Neden 1. parametre const & değil ? os için sadece const üye functionları çağırabilirdik ama os için çağrılan funclar const member func değil.
// HEr yazdırmada bu nesne değişiyormuş - ileride görülecek


main.cpp
#include <iostream>
#include "mint.h"

int main()
{
	Mint a{ 23 }, b{ 98 }, c{ -5 };
	std::cout << a << " " << b << " " << c << "\n"; //BURADA DEVREYE ADL GİRDİ.Aşağıda yazacağım.
}

ÇIKTI
-----
(23) (98) (-5)

--------------------------------------------------------------------------------------------------------------

Bjarne neden formatlı çıkış işlemi için << i düşünmüş?
ilk olarak & tokenını bu amaçla kullanmak istemiş.Sonrada ok << akım nesnesine doğru anlamında gibi kullanmış.
Giriş işleminde ise >> girişten gelen bytelar nesneyi set ediyor.

Operator left shifti formatlı çıkış işlemi yaptırmak için overload eden operator frunctionlarına inserter deme geleneği var.

Operator right shift ise giriş akımından aldıklarını kullanarak değişkeni set ettiği için böyle functionlara extractor deniyor

Biz inserter yazdık. Extractor da yazılacak.

Bunlar sadece standart çıkış akımına yazdırmıyor. Dosyayada yazdırabiliyorlar.Ben hocanın verdiği örneği yazmıyorum  1.08

------------------------------------------------------------------------------------------------------------------------------------

Giriş içinde >> yazacağız.
.h ye aşağıdaki eklendi.
friend std::istream& operator>>(std::istream&, Mint&); // dikkat 2. nesne const değil. Ekliyoruz kütüphaneye

Görmediğimiz bazı araçlar var bunları kullanacağız.Dikkat

.cpp ye aşağıdaki eklendi.
std::istream& operator>>(std::istream& is, Mint& m)
{
	return is >> m.mval;
}


-----------------------------------------------------------------------------------------------------------------------



SORU !!!!!!!!!!!!!!!!!!!

.h
class Mint {
public:
	explicit Mint(int x = 0) : mval{ x } { } // bu nesneye direkt bir sayı atanamayacak.explicit engelledi
	friend std::ostream& operator<<(std::ostream&, const Mint&);
	friend std::istream& operator>>(std::istream&, Mint&);
private:
	int mval;
};

main.cpp
std::cout << a << " " << b << " " << c << "\n";

SINIF İÇİNDE BİLDİRİLEN MEMBER FUNCTION BURADAN DİREKT OLARAK NASIL KULLANILDI?
ADL İLE

--------------------------------------------------------------------------------------------------

ADL ÖRNEĞİ.

class Myclass {
public:
	friend void func(Myclass);
	friend void foo(int);
};

int main()
{
	Myclass m;

	func(m); //GEÇERLİ
	foo(5); //SENTAKS hATASI
}

ADL
GEÇERLI OLMASININ SEBEBI, ÇAĞRIDA ARGÜMAN BIR SINIF TÜRÜNDENSE, BURADA DERLEYICI BU SINIFIN TANIMINADA BAKIP BURADA BIR FRIEND BILDIRIMI
VAR MI YOK MU DIYE BAKMAK ZORUNDA.GÖRDÜĞÜ İÇİNE HATA YOK.

----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------


Kendi Sınıf türünden nesnelerimiz
a - STL in containerlarında tutulacak
	vector, set ,map 
	Bazı containerlarda user defined typeları tutmak için sınıfın  operator< mutlaka olmalı.
	çünkü containerların kodu burada tutulan öğelerin küçüktür öğeleri, küçüktür operatörünün operandları yapıyor.
	Dolayısıyla eğer sınıfımızın operator< yoksa böyşe bir containerda Mint nesnesini tuttuğumuzda sentaks hatası oluşur.
	
	ör:
	int main()
	{
		set<Mint> myset;
		myset.insert(Mint(12)); burası sentaks hatası.hatada yazıyor zaten mesaj. < operatörününün olmamasından ötürü hata verdiği yazıyor.
								bazı durumlardada operator == olması gerekiyor.
	}

	C++ 20 de gelen bazı özellikler var.
	Spaceship veya three way comparision konuları var.Bunlar sonra anlatılacak.

	Karşılaştırma işlemleri için operator funclara ihtiyaç var. Bunlar binary simetric olduğundan 
	global operator function olarak	yazmakta fayda var.

	Şimdi sınıfın < ve == operator functionları friend global funclar olarak bildiriyoruz.

	Bunları inline olarak(neden inline ? keyfi :D:D ) ekle
	friend bool operator<(const Mint &x,const Mint &y);
	friend bool operator==(const Mint &x,const Mint &y);

-----------------------------------------------------------------------------------------

SON HALİ

Mint.h

#pragma once

#include <iosfwd>

class Mint {
public:
	explicit Mint(int x = 0) : mval{ x } { } // bu nesneye direkt bir sayı atanamayacak.explicit engelledi
	friend std::ostream& operator<<(std::ostream&, const Mint&);
	friend std::istream& operator>>(std::istream&, Mint&);
	friend bool operator<(const Mint& x, const Mint& y)
	{
		return x.mval < y.mval; // sınıfa friend olduğundan private bölüme erişim bir hata değil.ADL var yine muhtemelen
	}
	friend bool operator==(const Mint& x, const Mint& y)
	{
		return x.mval == y.mval;
	}
	//diğer karşılaştırmalar inline keyword ile sınıf dışında yazıldı dikkat et. + lar - ler değil, diğer logical operatorler

private:
	int mval;
};



//BUNLARI INLINE İLE TANIMLADI FAZLA AÇIKLAMA YOK!!!!!!!!!!!!
inline bool operator>=(const Mint& x, const Mint& y)
{
	return !(x < y); // >= demek küçük değil demek
	// return !operator<(x, y);  yukarıdaki ile aynı anlamda
}

inline bool operator>(const Mint& x, const Mint& y)
{
	return y < x;
}

inline bool operator<=(const Mint& x, const Mint& y)
{
	return !(y < x);
}

inline bool operator!=(const Mint& x, const Mint& y)
{
	return !(x == y);
	//return !operator(x,y); böylede olur.
}


Not: std::boolalpha manipulator. 0 veya 1 olan boolean değeri true false olarak çeviriyor.

int main()
{
	Mint a{ 12 }, b{ 5 };

	std::cout << (a > b) << "\n";
	std::cout << std::boolalpha << (a > b) << "\n"; // operator önceliğine dikkat. <<, < ten daha önce çalışır. o yüzden paranteze alındı.
}


MOLA
================================================================================================================================================
================================================================================================================================================
================================================================================================================================================
================================================================================================================================================


ARİTMETİK OPERATÖRLERİN OVERLOAD İŞLEMLERİ

Toplama overload edilecekse mutlaka += overload edilmeli.
Biz + yı overload edince += overload edilmiyor. + yı ediyorsak += te edilmeli.


Scott Meyers Convensionu 
------------------------
Tercih edilen, += i overload etmek yani bunu sınıfın üye functionu yapmak, + yı ise simetric olduğu için global yapmak fakat
onun += operatörünü çağırması.

//header içinden inline tanımlanır. MEMBER OPERATOR FUNC OLARAK YAZILDI YANI
Mint& operator+=(const Mint &r)
{
	mval += r.mval;
	return *this;// kendisine atama yapılan nesneyi ref semantiği ile döndürdü
}

//operator+
inline Mint operator+(const Mint& left, const Mint& right) // GLOBAL OPERATOR FUNCTION OLARAK YAZILDI
{
	
	//Mint temp{left};
	//temp += right;
	//return temp;
	
	//oneliner olarak ta yazılır.geçici nesne yaratılıp bunu mint right değeri ile toplayıp return edilebilir.
	// Neden geçici nesne kullandık.? çünkü left bir const nesne değiştirilemez. += dediğimde side effect var.SENTAKS HATASI OLUR
	// Mint{left} ise geçici nesne. += operandı olabilir.
	return Mint{left} += right;
	
}

//copy elision yapılabilecek durumda da yazılabilir
inline Mint operator+(Mint left, const Mint& right) // en son bunu koyduk
{
	return left += right;
	//1. parametresine geçici nesne gönderilirse doğrudan copy elision oluşacak.
}

Burada örnek yaptı.
mx my mz
cout mx + my + mz  yazdırdı


Bunun - ve -= tide yazdık class içine


-------------------------------------------------------------------------------------------

Hem member operator funclar hemde global operator funclar için - / * işlemlerinide yazdık.
Hepsi header file içerisinde

===========================================================================================================
===========================================================================================================
===========================================================================================================


SIGN / İŞARET OPERATÖRLERININ OVERLOAD EDILMESI
-----------------------------------------------

int main()
{
	using namespace std;

	int ival{12};

	+ival;
	-ival;  Unary oldukları için unary operator olarak overload edilmeleri gerekiyor.
			Yan etkileri olmadığı için sınıfın const üye fonksiyonu olmaları gerekiyor.

}


Mint operator+()const   // return değeri sağ taraf değeri olduğundan referans yapmadık
{
	return *this;
}

Mint operator-()const   // return değeri sağ taraf değeri olduğundan referans yapmadık
{
	return Mint{ -mval }; // Mint türünden geçici nesne ama bunu mval değil -mval ile oluşturup return ettik.
}


===============================================================================================================================
===============================================================================================================================
===============================================================================================================================


++ ve -- OPERATÖRLERİNİN OVERLOAD EDİLMESİ

Postfix			Prefix
x++				++x
x--				--x

class A{
public:
	... operator++(); //prefix
	... operator++(int); //postfix

};


Mint& operator++() //prefix
{
	++mval;
	return *this;
}

Mint operator++(int) //postfix. dummy int. biz değil derleyici kullanacak
{
	Mint temp{*this}; // bir kopyasını al

	++*this; // kendisini bir artır. Bu aslında bir üstteki Mint& operator++() //prefix fonksiyonunu çağıracak. 
	//operator++(); buda aynı şey bir üstteki ile.

	return temp; // ama kopyayı return et. klasik x++;
}




-- li halini yazalım

Mint& operator--() //prefix
{
	--mval;
	return *this;
}

Mint operator--(int) //postfix. dummy int. biz değil derleyici kullanacak
{
	Mint temp{*this}; // bir kopyasını al

	--*this; // kendisini bir azalt. Bu aslında bir üstteki Mint& operator--() //prefix fonksiyonunu çağıracak.
	//operator--(); buda aynı şey bir üstteki ile.

	return temp; // ama kopyayı return et. klasik x--;
}

--------------------------------------

TEST

#include <iostream>
#include "mint.h"

int main()
{
	Mint a{ 12 }, b{ 25 };
	std::cout << ++a << " " << b++ << "\n";

}

ÇIKTI
-----
(13) (25)

==================================================================================================================================

++ ve -- leri GLOBAL OPERATOR FUNCTION olarak yazmak isteseydim.Tercih edilmiyor ama...
Zaten bu durumda sınıf içinden friendlik veya get eden bir func yazmak lazım mval için.


inline Mint& operator++(Mint &x)
{
	++x.mval;
	return x;	
}

inline mint operator++(Mint &x,int)
{
	Mint temp{x};
	++x;
	//operator++(x); ile bir üsttekinin farkı yok.
	return temp;
}

==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================

2.15

BU KISIMDAN SONRA AŞAĞIDAKİ OPERATÖRLER OVERLOAD EDİLECEK
Aşağıdakilerin Global Operator Function ı ile overload edilemiyor.

operator[]
operator*  dereferencing
operator->  member selection
operator() func call operator
type cast operator

==================================================================================================================================
==================================================================================================================================

operator[] ile başlıyoruz

runtime da ilave maliyet yok operator overloadingte.
Bu fonksiyonlar isimleriylede çağrılır, operator notaasyonuylada çağrılır.Operator
notasyonu daha kolay ve doğal.

-----------------------------------------------
a[5]  *(a+5) konularına girdi.C den kısa özet.
-----------------------------------------------

1 - burada m in ait olduğu sınıf array-like olmalı.YOksa doğallıktan uzaklaşır.
	m[i] 
	m.operator[](i)  Bunlar aynı şey.

2 - Pointer-like bir sınıfta olabilir.
	Kendisi pointer olmayan ama pointer interfacesine sahip, instanceları pointermış gibi kullanılan sınıflar var.
	Bu sınıflar veri yapılarındaki öğelerin konumunu tutmak için kullanlan iterator sınıfları(iterator classes).
	
	Birde Smart Pointer var.
	Kendileri bir sınıf türden nesne olmalarına rağmen sınıf içinde pointer gibi kullanılıyorlar.
	
	Farkları
	-iteratörler veri yapılarındaki öğelerin konumunu tutuyor
	-Smart pointerlar dinamik ömürlü nesnelerin hayatlarını konrol eden pointerlar olarak kullanılıyor
	 std::unique_ptr
	 std::shared_ptr
		
Şimdi de kısaca STL ye girdik :D:D:D:D:D
	
using namespace std;
vector<int> ivec(10);
for(size_t i{} ; i < ivec.size(); i++)
{
	ivec[i] = i;
	ivec.operator[](i) = i; aynı
}

//vector deque string array map --- bu containerlar overload ediyor.

-------------------------------------------

int main()
{
	std::string name{"Berk Tepebag"};

	for(size_t i{}; i < m.size();++i)
	{
		std::cout << name[i] << " ";
	}
}

-------------------------------------------

int main()
{
	const std::string name{ "kaya" };
	std::cout << name << "\n";
	name[0] = 'm';				//Burası değiştirilemiyor çünü const.Bunu nasıl sağladığını bakacağız şimdi.
	std::cout << name << "\n";
}

-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------

SINIFIN [] OPERATOR FUNCTIONU NASIL OVERLOAD EDILIYOR

Köşeli parantez ile oluşturulan ifade lvalue exp yani referans olacak.

class Array{
public:
	T& operator[](size_t);
};


class Array{
public:
	int& operator[](size_t);
};

int main()
{
	Array a;
	a[5] = 10; //SENTAKS HATASI YOK

	const Array A;
	A[5] = 10 //SENTAKS HATASI. Çünkü const nesne için nonconst member func çağrılamaz.
}

EĞER

class Array{
public:
	int& operator[](size_t)const; // bu member func const yapılırsa
};

int main()
{
	const Array A;
				// ÇOOK ÖNEMLİ !!!!!!!!!
	A[5] = 10 //FONKSIYON ÇAĞRILIR AMA CONST BIR DIZININ ELEMANINI DEĞIŞTIRMEK SEMANTIK HATA AMA SENTAKA HATASI OLMAZ
}				// BUNU ENGELLEMEK İÇİN CONST OVERLOAD ETMEMİZ GEREKİYOR.

---------------------------------------

OLMASI GEREKEN

class Array{
public:
	int& operator[](size_t);
	const int& operator[](size_t)const;
};

int main()
{
	Array a;
	a[5] = 4;

	const Array ca;
	ca[5] = 12; //İşte const referans elde ettiğimiz için return de atama yapılamaz
}

==================================================================================================================================
==================================================================================================================================

ŞIMDI BASIT BIR ARRAY SINIFI OLUŞTURACAĞIZ.PRIMITIVE OLARAK.BIRAZ EKSIK OLACAK

#include <iostream>
#include "mint.h"

class Array {
public:
	explicit Array(size_t n) : msize{ n }, mp{ new int[msize] } {  }					// conversion olmasın istemiyoruz
	~Array() { delete[] mp; }  // copy ctoru copy assignmentları falan yazmadık.Normalde yazmak gerekir.UB oluşabilir.
	size_t size()const { return msize; }
	int& operator[](size_t idx)
	{
		return mp[idx];
	}
	const int& operator[](size_t idx)const
	{
		return mp[idx];
	}

	friend std::ostream& operator<<(std::ostream& os, const Array& a)
	{
		os << "(";
		for (size_t i = 0; i < a.size() - 1; ++i)
		{
			os << a[i] << ", ";
		}

		return os << a[a.size() - 1]<< ")"; // Son eleman 9. Return edilmeside gerekiyor.Sanırım o yüzden bu şekilde yazıldı.
	}
private:
	size_t msize;
	int* mp;
};

int main()
{
	using namespace std;
	Array a(10);
	cout << a.size() << "\n";

	for (size_t i = 0; i < a.size(); i++)
		a[i] = i;

	cout << a;
}

==================================================================================================================================
==================================================================================================================================
==================================================================================================================================

İÇERİK/DEREFERENCING/INDIRECTION VE OK/ARROW OPERATÖRÜNÜN OVERLOAD EDİLMESİ
---------------------------------------------------------------------------

*ptr

*adres demek bu adresteki nesne demek.

Burada ptr pointer değişkeni değilde bir sınıf türden nesne gibi düşünelim.
ptr Myclass sınıf türden bir nesne. Bu durumda derleyici bu ifadeyi sınıfın içerik operatörüne yapılan
cağrıya dönüştürüyor(tabi varsa).
yani *m ----> m.operator*()  demek.

*m nin lvalue exp olması için çağrılan fonksiyonun sol taraf referansı olması gerekiyor.

Neden yazıyoruz?
dereferencing in pointer like sınıflar için overload edilmesi.
Bunlarda kendi içinde 2 ye ayrılır.
1. STL de iterator sınıfları
2. Dinamik ömürlü nesnelerin hayatını kontrol etmekiçin kullanılan sınıflar Smart Pointer lar.

SENTAKS
--------
T& operator*()

BASIC ŞEKİLDE IMPLEMENTE EDİLMİŞ SMART POİNTER ŞEKLİNDE YAPACAĞIZ.
STANDART KÜTÜPHANENİN UNIQUE_PTR SİNİ YAPACAĞIZ

OK OPERATOR İÇİN DURUM BİRAZ FARKLI.
------------------------------------
ptr->x 

BİR KURAL VAR. OK OPERATÖRÜ BİNARI OPERATOR OLMASINA RAĞMEN UNARY OPERATOR OLARAK OVERLOAD EDİLİYOR.

class SmartPtr{
public:
	T operator->()
};

SmartPtr p; 
			DERLEYİCİ BURADA NE YAPIYOR.BU KURAL
p->x;		Ok operatörünün sol operandı olmuş sınıf nesnesi için, sınıfın ok operatör functionunu çağırıyor.	
			yani p.operator->() çağırıyor.bunun geri dönüş değerinide ifadedeki ok un sol operandı yapıyor.
			yani p.operator->()->x; Bu durumda p-> x in legal olması için, çağrıaln operator-> un return değeri öyle bir
			adres olmalı ki x o adresteki nesnenin üyesi olmalı.Özel bir istisna dışında sınıfların ok operator functionu
			bir pointer döndürecek.bizde içinde nesneye erişeceğiz.


-----------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------

YAZIYORUZ.ÇOK DİKKATLİ OKU.

#include <iostream>
#include "mint.h"

//Amacımız Smart Pointer Sınıfı
class ResourceUser {
public:
	ResourceUser() // dummy olarak yazıyoruz
	{
		std::cout << "ResourceUser Ctor kaynaklar edindi\n";
	}

	~ResourceUser()
	{
		std::cout << "ResourceUser Destructor kaynaklar geri verildi\n";
	}

	void func() // konumuz bu basit funclar değil
	{
		std::cout << "ResourceUser::func()\n";
	}
	void foo()
	{
		std::cout << "ResourceUser::foo()\n";
	}

};
	// Konumuz buradan sonra başlıyor.
	// öyle bir ptr ihtiyacımız varki dinamik ömürlü nesneyi atarsak
	// Amaç öyle bir sınıf oluşturmakki p yerine Smartptr sınıfı türden olan p nesnesini kullanacak.
	// bütün kodlar legal olacak ama delete etmeyeceğim. Scope u bittiğinde hayatını kontrol ettiği dinamik ömürlü nesne delete edilecek
	// bu strateji unique_ptr nin kullandığı strateji
	// Normalde main içinden aşağıdakiler yazılınca sorun yok.Bunu Smartptr ile otomatik delete eder halde yazacağız.

	void gf(ResourceUser& r)
	{
	}

	int main() 
	{
		ResourceUser* p = new ResourceUser;
		p->func();
		gf(*p);
		delete p;
	}

	//AŞAĞIDAKİNİ İSTİYORUZ. P DEĞİŞKENİNE DİKKAT, *P DEĞİL.
	-------------------------------------------------------
	SmartPtr p = new ResourceUser;   // p bir pointer değil ama dinamik ömürlü nesneyi tutacak
	p->func(); // içindeki elemanlara pointer olmadığı halde -> ile erişilecek.
	p->foo();
	gf(*p);



//BURASI ÇOK ÇOK KRİTİK!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------

ResourceUser sınıfı türünden dinamik ömürlü nesnelerin hayatını kontrol edecek.
SmartPtr p = new ResourceUser; bunun legal olması için sınıfın ResourceUser* türden bir ctorunun olması lazım.
YENİ BİR SINIF YAZILIYOR.SmartPtr sınıfı

class SmartPtr {
public:
	SmartPtr(ResourceUser* p) : mp{ p } { }
	ResourceUser& operator*()
	{
		return *mp;
	}

	ResourceUser* operator->()
	{
		return mp;
	}

private:
	ResourceUser* mp;


};

void gf(ResourceUser& r)
{
}

int main()
{
	SmartPtr p = new ResourceUser;

	p->foo();
	p.operator->()->foo(); // bununla yukarıdaki aynı.

	p->func();


	gf(*p);
	//gf(p.operator*()); //Yukarıdaki ile bu aynı anlamda

	(*p).foo();

}

ÇIKTI
------
ResourceUser Ctor kaynaklar edindi
ResourceUser::foo()
ResourceUser::foo()
ResourceUser::func()
ResourceUser::foo()

BURADAKİ SORUN KAYNAKLAR EDİNİLDİ AMA HİÇBİRİ SİLİNMEDİ.
SİLMEK İÇİN DESTRUCTOR YAZILACAK SMARTPTR İÇİNDEN


----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------

BU ÖRNEKTE İSE YİNE POINTER İLE TUTUP ELLE DELETE EDİLDİ.TEKRAR GİBİ OLDU
-------------------------------------------------------------------------

#include <iostream>
#include "mint.h"

AMACIMIZ SMART POINTER SINIFI

class ResourceUser {
public:
	
	~ResourceUser()
	{
		std::cout << "ResourceUser Destructor kaynaklar geri verildi\n";
	}

	void func() // konumuz bu basit funclar değil
	{
		std::cout << "ResourceUser::func()\n";
	}
	void foo()
	{
		std::cout << "ResourceUser::foo()\n";
	}

	
	void gf(ResourceUser& r)
	{
	}

	int main()
	{
		ResourceUser* p = new ResourceUser;
		p->func();
		gf(*p);
		delete p;	// AMAÇ BUNU ELLE SİLMEMEK. OTOMATİK OLARAK SİLİNMESİNİ SAĞLAMAK ZATEN.
	}

};


BURASI ÇOK ÇOK ÇOK ÇOK KRİTİK, DANANIN KUYRUĞU KOPUYOR BURADA!!!!!!!!!!!!!!!!!!!!!!!!
-------------------------------------------------------------------------------------

DESTRUCTOR EKLENDİ VE MOVE CTOR ... YAZILDI UNIQUE PTR YE BENZEMESİ İÇİN
-------------------------------------------------------------------------

ALTTAKİ TEKRAR EDEN AÇIKLAMALARI TEKRAR YAZDIM BİLEREK SİLMEDİM !!!!!!!!!
ResourceUser sınıfı türünden dinamik ömürlü nesnelerin hayatını kontrol edecek.
SmartPtr p = new ResourceUser; 

class SmartPtr {
public:
	SmartPtr() : mp{ nullptr } { }   //eklendi
	//unique_ptr de, copy ctor ve copy assign delete edilir bu sayede smart_ptr nesneleri kopyalanamaz.
	//birden fazla smartptr nesnesinini aynı dianamik ömürlü nesneyi göstermesi mümkün olmayacaktı
	//Smartptr sınıfı noncopiable oldu. Taşınabilmesi için move memberları yazılacaktı
	// biri mülkiyeti alıp diğeri bırakacaksa move memberlar yazılacaktı

	SmartPtr(const SmartPtr&) = delete; // eklendi.
	SmartPtr& operator=(const SmartPtr&) = delete; // eklendi

	SmartPtr(SmartPtr&& other) : mp{ other.mp }
	{
		other.mp = nullptr;
	}
	//SmartPtr& operator=(SmartPtr&& other); move assignment yazmadı.Unuttu hoca bence

	SmartPtr(ResourceUser* p) : mp{ p } { 
	
	}

	~SmartPtr() //Burası eklendi.
	{
		if(mp)
			delete mp;
	}
	
	ResourceUser& operator*()
	{
		return *mp;
	}

	ResourceUser* operator->()
	{
		return mp;
	}

private:
	ResourceUser* mp;


};

void gf(ResourceUser& r)
{
}

int main()
{
	{
		SmartPtr p = new ResourceUser;

		p->foo();
		p.operator->()->foo(); // bununla yukarıdaki aynı.

		p->func();

		gf(*p);
		//gf(p.operator*()); //Yukarıdaki ile bu aynı anlamda

		(*p).foo();
	}

	std::cout << "Kaynaklar geri verildi\n";
}

ÇIKTI
-----

ResourceUser Ctor kaynaklar edindi
ResourceUser::foo()
ResourceUser::foo()
ResourceUser::func()
ResourceUser::foo()
ResourceUser Destructor kaynaklar geri verildi
Kaynaklar geri verildi

----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
Unique Ptr ile yapılan örnekler

#include <iostream>
#include <string>
#include <memory>

int main()
{
	using namespace std;
	{
	//unique_ptr<string> uptr = new string{ "Orkun Sengor" }; // sentaks hatasının sebebi unique ptr nin bu ctoru explicit
	unique_ptr<string> uptr(new string{ "Orkun Sengor" }); // direct initialization ile yapılır
	cout << *uptr<<"\n";
	cout << uptr.operator*()<<"\n"; // yukarıdaki ile aynı.

	//member funclardan biri çağrılacak
	cout << "uzunluk  = " << uptr->length() << "\n";
	cout << "uzunluk  = " << uptr.operator->()->length() << "\n"; // buda yukarıdaki ile aynı anlamda

	}//buradan sonra string delete edilecek
}

--------------------------------------------------------------------------------------------

int main()
{
	using namespace std;
	{
	//unique_ptr<string> uptr = new string{ "Orkun Sengor" }; // sentaks hatasının sebebi unique pte nin bu ctoru explicit
	unique_ptr<string> uptr(new string{ "Orkun Sengor" }); // direct initialization ile yapılır
	cout << *uptr<<"\n";
	cout << uptr.operator*()<<"\n"; // yukarıdaki ile aynı.

	//member funclardan biri çağrılacak
	cout << "uzunluk  = " << uptr->length() << "\n";
	cout << "uzunluk  = " << uptr.operator->()->length() << "\n"; // buda yukarıdaki ile aynı anlamda

	// unique_ptr<string>upx(uptr);  copy ctor delete edildiği için SENTAKS HATASI
	// unique_ptr<string>upx;
	// upx = uptr; copy asisgnemnt demete edildiğinden yine SENTAKS HATASI

	//Ama çalabiliriz :D:D:D:D
	unique_ptr<string>upx(std::move(uptr)); // artık uptr boşaltıldı, upx ise dolu hale geldi.

	//get release reset ne yapıyor bir sonraki ders bakılacak.

	}//buradan sonra string delete edilecek

}



*/

#include <iostream>
#include <string>
#include <memory>

int main()
{
	using namespace std;
	{
	//unique_ptr<string> uptr = new string{ "Orkun Sengor" }; // sentaks hatasının sebebi unique pte nin bu ctoru explicit 
	unique_ptr<string> uptr(new string{ "Orkun Sengor" }); // direct initialization ile yapılır
	cout << *uptr<<"\n";
	cout << uptr.operator*()<<"\n"; // yukarıdaki ile aynı.

	//member funclardan biri çağrılacak
	cout << "uzunluk  = " << uptr->length() << "\n";
	cout << "uzunluk  = " << uptr.operator->()->length() << "\n"; // buda yukarıdaki ile aynı anlamda

	// unique_ptr<string>upx(uptr);  copy ctor delete edildiği için SENTAKS HATASI
	// unique_ptr<string>upx;	
	// upx = uptr; copy asisgnemnt demete edildiğinden yine SENTAKS HATASI

	//Ama çalabiliriz :D:D:D:D
	unique_ptr<string>upx(std::move(uptr)); // artık uptr boşaltıldı, upx ise dolu hale geldi.

	//get release reset ne yapıyor bir sonraki ders bakılacak.

	}//buradan sonra string delete edilecek

}
