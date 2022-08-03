/*

Operator new da kalmıştık. Başarısız olduklarında hemen exception throw etmiyorlardı.
Kısaca Operator new func özetledik.

Overload edilemeyen bir operator new var. Onuda biliyoruz.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PLACEMENT NEW
-------------
Bu ifadeler ve buna bağlı olarak placement new ne iş yapıyor. Burada amaç bir yeri allocate etmek yerine zaten varolan bir yerde nesneyi hayata getirmek. 
Otomatik ömürlü nesnenin yerini derleyici ayarlıyor. PLACEMENT NEW OVERLOAD EDİLEMİYOR !!!!!!

SENTAKS
new(address)Sınıf_türü(Varsa_Argümanlar);

Placement new da çağrılan operator new
void* operator new(size_t size, Heap*); // mesela bu placement new. İleride görüldü 

Dinamik ömürlüde biraz daha farklıydı. new->operator new->ctor.... 
sizeof değeri kadar yer ayıracak


int main()
{
	char buffer[sizeof(Date)]; 
	// Burası sizeof date olduğundan, bu bellek alanı bir date nesnesinin storage ı olarak kullanılabilir.
	// Çağıran ctorun this adresi olarak bu bufferın adresi alınabilir.

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << static_cast<void *>(buffer) << "\n";
	//Bu buffer adresinde bir date nesnesi hayata getirmek istiyoruz.Burada kullanılan new operatorlerine placement new deniyor

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	Date *p = new(buffer)Date{1,4,1987}; 
	
	SENTAKS
	new(address)Sınıf_türü(Varsa_Argümanlar);
	
	// Diğer newlerde olduğu gibi ifadenin ürettiği değer Date nesnesinin adresi.
	// Burada bir allocation yok!!!!! Burada çağrılan operator new func. Buradaki operator new overload edilemiyor. 
	// Overload edilemeyen : void *operator new(void *vp, size_t size) { //kodlar...	return vp;	}
	// Çağrılan operator new yukarıdaki, dolayısıyla şimdi çağrılan operator new bu olduğu için bizim verdiğimizi
	// return ediyor ve dolayısıyla this adresi olarak bu adres kullanılacak.
	// Date içinde this yazdırıldı.Buffer adresiyle this aynı olduğu ortaya çıktı.

	Date.h den ctorun çağrıldığını göstermek için değişiklik yapıldı.Test amaçlı yaptı hoca ben şimdilik dokunmadım.

	----------------------------------------------------------------------------------------------------------------------------------------------------------
		
	delete p;   //TANIMSIZ DAVRANIŞ OLUR ÇÜNKÜ DESTRUCTOR VE SONRA OTOMATIK ÖMÜRLÜ NESNENIN ADRESINI FREE ETMEYE ÇALIŞTIĞIMIZDAN ÖTÜRÜ.
				//AMA DELETE ETMEZSEKTE DESTRUCTOR ÇAĞRILMAYACAK BUNU YAPMAZSAK DOĞRUDAN DESTRUCTOR ÇAĞIRACAĞIZ.

	----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	p->~Date(); // BUNU ÇAĞIRACAĞIZ.DESTRUCTORUN ÇAĞRILACAĞI TEK ÖZEL DURUM BUYDU

}

BURADA ÇAĞRILAN OPERATOR NEW OVERLOAD EDİLEMİYOR.
void operator new(size_t, void *vp)
{
	return vp;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTHROW NEW
-----------

Exception throw etmediği için nothrow new deniyor. Nullptr döndürüyor hata oluşursa. Geçmişte yazılmış kodlarla uyum sağlanması için halen korunmuş, 
özel durumlar için ayrılmış bir operator

Nothrow new, başarısız olduğunda exeption throw etmeyen new.

Standart kütüphanede kullanılan bir teknik var.Sadece function overloading amaçlı bir imza farklılığı için empty classlar oluşturuyor.

struct nothrow_t
{

}nothrow; // tür define edilmiş ve bu türden global bir nesne tanımlanmış

void func(int, nothrow_t) // burası nothrow da olabilir.
{

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SENTAKS
new(nothrow)	

Burada derleyicinin ürettiği kod, functiona argüman olarak gönderdiğimiz nothrow nesnesini çağırdığı operator new e argüman olarak gönderiyor, 
böylece func overload resolutionla bu sefer parametresi nothrow_t türünden olan operator new çağrılıyor. Bu operator new da diğerlerinden
farklı olarak exception throw etmiyor.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Data{
	char buffer[1024 * 1024];
};

int main()
{
	vector<Data *>vec;

	try{
		for(;;){
			vec.push_back(new Data); //normalde bir süresonra exception throw etmeli
		}
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught :" << ex.what() << "\n";
	}

	std::cout << "vec.size() = " << vec.size() << "\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTHROW NEW EXCEPTION THROW ETMIYOR

int main()
{
	vector<Data *>vec;
	
	for(;;)
	{	
		auto pd = new(nothrow)Data;
		if(!pd) // Girerse buraya nullptr döndürdü demektir.
		{
			break;
		}
		vec.push_back(pd);
	}

	std::cout << "vec.size() = " << vec.size() << "\n";

}

==========================================================================================================================================================================================


ATTRIBUTE
---------
Kısaca buraya girildi.
MODERN C++ ile eklendi ama devam eden süreçte sürekli yenileri eklendi.Bunlar extension değil standart ama derleyiciler kendi attrübutelarını ekleyebiliyorlar.
Productionda kullanılması gereken yerde kesinlikle kullanılmalı.Gidipte printf nodiscard olarak bildirilseydi rahatsız ederdi

TEMEL SENTAKS
[[]] 
[[nodiscard]] --> Tipik bir attribute

Genel olarak bunlar derleyicinin uyarı mesajı vermesini yada vermemesini sağlayan yapılar.
Bunun return değerini kullanmayı şart koşuyor. Bazı durumlarda hayati önem taşıyor.

Static kod analizi yapan programlarda bunları dikkate alıyorlar.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

isprime functionuna nodiscard ekleyince return değerini kullanmak zorunda kalıyoruz. Çıkartınca zorunlu değiliz.

[[nodiscard]]
bool isprime(unsigned long long int val); // Bildirimde var

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	vector<int> ivec;

	ivec.empty(); // return değerini kullanmadığımız için hata veriyor.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

void f1();
void f2();
void f3();
void f4();

int main()
{
	int x;

	cin >> x

	switch(x)
	{
	case 1: f1(); // Burası şüpheli. Burada programcı %5 ihtimal bilerek yapmış olabilir. C de yorum olarak fallthrough yazılabilir.
	case 2: f2(); break;
	case 3: f3(); break;
	case 4: f4(); break;
			
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++17 de nodiscard eklenmiş.
C++17 de fallthrough eklenmiş.


int main()
{
	int x;

	cin >> x

	switch(x)
	{
	case 1: f1(); [[fallthrough]]; // bu olduğunda uyarı mesajı vermeyecek. Olmazsa vermesi gerekir. SONDAKİ NOKTALI VİRGÜLE DİKKAT!!!!!
	case 2: f2(); break;
	case 3: f3(); break;
	case 4: f4(); break;

	}

}

BUNLARLA İLGİLİ VİDEOLAR PAYLAŞACAK HOCA

==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================

OPERATOR NEW VE OPERATOR DELETE FUNCTIONLARININ SINIFLAR İÇİNDE OVERLOAD EDİLMESİ
---------------------------------------------------------------------------------
2 araç var. 

1 - Standart Library diyorki operator delete ve operator new funclarını global düzeyde overload et hangi tür olkursa olsun,
bir bellek alanı allocate edileceği zaman senin operator new / delete funcın çağrılsın

2 - Sınıf için operator new in overload edilmesi, o sınıf türünden dinamik ömürlü nesne oluşturduğumuz zaman o çağrılacak.O sınıf türden değilde
başka sınıf türünden oluşturulduğu zaman çağrılmayacak.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOK ÖNEMLİ BİR ÖZELLİK!!!!!!!!!!!!!!!!!!
STATIC KEYWORD OLMAMASINA RAĞMEN FUNCTION SINIFIN STATIC MEMBER FUNC I KABUL EDILIYOR.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

class Myclass {
public:

	Myclass()
	{
		std::cout << "Myclass() this : " << this << "\n";
	}

	~Myclass()
	{
		std::cout << "~Myclass() this : " << this << "\n";
	}

	void* operator new(std::size_t n) // Static yazsakta yazmasakta static member func olarak kabul ediliyor.Nonstatic gibi görünüyor ama değil
	{
		auto p = std::malloc(n);
		std::cout << "Myclass::operator new called! n = "  << n <<"\n";

		if (!p)
		{
			throw std::bad_alloc{};
		}

		std::cout << "address of allocated block = " << p << "\n";
		return p;
	}

	void operator delete(void* vp)  // AYın şekilde static tanımlanlanıyor.
	{
		std::cout << "Myclass::operator delete called! n = "  << vp << "\n";
		free(vp);
	}

private:
	char buffer[1024]{};

};


int main()
{
	auto p = new std::string; // bizim yazdığımız oper new çağrılmayacak

	std::cout << "sizeof(Myclass) : " << sizeof(Myclass) << "\n";
	auto px = new Myclass;	// Şimdi bizim sınıf türünden nesne yaratıldı ve bizim yazdığımız oper new çağrıldı

	delete px; // bizim yadığımız operator delete çağrıldı şimdi.

	ÇIKTI
	-----
	sizeof(Myclass) : 1024
	Myclass::operator new called! n = 1024
	address of allocated block = 0111DD60
	Myclass() this : 0111DD60
	~Myclass() this : 0111DD60
	Myclass::operator delete called! n = 0111DD60

	----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto px = ::new Myclass; // Global new çağrıldı
	::delete p; // global delete
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NEDEN BUNLARI OVERLOAD EDELİM?
BU KISMI DAHA ÇOK LIBRARY IMPLEMENTASYONU TARAFI İÇİN.
MEMORY LEAK YADA RESOURCE LEAK DURUMLARI İÇİN KENDİ OPERATOR NEW VE OPERATOR DELETE
FUNCTIONLARIMIZI YAZABİLİRİZ.  YİNE ÇILGIN SCOTT MEYERS IN KİTABINDA VAR BUNLAR

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOK GÜZEL UZUN BİR ÖRNEK.
OPERATOR NEW VE DELETE İ BİR SINIF İÇİN OVERLOAD EDECEĞİZ. NORMAL ALLOCATOR DEĞİLDE FARKLI BİR ALLOCATİON STRATEJİSİ OLUŞTURACAĞIZ.
BAŞTAN SINIF STATIC BİR BELLEK ALANINI DİNAMİK ÖMÜRLÜ NESNELERİN OLUŞTURULMASI DURUMUNDA KULLANILMAK ÜZERE BLOKE EDECEK.MESELA EMBEDDED SİSTEMLER İÇİN
BUNU KULLANABİLİRİZ. EMBEDDED SİSTEMLERDE HEAP KAVRAMI YOK. BURADA STATIC ÖMÜRLÜ BİR DEĞİŞKENİ BİR BELLEK HAVUZU OLARAK KULLANACAĞIZ.


BURADAKİ ÖRNEK ÖNEMLİ YENİ BİR HEADER FİLE YARATTI.

Heap olmayan gömülü sistemler için örnek.

Header file
-----------
class Myclass {
public:
	constexpr static size_t buffer_size = 1024;
	constexpr static size_t max_no_of_dynamic_objects = 100;
	void* operator new(size_t n); //static yazmasakta bunlar static funclar
	void operator delete(void*);

private:
	unsigned char m_buf[buffer_size]{};
	static unsigned char s_buffer[]; // bizim heap imiz gibi kullanılacak.Burada max object kadar öğeyi tutacak kadar bellek alanı olacak
	static bool s_flags[]; // YUkarıdaki bufferın hangi indisli elemanların kullanımda olup olmadığını tutacak.
};


Code File
---------

using namespace std;

unsigned char Myclass::s_buffer[max_no_of_dynamic_objects * sizeof(Myclass)];
bool Myclass::s_flags[max_no_of_dynamic_objects]{};

void* Myclass::operator new(size_t n)
{

	using namespace std;
	auto iter = std::find(std::begin(s_flags), std::end(s_flags), false);
	if (iter == end(s_flags))
	{
		throw std::bad_alloc{};
	}

	auto idx = iter - begin(s_flags); // bulursa indexi verdi bize
	s_flags[idx] = true;
	return s_buffer + idx * sizeof(Myclass);
}



void Myclass::operator delete(void* vp)
{
	std::cout << "Operator delete called : " << vp << "\n";
	if (!vp)
		return;

	auto idx = (static_cast<unsigned char*>(vp) - s_buffer) / sizeof(Myclass);
	s_flags[idx] = false;

	std::cout << "idx = " << idx << "\n";

}


Ana kod file

int main()
{
	using namespace std;
	vector<Myclass*>myvec;
	for (size_t i = 0; i < Myclass::max_no_of_dynamic_objects; ++i)
	{
		//auto p = new Myclass;
		myvec.push_back(new Myclass);
	}

	std::cout << "myvec.size() = " << myvec.size() << "\n";

	delete myvec[0]; // veya delete myvec.pop_back();
	//delete myvec[16]; da test edilebilir.
	getchar();

	try {
		myvec.push_back(new Myclass);
	}
	catch (const std::exception& ex)
	{
		std::cout << "exception caught : " << ex.what() << "\n";
	}
}

==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================


SMART POINTERS
--------------

1. Ptr dinamik ömürlü bir nesneyi mi gösteriyor? Bunun için kodu ayrıntılı incelemek gerekiyor.
2. Ptr delete edilmeli mi? Bu herşeyden önce new operatorlerinden biriyle tutup tutmadığı ile ilgili.
3. Dinamik ömürlü nesneyi gösteriyorsa, Bu bir array mi yoksa tek bir nesnes mi ? Bunun içine kodu detaylı incelemek gerekiyor
4. Delete edilmiş mi edilmemiş mi ? BUnunda cevabı doğrudan yok :D:D (Dangling mi değil mi ?)
5. Ya başka bir pointer kullanıyorsa? Bu da delete edilirse dangling pointer olur
6. Her delete edilen nesne için loglama gerekiyorsa yada başka veri yapıları azı işlemler yapılacaksa

Pointerlar dinamik ömürlü nesnenin hayatını kotnrol ediyorsa, hem zorluk var hemde risk farktörü var

Riskler
1. Memory leak
2. Resource leak
3. Double deletion
4. nullptr olma durumu? bazı pointerlar için bu ihtimal var bazıları nullptr olamıyor!!!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ancient C++ ta auto_ptr vardı. Bu yeterli bir sınıf değil.Dilin imkanlarının taşıma semantiği desteği olmayınca ancak bu kadar yetenekli olabilmiş.
perfect forwarding, move semantics, variadic tempalates ve perfect forwarding vs gelmesiyle smart pointers halini aldı

Akıllı pointer: Kendisi pointer olmadığı halde pointer gibi davranan pointer intrface ine sahip sınıfları ifade ediyoruz. 
Iteratörlerde pointer interface ine sahip sınıflar ama onlara smart pointers demiyoruz. Smart pointers dinamik ömürlü nesnelerin veya kaynakların kontrolünü üstlenen 
pointer gibi davranan sınıflar. Bunun dışında boost un kendi smart pointer sınıflarıda var.

unique_ptr
shared_ptr
weak_ptr : Shared kullanınca oluşabilecek potansiyel problemleri gidermek için weakptr çıktı. Weakptr bir smart pointer sınıfı değil.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Unique sözcüğü eşsiz anlamında.Bizi bir kaynağa eriştirecek tek bir nesne yani bunun başkabir kopyası yok garantisini veriyor. 
Dinamik ömürlü nesneyi unique_ptr sınıfı nesnesine bağlarsak neyden eminiz?
Bir başka raw ptr veya unique ptr benim nesnemi göstermiyor. Buna sahibiz. Başka bir yerde başka bir nesne benim kaynağıma erişemez demek.
Buna exclusive ownership deniyor. Burada sahiplik el değiştirebiliyor ama 2 sahip olamıyor. Buna exclusive ownership deniyor.

Burada unique ptr nesnesinin hayatı bitince, bu dinamik ömürlü bir nesneyi gösteriyorsa destructoru çalıştırıyor yani kaynağı geri veriyor.
Rahat ve pratik bir kullanım sunuyor.
Garbage collectore benziyor ama aynısı değil. Burada memory leak ve resource leak durumları sözkonusu olmuyor.Çünkü fiilen delete etmem gerekmeyecek.
Buda tipik RAII idiyomlarından biri.

Çok farklı bir durum yoksa dinamik ömürlü nesneyi raw ptr ile kontrol etmeyeceğiz. 1. seçim unique ptr olmalı.

Shared ptr paylaşımlı sahiplik ilkesini implemente ediyor. Amaç kaynağı paylaşımlı olarak kullanmak.Birden fazla kod aynı kaynağı kullanır.
Son pointer hayatını kaybederse destructor çağrıldığından kalan son shared pointer ise  kaynağı geri verecek.

Unique_ptr shared_ptr ye göre çok daha fazla kullanılıyor.Çünkü genel olarak bir kaynağın kod tarafından kullanılıyor olması çok daha sık karşımıza çıkan bir ihtiyaç.
Unique ptr kullandık ama paylaşmak istedik diyelim bunu shared ptr ye de bağlayabiliriz.

Unique ptr yi öğrenmek istemeyenler halen new operatörünü kullanarak dinamik ömürlü nesneler oluşturuyor. Programcının bilinçsizliği olarak görülmeli.
Birkaç ihtimal var aslında.New kodları görülüyorsa,
1 - Çok alt seviyeli bire koddur ve new fililen kullanılmışyır
2 - Programcı akıllı pointerları kullanmayı bilmediğinden eski usul kod yazmıştır.

BAŞLIK DOSYASI MEMORY
#include <memory>

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


UNIQUE PTR
----------
Unique ptr nesnesinin amacı dinamik ömürlü nesnenin ayatını kotnrol etmek ve hayatını unque ptr nesnesinin hayatına bağlamak.
Unique ptr nin destructoru var. Bu sınıf wrapper. T türünden bir pointerı sarmalıyor. T hayatı kontrol edilecek dinamik ömürlü nesne adresini tutuyor.

Bir unique ptr nesnesi hayatta ise ya bir nesnenin hayattaki bir kaynağını üstlenmiş durumda yani dolu durumda, yada boş durumda yani hayatını kontrol ettiği bir
nesne yok durumda.

#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr{
public:
	~unique_ptr()
	{
		if(mp)
		{
			Deleter{}(mp); // Deleter isimli sınıftan geçici nesneye hayatı sonra erdirilecek nesneyi gönderiyor ve siliyor.
		}
	}
private:
	T *mp;
};


Burada 2. template tür parametresini değiştirip kendikimizi verebiliriz. Başka işlerde yapılacaksa 2. argümanı veririz. Örnekleri yapılacak.
Bu durumda bizim argüman olarak verdiğimiz function object in func call operator func ı çağrılacak

EN ÇOK MÜLAKAT SORULARI BURALARDAN GELİYOR!!!!!!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DEFAULT_DELETE
--------------
template <typename T>
struct default_delete
{
	void operator()(T *)
	{
		delete p;
	}
};

unique_ptr<Myclass> uptr;
unique_ptr<Myclass, default_delete<Myclass>> uptr; // Yukarıdaki ile aynı

DEFAULT DELETE
dinamik ömürlü nesnehnin hayatını kontrol edip hayatını unique ptr ye bağlıyor.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRIPLE İSİMLİ SINIF ÜZERİNDEN İŞLEMLER YAPILACAK

class Triple
{
public:
	Triple(int x, int y , int z) : mx{x}, my{y},mz{z}
	{
		std::cout << *this << " degerinde " << this << " adresinde triple nesnesi hayata geldi\n";
	}
	
	Triple()
	{
		std::cout << *this << " degerinde " << this << " adresinde triple nesnesi hayata geldi\n";	
	}
	
	~Triple()
	{
		std::cout << *this << " degerindeki " << this << " adresindeki triple nesnesinin hayatı sona erdi\n";	
	}

	void set(int a, int b, int c)
	{
		mx = a;
		my = b;
		mz = c;
	}

	friend std::ostream& operator<<(std::ostream &os, const Triple &t)
	{
		return os << "(" << t.mx << ", " << t.my << ", " << t.mz << ")";
	}

private:
	int mx{}, my{}, mz{};

};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include "triple"

int main()
{
	using namespace std;

	auto p = new Triple;

	std::cout << p << "\n";

	//Delete etmezsek destructor çağrılmaz

	ÇIKTI
	-----
	(0, 0, 0) degerinde 00EF4EC0 adresinde triple nesnesi hayata geldi
	00EF4EC0

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	auto p = new Triple;

	std::cout << p << "\n";

	delete p; // Şimdi desturctor çağrıldı

	ÇIKTI
	-----
	(0, 0, 0) degerinde 00A94EC0 adresinde triple nesnesi hayata geldi
	00A94EC0
	(0, 0, 0) degerindeki 00A94EC0 adresindeki triple nesnesinin hayati sona erdi

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	Triple t;

	std::cout << t << "\n";
	
	----------------------------------------------------------------------------------------------------------------------------------------------------------

	CTORA ARGÜMANDA GEÇİLEBİLİR.

	auto p = new Triple(1,5,7);

	std::cout << *p << "\n"; // Nesneyi yazdırdık.Overload yazmıştık

	delete p;

	----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	DİNAMİK ÖMÜRLÜ BİR TRİPLE NESNESİNİN HAYATINI KONTROL ETMEYE ADAY BİR UNİQUE NESNESİ OLUŞTURALIM
	
	std::unique_ptr<Triple> uptr;

	std::unique_ptr<Triple,std::default_delete<Triple>> uptr; // Yukarıdaki yazım ile burası aynı anlamda

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE PTR NESNESI DEFAULT INITIALIZE EDEBILIR.BOŞ DEMEK BU. HERHANGİBİR NESNENİN HAYATINI KONTROL ETMEZ DURUMDA DEMEK

OPERATOR BOOL FUNCTIONU İLE BİR UNİQUE NESNESİNİN BOŞ OLUP OLMADIĞINI KONTROL EDEBİLİRİZ

int main()
{
	std::unique_ptr<Triple> uptr;

	if(uptr)
	{
		std::cout << "Ben sana bos degilim\n";
	}
	else
	{
		srd::cout << "bombosum\n";
	}

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ŞİMDİDE DİNAMİK ÖMÜRLÜ BİR NESNENİN HAYATINI KONTROL ETSİN ŞİMDİ.

int main()
{
	std::unique_ptr<Triple> uptr{new Triple(1,2,3)};

	if(uptr)
	{
		std::cout << "Ben sana bos degilim\n"; // buraya girer
	}
	else
	{
		srd::cout << "bombosum\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİ İLE AYNI ANLAMDA

int main()
{
	std::unique_ptr<Triple> uptr{new Triple(1,2,3)};

	if(uptr.operator bool()) // buda kulalnılabilir.
	{
		std::cout << "Ben sana bos degilim\n"; // buraya girer
	}
	else
	{
		srd::cout << "bombosum\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOŞ MU DEĞİL Mİ ? BUNU ÇOK KULLANACAĞIZ

int main()
{
	std::unique_ptr<Triple> uptr{new Triple(1,2,3)};
	
	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOLU OLUP OLMADIĞINI ANLAMANIN BAŞKA BIR YOLU

Sınıfın doğrudan nullptr_t parametreli karşılaştırma functionu var == ve != 

int main()
{
	std::unique_ptr<Triple> uptr;

	Boş için
	if(uptr == nullptr)
	{
		std::cout << "bos\n";
	}

	Yada

	if(!uptr)
	{
		std::cout << "bos\n";
	}

	Dolu için
	
	if(uptr)
	{
		std::cout << "bos\n";
	}
	
	veya

	if(uptr != nullptr)
	{
		std::cout << "bos\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GET
---
Sınıfın ilginç bir fonksiyonu . Sınıfın sarmalanan adresini get ediyor. KESİNLİKLE DİKKATLİ KULLANILMALI !!!!!!
Mülkiyeti bırakma yapmıyor.Yani hayatını kontrol ettiği nesnenin hayatını devretmiyor.

int main()
{
	std::unique_ptr<Triple> uptr;

	uptr.get(); // Doluysa adresi döndürüyor. Değilse nullptr döndürüyor.


	Aşağıdakilerin hepsi uptr boş depilse yani doluysa demek.
	if(uptr.get()) { 	}
	if(uptr.get() != nullptr) { 	}
	if(uptr) { 	}
	if(uptr != nullptr) { 	}

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN ÖNEMLİ CONSTRUCTOR

Dİnamik ömürlü nesnenin adres isteyip unique_ptr nin veri elemanında tutuyor.

int main()
{
	std::cout << "main basliyor\n";
	
	{ //sadece scope
		std::unique_ptr<Triple> uptr{ new Triple{1,2,3} }; 

		//std::unique_ptr<Triple> uptr{ new Triple[10]  };  // UNDEFINED BEHAVIOR
	}
	
	std::cout << "main bitiyor\n";
	
	// Nesnenin scope u bitince unique ptr nin destructoru çağrılacak ve sarmaladığı nesneyi delete edecek.

}

ÇIKTI
-----
main basliyor
(1, 2, 3) degerinde 012E4EC0 adresinde triple nesnesi hayata geldi
(1, 2, 3) degerindeki 012E4EC0 adresindeki triple nesnesinin hayat? sona erdi
main bitiyor



------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
UB DURUMU

int main()
{
	std::cout << "main basliyor\n";
	{ 
		std::unique_ptr<Triple> uptr{ new Triple[10]  };  // UNDEFINED BEHAVIOR
	}
	std::cout << "main bitiyor\n";
}

NEDEN UB
BÖYLE YAPILDIĞINDA UPTR NIN DESTRUCTORU ÇAĞRILACAK, AMA BU DESTRUCTOR DELETE MP KODULE SAHIP. DELETE[]MP DEĞIL !!!!
ARRAY NEW VARSA ARRAY DEETE KULLANILMALI

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNU WELL DEFINED BEHAVIOR YAPMAK İÇİN

BU SINIFIN BIR PARIAL SPECIALIZATION I VAR DIZI TÜRLERI IÇIN KULLANILAN DELETE EDERKEN DELETE[] KULLANIYOR VE UB OLMUYOR.

VEYA KENDI DELETERIMIZI KULLANIRSAK BUDA DELETE[] YAPARSA YINE HATA OLUŞMAYACAK.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UB ÇÖZÜMÜ

int main()
{
	std::cout << "main basliyor\n";
	{
		std::unique_ptr<Triple[]> uptr{ new Triple[10]  };  // TRIPLE[] KULLANILMIŞ. UB BÖYLE ÇÖZÜLDÜ. KONTROL ETTİM. DELETE EDERKENDE DELETE [] KULLANIYOR.
	}
	std::cout << "main bitiyor\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DİĞER ÇÖZÜM DELETER YAZABİLİRİZ

struct TripleDeleter{
	void operator()(Triple *p)
	{
		delete[]p;
	}
};

int main()
{
	std::cout << "main basliyor\n";
	{
		std::unique_ptr<Triple,TripleDeleter> uptr{ new Triple[5]  };  // TRIPLE KULLANILMIŞ BU SEFER. DELETE EDERKENDE DELETE [] KULLANIYOR.
	}
	std::cout << "main bitiyor\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	std:unique_ptr<Triple> uptr(??); // buradaki adres dinamik ömürlü bir blok adresi olmazsa yine UNDEFINED BEHAVIOR.Dİnamik ömürlü olmayan bloğu geri vermeye çalışmış	
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ptr = new Triple;

	std:unique_ptr<Triple> upx(ptr); 
	std:unique_ptr<Triple> upy(ptr); UNDEFINED BEHAVIOR 
}

Başka felaket senaryosu. Bİri destroy olursa nesneyi delete edecek diğeri ise dangling pointer haline gelecek.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAKE UNIQUE
-----------
Çok Önemli bir Fakrika Functionu. New operatörünü doğrudan kullanmak yerine new operatörünü kullanan dinamik ömürlü nesneyi kendi içinde hayata getiren
ve hayata getirdiği dinamik ömürlü nesnenin adresi ile initialize edilmiş bir unique ptr yi döndüren ismi make_unique olan bir func var.

İLK TERCİH HER ZAMAN MAKE_UNIQUE OLMALI.AYRICA PERFECT FORWARDING IN EN GÜZEL ÖRNEĞI

int main()
{
	std::make_unique<Triple>(1,4,5); // DINAMIK ÖMÜRLÜ HAYATI KONTROL EDILECEK NESNENIN CTORUNA GÖNDERILECEK ADRESI GEÇIYORUZ. EMPLACE GİBİ.
	
	auto up = make_unique<Triple>(1,4,5);  // RETURN DEĞERI UNIQUE PTR. ORTADA NEW OLMAMASI NEW KULLANILMADIĞI ANLAMINA GELMIYOR.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Make Unique Template
--------------------
template <typename T, typename ...Args>
std::unique_ptr<T>MakeUnique(Args&& ...args) // Burası forwarding reference
{
	return std::unique_ptr<T>{ new T{std::forward<Args>(args)...} };   // dikkat burada variadic olmasaydı, auto&& olsaydı forward<decltype(args)>(args)... kullanacaktık.
}

TEST
int main()
{
	auto up = MakeUnique<Triple>(1,4,5);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	auto uptr = make_unique<string>(10,'A'); //Ctora 10 tane A gönderildi.

	cout << *uptr << "\n"; // operator* doğrudan nesneye eriştirir.

}

MOLA

==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================

int main()
{
	using namespace std;

	auto uptr = make_unique<string>(10,'A'); //Ctora 10 tane A gönderildi.

	cout << *uptr << "\n"; // doğrudan nesneye eriştirir.

	uptr.operator->()->length(); -> böyle kullanılıyordu

	NESNE BOŞ İSE * VEYA -> İŞLEMLERİ UNDEFINED BEHAVIOR OLUR.

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	unique_ptr<string> uptr;

	try{
		auto str = *uptr;
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught\n";
	}

	HATA VERMEDİ UB VAR

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	Boşmu dolumu emin değilse

	if(uptr)
		cout << *uptr << "\n"; kontrol edilebilir.Dİğer kontrol etme yöntemlerinide yukarıda yazmıştık.

}


==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================

UNIQUE PTR MOVE ONLY TYPE
-------------------------
Unique ptr kopyalamaya karşı kapatılmış bir sınıf. Tipik bir move only type.

int main()
{
	unique_ptr<Triple> upx;
	auto upy = upx;			//SENTAKS HATASI OLUR COPY CTOR DELETE EDİLMİŞ.
	auto upy(upx);			//SENTAKS HATASI OLUR COPY CTOR DELETE EDİLMİŞ.
	auto upy{upx};			//SENTAKS HATASI OLUR COPY CTOR DELETE EDİLMİŞ.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void func(std::unique_ptr<Triple>)
{

}

int main()
{
	auto uptr = make_unique<Triple>(1,2,3); 

	func(uptr);		// SENTAKS HATASI. ARGÜMANDAN PARAMETREYE COPY YAPILIYOR.

	func(std::move(uptr));		// GEÇERLİ.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto upx = make_unique<Triple>(1,2,3);
	unique_ptr<Triple> upy;

	upy = upx; // COPY ASSIGNMENTTA DELETE EDİLMİŞ SENTAKS HATASI

	upy = std::move(upx); // Şimdi geçerli.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR UNİQUE PTR IN TAŞINMASI DEMEK, MOVE MEMBERLAR İLE, MÜLKİYETİ KAYBETMESİ, KAYNAĞI BIRAKMASI VE KAYNAĞI DİĞER NESNEYE İLETMESİ VE KENDİSİNİN BOŞA ÇIKMASI DEMEK !!!!!!!!!!!!!!!!!!!!!!!!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto upx = make_unique<Triple>(1,2,3);
	unique_ptr<Triple> upy;

	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n"; // Dolu
	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n"; // Boş
	
	upy = std::move(upx); // DİKKAT!!!! 

	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n"; // Boş
	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n"; // Dolu

	getchar();
}

MOVE FROM STATE TE OLAN BOŞ OLUYOR.

GETCHAR() A KADAR KESINLIKLE DESTRUCTOR ÇAĞRILMAYACAK. DELETE EDILEN TRIPLE NESNESI YOK.SADECE BIRI BOŞA ÇIKTI DIĞERI ISE MÜLKIYETI ALDI DEMEK.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int main()
{
	auto upx = make_unique<Triple>(1,2,3);

	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";

	std::unique_ptr<Triple>upy(std::move(upx)); // BURADA UPY, UPX IN KAYNAĞINI ÇALACAK. UPX TE MOVED FROM STATE DURUMUNDA OLACAK O DA BOŞ DEMEK

	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";

	getchar();

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto upx = make_unique<Triple>(1,2,3);

	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";
	
	{
		std::unique_ptr<Triple>upy(std::move(upx)); // BURADA UPY, UPX IN KAYNAĞINI ÇALACAK. UPX TE MOVED FROM STATE DURUMUNDA OLACAK O DA BOŞ DEMEK

		std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
		std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";
	}
	//Şimdi Upy nin scope u bittiğinden hayatıda sona erecek
	
	getchar();
}

Upy nin hayatı getchar a gelmeden nesne delete edilmiş olacak

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURASI ÇOK ÖNEMLİ. İKİ NESNEDE DOLUYSA

int main()
{
	auto upx = make_unique<Triple>(1,2,3);
	auto upy = make_unique<Triple>(5,7,12);
	
	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";

	
	upx = std::move(upy); // DİKKAT!!!!
	//Burada upx için move assignment çağrılacak. Bu move assignment kendi kaynağını geri verecek.1,2,3 nesnesi delete edilmiş olacak. Burada bir destructor çağrılacak
	// diğer taraftandan diğerinin kaynağını çalacak


	std::cout << "upy : " << (upy ? "dolu" : "bos") << "\n";
	std::cout << "upx : " << (upx ? "dolu" : "bos") << "\n";

	getchar();
}

ÇIKTI
-----
(1, 2, 3) degerinde 00CF4EC0 adresinde triple nesnesi hayata geldi
(5, 7, 12) degerinde 00CF3A98 adresinde triple nesnesi hayata geldi
upy : dolu
upx : dolu
(1, 2, 3) degerindeki 00CF4EC0 adresindeki triple nesnesinin hayati sona erdi
upy : bos
upx : dolu
getchardan sonra

(5, 7, 12) te ölüyor unique ptr olduğundan

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TAŞIMA YAPMADAN, MÜLKIYETI TAŞIMADAN, UPX IN DESTRUCTORIDA ÇAĞRILMADAN(YANI UPX HAYATTAYKEN) DINAMIK ÖMÜRLÜ NESNENIN HAYATINI SONLANDIRMAKI MÜMKÜN MÜ?
EVET. BUNU YAPMANIN BIRDEN FAZLA YOLU VAR.

int main()
{
	auto upx = make_unique<Triple>(1,2,3);

	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n";

	uptr.reset(); // Doğrudan kaynağı delete ediyor.Yani destuctor çağırdı ve nesne delete edildi. Uptr boşa çıktı.

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	uptr.reset(nullptr); // Bu da önce nesneyi delete edip sonra pointer değerini nullptr yapıyor.
						 // Zaten reseti argümansız çağırınca default olarak bunu kullanıyoruz.

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	uptr = nullptr; // bunu yapıncada aynı işi yapıyor.Nesneyi reset ediyor.
}

3 üde aynı işi yapıyor. Doluysa kaynağı delete edip boşa çıkacak.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NESNENIN KAYNAĞINI BITIRIP YENI BIR DINAMIK ÖMÜRLÜ NESNENIN ADRESINI TUTSUN İSTERSEK


int main()
{
	auto upx = make_unique<Triple>(1,2,3);

	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n";
	std::cout << *uptr;

	uptr.reset(new Triple{5,6,8}); // Yine kaynağı sonlandırıp ama yeni bir dinamik ömülü nesne oluşturulacak(new kullanıldığı için) ve reset functionuna çağrıdan sonra
									// uptr bu nesneyi kontrol edecek.Hayatını kontrol ettiği nesneyi delete etti ve yeni yaratılanı devraldı

	std::cout << *uptr; //yine dolu ama değeri değişti

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UPTR.RESET(PTR); // PTR DINAMIK ÖMÜRLÜ DEĞILSE TANIMSIZ DAVRANIŞ. PTR HAYATI ZATEN KONTROL EDILEN BIR NESNE ISE YINE TANIMSIZ DAVRANIŞ !!!!!!!!!!!!!!!!!!!!!!!!!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	{
		auto uptr = std::make_unique<Triple>(1,2,3);

		std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n";
		std::cout << *uptr;

		uptr.reset(new Triple{5,6,8}); // Yine kaynağı sonlandırıp ama yeni bir dinamik ömülü nesne oluşturulacak(new kullanıldığı için) ve reset functionuna çağrıdan sonra
										// uptr bu nesneyi kontrol edecek.Hayatını kontrol ettiği nesneyi delete etti ve yeni yaratılanı devraldı

		std::cout << *uptr; //yine dolu ama değeri değişti
	}
	std::cout << "Main sona eriyor\n"; // Buradan sonra bir öğe daha scopeu bittiğinden delete edilecek yani destructor çağrılacak.
}

ÇIKTI
-----
(1, 2, 3) degerinde 01084EC0 adresinde triple nesnesi hayata geldi
uptr : dolu
(1, 2, 3)(5, 6, 8) degerinde 01083A98 adresinde triple nesnesi hayata geldi
(1, 2, 3) degerindeki 01084EC0 adresindeki triple nesnesinin hayat? sona erdi
(5, 6, 8)(5, 6, 8) degerindeki 01083A98 adresindeki triple nesnesinin hayat? sona erdi
Main devam ediyor

==========================================================================================================================================================================================
==========================================================================================================================================================================================
==========================================================================================================================================================================================

INTERFACETEKİ FUNCTIONLAR
--------------------------

Get
---
Sarmalanan adresi get ediyor.Mülkiyeti geri vermiyor.

int main()
{
	auto uptr = make_unique<Triple>(1,2,3);
	std::cout <<uptr.get() << "\n";
}

Unique ptr nin inserterı var.

int main()
{
	auto upx = make_unique<Triple>(1,2,3);
	
	std::cout << "*uptr = " << *uptr << "\n"; // bu değerini verir 
	std::cout << "uptr = " << uptr << "\n";  // Bu ise adresi yazdırır.
	std::cout << "uptr = " << uptr.get() << "\n"; // Sarmaladığı pointerı döndürür
	
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Release
-------
Nesneyi delete etmiyor ama mülkiyeti bırakıyor. Memory leak oluşturmak istesek birebir :D
Return değeri sarmalanan adres.

int main()
{
	auto uptr = make_unique<Triple>(1,2,3);

	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n"; // dolu
	
	Triple *p = uptr.release(); //	uptr boşa çıktı ama Dtor çarılmadı.artık uique ptr ile yönetilmiyor biz bir pointera atadık
	
	std::cout << "uptr : " << (uptr ? "dolu" : "bos") << "\n"; // Boş. Dtor çağrılmadı ama mülkiyeti bıraktı sadece

	delete p; // Raw pointer olduğundan delete etmeliyiz.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto upx = make_unique<Triple>(1,2,3);
	auto upy = make_unique<Triple>(1,2,3);

	upy.reset(upx.release()); 
	
	upy = std::move(upx); //YUkarıdaki ile aynı. upx boşa çıkar. upy kendi kaynağını geri verir ve diğer nesnenin kaynağını üstlenir

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

upx.get() -> Sarmalanan adresi döndürür. Mülkiyete dokunmaz
upx.release() -> Sarmalanan adresi döndürür. Mülkiyeti bırakır ama delete etmez
upx.reset() -> Mülkiyeti varsa nesneyi sonlandırır ve nesneyi boşa çıkarır
upx.reset(nullptr) -> Yukarıdaki ile aynı. Yukarıda da zaten default nullptr parameter var.
upx.reset(adres) -> kaynağı varsa geri verir ama "adres" teki nesnenin mülkiyetini alır.Yani kaynağını yönetir.
cout << uptr ile	cout << uptr.get() aynı

if(upx == upy) karşılaştırma işlemi yapılabilir.


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MALİYET !!!!!!!!!

MALİYETİ YOK. BURADAKİ TEMPLATE KODLAR UYGUN ŞEKİLDE YAZILDIĞINDAN BİR İSTİSNA HARİCİNDE ONU DELETERDA GÖRECEĞİZ, DELETER BİR MALİYET GETİRMİYORSA HİÇBİR MALİYETİ YOK.


*/
