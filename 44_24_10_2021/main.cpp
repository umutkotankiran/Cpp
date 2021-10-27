/*

CHRONODA KALDIK

Modern C++ ile eklendi.Tarih zaman ilke ilgili destek veriyor. C deki time ile işbirliği halinde çalışıyor ve time dan daha geniş ve daha fazla alanda iş yapıyor.
Burada 3 tane birlirleriyle ilişkili tür var.Bir saat bize bir origin veriyor timepoint olarak ve bize bununla birlikte bir duration veriyor.

Buradaki türler
1 - Duration : Süre epoch ile ilgili değilse, doğrudan kendisiyse bunada duration deniyor.
2 - Time_point : Epochtan geçen süre olarak tarih zamanda bir noktayı belirliyor.
3 - Clock türleri : 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DURATION TEMPLATE

template <typename Rep, typename R>
struct Duration{

};

int main()
{
	using namespace std;
	using namespace std::chrono; // isimleri nitelemeden kullanmak için bunu yapıyoruz.
	
	duration<int, std::ratio<1,10>> x; // x nesnesi tik birimi int ve her bir tik saniyenin 1/10 u kadar
	
	//ÇOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Burada x.count dediğimde aslında x e atanan değeri elde ediyorum.Template in birinci tür parametresi bu değer.
	// bu durationun değeri ise x.count() * ratio<x,y> değeri olacak. Aynı şeyler değil yani

}


STANDART KÜTÜPHANE BAZI TÜREŞ ISIMLERI BILDIRMIŞ. BUNLAR SIK KULLANILAN SÜRE DEĞERLERI IÇIN
Bunlar bir tamsayı veya reel sayı türünden değişken compile time yöntemleriyle ilave maliyet getirmeden sarmalanmış halinden başka birşey değil.

int main()
{
	std::cout << typeid(milliseconds).name() << "\n"; // duration<int64, ratio<1,1000>> açılımını verir.
													  // Burada milliseconds ile duration<long long , std::milli>  demek aynı şeyler
													  // std::milli de ratio<1,1000> açılımı demek
 	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	HOURS

	std::cout << typeid(hours).name() << "\n"; // duration<int, std::ratio<3600,1>> demek. ratio<3600> ile ratio<3600,1> aynıydı 

	------------------------------------------------------------------------------------------------------------------------------------------------------
	BU TÜRDEN DEĞİŞKENLER TANIMLAYIP DEĞER VEREBİLİRİM

	seconds s; // DIKKAT GARBAGE VALUE. KULLANMAK UB
	std::cout << s.count() << "\n"; // UB

	------------------------------------------------------------------------------------------------------------------------------------------------------
	SANIYEYİ INITIALIZE EDELIM

	seconds s1{251}; // 
	std::cout << s1.count() << "\n"; // 251

	------------------------------------------------------------------------------------------------------------------------------------------------------
	NORMAL PARANTEZDE OLUR

	seconds s2(543); // Küme paranetezi değilde normal parantezde olur
	std::cout << s2.count() << "\n"; // 543
	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	CONSTRUCTOR EXPLICIT

	seconds s1 = 33; //CTOR EXPLİCİT. GEÇERSİZ
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LITERAL OPERATOR
----------------
45s demek 45 saniye demek. Peki bu nasıl oluyor. 123min bu nasıl 123 dakika oluyor.
456ms , 643us bu microsaniye demek, 333ns

45s diyince bir func çağrılıyor. Bu constexpr bir function.Function yapısı yine bir operator functionu fakat modern C++ ta eklendi.
Son ekin önündeki değeri argüman olarak göndermiş oluyoruz. İstersen kendi sabitlerimizide bu şekilde oluşturabiliyoruz.

operator""s(45) ...

int main()
{
	using namespace std;
	// 45s in çalışması için std::chrono veya std::literals in görünür olması gerekiyor.

	std::chrono::seconds s = 45s; // şuanda 45s görülmüyor sentaks hatası

	------------------------------------------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace std::chrono; // not bunlar inline namespace 

	std::chrono::seconds s = 45s; // Şuanda geçerli

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto s = 45s;

	------------------------------------------------------------------------------------------------------------------------------------------------------

	milliseconds ms;

	ms = 456s; // bu dönüşüm otomatik yapılacak

	std::cout << "ms.count " << ms.count()  << "\n"; 456000 çünkü bu kadar millisecond ediyor.

	------------------------------------------------------------------------------------------------------------------------------------------------------

	ms = 456; // doğrudan primitive türe atama yapılamıyor dönüşüm yok

}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

BİR SÜRE DEĞERİNİ KAVRAMAK İÇİN BİR FUNC ŞABLONU YAZALIM

template <typename Rep, typename P>
std::ostream& operator<<(std::ostream &os, const std::chrono::duration<Rep,P> &x)
{
	return os << "[" << x.count() << "] * (" << P::num << "/" << p::den <<")]";
}

int main()
{
	using namespace std;
	
	using namespace std::chrono;

	cout << 45ms << "\n"; // 45 * 1/1000 yazar.  Functionun 1. parametresine cout geçildi, 2. parameresine durationa da 45ms geçtik
							// Derleyici compile timeda Rep ve P nin ne olduğunu anlayacak tabi.

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	cout << 12h << "\n"; // 12 * 3600/1 yazar. Yani tik birimi 3600sn ve bundan 12 tane var.

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	cout << 4560ns << "\n"; // 4560 * 1 / 1'000'000'000

	------------------------------------------------------------------------------------------------------------------------------------------------------
	KENDİ TÜRÜMÜZÜ OLUŞTURALIM

	using halfsec = std::duration<int, ratio<1,2>>;

	cout << halfsec{45} << "\n"; // 45 * 1/2

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	BUNLARI İSTEDİĞİMİZ GİBİ ARİTMETİK İŞLEMLERE SOKABİLİRİZ.

	using frame = duration<int,ratio<1,60>>;

	cout << 5782ms + 12s + 2h + 45min + halfsec{453} + frame{59} << "\n";  // compile time teknikleriyle tüm türlerin common type ı elde ediliyor.
																			//30435796 * 1/3000 
}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

KARŞILAŞTIRMA İŞLEMLERİDE YAPILABİLİR

int main()
{
	using namespace std;
	using namespace std::chrono;

	cout << boolalpha << (1239ms > 123456us) << "\n"; // true

	------------------------------------------------------------------------------------------------------------------------------------------------------

	auto msec = 765423ms;

	if(msec < 2min)
	{
		//koşul sağlarsa girecek 
	}
}

===============================================================================================================================================================================================
===============================================================================================================================================================================================

DÖNÜŞÜMLER
----------

fine = ince anlamında. hassasiyeti daha fazla demek
coarse = kaba. hassasiyeti daha kötü

Dakika mı saat mi daha fine. dakika daha fine

Daha coarse bir türden daha fine bir türe dönüşüm her zaman otomatik olarak yapılıyor.

int main()
{
	using namespace std;
	using namespace std::chrono;
	
	auto x = 456s;
	milliseconds y = x; // dönüşüm daha coarse türden daha fine türe yapıldığından dönüşüm yapılır

	std::cout << y.count() << "\n"; // 456000 çıkar
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	KABA TÜRDEN HASSAS/İNCE TÜRE OTOMATİK DÖNÜŞÜM VERİ KAYBINDAN ÖTÜRÜ YOK.SENTAKS HATASI

	nanoseconds ns{123123213};

	milliseconds ms = ns; // SENTAKS HATASI. DAHA İNCE TÜRDEN DAHA KABA TÜRE VERİ KAYBI OLDUĞUNDAN HATA

	------------------------------------------------------------------------------------------------------------------------------------------------------

	BUNU DÖNÜŞÜMÜ YAPAN OPERATOR FUNC VAR. DURATION_CAST
	DURATION CAST ASLINDA NESNEYİ CAST EDİYOR. AŞAĞIDAKİ ÖRNEKLERDEN BİRİNDE COUNT U CAST ETMEYE ÇALIŞTIĞIMDA SENTAKS HATASI ALDIM NORMAL OLARAK

	nanoseconds ns{123123213};
	
	milliseconds ms = ns; // SENTAKS HATASI

	minutes min = ns; // SENTAKS HATASI

	hours h = ns; // SENTAKS HATASI

	------------------------------------------------------------------------------------------------------------------------------------------------------

	LEGAL HALE GETİRİLİYOR.
	BURADA YUKARI VEYA AŞAĞI YUVARLAMA YOK.GERİ KALAN BUDANIYOR

	nanoseconds ns{123123213};
	
	std::cout << "ns count = " << ns.count() <<"\n";

	milliseconds ms = duration_cast<milliseconds>(ns); // GEÇERLİ

	std::cout << "ms count = " << ms.count() <<"\n";
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	SANİYE İÇİN YAPALIM AYNISINI

	seconds min = duration_cast<minutes>(ns); // GEÇERLİ

	std::cout << "min count = " << min.count() <<"\n";

	------------------------------------------------------------------------------------------------------------------------------------------------------

	DAKİKA İÇİN YAPALIM AYNISINI

	minutes min = duration_cast<minutes>(ns); // GEÇERLİ

	std::cout << "sec count" << sec.count() <<"\n";

	------------------------------------------------------------------------------------------------------------------------------------------------------

	DÖNÜŞÜMLERİN YUKARI VEYA AŞAĞI YAPILMASI İÇİN FLOOR VEYA CEIL FUNCLARINI ÇAĞIRABİLİRİZ.

	nanoseconds ns{123123213};

	std::cout << "ns.count() = " << ns.count() << "\n";  // ns e bakıldı
	millisecond ms = duration_cast<milliseconds>(ns);
	std::cout << "ms.count() = " << ms.count() << "\n";  // ms e bakıldı burada da 


	ms = floor<milliseconds>(ns);
	std::cout << "ms.count() = " << ms.count() << "\n";  // Aşağı yuvarlandı
	
	ms = ceil<milliseconds>(ns);
	std::cout << "ms.count() = " << ms.count() << "\n";  //  Yukarı yuvarlandı

	//birde round var o da 5 ten büyükse yukarı küçükse aşağı yuvarlıyor.ms = round<milliseconds>(ns);
	

}

FLOOR VE CEILING C++14 TE EKLENDI

==============================================================================================================
==============================================================================================================
==============================================================================================================
BIR DURATION BAŞKA BIR DURATIONA DÖNÜŞECEKSE DÖNÜŞTÜRELIM. BU ZATEN VERI KAYBI OLACAKSA SENTAKS HATASI OLUYOR.
BUNU BILEREK YAPTIYSAK DURATIONCAST KULLANACAĞIZ. DAHA KABA TÜRDEN DAHA INCE TÜRE DÖNÜŞÜM HEP VAR.
BIRDE COUNT TÜRÜ GERÇEK/REEL SAYI TÜRÜYSE HERZAMAN OTOMATIK DÖNÜŞÜM VAR.
==============================================================================================================
==============================================================================================================
==============================================================================================================

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR
int main()
{
	using namespace std;
	using namespace std::chrono;

	nanoseconds ns {45646895123};

	using dh = duration<double,ratio<60*60>>;
	dh x = ns; // geçerli

	std::cout << "x.count() = " << x.count() << "\n";  // Yani 45646895123 nanosaniye ---> 0.0126797 bu kadar saat çıktı.

	------------------------------------------------------------------------------------------------------------------------------------------------------
	BÖYLEDE YAZILABİLİR.

	nanoseconds ns {45646895123};

	duration<double,ratio<60*60>>x {ns};

	cout << x << "\n"; // bu inserterı biz yazdık.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AŞAĞIDAKİLER GİTHUB ÖRNEKLERİ


#include <chrono>
#include <iostream>

int main()
{
	using namespace std::chrono;

	//seconds s1 = 345; //gecersiz çünkü ctor explicit
	seconds s2(345); //ok
	std::cout << "s2.count() = " << s2.count() << "\n";
	seconds s3{ 761 }; //ok
	std::cout << "s3.count() = " << s3.count() << "\n";
	seconds s4{}; // value init ile 0 sn olur
	std::cout << "s4.count() = " << s4.count() << "\n";
	seconds s5; //Garbage/Indetermined value
	//std::cout << "s5.count() = " << s5.count() << "\n"; //ub
	seconds s6 = 675s;
	std::cout << "s6.count() = " << s6.count() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AYRIŞTIRMA ÖRNEĞİ PRODDA ÇOK KULLANILIYOR

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
	long long msec;

	cout << "mili saniye olarak sureyi girin: ";
	cin >> msec;
	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	milliseconds ms{ msec };
	hours hrs{ duration_cast<hours>(ms) }; // Duration cast ile hour a dönüştürdük. Kalan kısım otomatik budanacak.Geri kalan kısımlarda gerekiyor bana ayrıştıracağız çünkü

	------------------------------------------------------------------------------------------------------------------------------------------------------
	minutes mins{ duration_cast<minutes> (ms % 1h) }; // Dakika için 1 saate bölümünden kalanda millisecond. Bunuda dakikaya cast ediyoruz. Burada doğrudan static cast kullanılamaz
	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	seconds sec{ duration_cast<seconds>(ms % 1min) }; // millisecond u 1 dakikaya böldük geriye kalan kısmı saniyeye cast ettik

	------------------------------------------------------------------------------------------------------------------------------------------------------
	milliseconds msx(ms % 1s); // burada da saniyeye böldük cast e gerek kalmadı. zate millisecond istiyoruz.

	------------------------------------------------------------------------------------------------------------------------------------------------------
	if (hrs.count())
		cout << hrs.count() << " saat ";

	if (mins.count())
		cout << mins.count() << " dakika ";

	if (sec.count())
		cout << sec.count() << " saniye ";

	if (msx.count())
		cout << msx.count() << " milisaniye\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KARŞILAŞTIRMA ÖRNEĞi

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
	using dsec = duration<double>; // bu demek duration<double,ratio<1>> demek aynı şeyler

	cout << boolalpha;
	cout << (543ms == 543000us) << "\n"; // true
	cout << (543ms < 543001us) << "\n"; // true
	cout << (1s > dsec{ 0.999 }) << "\n"; // true
	cout << (dsec{ 0.5 } < 499ms) << "\n"; // false
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;
using halfsec = duration<int, ratio<1,2>>;

int main()
{
	seconds sec{7623};
	std::cout << "sec.count() = " << sec.count() << "\n"; //7623
	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	++sec;
	std::cout << "sec.count() = " << sec.count() << "\n"; //7624

	------------------------------------------------------------------------------------------------------------------------------------------------------
	sec+= 1min; // 60 saniye arttı
	std::cout << "sec.count() = " << sec.count() << "\n"; //7684

	------------------------------------------------------------------------------------------------------------------------------------------------------
	sec+=halfsec{10}; //daha ine türden daha kaba türe dönüşüm olduğundan sentaks hatası oldu. 

	------------------------------------------------------------------------------------------------------------------------------------------------------
	halfsec x{1000}; 
	
	x += 20s;
	std::cout << "x.count() = " << x.count() << "\n"; //1040. Çünkü 20 saniye demek 40 yarım saniye demek.Count değeri 40 arttı.
	

}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

SÜRE ÖLÇÜMÜ

3 tane saat türü veriyor bize dil. C++20 hariç. C++20 de yenileri geldi.

System_clock : Ayarlanabilir saat yani ayarlanabilir.Sistem saati değişince system clockta ona göre değer verecek.Gerçek dakika saniye gün işlemleri bununla yapılıyor.
Steady_clock : Ayarlanamayan saat.Sistem saati değiştirsekte bu değişmeyecek.Monotonik saat.Kullanım amacı süre ölçmek
High_resolution_clock : Aslında yukarıdakilerden birinin eş ismi

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SYSTEM CLOCK
------------
System clock ın bir time point türü var.Bir duration türü var.
Now bir function. is_steady boolean türünden bir değer. steady clock ise is_steady true olmak zorunda, değilse false olmak zorunda.

int main()
{
	using namespace std;
	using namespace std::chrono;
	
	system_clock:: içindekilere baktık.

	system_clock::time_point --> saatin bize verdiği timepoint değeri
	
	//time_point<system_clock> <---> system_clock::time_point aynı şey 

	------------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << typeid(system_clock::time_point).name() << "\n"; 
	time_point<system_clock,system_clock::duration> // time_point<system_clock> te yazabilirdik default tempalte tür parametresi var.

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	Time point bir süre değil, tarih zamanda bir nokta. 2 time point birbirinden çıktığında duration elde ediliyor.

	time_point + duration = time_point
	time_point - duration = time_point
	time_point - time_point = duration
	time_point > time_point 
	time_point < time_point    			BUNLAR VAR

	is_same_v<time_point<system_clock>,system_clock::time_point>; //true yazar

	------------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << typeid(system_clock::time_point).name() << "\n"; // chrono::time_point<chrono::system_clock,chrono::duration<__int64,ratio<1,10000000> > >
	std::cout << typeid(time_point<system_clock>).name() << "\n"; // chrono::time_point<chrono::system_clock,chrono::duration<__int64,ratio<1,10000000> > >  YUKARIDAKİ İLE AYNI. 
	std::cout << typeid(system_clock::duration).name() << "\n";   // chrono::duration<__int64,ratio<1,10000000> > // saniyenin 10 milyonda biri

	std::cout << typeid(steady_clock::duration).name() << "\n";   // chrono::duration<__int64,ratio<1,1000000000> >. BURASI STEADY CLOCK !!!! Saniyenin milyarda biri 

}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

NOW
---
Sınıfın now isimli funcı var. Bu epoch tan geçen süreyi timepoint olarak veriyor.
Şimdiki zamanın timepointi.

int main()
{
	using namespace std;
	using namespace std::chrono;
	
	std::cout << system_clock::now().time_since_epoch().count() << "\n"; 
	// time_since_epoch duration döndürüyor.Count ilede epoch tan geçen süreyi verecek.Tamamen system clock ın durationunun ne olduğuna bağlı aslında.
	// Bu saatin epoch undan bu func çağrılana kadar saniyenin 10 milyonda birinden 16351563615147632 kadar geçmiş.
	//Bu duration değeri olduğundan bunu saat saniye ... olarak yazdırabilirim
	
	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	milliseconds x = system_clock::now().time_since_epoch().count(); // SENTAKS HATASI ÇÜNKÜ SAĞ TARAF DAHA İNCE BİR TÜR. CAST EDELİM
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	milliseconds x = duration_cast<milliseconds>(system_clock::now().time_since_epoch()); // DİKKAT DURATION CAST İLE COUNT CAST EDİLMİYOR !!!!!!!
	std::cout << x.count() << "\n"; // epochtan bu kdar ms geçmiş.Epoch ta 1.1.1970 genelde oluyor.
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << (duration_cast<hours>(system_clock::now().time_since_epoch())).count(); // DOĞRUDAN EPOCH TAN GEÇEN SAATI YAZDIRDIK.
	std::cout << (duration_cast<minunes>(system_clock::now().time_since_epoch())).count(); // DOĞRUDAN EPOCH TAN GEÇEN DAKIKA YAZDIRDIK.
	std::cout << (duration_cast<years>(system_clock::now().time_since_epoch())).count(); // 51 YIL. 1.1.1970 TEN BU YANA GEÇEN SÜRE
}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

2 TİMEPOİNTİ ÇIKARTIRSAM ARADAKİ DURATİONU BULURUM. BİRİMİDE SAATİN DURATION BİRİMİ NE İSE O ÇIKACAK
KENDİ İSTEDİĞİM DURATIONA DÖNÜŞTÜRMEK İÇİN İNCE TÜRDEN KABA BİR TÜRE CAST YAPABİLİRİZ YADA KABADAN İNCEYE ZATEN OTOMATİK DÖNÜŞÜM VAR.

ÖR:

#include <chrono>
#include <iostream>
#include <algorithm>
#include "nutility.h"

int main()
{
	vector<int> ivec;

	auto tp_start = steady_clock::now(); // Kesinlikle steady clock kullanmalıyız. System clock değil !!!!!

	rfill(ivec, 1'500'000, Irand{ 0,100000 });
	sort(ivec.begin(), ivec.end());

	auto tp_end = steady_clock::now();  // Kesinlikle steady clock kullanmalıyız. System clock değil !!!!!

	//std::cout << (tp_end - tp_start); // tik birimi saniye mi 1000 de biri mi ne IMPLEMENTATION DEFINED

	//milliseconds{tp_end - tp_start}; // SENTAKS HATASI çünkü içerideki tür millisec ten daha hassas

	std::cout << duration_cast<milliseconds>(tp_end - tp_start).count() << "ms" << "\n"; // Milliseconds türünden
	std::cout << duration_cast<microseconds>(tp_end - tp_start).count() << "us" << "\n"; // Microseconds türünden

	std::cout << duration<double>{tp_end - tp_start}.count() << "\n";
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	vector<int> ivec;

	auto tp = steady_clock::now();

	if(tp < tx){
		
	}
	//Böyle bir kod yazılabilir.2 time point kıyaslanabilir.


}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

BURADAKİ ÖRNEKLER GİTHUBDAN

1.
ÇOK KULANILAN BİR İDİYOM

using namespace std;
using namespace chrono;

int main()
{
	vector<int> ivec;
	mt19937 eng;
	uniform_int_distribution<> dist{ 0, 1000000 };
	cout << "islem basliyor\n";
	auto tp_start = steady_clock::now(); // işlem başlamadan önce timepoint aldık.

	rfill(ivec, 10'000'000, [&] {return dist(eng); }); // görülen isimleri referans ile capture ettik
	sort(ivec.begin(), ivec.end()); // sıralama yapıldı

	auto tp_end = steady_clock::now(); // işlem bitince timepoint aldık
	cout << "islem sona erdi\n";

	cout << "sure : " << duration_cast<milliseconds>(tp_end - tp_start).count() << " milisaniye \n"; // hem millisecond olarak yazdırdık
	cout << "sure : " << duration<double>(tp_end - tp_start).count() << " saniye \n"; // hemde double olarak yazdık.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2.

TO_TIME_T
Time pointi, time_t ye döndürüyor

using namespace std;
using namespace chrono;

int main()
{
	system_clock::time_point tpx; //default ctor (epoche)

	auto timer = system_clock::to_time_t(tpx); // TO_TIME_T FUNCTIONU, TIME POINTI TIME_T YE DÖNDÜRÜYOR.
	cout << ctime(&timer) << "\n";

	------------------------------------------------------------------------------------------------------------------------------------------------------

	std::cout << system_clock::to_time_t(system_clock::now()) << "\n";  // böylede yazılabilir.

	------------------------------------------------------------------------------------------------------------------------------------------------------

	C FUNCTIONU İLE BİRLİKTE KULLANALIM

	auto t = system_clock::to_time_t(system_clock::now());
	cout << ctime(&t);

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. 

BİRAZ C HATIRLATMASI OLACAK

void print_time(const time_t& timer)
{
	static const char* const pmons[] = {
	"Ocak",	"Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"
	};

	static const char* const pdays[] = {
	"Pazar","Pazartesi","Sali","Carsamba","Persembe","Cuma","Cumartesi",
	};

	auto p = localtime(&timer);
	cout.fill('0');
	cout << setw(2) << p->tm_mday << " " << pmons[p->tm_mon] << " " << p->tm_year + 1900 << " " <<
		pdays[p->tm_wday] << " " << setw(2) << p->tm_hour << ":" << setw(2)
		<< p->tm_min << ":" << setw(2) << p->tm_sec << "\n";
}

// AŞAĞIDA TIMEPOINT'TEN DURATION ÇIKARTTIĞIMIZ BİR ÖRNEK VAR 
int main()
{
	auto tp_now = system_clock::now(); // ŞIMDIKI SAATIN TIME POINTI. EPOCH TAN GEÇEN ZAMANI TIMEPOINT OLARAK VERIYORDU.

	print_time(system_clock::to_time_t(tp_now)); // BUNU TIME_T TÜRÜNE ÇEVIRILMIŞ HALINI, PRINT_TIME A GÖNDERDI. TIMEPOINTE ILIŞKIN TARIH ZAMAN DEĞERINI YAZDIRDIK
	int min;
	cout << "kac dakika : ";
	cin >> min;
	time_t timer = system_clock::to_time_t(tp_now - minutes{ min }); // TIMEPOINTTEN BU KADAR DAKIKA ÇIKARTI YINE TIME
	cout << min << " dakika oncesi : ";
	print_time(timer);	// MIN KADAR DAKIKA ÖNCESINI YAZIYOR
	timer = system_clock::to_time_t(tp_now + minutes{ min }); // MIN KADAR DAKIKA SONRASINI TIMER A VERDIK
	cout << min << " dakika sonrasi : ";
	print_time(timer); // MIN KADAR DAKIKA SONRASINI YAZDIRDI
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4.
IDIYOM

int main()
{
	mt19937 mt{1687} ; Seed değeri 1687 olacak aşağıda ise time a ilişkin bir değer.

	mt19937 eng(static_cast<unsigned>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count())); //time_since_epoch bir duration döndürüyor. 
	// {} kullanmadım init ederken narrowing conversion sentaks hatası çünkü										// bu durationunda count funcı çağrılıyor.

	for(int i = 0; i < 10;++i)
	{
		cout << eng() % 1000 << "\n"; 
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5.

int main()
{ 
	auto tp = system_clock::now(); // bir timepoint. yani şimdiki zamanın timepointi

	cout << tp.time_since_epoch().count() << "\n"; // time_since_epoch bir duration döndürüyor. count ta bu durationu longlong veya int64 türünden bir tamsayıya dönüştürüyor.
	using Days = duration<int, ratio<24 * 60 * 60>>;  // Yukarıdaki durationu güne çevirdik bu sayede epoıchtan kaç gün geçtiğini bulduk
	
	cout << duration_cast<Days>(tp.time_since_epoch()).count() << "\n"; // epochtan geçen günsayısı yazıldı
	cout << duration_cast<Hours>(tp.time_since_epoch()).count() << "\n"; // epochtan geçen günsayısı yazıldı
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

6. 
YİNE C HATIRLATMASI

#include <iostream>
#include <ctime>
#include <chrono>

int main()
{
	using namespace std;
	using namespace std::chrono;

	tm timeinfo{}; // struct tm türü C deki

	timeinfo.tm_year = 2000 - 1900;   // 2000 yili. 1900 den fazlasını tutuyordu
	timeinfo.tm_mon = 0;      // ocak
	timeinfo.tm_mday = 1;     // ayin 1'i
	timeinfo.tm_hour = 0;     // saat 00
	std::time_t tt = std::mktime(&timeinfo); // Bunlar C den

	system_clock::time_point tp = system_clock::from_time_t(tt);
	system_clock::duration dt = system_clock::now() - tp;

	auto nhours = duration_cast<hours> (dt);

	std::cout << "1/1/2000'den gecen gun sayisi: " << nhours.count() << "\n";
}

NOT : 
TO_TIME_T, TIME_T YE DÖNÜŞTÜRÜYOR
FROM_TIME_T, TIME POINTE DÖNÜŞÜRÜYOR.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

7.
CPPREFERENCE TAN ALMIŞ HOCA.

BURADA FARKLI FUNCLAR VAR !!!!!!!!!!!!!!!!

int main()
{
	//std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24)); // 24 SAAT ÖNCEKI TIME_T DEĞERINI HESAPLIYORUZ.
	std::cout << "One day ago, the time was " << std::put_time(std::localtime(&now_c), "%F %T") << '\n';
}

CHRONO ŞİMDİLİK BU KADAR

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================


LITERAL OPERATOR FUNCTIONLARI
-----------------------------

C++11 ile eklenen en önemli araçlardan biri user-defined literal oluşturmak.
Öyle bir sabit oluşturuyoruzki bu sabit bir user defined türden olabiliyor.
cm, km, kg, mil, kb .... herşey olabilir.

Kendi türümüzü ve kendi sabitlerimizi oluşturabiliyoruz.Date türü gibi, metre türü gibi.

Standart kütüphane kendi türlerini rezerve etmiş bu yüzden bizim türlerimiz underscore ile başlayacak bu zorunlu.

using namespace std;
using namespace std::chrono;

int main()
{
	12ms
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA 2 TARZ FUNCTION YAZMA ŞANSIMIZ VAR 
- COOKED 
- UNCOOKED

COOKED
------
Cooked ta function parametreik yapısı belirli kalıplara uyması gerekiyor.Mesela reel sayı parametre için parametre long double olacak
Tamsayı için unsigned long long türünden olması zorunlu.Yani belirli parametre tipleri var func parametresi o türlerden olması gerekiyor.

PARAMETRELER AŞAĞIDAKİLER OLABİLİR
----------------------------------
( const char * )	(1)
( unsigned long long int )	(2)
( long double )	(3)
( char )	(4)
( wchar_t )	(5)
( char8_t )	(6)	(since C++20)
( char16_t )	(7)
( char32_t )	(8)
( const char * , std::size_t )	(9)
( const wchar_t * , std::size_t )	(10)
( const char8_t * , std::size_t )	(11)	(since C++20)
( const char16_t * , std::size_t )	(12)
( const char32_t * , std::size_t )	(13)


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AĞIRLIK BIRIMLERIYLE ILGILI SABITLER OLUŞTURALIM

456.87_g mesela 456_87 gramı temsil etsin ve double türden olsun.
456.87_kg
456.87_mg
456.87_ug


int main()
{
	auto val = 456.87_g;
}


FUNCTİON TANIMLANMASI

İsmini değiştiremiyoruz. operator""_g bu formatta olacak.Return değeri void olabilir.
Parametreyi ise istediğimiz gibi seçemiyoruz.YUKARIDA YAZDIM

double operator""_g(long double val)   // buradaki parametre türleri belirli başlılar olabilir. 
{
	std::cout << "operator""_g(long double) called\n";
	std::cout << "val = " << val << "\n";
	return 1.1; // çalıştığı belli olsun diye yazdırdık anlamlı olduğundan değil.
}

int main()
{
	auto x = operator""_g(456.98); // Parametreye 456.98 geldi. çağrılan func ise operator""_g. Böyle çağırmayacağız ama
	std::cout << "x = " << x << "\n";

	------------------------------------------------------------------------------------------------------------------------------------------------------
	
	AŞAĞIDAKI GIBI YAPILABILIYOR. ASIL OLAYDA BU

	765.12_g;  // DERLEYICI ISIM ARAMAYLA BU FUNC I BULACAK. 765.12 YI OPERATOR""_G YE ARGÜMAN GÖNDERECEK OPERATOR""_G(765.12); YAZACAK YANI ASLINDA !!!!!

	std::cout << "x = " << x << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İŞİMİZE YARAYAN FUNCA BAKALIM
Functionların constexpr olması gerekmiyor ama sabit ifadesi olarak kullanmak için böyle yaptık.Genelde de constexpr yapılıyor zaten.

constexpr double operator""_mg(long double val)
{
	return static_cast<double>(val/1000);
}

constexpr double operator""_g(long double val)
{
	return static_cast<double>(val);
}

constexpr double operator""_kg(long double val)
{
	return static_cast<double>(val*1000.);
}

int main()
{
	constexpr auto weight = 5612._mg + 34.6_g + 0.234_kg; // ._mg buna saffix deniyor.
}

Bunların constexpr olması gerekmiyor ama sabit ifadesinde kullanacaksak constexpr olması gerekiyor.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

constexpr size_t operator""_KB(unsigned long long val)
{
	return static_cast<size_t>(val * 1024);
}

constexpr size_t operator""_MB(unsigned long long val)
{
	return static_cast<size_t>(val * 1024 * 1024);
}

constexpr size_t operator""_GB(unsigned long long val)
{
	return static_cast<size_t>(val * 1024 * 1024 * 1024);
}

int main()
{
	array<char, 10_KB> a; // array<char, 10240> gösterir.

	std:::cout << 23_GB + 5_MB + 45_KB << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PARAMETRE CHAR DA OLABİLİR.

constexpr int operator""_i(char c)
{
	return c;
}

int main()
{
	auto constexpr x = 'A'_i ; // 65 burası :D. A nın kodu 65 ve return değer int
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN SIK İHTİYAC DUYULAN CONST CHAR * VE EŞLİK EDEN SIZE_T

void operator""_x(const char* p, size_t n)
{
	std::cout << "operator\"\"_x(const char *p, size_t n) << "\n";
	std::cout << "n = " << n << "\n";
	puts(p);

}

int main()
{
	"9871"_x; // BÖYLE ÇAĞIRACAĞIZ. DİKKAT STRİNG LİTERALİ VAR. UZUNLUĞU 2. PARAMETREYE ARGÜMAN, YAZI 1. CIYE ARGÜMAN GITTI.
}
ÇIKTI
-----
operator""_x(const char *p, size_t n)
n = 4
9871


int main()
{
	"987546"_x; 
}
ÇIKTI
-----
operator""_x(const char *p, size_t n)
n = 6
987546

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Date operator""_date(const char* p, size_t)
{
	return Date(p);
}

int main()
{
	std::cout << "21_12_1987"_date - "05_04_1987"_date << "\n"; // operator- yazıldıysa tabiki yapılacak bu işlem
}

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

UNCOOKED LITERAL OPERATOR
-------------------------
Bu biraz daha karışık.Burada size_t argümanı alınmayacak, sadece const char * argümanı var.
Bu tür sadece const char * parametre olan ve gönderdiğimiz argümanı tamsayı reel sayı değeri olarak değil, bir string olaran func a gönderilmesi durumunda oluşturulan literallere
uncooked deniyor.

void operator""_x(const char *p)
{
	std::cout << p << "\n";
}

int main()
{
	789456_x; // Derleyici sabit kısmını string literaline dönüştürüyor ve argüman olarak gönderiyor.

	//operator""_x("789456"); // Aslında buna dönüştürüyor çağrıyı.Sabiti string literaline dönüştürüyor ve string literalini argüman alıyor.
}

ÇIKTI
-----
789456

Bu functionu ismiyle çağırsaydık, operator""_x("789456"); böyle çağıracaktık. Yukarıda da yazdıım

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int operator""_b(const char *p)
{
	return 34u;
}

int main()
{
	
	auto val = 254346456_b;
	std::cout << "val = " << val << "\n"; // 34 çıkar çünkü 34 e eşitlendi.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İKİLİK SAYI SISTEMİ İÇİN YAZALIM

unsigned int operator""_b(const char *p)
{
	unsigned int result{};

	while(*p)
	{
		if(*p != '0' && *p != '1')
			throw std::runtime_error{"Invalid binary digit\n"};
	
		result= result * 2 + *p - '0';
		++p;
	}
	return result;
}

int main()
{
	try{
		auto val = 101010001101100_b;
		std::cout << "val = " << val << "\n";
	}
	catch(const std::exception &ex)
	{
		std::cout << ex.what() << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:
void operator""_pr(const char *p)
{
	std::cout << "(" << p << ")";
}

int main()
{
	8789456_pr;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Gram{
public:
	Gram() = default;
	explicit Gram(double val);
	void set(double val);
	void get()const;
	friend std::ostream<<(std::ostream&s, const Gram &gr);

private:
	double m_val{};
};

int main()
{
	//Gram x = 34.56; //Explicit olduundan hata
	Gram x{1.234}; // Bu geçerli.

	------------------------------------------------------------------------------------------------------------------------------------------------------

	GRAM OLMAYANIDA GRAM GIBI YAZABILDIK

	double m = 347.863;
	Gram y{m}; // Gram olmayan bir double değişkeni ile initialize edebildik. Bunuda engelleyeceğiz.Prevent usage ile yapılacak.Bu bir nested type
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PREVENT USAGE EKLENDİ. BU BİR İDİYOM.

class Gram{
public:
	class PreventUsage{};

	Gram() = default;
	
	constexpr Gram(PreventUsage, double val) : m_val{val}
	{ 
	}
	
	void set(double val)
	{
		m_val = val;	
	}
	
	void get()const
	{
		return m_val;
	}
	
	friend std::ostream& operator<<(std::ostream&os, const Gram &gr)
	{
		return os << g.get() << "gr";
	}

	friend Gram operator+(const Granm &left, const Gram &right)
	{
		return Gram{PreventUsage{}, left.m_val + right.mval};
	}
private:
	double m_val{};
};

Gram operator""_g(long double val) // bu sayede aşağıdaki gibi tek argümanla çağırabileceğiz. Bu biraz wrapper gibi oldu.
{
	Gram{Gram::PreventUsage{}, static_cast<double>(val)};
}

Gram operator""_kg(long double val) // bu sayede aşağıdaki gibi tek argümanla çağırabileceğiz. Bu biraz wrapper gibi oldu.
{
	Gram{Gram::PreventUsage{}, static_cast<double>(val * 1000)};
}


int main()
{
	Gram g{23.42}; // SENTAKS HATASI

	Gram g = 23.67_g;

	std::cout << g << "\n";

	std::cout << 0.45_g + 234_kg << "\n";
}


MOLA

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

RANDOM SAYI ÜRETECİ
-------------------
C de ki çok primitive idi. C++ taki kriptoloji hariç heryerde kullanılabilecek bir uzay mekiği.
Profesyonel uygulamalarda rahatlıkla ve güvenle kullanılabilir. Kriptolojide daha özel bir library kullanmak gerekiyor.

header file random

BURADA 3 TANE TEMEL ENGINE VAR
------------------------------
1- LINEAR_CONGRUENTIAL ENGINE
2- MERSENE TWISTER ENGINE
3- SUBTRACT WITH CARRY ENGINE

Bunlar sınıf şablonları.Biz bu sınıf şablonlarının çoğunluğu nontype parametreye sahip.
Bunları doğrudan kullanmak yerine özel açılımlarını kullanıyoruz. mt19937 ve mt19937_64 en fazla kullanılan sınıflar. 
Biri 4 diğeri 8 bytelık rasgele sayı üretiyor. Çok özel bir ihtiyaç noktası yoksa Mersenne Twister kullanılabilir.

Bunları doğrudan kullanmak yerine kullanım amacına uygun bir dağılım modeliyle üretilen rasgele sayıları belli aralığa dağıtacak distribution nesneleri kullanacağız.

Birde Adapter sınıflarımız var. Rasegele üretim yapan enginlerden birini alıp bir adaptasyon yapıyor ve kendisi bu motorları kullanarak daha özel bir şekilde
sayı üretiyor. Mesela üretilen her rasgele sayıyı kullanmak yerine belirli olanları atlıyor gibi.

Bİzi ilgilendiren buradaki rasgele sayı üreten sınıflar.ÖR: minstd_rand, minstd_rand0, ranlux24_base, ranlux48_base gibi şekili koydum proje dosyasına.
Yada bunların adapte edilmiş halleri var, ranlux24, ranlux48, knuth_b gibi sınıflar

mt19937 ile başlayacağız

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MT19937
-------
En sık default kullanılan rasgele sayı üreteci sınıf

using namespace std;

int main()
{
	cout << typeid(mt19937).name() << "\n";
	// dev gibi bir açılım var.Buradaki parametreler matematikçilerin zamanla araştırığı değiştirdikleri parametreler
	// AÇILIM: class std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253>

	cout << typeid(minstd_rand).name() << "\n";
	// AÇILIM: class std::linear_congruential_engine<unsigned int,48271,0,2147483647>
}	

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DIKKAT EDILMESI GEREKEN MY19937 SINIFI SIZEOF OLARAK BÜYÜK BIR SINIF
Kopyalama gereken yerde çok dikkatli olmak gerekiyor

int main()
{
	std::cout << "sizeof(mt19937) = " << sizeof(mt19937) << "\n"; // 5000byte

	------------------------------------------------------------------------------------------------------------------------------------------------------
	SEED DEĞERİ

	mt19937 eng;

	std::cout << my19937::default_seed << "\n"; //DEFAULT TOHUM/SEED DEĞERİ

	------------------------------------------------------------------------------------------------------------------------------------------------------
	KENDIMIZ SEED VEREBİLİRİZ

	mt19937 eng {1234U}; //SEED DEĞERI VERDIK.

	eng.seed(87955); // BAŞKA SEED VERDIK ŞIMDI YARATTIKTAN SONRA.

	------------------------------------------------------------------------------------------------------------------------------------------------------

	mt19937 eng {1234U};

	for(int i = 0; i < 100; ++i)
	{
		std::cout << eng() << "\n";
	}

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÜRETİLEN RASGELE SAYI 4 BYTELIK İŞARETSİZ TAMSYI TÜRÜNDEN
Max değeri 0 ile 4 byte max değeri arasinda. Uygulamalarda bu rasgele sayıyı doğrudan kullanmıyoruz. Bu motor üretilen rasgele sayıları belirli bir 
aralığa dağıtma görevi için distribution sınıflar türünden nesneler kullanıyoruz.

mt19937 eng {1234U};

for(int i = 0; i < 100; ++i)
{
	std::cout << eng() << "\n";
	_getch();
}

BUNLAR ASLINDA BIZE RANDOM BITLER VERIYORLAR
BU BITLERDEN FAYDALANARAK RASGELE SAYIYI KULLANMAK IÇIN BIR DISTRIBUTION NESNELER KULLANIYORUZ.
RASGELE TAMSAYI VEYA REEL SAYILAR IÇIN KULLANABILIR VE BU SAYILARI BELIRLI BIR DAĞILIM MODELIYLE BIZIM IÇIN RASGELE SAYILAR ÜRETEBILIRIZ.
C DEKI GIBI MOD OPERATÖRÜNÜ KULLANMAYACAĞIZ ASLA.


-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

RASGELE SAYI ÜRETEN ALGORITMALAR DERLEYICIDEN DERLEYICIYE DEĞIŞMIYOR.AŞAĞIDAKI KOD HER DERLEYICIDE AYNI SAYI ZİNCİRİNİ ÜRETMEK ZORUNDA.

int main()
{
	mt19937 eng {1234U};

	for(int i = 0; i < 100; ++i)
	{
		std::cout << bitset<32>(eng()) << "\n";
	}
}

Her seferinde aynı sayıları üretmesi zayıf nokta değil zaten böyle olmalı. 
Her seferinde farklı bir rasgele sayı üretmek istersek 2 ayrı yöntem belirleyebiliriz.
Random içinde random_device sınıfı türünden nesne var. Bu nesnenin ürettiği rasgele sayı gerçek rasgele sayı.
Psudo random number değil. İşlemci ısısı, klavye tuşuna basma süresi, Os sistem functionları olabilir... Bunlar değil.
Gerçek rasgele sayıdan bahsediyoruz.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BU RASGELE SAYI ÜRETMEK IÇIN DEĞIL, HER SEFERINDE FARKLI SAYI ZINCIRI ÜRETMEK IÇIN TOHUM/SEED DEĞERİNİ RANDOM_DEVICESTEN ALIYORUZ

 #include <random>
 #include <iostream>

 int main()
 {
    random_device mydevice;
    for(int i = 0; i < 10; ++i)
    {
        std::cout << mydevice() << "\n"; //Burası her seferinde farklı sayı zincirini gösteriyor.
    }
 }

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

IDIYOMATİK KODLAR AŞAĞIDAKİ GİBİ
BÖYLECE RANDOM DEVİCE RASGELE GERÇEK SAYI ÜRETTİĞİNDEN BAŞKA BİR SEED DEĞERİNİ KULLANACAĞIM. C DEN HATIRLA

1. IDIYOM

int main()
{
	mt1993 eng{ random_device{} }; // random device seed değeri olarak verildi.
	
	for(int i = 0; i < 10; ++i)
	{
		std::cout << eng() << "\n";
	}
}


int main()
{
    random_device x;
    mt19937 eng{x}; // BÖYLEDE YAZABILIRDIK AMA X I DAHA KULLANMAYACAĞIZ NIYE TEKRAR YAZALIM.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. IDIYOM
Chronoyu kullanarak geçen zamandan faydalanmak.

#include <chrono>
#include <iostream>
#include <random>

int main()
{
	std::mt19937 eng(system_clock::now().time_since_epoch().count()); // now epochtan geçen süreyi time point verir. Zaten daha önecde yazdım.
	for(int i = 0; i < 10; ++i)                                       // time_since_epoch() bu bir duration verir. Count ta tamsayı olarak yazar.
	{
		std::cout << eng() << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Burada cppreference.com dan bakıldı mt19937 ye.

10000. sayı her compilerda aynı sonucu verecek yazıyor. Buna bakıyoruz.

int main()
{
    mt19937 eng; // default seed verildi. mt19937_64 te denenebilir

    for(int i = 0; i < 10'000 -1;++i) // 9999. sayıya geldik
    {
        (void)eng();
    }
    std::cout << eng() << "\n"; // 10'000. sayı her compilerda aynı
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MAX VE MIN FUNCTIONLARI
Üretilebilecek max ve min sayıları döndürüyor.

int main()
{
	mt19937_64 eng;

	std::cout << eng.min() << "\n"; // min değeri
	std::cout << eng.max() << "\n"; // max değeri
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DISCARD
-------
Discard ile sayı zincirinden n tanesinden atlama yapılmasını sağlayabiliriz.

int main()
 {
	mt19937_64 eng;

	eng.discard(9999) // 9999 tane sayıyı discard edecek bu
	std::cout << eng() << "\n"; // Burada 10 bininci sayıyı üretti.
 }

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

SEED DEĞERİNİ 2 FARKLI ŞEKİLDE DEĞİŞTİRİYORUZ.
1- Constructor ile kendimiz verebiliyoruz.
2- Nesne hayatta iken seed functionu ile verebiliyoruz.

ÇOK ÖNEMLİ !!!!!!!
Her rasgele sayı üretecinin bir state i var. Bir durum bilgisi bu. Az önceki kodda 100 tane rasgele sayı ürettiysek
o anda eng nin bir state i var. Bu stateleri aynı türden farklı türden nesnelerin statelerini != ve == ile
karşılaştırabiliriz. Örnek aşağıda.

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

 int main()
 {
	mt19937 x{4324543U};
	mt19937 y{4324543U};

	std::cout << boolalpha << (x == y) << "\n"; // STATELERI AYNI OLMALI. TRUE

	for(int i = 0; i < 100; ++i)
	{
		(void)x();
	}
    // 100 TANE SAYI ÜRETTIK VE X IN STATE I DEĞIŞTI.

	cout << boolalpha << (x == y) << "\n"; // FALSE

	for(int i = 0; i < 100; ++i)
	{
		(void)y();
	}
	cout << boolalpha << (x == y) << "\n"; // TRUE. İKISIDE AYNI TÜRDEN NESNE VE STATELER EŞIT.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 BU STATE İ BİR ÇIKIŞ AKIMINA YAZABİLİYORUM VE BİR GİRİŞ AKIMINA TEKRAR BUNU GERİ GETİREBİLİYORUZ

int main()
{
	mt19937 eng{213432u};

	for(int i = 0; i < 1000; ++i)
	{
		eng();
	}
    //1000 sayı ürettik ve bu state i bir yere yazmak istiyoruz.
    //Tipik olarak bir ostringstream nesnesi kullanabiliriz

	stringstream oss; //DİKKAT STRINGSTREAM, OSTRINGSTREAM DEĞİL !!!!!!!!!!!!!!!!!!
	oss << eng;

	for(int i = 0; i < 5; ++i)
	{
		cout << eng() << "\n";
	}

	std::cout << "\n\n";
	oss << eng; //state bilgisi oss e yazıldı

	for(int i = 0; i < 5; ++i)
	{
		cout << eng() << "\n";
	}

    //5 tane daha random sayı üretti ve state i değişti. Biz yine aynı state e geri getirmek istiyoruz.
    oss >> eng; // STRINGSTREAM NESNESİ OLDUĞUNDAN YUKARIDA YAZMA LINEDA OKUMA YAPILDI !!!!!!!!!

    for(int i = 0; i < 5; ++i)
    {
        cout << eng() << "\n";
    }
    // AYNI 5 SAYIYI ÜRETTI.BU DEĞİŞMEZ

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	mt19937 end{123124u};
    eng.discard(1'000'000 - 1);
    std::cout << end(); // 1 milyonuncu sayı yazıldı.
}

ÖZET:
BIR STATE BILGISI VAR,  BUNU YA BIR AKIMA YAZABILIRIM YADA HERHANGIBIR GIRIŞ AKIMINDAN STATE BILGISINI
SAYI ÜRETECI NESNESINE YAZABILIRIM !!!!

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    mt19937 eng;

    std::cout << eng; // state i yazdırınca baya bir tamsayı yazdırıyor.Ama anlamsız
}

eng yi farklı bir değişkene kopyalasak state saklanır !!!
Bu istenmez çünkü bu 5000 byte.
Bunun için aşağıdaki yapı kullanılabilir.

mt19937& myengine()
{
    static mt19937{random_device{}()};
    return eng;
}

int main()
{
    auto &e = myengine(); // Funcitonu çağıran tüm kullanıcılar engine nesnesini kullanır artık.
}
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BU ÖZELLİKLER DİĞER TAMSAYI ÜRETİCİLERİ İÇİNDE GEÇERLİ
MESELA MERSENE TWISTER DEĞILDE KNUTH_B KULLANMAK ISTERSEN AYNI FUNCTIONLAR ORADA DA VAR.

===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

DISTRIBUTIONS
-------------

Tam Liste aşağıdaki gibi. Biz en çok kullanılanları kullanacağız.

Category Name                Data                           Type
---------------------------------------------------------------------
Uniform distributions        uniform_int_distribution       IntType
                             uniform_real_distribution      RealType

Bernoulli distributions      bernoulli_distribution          bool
                             binomial_distribution           IntType
                             geometric_distribution          IntType
                             negative_binomial_distribution  IntType

Poisson distributions        poisson_distribution            IntType
                             exponential_distribution        RealType
                             gamma_distribution              RealType
                             weibull_distribution            RealType
                             extreme_value_distribution      RealType

Normal distributions         normal_distribution             RealType
                             lognormal_distribution          RealType
                             chi_squared_distribution        RealType
                             cauchy_distribution             RealType
                             fisher_f_distribution           RealType
                             student_t_distribution          RealType

Sampling distributions       discrete_distribution           IntType
                             piecewise_constant_distribution RealType
                             piecewise_linear_distribution   RealType


===============================================================================================================================================================================================
===============================================================================================================================================================================================
===============================================================================================================================================================================================

UNIFORM DISTRIBUTIONS

Üretilen tüm sayıların üretilme olasılıklarının aynı değere yakınsaması demek uniform distributions.
Belirli aralıkta sayıları uniform olarak dağıtacak.Ör 5-15 arasındaki üretilen sayıların
eşit ihtimalle üretilmelerini istiyoruz mesela. Burada uniform int distribution kullanırız.

Dağılım sınıfları ile rasgele sayı üreten sınıflar başka sınıflar.Yani bir rasgele sayı üreticisi ile
farklı dağılım nesnelerini birlikte kullanabiliriz.Veya aynı dağılım nesnelerini farklı sayı üreticileri
ile kullanabiliriz.

Dağılım nesneleri standart değil !!!!!!!
Aynı şekilde dağılım nesnelerini initialize etsek üretilecek rasgele sayılar aynı olmak zorunda değil.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
TAVLA ZARI ÜRETECEĞİZ. BUNUN İÇİN UNİFORM INT DİSTRİBUTION KULLANACAĞIZ

int main()
{
    //uniform_int_distribution<int> dist; // böyle yapabiliriz.
    //uniform_int_distribution<> dist; // böyle yapabiliriz.
    //uniform_int_distribution dist; // böyle yapabiliriz.
    //suniform_int_distribution dist{}; // Default init edilirse 0-max arasında sayı üretiyor.

    //uniform_int_distribution<int,int> dist{12,24}; // Böylede yazılabilir.

    uniform_int_distribution dist{12,24}; // 12-24 arası sayı üretir.12 ve 24 dahil.CTAD ile böyle yazıldı
    // dist nesnesini kullanmak için random sayı üreticisi gerekiyor.

    mt19937 eng;

    dist(eng); // dist in func call operator func ına eng yi argüman olarak geçtik.
    
 	------------------------------------------------------------------------------------------------------------------------------------------------------

    mt19937 eng;
    uniform_int_distribution dist{12,15};

 	for(int i = 0; i < 200; ++i)
    {
        std::cout << dist(eng) << " "; // 12-15 arasındakileri üretiyoruz.
    }

 	------------------------------------------------------------------------------------------------------------------------------------------------------

    RASGELE DOĞUM TARIHI ÜRETELIM

    mt19937 eng;
    uniform_int_distribution dist{1940,2000};

    for(int i = 0; i < 200; ++i)
    {
        std::cout << dist(eng) << " ";
    }
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TÜM SAYILARI SAYALIM

int main()
{
    mt19937 eng;
    uniform_int_distribution dist{1,6};

    std::map<int,int> cmap;

    for(int i = 0; i < 1'000'000; ++i)
    {
        ++cmap[dist(eng)];
    }

    for(auto[value,count] : cmap)
    {
        std::cout << value << "   " << count << "\n";
    }
    //UNIFORM DAĞILIM DEMEK BUNLARIN HEPSİNİN BİRBİRİNE ÇOK YAKIN OLMASI DEMEK.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

REEL SAYILARI BİR ARALIĞA DAĞITALIM

Bunun için uniform real distribution kullanılır.

int main()
{
    mt19937 eng;

    uniform_real_distribution<double> dist{2.387, 5.98761}; // Rasgele sayı üreticisinin ürettiği bitleri bu aralığa
                                                            // reel sayı olarak dağıtacak.

    std::ofstream ofs{"out.txt"};
    if(ofs.fail())
    {
        std::cerr << "out.txt dosyasi olusturulamadi\n";
        exit(EXIT_FAILURE);
    }

    ofs << fixed;
    for(int i = 0; i < 10000; ++i)
    {
        ofs << dist(eng) << "\n";
    }
}

*/
