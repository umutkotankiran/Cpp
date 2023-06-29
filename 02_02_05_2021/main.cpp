/*

Genel tekrar
isim arama
iki isim bulunursa C den farklı ambigious hatası

C++ ta

1. isim arama bir sırayla yapılır.
2. isim arama bir kez yapılır ve bulunduğunda da arama devam etmez.
int printf = 0;
printf++; bu geçerli.

ama
printf("ali"); geçersiz isim arama kuralına göre kendi scope unda
arayacak ve 0 bulacak printf i.



3. burada artık context control başlar.





4. Access control başlar.(C de yok)
Belirli isimlerin belirli kodlar tarafından kulanılması yasak.
class larda göreceğiz.



"Ali" bu char[4] türden dizi.Değiştirmek C de UB. C++ ta zaten bu const
string literali.C++ ta sentaks hatası.


----------------------------------------------------------------
----------------------------------------------------------------
initialize
int x = 5;

assign
x = 10;

initialization is not an assigment.

int x = 5; burada isim arama yok.zaten ne olduğunu söylüyor.
ama x = 10 da arama var

-----------------

C++ ta bir değişkeni initialize etmenin çok farklı yöntemi var.
2 tanesi C ile ortak.
Diğerleri ortak değil.

int x = 5; copy initialization deniyor.
int y; default initialization.
static ömürlüler için int x; bu zero initialize dır
boollar false ile, pointerlar NULL ile değişkenler 0 ile başlatılıyor.
C++ ta NULL pointer = nullptr.
int x; burası otomotik ömürlü ise indetermined value olarak başlar
ve kullanmak UB dir.

Artık bazı şeyler değişecek.
C den farklı olarak C++ ta
otomotik ömürlü bir değişkene herzaman bir ilk değer vermeye çalışmalıyız.
eğer çok mümkün değilse verilmeden yazılır.ama yapılabiliyorsa kesinlikle
ilk değer verilmeli.

scope leakage
değişkeni kulanıldığı yere yakın yerde tanımlanmalı.
amaç değişkenin kullanıldığı yerde tanımlamak.

C++ ta bazı araçlar var scope leakage ı engellemek için.
sonra görülecek.

BURASI C DE YOK
C++ ta direct initialization

int x(10);

Modern cpp(cpp11 ve sonrası) te {} küme parantezleriyle ilk değer verilebiliyor.
buna brace init. veya uniform init deniyor.

int x{10}; // direct list init deniyor.

scott meyers komitede
	effective c++

double dval = 3.987; // türe dikkat
int ival {dval}; uniform/brace init.modern c++ ta bu sentaks hatası.
narrowing conversion / daraltıcı dönüşüm

avantajı most vexing parse ı yok ediyor.
ve daraltıcı dönüşümü engelliyor.

int ival(10); direct init.
int ival{10}; direct list init/ uniform init. / brace init.

double dval = 3.456;
1 - int ival = dval;
2 - int ival(dval);
3 - int ival{dval};

1 ve 2 de veri kaybı var ama geçerli.
3. geçersiz


-------------------

Value init.

int x{}; içi boş küme.
otomotik veya static olması farketmez x in değeri 0 dır.
bool lar false
pointerlar nullptr ile başlar.



Hoca terciholarak
brace init tercih ediyor.

int x{};
int y{10};

-------

int x = 10;
int y(10);
int z{10};
int t{}; hepsi geçerli ama aşağıdaki.

int ival(); bu değişken tanımı değil fonksiyon bildirimi.
geri dönüş değeri türü int olan parametre değişkeni olmayan ismi ival
olan bir fonksiyon bildirim.

c++ ta operator overloading çok önemli.

C++ ta var ama ama C de yok
NAMESPACE ---> İSİMALANI.

namespace tanımı
namespace neco {
	int x;
}

:: scope resolution operator
::x operand olan ismi global namespace de ara
neco::x olsaydı. neco namespace içindeki x demek. Bunlara qualified name
denir. direkt x denseydi unqualified. Niteleyerek kullanmak daha iyi.
using namespace std; yazmaya her zaman gerek yok.iyi değil zaten.

Bu C dili
file scope, func scope, func prot. scope, block scope
aynı scope lardaki isimler tek olmalı.bir alt veya bir üst blokta
farklı olabilir zaten buna name hiding deniyor.

C++ dili
namespace scope(file ı kapsıyor)
block scope
func scope,
func prot. scope
class scope


if in parantezi içinde değişken tanımlanabiliyor.
if(int x = func())
{
	x++;
}
else
	x--;  hata yok.




===================================================================
===================================================================

REFERANS SEMANTİĞİ
------------------

GİRİLECEK.


-------------------

C++ ta fazladan storage class var.

not : C deki kütüphaneleri cpp ten include için başına c koyup
sonuna h koymuyoruz.

#include <cstdio> gibi.


----------------------

TEKRAR
------
int x; Default İnit.Refler hata, constlar hata
int y{}; Value init.burada y zero initialize edilir.y = 0 yani :D
int z{ 20 }; Uniform / Brace
int t(12); Direct init.
int k = 23; Copy init.
int x(); Function Decleration

Mülakat sorusu
auto x{ 10 }; x in türü int

auto x = { 10 };  buradaki tür Initializer list deniyor.Daha görülmedi.
std::initializer_list<int>

auto z{ 10,20 }; c++17 de artık sentaks hatası
auto z = { 10,20 }; init list oldu.Geçerli.





*/
