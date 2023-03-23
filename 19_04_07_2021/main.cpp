/*
STRINGLERDEN DEVAM EDİYORUZ.
----------------------------

En son find a bakmıştık.
find karakter, başka string data.... olabilir. bir tablo var.Onu buradaki resource files içerisinede koydum

rfind sondan başa arama yapıyordı

find_first_of verdiğimiz karakter grubu içindeki karakterlerden ilk bulduğunu döndürüyor. strpbrk

find_last_of verdiğimiz karakterlerden geçtiği son yeri buluyor.

find_first_not_of  verdiğimiz karakterlerden biri olmayan ilk karakter

find_last_not_of  verdiğimiz karakterlerden biri olmayan son karakter

Genel yapı, ilk argüman aranan varlık, son argüman aramanın hangi indexten başlayarak yapılacağı(genelde default oluyor bu)

-----------------------------------------------------------------------------------------------------------------------------

bir string içinde bir yazının geçtiği heryeri bulmak.Ödev
ankara ankara güzel ankara burada a veya ankara yazanların hepsini bulmamız gerekiyor mesela. Ödevlerde var
arama 0 dan yapılacak ve bulunandan bir sonraki index ile devam edilecek.

-----------------------------------------------------------------------------


string s1{"Necati"};
string s2{"Ergin"};

auto s = "Dosya :" + s1 + s2 + '_' + ".jpg";

ama eğer 2 adet cstring yazsaydık, 2 farklı pointer toplamı olduğundan hata olacak.
Mesela
auto s = "Dosya :" + "Adi " + s1 + s2 + '_' + ".jpg"; BURASI SENTAKS HATASI.


-----------------------------------------------------------------------------------------

Substring Elde Eden Functionlar
-------------------------------
Yazen bir substringi yeni bir yazı olarak kullanmak istiyoruz.
Bunun için substr yi kullanabiliriz.

string str{"bugun gunlerden pazar"};
str.substr(); // 2 parametresi var. ikiside default argüman alıyor. 1. parametre Başlangıç index değeri.size_type türünden karakter sayısı
				// 2. default parametre npos
str.substr(6, 3);

void print(const string &s)
{
	std::cout << "[" <<s.lenght() << "]  [" << s << "]\n"; 
}

int main()
{
	string str{"bugun gunlerden pazar"};
	auto s = str.substr(6, 3);
	print(s); // gun yazar

	auto s = str.substr(3);
	print(s); // 3 ten sonraki herşeyi yazar. npos ikinci default arguman çünkü

	auto s = str.substr(); //ise 0 default argüman. direk bir kopyasını çıkartır baştan sona
}

---------------------------------------------------------------------------------

C++17 ile gelen string_view sınıfı var

#include <array>
#include <vector>

Yazıları aşağıdaki gibi tutabiliriz.
char str[] = "necati ergin";
string s{"bjarne stroustrup"};
array<char, 20> ar;
//
vector<char> cvec;
//
const char *p = "Ali veli";

Bunların hepsinin ortak özelliği, hepsinin karakterleri ardışık olarak tutuluyor.
Yazı üzerinde salt okumaya yönelik işlemlerde, yazı kopyası yerine, yazının üzerinde 2 adet pointer ile işlemler
yapabilirim.

string view ne yapıyor?
Yazının ilgileneceğimiz ilk karakterinin konumunu bir ptr, diğeri ise son karkaterden bir sonraki konumu tutuyor.
Buna yönelik interface verilmiş. String sınıfının okuma amaçlı tüm fonksiyonları string view sınıfında da var.
string view yazıyı değil fonksiyonları tutuyor.

int main()
{
	string_view sv;

	sv. // buradan fonksiyonlara bakılır.
}


==================================================================================================================

REPLACEMENT VE DÖNÜŞÜM FONKSİYONLARI
------------------------------------

Replace demek silme + insert demek. Biz bunu yapmak yerine replace fonksiyonlarını çağırıyoruz.maliyet açısından da avantaj
İndex interface indeki tüm fonksiyonların ortak özelliği, ilk karakter index, ikinci karakter ise kaç karakterlik kısım üzerinde işlem
yapılacak demek.

int main()
{
	string str{"necati ergin"};

	str.replace(0,2,"xxxxx"); // 0. index ten sonra 2 karakter uzunluğunda olan yerlere yani "ne" yerine "xxxxx" yaz demek. 
	print(str); //  [xxxxxcati ergin] yazar.
}

Jossutisin kitabını oku. STRING CLASS IN DETAIL diye bir kısım var. burada baya bir özet açıklama var

---------------------------------------

DÖNÜŞÜM FONKSİYONLARI
string tamsayı veya real sayı dönüşümleri yapılacak.
tamsayıyı stringe dönüştürme olayıda var.



String Function									Effect
--------------------------------------------------------------------------------------
stoi(str,idxRet=nullptr, base=10)				Converts str to an int
stol(str,idxRet=nullptr, base=10)				Converts str to a long
stoul(str,idxRet=nullptr, base=10)				Converts str to an unsigned long
stoll(str,idxRet=nullptr, base=10)				Converts str to a long long
stoull(str,idxRet=nullptr, base=10)				Converts str to an unsigned long long
strof(str,idxRet=nullptr)						Converts str to a float
strod(str,idxRet=nullptr)						Converts str to a double
strold(str,idxRet=nullptr)						Converts str to a long double
to_string(val)									Converts val to a string
to_wstring(val)									Converts val to a wstring



Bunlar global functionlar.
1. parametreye string, 2. parametreye pointer geçiliyor. strtod strtold gibi. Dönüşüm yapılamayan kısmın indexini döndürüyor.

Ör:
int main()
{
	string str{"65Ahmet"};
	print(str);
	auto ival = stoi(str); // 65 değerini çevirir.Ahmet kısmı kaldı.default olarak nullptr gönderdiğim için onu almadım
	std::cout << ival << "\n";
}


Ör:
int main()
{
	string str{"65Ahmet"};
	print(str);
	size_t idx;
	auto ival = stoi(str,&idx);
	std::cout << ival << "\n";
	std::cout << idx << "\n"; // okuyamadığı kısmın indexini de aldık.
}

Ör:
int main()
{
	string str{"65Ahmet"};
	print(str);
	size_t idx;
	auto ival = stoi(str,&idx,16); // 16 lık sayı sistemi ve çıktı da değişti.Çünkü A 16 lık sayı sisteminde var.A yıda aldı
	std::cout << ival << "\n";
	std::cout << idx << "\n"; // 
}
ÇIKTI 
1626
3

---------------------------------------------------------------------------------------------------------

Bunun tersini yapan fonksiyonun ismi to_string ve overload edilmiş.

int main()
{
	int ival = 2345;
	to_string(ival);
}


----------------------------------------------------------------------------------------------------------

Linkedindeki soruya baktı.
kendisi ve karesinde 0 hariç tüm basamaklar olacak.Sayı 3 basamaklı.
int main()
{
	for (int i = 100; i < 1000; ++i)
	{
		auto square = i * i;
		auto s = to_string(square) + to_string(i);

		if (s.length() != 9)
			continue;

		sort(begin(s), end(s));
		if (s == "123456789")
		{
			cout << i << "  " << square << "\n";
		}
	}
}


16 LIK SAYI SISTEMINDE YAZARSAK
int main()
{
	for (unsigned long long  i = 1000; i < 1000000; ++i)
	{
		auto square = i * i;
		ostringstream oss;
		oss << uppercase << hex << i << square; // + ile toplamadık ta oss te topladık bunu. sprintf gibi.görülmedi

		auto str = oss.str(); // görmedik henüz bunları

		if (str.length() != 15)
			continue;

		sort(begin(str), end(str));
		if (str == "123456789ABCDEF")
		{
			cout << uppercase << hex << i << "   " << square << "\n";
		}
	}
}



----------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------

EKSİK OLAN NELER VAR?
Exception Handling ten fazla bahsetmedik.
kalıtım var ve bu konudan sonra girilecek hemen.

Belirli fonksiyonların geri dönüş değeri türlerini açık açık göstermedik. bazıları index, bazıları string & ve *this döndürüyorlar,
bazılarının geri dönüş değeri ise iterator interface ile çalışan iterator.

iterator invalidation görülmedi.

mesela bir soru var.
string str{25as342as5f}; istenilen string ise 
22as4422asf. Yani çiftler 2 defa yazılacak tekler silinecek. harflere dokunulmayacak.
ikinci bir string nesnesi yasak.


-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------

BURADA ÖDEVDEN BAHSEDİYOR HOCA.
1:00

User defined literal operator function kullanılmış hoca daha anlatmadı.
int veya floating literaller son ek alabiliyorlar.
34u
34ull
34. gibi...

'A' c de int c++ ta char

Modern c++ ta şöyle bir araç var.
Sınıf türden ifadeler oluşturabiliyoruz. Sabitlerin sonuna bir önek getirerek.

"ahmet"s --> bu bir user defined literal.udl
Burada ismi s olan bir function çağrılıyor.Bu function constexpr bir func.Burada yine operator overloading ile bir func
çağrılmasını sağlıyoruz. Çağrılan functionun return değeri string sınıfı türünden. Dolayısıyla "Ahmet"s ifadesi bruada çağrılan
return değeri string türünden olan bir func olduğundan ifadenin türü string.

#include <chrono>
ileride bu kütüphanede user defined literaller var. 15sn, 15ms, 15ns. Bunlar library tarafından bize verilen funclar
Bunları kendimizde yazabiliriz.

34_mt olabilecek mesela.
34_dm olabilir...

1024_byte 
1024_KB yazıp kendi sabitlerimizi kendimiz oluşturacağız.

"3/5"_f yazınca fraction nesnesini udl tür olarak yazma imkanı verdiğimizi söylüyor.


------------------------------------------------------------------------------------------

Bir soru üzerine anlatıldı

string s{"DogusUral"};
const char *p = str.c_str() + 5;

cout << *p << "\n";
std::cout << "str.capacity() = " << str.capacity()<< "\n";

str.insert(0,1,'A');

std::cout << "str.capacity() = " << str.capacity()<< "\n";
(void)getchar();
cout << *p << "\n";
Burada iterator invalidation var.Reallocationdan dolayı UB bile oluşabilir.insert ediliyor çünkü boyutu artacak.


==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================


KALITIM - INHERITANCE
---------------------

OOP da kalıtım bir sınıfın public interfacesini devralarak kendi public interfacesine katarak yeni bir sınıf oluşturmasına
karşılık gelen terim. Buna is a relationship deniyor. Daha önce compositionu görmüştük. Orada has a relationship vardı.

İs a ilişkisi ise bir nesnenin aynı zamanda başka türden bir nesne olarak kullanılabilmesi ilişkisini gösteriyor.
Örneğin, Her mercedes bir arabadır. Her aslan bir hayvandır. Her pencere bir gui objesidir gibi.

Burada C++ ile diğer diller arasında farklılık var. Diğer dillerde is a relationship ilişkisi var.
C++ ta ise kalıtımın 1 den fazla ilişkisi var.

Public inheritance
Private inheritance
Protected inheritance

Public diğer yani OOP dillerdeki anlamıyla kalıtımın karşılığı.
Private ve protected is a relationship ilişkisini oluşturmuyor.

C++ taki kalıtım aracı OOP dillerdeki kullanım amacından farklı amaçlarda da kullanılıyor.
Private ve Protected OOP deki karşılığından farklı olduğu için onları farklı başlık altında inceleyeceğiz.

-------------------------------------------------------------------------------------------------------------

Kalıtımda kaynak olarak kullanılan sınıflara
Super class / Parent class deniyor.

Kalıtım yoluyla oluşturduğumuz yeni sınıfa 
Sub class / child class deniyor.


Bir de C++ ın kalıtım ile ilgili kendi terimleri var.
Inheritance = derive(isim hali derivation)

Kalıtımda kaynak olarak kullanılan sınıf base class, elde edilen ise  derived class / Türemiş sınıf (public protected private için geçerli)
Modelleme dillerinde sınıfları gösteren diagramlara class diagram deniyor ve sınıflar arası ilişkileri gösteren notasyonlar kullanılıyor
Kalıtım ilişkisi sınıf diagramlarında dikdörtgenlerle temsil ediliyorlar. 


Mercedes -------> Car  

Burada car sınıfı taban sınıf, mercedes türemiş derived class.
UML diagramında okların uçlarının çizgilerin herşeyin ilişkisi farklı.içi boş veya dolu ok fark yaratıyor.

Bir super class tan subclass elde ederken buna single inheritance deniyor.


multi-level inheritance
-----------------------
S500 --------> Mercedes -------> Car

Her s500 bir mercedestir. Her mercedeste bir arabadır.Bu durumda her s500 bir arabadır.
Bu şekilde uygulanan kalıtıma multi-level inheritance deniyor.


Multiple inheritance
--------------------
Birde Multiple inheritance denen, C++ ta doğrudan bir araçla desteklenen, diğer programlama dillerinde farklı araçlarla 
desteklenen bir araç.Bir sınıftan, 2 den fazla sınıfı doğrudan taban sınıfı kullanıp tek bir kalıtım işleminde bir sınıf elde etmek

		----->	Modem
FaxModem	
		----->	Fax

Böylece faxmodemin clientları hem fax hemde modemden gelen arayüzleri kullanıyorlar


Class Hierarchy
---------------
Yukarıdaki şekilde oluşturulan sınıfların biraraya gelerek oluşturdukları grup anlamında.
mesela araba sınıfı var arabadan bmw audi fiat sınıfları kalıtım yoluyla elde edilmiş.
bunlardan da başkaları kalıtım yoluyla elde edilmiş. Bunların oluşturduğu kümeye class hierarchy deniyor.

------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

Kalıtımda Super / Parent class diye bir sınıfın olması gerekiyor.
Bu sınıfın complete type olması zorunlu. Incomplete type kalıtımda geçersiz.

SENTAKS
-------
class Base {

};

class Der : public Base {

};

Burası Der isimli sınıfın public kalıtımı yoluyla Base sınıfından elde edilmesi deniyor.
Kalıtım biçimini gösteren public private protected dan birini yazmazsak, kalıtımın biçimi private
Yani hiçbirşey yazmazsan private.

class Der : Base {    
};

----------------

İstisna
class değilde struct kullırsak ve public private protected tan birini yazmazsak, varsayılan public kalıtım oluyor.
Aşağısı public kalıtım

struct Der : Base {    
};

---------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------

class Base {

};

class Der : public Base {

};

1 - Her Der nesnesi aynı zamanda bir Base türündendir.
Yani ör: Base gereken bire yerde biz Der nesnesi kullanabiliyoruz.Derleyici durumu geçerli kabul eder. Upcasting.

2 - Der sınıfının public interface ine, Base sınıfının public interface indeki fonksiyonlar türler elemanlar dahil edilmiş olacak.

class Base {
public:
	void func();
	void foo();
	int mx;
	class Nested{
		
	};	
};

class Der : public Base {
public:
	void f1();
	void f2();
};

int main()
{
	Der myder;
	myder. // burada func foo mx... hepsi geliyor.

	Normalde aşağıdaki gibi kullanılıyordı
	Base::Nested x; gibi kullanılıyordu ama kalıtım var artık.
	Der::Nested x; diyebiliriz.
}

Burada client ı kalıtım mı var yok mu ilgilendirmiyor.Client kendi işine bakıyor.
Burada türetilmiş nesnesini bir taban sınıf nesnesi gibi kullanabiliyorum. Çünkü tüm public interface i katılıyor.
Kalıtım yoluyla varolan bir sınıfı, onun bütün işlevselliğini alıp genişleterek yeni sınıf veya sınıflar oluşturabiliyorum.

Burada seçerek almak yok. Tamamını alıyoruz. Şu fonksiyon olsun diğer tür olmasın diye birşey yok.
Kalıtım kullanınca türemiş sınıf taban sınıfın public interface ini kullanıyor.

Eğer bir sınıfın interface ini seçerek filtreleyerek, kısıtlamalar koyarak, kendi sınıfımıza uyumlandırarak oluşturmak istersek
kalıtım yerine composition kullanmalıyız.

a ve b classları olsun

a nın içindeki b, a nın elemanı olan b ise buna member object/embedded object
a nın içindeki b, a kalıtım yoluyla b den elde edildiyse, b nesnesine base class object demek yaygın


================================================================================================================================
================================================================================================================================

BAKILACAK KONULAR

NAME LOOKUP
ACCESS CONTROL
VIRTUAL DISPATCH - RUNTIME POLYMORPHISM

-----------------------------------------------------------

İSİM ARAMA
----------

class Base {
public:
	void func();
	void foo();
	int mx;
	class Nested{

	};
};

class Der : public Base {
public:
	void f1();
	void f2();
};

int main()
{
	Der myder;
	Der *p = &myder;

	//myder.x;
	//p->x
	//Der::x
}

//myder.x;
//p->x
//Der::x


KURAL : BURADA SAĞDAKI ISIMLER ÖNCE TÜREMIŞ SINIFIN KAPSAMINDA, BULUNAMAZSA TABAN SINIFIN MEMBERLARI IÇINDE ARANIYOR

ÖR : myder.foo() bu türetilmiş sınıfta bulunamadı ama taban sınıfta bulundu. foo base sınıftata olmasaydı sentaks hatası
	 Aynı durum ok veya çözünürlük içinde geçerli.

class X{

};

class Y : public X{  //x ten y sınıfı kalıtım yoluyla elde edilmiş.

};

class Z : public Y{ // y dende z kalıtım yoluyla elde edilmiş.

};

int main()
{
	Z z;
	z.func() // Bu isim ilk önce z nin scope unda sonra y nin scope unda sonrada x in scope unda aranır.Bulunamazsa orada da sentaks hatası
}

FUNC İSMİ BU ISIM ILK ÖNCE Z NIN SCOPE UNDA SONRA Y NIN SCOPE UNDA SONRADA X IN SCOPE UNDA ARANIR.BULUNAMAZSA ORADA DA SENTAKS HATASI
nokta ok :: hepsi için geçerli.

----------------------------------

SORU: 
class Base{
public: 
	void func(int);
};

class Der : public Base{
public: 
	void func(int,int);
};

int main()
{
	Der myder;
	//myder.func(12); 
}

1 - Function overloading var mı?
	Kesinlikle func overloading değil. Func overloading olması için aynı isimli funcların aynı scopeta bulunması gerekiyor.
	base class ve derive classtaki aynı isimli funclar overload değil.

2 - myder.func(12); legal midir ? 
	Değildir.Func overload resol. da isimleri bulur. burada candidate funclar arasında void func(int) yok.
	türemiş sınıftaki func, tabandaki func ı maskelemiş oldu.SENTAKS HATASI.

Özel durumlar sözkonusu değilse yukarıdaki bildirimler yapılmamalı.

Myder ile base sınıfın func ını çağırmak istersek.

myder.Base::func(5);
. operatörü ile base sınıfa geçebildik.

kendi funcına erişim
myder.func(23,56);

-----------------------------------------------------------------------------------

class Base{
public:
	void func(int);
};

class Der : public Base{
public:
	void foo()
	{
		x   // bu isim this ile nitelenmemişse veya :: ile nitelenmediyse isim arama sırasını aşağıda yazdım
	}
};

int main()
{

}

1. Blok içinde ama bulunamazsa
2. Der sınıfı memberları içinde ama bulunamazsa
3. Base sınıfı memberları içinde ama bulunamazsa
4. Namespace içinde arar.

---------------------------------------------------------------------------------------------

class Base{
public:
	void func(int);
};

class Der : public Base{
public:
	void foo()
	{
		foo(12); //SENTAKS HATASI. Der memberları içine buldu ama buradaki foo argüman almıyor
		
		foo(); //geçerli. Recursive call.
		Base::foo(12); //Bu şekilde baseden gelen foo çağrılabilir.				
};

int main()
{

}

-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------


ACCESS CONTROL
--------------
Bu kontrol sıralaması içinde hep sonuncu kontroldu
name lookup
contex control 
access control


PUBLIC KALITIMDA
Taban sınıfın public interfaceindeki isimler herkese açık. 

class Base{
public:
	void foo(int);
};

class Der : public Base{
public:

};

SORU : foo yu kimler çağırabilir?
Base in client ları çağırabilir. Der nesnesiyle . veya -> ile foo çağrılabilir.
Kimseye yasak yok.

------------------------------------------------------------------------------------------------


SINIFIN PRIVATE BÖLÜMÜ HERKESE KAPALI.
KATILIM YOLUYLA ELDE EDİLEN SINIFADA KAPALI.FRIENDLİK HARİCİNDE TABİKİ.

class Base{
private:
	void foo(int);
};

class Der : public Base{
public:
};

int main()
{
	Der myder;
	myder.foo(12); SENTAKS HATASı
}

Name lookupta hata yok ama access controle takılacak.
derleyici verdiği hatada bunu yazar zaten.

AYNI ŞEKİLDE
class Base{
private:
	void foo(int);
};

class Der : public Base{
public:
	void func()
	{
		foo(12); //SENTAKS HATASI.ACCESS CONTROLDEN ÖTÜRÜ.
	}
};


-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

TÜREMİŞ SINIF TABAN SINIFIN PROTECTED INTERFACE INI KULLANABİLİR

class Base{
protected:
	void foo();
};

class Der : public Base{
public:
	void func()
	{
		foo(); // GEÇERLİ !!!!!!!!!!!!!!!!!
	}
};

int main()
{
	Der myder;
	Base mybase;

	mybase.foo(); //SENTAKS HATASI. CLİENT KODLAR KULLANAMAZ.
	myder.foo(); //SENTAKS HATASI CLİENT KODLARA KAPALI. SINIFIN İÇİNDEN ERİŞİLEBİLİR.
}

--------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------

class Base{
public:
	void func(int);
};

class Der : public Base{
private:
	void func();
};

int main(
{
	Der myder;
	
	myder.func(123); // SENTAKS HATASI.Access control name lookuptan sonra yapılır.func bulundu ama access controle takılır.
	myder.func(); //SENTAKS HATASI. Access control.
	myder.Base::func(123); GEÇERLİ!!!
}

=========================================================================================================================
=========================================================================================================================
=========================================================================================================================

TABAN SINIF İLE TÜREMİŞ SINIF ARASINDAKİ TÜR DÖNÜŞÜMLERİ
--------------------------------------------------------
Türemiş sınıftan taban sınıfa otomatik tür dönüşümü var.Implicit type conversion var.
Taban sınıf türünden bir pointer, türemiş sınıf türünden bir nesnenin adresini tutabilir/alabilir.


class Base{
public:
	void func(int);
};

class Der : public Base{
private:
	void func();
};

int main()
{
	Base *p = new Der; // Der * türünden değişken Base * a atanmış.SENTAKS HATASI YOK.
	
	Der myder;
	Base *baseptr;
	baseptr = &myder; //SENTAKS HATASI YOK.

	//Aynı durum referans semantiğinde de var.
	Der myder;
	Base& baseref = myder; //SENTAKS HATASI YOK.

}


TERMINOLOJI
Modelleme dillerinde kalıtım ilişkisi türemiş sınıftan taban sınıfa doğru çizin okla çizildiği için, türemiş 
sınıftan taban sınıfa doğru yapılan dönüşümlere UPCASTING deniyor.Yukarıdönüşüm gibi.

Eğer bu dönüşüm pointer yada referans semantiğiyle değil de kopyalama semantiği ie yapılırsa
bir sentaks hatası olmamasına rağmen başka nedenlerden (sonra görülecek)yanlış olarak değerlendiriliyor.

Der myder;
Base mybase;

mybase = myder; // SENTAKS HATASI DEĞİL. AMA %99 HATALI. %1 ÖZEL DURUM.YANLIŞ BİR DURUM.
				// Buna karşılık gelen bir terimde var. Object slicing.Nesne dilimlenmesi


taban sınıfı türden nesneye türemiş sınıf nesnesini atayınca, fiilen türemiş içerisindeki tabanı atamış oluyoruz.
Şekille daha iyi anlaşılabilir belki. 2:45

		Türemiş Sınıf				 Taban Sınıf
		|----------|				|-----------|
		|Türemiş   |				|	    |
		|içindeki  |				|	    |
		|taban Sın.|				|	    |
		|----------|				|-----------|
		|----------|
		|          |
		|	   |
		|	   |
		|----------|

Dolayısı ile türemiş sınıftaki bilgi kaybediliyor.Bu sebeple nesne dilimlenmesi deniyor.

class Base{
public:
	void func();
};

class Der : public Base {
	
};

int main()
{
	Der myder;
	myder.func(); //BURADA DA BİR UPCASTİNG VAR.AÇIKLAMA AŞAĞIDA
}

func, Base sınıfının nonstatic member func ı. Bunun this ptr var.Bu functionun gizli parametresi Base * türünden.
Biz myder.func() yapınca, myder in adresini bu fonksiyonun gizli parametresi olan Base * a kopyalamış oluyoruz.
Burada da upcasting var.

Arka planda türemiş sınıf nesnesinin adresini verdiğimizde aslında ona verdiğimiz adres fiziksel olarak
türemiş sınıf içindeki taban nesnesinin adresi.

Dikkat : Türemiş sınıf nesnesinin içindeki taban sınıfı nesnesinin adresi ile, türemiş sınıfın nesnesinini kendi adresi
		fiziksel olarak aynı mıdır? HAYIR.Olmayabilir
		AMA biz taban sınıf pointerına türemiş sınıfın pointerını atadığımızda, türemiş sınıfın içindeki taban sınıfın adresini
		oraya yerleştirmiş oluyoruz.

	    Türemiş Sınıf				 Taban Sınıf
		|----------|				|-----------|
		|Türemiş   |				|	    |
		|içindeki  |				|	    |
		|taban Sın.|				|	    |
		|----------|				|-----------|
		|----------|
		|	   |
		|	   |
		|	   |
		|----------|


-----------------------------------------------------------------------

ÖR:
Türemiş sınıf nesnesi içinde fiziksel olarak taban sınıf nesnesi olduğunu unutma
Bu ne demek

class Base{
	int x,y;
};

class Der : public Der
{
	int a, b;
};

int main()
{
	std::cout << "sizeof(Base) = "<< sizeof(Base) << "\n";  // 8 byte 
	std::cout << "sizeof(Der) = "<< sizeof(Der) << "\n";  // 16 byte 
}

Kalıtım olmasaydı Der sınıfı 16 byte olmayacaktı.

---------------------------------------------------------
Haydarın sorusunu yazmıyorum.
this ile base veya drived class a erişebilir miyiz ? evet
---------------------------------------------------------

MOLA

================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================


SINIFIN SPECIAL MEMBER FUNCLARININ DURUMLARI
--------------------------------------------
Derived class içinde base class nesnesi var dedik.
Bir türemiş sınıf oluşturduğumuzda, onun taban sınıf nesnesininde construct olması gerekiyor.

Türemiş sınıfın default Ctorunu derleyici yazıyorsa(implicitly declared veya user declared defaulted ise) derleyici her zaman 
taban sınıf nesnesi için default ctoru çağıracak bir kod üretiyor.Yani derleyici türemiş sınıf içindeki taban sınıf nesnesi için
default ctora çağrı yapıyor.

class Base{
public:
	Base(){
		std::cout << "Base Default Ctor \n";
	}
	~Base(){
		std::cout << "Base Destructor \n";
	}
};

class Der : public Base{
public:
};

int main()
{
	Der myder; // Base in default ctoru ve Destructoru çağrıldı.
}

Dikkat !!!
1 - Base in default ctoru private ise, bu durumda Der in default ctoru derleyici tarafından delete edildi.
	Der myder; sentaks hatası verir.Delete edilmiş func a ayapılan çağrıdan dolayı.
	
2 - Base in default ctoru da delete edilirse programcı tarafından benzer şey olur.
	Der myder; SENTAKS HATASI
	
3 - Base içinde Base(int); tanımlarsak, base in default ctoru not declared olur.
	Bu durumda Der myder; çağrısı olduğunda, Base in default ctoru olmadığından Der inde
	default ctoru hata vermemesi için delete edilir.Implicitly deleted.
	Der myder;  Yine Sentaks hatası oluşur

------------------------------------------------------------------------------------------------


class Base{
public:
	Base(){
		std::cout << "Base Default Ctor \n";
	}
	~Base(){
		std::cout << "Base Destructor \n";
	}
};

class Der : public Base{
public:
	Der()   // biz ctor init liste base sınıfın default ctoruna çağrı yapmazsak derleyici buraya yine base in default ctorunu ekler.
	{		// çünkü ctor init list ile initialize etmediğim öğeler default init ediliyor.Default init demekte sınıf türden nesnelerin
			// default ctoru çağrılması demek.NOT :Der myder; dendiğinde ilk base class için ctor çağrılır sonra der ctoru devreye girer.

		std::cout << "Der Default Ctor\n";
	}

	~Der() //Burası çalıştığında, içieisindeki tüm kodlar çalışacak, sonra taban sınıf nesnesininin elemanları hayata gelmesiyle ters sırada
	{		// Destructorları hayata veda edecek.

		std::cout << "Destructor Ctor\n";
	}
};

int main()
{
	Der myder; // Base in default ctoru ve Destructoru çağrıldı.
}

ÇIKTI
-----
Base Default Ctor
Der Default Ctor
Der Destructor Ctor
Base Destructor

-------------------------------------------------

Aşağıdaki durumu inceleyelim.

class Base{
public:
	Base(int x){
		std::cout << "Base(int x)\n";
	}
	
};

class Der : public Base{
public:
	//Der()   Böyel bırakırsak default init olacağından default ctor çağrılır. Base de Default ctor yok SENTAKS HATASI Olur
	//{
	//	std::cout << "Der Default Ctor\n";
	//}

	//Bu senaryoda Ctor init list kullanacağız.
	//Der() : Base(12)	C++ 11 e kadar böyleydi.
	//{
	//	std::cout << "Der Default Ctor\n";
	//}

	Der() : Base{12}	//C++ 11 den sonra böyle de yazılabiliyor.Stringlerde gördük {} ile () arasında initializer list  farkı vardı.
	{					//birde {} de narrowing conversion sentaks hatası oluşturuyor

		std::cout << "Der Default Ctor\n";
	}
};

int main()
{
	Der myder;
}


YAYGIN DURUM
Bu tip sınıflarda türemiş sınıfın ctorunun aldığı argümanlardan birinini yada birden fazlasının, aslında türemiş sınıf ctor tarafından
ctor init list sentaksıyla taban sınıfın ctoruna argüman olarak geçilmesi çok yaygın.

Burada Date operator sorusuna baktı hoca.
Buradan örnek verdi.

---------------------------

class MemberX{
public:
	MemberX()
	{
		std::cout <<"MemberX Default Ctor\n";
	}
	~MemberX()
	{
		std::cout <<"MemberX Destructor\n";
	}
};

class MemberY{
public:
	MemberY()
	{
		std::cout <<"MemberY Default Ctor\n";
	}
	~MemberY()
	{
		std::cout <<"MemberY Destructor\n";
	}
};

class Base{
public:
	Base()
	{
		std::cout <<"Base Default Ctor\n";
	}
	~Base()
	{
		std::cout <<"Base Destructor\n";
	}
};

class Der : public Base{
public:
	MemberX mx;
	MemberY my;
};

int main()
{
	Der myder;
}

ÇIKTI
------
Base Default Ctor      // Burayı yorumla.Sıralaması garanti.Hayata gelme sırası ve sonlandırılma sırası belli.
MemberX Default Ctor
MemberY Default Ctor
MemberY Destructor
MemberX Destructor
Base Destructor


------------------------------------------------------------------------------------------------------

Diyelimki Multilevel İnheritance Var.

class A{
public:
	A() = default;
	A(int,int);
};

class B : public A{
public:
	B() = default;
	B(int);
};

class C : public B{
public: 

};

A, C nin taban sınıfıdır.
B, C nin taban sınıfıdır.
B ile A nın farkını nasıl vurgularız.
C nin direk kalıtımla elde edildiği taban sınıfa Direct Base Class/ doğrudan taban sınıf deniyor.Bu durumda B, C nin direct base class ı.
Bu durumda A, B nin direct base class ı.

C, A dan kalıtım yoluyla elde edilen B den elde edilmiş. Bu duruma indirect base class deniyor.

Bunların bahsedilmesinin sebebi.Ctor init liste doğrudan taban sınıf konulabilir.indirect taban sınıf konulamaz

class C : public B{
public:
	C() : B(int){ // GEÇERLI
	}

	C() : A(int,int){ //SENTAKS HATASI.
	}
};

=======================================================================================================================
=======================================================================================================================

COPY CONSTRUCTOR
----------------

Copy ctoru derleyicinin yazımına bırakırsak(daha önce derleyici elemanları da copy ctor eder demiştik ama orada kalıtım yoktu şimdi
kalıtımıda işin içine katıyoruz.) taban sınıf nesnesinide copy ctor edecek.

DERLEYICININ YAZDIĞI KOD AŞAĞIDAKI GIBI

class Der : public Base{
public:
	
	// upcasting ile other(der& türünden) türüne Base in copy ctoru olan referansa aktarılabilir.
	Der(const Der &other) : Base(other), ax(other.ax), bx(other.bx) // iki nesne kopyalandığı için base nesneleride kopyalanacak.
	{
	
	}

private:
	A ax;
	B bx;
};

-------------------------------------------------------------------------

ÖR:

class Base{
public:
	Base()
	{
		std::cout <<"Base default Ctor"
	}
	Base(const Base&)
	{
		std::cout <<"Base copy Ctor"
	}
};

class Der : public Base{

};

int main()
{
	Der x;
	Der y(x); // der in copy ctory Base in copy ctorunu çağırır.
}

ÇIKTI
-----
Base default Ctor
Base copy Ctor

--------------------------------------

DİKKAT 
TÜREMİŞ SINIF İÇİN COPY CTORU BİZ YAZIYORSAK CTOR İNİT LİSTTE TABAN SINIF NESNESİ İÇİN COPY CTORUN ÇAĞRILMASINDAN SORUMLUYUZ
BUNU YAPMAZSAK DERLEYİCİ HAYATA GELEN DER NESNESİNİN İÇİNDEKİ BASE İÇİN, BASE İN COPY CTORUNU DEĞİL DEFAULT CTORUNU ÇAĞIRIR.

class Der : public Base{
	Der() = default;
	Der(const Der &other) : Base(other) bunu biz yazmalıyız.
	{
	
	}
};






*/

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class Base {
public:
	Base(int) {
		std::cout << "Base Default Ctor \n";
	}
	~Base() {
		std::cout << "Base Destructor \n";
	}
};

class Der : public Base {
public:
};

int main()
{
	Der myder; // Base in default ctoru ve Destructoru çağrıldı.
}
