/*
 
DÜNKÜ DERSTEKİ YAZILANLARI BURAYADA KOPYALIYORUM
------------------------------------------------
UNORDERED SET VE UNORDERED MAP
UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------

Yolumuz boost ile birçok yerde kesişebilir. Mesela network ile ilgili bir library yok ama boostta var.
Boostta çok fazla sayıda ilave container var.STD library eki containerlar işimizi görmeyince boosttaki ek
containerlar işimizi görebilir. Zaten STL deki containerların bir kısmı STL e dahil edildi. MEsela
array, tuple, unordered container... bunlar boosttan küçük farklılıklarla boosttan alındı.

unordered set
unordered multiset

unordered map
unordered multimap

Hashtable veri yapısını kısaca yazalım.
Burada amaç anahtarla erişimin artık logaritmik karmaşıklıkta değil constant timeda yada constant time ile log karmaşıklık arasında yapılması.
Anahtarı bulmak nasıl O(1) karmaşıklıkta olacak.
Bunu yapmanın birden fazla yolu var.Ama bu tip veri yapılarına hashtable deniyor
Farklı farklı hashtable implementasyonları var tabi.

Öyle bir veri yapısı olsun ki, numaradan bize o numaranın sahibi olduğu isme eriştirsin. 20 elemanlı bir dizi oluştururuz. o elemenlarada isimleri yazarız mesela.
C deki lookup table ları düşün. Asal sayılara index ile erişmek. Kaç kere yaptık.

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

Örneğin key 12342135 olsun ama 1 indexini versin hash functionu, o zaman 3 ahantar çakışmışsa bu bağlı listede 3 öğe var.
1. node a bakılır aradığımız bu değilse, 2. ve 3. ye bakılır.

BU VERI YAPISININ EN BELİRLEYİCİ ÖZELLİKLERİNDEN BİR TANESİ KALİTELİ BİR HASH FUNCTIONU. BU MATEMATİĞİNDE KONUSU !!!!!!!!!!!!!!!!!

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
Arama yaptığımızda aranan öğe sette var mı dendiğinde karşılaştırma buna göre yapılıyor. !(a op b) ve !(b op a) ---> burası true ise a ==b olmuş oluyor.
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

DÜNKÜ DERS BURADA BİTTİ.

================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
================================================================================================================================================================================================= 
 
UNORDERED ASSOCIATIVE CONTAINERSTA KALMIŞTIK

Bunlar bildiğimiz hashtable veriyapısı, yani değer ile eşlemenin sabit zamana çekilmeye çalışıldığı veri yapısı.

Elimizde hash func var.Bu func aramada kullanılacak değeri indexe dönüştürüyor bu işleme hashing deniyor.Hasher a çırpılama deniyor hoca türkçe tabir için türkçede.

Hash functionundan istenen aynı anahtarı aynı tamsayı değerine döndürmesi.Mümkün olduğunca farklı anahtar değerlerini farklı tamsayılara dağıtması gerekiyor ama 
collision kaçınılmaz durum oluyor burada.Yani birden fazla anahtar için aynı index değeri elde ediliyor.Farklı türden çözümler var, STL de vectorel bir veri yapısında 
eleman olarak bağlı listesi kullanarak çözülüyor bu. Collision yoksa tek seferde erişiyoruz.

Hash functionunun performans üzerindeki etkisi çok önemli. Arka planda vectorel veri yapısındaki öğe sayısına bucket size deniyor.
Tek bir öğeye bucket deniyor. Bir bucketta bir veya daha fazla öğe var.Bunlar işte bağlı listeler. İmplentation defined olarak singly veya doubly olabilir.

Unordered set ve Unordered map grubunun, Associative containerlarla ile interface i neredeyse aynı.Bazı detaylar saymazsak.

Programcı benchmark yaparken associative den unordered associative e geçebilir. Unordered ın bucket denen ayrı bir interface i var.

Aritmetik pointer standart library deki türler için hasher yazmamıza gerek yok.
Custom type için 2 şart sağlanmalı. 
Bir hasherımız olmalı. Bunun 2 yolu var.
1. std::hash e explicit specialization yazmak
2. date hasher functor oluşturabiliriz.


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HATIRLATMA !!!
template <typename T, typename H = std::hash<T>, typename E = std::equal_to<T>, typename A = std::allocator<T>>
class UnorderedSet{

};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR ÖNCEKİ DERS YAZDIĞIMIZ HASHER BÖYLEYDİ.

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

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "date.h"
#include <unordered_set>
#include <iostream>

using namespace std;
int main()
{
	unordered_set<Date> myset;

	for(int i = 0 ; i < 100; ++i)
	{
		myset.insert(Date::random()); // SENTAKS HATASI OLDU BURADA.
	}								  // Eşitlik karşılaştırması ve hash işlemi yapılmalı
	
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LEGAL HALE GETİRELİM

namespace std{
	template <>
	struct hash<Date>{
		size_t operator()(const Date& d)const
		{
			std::hash<int> hasher; 
			return hasher(d.year()) + hasher(d.month()) + hasher(d.month_day()); // dün daha farklı yazdık bugün değiştiriyoruz keyfi olarak
		}
	};
}


int main()
{
	unordered_set<Date> myset;

	for(int i = 0 ; i < 100; ++i)
	{
		myset.insert(Date::random()); // GEÇERLİ ÇÜNKÜ HASH<DATE> VAR AYNI ZAMANDA EQUAL_TO<DATE> IÇINDE OPERATOR== FUNC KULLANILACAK VE BUDA YAZILMIŞTI ZATEN.
	}								   
}

NOT : DATE İÇİNDEN OPERATOR==  SİLİNİRSE BU İŞLEM YAPILAMAZ.!!!!!!!!!!!!!!!!!
	  DATE İÇİNDEN SİLERSEK GÖRÜRÜZ HATAYI.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KENDİMİZDE TÜR OLUŞTURUP YAPABİLİRDİK.

HATIRLATMA KISMINDA TEMPLATE YAPISINA BAKILINCA 2. ARGÜMAN OLARAK HASHER GÖNDERIYORUZ ASLINDA.

struct DateHasher{							//DİKKAT
	size_t operator()(const Date& d)const
	{
		std::hash<int> hasher; // dün daha farklı yazdık bugün değiştiriyoruz keyfi olarak
		return hasher(d.year()) + hasher(d.month()) + hasher(d.month_day());
	}
}


int main()
{
	unordered_set<Date,DateHasher> myset; //DİKKAT

	for(int i = 0 ; i < 100; ++i)
	{
		myset.insert(Date::random()); // GEÇERLİ
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BÖYLEDE OLUR

struct DateHasher{							
	size_t operator()(const Date& d)const
	{
		std::hash<int> hasher; // dün daha farklı yazdık bugün değiştiriyoruz keyfi olarak
		return hasher(d.year()) + hasher(d.month()) + hasher(d.month_day());
	}
}

//EKLENDİ
//Bunuda 3. template tür parametresinin yerine yazabiliriz.

struct DateEqual{							
	size_t operator()(const Date& dx,const Date &dy)const
	{
		return dx.year() == dy.year() &&
			   dx.month() == dy.month() &&
			   dx.day() == dy.day(); //day olmayabilir dikkat
	}
}


int main()
{
	unordered_Set<Date,DateHasher,DateEqual> myset; //DİKKAT

	for(int i = 0 ; i < 100; ++i)
	{
		myset.insert(Date::random()); // GEÇERLİ
	}
}

Burada bir sıra yok. Associative Container olsaydı dolaştığımızda belirli bir sıraya göre dolaşacaktı,
Unordered sette böyle bir sıra yok. Zaten dolaşmanında anlamı yok.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA YANİ UNORDERED ASSOCIATIVE DE BİR SIRA YOK. ASSOCİATİVE DE VARDI.

Bir unordered sette dolaşmaya çok ihtiyaç yok ama dolaşalım

int main()
{
	unordered_set<int>us;

	for(int i = 0; i < 100; ++i)
	{
		us.insert(Irand(0,1000)();
	}

	for(auto i : us)
	{
		std::cout << i << " ";  // öğeler karmaşık.multiset olsaydı bir öğeden daha çok olacaktı
	}

}

us. yazıp interface e bakılabilir yukarıda.

Modern C++ öncesinde associative containerların merge functionu yoktu.Listin vardı ama bunların yoktu.Merge daha sonra eklendi.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUCKET INTERFACE FUNCLARI YABANCI GELEBİLİR.

#include <iomanip>
int main()
{
	vector<string> svec;
	rfill(svec,10000,rname);

	map<string,int> cmap; 

	for(const auto &name : svec){
		++cmap[name];
	}

	cout << left;
	for(const auto &[name,count] : cmap)
	{
		std::cout << setw(20) << name << " " << count << "\n";
	}
}

Sonuçlar less fucntoru ile oluşturulduğu için key ler küçükten büyüğe.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DÜNKÜ ÖRNEĞİ UNORDERED İLE YAZALIM

#include <iomanip>
int main()
{
	vector<string> svec;
	rfill(svec,10000,rname);

	unordered_map<string,int> cmap; 

	for(const auto &name : svec){
		++cmap[name];
	}

	//Buraya kadar olan kısımda sonuçları yazdırdığımızda belirli bir sıra yok.Dünkü Derste Associative ile unordered farkını yazmıştık.Nedeni orada var.

	vector<pair<string,int>> vec{ cmap.begin(), cmap.end() }; // Range Ctor ile vector olarak init ettik.

	//SORT EDELIM
	sort(vec.begin(), vec.end(), 
	[](const auto &px, const auto &py){ 
	return px.second > py.second || (px.second == py.second && px.first < py.first); });

	cout << left;
	for(const auto &[name,count] : cmap)
	{
		std::cout << setw(20) << name << " " << count << "\n";
	}
}

ÇIKTISI BAYA GÜZEL.YAZ.

Dün gördüğümüz funcları değilde bucket interaface ine bakacağız

==================================================================================================================================================================================================
==================================================================================================================================================================================================

BUCKET INTERFACE 

Hepsinin ne işe yaradığı yanında yazıyor aşağıda

int main()
{
	unordered_set<string>us;
	std::cout << "bucket count        : "  << us.bucket_count() << "\n"; // Bucket sayısını verir.Default 8 bucket var
	
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	unordered_set<string>us(128);
	std::cout << "bucket count       : "  << us.bucket_count() << "\n"; // 128 bucket var artık.

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------

	unordered_set<string>us(128);
	for(int i = 0; i < 100; ++i)
	{
		us.insert(rname());
	}
	std::cout << "size				  : " << us.size() << "\n";  // 86 çıktı hocada
	std::cout << "bucket count       : "  << us.bucket_count() << "\n";  // 128 adet zaten

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------

	BU BUCKET LARIN HEPSINI DOLAŞIP BIR BUCKETIN HANGISINDE OLDUĞUNU BULABILIRIZ.

	unordered_set<string>us(128);
	for(int i = 0; i < 100; ++i)
	{
		us.insert(rname());
	}
	
	std::cout << "size				  : " << us.size() << "\n";  
	std::cout << "buckket count       : "  << us.bucket_count() << "\n";
	
	us.bucket("ahmet"); // Return değeri varsa ahmetin bulunduğu bucket.
						// bu çok istediğimiz işlem değil aslında önemli olan hangi parametreleri değiştireceğimiz.

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	std::cout << "max bucket count degeri    : " << us.max_bucket_count() << "\n"; // 536870911 gibi bir değer çıktı

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	LOAD FACTOR

	std::cout << (double)us.size() / us.bucket_count(); // C style casting yazdık. Containerdaki öğe sayısının bucket sayısına oranını yazdırdık.
														//BU ORANA LOAD FACTOR DENİYOR.AYNI ZAMANDA FUNCTION ISMI.AŞAĞIDA YAZILDI.

	CONTAINERDAKI ÖĞE SAYISININ BUCKET SAYISINA ORANINI YAZDIRDIK. HOCADA 0.67 ÇIKTI. BUNA LOAD FACTOR DENIYOR !!!!!!!!!!

	std:cout << "Load Factor        : " << us.load_factor() << "\n";

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------

	MAX LOAD FACTOR
	---------------
	Hem set hemde get function.Eğer argüman göndermeden çağırırsak default geçerli olan max load factor veriyor.Default 1
	128 bucket varken sürekli eleman ekleşrsek eleman sayısı arttıkça collision artacak.128 bucket var diyelim ama 1000 elemanım var.
	Bu veri yapısı bir avantaj sağlamayacak.

	Max Load : Öyle bir load factor ki bu değere erişilince rehash yapılacak. Yani bucket sayısı artırılıp tüm öğeler yeniden konumlandırılacak.
	Bucket count 128 den daha yüksek bir sayıya çıkacak.

	std:cout << "Max load factor        : " << us.max_load_factor() << "\n"; // Maximum load factor değerini yazdı. 1

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	100 ELEMAN EKLEYIP TOPLU HALDE TEKRAR BAKALIM 
	BURASI ÖNEMLİ !!!!!!!!!!

	unordered_set<string>us(128);
	for(int i = 0; i < 100; ++i)
	{
		us.insert(rname());
	}

	std::cout << "Size				  : "  << us.size() << "\n";
	std::cout << "Bucket Count        : "  << us.bucket_count() << "\n";
	std::cout << (double)us.size() / us.bucket_count()<<"\n";
	std::cout << "Load Factor         : " << us.load_factor() << "\n";
	std::cout << "Max Load Factor     : " << us.max_load_factor() << "\n";

	//100 eleman daha ekliyoruz.
	for(int i = 0; i < 100; ++i)
	{
		us.insert(rname());
	}
	
	std::cout << "Size				  : "  << us.size() << "\n";
	std::cout << "Bucket Count        : "  << us.bucket_count() << "\n";
	std::cout << (double)us.size() / us.bucket_count();
	std::cout << "Load Factor         : " << us.load_factor() << "\n";
	std::cout << "Max Load Factor     : " << us.max_load_factor() << "\n";

}

Max load factore her erişildiğinde rehash yapıldı.

ÇIKTI
-----
Size                : 87
Bucket Count        : 128
0.679688
Load Factor : 0.679688
Max Load Factor     : 1

Size                : 155
Bucket Count        : 1024
0.151367
Load Factor         : 0.151367
Max Load Factor     : 1


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIZ ISTERSEK MAX LOAD FACTORU DEĞIŞTIREBILIRIZ.

us.max_load_factor(0.75f); // artık 0.75 ine gelince rehash yapılacak ve bucket sayısı artırılacak.
float parametreli ender functionlardan biri. return değeride float.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CTORA BAŞLANGIÇTA BUCKET SAYISINIDA VEREBILIRIZ.
Yukarıda zaten gösterildi örnektede var.

unordered_set<string> us(237);

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUCKET INTERFACE INDEKI FUNCLARLA BUCKETTA HANGI DEĞERLER VAR ONLARI GÖREBILIRIZ. BU SAYEDE INCE AYARI KONTROLLÜ BIR ŞEKILDE KENDIMIZ YAPABILIRIZ.

int main()
{
	unordered_set<string>us(128);
	for(int i = 0; i < 100; ++i)
	{
		us.insert(rname());
	}

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr <<"out.txt olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	ofs << "size			: " << us.size() << "\n";  //burayı yaz 
	ofs << "bucket count       : "  << us.bucket_count() << "\n"; 
	ofs << "max bucket count degeri    : " << us.max_bucket_count() << "\n";
	ofs << (double)us.size() / us.bucket_count()<<"\n"; // C style yazdık.
	ofs << "load factor        : " << us.load_factor() << "\n";
	ofs << "Max load factor        : " << us.max_load_factor() << "\n";


	// C++20 ILE BIRLŞIKTE SSIZE ISIMLI FUNCTION GELDI. SIZE DAN FARKLI IŞARETLI BIR TAMSAYI OLARAK VERIYOR SIZE DEĞERINI.
	// BÖYLECE IŞARETLI IŞARETSIZ KARŞILAŞTIRMALARINDA DERLEYICININ UYARI MESAJINI KESEBILIYORUZ.
	// DÖNGÜ DEĞIŞKENININ NEGATIF OLMASIYLA DÖNGÜDEN ÇIKABILIYORUZ.
	// İŞARETLI TÜRLERLE YAPILAN ARITMETIK IŞLEMLERIN MAKINA DÜZEYINDE BAZEN IŞARETSIZ TÜRDEN YAPILAN SAYILARLA YAPILAN IŞLEMLERINE GÖRE AVANTAJ SAĞLADIĞI YERLERDE
	// IŞARETLI TÜRÜ KULLANMAK ISTEYEBILIRIZ. 
	// ssize(us). CONTAINER DOLAŞSAYDIK BUNU YAZABILIRDIK AMA BUCKET DOLAŞACAĞIZ O YÜZDEN AŞAĞIDAKI GIBI DEVAM EDIYORUZ.


	//DİKKAT !!!!
	// bucket_size() diye bir function kullanılacak.İlgili bucketta kaç tane öğe olduğunu gösteriyor.

	for(int i = 0 ; i < us.bucket_count(); ++i)
	{
		ofs << "|" <<setw(2) << i << "| [" << us.bucket_size(i) <<"] \n";
	}
	// ilk görülen kaçıncı bucket olduğu yanında kaç öğe olduğu. Mesela ilkinde 2 rakamı yazıldı demekki collision var.	
	

	ÇIKTI
	-----
	size			: 85
	buckket count       : 128
	max bucket count degeri    : 536870911
	0.664062
	load factor        : 0.664062
	Max load factor        : 1
	| 0| [1]
	| 1| [0]
	| 2| [1]
	| 3| [1]
	| 4| [0]
	| 5| [2]
	| 6| [0]
	| 7| [1]
	....		diye gidiyor hatta bazıları 2 veya 3 var, yani collision var.

	----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//DİKKAT!!!!
	// BURADAKİ BEGIN VE END FUNCLARININ PARAMETRELERİNE DİKKAT. BAĞLI LİSTENİN İTERATÖRÜ OLDUĞUNDAN BEGİNİN VE ENDİN PARAMETRESİ OLAN OVERLOADLARI VAR  !!!!!!!!!!
	// ARGÜMAN OLARAK BUCKET COUNT DEĞERİ VERİLDİ.

	for(int i = 0 ; i < us.bucket_count(); ++i)
	{
		ofs << "|" <<setw(2) << i << "| [" << us.bucket_size(i) <<"] ";
		
		//SONRADAN EKLEDIK BUNU.ARTIK STRINGLERIDE YAZDIRDIK.
		for(auto iter = us.begin(i); iter != us.end(i); ++iter) //DİKKAT !!! BURASI ÇOK KRİTİK !!!!!!!!!!!!!!!!!!!!!! begin ve end in içine bak !!!!!!!!!!!!!!
		{														// BEGIN VE END IÇINE ILGILI BUCKET DEĞERINI VERIP O RANGE TE DOLAŞABILIRIZ
			ofs << *iter << " ";
		}
		ofs << "\n";
	}
	// ilk görülen kaçıncı bucket olduğu yanında kaç öğe olduğu. Mesela ilkinde 2 rakamı yazıldı demekki collision var.
}

ÇIKTI
-----
| 0| [1] melih
| 1| [0]
| 2| [3] tugra orkun taci // 3 tane collision
| 3| [1] kerim
| 4| [1] necmettin
| 5| [0]
| 6| [0]
| 7| [1] yasar
| 8| [0]
| 9| [1] sadettin



Yukarıdakilkerden 1 adet olanlara doğrudan erişirken, 2 veya daha fazla olanlarda collision olduğundan bir sorgulama daha yapacağız.Amortised Constant time

Buradaki bucket sayısı load factor hash functionun kalitesi.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOĞUNLUKLA BU KADAR İNCE AYAR YAPMAMIZ GEREKMEYECEK

us.rehash(400); // BUCKET SAYISINI 400 YAPIYOR.ARGÜMAN BUCKET SAYISI.TEST ETTİM 512 YAPTI.1500 YAPTIM 2048 YAPTI.
us.reserve(); // MAX_COUNT TANE BUCKET RESERVE EDILEBILIYOR.DOĞRUDAN MAX_COUNT TANE BUCKET I RESERVE EDEBILIYORUZ.ASLINDA REHASH ILE AYNI IŞLEMI YAPIYOR.

Tek fark rehash bucket sayısını alıyor, reserve dediğimizde bu değer size.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KISACA GÖZATALIM

us.bucket() -> bir öğenin bucket nosunu veriyor.key ile arama yapabiliriz.
us.bucket_count() -> Toplam bucket sayısını getiriyor.
us.bucket_size() -> Bİr bucketta kaç öğe var.index veriyoruz oradaki öğe sayısını veriyor.
load_factor -> eleman size / bucket_size
.... baktık diğerlerine.



==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================


CONTAINER ADAPTÖRLERİ
---------------------
Bunlar container değil ADT-ABSTRACT DATA TYPE
Bunlara container adapter denmesinin sebebi, containerı eleman olarak alıyorlar ve o containerın interfaceini bu soyut veri yapıları için adapte ediyorlar.

Stack : Son giren ilk çıkar.LIFO

Queue : ilk giren ilk çıkar. FIFO

Priority_queue : Kim önce girerse girsin önceliği yüksek olan kuyruktan çıkıyor.
priority queue anlayıp kullanmak için ve bu sınıf olmadanda kendi implementasyonumuzu yapabilmemiz için biraz heap veri yapısını bilmemiz gerekiyordu.
Burası bellek alanı anlamındaki heap değil. Heap veri yapısından geliyor bu. işin güzel tarafı bu veri yapısı bize sınıf şablonu olarak sunuluyor ve STL
algoritmalarıda var. Biz bunları kullanarak bir öncelik kuyruğunu bir vector üstünde oluşturabiliriz.

heap algoritmaları algorithm header fileda yer alıyor
make_heap
push_heap
pop_heap
sort_heap

Sadece 2 header file var.Stack ve queue. priority queue ve queue aynı header file içinde

==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================

STACK CONTAINER ADAPTER
-----------------------
Stack veri yapısını implemente eden sınıf şablonu.Recursive herhangibir algoritmayı bir stack kullanarak iterative hale getirebiliriz.
stack header file içinde yer alıyor. STL deki stack bir sınıf şablonu.

int main()
{
	stack<double> 
	// ilk argüman kullanılacak verinin türü.Date,double , int ...
	// İkinci tür parametresi explicit olarak verilmezse deque<int> kullanılır.
	// İkinci argümanı bizim seçmemizde bir motivasyon var mı %95 hayır
	// Ama geriye kalan ihtimal için mesela vector kullanılabilir.

	stack<int,vector<int>> mystack; 
	//Eleman olarak deque yerine eleman yerine vector kullanılacak.
	//Vector deque farkı ne burada ? Container argümanını değiştirmemiz gerekiyor.Görülecek.

	stack<int>; 
	//genelde böyle kullanılıyıor.

}

Dİğer kullanımlarda aşağıdaki template alias kullanılması iyi bir seçenek.

template <typename T>
using stack = std::stack<T,std::vector<T>>;

bu şekilde alias template te kullanılıyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Burada çok fazla function yok zaten ihtiyaçta yok.

int main()
{
	stack<int> s = {1,4,7,8}; //SENTAKS HATASI. İnit list ctor yok. 
	stack<int> x{4}; // SENTAKS HATASI
	stack<int> x(5); //SENTAKS HATASI

	
	Hangi Ctorlar var
	-----------------
	Default ctor
	Copy ctor
	Move Ctor

	ÖDEV : STACK SINIF ŞABLONUNU YAZ. 1:06

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	for(int i = 0; i < 10; ++i)
	{
		s.push(i);
	}

	cout << "size = " << s.size() << "\n"; //10
	s. ile varolan funclar görülür zaten çok az 5-10 civarı func var.

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	s.top(); // Yığındaki ilk öğeye eriştirir. Referans semantiği ile eriştiriyor. 

	s.top() = 45;
	std::cout << s.top() << "\n";

	NOT : S.POP UN RETURN DEĞERI VOID !!!!!!!!!!!!!!!!
		  Diğer diller gibi çıkartılan elemanın değeri diye birşeyi göstermiyor.
	--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	stack<string> name_stack;

	for(int i = 0; i < 10; ++i)
	{
		auto s = rname();
		cout << s << "Yigina push ediliyor\n";
		name_stack.push(s);// s lvalue expr. move(s) yapsaydık artık push un sağ taraf & parametreli kod çalışacaktı ve kod daha efektif olacaktı.
	}

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	AŞAĞIDAKİ KODDA HATA VAR MI ? YOK

	stack<string> name_stack;

	string s;

	for(int i = 0; i < 10; ++i)
	{
		s = rname();
		cout << s << " yigina push ediliyor\n";
		name_stack.push(move(s)); // BURADA HATA OLUŞUR MU ? HAYIR
	}

	// S MOVED FROM STATE TE AMA TEKRAR ATAMA YAPILDIĞI IÇIN BIR TANIMSIZ DAVRANIŞ YOK
	// Moved from state teki bir nesne geçerli bir nesnedir kullanılabilir ama değerinin ne olduğu konusunda bir öngörüde bulunamayız.
	// Moved from state destructible dır yani destroy olabilir.
	// Valid state tedir.

	std::cout << "size = " << name_stack.size() << "\n"; //size

	while(!name_stack.empty()){ // empty
		cout << name_stack.top() << " Yigindan cikartiliyor\n"; // top ilk öğeye referans yoluyla eriştirir.
		name_stack.pop();  // ilk öğeyi çıkartır.
	}

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Stack sınıfı implementasyonu ile ilgili bir ödev verdi hoca
	nasıl yapılacağını açıklıyor ?????? 1:22

}

NOT : STACK BOŞ İKEN ELEMAN SİLMEK VEYA ERİŞMEK UNDEFINED BEHAVIOR !!!!!

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖZEL CTOR

int main()
{
	std::deque dx{1,4,7,2,4,8}; // NEDEN GEÇERLİ ? CTAD C++17
	std::stack mystack(dx); // GEÇERLİ. Stack<int> in bir Ctoru aynı zamanda deque<int>. Dolayısıyla elimizde deque varsa ondaki öğeleri alıp doğrudan stack başlatılabilir.
	stack<int,vector<int>> x{y}; //BURASIDA GEÇERLİ. CTAD KULLANMADIM SADECE

	while(!mystack.empty())
	{
		std::cout << mystack.top() << "\n";
		mystack.pop();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PEKİ ELİMİZDE VECTOR OLSAYDI

int main()
{
	std::vector dx{1,4,7,2,4,8}; // NEDEN GEÇERLİ ? CTAD C++17
	std::stack mystack(dx); // GEÇERLİ. DEMEKKİ BÖYLE BİR CTOR VAR.

	while(!mystack.empty())
	{
		std::cout << mystack.top() << "\n";
		mystack.pop();
	}
}

ÖDEV: 1:33, 1:37  deki forward listten eleman silmeyi yaz. ilgili derse ekle. 
EKLENDİ !!!


MOLA

==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================

QUEUE CONTAINER ADAPTER
-----------------------
Header file queue
hem queue hemde priority_queue aynı header file içinde.Yine bir template stack gibi.

queue<int> demek aslında bu anlamda ----->	 queue<int,deque<int>>

İlk giren ilk çıkıyor.

Default container yine deque protected veri elemanı C ismiyle temsil edilmiş yani kalıtım yoluyla yeni bir sınıf elde edip bu C yi kullanabiliriz.
Interface stack e benzemekle birlikte ufak farklılıklar var.Bunlara bakacağız. Default container yine aynı, sınıfın protected elemanı yine C ile belirtilmiş.
ödevde yer alıyor protected olayı.Ayrıca bakacağım.



int main()
{
	using namespace std;

	queue<string> x;

	x. //interface e baktık.FRONT VE BACK VAR. STACK TE TOP VARDI.

	for(int i = 0 ; i < 10; ++i)
	{
		auto s = rname();
		std::cout << s << " kuyruga giriyor\n";
		x.push(move(s));
	}

	std::cout << "kuyrukta " << x.size() << " kisi var\n";
	std::cout << "kuyrugun basinda " << x.front() << " var\n";
	std::cout << "kuyrugun sonunda " << x.back() << " var\n";

	while(!x.empty()){
		std::cout << x.front() << " kuyruktan cikiyor\n";
		x.pop();
	}

}

ÇIKTIYI YAZ.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	queue<string,vector<string>> x; //BUNU YAPINCA SENTAKS HATASI OLDU ÇÜNKÜ POP FRONT FUNCTIONI, VECTORDE YOK
								  // ARKA TARAFTAKİ FUNCLAR POPFRONT KULLANIYOR.
	x. //interface e baktık.

	for(int i = 0 ; i < 10; ++i)
	{
		auto s = rname();
		std::cout << s << " kuyruga giriyor\n";
		x.push(move(s));
	}

	std::cout << "kuyrukta " << x.size() << " kisi var\n";
	std::cout << "kuyrugun basinda " << x.front() << " var\n";
	std::cout << "kuyrugun sonunda " << x.back() << " var\n";

	while(!x.empty()){
		std::cout << x.front() << " kuyruktan cikiyor\n";
		x.pop();
	}

}

==================================================================================================================================================================================================
==================================================================================================================================================================================================

PRIORITY QUEUE CONTAINER ADAPTER
---------------------------------
Bunu anlamak için heap bilinmeli.Hoca resimler gösterdi.1:55

HEAP
----
Heap bir ağaç fakat bu ağacın önemli bir özelliği var. Bir ağacın heap olabilmesi için
1 - Complete olmalı, eksiklik varsa son kademede eksiklik olmalı.Şekinden hatırla yada videoya bak.
2 - Sıralama kriterine göre her ağacın tepe düğümü kendi ağacının en büyük yada ek küçük değeri olacak.maxheap minheap 1:56

Heapten en büyük değeri (max heap olduğunda) eleman çıkarmak için logaritmik karmaşıklıkta bir algoritma kullanabiliyoruz.
Çıkarılacak eleman ilk önce başka bir tanesi ile swap ediyor sonra, çıkartılacak eleman çıkartılıyor, daha sonrada swap edilen diğer eleman olması gereken yere gidiyor.

Heap olan bir veri yapısını vectorel bir veri yapısı şeklinde tutabiliriz.Bir ağaç kurmak gerekmiyor.
Herhangibir veri yapısını heap hale getiren algoritmaya make heap deniyor. STL de bu algoritma var.


#include <algorithm>

int main()
{
	vector<int>ivec;
	rfill(ivec,16,Irand(0,5000));
	print(ivec);

	//bir algoritma ile bunu heap haline getireceğiz
	make_heap(ivec.begin(),ivec.end()); // default overload less functor.Verileri alıp heap hale getirdi.
	print(ivec);

	cout << "max = " << ivec.front() << "\n";
	pop_heap(ivec.begin(),ivec.end()); // POP_HEAP POP EDİLECEK ÖĞEYİ SONA GETİRİYOR.
	ivec.pop_back(); // SONA GETİRİLEN ÖĞE POP_BACK İLE SİLİNİYOR.
	print(ivec);
}					

2:02
Çıktı
-----
4999 3007 4319 2466 2508 3299  4212 1423 1983 1574 1019 1917 2350 726 224 1068

							AÇILMIŞ HALİ

							  4999		
					3007				4319
				 2466    2508		3299	4212
			 1423 1574 1574 1019  1917 2350 726 224
			1068


Heap haline getirmenin karmaşıklığı O(n)
Peki heap haline getirdikten sonra neler yapabiliriz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HEAP E YENİ ELEMAN EKLEMEK/SİLMEK

Heap e bir eleman ekleyerek heap olma özelliğini koruyabiliriz ve heapteki en büyük öğeyi heapten çıkarabiliriz.
En büyük öğeyi heapten çıkarmak için ne yapmak gerekiyor ona bakalım.Bu zaten vectordeki ilk öğe(en büyük öğe). Biz bunu vectorden çıkarırsak,

int main()
{
	vector<int>ivec;
	rfill(ivec,16,Irand(0,5000));
	print(ivec);
	make_heap(ivec.begin(),ivec.end()); // default overload less functor
	print(ivec);

	--------------------------------------------------------------------------------------------------------------------------------------------------------
	// SİLDİK

	cout << "max = " << ivec.front() << "\n"; //vectordeki ilk öğe en büyüğü
	
	//tekrar heap olma özelliğini korumak için bu seferde pop heap çalıştırılıyor. Pop heap aynı zamanda çıkarılacak elemanı en sona taşıyor 
	// buradan da vectorun pop_back func ı ile siliyoruz. Aynı zamanda elemanı sona taşırken heap olma yapısınıda koruyor.

	pop_heap(ivec.begin(),ivec.end());
	ivec.pop_back();
	print(ivec);
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------

	//EKLEDİK

	ivec.push_back(9777);
	push_heap(ivec.begin(), ivec.end()); // Heap olma özelliğinin bozulmadığı görülüyor.
	print(ivec);
	
	sort_heap(ivec.begin(),ivec.end()); // Veri yapısını heap hale getirip ondan sonra heap i sıralı hale getiriyor.Küçükten büyüğe sıraladık.N x LogN karmaşıklığında
	print(ivec);

}

Push heap, pop heap, make heap ile heapten eleman çıkartıp ekleme işlemlerini heap olma özelliğini bozmadan yapabiliriz.

Heap sort algoritmasıda böyle yapıyor veri yapısını heap ile getirip sort algoritması çalıştırıyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖNCELIK KUYRUĞUYLA ALAKASI

Öncelik kuyruğu kuyruktan çıkacak ilk öğenin en büyük öğe olması. Mesela tamsayıların büyüklüğüne göre heap oluşturursak kuyruktan bir öğe çıkınca en büyük tamsayı çıkar.
Sonra geriye kalanların en büyüğü. sonra yine geriye kalanların en büyüğü ......


int main()
{
	vector<int>ivec;

	rfill(ivec,10,Irand(0,10000));
	print(ivec);

	make_heap(ivec.begin(), ivec.end()); // İvec bir Heap haline getirdik.Default olarak less kullanılıyor. greaterda kullanabiliriz.

	while(!ivec.empty())
	{
		pop_heap(ivec.begin(),ivec.end()); // Çıkartılacak öğeyi heap olma özelliğini bozmadan sona getirdi.
		cout << "onceligi en yuksek olan " << ivec.back() << " kuyruktan cikiyor\n";
		ivec.pop_back(); // sona getirilen öğe silindi.
		getchar();
	}
}


O(n) karmaşıklığında algoritma ile heap hale getirip, O x Logn karmaşıklığında algoritma ile önceliği en düşük yada en yüksek olanı kuyruktan çıkarıyoruz.

Random access veren herhangibir containerı make heep push heap pop heap sort heap ile maniplue edebiliriz. Doğrudan priority queue ile temiz bir interface tede yapabiliriz.

==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================

PRIORITY_QUEUE CONTAINER ADAPTER
--------------------------------
queue header file içinde. 

Template 
--------
priority_queue<T, std::vector<T>, std::greater<T>>	halinde

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	priority_queue<int,vector<int>,less<int>>; 
	// birinci temp tür parametre öğe türü
	// ikincisi kullanılacak container türü. default vector.
	// Üçüncüsü ise Karşılaştırma kriteri
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Alias template kullnımı örnerilir.
template<typename T>
using minque = std::priority_queue<T, std::vector<T>, std::greater<T>>;

minque<int> x; yazabiliriz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÜYE FONKSİYONLARI
-----------------

int main()
{
	priority_queue<int> x;

	for(int i = 0 ; i < 10; ++i)
	{
		x.push(Irand(0,10000)());
	}
	
	while(!x.empty())
	{
		cout << x.top() << " kuyruktan cikiyor\n"; // baştaki öğeyi gösteriyor.
		x.pop(); // Pop diyince baştan çıkarıyor.
		getchar();
	}
}


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAX ILE MIN FARKI

int main()
{
	priority_queue<Date,vector<Date>,greater<Date>> x; // DİKKAT!!!

	for(int i = 0 ; i < 10; ++i)
	{
		x.push(Date::random());
	}

	while(!x.empty())
	{
		cout << x.top() << " kuyruktan cikiyor\n";
		x.pop();
		getchar();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KABACA IMPLEMENTASYON BU OLABILIR.

template<typename T, typename C = std::vector<T>, typename comp = std::greater<T>>
class PriorityQueue
{
public:
	void push(T &tval)
	{
		c.push_back(tval);
		push_heap(c.begin(), c.end());
	}

	T& top()
	{
		return c.front();
	}

	void pop()
	{
		pop_heap(c.begin(), c.end());
		c.pop_back();
	}

private:
	C c;

};


BU SINIFLARIN NASIL İMPLEMENTE EDİLDİĞİNE BAKACAĞIZ.BİZDE İMPLEMENTE EDECEĞİZ.
CONTAİNER ADAPTER BİTTİ. MOLA

==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================

REFERENCE WRAPPER
-----------------

Referans bir nesnenin yerine geçen bir isim. C++ ta bir çok yerde kullanılıyor. C++ ta reference lar rebindable değil.x i tutuyordum artık y yi tutuyordum durumu yok.
Bir çok programlama dilinde rebindable reference kavramı var. Mesela Pythonda var. Pointerları ise yeniden rebind edebiliyoruz.Bu konuda sorun yok.

Diğer dezavantajda containerlarda tutamıyor olmamız.

int main()
{
	vector<int&> ivec; //SENTAKS HATASI. Containerda referans tutulamıyor.
}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REFERENCE WRAPPER bir pointer sarmalıyor, fakat interface i ile sarmaladığı pointer üzerinden rebindable referans yapısı oluşturuyor.

Basit olarak implemente ettik.bunların yazılmışı var tabi.

template <typename T>
class ReferenceWrapper{
public:
	ReferenceWrapper(T &r) : mptr{&r} { }
	ReferenceWrapper operator=(T&r)
	{
		mptr = &r;
		return *this;
	}

	operator T&() //aşağıdaki r + 5 işlemini yapabilmek için type casting operator func yazdık.
	{
		return *mptr;
	}

	T& get()
	{
		return *mptr;
	}

private:
	T* mptr;
};

int main()
{
	int x = 20;
	int y = 45;
	ReferenceWrapper<int> r = x;

	r = y;

	int ival = r + 5;
	std::cout << "ival = " << ival;
}

Biz bu kodları yazmayacağız çünkü yazılmışı var.Functional header file içinde var.ÇOK ÇOK ÖNEMİ BİR SINIF.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR BAŞKA YOLU

template<typename T>
ReferenceWrapper<T> Ref(T& t)
{
	return ReferenceWrapper<T>{t};
}

int main()
{
	int x = 20;
	int y = 45;

	Ref(x); // Artık bu ifade ReferenceWrapper türünden ifade olacak.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ORIGINALINI GORELIM
-------------------

#include <functional>

int main()
{
	using namespace std;
	int x = 10;
	int y = 20;

	reference_wrapper<int> r = x;

	++r;
	std::cout << "x = " << x << "\n";
	r.get() = 99;
	std::cout << "x = " << r << "\n";

	r = y; // Burada r yi artık y ye bağladık.
	std::cout << "r = " << r << "\n";
	
	++r;
	std::cout << "y = " << y << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CALL BY VALUE

template <typename T>
void func(T x)
{
	++x;
}

int main()
{
	int ival = 10;

	func(ival);

	std::cout << "ival = " << ival << "\n"; // call by value olduğundan değişmez
}

PEKI BUNU CALL BY REFERENCE HALINE GETIREBILIR MIYIZ? EVET.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CALL BY REFERENCE

int main()
{
	int ival = 10;

	func<int &>(ival); // şimdi call by reference

	std::cout << "ival = " << ival << "\n"; // değişti.
}

Bunu yapmamın bir yolu daha var.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REF FUNCTIONAL HEADER FILE İÇİNDE

template <typename T>
void func(T x)
{
	std::cout << typeid(T).name() << "\n";
	++x;
}

int main()
{
	int ival = 10;

	func(ref(ival)); // şimdi call by reference.ref(ival) artık reference_wrapper<int> türünden.

	std::cout << "ival = " << ival << "\n"; // değişti.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Eğer elimizde bir template varsa, func şablonunun func parametresi referans değilse ama biz yinede bu şablondan oluşacak functionun referans semantiği ile bir nesneyi almasını istersek bunu
2 şekilde yaparız

1. Explicit template argüman
2. Reference_wrapper <int> (veya başka bir açılım) türünden bir nesne göndererek.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KÖTÜ KOD ÖRNEĞİ

Diyelimki bir algoitmaya çağrı yapmamız gerekiyor fakat algoritma bizden bir functor/callable istesin.
Mesela generate inceleyelim. 

int main()
{
	vector<int>ivec(1000);
	mt19937 eng;

	generate(ivec.begin(),ivec.end(),eng); // 3. parametre referans değil.
	// burada eng kopyalanır. ve 5000 byte boyutu var.Kopyalama maaliyeti var.
	// bunu kopyalıyoruz şuanda referans semantiği ile tutmalıyız
	//sizeof ile bakılabilir.

	generate(ivec.begin(),ivec.end(),ref(eng)); // Artık kayıp yok !!!!!!!!

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REFERENCE WRAPPER BIR SINIF OLDUĞU IÇIN BIR CONTAINERDA REFERENCE WRAPPER NESNELERINI TUTABILIRIZ

int main()
{
	
	int x = 10, y = 20;

	auto p = make_pair(x,y);

	p.first = 40;
	p.second = 70;

	std::cout << "x = " << x << "\n"; // burada değerler değişmedi
	std::cout << "y = " << y << "\n"; // burada değerler değişmedi
	
	//Neden değişmedi? Burada oluşan pairin <int,int> açılımı
	//Dolayısıyla pairin int& int& açılımı değil.

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int x = 10, y = 20;

	pair<int&,int&>p(x,y); //DİKKAT vector<int&> SENTAKS HATASI ÇÜNKÜ CONTAINERLAR & TUTAMIYOR. AMA PAIRDE SORUN YOK.
	
	p.first = 40;
	p.second = 70;

	std::cout << "y = " << y << "\n";
	std::cout << "x = " << x << "\n"; // DEĞİŞTİ.

	//Değişti çünkü int&,int& açılımı.
	
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int x = 10, y = 20;

	auto p = make_pair(ref(x),ref(y));

	p.first = 40;
	p.second = 70;

	std::cout << "y = " << y << "\n";
	std::cout << "x = " << x << "\n"; // DEĞİŞTİ.

	// Değişti çünkü make paire gönderdiğim argümanlar reference wrapper nesneler.
	// make_pair bu referansın yerine geçtiği nesneleri kullanmış olacak.
	// Böylece return değeri pairin int&,int&  açılımı olacak.
	
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÇOK GÜZEL ÖRNEK

#include <list>

int main()
{
	list<int> mylist{10,20,30,40,50,60};

	vector<reference_wrapper<int>> myvec{mylist.begin(), mylist.end()};

	for(auto &x : myvec)
	{
		++x;
	}

	for(auto x : mylist) // Vectordeki elemanlar listedeki elemanlara referans olduğundan aslında listedeki elemanlar değişti.
	{
		std::cout << x << " ";
	}
}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SHUFFLE

Listedeki öğelere dokunmadan random olarak sırasını değiştirmek istesek shuffle algoritmasını list üzerinde kullanamam çünkü random access iterator istiyor.
Shuffle ı vector üzerinde kullanabiliriz.

int main()
{
	list<int> mylist{10,20,30,40,50,60};

	vector<reference_wrapper<int>> myvec{mylist.begin(), mylist.end()};

	shuffle(myvec.begin(),myvec.end(), mt19937);

	for(auto x : myvec)
	{
		cout << x<< " ";
	}

	cout << "\n";
	
	for(auto x : mylist)
	{
		cout << x<< " ";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REFERENCE WRAPPER SAĞ TARAF DEĞERINE BAĞLANAMAZ

const herşeye bağlanıyor diyip kod yazamayız.

reference_wrapper<int>&r = 10; SENTAKS HATASI.

İlave bir maliyette yok reference wrapperda.Bir referans wrapper kullanmakla pointer kullanmak arasında bir fark maliyet açısından pek yok.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REFERENCE WRAPPER CTAD DAN FAYDALANIYOR.

int main()
{
	int x = 29;

	reference_wrapper r = x; //CTAD. Reference wrapper ın int açılımı olduğunu anlıyor.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REFERENCE WRAPPER FUNCTIONU DA REFERENCE WRAPPERA BAĞLAYABİLİRİZ.

int foo(int x)
{
	return 5 * x + 10;
}

int bar(int x)
{
	return 3 * x - 4;
}

int main()
{
	reference_wrapper<int(int)> r = foo;

	//reference_wrapper r = foo; // BUDA KULLANILABİLİR. CTAD ile.
	
	cout << r(100) << "\n"; // 510

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	r = bar;
	cout << r(100) << "\n"; // 296
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	list<string> mylist;
	rfill(mylist,20,rname);

	vector<reference_wrapper<string>> myvec(mylist.begin(), mylist.end());

	for(auto &name : mylist)
	{
		name += "can";		
	}

	for(const auto &name : mylist)
	{
		std::cout << name << " ";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int x = 10;
	
	auto t = ref(x);
	auto y = cref(x); // reference_wrapper<const int> olanı bu.

	cout << typeid(y).name() << "\n";

	y.get() = 10; //sentaks hatası oluşturacak.

}

==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================
==================================================================================================================================================================================================

STD::FUNCTION
-------------

Bu aslında bir sınıf. std::function olmasına bakma :D
Bu bir class template. Function template değil.

Öyle bir sınıf şablonu ki, belirli bir parametrik yapıdaki tüm callable ları sarmalıyor.
Önemli bir sınıf.


int foo(int x)
{
	std::cout << "foo islevi cagrildi\n";
	return 3 * x + 23;
}

int main()
{
	std::function<int(int)> f(foo); // f kimi sarmalamışsa aşağıda o çağrılır.Bu function derken herhangibir callable olabilir
	
	//

	cout << f(100)<< "\n";

	--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::function<int(int)> f([](int val){ return val * val;}); // lambda olabilir.

	cout << f(100)<< "\n"; // 10000

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Functor{
	int operator()(int x)const
	{
		return x * x * x;
	}
};

int main()
{
	std::function<int(int)> f(Functor);

	cout << f(100); // 1000000
}

BU NE IŞE YARAR ? NEDEN KULLANALIM ?

Birdahaki derste göreceğiz farklı nedenleri var. Örneğin C den callback gibi.


*/
