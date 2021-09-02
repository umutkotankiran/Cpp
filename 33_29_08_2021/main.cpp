/*

EN SON SIRALAMA ALGORİTMALARINI GÖRDÜK.
BUNLARIN HEPSİ ASLINDA SIRALAMA YAPMIYOR, SIRALAMA İLE İLGİLİ ALGORİTMALAR.

==========================================================================================================

IS SORTED

İs sorted boolean döndürüyor bir range in sıralı olup olmadığını test ediyor.

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
	vector<int> ivec{2,4,6,8,9,12,20,45};
	
	cout << boolalpha;
	cout << is_sorted(ivec.begin(), ivec.end()); //sadece forward iterator istiyor
	 // true döndürecek
	 // sırayı bozsaydık false dönecekti

}
-----------------------------------------------------------

BÜYÜKTEN KÜÇÜĞE

using namespace std;
int main()
{
	vector<int> ivec{91,12,2,-1,-4,-7};

	cout << boolalpha;
	cout << is_sorted(ivec.begin(), ivec.end()), greater{}) // 2. overload binary predicate istiyor
	// büyükten küçüğe sıralamayı kontrol edip true dönecek. default ta küçükten büyüğe idi less{}
	
}

-----------------------------------------------------------

IS SORTED UNTIL

Sıranın bozulduğu yere iteratör döndürüyor

using namespace std;
int main()
{
	vector<int> ivec{1,5,7,9,11,5,78,88};

	auto iter = is_sorted_until(ivec.begin(), ivec.end());

	if(iter != ivec.end())
	{
		std::cout << *iter << " distance " << distance(ivec.begin(),iter) << "\n";
		//std::cout << *iter << " distance " << iter - ivec.begin() << "\n"; // distance kullanmasaydık böyle olabilirdi
	}
}


-------------------------------------------------------------

PARTITION POINT

partition point veriyor ama bunun için zaten partition yapılmış bir range gerekiyor

using namespace std;
int main()
{
	vector<int> ivec{1,5,7,9,6,8,2};

	auto iter = partition_point(ivec.begin(), ivec.end(), [](int x) { return x % 2 != 0; });
	cout << iter - ivec.begin() << " partition noktasi\n"; // 6 nın konumu. partisyon buradan başlamış.
}

=============================================================================
=============================================================================
=============================================================================
=============================================================================
=============================================================================

ITERATOR INVALIDATION
---------------------
Yeni başlayan programcıların anlamakta zorlandığı ve sılıkla hata yaptığı alanlardan biri

Mülakatlarda çok karşımıza çıkıyor. 10 programcıdan 9 u yanlış yapıyor.

SORU:
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
int main()
{
	vector<int> svec(20);
	generate(svec.begin(), svec.end(), rname);
	copy(svec.begin(), svec.end(), ostream_iterator<string>{cout, " "});// vectordeki stringeri ıkış akımına yazdı son argümanda
	cout << "\n";

	//vectoru dolaşarak uzunluğu 5 olanları silecek, uzunluğu 6 olanlardan bir tane daha ekleyeceğiz.
	// 5 veya 6 olmayanlara dokunmayacak.

	//BU KOD ITERATOR INVALIDATIONDAN DOLAYI YANLIŞ
	for(auto iter = svec.begin(); iter != svec.end(); ++iter)
	{
		if(iter->lenght() == 5)
		{
			svec.erase(iter);
		}
		else if(iter-> size() == 6) // buralarda artık invalid olan iteratörü kullanıyoruz.
		{
			svec.insert(iter, *iter);
		}
	}
	copy(svec.begin(), svec.end(), ostream_iterator<string>{cout, " "});// Şanslı isek buradaki runtime hatasını görebiliriz. Release modda çalıştırdı hoca
	cout << "\n";
}

Bu soruyu yanlış yapmalarının sebebi iterator invaliadion.
Bizim iteratörlerimiz bir containerdaki bir öğenin konumunu tutuyorlar.
Mesela bizim bir iteratörümüz varsa ve bu end iteratörü değilse o zaman aslında
bir containerdaki öğenin konumunu tuyuyor.bizde bu iteratör ile öğeye erişip işlem yapabiliyoruz.

Bu iteratörün geçerliliğini koruması için halen bizi bu konumdaki nesneye eriştirmesi için valid
iteratör olması gerekiyor. Tıpkı C deki valid pointer gibi. Bu iterator herhangibir işlemden dolayı
invalid hale gelmişse bu duruma iterator invalidation deniyor. Buna pointerlar ve referanslarda
dahil. Aslen geçerli pointer / reference / iterator ün bir işlemden sonra geçersiz hale gelmesidir.

Dereference etmek ub olabilir.
Ub değildir ama o konumda artık olması gereken nesne değil başka bir nesne var.

Containerların vector list dahil , hepsi için iteratörlerin invalid olup olmamasına yönelik
kuralları var.

VECTORDEKİ KURALLAR
-------------------
1 - Yeni boyut eski kapasiteden daha büyük olursa realloc olur. bu öğelerin biryere taşınması demek.
	yani realloc olduğunda eskilerin hepsi geçersiz hale geliyor.

2 - insert, emplace_back, emplace, pushback bu funclar çağrıldığında herhangibir realloc olmazsa
	eklemenin yapıldığı konumdan önceki nesnelere yönelik iteratörler ve referanslar geçerliliğini koruyor.
	AMA ekleme yapılan ve daha sonraki konumlar geçersiz hale geliyor.

3 - Silme işlemlerinde ise erase ve pop_back ile bir konumdaki öğe silinirse,
	bundan öncekilerin konumunu tutan pointer veya iteratörler geçerliliğini
	koruyorlar ama silinen dahil silinenden sonrakileri elemanları tutan iteratör veya pointerlar veya referanslar
	geçerliliğini kaybediyor.

Az önceki soruda kodu yanlış yazma sebebi tipik olarak iterator invalidation.

PEKİ BUNU NASIL YAZACAĞIZ.

int main()
{
	vector<string> svec(20);
	generate(svec.begin(), svec.enc(),rname);
	print(svec);

	auto iter = svec.begin();
	// bir iteratörü silince yolumuza bir sonrakinden devam etmeliyiz zaten erase funclarıda silinenden bir sonraki öğeyi return ediyor.
	// burada iteratörün değerini değiştirip erase in return değeri yapacağız, Yani iterator silme işlemi yapunca
	// bir sonrakini gösterecek. 

	// Ekleme durumunda ise ilgili konuma eklersek, insert func ın return değeri eklenen öğeye iterator olacak. 
	// dolayısıyla insertin return değerini yine aynı iteratöre atarsam bu durumda iteratörün yeni değeri
	// eklenmiş öğenin konumu olacak. Bu durumda iteratörün değerini 2 artırmam gerekiyor. BURAYI TEKRAR DİNLE 23:00s
	
	// ikiside değilse iteratörü 1 artırıyortuz.
}

-----------------------------------------------------------------------------

KODU YAZALIM.

int main()
{
	vector<string> svec(20);
	generate(svec.begin(), svec.enc(),rname);
	print(svec);

	auto iter = svec.begin();

	while(iter != svec.end()){
		if(iter->length() == 5)
		{
			iter = svec.erase(iter); // bu durumda iteratörü artırmamak gerekiyor.
		}
		else if(iter -> length() == 6){
			iter = svec.insert(iter, *iter);
			iter += 2; // random access te böyle yazılır. bidirectiona olsaydı advance(iter,2) veya 2 defa artıracaktık
		}
		else
		{
			++iter;
		}
	}
	print(svec);
}

----------------------------------------------------------------------------
----------------------------------------------------------------------------

BAŞKA BİR SORU

Bir vectorden bir öğeyi sileceğiz ama silme constant time da olacak.

int main()
{
	vector<int> ivec{2,4,6,7,9,12,20,1};

	auto iter = ivec.begin() + 4; // değeri 9 olan öğe silinecek.

	iter_swap(iter, ivec.end() -1 ); // Çözüm
	ivec.pop_back();

	//2. yol iter swap ie olacak diye birşey yok.
	swap(*iter, ivec.back());
	ivec.pop_back();
}

Erase ile silersek karmaşıklık O(n) olacak. 
Biz O(1) istiyoruz. 

Son öğe ile yer değiştirip sonra silebiliriz.


===========================================================================
===========================================================================
===========================================================================
===========================================================================

DEQUE CONTAINER
---------------

Double ended queue dan uydurmuşlar.
Polüler veri yapısından uydurmuşlar. Avantajı index ile sabit zamanda erişmek.
Baştan ve sondan eklemeyide yine sabit zamanda yapmak.
Sabit zaman derken amortised constant time.

Vectorden farklı olarak hem baştan hemde sondan eleme constant time da.
Vectorde sadece sondan ekleme constant idi.

Ama index ile erişmek yine constant time da. Hepsinin avantajları ve dezavantajları var.

-------------------------------------------------------------------------------

Deque implementasyonu

Bu dinamik ömürlü dizilerin dizisi aslında. Tipik bir deque in bir t zamanındaki
bellek yerleşimi böyle(31:53) olabilir. Buradaki sütunlar hepaten ayrı ayrı allocate ediliyorlar.
Bunlara popüler olarak chunk deniyor. Chunkların boyutu implementasyona bağlı. Sondan ekleme yaparken chunklardan birini, baştan ekleme yaparken
chunklardan birini kullanacağız. Dolayısı ile burada reallocation yok.

Olsa olsa bir chunk bittiğinde yeni bir chunk allocate edilecek. Allocation var ama
vectordeki gibi bir realloc yok. Eski bellek bloğundakilerin yeni bir yere taşınması gibi.

NASIL OLUYORDA İNDEXLE ERİŞMEK SABİT ZAMANDA OLUYOR.
Bunların adresleri için bir tablo var.
mesea 88 değerindeinin indexi 12 olsun. index ile chunka erişiyor ve onunda belli indextei
elemanına erişiyor.Client kod açısından bakınca deque teki 12. öğe.

Sondan ve baştan eklemenin maaliyeti O(1).

Bu veri yapısının interface i genel sequence sınıfının interface ine benziyor tamamen aynı.
Vectör ile neredeyse aynı ama vectorden farkı baştan ekleme constant time da olduğu için vetorde
olmayan push_front ve pop_front functionlarıda var.  header file deque
Yİne random access iterator category sinde.


NOT : ARADAN SİLMEDE YİNE KAYDIRMA İŞLEMİ VAR.

template <typename T, typename A = allocator<T>>
class deque{
	
};

-----------------------------------------------------------------------------



#include <vector>
#include <deque>

int main()
{
	deque<int> x;

	x. // birsürü ortak func var.Neredeyse aynı zaten :D:D:D
	// emplace front var çünkü push front var.
	//shrink to fit neden var? chuknları ne zaman geri vereceği konusunda belirleme yok çünkü.
}

-----------------------------------------------------------------------------

Baştan kelemede sondan eklemede constant time da

int main()
{
	deque<int>x;

	for(int i = 0; i < 100; ++i)
	{
		auto ival = Irand{0,1000}();

		if(ival % 2 != 0)
			x.push_front(ival);
		else
			x.push_back(ival);
	}

	print(x);

	// diğer taraftan random access iteratör isteyen tüm algoritmalar çalıştırılabilir.
	
	for(size_t i = 0; i < x.size() ; ++i)
	{
		std::cout << x[i] << " ";
	}

}

--------------------------------------------------------------------------

NEDEN DEQUE KULLANALIM

1. Hem index ile erişip, hem baştan hemde sondan sıksık ekleme silme yapıyorsak,
vector baştan eklemede constant t,me karmaşıklığa sahip değil ama deque constant time.
Bu başlı başına sebep.

2. Vectorde reallocation var ama burada yok.Baştan ne kadar büyüyeceği belli ise reserve edilir
ama belirsiz ise reserve etmekte mantıksız.

3. Iterator invalidation ile iligli olabilir. Deque in iteratör invalidation kuralları
vectörünkine göre farklı. Burada avantaj varsa yine deque kullanılabilir.

4. fragmantasyon ile ilgili bir seçim olabilir. Vector tek parça bloğa sahip.
ama Deque da bir chunklık yer varsa onu büyütebiliriz.

==========================================================================
==========================================================================
==========================================================================
==========================================================================

DEQUE ITERATOR INVALIDATION KURALLARI
-------------------------------------

1. Ekleme baştan yada sondan değilde ortadan yapılırsa, bütün referanslar ve iteratörler invalid hale geliyor.
   Eklemeyi baştan veya sondan yapıyorsak, iteratörler yine invalid hale geliyor ama REFERANSLAR HALE GELMİYOR.

ÖRNEKTE GÖRELİM.

int main()
{
	deque<string>ds{"ali","helin","murat","haydar"};
	const auto &x = ds.front(); // begin de yazabilirdik.
	const auto &y = ds.back();

	ds.push_front("nurettin");
	ds.push_back("seyfettin");

	print(ds); // nurettin başta seyfettin sonda

	//REFERANSLAR INVALID HALE GELMEDI
	cout << x << "\n";
	cout << y << "\n";

	//EKLEMEYI BAŞ VE SONDAN YAPMASAYDIK HERŞEY INVALID HALE GELIRDI.

}

---------------------------------------------------------------------------
---------------------------------------------------------------------------

VECTOR VS DEQUE
---------------

- ÇOK FAZLA BAŞTAN EKLEME YAPILIYORSA DEQUE

- POINTER INVALIDATION, VECTORDE SİZE KAPASİTEYE EŞİT İKEN EKLEME YAPTIĞIMIZDA
  REALLOCATION OLUŞUYOR.REALLOC İTERATORLERİ VE REFERANSLARI GEÇERSİZ KILIYOR.

- C DİZİLERİNE VECTORÜ GEÇEBİLİRİZ AMA DEQUE GEÇEMEYİZ.

- REALLOC MALİYETİNDEN KAÇINMAK İÇİN, EĞER VECTORDEKİ BÜYÜME ÖNCEDEN ÖNGÖRÜLEMİYOR
  İSE (ÖNCEDEN RESERVE İLE YER AYIRMA DURUMU YOKSA EĞER) STD::DEQUE DAHA İYİ BİR 
  SEÇENEK OLABİLİR.

- VECTOR<BOOL> YERİNE DEQUE<BOOL> KULLANABİLİRİZ.

- VECTOR TEK BİR BELLEK ALANI İSTİYOR AMA DEQUE CHUNKLARI İSTİYOR

--------------------------------------------------------------------------

DİKKAT : vectorun bool açılımı yani specializationu içinde bool tutan bir
vector değil. Bu partial bir specialization ve bir proxy class kullanıyor.
bir nested type kullanıyor. Nedeni bit seviyesinde bool u tutmak.

BU DA C++ IN GENÇLIK HATASI. :D:D:D:D:D:D:D:D

int tmain()
{
	vector<bool> bvec{true,false,true, true};

	auto x = bvec[2];

	cout << typeid(x).name() << "\n"; // x in türü bool değil bu bir nested type, bir proxy class
	// bit seviyesinde bir değişken yok.arka tarafı boolean değeri bitlerde tutuyor.

}

SONUÇ:
1 - Emin olmadan vectorun boo açılımını kullanmayın. Muhtemeln tercihimiz bu olmayacak.
2 - Gerçeketen bool tutan indexle sabit zamanda erişebileceğim, vector bool yerine deque in
	bool açılımını kullanmalıyız.

Aslında birçoğunun isteği deqeue an yana ama vector<bool> farklı bir şekilde bit seviyesinde implemente
edildiği için onun getirdiği kodlama riskinden kaçınmak için deque kullanıyor.

====================================================================================
====================================================================================
====================================================================================
====================================================================================
====================================================================================

LINKED LIST
-----------
Bağlı liste.Çok temel bilgileri hatırlayalım.

Bağlı listede öğeler implementasyonda node denen birimlerin iinde tutuluyor.
Node : Veri ile kendisi gibi verileri birbirleriyle ilişkilendirecek bir implementasyon birimi.
Node içinde hem data hemde başka nodelara eriştirecek pointerlar var.

1:01 deki basic şekile bakılabilir.

Singly linked list, doubly linked list konuları.
Bağlı listelerin kullanımı bir hayli azaltıldı.bağlı liste yerine dinamik dizi şaşırtıcı bir şekilde
avantajlı durumda kalıyor.

doubly linked listte çift yönde hareket edilebiliyor.
singly linked list tek yönde hareket edebiliyor.
Tek fark bu değil, interfae lerde farklı.

Çifte bağlı listede bir konuma insert yapmak istersek, bu konumdan başka konuma ihtiyaç yok doubly linked listte.
çünkü öncekinede sonrakinede erişebiliyoruz.

Singly linked list bir konum elimizdeyse bunun yerine insert yapamayız.
Aynı şey silme işlemi içinde geçerli.

bağlı listelerden neden avantaj bekliyoruz. hangi noktalarda avantaj sağlayabilir.
Ekleme ve silme işlemleri.

İndex ile erişme O(n) karmaşıklığında.index ile erişeceksek kesinlikle iyi bir fikir değil.
Konumunu bildiğimiz yere ekleme yapacaksak yada o noktadan silme yapacaksak bu constant time da.

Çünkü sadece 2 pointer update edilecek.tekli bağlı list veya çifte bağlıya bağlı olarak değişebilir.
Ekleme veya silme noktası biliyorsa O(1) karmaşıklığında oluyor.

Bağlı listelerin varlık sebebi bu.
Herhangibir konumdan ekleme veya silmeyi constant time a çekiyor.

==============================================================================================
==============================================================================================
ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!
Vectorde sadece sondan ekleme constant time da
Deque te hem sondan hem baştan constant time
linked list lerde baştan sondan ortadan heryerden konum elimde olduğu sürece constant time da.
==============================================================================================
==============================================================================================

Bu avantaj karşısında ödenen bedel çok yüksek.
Ödenen Bedeller
---------------
1. Bellek kullanımı. 2 pointer + data + header. Çok yüksek maliyet.
2. Cache mekanizması. Vector contigues olduğundan bunu cache almak ve sık kullanılanları kolay
	cache yoluyla erişmek, cache miss ve cache hit oranını düşürüyor.
	cache miss: Veri kullanılacak ama cache te değil. memory ye erişip cache e transfer yapma gerekiyor.
	
	Özel bir allocator kullanılmıyorsa cache miss çok fazla oluyor. Bu günümüzdeki performası belirleyen
	en önemli faktör haline gelmiş durumda.Eğer bağğlı listedeki öğe sayısı az ise 50-100 gibi.
	eklemeyi ortadan yapsak bile vector daha avantajlı olabilir.

Bağlı Listenin avantajları
--------------------------
1. Bağlı listenin bir avantajı var.Bunu anlamadan önce vectordeki dezavantajı anlamak lazım.

Node temelli veri yapılarında iterator invalidation problemi yok. düğümler silinmediği sürece 
bu düğümü gösteren iteratörler pointerlar referanslar invalid olmayacaklar

Diyelimki vectorde 400 byte lık büyük nesneler tutuyoruz.
class nec nesnesi olsun bunlar. Bu veri yapısında çalışacak algoritmaların önemli ksımı swap yapıyor.
partisyon, sort algolar merge gibi...
Vectorde swap yapmnanın başka bir yolu yok. Fiilen swap yapılacak.
Taşıma her zaman düşüm maliyet değil. Elemanın ne olduğuna göre dğeişir.
Taşıma kopyalamaya bir optimizasyon.

struct nec{
	array<int,100> mx;
	// array in move ctoru bunu ne yapabilir ki, int in taşınması diye birşey yok bu
	// 400 byte lık alan yine kopyalanmak zorunda.Yani bir çok sınıf için move un ilave bir avantajı yok.

};

ÖRNEĞE GERİ DÖNELİM :D:D:D
Vectörde tutuluyorlar ve argoritma çalışınca öğeler swap ediliyor.
öğeler büyüdükçe maiyet artıyor.

Linked list olursa, veriler düğümlerin içinde. Bu durumda Node ların içerisindeki pointerlar
takas edilebilir. Neden 400 bytelık veriler takas edilsin. Bu durumda bağlı liste arayüzünde
diğer sequence containerlarda olmayan fonlsiyonlar göreceğiz. neden bunlar member func yapılmış?
swapın getireceği avantajlardan faydalanmak için. Mesela merge , reverse, uniue , sort
bunlar normalde STL algoritmaları ama list sınıfında sınıfın member funcları bunlar.

Bunlar takas yapıyorlar ama Node ların içinde ki veriyi değilde içerisindeki pointerları takas ederek yapıyorlar.

STL e gelelim

------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------


Biri C++ 11 ile dile elendi diğeri eskiden beri var.
list eskiden beri olan çifte bağlı liste sınıfı. Birde modern C++ ile dile eklenen forward list var.

LIST = Çifte bağlı liste sınıfı. Sequence container interafce ini neredeyse tamamen alıyor.
Sadece ilave fonksiyonları göreceğiz.İteratörler bidirectional iterator. bağlı listede iki yönde
hareket edeceğiz çünkü :D RANDOM ACCESS DEĞİL!!!!! UNUTMA !!!!!

FORWARD LIST = Tekli bağlı liste.tek yönde dolaşılıyor. Forward iterator kategorisinde. -- işlemide yok.

Hemen çok hızlı iterface e bakalım

int main()
{
	list<int> mylist;
	mylist. 
			
}			

Merge algoritması vardı ama listte sınıfın merge isimli member func ı var.
Remove algoritmas vardı ama list in remove member func ı var.
daha önce konuştuk hem global varsa hem member varsa kim çağrılır?

Splice var. Node hangi bağlı listeye ait olduğunu bilmez.Dolayısıyla şöyle işlemler yapılabilir.
bağlı listedeki bir düğümü çıkarıp başka bi bağlı listeye bağlayabiliriz.

Her iki listede de konum belliyse o zaman ekleme ile silme herbiri constant time da olduğu için
ekleme ve islemide constant time da olacak. Ör : 2 liste var biri geçenler diğeri kalanlar.
Geçenlerden birini karar değiştirip kalanlar listesine koyabilirim.

Her iki listedeki konumlarıda biliyorsak birinden çıkarıp diğeine takmak constant time da olacak.
sequence container olmasının dışında düğüm temelli bir veri yapısı olmasından kaynaklanan
avantajları sömürmeye onları kullanmaya yönelik birde ilave bir interface var.
Bunun dışında herşey aynı.Vected deque list template yapısı aynı. 
Constructor grubuda tamamen aynı. İncelememize gerek yok.
10 öğe ile başlatılabilir, başla listeden kopyalanabilir, başka listeden taşıyabiliriz,
range ctor ile başka listeden öğeler aktarabiliriz.

Burada push_front ile baştan
push_back ile sondan ekleme yapabiliriz.

Düğüme ne eklenirse eklensin veya silinsin ama düğümün kendisi silinmediği sürece
iterator invalidation yok.

int main()
{
	list<int> mylist;

	mylist.push_front(4); // baştan ekleme yapılabilir
	mylist.push_back(2); // sondan ekleme yapılabilir

}

listeyi dolaşırken ya range fbase for loop yada [] ve iterator ile kendi for döngümüzü yazacağız.
Önerilen, range base for loop işi görüyorsa ayrı bir iterator döngüsü oluşturmayacağız.

class Myclass{
public:
	Myclass(int,int,int)
	{
		std::cout << "int ctor\n";
	}
	
	Myclass(const Myclass &)
	{
		std::cout << "copy ctor\n";
	}
	Myclass(Myclass &&)
	{
		std::cout << "move ctor\n";
	}

};

using namespace std;

int main()
{
	list<mylist>mylist;
	myclass x{1,4,5}; // int ctor
	
	mylist.push_back(x); // copy ctor
	
	mylist.push_back(std::move(x)); // move ctor

	mylist.push_back(Myclass{1,3,5}); // move ctor. veri türü myclass çünkü ve tek parametre.

	mylist.emplace_back(1,4,5); // Burada sadece int ctor çağrılıyor.
	// elemanı doğrudan kullanmak için argümanlar elimizde ise emplace_back kullanılabilir.
	// copy ellisiona çok benziyor.

}


MOLA
===============================================================================================
===============================================================================================
===============================================================================================
===============================================================================================

MEMBER FUNCLARI SEQUENCE CONTAINERLARDA OLMAYAN , OLNLARIN ALGORITMALARDAN FAYDALANDIĞI AMA BIR SINIFINDA ÜYE
FUNCTIONI OLAN FUNCTIONLARA BAKALIM

int main()
{
	list<string>mylist;
	rfill(mylist,10,rname);

	print(mylist);

	//reverse algosu yerine sınıfın reverse func çağırıyoruz.
	mylist.reverse();
	print(mylist);
	
	mylist.sort(); // küçükten büyüğe
	print(mylist);

	mylist.sort(greater{}); // büyükten küçüğe
	print(mylist);


------------------------------------------------------------------------------------------

REMOVE İLE SİLME YAPILABİLİR.

int main()
{
	list<int> mylist;
	rfill(mylist,100,Irand{0,5});
		
	cout << "hangi deger silinecek : ";
	int ival;
	cin >> ival;

	auto n = mylist.remove(ival);
	// auto n = erase(mylist,ival); //C++20 ile buda geldi.

	std::cout << "toplam " << n << " oge silindi\n";
	print(mylist);
	
}

------------------------------------------------------------------------------------------

REMOVE_IF

int main()
{
	list<int> mylist;
	rfill(mylist,100,Irand{0,100});

	cout << "Kaca tam bolunenler : ";
	int ival;
	cin >> ival;

	auto n = mylist.remove_if([ival](int x){return x % ival == 0; });

	std::cout << "toplam " << n << " oge silindi\n";
	print(mylist);
}

------------------------------------------------------------------------------------------

UNIQUE

int main()
{
	list<int> mylist;
	rfill(mylist,100,Irand{0,3});

	print(mylist);
	auto n = mylist.unique(); // return değeri yine silinen öğe sayısı
		
	//Diğer overload 
	auto n = mylist.unique([](int x, int y){return x % 2  == y % 2; });

	std::cout << n << " eleman silindi\n";
	print(mylist);
}

------------------------------------------------------------------------------------------

MERGE
Sıralı birleştirme anlamında.
İki sıralanmış listeyi birbiriyle birleştirebiliriz.Sıralanmamış ise hata veriyor.Denendi.

int main()
{
	list<int> x,y;
	rfill(y,10,Irand{0,100});
	rfill(x,10,Irand{0,100});

	x.sort();
	y.sort();

	print(x);
	print(y);

	x.merge(y); // x kendine y yi katacak :D:D

	std::cout << "y.size() " << y.size() << "\n"; // size 0 artık. Buradakiler x e katıldı.
	std::cout << "x.size() " << x.size() << "\n"; 
		
	print(x);
}

	
	
DİĞER ÖRNEK.

int main()
{
	list<string> x,y;
	rfill(y,10,rname);
	rfill(x,10,rname);

	auto fpred = [](const string &s1, const string &s2){
		return s1.size() < s2.size() ||s1.size() == s2.size() && s1 < s2;
	};

	x.sort(fpred);
	y.sort(fpred);

	print(x);
	print(y);

	x.merge(y,fpred); // x kendine y yi katacak :D:D

	std::cout << "y.size() " << y.size() << "\n"; // size 0 artık. Buradakiler x e katıldı.
	std::cout << "x.size() " << x.size() << "\n";

	print(x);
}

Diğer sequence iterator funclara aynı olduğundan bakmıyoruz ama basit bir örnek
-------------------------------------------------------------------------------

list<string> x;
rfill(x,12,rname)
print(list);

x.front() += "can";
x.back() += "han";

print(x);

while(!x.empty())
{
	x.pop_front();
	print(x);
	getchar();
}


------------------------------------------------------------------------------------------

SPLICE

Bir bağlı listeden bir veya daha fazla öğeyi list in birinden çıkarıp diğerine ekliyoruz.
	
int main()
{
	list<int> x,y;
	rfill(x,5,rname);
	rfill(y,5,rname);

	print(x);
	print(y);
		
	x.splice(x.begin(),y); // x in başlangıç konumundan itibaren, x'e y'yi ekledi.
	std::cout << "y.size() " << y.size() << "\n"; // 0. x e katıldı ve 0 oldu
	std::cout << "x.size() " << x.size() << "\n"; // 10 oldu.

}

size() member func ın karmaşıklığı O(1) constant time

x.splice(x.begin() + 2,y); // SENTAKS HATASI
x.splice(next(x.begin(),2) ,y); // 2. konuma ekleme yapacak.

------------------------------------------------------

Tamamını eklemek zorunda değiliz.
x.splice(x.begin(),y ,y.begin()); // x.begin konumuna, y listesinin y.begin konumundaki öğe katılacak
1 adet öğe katıldı.

------------------------------------------------------

RANGE PARAMETRELI SPLİCE

int main()
{
	list<int> x,y;
	rfill(x,5,rname);
	rfill(y,5,rname);

	print(x);
	print(y);

	x.splice(x.begin(),y.next(y.begin()), prev(y.end()); // x'e, ynin başlangıç ve bitişi hariç hepsini taşıyacak.
	std::cout << "y.size() " << y.size() << "\n"; //  2
	std::cout << "x.size() " << x.size() << "\n"; //  8
	print(x)
	print(y)

}


------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------

FORWARD LIST
EN PROBLEMLİ VE EN AZ KULLANILAN CONTAINER :D:D:D:D:D

Modern C++ tan önce forward_list sınıfı yoktu. Bu geldiği zaman belki ideal isim slist
single list gibi isim olabilirdi ama geçmiş kodlarla isim çakışması olmasın diye forward_list
dediler.

Tekli bağlı liste sınıfı bu. Burada bir tercih var. Bunda tipik olarak implementasyon 2 tane
anchor tutuyor. Biz push_front ve push_back çağrıldığı zaman aslında container nesnesi içinde
bunların konumunu tutan iteratörler var.yani ilk ve son düğümün konumları. Baştan ve sondan
ekleme yapınca mecbur eklemeyi bu pointerları kullanarak yapıyor. Tipik olarak size da ayrı bir veri elemanında
tutuluyor. Standartlar diyor ki C de yazılmış en temel minimal bağlı liste sınıfı nasılsa STL dekide böyle.

Böyle olunca size elemanı biryerde tutulmayacak. bağlı listenin interface ide biraz farklı oluyor.
	
tekli bağlı listede düğüme erişirsek ondan sonrakine ekleme yapabiliriz.
öncekini bilmediğimiz için eriştiğimiz node u değiştiremeyiz. Eriştiğimizin bir öncekini
bilseydik, yeni eklediğimizi bir öncekinin next i yapardık .... Bildiğimiz singly linked list

------------------------------------------------------------------------------------------

INTERFACE E BAKALIM.

#include <forward_list>

int main()
{
	forward_list<string> mylist{"ali","hasan","huseyin","ali"};
		
	mylist.insert(mylist.begin(),"bilal"); // SENTAKS HATASI. Bu list olsaydı eklerdik ama şuanda 
	print(mylist);

	-----------------------------------------------------------------------------------------

	mylist.insert_after(mylist.begin(),3 ,"bilal"); // 3 tane bilali, beginden bir sonrasına insert etti.
	print(mylist);
		
	-----------------------------------------------------------------------------------------

	BAŞA NASIL EKLEME YAPACAĞIZ.
	before_begin func ile. bundan aldığımız iteratörü dereferene etmeyeceğiz.sadece
	insert after ve erase aftera argüman olarak geçmek için var.

	forward_list<string> mylist{"ali","hasan","huseyin","ali"};
		
	print(mylist);
	mylist.insert_after(mylist.before_begin(), 3, "dogus"); // ilk öğeler olarak 3 doğuş eklendi
	print(mylist);
	
	Aynı işlemler silme işlemlerinde de geçerli !!!!!!!!!!!!!!!

	-----------------------------------------------------------------------------------------
		
	NOT : mylist in push_back func ı yok. nedeni anchor tutmuyor son öğenin konumunu
	sadece ilk öğenin konumunu tutuyor.pushback pushfront constant time da değil.
	son öğeye ulaşıp insert after yapmak gerekiyor pushback için.

	-----------------------------------------------------------------------------------------

	Erase örneği

	forward_list<string> mylist{"ali","hasan","huseyin","ali","gul","eda"};

	print(mylist);
	mylist.erase_after(mylist.begin()); // 2. öğeyi silecek.
	print(mylist);
		
	-----------------------------------------------------------------------------------------

	İlk öğeyi silmek isteseydim
	ya pop_front çağıracaktım

	mylist.pop_front();
	print(mylist);

	yada aşağıdaki gibi çağıracaktım.

	mylist.erase_after(mylist.before_begin());
	print(mylist);

	-----------------------------------------------------------------------------------------

	BAĞLI LİSTEDEKİ İLK 3 ÖĞEYİ SİLMEK İSTERSEK.
		
	list<string> mylist{"ali","hasan","huseyin","ali","gul","eda"}; // DİKKAT BURASI LIST
	print(mylist);
	mylist.erase(mylist.begin(), next(mylist.begin(),3)); // LISTTE ERASE VARDI
	print(mylist);

	-----------------------------------------------------------------------------------------

	Aşağıdaki gibide yapılabilir 

	forward_list<string> mylist{"ali","hasan","huseyin","ali","gul","eda"}; //BURADA FORWARD LIST OLDU

	print(mylist);
	mylist.erase_after(mylist.before_begin(), next(mylist.begin(),3)); // BUNDA ISE ERASE AFTER VAR
	print(mylist);

	-----------------------------------------------------------------------------------------

	Erase yok erase after_after var, splice ve insert içinde splice_after ve insert_after 
	functionları var. push_front pop_front functionları var, ama push_back ve pop_back function
	ları yok. 
		
	En tuhafı size() member func yok.Global olarakta yok.
	Size için distance çağrılabilir.
	cout << "size = " distance(mylist.begin(), mylist.end());

	-----------------------------------------------------------------------------------------

	ÖDEV: Bir tane tekli bağlı liste var. string bağlı listesi.n tane öğe var.

	forward_list<string> mylist{"ali","hasan","huseyin","ali","gul","eda"};
	rfill(mylist,20,rname);
	print(mylist);

	string name;
	std::cout << "silinecek ismi girin: ";
	cin >> name;
	// bu ismin ilk bulunduğu yerde bu ismi sileceğiz.

	doubly linked list olsayudı find ile bulup erase e argüman olarak gönderip ile silerdik

	C++ sınavındaki sorulardan biri. bahsedilen isim değil ondan önceki konumu bulmamız gerekiyor.
	sonrada erase_after

	-----------------------------------------------------------------------------------------

	Dikkat: sequence containerlarda değerle silme yapan func yok.Sequence containerlarda değerle silmek için
	remove erase idiyomunu kullanıyoruz. Bu da C++ 20 ile basitleştirildi. Global erase ile silebiliyoruz.
	compiler C++20 desteklemiyorsa remove eraes idiyom kullanılır.

	list<int> mylist;
	mylist.erase()
		
}


===============================================================================================================
===============================================================================================================
===============================================================================================================
===============================================================================================================
===============================================================================================================
		
	
SET VE MULTISET CONTAINERLARI
-----------------------------
Bunlar bildiğimiz ikili arama ağaçları.Binary search tree.
Biz ikili arama ağacını bize verilen interface te kullanacağız.Arka tarafta implementasyonların hemen
hepsinde red black tree denilen dengelenme katsayısı yüksek özel ikili arama ağaçları kullanılıyor.

set matematikteki set gibi bir küme, anahtarları tutuyor ve herhangibir değeri log karmaşıklıkta
tutulan anahtarlar arasında arayabiliyoruz. Aramaya konu olan değere veri yapıları ve algoritmalar
disiplininde KEY deniyor.Sette aramayı key ile yapıyoruz ve bulduğumuz key in kendisi.

Dolayısı ile set daha çok var mı yok mu sorgulaması için kulanılıyor.Yani değerle aramanın logaritmik
karmaşıklıkta olduğu bir veri yapısı. Değerle ekleme ve değerle silmede ytine logaritmik O(logn) karmaşıklıkta.

Bunun algoritma halide binary search algoritması. Baktığım var mı yokmu ise doğrudan boolean değer elde
edebiliriz ama erişmem gerekiyorsa eriştirecek arama yapılan functionda var.

SET biraz karmaşık bir veri yapısı. İkili arama ağacında associative containersta bir ilişkiye
göre yeri baştan belli.Sıralama ilişkisi var. Küçükten büyüğe ise yine düğümlerde tutuluyor.2:27

Eğer bu ağaç dengelenmişse bir değere erişmek için yapılan her sorgulamada varolan ağacın
yarısını elemine ediyoruz.Dolayısı ile ekleme silme arama işlemleride O(logn) karmaşıklığında

Burada eşitlik değil arama ekleme silme işlemlerinde, equality değil equivalance denen kavram kullanılıyor.
C++ ta eşitlik == ile yapılıyor. Buna equality deniyor.

Equivalance denen karşılaştırma == ile yapılan karşılaştırma değil.
!(x < y) && !(y < x) böyle yapılıyor. Sette öğeleri tutabilmek için öğelerin ya < operatörü ile karşılaştırılabiliyor
olması gerekiyor yada template parametresi olarak burada küçüklüğü temsil eden binary predicateın
sete tür argümanı olarak verilmesi gerekiyor.(!(x op y) && !(y op x))

Dolayısı ile bu template tür parametresi olarak less<T> açılımını alıyor.

template <typename T, typename comp = std::less<T>, typename A = std::allocator<T>>

Neden iki tane var.sette bir anahtardan bir tane var. Her değer karşılaştırma kriteri açısından unique.
Ama Multisette aynı anahtardan birden fazla olabilir.

header file hepsi için set.

#include <set>

int main()
{
	//set<int,less<int>,allocator<int>> myset ; bunun yerine aşağıdakini yazıyoruz.

	set<int> myset; // bu durumda sette equivalance karşılaştırmasında less kullanılmış olacak.

	for(int i = 0; i < 100; ++i)
	{
		myset.insert(Irand(0,120)());
	}
	// burada size ın 100 olma garantisi yok çükü aynı değerden bir tane daha gelirse(2. gelirse)
	// o insertt işlemi yapılmayacak.

	std::cout << "myset.size() = " << myset.size() << "\n"; // mesela 70 çıktı burada hocada.

	//bunun for un yerine range base for loop yazıldı altta
	//for(auto iter = myset.begin(); iter != myset.end(); ++iter)
	//{
	//	std::cout << *iter << " ";
	//}

	for(auto i = myset)
	{
		std::cout << i << " "; 
	}

}

-----------------------------------------------------------------------------------------

Sıralama ilişkisini biz kurmak istersek 2. template tür parametresini tür argümanı olarak
vereceğiz.Bu tür argümanı, functor, function object, standart function object yada lambda ifadesi olabilir.

#include <functional>
#include<set>

int main()
{
	set<int,greater<int>> myset; // artık buradabüyüktn küçüğe set ilişkisi oluşturulacak.

	for(int i = 0; i < 100; ++i)
	{
		myset.insert(Irand(0,120)());
	}

	std::cout << "myset.size() = " << myset.size() << "\n"; 

	for(auto i = myset)
	{
		std::cout << i << " ";
	}

}

-----------------------------------------------------------------------------------------

Kendi karşılaştırma ilişkimizi kendimiz kurabiliriz.

class Compare
{
public:
	bool operator()(int x, int y)
	{
		return x < y;
	}
};

int main()
{
	set<int,Compare> myset; // artık bizim karşılaştırma ilişkimiz olacak.

	for(int i = 0; i < 100; ++i)
	{
		myset.insert(Irand(0,120)());
	}

	std::cout << "myset.size() = " << myset.size() << "\n";

	for(auto i = myset)
	{
		std::cout << i << " ";
	}

}


--------------------------------------------------------------------------------------

BU KARŞILAŞTIRMA KRITERLERININ BELIRLI ÖZELLIKLERI SAĞLAMASI GEREKIOR YOKSA UNDEFINED BEHAVIOR OLUŞABILIR

Bu karşılaştırma işlemlerine strict weak ordering.

1. a op b --> true ise      b op a --> false vermek zorunda.yoksa equivalance kriteri olarak kullanılamaz.

2. a op a --> false olmak zorunda.true vermeyecek.

3. a op b --> true ise		b op c --> true ise     a op c --> true olmak zorunda.

4. !(a op b) && !(b op a) -->  bu durumda a ve b eşit kabul edilecek.
	
!(a op b) && !(b op a) ve !(b op c) && !(c op b) ise ----> !(a op c) && !(c op a) olmak zorunda.

Yani a ve b eşit ise b ve c eşit ise a ve c eşit olmak zorunda.

Bunların hepsinin özel adları falanda var.

--------------------------------------------------------------------------------------

ÖR:

int main()
{
	auto fcomp = [](const string &s1, const string &s2) {
		return s1.size() < s2.size() || s1.size() == s2.size() && s1 < s2;
	}


	BUNLAR YORUM SATIRINDAN ÇIKARILIP DENENECEK
	//set<string,decyltype(fcomp)> myset; // C++20 den önce lambdaların default Ctorları delete edildiği
										// için bu kod sentaks hatasıydı.Şimdi stateless lambdaların default
										// ctorları delete edilmediği için set i bu şekilde oluşturabiliyoruz.
	// 2.
	//set<string,decyltype(fcomp)> myset(fcomp); //C++17 ye göre yazsaydık böyle yazacaktık.argüman olarak fcomp
												// yazılacak
												// equivalance kriteri değişti.
	// 1. ilk deneme buna göre 
	set<string> myset;

	while(myset.size() < 20)
	{
		myset.insert(rname());
		print(myset);
		getchar(); 
		// 1. durum için küçükten büyüğe sırası korunuyor.kendisi bildiği yere insert ediyor.
		// 2. durum için hem sıra hemde uzunluğa bakılıyor.
	
	}
}

Burada karşılaştırma kriteri olarak ister kendi func objemi istar standart func object
isterde lambda yı karşılaştırma türü verebiliriz.Bu durumda decltype ile onun tür bilgisini
elde etmem gerekiyor.Gerçek bir functa olabilir karşılaştırma türü. C++20 de default ctor
için delete edilmiş değil artık fazladan argüman geçmek gerekmiyor.C++17 ve öncesi için ctora 
argüman olarak kendisini vermeliyiz.

----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------

SET IN INTERFACE INDEKI FUNCLAR

Range ctor, default ctor, copy ctor, move ctor var, init list ctor var.
ama şu kadar tane bu öğe ile başlat yok.

alias template in sık kullanıma aday olduğu yerler, set map multiset multimap gibi containerlar.

template <typename T>
using gset = std::set<T, std::greater<T>>;

int main()
{
	gset<int> myset{2,5,7,9,1,6}; // karşılaştırma kriteri büyükten küçüğe oldu.
	print(myset);

	gset<string>x {"zeynep", "demir","ayla","murat"};
	print(x);
}


Set ile multiset farkı, sette bir anahtardan  tane olabilir ama multisette böyle bir kısıt yok.

int main()
{
	set<int> myset;

	for(int i = 0; i < 100; ++i){
		myset.insert(Irand(0,100)());
	}

	cout << myset.size(); << "\n"; // bütün değerler unique. 100 de çıkmadı size. Eşit olanlar eklenmedi
	print(myset); 
}

BUNU MULTISET YAPALIM.

int main()
{
	multiset<int> myset;

	for(int i = 0; i < 100; ++i){
		myset.insert(Irand(0,100)());
	}

	cout << myset.size(); << "\n"; // Buraad size 100 çıktı aynı anahtardan bvirden fazla çıkabilir.
	print(myset);
}

---------------------------------------------------------------------------------------------

YANLIŞ ANLAŞILMA OLABİLİR

Sette int tutyorsak karşılaştırma kriteri zaten değerin kendisine eşit.
Multisetin kulanılma senaryosu :
Anahtarın kendisine eşit olması o anahtarı taşıyan değerin eşit olduğu anlamına gelmiyor
sette bir anahtardan bir tane oluyor ama multisette bir anahtardan birden fazla olabilir.

setin person açılımını kullanınca personun karşılaştırma operatoru ne ise ona göre karşılaştırma yapacak.
Kendimiz farklı bir comp yazıp personun tamamını karşılaştırmak yerine sadece id si ile persona erişebiliriz.
ID ile erişince aynı id de sahip birden fazla kişi varsa multiset bunların hepsini tutacak, ve bunlara eriştirecek.
ID lerin farklı olması onları aynı kişi yapmıyor belkide. yada ismi anahtar olarak kullanıyoruz.

set olsaydı doğuş ural varken, doğuş aksoy olmayacaktı. ikisini aynı kabul edecekti eğer karşılaştırma kriteri
sadece isimse. Multiset ise doğuşlar aynı değerde kabul edilecek.yanyana olacaklar ama eriştiğim zaman 
biri doğuş ural diğeri doğuş aksoy olabilecek.Dolayısı ile anahtar değerle aynı olmak zorunda değil.


-------------------------------------------------------------------------------------------

Interface e bakmaya devam edelim

Dikkat : sette bir iterator konumundaki öğe const olarak alınıyor.Değeri değiştirilemez.
Sentaks engelini aşıp değiştirme yapsak bu durumda veri yapısını corrupt etmiş oluruz.

int main()
{
	set<int> myset;

	auto iter = myset.begin();
	*iter = 456; //SENTAKS HATASI 
	
	Dİyelim ki aştık 
	const_cast<int &>(*iter) = 456; // TANIMSIZ DAVRANIŞ / UNDEFINED BEHAVIOR

}

Setteki anahtarın nasıl değiştirildiği ayrıca anlatılacak. Sonuçta setteki anahtarı değiştirmek için
o anahtarı setten çıkarıp yeni anahtar koymak gerekiyor. Doğrudan anahtar değiştirmeye çalışırsak veri yapısını
corrupt ederiz.

MOLA 

=============================================================================================
=============================================================================================
=============================================================================================
=============================================================================================
=============================================================================================

MEMBER FUNCLARI SIRASIYLA GÖRELİM

int main()
{
	vector<int> ivec;
	rfill(ivec,100,Irand{0,100});
	print(ivec);

	set<int> myset{ ivec.begin(), ivec.end() }; //range ctor.küçükten büyüğe sıraladı ayrıca
	print(myset);

}

-----------------------------------------------------------------------------------------

INSERT
Set insert ile multiset insert birbirinden farklı.
Normalde return değeri iterator dür ve insert edilmiş öğeye iteratör.
multisette insert edilmeme şansı olmadığı için return değeri doğrudan iterator.
Ama setin insert func return değeri pair<iterator,bool>

bool ekleme yapıldı mı yapılmadımı bunun bilgisini veriyor. True ise ekleme yapıldı false
ise yapılmadı

iterator ise ekleme işlemi yapıldıysa, iterator eklenmiş öğeye iterator, ama yapılmadıysa var
olan değere iterator.

int main()
{
	set<string> myset {"ali","deniz","ferda","nuri","zeynep"};
	print(myset);

	cout << "eklenecek ismi girin\n";
	cin >> name;

	myset.insert(name);
	// insert yapıldı mı ? tercih edilmesede  önce ve sonra size a bakılır artmışsa edilmiştir.
	//ama kolay test etme yolu return değerine bakmak.

	//auto ib = myset.insert(name);
	pair<set<string>::iterator,bool> ib = myset.insert(name);

	if(ib.second)
	{
		std::cout << "ekleme yaoildi. eklenen oge " << *ib.first << "\n";
		print(myset);
	}
	else
	{
		std::cout << "ekleme yapilmadi " << *ib.first << "\n";
	}
}

test et.

-----------------------------------------------------------------------------------------------

Bu tip karşılaştırmalarda structured kullanmak kolaylık sağlıyor.
Birden fazla öğeye sahip bir türü öğelerine ayrıştırıyor.

int main()
{
	set<string> myset {"ali","deniz","ferda","nuri","zeynep"};
	print(myset);

	cout << "eklenecek ismi girin\n";
	cin >> name;

	if(auto[iter,flag] = myset.insert(name); flag) // hem struc. binding hemde if with init. var
	{
		cout << *iter << " eklendi\n";
	}
	else
	{
		std::cout << *iter << " sette var\n";
	}
}

Multiset olsaydı insertin return değeri doğrudan iterator. iterator bool değeri değil.

-----------------------------------------------------------------------------------------------

ARAMA İŞLEMLERİ

C++20 den önce 2 yol vardı ama artık 3 oldu.C++20 den önce count functionu çağırıyorduk.
En uygun karşılaştırma bu. çünkü count o değerden kaç tane var bunu gönderiyor.
Sette ya 0 ya da 1 olacak.

int main()
{
	set<string> tset;
	rfill(tset,20,rtown);
	
	std::cout << "desteklenecek iller : ";
	print(tset);

	std::cout << "ili girin: ";
	sting town;
	cin >> town;

	if(tset.count(town)){
		std::cout << "evet iliniz destekleniyor\n";
	}
	else
	{
		std::cout << "hayır dilinize yatırım desteği yok.\n"
	}
}


-----------------------------------------------------------------------------------------------

2. yol var mı yokmu diye değil sadece varsada erişmek istiyouz. bu durumda find functionunu çağırabiliriz.
find in varsa return değeri bulunduysa bulunan öğeye iterator, yoksa end iteratörü.

int main()
{
	set<string> tset;
	rfill(tset,20,rtown);
	std::cout << "desteklenecek iller : ";
	print(tset);

	std::cout << "ili girin : ";
	sting town;
	cin >> town;

	if(auto iter = tset.find(town); iter != tset.end()){
		std::cout << "bulundu... " << *iter << "\n";
	}
	else
	{
		std::cout << "bulunamadi\n";		
	}
}

range de olanlar ve olmayanlarla test et.

-----------------------------------------------------------------------------------------------

C++20 ILE CONTAINS ISIMLI FUNCTION VAR DOĞRUDAN BOOLEAN DÖNDÜRÜYOR.


int main()
{
	set<string> tset;
	rfill(tset,20,rtown);
	std::cout << "desteklenecek iller : ";
	print(tset);

	std::cout << "ili girin : ";
	sting town;
	cin >> town;
	
	if(tset.contains(town))
	{
		std::cout << "var\n";
	}
	else
	{
		std::cout << "yok\n";
	}
}

-----------------------------------------------------------------------------------------------

ANAHTARI SİLMENİN FARKLI SİLME FONKSİYONLARI VAR

-Bütün funclarda olan iter paramereli erase func ile iteratör konumundaki öğe silinir.
 myset.erase(iter);

-range erase ile silinebilir.
 myset.erase(iterbeg,iter);

-Anahtar ile silme yapan funclar var.
myset.erase(value);


int main()
{
	set<string> tset;
	rfill(tset,10,rtown);
	std::cout << "desteklenecek iller : ";
	print(tset);

	-----------------------------------------------------------------------
	
	ilk öğeyi silmek istersek
	myset.erase(tset.begin());
	
	-----------------------------------------------------------------------
	
	son öğe silmek için
	myset.erase(tset.end() - 1);
	myset.erase(prev(tset.end()));
	
	-----------------------------------------------------------------------
	
	İlk ve son hariç hepsini silmiş olduk
	tset.erase(next(tset.begin()), prev(tset.end()));
	print(tset);

	-----------------------------------------------------------------------
	
	Birde değerle silme yapan func var.
	auto n = tset.erase("bolu"); // return değeri silinen öğe sayısı
	std::cout << "n = " << n;

	-----------------------------------------------------------------------
	
	multiset yaparsak.birden fazla aynı anahtar olabileceğinden.

	set<string> tset;
	rfill(tset,200,rtown);
	print(tset);

	auto n = tset.erase("bolu");

	std::cout << "n = " << n << "\n"; // mesela hocanın compiler 5 tane bolu buldu.
}
-----------------------------------------------------------------------

ÇOK KLASIK BIR SORU VAR. ANAHTARI DEĞIŞTIRME!!!

C++17 öncesi ve sonrası çözümü var.
	
1 .C++17 öncesi çözüm.
	
int main()
{
	set<string> myset;
	rfill(myset.10,rname);
	print(myset);

	string old_key, new_key;

	std::cout << "eski ve yeni isimleri girin\n";
	cin>> old_key >> new_key;

	auto iter = myself.find(old_key);
	if(iter != myset.end())
	{
		myset.erase(iter);
		myset.insert(new_key);
		print(myset);
	}
	else{
		std::cout << "bulunamadi\n"; 
	}
}
// bir isim gitti ve diğeri yani geldi.

-----------------------------------------------------------------------

C++17 ILE ÇOK ÖNEMLI BIR FUNC EKLENEDI

myset. // ile bakabiliriz.

EXTRACT
--------

Extract bize bir node un handle değerini veriyor.
Düğümü setten çıkartıyor ama içindeki veriyi destroy etmiyor.


int main()
{
	set<string> myset;
	rfill(myset.10,rname);
	print(myset);

	string name;
	std::cout << "isim girin : ";

	auto iter = myset.find(name);
	if(iter != myset.end())
	{
		auto handle = myset.extract(iter); // handle move semantics ten faydalanacağız
		handle.value() = "muzaffer"; // value nodda tutulan anahtara referans döndürüyor.
		myset.insert(std::move(handle));
	}
}

-----------------------------------------------------------------------

ŞİMDİ C++17 SONRASI ÇÖZÜM OLARAK YUKARIDAKİ UYARLAYALIM.


int main()
{
	set<string> myset;
	rfill(myset.10,rname);
	print(myset);

	std::cout << "myset.size() = " << myset.size() << "\n";
	string name;

	std::cout << "eski ve yeni isimleri girin\n";
	string old_key, new_key;

	cin>> old_key >> new_key; // olan isimlerden biri birde yeni isim gir.

	auto iter = myset.find(name);
	if(iter != myset.find(old_name); iter != myset.end())
	{
		auto handle = myset.extract(iter); //faydalanacağız
		handle.value() = new_name; // value nodda tutulan anahtara referans döndürüyor.
		myset.insert(std::move(handle)); // handle kopyalamaya kapatılmış bir tür. bu yüzden move ediyoruz
										 //myset.insert(handle.value()); diyebilirdik ama bunun bir avantajı kalmazdı bu tekrar insert işlemi yapıyor.
		print(myset);
	}
	else
	{
		std::cout <<"bulunamadi\n";
	}
}

//Hiç silme işlemi yapmadık ve değiştirdik.

Aşağıdaki gibide yazılabilirdi. Tamamını yazmayacağım.

if(auto handle = myset.extract(old_name); handle)
{
	handle.value() = new_name;
//..
//..
}

-----------------------------------------------------------------------























*/
