/*

IOSTREAM KÜTÜPHANESININ FSTREAM MODÜLÜNÜ INCELIYORDUK.
primes.dat ı yazmıştık. Bu dosyaya binary olarak okuma ve yazma işlemleri yapıldı.
Buradaki funclar read ve write functionlarıydı.reinterpret_cast in kullanımının ender olarak görüldüğü senaryolar buradaydı.

Gcount formatsız okumada okunan byte sayısını döndürüyor çünkü formatsız okuma funcları akım nesnesini döndürüyor.
Bunu logic ifade gereken yerde kullanınca operator bool çağrılıyordu.Akımda hata olduğunda mesela akımda karakter kalmadığında okuma yapınca döngüden çıkıyordu

Belirli durumlarda bizim hem formatsız okuma yapıp hemde kaç byte okunduğu bilgisinide kullanmamız gerekiyordu. Ör, bir dosyanın kopyasını çıkartmak istersek
bunun baştan kaç. byte olduğunu bilmezsek, o dosyadan okluma yapıp başka dosyaya formatsız yazma işlemi yapınca ne kadar okuduysak o kadar yazma işlemi
yapmak gerekiyordu.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KOMUT SATIRINDAN YAZILAN BIR KOPYALAMA FUNCTIONU. C DE YAZMIŞTIK.

// filecopy ali.exe veli.exe
int main(int argc, char **argv)
{
	using namespace std;

	if(argc != 3) 	// argc3 olmalı
	{					
		std::cerr<< "usage : <filecopy> <source file name> <dest file name>\n"; // cerr hata akımını temisl ediyor. C de fprintf(stderr,... gibi)
																				// cerr her yazma işleminden  sonra flush ediliyor.
		return 1;
	}

	constexpr int size{1024};
	unsigned char buffer[size];

	ifstream ifs{ argv[1], ios::binary};
	if(!ifs)
	{
		cerr << "file " << argv[1] << "cannot be opened\n";
		return 1;
	}

	//kopyalama kısmı
	ofstream ofs{ argv[2], ios::binary};
	if(!ofs)
	{
		cerr << "file " << argv[2] << "cannot be created\n";
		return 1;
	}

	streamsize read_bytes{0};

	while(ifs.read(reinterpret_cast<char *>(buffer), size)) // unsigned char * dan char * a cast ettik.
	{
		auto n = ifs.gcount();
		ofs.write(reinterpret_cast<char *>(buffer), n);
		read_bytes += n;
	}

	std::cout << "file " <<argv[1] << " of" << read_bytes << " copied as file " << argv[2] << "\n";

}

filecopy yaz.exe yazyaz.exe test edilebilir bir exe ile
C de baya yazdık bunları.komut satırından test edilebilir.

===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================

DOSYA KONUM GÖSTERICISI ILE ILGILI FUNCTIONLAR
----------------------------------------------
İster formatlı ister formatsız olsun, biz okuma işlemi yapan herhangibir func çağırdığımızda, o func ilk önce file pointerın değerine bakıyor ve o hangi byte ise oradan yapıyor bu işi.
Aynı şekilde yazma işlemi de böyle.File pointera bakılıp yazma işlemini o bytten başlayarak yapıyorlar.

Sequencial access denilen biçimde bir dosyaya erişim gerçekleştirirsek, bu şu anlama geliyor döngüsel bir yapı içinde okuma yaptığımızda her turda yeni bir byte okuyoruz taa ki 
okunacak byte kalmayana kadar yani akım EOF durumuna geçene kadar. Yazma işlemi de aynı, döngüsel yapıda her yazma işlemi file pointerı yazdırılan byte sayısı kadar ilerletiyor 
böylece her yazma işlemi yeni bir yere yazmış oluyor. Yazma işlemi 2 farklı işin birşelim kümesi gibi, varolan byte ın değerini değiştirmek diğeride dosyaya yeni byte eklemek.
Her ikiside yazma işlemi.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

- Istream sınıfından kalıtım yoluyla elde edilen sınıflarda dosya konum göstericisini set eden funcların ismi seekg. Okuma amaçlı dosya konum göstericisinin konumunu seekg set ediyor.

- Ostreamden kalıtımal elde edilen sınıflarda ise dosya konum göstericisini konumlandıran funca seekp deniyor.2 Overlodu var ikisininde

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
#include <fstream>
#include <iostream>
#include <stdexcept>

std::ifstream open_read_file_bin(std::string file_name)
{
	std::ifstream ifs {file_name, std::ios::binary};
	if(ifs.fail())
	{
		throw std::runtime_error{"file : " + file_name + " cannot be opened!"};
	}

	return ifs;
}

int main()
{
	using namespace std;
	std::cout << typeid(streampos).name() << "\n";

	try{
		auto ifs = open_read_file_bin("primes.dat"); // primessss.dat ta denenip hata görülebilir.

		----------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		2 OVERLOADU VAR SEEKG NİN
		Bir tanesi streampos türünden bir değer istiyor.
		
		1.Overload
		----------
		ifs.seekg(10000); // Tamsayı değerini argüman olarak verdik. Dosya konum göstericisini baştan 10bininci byte a konumlandırdı.

		----------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		2. Overload
		-----------
		Bu overload un 1. parametresi kaç adet ileri geri gidileceğini istiyor, 2. parametresi ise 3 tane bitsel maskeden birini alıyor.
		ios::end, ios::beg, ios::cur. Tamamen fseek ile aynı.

		DOSYA SONU

		ifs.seekg(0,ios::end); // dosyanın sonunda iken dosya konum göstericisinin değerini okursam dosyanın büyüklüğünü verir.
		
		cout << ifs.tellg() << "\n"; // dosya büyüklüğünü verir.
		
		----------------------------------------------------------------------------------------------------------------------------------------------------------------------
		
		DOSYANIN BAŞI

		ifs.seekg(0,ios::beg); 

		----------------------------------------------------------------------------------------------------------------------------------------------------------------------

		ŞİMDİKİ KONUM

		ifs.seekg(0,ios::cur); // şimdiki yeri. 4 yazarsak 4 byte ileri. -4 yazsak 4 geri alırız

	}
	catch(const std::exception &ex)
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	using namespace std;

	auto ifs = open_read_file_bin("primes.dat");
	int n;

	for(int i = 0; i < 10; ++i)
	{
		std::cout << "kacinci asal sayi: ";
		cin >> n;

		ifs.seekg((n - 1)*sizeof(int), ios::beg); // Türden bağımswız olduğu için her bir sayı da 4 byte olduğundan her okumada 1 sayı alacak. ÖR: 1. asal için 0 pozisyonuna getirecek
		
		ifs.read(reinterpret_cast<char *>(&ival), sizeof(int)); // Burada ise okuma yapılacak. Yukarıda türden bağımsız şekilde file pointer gerekli yere getirildi artık okuma zamanı.
		
		if(ifs.gcount() != sizeof(int)) // hiç okuyamadıysa çıkacak.
			break;

		std::cout << n << ". asal sayi " << ival << "\n";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GİTHUB ÖRNEK

#include <iostream>
#include <string>
#include <sstream>

int main()
{
	using namespace std;

	istringstream iss("Necati Ergin");
	std::string str;

	iss >> str;
	cout << "[" << str << "]\n"; // Necati

	iss.seekg(0, ios_base::beg); 
	iss >> str;
	cout << "[" << str << "]\n"; // Necati
	
	iss.seekg(1, ios_base::cur); 
	iss >> str;
	cout << "[" << str << "]\n"; // Ergin
	
	iss.seekg(-6, ios_base::cur); 
	iss >> str;
	cout << "[" << str << "]\n"; // Ergin
	
	iss.seekg(-6, ios_base::end); 
	iss >> str;
	cout << "[" << str << "]\n"; // Ergin

	iss.seekg(0, ios_base::beg);
	iss >> str;
	cout << "[" << str << "]\n"; // Necati
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GİTHUB ÖRNEK

#include <string>
#include <fstream>
#include <iostream>
#include <exception>

void print_file_n_times(const std::string& filename, int n)
{
	// open file
	std::ifstream ifs(filename);
	if (!ifs)
		throw std::runtime_error{ "dosya acilamadi\n" };

	while (n--) {
		std::cout << ifs.rdbuf(); // streambuf pointerını ostream in inserterına argüman olarak gönderdik.
		std::cout << "\n--------------------------\n";
		ifs.seekg(0);
		(void)getchar();
	}
}


int main()
{
	print_file_n_times("isimler.txt", 5); // dosyayı 5 kere yazdırıyor.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Okuma işlemi fail ettiyse ve tekrar bir işlem yapılcaksa hata bayrakları tekrardan reset edilmeli.Ya file pointer set eden func ı çağıracağız ya da clear func ı bu işe yarıyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Nodiscard kullanılmalı.TÜm arttribute lardan önemli

[[nodiscard]] int foo(int x)
{
	return x * x;
}
int main()
{
	foo(5);
}

Atribute lar ile ilgili video paylaşılacak.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DİKKAT !!!!

int main()
{
	ofstream ofs{"input.txt"};

	ofs.seekp(10, ios::beg);
	ofs.put('!');

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GİTHUB ÖRNEK

#include <sstream>
#include <iostream>

int main(int argc, char** argv)
{
	using namespace std;

	ostringstream oss{ "*necati ergin" };

	cout << "[" << oss.str() << "]\n"; // *necati ergin

	oss.seekp(7); // Tam boşluğa geldi pointer. MEMORY DE DÖNÜYOR BU OLAYLAR BİR FİLE İÇERİSİNDE DEĞİL. OSTRINGSTREAM DİKKAT!!!!!
	oss.put('-'); // - yazdı boşluğa
	cout << "[" << oss.str() << "]\n"; //tekrar yazdık

	oss.seekp(0, ios::end);
	oss.put('!');
	cout << "[" << oss.str() << "]\n";// *necati ergin!

	oss.seekp(0);
	oss.put('!');
	cout << "[" << oss.str() << "]\n"; // !necati ergin!

}

IFSTREAM DE SEEKG VAR
OFSTREAM DE SEEKP VAR
FSTREAM DE İKİSİDE VAR

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EXCEPTION
---------
Giriş çıkış işlemlerinde bir hata olduğunda exception throw edilmiyor. Bunun 2 nedeni var. 
1 - Giriş çıkış sınıflarının exception handlingten çok daha erken dile eklenmiş olması
2 - Exception handling eklendikten sonrada default olarak exception throw etmemesi durumunu tercih etmişler

Exception throw etmesini sağlayabiliyoruz. Bu state e getirebiliyoruz. Exceptions isimli sınıfla oluyor bu.
Ama hata verilmesi state ine getirebiliytoruz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	try{
		int x;
		cout << "bir tamsayi girin:"; //ali
		cin >> x;
	}
	catch(const std::exception &ex)
	{
		std::cout << "exception caught "<< ex.what << "\n"; 
	}
}

BURADA EXCEPTION THROW ETMEDI

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA HATA VERMESİNİ SAĞLAYACAĞIZ

int main()
{
	cin.exceptions(ios::failbit); // failbiti set edildiğinde exception throw edecek.Failbit set edildiğinde exception throw edilecek demek bu
	
	try{
		int x;
		std::cout << "bir sayi giriniz\n";
		cin >> x; //Ali 
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}

Exception throw etti

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cin.exceptions(ios::eofbit); // EOF set edildiğinde exception gönderecek şekilde func call yaptık
	try{
		int x;
		std::cout << "bir sayi giriniz\n";
		cin >> x; //Ali  
	}
	catch(const std::exception& ex)
	{
		std::cout << "exceotion caught : " << ex.what() << '\n';
	}
}

Ali yazarsak exception throw etmez çünkü EOF flag set edilmedi. Biz ise Eof biti set edildiğinde exception gönder dedik yukarıda

ctrl z girersek eof bit set  edildiğinden exception throw edilir.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	//ios_base::ios_state x = cin.exceptions(ios::eofbit | ios::badbit);	böylede yazılır.
	
	auto x = cin.exceptions(ios::eofbit | ios::badbit);	 // x in değeri hangi bit set edildiğinde exception throw edileceğinin bilgisi. Şuanda defaultta exception throw etmediğinden 
														// x in değeri goodbit olacak.Goodbit tüm bitleri 0 olan iostate maskesi.

	std::cout << boolalpha << (x == 0);
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SIK KULLANILAN İDİYOMLAR

Print func spesifik bir formatlama gerektiriyorsa print bunu yapabilir ama zaten main içinde bazı formatlama özellikleri değiştirilmişse ne olcak ?


using namespace std;

void print(std::ostream& os)
{
	os << hex << uppercase << showbase << boolalpha;
	//...
}

int main()
{
	int ival = 8976234;

	cout << ival << " " << (10 > 15)<<"\n";
	print(cout);
	cout << ival << " " << (10 > 15)<<"\n";
}

ÇIKTI
-----
8976234 0 
0X88F76A 0 

Görüldüğü gibi formatlama özellikleri değişti. Nesneyi bozdu. Biz böyle yazdırmak istemiyoruz. Formatlamamızı bozdu.

Böyle bir func bu nesne kendisine ait olmadığı için ya bunun için kendi ostream nesnesini kullanacak yada bunu kullanacaksa kulandığını eski haline getirmeli.
Bunun için RAII idiyomunu kullanalım.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RAII
BIZ BIR RAII SINIFI OLUŞTURSAK BU BIR OSTREAM NESNESINI REFERANS YOLUYALA ALSA VE ONUN FORMATLAMA ÖZELLIKLERINI KENDI VERI ELEMANINDA SAKLASA DESTRUCTORUDA ESKI DURUMUNA GERI DÖNDÜRSE.

using namespace std;

class fmguard{
public:
	fmguard(std::ostream&os) : 
		os_{os}, 
		flags_{os.flags()}, 
		width_{os.width()}, 
		fillc_{os.fill()}, 
		precision_{os.precision()} {	}
	
	~fmguard()
	{
		os_.flags(flags_);
		os_.width(width_);
		os_.fill(fillc_);
		os_.precision(precision_);
	}

private:
	std::ostream& os_;
	std::ios::fmtflags flags_;
	std::streamsize width_;
	std::streamsize precision_;
	char fillc_;
};

void print(std::ostream& os)
{
	fmguard fg{os};
	os << hex << uppercase << showbase << boolalpha;
	os << 7771234 << " " << (10 > 5) << "\n";
}

int main()
{
	int ival = 7894564;

	cout << ival << " " << (10 > 15)<<"\n";
	print(cout);
	cout << ival << " " << (10 > 15)<<"\n";
}

ÇIKTI
-----
8976234 0
0X88F76A 0
8976234 0

Burada sanırım standart çıkış akımındaki formatlama özelliklerini default hale getirdi. HOCAYA SOR ???????????????????????????????????????????????????????

MOLA

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================

CRTP - Curiously Recurring Template Pattern
-------------------------------------------
C++ ın en çok kullanılan idiyomlarından biri.

1. KULLANIM CRTP NİN STATIC POLYMORPHISM AMAÇLI KULLANILMASI
------------------------------------------------------------

template <typename T>
class Base{
public:
	void func()
	{
		//static_cast<T &>(*this) //buda olurdu

		(static_cast<T *>(this))->foo();
	}
};


class Der : public Base<Der>
{
public:
	void foo()
	{
		std::cout << "Der::foo()\n";
	}
};


class Nec : public Base<Der>
{
public:
	void foo()
	{
		std::cout << "Nec::foo()\n";
	}
};


int main()
{
	Der myder;

	myder.func(); // Der in foo fonksiyonu çağprılır func içinden

	Nec mynec;

	mynec.func() // Nec in foo fonksiyonu çağprılır func içinden
}

Virtual dispatch in compile time da olan hali olarakta kullanılabilir. Static Polymorphism de deniyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EĞER BU BİRDEN FAZLA YERDE KULLANILACAKSA HER SEFERİNDE BU DÖNÜŞÜMÜ BİR BASE E YAPTIRABİLİRİZ.
BASE DEĞİŞTİRİLDİ

template <typename T>
class Base{
public:
	T& derived()
	{
		return static_cast<T&>(*this);
	}
	
	const T& derived()const
	{
		return static_cast<const T&>(*this);
	}

	void func()
	{
		derived().foo();		
	}
};


class Der : public Base<Der>
{
public:
	void foo()
	{
		std::cout << "Der::foo()\n";
	}
};


class Nec : public Base<Der>
{
public:
	void foo()
	{
		std::cout << "Nec::foo()\n";
	}
};


int main()
{
	Der myder;

	myder.func(); // Der in foo fonksiyonu çağprılır func içinden

	Nec mynec;

	mynec.func() // Nec in foo fonksiyonu çağprılır func içinden
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ANIMAL ÖRNEĞİ

class Animal
{
public:
	virtual void cry() = 0;
	virtual ~Animal(){ }
	//...
};

class Dog : public Animal{
public:
	void cry() override
	{
		std::cout << "Köpek Havliyor\n";
	}
};

class Cat : public Animal{
public:
	void cry() override
	{
		std::cout << "Kedi Miyavliyor\n";
	}
};

class Lamb : public Animal{
public:
	void cry() override
	{
		std::cout << "Kuzu Meeliyor\n";
	}
};

void game(Animal &r)
{
	r.cry();
}

int main()
{
	Dog mydog;
	Cat mycat;
	Lamb mylamb;

	game(mydog);
	game(mycat);
	game(mylamb);
}

Çıktı
-----
Kopek Havliyor
Kedi Miyavliyor
Kuzu Meeliyor

Virtual Dispatch maliyetli.
Vptr var, bir table var bu func pointerları tutan. Bellek maliyeti ve runtime maliyeti var.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİNİ CRTP İLE YAPALIM

template<typename Der>
class Animal
{
public:
	void make_sound()
	{
		Der& der = static_cast<Der&>(*this);
		der.cry();
	}
};

class Dog : public Animal<Dog> {
public:
	void cry()
	{
		std::cout << "Kopek Havliyor\n";
	}
};

class Cat : public Animal<Cat> {
public:
	void cry()
	{
		std::cout << "Kedi Miyavliyor\n";
	}
};

class Lamb : public Animal<Lamb> {
public:
	void cry()
	{
		std::cout << "Kuzu Meeliyor\n";
	}
};

//bunu sonradan ekledik. olmadanda yaptık aslında
template <typename T>
void game(Animal<T>&a)
{
	a.make_sound();
}

int main()
{
	Dog mydog;
	Cat mycat;
	Lamb mylamb;
	
	game(mydog);
	game(mycat);
	game(mylamb);
}

ÇIKTI
-----
Kopek Havliyor
Kedi Miyavliyor
Kuzu Meeliyor

BURADA TÜM MALIYET COMPILE TIME DA

Bazı kısıtlamalar var CRTP de.
Mesela virtal dispatch olsaydı bir containerda animal ptr lerini tutabilirdik yada unique_ptr<animal> nesnelerini tutabilirdik.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. MIXIN CLASS AMAÇLI KULLANIMI
-------------------------------

Bir sınıfa ekstra özellikler kazandırmak için kullanılan sınıf ya da sınıflar.
Static bir kalıtım yoluyla bir sınıfın interface ine ilave birtakım skiller ekliyoruz.

ÖR : SINIFLARIN == VE != IŞLEVLERININ CRTP ILE INTERFACE E EKLENMESI.

< işlemine destek veren sınıfların == ve =! işlevlerini otomatik olarak edinmesini sağlamak
!(a < b) && !(b < a) 

ÖNEMLİ
------
Aşağıdaki örnekte 
!= OPERATÖR FUNC, == OPERATOR FUNC KULLANIYOR.
== İSE, < OPERATOR FUNC KULLANIYOR


ÖR:
template <typename Der>
struct equality{
	const Der& derived()const
	{
		return static_cast<const Der&>(*this);
	}
};

template <typename Der>
bool operator==(const equality<Der> &left, const equality<Der> &right) // == LIK SINANIYOR BURADA
{
	auto &derleft = left.derived();	
	auto &derright = right.derived();

	return !(derleft < derright) && !(derright < derleft);
}

template <typename Der>
bool operator!=(const equality<Der> &left, const equality<Der>& right) // BURADA DA YUKARIDAKI == KULLANILARAK != SINANIYOR.
{
	return !(left == right);
}

class Nec : public equality<Nec> // BURADA NEC IN < FUNCTIONU OLDUĞUNDAN, YUKARIDAKİ == SINAYAN FUNC A GİRİLDİĞİNDE BURADAKİ < OPERATÖRÜNÜ KULLANACAK.
{
public:
	Nec(int val) : mval{val} {}
	bool operator<(const Nec& other)const
	{
		return mval < other.mval;
	}
private:
	int mval{};
}

int main()
{
	Nec x{ 123 };
	Nec y{ 234 };

	std::cout << std::boolalpha;
	std::cout << (x == x) << "\n";
	std::cout << (x != x) << "\n";
}

Bunun özelliği, artık hemn interface te doğrudan static kalıtım yoluyla kullanıyoruz hemde istediğimiz kadar sınıfa bunu katabiliriz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

template <typename Der>
struct equality{
	const Der& derived()const
	{
		return static_cast<const Der&>(*this);
	}
};

template <typename Der>
bool operator==(const equality<Der> &left, const equality<Der>& right) 
{
	auto &derleft = left.derived();
	auto &derright = right.derived();

	return !(derleft < derright) && !(derright < derleft);
}

template <typename Der>
bool operator!=(const equality<Der> &left, const equality<Der>& right) 
{
	return !(left == right);
}

class Person : public equality<Person>
{
public:
	Person(std::string name) : name_{std::move(name)} { }
	bool operator<(const Person& other)const
	{
		return name_ < other.name_;
	}
private:
	std::string name_{};
}

int main()
{
	Person p1 {"Burak"};

	Person p2 {"Burak"};
	
	std::cout << boolalpha;
	cout << (p1 == p2) << "\n";
	cout << (p1 != p2) << "\n";

	-------------------------------------------------------------------
	
	Person p1 {"Burak"};

	Person p2 {"Umut"};

	cout << (p1 == p2) << "\n";
	cout << (p1 != p2) << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

template <typename Der>
struct Base {
public:
	Der get_double()const	// Burada toplama operatörünün operandı olan nesneler eğer base sınıfından elde edilecek sınıflar CRTP ile elde edildiyse, aslında o sınıfların + func çağrılıyor.
	{						// Böylece + operator func olan her sınıf , base sınıfından crtp ile elde edildiğinde bunlar otomatik olarak get_double ve get_triple kabiliyetlerini elde ediyorlar.

		const Der& me = static_cast<const Der&>(*this);

		return me + me;
	}

	Der get_triple()const
	{
		const Der& me = static_cast<const Der&>(*this);

		return me + me + me;
	}
};

class Value : public Base<Value>
{
public:
	Value(int x) : val_{ x } { }
	void print()const
	{
		std::cout << val_ << "\n";
	}

	Value operator+(const Value& other)const
	{
		return val_ + other.val_;
	}
private:
	int val_;	
};

int main()
{
	Value x{ 12 };

	auto n = x.get_double();
	n.print();

	n = x.get_triple();
	n.print();
}

ÇIKTI
-----
24
36

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

VALUE SINIFININ KENDISIDE BIR CLASS TEMPLATE OLABILIR.

template <typename Der>
struct Base {
public:
	Der get_double()const	// Burada toplama operatörünün operandı olan nesneler eğer base sınıfından elde edilecek sınıflar CRTP ile elde edildiyse, aslında o sınıfların + func çağrılıyor.
	{						// Böylece + operator func olan her sınıf , base sınıfından crtp ile elde edildiğinde bunlar otomatik olarak get_double ve get_triple kabiliyetlerini elde ediyorlar.

		const Der& me = static_cast<const Der&>(*this);

		return me + me;
	}

	Der get_triple()const
	{
		const Der& me = static_cast<const Der&>(*this);

		return me + me + me;
	}
};


template<typename T>
class Value : public Base<Value<T>> //DIKKAT !!!!
{
public:
	Value(const T& val) : val_{ val } { }
	void print()const
	{
		std::cout << val_ << "\n";
	}

	Value operator+(const Value& other)const
	{
		return val_ + other.val_;
	}
private:
	T val_;
};

int main()
{
	Value<std::string> x{ "burak" };

	auto y = x.get_double();
	y.print();

	//--------------------------------

	Value<std::string> a{ "burak" };
	auto b = a.get_triple();
	b.print();

}

ÇIKTI
-----
burakburak
burakburakburak

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SHARED PTR DEKI ENABLED_SHARED_FROM_THIS ÖRNEĞI

// Eğer bir sınıfın üye fonksiyonu içinde shared_ptr ile hayatı kontrol edilen * this nesnesini gösteren
// shared_ptr'nin kopyasını çıkartmak isterseniz sınıfınızı CRTP örüntüsü ile kalıtım yoluyla std::enable_shared_from_this
// sınıfından elde etmelisiniz

#include <memory>
#include <iostream>


using namespace std;

class Neco : public std::enable_shared_from_this<Neco> {  //CRTP
public:
	Neco()
	{
		std::cout << "Neco ctor this : " << this << "\n";
	}

	void func()
	{
		std::cout << "Neco::func() islevi : " << this << "\n";

		//ben func islevinin bir shared_ptr ile kontrol edilen dinamik Neco nesnesi icin cagrildigina eminim
		auto sptr = shared_from_this();
		std::cout << "sptr.use_count() = " << sptr.use_count() << "\n"; // use_count arttı
	}

	~Neco()
	{
		std::cout << "Neco destructor : " << this << "\n";
	}
};


int main()
{
	auto sp = make_shared<Neco>();
	sp->func();
	//Neco *p = new Neco;

	//try {
	//	p->func();
	//}
	//catch (const std::exception &ex) {
	//	std::cout << "hata yakalandi : " << ex.what() << "\n";
	//}

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA TEMPLATE TEMPLATE TÜR PARAMETRESINE GIRILDI KISACA

Templatelerde 3 parametre yapısı var.
1 - Template type parametrer
2 - Template nontype parameter
3 - template template parameter

Template Template Parameter ileri C++ ta görülecek normalde.Parametreye karşılık gelen argümanda template olmalı.

template <typename T, template<typename X> typename Con>
class Myclass{
	void func()
	{
		Con<T> x; //Con hangi template ise T de hangi tür ise, o template in T açılımı kullanılmış olacak.
	}
};

Myclass ın bir sınıf şablonu olduğunu söylüyor ama template argümanı olarak bir tane template tür parametreye sahip bir template kullanılması gerekiyor.
Biz burada Con kullandığımız zaman aslında Con bir templatein karşılığı.

C++17 den önce
template <typename T, template<typename> class Con> 
Burada class keyword kullanılmak zorundaydık. C++17 den sonra burada da typename kullanabiliyoruz.
Burada template değişen kullanmadan da yazabiliriz. Yukarıdakinde X demiştik. 

2 parametresi varsa
template <typename T, template<typename, typename> typename Con>	yazarız

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

template <typename T, template<typename, typename> typename Con>
class Myclass{
public:
	void func()
	{
		Con<T> x; 
		
		std::cout << typeid(x).name();
	}
};

template<typename T>
class Value{

};

int main()
{
	Myclass<int, double> mx; // SENTAKS HATASI
	
	Myclass<int, Value> my; //GEÇERLİ

	my.func(); // x in türü Value<int> çıkacak. x class template içindeki x
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURASI KARMAŞIK AMA GÜZEL

template <typename T, tempalte <typename> typename Der>
class Myclass{
public:

};

template<typename T>
class Value : public Base<Value>
{
public:

};

int main()
{
	
}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================

	
RATIO
-----
Bu bir sınıf şablonu yine :D:D Ratio kesir demek. tamamen compile time türü. Compile time programlaması için kullanılıyor.
Chrono da kullanılıyor ve bundan sonra chrono göreceğiz. O yüzden ratio anlatılıyor. Header file ratio. AYnı zamanda chrono header file içinde de var ratio

rationun 2 tane nontype template parametresi var. Bunların türü intmax_t. intmax_t de bir type alias.Sistemdeki en büyük işaretli tamsayı türü.

int main()
{
	cout << typeid(std::intmax_t).name() << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <ratio>

int main()
{
	std::ratio<12,7>;	// 1. nontype parametre için argüman 12, ikinci nontype parametre için 7 sabiti kullanıldı
}

Bu bir kesiri compile timeda ifade ediyor. ratio<5,9> ise 5/9 sabiti olarak kullanılıyor.

int main()
{
	std::ratio<5,9>; // template nontype argüman bir constexpr veri elemanı olarak tanımlanmış
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEMPLATE
--------

template<long long n, long long d>
struct Ratio{
	static constexpr long long num = n;
	static constexpr long long den = d;
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Örneğe geri dönemlim

#include <ratio>
#include <iostream>

int main()
{
	constexpr auto x = ratio<5,12>::num; // mouse ile üzerine gelince 5 görünür
	constexpr auto y = ratio<5,12>::den; // mouse ile üzerine gelince 12 görünür

	cout << typeid(ratio<5,12>::type).name() << "\n";	
}

using bildirimide verilebilir using rat = ratio<5,12>; denebilirdi...

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

#include <ratio>
#include <iostream>

using rat = ratio<8,24>;

int main()
{	
	//DİKKAT!!!!!!!!!!
	constexpr auto x = rat::num; // 1 görünür
	constexpr auto y = rat::den; // 3 görünür

	cout << typeid(rat::type).name() << "\n"; // ratio<1,3> açılımı görülür.
	
	//SADELEŞTİRİYOR. SADELEŞTİRMEDE COMPILE TIME DA YAPILIYOR.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NEGATIF ORNEK

#include <ratio>
#include <iostream>

using rat = ratio<8,-24>;
- KISIM PAYA ÇIKACAK

int main()
{
	//DİKKAT!!!!!!!!!!
	constexpr auto x = rat::num; // -1 görünür. DİKKAT!!!! - KISIM PAYA ÇIKTI
	constexpr auto y = rat::den; // 3 görünür

	cout << typeid(rat::type).name() << "\n"; // ratio<-1,3> açılımı görülür.

	//SADELEŞTİRİYOR. SADELEŞTİRMEDE COMPILE TIME DA YAPILIYOR.

}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NEGATIF ORNEK

#include <ratio>
#include <iostream>

using rat = ratio<-8,-24>;

int main()
{
	//DİKKAT!!!!!!!!!!
	constexpr auto x = rat::num; // 1 görünür. İkiside pozitif
	constexpr auto y = rat::den; // 3 görünür

	cout << typeid(rat::type).name() << "\n"; // ratio<1,3> açılımı görülür.

	//SADELEŞTİRİYOR. SADELEŞTİRMEDE COMPILE TIME DA YAPILIYOR.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <ratio>
#include <iostream>

using rat = ratio<5>;
Bu ratio<5,1> demek yani default olarak ikinci argüman 1


int main()
{
	//DİKKAT!!!!!!!!!!
	constexpr auto x = rat::num; // 5
	constexpr auto y = rat::den; // 1 görünür

	cout << typeid(rat::type).name() << "\n"; // ratio<5,1> açılımı görülür.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using rat = ratio<5,0>;  // BURASI COMPILE TIME HATASI

using rat = ratio<>; // BURASI SENTAKS HATASI

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RATIO HEADER FILE İÇİNDE BELİRLİ KESİRLERİN DOĞRUDAN EŞ İSİMLE İSİMLENDİRİLMİŞ HALİ VAR

#include <ratio>
#include "nutility.h"
#include <iostream>

template<intmax_t x, intmax_t y>
std::ostream& operator<<(std::ostream& os, std::ratio<x, y> r)
{
	return os << x << " / " << y;
}

int main()
{
	using namespace std;
	cout << "exa    = " << exa{} << "\n";
	cout << "peta   = " << peta{} << "\n";
	cout << "tera   = " << tera{} << "\n";
	cout << "giga   = " << giga{} << "\n";
	cout << "mega   = " << mega{} << "\n";
	cout << "kilo   = " << kilo{} << "\n";
	cout << "hecto  = " << hecto{} << "\n";
	cout << "deca   = " << deca{} << "\n";
	cout << "deci   = " << deci{} << "\n";
	cout << "centi  = " << centi{} << "\n";
	cout << "milli  = " << milli{} << "\n";
	cout << "micro  = " << micro{} << "\n";
	cout << "nano   = " << nano{} << "\n";
	cout << "pico   = " << pico{} << "\n";
	cout << "femto  = " << femto{} << "\n";
	cout << "atto   = " << atto{} << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

COMPILE TIME PROGRAMMING DESTEKLEMEK IÇIN RATIO ILE ILGILI METAFUNCLAR VAR

Örnek iki kesri toplamak ratio_add

int main()
{
	constexpr auto r = ratio_add<ratio<1,3>, ratio<2,5>>::num; // 11
	constexpr auto r = ratio_add<ratio<1,3>, ratio<2,5>>::den; // 15

	-----------------------------------------------------------------------------------------------------------------------------------------------------

	constexpr auto r = ratio_subtract<ratio<1,3>, ratio<2,5>>::den; // - işlemi

	-----------------------------------------------------------------------------------------------------------------------------------------------------

	constexpr auto r = ratio_multiply<ratio<1,3>, ratio<2,5>>::den; // * işlemi

	-----------------------------------------------------------------------------------------------------------------------------------------------------

	KARŞILAŞTIRMA OPERATORLERİ

	ratio_less<ratio<1179, 3457>, ratio<1183, 3471>>::value;
	
	ratio_less_v<ratio<1179, 3457>, ratio<1183, 3471>>;
	
	Burada eksik olan inserter.

}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================

CHRONO
------
Modern C++ ile gelen ve c++ 11 den sonra sürekli eklemeler yapılan en önemli kütüphanelerinden biri chrono.
Zamanla ilgili bir library. Burada zamana yönelik türler var, bunlara ilişkin interface var, timepointe ilişkin değerler var.
Standart library nin chrono modülü si tarih zaman süre gibi konularda destek veriyor. Chronoyu kendi kodlarımızda çok sık kullancağız.
Ayrıca başka standart library bileşenleri bazı func parametrelerinde chrono değerlerini kullanacaklar.

Başta karmaşık gelebilir.
Header file chrono ama bu header file bir nested namespace içinde. Bunun adıda chrono. chronodaki öğelerden birini kullanmak için ortada using namespace bildirimi yoksa
std::chrono::system_clock şeklinde yazacağız.

using namespace std; yazarsak artık
chrono::system_clock yazarız


using namespace std::chrono;
system_clock kullanılabilir burada doğrudan

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Chrono içinde bizi ilgilendiren 3 tane önemli bileşen var. HErşey bu birbiriyle ilişkili 3 bileşen üstünde dönüyor.
1 - Clock türleri
2 - Duration türleri (süre)
3 - Time_point türleri (zamanda nokta)

C deki time ile yaptıklarımızın çok büyüğünü ve çok daha fazlasını chrono ile yapabiliyoruz ama bazı işlemlerde ctime ile işbirliği halinde chronoyu kullanıyoruz.

time_point ise bir clock a bağlı. Bir clock bize bir epoch ile bir time_point türü veriyor. Her clock un bir epoch u var.Epoch tarih zamanda bir timepoint idi.
En yaygın epoch 1.1.1970 00.00 olabilir.

	|								|
	|								|
	|								|
	|								|
	|	Bu kadar süre sonrası		|
	|---------------------------->  |
	|								|
	|								|
	|								|
	|								|
 Epoch					 Burası bir time point


 Bu time point epoch tan önceki bir timepointte olabilirdi.Time pointin ve epoch un ne olduğunu belirleyen clock denen nesneler.
 C++20 ye kadar bize 3 tane standart saat türü veriliyordu. system clock, file resolution clock, steadyclock. C++20 ile bu sayı arttı.

 ÖZET: Bİr clock umuz varsa bu bize bir timepoint veriyor birde bu time pointe anlam kazandıracak bir epoch değeri veriyor.
		
 Duration ise 2 timepoint arası fark.Duration dediğimiz zaman doğrudan saate bağlı değiliz. Elimizde 2 timepoint varsa bunların farkı duration verecek.
 saniye, millisanie ... şeklinde olabilir.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DURATION TEMPLATE
-----------------
duration<int,ratio<1>>;  Bu öyle bir süre birimi ki, her tiki bir saniye ve her türü int ile ifade ediliyor.

duration<long long int,ratio<1,1000>>;  Her tik saniyenin binde biri, ve tikin türü long long int anlamına gelecek.

BURADA TYPEDEF ISIMLERINIDE KULLANABILIRIZ.

int main()
{
	using namespace std;
	using namespace std::chrono;

	cout << typeid(seconds).name() << "\n"; // Burada second ın ne olduğunu veriyor. duration<int64,ratio<1,1>> açılımı özetle.Yani tik birimi 1 saniye ama herbir tik bir tamsayı ile ifade ediliyor.
											// 3356 saniye gibi...

	cout << typeid(milliseconds).name() << "\n"; // duration<int64,ratio<1,1000>>    Tik birimi int64 ama her tik 1/1000 saniye
	
	cout << typeid(nanoseconds).name() << "\n"; // duration<int64,ratio<1,1000000000>>  ...	

	cout << typeid(nanoseconds).name() << "\n"; // duration<int64,ratio<1,1000000>> 
												
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TÜREŞ ISMI VEREBILIRIZ

using half_second = std::chrono::duration<long long, ratio<1,2>>; // Bu türden nesne, 1 tiki yarım saniye olan bir süreye karşılık gelecek.

int main()
{
	half_second x {1234}; // 1234 tane yarım saniye demek
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

using frame = std::chrono::duration<long long, ratio<1,60>>; // saniyenin 1/60 ından veriler tutacak

int main()
{
	frame f{23.98}; // 23.98 tane saniyenin 1/60 ına karşılık geliyor. Bir sonraki ders compile time teknikleriyle birbirine dönüştürülüp aritmetik işlemlere sokulabileceğini gösterecek hoca
}

using hour = std::chrono::duration<long long, ratio<60*60>>; // bu var aslında. Hour 60*60 = 3600 saniyeye karşılık geliyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Arka plandaki template teknikleri ile bir süreyi kullanmak bir tamsayı değişkeni kullanmaya göre assembly kod karşılığı olarak hiçbir farklılığı yok.

int main()
{
	using namespace std;
	using namespace std::chrono;

	nanoseconds d{7489564}; // aslında low levelda long long ile bunun arasında fark yok.

	d.count(); // doğrudan tamsayı değerini veriyor.

	------------------------------------------------------------------------------------------------------------------------------------

	BIR SONRAKI DERSTE BUNLARI BIRBIRINE DÖNÜŞTÜRECEĞIZ, ÇARPABILECEĞIZ, TOPLAMA ÇIKARMA KARŞILAŞTIRMA DÖNÜŞTÜRME ... IŞLEMLERI YAPILACAK

	seconds s{2345};
	hours h{12};
	nanoseconds x{24325435}; 

	------------------------------------------------------------------------------------------------------------------------------------

	12h + 41232min + 1234s+ 123214ms + 65435645ns;
}


*/