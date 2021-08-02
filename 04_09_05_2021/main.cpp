/*

REFERANSLARDA KALMIŞTIK

ARTIK NULL MACROSU YOK. :d

nullptr keyword kullanılacak
nullptr_t türden bir sabit ve anahtar sözcük.
pointer türlere dönüşüm var bunlardan.



LVALUE REFERENCES
RVALUE REFERENCES LAR VARDI.

SOL TARAF REFERANSLARI SOL TARAF İFADELERİNE BAĞLANIYOR.
SAĞ TARAF REFERANSLARI İSE SAĞ TARAF İFADELERİNE BAĞLANIYORDU.


DATA TYPE VALUE CATEGORİ GÖRÜLDÜ.

C++ TA    L - PR - X  var.


---------------------------------------

T& foo()
{

}

foo() bu ifade bir lvalue expression.
foo() = 12 yapılabilir.

-------------

T foo();

foo() bu ise PR expression.

----------------

BIRAZ GEYİK

----------------

getter setter/mutater functionlar.
const varsa getter.
yoksa setter demek istiyor.

bazı fonksyionlar
const T& foo();  salt okuma amaçlı erişmek için bu.

C de
const T* idi

const int ten int e C de warning verir ama implicit dönüşüm var.
C++ TA SENTAKS HATASI.

int ten ise const int e herhangibir hata yok.

------------
buraya bak.
referans semantiğinde de var.

const int& foo();

int main()
{
	foo();
}


--------------------

ÖNEMLİ UYARI

double dval = 1.2;
int &r = dval;          referansın türü int& , sağ tarafa double.Sentaks hatası
int &r2 = 10;		burası da sentaks hatası. biri l diğeri pr val.

Const olunca herşey değişiyor !!!!!!!!!!!!!

double dval = 1.2;
const int &r = dval;
//
	derleyici aşağıdakini yapar.
	int temp_val{dval};
	const int &r = temp_val;
	referans derleyicinin oluşturduğu temp değişkenin refere etti.Onun yerne geçti
//

const int& r2 = 10;
//
	yine
	int temp_val{10};
	cosnt int &r = temp_val;
//


-------------------------- -


unsigned long x = 0;
const int& r1 = x;
const int& r2 = x;

x++

cout r1 ve r2;

r1 ve r2 == = > 0

--------------------------------

void func(T&);

bu fonksiyon Lvalue expr ile çağrılır.


void func(const T&);

bu fonksiyon Lvalue hemde prvalue expr ile çağrılır.
const çünkü yukarıdaki gibi temp value yaratıp ona eşitliyor.


-------------------------------- -


REFERANS SEMANTİĞİ VS POINTER SEMANTİĞİ.
----------------------------------------

- pointerlar default init edilebilir. int* p; ok
- referans default init edilemez. int& r; hata

- pointerlar kendisi const olmadığı sürece farklı farklı nesneleri gösterirler
- referanslar sadece bir nesneye bind olur hayatı boyunca çünkü default olarak const.
yani rebind edilemiyorlar.
int& r = x;
r = y;  bu demek x e y yi atamak demek : D

2 - 3 ay sonra std : reference_wrapper sınıfı var.Bu sınıf bir referansı rebind ettiriyor.

- NULL pointer diye bir kavram var.
- NULL reference diye bir kavram yok.

dangling pointer e girdi ufaktan
NULL ptr gönderildiği functionlar.


referanslarda ya bir nesne return et ya da null reference return et olayı YOK.

2017 standartlarında bir sınıf geldi.

std::optional == = > bir değeri olabilir olmayadabilir.
std::optional<T>    fonksiyonun return değerini böyle yapacağız.
boşsa bir değer döndü, değilse dönmedi.


REFERANS SEMANTİĞİNDE BU YOK.
YA BANA BİR NESNE GÖNDER YA DA GÖNDERME.BU REFER.SEMANTİĞİNDE YOK.

anti pattern = Hatalı bir çözüm ama çok kullanılıyor demek.

BEST PRACTICE LER
C++ Core Guidelies
Projeyi başlatan Bjarne && Herb Sutter

cppcon isimli konferanslar var.
Her yıl düzenleniyor.
Buradakiler baya öğretici.
Başkalarıda var.
cppconda back to basics altından izlenebilir.


- POINTER DİZİSİ OLUR.	   int* p[10]; var
- REFERANS DİZİSİ OLUR	   int& p[10]; olmaz.


- Referansları containerlarda da tutamam.ileride görülecek
- Pointer tutulabilir.ileride...


- Reference to Reference yok.
  Type deduction haricinde yok.
- Pointer to Pointer var.


NOT : BURASI ÖNEMLİ
POINTER TO REF YOK. REF TO POINTER VAR.

int x = 10;

int*& r = p;		P BIR POINTER.BURASI OK.

int *ptr = &r;		BURADA PTR X'İN ADRESİNE EŞİTLENİYOR.POINTER TO REF DEĞİL BU.
int *ptr = r;		SENTAKS HATASI.ÇÜNKÜ POINTER TO REF YOK.

int*& r = p;		BURASIDA OK.YAPILMIŞTI BU ÖRNEK.

diğer örnek.
int x = 10;
int* p{ &x };
int** ptr = &p;
int**& r{ ptr };
++** r;
x = 11 oldu demek


HATIRLATMA

int a[5] = { 1,2,3,4,5 };
int(&r)[5] = a;

1.24
C de array decay uygulanmayan 2 yer.
1 sizeof operatörünün operandı
2 & operatörünün operandı olması.


HEMEN HERŞEYİ ÖĞRENMEYECEĞİZ.KURS İLERLEDİKÇE ÖĞRENECEĞİZ.

----------------------------------------------------

MODERN C++ TA DİLE EKLENEN SAĞ TARAF REFERANSLARI VAR.
2 TANE AMACI VAR BUNUN.

MOVE SEMANTİCS(TAŞIMA SEMANTİĞİ) HOWARD HINNANT
PERFECT FORWARDING

BU İKİ ÖNERİYİ HAYATA GEÇİRMEK İÇİN SAĞ TARAF REFERANSLARI / R VALUE REFERENCES DİLE EKLENİYOR.
BUNLARIN HEPSİ İLERİDE GÖRÜLECEK.
SAĞ TARAF REFERANSLARINDAN BİRAZ BAHSEDİLECEK AMA ASIL TANIŞMA, TAŞIMA SEMANTİĞİNE GEÇİNCE.
PERFECT FORWARDING İSE GENERİC PROGRAMLAMA İLE ALAKALI.

------------------------------------------------------------ -
------------------------------------------------------------ -

ÇOOOOK ÖNEMLİ !!!!!!!!!
SOL TARAF DECLERATOR ÜNDE & KULLANILIYOR
SAĞ TARAF DECLERATOR ÜNDE && KULLANILIYOR


int x = 10;
int& r = x; 	sol taraf referansıla sol taraf değeri.const dışında.cosnt olunca temp value yaratıp ona eşitliyordu.
int&& y = x; 	sağ taraf referansınada sağ taraf değeri verilebilir.Burada sentaks hatası var.x + 5 olmalıydı.o örnek te aşağıda.
Çünkü sol taraf değerini sağ taraf referansına bağlayamayız.

Sağ taraf değerinide r value expression ile initialize etmek mecburi.
int&& y = x + 5; burada sorun yok çünkü x + 5 rvalue expression

Soru - cevap
r nin değer kategorisi nedir ? L value expr.
y nin değer kategorisi nedir ? L value expr.


BURASI ÇOK ÖNEMLİ
-------------------------------------------------------------------------------- -

değer kategorisi		referans kategorisi					Veri türü
------------------------------------------------------------------------------------------------ -
r--->lvalue expression		Lvalue reference / sol taraf referansı			int&
y--->lvalue expression		Rvalue reference / sağ taraf referansı			int&&


y nin sağ taraf referansı olması, onun r value expression olduğunu göstermez.
Bu çok karıştırılıyor.

Aşağıdakiler doğru formdalar.
------------------------------
int x = 10;
int& r = x;
int&& y = x + 5;



void func(T&&);
böyle fonksiyonların tek varlık sebebi taşıma semantiği.


----------------------------------------------------------------
----------------------------------------------------------------


TYPE DEDUCTION - TÜR ÇIKARIMI
---------------------------- -
Tamamen derleme zamanıyla ilgili.Runtime ile ilgili değil.
Değişkenin türünü açıkça yazmasakta, derleyici değişkenin türünü compile time da
anlıyor.

mesela
auto ile type deduction
decltype ile ..
decltype(auto)
template
lambda expression

auto = tür yazmak yerine bunu yazıyoruz ve sonrada değişkenin adını yazıyoruz.
ve buna değer vermekte zorunlu !!!!

------------------------------------

Bunlar C de. :D
not : auto x = 1.0; burada x double
auto x = 1; burada x int

------------------------------------

//placeholder
auto x = 10; // x int olacak bu durumda.

akronim ör : NATO TC ODR RAII CRTP AAA
Her bir harf bir kelimeye denk gelen keilmeler.
mesela AAA = Almost Always Auto.

auto koymak performansa etki etmiyor çünkü compile time da belli oluyor.
Derleme zamanını da çok çok az miktarda uzatır.

auto yu kullanmayan da var kullananda var.Doğru kullanmayan öğrenmek lazım.


mesela

const char* (*fp(const char* (*fa)(const char*, const char*), const char* (*fb)(const char*, const char*)))(const char*, const char*)

bunu yazmak zaman alır hemde yazamayacak birsürü insan var.auto bunun türünü elde ediyoruz.

------------------------------------------------
1. TÜR ÇIKARIM ARACI.

AUTO ÇIKARIMI NASIL YAPILIR
----------------------------
1. KULLANIM ŞEKLİ. auto nun yanında & yok.
Yani türü auto & ile elde etmediğimiz durumlar


1 int a = 10;
auto x = a;  burada x in türü in olur.

2 int a[10]{};
auto x = a;	x'in türü int *

3 cosnt int a[] = { 1,2,3 };
auto x = a;  x in türü const int*

4 auto a = "Ali";
auto x = a;    x in türü const char*, C de char* dı.

5 const int x = 10;
auto y = x;         DİKKAT!!burada y nin türü int.
const luk düşüyor.

6 int x = 10;
int& r = x;
auto y = r;    DİKKAT !!burada y nin türü int.
				referanslık düşüyor.


7 int x = 10;
const int& r = x;
auto y = r;          Burada hem referanslık hemde const luk düşüyor.Dizilerde const luk düşmüyordu.
y nin türü int.


8 int func(int);
auto f = &func;
int(*f)(int);

9 ÇOK ÖNEMLİ ÖRNEK.
BUNU GITHUB ÖRNEKLERINDEN ALDIM.

	int x = 10;
	int y = 20;
	const int *p = &x;
	int *const cp = &x;

	auto a = p; // bu const int *a = p; burada pointer const değil.bu sebeple tür çıkarırken const a dokunmuyor.
	auto b = cp; // int *b = cp; burada pointerın kendisi const. auto const luk gitti.	

	a = &y; // ok
	*a = 20; // HATA.ok değil
	b = &y;  // ok
	*b = 56; // ok



---------------------------------------------------------------- -
---------------------------------------------------------------- -
2. KULLANIM ŞEKLİ. auto nun yanında & var.
Yani türü auto & ile elde ettiğimiz durumlar


auto & x = burada ne geelirse gelsin onun ref türünden olacak.

int x = 10;
auto& r = x;   int ref / int&

auto & r = 20;   SENTAKS HATASI!!!!!!!!!!!!!!  20 PR value


const int x = 10;
auto& r = x;      Burada const luk düşmüyor.türü const int ref.

auto nun yanına & gelince constluk düşmedi.


int a[]{ 1,2,3,4,5 };
auto& x = a;              x in türü int(&)[5]
yani aslında int(&x)[5] = a;


const int a[]{ 1,2,3,4,5 }; olsaydı
auto& x = a; burada const luk yine düşmeyecekti.
yani aslında const int(&x)[5] = a;


auto& x = "ezgi";   const char[5] // array decay olmuyor.auto yanında & var çünkü
yani const char(&x)[5] = "ezgi"; oldu.


int func(int);

auto x = &func;
int(&x)(int) = &func; oluyor.Buna function reference deniyor.


-------------------------------------------------------------------------- -
-------------------------------------------------------------------------- -

BU BÖLÜM BAYA KARMAŞIK.
TAMAMLANSIN DİYE ANLATIYOR.İLERİDE ÖĞRENİLECEK.

3. DURUM.Declerator olarak && kullanılacak.

int x{};
auto&& r = x;  // && normalde sağ taraf referans değeri.sağ taraf değerine l value exp. ile değer vermek sentaks hatası olurdu.Ama hata yok.
		// Bu durumda auto ya karşılık gelen türün ne olduğu, ilk değer veren ifadenin değer kategorisine bağlı.


bu şekilde oluşturulan referanslara ileride görülecek
Universal / forwarding Reference deniyor.

ÇOOK ÖNEMLİ !!!!!!!!!
-------------------- -
ilk değer veren ifadenin değer kategorisine bağlı demiştik.


a - auto && r = x; ise

ilk değer veren(x yani) lvalue exp ise auto karşılığı olan tür sol taraf referansı.
r ye karşılık gelen değil auto ya karışılık gelen.r ye henüz birşey demedik.

Bu durumda auto ya karşılık gelen tür ==> int&
derleyici auto yerine int& kodu
int&&& r

======================================================================================================
======================================================================================================

BU DURUMDA UYGULANAN KURALLAR VAR.BUNLARA REFERENCE COLLAPSING DENİYOR.
REFERENCE COLLAPSİNG
--------------------
C++ TA REFERANSA REFERANS OLMAZ ANCAK TÜR ÇIKARIMI YAPILAN BAĞLAMLARDA / CONTEXLERDE TÜR ÇIKARIMI SONUCUNDA
REFERANSA REFERANS OLUŞABİLMEKTEDİR.BU DURUMDA DERLEYİCİ REFERENCE COLLAPSİNG DENEN KURALLARI UYGULAR.

REFERANS	REFERANS	SONUC REFERANS
--------------------------------------
&&			&				&
&			&				&
&			&&				&
&&			&&				&&

(&= SOL TARAF REFERANSI, && = SAĞ TARAFA REFERANSI)

======================================================================================================
======================================================================================================

int&&& r == = > burada kalmıştık
sol taraf referansı(&) ve sağ taraf referansı(&&) == = sonuc sol taraf referansı(&)


b - auto && r = x + 5; ise

Derleyici auto yerine int&& koydu. int && &&  -> int && 
int &&r = x + 5;

Pratik Kural
------------
ilk değer veren rvalue exp ise auto karşılığı olan tür türün kendisi.
Bu durumda auto ya karşılık gelen tür kendisi yani ==> int

Derleyici auto yerine int koydu
int&& r = x + 5;
bu durumda r sağ taraf referansı oldu


BASİT KURAL
auto&& r = x; ise r sol taraf referansı
auto&& r = 10; ise r  sağ taraf referansı


Normalde C++ türünde referansa referans olmaz.Ancak tür çıkarımı yapılan bağlamlarda
tür çıkarımı sonucunda referansa referans oluşabilmektedir.
Bu durumda derleyici referance collapsing denen kuralları uygular.Kurallarıda yukarıda yazdık zaten.


--------------------------------------------------------------
--------------------------------------------------------------

2. TÜR ÇIKARIM ARACI

DECLTYPE SPECIFIER
------------------

Buna operatörde diyorlar.
auto dan farklı biraz.Ortak özellikleri tür çıkarımı yapıyor olması.
Başka yerlerde başka amaçlarda da kullanılacak.

int x = 44;
decyltype(x); Bunu tür gereken heryerde kullanabilirim

decyltype(x) a;
int i ne şekilde kullanırsam decltype ı da öyle kullanırım.

decltype(x) func(); func geri dönüş değeri şeklinde kullnabilirim.

--------------------------------

1 decltype operandı isim formnundaysa

decltype(x)
decltype(ptr->x)
decltype(ptr.x)

burada uygulananlar aşağıdakilerle farklı


2 decltype operandı isim formnundaysa olmayan ifadeyse.

decltype(x + 5)
decltype(*ptr)
decltype((x))


--------------------------------------------

1 - İsim formunda ise
Bu isim hangi türden declere edildiyse bizim elde ettiğimizde o tür.

int x = 56;
int& r = x;
int a[10]{};
const int b[3]{};
const int y{ 12 };

decltype(x) ==> int türü
decltype(r) ==> int& türü
decltype(a) ==> int[10] türü.NOT: int[] bir incomplete type.
decltype(b) ==> const int[3] türü
decltype(y) ==> const int türü
decltype(r) t; ==> sentaks hatası.ilk değer verilmemiş.
decltype(a) k; ==> sentaks hatası yok. int k[10] demek;
decltype(a) c[20] ==> tür[10] olacak.c[20][10].

const int x = 56;
decltype(x) y; // hatalı çünkü const nesneye ilk değer verme şartı var.



2 - İsim formunda ifade değilse

Bu durumda decltype karşılığı elde edilen tür parantez içindeki ifadenin value kategorisine bağlı.

a - eğer ifade pr value expr ise, decltype yerine gelen tür 	T türü
b - eğer ifade L value exp.ise decltype yerine geşen tür 	T & türü
c - eğer ifade X value exp.ise decltype yerine geşen tür 	T && türü


int x = 10;
int y = 20;
decltype(x + 5) y; ==> int y;

int* ptr = &x;
decltype(*ptr) z = y; ==> int& z = y;


MÜLAKAT SORUSU
int x = 10;
int y = 20;

decltype(x) a = y; ==> int a = y;
decltype((x)) b = y; ==> int& b = y;


int x = 10;
int y = 20;
decltype(++x) z = y;

++z; ==> ++x bir lvalue expr.Decltype bunu int& olarak belirtir. int& z = y; z++ = 21 olur
21

BURADAN SÜREKLİ MÜLAKAT SORUSU GELİYOR.

------------------------------------------------------------

Peki x kaç ?
x halen 10

decltype unevaluated contex oluşturuyor. sizeof gibi. & gibi.
burada ++x için compiler işlem kodu üretmiyor.birkaç yerde daha var unevaluated contex.
mesela auto s = typeid(x++).name()


============================================================== =

Modern C++ 2011 öncesinde tür çıkarımı çok zayıftı.
auto decltype yoktu.Sadece template lar sayesinde çıkarım vardı.
Yeni standartlarda da sürekli genişliyor.


Güzel bir soru daha

int x = 10;
auto p = &x;
auto* ptr = &x;

Hem p hemde ptr nin türü int*
alttaki auto daki* tokenı dikkate alınmıyor.Yaygın değil.

----------------------------------------------------------------------------


ÖNÜMÜZDEKİ KONULAR.
------------------ -

cosntexpr.Modern C++ ta geldi.En önemli keywordlerden biri.
Default Argument
Function Overloading.Bu cidden çok önemli.

------------------------------------------------------------

const int x = 10;
cosnt int y = func();

int a[x] = { 0 }; // dizi boyutu const cosntant expr.bu yüzden sabit ifadesi olarak burada kullanılabilir.
int b[y] = { 0 }; // burada y bir sabit ifadesi şeklinde initialize edilmemiş.Burada dizi boyutu olarak verilemez.Sentaks hatası.

*/

#include <istream>

int main()
{

	
	

}
