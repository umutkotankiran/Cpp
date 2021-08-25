/*

Dünkü dersteki bir soru üzerine
lambdalarda referansı, const referans olarak kullanma ile alakalı

class Biggie{
public:
	void func_non_const();
	void func_const()const;
};

int main()
{
	Biggie big;

	auto f = [big = static_cast<const Biggie &>(big)]() { // const_cast te kullanılabilir tabi.

		big.func_const();  // Bu hata değil.Big const bir nesne ve çağrılan func ta const.
		big.func_non_const(); // Burası hata. big artık const bir nesne amaçağrılan func nonconst. const nesne ile const olmayan func çağrılamaz.SENTAKS HATASI
	}
}




---------------------------------------------------------------------------------------------------------------------------------------------------------------------

BU IŞI YAPAN BIR DE FUNCTION ŞABLONU VAR C++2017 DE GELDI

Const olmayan bir nene veriyoruz ve o nesneye const referans döndürüyor.

as_const - utility altında(move, forward, pair .... hepsi burada)

int main()
{
	Biggie big;

	auto f = [big = std::as_const(big)]() {
		big.func_const();  // Bu hata değil
		big.func_non_const(); // Bu hata
	}
}
Çok ihtiyaç olmuyor zaten ama hoca bu implementasyonu tercih ediyor


=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================
=====================================================================================================================================================================

KALDIĞIMIZ YERDEN DEVAM
Bazı funclar var ki iteratörleri manipule ediyor. Bunlar  advance, distance, next, prev, iter_swap.
İteratörü artırmanın ideal yolu advance functionu. Belirli bir pozisyon kadar artırıyor. Eksiltmekte mümkün ama o zaman en az bidirectional olması gerekiyor.

Dolayısıyla iteratörün capability sinden bağımsız iteratörü artırmak için ideal yol advance functionu.

#include <vector>
#include <list>
#include <utility>
#include <iostream>

int main()
{	
	list<int>ilist{0,1,2,3,4,5,6,7,8,9};
	auto iter = ilist.begin();

	std::cout << *iter << "\n";
	advance(iter,3);
	std::cout << *iter << "\n";
	
	advance(iter,-2); // bidirectional olduğundan -2 diyebiliriz
	std::cout << *iter << "\n";
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

TAG DISPATCH TEKNIĞINE UYGUN. BIR IMPLEMENTASYON GÖSTERILIYOR.

Buradaki implementasyonu hoca yazmış zaten.Açıklayıcı bir implementasyon

#include <iterator>

namespace details
{
	template <typename Raniter, typename Distance>
	void advance(Raniter& it , Distance n, std::random_access_iterator_tag)		
	{
		it += n;	
	}

	template <typename Biditer, typename Distance>
	void advance(Biditer& it , Distance n, std::bidirectional_iterator_tag)
	{
		if(n>0)
		{
			while(n--)
			{
				++it;
			}
		}
		else
		{
			while(n++)
			{
				--it;
			}
		}
	}

	template<typename Initer, typename Distance>
	void advance(Initer &it, Distance n, std::input_iterator_tag)
	{
		while(n--){
			++it;
		}
	}
}

template<typename Iter, typename Distance>
void advance(Iter& it, Distance n)
{
	details::advance(it, n, typename Iter::iterator_category{}); // compile timeda vector<int> iteratörü olduğunu anlaşılırsa mesela, iterator türü random access iterator tag olcak ve 1. ci overload seçilecek
												// Ama iter türü list<int> iteratör türü ise, iterator categori bidirectional olduğu için 2. overload seçilecek. Input ise 3.
												// normalde ...::iterator::iterator_category derdik ama zaten buraya gelen bir iterator oldupu için yani ...::iterator türden gönderildiği için
												// birdaha iterator yazmaya gerek yok.
	NOT !!!!!!!
	YUKARIDAKİ KISIM POINTER TÜRLERİ İÇİN HATA VERECEK.AŞAĞIDA DAHA POINTERLARIDA KAPSAYAN KISIM VAR.

}


Buradaki sorun iterator kategorisine bağlı olarak ya artıracağız yada döngüsel bir yapı içinde eksilteceğz.
Bunun için compile time da ideal kodun seçilmesi gerekiyor.

Bunlar birbirlerinin overloadları.Biz bu functiona bir iterator birde distance gönderirsek birde iterator categorisi belirleyen sınıflardan biri türünden
geçici nesne gönderirsek, function overload resolutionda ilgili function seçilecek.


int main()
{
	int a[10]{};

	int *ptr = a;

	advance(ptr,5); //SENTAKS HATASI. Neden bu int * türünden ve bunun iterator categorisi yok.

}

BU TİP POINTER DURUMLARINI ÇÖZMEK İÇİN NE YAPILMIŞ AŞAĞIDAKİ ÖRNEKTE AÇIKLANIYOR.


---------------------------------------------------------------------------------------------------------------------------------------------------------------------

ITERATOR TRAITS ISIMLI METAFUNCTION VAR. 


int main()
{
	int a[10]{};

	int *ptr = a;

	iterator_traits<vector<int>::iterator>::Iterator_category

	advance(ptr,5); //SENTAKS HATASI. Neden bu int * türünden ve bunun iterator categorisi yok.
}

iterator_traits pointer türleri için özelleştirilmiş.Dolayısıyla aslında iteratörün iterator categorisi demekle, iterator_traits in iterator açılımının iterator categorisi demek
aynı şey. Neden Böyle birşey yapmışlar ? Iterator traits pointer türleri için özelleştirilmiş.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------


template <typename Iter, typename Distance>
void advance(Iter& it , Distance n)
{
	advance(it, n, typename std::iterator_traits<Iter>::iterator_category{}); // Gerçek iterator türleri için aynı kategori ama pointer türleri için doğrudan pointer kullanılacak
}																				// bu da özelliştirmede random access iterator tag verecek.

POINTER HATASIDA BÖYLE ÇÖZÜLMÜŞ OLUYOR.

iterator_traits e bakıldı cppreference tan.iterator header file içerisinde bulunuyor.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------

BU TÜR KODLARI YAZMAYI DAHA KOLAY HALE GETİREN C++2017 İLE DİLE GELEN IF CONSTEXPR VAR

Aynı kodu compile time if kullanarak hiç tag dispatch uygulamadan gerçekleştirebiliriz.

#include <iterator>
#include <type_traits>

template <typename Iter, typename Dist>
void advance(Iter& pos, Dist n)
{
	using cat = typename std::iterator_traits<Iter>::iterator_category; // bunu birden fazla yazacağımız için türeş ismi verildi.

	if constexpr(std::is_same_v<cat,std::random_access_iterator_tag>)
	{
		pos += n;
	}
	else if constexpr(std::is_same_v<cat,std::bidirectional_iterator_tag>) is_same_v yerine is_same olsaydı en sona ::value gelecekti.
	{
		if(n>0)
		{
			while(n--)
			{
				++it;
			}
		}
		else
		{
			while(n++)
			{
				--it;
			}
		}
	}
	else // input iterator tag
	{
		while(n--)
			++pos;
	}
}

Yukarıdaki gibi compile time if i ile gerçekleştirebiliriz.
if constexpr de ileri C++ ta ayrıntılı anlatılıyor.

ADVANCE NASIL IMPLEMETE EDİLİR GÖRDÜK

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

DISTANCE
--------

int main()
{
	vector<int>vec{1,2,3,4,5,6,7};
	auto iter_x = vec.begin();
	auto iter_y = vec.end();

	// vectordeki eleman sayısına distance deniyor.
}

iter_y - iter_x bu distance ı verecekti eğer pointer olsaydı.
[iter_y,iter_x) buna distance deniyor zaten

Bu işin yapılması için iterator category random access iterator olmalı.
list açılımında sentaks hatası olur mesela bu çıkarma işlemi.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
List ile nasıl olacaktı

int main()
{
	list<int>vec{1,2,3,4,5,6,7};
	auto iter_x = vec.begin();
	auto iter_y = vec.end();

	int n = 0; // aradaki öğe sayısı falan. Çok dikkat li yazılmadı amaç her seferinde 1 tane artırmak olduğunu göstermek.
	while(iter_x != iter_y)
	{
		++iter_x;
		++n;
	}
}
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunu compile timeda yaptırmak istersek arka planda tag dispatch veya if constexpr ile yapılabilir
Ama yapılmışı var biz yapmayacağız. std::distance

#include <iterator>

int main()
{
	vector<int>vec{1,2,3,4,5,6,7};
	auto iter_x = vec.begin();
	auto iter_y = vec.end();
	
	auto n = distance(iter_x, iter_y);
	std::cout << "n = "<< n << "\n"; // 7
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pointerlarla da çalışır

int main()
{
	int a[]{1,2,3,4,5,6,7,8,9};

	int* pf{a + 3}, *pe{a + 7};

	std::cout << distance(df,pe)<< "\n"; // 4 
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Distance mecburi senaryo

int main()
{
	forwar_list<int> mylist {1,2,3,4,5,6,7,8,9}; // ileride görülecek bir nedenden size func ı yok. Diğer tüm containerlarda var ama bunda yok.Verimli olması için eklenmemiş.
	
	std::cout << distance(mylist.begin(),mylist.end()) << "\n"; // mylist in boyutunu veriyor.
}

Distance ve advance modern C++ ile gelmedi.Öncesinde vardı.
Ama prev ile next C++ 11 ile geldi.

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================


NEXT VE PREV
------------
Advance pointerın veya iteratörün kendisini iletiyor yani referans yoluyla alıyor.call by reference
Fakat next bizden bir iterator alıyor ve o iteratörden n sonraki konumu return değeri olarak iletiyor.Call by value

next(iter, 5);//call by value. Bu iteratorden 5 sonraki konum. 2. parametresine argüman geçmezsek default olarak 1 alıyor.
next(iter); // bir sonraki konumu return ediyor.

Prev de bunun tam tersi.
prev(iter ,3); Bidirectional olmalı minimum. Bu konumların geçerli olması programcının sorumluluğunda. Exception throw etmiyorlar bu funclar.
prev(iter); birönceki konumu veriyor.

ÖR:
int main()
{
	vector <int> x {1,2,3,4,5,6,7};

	auto iter{x.begin()};

	auto iter_a = iter + 3; // 3 sonraki konum bu.Random access iterator bu

	//vector değilde list olsaydı sentaks hatası olurdu ama çözebiliyoruyz tabi
	auto iter_a = next(iter,3); diyoruz. ITER DEĞIŞMIYOR HALEN AYNI DEĞERDE. ITER_A YA 3 SONRASI ATANDI !!!!!!

	std::cout << *iter <<"\n";

	//ilk ve son hariç hepsini yazdır
	print(next(x.begin()), prev(x.end()));

	//RANGE BASE FOR LOOPTA BİR BUG VAR.

	*prev(e.end(),2) = -1;  // 1,2,3,4,5,-1,7}
	print(x);
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

ITERSWAP 
Iter swap doesnt swap iterators. İterator konumundaki 2 nesneyi swap ediyor.


template <typename Iter1, typename Iter2>
void iter_swap(Iter1 it_x , Iter2 it_y)
{
	....
}



İlk ile son elemanı değiştirelim mesela

int main()
{
	list<int> x {1,2,3,4,5,6,7};

	swap(x.front(), x.back()); //aslında böyle yapılabilir. Front ve back, ilk ve son öğeye referans alabiliyoruz.

	swap(*x.begin(), *prev(e.end())); // end ten bir geri geldi. onu kullandi tabiki.

	iter_swap(x.begin(), prev(x.end())); //DİKKAT!!! Asıl örnek bu.konumları değil, konumdaki nesneleri takas ediyor.

	print(x);
}

2 değişkeni nasıl swap ederiz.

int x = 10;
int y = 45;

swap(x,y); // referans semantiği ile
iter_swap(&x,&y); // pointerlar iterator gibi kullanılabiliyorlar.
tuple sınıf şablonuyla call by value ilede swap edilebilir.Sonra görülecek
birde bitwise işlem var.Çok önermiyor hoca.xor swap.sadece tamsayı türleri için

Görmediğimiz iterator adaptörleri var
ostream_iterator
istream_iterator
move_iterator	sınıfları

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================


STL ALGORİTMALARINA DÖNÜYORUZ YİNE

200 e yakın algoritma var. Algoritmaların birçoğunun overloadları var. Bunlar bir veri yapısı üzerinde çalışacak algoritmaların generic kodları.
replace, copy, copy_if ... Dolayısı ile productionda kodun daha okunur olması için test edilmesinin daha kolay olması için hata yapma riskinin daha az olması için
algoritma uygulamamız gereken yerde ya doğrudan STL algoritması kullanmalıyız yada birden fazla algoritmayı combine ediyoruz. Genel yapısını öğrenirsek yenisini
daha kolay anlayabiliriz.Tüm algoritmaların complexity si dökümante edilmiş.Profesyonel kişiler tarafından yazılınca ve derleyicinin de bazı özellikleri göz
önüne alındığı için çok iyi optimize edilmiş bu kodlar.

raw for looptan kaçınıyoruz.

Şimdiye kadar bahsedilen algoritmalar
copy
copy_if
count
count_if
reverse    Şimdi bir tane daha görelim :D

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REVERSE

int main()
{
	std::vector<std::string>svec; // mülakatlarda hava atmak için böyler yaz :D:D:D:D
	rfill(svec,10,rtown);
	print(svec);


	reverse(begin(svec),end(svec)); // ters çevirdi.
	print(svec);


	for(auto &s : svec)
	{
		reverse(begin(s),end(s)); // her turda reverse çağrıldı. yazıların kendiside ters döndü :D
	}	
	print(svec);

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İKİ SEÇENEĞİM VAR HANGİSİNİ KULLANIRIM

A - Bu işi yapmak için bir STL algoritmasına çağrı yapabiliriz. 
B - Sınıfın bu işi yapan member funcına çağrı yapabiliriz. 

Cevap member func.
Algoritma iterator parametreli. Dolayısıyla algoritmanın kodu ne olursa olsun algoritma containera erişemiyor.
Mesela Reverse algoritması
Bu algoritma iterator konumlarındaki nesneleri takas ediyor.
Bu bir bağlı liste olsaydı, bağlı listenin ters çevrilmesi için reverse algoritmasını çağırırsak böyle yapacak.
Bağlı listelerdeki öğeler 4bin byte lık öğeler olduğunu düşün.Bu durumda reverse algoritmasını çağırırsak 4 Bin byte lık nesneleri takas edecek
Ama bağlı listenin kendi reverse functionu kodu pointerları takas edecek şekilde yazılmış.Zaten private memberlarınada erişiyor ki bunlar implementasyon
için çok önemli olabilir. Böylece 4Bin bytelık bloklar takas etmesine gerek kalmaz. Algoritma bundan faydalanamaz.

Mesela Find algoritması
lineer arama yapıyor.Set te değer arayabiliriz ama bu ikili arama ağacı, setin kendi arama func ını çağırırsak o ikili arama ağacında logaritmik karmaşıklıkta
arama yapıyor.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	list<string> x;
	rfill(x,100,rname);
	
	reverse(x.begin(), x.end()); // Bu STL algoritması maaliyeti çok yüksek olabilir

	x.reverse(); // member function.Daha verimli olabilir.İçinde tutulan öğelerin türüne göre 1000 lerce kat daha verimli olabilir.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STL ALGORITMASI INCELEYELIM.

for_each

Bir rangedeki tüm öğeleri bir functiona gönderiyor.range base for loop un kullanılmasını azalttı.

template <typename Iter, typename Ufunc>
Ufunc foreach(Iter beg, Iter end, Ufunc f)
{
	while(beg != end)
	{
		f(*beg++);
	}
	return f; // burası ilginç.Return değerinden ilave bilgi elde edilebilsin diye var.
}


int main()
{
	vector<string> svec;
	rfill(svec,100,rname);
	print(svec);

	for_each(svec.begin(), svec.end(), [](auto &s){s += "can";}) // range base for loopta kullanılabilir.
	print(svec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	vector<Date> dvec;
	rfill(dvec,10,Date::random);
	print(dvec);

	std::cout << "\n\n\n";

	for_each(svec.begin(), svec.end(), [](auto &d){++d;}) // range base for loopta kullanılabilir.Günleri 1 date artırdı

	std::cout << "\n\n\n";

	print(svec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRANSFORM
---------

C++20 ile ileri C++ ta anlatılan bir kütüphaneyide anlamamıza yardımcı oluyor.

2 adet overload u var. Bir range i transform ediyor.
1. overload u range teki öğeleri bir functiona gönderiyor ve bunun return değerini bir hedef range yazıyor.

Template Kodunu yazalım

template <typename InIter, typename OutIter, typename Func>
OutIter Transform(InIter beg, InIter end, OutIter dest,Func f)
{
	while(beg != end){
		*dest++ = f(*beg++);
	}

	return dest;
}

NOT : HEDEF RANGE ILE KAYNAK RANGE AYNIDA OLABILIR !!!!

int main()
{
	vector<int>ivec{1,3,5,7,9,11,13,19,199};
	list<int> ilist(ivec.size());
	int n;

	std::cout << "kac kat: ";
	cin>> n;

	print(ivec);
	transform(ivec.begin(), ivec.end(), ilist.begin(), [n](int x) {return x*n;})
	print(ilist); // listedeki öğeler vectördekinin 5 katı oldu.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LISTEMIZ BOŞ OLSUN


int main()
{
	vector<int>ivec{1,3,5,7,9,11,13,19,199};
	list<int> ilist;
	int n;

	std::cout << "kac kat: ";
	cin>> n;

	print(ivec);
	transform(ivec.begin(), ivec.end(), back_inserter(ilist), [n](int x) {return x*n;}) // backinserter ile yapıldı
	print(ilist); 


	transform(ivec.begin(), ivec.end(), ivec.begin(), [n](int x) {return x*n;}) // Vectorun kendisini değiştirmek için böyle yapilir
	print(ilist); 
}

TRANSFORM COPY TÜM YAZMA ALGORİTMALARI EN SON YAZILAN KONUMDAN BİR SONRAKİ KONUMU DÖNDÜRÜYORLAR.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRANSFORM ALGORITMASININ BIR OVERLOADU DAHA VAR
Bu sefer 2 kaynak range var. Bunlar 2 parametreli bir functiona bu kaynak range teki öğeler argüman olarak gönderiliyor.İkisinden de her turda birer öğe.
Buradaki functionda tabiki binary function. Yaptığı iş geri dönüş değerini bir range e yazmak.

CPPREFERENCE TAN ALINDI
Maşallah 5 parametresi var :D:D:D:D

template<class InputIt1, class InputIt2, class OutputIt, class BinaryOperation> 
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op)
{
	while (first1 != last1) {
		*d_first++ = binary_op(*first1++, *first2++);
	}
	return d_first;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

VECTORDEKI ELEMANLARLA LISTEDEKI ELEMANLARIN KARELERI TOPLAMINI BAŞKA LISTEYE YAZACAĞIZ.

int main()
{
	vector<int>ivec{1,3,5,7,9,11,13,19,199};
	list<int>ilist{21,23,25,27,29,211,213,219,399};

	vector<int> dvec;

	transform(ivec.begin(), ivec.end(), ilist.begin(), back_inserter(dvec),	[](int a, int b){ return a * a + b * b ;});

	print(dvec);
}


MOLA

============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================
============================================================================================================================================================================


Bazı algoritmalar nonmodifying, bazı algoritmalar ise modifying. Mesela find sadece öğe ararken, sort sıralıyor değiştiriyor yani.

Sıralamaya ilişkin algoritmalar 10 civarı
Silme algoritmaları var

_copy ile biten algoritmalar bir işlemi range üzerinde değilde, o range üzerinde o işlem yapılmış gibi başka bir range yazıyor.

remove_copy    böyle
remove_copy_if     belirli koşulu sağlayanları siliyor.
reverse_copy        range in tersini bir hedefe yazıyor. aşağıda örnek var. 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	vector<string>svec;
	rfill(svec,10,rname);
	print(svec);
	vector<string> destvec(10);

	reverse_copy(svec.begin(), svec.end(), destvec.begin()); // destvec e svec tekilerin tersini kopyaladı
	print(destvec); //destvec e tersini yazmış
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE_COPY

template <typename InIter, typename OutIter, typename T>
OutIter RemoveCopy(InIter beg, InIter end, OutIter destbeg, const T& val)
{
	while(beg != end)
	{
		if(*beg != val)
		{
			*destbeg++ = *beg;
		}
		++beg;
	}
	return destbeg;
}

ÖR:
int main()
{
	vector <int> ivec;
	rfill(ivec,100,Irand{0,5});
	print(ivec);

	vector<int>dvec;
	int ival;
	std::cout << "silinecek deger : ";

	cin>> ival;
	remove_copy(ivec.begin(), ivec.end(), back_inserter(dvec),ival); // 3 girersek 3 ler silinecek.Neden backinserter çünkü kapasitesi artmalı.
	print(dvec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE_COPY_IF

Function bir değer için false döndürürse silinmeyecek
template <typename InIter, typename OutIter, typename UnPred>
OutIter RemoveCopyIf(InIter beg, InIter end, OutIter destbeg, UnPred f)
{
	while(beg != end)
	{
		if(!f(*beg))
		{
			*destbeg++ = *beg;
		}
		++beg;
	}
	return destbeg;
}

int main()
{
	vector<string>svec;
	rfill(svec,100,[]{return rname() + '_' + rfname();}); // isimle soyisim arasına _ koydu
	print(svec,"\n");

	char c;
	std::cout << "bir karakter girin : ";
	cin>> c;
	vector<string> evec;

	remove_copy_if(svec.begin(), svec.end(),back_inserter(evec),
	[c](const string &s){return s.find(c) != string::npos;} ); // içinde belli bir char olanları yeni vectore yazmadı

	print(evec,"\n");

}


Algoritmaların çoğu paralel programlamaylada çalıştırılabiliyor. Birden fazla thread tarafından çalışıtırılabiliyor yani.
Hepsi değil ama birçoğu bu özelliğe sahip.

bir örnek daha yaptı onuda yaz.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
REPLACE_COPY_IF 

int main()
{
	vector<string>svec;
	rfill(svec,100,[]{return rname() + '_' + rfname();}); // isimle soyisim arasına _ koydu
	
	vector<string> evec; // bu range de yazabilirdik ama yazmadık. Kendisine yazıldı.
	size_t len;

	std::cout << "uzunluk degerini girin\n";
	cin>>len;

	//uzunluğu len olanlar "rejected" yazısı ile değiştirilecekler.
	replace_copy_if(svec.begin(),svec.end(),svec.begin(),[len](const string &s){ return s.size() == len },"rejected");
	print(svec,"\n");

}

 
===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================
===========================================================================================================================================================================


CONTAINERLAR
------------

Vector
------
Tüm contrainer sınıfları bir yana vector bir yana. Uzak ara en çok bu kullanılacak. Çünkü vector bir dinamik dizi.Stringlerde de dinamik dizi vardı. Vector genel
amaçlı iken string sadece yazılara ilişkin.

Sequence Containers
-------------------
std::vector
std::deque
std::list
std::forward_list
std::array
std::string
C array

C Array saymazsak bunların tüm containerların,
a - Bütün containerlarda ortak olan member functionları var.
b - Sequence containerlara özgü ayrı ortak functionlar var.

Vectorü incelediğimiz zaman diğerlerinide büyük ölçüde incelemiş olacağız.

Dİnamik dizi neydi ? 
Öğeler contigues şekilde dinamik olarak allocate edilmiş bir bellek bloğunda tutuluyorlar.
Bu bellek bloğunda tutulan fiziksel olarak öğe sayısı, containerın size ı.
Allocate edilmiş bellek bloğunda yeni bir bellek alanına ihtiyaç duymadan tutulabilecek öğe sayısı vectorun capacity si.

Temel Avantajı
Sondan ekleme amorties constant time
index ile erişim constant time(amortised demedik.)

En dikkat edilmesi gereken nokta, Size capacity ye eşit olduğunda bir insert işlemi yapılırsa, kapasite yetersiz olduğundan reallocation olacak,
reallocation yeni allocate edilmiş bir bellek alanına taşıyacak. Eski bellek bloğundaki öğeler yenisine kopyalanacaklar yada taşınacaklar.
ilave maliyet bu.Reallocationdan kaçınmak için neler yapmak gerekir, tipik hatalar nelerdir görülecek.

Productionda container ihtiyacımızın en az %70 ini karşılayan sınıf bu. Adımız gibi hakim olmalıyız.
Default containerımız her zaman vector.

Vectorun Önemli bir avantajı.
Dİnamik dizi veri yapısının cache friendly olması. Bellekte ardışık oldukları için l2 - l3 cache e belli bir miktarını alabiliriz.
Burada cache hit cache miss oranı çok daha iyi. Günümüzde en çok performansı etkileyen veri yapısı bu.

Ortalama performansı en yüksek veri yapısı vector.
Özellikle çok fazla öğe tutulacaksa, sondan değilde herhangibir noktadan ekleme silme yapılacaksa, belirli bir sıra ilişkisiyle elemanları tutacaksa
başka altrnatiflere bakmak lazım. Tipik olarak ekleme sondan ve index erişimi varsa vectörden iyisi yok.

Vector bir std içinde sınıf şablonu.

template <typename T, typename A = std::allocator<T>>
class Vector{

};

Allocator İleri C++ ta anlatılıyor.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	std::vector<int> Bununla aşağıdaki aynı anlamda
	std::vector<int, std::allocator<int>>
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++17 ile Constructordan faydalanarak template argümanının çıkarılması özelliği var.

ÖR:
pair<ind,double> px{12,3.4}; Normalde pairi böyle yazarız
pair px{12,3.4}; C++ 17 de argümanların türünden hareketle template tür argümanlarının türünü compiler anlıyor.

std::vector vx(2,3,4,5);  // Bu aslında vector<int> bu CTAD ile anlaşılıyor.


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CTAD ÖRNEĞİ

Tür çıkarımı auto ile aynı.array decay, refin düşmesi gibi herşey aynı özel durumlar hariç

ÖR:
template <typename T>
class Myclass{
public:
	Myclass(T x);
	Myclass(T x, T y);
};

int main()
{
	Myclass x(12); // SENTAKS HATASI YOK
	Myclass y(12, 45); // SENTAKS HATASI YOK
}

ÖR:
template <typename T, typename U>
class Myclass{
public:
	Myclass(T x);
	Myclass(T x, T y);
};

int main()
{
	Myclass y(12, 4.5); // SENTAKS HATASI YOK YİNE
}

T nin çıkarımı int U nunki double olarak çıkarım yapıldı.
İleri C++ ta bu yine görülecek.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename >
void func(std::vector<T>&c);

int main()
{
	vector<double>dvec;
	func(dvec);
}

vector return değeri parametre argüman .... herşey olabilir.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR CONTAINERI ÖĞRENECEKSEK ILK ÖNCE INTERFACE INI VE MEMBER TYPELARINI ÖĞRENMELIYIZ.HANGI MEMBER VE NESTED TYPELARI VAR NE IŞE YARIYOR BUNLAR ÖNEMLI.
TÜM CONTAINERLARIN DEFAULT CTORU VAR. İÇINDE HENÜZ ÖĞE TUTMAYAN SIZE I 0 OLAN BIR CONTAINER NESNESI OLUŞTURUYOR. 


STRINGTE LENGTH VE SIZE OLMASININ SEBEBI CONTAINERLARIN ORTAK ARAYÜZÜ.

vector<int>ivec;
ivec.size = 0
ivec.empty() true değer döndürecek.
ivec.capacity() vectorun kapasitesini döndürüyor. türü size_type yani size_t ile aynı.



int main()
{
	vector<int>ivec;
	ivec.size = 0 
	ivec.empty() true değer döndürecek.
	ivec.capacity() vectorun kapasitesini döndürüyor. türü size_type yani size_t ile aynı.

	vector<int>::size_type n = ivec.size();
	auto n = ivec.size();
	std::size_type  = ivec.size();


	vector<ivec>(10);
	ivec.push_back(2); //size = 11
	ivec.push_back(3); //size = 12
	ivec.push_back(7); //size = 13

	std::cout << "size = " << ivec.size() << "\n";
	std::cout << "cap = " << ivec.capacity() << "\n";
	ivec.push_back(5); //size = 14
	ivec.push_back(7); //size = 15. size capacity ile aynı oldu

	ivec.push_back(34); //Burada reallocation olacak artık. size16 capacity 22 oldu.

	std::cout << "size = " << ivec.size() << "\n"; 
	std::cout << "cap = " << ivec.capacity() << "\n"; kapasite artı. Kapasite artma miktarı implementation defined.

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Kapasite artık kodunu önceden yazmıştık önceden şimdi yazmayacağım. 1 milyon öğe olmadan 35 defa reallocation yapıldı. oradan oraya gitti veriler.
Çok maliyetli.Reserve ile baştan ayırt edersek alanı. reallocation olmayacak belkide hiç. 

reserve kapasiteyi baştan ayarlıyor.1 milyonu ayarlasak reserve ile allocation yapmayacak bu kadar	

Vectorde iki şeye dikkat edilmeli 
1 - Maliyet - Gereksiz Reallocation
2 - Iterator Invalidation 

vectorun öğelerini gösteren pointerlar veya referanslar olabilir. Herhangibir eklemede reallocation yapıldığında yeni bellek alanına kopyalandığında,
eski bellek alanını gösteren pointerlar dangling hale gelir.Buna çok dikkat etmeliyiz. Bunları kullanmamalıyız.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RESERVE KAPASITEYI KESIN AZALTIR DENEMEZ.

Mesela capacity = 100'000 ve size = 5'000  olsun
svec.reserve(5000) dersek burada fazla kapasiteyi daraltır diye birşey yok. Nonbinding shrink request.
shrink_to_fit C++11 ile geldi ve bu işi yapıyor.

Vectörde kapasite otomatik büyür ama kapasite küçültülmez.

int main()
{
	vector<int>ivec(100000);
	for(int i = 0; i < 100000;++i)
	{
		ivec.push_back(i);
	}

	std::cout << ivec.capacity() << "\n";
	ivec.clear();
	std::cout << ivec.capacity() << "\n"; //Kapasite hep aynı
}

NOT : MOVE CTOR NOEXCEPT GARANTISI VERIRSE REALLOCATION SIRASINDA MOVE CTOR ILE ÖYELERI YEN BELLEK ALANINDA OLUŞTURUYOR !!!!!!!!!!!!
	  	
VECTORUN TUM MEMBER FUNCLARINI ÖĞRENMELİYİZ.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SHRINK_TO_FIT

int main()
{
	vector<int>vec(672334);
	
	std::cout << vec.size << " " << vec.capacity() << "\n"; size  672334 capacity 672334
	
	vec.erase(vec.begin() + 5,vec.end());
	
	std::cout << vec.size << " " << vec.capacity() << "\n"; size 5 capacity 672334

	vec.shrink_to_fit();

	std::cout << vec.size << " " << vec.capacity() << "\n"; size 5 capacity 5	BURASI OLDU ARTIK

}


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DEFAULT CTOR
------------
vector<int> x; // default init 
vector<int> y{}; // value init Default ctor çağrılacak ikisinde de.
Size 0 olacak empty true döndürecek.

if(x.empty()) // boş olduğunu sınıyoruz.  x.size() == 0 yazmıyoruz

if(empty(x)) //te yazılabilir.

make empty gibi anlaşılmasın.BU sadece empty.
Containerdaki öğelerin tamaını silmenin en basit yolu clear func call.
STL de zaten make empty anlamında clear kullanılıyor.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

COPY CTOR
---------

int main()
{
	vector<int> x(6547); // Containerın size 6547

	vector<int> y = x;
	vector<int> y(x);   
	vector<int> y{x};
	auto y{x};			//bunlarda çağrılan hep copy ctor.

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MOVE CTOR
---------

Argüman olarak rvalue expression gönderirsek Move Ctor çağrılacak.
Vector implementasyonda small buffer optimization yok ama Boost library de var.
Kopyalama semantiği deep copy, move semantik ise pointerları kopyalıyor sadece. 3 pointer var
Vectorde. vector başlangıç adresi, push back ile ekleme yapılacak adres, diğeride sonunu tutuyor.
	
MOVED-FROM OBJECT
-----------------
Kaynağı Çalınmış nesne halen geçerli bir nesnedir.(kullanılabilir ama değeri konusunda bir öngörüde bulunulamaz)
Taşınmış bir nesne için dtor çağrıldığında herhangibir UB veya Resoure leak oluşmayacak
Taşınış nesneye yeni değer atamakta problem değil.

Dclass x;
Dclass y(std::move(x));
y = z; yapılabilir.

Mümkün olduğunca taşınmış nesneleri kullanmamak gerek. İllaha kullanılacaksa belirli bir değere sahip olduğuna varsayamayız.

Bu sınıf doğru yazılmışsa, sınıfın değişmezleri(invariantları) korunacak. Mesela nesne boş ise size func 0 döndürür.
	
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SIZE TYPE CTOR
--------------

Size type parametreli bir ctor var. bu vectorü n tane öğe ile başlatiyor.

int main()
{
	size_t n;
	std::cout << "kac tarih\n";
	cin>> n;
	vector<Date>dvec(n); // Bu Ctorda n, size değeri olacak. Bu ctor öğeleri default init ediyor. 

	std::cout << dvec.size()<< "\n";
}

BU CONSTRUCTOR VALUE INIT EDIYOR.
vector<int>dvc(10); tüm elemanlar 0 olma garantisinde.

Yani sınıf türden nesnelerde default ctor çağrılacak, bool türü için false, pointer ise nullptr olacak.
Date in default ctoru  1 1 1900 ile başlatıyor mesela

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

INITIALIZER LIST CTOR 
---------------------

Normalde uniform initialization parantez ile ayni anlama geliyor.

Burada sınıfın initializer list ctoru olduğundan küme parantezi ile normal parantez farklı anlama geliyor.
Küme parantezi kullanırsak o initializer list constructor demek.

vector<int>x(10); // size_t parametreli ctor kullanıldı. X in size 10 ve öğeler 0
std::cout << "x.size() = "<< x.size() << "\n"; // 10
print(x); // 0 0 0 

vector<int>x{10}); // size 1 oldu ve değeri 10
std::cout << "x.size() = "<< x.size() << "\n"; // 1
print(x); // 10 

//vector<size_type n, const T&val>; Örnek aşağıda
vector<int>ivec(100,5); // 100 tane 5
vector<int>ivec{100,5}; // 100 ve 5 değerleri tutulacak size değeri 2

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNU KENDİ SINIFLARIMIZDA DA YAPABİLİRİZ

class Myclass{
public:
	Myclass(int){
		std::cout << "Myclass(int)\n";
	};

	Myclass(int,int){
			std::cout << "Myclass(int,int)\n";
	};

	Myclass(std::initializer_list<int>){
		std::cout << "Myclass(std::initializer_list<int>)\n";
	}

};

int main()
{
	Myclass x(12);		// "Myclass(int)"
	Myclass y(1,2);		//"Myclass(int,int)"
	Myclass z{12};		// "Myclass(std::initializer_list<int>)"
	Myclass t{1,2};		// "Myclass(std::initializer_list<int>)"
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RANGE CTOR
----------

vector<int>vx;
vector<double>vy = vx; // vector<int> ve vector<double> farklı sınıflar atama yapılamıyor. İsteselerdi yaparlardı member template ile ama tercih edilmemiş.
vy = vx ; Bu da aynı şekilde hata.


int main()
{
	vector<int> myvec;
	list<int>mylist(myvec); // SENTAKS HATASI
}

Range Constructor iterator parametreli ve iteratörlerin türünün aynı olması gerekmiyor. Önemli olan iteratör konumundaki öğelerin birbirine atanabilmesi gerekiyor

vector<int> mycvec{1,2,3,4,6,8,7,5,3};
vector<double> dvec(myvec.begin(),myvec.end()); // GEÇERLI çünkü intten double a geçerli dönüşüm var.

vector <const char *>vec {"Ali","Can","Oya"};
list<string>mylist{vec.begin(), vec.end()}; // GEÇERLİ.const char * dan stringe dönüşüm var.
	
Range constructor çok önemli. Böyle farklı containerları içindeki öğeler birbirine assignable ise başka bir containerla başlatabliyoruz.

int a[]{1,4,6,8,9};
vector<int>ivec(begin(a),end(a));	//GEÇERLİ
vector ivec(begin(a),end(a));		//CTAD ÇALIŞIYOR BURADA.SEBEBİ DEDUCTION GUIDE BAŞLIKLI SENTAKS ÖZELLİĞİ.DAHA ANLATILMADI

MOLA

=======================================================================================================================================================================
=======================================================================================================================================================================
=======================================================================================================================================================================
=======================================================================================================================================================================
=======================================================================================================================================================================
=======================================================================================================================================================================

SINIFIN DİĞER FUNCTIONLARINA BAKALIM.

BUNLAR GET FUNCTIONS
size
capacity
max_type (tüm containerlarda ortak bir func)
empty

int main()
{
	vector<string>svec;

	svec.max_size(); // containerda tutulabilecek maximum kaç string olabilir bunu döndürüyor.Visual studo ayarlarıyla ilgili olabilir veya kullanılan donanımla ilgili

	ostream os{ cout.rdbuf() };	// Noktalarla ekrana birşey yazdırmak istersek. rdbuf ın return değeri ile başlattık.
	os << 12 << "\n"; // Ekrana çıktıyı yazacak.cout gibi ama os in formatlama özeliklerini değiştirip farklı şekillerde yazmasını sağlayabilirim.

	os << boolalpha << hex << showbase; // tamsayıları yazarken hex sayı sisteminde yazacak.
	int x = 234545;
	cout << x << " "<< (10>5)<<"\n"; 234545 1 
	os << x << " "<< (10>5)<<"\n"; 0x39431 true

	os.imbue(std::locale{ "" });
	os << 87923812 << "\n"; // 87.923.812 yazdı

}

NOT : Cout kopyalanamaz ama taşınabilirdi !!!!


ÇOK SAYIDA FUNC VAR AMA BUNLAR ITERATOR DÖNDÜRÜYOR

int main()
{
	vector<int> ivec;

	ivec.begin();
	ivec.cbegin();
	ivec.rbegin();
	ivec.crbegin();
	ivec.end();
	ivec.cend();
	ivec.rend();
	ivec.crend();
	//...
}



MAX SIZE A GERİ DÖNDÜK

int main()
{
	vector<Date>dvec;
	coutr << dvec.max_size() << "\n"; // en fazla kaç öğe tutabilir bunu gösteriyordu.türe göre bu değer değişiyor.
}

NEDEN BU STATIC MEMBER FUNC DEĞİL? NEDEN NONSTATIC MEMBER FUNC
ÇÜNKÜ ALLOCATOR A BAĞLI. ALLOCATOR IN NE OLDUĞUNA BAĞLI OLARAK FARKLI DEĞERLERDE OLABILIR


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖĞELERE ERİŞMEK

operator[] functionu referans döndürüyor.const vector için const referans döndürüyor.

int main()
{
	vector<int>ivec{1,2,4,6,8,9,5,4};

	for(size_t i = 0; i < ivec.size();++i)
	{
		cout << ivec[i] <<"\n";
		cout << ivec.operator[](i) <<"\n"; // ikiside aynı.
		
		++ivec[i]; // yapılabilir
	}
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

[] operator func hata durumunda exception throw etmiyor.

int main()
{
	vector<int>ivec{1,2,4,6,8,9,5,4};
	
	try{
		auto val = ivec[54]; // UNDEFINED BEHAVIOR
		auto val = ivec.at(54); // BURADA EXCEPTION THROW EDILIR VE YAKALANIR
	}
	catch(const std::exception &ex){
		std::cout << "Exception cought : " << ex.what() << "\n"; 
	}

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FRONT VE BACK 
front functionu sequence containerlarda ilk eğeye referans döndürüyor
back functionu sequence containerlarda son eğeye referans döndürüyor

int main()
{
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};

	//svec[0]
	//svec.front() //ikiside aynı ama  front template ise tüm sequence containerlar için geçerli olacak.

	svec.front() += "han";
	svec[svec.size() - 1];

	svec.back() += "naz";

	print(svec);	// "Alihan","Ayse","Hasan","Selonaz"
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Container const ise yukarıdaki tüm işlemlerin return değeri const & olacak.
const vector<string>svec{"Ali","Ayse","Hasan","Selo"};

auto x= svec[0]; //GEÇERLI.
svec[0] = "kerim"; //SENTAKS HATASI

Aynı durum diğerleri içinde geçerli.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR VECTORU DOLAŞMAK
--------------------

int main()
{
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};

	for(size_t i{0}; i < svec.size(); ++i)
	{
		std::cout << svec[i] << "\n"; 
		// std::cout << svec.at(i) << "\n";  Buda kullanılabilir.
	}

	----------------------------------------------------------------------------
	//set amaçlı
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};

	for(auto iter = svec.begin(); iter != svec.end(); iter++)
	{
		*iter += "can";
	}
	
	----------------------------------------------------------------------------
	//get amaçlı
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};

	for(auto iter = svec.cbegin(); iter != svec.cend(); iter++)
	{
		std::cout << iter->length() << " ";
	}
	
	----------------------------------------------------------------------------
	//Birçok durumda range base for loop kullanılabilir

	vector<string>svec{"Ali","Ayse","Hasan","Selo"};

	for(const auto &s = svec) // string &s : svec te yazılabilir.
	{
		std::cout << s << "\n";
	}
	
	
	for(auto&&s = svec) // burası sağ taraf değil forwarding referans. Çıkarım yapılıyor.
	{
		//
	}

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RESIZE
------
Reserve ile resize karıştırılmamalı.

int main()
{
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};
	std::cout << "size = " << svec.size() << "\n";

	svec.resize(40);

	std::cout << "size = " << svec.size() << "\n"; 
	// ilk 4 öğe belli ama diğer öğeler eğer bu sınıf türündense default init ediliyor
	// aritmetik türden değerler tutan vector olsaydı, beklenen öğeler 0, pointer ise nullptr.

	svec.resize(2);
	std::cout << "size = " << svec.size() << "\n"; 
	// ilk iki öğe kaldı ve size 2 oldu.
}

Aynı örnek date sınıfı için yapıldı ve default ctor çağrılacağı görüldü. Ben yazmadım.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RESIZE IN BIR OVERLOAD U DAHA VAR. EKLEME YAPILDIĞINDA EKLENECEK DEĞERLERIN HANGI DEĞERLERLE BAŞLATILACAĞINI BELIRTIYOR.

int main()
{
	vector<int> ivec{1,2,3,4,5,6,7};
	ivec.resize(20,-1); // 1,2,3,4,5,6,7,-1,-1,-1,-1 .... -1 yapar
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SEQUENCE CONTAINERLARIN INSERT VE ERASE FUNCTIONLARI

erase in 2 biçimi var. 
1. iterator alıyor ve konumdaki değeri siliyor
2. range alıyor ve rangedekileri siliyor.

int main()
{
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};
	svec.erase(svec.begin()); // ilk konumdaki öğeyi siler
	svec.erase(svec.begin() + 1); // ikinciyi siler

	//list sınıfında bu böyle bir toplama işlemi olmayacak.bu sebeple next kullanacağız.
	svec.erase(next(svec.begin())); // beginin bir sonrasını silecek yani 2. öğe

	// Son öğe
	svec.erase(svec.end() - 1);
	svec.erase(prev(svec.end()));
	// silme işleminde diğer elemanlar kaydırılıyor.

	svec.pop_back(); // son elemanı siliyor ama return değeri yok. dezavantajı bu.


	// silme functionlarının return değeri var. Bu çok önemli.
	auto iter = svec.erase(svec.begin()); // silinen öğeden sonraki konumu tutuyor.
	std::cout << *iter << "\n";

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RANGE PARAMETRELİ ERASE FUNC

int main()
{
	vector<string>svec{"Ali","Ayse","Hasan","Selo"};
	svec.erase(svec.begin() +1, svec.end() -1 ); // ilk v son hariç hepsini siler.
	svec.erase(svec.begin(), svec.end() ); // hepsini siler
	svec.clear(); // buda sielr hepsini ve bu tercih edilir yukarıdakine göre.
}



*/