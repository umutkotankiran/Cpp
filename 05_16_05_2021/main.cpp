/*

TYPE DEDUCTION GÖRDÜK.
BURASI İYİ ÇALIŞILMALI.

CONST BİR NESNENİN DEĞERİNİN DEĞİŞEMEYECEĞİNİ SÖYLÜYOR.
CONSTANT EXPRESSION İSE BİR SABİT İFADESİ OLDUĞUNU BELİRTİYOR MESELA, 5 BİR SABİT 

NOT: CONSTEXPR İLE TANIMLANANLAR HEM SABİT İFADESİ HEMDE DEĞİŞTİRİLEMİYOR.
NOT: CONST İLE TANIMLANANLAR DEĞİŞTİRİLEMİYOR AMA SABİT VEYA SABİT OLMAYAN BİR İFADE OLABİLİR.

CONSTEXPR BİR KEYWORD

const int x = 10;

C de bu sabit ifadesi gereken yerlerde bu kullanılamıyor.
C deki sabit ifadeleri switch deyimleri, array size ları
bitsel işlemlerindeki bit size, designated init ifadelerinde kullanılıyor

C++ ta ifadeye göre değişiyor.
const int x = 10;  sağdaki ifade sabitse bu sabit gereken yerlerde kullanılanilir
const int x = foo(); burada ise foo() sabit ifadesi olmadığı için kullanılamaz.

const nesneye ilk değeri sabit ifadesi ile verirsek sabit ifade
gereken yerlere kullanılır.

----------------------------------------------------------------------------------------------------

constexpr

BU NESNELERE ILK DEĞER SABIT IFADESI ILE VERILMELI.

constexpr int x = 10; 		BURASI OK
constexpr int x = foo(); 	SENTAKS HATASI

YANI CONSTEXPR ILE TANIMLANABILEN NESNELER SABIT IFADESI GEREKEN
HERYERDE KULLANILABILIR.

constexpr int x = 10;
constexpr int y = x * 5;   OK.Çünkü x te sabit.

CONSTEXPR ILE VERILMIŞ DEĞERLER DEĞIŞTIRILEMEZ.
x = 100; burada sentaks hatası.

bildiğimiz const ile constexpr nin farkı ileride görülecek.

----------------------------------------------------------------------------------------------------

Birde constexpr fonksiyonlar var.

const bir türün bileşeni.
const int x = 10;
decltype(x); türü const int. yani x e yeni atama yapamayacağım demek bu.

AMA CONSTEXPR ISE BU IFADENIN SABIT IFADESI OLARAK KULLANILACAĞINI GÖSTERIYOR.

constexpr const int* p = &x;   burada ikiside farklı anlamda
nesnenin türü const int* ama constexpr ile tanımlanmış.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
ÖRNEK: BURASI ÖNEMLİ !!!!
const sentaks bileşeni. ifadenin değişmeyeceğini söylüyor.
sabit ifadesi geçen yerlerde C++ ta const nesne kullanılır.

constexpr ise ifadenin bir sabit ifadesine eşitleneceğini söylüyor.

int y = 54;
int z = 44;
const int t = 22;

const int x = y; //Burası OK. const demek nitelenen ifade değişmeyecek demek.
constexpr const int x = z; // Sentaks hatası çünkü.z const değil.const olsaydı C++ ta sabit yerine kullanılabilirdi.
constexpr const int x = t; // Burası OK.burada t const, constexpr zaten ifadenin sabit olmasını ister. t sabit yerine kullanılır.
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

IMPLİCİT OLARAK BİR CONST DAHA GELİYOR

constexpr const int* p = &x; alttaki gibi aslında.Yani constexpr kullanıldığında implicit olarak aşağıdakine dönüşüyor.
constexpr const int* const p = &x; oldu.Yukarıdaki ile kıyasla.

DİKKAT !!
x i yukarıda global scope ta tanımlayınca çalışıyor ama local scope ta tanımlayınca otomotik ömürlü
olduğundan hata verdi. sanırım bu ileride görülecek.

Hocadan cevap alındı: Yerel değişken adresleri sabit ifadesi olarak kabul edilmiyor.
Global dğeişkenleri kabul edilebilir.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

CONSTEXPR FUNCTION

constexpr int square(int x)
{
	return x * x;
}

a - Bazı koşulları sağlaması gerekiyor.ileride görülecek
ör : static int val = 0; static yerel değişkene sahip olamaz.
Yani tüm değişkenlerin otomotik ömürlü olması gerekiyor.

b - Eğer bir constexpr func a gönderilen tüm argümanlar constant expr ise
ise bu durumda fonksiyonun geri dönüş değeri COMPILE TIME DA ELDE EDILIYOR. RUNTIME DA DEĞİL.
BUDA ŞU DEMEK FONKSİYONA YAPILAN ÇAĞRI İFADESİ BİR CONSTANT EXPR OLUŞTURUYOR.

constexpr functionu sabit ifadesi ile çağırmak zorunlu değil.

square(5) mesela burası bir sabit ifadesi oldu.RETURN DEĞERİ COMPILE TIME DA HESAPLANACAK
square(x + 5) burası sabit ifadesi değil.RETURN DEGERI RUNTIME DA HESAPLANACAK.


constexpr int a = 54;
constexpr int a = 66;

sum_square(a, b); sum_square constexpr olsun.a ve b sabit ifadesi olduğu için
bu ifade de sabit.ÖNEMLİ: Bu değer compile time da elde ediliyor.

constexpr fonksiyonun kendisini niteliyor.
fonksiyon return değerini değil.

int a = 54;
int a = 66;
sum_square(a, b);   
BU FONKSIYON BU DURUMDA 
1 - a ve b CONSTANT EXPRESSION DEĞİL.
2 - SENTAKS HATASI YOK.
3 - SABİT İFADESİ DEĞİL!!!!!!!
4 - SABİT İFADESİ GEREKEN YERDE KULLANILAMAZ. KULLANMADIĞIM ZAMANDA SORUN YOK.

NOT !!!!!!!!!!!!!
YANİ CONSTEXPR FOPNKSIYONA SABİT İFADESİ GÖNDERME ZORUNLULUĞU YOK AMA 
GÖNDERİRSEK FONKSİYON ÇAĞRISIDA SABİT İFADESİ OLUYOR VE COMPİLE TİME DA ELDE EDİLİYOR.


----------------------------------------------------------------------------------------------------

C de yazdığımız asal sayı fonksiyonunu C++ ta yazıyor.

constexpr bool isprime(int val)
{
	if (val == 1 || val == 0)
		return false;
	if (val % 2 == 0)
		return val % 2 == 0;
	if (val % 3 == 0)
		return val % 3 == 0;
	if (val % 5 == 0)
		return val % 5 == 0;

	for (size_t i = 7; i * i < val; i+=2) // buradaki koşul matematiksel olarak biliyor yoksa hepsine bakılırdı.
	{
		if (val % i == 0)
			return false;
	}
	return true;
}


2011 de geldi constexpr fonksiyonlar.
ilk başlarda kısıtlamalar daha sıkıymış.
Şimdi biraz gevşetilmiş.tek return deyimi gibi şeyler varmış.
Hoca bunu beğenmiyor : )


constexpr bool b = isprime(43); b nin üzerine imleci getirirsek "true" gösteriyor.
Yani compile time da elde ediyor bunu.b burada bir sabit ifadesi.

Not : b yi constexpr ile nitelemezsem compile time da değeri bulup true göstermedi.hatta uyarıyor.

constexpr int a = 234;
constexpr int b = 42;

a * b + 4 ---> buda bir sabit ifadesi. değeri compile time da belli oluyor.
const int x = a * b + 4; yazıp x in üzerine gelirsek sonucu gösterir. x i const yapmayınca göstermedi.


isprime(square(a,b) +1); bu ifade bir sabit ifadesi.çünkü fonksiyonlar constexpr ve elemanlarda sabit ifadesi.

----------------------------------------------------------------------------------------------------

sabit ifadesi olup olmadığını anlamak için başka bir constexpr değişkene
bu değer atanmalı.

----------------------------------------------------------------------------------------------------

constexpr int func(int x, int y)
{
	int a{10}; // constexpr fonksiyonlarda ilk değer vermemekte sentaks hatası

	std::cin >> a;

	return a;    // constexpr koşulu sağlanırsa ve değer runtime da hesaplanırsa değersabit ifadesi olmayacak
}

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

BU KISMIN ÖZETİ AŞAĞIDA
-----------------------

cosnt int x = 23;
cosnt int y = 23;

constexpr auto a = isprime(sum_square(x,y) + 3);  bu bir sabit ifadesi ve sentaks hatası yok. 
						  çünkü gönderilen değerler sabit



int x = 23;
cosnt int y = 23;

constexpr auto a = isprime(sum_square(x,y) + 3); burası ise sentaks hatası çünkü burada x sabit ifadesi değil.
						 doayısı ile constexpr ile belirtilen değilken sabit olamıyor.
						 fonksiyonlar constexpr ama argümanlar const değil, bu durumda
						 fonksiyonların ürettiği değerler sabit ifadesi değil.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

C++'TA ASIL OLAN VERİM !!!!!!!!!!!!!!!!!

KODU YAZARKEN BELLİ OLAN DEĞERLERİN İFADELERİN DEĞERLERİNİ
PROGRAMIN COMPİLE TİME DA HESAPLATMAK.

MESELA ASAL SAYI ÖRNEĞİ BÖYLE.
ÇÜNKÜ FONKSİYON CONSTEXPR İDİ.

double dval = sqrt(sin(x - y) + cons(a - b)); bunlar constexpr fonksiyonlar.
x y a ve b de öyle.

compile time da herşey hesaplanıyor bu durumda
derleme zamanında hesaplanacak değerler için gereksiz yere
runtime da kaynak harcanmıyor.Ne kadar mükemmel.
Bu dilin kuralı.Compiler optimization değil.

NOT : BU TANIŞMA DERSİ.
İLERİDE GÖRÜLECEK ZATEN.

----------------------------------------------------------------------------------------------------

DİKKAT !!!
C++ TA BAZI KODLARIN BAŞLIK DOSYASINDA BULUNMASI GEREKİYOR.
MESELA CONSTEXPR BİR FONKSİYON VAR DİYELİM.COMPİLERIN BUNU GÖRMESİ LAZIM.
BUNA GÖRE COMPİLE TİME DA HESAPLAMA YAPACAK.

YANİ FUNCTION DEFINITION HEADER FILE DA OLMALI.

INLINE FUNCTIONS
CONSTEXPT FUNCTIONS
TEMPLATE CODES
INLINE VARIABLES

KODU GÖSTERMEK İSTEMİYORSAK BU BİR DEZAVANTAJ OLABİLİR.

====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================

FUNCTIONLARIN VARSAYILAN ARGÜMAN ALMASI
---------------------------------------
C DE YOK.

BUNDAN SONRAKİ KONU FUNCTION OVERLOADING
--------------------

BİR FONKSİYONUN KAÇ PARAMETRESİ VARSA ONA O KADAR ARGÜMAN GÖNDERMELİYİZ.

void foo(int x, int y, int z);

int main()
{
	foo(1, 2); SENTAKS HATASI
		foo(1); SENTAKS HATASI
		foo(); SENTAKS HATASI
		foo(1, 2, 3, 4); SENTAKS HATASI

		foo(1, 2, 3); GEÇERLİ.
}

DEFAULT PARAMETER İSE
PARAMETREYE ARGÜMAN GÖNDERMİYORUM SEN VARSAYILAN ARGÜMANLARI KULLAN DEMEK.

void func(int, int, int = 10);

func(1, 2, 3); geçerli. 1, 2, 3 gönderildi
func(1, 2); geçerli. 1, 2, 10 gibi çağrılmış olacak.

MÜLAKAT SORUSU :
VARSAYILAN ARGÜMAN PROGRAMA MAALIYET GETIRIR MI ?
Hayır tamamen compile time ile ilgili bir olay.

EĞER BİR FONKSİYON İLE TANIŞIRSAK VEYA KAVRAM İLE, SORULACAK SORU :
BUNUN RUMTİME MAALİYETİ VAR MI ?

ÖYLE FONKSİYONLAR VAR Kİ YAPILAN ÇAĞRILAN ÇOK BÜYÜK ORANDA
BELİRLİ PARAMETRELER İÇİN HEP AYNI DEĞERLER ARGÜMAN OLARAK
GÖNDERİLİYOR.

PROGRAMCI İÇİNDE RAHATLIK GETİRİYOR.
BURADAKİ EN BÜYÜK RİSK SIRANIN KARIŞMASI.

KENDİ API LERİMİZİ YAZARKENDE CLIENT KODUN RAHAT ETMESİ İÇİN
KULLANABİLİRİZ.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

EĞER BİR FONKSİYONUN BİLDİRİMİNDE BİR PARAMETRE İÇİN DEFAULT ARGUMENT
BELİRTİLMİŞSE ONUN SAĞINDAKİ TÜM PARAMETRELERİNDE DEFAULT ARGUMENT
ALMASI GEREKİYOR.

1 - void func1(int = 5, int); BURASI SENTAKS HATASI
DEFAULT ARGUMENT VAR AMA SONRASINDA ARGUMENT GELMİŞ.

2 - void func2(int = 5, int, double); BURASIDA SENTAKS HATASI

3 - void func3(int = 5, int = 4, double = 3.4); BURASI GEÇERLİ.

NOT !!!!!!!!!!!!!!!!!!!
BİLDİRİMDE VARSAYILAN ARGUMENT BELİRTİLMİŞSE TANIMDA KESİNLİKLE
BELİRTİLMEYECEK.YOKSA SENTAKS HATASI.

----------------------------------------------------------------------------------------------------

NOT !!!!!!!!!!!!!!!!!!!
func(1, , 3); BU HATA.BU ŞEKİLDE ÇAĞIRAMAYIZ.

FONKSİYON BİLDİRİMLERİNDE VARSAYILAN PARAMETRELERE İSİM VERİLEDEBİLİR,
VERİLMEYEDEBİLİR.

void func1(int a = 5, int b = 10); bu gerçerli.


void func(const char* p = "Error"); GEÇERLİ ZATEN FARKI DA YOK.


NOT !!!!
VARSAYILAN İFADENİN SABİT İFADESİ OLMASI GEREKMİYOR.

int foo(int x = 10);
int func(int y = foo());

int main()
{
	func(); // çağrılırsa 
		// func(foo(10)); çağrılacak aslında.
}


Mülakat Sorusu
--------------
int foo()
{
	static int x = 0;
	std::cout << "foo cagrildi\n";
	return ++x;
}

void func(int y = foo())  // SORU: Burada foo bir kere mi çağrılacak yoksa her çağrıda tekrar mı çağrılacak?
{									// Her çağrıda tekrar çağrılır. yani x --> 3 olur.
	std::cout << "x = "<< x << "\n";
}
int main()
{
	func();
	func();
	func();
	
	ÇIKTI:
		foo cagrildi
		y = 1
		foo cagrildi
		y = 2
		foo cagrildi
		y = 3
}

----------------------------------------------------------------------------------------------------

int foo(int a, int b = a); BURASI SENTAKS HATASI
DEFAULT ARGUMENTTA DAHA ÖNCE KULLANILAN PARAMETRE 
KULLANILAMIYOR.

----------------------------------------------------------------------------------------------------

NOT !!!! ÇOOOK ÖNEMLİ !!!!!!!!!
void func(int, int, int);
BÖYLE BİLDİRİMİ OLAN FONKSİYONA DEFAULT ARGÜMAN EKLENEBİLİR Mİ ?
EVET EKLENEBİLİR.

BURASIDA ÇOOK ÖNEMLİ !!!!!!!!!!!!
TEKRAR BİLDİRİM / REDECLERATION İLE YAPILIR
void func(int, int, int = 10);


----------------------------------------------------------------------------------------------------

void func(int, int = 10, int); BURASI TEK BAŞINA SENTAKS HATASI

void func(int, int  int = 20); BURASI GEÇERLİ.
void func(int, int = 10, int); BURASI YUKARIDAKİ İLE BİRLİKTE SENTAKS HATASI DEĞİL. 
							   GEÇERLİ. SIRASI ÇOK ÖNEMLİ.

ARTIK BU İKİSİNİN CUMULATİVE HALİNİ KULLNABİLİYORUM.
Function redecleration olarak alıyor burayı.

func(1); BURASI GEÇERLİ.ÇAĞRILABİLİR.
// func(1,10,20); bu şekilde çağrılır.

NOT:
void func(int, int  int = 20);
void func(int, int  int = 20);

2 DEFA TEKRAR EDİLMİŞ AYNI BİLDİRİM.REDECLERATİON. SENTAKS HATASI.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

ÇOK ÖNEMLİ BİR YER DAHA.
REDECLEREATION İLE REDEFINITION KARIŞTIRILIYOR.
BURAYI KARIŞTIRMA.

AŞAĞISI SENTAKS HATASI.
int func()
{
	return 1;
}
int func()
{
	return 1;
}

----------------------------------------------------------------------------------------------------

redecleration örnek
#include <cstdlib>



int main()
{
	int ival = { 12345 };
	char buf[100];

	_itoa(ival, buf, 10);
	cout << "(" << buf << ")";

}

Global scope ta üst tarafta, 
aşağıdaki gibi REDECLERATION yapsaydık bir parametreyi göndermeye gerek yoktu.

int _itoa(int, char*, r = 10);


----------------------------------------------------------------------------------------------------

void print_date(int day, int mon, int year = -1);
bu kullanılan bir tema. default argument kullanıldığını söylüyor.

printf_date(15, 4); bu çağrı 2020 de yapıldıysa 15 4 2020 gibi bir
birşey sağlamak.

----------------------------------------------------------------------------------------------------

ÖR:

Decleration // header file da olabilir.
void print_date(int day = -1, int mon = -1, int year = -1);
//gönderilmeyen argümanlar için içinde bulunduğumuz yıl kullanılacak.

definition
void print_date(int day = -1, int mon = -1, int year = -1)
{
	if (y == -1)
	{
		time_t timer; // doğrusu std::time_t timer;  C den gelen fonksiyonları kullanırken bunların std:: içinde düşüneceğiz.
		time(&timer); // std::time(&timer);				
		struct* tm = localtime(&timer); //yada auto p = std::localtime
		y = tm->tm_year + 1900;

		if (m == -1)
		{
			m = tm->tm_mon + 1;
			if (d == -1)
				d = tm->tm_mday;
		}
	}

	printf("%02d-%02d-%d", d, m, y);
}


----------------------------------------------------------------------------------------------------

void func(int, int* ptr = nullptr);  bu tip örnekler çok göreceğiz.

char str[] = "7654.723ahmet"

char* p;

double dval = strtod(str, &p);

p burada başarısız olunan kısmın adresini döndürüyordu.
yani p = "ahmet" oldu.

C++ ta olsa

double strtod(cosnt char*, char** = nullptr); bunu bildirimde yukarı yazsaydık.
çağırırkende sadece strtod(str); deseydik bu stdtod(str,NULL) ile aynı anlamda olacaktı.


====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================
====================================================================================================


FUNCTION OVERLOADING
--------------------
C++ IN EN ÖNEMLİ ÖZELLİKLERİNDEN BİRİ.

FONKSİYONLARIN AŞIRI YÜKLENMESİ ÇEVİRİSİNE HOCA AŞIRI KARŞI : D:D

FONKSİYONLARIN YÜKLENMESİ DİYOR.

KODLARI BİRBİRİNDEN FARKLI BİRDEN FAZLA FONKSİYON İSİMLERİNİN
AYNI SEÇİLMESİNE DENİYOR.

C DE BU SENTAKS HATASI.
C++ FAYDALI BİR ARAÇ.

1. AMAÇ : AYNI İŞİ YAPAN FONKSİYONLARIN AYNI İSMİ ALARAK PROGRAMCIYA RAHAT
KOD YAZMA İMKANI VERMEK.

C DE MUTLAK DEĞER FONKSİYONLARI VAR.
HER TÜR İÇİN FARKLI MUTLAK DEĞER FONKSİYONLARI VAR MESELA
abs() - fabs() - labs() gibi birsürü aynı işi yapan fonksiyon var.
Overloading bunlara tek isim vermek anlamında kullanılıyor.

Mesela tamsayılar için toplamayı + operatörü ile
Reel sayılar için toplamayı @ operatörü ile yapmak gibi.


2. BUNUN BİR İŞLEM MAALİYETİ YOK.
A - HANGİ FONKSİYONUN ÇAĞRILDIĞI DERLEME ZAMANINDA ANLAŞILIYOR.
STATIC BINDING / EARLY BINDING . BU FUNCTION OVERLOADING !!!!!!!!!!!
BİZ ŞUANDA BURADAYIZ.

B - HANGİ FONKSİYONUN ÇAĞRILDIĞI ÇALIŞMA ZAMANINDA ANLAŞILIYOR.
DYNAMIC BINDING / LATE BINDING . BU FUNCTION OVERLOADING DEĞİL !!!!!!!!!!!
BUNUNLA KURSUN 2. YARISINDA TANIŞACAĞIZ.


OVERLOAD İNGİLİZCEDE HEM FİİL HEMDE İSİM OLARAK KULLANILIYOR.
FONKSİYONUN 3 TANE OVERLOAD U VAR MESELA İSİM ANLAMINDA KULLANILMIŞ.

foo FUNCTIONU OVERLOAD EDİLMİŞ
foo FUNCTIONUNUN 3 TANE OVERLOAD U VAR. HEM FİİL HEM İSİM ANLAMINDA KULLANILIYOR.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

BU KONU ÇOK KARIŞTIRILIYOR

1 - FUNCTION OVERLOADING VAR MI YOK MU ? BU AYRI BİR KONU
2 - FUNCTION OVERLOADING VAR VE BEN BU FUNCTIONLARDAN BİRİNİ
ÇAĞIRINCA HANGİSİ ÇAĞRILMIŞ OLUR ? FUNC(? ? ? );
BU FUNCTION OVERLOAD RESOLUTION SÜRECİNDE BELLİ OLUYOR.
BURADA ÇOK NET KURALLAR VAR.

----------------------------------------------------

FUNCTION OVERLOADING OLMASI İÇİN 2 KOŞUL VAR.

1. SORUNUN CEVABI.
BUNUN OLMASI İÇİN OLMAZSA OLMAZ İKİ KOŞULUN SAĞLANMASI GEREKİYOR.

	A - AYNI KAPSAM(SCOPE) İÇİNDE BİRDEN FAZLA FONKSİYONUN İSİMLERİ AYNI OLACAK.
	FARKLI KAPSAMLARDAKİ AYNI İSİMLİ FONKSİYONLAR OVERLOAD DEĞİL.NAME MASKİNG
	OLUR BURADA.YANİ AYNI SCOPE TA AYNI İSİM OLACAK !!!!!!!!!!!!

int func();

int main()
{
	int func(double);  // KESİNLİKLE FUNCTION OVERLOADING DEĞİL.SCOPE LARI FARKLI
}


	B - AYNI SCOPE TAKİ AYNI İSİMLİ FUNCTION İMZALARI/SIGNATURE FARKLI OLACAK.
	İMZALAR AYNI İSE OVERLOADİNG YOK.

IMZA NE DEMEK : 
BİR FONKSİYONUN GERİ DÖNÜŞ DEĞERİ TÜRÜ DIŞINDAKİ PARAMETRİK YAPISINA O FONKSİYONUN İMZASI DENİR.
YANİ RETURN DEĞERİ HARİCİNDEKİ HERŞEY İMZAYA DAHİL.

int func(long);
double func(long);  İMZALARI AYNI. RETURN DEĞER DAHİL EDİLMİYOR. GERİ KALANLAR AYNI.
					İMZALAR AYNI İSE OVERLOADİNG YOK.

int func(int)
int func(int)   OVERLOADING DEĞIL.REDECLERATION VAR.SENTAKS HATASI YOK.


int func(int, int, int = 10);
int func(int, int, int = 10);  DİKKAT!!!!! BURADA SENTAKS HATASI VAR.ARGUMENT DEFAULT PARAMETERDAN DOLAYI.


int func(int)
double func(int)  OVERLOADING DEĞIL VE SENTAKS HATASI.RETURN DEĞERDEN ÖTÜRÜ SENTAKS HATASI.

int func(int);
int func(int, int);
int func(double);
int func(int*);   BURADA BU FONKSIYONUN 4 TANE OVERLOAD U VAR.

int func(int);
int func(int, int = 10);  2 TANE OVERLOAD VAR ÇÜNKÜ FUNCTION IMZASI FARKLI.

----------------------------------------------------------------------------------------------------

int func(int);
int func(const int);   BURASI OVERLOADING DEĞIL.REDECLERATION VAR.CONST BURADA İHMAL EDİLİYOR. PTR DA İHMAL EDİLMİYOR
			VEYA REFERANSLARDA İHMAL EDİLMİYOR.

NASIL ANLARIM ?
REDECLERATİON HATA VERMEZ AMA BUNU DEFINITIONA ÇEVİRİRSEK HATA VERİR.
int func

REDECLERATION ILE REDEFINITION FARKLI ŞEYLER.

BURADA HAS ALREADY BODY GİBİ BİR HATA GÖRÜRÜZ.
YANİ AYNI FUNCTIONDAN BİR TANE DAHA VAR DEMEK AŞAĞISI
BURASI DEFİNİTİON. DECLERATİON DEĞİL.
int func(int)
{

}
int func(const int) // DERLEYİCİ CONST U GÖRMEZDEN GELİYOR.
{

}

BURADA İSE OVERLOADİNG VAR. ÇÜNKÜ İMZASI FARKLI.FONKSİYON İSİMLERİ İSE AYNI.

int func(int)
{
	return 1;
}
int func(const int,int)
{
	return 1;
}


TEKRAR YAZIYORUM YUKARIDA VARDI
int func(int);
int func(const int);   BURASI OVERLOADING DEĞIL.REDECLERATION VAR.

----------------------------------------------------------------------------------------------------

void func(int*);
void func(const int*); BURASI KESINLIKLE FUNCTION OVERLOADING.


----------------------------------------------------------------------------------------------------

void func(int*p);
void func(int* const p);   BURADA FUNCTİON OVERLOADING YOK. TOP LEVEL CONST DERLEYİCİ TARAFINDAN İHMAL EDİLİP
							AYNI TÜR GİBİ İŞLEM GÖRÜYOR.
KANITLAMAK İÇİN DECLERATIONDAN DEFINITIONA ÇEVİR.

NOT : OVERLOADİNG VARSA DECLERATIONDAN DEFINITIONA ÇEVİRDİĞİMDE HATA OLUŞMAZ
OVERLOADİNG YOKSA HATA VERİR ÇÜNKÜ AYNI İSİMDE BİR FONKSİYON DAHA TANIMLANMIŞ OLUR.
BU OVERLOADİNG VARSA MÜMKÜN.

----------------------------------------------------------------------------------------------------

typedef int itype;

void func(int);
void func(itype);  OVERLOADING YOK, REDECLERATION VAR.

----------------------------------------------------------------------------------------------------

C++ ta
using itype = int;

typedef int (*fptr)(int); bu C ve C++ ta
using fptr = int(*)(int); bu Modern C++ ta daha çok kullanılır.

----------------------------------------------------------------------------------------------------

void func(char);
void func(signed char);
void func(unsigned char);  burada 3 tane function overloading var.

ikna için : D
void func(char) {}  üçünede yaz.hata yoksa overloading var.
void func(signed char) {}
void func(unsigned char) {} hata yok çünkü overloading

----------------------------------------------------------------------------------------------------

void func(int);
void func(int32_t);  // IMPELEMTATION DEFINED :D
		     // bende overloading yok.redefinition var :D
		     
----------------------------------------------------------------------------------------------------

void func(int&);
void func(const int&);  burada OVERLOADİNG var.Pointer örneğinde olduğu gibi.

BU EN SIK KULLANILAN OVERLOAD BİÇİMLERİNDEN BİRİ.

----------------------------------------------------------------------------------------------------

void func(int&);
void func(const int&);
void func(int &&);		BURADA 3 ADET OVERLOAD VAR.

TEREDÜTTE Mİ KALDIM ?
HEPSİNDE ; YERİNE {} YAPIP DEFINITION YAP.
HATA YOKSA OVERLOAD VAR. HATA VARSA OVERLOAD OLMAMIŞTIR.

----------------------------------------------------------------------------------------------------

void func(int&)
void func(const int&)
void func(int&&)  3 adet overloading var.

void func(int)
void func(int&)  BURADA DA OVERLOADING VAR

void func(int ,...)
void func(int ,int)  BURADA DA OVERLOADING VAR


void func(int[]);
void func(int*);  BURADA OVERLOADING YOK!!!


TUZAK SORU
----------
void func(int[]);
void func(int[5]);
void func(int[6]);
void func(int*);     OVERLOADING YOK.

----------------------------------------------------------------------------------------------------

NOT !!!!!!!!!!

Nesnenin kendi constluğu bir overloading yaratmıyor.

birde paramtetrelerin top level constluğu overloading oluşturmuyor.

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

ZOR BÖLÜM !!!!!!!!!!!!!


2. FUNCTİON OVERLOADİNG VAR VE HANGİ FONKSİYONUN
ÇAĞRILDIĞI NASIL ANLAŞILIR.

void func(long double);
void func(char);

func(2.3);  SENTAKS HATASI. HEMEN ANLAŞILMIYOR. :D :D
fonksiyonların ikisinden biri olsaydı sentaks hatası olmayacaktı ama ikisi olunca compiler seçemiyor.


FUNCTION OVERLOAD RESOLUTION
	
Bu süreç 2 farklı şekilde sonuçlanır.

	a - GEÇERLİ KOD OLUŞUR VE HANGİ FONKSİYONUN ÇAĞRILDIĞINI ANLAR
		VE PROGRAMI O KODA BAĞLAR
	
	b - SENTAKS HATASI OLUR.
		Bu hatalar 2 ye ayrılıyor

		1 - NO MATCH : UYGUN FONKSİYON OLMAMASI DURUMU SENTAKS HATASIDIR.
			func(nullptr); yukarıdaki func ı bu şekilde çağırmak gibi.

		2 - AMBIGUITY(çift anlamlılık) :
			func tanımında 2 sinden biri bile olsa hata yoktu
			ama 2 seçenek arasında seçme yapılamıyor.
			öncelik veremiyor.Böyle durumlarda SENTAKS HATASI

----------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------

FUNCTION OVERLOAD RESOLUTION SÜRECİ 3 AŞAMADA ELE ALINIYOR.

1 - FUNCTİON ÇAĞRI AŞAMASINDA GÖRÜLEBİLİR OLAN AYNI İSİMDEKİ
TÜM FUNCTIONLARI BİR LİSTEYE KOYUYOR.CANDIDATE FUNCTIONS

2 - VIABLE FUNCTION.BU FONKSIYON TEK BAŞINA OLSAYDI BU ÇAĞRI
LEGAL OLUR MUYDU ? EVET İSE BU VIABLE FUNCTION
NASIL OLACAK BU

	A - FUNCTION ÇAĞRISINDA KULLANILAN ARGÜMAN SAYISI İLE
	FUNCTION PARAMETRE SAYISI UYUMLU OLACAK.DEFAULT ARGUMENT DAHİL.
	VERİKAYBI DA OLABİLİR SORUN DEĞİL.

	B - HER ARGÜMANDAN HER PARAMETREYE GEÇERLİ BİR TÜRDÖNÜŞÜMÜ OLACAK.

	SORU : HANGİSİ VIABLE ? 

	void func(long double);
	void func(char);
	void func(int, int);
	void func(int*);

	int main()
	{
		func(21);
	}

	CEVAP = 1 ve 2. sıradakiler VIABLE. Veri kaybı olması sorun değil
			3. dönüşüm tek başına olsaydı sentaks hatası. 4. fonksiyon 
			olsaydı implicit dönüşüm yok, yine sentaks hatası.C++ casting esas alınacak. 
			C yi karıştırma :D

	----------------------

	SORU : HANGİSİ VIABLE ? 

	void func(int*);
	void func(void *);
	void func(nullptr_t);

	int main()
	{
		func(malloc(1000));
	}

	CEVAP = C++ void * dan int * a implicit yok. 
		    SADECE void * olan VIABLE. nullptr_t türüne de dönüşüm yok.

	-----------------------

	SORU : HANGİSİ VIABLE ?

	enum color {red,purple,orange,white,pink};

	void func(int);
	void func(color);

	int main()
	{
		func(white);
	}

	CEVAP = İKİSİDE VIABLE ÇÜNKÜ C++ IN GENÇLİK HATASINDAN ÖTÜRÜ
			int = color  OLABİLİYOR YANİ CAST EDİYOR. İNT ENUM TÜRÜNÜ TUTABİLİYOR.
			İNT, ENUM CLASS I TUTAMIYOR. COLOR İSE İNT TÜRÜNÜ YİNE TUTAMIYOR.

	-----------------------

	SORU : HANGİSİ VIABLE ?

	void func(bool);
	void func(void *);

	int main()
	{
		int x{};
		func(&x);		
	}

	CEVAP = İKİSİDE VIABLE. BOOL TÜRÜ ADRESTEN DÖNÜŞÜM YAPABİLİYOR.
			DİĞERİ İSE ZATEN VOİD *, HER TÜRDEN POİNTERI TUTABİLEN BİR TÜR.

	-----------------------

3 - VIABLE LARIN İÇERİSİNDEN EN UYGUN OLANIN SEÇİLMESİ
BEST VIABLE VEYA BEST MATCH FUNCTION DENIYOR.
2 VEYA DAHA FAZLA FUNCTION ARASINDAN SEÇEMEZSE, AMBIGUITY DURUMU OLACAK.
SENTAKS HATASI OLACAK.

NOT: ORTADA VIABLE FONKSİYON YOKSA BU AŞAMAYA GEREK YOK.
	 NO MATCH VEYA AMBIGIUTY HATASI OLUŞMUŞTUR
	 EĞER BİR TANE VİABLE OLSAYDI YİNE GEREK YOKTU. 
	 VIABLE OLAN SEÇİLECEKTİ ÇÜNKÜ BAŞKA ÇAĞRILMA İHTİMALİ OLAN FONKSİYON YOK.

	 BU DURUMDA VIABLE FUNCTION SAYISI 2 VEYA DAHA FAZLA.
	 ----------------------------------------------------
	 ----------------------------------------------------

	ARGÜMANDAN PARAMETREYE YAPILAN DÖNÜŞÜM BELİRLİ KATEGORİLERE AYRILIYOR.
	BUNLAR DAHA İYİ VEYA DAHA KÖTÜ

	3.1 - VARIADIC CONVERSION = OLABILECEK EN KÖTÜ DÖNÜŞÜM BU.
		
		void func(...); olsun mesela parametresiz olmaz normalde 
		void func(void *);

		int main()
		{
			int x = 10;
			func(&x);    kesinlikle ikincisi seçilecek. variadic olanın şansı yok.
		}					en az öncelikli olan variadic.

	--------------------------------------------------------

	3.2 - USER DEFINED CONVERSION / PROGRAMCI TANIMLI DÖNÜŞÜM
	VARIADICTEN İYİ AMA DİĞERLERİNDEN KÖTÜ.

	struct data{
		int x;
	};
	int main()
	{
		data mydata;
		mydata = 10; // sentaks hatası int ten mydataya conversion yok.
	}

	EĞER
	struct data{
		int x;
		Data(int);
	};

	int main()
	{
		data mydata;
		mydata = 10; // Artık sentaks hatası yok.bunun sebebi Data(int) in varlığı
	}				// buradaki dönüşüm kategorisi USER DEFINED CONVERSION oluyor.


	struct A{
		Operator int()const;
	};

	int main()
	{
		A ax;
		int ival = ax;  // Operator int()const; BUNUN SAYESINDE BU CONVERSION LEGAL HALE GELDI.
	}

	İLERİDE CLASSLARDA GÖRÜLECEK ZATEN

	-----------------------------------------

	3.3 - STANDART CONVERSION
	INT TEN DOUBLE A VEYA TERSİ
	İNT * DAN CHAR * A  TÜM TÜR DÖNÜŞÜMLERİ.
	LONT TAN CHAR A DÖNÜŞÜM VAR MI ?
	LOSS OF DATA OLABİLİR... AMA DÖNÜŞÜM VAR : D
	DÖNÜŞÜM UB OLUŞTURABİLİR... AMA DÖNÜŞÜM VAR : D

	STANDART CONVERSION İSE USER DEFINED CONVERSIONDAN VE VARIADIC CONVERSIONDAN DAHA ÖNCELİKLİ.

		STANDART CONVERSION 1 DEN FAZLA OLURSA.

		ÖR:
		void func(long double);
		void func(char);
		
		int main()
		{
			func(2.3); // burada conversionu yapacak. SENTAKS HATASI VERMİŞTİ.
		}
		Aşağıdaki kurallar geçerli.

			3.3.1 - EXACT MATCH - TAM UYUM
				
			      - EXACT MATCH - TAM UYUM
				ARGÜMAN TÜRÜ ILE PARAMETRE TÜRÜNÜN TAMAMEN AYNI OLMASI DURUMU.
				İstisnai durumlarda var.

				void func(long double);
				void func(char);
				int main()
				{
					func(2.4L); // 2.4L long double türüdür. 1. fonksiyon ile EXACT MATCH VAR.
					func('A'); // 'A' char türündendir. 2. fonksiyon ile EXACT MATCH
				}				

						
				- ARRAY DECAY. 
				  int a[] = {1,2,3}; 
				  func(a); //array decay var.Aynı şey REFERANS SEMANTIĞINDE de geçerli.EXACT MATCH
			
				- CONST CONVERSION
				  void func(const int);
				  int x{12};
				  func(&x); // int & ten const int & e dönüşüm legal. const conversion var.EXACT MATCH
							// tersi zaten viable değil. implicit dönüşümü yok.

				- FUNCTION TO POINTER CONVERSION
				  void func(int (*)(int));
				  int foo(int);

				  func(foo); //bu şekilde çağırmakla
				  func(&foo);  // bu şekilde çağırmak arasında fark olmayacak.
								// klasik function to pointer conversion.


			3.3.2 - PROMOTION - YUKSELTME - TERFİ
			
				- INTEGRAL PROMOTION
				  C DE GÖRÜLDÜ.INT ALTI TÜRLERDEN İNT E DÖNÜŞÜM.
				  PROMOTION DİĞER CONVERSİONLARDAN DAHA ÜSTÜN.
			      BOOL->İNT
				  CHAR->İNT
				  SİGNED CHAR->İNT
				  UNSGINED CHAR->İNT
				  SHORT->İNT
				  UNSGINED SHORT->İNT

				  Aşağıdakilerde geçerli 
				  FLOAT->DOUBLE

				  AMA 
				  DOUBLE VEYA FLOAT->LONG DOUBLE A PROMOTION DEĞİL.CONVERSION.

			3.3.3 - CONVERSION - ÇEVİRİ
				
				BUNUN DIŞINDA EXACT MATCH OLMAYAN, PROMOTION OLMAYAN TÜM DÖNÜŞÜMLER DÜZ DÖNÜŞÜM.
				VE BUNLAR ARASINDA HİÇBİR SEÇİM KRİTERİ YOK. AMBIGUİTY
			
			AYNI ÖRNEK. :D:D

			ÖR:
			void func(long double);
			void func(char);

			int main()
			{
				func(2.3); // exact match veya promotion değil. Conversion. Burada Ambigiuty var 
			}				// SENTAKS HATASI.
						
			---------------------------------

			ÖR:
			void func(unsigned int);
			void func(double);

			int main()
			{
				//func(12); // Conversion var. promotion yok. exact match zaten yok. SENTAKS HATASI.
			}				// Ambigiuty

			----------------------------------

			ÖR:
			void func(unsigned int);
			void func(double);

			int main()
			{
				//func(2.5f); // float tan double a promotion var. 2. ci çağrılır 
			}


			----------------------------------

			ÖR:
			void func(unsigned int);
			void func(long double);

			int main()
			{
				//func(2.5f); // float tan long double a promotion değil conversion.Ambigiuty
								// SENTAKS HATASI
			}

			----------------------------------

			ÖR:
			void func(int);
			void func(double);

			int main()
			{
				//func(5 > 2 ); // bool dan int e integral promotion var. 1. çağrılır
				//func('A'); // integral promotion var. 1. çağrılır.
			}

			----------------------------------

			ÖR:
			void func(int);
			void func(double);
			void func(long);

			int main()
			{
				//func(2ul); // Ambigiuty - SENTAKS HATASI. unsigned long convert edilir.conversion var.
			}


			================================================================================================
			================================================================================================
			================================================================================================
			================================================================================================
			================================================================================================
			================================================================================================
			================================================================================================
			================================================================================================
			

			ÖZET
			OVERLOADİNG KURALLAR
			1 - FUNCTION OVERLOADING VAR MI YOK MU ?

				1.1 Eğer aynı scope ta aynı func isminden 1 den fazla varsa
				1.2 İsimleri aynı olan bu func ların imzaları farklımı yani
				parametreleri farklıysa
								
				YUKARIDAKİ İKİ KURAL VARSA OVERLOADING VARDIR.
				AŞAĞIDAKİ KURALA GEÇİLİYOR.

			2 - FUNCTION OVERLOADING VAR İSE BEN BU FUNCTIONLARDAN BİRİNİ
			ÇAĞIRINCA HANGİSİ ÇAĞRILMIŞ OLUR ?
			
				 FUNCTION OVERLOADING RESOLUTION SÜRECİ İLE BELİRLENİYOR
				 BURADA İKİ TANE SENARYO VAR. YA UYGUNU BULUP ÇALIŞACAK
				 YA DA UYGUN KODU BULAMAYIP 2 FARKLI ŞEKİLDE HATA VERECEK.

				 2.1 Geçerli kod oluşur hangi fonksiyonun çağrıldığı anlaşılır
					 ve program o koda bağlanır.
				 2.2 İki tane hata durumu ile karşılaşılır
					 2.3 No match : Uygun fonksiyon olmaması durumu
					 2.4 Ambigiuty : Çift anlamlılık. 2 veya daha fazlası
					 arasında karar veremiyor.


			3 - FUNCTİON OVERLADING RESOLUTION SURECİ 3 AŞAMADA ELE ALINIYOR.

				3.1 Fonksiyon çağrı aşamasındaki görünür isimlerin tamamını
					bir listeye koyuyor.Candidate functions
				3.2 Viable function durumu. Bu fonksiyonlar herbiri tek
					başına kullanılsaydı çalışır mıydı ? Evet ise
					Viable function oluyor.

				Nasıl Viable function oluyor
				a - Kullanılan argüman sayısı ile function parametre
					sayısı tamamen aynı ise. Default arg dahil.
					veri kaybı olması sorun değil.
				b - Her argümandan parametreye geçerli tür dönüşümü olacak


				3.3 Viable olanların içinden en uygunun seçilmesi. Best viable
				veya best match deniyor.1 den fazla arasında seçme yapamazsa
				Ambigiuty hatası olacak.

				3.3.1 Variadic Conversion
					  Olabilecek en kötü conversion. En kötü ihtimal bu.

				3.3.2 User Defined Conversion
					  Bu Variadicten daha iyi.İleride görülecek struct
					  dönüşümlerinde kullanılacak.

				3.3.3 Standart Conversion
					  Hepsinden daha üstün conversion.İlk öncelik bunun.
					  Bazı adımları var.

					  STANDART DÖNÜŞÜM BİRDEN FAZLA OLURSA AŞAĞIDAKİ
					  KURALLARA BAKILIR.

					  3.3.3.1 Exact Match - Tam Uyum
						  1. Öncelik
						  Argüman ile parametrenin tamamen uyumlu olması.
						  Bazı istisnaları var.Aşağıdakiler bunlar.
						  Bu tip conversionların Hepsi Exact Match.

						- Array Decay
						- Const Conversion
						- Function to Pointer Conversion
						Hepsi Exact Match.

					  3.3.3.2 Promotion
						  2. Öncelikte bunlar var.

						  C DE GÖRÜLDÜ.INT ALTI TÜRLERDEN İNT E DÖNÜŞÜM.
						  PROMOTION DİĞER CONVERSİONLARDAN DAHA ÜSTÜN.
						  BOOL->İNT
						  CHAR->İNT
						  SİGNED CHAR->İNT
						  UNSGINED CHAR->İNT
						  SHORT->İNT
						  UNSGINED SHORT->İNT

						  Aşağıdakide geçerli
						  FLOAT->DOUBLE
						  
						  DOUBLE -> LONG DOUBLE  PROMOTION DEĞİL.
						  FLOAT -> LONG DOUBLE   PROMOTION DEĞİL.

					   3.3.3.3 Conversion
						   Conversionlar arasında seçim kriteri yok.
						   Bu Ambigiuty olarak değerlendiriliyor.

*/
