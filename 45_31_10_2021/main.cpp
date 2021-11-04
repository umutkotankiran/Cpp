/*

RANDOM SAYI ÜRETECİNDEN DEVAM EDİYORUZ.

KRİPTOLOJİ HARİÇ HERYERDE KULLANABİLECEĞİMİZ BİR LİBRARY VAR.
BİRDE RASGELE SAYI ÜRETEN SINIFLARIN DIŞINDA DAĞILIM SINIFLARI VARDI.BUNLAR FARKLI ŞEYLER
RASGELE SAYILARIN ÜRETILMESI BAŞKA AMA BU ÜRETILEN BITLEIRN HANGI ARALIKTA HANGI MODELDE OLDUĞUNU AYARLAYAN SINIFLAR FARKLI.

Rasgele sayı üreten sınıfların çok benzer arayüzleri var.
Mesela max en büyük değeri veriyor, min en küçüğü, default seed default olarak seed edilenleri veriyor.
Bunları akımlara yazabiliyoruz.Akımlardan statelerini geri yükleyebiliyoruz.

Rasgele sayı üretiminde en çok kullanılan sınıf mt19937 sınıfı veya mt19967_64 sınıfı.
Rasgeleliği ölçen kriterler açısından iyi bir yerde ve hızlı bir üretim yapıyor.
Diğer motorlara göre genel olarak daha avantajlı.

default_random_engine, mt19937 nin eş ismi genelde. Her derleyicide aynı olmayabilir ama genelde böyle
Rasgele sayı üreticisinin ürettiği sayıları doğrudan kullanmıyoruz. O uniform tamamen ilgili tamsayı aralığında.
Aşağıdakini yazmama engel durum yok yani.

int main()
{
	mt19937 eng{3456U};

	for(int i = 0; i < 10 ; ++i)
	{
		std::cout << eng() << "\n";
	}

	---------------------------------------------------------------------------------------------------------------------------------------------------

	Bizi problem domaininde üreteceğimiz rasgele sayı için hemen her zaman bir dağılım nesnesi kullanıyoruz.
	Farklı dağılım modelleri var en çok kullanılan uniform distribution.

	uniform_int_distribution dist{10,45}; // CTAD DAN FAYDALANDIK.BU BİR TEMPLATE. AYRICA AŞAĞIDAKİLERDE LEGAL
	uniform_int_distribution<int> dist{10,45}; // GEÇERLİ
	uniform_int_distribution<> dist{10,45}; // GEÇERLİ 

	for(int i = 0; i < 100; ++i)
	{
		std::cout << dist(eng) << "\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : DISTRIBUTION NESNELERİ STANDART DEĞİL !!!!!!!!!!!!!
	  DERLEYİCİDEN DERLEYİCİYE GÖRE DEĞİŞEBİLİR !!!!!!!!!!!!!!!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BELİRLİ ARALIKTA RASGELE SAYI ÜRETEBİLİYORUM.

int main()
{
	using namespace std;
	using namespace chrono;

	mt19937 eng; // default seed kullanmakta sakınca görmüyor hoca
	mt19937 eng{547658U}; // seed değeri verebiliriz.
	mt19937 eng{random_device{}()};

	mt19937(system_clock::now().time_since_epoch().count()); // içeridekini unsigned inte cast edebiliriz.Tür uyuşmazlığı olmasın diye
			//timepoint verir   // duration verir  // count türü long long olabilir
}

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

BİLGİSAYAR DETERMİNİSTİK BİR DEVICE NASIL OLUYORDA RANDOM SAYI ÜRETİYOR?

Bu tamamen derleyiciye bağlı. İşletim sisteminin apileri kullanılıyor burada.Yani işletim sisteminin apileri gerçek sayı üretimi 
imkanı veriyor. Buradaki gerçekten gerçek random sayı mı? Bu tartışılır. Buradakine sözde gerçek sayı diyor hoca :D:D:D:D:D
Arta planda ya cpu sıcaklığı ya keyboardu takip edebilir, yada mouse hareketleri takibi yada başka bir şeyi alabilir.

Random device in entropy isimli bir funcı var.

int main()
{
	mt19937 eng;
	random_device device;

	device.entropy(); // Bu func gerçek sayı döndürüyor. Eğer 0 ise gerçek sayı üretimi sözkonusu değil.
					  // GCC de gerçek rasgele sayı olmasına rağmen entropy yine 0 döndürüyor.
					  // Burada 32 değerinde. Wandboxta 0 değerinde

	for(int i = 0 ; i < 10; ++i)
	{
		std::cout << device() << "\n"; //sayılar görülebilir.
	}	
}

Burada biraz OS in yeteneklerinden faydalanılıyor.Tamda gerçek olduğu söylenemeyebilir.

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

UNIFORM REAL DISTRIBUTION

int main()
{
	mt19937 eng;

	//uniform_real_distribution<double> dist{35., 41};
	//uniform_real_distribution<> dist{35., 41};
	uniform_real_distribution dist{35., 41}; // hepsi olur

	for(int i = 0; i < 100; ++i)
	{
		cout << dist(eng) << "\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NORMAL DISTRIBUTION

Ortalamadan uzaklaşınca sayılarında azalması gerekiyor bunda

int main()
{
	mt19937 eng;

	normal_distribution dist{50., 5.}; // aritmetik ortalama 50 ama standart sapma 5. 
										// 50 Civarında yoğunlaşma olacak, ortalamadan uzaklaştıkça miktar azalacak.Gerçekçi test datalarına uygun bir dağılım
	for(int i = 0; i < 100; ++i)
	{
		cout << dist(eng) << "\n";
	}
}


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	mt19937 eng;

	normal_distribution dist{50., 5.}; // aritmetik ortalama 50 ama sapma 5
	map<int, int> cmap;

	constexpr int iteration{100'000};

	for(int i = 0; i < iteration; ++i)
	{
		++cmap[static_cast<int>(round(dist(eng)))]; // round ile yuvarladık daha sonrada cast ettik.
	}

	for(auto[value,count] : cmap)
	{
		std::cout << setw(12) << value << count << "\n"; // 12 karakterlik alanda ekrana yazdırdık
	}
}

Ortalama 50. 50 de yığılma var  uzaklaştıkça sayılar azalıyor.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Histogram halinde yazıyoruz.

int main()
{
	mt19937 eng;

	normal_distribution dist{50., 5.}; // aritmetik ortalama 50 ama sapma 5
	map<int, int> cmap;

	constexpr int iteration{100'000};
	constexpr int chunk{200};

	for(int i = 0; i < iteration; ++i)
	{
		++cmap[static_cast<int>(round(dist(eng)))]; // tamsayıya dönüştürmek için yuvarladık.round func ile.
	}

	for(auto[value,count] : cmap)
	{
		std::cout << setw(4) << value;
		cout << string(count / chunk, '*') << "\n";
	}
}

Dosyaya yazdırmak içinde gerekli kod yazılabilir. Hoca yazdı ben yazmıyorum.
  .
  .
  35
  36
  37*
  38**
  39***
  40*****
  41*******
  42***********
  43***************
  44*******************
  45***********************
  46*****************************
  47*********************************
  48*************************************
  49**************************************
  50****************************************
  51***************************************
  52************************************
  53*********************************
  54***************************
  55************************
  56*******************
  57**************
  58***********
  59*******
  60*****
  61***
  62**
  63*
  64
  65
  .
  .

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISCREET DISTRIBUTION

Değerlerin olasılıklarını kendimiz seçiyoruz burada.Bir tavla oyununda veya zar oyununda zarı hileli oluşturmak istiyoruz.İngilizcede biased deniyor. 
Yani her öğenin olasılığı aynı değil. Belirli olanlarının olasılığı daha yüksek.
Belirli öğelerin olasılıkları daha yüksek olacak mesela.Biased

Buradaki bence kilit nokta index nosu kaç ise o sayının ihtimalinden bahsediyoruz demek. O indexteki değerde 

Burada 1 ile 6 arasında uniform_int_distribution ile sayılar üretsek ve oranlarına baksak hepsinin sayıları aşağı yukarı aynı. Bunu discrete distribution ile yapalım.

int main()
{
	mt19937 eng;

	//discrete_distribution<int> dist{ 0, 10, 10., 10., 10, 10, 10 }; // BURADA 0 DAN BAŞLAYARAK ÜRETILECEK RASGELE SAYILARIN ORANINI BELIRLEYEN BIR INIT LIST KULLANABILIRIZ.
									  // YADA BUNU HERHANGIBIR RANGE DEN ALABILIRIZ.BURASI ŞU DEMEK,
									  // 0 I GELME OLASILIĞI 0/60, 1 IN GELME OLASILIĞI 10/60, 2 NIN OLASILIĞI 10/60 ....

	 discrete_distribution<int> dist{0, 10., 10., 10,10,10,15}; // 6 NIN GELME OLASILIĞINI 15/60 YAPTIK BURADA DA.BURADA 100 E TAMAMLAMAK ZORUNDA DEĞİLİZ !!!!!!!
								    // DIĞER SAYILARIN GELME ORANLARINI YAZMIYORUM

	map<int, int> cmap;

	constexpr int iteration{ 100'000 };
	constexpr int chunk{ 300 };

	for (int i = 0; i < iteration; ++i)
	{
		++cmap[static_cast<int>(round(dist(eng)))]; // tamsayıya dönüştürmek için yuvarladık.round func ile.
	}

	cout << left;
	for (auto [value, count] : cmap)
	{
		std::cout << setw(4) << value;
		cout << string(count / chunk, '*') << "\n";
	}
	
	---------------------------------------------------------------------------------------------------------------------------------------------------
	
	PROBILITIES
	Bu function ihtimalleri yazdırıyor. Return değeri vector<double>.
			
	std::vector vec = dist.probabilities();
	
	for (auto s : vec)
	{
		std::cout << s << " ";
	}
	
}

1   ***************************************************
2   ***************************************************
3   **************************************************
4   ***************************************************
5   ***************************************************
6   ****************************************************************************   Bunun ihtimalini yukarıda 15/60 yapmıştık.

İHTİMALLERİN ÇIKTISI
0 0.153846 0.153846 0.153846 0.153846 0.153846 0.230769

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	using namespace std;
	vector<double> dvec(26,5); // Bunlar harflerin yüzdeleri olsun.Biz burada [0,26) aralığında 5 yazdırdık tüm elemanlara
							   // buradaki ihtimaller şuanda 5 / (26*5)

	dvec['A' - 'A'] = 14.5; // A E I U O oranları 8.5. Bunların gelme ihtimalleri daha fazla yani 14.5 / (5*26)
	dvec['E' - 'A'] = 14.5;
	dvec['I' - 'A'] = 14.5;
	dvec['U' - 'A'] = 14.5;
	dvec['O' - 'A'] = 14.5;

	discrete_distribution<int> dist{dvec.begin(), dvec.end()};  // Vectordeki değerleri discrete distribution nesnesine verdik.
	mt19937 eng;												

	//while(true)
	//{
	//	cout << dist(eng); // yukarıdaki dağılmıı görmek için ufak test kodu yazdık.
	//	getchar();
	//}

	while(true)
	{
		std::cout << static_cast<char>(dist(eng) + 'A');
		_getch(); //conio.h de
	}
}

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

CONSTEXPR NE ZAMAN KULLANILMALI. BEN SORMUŞTUM

1 - Parametre değişkeni returndeğeri ve localler literal type olmalı.Yoksa coısntexpr geçerli kabul edilmiyor zaten.

constexpr std::string foo(std::string x)
{
	std::string y {"necati"};
	return x + y; //Sentaks hatası
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Myclass{
public:
	Myclass(int);
};

constexpr int foo(Myclass m)
{
	++m; //Bu sınıf literal type olmadığı için constexpr func olamayacak.

	return 1;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constexpr func olma koşullarını sağlaması başka birşey ama o funca yapılan çağrının üreteceği return değerinin compile time da hesaplanabilmesi bambaşka.

constexpr int func(int x, int y) // Bu constexpr olma koşullarını sağlıyor ama bu funca yapılan çağrıdan elde edilecek değerin bir compile time sabiti olduğu anlamına gelmiyor.
{
	return x * y - 3;
}

int main()
{
	constexpr auto val = func(12,56); // Burada sabit ifadeleri kullanıldığından geçerli

	int x = 23;

	constexpr auto val = func(x,56); // Burada x sabit ifadesi değil bu sebeple değer copile timeda elde edilmeyecek.Const olsaydı elde edilecekti yine	

	auto val = func(x,56); //Burası geçerli. Funcın return değeri constexpr değişkene atanmamış çünkü.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Constexpr funclar implicitly inline dır !!!!!

Kritik diğer nokta biz bunu header file a koymalıyız. Derleyici compile timeda hesaplama yapması için func call olan heryerde func tanımını görmeli.
Bu sebeple constexpr function implementasyonu header file içinde olacak.

Bunu sürekli constexpr olarak yazmayı düşünmeyeceğiz. Optimizasyon kısmını derleyiciye bırakabiliriz.
Biz genel kodlama ilkelerine sadık kalacağız.Mesela const keywordünü kullanmam gereken yerde kullanacağım.
Derleyicinin işine karışmak iyi değil. Zaten optimizasyonu mükemmel yapıyor.

2 farklı optimizasyon var burada.
1 - Derleyicinin compile timeda kod seçimini değiştiriyor.
2 - C de de olan daha etkin assembly kodu üretmek için yaptığı optimizasyonlar.

template <typename InIter, typename OutIter>
OutIter Copy(InIter beg, InIter end, OutIter destbeg)
{
	while(beg != end)
	{
		*destgeb ++ = *beg++;
	}
	return destbeg;
}

Optizimasyonlar Baya fazla
1 - İşlemci tarafındaki optimizasyon
2 - Derleyici kod optimizasyonu
3 - Programcının optimizasyona katkısı.

Bizim müdahalemiz daha çok uygun veri yapılarını ve algoritmayı kullanmak.

Mikrosaniyeler önemlisyse eğer burada profilerlar kullanılıyor. Bunlar nerede darboğaz olduğunu buluyor.Bizde onu optimize etmeye çalışırız.

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

DOSYA KONUM GOSTERICISI OLAYI

ifstream sınıfı istream sınıfından kalıtımla elde edilmiş. >> var, << yok
ofstream sınıfı ostream sınıfından kalıtımla elde edilmiş << var, >> yok
Hem okuma hem yazma yapılacaksa fstream sınıflarını kullanmak gerekli.

Her sınıfın default açış modu var. ofstream ofs{"out"}; bu demek ofstream ofs{"out", ios::out | ios::trunc}; demek
ios::app kullanırsak append modda açıyor.

fstream default açış modu ise ios::in | ios::out. truncate etmiyor.
truncate te etmek istersek kendimiz yazacağız. ios:in | ios::out | ios::trunc

OKUMADAN YAZMAYA YAZMADAN OKUMAYA GEÇİŞTE FİLE POINTER TEKRAR SET EDİLİYOR. YAPILMAZSA UNDEFINED BEHAVIOR !!!!!!!!!!!!!!!!!
İSTİSNASI VAR. EN SON OKUYARAK DOSYA SONUNA GELİP ORAYA YAZARSAK ORAYA SET ETMEYE GEREK YOK.


========================================================================================================================================================================

BUFFERLAMA MODLARI

streambuf sınıfı var. Aslında dosyada alt seviyeliokuma yazma bufferlama işlerinden sorumlu olan sınıf streambuf sınıfı.
File nesneleri ile bir veri yazdık yada okuma yaptık, aslında bunlar geri planda streambuf sınıfı türünden nesneye yaptırıyorlar.
Aslında dosya işlemlerinin çekirdeğindeki sınıf streambuf sınıfı.

Alt seviyeli bir okuma yazma işleminde formatsız birtakım işlemler yapmayacaksak bu sınıfı görmezden geliyoruz.
Dışsal bir device a veri göndereceksek ve alt seviyede formatsız olarak bir takım verilere müdahale etmek istiyoruz, bu durumda streambuf kullanılır.

Bu sınıfın bazı sınıfları virtual. Bufferlama stratejisini değiştirmek içinde streambuf sınıfını kullanıyoruz.

int main()
{
	ifstream ifs{"out.txt"};

	if.rdbuf() -> buradaki sınıflar streambufın sınıfları
	if.rdbuf() -> pubsetbuf() // bu functiona adres ve buffer büyüklüğü verirsek bu adresi buffer olarak kullanmış oluruz.
}

CPPREFERENCE TAN Basic streambuf sınıfına bakabiliriz.Josuttis in kitabından da okunabilir. Hoca jossutsin tüm kitaplarını öneriyor.

========================================================================================================================================================================

cout << endl;
endl(cout) a nasıl dönüştünün cevabı. Bunu yapan kod aşağıda

Bu kod ostream içerisinde

Ostream& operator<<(Ostream&(*fp)(Ostream&)) // BU ÇOK ÖNEMLİ. Biz buna bir func adresi gönderiyoruz.Bu ise bizim gönderdiğimiz sınıf nesnesinin kendisi ile çağırıyor.
{												// return değeri bu func ın return değeri.
	return fp(*this);
}


========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================


VOCABULARY TYPES
----------------
C++17 ile eklendiler bunlar

std::optional -> sınıf şablonu
std::variant -> sınıf şablonu
std::any -> bu sınıf şablonu değil.


STD::OPTIONAL
-------------
Öyle bir değişkenki bu değişkenin değerinin olması kadar olmamasıda normal. Bir değere sahip olabilir yada olmayabilir. C de bunu ifade etmenin doğrudan yolu yok.
Neden buna ihtiyaç var ? Mesela bir func bir kişinin 2. ismini istiyor ama herkesin middle name i yok. Functiona middle name parametreside koyuyoruz ama
dğer gelmeyebilir. Bu öyle tür olacakki olması kadar olmamasıda normal olduğu bir arayüzde kullanılacak. En çok kullanıldığı yer func return , func parameters ve
class data member olarak kullanılıyor. C de belki bunu nullptr ile gösterebiliriz.header file optional

#include<optional>

template<typename T>
class Optional{
public:
	// .. interface
private:
	T x;
	bool value_flag;
};

int main()
{
	Optional<std::string>oname;
	//
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	std::optional<int> x; // x ya bir değere sahip ya da sahip değil.

	// interfacetekiler sayesinde boşmu dolumu görürüm.
	// boş nesneyi doluyuş gibi kullanırsam exception throw yada UB oluşur.

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	x.has_value(); //bool döndürüyor. ve constexpr duruma göre

	if(x.has_value()){
		std::cout << "Evet degeri var = ";  // doluysa buraya girer
	}
	else
		std::cout << "Hayir Degeri yok";  // boşsa buraya girer


	---------------------------------------------------------------------------------------------------------------------------------------------------------

	std::optional<int> x{456};

	if(x.has_value()){
		std::cout << "Evet degeri var = " << *x << "\n"; 
	}
	else
		std::cout << "Hayir Degeri yok";

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
DEĞERİ KULLANMAK
----------------
Dereference/* ile yapılabilir. * tün return değeri referans türü

int main()
{
	std::optional<int> x{123};

	std::cout << " Deger = " << *x << "\n"; 

	try{
	
		std::cout << " Deger = " << *x << "\n"; 
	}
	catch(std::exception &ex)
	{
		std::cout << ex.what() << "\n";
	}
}


ÖRNEK:
int main()
{
	std::optional<int> x; // DİKKAT!!!!!

	std::cout << " Deger = " << *x << "\n"; //UNDEFINED BEHAVIOR ÇÜNKÜ DEĞERİ YOK

	try{
	
		std::cout << " Deger = " << *x << "\n"; //UNDEFINED BEHAVIOR ÇÜNKÜ DEĞERİ YOK
	}
	catch(std::exception &ex)
	{
		std::cout << ex.what() << "\n";   // HATA YAKALANMAZ ÇÜNKÜ UB.
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

VALUE
-----
Return değeri referans, dereference gibi.
Farkı value Exception throw ediyor. HATA YAKALANIR. Dereference tan farkı bu.

Hata gönderirse türü bad_optional_access

int main()
{
	std::optional<int> x;
	try{

		std::cout << " Deger = " << x.value() << "\n"; 
	}
	catch(std::bad_optional_access &ex) // HATA TÜRÜNE DİKKAT!!!!
	{
		std::cout << ex.what << "\n";   // HATA YAKALANDI.
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DEREFERENCE VE VALUE REFERENCE DÖNDÜRÜR

int main()
{
	std::optional<int> x{111};  // optional nesnesini değerle başlatmayınca aşağıda eşitlesek bile sorun çıkıyor.Çözüm birsonraki örnekte

	*x = 999;
	std::cout << "x.value() = " << x.value << "\n";

	x.value() = 666;  //İKİSİDE GEÇERLİ
	std::cout << "x.value() = " << x.value << "\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SONRADAN DA DEĞER VERİLEBİLİYOR.
DİKKAT !!! YUKARIDA VAROLAN DEĞERİ DEĞİŞTİRMEK İÇİN *X VEYA X.VALUE() KULLANDIK AMA DEĞER TUTMUYORSA BUNLAR TANIMSIZ DAVRANIŞ.
EĞER OPTIONAL NESNESİ BOŞ İSE DOĞRDAN NESNEYE EŞİTLEME İLE DEĞER VEREBİLİYORUZ.ÖRNEK AŞAĞIDA

int main()
{
	std::optional<int> x;

	x = 23;

	std::cout << *x;
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OPERATOR BOOL DEĞER OLUP OLMADIĞINI SORGULAR

int main()
{
	std::optional<int> x;

	if(x) // operator bool çalışır burada zaten
	{
		std::cout << "Degee sahip :" << *x << "\n";
	}
	else
	{
		std::cout << "degere sahip degil\n";
	}	
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void func(std::string name, std::optional<std::string> middle_name)
{
	std::optional<int> x{543};

	if(middle_name) // hepsiyle sorgulanır
	{
	}
	
	if(middle_name.operator bool()) // kimse gelende bu şekilde yazmaz.
	{
	}

	veya

	if(middle_name.has_value())
	{
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

VALUE OR
--------
Return değeri referans değil value. Valuedan farklı olarak değeri varsa değeri elde ediyor ama değer yoksa default bir değer kullanmak.
Optional nesnesinin değerini set etmiyor, return ettiği değer yukarıda yazdığım kontrole ilişkin değer.

int main()
{
	optional<string> ox;

	auto str = ox.value_or("mustafa");

	std::cout << "str = " << str << "\n"; // ox boş olduğundan bizim verdiğimiz değeri alacak.

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	optional<string> ox{"Ali"};

	auto str = ox.value_or("mustafa");

	std::cout << "str = " << str << "\n"; //Ali döndürecek. Çünkü zaten doluydu o yüzden değiştirmedi.

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	optional<int> ox{123};

	if(ox.has_value())
	{
		std::cout << "deger : " << *ox << "\n";
	}
	else
	{
		std::cout << "deger yok" << "\n";
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CONSTRUCTORS
------------
OPTIONAL ALTINDA NULLOPT VAR. BUDA BOŞ DEMEK

int main()
{
	optional<int> ox{nullopt};
	optional<int> ox = nullopt; // AYNI ŞEY YUKARIDAKİ İLE. CTOR EXPLICIT DEĞİL
	optional<int> ox; // BUDA AYNI

	if(ox.has_value())
	{
		std::cout << "deger : " << *ox << "\n";
	}
	else
	{
		std::cout << "deger yok" << "\n"; // Buraya girecek çünkü değeri yok
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Myclass{
	~Myclass()
	{
		std::cout << "Myclass Destructor\n";
	}
};

int main()
{
	Myclass mx;
	optional<Myclass> ox{mx}; 

	(void)getchar(); // Buraya kadar dtor çağrılmadı. Scope bitince çağrılacak.

	---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Myclass mx;
	optional<Myclass> ox{mx}; // bu durumda ikisi içinde dtor çağrıldı

	ox = nullopt; // Bu kod çalıştığı anda destructor çağrılıyor !!!!!!!

	(void)getchar();

	---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	RESETTE KULLANILABİLİR.	AYNI İŞİ YAPIYOR NULLOPT İLE

	Myclass mx;
	optional<Myclass> ox{mx}; // 

	ox.reset(); // Yine ox için dtor çağrıldı

	(void)getchar();

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	ox = {}; //ta yazarsakta Destructor çağrırır sınıf için

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖRNEKLER
--------

#include <optional>
#include <iostream>
#include <string>

template<typename T>
void print_op(const std::optional<T>& op)
{
	std::cout << "type is  : " << typeid(T).name() << "\n";

	if (op) {
		std::cout << "value is : " << *op << "\n";
	}
	else {
		std::cout << "has no value\n";
	}
	std::cout << "--------------------------------------------------\n";
}

int main()
{
	using namespace std::string_literals;

	std::optional<int> op1;
	print_op(op1); // no value

	std::optional<double> op2{};
	print_op(op2); // no value

	//std::optional<long> op3(); //function decleration

	std::optional<char> op4 = std::nullopt;
	print_op(op4); // no value

	std::optional op5{ 12.f }; //CTAD
	print_op(op5);  // dolu değeri yazar

	std::optional op6{ "necati" };
	print_op(op6); // dolu değeri yazar

	std::optional op7{ "necati"s };
	print_op(op7); // dolu değer yazar

	std::optional<std::string> op8{ "alican" };
	print_op(op8); // dolu değer yazar
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class UserName
{
public:
	explicit UserName(const std::string& str) : m_name(str)
	{
		std::cout << "constructor : " << m_name << "\n";
	}

	~UserName()
	{
		std::cout << "destructor : " << m_name << "\n";
	}

private:
	std::string m_name;
};

int main()
{
	std::optional<UserName> op_name;

	op_name.emplace("Necati Ergin");

	op_name.emplace("Ali Serce"); //destructor cagrilacak tuttuğu nesne destroy edilecek.Sonrada tekrar Ctor

	op_name.reset(); // destructor cagrilacak
	
	op_name.emplace("Kaan Aslan"); //Constructor cagrilacak
	
	op_name = std::nullopt; // Destructor çağrılacak
	
	op_name.emplace("Oguz Karan"); //Cosntructor çağrılacak
	
	op_name = UserName("Nuri Yilmaz"); // Oğuz karan için Dtor, Nuri için Ctor yine 
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

#include <optional>
#include <iostream>


int main()
{
	std::optional<double> d1{ 2.56 };
	std::optional<double> d2{ 0.78 };
	std::optional<int> i{ 40 };

	std::cout << *d1 << '\n';
	d1 = d2; // aynı türden nesneler birbirine atanabilir
	std::cout << *d1 << '\n';
	d1 = i; // Farklı türden nesnelerde birbirine atanabiliyor.Önemli olan değerlerin atanabilmesi.
	std::cout << *d1 << '\n';
	d1 = 5.69; // Atanabilir
	std::cout << *d1 << '\n';
	d1 = 13; // Atanabilir.
	std::cout << *d1 << '\n';
	d1 = std::nullopt;
	d2 = {}; // İçi boş blokta oluşturabiliriz.Default init edilmiş optional nesnesi demek.

	if (!d1 && !d2)
		std::cout << "her iki nesnenin de degeri yok\n";
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <iostream>

int main()
{
	std::optional<std::string> op{ "oguz karan" };

	std::cout << op.value() << "\n"; //Value turulan değere referans döndürüyor.
	op.value().assign(5, 'A'); // return değeri referans olduğundan string nesnesinin assign func ına çağrı yapıp değeri değiştirdik.
	std::cout << op.value() << "\n";
	op = std::nullopt; // nullopt atadık ve değeri yok artık.

	try {
		std::cout << op.value() << "\n"; // value da exception throw edecek.
	}
	catch (const std::bad_optional_access& ex) {
		std::cout << "hata yakalandi : " << ex.what();
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::optional<string> foo()
{
}

int main()
{
	//foo değer döndürürse

	if(auto p = foo(); p)  // p.has_value() yapılabilir p.operator bool() yapılabilir.Hepsi aynı. Bunlar boş mu dolumu testi yapmak için
	{
	}
	else
		...
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using osptr = std::optional<std::string>;

int main()
{
	using namespace std;

	vector<osptr> vec(100);

	for(const auto &x : vec)
	{
		if(x.has_value())
			std::cout << "dolu\n";
		else
			std::cout << "bos\n";
	}

	---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	for(auto &x : vec)
	{
		x.emplace(rname());
	}

	//..

	for(const auto &x : vec)
	{
		if(x)
			std::cout << *x << '\n';
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <iostream>
 
void display_e_mail(const std::optional<std::string> &op)
{
	std::cout << "e posta adresi : " << op.value_or("belirtilmemis") << "\n";
}
 
int main()
{
	std::optional<std::string> e_mail_address{ "necati@gmail.com" };
	display_e_mail(e_mail_address); // Dolu olduğundan value_or bu değeri yukarıdaki functa değiştirmez
	e_mail_address = std::nullopt;
	display_e_mail(e_mail_address); // Burada boş olduğundan belirtilmemiş yazısı olacak func return değeri.
	//...	
}

NOT : VALUE_OR UN RETURN DEĞERİ REFERANS DEĞİL !!!!!

Yani, p.value_or(23) = 45; // böyle bir atama sentaks hatası.Lvalue expr değil.Sınıf türünden olmadığı için sentaks hatası.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SIZEOF DEĞERİ

constexpr size_t size = 512;

class Myclass{
	char buffer[size];
};

int main()
{
	std:cout << sizeof(Myclass) << "\n"; // 512 byte
	std:cout << sizeof(std::optional<myclass>) << "\n"; //513 byte
}

Sadece 1 byte fazlası var.Çünkü aslında optional nesnesi nesneyi kendi içinde tutuyor ve onunla birlikte boolean bayrak tutuyor.Bu boolean bayrağa bakarak
dolu mu boşmu anlıyor.


DİNAMİK BELLEK ALANI ALLOCATE EDİYOR MU ? HAYIR.

Burada Operator new yazdı hoca çağrılıp çağrılmadığını görmek için ben yazmıyorum.

int main()
{
	std::optional<std::mt19937> x; 

	std::cout << sizeof(x) << "\n"; // 5004 byte ve dinamik bellke bloğu allocate edilmedi.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TAŞIMA SEMANTİĞİNDEN FAYDALANABİLİYORUZ.

#include <optional>
#include <iostream>

struct A {
	A() { std::cout << "default ctor.()\n"; }
	A(const A&) = delete;
	A& operator=(const A&) = delete;
	A(A&&) { std::cout << "move ctor()\n"; }
	//...
};

int main()
{
	A ax;

	std::optional<A> op1{ std::move(ax) }; // ax sağ taraf değeri, compile timeda sağ taraf değeri olduğunu anladığında, taşıma semantiğini devreye soktu.
	getchar(); 

	// BURADA TERSIDE MÜMKÜN.OPTIONALDAKI NESNEYIDE TAŞIYABILIRIZ.
	std::optional<A> op2{ std::move(*op1) }; //  Yine taşıma semantiği çalıştı.

	std::cout << op1.has_value() << "\n"; //TRUE  
	std::cout << op2.has_value() << "\n"; //TRUE.BURADA OPTIONAL DOLU AMA TUTTUĞU NESNE MOVED FROM STATE TE.

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OPTIONAL NESNELERİ KARŞILAŞTIRILABİLİR.

Boş olan optional nesnesi değerce her zaman dolu olndan daha küçük kabul ediliyor.

int main()
{
	optional x = 10;
	optional<int> y = 20;

	std::cout << boolalpha;

	std::cout << (x < y) << "\n"; //True
	
	---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	optional x = 10;
	optional<int> y;

	std::cout << boolalpha;

	std::cout << (x < y) << "\n"; //False

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	optional x = true;
	optional y = false;
	optional<bool> z;

	std::cout << boolalpha;

	std::cout << (x == y) << "\n"; //false
	std::cout << (x == z) << "\n"; //false
	std::cout << (z == true) << "\n"; //false
	std::cout << (z == false) << "\n"; //false   Hepsi yanlış.Değerinin olmaması true veya false yapmıyor. değerinin olmaması ayrı bir statü.

	std::cout << (z == nullopt) << "\n"; // True.  
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OPTIONAL İÇİN INSERTER YOK. KENDIMIZ YAZACAĞIZ.

template <typename T>
std::ostream& operator << (std::ostream &os, const std::optional<T>&op)
{
	if(op)
	{
		os << *op;
	}
	else
		os << "degeri yok!";

	return os;
}

int main()
{
	std::optional<string> x{"Alican"};

	cout << x << "\n";

	x.reset();

	cout << x << "\n";
}

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================


VARIANT
-------
C deki unionlar gibi.Aynı bellek alanını paylaşan elemanlardan oluşuyor union.C++ tada union kullanılabilir.

union Data{
	int x;
	string str;
	double dval;
};

C++ ta birliklerde sınıf türden nesne tutunca onun ctorunun, dtorunun çağrılması problemli. Dİkkatli olunmalı.
Bir string nesnesini hayata getirrisek burada, bu birliğin başka elemanını kullanmak için stringi destroy etmek gerekiyor.
Variant sınıf şablonu bunu template hale geiriyor. Bir de interface veriyor, bu yolla arka planda kullanılan birliğin hangi öğesinin aktif olduğunu öğrenebiliyoruz.

AMAÇ, Önceden belirlenmiş türlerden herhangibirinden değer tutabilen bir nesne kavramı oluşturmak.
Yani örneğin nesne öyle bir nesne olsunki, bu nesne aşağıdaki türlerden değerler tutabilsin.

int
double
Date
string

BUnu kendimizde yazabiliriz.Birde hangi elemanın aktif olduğunu gösteren birşey koymamız lazım.Variant olunca böyle bir birliği bir arayüzde güvenli kullanma imkanı veriyor.
Variant variadic bir sınıf şablonu.C++17 ile dile eklendi. Header file variant

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <variant>

int main()
{
	variant<int, double, string, Date> vx;  // vx int, double,string yada date tutabilir. Bunlardan biri olmak zorunda.
}

Variantta da tutuğu değerin hangi türden olduğunu öğremek için interfaceteki funclardan birini çağırabiliriz.

FUNCLARDAN BIR TANESI INDEX.Size_t türünden değer döndürüyor.

int main()
{
	variant<int, double, string, Date> vx;
	
	std::cout << vx.index(); // return değeri 0 ise int, 1 ise double, 2 ise string, 3 ise date

	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	vx = 2.3; //variant double türden
	std::cout << vx.index(); // 1

	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	vx = "burak"s;
	std::cout << vx.index(); // 2

	--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Date mydate;
	vx = mydate;

	std::cout << vx.index(); // 3
}

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

VARIANTIN TUTMAYA ADAY OLAN TÜRLERE ALTERNATIVE DENIYOR

int main()
{
	variant<int,double,string,Date> vx;

	auto b = holds_alternative<double>(vx);	// bool döndürüyor.Şuanda alternatiflerden biri double.True

	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	if(vx.index() == 3)
	{
		//buraya girerse Date tutuyor demektir.
	}

	Veya aşağıdaki ile aynı anlamda

	if(holds_alternative<double>(vx)) // burayı yaz
	{
	
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GET KULLANILABİLİYOR

Bu bir func şablonu. Variantta tutulan öğeye eriştiriyor.

int main()
{
	variant<int, double, string,Date>vx{345};

	try{
		cout << "deger = " << get<0>(vx) << "\n";
	}
	catch(const std::bad_variant_access& ex){
		std::cout << "Exception caught " << ex.what() << '\n'; 
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YİNE TUPLEDAKİ GİBİ

int main()
{
	variant<int, double, string,Date>vx{345};

	try{
		cout << "deger = " << get<int>(vx) << "\n"; //DİKKAT !!!! TÜR YAZDIK  get<0>(vx) da yazılabilirdi.
	}
	catch(const std::bad_variant_access& ex){
		std::cout << "Exception caught " << ex.what() << '\n';
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİKKAT !!!!!!

gette index doğru değilse exception throw eder

int main()
{
	variant<int, double, string,Date>vx{345};

	get<1>(vx); // Exception throw eder çünkü tür double değil, hatalı index verildi. int için 0 olmalıydı
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	variant<int, double, string,Date>vx{5.56};

	get<1>(vx); // Artık tür double. get<1>(vx) ile double olan tür değerine erişmek istedik.Geçerli
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GETE GEÇERSİZ TÜR VERDİĞİMDE BU COMPILE TIME DA KONTROL YAPIYOR.

int main()
{
	variant<int,double>vx{4.5};

	auto x = get<4>(vx); //compile time hatası
	auto x = get<float>(vx); //Yine compile time hatası
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GET_IF
------
Argüman olarak variant nesnesinin adresini veriyoruz.Kendisini değil !!!!! Get if funcionu açısal parantez içinde yazdığımız türden bir pointer döndürüyor.
Eğer variantımız bu noktada int tutuyorsa bu pointer nullptr değil o nesneye pointer.gette exception throw vardı burada nullptr karşılığı var.

Eğer get_if çağrılan noktada tutulan değer o türden değilse nullptr döndürüyor eğer tutulan değerse o nesneye pointer döndürüyor.

int main()
{
	variant<int, double, string,Date>vx{345};

	auto ptr = get_if<int>(&vx); // ptr türü int*. Değeri double olsaydı vx in, ptr değeri nullptr olacak. 
								 // Ama değeri vx in değeri int, ptr variantta tutulan nesneye pointer olacak bu durumda.

	if(ptr)
	{
		std::cout << "deger =  " << *ptr << "\n"; 
	}
	else
	{
		std::cout << "Tutulan deger int degil\n";
	}
}

Get_if in index versiyonuda var

auto ptr = get_if<0>(&vx); Buda geçerli yine 0 indexli öğeye erişmek istedik. auto ptr = get_if<int>(&vx); aynı anlamda. 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

#include <string>
#include <variant>
#include <iostream>

int main()
{
	try
	{
		using age_t = int;
		using weight_t = double;
		using name_t = std::string;

		std::variant<age_t, weight_t, name_t> va;

		enum : size_t { idx_age, idx_weight, idx_name }; // burada indexler 0 dan başlıyor. artık index ilede tür ilede erişebileceğiz aşağıda var.

		va = 19;

		std::cout << "yas     = " << std::get<idx_age>(va) << std::endl; // index ile yaşa erişim
		std::cout << "yas     = " << std::get<age_t>(va) << std::endl;  // yaşın türü ile yaşa erişim

		va = 3.14;

		std::cout << "agirlik = " << std::get<idx_weight>(va) << std::endl;
		std::cout << "agirlik = " << std::get<weight_t>(va) << std::endl; // kiloyu yazdı hata yok

		va = "Ahmet Karaman";

		std::cout << "isim    = " << std::get<idx_name>(va) << std::endl;
		std::cout << "isim    = " << std::get<name_t>(va) << std::endl; // isim soyisim yazdı hata yok. indexte türde uyumlu


		std::cout << "isim    = " << std::get<idx_age>(va) << std::endl; //EXCEPTION THROW EDER  !!!!!!!!!!!!!
		std::cout << "isim    = " << std::get<name_t>(va) << std::endl; 


	}
	catch (std::bad_variant_access& e)
	{
		std::cout << "hata yakalandi: " << e.what() << std::endl;
	}

}



































*/
