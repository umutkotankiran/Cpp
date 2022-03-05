/*
NOTLAR
-------

classlar nedir
nasıl tanımlanır
memberlar
erişim kontrolleri
global/free functions
member functions
static veri elemanları daha sonra değinilecek
nonstatic veri elemanları ve üye fonksiyonlarına değinildi.

------------------------------------

Bu definition
class myclass{
	int x;
};

Bu decleration.Burası Bir incomplete type.
class Myclass;

Burada Geçen ders yaptıklarımızı sözlü olarak ifade etti hoca.


--------------------------------------------------------
Hatırlatma
Nonstatic elemanlar sınıfın sizeof değerini artırıyordu.
static artırmıyor.

Bir class ın public interface inde onun neler yapabileceği olacak.

bu class bir kavram, bundan üretilen nesnelere instance deniyor.

Şimdi Header file a geldik. Mul. inc. guard. kısaca bilmeyenlere açıklandı.

Header da class yaratıldı. header file a yazılanları oraya yazıyorum.
date.h  --> BURADAN DEVAM.
Assembly seviyesinde global fonksiyonlar ile member functionlar arasında pek fark yok.

----------------------------------

class Date{
	public:
	void set(int d, int m, int y);
};

void in 3 parametresi yok. 1 tanede gizli parametresi var.
4 parametresi var.

Date mydate;
mydate.set(12,23,1978); set fonksiyonuna bu değerleri göndermiş oldum. burada görünmeyen parametre mydate class adresi.

Date xdate;
xdate.set(1,1,1997); ayı şekilde görünmeyen parametre xdate class adresi.

----------------------------------

not : member func lar redecleration edilemez ama overload var.

NOT!!!!!!!!!!!! ÖNEMLİ!!!!!
class Date{
	public:
	void set(int d, int m, int y)
	{
		// diğer dillerde bu şekilde olabilir. C++ tada bu destek var. 
		// Bu modele INLINE model deniyor.Sonra görülecek.
	}
};

------------------------------------

şimdi date.cpp içinden function definition yapılıyor.

void Date::set(int d, int m, int y)
{

}

----------------------------------------------------
İsim nasıl aranırdı ?
Global func larda isim arama, kendisi, onu kapsayan, onuda kapsayan blok, ... namespace e bakılırdı

----------------------------------------------------
MEMBER FUNCTIONDA FARKLI !
KENDI SCOPE, SONRA BIR SONRAKI ... CLASS SCOPE(BU YENİ) A BAKILIR. EN SON GLOBAL NAMESPACE
CLASS SCOPE HEADER IÇINDEKI DECLERATION ASLINDA.
----------------------------------------------------

Altta şu çalışıyor.
O gizli görünmeyen pointer parametresi vardı.Gizli class pointer parametresi.(implicit object parameter deniyor)
aramada -> operatörü ile class scope adresine gidilir.

Myclass *p olsun
mm aransın mesela

p->mm yazıp bulmaya çalışır.

---------------------------
class Nec
{
public:
	void foo();
private:
	int x;
};

int x = 87;

void Nec::foo()
{
	int x{};	ÖNEMLİ !!!
	x = 10;		bu x local x,  
				Eğer local scopeta Bulamazsa class scope a bakacak. 
				Bulamazsa Namespace scope
		
	::x			Bu ise Namespace yani global x

	Nec::x = x + ::x;  Sınıfın veri elemanı x = local x + global x :D:D:D
}						Pek mantıklı değil ama olsun.Kuralları öğretiyor.


--------------------------------------------

Şirketten şirkete değişir ama class data member lara bunların member olduğunu vurgulamak
için m_... ile isim devam edilebilir. veya x_ diyen var. m.. olabilir

void Date::set(int d, int m, int y)
{
	d = md ;
	m = mm;
	y = my;   bunlar class scope tan bulunur.
}

Yukarıdaki fonksiyon global olsaydı, sınıfın data memberlarına mm,my,md ye erişemezdik
Private çünkü buradaki değerler.

------------------------------
SORU
EN ÇOK HATA YAPILAN YER !!!!!!!!!!!!! 
400. SATIRDAKİ KODLA KARIŞTIRMA.

class Nec
{
public:
	void foo();
private:
	int x;
};

Nec gnec;

void Nec::foo()
{
	Nec a;
	
	gnec.x = 10; 	Geçerli.Farklı obje bile olsa private bölümüne erişir.
	
	a.x = 20;	    Geçerli.Farklı obje bile olsa private bölümüne erişir.
}

KURAL !!!!!!!!! 
SINIFIN ÜYE FONKSİYONLARI, SINIFIN PRIVATE BÖLÜMÜNE ERİŞEBİLİR DERKEN, KASTEDİLEN HANGİ DEĞİŞKEN İÇİN
TANIMLANIRSA TANIMLANSIN PRIVATE BÖLÜME ERİŞİR.!!!!!!!!!!!!!


---------------------------------------
SORU : FUNCTION OVERLOADING VAR MI ? 

class Nec
{
public:
	void foo();
private:
	int x;
};

void foo(int a)
{
	
}
void Nec::foo()
{
	foo(12); // SENTAKS HATASI MI ? EVET SENTAKS HATASI ÇÜNKÜ İSİMİ CLASS SCOPE TA BULUR VE 
			 // PARAMETRE İLE ARGÜMAN SAYISI DENK DEĞİL. ::foo(12) DESEYDIK HATA OLMAZDI.
			 // VEYA FONKSIYONA ARGÜMAN GÖNDERMESEYDIK BU SEFER RECURSIVE ÇAĞRI OLURDU.
}

FUNCTION OVERLOADING YOK ÇÜNKÜ SCOPE LARI FARKLI.

-------------------------------------

class Nec
{
public:
	void foo();
	void func(int);
private:
	int x;
};

void Nec::foo()
{
	func(3);  // CLASS SCOPE TA BULDU.func ismi Nec sınıfının nonstatic public functionunun ismi.
			  // Bu fonksiyonun gizli bir parametre değişkeni var. Nec * türden bir adres.
}

int main()
{
	Nec mynec;
	mynec.foo(); // burada foo mynec için çağrılacak. Yani Nec * türden bir mynecin adresini gönderiyor.
				 // Bu da noktanın sol operandından geliyor.
}

----------------------------------------
SORU:

class Nec
{
public:
	void func(int x);	
	void func(int x,int y);		//Function overloading geçerli ve var burada.
private:
};

int main()
{
	Nec mynec;

	mynec.func(2);
	mynec.func(1,2);
}



----------------------------------------

SORU:

class Nec
{
public:
	void func(int x);
private:
	void func(double x); 
};

int main()
{
	Nec mynec;

	mynec.func(2.3); // SENTAKS HATASI olur.
}

ACCESS CONTROL EN SON YAPILIR. FUNCTION RESOLUTION BİTTİ.ÇAĞRILACAK FUNCTION BULUNDU.
FONKSİYONUN BULUNDU AMA KULLANAMIYORUZ ÇÜNKÜ PRİVATE :D:D

FUNCTION OVERLOAD RESOLUTION SONRADA ACCESS CONTROL.
DOUBLE UYGUN AMA ÇAĞRILAMIYOR.HATA.

-----------------------------------------
SORU:

class Nec
{
public:
	void func(int x);
private:
	void func(double x);
	void foo();
};

void Nec::foo()
{
	func(12);
	func(1.2);
}

BURADA HİÇBİR HATA YOK. foo BURADA CLASS MEMBER FUNCTION.
HERYERE ERİŞİR.


===================================================================
===================================================================
===================================================================
===================================================================
===================================================================


CONST CORRECTNESS 
pointerlarda ve referanslarda.
getter ve setter functionlar var.
cosnt olması gereken heryerde const olacak.
Kodun kalitesini 1. dereceden belirliyor.

void func(Data *);
void foo(const Data *);

void func(Data &);
void foo(const Data &);

-----------------------------------------------------------------------------------------------------

class Nec{
public:
	void func(int); // ikiside nonstatic. ikisinde de gizli parametre değişkeni var.Bu Nec * türünden değişken
	void foo();
};

Eğer bu gizli olmasaydı
void func(Nec *p, int x); olacaktı. Peki bu accesser mı mutater mı?
Nasıl anlaşılacak?

const fonksiyonlar ile

=================================================================================
=================================================================================
=================================================================================

CONST MEMBER FUNCTIONS / CONST ÜYE FONKSİYONLAR

KURALLAR.
--------
BUNLARIN HEPSİNİN ÖRNEKLERİ AŞAĞIDA BOL BOL VAR.
1 - CONST ÜYE FUNC.LAR İÇİNDE SINIFIN NONSTATIC VERİ ELEMANLARINI DEĞİŞTİREMEYİZ AMA ERİŞEBİLİRİZ
2 - CONST ÜYE FUNC.LAR İÇİNDE SINIFIN NONCONST CONST OLMAYAN FUNC. LARINI ÇAĞIRAMAYAZ.
3 - CONST SINIF NESNELERİ İÇİN SINIFIN NONCONST ÜYE FOKSİYONLARI ÇAĞRILAMAZ.

class Nec{
public:
	void func()const;  // bu fonk. const demek. bu fonksiyon accesser
	void foo();
};

Eğer yukarıdaki gibi const gelirse en sona
buna const member function deniyor.

Non static member functions
	a - non const == Mutater / setter
	b - const == accesser / getter

const var ise
1 - bu accesser
2 - gizli parametre değişkeninde de const var


void func(int)const;  Bu aslında şu  void func(cosnt Nec *p) demek bu.test ettim.başka parametre varsa const yapmıyor.
void foo(); buda şu  void foo(Nec* p); demek

-----------------------------------------------------------------------------------------------------

struct data{
	int a,b,c;
};

int main()
{
	data mydata = {1,2,3};
	const data *ptr = &mydata;
	ptr->a = 20;	SENTAKS HATASI.çünkü (*ptr).a = 20; SENTAKS HATASI
	ptr->a; // GEÇERLİ. ERİŞİLEBİLİR.
}


-----------------------------------------------------------------------------------------------------


class Nec{
public:
	void func(int);
	void foo()const;
private:
	int mx;

};


void Nec::func()
{
	mx = 20; GEÇERLİ.
}


void Nec::foo()const  
{
	mx = 20;   SENTAKS HATASI. Gizli pointer burada const. const Nec *p. bu durumda low level const var.
			   Elemanlar değiştirilemez.
}

void Nec::foo()		böyle olursa SENTAKS HATASI. Sonda const yok. İlk bakışta görülmüyor
{

}

-----------------------------------------------------------------------------------------------------


AŞAĞISI GÜZEL SORU !!!!!!!!!!!!
140. SATIRDAKİ KODLA KARIŞTIRMA


class Nec{
public:
	void func();
	void foo()const;
private:
	int mx;

};

void Nec::func()
{
	mx = 23; OK
}


void Nec::foo()const
{
	mx = 23;  SENTAKS HATASI. ÇÜNKÜ GİZLİ PARAMETRE DEĞİŞKENİ DE CONST.
		ELEMAN DEĞİŞTİRİLEMEZ.
	
	std::cout << mx << '\n'; // GEÇERLİ. MX DEĞİŞTİRİLEMEZ AMA ERİŞİLİR
	
	Nec mynec;
	mynec.mx = 23   TAMAMEN GEÇERLİ. ÇÜNKÜ GİZLİ NEC POİNTER İLE ERİŞMEDİM.
					YENİ BİR NESNE YARATILDI VE FOO DA MEMBER FUNC OLDUĞU İÇİN ERİŞİMİ VAR.
					DEĞİŞTİREBİLİR.
}


-----------------------------------------------------------------------------------------------------

struct Data{
	int a,b,c;
};

void foo(Data *ptr);

void func(const Data *p)
{
	foo(p);		// BURASI SENTAKS HATASI. P COSNT DATA, FOO YA CONST DATA GÖNDERİYORUZ. 
				// CONST İNT TEN ,İNT E DÖNÜŞÜM BURADA SENTAKS HATASI.
}

-----------------------------------------------------------------------------------------------------

class Nec{
public:
	void func();
	void foo()const;
private:
	int mx;

};

void Nec::func()
{

}

void Nec::foo()const
{
	func();		SENTAKS HATASI !!!
				ÖNEMLİ!!! BİR MEMBER FUNC, BİR DİĞER MEMBER FUNC I ÇAĞIRDIĞINDA, ASLINDA GİZLİ PARAMETRESİ OLAN
}				POİNTERIN DEĞERİNİ ÇAĞIRDIĞI FUNC IN GİZLİ PARAMETRESİNE GEÇİYOR.
				

-----------------------------------------------------------------------------------------------------

class Nec{
public:
	void func();
	void foo()const;
private:
	int mx;

};

void Nec::func()
{
	foo();		// BU GEÇERLİ.DÖNÜŞÜM T* DAN CONST T* A.SORUN YOK.
}

void Nec::foo()const
{
	
}

-----------------------------------------------------------------------------------------------------
struct Data{
	int a,b,c;
};

void foo(Data *ptr);

int main()
{
	const Data mydata = {1,2,4};
	foo(&mydata);	// SENTAKS HATASI
}

-----------------------------------------------------------------------------------------------------

struct Data{
	int a,b,c;
};

void foo(Data *ptr);

void func(const Data *p)
{
	foo(p);		// BURASI SENTAKS HATASI. P COSNT DATA, FOO YA CONST DATA GÖNDERİYORUZ.
				// CONST İNT TEN ,İNT E DÖNÜŞÜM BURADA SENTAKS HATASI.
}

-----------------------------------------------------------------------------------------------------
3. KURALIN ÖRNEĞİ

class Nec{
public:
	void func();
	void foo()const;
private:
	int mx;
};

int main()
{
	const Nec mynec;
	
	mynec.func();	// burada mynec const türden. mynec.func() ta ise gizli const Nec * türden nesne gönderiliyor	
					// const gönderiyoruz ama class member func da const olarak bildirilmemiş. cont Nec * dan
					// Nec * a dönüşüm SENTAKS HATASI
	
	mynec.foo();	// Burası ise geçerli. const Nec* ile çağrılıyor ve class içinde const ile bildirilmiş.
					// GEÇERLİ.
}

ÇOOOOOOOOOK ÖNEMLİ !!!
CONST NEC MYNEC YERINE NEC MYNEC; DENSEYDI. HİÇBİRİNDE HATA YOKTU


-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------

SORU
CONST ÜYE FONKSİYON NE DEMEK ?
YANLIŞ CEVAP : SINIFIN VERİ ELEMANLARINI DEĞİŞTİRMEME GARANTİSİ VEREN İŞLEVDİR.BU YANLIŞ CEVAP
DOĞRU CEVAP : BU FONKSİYON NESNEYİ DEĞİŞTİRMEYECEK DEMEK. YUKARIDAKİ İLE AYNI DEĞİL

NESNEYİ DEĞİŞTİRMEKTEN KASIT, 
	NESNENİN PROBLEM DOMAİNİ İÇİNDEKİ SOYUTLANMIŞ ANLAMINI DEĞİŞTİRMEYECEK.

class fighter{
public:
	void shoot();
};

int main()
{
	fighter myfigher;
	myfigher.shoot();
}

Soru? 
void shoot const olmalı mı olmamalı mı ? 
Probleme göre değişir.
Ama burada bu const olmamalı. belki shoot her çağrıldığında 
birşeyler değişecek. mermi azalacak...


DİĞER ÖRNEK

class fighter{
public:
	void tell_name(); 
};

Burada daha fazla bilgiye ihtiyaç var.Yakın ihtimal const ama 
her tell_name() çağrıldığında bir can gidiyorsa herşey değişir.

---------------------------------------------------------------------------------------------

class Fighter{
public:
	int get_age()const;
	// int debug_call_count{}; // kaç kere func call olmuş bunu hesaplıyor.Önceki hali
	// mutable int debug_call_count{};  YENİ HALİ. ARTIK CONST MEMBER FUNC Bunu değiştirebilir.hata yok.
};

int Figher::get_age()const
{
	++debug_call_count; // Semantik açıdan hata yok ama sentaks hatası var. fonksiyon const 
			    // burada semantik ile sentaks uyumsuzluğu var.Burada bir keyword devreye girer
}			    // mutable. yukarıda mutable ile tanımlandı tekrar.
			    // bu değişkenin değişmesi problem domainindeki anlamını değiştirmiyor.Bu sebeple normal
			    // karşılanmalı bu.Bunu aşmak için mutable kullanıyoruz.

mutable bir keyword.

const önemli.
print gibi bir function kesinlikle const olmalı.

print const yapmadık diyelim.
adam const olan bir nesneyi print ile gönderiyor. const T den const a sentaks hatası olur.
bu durumda verideki const luğu silmek lazım. buda başka problemler doğuruyor....

Çok tehlikeli.

==============================================================================================
==============================================================================================
==============================================================================================
==============================================================================================
==============================================================================================

this
this bir POINTER - this göstericisi. 
Bu bir keyworddur.
Sadece sınıfların nonstatic member fonksiyonlarında bu kullanılabilir.
Global function içinde kullanılamaz.Static öğe fonksiyonlarında da this pointerı kullanılamaz.
PRvalue expression 


class Nec{
public:
	void func();
};

void Nec::func()
{
	this  
}

this = Yukarıdaki void Nec::func() fonksiyonunun gizli bir parametre değişkeni var. Nec *. 
		İşte bu Nec * türden adresi kullanmak istiyorsak this keyword / pointer kullanılır.
		Yani this demek, bu üye fonksiyon hangi nesne için çağrıldıysa o nesnenin adresi demek.

---------------------------------------------------------------------------------------------------------

BURASI adresleri karşılaştırıyor.
Neco nesnesinin adresi ile neco.func() çağrısından this ile yine neco nesnesinin adresine bakıyoruz.
ikiside aynı.

class Nec{
public:
	void func();
};

void Nec::func()
{
	std::cout << "this : " << this << "\n";
}

int main()
{
	Nec neco;

	std::cout << "&neco : " << &neco << "\n";
	neco.func();
}

ÇIKTI
&neco : 005EF84F
this : 005EF84F


---------------------------------------------------------------------------------------------------------


class Nec{
public:
	void func();
private:
	int mx;
};

void Nec::func()
{
	mx = 10;
	this->mx; ikiside aynı. this zaten Nec * türden adres.
	
	foo(); bu bir foo çağrısı
	this->foo(); buda aynı anlam. foo() ya erişiyor.
}


mx = 10;	
Nec::mx = 20; //bu şekilde :: operatörünün operandı olarak kullanılan isimlere qualified name deniyor.
	      //doğrudan kullanım unqualified

this->mx = 30; //bunların hepsi aynı.											


AYNI şekilde
foo();
Nec::foo();
this->foo();   Bunlarında hepsi aynı.

this pointerı PR value exp dir.
Pythonda self diye geçiyordu bu.

------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------

SORU
class Nec{
public:
	void func();
};

void Nec::func()
{
	std::cout << "this : " << this << "\n";
}

int main()
{
	Nec neco;

	std::cout << "&neco : " << &neco << "\n";
	neco.func();
}


Bu fonksiyon hangi nesne için çağrılıyorsa o nesnenin kendisi nedir?
member function içerisinden *this
*this neco dur.
 
------------------------------------------------------------------------------------------------------

Madem
mx / this->mx / Nec::mx aynı anlamda
o zaman this neden var ???

------------------------------------------------------------------------------------------------------

class Nec{
public:
	void func();
	void foo();
private:
	int mx;
};

void Nec::func()
{
	std::cout << "this : " << this << "\n";
}

void foo()
{
	int mx{};
	mx;   //BURADA LOCAL MX KULLANILIR.
	
	this->mx;	//CLASS DATA MEMBER OLAN MX KULLANILIR.
	Nec::mx;	// te ulaşır mx e.
}

int main()
{
	Nec n;

	n.foo();
}


SADECE BU KADAR DEĞİL.

------------------------------------------------------------------------------------------------------

class Nec{
public:
	void func();
private:
	int mx;
};

void foo(Nec* p);
void f(Nec& r);
void g(Nec );


void Nec::func()
{
	// Func hangi nesne ile çağrıldıysa o argüman ile foo yu çağırsın
	// this olmadan bunu yapmanın yolu yok.
	foo(this);

	f(*this); bu kısımda reference semantiği ile çağırmak için.
	g(*this); buda kopyalama semantiği.
}

This olmadan yukarıdakiler mümkün değil.


------------------------------------------------------------------------------------------------------

İleride bazı fonksiyonların geri dönüş değeri Nec&(Nec sınıfı türden referans) türden olacak.

class Nec{
public:
	Nec& func();	// operator overloading konusunda görülecek .Nec *func(); olabilecek bazı örnekler.
	void foo();
private:
	int mx;
};

Nec& Nec::func()
{
	//...
	return *this; 
}

int main()
{
	Nec mynec;
	mynec.func();	// Nec * türden adres gönderdi implicit olarak.

	mynec.func().foo();   // bu işlem yapılabilir.2 satırda da yazılabilir. Ama ileride görülecek bazı örneklerde
				// bunu kullanmak avantaj sağlayacak. Buna chaining deniyor.

}

---------------------------------------------------------------------------------------------------------------

int main()
{
	int x = 10;
	double dval = 2.3;

	cout << x << dval;
	
	cout.operator<<(x); //burada çağrılan fonksiyonun return değeri sınıf türünden referans.ostream referans
			    //yani burası cout un kendisi

	cout.operator<<(x).operator<<(dval); //bu ile cout<<x << dval ; aynı şey.

}

----------------------------------------------------------------------------------------------------------------


class Nec{
public:
	Nec *func();	//yukarıda referans ile örnek yapılmıştı burada pointer ile.
	void foo();		// daha az rastlanıyor ama bu
private:
	int mx;
};

Nec* Nec::func()
{
	//code
	return this;
}

int main()
{
	Nec mynec;
	mynec.func();

	mynec.func()->foo();   
}


----------------------------------------------------------------------------------------------------------------

heryerde this kullanımını hoca beğenmiyor.
uygun class isimleri vermek daha mantıklı.

class myclass{
public:
	myclass& func()const;

};

myclass& func()const
{
	return *this;	//SENTAKS HATASI. CONST POINTER DEREFERENCE EDİLDİ. TÜR CONST MYCLASS. COSNT MYCLASS TO MYCLASS SENTAKS HATASIDIR.
}

SENTAKS HATASI OLMAMASI İÇİN YA MEMBER FUNCTİONDAKİ CONST SİLİNECEK YADA RETURN DEĞERİNE CONST EKLENECEK.

------------------------------------------------------------------------------------------------------------------------------

class myclass{};

void func(myclass *);
void func(const myclass *);   //bu ikisi OVERLOAD.

int main()
{
	myclass a;
	const myclass c;

	func(&a);  //1. overload çağrılır
	func(&c);  //2. overload çağrılır.
		
}

------------------------------------------------------------------------------------------------------------------------------

class Myclass{
public:
	void func(); //Gizli parametre Myclass *
	void func()const;  //BURADA OVERLOADING VAR.Gizli param const Myclass *
};

BUnları çağırdığında hangisinin çağrıldığına baktı.
const olan const parametre ile
Olmayanda olmayan parametre ile çağrıldı.

------------------------------------------------------------------------------------------------------------------------------

EKLEME

class Myclass{
public:
	void func();	//Gizli parametre Myclass *
	void func()const;	//BURADA OVERLOADING VAR.Gizli param const Myclass *
};

void Myclass::func()
{
	//this ==> Myclass *
}

void Myclass::func()cosnt
{
	//this ==> const Myclass *
}

--------------------------------------------------

*this deyip buna bir myclass objesi atama örneği yaptı.
ileride de görülecek zaten.





================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================
================================================================================================================================





SINIF CONSTRUCTORLARI VE DESTRUCTORLARI
SPECIAL MEMBER FUNCTIONS - SINIFLARIN ÖZEL UYE FONKSİYONLARI.	 EN ZOR KISIM

5 - 10 DK HİÇBİRŞEY ANLAŞILMAYABİLİR :D:D:D:D:D

Bu fonksiyonlar dilin kuralları tarafından garanti altına alınmış,
Belirli koşullar sağlandığında derleyici tarafından yazılabilen functionlara Special Member Functionlardır.
Bunları bizde yazabiliyoruz tabi.

Buna derleyicinin bu kodu default etmesi deniyor.

Modern C++ ta bu konu baya değişmiş.
Eskiyi hiç anlatmayacak hoca.

BİLİNÇALTINA GİRSİN DİYE HOCA HABİRE TEKRARLAYACAK.
-----------------------------------------------------------------------------------------

Special Member Functions
------------------------
DEFAULT CONSTRUCTOR
DESTRUCTOR
COPY CONSTRUCTOR
MOVE CONSTRUCTOR C++11
COPY ASSIGNMENT
MOVE ASSIGNMENT C++11

NASIL ISLAMIN VE IMANIN ŞARTLARI VARSA, SPECIAL MEMBER FUCNTIONS LARINDA ŞARTLARI VAR.

-----------------------------------------------------------------------------------------

TÜRKÇELERİNİ YAZMAYACAĞIM BAYA ANLAMSIZ. :D:D
C++ I ÖĞRENMENİN 3 TE 1 İ
EN ZOR KONU.

ESKİ C++ İLE YENİ C++ ARASINDA CİDDİ FARKLILIKLAR VAR.

--------------------------------------------------------------

BİR SINIF NESNESİNİ HAYATA GETİREN SINIFIN ÜYE FONKSİYONLARINA SINIFIN
CONSTRUCTORLARI DENİYOR.

BİR SINIF VARSA, SINIF NESNELERİNİ HAYATA GETİRMEK İÇİN CONSTRUCTOR KULLANMALIYIZ.

DESTRUCTOR İSE NESNENİN HAYATINI SONLANDIRIYOR.AZRAİL. :D:D:D

---------------------------------------------------------------------------

CONSTRUCTOR KURALLARI
---------------------

1 - CONSTRUCTOR İSMİ SINIF İSMİYLE AYNI OLMALIDIR.
2 - GLOBAL FONKSİYON OLAMAZ.
3 - SINIFIN STATİC ÜYE FONKSİYONU OLAMAZ(non-static)
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.

ÖR:
class Myclass{
public:
	Myclass();	İSMİ SINIF İSMİYLE AYNI.
};				BAŞINA VOİD-STATIC-CONST YAZARSAK SENTAKS HATASI

5 - CONST ÜYE FONKSIYON OLAMAZ.
6 - SINIFIN PUBLIC, PRIVATE, PROTECTED FONKSIYONLARI OLABILIR.
	PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.
7 - CONSTRUCTOR OVERLOAD EDILEBILIYOR

class Myclass{
public:
	Myclass();
	Myclass(int);
	Myclass(int,double);
};

8 - BIR SINIFIN
	A - PARAMETRE DEĞIŞKENI OLMAYAN
	B - TÜM PARAMETRELERI DEFAULT ARGÜMAN ALAN
		CONSTRUCTORLARA DEFAULT CONSTRUCTOR DENIR.

	class Myclass{
	public:
		Myclass();	Bu Default Constructor
	};

9 - CONSTRUCTOR İSMİ İLE ÇAĞRILAMAZ. YANİ . -> OPERATÖRLERİYLE ÇAĞRILAMAZ.


DESTRUCTOR KURALLARI
--------------------

1 - İSMİ SINIF ~İSMİYLE AYNI OLAN FONKSİYONLAR
	~Myclass();
2 - GLOBAL FONKSİYON OLAMAZ.
3 - SINIFIN STATIC ÜYE FONKSİYONU OLAMAZ.
4 - GERİ DÖNÜŞ DEĞERİ KAVRAMI YOK.
5 - CONST ÜYE FONKSIYON OLAMAZ.
6 - SINIFIN PUBLIC, PRIVATE,PROTECTED FONKSIYONLARI OLABILIR.
	PRIVATE VE PROTECTED OLUNCA CLIENT KODLAR TARAFINDAN ÇAĞRILAMAZ.
7 - DESTRUCTOR OVERLOAD EDILEMEZ. !!!!!!  FARK BURADA
	PARAMETRESI OLMAYAN BIR FONKSIYON OLMAZ ZORUNDA.
8 - DESTRUCTOR İSMİ İLE ÇAĞRILABİLİR.ÇOK ÖZEL BİR DURUMDA YAPILACAK BU.
	ASLA BİR DESTRUCTORU İSİMLE ÇAĞIRMAYIN.


========================================================================================================================
========================================================================================================================

BU BÖLÜM AKSİ BELİRTİLENE KADAR DEFAULT İNİT İLE ALAKALI

GLOBAL VE STATIC ÖMÜRLÜ NESNELER HAYATA GELME VE VEDA ETME DURUMLARI


class Myclass {
public:
	Myclass();	// DEFAULT CONSTUCTOR
	~Myclass(); // DESTRUCTOR
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}

// Sınıf nesneleri default init edildiğinde Default constructor devreye girer.
// ÖR : int x; default init

Myclass g; // DEFAULT İNİT EDİLDİ.


int main()
{
	std::cout << "main basladi\n";

	std::cout << "&g = "<<&g<<"\n";

	std::cout << "main sona erdi\n";
}


// ÇOK ÖNEMLİ!!!
// STATIC ÖMÜRLÜ GLOBAL NESNELER MAİN FONKSİYONUNUN ÇAĞRILMASINDAN ÖNCE HAYATA GELİYORLAR.
// BURADA CONSTRUCTOR MAİNDEN ÖNCE HAYATA GELİR, DAHA SONRADA MAİN HAYATA GELİR.
// MAİN SONLANDIKTAN SONRA DA DESTRUCTOR DEVREYE GİRER VE OBJE YOK EDİLİR.

// ÇIKTISI

//00A6E138 adresinde bir Myclass nesnesi hayata geliyor
//main basladi
//& g = 00A6E138
//main sona erdi
//00A6E138 adresindeki nesnesi hayata veda ediyor.

// Myclass g; BURADAKİ g NİN ADRESİ İLE CONSTRUCTOR/DESTRUCTOR İÇERİSİNDEKİ THİS ADRESİ AYNI.
// ZATEN BU DEFAULT İNİT YAPILIYOR VE OBJE YARATILIYOR. BU CONST. VE DEST. LERDE BU OBJEYE AİTLER.
// TABİKİ NESNE ADRESLERİ AYNI.

--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------

ÖNCE HANGİ NESNE İÇİN DESTRUCTOR ÇAĞRILACAK?

BİLDİRİM SIRASIYLA ÇALIŞACAK. BU KURAL.
Myclass g1;
Myclass g2;
Myclass g3;  

HAYATLARININ BİTMESİ İSE HAYATA GELMELERİYLE TERS ORANTILI.
YANİ İLK HAYATA GELEN EN SON VEDA EDİYOR. SON GELENDE İLK VEDA EDİYOR.

DİĞER ÖRNEKTEN YAZIYORUM

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}

// Sınıf nesneleri default init edildiğinde Default constructor devreye girer.
// ÖR : int x; default init

Myclass g1;
Myclass g2;
Myclass g3;


int main()
{
	std::cout << "main basladi\n";

	std::cout << "main sona erdi\n";
}


//00F8E139 adresinde bir Myclass nesnesi hayata geliyor		İLK HAYATA GELEN. EN SON VEDA ETMİŞ AŞAĞIDA ADRESLERİ KONTROL ET
//00F8E138 adresinde bir Myclass nesnesi hayata geliyor
//00F8E13A adresinde bir Myclass nesnesi hayata geliyor
//main basladi
//main sona erdi
//00F8E13A adresindeki nesnesi hayata veda ediyor.
//00F8E138 adresindeki nesnesi hayata veda ediyor.
//00F8E139 adresindeki nesnesi hayata veda ediyor.

 
========================================================================================================================
========================================================================================================================


OTOMATİK ÖMÜRLÜ NESNELER HAYATA GELME VE VEDA ETME DURUMLARI

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}

void func()
{
	std::cout << "func basladi\n";
	Myclass x;
	std::cout << "func calisiyor\n";
}



int main()
{
	std::cout << "main basladi\n";

	func();

	std::cout << "main sona erdi\n";
}

// ÇIKTISI

//main basladi
//func basladi
//0133FD03 adresinde bir Myclass nesnesi hayata geliyor
//func calisiyor
//0133FD03 adresindeki nesnesi hayata veda ediyor.
//main sona erdi


-------------------------------------------------------------------------------------------------------------------------

for ile örnek yaptı 5 tane nesne hayata gelip veda ediyor yazdı. Yazmadım o örneği.

-------------------------------------------------------------------------------------------------------------------------

ÖR:

#include <iostream>

class Myclass {
public:
	Myclass();
	~Myclass();
};


Myclass::Myclass()
{
	std::cout << this <<" default cunstructor called\n";
}

Myclass::~Myclass()
{
	std::cout << this << " destructor called\n";

}

void func(Myclass x)
{
	std::cout << "func called\n";
}

int main()
{
	Myclass my;
	func(my);
}


ÇIKTI:
------

0073FEC7 default cunstructor called
func called
0073FDEC destructor called
0073FEC7 destructor called

========================================================================================================================
========================================================================================================================


STATIC ÖMÜRLÜ YEREL NESNELER HAYATA GELME VE VEDA ETME DURUMLARI

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}

void func()
{
	static Myclass m;
}

int main()
{
	std::cout << "main basliyor\n";
	func();
	func();
	func();
	func();
	func();
	std::cout << "main sona eriyor\n";
}


// STATIC LOCAL DEĞİŞKENLER ÇAĞRILDIĞINDA HAYATA GELİR VE BİR DAHA ÇAĞRILDIĞINDA FUNCTION TEKRAR HAYATA GELMEZ.
// ZATEN HAYATTADIR. AYNI DURUM TABİKİ BURADA DA VAR.

//ÇIKTI
//main basliyor
//0015D140 adresinde bir Myclass nesnesi hayata geliyor
//main sona eriyor
//0015D140 adresindeki nesnesi hayata veda ediyor.

// MAIN BAŞLAR FONKSIYON ÇAĞRISI NE KADAR YAPILIRSA YAPILSIN 1 KERE YARATILDIĞI IÇIN BIRDAHA YARATILMAZ.
// SONRA MAIN SONA ERER. EN SONUNDA DA O YARATILAN STATIC ÖMÜRLÜ LOCAL DEĞIŞKEN IN HAYATI SONA ERER


========================================================================================================================
========================================================================================================================

KARIŞIK SORULAR.

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}


int main()
{
	Myclass x;
	Myclass* p1 = &x;
	Myclass* p2 = &x;		// CONSTRUCTOR KAÇ KERE ÇAĞRILIR ? 1 KERE ÇAĞRILIR
}


----------------------------------------------------------------------------------------------------------------------

#include <iostream>

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}


int main()
{
	Myclass x;
	Myclass& p1 = x;		 // BU SEFER POINTER YOK.REFERANS SEMANTİĞ VAR
	Myclass& p2 = x;		// CONSTRUCTOR KAÇ KERE ÇAĞRILIR ? YİNE 1 KERE ÇAĞRILIR
}

----------------------------------------------------------------------------------------------------------------------

ÖR:

class Myclass {
public:
	Myclass();
	~Myclass();
	void func();  // Bu yeni geldi.Dikkat
};

void Myclass::func()
{
	std::cout << "Myclass::func cagrildi\n";
}

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}


int main()
{
	Myclass x;
	x.func();

	//COSNTRUCTOR AŞAĞIDAKI GIBI ÇAĞRILAMAZ !!!
	x.Myclass();

	//AŞAĞISI LEGAL FAKAT ASLA YAPILMAYACAK. SADECE 1-2 ÖZEL DURUM VAR.ORADA ÇAĞRILACAK.
	x.~Myclass();

	//NOT !!! ÇOK ÖNEMLİ !!!!
	// CONSTRUCTOR PRİVATE YAPILABİLİR AMA BU DURUMDA Myclass x; DENDİĞİNDE DEFAULT CONSTUCTOR DEVREYE GİRER.
	// İSİM ARAMA KURALLARINA GÖRE BUNU BULUR AMA SON ADIMDA ACCESS CONTROL HATASI ALINIR.!!!!!!!!!!!!!!!!!!!
	// AMA BUNU YAPMAMIZ GEREKEN YERLER OLACAK.MEMBER FUNCTIONLAR İÇİNDEN PRIVATE ERİŞİLİYOR. CLİENTLAR NESNE
	// OLUŞTURAMAYACAK AMA MEMBERLAR OLUŞTURABİLECEK.

	// DESTRUCTORDA DA AYNI DURUM VAR.SENTAKS HATASI DEĞİL AMA CLİENT ÇAĞIRAMAZ. MEMBER FUNCLAR ÇAĞIRIR.

}

----------------------------------------------------------------------------------------------------------------------------

ÖR:

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	std::cout << this << " adresinde bir Myclass nesnesi hayata geliyor\n";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{
	std::cout << this << " adresindeki nesnesi hayata veda ediyor.\n";
}


int main()
{
	Myclass a[10]; // 10 kere constructor çağrılacak ve dizinin hayatı bitince herbiri için destructor çağrılacak.
					// ilk yaratılan en son veda edecek.
}

//ÇIKTI
//
//0135FC2C adresinde bir Myclass nesnesi hayata geliyor
//0135FC2D adresinde bir Myclass nesnesi hayata geliyor
//0135FC2E adresinde bir Myclass nesnesi hayata geliyor
//0135FC2F adresinde bir Myclass nesnesi hayata geliyor
//0135FC30 adresinde bir Myclass nesnesi hayata geliyor
//0135FC31 adresinde bir Myclass nesnesi hayata geliyor
//0135FC32 adresinde bir Myclass nesnesi hayata geliyor
//0135FC33 adresinde bir Myclass nesnesi hayata geliyor
//0135FC34 adresinde bir Myclass nesnesi hayata geliyor
//0135FC35 adresinde bir Myclass nesnesi hayata geliyor
//0135FC35 adresindeki nesnesi hayata veda ediyor.
//0135FC34 adresindeki nesnesi hayata veda ediyor.
//0135FC33 adresindeki nesnesi hayata veda ediyor.
//0135FC32 adresindeki nesnesi hayata veda ediyor.
//0135FC31 adresindeki nesnesi hayata veda ediyor.
//0135FC30 adresindeki nesnesi hayata veda ediyor.
//0135FC2F adresindeki nesnesi hayata veda ediyor.
//0135FC2E adresindeki nesnesi hayata veda ediyor.
//0135FC2D adresindeki nesnesi hayata veda ediyor.
//0135FC2C adresindeki nesnesi hayata veda ediyor.

----------------------------------------------------------------------------------------------------------------------------

MÜLAKAT SORUSU

class Myclass {
public:
	Myclass();
	~Myclass();
};

//Burası date.cpp de aslında
Myclass::Myclass()
{
	static int x = 0;
	std::cout << x++ << " ";
}

//Burasıda date.cpp de aslında
Myclass::~Myclass()
{

}

int main()
{
	Myclass a[100];
}

//BU MÜLAKAT SORUSU
//
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40
//41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60
//61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80
//81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99

=======================================================================================================================
=======================================================================================================================

VALUE INIT İLE İLGİLİ KISIM

	Myclass x;  // DEFAULT INIT
	Myclass y{}; // VALUE INIT

Value initte de Default constructor çağrılır

------------------------------------------------------------------------------------------------------------------------

class Myclass {
public:
	Myclass();
};

Myclass::Myclass()
{
	static int x = 0;
	std::cout << x++ << " ";
}


int main()
{
	Myclass x;  // DEFAULT INIT
	Myclass y{}; // VALUE INIT
	Myclass z(); // BU FUNCTION DECLERATION :D:D:D
}

2 Defa default constructor çağrılır.

*/


#include <iostream>

class Myclass {
public:
	Myclass();
};

Myclass::Myclass()
{
	static int x = 0;
	std::cout << x++ << " ";
}


int main()
{
	Myclass x;  // DEFAULT INIT
	Myclass y{}; // VALUE INIT
}
