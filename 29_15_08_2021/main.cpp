/*

EN SON STL E BAŞLADIK.

Standart kütüphanemizin %95 ini belkide stl oluşturuyor.
Nesne yönelimli değil, generic bir kütüphane.Kalıtım var type traitste gördüğümüz gibi ama runtime polymorphism yok.
Yani static bir polymorphism kullanılıyor.Dezavantajı hata mesajlarının açık olmaması.100-150 satır en basit hatada görülebilir.

Container iterator ve algoritmalar en önemli 3 üyesi.

CONTAINER: Veri yapılarını implemente eden sınıf şablonlarına deniyor. Ör: vector dinamik dizi veri yapısını implemente ediyor.

ITERATOR : Pointer benzeri arayüze sahip.Nesneleri pointer gibi kullanılabilen sınıf şablonları.
		   Amacı : Containerda bulunan öğelerin konumlarını tutan sınıflar.Adreste bir konumdur.Raw pointer da bir iterator olarak kullanılabilir.
		   Containerda bulunan öğelere erişmek için kulanılıyor.

ALGORITMA : Algoritmaları implemente eden fonk şablonları. sort, find, reverse ...
			Containerda bulunan veriler üzerinde birtakım işlemler yapılması gerekiyor. Bunların yapılması için algoritma denen functionları çağırıyoruz.
		    Algoritmalarla containerları birbirine bağlıyan ise iterator.
			Algoritmalar iteratorleri kullanarak containerlar üzerinde birtakım işlemler yapan functionlar.

BUNLARIN HEPSI TEMPLATE.

Başka öğelerde var
CONTAINER ADAPTERS, ITERATOR ADAPTERS, FUNCTION ADAPTERS, FUNCTION OBJECTS

STL aynı zamanda extendable bir yapıya sahip. kendimiz yeni algoritmalar oluşturabiliriz.Varolan container veya iteratörleri kullanarak bunları yapabiliriz.
Yeni iterator, container sınıfları oluşturabiliriz. ÖR: Boostta stl de olmayan birsürü container ve iterator sınıfı aynı zamanda algoritma şablonları var

STL Modern C++ tan çok büyük destek aldı.Eski STL ve Yeni STL de baya farklı. Kodlar daha verimli hale geldi ve yeni öğeler geldi.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------

SEQUENCE CONTAINERS
-------------------
Ekleme silme işlemleri konumla yapılıyor.İstediğim konuma istediğim öğeyi ekleyebiliyorum.

std::vector			-> En çok kullnılan STL container
std::deque			-> double ended queue. Baştan ve sondan ekleme yapabileceğimiz veri yapısı
std::list			-> doubly linked list
std::forward_list	-> (C++ 11 de geldi)  singly linled list
std::string			-> Yazı tutuyor.Gördük bunu.Bu da containers.Bunu daha çok STL algoritmalarıyla kullanacağız.
std::array			-> (C++ 11 de geldi) array container



ASSOCIATIVE CONTAINERS
----------------------
İkili arama ağacı
Ekleme işlemi belirli bir konum değil değerle yapılıyor.
İkili arama ağacı veri yapısı kullanılıyor. Değerin ne olduğuna bağlı olarak ekleneceği yer belirleniyor.

std::set		-> Sadece anahtar tutuyor.Tamsayıların setini oluşturursak 17 nin sette olup olmadığını sorgulayabiliriz.Bir anahtardan bir tane var.
std::multiset	-> Bir anahtardan birden fazla olabilir.Tamsayıların setinde 1 tane 12 olabilir.multisetinde 3,4,5,6 tane 12 olabilir.
std::map		-> Anahtarın değerle eşlendiği veri yapısı.Anahtarla erişiyoruz yine ama anahtar karşılığı bir değere erişiyoruz.Buradakiler pair gibi anahtar değer çifti
std::multimap	-> Bir anahtardan birden fazla olabilir.



UNORDERED ASSOCIATIVE CONTAINERS
--------------------------------
Diğer dillerdeki adı hash tablosu denen veri yapısını implemente eden sınıflar.
Neden diğer dillerden farklı olarak böyle tuhaf isimler almışlar.Görece olarak geç dile eklenmesi.
Dİğer diller eklemişti bunu kendisine ama C++ bu isim seçilseydi geçmişte yazılan kodlarda sentaks hataları oluşabilirdi.

std::unordered_set			-> (C++ 11 de geldi) Sadece anahtar tutuyor.Bir anahtardan bir tane var.
std::unordered_multiset		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.
std::unordered_map			-> (C++ 11 de geldi) Anahtarın değerle eşlendiği veri yapısı.Buradakiler pair gibi anahtar değer çifti
std::unordered_multimap		-> (C++ 11 de geldi) Bir anahtardan birden fazla olabilir.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------

stack queue priority_queue tabiki var ama bunlar kesinlikle container değil.
Böyle veri yapılarına Abstract Data Type (ADT).Implementasyondan bağımsız bir interface sözkonusu.

Bunlar STL de containerları eleman olarak (composition ilişkisi ile) aldığı containerın interface ini bu soyut veriyapısına adapte eden yardımcı sınıflar.

Başlangıç noktamız iteratorler olacak. Nedir neden kullanılır algoritmalar arasındaki ilişki, sonada contailerlarla arasındaki ilişki olarak devam edecek...

İteratorler söz konusu olunca anlamamız gereken kavram range/aralık
range-base for loop kavramıda vardı hatta.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------


RANGE
-----
İki konumun oluşturduğu birim.Pointerda olabilir iterator denen varlıklar da olabilir.
Bunun range olması için aşağıdaki koşul sağlanmalı.

Birinci konumu tutan konumu artırdığımda bir süre sonra ikinci konuma eşitlenmeli.
[konum1		konum2)
p1			p2

Range boşta olabilir veya içinde öğeler tutulabilir. Range bir containerın range i.Yani herzaman bir containerla ilişkili.
Range sözkonusu olduğunda konum1 dahil ama konum2 dahil değil.
[konum1,konum2)

Burada P1 i kaç kere artırıyorsam, p1-p2 range inde o kadar öğe var demek.Range kavramı önemli çünkü STL deki algoritmalar buna göre yazılıyor.
Tipik bir algoritmada range parametreleri var.Range olması için minimum 2 parametre olmalı

template <typename Iter>  //Burası bir func şablonu
void display_elements(Iter beg, Iter end)
{
	while(beg!=end)
	{
		std::cout << *beg << "\n";
		++beg;
	}
	std::cout << '\n';
}

Burada != ++ * operatorlerinin overload edilmiş olması gerekiyor.

-------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunu yazsaydık elemanları yazdıracaktı. * lara dikkat

template <typename Iter>
void display_elements(Iter *beg, Iter *end) // * lar eklendi.
{
	while(beg!=end)
	{
		std::cout << *beg << "\n";
		++beg;
	}
	std::cout << '\n';
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	display_elems(a,a+10); // a + 10 dizinin bittiği yerin adresi.
	display_elems(a+4,a+7); // 5 6 7 yi yazdırır.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------

double a[10] = {1,2,3,4,5,6,7,8,9,10};
display_elems(a+4,a+7); bu seferde double dizinin elemanları çağrılacak 

-------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Iter>  //Burası bir func şablonu
void display_elements(Iter beg, Iter end)
{
	while(beg!=end)
	{
		std::cout << *beg << "\n";
		++beg;
	}
	std::cout << '\n';
}

int main()
{
	using namespace std;
	vector<string> svec{"dogus","necati","ayse","gizem","can","umut"};

	display_elems(svec.begin(), svec.end()); //yazdırılır.
}

------------------------------------------------------------------------------------------
Yukarıdaki func template burada da tanımlı

int main()
{
	using namespace std;
	list<bitset<16>>mylist{76,12,32,42,52};

	display_elems(mylist.begin(), mylist.end()); //Bitwise olarak yazdı
}

1 template ile Her seferinde farklı şeyler yazdırdık.Herşey şablon
list bitset display_elems hepsi template

Dizi için nasıl çalıştığı açıklandı.Pointer oldu iter ... ptr aritmetiği

------------------------------------------------------------------------------------------

ITER VECTOR İÇİN NASIL ÇALIŞIYOR

Vector aşağıdaki gibi bir container

namespace std{

	template <typename T> // allocator parametrede var aslında
	class Vector{
	public:
		//bunun iterator gibi nesned typeları var
		class iterator{
		public:
			operator*
			operator++
		};
		iterator begin(); //konumları tutuyorlar. ilk öğenin konumunu tutuyor
		iterator end();	// bu son öğeden bir sonraki konumu döndürüyor.
	};
}

vector<int>::iterator diye kullanacağım

int main()
{
	using namespace std;
	vector<int>ivec{1,2,4,6,7,8};
	
	vector<int>::iterator it =  ivec.begin(); // auto burada fayda sağlar.Bundan uzunlarıda var.

	while(it != ivec.end()){
		cout << *it << " ";
		++it;
	}

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA DA LIST KULLANALIM.YANİ BAĞLI LİSTEYİ DOLAŞIYORUZ

int main()
{
	using namespace std;
	list<int>ilist{1,2,4,6,7,8};

	auto it = ilist.begin();

	while(it != ilist.end()){
		cout << *it << " ";
		++it;
	}

}

Listte operatorler overload edilmiş. Listte iterator nested type var, * ++ funcları var. begin ve end funcları var.
Bu kodlar vectörün kodlarıyla birebir aynı değil.Biri bağlı liste diğeri vector yani elemanlar ardışık contigues

-------------------------------------------------------------------------------------------------------------------------------------------------------------

Iter bir iterator türü ise tüm iteratorlerin != ile karşılaşltırılabileceğine, * operandı olabileceğine ve ++ operandı olabileceğine güvenerek 
böyle bir şablon yazarsam, bu koşulları sağlayan iterator türleri için bu function bu range deki öğeleri yazdıran bir function.
std::cout << *beg; yazılmış birde buradaki inserterında çalışıyor olması gerekiyor

Önce algoritmaların iteratör ile ilişkisini kavramamız gerekecek.

-------------------------------------------------------------------------------------------------------------------------------------------------------------

LINEER ARAMA ALGORITMASI

Bulursa konum bulduğunun konumunu, bulamazsa end konumu

template <typename Iter, typename T>
Iter Find(Iter beg, Iter end, const T &val) // sonuncu aranacak değer. Eğer bulursa konumu
{											// bulamazsa end konumunu döndürüyor.
	while(beg != end)
	{
		if(*beg == val)
			return beg;
		++beg;
	}
	return end;
}

Algoritmanın gücü : Birkaç satırlık func şablonu bu.Bu şablondan yazılacak function, bir int dizide int te arayabilir
					bir bağlı listede tarihte arayabilir, oyun programındaki fighter sınıf türünden nesneler tutan dizide 
					bir fighterda arayabilir.Derleyici bu template ten kodu gönderdiğimiz türe göre yazacak.
					

int main()
{
	using namespace std;
	vector<string>svec {"ali","can","deniz","murat","hakan","ayse"};
	
	string name= "hakan";

	if(auto iter = Find(svec.begin(), svec.end(), name); iter != svec.end()) // end değilse öğeyi bulmuştur.
	{
		std::cout << "bulundu ... "<< *iter << "\n"; // bulduysa değer yazılacak.
	}
	else
	{
		std::cout << "Bulunamadi\n";
	}
}

ÇIKTI
-----
bulundu ... hakan

Bu tempalte i neye göre yazdık, iteratorler karşılaştırılabilir (!=), dereference in operandı olabilirler (*), artırılabilirler ++
Buradaki Iter sınıfları farklı sınıflar olabilir ve bunlar bu işlemleri farklı şekilde kodlamış olabilirler.


-------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKI BILGILERE GÖRE BURADA TÜR OLARAK LIST KULLANSAK YINE ÇALIŞACAK

Template tanımlı varsay

int main()
{
	using namespace std;
	list<string>svec {"ali","can","deniz","murat","hakan","ayse"}; // dikkat vector değil list.

	string name= "hakan";

	if(auto iter = Find(svec.begin(), svec.end(), name); iter != svec.end()) // end değilse öğeyi bulmuştur.
	{
		std::cout << "bulundu ... "<< *iter << "\n"; // bulduysa değer yazılacak.
	}
	else
	{
		std::cout << "Bulunamadi\n";
	}
}

ÇIKTI
-----
bulundu ... hakan

-------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR CONTAINER BOŞ OLABILIR.

size=0 demek, empty si true demek.
Containerlarında ortak olarak isimlendirilmiş member funclarıda var.1 tanesi hariç hepsinin size member func ı var.
string te bir container onunda size ı var.length var

Modern C++ ta bunların bir kısmı global

int main()
{
	using namespace std;
	list<string>slist{"ali","can","deniz","murat","hakan","ayse"};

	auto iter = list.begin(); //C++ 11 e kadar tek yol buydu ilk öğeyi elde etmek için

	Modern C++ ile globalleride eklendi
	auto iter = begin(slist); //adl sayesinde nitelemeden kullanıyrum

}

--------------------------------------------------------------------------------------------------------------------------------------------

BU ÇOK İYİ BİR ADL ÖRNEĞİ

int main()
{
	std::vector<std::string>svec{"ali","veli","hasan","huseyin","mehmet"};

	sort(begin(svec),end(svec)); // nitelenmedi ama ADL sayesinde kullanılabilir.

}

AÇIKLAMASI ÇOK ÖNEMLİ
---------------------
begin end ve sort std namespace inde olmasına rağmen, nitelemeyince bir sentaks hatası olmamasının sebebi ADL.
1 - svec, std namespace i içinde tanımlanan bir türden olduğu için begin de std namespace inde arandı
2 - begin in geri dönüş değeri vector<string>::iterator türünden.Yani yine std namespace ine ilişkin bir tür var.
3 - Bu durumda sort ta std namespaceinde aranır.


--------------------------------------------------------------------------------------------------------------------------------------------

BIR CONTAINER BOŞ OLABILIR.TEKRAR :D

Boş container için begin ve end funcları çağrılabilir.

int main()
{
	std::vector<std::string> svec{};

	auto iter_beg = svec.begin(); //Geçerli
	auto iter_end = svec.end();	 //Geçerli	

	std::cout << *iter_beg << "\n"; //UNDEFINED BEHAVIOR.ÇÜNKÜ BOŞ CONTAINER. DOLU OLSAYDI GEÇERLİYDİ.

	std::cout << *iter_end << "\n"; //UNDEFINED BEHAVIOR.HER DURUMDA BÖYLE.
	
}

Bir iterator eğer begin functan alınmışsa ve sözkonusu container boş ise geçerli bir iteratördür, bazı işlemlerde kullanılabilir
ama dereference edilmesi UNDEFINED BEHAVIOR.Exception handling yok.

Neden exception throw etmiyor?
Çünkü STL in felsefesi ile alakalı.Çünkü verim odaklı.
Herşey verim. C de yazılmış bir veri yapısı kodu veya algoritma kodu ne kadar verimliyse bu da o kadar verimli hatta
bazı durumlarda optimization ile basic C kodundan daha verimli.

--------------------------------------------------------------------------------------------------------------------------------------------

KURAL 1 : BOŞ OLAN BIR CONTAINERIN BEGIN FUNCINDAN ALDIĞIMIZ ITERATÖRÜ ASLA DEREFERENCE ETMEMELIYIZ.UNDEFINED BEHAVIORDUR BU.
KURAL 2 : END BOŞTA OLSA DOLUDA OLSA DEREFERENCE ETMEMELIYIZ. UNDEFINED BEHAVIOR

--------------------------------------------------------------------------------------------------------------------------------------------

BOŞ VECTORÜ FIND ALGORITMASINA GÖNDERINCE UB OLUŞMUYOR

int main()
{
	vector<string> svec; // boş bir vector
	string name{"ali"};

	Find(svec.begin(),svec.end(),name); // UB YOK.Sadece değer bulunamaz.

	std::cout << boolalpha << (svec.begin()) == svec.end());
}

ÇOK ÖNEMLİ !!!!!!!!!!!

BOŞ BIR CONTAINER RANGEINI ALGORITMALARA GÖNDEREBILIRIZ.
BOŞ VECTORUN BEGIN END RANGE I GEÇERLI BIR RANGE. VECTOR BOŞ ISE BEG VE END DEĞERI 
BIRBIRINE EŞIT DURUMDA BU SEBEPLE FIND IÇINDEKI WHILE DÖNGÜSÜNE GIRMEZ.

---------------------------------------------------------------------------------------

int main()
{
	using namespace std;
	vector<string> vec;
	cout << boolalpha << (svec.begin() == svec.end()); // bu şekilde gösterilebilir.
}
true

---------------------------------------------------------------------------------------

BEGIN VE END IN GLOBAL BIÇIMIDE EKLENDI.

Neden eklendi? Dİzilerinde bu şekilde kullanılabilmesi için

int main()
{
	int a[] = {1,2,3,4,5,6,7};
	print(a,a+sizeof(a)/sizeof(a[0]));	// print i hocanın kendi yazmış.
										// normalde bu şekilde çağrılırdı.

	//Bunu doğrudan yazabiliriz.Specialization yapılmış
	print(begin(a),end(a)); // böyle yapabiliriz.
}
Hocanın 1. tercihi global funclar.bunlar iterator header file içerisinde

---------------------------------------------------------------------------------------

Global funcların sayısıda arttı.
artık size da var.

int a[] = {1,2,3,4};
std::size(a); // a nın boyutunu veriyor.
std::empty(a); //buda yoktu. artık var.
std::data(a); // hepsi aynı şekilde.
....

BURAYA KADAR ITERATOR NEDIR GENEL BIR BILGI ELDE ETTIK.
ŞİMDİ DERINDEN INCELEYECEĞIZ.

==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================

ITERATORS
---------
En önemli özelliği iterator category.


ITERATOR CATEGORY
-----------------
Pointer like bir interface e sahip dolayısı ile bunların sınıf türünden nesneler olması durumunda yine pointer gibi 
kullanılmasını sağlayan operator overloading mekanizması.

*iter;
++iter;
--iter;
iter->foo()

Iteratorlerin interfaceleri birebir aynı değil.
Bir iteratörün hangi işlemlerde kullanılabileceğini belirleyen iteratörün kategorisi.
Bu iteratörün interface inde hangi işlemler var, hangileri yok bunu ölçüsü. Bu kategorilere isimler verilmiş.
Her iteratörün bir kategorisi olmak zorunda.

ÖR: vector, random access denen bir iterator categorisinde. Bu sayede vectörün iteratörü ile neler yapabileceğini bilebiliyorum.
Random access categorisi neler yapabilirse vectorde onları yapabiliyor

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

İTERATÖR KATEGORİLERİ
---------------------
Output iterator
Input iterator
Forward iterator
Bidirectional iterator
Random access iterator

Elimizde bir iterator varsa yukarıdakilerden biri olmak zorunda.
a - Bir iteratorun kategorisini bunlardan hangisi olduğunu nereden anlıyorum ?
b - Ne ifade ediyor bu kategoriler ?

-------------------------------------------------------------------------------------------

Bütün iteratorlerin iterator_category isimli bir nested type ı var.

vector<int>::iterator::iterator_category 
list<int>::iterator::iterator_category 
forward_list<string>::iterator::iterator_category 


Buradaki nested type STL deki tanımlanmış empty classlardan biri.
Nedir bu sınıflar? Aşağıdakiler.1


struct output_iterator_tag
struct input_iterator_tag
struct forward_iterator_tag
struct bidirectional_iterator_tag
struct random_access_iterator_tag


------------------------------------------------------------------------------------------
using type = std::vector<int>::iterator::iterator_category;
int main()
{
	cout << typeid(type).name() << "\n"; //random_access_iterator_tag empty classı burası
}
------------------------------------------------------------------------------------------
using type = std::list<int>::iterator::iterator_category;
int main()
{
	cout << typeid(type).name() << "\n"; //bidirectional_iterator_tag yazacak.
}
------------------------------------------------------------------------------------------
using type = std::forward_list<int>::iterator::iterator_category;
int main()
{
	cout << typeid(type).name() << "\n"; //forward_iterator_tag
}
------------------------------------------------------------------------------------------
using type = std::ostream_iterator<int>::iterator_category; // burada doğrudan ostream_iterator yazdığımız için
int main()													// ::iterator:: gibi bir nesneye erişmeye gerek kalmadı
{
	cout << typeid(type).name() << "\n"; //output iterator tag  ..
}
------------------------------------------------------------------------------------------
using type = std::istream_iterator<int>::iterator_category;
int main()
{
	cout << typeid(type).name() << "\n"; //istream iterator tag  ..
}
---------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------

Her iteratörün bir iterator categorisi var. Bir iteratör sınıfını oluşturan, o oluşturduğu iterator sınıfının iteratör kategorisinide belirlemek zorunda.
STL de de farklı farklı iteratör sınıfları var, vector ün listin ostream in iterator sınıfı gibi. Bunların hepsininde birer iterator kategorisi var.
Bu kategorilerde yukarıda yazan 5 taneden biri olmak zorunda ama iterator kategorisinin ne olduğunu anlamanın yolu, iterator sınıfının iterator category
nested type ının ne olduğuna bakmak.

İTERATÖR KATEGORISI SÖZKONUSU ITERATÖRLERLE NELER YAPABILIRIM NELER YAPAMAM BUNLARI BELIRLIYOR BU YÜZDEN ÇOK ÖNEMLI!!!!!!!!!!

---------------------------------------------------------------------------------------------------------------------------------------------------------------
| ITERATOR KATEGORİLERİ	  			  |						OPERASYONLAR						      |													  |
---------------------------------------------------------------------------------------------------------------------------------------------------------------
|						  |						          |         					      |	
|						  |	Copy constructible				  |	ostream_iterator	    		      |	
|	 OUTPUT ITERATOR	  		  |	++it	it++	=				  |	ostreambuf_iterator   	     		      |
|						  |	*it		it->  (sol taraf değeri)	  |  						      |
|						  |							  |					              |
|-------------------------------------------------|-------------------------------------------------------|---------------------------------------------------|
|						  |	Copy constructible			  	  |						      |
|						  |	++it	it++	=			  	  |	istream_iterator	      		      |
|	  INPUT ITERATOR	  		  |	*it		it->  (sağ taraf değeri)	  |	istreambuf_iterator	      		      |
|						  |	it1 == it2		it1 != it2		  |						      |
|						  |							  |						      |
|-------------------------------------------------|-------------------------------------------------------|---------------------------------------------------|
|						  |	Copy constructible - Default Constructible	  |		 				      |
|						  |	++it	it++	=				  |	forward_list		    		      |
|	FORWARD ITERATOR	  		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	unordered_set		unordered_multiset    |
|						  |	it1 == it2		it1 != it2		  |	unordered_map		unordered_multimap    |
|						  |							  |						      |
|-------------------------------------------------|-------------------------------------------------------|---------------------------------------------------|
|						  |	Copy constructible - Default Constructible	  |						      |
|						  |	++it	it++	--it	it--		=	  |	list					      |
|	  BIDIRECTIONAL		 		  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	set		multiset		      |
|	    ITERATOR		  		  |	it1 == it2		it1 != it2		  |	map		multimap		      |
|						  |							  |						      |
|						  |							  |						      |
|-------------------------------------------------|-------------------------------------------------------|----------------------------------------------------
|						  |	Copy constructible - Default Constructible        |						      |
|						  |	++it	it++		--it	it--	=	  |	vector			      		      |
|						  |	*it    it->  (sağ taraf değeri) (sol taraf değeri)|	deque			      		      |
|	  RANDOM ACCESS		  		  |	it1 == it2		it1 != it2		  |	array			      		      |
|	    ITERATOR		  		  |	it + n		n + it		it - n		  |	string			      		      |
|	(Pointer Interface )  			  |	it+=n		it-=n				  |	C array			      		      |
|						  |	it1 - it2					  |						      |
|						  |	it[n]						  |						      |
|						  |	it1 < it2   it1 <= it2   it1 > it2   it1 >= it2   |						      |
---------------------------------------------------------------------------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------


ÖRNEKLER

int main()
{
	vector<int>ivec{1,2,3,4,5}; // burada pointer işlemleri yapılacak
								// öyle geçiyor.Random access iterator
	auto iter1 = ivec.begin();
	auto iter2 = ivec.end();

	++iter1;
	--iter1;
	--iter1[3];

	iter2 - iter1;
	iter + 2;
}

-----------------------------------------------------------------------------------

int main()
{
	list<int>ilist{1,2,3,4,5}; //Bidirectional
								
	auto iter1 = ilist.begin();
	iter +1 ; //hata
	iter -2 ; //hata
	iter1.end()  - iter2.begin() ; //hata

	auto iter = ilist.end();
	--iter; // BURASI GEÇERLI.

}

-----------------------------------------------------------------------------------

int main()
{
	forward_list<int>ilist{1,2,3,4,5}; // 
								
	auto iter1 = ilist.begin();
	iter +1 ; //hata
	iter -2 ; //hata
	iter1.end()  - iter2.begin() ; //hata

	auto iter = ilist.end();
	--iter; // ŞİMDİ SENTAKS HATASI

}

-----------------------------------------------------------------------------------

int main()
{
	list<int>ilist{1,2,3,4,5}; // 
	
	auto iter = ilist.begin();

	iter = ilist.end();   // assingment örneği verdi.
							// Tabloda yok ama yapıalbiliyor.Hoca ekleyecek

}

-----------------------------------------------------------------------------------

STL IN EN SIK KULLANILAN ALGORITMASININ KODU.

template <typename Iterx, typename Itery>
Itery Copy(Iterx beg, Iterx end, Itery destbeg)
{
	while(beg!= end)
	{
		*destbeg++ = *beg++;
	}
	return destbeg;
}

BURADA ITERX MİNİMUM HANGİ KATEGORİDE OLURSA HATA VERMEZ ?
INPUT ITERATOR.

ITERY MİNİMUM NE OLMALI?
OUTPUT ITERATOR

-----------------------------------------------------------------------------------

Parametre isimleri değiştirildi ki hangi kategoriden olduğu belli olsun.
Okuyan anlasın yani.

template <typename InIter, typename OutIter>
OutIter Copy(InIter beg, InIter end, OutIter destbeg)
{
	while(beg!= end)
	{
		*destbeg++ = *beg++;
	}
	return destbeg;
}

Bu algoritma ile bir bağlı listeden bir dinamik dinamik diziye kopyalama yapılabilir mi?
EVET.
Çünkü bağlı listenin iteratörleri Bidirectional(inputu kapsıyor), Vectorunkide
Random access zaten.

-----------------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main()
{
	vector<int>ivec{1,3,4,8,6};
	sort(ivec.begin(),ivec.end());
}

Burada imleci sort üzerine getirince parametresinin RanIt isimli olduğunu gördük.
Random Access Iterator kısaltması olarak yazmış.

-----------------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main()
{
	list<int>i{1,3,4,8,6};
	sort(i.begin(),i.end()); // SENTAKS HATASI
}

Sort random access iterator kategorisini istiyor.
Bağlı liste ise bidirectional.SENTAKS HATASI
Hata mesajlarıda efsane. Hiçbirşey anlaşılmıyor :D

-----------------------------------------------------------------------------------

template <typename InIter, typename T>
InIter Find(InIter beg, InIter end, const T &val) // sonuncu parametre aranacak değer
{
	while(beg != end)
	{
		if(*beg == val)
			return beg;
		++beg;
	}
	return end;
}

!= , * , ++ kulalnılmış.
iterator kategorisi input iterator

MOLA

====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================


BUNDAN SONRASINDA EPEY KOD YAZILACAĞI IÇIN HOCA KENDI YAZDIĞI NUTILITY YI KULLANACAK
DAHA SONRA BUNLARIN NASIL YAZILDIĞINI BERABER INCELEYECEĞIZ.

biri rfill örnek verelim

int main()
{
	vector<string> svec;
	rfill(svec,100,rname); // 1. container nesnesi, 2. Kaç öğe doldurulacağı 3.containera konulacak öğeler hangi callable dan elde edileceğini yazdık
	print(svec); //ekrana 100 isim yazdırıyor mesela.

	list<int> ilist;
	rfill(ilist,10,Irand{10,20});
	print(ilist);
	
}


-------------------------------------------------------------------------------------------

Bazı STL algoritmaları(copy de olduğu gibi) bir range de yazma işlemi yapıyor. 
En tipik olanı copy algoritması

Burada farklı veri türleri arasında kopyalamalar yapabiiyoruz.
Önemli olan iterator konumundaki nesnelerin birbirine atanması

Yazma algoritmalarının hepsinin ortak özelliği, return değeri en son yazdığı yerden bir sonraki konum.
Öğe yoksa containerın end konumu. Bittiği yer oluyor.

STL agoritmalarının en önemli özelliklerinden biri, yazma range i çoğunlukla başlangıç iteratörü olarak alınıyor.
Yani ilgili konumda yeterince nesne olmasından biz sorumluyuz.Excention throw da etmiyor.

Dİyelim source range de 20 öğe var, destinationda en az 20 öğe olması gerekir.
Eğer 20 öğe yoksa UNDEFINED BEHAVIOR.Geçersiz bir iterator konumuna yazmaya çalışmış oluyoruz çünkü.


template <typename InIter, typename OutIter>
OutIter Copy(InIter beg, InIter end, OutIter destbeg)
{
	while(beg != end)
	{
		*destbeg++ = *beg++;
	}
	return destbeg; //2. template tür parametresine yazıldığı için
}					// en son yazılandan bir sonrasını dönecek ayrıca


-------------------------------------------------------------------------------------------

#include <algorithm>
#include <vector>

int main()
{
	vector<int>ivec;
	rfill(ivec,20,Irand{0,50});
	print(ivec);

	vector<int>vx;
	copy(ivec.begin(),ivec.end(), vx.begin()); //SENTAKS HATASI DEĞİL AMA UNDEFINED BEHAVIOR

	vector<int>vy(20);  
	copy(ivec.begin(),ivec.end(), vy.begin()); //GEÇERLİ. YETERLİ ELEMAN VAR

}

UB OLMAMASI IÇIN VX TE EN AZ 20 ÖĞE OLMALI

------------------------------------------------------------------------------------------------------

ALGORITMALAR ITERATÖRLERE GÖRE YAZILIYOR VE TÜRLERININ AYNI OLMASI BEKLENMIYOR.

#include <vector>
bunları includeet


int main()
{
	vector<int>vx; // DİKKAT vector <int>
	rfill(ivec,20,Irand{0,50});
	print(ivec);

	vector<double>vy(20); // DİKKAT vector<double>

	copy(vx.begin(),vx.end(), vy.begin()); // GEÇERLİ.Türler farklı olsa bile kopyalama gerçekleşir.
	std::cout << "\n";
	print(vx);
}

Atamayı iteratorler yapıyor.Copy algoritmasından hatırla.

------------------------------------------------------------------------------------------------------

ALGORITMALAR ITERATÖRLERE GÖRE YAZILIYOR VE TÜRLERININ AYNI OLMASI BEKLENMIYOR.

#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include "nutility"



int main()
{
	vector<string>svec;
	rfill(svec,10,rname);
	print(svec);

	list<string> slist(10);

	copy(svec.begin(),svec.end(),slist.begin()); //GEÇERLİ. String vectorunden string listesine kopyalama var
	print(slist);

}

------------------------------------------------------------------------------------------------------

ALGORITMALAR ITERATÖRLERE GÖRE YAZILIYOR VE TÜRLERININ AYN I OLMASI BEKLENMIYOR.

#include <vector>

bunları includeet

int main()
{
	vector<const char *>svec{"Ali","Veli","hakan","Huseyin"};
	list<string> slist(10);

	//copy(svec.begin(),svec.end(),slist.begin()); // farklı türler arasında copy

	auto iter = copy(svec.begin(),svec.end(),slist.begin()); // burada iter en son yazma yapılan yerden bir sonraki konum.bittiği yer

	print(slist.begin(), iter); // burada da slist.begin, slist.end() gibi. Range yaptık yani.

}

Copy yi hatırlayalım
*destbeg++ = *beg++

Burada *destbeg bir string
Burada *beg ise const char * türünden

stringe const char * atanabilir. Bu geçerli.Tersi değildi.Stringlerden hatırla


EN İYİ ALIŞTIRMALAR BU ALGORİTMALARIN KODUNU YAZMAKTIR
ZATEN C ALGORİTMALARINA BENZİYOR.SADECE TEMPLATE HALİNE GETİRMEK YETERLİ OLACAK DİYE DÜŞÜNÜYORUM.

cpprefernece tan possible implemetation dan copy ye bakıldı.

------------------------------------------------------------------------------------------------------

class Myclass{ };

int main()
{
	vector<int>ivec(20);
	list<string> ilist(100);
	copy(ivec.begin(),ivec.end(),ilist.begin()); // OK Türler arasında bi uyumsuzluk yok.

	vector<int>ivec(20);
	list<Myclass> ilist(100); //Dikkat
	copy(ivec.begin(),ivec.end(),ilist.begin()); // Compile timeda sentaks hatası

}

Burada Myclass nesnelerine int türden nesneler atanacak. Bu compile timeda sentaks hatası oluşturacak.
Conversion Constructor olmuş olsa sentaks hatası değil çünkü atamayı legal hale getirmiş oluyoruz.

======================================================================================================================================================================
======================================================================================================================================================================
======================================================================================================================================================================
======================================================================================================================================================================


BAZI STL ALGORİTMALARINI BİZ YAZACAĞIZ
--------------------------------------

Bazılarının isminde if sözcüğü geçecek. Bu algoritmalar bir template parametresiyle bir predicate alacaklar ve onun true değer verdiği öğeler üzerinde
o işlemleri yapacaklar.

//count --> Bir range te belirli değerlere sahip öğe sayısını buluyor
//count_if --> Bir range te belirli koşulu sağlayanların sayısını buluyor

//find --> Bir range te değer arıyor.
//find_if --> Bir rangete bir koşulu sağlayan ilk öğenin konumunu buluyor.


----------------------------------------------------------------------------------------------------------------------------------------------------------

FIND LINEAR SEARCH ALGORITMASI
STL deki arama algoritmalarının ortak özelliği return değerlerinin iterator olması.C de arama functionlarının return değeri genelde pointer olur.
String sınıfında index döndürüyordu bulamazsa ise constexpr static olan npos değerini döndürüyor. C ise bulamazsa NULL pointer döndürür.

STL deki arama algoritmaları aranan değerleri bulunamazsa, algoritmaya geçilen range in end konumunu döndürüyor.
Dolayısı ile bir arama algoritmasının aranan değeri bulup bulmadığını sınamak için return değerini bir iterator değişkeninde tutup
bunun algoritmaya gönderilen end konumu olup olmadığına bakacağız.


using namespace std;

template <typename InIter, typename T>
InIter Find(InIter beg, InIter end, const T& t)
{
	while(beg != end){
		if(*beg == t)
			return beg;
		beg++;
	}
	return beg; // burada return end de denebilir.
}

int main()
{
	list<string> slist;
	rfill(slist,20,rname);
	print(slist);

	string name;
	std::cout << "aranacak ismi girin: ";
	cin>>name;

	auto iter = Find(slist.begin(), slist.end(),name); // if with init kullanılmalı aslında
	if(iter != slist.end())
	{
		std::cout << "bulundu..." <<*iter << "\n";
		*iter = "KAYHAN";
		print(slist);
	}
	else
	{
		std::cout "bulunamadi\n";
	}
}

IF WITH INIT EN ÇOK KULLANILAN ARAÇLARDAN BIRI.
if(auto iter = Find(slist.begin(), slist.end(),name); iter != slist.end())
Yukarıda bu olabilirdi.

Find tipik bir arama algoritması. 
Aranan değer bulunursa bu değere sahip öğenin konumunu dönüyor bulamazsa ilgili range in end konumunu döndürüyor.

Stringin tabi kendi funclarıda var.Onlarla da arama yapabilirdik.

=================================================================================================================================================
=================================================================================================================================================
=================================================================================================================================================


FIND_IF ALGORİTMASI
Predicate isteyen algoritmaların tipik örneği.

STL de predicate return değeri bool olan callable lara deniyor. callable demek, functor lambda veya func ptr olabilir.
Eğer bu functionlar 1 parametreli ise unary predicate, İki parametreli ise binary predicate

template<typename InIter, typename Pred>
InIter Find_if(InIter beg, InIter end, Pred f)
{
	while(beg != end){
		if(f(*beg)) // f(*beg) true ise girecek
			return beg;
		++beg;
	}
	return beg;
}

f(*beg) koşulunu sağlayan ilk öğenin konumu döndürülüyor burada.

-------------------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ ÖRNEK

bool is_len_5(const std::string &str)
{
	return str.length() == 5;
}

using namespace std;
int main()
{
	vector<string> svec;
	rfill(svec,20,rtown);
	print(svec);

	// uzunluğu 5 olan ilk öğe

	find_if(svec.begin(), svec.end(), is_len_5); 
	// &islen de yazılabilir.
	//burada bizim yazdpımız fonksiyona vectordeki stringler gönderilecek.
	// ne zaman true olursa return edecek


	if(auto iter = find_if(svec.begin(), svec.end(), is_len_5); iter != svec.end())
	{
		std::cout << "bulundu ..." << iter - svec.begin() << " indisli oge " << *iter << "\n";
	}
	else
	{
		std::cout << "bulunamadi\n";
	}
}
Burada kullanılan iter random access

VECTOR YERINE LIST DERSEK BIDIRECTIONAL ITER OLACAĞINDAN SENTAKS HATASI OLUR

AMA bu yöntemler pratik değil.Sadece 5 olduğunu sorguluyor.
Ya client kodu yaan sadece 5 değilde 6,7,8 kontrolü isterse

Bu durumda functor objeler büyük fayda sağlıyor.

find a baktık cppreference tan

-------------------------------------------------------------------------------------------------------------------------------------

AŞIRI ÖNEMLİ !!!!!!!!!!!!

YUKARIDAKI YÖNTEM PRATIK DEĞIL.SADECE 5 UZUNLUĞUNUN KONTROLÜNÜ YAPIYOR.
BUNU HERHANGIBIR UZUNLUĞU KONTROL EDECEK ŞEKILDE YAZMAMIZ GEREKIR.
CPPREFERENCE'TAKİ SECOND VERSION GİBİ.SINIF NESNESİ FUNC ÇAĞRI OPERATÖRÜNÜN OEPRANDI OLUYOR.FUNCTOR


class LenPred{ 
public:
	LenPred(size_t len) : mlen{len} { }
	bool operator()(const std::string &s){		// DİKKAT!!!
		return s.size() == mlen;
	}
private:
	size_t mlen;
};


using namespace std;
int main()
{
	vector<string> svec;
	rfill(svec,20,rtown);
	print(svec);

	size_t len;
	cout <<"uzunluk kac olan bulunsun : ";
	cin>>len;
	

	; // Dikkat!!!!

	if(auto iter = find_if(svec.begin(), svec.end(), LenPred{len}); iter != svec.end())
	{
		std::cout << "bulundu ..." << iter - svec.begin() << " indisli oge " << *iter << "\n";
	}
	else
	{
		std::cout << "bulunamadi\n";
	}
}

LenPred{len} burada geçici nesne bizim tarafımızdan değeri verilmiş bit tamsayı ile construct ediliyor.
Daha sonra algoritma bunu callable olarak kullanacak.Her bir string değeri için uzunluk uyuşuyor mu diye bakacak.
Bizim yazdığımız find_if ten koduna bakılırsa nasıl bir şekilde callable olarak kullandığı görülür.

func call operatörünü overload eden sınıflara functor veya function object sınıfları deniyor.
Bunlar özellikle STL algoritmalarında algoritmanın predicate veya callable parametresine argüman olarak gönderiliyor
ve çok daha esnek bir yapı sağlanıyor.

Burada Functor class kullandık bunlar çok faydalı.

-------------------------------------------------------------------------------------------------------------------------------------

Önce gerçek func yazıp adres sgönderik
sonra sınıf yazdık ...
Bundan biraz daha ötesi Lambda ifadesi.ModernC++ ın 
en önemli öğelerinden biri.

=====================================================================================================================================================
=====================================================================================================================================================
=====================================================================================================================================================
=====================================================================================================================================================

LAMBDA EXPRESSION
-----------------

Bunu ileride 3-4 saat göreceğiz.

Bu öyle bir ifadeki derleyici bununla karşılaştığında bir sınıfın kodunu compile time da yazıyor
ama bu sınıf local bir sınıf( biz daha görmedik, func içinde tanımlanan sınıflar)
ve ifadeyide yazılan sınıf türünden geçici bir nesne oluşturma ifadesine dönüştürüyor.

Yani lambda yazınca sınıf türünden geçici nesne oluşturma ifadesi yazıyor compiler.

ÖR:
using namespace std;
int main()
{
	vector<string> svec;
	rfill(svec,20,rtown);
	print(svec);

	size_t len;
	cout <<"uzunluk kac olan bulunsun : ";
	cin>>len;


	if(auto iter = find_if(svec.begin(), svec.end(), [len](const string &s){return s.size() == len;} ); //DİKKAT!!!
	{
		std::cout << "bulundu ..." << iter - svec.begin() << " indisli oge " << *iter << "\n";
	}
	else
	{
		std::cout << "bulunamadi\n";
	}
}

[len](const string &s){return s.size() == len;} -> Burada derleyici bir sınıf yazacak ve bunu o sınıf türünden bir geçici nesne ifadesine döüştürecek
Bu derleyicinin yazdığı sınıf türden nesne olduğu için find_if algoritmasının ikinci tempalte tür parametresi bu sınıf türünden nesne olacak.
Bu nesne func call operatörünün operandı olacak için algoritma içinde.

Programcı lambda function derse, derleyicinin yazdığı sınıfın function call operator functionuna lambda function demiş olabilir.

-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------

LAMBDA IFADESİ

[]() {}();   // Bu bir lambda ifadesi

Derleyiciye sınıf kodu yazdıran bir ifade lambda ifadeleri.Derleyici bu ifadeyi bir geçici nesne oluşturma ifadesine dönüştürüyor.
Lambda gördüğümüz heryerde bir sınıf türünden geçici nesneler var demektir.

Lambda ifadeleri karşılığında derleyicinin oluşturduğu türe closure type, oluşan geçici nesneyede closure object deniyor.

[] -> buraya yazılan ifadelere lambda capture deniyor
ilk () -> Derleyicinin yazdığı sınıfın parametresinin parantezi
{} -> derleyicinin yazacağı sınıfın anabloğu
son () -> Func çağrı operatörü 

class asd{
public:
	auto operator()(int x){
		return x + 5;
	}
};

[](int x){ return x + 5;}  -> Bu ifade asd sınıfı türünden bir geçici nesne

-------------------------------------------------------------------------------------------------------------------------------------------------------------

BU LAMBDA IFADELERI ILE NELER YAPABILIRIM

[](int x){ return x + 5;}(9) gibi funccall operatörünün operandı yaparak çağırabilirim.

auto f = [](int x){ return x + 5;};
f(3) gibi çağırabilirim

Bunu bir algoritmaya argüman olarak gönderirsek, algoritmanın ilgili func parametresi bu sınıf türünden olacak, 
template parametreside bu bu sınıf türünden olacak

Bu sınıfın bizim açımızdan bir ismi yok. Derleyici biliyor bu ismi.

-------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
voidfunc(T f)
{

}

int main()
{
	func([](int x, int y){return x*x + y*y;}); en sık kullanılan biçimi.
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto f = [](int x, int y){   // bu türden değişken f
	return x*x + y*y;
	};

	cout << typeid(decltype(f)).name() << "\n"; // bu lambda ifadesinin türünü veriyor
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------

TEMEL SENTAKS
-------------
auto f = [](){return 1;};
auto f = []{return 1;}; // ikisi arasında fark yok eğer parametre değişkeni olmayınca ve ileride göreceğimiz bazı betimleyiciler yoksa.

decltype(f) x; // C++20 ye kadar bunun cevabı hayır tanımlanamazdı. 
Default ctorun delete edildiğini söyleyecek.bu sebeple sentaks hatası.C++20 de geçerli

Aynı şekilde copy assignment ta delete edilmiş durumda
decltype(f) g(f); // burada copy ctor çağrılıyor.Delete edilmemiş.

f = g; //buda sentaks hatası.Copy assignment delete edilmiş. C++20 de geçerli.

Lambda stateless lambda ise (yani hiçbir değişkeni capture etmeyecek - [] içinde ifade olmayacak) default ctor, copy assignment deleted değil.

Func anabloğu içinde return statement yoksa veya sadece return; varsa, bu durumda derleyicinin yazdığı functionun return değeri türü void.

[](){} = bu kadarı lambda ifadesi sonraki 
[](){}() = burada ise sonda func call var.

Aşağıdaki ile aynı aslında
class A{
public:
	void operator()(){ 
	
	}
};

int main()
{
	A{}(); aynısı yukarısı ile
}


-----------------------------------------------------------------------------------------

[](){
	//FUNC CALL OPERATOR FUNCTIONUNUN ANA BLOĞU 
	// HERHANGİBİR ŞEY YAZILABİLİR.
}

-----------------------------------------------------------------------------------------

int main()
{
	[](){ std::cout << "Merhaba Dunya\n";}();  
}

Merhaba Dunya

-----------------------------------------------------------------------------------------

int main()
{
	auto sum_square = [](int x, int y){	
		return x * x + y * y;
	};
	//Yukarıdaki sınıf türden değişken. sum_square sınıf türden bir değişken oldu.

	cout << sum_square(33,42) << "\n"; // burada da değeri gösterir.
}

-----------------------------------------------------------------------------------------

int main()
{
	auto sum_square = []{
		return x * x + y * y;
	};
	//Yukarıdaki sınıf türden değişken. sum square sınıf türden bir değişken oldu.

	cout << sum_square(33,42) << "\n"; // burada da değeri gösterir.
}

-----------------------------------------------------------------------------------------

LAMBDA IFADESI IÇINDE IFADENIN YAZILDIĞI YERDE GÖRÜLEN STATIC ÖMÜRLÜ NESNEYI KULLANABILIYORUM.
COUT MESELA STATIC ÖMÜRLÜ GLOBAL BIR ISIM O YÜZDEN KULLNABILDIK

int x = 10;
int y = 20;

int main()
{
	auto f = [](int a){return a * ( x + y); } // x ve y burada kullanılabilir.

	cout << f(10) << "\n"; // 300 gösterir.
}

-----------------------------------------------------------------------------------------

int main()
{	
	static int x = 10;
	static int y = 20;

	auto f = [](int a){return a * ( x + y); } // x ve y burada kullanılabilir.

	cout << f(10) << "\n"; // 300 gösterir.
}

-----------------------------------------------------------------------------------------

int main()
{	
	int x = 10;
	int y = 20;

	auto f = [](int a){return a * ( x + y); } // SENTAKS HATASI

	cout << f(10) << "\n"; 
}

YEREL DEĞIŞKENLERI LAMBDA IFADESINDE KULLANMAK IÇIN CAPTURE DENEN YAPIYI KULLANMAMIZ
GEREKIYOR

-----------------------------------------------------------------------------------------

class Myclass{
public
	Myclass(int x, ,int y) : x(x),y(y) {	}
private:
	int x,y;
};

int main()
{
	int x = 10;
	int y = 20;
	Myclass(x,y); // bu şekilde yazıldığı zaman sınıfın ctorlarına gönderilen değerleri
}					// kullanmış olurdu.

-----------------------------------------------------------------------------------------

CAPTURE YAPISI

Lambdalarda da [x] yazıldığı zaman, öyle bir sınıf kodu yazıyorki, yazılan sınıfın veri
elemanı değeri köşeli parantezin içine yazdığımız değerden kopyalanarak alınsın demek.

int main()
{
	int x = 10;

	[x](int a){}   // lambda içinde x i kullandığımız zaman sınıfın veri elemanı olan x i 
					// kullanmış oluyoruz.Bu data member ise bizim local x ten kopyalama
					// yoluyla alıyor değerini

	auto f = [x](int a){ return x * a; };
	f(45) = 45 * 10 olacak.
}

-----------------------------------------------------------------------------------------

LAMBDALARIN MEMBER FUNCLARI DEFAULT OLARAK CONST
Lambdalar için yazılan member funclar aksi bir belirleme yapılmadıkça const member functır.


class xyz123{
public:
	int operator()(int a) const 
	{
		return x * a;
	}
private:
	int x;
};

int main()
{
	int x = 10;
	[x](int a){return x * a};
}

-----------------------------------------------------------------------------------------

NEDEN SENTAKS HATASI AŞAĞISI

int main()
{	
	int x = 10;
	int y = 20;

	auto f = [x](int a){ x = a;}; // SENTAKS HATASI
}

Const member func içinde sınıfın data memberını değiştiremeyiz.

-----------------------------------------------------------------------------------------

#include<string>

int main()
{
	string str{"alican"};
	[str] {str.append("ali")}; //SENTAKS HATASI. Yazılan const member func ama {} içindeki
}								// str, değerini yukarıdaki str den almış veri elemanı.
								// str.size(); deseydik hata yoktu.


================================================================================================================================
================================================================================================================================

MUTABLE

Daha önce öğrendiğimiz mutable ile ilgili değil bu mutable.

int main()
{
	int x = 10;
	[x](int a)mutable {x *= a;}; //SENTAKS HATASI YOK.
}

Yukarıdaki mutable, const olan member functionu const olmayan hale getirdi.
Derleyici func call operator func ı nonconst olarak yazdı.

AŞAĞIDAKİNİ YAZDI COMPILER
--------------------------

class xyz123{
public:
	void operator()(int a) { return x *= a;	};
private:
	int x;
};

int main()
{
	int x = 10;
	auto f = [x](int a){return x *= a;};
}


*/
