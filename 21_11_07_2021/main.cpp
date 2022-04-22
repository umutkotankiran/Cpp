/*

Sınıfın private bir member func ı olsa bunu override etmemde bir sakınca oluşur mu ?
Oluşmaz.Böyle olabilir.Kodu aşağıda

class Base {
private:
	virtual void foo() // olabilir.son derece doğal
	{
		std::cout << "Base::foo()\n";
	}
};

Peki kalıtım yoluyla yeni bir sınıf elde ettiğimde bu fonksiyonu override edebilir miyim
Evet yapılıyor.Kullanılan bir yapı

class Der : public Base {
public:
	virtual void foo() override {
		std::cout << "Der::foo()\n";
	}
};


void gfunc(Base& baseref)
{
	baseref.foo(); // SENTAKS HATASI.Compile time da erişim kontrolne takılır.Erişim kontrolü burada Base sınıfı nesnesi için
}

Base classın public interface inde bulunan virtual func derived classın private interface inden override ettik.

----------------------------------------------------------------------------------------------------- -

Sınıfın public interface inde sanal yada sanal olmayan fonksiyonlar olacak.

class Base {
private:
	virtual void foo()
	{
		std::cout << "Base::foo()\n";
	}
public:
	void var()
	{
		// kodlar..
		foo();
		//
	}
};


İşte buradaki yapı çok populer bir idiyom.Herb Sutter
NVI - Nonvirtual İnterface - Sanal olmayan arayüz

Base sınıfından kalıtım yoluyla elde edilecek sınıflar, yukarıdaki örnekteki gibi taban sınıfın private/protected sanal functionlarını
override ediyor.Bazı avantajları var.En önemlilerinden biri, bu fonksiyonun kendisi sınıfın public functionu olsaydı ve 
biz klasik modeldeki gibi bunu override etseydik, bir kontrol noktası oluşmayacaktı.ilerleyen derslerde invariant görülecek.
Invariant, sınıf/func ın doğru çalışması için mutlaka sağlanması gereken koşullardır.Bu invariantlar sağlanmadıysa bir yanlışlık vardır.

invariant
fonksiyonun yada sınıfın düzgün çalışması için mutlaka yapılması gereken kurallar.

Mesela bağlı listenini tipik invariantları var.boş ise size ın 0 döndürmesi gibi.

void func()
{

}
Bu fonksiyonun işini düzgün yapabilmesi için tipik olarak yapılması gereken 2 şey var.
invariantlar doğru mu ?
fonksiyon işini yaptıktan sonra
yine invariant kontrolü ?

Burada var isimli function olmasa ve sanal function public olsa zaten override olan function çağrılacaktı
Ama burada bir kontrol sağlamış oluyoruz.Gerekli kontroller varsa bunlar sağlanır ve sonrasında virtual dispatch devreye girecek.
Yani hangi sınıf için bu çağrılıyorsa onun override ı çağrıldıktan sonra da ine çıkarken invariant kontrolü yapılabilir.

Programcılar, sanki sanal fonksiyonlar private olamazmış gibi, yada private sanal functionlar türemiş sınıflar tarafından override 
edilemez gibi düşünüyorlar.Bunu düşündüren ne, func private olduğunda taban sınıf ptr veya referans ile çağrılınca sentaks
hatası olacak. Ama biz bunu ptr veya referans ile doğrudan çağırmayacağız.sınıfın başka bir memberı bunu çağıracak
bu şekilde private bölüme erişimde sıkıntı olmayacak.

Bunu normalde private yapıyoruz ama bazen şu gerekiyor.
türemiş sınıfın override ı, önce taban sınıfın sanal func ının kodunu çalıştırmak istiyor.Bu durumda :: ile bu func ı çağıracak.
Private ta sentaks hatası olur ama protected ta hata olmaz.

class Base {
protected:
	virtual void foo() //protected yapıldı.
	{
		std::cout << "Base::foo()\n";
	}
public:
	void var()
	{
		// kodlar..
		foo();
		//
	}
};

class Der : public Base {
public:
	virtual void foo() override 
	{
		Base::foo(); //Burada olduğu gibi.
		std::cout << "Der::foo()\n";
	}
};

Burada bu konuya sadece değindi hoca.İleri C++ ta anlatılıyormuş.
Özellikle exception handlingde görülecek.

===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================
===========================================================================================================================


SANALLIK MEKANİZMASI NASIL İMPLEMENTE EDİLİYOR
-----------------------------------------------

EN ÇOK SORULAN MÜLAKAT SORUSU BURADAN GELİYOR

#include <iostream>
#include "car.h"
#include <conio.h>

car header file ı include ettik.Oradan anlatacak.

void car_game(Car * p)
{
	p->start();
	p->run();
	p->stop();
	std::cout << "------------------------------------\n";
}

int main()
{
	for (;;)
	{
		auto cp = create_random_car();
		car_game(cp); // Bunun C kodunu düşün.
		_getch();
		delete(cp);
	}
}

Varlık nedeni nesne oluşturup kendisini çağıran koda ileten fonksiyonlara fabrika fonksiyonu deniyor.
biz car_game(cp) de sadece adres gönderiyoruz.Nasıl oluyorda bu adresten hareketle bu program çalışırken, start functionu
çağrıldığında, dacia ise dacia startı, bmw ise bmw startı nasıl çalışıyor. Adresten hareketle nasıl oluyor bu iş.

C de bunu bi implemente edip hocaya gönder.


ŞİMDİ ARKA PLANDA NELER DÖNÜYOR ONA BAKALIM.
--------------------------------------------

class Base {
	int x, y;
};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // 8 byte
}

------------------------

class Base {
	int x, y;
	void f1();
	void f2();
};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // Halen 8 Byte
}

Üye fonksiyonlar fiziksel olarak o nesne içinde il o yüzden halen 8 byte.

-----------------------------------------------------------------------------

class Base {
	int x, y;
	virtual void f1();
	void f2();
};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // 12 byte oldu
}

Sanala function gelince farklılık oldu.12 byte. 

-----------------------------------------------------------------------------

class Base {
	int x, y;
	virtual void f1();
	virtual void f2();
};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // Yine 12 byte
}

Sınıfa virtual function ekleyince size 12 oldu.Bir tane daha ekleyince halen 12 byte.
1 tane dahada eklesek yine 12 olacak.

Sınıfın en az bir sanal fonksiyonu varsa bunlara polimorfik sınıf deniyordu.
Sınıf polimorfik olunca sınıf için beklenen sizeof değeri fazla oldu.Nonpolimorfik için
farketmedi.

-----------------------------------------------------------------------------

Bu sınıftan kalıtım yoluyla yeni sınıf elde edelim

class Base {
	int x, y;
	void f1();
	void f2();
};

class Der : public Base {

};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // 8
	std::cout << "sizeof(Der) = " << sizeof(Der) << "\n"; // 8
}

Yine 8 oldu

-----------------------------------------------------------------------------

Şimdide functionlardan birini polimorfik yapalım ve size a bakalım.

class Base {
	int x, y;
	virtual void f1();
	void f2();
};

class Der : public Baase {

};

int main()
{
	std::cout << "sizeof(Base) = " << sizeof(Base) << "\n"; // 12
	std::cout << "sizeof(Der) = " << sizeof(Der) << "\n"; // 12 oldu ikiside
}

Eğer bir sınıf polimorfik ise, derleyici bu nesnelerin içine pointer daha koyuyor.
Bu görülmüyor ama tipik implementasyon böyle. Yani base sınıfı türünden her nesne sizeof ça artık 1 ptr daha fazla.

Bu tip pointerlara VIRTUAL POINTER deniyor.Tam adı VIRTUAL FUNCTION TABLE POINTER.
Makalelerde vptr diye geçiyor.

Bu taban sınıf nesnesinin içerisindeyse, her türemiş nesne içinde türemiş sınıflardan hangisi olursa olsun, içerisinde
bir taban sınıf nesnesi var.Yani polimorfik hiyerarşideki her sınıf nesnesinin içinde bu pointer var.
Bu pointera biz bir sınıf nesnesi oluşturduğumuzda, bu ptr ı initialize edecek kodu derleyici üretiyor.

Peki ne ile initialize ediliyor bu pointer?
Bu pointer aslında bir lookup table gösteriyor.Yani bu bir veri yapısını gösteriyor.
index ile elemanlarına erişebildiğimiz bir veri yapısı.Bu veri yapısına sanal fonksiyon tablosu deniyor.

Bu tabloda function pointerları tutuluyor.

MERCEDES SANAL FONK. TABLOSU
|---------------------------|
| 1	| &mercedes::start  |
|---------------------------|
| 2	| &mercedes::run    |
|---------------------------|
| 3	| &mercedes::stop   |
|---------------------------|

Bu sanal function tablosu runtime ın başında oluşturuluyor ama bu tablonun oluşturulmasında bu indexler compile timeda
sınıfın veya sınıf hiyerarşisine bakarak derleyici tarafından oluşturuluyor. Sınıf hiyerarşisindeki her sınıf için böyle
bir sanal function tablosu var. Mesela Audinin sanal function tablosu var.

Audi SANAL FONK. TABLOSU
|---------------------------|
| 1	| &audi::start	    |
|---------------------------|
| 2	| &audi::run	    |
|---------------------------|
| 3	| &Audi::stop	    |
|---------------------------|

Hiyerarşide ne kadar sınıf varsa herbiri için derleyici sanal function tablosu oluşturuyor.

İşin sırrı şurada, tüm sınıfın sanal fonksiyon tablolarında aynı indexte aynı sanal functionun overrideları var.
Mesela Fiat124 içinde 1 de start, 2 de run, 3 te stop var.

Ama eğer Fiat124 bu functionı override etmemişse bu indexli adres olan function, onu override eden ilk taban sınıfın
üye fonksiyonunun adresi olacak. ÖR: Fiat124 run ı override etmediyse ama Fiat sınıfı run ı override etmişse,
fiat sınıfının run functionunun adresi olacak.

Biz bir sınıf nesnesi oluşturunca (otomatik veya dinamik ömürlü), sınıf nesneleri içinde bulunan taban sınıf nesnesi içine gömülü
bu pointera, ilk değerini derleyicinin ürettiği kod veriyor. Bu bir Audi nesnesi ise, sanal fonksiyon tablo göstericisinin değeri
Audi nin sanal function adresi olacak. Mercedes ise mercedesin içinde vptr değeri mercedesin sanal fonksiyon değerinini adresi olacak.

SONUÇ:
void car_game(Car * carptr)
{
	carptr->run();
}

Derleyici compile time da isim aramayla run ismini taban sınıf memberları arasında buluyor.
Bunu sınıfın sanal func olduğunu anlıyor.Artık bir virtual dispatch kodu üreteceğini biliyor compile timeda.
Nasıl kod üretecek

psudo code
carptr->run();
(carptr->vptr)[2]();
 

MALIYET FAKTÖRÜ
---------------
Uygulamaya bağlı.Maliyet tamamen çalıştığımız ortama işlemciye uygulama karakterine ve func ın hangi sıklıkla çağrıldığına bağlı.
mikrosaniyeler önemlide olabilir ama cpu bound olmayan uygulamada olabilir.

Bellek kullanımı : Her polimorfik nesne pointer sizeofu kadar daha fazla storage değerine sahip olacak.
Polimorfik sınıflar türünden nesne başına fazladan maliyet var. 4 byte ise ptr, nesne başına 4 byte.

Mesela çok sayıda araba varsa her bir araba için sanal function tablo göstericisi var.Polimorfik olmasaydı
4 bytelık ilave alan gerekmeyecekti.

Sanal fonksiyon tablolarının kendisi.Heap te oluşturuluyorlar.Bunun içinde bellek alanı allocate edilir.
Bununda maliyeti var.Dinamik bellek yönetimini gerçekleştiren birde header kısmı vardı.
Her sınıf için burada sanal sınıf function tablosuna ihtiyacımız var.

------------------------------------
ÇOK ÖNEMLİ BURASI !!!!
Bu tablo nesne ile ilgili değil sınıf ile ilgili.Static veri elemanı gibi düşünülebilir.
Static veri elemanı class a aitti. nonstaticler nesneye ilişkindi. Vptr ler sınıfın nonstatic memberı gibi.
Sanal function tablosu da sınıfın static memberı gibi düşünülebilir.Çünkü her bir nesne için çağrılacak function
adresi aynı.Herbiri için ayrı ayrı functionlar yok. Vptr ler ayrı ayrı var ama bunlarda sınıf için olan static gibi
düşündüğümüz adresleri gösteriyor.
------------------------------------

Runtime maliyeti : ptr->foo(); Compile time da kimin çağrılacağı belli.Çağrıldığında derleyici buna yönelik bir kod üretir.
Polimorfik çağrılarda buna ilaveten 2 adet dereferencing olmalı.Neden bu yapılıyor.

1. Carptr->run() gibi çağrı yapılınca, derleyici vptr nin değerini get edecek. Sınıf nesnesinin adresinden hareketle derleyici o sınıf
nesnesinin içindeki kendi initialize ettiği vptr nin değerinin get edileceği bir kod üretmek zorundaki, sanal function tablosuna erişsin.

2. Yine index ile bu kez sanal func tablosundaki o indexteki pointera erişecek ve functionun adresini elde edecek.

NOT : Derleyiciler çağrılan functionun sanal olması durumunda bazı durumlarda koda bakarak şöyle bir optimizasyon yapabilirler.
Aslında koddan da hangi functionun çağrıldığı anlaşılabiliyor(bazen). Dolayısı ile derleyicilerin yaptığı ilginç optimizasyonlardan birine
de devirtualization deniyor. Bu şu demek. Normalde virtual dispatch yapılması gerekiyor ama derleyici koda bakarak çağrılanı anlayabiliyorum
diyor.Buna devirtualization deniyor.Böyle optimizasyon yoksa 2 adet dereferencing var.

İşlem maliyeti açısından bakınca, 
Sanal func tablosunun runtime da oluşturulması(bunlar için bellek alanı allocate işlemlerinide sayıyoruz).
Bir sınıf nesnesi oluşturulması durumunda onun içindeki virtual pointerın initialize edilmesi.


==============================================================================================================================================
==============================================================================================================================================
==============================================================================================================================================


Virtual Constructor ve Virtual Destructor
-----------------------------------------

C++ ta constructor virtual olamaz. Virtual keywordü constructor için kullanılamaz.
Ayrıca nonstatic member functionlar ve global functionlar sanal olamaz. Bu sentaks kuralı

class Base {
public:
	virtual Base(int); // bu olamaz.SENTAKS HATASI

};

Virtual ctor ihtiyacı var mı? Evet var.

---------------------------------------------------------------------------------------------


void car_game(Car *ptr)
{
	ptr->start();
}


*ptr nin türü nedir, char
*ptr nin dinamik türü nedir, runtime da belli olacak.
audi nesnesi ile çağrı yapılırsa runtime da audi olacak.Hatta bunu sorgulayan araçlarda var.

Buraya gelen arabanın bir kopyasını çıkartın...
Copy Ctor ile yapılamaz. Car mycar(*ptr); Böyle yaparsak olmaz.Çünkü Ctor virtual olamıyordu.Virtual dispatch devreye girmez.
1 - Car sınıfı abstract class ise abstract class türünden nesne oluşturamayız zaten.
2 - Diyelim ki abstract değil, nesnenin türü static tür olarak Car.Runtime da belli olmuyor mycar ın türü.
	Derleme zamanında oluyor.

Nasıl Kopyasını çıkartacağım?
Mesela, buraya mercedes gelirse onunla yarışacak bir araba oluşturulması gerekiyor ve o da mercedes olacak.
Bu durumda virtual constuctora ihtiyaç var.Dilde böyle araç yok.Kendimiz oluşturacağız.
Bu durumda virtual Ctor idiyom diyeceğiz buna.Ya da Clone idiyomu.Mülakat sorusu.

Car.h deki Base classa bir sanal function ekleyeceğiz.Hoca normalde smart pointer kullanıyor.
İdeali bu. Ama daha görmedik o yüzden kullanmıyoruz.


virtual Car* clone() = 0; //Base classta yazıldı
Bu pure virtual olduğuna göre bu sınıftan kalıtım yoluyla elde edilen sınıfların somut olmaları için 
bunu override etmeleri gerekiyor. Bmw bunu override ederse dinamik ömürlü bir bmw nesnesi oluşturup onun adresini döndürür.
Audi bunu override ederse Audi oluşturup onun adresini döndürecek.

Bmw sınıfı içinde implemente edelim inline olarak

Car* clone()override
{
	return new Bmw(*this); // new operatorüyle dinamik ömürlü bir nesne oluşturduk ama bunu copy ctor ile oluşturdum.
}

Yukarıdaki ile return new Bmw; arasındaki farka bakalım. bu olursa clone çağrıldığından aynısından bir tane daha oluşturur.
Mesela Bmw nun öznitelikleri olsa, yaşı rengi modeli...  ve clone functionu 5 yaşındaki kırmızı Bmw için çağrılmış olsun;
O zaman new Bmw(*this) buradaki yeni Bmw da 5 yaşında ve kırmızı olacak. Ama return new Bmw böyle olursa, oluşturduğum Bmw
Default init edilmiş olacak. Gri renk 0 yaşında son model olmuş olacak. 
Yani 
return new Bmw bu clone değil.
new Bmw(*this) bu ise clone.

Şimdi bunu alıp tüm derived class / türemiş classlara yazılır.Audi ye audi olanı, Mercedes e mercedes olanı

#include <iostream>
#include "car.h"
#include <conio.h>

void car_game(Car* p)
{
	Car* newcar = p->clone();
	p->start();
	newcar->start();
	_getch();
}

int main()
{
	for (;;)
	{
		auto c = create_random_car();
		car_game(c);
		delete c;
	}
}

ÇIKTI
-----
Mercedes has just started
Mercedes has just started
Fiat has just started
Fiat has just started
Renault has just started
Renault has just started
Volvo has just started
Volvo has just started
Mercedes has just started
Mercedes has just started

-------------------------------------

Dikkat 
Polimorfik sınıflarda kopyalama felakete sebep olur.
void car_game(Car *p)
{
	Car mycar = *p;  // burada object slicing var.Mercedes gitti Base kısmı kaldı gibi.
}					
				
Eğer Car abstact class ise bir sıkıntımız yok çünkü SENTAKS HATASI, yani uyarıyor ve işlemi yapmıyor.
Ama değilse yani polimorfik sınıfsa bu kod legal olduğundan, çok sıkıntılı bir durum. Object slicing var ve 
kod çalışmaya devam ediyor.

Böyle bir kod yazsak ne olur. Bundan bir fayda beklenemez.Bu hayırlı değil :D
bu duruma object slicing deniyor. Yani polimorfik nesneleri böyle oluşturursak object slicing olur.
Yani artık bunun Mercedes olma özelliği gitti içindeki Base kısmı kaldı sadece. Biz Mercedesin değil
arabanın kopyasını çıkardık.

2. Ektisi Virtual dispatch imkanı yok. Çünkü sınıf ismiyle yapılan çağrılarda virtual dispatch devreye girmiyordu.
Bu herzaman kötü. Normalde derleyici copy ctoru yazıyor. Bazı senaryolar dışında.Biliyoruz bunları.
Copy memberın delete edildiği durumlarda, 
dikkat!! abstract class değilse copy constructoru ve copy assignmentı delete et.
Bu yanlışlıkla object slicing olduğunda, sentaks hatası vermesini sağlıyor.

Car(const Car& other) = delete;
Car& operator=(const Car& other) = delete;


----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------


Virtual Destructor
------------------

class Base {
public:
	~Base()
	{
		std::cout << "Base Destructor\n";
	}
};

class Der : public Base {
public:
	~Der()
	{
		std::cout << "Der destructor\n";
		// buraya gelince yani sona, ctorun hayata getirdiği öğeler ve taban sınıfın alt nesnesi için Dtor çağrılacak.
	}
};

int main()
{
	Der myder;
}

objeler yaratıldı
Der Destructor
Base Destructor

Burası OK

----------------------------------------------------------------------

Polimorfik sınıf nesneleri birçok senaryoda dinamik olarak oluşturuluyor.

int main()
{
	Der* p = new Der;
	//

	delete p;
}

Burada da problem olmadı

----------------------------------------------------------------------

BURASI KRİTİK.

int main()
{
	Base* p = new Der; //Böyle yazınca sadece base destructor çalışır
	//

	delete p;
}

Delete operatörünün operandı olan adres Base * türden olduğu için derleyici Base in destuctorunu çağırdı.
Oysa burada hayata getirilen nesne der sınıfı türünden olduğu için Der in destructoru çağrılması gerekirdi.
Yani Der in aldığı kaynaklar geri verilmedi.Dahada kötüsü UNDEFINED BEHAVIOR Da oluşabilir.

Burada derleyici operator delete e de çağrı yapar. Operator delete kendisine gelen adresteki bellek bloğunu sisteme
geri veriyor. Ya p nin değeri olan adresle, dinamik ömürlü nesnenin adresi aynı değilse.
Türemiş sınıf nesnesinin adresini taban pointera atayınca, derleyici türemiş sınıf nesnesi içindeki taban sınıf 
nesnesinin adresini kullanıyor. Şimdi bu adres(p) türemiş sınıf nesnesinin adresi değilse.Yani bu adresteki bellek bloğu
türemiş sınıf nesnesi için allocate edilen bellek bloğu adresi değilse, o zaman başka bir bloğun adresini free etmiş 
oluyoruz.

Eğer 
a - Sınıf polimorfik bir sınıfsa ve dinamik ömürlü nesneleri taban sınıf pointerıyla yönetme ihtimali varsa
	bu durumda derleyici doğru kod üretmeli. Nasıl olacak. p nin adresi base* türünden olmasına rağmen
	derleyici eğer p hangi türden nesneyi gösteriyorsa, onun destructorunu çağırmalı.Mesela Mercedesi gösteriyorsa
	mercedesin destructorunu çağırmalı. Burada da destructor sanal olacak ve sanal destuctorun çağrılması durumunda
	p dinamik türü kullanılacak, p nin gösterdiği değer için. Bu şekilde birşekilde türemiş sınıf nesnesinin
	destructoru çağrılacak ve operator new ile elde edilen bloğun verilmesinde sıkıntı olmayacak.

NOT : Türemiş sınıf nesneleri taban sınıf pointerıyla delete edilecekse destructoru virtual yapacağız.
	Bu durumda destructor sınıfın public member func ı olacak.Bu arada destructor virtual ise türemiş sınıflar için 
	yazılmış destuctorlarda bunun override ı kabul ediliyor. Yani türemiş sınıflar için ilave birşey yapmaya gerek yok.
	Derleyici yazıyorsa sorun değil.

Base sınıfının destructorunu ekleyelim
virtual ~Base()
{
	
}

Eklendi
class Base {
public:
	virtual ~Base()
	{
		std::cout << "Base Destructor\n";
	}
};

class Der : public Base {
public:
	~Der()		// Burası ~Der() olacak, ~Base()override gibi düşünmüyoruz.~Base() zaten Basein Dtoru.
	{
		std::cout << "Der destructor\n";
		// buraya gelince yani sona, ctorun hayata getirdiği öğeler ve taban sınıfın alt nesnesi için Dtor çağrılacak.
	}
};

int main()
{
	Der myder;
}

taban sınıf dtoru virtual olduktan sonra aynı kodu tekrar derleyip çalıştırıyor.
Der Destructor
Base Destructor

Tekrar : Sınıf polimorfik ise mutlaka taban sınıfın destructorunu virtual yapmalıyız böylece türemiş sınıf nesneleri
taban sınıf pointerı ile delete edildiğinde veya handle edildiğinde bir problem olmasın.


TÜREMİŞ SINIF NESNELERİNİN TABAN SINIF POINTERLARIYLA KULLANILMASINI İSTEMİYORSAK
Taban sınıfın Destructorunu virtual değilde protected yaparız. Bu durumda taban sınıf ptr ını delete ettiğimizde
sentaks hatası oluşur.

int main()
{
	Base* p = new Der; 
	//
	delete p; // Burada sentaks hatası vermesini sağladık.
}

Burada olan şey, derleyici taban sınıfın destructorunu çağırdı.Derleyici delete operatörü olduğunda 
burada access control gerçekleştirdi ve destructor protected olduğundan sentaks hatası oluşur.
Artık zaten taban sınıf ptr ile delete etme compile time da bir hata olacak.Eğer türemiş sınıf nesnesini türemiş sınıf
ptr ile delete edersek bir sorun olmayacak çünkü taban sınıfın protected üyelerine türemiş sınıf erişebilir.



Aşağıdaki gibi yaparsak bir problem yok çünkü access controlden geçiyor.Taban sınıfın protected destructorunu çağırmak
sentaks hatası değil.
int main()
{
	Der* p = new Der;
	//
	delete p; // Sorun yok burada.
}

HERB SUTTER diyorki
Taban sınıfın destructorları virtual public yada nonvirtual protected olacak.
ikisinden birini seçmemiz gerekiyor.

Taban sınıfın destructorunun virtual olmaması polimorfik sınıflarda doğrudan bir kodlama hatası olarak görülüyor.
Sentaks hatası değil ama hata olarak görülüyor.

---------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------

Global bir fonksiyonu sanal yapabilir miyiz?
Buna yönelik bir idiyom düşünelim.

int main()
{
	randomize();
	Car *p = create_random_car();
	cout << *p << "\n"; // Öyle bir kod yazacağız ki bu kod legal olacak

	p->run(); // burada hangi func ın çağrılacağı runtimeda belli oluyor.
}


cout << *p << "\n";
Öyle bir kod yazacağız ki bu kod legal olacak
Ayrıca bu kod çalıştığında *p nin dinamik türü yazacak.

1. çözüm : Car sınıfına aşağıdaki func eklenebilir.
Ama bu fonksiyon sanal olamaz yani polimorfik bir şekilde davranmaz.
Neden sanal olamaz çünkü global bir function.Ama sanal function çağırırsak olabilir.

inline std::ostream& operator<<(std::ostram& os,const Car& c)
{
	c.vprint(os); // çıkış akım nesnesinide kullanacağı için argüman yazdık.Bu vprint i pure virtual funciton
					// olarak ekleyeceğiz ve diğer diğer sınıflar bunu override edecek.Onlar override ederken Bmw
					// çıkış akımına im Bmw yazacak, audi ise im audi yazacak.
	return os;
}

virtual void vprint(std::ostream &os)const = 0; bunu Car sınıfına ekleyeceğim.
Dİkkat const member func yazdık.

Sırada bunu override etmek var.Bmw de override edelim sonrada diğerlerine kopyalarız.
const imzanın bir parçası olduğundan, override sözcüğü consttan daha sonra olmalı.

virtual void vprint(std::ostream &os)const override // BURAYA DİKKAT!!!!!
{
	os<< "Im a BMW\n";
}

Audi skoda Mercedes hepsi içine yazılacak.Sonra yaz.


int main()
{
	randomize();

	Car* p = create_random_car();
	p->start();
	cout << *p << "\n";

	p->run();
} 

TEST ET BUNU


Son 3 başlığı tekrar edelim.
1 - Virtual Ctor / clone idiom
2 - Virtual Dtor
3 - Global funcların sanala olamayacağını ama idiyomatik bir yapıyla sanallıktan faydalandık.


====================================================================================================================
====================================================================================================================
====================================================================================================================

POLİMORFİK LİSTELER
-------------------
Birçok uygulamada nesnelerin gerçek türlerini bilmeden bir containerda tutmamız gerekiyor.
Bunlar bir list yada vector container olabilir.veya başka
Fakat polimorfik şekilde davranacak bunlar.

Mesela araba oyunununda 50 araba var fakat bunlar bir veri yapısında tutuluyor sonra bunlar yarışa katılıyor.
Yarışta hepsinin startı çağrılacak run ı çağrılacak gibi.

Dolayısı ile arabaları containerda tutuyoruz. bunların ortak interface ini kullanarak işimizi görüyoruz.

Bunu göstermek için eski usül pointer kullanacağız.Ama normalde dinamik ömürlü nesneler için bunları raw/ham
pointerlarda tutmak iyi bir fikir değil.raw/naked pointer
ör: int *, car *, data*...

C den gelen pointerlara raw pointer deniyor. Birde smart pointerlar var.Bunlar aslında kendisi pointer değil ama pointer
like interface e sahip. Kullanım amacı dinamik ömürlü nesnelerin hayatını kontrol etmek.

unique_ptr
shared_ptr olarak ikiye ayrılıyor.

biz bunları kullanmayacağız. Başka bir araç kullanacağız.

#include <vector>
#include <iostream>
#include <conio.h>

int main()
{
	vector<Car *>cvec;

	randomize();

	for(int i = 0 ; i < 100; ++i)
	{
		cvec.push_back(create_random_car()); // böylece bu vectörün herbir elemanı polimorfik bir nesnenin elemanını tutan pointer
	}

	for(auto p : cvec)
	{
		cout << *p << "\n";
		p->start();
		p->run();
		p->stop();
		_getch();
	}
		
	for(auto p : cvec)
	{
		delete p;
	}
}

Bazende kesin türünün ne olduğunu bilmeden bunları bir containerda tutabiliyoruz.
NOT : auto_ptr vardı eskiden depricate oldu.

Burada bir soru üzerine virtual destructor konusuna girdi hoca.
Tekrar anlattı. İyi oldu.

===========================================================================================================================
===========================================================================================================================
===========================================================================================================================


Variant Return Type - Covariance
--------------------------------
Virtual function ve bunların override edilmesine yönelik kuralları tekrar hatırlayalım.Tamamen bunlarla alakalı çünkü.
Bir sınıfın sanal fonksiyonunu override eden türemiş sınıf fonksiyonu nasıl olmalı?
Hem imzası hemde return type ı aynı olacak. Eğer imza aynı return değeri türü farklıysa 
derleyici durumu sentaks hatası olarak değerlendiriyor.

class Base{
public:
	virtual int foo(int);
};

class Der : public Base{
public:
	float foo(int); //SENTAKS HATASI.Vİrtual olmasaydı sentaks hatası değildi.
};					//ayrıca burada covariant olma durumu ile alakalı bir hata verdi.


Covariance
----------
Taban sınıfın bir virtual member functionunu override eden türemiş sınıf fonksiyonu hem aynı imzada hemde ayrı return değeri
türünde bir fonksiyon bildirmek zorunda.Tekrar yazdık.İmza aynı return değeri türü farklı bir fonksiyon bildirerse override keywordu
kullanmasada sentaks hatası olacak.Bunun bir istisnası var.Covariance bu istisna kurala verilen isim

Eğer türemiş sınıf taban sınıfın virtual member func ını override ederken başka bir return değeri türü kullanırsa, bu özel durumda
sentaks hatası olmayacak.Buna variant return type veya covariance deniyor.

Eğer taban sınıfın virtual member func ının return değeri bir sınıf türünden pointer veya referans ise türemiş sınıf bunu 
override ederken(aşağıdaki foo için konuşuyoruz), bu fonksiyonun return değeri türünü değiştirebilir. A sınıfı türünden değilde 
A dan kalıtım yoluyla elde edilmiş bir sınıf türünden pointer yapabilir. Nede olsa türemiş sınıf public kalıtımında aynı zamanda
taban sınıf türünden kabul ediliyor.

class A{
};

class DerA : public A{	// Bu sınıf A dan public kalıtım ile elde edildiğine göre, her DerA nesnesi bir A nesnesidir
						// foo da A nesnesi adresi döndürüyor.O zaman alttaki Der classı da DerA türünden bir foo functionu döndürebilir.
};						// Buna covariance deniyor.

class Base{
public:
	virtual A* foo(int);
};

class Der : public Base{
public:
	DerA* foo(int)override; // bunu yazdık en son.DerA, A dan public kalıtım yoluyla elde edilmeseydi sentaks hatası olacaktı.
};				



BUNLARIN AYNISI REFERANS SEMANTIĞI IÇINDE GEÇERLI
-------------------------------------------------

class A{
};

class DerA : public A{	
						
};						

class Base{
public:
	virtual A func(int); // & veya * yok. Kuralın olmabilmesi için * veya & olmalı.
	virtual A& foo(int);
};

class Der : public Base{
public:
	DerA func(int)override; // Bu durumda burası sentaks hatası olur.
	DerA& foo(int)override; //burası covariant oldu
};

2:30 da bununla alakalı grafikte çizdi hoca.
Pointer yada referans semantiği olacak. Yoksa override edemez.Covariant olmaz.


NEDEN BÖYLE BİRŞEY VAR?

class A{
};

class DerA : public A{

};

class Base{
public:
	virtual A* foo(int);
};

class Der : public Base{
public:
	A* foo(int)override;
};

int main()
{
	Der myder;
	DerA *p = myder.foo(5); // SENTAKS HATASI.Burada taban sınıfı türemişe atama var. Downcasting var. 
							// A = DerA ok ama DerA = A sentaks hatası. 

	//legal olması için static cast kullanılmalı
	DerA *p = static_cast<DerA *>(myder.foo(12)); // bu şekilde olur.
}

YAZDIĞIMIZ CAR SINIFINDA GÖSTERİLECEK
-------------------------------------
2:38 gösterdi.

BMW içinden Car* clone()override yerine Bmw* clone()override yapılabilir covariance sayesinde.
Çünkü Bmw Car sınıfından kalıtım yoluyla elde edilen bir sınıf.

Covariant kullanmadığımız örneğe geri dönüp sakıncayı görelim? kod yazmak neden zor

int main()
{
	Bmw *p = new Bmw;
	Bmw *pb = p->clone(); // Covariant yapmazsak clonun return değeri car *. dolayısı ile burada sentaks hatası oluşur
							// ama covariant yaparsak return değeride bmw * olursa sorun kalmıyor zaten :D
							// NOT : türemiş taban sınıfına otomotik dönüşüyor, ama taban türemişe otomotik dönüşmüyor.
	Legal olması için
	Bmw *pb = static_cast<Bmw *>(p->clone()); // Bu şekilde covariant olmadan legal olur

	covariant varsa zaten aşağısı geçerli :D
	Bmw *pb = p->clone();

}

Bu örnekte covarianc yapıp denedi hoca, geri alıp denedi...
Test etti.


MOLA

==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================
==================================================================================================================================

INHERITED CONSTRUCTOR
---------------------

Sınıf içinde yapılan using bildirimini incelemiştik.Bunda taban sınıftaki isim türemiş scope içinde visible hale geliyordu.
Aşağıdaki işleri yapmak kolaylaşıyordu.

1 - taban sınıfın üye funct ile türemiş sınıfın üye functionu aynı isimli farklı imzalara sahip olsa bile overload değiller
	ama using bildirimi ile taban sınıftaki ismi türemiş sınıfta visible hale getirirsek bir overloading oluşturuyorduk.

2 - başka yol, türemiş sınıfa yeni function ekleyip onun aldığı argümanları taban sınıfın aynı isimli member func a pass etmesi,

3 - Protected bir fonksiyonu public interface de yapacağımız using bildirimi ile doğrudan türemiş sınıfın public functionu gibi 
	türemiş sınıf clientlarının kullanabilmesini sağlayabiliyorduk.Yoksa yine türemiş sınıfa aynı isimli bir func yazıp, taban sınıfın
	protected func ına çağrı yapmak gerekecekti.


Using eskiden de vardı ama modern C++ ta kapsamı baya genişledi.
Cosntructor içinde using bildrimi yapabiliyoruz.Ctor için using bildirimi yaptığımızda, bu sefer sanki diğer member funclarda olduğu gibi
taban sınıfın ctorlarıda türemiş sınıf içinde visible hale geliyor.

DİKKAT!!
BUNA TABAN SINIFIN SPECIAL MEMBER OLAN CTORLAR DAHIL DEĞIL!!!!!!!!!!!!!
AŞAĞIDADA YAZDIK. EĞER IMPLICITLY DEFAULT EDILDIYSE TÜREMİŞ SINIFIN SPECİAL MEMBER FUNCLARI KULLANILACAK ZATEN.
DİĞER PARAMETRELİ CTORLARDA BASE CLASSTAN INHERIT EDILECEK

class Base{
public:
	Base() = default;
	Base(int);
	Base(int, int);
	Base(double);
	void foo();
	void func();
	void f();
};

İstediğimiz base gibi bir sınıf.Base in public interface ini kendi interface ime katmak istiyorum
Belki bir takım eklemelerde yapacağız.

class Der : public Base{
public:
	void g();
};

int main()
{
	Der myder;
	myder.foo();
	myder.func();
	myder.f();
	myder.g();

	Bir sorun var.Evet her der bir base, Base mybase(12,12); bunu çağırabilecektim ama myderi kullanırken
	Der myder(12,12); i kullanayım dersem SENTAKS HATASI. Türemiş sınıf scope unda arayacak ve bunu bulamadığı için SENTAKS HATASI.

	EĞER inherite Ctor olmasaydı ne yapmamız gerekirdi?
	Herbir Ctor ı Der içinde de yazacaktım ve bu ctorlar ctor init list ile Base alt nesnesini oluştururken Base in Ctoruna pass edecek.

}

---------------------------------------

Kodun yeni hali aşağıda
class Base{
public:
	Base() = default;
	Base(int);
	Base(int, int);
	Base(double);
	void foo();
	void func();
	void f();
};


Türetilmiş sınıfı aşağıdaki gibi yazıyoruz
class Der : public Base{
public:
	Der(int x) : Base{x} {  }
	Der(int a, int b) : Base{a,b} {  }
	Der(double d) : Base{d} {  } 
	void g();
};

int main()
{
	Der myder(12,12); // artık burası Legal oldu çünkü ctoru eklendi.
	Der myder2(12); // artık burası Legal oldu çünkü ctoru eklendi.
	Der myder3(1.2); // artık burası Legal oldu çünkü ctoru eklendi.
}

Hem yukarıda zahmet var hemde kodlama hatası riski var.

Modern C++ta Inherited Constructor geldi.

-----------------------------------------------------------------------------------------------------------------

Inherited Constructor ile yazalım
---------------------------------
SENTAKS
using classname::classname; 

class Base{
public:
	Base() = default;
	Base(int);
	Base(int, int);
	Base(double);
	void foo();
	void func();
	void f();
};


class Der : public Base{
public:
	using Base::Base; // Bu bildirime dikkat.Bunun sayesinde Taban sınıfın Ctorları türemiş sınıfın scope u içinde visible hale geldi
	void g();			// Dolayısı ile artık derleyici Der myder(12); gibi bir nesne oluşturunca taban sınıfın Ctorune bu argümanları
};						// göndermiş olacak.
						
int main()				
{
	Der myder(12);
}

1 - Special member funclar geçerli değildi.Bunlar taban sınıftan alınmıyor.Yani türemiş sınıfın bu funcları var
2 - Eğer bu bildirimle birlikte türemiş sınıfın kendi Ctorlarıda varsa, hem using ile Base in Ctorları hemde 
	Der in Ctorlarını yazarsak, Der sınıfının kendi Ctorlarının önceliği var.

NOT : BIZIM ISTEDIĞIMIZ CONSTRUCTOR DER IN DE ELEMANLARI INIT EDECEKSE INHERITED CTOR IŞIMIZI GÖRMEZ!!!!!!!!!!!!!!!!!

ÖRNEK Aşağıda
class Der : public Base{
public:
	using Base::Base; 
	Der() = default;
	Der(int);
	void g();			
};						

int main()
{
	Der myder(12); //Der sınıfının int parametreli ctoru çağrılır. Der(int) yani.Öncelik Der in.
}

-------------------------------------------------------------------------------------------------------------------

BURADA ENTERESAN BİR DURUM VAR

class Base{
protected:
	void func(int);
};

class Der : public Base{
public:
	using Base::func; // herhangibir member func ismini derived class içinde visible hale getiriyor.

};

int main()
{
	Der myder;
	myder.func(12); //burası ok
}

----------------------------------------------------------

YUKARIDAKI ÖZELLIK INHERITED CTOR OLDUĞUNDA GEÇERLI DEĞIL.
class Base{
protected:
	Base(int);
};

class Der : public Base{
public:
	using Base::Base; 

};

int main()
{
	Der myder(12); //SENTAKS HATASI. Normalde Legal olmasını bekleyebiliriz.Ama değil.Garip bir kural.
}					// inherited Ctor için bu özellik geçerli değil.




NOT : BIZIM ISTEDIĞIMIZ CONSTRUCTOR DER IN DE ELEMANLARI INIT EDECEKSE INHERITED CTOR IŞIMIZI GÖRMEZ!!!!!!!!!!!!!!!!!

class Base{
public:
	Base() : mx{0} { }
	Base(int x) : mx{x} {  }
	void print()const
	{
		std::cout << "mx = " << mx << "\n";
	}
private:
	int mx;
};

class Der : public Base{
public:
	using Base::Base; // Bu bildirime dikkat.Bunun sayesinde Taban sınıfın Ctorları(speciallar hariç) türemiş sınıfın scope u içinde visible hale geldi
	void print()const
	{
		Base::print(); //buradan da mx i çağırıyor
		std::cout << "mval = " << mval << "\n";
	}
private:
	int mval;
};

int main()
{
	Der myder(40);
	myder.print(); //Burada myder içindeki mvalin değerini ve base içindeki mx in değerine baktık
}					// base içindeki değer st edilmiş ama mval Garbage value da.

Yani Der içindeki  ctor devreye girmiyor, Base in içindeki devreye giriyor.
O argüman base in ctoruna parametre olarak geçilmesini sağlıyor bu araç.

----------------------------------------------------------------------------------------------------------------------

Default Member İnit yada In Class İnit kullanalım

class Base{
puıblic:
	Base() : mx{0} { }
	Base(int x) : mx{x} {  }
	void print()const
	{
		std::cout << "mx = " << mx << "\n";
	}
private:
	int mx;
};

class Der : public Base{
public:
	using Base::Base; // Bu bildirime dikkat.Bunun sayesinde Taban sınıfın Ctorları türemiş sınıfın scope u içinde visible hale geldi
	void print()const
	{
		Base::print(); //buradan da mx i çağırıyor
		std::cout << "mval = " << mval << "\n";
	}
private:
	int mval{100};
};

int main()
{
	Der myder(40);
	myder.print(); // Default Member initten dolayı mval 100, mx ise 40 oldu.
}


SET EDILECEK KENDI MEMBERLARIMIZDA VARSA, TÜREMIŞ SINIF CTORUDA YAZACAĞIZ YADA DEFAULT MEMBER INIT ILE INIT EDECEĞIZ.

======================================================================================================================================
======================================================================================================================================
======================================================================================================================================

MULTIPLE INHERITANCE
--------------------
Zamanında bir tepki çekmiş. Dili gereksiz bir karmaşık yapıya sokuyor ama dilinde karmaşık hale gelmesi bir dezavantaj.
Görmediğimiz bir nokta var.Derleyiciyi yazanlarda var. Bunu yazmakta kolay değil. Bazı araçların yazılması compiler yazanlar 
için büyük maliyet.

Multiple inheritance : A ve B sınıflarının public interface lerini devralarak yeni bir C sınıf oluşturma işlemine deniyor.
Burada Her C bir A dır aynı zamanda Her C bir B dir. A gereken yerde de C yi kullanabilirim B gereken yerde de C yi kullanabilirim.
Single inheritance deki tüm özellikler burada da var. Burada C sınıf nesneleriyle A dan ve B den alınan functionlarda çağrılabilecek.
Updasting sözkonuısu olduğunda C nesnesi adresini A ya veya B ye atayabileceğim. A& veya B&, C ye bağlanabilecek.
A nın ve B nin virtual funclarını C override edebilecek.
Bir C nesnesi Construct olunca, içerisindeki A ve B nesneside construct olacak.
C nesnesi Destroy olduğunda, onun içindeki B nesneside A nesneside destroy olacak.
Multiple İnheritance bunun aracı. Multi-level inheritance, car -> fiat->fiat124 gibi. Hiyerarşideki derinliği ifade ediyor.
Multiple inheritance ise bir araç.

NEsne yönelimli programlama dillerinin çoğunun doğrudan desteklediği bir araç değil.
Bazı işleri kolaylaştırıyor ve standart kütüphanede kullanıyor.


SENTAKS:
class A{
};

class B{
};

class C : public A, public B{
	
};

Aşağıdaki gibi yazsaydım C, A ve B den private kalıtımı yoluyla elde edilmiş olacaktı.
class C : A, B{

};


Burada ise A dan public, B den ise private kalıtımı yoluyla elde edilmiş.
class C : public A, B{

};


Aşağıda ise public kalıtım olur hem A hemde B için
struct C : A, B 
{

};

-------------------------------------------------------------------------------

class A{
};

class B{
};

class X{
};

class C : public A, public B, public X{ // sayısının fazla olması sentaks açısından engel değil.
	
};


---------------------------------------------------------------------------------


class A{
public:
	void afunc();
};

class B{
public:
	void bfunc();
};

class C : public A, public B, public X{ // sayısının fazla olması sentaks açısından engel değil.
public: 
	void cfunc();
};

int main()
{
	C cx;
	cx. // afunc, bfunc, cfunc hepsi geldi.Hepsi çağrılabilir.
	
	cx.afunc();
	cx.bfunc();
	cx.cfunc(); // hepsi çağrılır.
}

Burada multiple inheritance ile elde edilme var.Bu durumda C nin içinde bir A birde B nesnesi var.

*/



#include <iostream>
#include "car.h"
#include <conio.h>

void car_game(Car* p)
{
	Car* newcar = p->clone();
	p->start();
	newcar->start();
	_getch();
}

int main()
{
	Bmw* w = new Bmw;
	w->run();
}
