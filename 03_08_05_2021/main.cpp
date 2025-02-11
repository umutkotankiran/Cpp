/*

	NUMARALANDIRMA TÜRLERİ

1. C DE ENUM TÜRÜ SIGNET İNT.SİZEOF DEĞERİDE AYNI ZATEN
C++ TA UNDERLYİNG TYPE DİYE GEÇİYOR.BU MODERN C++ TA GELDI.BELİRTMEZSEK BU TÜRÜ KENDİ SEÇİYOR.
MODERN C++ TA TÜRÜNÜ BELİRTEBİLİYORUZ
	
ENUM COLOR : UNSİGNED LONG { WHITE, RED,BLACK};
TÜR BELİRTMEZSEK ENUMERATOR DEĞERLERİNE BAKARAK KENDİ SEÇİYOR.

2. BİLDİRİM YAPARSAK EĞER TYPE BİLGİSİNİ BİLDİRİMDE DE GÖRÜYORUZ.
İÇİNİ GÖRMESEKTE TÜR VAR.
ENUM COLOR : UNSİGNED LONG; 

3. enum color mycolor;
mycolor = 3; olabiliyordu C de.
hatta mycolor = purple; başka enum türünün içinde tanımlansa bile
atama sorunsuz

C++ ta farklı 

C++ DILINDE ARITMETIK TÜRLERDEN ENUM TÜRLERINE ÖRTÜLÜ TÜR DÖNÜŞÜMÜ YOK.

Color mycolor = white;
white = 2; DİREKT SENTAKS HATASI.
while = off; (başka bir enum türünün elemanı off) SENTAKS HATASI

4. EN BÜYÜK FARKLILIK MODERN C++ TA GELDİ.
YENİ BİR ENUM KATEGORİSİ EKLENDİ.

BUNLARA ENUM CLASS DİYENLER VAR AMA STANDARTLAR SCOPED ENUM DİYOR.
KAPSAMLANDIRILMIŞ NUMERATÖRLER.

eskiden numaralandırma türünün scope u neyse num. sabitininde türü oydu.

iki farklı başlık dosyasından iki farklı bildirim gelse.
bunlar enum bildirimi.
ikisininde içindeki elemanlardan biri aynı olsa, bunlar 
redefinition hatası verir.C de de bu böyle.ENUM türünün kapsamı yok yani.

Ciddi problem bu.
class yazan var, namespace yazan var. enumerator adını değiştiren var.
enum tag ismini başına yazılması gibi.

-----------------------

HOCA BUNA C++ IN GENÇLİK HATASI DIYOR :D
screencolor color = gray;
int ival = 34;

ival = color ; BU OK. IMPLICIT DÖNÜŞÜM VAR.BUNA OK DEMESİ YANLIŞ BİR KARAR.
color = ival ; SENTAKS HATASI

BİR PROBLEM DAHA VAR. 3. bu.

complete type ve incomplete type konusu.
başlık dosyasında
enum color;  yapılamıyordu.


ÇÖZÜMÜ
enum class color { white,red,magenta,black};
artık bu enum constans/enumeratör leri doğrudan kullanamıyorum.

Color mycolor = color::red; ile kullanabilirim.
Bu sayede çakışmada olmuyor.Gayet mantıklı
Her birinin scope u var.

BURADA
Ne aritmetik türlerden(double int long...) bu türlere,
nede bu türlerden artitmetik türlere dönüşüm yok.

int ival = screencolor::white; mesela bu.SENTAKS HATASI.
yukarıda bir kod vardı.Orada izin veriyordu.GENÇLİK HATASI KODU :D:D
IMPLICIT DÖNÜŞÜM YOK.
EXPLICIT DÖNÜŞÜM VAR.

bunu int ile yapılabilir ama önerilmiyor.
önerilen static_cast<int> ile yapılıyor.


enum classta da underlying type verilebilyor.
enum class color : short { white,red,magenta,black}; gibi.


C++20 DE BİR DEĞİŞİKLİK DAHA GELDİ.DERLEYİCİLER BİLE DESTEK VERMİYOR DAHA


void func()
{
	//birsürü screencolor var

	using ScreenColor::White;
}


-------------------------------------------------------------------

REFERANS SEMANTİĞİ
------------------
C++ dilinde pointer kullanımı C ye göre çok çok daha az.

Bunun yerine 
------------
Referans Semantiği
Smart Pointer kullanılıyor.

Pointerlar C++ ta maalesef generic programlama tarafındaki araçlarla çok uyum sağlamıyor.
Bu yüzden Referans semantiği smart pointer gibi araçlar var.

Referans Modern C++ tan önce 1 taneydi.
Şimdi 2 ayrı referans kategorisi oldu.


R Value reference
Taşıma/Move Semantics
Mükemmel gönderim / Perfect forwarding

L Value reference 
Nesnenin yerine geçen bir isim

Referanslar default init. edilemiyorlar
int& r; BU SENTAKS HATASI
hatırlatma const int x; buda hata.C de değil ama C++ ta hata çünkü değeri yok.

Bildirimlerde kullanılan 
int* p; bu * bir decleratör.
int&r = x; 
Artık r demek x demek.

r burada referans olan isim.bunlara Lvalue referans deniyor.
x te buna ilk değer veriyor.

int&r = x;  veya int&r(x); veya int& r{x}; hepsi aynı.

burada artık r, x in yerinde kullanılıyor. r demek x demek.

BU R Yİ X E BAĞLAMAK DEMEK.BIND
DOLAYLI BİR POINTER GİBİ.

int&r = x;
r = 40;
godbolt.org dan bakınca assembly düzeyinde pointerlar ile aynı kodu
üretiyor.



void foo(int& r)
{
	r = 45;
}

int main()
{
	int x = 10;
	foo(x);
}

BU Şekilde kullnılıyor.


-----------------------

int x = 10;
int& r = x;

r artık kullanıldığı yerlerde x i temsil ediyor.

Adreslerine baktı, aynı.
fonksiyon örneğinde de adrese baktı.Aynı adres.

int x = 10;
double &r = x; sentaks hatası.

double y = 2.0;
double &r = y; burası legal

Yani referans hepsi kendi türünden atamaya izin veriyor.

Pointer ve Referans semantikleri araasında hız farkı yok.
Zaten aynı şeyler alt düzey kodlarda.


Burda C deki swap functionunu yazdık.farkına baktık.

#include <iostream>

void Swap(int& r1, int& r2)
{
	int temp = r1;
	r1 = r2;
	r2 = temp;
}

int main()
{
	int x = 10, y = 34;
	std::cout << "x = " << x << " y = " << y << "\n";
	Swap(x, y);
	std::cout << "x = " << x << " y = " << y << "\n";
}

----------------------------------------------------

int& int ref diye okunuyor.


int g = 98;
int func()
{
	return g;
}

int& foo(int &r) foo(x) ile çağrılsaydı x i bir artırıp geri döndürecekti.
{	
	++r;
	return r;
}

int main()
{
	std::cout << "g = " << x << "\n";
	++func(); // g yi 1 artırır.
	std::cout << "g = " << x << "\n";
}


----------------------------

elemanları referans olan dizi yok.
elemanları pointer olan diziler vardı.

------------------------------------------------------------------

BIR SONRAKİ DERS

int main()
{
	int x = 10;
	int& r1 = x; // r1, x e referans
	int& r2 = r1;// r2, r1 e referans
	int& r3 = r2;// ...
	++r1;
	++r2;
	++r3;
	// x = 13 yapar
}

-------------------------

int& foo(int& r)
{
	return x;
}

int main()
{
	int a = 10;
	int& r = foo(a);
	r = 45;
	// a 45 oldu artık.
}

--------------------------

int main()
{
	int x = 10;
	int* ptr{ &x };
	int& r{ *ptr };
	++r;
	// x = 11 oldu
}

--------------------------

burada bir örnek daha yaptı ama yazmayacağım.
for(auto val : a)
{
	// a her seferinde dizi elemanı oluyor. Bu biraz foreach gibi.
}

-------------------------------
-------------------------------
-------------------------------

EXPRESSION - ifade
13
x
x + 6   hepsi ifade


'A' bunun türü C de int, C++ ta char.

char c = 13;
+c; bu inttir. çünkü integral promotion olur. + operatörü sayesinde.

-----------------------------------------------

int&r; r nin türü ----> int&

====================================================================
====================================================================
====================================================================

DEĞER KATEGORILERI
--------------------
C de L ve R value var
C++ ta L, PR , X value var.

				  KESİŞİMLERİ
GLVALUE	|--------------------|------------------|-----------------------|  RVALUE
	|	LVALUE       |      XVALUE	|	PRVALUE		|
	|		     |			|			|
	|--------------------|------------------|-----------------------|


LEFT VALUE = LOCATORS VALUE
PR VALUE = PURE R VALUE
X VALUE = EXPIRING VALUE
-----------------------------
PRVALUE + XVALUE = RVALUE
LVALUE + XVALUE = GLVALUE
---------------------------------------

PR VALUE = NESNE GÖSTERMEYEN İFADE DEMEK
X VALUE = NESNE GÖSTEREN İFADE AMA HAYATI BİTMEK ÜZERE OLAN NESNE.

TEKRAR
int& r; r nin türü intref

				C			C++
-----------------|------------------------------------------
++x		 |		R			L
--x		 |		R			L
(x,y)		 |		R			L
a > 5 ? x : y	 |		R			L
(x = y)		 |		R			L


SONUC:
LVALUE REFERANS BİR LVALUE EXPRESSİONA BAĞLANMAK ZORUNDA. RVALUE EXPRESSİONA BAĞLANAMAZ.
SENTAKS HATASI OLUR.

int& r = 10; // sentaks hatası.

int main()
{
	int x = 10;
	int& r = x++; sentaks hatası
	int& r = ++x; burada sorun yok. Çünkü ++x lvalue expr.
}

Aynı şekilde fonksiyon çağrılarıda böyle çalışıyor

-----------------------------------

int main()
{
	int x = 10;
	int y = 20;
	int* ptr = &x;

	int*& r = ptr; // r, int * türden bir nesneye bağlanıyor.
	r = &y;
	++* r;
	// y = 21 oldu burada
}

int* &r; r burada int * türünden bir nesneye referans olan r.

============================================================================
============================================================================
============================================================================

NULL POINTER.
-------------
C++ ta object like macro yada function like macrolar çok kullanılmıyor.
Dezavantajları var.Kodlama hatası riski yüksek.

C++ ta nullptr olarak kullanılır.bu bir keyword.
Bunun türü nullptr_t.Pointer türlerine dönüşüyor ama tamsayı türlerine dönüşmüyor.

Modern C++ a kadar, int *p = 0; olarak ilk değeri verilirdi.

-------------------------------------------------------------------------


int x = 10;
double &r = x ; double ref türden nesne int türden nesneye bağlanmaya çalışılmış. sentaks hatası.


==========================================================================
==========================================================================
==========================================================================

REFERANSLAR VE CONST SEMANTİĞİ.

const correctness aşırı önemli.

int main()
{
	int x = 10;

	const int& r = x; // const reference
	int const & r = x; // const reference. aynısı. Pointerlar gibi.
	int& const r = x; // r zaten doğuştan const.bir referans başka bir nesnenin yerine geçemiyor.
						// ilk değer verirken hangi nesneye bind edilmişse ondan devam etmeliyiz.rebind edilemez.

}


r, dereference edilmiş bir pointer gibi davranıyor.

---------------------------------------------------------------

int a[5];
int (*p)[5] = &a;

Biraz farklı şekilde referans semantiği ile aşağıdaki gibi ifade ediyoruz.

int a[5] = { 1,2,3,4,5 };
int(&ra)[5] = a;


----------------------------------------------------------


FONKSIYONA NASIL GÖNDERECEĞİZ

#include <iostream>

void func(int(&r)[5]) 
{
	for (int i = 0; i < 5; i++)
	{
		r[i] *= 2;
	}
}

int main()
{
	int a[5] = { 1,2,3,4,5 };
	func(a);
	for (int val : a)
	{
		std::cout << val << "\n";
	}
}

-------------------------------------------------------------

ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!

	int a[5];
	int(&r)[5] = a;   
					  
-------------------------------------------------------------

OTOMOTİK ÖMÜRLÜ BİR NESNEYİ REFERANSLA DÖNMEMELİYİZ.

int& foo(int x)
{
	//...

	return x;   //hata.Hatanın içeriği otomotik ömürlü bir nesnenin adresini return etme hatası ile aynı.
}
BURASIDA UNDEFINED BEHAVIOR.




*/

#include <iostream>

void func(int(*&r)[5])
{
	for (int i = 0; i < 5; i++)
	{
		std::cout << (*r)[i] << "\n";
	}
}



int main()
{	
	
	int a[5]{ 1,2,3,4,5 };
	int(*p)[5]{ &a };
	func(p);



}
