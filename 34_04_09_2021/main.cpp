/*

Başta bir soru üzerine iterator ve iterator_category kısmını anlatı hoca.
Yazmaya gerek yok.İterator traits kısmını kısaca anlattı hoca.

Bir takım lideri static keyword kullanmak sakıncalı demiş hoca şimdi onu anlatıyor. :D:D:D

20DK kadar genel bir tekrar.

===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================


EN SON KALDIĞIMIZ HER SET MULTISET VE MAP MULTIMAP IDI

Set ve multiset aynı header file içerisinde tanımlanmış containerlar.Farkları sette bir keyden bir tane, multisette ise daha fazla key olabiliyor.
İnterface de farklılık var birde. Set in insert functionunun return değeri iterator bool değeri, ama multisetin insert func return değeri doğrudan iterator.
Sette insert işleminin gerçekleşmeme durumu var ama multisette böyle bir ihtimal yok.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SETIN GERİ KALAN FUNCLARI

1.Ekleme işlemi, insert...
2.Silme işlemi, erase
	...


#include<set>
#include "nutility.h"
using namepsce std;

int main()
{
	set<string> myset= {"yunus","emre","dogus","umut","leyla","sibel"};
	
	myset.erase(myset.begin()); //iter parametreli func.ilki siler
	print(myset);
	
	-----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	myset.erase(prev(myset.end())); // Son öğe silinir.
	print(myset);

	-----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	myset.erase(next(myset.begin()),prev(myset.end()));
	print(myset);

	-----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	myset.erase("umut");  // key ile silme işlemi yapılınca return değeri silinmiş öğe sayısı.
	print(myset);

	-----------------------------------------------------------------------------------------------------------------------------------------------------------

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	multiset<string> myset;
	rfill(myset,300,rname);
	print(myset);

	std::cout << "Silinecek isim : ";
	string name;
	cin>> name;

	auto n = myset.erase(name); // return değeri silinen öğe sayısı.List containerında da erase değil remove siliyordu.
	std::cout << n << " eleman silindi";

	print(myset);

}

count kaç olduğunu sayıyor.
find iterator konumu döndürüyor.Bulamazsa verilen setin end konumunu döndürüyor.
C++20 ile contains doğrudan boolean döndürüyor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİKKAT !!!!!!!!!!!!!!!!!!!!!!!!!!

SETTE KAFA KARIŞTIRAN BIR KONU VAR.SETTE ISTEDIĞIMIZ ÖĞEYI ISTEDIĞIĞMIZ YERE EKLEYEMIYORDUK.
SEQUENCE CONTAINER ILE ASSOCIATIVE CONTAINERLAR ARASINDAKI FARKLILIKLARDAN BIRI BUYDU.
ASSOCIATIVE CONTAINERLARDA ELEMANLARIN KONUMLARI DEĞERI TARAFINDAN BELIRLENIYOR. SET IN LESS AÇILIMIYSA KÜÇÜKTEN BÜYÜĞE IKILI ARAMA AĞACI OLUŞTURULUYOR.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	multiset<string> myset;
	rfill(myset,10,rname);
	print(myset);

	std::cout << "silinecek isim : ";
	string name;
	cin>> name;

	myset.insert(myset.begin(),"abidin");   // Burada başa ekliyor gibi görünüyor
											// Buradaki konum hint, associative containerlarda hem değer hemde konum alan functionlara deniyor.
											// bu konuma değilde bu konumu ip uçu olarak kullan kontrole buradan başla demek.
											// Ayrıca maaliyeti azaltıyor.Yani abidini setin başına ekle anlamında değil.

	
	myset.insert(myset.begin(),"zeynep"); // Mesela sona eklendi burası Z harfi en sonda.Abidin A dan başladığı için başa ekledi.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunun anlatılmasının bir sebebi emplace functionları.Emplace insert funclarının karşılığı.
Emplace funclarının isimlendirilmesi STL de şöyle. Eğer func ismi insert ise diğer func ın ismi emplace.
Emplace perfect forwarding yoluyla işini görüyordu.

Emplace Funclarının STL de İsimlendirmesi
-----------------------------------------
Insert -----> Emplace
Back_back ----> Emplace_back
Back_front ----> Emplace_front


int main()
{
	set<string> myset;
	rfill(myset,10,rname);
	print(myset);

	myset.emplace(10,'a'); // Yerinde construct edilip sete eklendi
	print(myset);

	myset.emplace_hint(myset.begin(),10,'a'); // DİKKAT!!! hint ipucu olarak verildi. Konum verildi yani.
	print(myset);

}

===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================

Belirli veri yapıları sorted durumda olabilir.Bunların range ine STL sorted range diyor.
Bazı algoritmalar varki işlem yapılacak range in sorted yani sıralanmış olmasını bekliyorlar, bu algoritmalara sorted range algorithm.

Burada aşağıdaki isimler bulunuyor
----------------------------------
lower_bound
upper_bound
equal_bound 

Bunlar algoritma olmalarının yanı sıra aynı zamanda zaten bir sıralama ilişkisi ile kurulan, associative containerlar içinde aynı zamanda member funcların isimleri.
Bunları çağırarak bazı önemli işleri yapabiliriz.Vector olsaydı bu member funclar yok ama algoritmalar içinde bunlar var.

Bunlar C++ ile ilgili değil veri yapıları ve algoritmalar ile alakalı.

===================================================================================================================================================================================

LOWERBOUND
----------
VERİLEN DEĞERDEN BÜYÜK YADA EŞIT OLAN ILK ÖĞE.
Yani sırayı bozmadan ekleyebileceğim ilk konum. >= key olan ilk öğenin konumu yani.


int main()
{
	multiset<int> myset;

	rfill(myset,20,Irand{0,9});
	print(myset);

	int x;

	cout << " bir tamsayi girin : ";
	cin>> x;

	auto iter = myset.lower_bound(x);
	cout << "lower bound için index : " << distance(myset.begin(),iter);
	
	// 11222444555677 
	// MESELA BURADA 2 İÇİN LOWER BOUND 2 INDEXLI KONUM
	// 3 LOWERBOUNDU 5. İNDEX 
}


===================================================================================================================================================================================

UPPERBOUND
----------
VERİLEN DEĞERDEN BÜYÜK KEY OLAN ILK ÖĞENIN KONUMU. > için yani. Lower bound >= idi.

11222444555677 Mesela burada 6 için upperboud, 12. indexteki konum. 
Lowerbound ise 11. index

lower_bound ile upper_boundu bir range yaparsak, [lower_bound,upper_bound) buna EQUALRANGE deniyor. Yani burada sadece ilgili anahtarlar var.
Bu range in distance ı bu keylerden kaç tane olduğu

int main()
{
	multiset<int> myset;

	rfill(myset,20,Irand{0,9});
	print(myset);

	int x;

	cout << " bir tamsayi girin : ";
	cin>> x;

	auto iter_lower = myset.lower_bound(x);
	auto iter_upper = myset.upper_bound(x);

	cout << "lower bound için index : " << distance(myset.begin(),iter_lower);
	cout << "upper bound için index : " << distance(myset.begin(),iter_upper);

	print(iter_lower, iter_upper);

	cout << "distance for equal range : " << distance(iter_lower, iter_upper);
	// 0011133444555... diye gidiyor random sayılar
	// test ettik mesela 1 ler için distance 3 çıktı ...
	
}

===================================================================================================================================================================================

EQUALRANGE 
----------
Bunun return değeri pair olacak.

int main()
{
	multiset<int> myset;

	rfill(myset,20,Irand{0,9});
	print(myset);

	int x;

	// pair<multiset<int>::iterator, multiset<int>::iterator> ip = myset.equal_range(x);
	// auto neden gerekli açık sanırım :D:D:D:D

	//Modern C++ ta aşağıdaki gibi yazılır.
	auto ip = myset.equal_range(x);
	
	print(ip.first, ip.second); // Böyle yazılır ama daha güzeli var.
	
	-----------------------------------------------------------------------------------------------------------------------------------------------------------

	// DAHA GÜZEL OLAN KISIM
	// Structured binding ile birleştirebiliriz.

	auto [iter_lower, iter_upper] = myset.equal_range(x);
	
	// STRUCTUED BINDINGTE DERLEYICININ ÜRETTIĞI KOD AŞAĞIDA
	// auto object = myset.equal_range(x)
	// iter_upper is an alias for object.first
	// iter_lower is an alias for object.second

	-----------------------------------------------------------------------------------------------------------------------------------------------------------

	//BİR ÇOK SENARYDA IF WITH INIT İLEDE BİRLEŞTİREBİLİRİZ.

	if(auto [iter_lower, iter_upper] = myset.equal_range(x); iter_upper != myset.end())
	{
		//.....
	}
	//ÇOK ÖNEMLİ.

	Return değeri pair yada tuple olan funclarda structured binding çok işe yarıyor.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ALGORİTMA KARŞILIKLARI

Mülakatlarda çok sık soruluyor.

int main()
{
	vector<string> svec;
	rfill(10,10,svec);

	sort(svec.begin(),svec.end());
	print(svec);

	auto iter = lower_bound(ivec.begin(),ivec.end(),"necati"); //NOT : MINIMAL FORWARD ITERATOR ISTIYOR.
	cout << iter - svec.begin() << "\n"; // necatiyi ilk ekleyebileceğimiz yere baktık.
}

Mantık aynı ama bu algoritma.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SIRALAMA KRITERI LESS DEĞILSE BUNUDA VERMEK ZORUNDAYIZ.

int main()
{
	vector<int> svec;
	rfill(10,10,svec);

	sort(svec.begin(),svec.end(),greater{});   //DİKKAT !!!
	print(svec);

	auto iter = lower_bound(ivec.begin(),ivec.end(),"zeynep",greater{});   //DİKKAT !!! Sıralama kriterinide argüman olarak geçmeliyiz.
	cout << iter - svec.begin() << "\n"; // Zeynepi ilk ekleyebileceğimiz yere baktık.
}

Z ile ilgili birşey çıkmadı ve Zeynepin ekleneceği ilk konum 0 indexi.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EQUALRANGE RETURN DEĞERİ ITERATOR RANGE

int main()
{
	vector<int> svec;
	rfill(svec,50,Irand{0,40});

	sort(svec.begin(),svec.end());
	print(svec);

	auto [iter_lower, iter_upper] = equal_range(svec.begin(),svec.end(),9); //RETURN DEĞERİ PAIR UNUTMA
	print(iter_lower,iter_upper); // 
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN BÜYÜK EN KÜÇÜK ÖĞEYESAHIP ÖĞELERIN KONUMLARI

int main()
{
	vector<string> svec;
	rfill(svec,10,name);
	print(svec);

	auto iter_min = min_element(svec.begin(), svec.end()); // RANGE ISTIYORLAR VE RETURN DEĞERLERI ITERATOR
	auto iter_max = max_element(svec.begin(), svec.end());

	cout << "min = " << *iter_min << " ve dizinin "<< iter_min - svec.begin() < " indisli öğesi\n"; //C dizisi içinde kullanılabilirdi.
	cout << "max = " << *iter_max << " ve dizinin "<< iter_max - svec.begin() < " indisli öğesi\n"; //C dizisi içinde kullanılabilirdi.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİYELIMKI HEM EN KÜÇÜK HEMDE EN BÜYÜK DEĞERE IHTIYAÇ VAR.
O zaman aynı veri yapısını 2 kere dolaşmak maliyetli.1 kere dolaşmak daha iyi. Modern C++ ile bu geldi.

MINMAX_ELEMENT

int main()
{
	vector<string> svec;
	rfill(svec,10,name);
	print(svec);
	
	auto [itermin,itermax] = minmax_element(svec.begin(), svec.end());

	cout << "min = " << *itermin << "\n";
	cout << "max = " << *itermax << "\n";

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ahmet Semraya yürüyor muhabbeti :D:D:D	 Dillerin sürekli değişmesi durumu
Tuple a biraz değinildi. tuple <int,double, long,string> tutuyor herhangibir sınır yok
Sınıfta gerekmiyor ise tuple kullanılabilir.

Stephan T. Lavavej
Microsoft un STL ekibinin başında. İsminin baş harfleride STL.

SET BURADA BİTMİŞ OLDU

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR MÜLAKAT SORUSU

Vectore sürekli eleman ekleyeceğiz ama sırada hiç bozulmayacak

int main()
{
	std::vector<string> svec;

	for(int i = 0; i < 10; ++i)
	{
		auto s = rname(); // her seferinde sort yapmak mantıksız.
		cout << s << "\n";
	}
}

ÇÖZÜM
int main()
{
	std::vector<string> svec;

	for(int i = 0; i < 10; ++i)
	{
		auto s = rname(); // her seferinde sort yapmak mantıksız.
		cout << s << "\n";
		auto iter = lower_bound(svec.begin(),svec.end(),s);
		svec.insert(iter,s);
		print(svec);
		getchar();
	}
}


===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================

MAP
---
Anahtarın birer değer ile eşlenmesi durumuna deniyor.Veri yapısı sette olduğu gibi ikili arama ağacı.
Ekleme arama silme işlemleri anahtar ile yapılacak ve logaritmik karmaşıklıkta olacak. Burada sadece anahtar tutmak yerine, anahtarı anahtarla birlikte kullanılacak bir değerle
birlikte tutuyoruz.İngilizcede ilgili key in value değeri deniyor.

Set ve multiset ile özünde aynı ama farklılık nerede? 
Set ve multisette sadece key tutulurken burada key value çiftleri tutuluyor. Yani key value pairleri
Mapte bir arama yapıp konum elde edersek, o konumdaki öğe key value pairi.
Set var mı yokmu için kullanılırken, map belirli anahtara ait değere erişmek için kullanılıyor.

pair<key,value>

key <-> value

key const ama value const değil. Keyi çakartıp mapten yerine yeni bir key value pair konulabilir ama doğrudan key değiştirmek mümkün değil.

pair<keyi value>   Header file map
#include<map> yani 

set ile multiset arasındaki fark map ile multimap arasında da aynı şekilde.

Ör:
Rehberde kişilerin isimlerinden telefon numaralarına erişiyoruz.

mapte iki tane Onur Göksu olamazken
multimapte iki tane Onur Göksu olabilir.Bunlar ayrı kişiler olabilir.Telefon numaraları farklı olabilir.

TEMPLATE HALİ
template<typename Key, typename Value, typename Comp = less<Key>, typename A = allocator<pair<Key,Value>>>
class map{

};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	map<int,double>; // aslında tam açılımı aşağıdaki gibi.

	map<int, double,less<int>,allocator<pair<int,double>>> x;
}

Map'in interface'i ile set'in interface'i birbirine baya yakın. Burada farklılıklar anlatılacak.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	map<int,string> ismap;

	------------------------------------------------------------------------------------------------------------------------------------------------------------------

	BU MAPE INSERT EDERKEN PAIR<INT,STRING> TÜRÜNDEN DEĞERLER INSERT EDILECEK

	ismap.insert(pair<int,string>{123,"haydar"});
	ismap.insert(make_pair(145,"umut"));
	
	------------------------------------------------------------------------------------------------------------------------------------------------------------------

	C++ 17 ile CTAD GELDİ
	ismap.insert({29,"Zeynep"});
	
	------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	EMPLACE TE OLABILIR.
	ismap.emplace(55,"muhittin"); //Ctora geçeceğimiz argümanları emplace e veriyoruz
	
	------------------------------------------------------------------------------------------------------------------------------------------------------------------

	MAP İ DOLAŞMANIN BİRSÜRÜ YOLU OLABİLİR.

	// Küçükten büyüğe dolaşıyoruz burada
	for(auto iter = ismap.cbegin() ; iter != ismap.cend(); ++iter)
	{
		cout << iter->first << " " << iter->second << "\n";
	}

	Burada dikkat edilmesi gereken nokta, iter konumundaki öğe bir pair.Dolayısı ile iter->first dediğimizde pairin firstü.
	iter->second dediğimizde pairin secondu kullanılacak.

	------------------------------------------------------------------------------------------------------------------------------------------------------------------

	RANGE BASE FOR LOOP KOLAY BİR YAZIM SAĞLIYOR.

	for(const auto &p : ismap)
	{
		cout << p.first << " "<< p.second << "\n";  
	}

	------------------------------------------------------------------------------------------------------------------------------------------------------------------

	RANGE BASE FOR LOOP İLE STRUCTURED BINDINGİ BİRLEŞTİRELİM

	for(const auto &[age,name] : ismap) // range base for loop ile structured binding beraber
	{
		cout << name << " " << age << "\n";  
	}

	------------------------------------------------------------------------------------------------------------------------------------------------------------------

}

MOLA

===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================

MAP ÜZERINDEK İŞLEMLERE BAKALIM

int main()
{
	map<int,string> mymap;

	//map<int,string,greater<int>> mymap; // Burada karşılaştırma kriteri girilebilir.Büyükten küçüğe oluştururduk bu şekilde.Anahtar int

	for(int i = 0; i < 100; ++i)
	{
		mymap.emplace(Irand{1,100}(),rname());
	}

	std::cout << "size = " << mymap.size() << "\n";
	getchar();

	print(mymap,"\n"); // AYnı anahtardan bir tane var, Multimap olsaydı aynı anahtardan birden fazla olabilirdi.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAP LERİ ÇOK KULLANIYORSAK ALIAS MAP KULLANABİLİRİZ.

template <typename K, typename V>
using gmap = std::map<K,V, std::greater<k>>;

using namespace std;

map<int,string,greater<int>> mymap;    // böyle yazmak yerine aşağıdaki yazılır
gmap<int,string> mymap;

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖNCEKİ ÖRNEKTE BİR DEĞİŞİKLİK

int main()
{
	map<string,int> mymap; // ARTIK ANAHTAR/KEY STRING OLDU.STRİNGTEN BİR TANE OLABİLİR ÇÜNKÜ MAP. MULTİMAPTE DAHA FAZLA OLABİLİR.

	for(int i = 0; i < 100; ++i)
	{
		mymap.emplace(rname(),Irand{1,100}());
	}

	std::cout << "size = " << mymap.size() << "\n";
	getchar();

	print(mymap,"\n");

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CTOR GRUBUNA KISACA GİRDİK

DEFAULT CTOR
COPY CTOR
MOVE CTOR
RANGE CTOR
İNİT LİST CTOR

map<int,string> mymap; //Default ctor.

map<string,int> mymap{{"Ali",12},{"Ferda",34},{"Ayşe",26}}; //Init list ctor.

vector<pair<string,int>> myvec{{"Ali","12"},{"Ferda",34},{"Ayşe",26}}; 

map<string,int>mymap{myvec.begin(), myvec.end()}; // Range Ctor

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİĞER FUNCTIONLARDA AYNI

ÖR:

int main()
{
	vector<pair<string,int>> myvec{{"ali",12},{"ferda",34}, {"ayse",56},{"belgin",67}};

	map<string,int>mymap{myvec.begin(), myvec.end()};

	mymap.insert({"kerim",34}); // RETURN DEĞERI ITERATOR BOOL DEĞERI

	if(auto[iter,inserted] = mymap.insert({"kerim",56}); !inserted )
	{
		cout << "Ekleme yapilamadi << iter->first << "zaten var\n";
	}

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
#include <iomanip>
using namespace std;
int main()
{
	map<string ,Date> mymap;

	for(int i = 0; i < 100; ++i)
	{
		//mymap.insert({rname(), Date::random()});
		mymap.emplace(rname(), Date::random()); // Doğrudan değerlele başlatalım daha verimli.
	}

	std::ofstream ofs{"out.txt"};
	if(!ofs){
		std::cerr<< "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	ofs << left;

	for(const auto&[name,bdate] : mymap)
	{
		ofs << setw(20) << name << " " << bdate << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KEYLERİ DEĞİŞTİREMEYİZ AMA VALUE LARI DEĞİŞTİREBİLİRİZ.

#include <iomanip>
using namespace std;

int main()
{
	map<string ,Date> mymap;

	for(int i = 0; i < 500; ++i)
	{
		//mymap.insert({rname(), Date::random()});
		mymap.emplace(rname(), Date::random()); // doğrudan değerlele başlatalım daha verimli.
	}

	std::ofstream ofs{"out.txt"};
	if(!ofs){
		std::cerr<< "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}
	
	std::cout << "aranacak ismi girin: ";
	string name;
	cin >> name;

	if(auto iter = mymap.find(name); iter != mymap.end()) // BURADA İSMİ BULDUK.KEY BURADA NAME
	{
		cout << "bulundu\n";
		iter->second = Date{31,12,1999};  // BURADA DA VALUE DEĞİŞİMİ YAPTIK. VALUE BURADA DATE
	}
	else
	{
		std::cout << "bulunamadi\n";
	}

	ofs << left;

	for(const auto&[name,bdate] : mymap)
	{
		ofs << setw(20) << name << " " << bdate << "\n";
	}

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İLGİNÇ BİR FUNCTION. BU MAP TE VAR MULTİMAP TE YOK
operator[]

Aşağıdaki örnek ile ne yaptığını anlamaya çalışalım.Burada [] pointer çağrışı değilde içine key türden değeri yazdık(burada name)
sağınada değer girdik. mymap[name] = 9999;

İçerisine anahtarı yazıyoruz

int main()
{
	map<string,int>mymap;
	rfill(mymap,10,[]{return make_pair(rname(),rand());})
	print(mymap,"\n");

	string name;
	cout << "bir isim girin : ";
	cin>>name;

	mymap[name] = 9999; //DİKKAT
	print(mymap,"\n"); 
	
	//TEST EDİP DENE

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOT : EĞER [] İÇİNE YAZDIĞIMIZ ISIM YOKSA EKLEMEYE DÖNÜŞECEK !!!!!!!!!!!!!!!!!

ARKA PLANDA BU KEY MAPTA ARANIYOR, EĞER BULURSA, [] MAPTAKİ ÖĞENİN VALUE SUNA (SECOND YANİ) 
REFERANS DÖNDÜRÜYOR. BU ANAHTAR YOK İSE, YENİ BİR PAIR INSERT EDİYOR, FİRST OLARAK İÇİNE
GİRDİĞİMİZ DEĞERİ KULLANIYOR SECOND OLARAK VALUE İNİT EDİLEN DEĞERİ KULLANIYOR. ASLINDA 0 AMA
BURADA 9999 İLE BAŞLATILDIĞI İÇİN DEĞERİ 9999 OLDU.

YANİ VAR İSE VALUE DEĞİŞTİRİLEBİLİYOR, KEY YOKSA EKLİYOR.

BU ÖNEMLI ÇÜNKÜ TIPIK BIR IDIYOMDA KULLANILACAK. 

MULTIMAPTE BU [] YOK. SADECE MAP TE VAR !!!!!!!!!!!!!!!!
MANTIKEN [] MULTİMAPTE OLSAYDI, AYNI KEY DEN 2 VEYA DAHA FAZLA OLMUŞ OLSAYDI HANGİSİNİ DEĞİŞTİRECEĞİNİ BİLEMEZDİ.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SIK KULLANILAN BİR İDİYOM
-------------------------

VERI YAPISINDAKI HERBIR ÖĞEDEN KAÇ TANE OLDUĞUNU SAYMAK.

int main()
{
	vector<string> svec;

	rfill(svec,1000,rname); // hepsinden kaç tane var bu bulunacak.Prodda çok ihtiyaç duyuluyor.
	//print(svec);

	map<string, int> cmap; // maptaki stringler sayılacak value lar ise kaç tane bundan olduğunu tutacak.

	for(const auto&s : svec)
	{
		++cmap[s];		// Varsa bir artıracak yoksa ekleyecek.Yoksa value initten dolayı 0 ile başlayacak ama ++ ile 1 olacak :D:D:D
	}

	for(const auto&[name,count] : cmap)
	{
		cout << name << " " << count << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MÜLAKATLARDA BIRAZ DAHA ZORLUYORLAR. SAYILARI BÜYÜKTEN KÜÇÜĞE ISTIYORLAR

int main()
{
	vector<string> svec;

	rfill(svec,1000,rname); // hepsinden kaç tane var bu bulunacak.Prodda çok ihtiyaç duyuluyor.
	//print(svec);

	map<string, int> cmap; // maptaki stringler sayılacak value lar ise kaç tane bundan olduğunu tutacak.

	for(const auto&s : svec)
	{
		++cmap[s]; // varsa bir artıracak yoksa ekleyecek.
	}

	//MAPTAKI ÖĞELERI VECTORE AKTARABILIRIZ.

	//vector<decltype(svec)::value_type> myvec; Böylede olabilir.
	vector<pair<string,int>> myvec{cmap.begin(),cmap.end()}; 

	//Vectoru sıralayacağız.
	auto pred = [](const auto &p1,const auto &p2){
		return p2.second < p1.second;
	};

	sort(myvec.begin(), myvec.end(),pred);

	for(const auto&[name,count] : myvec)
	{
		cout << name << " " << count << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAPTAKİ KEYWORD DEĞİŞTİRİLMEK İSTENİRSE SİLİP YENİSİNİ EKLEMEK GEREKEBİLİR.

int main()
{
	map<string,int> mymap;
	
	rfill(mymap,10,[]{return make_pair(rname(),rand() % 1000);});
	print(mymap,"\n");

	cout << "eski ve yeni anahtarları girin: ";
	string oldkey, newkey;
	cin >> oldkey >> newkey;
	
	// BURAYA KADARKİ KOD ORTAK. AŞAĞIDAN DEVAM EDİLECEK.

	----------------------------------------------------------------------------------------------------------------------------------------------------------

	//BURASI ESKİ YÖNTEM. C++17 ÖNCESI

	if(auto iter = mymap.find(oldkey); iter != mymap.end())
	{
		auto val = iter->second;
		mymap.erase(iter);
		mymap.insert({newkey,val}); 
		std::cout << "Anahtar degistirildi\n";
		print(mymap,"\n");
	}
	else
	{
		std::cout << "bulunamadi\n";
	}

	----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//YENİ YÖNTEM. C++17 DE EKLENENLERI KULLANDIK

	EXTRACT FUNCTION

	if(auto iter = mymap.find(oldkey); iter != mymap.end())
	{
		auto handle = mymap.extract(iter);
		handle.key() = newkey;
		mymap.insert(std::move(handle));

		std::cout << "bulundu ve degistirildi\n";
		print(mymap,"\n");
	}
	else
	{
		std::cout << "bulunamadi\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

INSERT_OR_ASSIGN
C++17 ile geldi.

Map e bir ekleme yapmak istersek, bu ekleme mapta bu anahtar yoksa gerçekleşecek ve mapta bu anahtar varsa gerçekleşmeyecek.Bunu istiyoruz.

mymap.insert({"Mustafa",987}); 

İnsertin duruma göre bir dezavantajı var. Bu key mapte olsada olmasada biz bir pair<string,int> oluşturmuş oluyoruz.Bu key varsa ekleme yapılmayacağına göre
boşyere pair oluşturup destroy etmenin anlamı yok. Pair second unun init edilme maliyeti yüksekse, bu durum ciddi bir maliyet oluşturur. Eski C++ta eksiklerden biri buydu

BU anahtar var mı diye kontrol edip, eğer key yoksa değeri oluşturmak mantıklı.Anahtar yoksa oluşturacak.Insert or assign bunu yapıyor
Ayrıca eğer anahtar varsa nesneyi oluşturmuyor ama value sunu istediğimiz değere çekiyor.

return değeri yine iterator bool değeri.


int main()
{
	map<string,int> mymap;

	auto [iter,inserted] = mymap.insert_or_assign("hakki",9897); 
	// Önce hakki var mı diye bakacak, yoksa oluşturup ekleyecek.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	map<string,int> mymap;

	for(int i = 0; i < 10; ++i)
	{
		mymap.emplace(rname(), Irand{0,100}());
	}

	print(mymap,"\n");

	string name;
	cout << "isim girin : ";
	cin>> name;

	mymap.insert_or_assign(name,999);  // C++ 17 ile geldi. contains te c++20
	print(mymap,"\n"); // deniz ekleyecek, yoksa ekler, varsa eklemeyecek.Farkı nesneyi hiç oluşturmuyor.
}

NOT : DİYELİMKİ LİSTEDE AHMET VAR DEĞERİ 44, BİZ AHMETİ BU FUNCTİONLA EKLEMEYE ÇALIŞIRSAK NESNEYİ OLUŞTURMUYTOR AMA VAROLAN AHMETİDE 999 DEĞERİNE ÇEKİYOR !!!!!!!!!!!
		BU ÖRNEKTE HOCA BUNU YAPTI !!!!!!!!!!!!!!

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AT C++2017

[] ten farkı exception throw etmesi.

int main()
{
	map<string,int> mymap;

	for(int i = 0; i < 10; ++i)
	{
		mymap.emplace(rname(), Irand{0,100}());
	}

	print(mymap,"\n");

	string name;
	cout << "isim girin : ";
	cin>> name;

	try{
		mymap.at(name) = 7777; 
		print(mymap,"\n");
	}
	catch(const std::exception& e)
	{
		std::cout << "hata yakalandi ..." << e.what() << "\n";
	}

}

MOLA

===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================
===================================================================================================================================================================================


UNORDERED SET VE UNORDERED MAP
UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------

Yolumuz boost ile birçok yerde kesişebilir. Mesela network ile ilgili bir library yok ama boostta var.
Boostta çok fazla sayıda ilave container var.STD library eki containerlar işimizi görmeyince boosttaki ek
containerlar işimizi görebilir. Zaten Boosttaki containerların bir kısmı STL e dahil edildi. Mesela array, tuple, unordered container... 
bunlar boosttan küçük farklılıklarla boosttan alındı.

unordered set
unordered multiset

unordered map
unordered multimap

Hashtable veri yapısını kısaca yazalım.
Burada amaç anahtarla erişimin artık logaritmik karmaşıklıkta değil constant timeda yada constant time ile log karmaşıklık arasında yapılması.
Anahtarı bulmak nasıl O(1) karmaşıklıkta olacak.
Bunu yapmanın birden fazla yolu var.Ama bu tip veri yapılarına hashtable deniyor
Farklı farklı hashtable implementasyonları var tabi.

Öyle bir veri yapısı olsun ki, numaradan bize o numaranın sahibi olduğu isme eriştirsin. 20 elemanlı bir dizi oluştururuz. O elemenlarada isimleri yazarız mesela.
C deki lookup table ları düşün. Asal sayılara index ile erişmek. Birçok kere yaptık.

Problemi biraz değiştirelim, bu sefer telefon numaraları 0-20 arası değilde normal telefon nosu uzunluğunda. Bu durumda milyar uzunluğunda dizi tanımlamak çok anlamsız ve
verimsiz. Sonuçta index ile erişmek istiyoruz. Bu anahtarı bir function yardımıyla indexe dönüştürsek. Bu işi yapan functionlara hash function deniyor ve buradan
elde edilen değere hash değeri deniyor.

89765498 ==> 12 indexine dönüştürecek
21257894 ==> 55 indexine dönüştürecek gibi.

Böylece biz hash functionunun bize verdiği indexi vectorel bir veri yapısında kullanacağız ve index ile erişeceğiz.
İdeal olarak bu hash functionu bütün farklı anahtarları farklı indexlere hash etse çok güzel olur.

Hayatın şöyle bir gerçeği var :D:D:D
Biz bu ideal functionu nasıl bulacağız. Ne kadar iyi hash functionu yazarsak yazalım collision denen durumdan kaçınılmaz yani çakışma.

Yani 2 farklı anahtar var ve hash functionu bu iki anahtarı aynı indexe dönüştürdü.Aşağıdaki gibi yani
89765498 ==> 17 
21257894 ==> 17

Bunun çözülmesi gerekiyor. Bunun için farklı farklı algoritmalar var
Bizim vectorel veri yapısı bağlı listelerden oluşsa 3:06 da şekil var.Yani vectorun herbir indexinde bir bağlı liste var.
Anahtarı alıp hash functionu çağırdık ve bu bize bir index verdi, eğer collision yok ise o indexte zaten benim anahtarıma karşılık gelen değer olacak.
Diyeilmki 2 farklı anahtar bu indexe hash edildiyse o zaman bir bağlı listeye erişeceğim, o bağlı listeyi takip edeceğim.

Örneğin key 12342135 olsun ama 1 indexini versin hash functionu, o zaman 3 anahtar çakışmışsa bu bağlı listede 3 öğe var.
1. node a bakılır aradığımız bu değilse, 2. ve 3. ye bakılır.

BU VERI YAPISININ EN VELİRLEYİCİ ÖZELLİKLERİNDEN BİR TANESİ KALİTELİ BİR HASH FUNCTIONU. BU MATEMATİĞİNDE KONUSU !!!!!!!!!!!!!!!!!

Bazı durumlarda bizimde hash functionu yazmamız gerekecek. HErşeyden önce anahtarı indexe dönüştüren bir hash functionuna ihtiyacımız var,
popüler olarak bu işi yapan sınıf veya functiona hasher deniyor. Unordered set böyle.

Unordered map ise bu durumda pair ler tutuluyor. İndex ile eriştiğimiz bağlı listede pairler var.anahtar değer çiftleri.
Bunu template hale getirdiğimizi düşünelim. template parametrelerine de bakmamız gerekir.

Hash functionu template in bir tür parametresi, yani hashtable kullanabilmek için (unordered set ve unordered map kullanabilmemiz için)
bir hasher türüne ihtiyaç var. bu bir func veya lambda func yada function object.. olabilir.
STD library nin kendi hash func nesnesi var, dolayısı ile standart türlerden hangisi olursa olsun, bu tür standart kütüphaneye ilişkinse
o türü hash etmek için mutlaka bir hasherımız var.

Eğer bir hashtable da kendi nesnelerimizi tutmak istersek bu durumda bu türü hash eden bir hasher a ihtiyacımız var.
Bunu kendimiz yapacağız. Bu containerlarda aritmetik değerler tutmak hiç sorun değil, standart library den değerler tutmak sorun değil ama
custom typelar için bir hasher oluşturmak zorundayız. Nasıl yapıldığını göreceğiz.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEMPLATE YAPISINA BAKALIM
-------------------------
unordered set ve unordered multiset aynı header fileda
set ile neredeyse aynı ama bir ciddi fark var, biri ikili arama ağacı diğeri hash table, kullanıcı açısından ikiside arama yapıyor.
Associative containerlarda equivalance kullanılıyor. set<int> demek set<int, less<int>> kullanmış oluyoruz.
Arama yaptığımızda aranan öğe sette var mı dendiğinde karşılaştırma buna göre yapılıyor. !(a op b) ve !(b op a) ---> burası true ise a == b olmuş oluyor.
Buna equivalance deniyor geçen derste yazmıştım.

Hash Containerlarında ise (unordered set ve unordered map lerde) eşitlik doğrudan equality ile sınanıyor. a == b diye kıyaslanıyor.
Önemi şu sette bir öğeyi tutabilmek için 2 date nesnesinin < ile karşılaştırabilmemiz gerekiyor.
Date nesnesini unordered sette hash table da tutmak istersek date in < ü değil, date in == karşılaştırmasını yapacak functor gerekiyor.
Standart library de bu doğrudan equal_to functor ı.


#include <unordered_set>

int main()
{
	unordered_set<int,hash<int>> ;  

	// BIRINCI PARAMETRE SETTE TUTULACAK ÖĞE TÜRÜ. KEY TÜRÜ
	// IKINCISI ISE HASH IŞLEMINI YAPACAK TÜR.
	// ÖYLE FUNC OLACAKKI 1. TEMPLATE TÜR PARAMETRESİ TÜRÜ DEĞERİ ALACAK (CONST& İLE) VE SIZE_T TÜRÜNDEN DEĞER DÖNDÜRECEK.
	// BURADA HASH<INT> DEFAULT ARGÜMAN OLARAK KULLANILIYOR. BU HASH FUNC CALL OPER FUNC İLE BİR İNT ALIP ONU
	// İNDEXE DÖNÜŞTÜRÜYOR. HASH<STRING> OLSAYDI YİNE BU SEFER () OPER FUNC STRİNG İ BİR İNDEXE DÖNÜŞTÜRECEK.

}

template<typename T>
struct Hash{
	size_t operator()(const T&)const
	{
		
	}
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	hash<int> hasher;
	hasher(897987); // bu anahtarı indexe dönüştürecek.
	
	cout << hasher(897987);
	cout << hasher(897988); // dikkat argüman bir fazlası.
	// bambaşka 2 index verdi.Hasher ın verdiği index 0 - size_t nin max ı arasında
	// bunu vectorel veri yapısında indexe dönüştürmek containerın kendi kodlarıyla yapılıyor.
	// yani hasher ın aldığı indexi doğrudan bu containerda kullanmıyoruz. Container bu indexi alıp buradaki öğe sayısı ile ilgili bir değere dönüştürüyor.
	// Buradaki öğe sayısına bucket deniyor.

}


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADAKI SISTEMIN DÜZGÜN ÇALIŞMASI IÇIN, AYNI ANAHTARIN HER ZAMAN AYNI DEĞERE HASH EDILMESI GEREKIYOR.
FARKLI İNDEXLER VERMESİ KABUL EDİLEBİLİR BİR DURUM DEĞİL.

ör:
int main()
{
	hash<string> hasher;
	cout << hasher("yunus") << "\n";
	cout << hasher("yunus") << "\n";
	cout << hasher("yunus") << "\n";
	cout << hasher("ali")<< "\n";
	cout << hasher("veli")<< "\n"; // farklı olanlar için farklı size_t değerleri gelir. Aynı olanlar için aynı size_t değeri gelir.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKI KODU AŞAĞIDAKI GIBIDE YAZABILIRIZ.

ör:
int main()
{
	cout << hash<string>{"yunus"}() << "\n"; // böyle de geçici nesneyle olabilir
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİKKAT!!

int main()
{
	unordered_set<int>	// Burada hash in int açılımını kullanmış olacağım.
	unordered_set<Date>	myset; // SENTAKS HATASI ÇÜNKÜ HASH IN DATE AÇILIMI YOK.BÖYLE BİR DURUMDA HASH<DATE> İ OLUŞTURMAK GEREKİR.
	
	myset.insert(Date{11,1,1987}); //Neden sentaks hatası ? YUkarıdaki sebepten ötürü hash<Date> yok.
}

2 Yolu var.
1. std namespace te explicit specialization yapıp hash<Date> için kendi kodumu oluşturacağım.
2. Doğrudan hasher functor oluşturabiliriz.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, typename H = std::hash<T>, typename E = std::equal_to<T>, typename A = std::allocator<T>>
class UnorderedSet{
	
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Eğer biz standart türlerden birini kullanıyorsak hiçbir sorun yok.Set i kullanır gibi kullanacağız.

int main()
{
	unordered_set<string> myset;
	for(int i = 0 ; i < 100;++i)
	{
		myset.insert(rname());
	}
	
	myset.find()
	myset.contains() // burada bu funclar çağrılabilir interface aynı. hashtable var ve O(1) karmaşıklığında arama yapıyoruz.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HASHER
------
Hashtable da hepsi için tutulabimesi için anahtarlarımızı size_t ye hash eden bir functiona ihtiyaç var.
Bunu yapmanın 2 yolu var.

namespace std{
	template<>
	struct hash<Date>
	{
		size_t operator()(const Date &date)const
		{
			std::hash<int> hasher;
			return hash<int>{}(date.month_day() + date.month() + date.year()); //Amatörce böyle yazılabilir ama professional şekilde bir sonraki ders yazılacak.
		}
	};	
}

int main()
{
	auto mydate = Date::random();
	std::cout << hash<Date>{}(mydate); // bir index elde ettik.
}


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	unordered_set<Date> myset; // Eğer bunu kullansaydık ikinci template argümanı olarak hash<Date> i kullanacaktık, ne zaman bir hash gerekse yukarıdaki operator()(const Date &date) function çağrılacak.

	//Bir problem daha var.Bİzim equal_to nun date açılımına ihtiyacımız var. Arka taraftaki kodların eşitlik sorgulaması için 2 date nesnesini == ile karşılaştırıyor.
	// Date sınıfı türünden iki nesneyi == ile karşılaştırma olanağı yoksa buna == operatörü overload edilmemişse yine sentaks hatası olacak.Bizim Date sınıfında operator= overload edilmişti.

}

*/
