/*

Meeting Id : 895 3331 1835
Password : 111222



C nin eski standartlarında implicit int var

foo()
{
} burası ok


c++ ta sentaks hatası.

--------------------------


c de fonksiyon adını yazınca, olmasa bile hata vermiyordu.
Eskiden kalma. implicit function decleration.zaten kullanmıyoruz.

C++ ta sentaks hatası.

----------------------------


old style funct. decleration

garip bir kural.bura eski kullanılmıyor artık.

int func(a,b,c) // int yazmadı
double a,b;
{

}

C++ ta sentaks hatası.

----------------------------


int foo(int x)
{

}

C de
boş bırakılırsa sadece uyarı gelir.ama UNDEFINED BEHAVIOR.

C++ ta sentaks hatası

------------------------------

C de aşağıdakiler farklı anlamda
void func();
void foo(void);

C++ ta ikisi arasında anlam farkı yok.
parametre değişkeni yok demek ikiside.

-------------------------------------

C99 dan önce bir statemant tan sonra bir değişken tanımlanamıyordu
yani kodun aşağısında bir değişken tanımlamak yoktu.


C++ ta bu mümkün.

----------------------------------------

C nin eski c99 dan öncesinde
for(int i = 0 ; ;)   bu hata

C++ ta ise hata değil.

-----------------------------------------

C de geçerli aşağısı
for(int i = 0;;)
{
	int i; //derleyici burayı farklı bir blok olarak yorumluyor.
}		// bunu değişkeni tanımlarsa yapıyor.

C++ ta GEÇERSİZ

-----------------------

_Bool c de var.bu keyword
hatta stdbool inclu değilirse

buradaki bool ise macro
bool x = true
bool x = false yapılabiliyor.
ama insanlar int kullanıyor.bool çok kullanılan bir konvensiyon değil.
çakma bool


_Bool C++ ta hata
C++ taki bool farklı.
C++ ta bool türü dilin basic türü
bool x = true;
x = false; bu bool doğrudan dilin içinde geliyor.

NOT
static ömürlü global ve static ömürlü yerel bool değişkenler
hayata FALSE ile başlar.
int x = 12;
bool b = 12; ise eğer burası nonzero yani TRUE olur.
Eğer 0 olsaydı FALSE olacaktı.


Pointerlardan da bool türüne dönüşüm var.

int x = 10;
int *p = &x;

bool b = p;  nesne adresi olduğu için True olacak
nullptr olsaydı False olacaktı.

Bool türüne otomotik dönüşüm var.

Bool dan diğer türlere de otomotik dönüşüm var.

bool flag = true;
int x = flag;   x burada 1 dir.

false olsaydı -> 0 a dönüşecekti.


Modern C++ ta bazı kurallar geldi.
Modern ++ öncesinde

bool flag = false;
++flag; sentaks hatası değildi.


Modern ++ sonrası
++flag; sentaks hatası

bool türünü pointera atamak yanlış.sentaks hatası.



------------------------------------

C dilinde

'A' karakter sabiti yada literali
bunun türü int

C++ dilinde
türü char.

----------------------------------------

EN KRİTİK YER
TÜR DÖNÜŞÜM KURALLARI
IMPLICIT TYPE CONVERSION

C de
farklı ptr türleri ve farklı tamsayı türleri arası
implicit type conversion var.


C++ ta
BU ÇOK NET SENTAKS HATASI.

DETAYLI yazmayacağım.

--------------------------------------

Const ile ilgili farklılıklar

C de ilk değer vermeden const nesne yaratılabilir.
garbage value de olur , ama tanımlanabilir.

C++ ta sentaks hatası
ilk değer vermek şart.
global değişken olsa bile sentaks hatası.

const int *ptr; hata değil.
int * const ptr; burası hata.

Yani kendisi const olan nesneleri initialize etmemek sentaks hatası.


-------------------------------------

2. Const farklılığı

C de

int x = 20
const int x = 20
bu durumlarda external linkage.static gelirse internal linkage a ait olur.


C++ ta
const global nesneler internal linkage dır.

-------------------------------------

C de
const int x = 10;
int a[x]; c de hata

C++ ta hata değil.
const int x = 10;
int a[x]; c++ ta hata değil.

switch case de de kullanılır. case den sonra sabit gelmeli
ama const türünden değişken konulabilir.

-----------------------------------------


C de const türden, türe e implicit cast var

C++ ta const türden, başka bir türe implicit dönüşüm sentaks hatası.
Operatörü var.const_Cast operatörü

-------------------------------------------


C de malloc u cast etmeden pointera atamak hata değil

C++ ta hata.

int *p = malloc(n * sizeof(int)); burası C++ ta hata, C de hata yok.
malloc void * çeviriyor buarada.


----------------------------------------------

C++ taglar türün kendisini belimlemiyor.

C de bir tür eş ismi yada struct data union nec enum color
gibi uzun uzun yazmak gerekiyor.

struct Data{
int a,b,c;
};

union Nec{
	unsigned int x;
	char str[4];
};

enum color{
	red,black,gray
};

struct data x;
enum color a;
union Nec c;



C++ ta çok büyük fark var.
C++ ta etiket ismi tür ismi değil.

Hepsi legal

data mydata;
nec nec;
color mycolor;


------------------------------

char dizilerdeki farklılık

struct C de boş olamaz
struct C++ ta boş olabilir.

------------------------------


auto C de artık kullanılmıyor.
otomotik ömürlü demek

C++ taki anlamı tamamen farklı.

---------------------------------

char str[4] = "umut"; bu C de ok ama C++ ta sentaks hatası.


*/
