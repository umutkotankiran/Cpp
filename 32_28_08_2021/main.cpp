/*

Vectörlerden devam ediyoruz.STL in en çok kullanılan container sınıfı vector. header file vector.
kapasite değeri, size değeri var.size = capacity ise buradan sonra insert işlemi yapılınca kapasite artırılıyordu.
Burada Ctorlarına ait tablo aşağıda.Bunlar gösterildi.

vector<Elem> c					Default constructor; creates an empty vector without any elements
vector<Elem> c(c2)				Copy constructor; creates a new vector as a copy of c2 (allelements are copied)
vector<Elem> c = c2				Copy constructor; creates a new vector as a copy of c2 (allelements are copied)
vector<Elem> c(rv)				Move constructor; creates a new vector, taking the contentsof the rvalue rv (since C++11)
vector<Elem> c = rv				Move constructor; creates a new vector, taking the contentsof the rvalue rv (since C++11)
vector<Elem> c(n)				Creates a vector with n elements created by the default constructor
vector<Elem> c(n,elem)				Creates a vector initialized with n copies of element elem
vector<Elem> c(beg,end)				Creates a vector initialized with the elements of the range[beg,end)
vector<Elem> c(initlist)			Creates a vector initialized with the elements of initializer list initlist (since C++11)
vector<Elem> c = initlist			Creates a vector initialized with the elements of initializerlist initlist (since C++11)
c.~vector() 					Destroys all elements and frees the memory

Container sınıfları array hariç RAII sınıfları
Ctor kaynak edinip Dtor kaynakları geri veriyor.Dolayısıyla taşınma semantiğine aday.
Burada ciddi performans farkları oluşabilir.

En son erase func ında kaldık.

.erase(iter);			 //KONUMDAKINI ÖĞEYI SILIYOR
.erase(iterbeg,iterned); //RANGE DEKI ÖĞELERI SILIYOR

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ERASE

using namespace std;

int main()
{
	vector<string>svec;
	rfill(svec,20,rname); //vectoru doldur

	while(!svec.empty()) // vector bos olmadığı sürece dönecek
	{
		print(svec);
		
		svec.erase(svec.begin()); // her turda birinci öğe silincek
		
		//svec.pop_back(); // böyle yapsaydık son öğe silinirdi. NOT : popback return değerine sahip değil.
		
		getchar(); //her seferinde baştaki öğey isilip durduruyoruz.
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İlk ve son öğe haricindekileri silmek için içinde aşağıdakini yazmıştık
svec.erase(nex(svec.begin()), prev(svec.end());

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ATAMA İŞLEMLERİ

c = c2					Assigns all elements of c2 to c
c = rv					Move assigns all elements of the rvalue rv to c (since C++11)
c = initlist				Assigns all elements of the initializer list initlist to c (since C++11)
c.assign(n,elem)			Assigns n copies of element elem
c.assign(beg,end)			Assigns the elements of the range [beg,end)
c.assign(initlist)			Assigns all the elements of the initializer list initlist
c1.swap(c2)				Swaps the data of c1 and c2
swap(c1,c2)				Swaps the data of c1 and c2


Bir vectöre başlka bir vectorü kopaylayarak taşıyarak yada init list atayabiliriz.
bunlar atama operator funcları.

int main()
{
	vector<string>svec;
	vector<string>x{"ali","veli","can","nur","beyza"};
	rfill(svec,10,rname);
	print(svec);

	svec = std::move(x); // move assignment ile atama yapıldı
	svec = x; // copy assignment ile tama yapıldı
	//yazdırıp görebiliriz. print ile

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İNITIALIZER LIST ATAMASI VAR.
int main()
{
	vector<string>svec;
	vector<string>x{"ali","veli","can","nur","beyza"};
	rfill(svec,10,rname);
	print(svec);

	svec = {"remzi","hasan",huseyin}; // buda init list ataması
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RANGE ASSIGNMENT

Bir vectöre farklı türden bir vectorü atayamayız.Assign func ının return değeri yok ama copy asignemnt func ının return değeri *this yine.Kendisi yani.
Ama range ctor gibi range assignment ta var. Prodda çok sık kullnılıyor.

int main()
{
	vector<string>svec;
	vector<string>x{"ali","veli","can","nur","beyza"};

	list<string>mylist{"kerim","fuat","naci"};
	svec.assign(mlist.begin(), mylist.end()); // RANGE ASSIGN. farklı containerlar olmasına ramen atama range parametreden ötürü yapılabildi.
	svec.assign{"hasan","huseyin","mert"}; // INITIALIZER LIST ASSIGNMENT
	
	print(svec);
}

Farklı türden ama assign burada iteratör parametreli olduğundan bu atama gerçekleşebilir.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FILL ASSIGN DA VAR.

int main()
{
	vector<int>ivec;

	ivec.assign(20,3); // 20 adet 3. Assign ın return değeri yok.

	print(ivec);

}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

front = containerdaki ilk öğeye referans
back = son öğeye referans döndürüyor

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================

15 :00

INSERT

Vectorde her ne kadar sondan ekleme constant time ama istediğimiz yerinden de ekleme yapabiliriz.

c.push_back(elem)		Appends a copy of elem at the end
c.pop_back()			Removes the last element (does not return it)
c.insert(pos,elem)		Inserts a copy of elem before iterator position pos and returns the position of the new element
c.insert(pos,n,elem)		Inserts n copies of elem before iterator position pos and returns the position of the first new element (or pos if there is no new element)
c.insert(pos,beg,end)		Inserts a copy of all elements of the range [beg,end) before iterator position pos and returns the position of the first newelement (or pos if there is no new element)
c.insert(pos,initlist)		Inserts a copy of all elements of the initializer list initlist before iterator position pos and returns the position of the first new element (or pos if there is no new element; since C++11)
c.emplace(pos,args...)		Inserts a copy of an element initialized with args before iterator position pos and returns the position of the new element (since C++11)
c.emplace_back(args...) 	Appends a copy of an element initialized with args at the end (returns nothing; since C++11)
c.erase(pos)			Removes the element at iterator position pos and returns the position of the next element
c.erase(beg,end)		Removes all elements of the range [beg,end) and returns the position of the next element
c.resize(num)			Changes the number of elements to num (if size() grows new elements are created by their default constructor)
c.resize(num,elem)		Changes the number of elements to num (if size() grows newelements are copies of elem)
c.clear()			Removes all elements (empties the container)


int main()
{
	vector<string>svec{"nur","can","demir","avni"};
	print(svec);
	
	svec.insert(svec.begin(),"Ali"); // başlangıca Ali eklendi
	print(svec);
	
	svec.insert(next(svec.begin()),"Ali"); // baştan 2. konuma ali eklendi
	print(svec);
	
	//Nereye ekleme yaparsak o konuma eklenir ve sonrası kaydırılıyor.
	auto iter = svec.insert(next(svec.begin()),"Ali"); 
	cout << *iter <<"\n"; // Eklenen öğenin konumunu döndürür.Yani Ali.
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HER TURDA BAŞA EKLEME YAPAN KOD

ÖR:
int main()
{
	vector<string>svec{"nur","can","demir","avni","sevda"};
	vector<string> destvec;

	for(const auto & s : svec)
	{
		destvec.insert(destvec.begin(),s); // hangi konumu verirsek oraya ekler ve eklediği öğeye referans döndürür.
		print(svec);
		getchar();
	}
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EKLEMEYİ RANGE OLARAK YAPABİLİRİZ:

int main()
{
	int a[] = {2,3,5,7,11};
	vector<int> ivec {10,20,30,40,50};

	print(ivec);
	ivec.insert(ivec.begin() + 2 , begin(a),end(a)); // begin +2 konumuna, bir range deki öğeleri insert etti.
	print(ivec);
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FILL INSERT

int main()
{
	int a[] = {2,3,5,7,11};
	vector<int> ivec {10,20,30,40,50};

	print(ivec);
	ivec.insert(ivec.begin() + 2 , 5,77); // begin + 2 konuma, 5 tane 77 ekledik.
	print(ivec);
}

========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================
========================================================================================================================================================================


CONTAINER EMPLACE FUNCTIONLARI

Verim için çok önemli.

Heapte allocate edilen bir alanımız var olsun.Bir şekil çizildi.3 adet eleman var. yani size 3. Bular zaten hayatta.
Pushback veya herhangibir insert func çalıştıktan(hangisinin olduğu önemsiz) sonra bizim nesnemizin 4. eleman olaran hayata başladığını düşünelim(son konumda).


Burada 3 ihtimal var.

1. Eklenen nesne kopyalama yoluyla eklenecek yani copy ctor çağrılacak.Yani eklenen bellek bloğu this adresi olarak kullanıp sınıfın copy ctoru çağrılacak.

2. Bu nesne bir sağ taraf değeri ise yani birdaha kullanılma ihtimali yoksa ya da move kullanılarak bu gözden çıkarılmışsa o zaman bunun için move ctor çağrılacak.
   Copy ile move arasında çok büyük performans farkı olabilir

3. Emplace ne yapıyor : Sen bana ctora göndereceğinm argümanları gönder, ben containerın o nesne için kullanacağı bellek alanında doğrudan ctoru çalıştırayım.
   Yani nesneyi ilgili bellek alanında hayata getiriyor.Copy ellision gibi.

Perfect forwarding ile yapıyor bunu.

int main()
{
	vector<Date> dvec;
	Date mydate(12,4,1987);
	dvec.push_back(Date::random()); // Burada pushback in sağ taraf ref parametreli overload u çalıştı çünkü sağ taraf değeri date::random
	-------------------------------------------------------------------------------------------------------------------------------------------------------------

	dvec.push_back(mydate); // kopyasını çıkarttı burada

	-------------------------------------------------------------------------------------------------------------------------------------------------------------

	dvec.emplace_back(4,4,1944);	// Bu ise ilgili bellek alanında doğrudan nesneyi oluşturdu.Dolayısı ile containera koyacağımız nesneyi nasıl oluşturacağımız
					// baştan belliyse, insert veya push_back push_front gibi funcları çağırmak yerine, emplace funclarını çağırırsak, emplace func
					// verdiğimiz argümanları kullanarak containerda verdiğimiz alanda nesneleri doğrudan construct edecek.
					// push_back e karşı emplace_back var. 
					// push_front a karşılık emplace_front var(buarada vectorde değil list, deque de vardı push_front).
					// insert için ise doğrudan emplace var.


	-------------------------------------------------------------------------------------------------------------------------------------------------------------

	dvec.emplace(dvec.begin(),1,1,2001); //burası emplace olduğundan konum girdik.Yukarıdaki emplace backti
	 									// nesneyi oluşturup kopyalama yerine doğrudan ilgili yerde default ctor

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Tercih Sırası nasıl olmalı

1 Copy ellision (ideali bu)
2 Move
3 Copy

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

RESIZE İLE HEM ATAMA HEM SİLME YAPILABİLİR.

int main()
{
	vector<int> ivec(100);

	ivec.erase(ivec.begin() + 16); // 16. öğe silinecek.

	ivec.resize(20); // yapılabilir. Boyutu 20 yapınca, 20 den sonrası yok artık :D

	------------------------------------------------------------------------------------------------------------------------------------------------

	size_t idx  = 34;
	ivec.erase(ivec.begin() + idx, ivec.end()); // bu şeklilde silinir. NOT : Erase return değeri var ama resize return değeri yok.
	ivec.resize(idx); // bunu yaz.size ını küçülterek silme işlemi yaptı denebilir.

	------------------------------------------------------------------------------------------------------------------------------------------------

	auto iter = ivec.begin() + 20;
	ivec.erase(iter,ivec.end()); // 20 den sonrasını sildik.

	ivec.resize(iter - ivec.begin()); // yine boyutunu 20 ye resize etti.
		
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

SWAP 

Global swap veya member swap ile swap yapılınca container elemanlarına erişir yani containerın tuttuğu pointerları takas eder.

int main()
{
	vector<int> odds{1,3,5,7,9};
	vector<int> evens{2,4,6,8,10};

	swap(odds,evens); // global swap func
	print(odds);
	print(evens);

	------------------------------------------------------------------------------------------------------------------------------------------------

	odds.swap(evens); // Buda olur aynı şey.
	evens.swap(odds); // Buda olur yine.

}

Bu normal takas func değil. Containerın elemanlarına yani pointerları takas ediyor.
Öğeler durduğu yerde duruyor ama pointerlar takas ediyor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

DATA - ÇOK ÖNEMLi
Vectördeki öğeler dinamik bellek bloğunda contigues halde duruyolar. Biz dinamik bell . blok. ilk öğenin adresini
bilirsek ve dinamik dizinin size bilgisini bilirsek, bir C apisine bu adresi ve size bilgisini argüman olarak gönderebiliriz.
Bunun için ilk öğenin adresine ihtiyaç var ve bunu veren function data. Sadece data ile alırız demiyoruz tabiki.

void display_array(const int *p, size_t n)
{
	while(n--)
	{
		std::cout << *p++ << " ";
	}
	std::cout << "\n";
}

int main()
{
	vector<int> ivec{2,4,7,9,1,6};
	ivec.data(); // 2 overload u var. Hem get hem set için, int * ve const int *

	display_array(ivec.begin() .... ); // bu şekilde yazamayız çünkü const int * parametresi var ve biz argüman olarak iteratör gönderiyoruz.

	display_array(ivec.data(),ivec.size()); // bu şekilde yazılabilir.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

BAŞKA BIR C APISI OLSUN

void increment(int *p, size_t n) 
{
	while(n--)
	++ *p++; // dikkat
}

int main()
{
	vector<int> ivec{2,4,7,9,1,6};

	display_array(ivec.data(),ivec.size()); 
	increment(ivec.data(),ivec.size());

	//Sadece Data kullanılacak diye birşey yok !!!
	display_array(&ivec[0],ivec.size()); // bu şekilde yazılabilir.
	
	display_array(&*ivec.begin(),ivec.size()); // bu şekilde yazılabilir.
	
	birsürü yazım şekli olabilir.
	
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Kısaca tüm funclara baktık kısaca özet geçildi.

ivec. yazıp karşına çıkanları bilip bilmediğini kontrol et.

==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================
==================================================================================================================================================================


ALGORTİMALAR - SİLME ARLGORİTMALARI

Başlıkta oksimoronik bir durum var.Algoritmalar silme işlemi yapamazlar :D:D
Neden?
Algoritma parametresi iterator çünkü.

template <typename Iter, typename T>
void remove(iterator beg, iterator end, const T& val)
{
	*beg ; // belirli iterator konumundaki nesneye erişir
	iter_swap(iterator begin, iterator end ) 
	biz buna en fazla bir containerdaki iteratörleri argüman olarak geçebiliriz.Bu algoritma ne yapabilirz?
	iterator alarak belirli iteratör konumudaki nesneye erişirler veya bu nesneleri swap edebilirler.
	bunun dışında bu containera ekleme veya silme yapamazlar.
	
	Containera ekleme veya silme işlemi yapmak için mecburen containerın member funclarını çağıracağız.
	bu durumda container parametreli function yazacağız iterator parametreli değil.
			
	SONUÇ :
	İterator konum tutan bir değişken, iterator containerı değiştiremez.
	Container değiştirmek için container nesnesinin kendisine ihtiyacımız var.

}

Nasıl oluyorda STL algoritmaları silme işlemi yapıyor gibi içinde remove geçen silme algoritmaları var.
remove
remove_if
unique        bunlar silme algoritmaları

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE
------
Bu algoritma bizden bir range ve silinecek olan değeri istiyor.

int main()
{
	ivector<int> ivec{1,2,3,4,5,2,7,8,9};
	//Bu vectorden 2 değerlerini silelim.Bunun için erase ve remove algoritmaları var ama tahmin edilenin dışında bir iş yapıyor.
	// memfunc func olanının adı erase global olanının adı remove.

	remove(begin(ivec),end(ivec),2); // container member func erase. global remove
	// bunu aslında silmeyecek peki ne yapıyor ?
	// Öğeler silinmiş gibi davranıp containerdaki elemanları kaydırıyor.
	// 1,2,3,4,5,2,7,8,9
	// 1,3,4,5,7,8,9,* *     Burada 2 tane daha öğe var aslında. fiilen bir silme işlemi yok. remove çağrıldıktan sonraki boyut ile önceki boyut aynı.

	//Return değeri logic end konumu.Bunlar silinmiş olsaydı containerda belirtilen öğeler kalacaktı. 
	// Logic end silinmemiş ilk öğeden sonraki iterator konumu	veriyor. yani 9 dan sonraki konumu.
}

LOGIC END IN AVANTAJLARI
Logic end elde edildiğinde, logic end ile container begin konumunu beraber kullanıp bir range oluşturunca silinmemiş öğelerin range ini kullanmış oluruz.
Yani gerçekten silinmeyen ama silinmiş gibi görünenlere silinmiş muamelesi yaparak, silinmemişleri dolaşabiliriz.

Logic end ile gerçek end i bir iterator range i yapıp, bunu containerın silme func ına argüman olarak göndererek,bu değerlerin tamamen silinmesini
sağlayabiliriz.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	ivector<int> ivec{1,2,3,4,5,2,7,8,9};
	
	cout << ivec.size()<<"\n";
	auto iter = remove(begin(ivec),end(ivec),2);  // remove un return değeri logic end
	cout << ivec.size()<<"\n";
	// şuanda container sıze ı değişmedi.

	print(ivec.begin(),iter);  // silinmemiş kısmı yazdırır.

	cout << "silinmemis ogelerin sayisi : "<< distance(ivec.begin(), iter)<< "\n"
	cout << "silinmis ogelerin sayisi : "<< distance(iter,ivec.end()) << "\n"

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE ERASE
AMAÇ GERÇEKTEN BU DEĞERLERİ SİLMEK İSE C++20 YE KADAR MEŞHUR IDIYOMU KULLANIYORUZ

int main()
{
	ivector<int> ivec{1,2,3,4,5,2,7,8,9};
	
	std::cout << "size = " << ivec.size() << "\n";
	ivec.erase(remove(ivec.begin(), ivec.end(),2), ivec.end()); // meşhur idiyom bu.
	std::cout << "size = " << ivec.size() << "\n";  // artık size değeride düştü.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

1 ÖRNEK DAHA

 int main()
{
	vector<string> svec {"ali","veli","nur","ali","sami","ali,"gurbuz"};
	
	print(svec);
	svec.erase(remove(begin(svec),end(svec),"ali"),svec.end());
	print(svec); // ali ler gitti 
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

C++20 DE BUNUDA AYRI FUNC ŞABLONU YAPTILAR. !!!!!!!!!!!!!!!!
Farklı farklı specializationları var.Argüman olarak vegin ve end değil nesnenin kendisini gönderiyoruz !!!!!!!!!!!!!!

auto n = erase(svec,"ali"); //Artık böyle yapılabiyor kendi içinde erase remove idiyomu kullanıyor. svec in kendisini gönderdik.
//return değeri silinen öğe sayısı

print(svec);
std::cout << n << "eleman silindi\n";

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

YANLIŞ ANLAŞILAN KISIM
int main()
{
	vector<string> svec {"ali","veli","nur","ali","sami","ali,"gurbuz"};

	print(svec);

	auto iter = remove(svec.begin(),svec.end(),"ali");

	print(svec.begin(), iter); // silinmemişler
	print(iter, svec.end());  // Burada 3 ali yazacak diye birşey yok. Burası yanlış anlaşılıyor.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE_IF

Bir predicate alıyor ve onun true döndürdüğü değerleri siliyor.

int main()
{
	vector<string> svec;
	rfill(svec,100,rname);

	print(svec);
	size_t len;

	std::cout << "uzunluğu kac olanlar silinsin: ";
	cin>>len;

	svec.erase(remove_if(svec.begin(), svec.end(),[len](const string&s){ return s.size() == len;}),svec.end());
	// remove_if ifadenin değeri logic end

	print(svec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ERASE_IF
C++20 de geldi.Return değeri silinen öğe sayısı.

int main()
{
	vector<string> svec;
	rfill(svec,100,rname);

	print(svec);
	size_t len;

	std::cout << "uzunluğu kac olanlar silinsin: ";
	cin>>len;

	auto n = erase_if(svec,[len](const string&s){ return s.size() == len;});

	print(svec);
	std::cout << "silinen oge sayisi = " << n;

}


-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE

Range teki ardışık aynı değere sahip öğelerden bir tane bırakıyor.
11234444555678997766554433 -- >  12345678976543   BURAYI YAZ 

Unique öğelerin silineceğinin kararını vermek için == kullanıyor.
unique te logic silme yapıyor.Unique in return değeri logic end. Yukarıda 3 ten sonrası. Fiziksel silme için logic end ile gerçek end i 
container ın erase func ına argüman göndermemiz gerekiyor.

int main()
{
	vector<int> ivec;
	rfill(ivec,300,Irand(0,3));
	
	print(ivec);

	ivec.erase(unique(ivec.begin(), ivec.end()), ivec.end());
	// unique logic end döndürüyor.
	print(ivec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

HER ÖĞEDEN BIR TANE KALMASINI ISTIYORUZ.

İlk önce sort edip ondan sonra unique yapılır.

int main()
{
	vector<int> ivec;
	rfill(ivec,60,Irand(0,3));
	print(ivec);

	sort(ivec.begin(), ivec.end());
	ivec.erase(unique(ivec.begin(), ivec.end(),ivec.end());
	print(ivec);
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQEU İN DİĞER OVERLOAD U

Burada binary predicate verilecek. Bu sefer aynı olmayanlar silinecek :D

int main()
{
	vector<int> ivec;
	rfill(ivec,300,Irand(0,10000));
	print(ivec);

	ivec.erase(unique(ivec.begin(), ivec.end(), [](int x, int y){return x % 2 == y % 2;}),ivec.end());

	print(ivec);
}

Çiftler ve tekler yanyana gelmeyecek şekilde yazdık.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	vector<string> svec;
	rfill(ivec,300,rname);

	unique(ivec.begin(), ivec.end(), [](const auto &x,const auto &y){return x.size() == y.size();}),svec.end());
	print(ivec);

}

2 stringin uzunluğunun eşit olma şansı kalmadı.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

REMOVE COPY 

Kopyalayarak silme işlemini yapıyor.Silinecek öğeleri kopyalamıyor. Geçen ders görülmüştü.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE COPY
Ardışık öğelerin 1 tanesini kopyalıyor.


int main()
{
	vector<int>ivec;
	list<int> ilist;
	rfill(ivec,100,Irand{0,3});
	
	unique_copy(ivec.begin(), ivec.end(), back_inserter(ilist));

	print(ilist);
}

// ilistte ardışıklardan olmayacak.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

MÜlakat sorusu.

int main()
{
	vector<string> svec;
	rfill(svec, 20, rname);
	print(svec);

	std::cout << "Silinecek ismi girin\n";
	string name;

	cin >> name;

	if(auto iter = find(svec.begin(), svec.end(),name) ; iter != svec.end())
	{
		svec.erase(iter);
		print(svec);
	}
	else
	{
		std::cout << "aranan deger bulunamadi\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

SONDAN İLK ÖĞEYİ SİLMEK İÇİN REVERSE ITERATOR

int main()
{
	vector<string> svec;
	rfill(svec, 20, rname);
	print(svec);

	std::cout << "silinecek ismi girin\n";
	string name;
	cin >> name;

	if(auto iter = find(svec.rbegin(), svec.rend(),name) ; iter != svec.rend())
	{
		svec.erase(iter.base() - 1);
		print(svec);
	}
	else
	{
		std::cout << "aranan deger bulunamadi\n";
	}
}

MOLA

Moladan sonra bir soruya uzun uzun cevap verildi.

=================================================================================================================================================================
=================================================================================================================================================================
=================================================================================================================================================================
=================================================================================================================================================================
=================================================================================================================================================================

BUGÜNKÜ ALTBAŞLIKLAR BİRAZ FARKLI KONULARDA

STANDART FUNCTION OBJECT
SIRALAMAYA İLİŞKİN ALGORİTMALAR (SIRALAMA DEMİYORUZ)
ISTREAM_ITERATOR SINIFI

=================================================================================================================================================================
=================================================================================================================================================================
=================================================================================================================================================================

STANDART FUNCTION OBJECT

template <typename T>
struct Less{
	bool operator()(const T&x, const T&y)const
	{
		return x < y;
	}
};

int main()
{
	Less<int> a;
	a(10,2); // 10 < 2 ye eşdeğer false

	cout << boolalpha << a(10,2) << "\n"; // false
	cout << boolalpha << a(1,2) << "\n"; // true
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

KISALTABILIRIZ KODU

int main()
{
	cout << boolalpha << Less<int>{}(1,2) << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİNİN BİZE NE FAYDASI OLUR
STL ALGORİTMALARINI DÜŞÜNELİM. ALGORİTMA AŞAĞIDAKİ GİBİ OLSAYDI.
Aşağıdaki functiona gönderilen argüman less<int> olsaydı ve bu gönderdiğim değerlerde int türünden olsaydı,
aslında *deque < *(deque + 1) işlemi yapılacaktı. 

template <typename Iter, typename F>
void func(Iter beg, Iter end, F pred) 
{
	pred(*beg, *(beg + 1));
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

FUNCTIONAL HEADER FILE TANIMLANMIŞ BUNLAR
mesela greater da

struct Greater{
	bool operator()(const t&x, const t&y)const
	{
		return x > y;
	}
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
PLUS  

struct Plus{
	bool operator()(const t&x, const t&y)const
	{
		return x + y;
	}
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------
EQUAL_TO

struct Equal_to{
	bool operator()(const t&x, const t&y)const
	{
		return x == y;
	}
};


YANİ BİZDEN BİNARY PREDİCATE İSTEYEN BİR ALGORİTMAYA 2 PARAMETRELİ FUNCTION ÇAĞRI OPERATOR FUNC SUNAN FUNCTION NESNELERİNDEN BİRİNİ(EQUAL_TO, PLUS ... )
GEÇEBİLİRİZ.


BU FUNCLARIN LİSTESİ AŞAĞIDAKİ GİBİ
------------------------|------------------------
negate<type>()			|		- param
plus<type>()			|		param1 + param2
minus<type>()			|		param1 - param2
multiplies<type>()		|		param1 * param2
divides<type>()			|		param1 / param2
modulus<type>()			|		param1 % param2
equal_to<type>()		|		param1 == param2
not_equal_to<type>()		|		param1 != param2
less<type>() param1		|		< param2
greater<type>()			|		param1 > param2
less_equal<type>()		|		param1 <= param2
greater_equal<type>()		|		param1 >= param2
logical_not<type>()		|		! param
logical_and<type>()		|		param1 && param2
logical_or<type>()		|		param1 || param2
bit_and<type>()			|		param1 & param2
bit_or<type>()			|		param1 | param2
bit_xor<type>()			|		param1 ^ param2


Bunlar STL in functional header file içerisinde.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖRNEK:

int main()
{
	vector <int> ivec;
	rfill(ivec,100,Irand(0,10000));
	print(ivec);

	sort(ivec.begin(), ivec.end()); // SORT ALGORITMASININ BIR OVERLOADU 
	//sort(ivec.begin(), ivec.end(),less<int>{}); // BUNUNLA YUKARIDAKI AYNI ŞEY.YUKARIDAKI ILE BIR FARK YOK.
	print(ivec); // ikisinide test ettik yanı sonuç
	
	
	Greater kullanırsak
	sort(ivec.begin(), ivec.end(),greater<int>{}); // BU SEFERDE BÜYÜKTEN KÜÇÜĞE SIRALANDI. // SORT ALGORITMASININ DIĞER OVERLOADU.

	---------------------------------------------------------------------------------------------------------------------------------------------------

	C++11 E KADAR <> İÇİNE TÜR YAZMAK ZORUNLUYDU ŞİMDİ TRANSTPARENT OBHECT GELDİ

	sort(ivec.begin(), ivec.end(),greater{}); //BÖYLEDE YAZIALBİLİR

	---------------------------------------------------------------------------------------------------------------------------------------------------
	
	vector <int> x;
	vector <int> y;
	rfill(x,100,Irand(0,10000));
	rfill(y,100,Irand(0,10000));

	transform(x.begin(), x.end(), y.begin(), x.begin(),plus{}); // x'e x + y toplamı gönderiliyor. plus<int> te yazılabilirdi.

	---------------------------------------------------------------------------------------------------------------------------------------------------

	BU BIRAZ ZORLAMA BIR ÖRNEK.

	vector <int> x;
	rfill(x,100,Irand(0,10000));

	for(auto &i : x)
	{
		i = -i;	
	}
	print(x);

	---------------------------------------------------------------------------------------------------------------------------------------------------
	
	YUKARIDAKINI YAPTIK ASLINDA BURADA

	vector <int> x;
	rfill(x,100,Irand(0,10000));

	transform(x.begin(), x.end(), x.begin(), negate{ });
	print(x);
	
	---------------------------------------------------------------------------------------------------------------------------------------------------
		
	vector <int> ivec;
	rfill(x,100,Irand(0,1'000'000));
	print(ivec);

	auto iter = max_element(ivec.begin(),ivec.end()); // max_element bi range deki en büyük öğenin konumunu döndürüyor. 
														// Karşılaştırma yaparken less kullanıyor.

	cout << "max = " << *iter << " ve " << iter - ivec.begin() << "indisli oge\n";  //distance ta kullanılabilirdi.

	---------------------------------------------------------------------------------------------------------------------------------------------------

	KARŞILAŞTIRMADA KÜÇÜK DEĞIL, BÜYÜK ALSAYDI

	auto iter = max_element(ivec.begin(),ivec.end(),greater{});

	cout << "max = " << *iter << " ve " << iter - ivec.begin() << "indisli oge\n";  // max dedik ama max yerine min bulundu.

	---------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto iter = max_element(ivec.begin(),ivec.end(), [](int a, int b){ return ndigit(a), < ndigit(b); });
	// buyuktur küçüktür basamak sayısına göre oldu

	---------------------------------------------------------------------------------------------------------------------------------------------------

	sort(ivec.begin(),ivec.end(),greater{});
	sort(ivec.begin(),ivec.end(),[](int a, int b){return a > b;});


}

=======================================================================================================================================================
=======================================================================================================================================================
=======================================================================================================================================================
=======================================================================================================================================================
=======================================================================================================================================================

OSTREAM ITERATOR ADAPTER SINIFI
-------------------------------
Bunun kodunu yazıp göreceğiz. İlk önce copy nin kodunu yazmamız gerekecek konunun iyi anlaşılması için.

template <typename InIter, typename OutIter>
OutIter Copy(InIter beg, InIter end, OutIter destbeg)
{
	while(beg != end)
	{
		*destbeg++ = *beg++;
	}
	return destbeg;
}

// ALTTAKI OSTREAMITERATOR KISMINA GELMEDEN MAINDEKI YAZILANLARI OKU !!!!!!!!!!!!!!!
//BACK INSERTERA BENZIYOR KOD

template <typename T> 
class OstreamIterator{
public:
	OstreamIterator(std::ostream &os, const char *p = "") : mos{os}, mp{p} {} // default olarak boşluk yok ama biz " " verirsek 2. argümanı boşluk koyar.
	OstreamIterator& operator++() { return *this; }
	OstreamIterator& operator++(int) { return *this; } // bu ref döndürmüyordu ama bu örnek için yine & olacak
	OstreamIterator& operator*() { return *this; } // bu ref döndürmüyordu ama bu örnek için yine & olacak
	OstreamIterator& operator=(const T &val)
	{
		mos << val << mp;
		return *this;
	}
private:
	std::ostream &mos; 
	const char *mp;
};


using namespace std;
int main()
{
	
	vector<int> ivec{1,5,7,9,2,0,3,6};
	// Öyle bir çağrı yapacağızki bir containerın öğeleri bir çıkış akımına yazacak.
	// ŞIMDI OSTREAMITERATOR KODUNA DÖN !!!!!!!!!!!!!!!!!!!!!
	
	// OstreamIterator<int>{cout}; test için yazdık bunu

	Copy(ivec.begin(), ivec.end(), OstreamIterator<int>{cout," "}); // containerdaki öğeleri cout a gönderdik aslında
	// boşluk verilmezse default parametre den gelen çalışır.
	
	-------------------------------------------------------------------------------------------------------------------

	Bunu bir dosya içinde kulanabiliriz.
	fstream header file eklenecek.

	ofstream ofs{"out.txt"};
	Copy(ivec.begin(), ivec.end(), OstreamIterator<int>{ofs," "});
	
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA YUKARIDAKİNİN ORIGINALI KULLANILIYOR

include nutility algorithm ....

int main()
{
	vector<string> svec;
	
	rfill(svec,20,rname);

	copy(svec.begin(), svec.end(), ostream_iterator<string>{cout," "}); // vectorde string olduğundan burasıda string açılımı
	copy(svec.begin(), svec.end(), ostream_iterator<string>{cout,"\n"}); //veya böyle

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNU KULLANMAK IÇIN INSERTERLAR OLMALI. YANI MESELA DATE SINIFININ INSERTERA VAR. BU DURUMDA DATE IÇINDE BUNU KULLANABILIRIZ

int main()
{
	vector<Date> dvec;

	rfill(svec,20,rname);

	copy(dvec.begin(), dvec.end(), ostream_iterator<Date>{cout,"\n"});
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------


GENERATE

bir iterator range i functor ın return değerine göre dolduruyor.

int main()
{
	vector<string> svec(20);

	generate(svec.begin(), svec.end(), rname); // range e return değer olan string atanacak. rname den gelen değerler atanacak rang e

	generate(svec.begin(), svec.end(), []{return rname() + ' ' + rfname();});

	print(svec);
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

GENERATE_N
Yukarıdakinden farkı kaç eleman olacağını belirtiyor.

int main()
{
	vector<string> svec(20);

	generate_n(svec.begin(), 20,rname);
	print(svec);

	----------------------------------------------------------------------------------------------------------------

	generate_n(back_inserter(svec), 20,rname); // iki türlüde olur.
	print(svec);

	----------------------------------------------------------------------------------------------------------------

	generate_n(ostream_iterator<string>{cout},20,rname); // 20 tane ismi standart çıkış akımına yazdı.

	generate_n(ostream_iterator<string>{cout,"\n"},20,rname); // newline vererek yazdı.

	generate_n(ostream_iterator<string>{cout," "},20,rname); // boşluk vererek yazdı.

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Mülakat sorusu
ÖYLE BIR KOD YAZILACAKKI AŞAĞIDAKI BOŞLUKLAR 1 E INDIRILECEK
BUNU UNİQUE İLE YAPARIZ.

int main()
{
	string str;

	std::cout << "bir yazi girin\n";
	getline(cin, str);					// ali		veli	 hakan	 murat	 ayse	mehmet
	cout << '|' << str << "|\n";


	// AŞAĞIDAK FUNC İLE MÜMKÜN
	str.erase(unique(str.begin(), std.end(), [](char c1, char c2){return isspace(c1) && isspace(c2);}),str.end()); 
	//str.erase ... den önce logic silme durumunda. bunu str.erase siliyoruz.

	cout << '|' << str << "|\n";
}


-------------------------------------------------------------------------------------------------------------------------------------------------------------------

OSTREAM ITERATOR SINIFI İLE BİR DOSYAYADA YAZABİLİRİZ.

int main()
{
	std::ofstream ofs{"out.txt"};

	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	generate_n(ostream_iterator<string>{ofs,"\n"},10000,[]{return rname() + ' ' + rfname();});

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR ÖRNEK DAHA

int main()
{
	std::ofstream ofs{"out.txt"};

	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi\n";
		exit(EXIT_FAILURE);
	}

	generate_n(ostream_iterator<string>{ofs,"\n"},10000,Date::random);
	// ofs yerine cout yazsaydık bu standart çıkış akımına yazdıracaktı.
}


MOLA

====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================
====================================================================================================================================================================

SIRALAMA / SORT ALGORİTMALARI
-----------------------------
Üretimdeki en sık kullanılan algoritmalar sıralamaya ilişkin algoritmalar.Algorithm header file da birsürü göreceğiz. Sort algorithms diye geçiyor.
Sıralamaya ilişkin algoritmalar.Sadece sıralama algoritmasından bahsetmiyoruz yani.

sort, partial_sort,	stable_sort, nth_element, partition, stable_partrition, is_sorted, is_sorted_until ...

Yukarıdakiler sıralamaya ilişkin algoritmalar
Bunlara heap algoritmalarda eklenebilir

make_heap, is_heap, push_heap, pop_heap, sort_heap

Bunlar random access iteratör isteyen dolayısı ile random access iterator rangeleri üstünde kullanılabilen algoritmalar. 

STL containerlarından
vector, string, array, c aray, deque üzerinde kullanabiliriz.

List sınıfı iteratörleri bidirectional iterator olduğundan sort algoritmasıyla bir bağlı liste sort edilemez.
Zaten list in kendi sort functionu var.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

SORT FUNCTIONUN 1. OVERLOAD U LESS FUNCTOR INI KULLANIYOR.

int main()
{
	int a[100];

	generate(begin(a), end(a),Irand{0,1000});
	print(begin(a), end(a));
	
	-------------------------------------------------------------------------------------------------------------------------------------	
	
	sort(begin(a),end(a));		// küçükten büyüğe sıraladı
	print(begin(a), end(a));
	
	-------------------------------------------------------------------------------------------------------------------------------------

	sort(begin(a),end(a),greater{}); //functional header file içerisinde. Büyükten küçüğe sıraladı
	print(begin(a), end(a));

}

Sort algoritması nlogn karmaşıklığında average case de.
Derleyicilerin STL implementasyonları tipik olarak günümüzde introsort denen bir algoritma kullanıyorlar.Doğrudan quick kullanmıyorlar.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	vector<Date>dvec;

	generate_n(back_inserter(dvec), 1000, Date::random);
	sort(dvec.begin(), dvec.end());
	
	//sort(dvec.rbegin(), dvec.rend()); // büyükten küçüğe sıralar. rbegin rend var dikkat!!!!
	//sort(dvec.begin(), dvec.end(),greater{}); // büyükten küçüğe sıralar yine :D:D

	copy(dvec.begin(),dvec.end(),ostream_iterator<Date>{ofs,"\n"}); // tarihler küçükten büyüğe sıralı.

	-------------------------------------------------------------------------------------------------------------------------------------

	//sıralama kriteri yazıyoruz şimdi.

	auto dcomp = [](const Date& dx, const Date &dy){
		return dx.month_day() < dy.month_day() || dx.month_day() == dy.month_day() && dx.month() < dy.month();
	};
	
	sort(dvec.begin(), dvec.end(),dcom); // Ayın gününe göre sıralıyor.

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi";
		exit...
	}

	copy(dvec.begin(), dvec.end(), ostream_iterator<Date>{ofs,"\n"});

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

PARTIAL SORT
------------
Diyelim ki en genç 20 kişiyi bulmamız gerekiyor.
Interface biraz tuhaf.
1. ve 3. parametreye range in begin ve end iteratorler geçiliyor ama ortadaki parametreye ilk kaç tanesi sıralı olacaksa onun end konumunu geçiyoruz !!!!!!

int main()
{
	vector <Date> dev;
	generate_n(back_inserter(dvec), 1000, Date::random);

	partial_sort(dvec.begin(), dvec.begin() + 10, dev.end()); // ILK 10 TANESINI SIRALADI. SONRASI SIRALI DEĞIL

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi";
		exit...
	}
	//dosyayada yazırabiliriz. burada copy kodunu yazmadık dosyaya yazdırmak için

	print(dvec,"\n",ofs);

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

En yaşlılarıda bulabiliriz.Bu tür sıralama functionlarında predicate overloadu var.

partial_sort(dvec.begin(), dvec.begin() + 10, dev.end(), greater{}); // En yaşlı 10 tanesi bulundu

--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

STABLE SORT

Sıralamadan önce sıralama kriterine göre daha önde olan öğeler sıralamadan sonra izafi yerleri korunacak.
Doğrudan bir problem üzerinde bakılacak. C de anlatılıyor.Çok Çok önemli.

STABLE SORT : SIRALAMADAN ÖNCE SIRALAMA KRİTERİNE GÖRE DAHA ÖNDE OLAN ÖĞELER, SIRALAMADANSONRA İZAFİ YERLERİ KORUNACAKLAR.
STABLE SORT OLDUĞUNDA, AYNI DEĞERE SAHİP ANAHTARLAR BİRARAYA TOPLANACAKLAR AMA BUNLAR SIRALAMADAN ÖNCEKİ İZAFİ KONUMLARINI KORUYACAKLAR.

#include ...
#include <iomanip>

using namespace std;

using na_pair = std::pair<std::string, int>;

int main()
{
	vector<na_pair>vec; //isim ve yaş gibi.

	generate_n(back_inserter(vec),100'000,[]{return na_pair{rname(),Irand{10,50}()};}); //pair CTAD ile tür beliertmeden de kulanılabilridi.

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi";
		exit...
	}

	// bu aşamada aslında ilk önce yazdırma işlemine bakıldı. osfs<<left kısmı var aşağıda ilk önce oraya bakıldı. Sonra burası :D:D:D

	// biz pairleri pairin karşılaştırma operatörünü özellikle kullanmadan isimlerine göre sıralayacağız.İsimlerine göre sıralayınca 
	// yaşları sıralı olmayacak.Aşağıdakini yapınca istediğimiz gibi sıralamış olacak.

	sort(vec.begin(), vec.end()); // sonuca bak.

	--------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Biz bir nedenden dolayı bunu sadece isme göre sıralamış olacağız.

	STL in kendi sortunu çağırırsak

	sort(vec.begin(), vec.end(), [](const auto &p1, const auto &p2){ // Burada pairleri isimlerine göre sıraladık yani yaşları kendi içinde sıralı değil.
		return p1.first < p2.first; });								 // Problemde burada başlıyor.16 yaşındaki kişiler içinde abdi hep daha önce çünkü alfabetik sıraladı.

	// artık 10 yaşındakiler alfabetik sırada değil ama izafi sıra bozulmuş.

	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Biz bu veri yapısını bu haldeyken yaşlarına göre sıralasam, o zaman alfabetik sıra bozulur mu ? bu garantiyi vermesi için sıralama algoritmasının stable olması gerekiyor.
	// Siralamadan önce siralama kriterine göre daha önde olan öğeler, siralamadan sonra izafi yerleri korunacaklar.
	// 16 Abdi metinden daha önce geliyor. Sıralamadan sonrada izafi olarak 16 yaşlar arasında abdi metinden önce gelecek.
	// Bu noktada zaten bu veri yapısı sıralı.Bir üstte sıralandı. Biz bu sıralananları stable olarak sıralayacağız daha iyhi görmek için. doğrudan stable sort
	// yapmayacağız

	stable_sort(vec.begin(), vec.end(), [](const auto &p1, const auto &p2){ // Burası artık stable. Sıralamaya bakılırsa sıralamadan önceki izafi sıra kalıyor.
		return p1.second < p2.second; }); // Dikkat!!! yaşlara göre sıralandı.	
	
	--------------------------------------------------------------------------------------------------------------------------------------------------------------

	ofs << left;

	for(const auto &[name, age] : vec)
	{
		ofs << setw(20) << name << " " << age << "\n"; // setw iomanip içinde var.
	}

}

Bunların iteratör kategorilerini belirtmiyoruz zamandan ötürü.
Partial sort ve sort random access iterator istiyor.
Stable sort bidirectional iterator.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------

NTH_ELEMENTH

N. elemana göre partsiyon yapıyor. Sıralama yapıldığında N. sıradakiler yerine geçiyor, sonrakiler ondan daha büyük, öncekiler daha küçük oluyor.
Diğerleri kendi içinde sıralanmıyor.Ama gertçekten sıralansaydı mesela 500. öğe gösterdiği öğe olacaktı

int main()
{
	vector<int> ivec(1000);
	generate(ivec.begin(), ivec.end(),Irand{0,10000});

	nth_elementh(ivec.begin(),ivec.begin() + ivec.size() / 2 ,ivec.end()); // 500 indisli elemanlar yerini bulacak.

	nth_elementh(ivec.begin(),ivec.begin() + ivec.size() / 2 , ivec.end(), greater{}); // büyükten küçüğe arama kriteri oldu şimdide
																			

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi";
		exit...
	}

	print(ivec,"\n",ofs);
																			
}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------------------------------------------------

PARTITION ALGORTİMASI

Bir range i sağlayanlar ve sağlamayanlar olarak ikiye ayrılır.
return değeri koşulu sağlamayanlar içinde ilkinin konumu. O(n) karmaşıklığında bir algoritma.

int main()
{
	vector<Date> dvec;
	rfill(dvec, 100,Date::random);

	// koşulu sağlayanlar bir tarafa sağlamayanlar bir tarafa.
	//aşağıda şubat ayları başa diğer aylar diğer yere ama şubatlar kendi i,çinde sıralı değil. İzafi sıra korunmuyor.
	auto iter = partition(dvec.begin(), dvec.end(), [](const Date &x){ return x.month() == 2;});

	//auto iter = partition(dvec.begin(), dvec.end(), [](const Date &x){ return x.month_day() == 6;}); // buda olabilirdi.
		
	if(iter != dvec.end())
	{
		cout << "kosulu sağlamayan ilk tarih : " << *iter << " ve indexi " << distance(dvec.begin(),iter) << "\n";  // BURADA PARTITION POINTI YAZDIK.
	}

	std::ofstream ofs{"out.txt"};
	if(!ofs)
	{
		std::cerr << "out.txt dosyasi olusturulamadi";
		exit...
	}

	print(dvec,"\n",ofs);

}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

STABLE PARTITION KULLANILSAYDI İZAFİ SIRA KORUNACAKTI BURALARI YAZ.
bunun içinde stable_partition var.

Biz yukarıdaki partitionu kullanmadan önce sıralasaydık.

sort(dvec.begin(), dvec.end());

auto iter = stable_partition(dvec.begin(), dvec.end(), [](const Date &x){ return x.month_day() == 5;}); //mayıs ayı başa gelecek, mayıs ayı olmayanlar daha sonra gelecek

Burada izafi sıranında korunduğunu görürüz.


-------------------------------------------------------------------------------------------------------------------------------------------------------------------

PARTITION COPY DE VAR.

Koşulu sağlayanları bir yere sağlamayanları bir yere yazıyor. return değeri en son yazdığı konumdan sonraki iteratörlere ilişkin iterator pairi.
return değeri, pairin iterator iterator açılımı. return değeri olan değerin first ü koşulu sağlayanların yazıldığı range in end i, second ise 
koşulu sağlamayan range e yazılan son öğeden sonraki konum.


int main()
{
	vector<Date> dvec;
	rfill(dvec, 100,Date::random);

	vector<Date> ok_vec;
	vector<Date> not_ok_vec;
	
	auto iter_pair = partition_copy(dvec.begin(), dvec.end(),back_inserter(ok_vec),back_inserter(not_ok_vec),
	[](const Date &x){ return x.week_day() == 6;})
	//return değeri pairin first olan koşulu salayanların end i, secondlar sağlamaynalar ise sağlamayanların end i.

	cout << "kosulu sağlayanlar\n";
	print(ok_vec,"\n");
	(void)getchar();
	system("cls");
	cout << "kosulu saglamayanlar\n";
	print(not_ok_vec,"\n");

}



*/
