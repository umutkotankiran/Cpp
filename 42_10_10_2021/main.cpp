/*

Bellek üzerinde okuma yazma işlemlerinde kaldık.
Inmemory input output işlemleri.

Giriş yada çıkış işleminin doğrudan programın kullandığı bellek alanı üzerinde yapılması kastediliyor.Mesela char türden bir dizi var. 
Herhangibir çıktıyı o dizide yazı formunda oluşturmak  istiyoruz.Yada elimizde bir yazı formunda veri var, onun karakterlerini kullanarak bir formatlı giriş işleminde kullanmak istiyoruz.
Yani karakterleri standart inputtan değil bir dosyadan değil doğrudan bellekten almak istiyoruz. C deki karşılıkları sprintf ve sscanf funcları. 
Burada bu işi yapan sınıflar var bunlar sstream header file da tanımlanan sınıflar var.

Burada ise ostringstring istringstring ve stringstream sınıfları var demiştik.Bunlar sstream header file içinde tanımlanmış

ostringstream : ostream den kalıtımla elde edilmiş. Bellekte bir yazıyı elde etmek için.ostream im tüm interface ini almış ama ilave func ı var.
istringstream : istream den kalıtımla elde edilmiş. Bellekteki bir yazıyı okumak için.istream interfaceini almış. 
stringstream : basic_iostream sınıfından kalıtımla elde edilmiş. Hem okumak için hemde elde etmek için

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include<sstream>
#include<iomanip>

int main()
{
	using namespace std;
	int ival = 34;
	doubledval = 123. / 7.;

	ostringstream oss;

	oss << "Necati Ergin" << setw(4) << ival << " " << fixed << setprecision(3) << dval; 

	auto str = oss.str();  // oss.str ile elde ediyoruz. 

	str.erase(0,1); // baştan karakter sildik
	str.pop_back(); // sondan karakter sildik
					// yani bu bir string istediğimiz işlemi yaparız

	cout << "str = " << str <<  "\n";

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	ostringstream oss;
	for(int i = 0; i < 10; ++i)
	{
		oss << setw(2) << i + 1 << ";" << rname();
	}

	cout << oss.str() << "\n"; // tek bir yazı olarak aldık.

}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FORMATLAYABILIRIZ

int main()
{
	using namespace std;

	ostringstream oss;
	oss << right << setfill('.');

	for(int i = 0; i < 10; ++i)
	{
		oss << setw(2) << i + 1 << ";" << rname();
	}

	cout << oss.str() << "\n"; // tek bir yazı olarak aldık.

}

=============================================================================================================================================================================================
=============================================================================================================================================================================================
=============================================================================================================================================================================================
=============================================================================================================================================================================================
=============================================================================================================================================================================================
=============================================================================================================================================================================================


ISTRINGSTREAM
-------------
Header file sstream. Bellekten okuma işlemi yapacak.Yani karakterleri bellekten extract edecek.
Constructora argüman olarak bir string veya bir cstring geçebiliriz.

int main()
{
	using namespace std;

	string sline;

	std::cout << "bir cumle girin : ";
	getline(cin, sline);

	istringstream iss{sline};

	string word;

	while(iss >> word)
	{
		cout << word << "\n"; // döngünün her turunda kelimelerden birini yazdık.
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	string sline;

	std::cout << "tamsayilari girin : ";
	getline(cin, sline);

	istringstream iss{sline};
	int ival;
	int sum{};

	while(iss >> ival)
		sum += ival;

	std::cout << "toplam = " << sum << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GÜZEL ÖRNEK ADIM ADIM BAK

int main()
{
	using namespace std;

	string sline;

	std::cout << "tamsayilari girin : ";
	getline(cin, sline);

	istringstream iss{sline};

	vector<int> ivec;
	int ival;

	while(iss >> ival) // vectore ekleniyor.
		ivec.push_back(ival);

	sort(ivec.begin(), ivec.end(), greater{}); // Büyükten küçüğe. <> kullanmayınca transparent func object oluyor.Böyle deniyor

	//Reverse iterator ilede yapabilirdik
	sort(ivec.rbegin(), ivec.rend())

	//Yazdırmayı aşağıdaki gibide yapardık
	copy(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "});

}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================


GIRIŞ ÇIKIŞ IŞLEMLERINE AIT BAZI ÖZELLIKLER

IGNORE
------
istream::ignore = İstediğimiz kadar karakteri giriş akımının bufferı içinden çıkartıyor. Bu istream sınıfının funcı olduğundan, istream sınıfı için, istreamden kalıtımla elde edilen
ifstream için ve istringstream için kullanılabilir.cin içinde kullanılabilir.

1 PARAMETRELİ OVERLOAD
Belirtilen değer kadar karakteri ignore eder

2 PARAMETRELİ OVERLOAD
Bİrinci parametre kaç karakter içerisinde arama yapılacak
İkinci parametre ise hangi karakteri arıyorum. Bulursa o karaktere kadar olanı ignore ediyor

istream den kalıtımla elde edilenler içinde de kulanılabilir.

int main()
{
	cin.ignore(); 
	// Birinci karakter kaç karakter ignore edileceği.defaultta 1 değerinde. Türü steamsize. 64 bitlik yani 8 bytelık int türü. long long türü
	// İkinci karakter hangi karakter görünene kadar ignore edilecek bunu belirliyor. default olarak -1 yani EOF
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

int main()
{
	using namespace std;
	istringstream iss{"123456ali\n8757"};

	int ival;

	iss>>ival;
	std::cout << "ival = " << ival << "\n"; //burada ival 123456 olmalı
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR: DİKKAT

int main()
{
	using namespace std;
	istringstream iss{"123456ali\n8757"};

	int ival;

	iss.ignore(); // default olarak 1 karakter ignore ediliyor. iss.ignore(1);
	iss>>ival;
	std::cout << "ival = " << ival << "\n"; //ival 23456 olacak
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR: DİKKAT

int main()
{
	using namespace std;
	istringstream iss{"123456ali\n8757"};

	int ival;

	iss.ignore(3); // default olarak 3 karakter ignore ediliyor
	iss>>ival;
	std::cout << "ival = " << ival << "\n"; //ival 456 olacak
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR: Newline görene kadar tüm karakterleri ignore etmesini istesek

int main()
{
	using namespace std;
	istringstream iss{"123456ali\n8757"};

	int ival;

	iss.ignore(100,'\n'); // 100 KARAKTERE BAKACAK VE İLK 100 KARAKTER İÇERİSİNDE \n VARSA BUNA KADAR OLANLARI IGNORE EDECEK.
				// iss.ignore(100); OLSAYDI DOĞRUDAN İLK 100 KARAKTERİ IGNORE EDECEKTİ.
	iss>>ival;
	std::cout << "ival = " << ival << "\n"; // 8757
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR SATIRIN TAMAMINI IGNORE ETMEK ISTESEM AŞAĞIDAKI GIBI ÇAĞRI YAPABILIRIZ.
1. parametreye alacağı max değer 2. parametreye new line


int main()
{
	using namespace std;
	
	istringstream iss{"123456ali\n8757"};
	int ival;

	iss.ignore(numeric_limit<streamsize>::max(), '\n'); // 8757 ye kadarını ignore etti

	iss>>ival;

	std::cout << "ival = " << ival << "\n"; // 8757
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	using namespace std;

	int x{}, y{};

	cout << "Bir tamsayi girin\n"; // 234Alican girersek aşağıda tekrar birşey girmeme izin vermez çünkü standart inputun bufferını boşaltmadı
	cin>>x;

	cout << "Bir tamsayi daha girin\n";
	cin>>y;

	std::cout << "x = " << x << "\n"; 
	std::cout << "y = " << y << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKINI DÜZELTMEK IÇIN

int main()
{
	using namespac estd;

	int x{}, y{};

	cout << "Bir tamsayi girin\n";
	cin>>x;

	cout << "Bir tamsayi daha girin\n";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bu limits te var
	cin>>y;

	std::cout << "x = " << x << "\n";
	std::cout << "y = " << y << "\n"; // hata oluştu buffer dolu olduğundan

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BASIC ÖRNEK ASLINDA GÜZEL ÖRNEK

int main()
{
	istringstream iss{"necatiergin"};

	iss.ignore(100,'a'); // a yı görene kadar tüm argümanları ignore etti.

	string str;

	iss>>str;

	std::cout << str << "\n"; // tiergin yazar 
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

int main()
{
	istringstream iss{"necatiergin\nhasan"}; //dikkat

	iss.ignore(100,'a'); // a yı görene kadar tüm argümanları ignore etti.

	string str;

	iss>>str;

	std::cout << str << "\n"; // tiergin yazar. \n a gelince durdu.
}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DEVAMI

int main()
{
	istringstream iss{"necatiergin\nhasan"}; //dikkat

	iss.ignore(100,'\n'); // \n a kadar olanları ignore etti.

	string str;

	iss>>str;

	std::cout << str << "\n"; // hasan yazar.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	char str[10];

	std::cout << "Bir isim girin : ";
	cin>> setw(10) >> str; /// girişte en fazla 10 tane karaketer alacak
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class ingone_nline{
public:
	ignore_nline() = default;
	
	ignore_nline(int n) : mval{n} { }
	
	int get()const
	{
		return mval{1};
	}
	
	friend istream& operator>>(istream &is, ignore_nline x)
	{	
		int n = x.mval;
		while(n--)
		{
			is.ignore(numeric_limits<streamsize>::max,'\n');
		}
		return is;
	}
private:
	int mval;
};


int main()
{
	istringstream iss{"ali\nveli\nhasan\ntuncay\n"};

	string str;
	iss >> ignore_nline{3} >> str; // burada 3 tane \n ignore edilecek
	cout << str<<"\n"; 
}

Githubdaki kodlara bakılıyor.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GİRİŞİN KELİMELERE AYRILMASI MÜLAKAT SORUSU

int main()
{
	using namespace std;
	string sline;

	cout << "Bir cumle girin\n";
	getline(cin, sline);

	istringstream iss(sline);
	string word;

	while(iss >> word)
	{
		std::cout << word << "\n";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	string fullname{"necati ergin"};
	string name ,surname;

	istringstream iss {fullname}; //Bu işi yapmak için isimlendirilmiş nesne kullandık.Bunu da aşabiliriz.
	iss >> name >> surname;
	
	std::cout << "isim = " << name << "\n";
	std::cout << "soyisim = " << surname << "\n";

}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SAĞ TARAF DEĞERİ İÇİN BAKALIM

int main()
{
	string fullname{"necati ergin"};
	string name ,surname;

	istringstream{fullname}>> name >> surname; //DİKKAT.
	
	std::cout << "isim = " << name << "\n";
	std::cout << "soyisim = " << surname << "\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OSTRINGSTREAM İÇİNDE YAPILABİLİR

int main()
{
	int x = 10;
	string name {"gurbuz"};

	auto s = (ostringstream{} << name << '_' << x << ".jpg").str(); // Bu C++ 11 ile geldi

	cout << "(" << s << ")";
}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================

GET FUNCTIONU
-------------

Dosyadan veya standart inputtan okurken get kullanabiliriz.Getchar karşılığı aslında

int main()
{
	using namespace std;

	istringstream iss{"0123456789BABADEDE"};

	char c;

	while(iss.get(c)) // Referans semantiği ile get e gönderiliyor.Her turunda C yi set ediyor.return değeride istream&. operator>> gibi. akım fail olduğunda operator bool
	{					// functionu false döndürecek ve döngüden çıkacak
		
		cout << c << " ";
	}

	------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int c;

	// C deki gibi aşağıdaki gibi olabilir.Parametreyi int alıp EOF eşitliği sınanabilir.
	while((c = iss.get()) != EOF)
	{
		cout << static_cast<char>(c) << "\n"; // c int olduğundan ascideki kodunu yazacaktı bu sebeple char a cast ettik.
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Myclass{
public:
	const std::string& get_str()const &
	{
		return mlongstr;
	}

	std::string get_str()const &&
	{
		return std::move(mlongstr); // nesne hayatı biteceği için move ediyor.
	}

private:
	std::string mlongstr;

};

int main()
{
	Myclass m;

	auto &str = m.get_str(); // Burada kopyalama var.Bundan kaçınmak için getin return değerini referans yapmak.
							// Bu baya tehlikeli ama.Burada dangling reference oluşabilir.

}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================


ISTREAM ITERATOR SINIFI
-----------------------

Bir iterator adaptörü.Bunlar iterator header fileda yer alıyor. Buda böyle ostream_iteratorde öyle. Ostream_iterator kodunu daha önce yazmıştık.
Bir giriş akım nesnesini kullanarak okuma amaçlı range oluşturuyoruz.

int main()
{
	istringstream iss{"19 23 45 90 5 8 432 24 348 673 4568"};

	istream_iterator<int> end;

	cout << count_if(istream_iterator<int>{iss}, end,[](int x){return x % 2 == 0;});
}

Burada end 3 farklı yolla oluşturulabilr.
1. isimlendirilmiş nesne.Yukarıda yaptığımız buydu.Genelde tercih edilmez.
2. Geçici nesne olabilir
3. {} kullanarak gönderiyoruz.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cout << count_if(stream_iterator<int>{cin},istream_iterator<int>{}, [](int x){return x % 2 == 0;}) << "\n"; // ctrl+z

	cout << count_if(stream_iterator<int>{cin},{}, [](int x){return x % 2 == 0;}) << "\n"; // ctrl+z. diğer yazım şekli biraz populer olmuş bu
}

Birçok algoritmada kullanılabilir sadece countif değil.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunları bir containera da aktarabiliriz.

int main()
{
	istringstream iss{"19 10 12 13 23842 24 56 65"};

	vector<int> ivec{istream_iterator<int>{iss}, {}};

	std::cout << "ivec.size() = " << ivec.size() << "\n";

	sort(ivec.begin(), ivec.end()); 
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cout << accumulate(istream_iterator<int>{cin},{},0) << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	ifstream ifs("notlar.txt");

	vector<string> svec{istream_iterator<string>{ifs}, {}};

	std::cout << "svec.size() = " << svec.size() << "\n";
}	


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Hocanın bir bitcoin verilerini aldığı dısya var ona bakıyoruz

int main()
{
	ifstream ifs{"input.txt"};

	vector<double> dvec{istream_iterator<double>{ifs},{}};

	std::cout << "dvec.size() = " << dvec.size() << "\n";

	std::cout << *max_element(dvec.begin(),dvec.end()); << "\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

STRINGSTREAM ILE IKI IŞLEMDE YAPILABILIYOR.

int main()
{
	stringstream ss;
	int ival;
	
	ss >> ival;
	ss << ival; // ikiside dahil.
}


MOLA


============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================


DOSYA İŞLEMLERİ
---------------
Dosyalar üzerinde işlem yapmak için 3 sınıf var.
ofstream, ifstream, fstream sınıfı.

ofstream = ostream den kalıtımal elde edilmiş.
ifstream = istream den kalıtımda elde edilmiş.
fstream = iostream den kalıtımla elde edilmiş.

ofstream yazma amaçlı dosyaları yönetmek için kullanacağımız sınıf.
ifstream ise okuma amaçlı.
fstream hem yazma hemde okuma amaçlı.

HEPSI DEFAULT INITIALIZE EDILEBNILIYORLAR.KOPYALANAMIYORLAR AMA TAŞINABILIYORLAR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
DEFAULT INIT EDINCE HERHANGIBIR DOSYAYIU YÖNETMEYEN BIR NESNE OLUŞTURMUŞ OLUYORUZ

FSTREAM
-------
Bunların hepsi default initialize edilebiliyorlar, kopyalanamıyorlar ama taşınabiliyorlar.
Default init edildiğinde herhangibir dosyayı yönetmeyen bir sınıf nesnesi oluşturmuş oluyoruz.


int main()
{
	ofstream ofs; // Herhangibir dsyaya bağlı değil.Daha sonradan sınıfın open functını çağırıp bir dosya açıp nesneye bağlayabilirim.

	ofstream ofs("out.txt"); // Dosya yoksa oluşturacak varsa sıfırlanacak.Burada dosya text modunda açılacak ve doğrudan yazmaya müsade eden mode olacak.

	ofstream ofs("out.txt"); // ikinci parametre typedef ismi olan openmode. Openmode, bitsel masekeleri kullanabileceğimiz bir sınıf.Yani bitsel işlemlere uygun bir sınıf.
							 // Buraya birşey yazmadığımızda text modunda açıyor.
							 // Kullanacağımız constexpr static maskeler.ios veya ios_base elemanları (aynı şey)

	fstream ofs("out.txt", ios::out); // Yazma amaçlı açılıyor
	fstream ofs("out.txt", ios::in);  // Okuma amaçlı açılıyor
	fstream ofs("out.txt", ios::ate); // File pointer dosya sonunda olacak demek.
	fstream ofs("out.txt", ios::app); // Sona ekleyerek yazma amaçlı(append) 
	fstream ofs("out.txt", ios::trunc); // Dosyanın yazma amaçlı sıfırlanarak açıyor.
	fstream ofs("out.txt", ios::binary); // Binary Modda açıyor


	Ofstream için default açış modu =  ios::out | ios::trunc
	Yani böyle bir dosya varsa sıfırlanacak, yoksa oluşturulacak.

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ofstream ofs{out.txt};
	ofs << "necati ergin";

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ofstream ofs{"out.txt",ios::app}; //sona ekleme modu.yoksa yaratılacak varsa açılacak
	
	ifstream ofs{"out.txt"}; // Defaultta ios:in 

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ifstream ofs{"out.txt",ios::binary}; // default olanları tekrar yazmaya gerek yok. binary okuma amaçlı açtık.

	ifs << 12; //HATA OLUR. çünkü ifstream de bu yok >> vardı :D
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YA DEFAULT OLARAK VERIYORUZ YADA AÇIŞ MODUNUDA YAZIYORUZ.

int main()
{
	ofstream ofs{"out.txt",ios::ate | ios::binary}; // ate file pointer dosya sonunda olacak demek.
													// bunu dosyayı açıp sonuna da getirebiliriz.app ile karıştırma. app sona ekleme modunda açıyor.
	
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	fstream ofs{"out.txt"};
	fstream ofs{"out.txt", ios::in | ios:::out}; gibi hepsinin default açış modu bilgisi var.Yukarıdaki ile arasında fark yok.Default açış modu var.
	// in out append binary.... hepsi constexpr static maske bunlar

}

Yani fstream ifstream ve ofstream in default açılış modu bilgisi var.


============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================


DOSYA AÇILDI MI AÇILMADI MI

Bunun için akım nesnesinin sağlık durumuna bakıyoruz. En basiti bu.

int main()
{
	ofstream ofs{"out.txt"};

	if(!ofs) // ofs.fail() de olur
	{
		cerr << "Dosya olusturulamadi";
		return 1;
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	ifstream ifs{"yok.txt"};
	
	if(!ifs) // ofs.fail() de olur
	{
		cerr << "Dosya acilamadi";
		return 1;
	}
	std::cout << "dosya acildi\n";
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

IS_OPEN
-------

fstream ofstream ifstream e bağlanmış bir dosya var mı onu sınıyor.Bool değer gönderiyor.
Açık dosya var mı yok mu ile akımda hata var mı yok mu farklı şeyler.


int main()
{
	ifstream ifs;

	if(ifs)
	{
		std::cout << "akimda hata yok!\n"; //Akımda hata yok yazar
	}
	else
	{
		std::cout << "akimda hata var!\n";
	}


	if(ifs.is_open())
	{
		std::cout << "acik dosya var\n"; 
	}
	else
	{
		std::cout << "acik dosya yok\n"; // Açık dosya yok yazar
	}
	
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ifs.open("out.txt");
	
	if(ifs)
	{
		std::cout << "akimda hata yok!\n"; //Akımda hata yok yazar yine 
	}
	else
	{
		std::cout << "akimda hata var!\n";
	}


	if(ifs.is_open())
	{
		std::cout << "acik dosya var\n"; //Artık açık dosya var !!!!
	}
	else
	{
		std::cout << "acik dosya yok\n"; 
	}

	ifs.close();

	if(ifs.is_open())
	{
		std::cout << "acik dosya var\n"; 
	}
	else
	{
		std::cout << "acik dosya yok\n"; // Açık dosya yok yazar. 
	}


}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOSYA NASIL KAPATILACAK

Dosya açıkken sınıf nesnesi dtor çağrılırsa dosya kapatılacak
2 ihtimal var.
1- Dosya çıkken destructor çağrılırsa dosya kapatılacak.
2- Close functionu ile kapatılır.

DOSYANIN AÇILMASI ISE
1- Constructor ile açılır
2- open functionu ile açılır


int main()
{
	{
		ofstream ofs("out.txt");
	} // dosya burada kapandı.Dtor çağrıldı ve nesneyi kapattı aslında.
}

yada

int main()
{
		ofstream ofs("out.txt");
		ofs.close(); // Böylede kapatılabilir.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OFSTREAM NESNELERI NONCOPYABLE

int main()
{
	ofstream ofs{"deneme.txt"};

	ofstream fx = ofx; // SENTAKS HATASI. KOPYALAMA YAPILAMIYOR AMA TAŞIMA SEMANTİĞİNE AÇIK.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TAŞIMA SEMANTİĞİ

std::ofstream open_write_file(const std::string fname)
{
	std::ofstream ofs{fname};
	if(!ofs)
	{
		throw  std::runtime_error{"file: " + fname + " cannot created"}; //stdexcept header file eklemek gerekecek.
	}

	return ofs;
}

int main()
{
	auto ofs = open_write_file("out.txt")

	ofs << "Necati Ergin";

	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Modern C++ ile aşağıdaki gibide yazabiliriz.
	
	open_write_file("out.txt") << "haydar burak necati";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void write_close_file(std::ofstream ofs)
{
	ofs << "yazma islemi yapildi\n";
}

int main()
{
	write_close_file(open_write_file("out.txt")); // Dosyayı açıp içine yazı yazdırıp kapattık :D
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

int main()
{
	auto ofs = open_write_file("out.txt");
	for(int i = 0; i < 1000; ++i)
	{
		ofs << rname() << '\n';
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FORMATLI YAZIM ÖRNEĞI

int main()
{
	auto ofs = open_write_file("out.txt");
	
	ofs << left << setfill('.'); // right ilede yapılabilir veya başka miniplatorler de denenebilir.

	for(int i = 0; i < 1000; ++i)
	{
		ofs << setw(20) <<rname() << " " << setw(32) <<  rfname() << " " << rtown() << '\n'; 
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOSYAYA İLK 100'000 ASAL SAYI YAZDIRIYORUZ

int main()
{
	auto ofs { open_write_file("primes.txt") };

	int prime_count{};
	int x = 2;
	ofs<< left;

	while(prime_count < 100'000){
	
		if(isprime(x))
		{
			if(prime_count && prime_count % 10 == 0)
			{
				ofs << "\n";
			}
			ofs << setw(12) << x << " ";
			++prime_count;
		}
		++x;
	}
}

BURADA FORMAT KÜTÜPHANESI ÇOK DAHA PRATIK AMA HENÜZ IŞLEMEDIK ONU.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ofs{open_write_file("out.txt")};

	vector<string> svec;

	rfill(svec,5000,[]{return rname() + '_' + rfname();});

	copy(svec.begin(), svec.end(),ostream_iterator<string>{ofs,"\n"});
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ELEMANLARIN HEPSİNİ BİR STRİNG VECTORUNE ALACAĞIZ

std::ifstream open_read_file(const std::string &fname)
{
	std::ifstream ifs{fname};
	if(!ifs)
	{
		throw  std::runtime_error{"file: " + fname + " cannot created"}; //stdexcept header file ekle
	}

	return ifs;
}

int main()
{
	try{
		auto ifs{open_read_file{"olamayandosya"}}; // okuma amaçlı bu dosyayı açmaya çalıştık 
	}
	catch(const std::exception& ex)
	{
		std::cout << "exception caught :" << ex.what() << "\n"; // dosya olmadığından hata verdi
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ifs{open_read_file("out.txt")};

	vector<string> svec {istream_iterator<string>{ifs}, {}};

	std::cout << "svec.size() = " << svec.size() << "\n";

	partial_sort(svec.begin(), svec.begin() + 10 , svec.end(), greater{}); // en büyük 10 eleman

	copy(svec.begin(), svec.begin() + 10, ostream_iterator<string>{cout, "\n"}); // elemanlarıda copy algoritmasıyla ekrana yazdırıyoruz.

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YAZDIRMA TARAFINA BAKIYORUZ
Okuma dedik ama yazdırma yaptık o yüzden başlığı değiştirdim :D:D:D

ÖR:
int main()
{
	auto ofs{open_write_file("primes.txt")};

	int count = 0;
	int x{};

	while(count << 10000)
	{
		if(isprime(x))
		{
			if(count && count %10 == 0)
				ofs << "\n";
			ofs << setw(12) << x << " ";
			
			++count;
		}
		x++;
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BİR DOSYAYI YAZDIRMANIN KOLAY YOLU

Dosya sınıflarının readbuf isimli bir func ı var. Bunlar buffer sınıfı türünden bir pointer döndürüyor.
Ostream sınıfının filebuf * türünden parametresi olan bir inserterı var.Aşağıdaki gibi yazabiliriz.

int main()
{
	auto ifs{open_read_file("primes.txt")};

	cout << ifs.rdbuf();
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ifs{open_read_file("primes.txt")};
	ostream ofs{"out.txt"};

	ofs << ifs.rdbuf(); // primes tan okuyup out a yazdırdı
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ifs {open_read_file("primes.txt")};
	
	int x;
	ifs>>hex;

	while(ifs >> x)
	{
		cout << x;
		getchar();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	auto ofs{open_write_file("out.txt")};

	ofs << fixed << showpoint << setprecision(2) << left;

	for(int i = 0; i < 100 ; ++i)
	{
		ofs << setw(4) << Irand{0,9999}() << " " << Drand{0,100}() << " " << rname() << "\n";
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOSYADAKİLERİ VECTORE GÖNDERİP SONRA VECTORDEN OLUYUP BAŞKA BİR FİLE A YAZDIK.

int main()
{
	auto ifs{open_read_file("out.txt")};

	int ival;
	int dval;
	string name;

	using Person = tuple<int,double,string>;
	vector<Person> pvec;

	while(ifs >> ival >> dval >> name)
	{
		pvec.emplace_back(ival,dval,name);	
	}

	sort(pvec.begin(), pvec.end());

	auto ofs{open_write_file("person.txt")};
	ofs << left << setprecision(4) << fixed;
	
	for(const auto &[name,grade,wage] : pvec)
	{
		ofs << setw(16) << name << setw(8) << grade << wage << "\n";
	}
}


MOLA

===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================
===========================================================================================================================================================================================


OKUMAYI C DE OLDUĞU GIBI FARKLI FARKLI BİÇİMLERDE YAPABILIRIZ

Formatlı veya formatsız olarakta yapabiliriz.Mesela burada boşluklarla ayrılmış yazıları formatlı olarak okuduk ama byte byte formatsız olarakta okuyabiliriz.

get in bildirimi
----------------
istream& get(char &c); 

get dosyadaki okuduğu byte ile c yi set ediyor ve return değeri *this nesnesi.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BYTE BYTE OKUMA ÖRNEĞİ

int main()
{
	auto ifs{open_read_file("out.txt")};
	char c;

	while(ifs.get(c))
	{
		cout.put(c);
		_getch(); // conio.h
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

INT İLE YAPARSAK

int main()
{
	auto ifs{open_read_file("out.txt")};
	int c;  //DİKKAT!!

	while((c = ifs.get()) != EOF)
	{
		cout.put((char)c);
		_getch(); // conio.h
	}
}

Getin farklı overloadları var.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DOSYADAN SATIR SATIR OKUMAK IÇIN

&istream& getline(ifs,sline);

int main()
{
	auto ifs{open_read_file("out.txt")};

	string sline;

	while(getline(ifs,sline))
	{
		cout << "(" << sline << ")\n";
		_getch();
	}
}

getline ında birden fazla overloadu var

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DELİMİTER OLARAK NEW LİNE YERINE BAŞKA KARAKTER VERDİK. BAŞKA BİR OVERLOAD BU. 

&istream& getline(ifs,sline);

int main()
{
	auto ifs{open_read_file("out.txt")};

	string sline;

	while(getline(ifs,sline,'.'))
	{
		cout << "(" << sline << ")\n";
		_getch();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KLASIK IDIYOM

int main()
{
	auto ifs{open_read_file("out.txt")};
	string sline;
	vector<string> svec;

	while(getline(ifs,sline))
	{
		//svec.push_back(sline); // Burada copy semantics çalışır
		svec.push_back(std::move(line)); // Burada ise taşıma semantiği çalışır.Move from state teki nesneyi tekrar kullandık ama tekrar değer yerleştiriyoruz her turda.
	}
	std::cout << "svec.size() = " << svec.size() << "\n";
}

============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================
============================================================================================================================================================================================


BINARY MOD - FORMATSIZ İŞLEMLER 
-------------------------------
Dosyayı text ve binary modda açmak farklı şeyler.Linuxta bu fark bu kadar önemli değil ama windowsta önemli.
Dosya text modunda açınca windowsta new line 13 ve 10 karakterleri yazıyor. Okurkende bu 13 ile 10 yanyana bytelar ise bunu 10 olarak okunuyor. birde 26. karakter sorunu var.
ctrl + z yani dosya sonu muamelesi yapıyor 26. karakteri görürse.

int main()
{
	ifstream ifs{"out.txt", ios::binary}; //out.txt yi binary okuma modunda açtık.
}

fread karşılığı C++ta read
fwrite karşılığı C++ta write


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
İLK BIR MILYON ASAL SAYIYI FORMATSIZ OLARAK PRIMES.DAT DOSYASINA YAZALIM
4 MILYON BYTE OLACAK BU DOSYANIN BÜYÜKLÜĞÜ EĞER İŞLEMLERİ DOĞRU YAPTIYSAK

int main()
{
    std::ofstream ofs{"primes.dat", std::ios::binary};
    if(!ofs){
        std::cerr << "dosya olusturulamadi\n";
        return 1;
    }
    int prime_count{};
    int x;
    while(prime_count < 1'000'000)
    {
        if(isprime(x))
        {
            ofs.write(reinterpret_cast<char *>(&x),sizeof(int)); // reinterpret_Cast i kullanmamız gereken ender durumlardan biri.
            							 // Akımdaki karakter türü char olduğundan char * parametre.Dolayısı ile x in adresinden okuma yapacak
       								 // x int olduğundan int * ı göndermiş olurduk. Bu sebeple reinterpret_cast kullanıyoruz.
           							 // ikinci parametre dosyaya kaç byte yazılacağı sizeof x veya sizeof int.

            ++prime_count;
        }
        ++x;
    }
}
4 milyon bytelık dosya oluştu şimdi.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OKUMA TARAFI
------------

int main()
{
	ifstream ifs{"primes.dat", ios::binary};
	ifs(!ofs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}
	
	int x;

	while(ifs.read(reinterpret_cast<char *>(&x),sizeof(x)) // Formatlı değil data binary modda yazıldı ve binary modda açıldı artık, o yüzden read kullanıyoruz !!!!
	{														// read in return değeri istream&. HEr turda 4 byte okuyacak.
		cout << x << " ";
		_getch();
	}

	------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	TEK INT DEĞIL DAHA FAZLASINI OKUYABILIRDIK

	constexpr int size{10};
	int a[size];

	while(ifs.read(reinterpret_cast<char *>(a),sizeof(a)) // Döngünün her turunda bu diziyi dolduracak kadar byte okumuş olacak.C deki generic programming i hatırlattı bu.
	{
		print(begin(a), end(a)); // bunu hoca yazdı print algoritması
		_getch();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ARRAY ILE YAPARSAK

int main()
{
	ifstream ifs{"primes.dat", ios::binary};
	ifs(!ofs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}

	constexpr int size{10};
	array<int,size>ar;

	while(ifs.read(reinterpret_cast<char *>(ar.data()),sizeof(int) * size)
	{
		print(begin(a), end(a)); // bunu hoca yazdı print algoritması
		_getch();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Vector ile yaparsak

int main()
{
	ifstream ifs{"primes.dat", ios::binary};
	ifs(!ofs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}

	array<int>ivec(100);

	while(ifs.read(reinterpret_cast<char *>(ivec.data(),sizeof(int) * ivec.size())
	{
		print(begin(ivec), end(ivec));
		_getch();
	}
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PRIMES.DAT TA KAÇ ASAL SAYI OLDUĞUNU BILMEDIĞIMIZDEN KAÇ BYTE KAÇ BYTE OKUMAMIZ GEREKIYOR ONU BILMIYORUZ BU YÜZDEN SINIFA GCOUNT FUNC EKLEMIŞLER

Gcount formatsız okuma işlemi yaptıktan sonra kaç byte okuduğunu geri veriyor.

int main()
{
	ifstream ifs{"primes.dat", ios::binary};
	ifs(!ifs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}
	
	int x;
	ifs.read((char *)&x, sizeof(x));
	cout << ifs.gcount() << "\n"; // gcount değeri 4 olmalı

	-----------------------------------------------------------------------------------------------------------------------------------------------------------------

	int a[10];

	ifs.read((char *)a, sizeof(a));
	cout << ifs.gcount() << "\n"; // Dizinin tamamını doldurduysa bu durumda gcount değeri dizinin sizeof u olacak

	//Mesela bir okuma yaptık ama kaç adet okuduğumuzu bilmemiz gerekiyor.Bu tip senaryolarda işe yarıyor.
}

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


using namespace std;

int main()
{
	ifstream ifs{"primes.dat", ios::binary};
	ifs(!ifs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}
	
	ofstream ofs{"primescopy.dat", ios::binary};
	ifs(!ofs){
		cerr << "dosya olusturulamadi\n";
		return 1;
	}

	constexpr size_t size{1024};
	unsigned char buffer[size]; // döngünün her turunda bu buffera yazılacak

	while(ifs.read(reinterpret_cast<char *>(buffer), size)) // char olduğundan dizi boyutu doğrudan size :D
	{
		ofs.write(reinterpret_cast<char *>(buffer), ifs.gcount()); // ifs ile read ettiklerini ofs.write ile yazıyor ve count u da argüman veriyoruz.
	}

	//cevap tam 4 milyon çıkmadı hocada 3.997 gibi birşeydi sanırım bende test edeceğim.
}

*/
