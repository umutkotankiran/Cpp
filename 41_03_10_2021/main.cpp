/*

INPUT OUTPUT OPERATIONS - GİRİŞ ÇIKIŞ İŞLEMLERİ
-----------------------------------------------
Bizim programımızın çalışan haline process deniyor. Processler çalışırken dış dünya ile haberleşme içinde oluyorlar.

output stream --> Programdan dış dünyaya akan bytelara deniyor
input stream --> dış dünyadan programa akan verilere deniyor.

Gidenler Bu bytelar ekran, dosya, network başka bir programa gönderiliyor olabilir.
Gelenler ise klavyeden dosyadan başka bir programdan gelebilir.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunlar formatlı mı formatsızmı?
formatted input-output, unformatted input-output

Formatlı giriş çıkış demek byte ların bir text e dönüştürülerek giriş çıkış işlemlerinin yapılması demek.
C den de işledik.

int val = 9879847;
1011 1110
1001 0001
0010 0011
1100 0101  diyelimki böyle açıldı bitlere

Ben bu byteları doğrudan programa veya networke gönderirsem bu formatsız çıkış olur. Bytelar olduğu gibi işleme sokuluyor.

Bu byteların temsil ettiği değerleri, benim belirttiğim formatlama kriterlerine göre karakter kodlarına dönüştürürsem ve 
o karakter kodlarını gönderirsem bu formatlı çıkış. Formatlı girişte benzer

Programlama dilleri bunu destekliyorlar.
Mesela C de, printf sprintf fprintf, scanf, sscanf, fscanf, fread, fwrite, fgetc, fputc, getchar, putchar

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

C++ ın kütüphanesi ise eleştiriliyor. Bahsedilecek. 

Bu kütüphaneye iostream kütüphane deniyor ama çok sayıda sınıf var burada. Hepsini birden kastederken iostream diyoruz.

Birinci fark C++ OOP tarzında.Kaynakları kontrol eden sınıf nesneleri var.Yani giriş çıkış işlemlerini gerçekleştirmek için sınıf nesnelerini kullanıyoruz.
Mesela cout fonksiyonu demek yanlış. Cout ostream sınıfı türünden global bir değişken kullanıyoruz.Cout un ait olduğu sınıf ostream.
Hatta ostream sınıfın ismi bile değil, o sınıfın türeş ismi. Gerçek adı basic_ostream. Bu bir sınıf şablonu. Bunun template argümanlarıyla açılmış
gerçek sınıf oluşturulmuş hali ostream.

Cin de istream isimli bir sınıf türünden nesne. Bunlar function değil global değişkenler.

Burada overload edilen operatorler var.>> ve << gibi.
Giriş tarafında >> kullanılıyor
Çıkış tarafından << kullanılıyor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

cout << x  burada 2 ihtimal var
a) cout.operator<<(x)   
b) operator<<(cout,x)

cin >> x

cin>> x >> y >> z; bunu oluşturabilmek istenmiş. Fluent api deniyor.
veya
cout << a << b << c; // tek bir statementta işimizi halletmemiz mümkün. Bunu sağlayan yapı bu funcların return değerlerinin bir referans olması.Akımı temsil eden 
nesnenin kendisini döndürüyor.

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

FORMATLAMA NASIL YAPILIYOR
--------------------------
Giriş veya çıkış işlemleri formatlı olduğunda önemli soru bunun nasıl yapılacağı?
Formatlama demek tercih demek. 16 lık veya 8 likte yazılacaksa bu ön ek ile gösterilecek mi gösterilmeyecekmi?

21 mesela bu 10 luk sayı sisteminin basamakları olarak mı alınacak yoksa 16 mı?
yoksa 8 lik sayı sistemi olarak mı alınacak.Formatlama buradaki tercihler demek.

2.3 mü yoksa 2.3e diyemi gösterilecek.
, den sonra kaç basamak gösterilecek ... gibi birsürü şey var

C++ ta bu formatlama sorunluydu. Okuma ve yazma zorluğu oluşturan bir yapı vardı.Halen daha var. C++20 ile birlikte gelen format kütüphanesi geldi. 
Hem daha fazla olanağa sahip, daha hızlı daha yetenekli hale geldi. format kütüphanesi çıkışı yapılacak varlığı bir text olarak formatlayıp bize bir 
string veriyor.

İleri C++ ta format kütüphanesi daha detaylı görülecek

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MESELA INT TÜRDEN DEĞIŞKENI BELIRLI BIR FORMAT BILGISIYLE YAZDIRACAĞIZ

#include <format>
#include <iostream>

using namespace std;

int main()
{
	int x = 2543;
	
	cout.setf(ios::dec);
	cout.width(16);				    // yazma alanı değişikliği için
	cout.setf(ios::left, ios::adjustfield);     // sola dayalı yazmak için 
	cout.fill('_');				    // Boşluk karakterlerini _ ile dolduralım

	cout << x << "ali"; // sola dahalı 16 karakterlik alana yazdı.
}

Yukarıdakilerin hepsi görülecek

Formatlama özellikleri aslında çıkış akımı ve giriş akımı nesnelerinin state inin bir parçası durum bilgisi. Her akım nesnesi formatlama bilgisi için
bir veri elemanı tutuyor. Giriş çıkış işlemlerinden önce veri elemanından bu formatlama bilgisi çekilip giriş çıkış işlemleri ona göre yapılıyor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

YUKARIDAKİLERİ BOŞVERİP İSMİ FORMAT OLAN GLOBAL BİR FUNC ÇAĞRIRALIM

int main()
{
	int x = 2543;

	cout << format("|{:_^<18}|",x) << "\n";
	// C++20. Tüm formatlama özelliklerini tek bir string ile belirtebileceğim
	// :18 yazma alanı genişliği 18
	// < sola dayalı yazdı
	// _ doldurma karakteri olarak kullanıldı
	// < yerine ^ kullanırsak ortalamalı centered yazım biçimi
}

Bunlar C++ 20 ile geldi
Ama bu demek değilki iostream sınıfının kendi formatlama özelliklerinden faydalanmayacağız.Onlarıda kullanacağız.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BURADA BIR ŞEKIL GÖSTERILDI. INHERITANCE KONUSUNDA GÖRÜLDÜ.ORADAN ALDIM.
Burada konuyu %70 oranında ele alacağız. Bu konu için biraz çaba sarfetmemiz lazım.

			|------------|
			|  ios_base  |
			|------------|							   |------------------|
			      ^								   |basic_streambuf<> |
			      |								   |------------------|
			      |								   streambuf/wstreambuf
			|------------|
			| basic_ios<>|
			|------------|
		  	   ios/wios
			   (virtual)
		      ^			^
		     /			 \
Virtual	inheritance /			  \	 Virtual inheritance
		   /			   \
		  /			    \
|----------------|			|---------------|
|basic_istream<> |			|basic_istream<>| 
|----------------|			|---------------|
 istream/wistream			ostream/wostream
	
	       ^                	     ^
		\			    /
		 \			   /
		  \			  /
		   \		 	 /
 		    \	    		/
		     |----------------|
		     |basic_iostream<>|
		     |----------------|
		     iostream/wiostream

IOS_BASE = Bu bir sınıf şablonu değil. Karakter türünden bağımsız giriş çıkış işlemi türünden bağımsız interface var.
Biz cout veya cin kullanırken kullandığımız memberfunclar onun ios_base den aldıkları funclar. 
Burada nested type lar olabilir tür eş isimleri olabilir ... 

BASIC_IOS = Bu bir sınıf şablonu.Akımdaki karakter türüne bağlı olduğu için bunu şablon yapmışlar. 2 template parametresi var. 
1. parametresi akımdaki karakter türü.char olabilir, 2 bytelık char olabilir başka özel bir tür olabilir.  2. template tür parametresi ise, 
kopyalama karşılaştırma işlemlerinin nasıl yapılacağını belirten bir traits sınıfı.

basic_ios<char, char_traits<char>>

basic ios halen giriş veya çıkış işlemleri ile doğrudan ilgili değil. Buradaki interface giriş/çıkıştan bağımsız yani
Tam burada bundan kalıtımla iki sınıf elde ediliyor.Aşağıdakiler

BASIC_ISTREAM ve BASIC_OSTREAM = Giriş ve çıkış işlemlerinin interface ini veriyorlar. Bunların ikiside sınıf şablonu. basic_istream<char> veya basic_ostream<char> veya
wchar açılımlarını kkullanabiliyoruz. Char açılımlarının hepsinin typedef ismi var. 

basic_ios<char> ın typedef ismi ios
basic_istream<char> ın typedef ismi istream. cin nesnemiz bu sınıfın char açılımı türünden
basic_ostream<char> ın typedef ismi ostream. cout nesnesmiz bu sınıf şablonunun char açılımı türünden
Bu ikisinin kalıtımı virtual inheritance. Burada multiple inheritance var.Neden kullanılmı bu?
iostream hem giriş hemde çıkış interface ine sahip bu sebeple böyle.

basic_streambuf : okuma yazma işlemlerini yapan bir buffer sınıf. Kalıtım yoluyla bundan farklı sınıflar elde ediliyor.

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

KODA GERİ DÖNÜYORUZ

int main()
{
	cout bir nesne !!!!!!!!!

	cout. // interface i görülür.

	basic_ostream<char, char_traits<char>>		// cout bu sınıf türünden
	basic_ostream<char>							// yukarıdaki ile bu aynı
	ostream										// yukarıdakininde typedef ismi bu

	---------------------------------------------------------------------------------------------------------------------------------------------

	BAŞINDA W OLANLAR AYNI SINIFLARIN CHAR DEĞILDE WCHAR AÇILIMLARI
	using ostream = std::basic_ostream<char>
	using wostream = std::basic_ostream<wchar_t>

	---------------------------------------------------------------------------------------------------------------------------------------------
	
	using istream = basic_ios<char>
	using wistream = basic_ios<wchar_t>
		
	---------------------------------------------------------------------------------------------------------------------------------------------

	using ios = basic_ios<char>
	using wios = basic_ios<wchar_t>   // wchar_t 2 byte. Mesela windows programlarında daha çok bu kullanılıyor.

}

biz iostream header file ı include ettiğimizde, 
extern ostream cout; bunuda include etmiş oluyoruz.Bunlarında yine wchar_t için oluşturulmuş global değişkenler var
extern ostream wcout;
extern ostream wcin; ... gibi.

Bu sınıflarında dğer türler için açılımı sözkonusu. Doğrudan bir typedef ismi yok ama istediğimiz tür için açılım yapabiliriz.
Bu yüzden template zaten.

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

FORMATLI ÇIKIŞ İŞLEMLERİ
------------------------
Formatlı çıkış için operator<< funclarımız var.Bunlar ostream sınıfının funcları.
Formatlı çıkış işlemi ostream sınıfından başlıyor. Taban sınıfı giriş çıkıştan bağımsız.Bu interface yok
Burada 2 farklı func kategorisi var. 
1 - Sınıfın üye funcları


class Ostream{  // Bu aslında sınıf şablonu ve onun typedef ismi

public:
	Ostream& operator<<(int);
	
	Ostream& operator<<(double);
	
	Ostream& operator<<(long);  // Argüman türüne bağlı olarak compile time da overload resolutionda hangisinin çağrılacağı belli oluyor.
	
	Ostream& operator<<(void *);
	
	Ostream& operator<<(Ostream&(*fp)(Ostream&)) // BU ÇOK ÖNEMLİ. Biz buna bir func adresi gönderiyoruz.Bu ise bizim gönderdiğimiz sınıf nesnesinin kendisi ile çağırıyor.
	{												// return değeri bu func ın return değeri.
		return fp(*this);
	}
};

int main()
{
	int x = 33;
	double d = 1.111;

	cout << x << d;
	cout.operator<<(x).operator<<(d); // yukarıdaki ile aynı  
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FAKAT BAZI FUNCLARDA AŞAĞIDAKİ GİBİ

std::ostream& operator<<(std::ostream&os, const char *p);
Çok karıştırılıyor. Aradaki fark aşağıda

int main()
{
	cout << "yusuf yilmaz"; // burada yusuf yilmaz yazar
	operator<<(cout,"yusuf yilmaz"); //BU da global func. yusuf yilmaz yazar

	cout.operator<<("yusuf yilmaz"); // Yukarıda ismi yazdırırken, burada adres yazar. Bunun parametresi void * çünkü. 
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{ 
	cout << 'A'; // A yazar
	operator<<(cout,'A'); // A yazar yine. Global operator func

	cout.operator<<('A'); // 65 Yazar	
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cout << "ali" << 123 << " " << 1.234 << bitset<16>(45) << "\n"; // chaining mekanizması olmasa ve chaining mekanizması doğrudan operator overloading ile birleşmese
																	//aşağıdaki gibi yazmak gerekirdi	

	operator<<(operator<<(operator<<(cout, "ali").operator<<(123), " ").operator<<(1.234),bitset<16>(45) ) ... böyle yapmak zor olacak
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

OSTREAM MANIPLATORU
-------------------

ostream& neco(ostream& os) // bu tip parametrik yapısı ve return değeri olan funclara manipulatör deniyor.
{
	std::cout << "neco cagrildi\n";
	return os;
}

int main()
{
	cout <<  neco; // Bu aslında neco(cout) a dönüştürülüyor.Yukarıda Ostream i yazdık. Onun içindeki son func çağrılıyor.Func çağrılabildi çünkü parametrik yapısı uygun
	cout <<  neco << "alican";					
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ENDL DE BÖYLE BIR MANIPLATOR

ostream& Endl(ostream& os)
{
	os.put('\n');
	os.flush();
	return os;
}

int main()
{
	cout << Endl;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIZDE BUNU YAZDIK NUTILITY DE VAR. BUDA BİR MANIPULATOR

std::ostream& sline(std::ostream&os)
{
	return os << "\n**********************************************************\n"
}

int main()
{
	std::cout << 12 << sline << 2.3 << sline << 34L << sline;
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

FORMATLAMA ÖZELLİKLERİ
----------------------
Ostream ve Istream nesneleri giriş/çıkış işlemlerinde formatlamanın nasıl yapılacağını tutan bir türden veri elemanı tutuyor.Veri elemanı en tepedeki taban sınıfın nested type.
Aslında her osteam nesnesi nasıl formatlama yapacağını biliyor. 

Bu türün ismi fmtflags

int main()
{
	ios_base::fmtflags
}

Bu nested type bitsel işlemlere uygun bir tür.Ama gerçekte ne olduğu tamamen derleyiciye bağlı.Formatlama işlemlerinde kullanacağımız türlerden biri bu.

Sınıfın setf isimli member funcları var. En tepedeki taban sınıftan geliyor.Formatlama özellikleri 3 kategoriye ayrılabilir. Bazıları boolean bilgi.
On-off flag deniyor. Yani bir formalama özelliği ya aktif yada değil demek.

0 1 olarak mı yazılsın yoksa true false olarak mı yazılsın ? gerçek sayı 0 ise nokta olsun mu olmasın mı ? hex yazımda harf karakterleri büyük mü küçük mü olsun ? 
hex yada octal yazımda sayı sistemi ön ek gösterilsin mi gösterilmesin mi ? 
Bunlar boolean bilgi.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOLEAN BILGILER AŞAĞIDAKI GIBI SET VE GET EDILIYOR
---------------------------------------------------
Bunların default durumları var.boolean verinin yazılmasında default durum 0 - 1 olarak yazılması.

ÖR:
int main()
{
	cout << (10 > 5) << "\n"; // Bunu yazan func fmtflags türünden veri elemanına bakacak, orada tipik olarak bit seviyesinde bir biti get edecek ve boolean değerin false 
				  // olduğunu görecek ve 10 > 5 i true olarak değilde, 1 olarak yazacak.Default durumu 0 - 1 yazımı 

	---------------------------------------------------------------------------------------------------------------------------------------------

	Biz bunu ne şekilde true false yazacak hale getiririz.Bu bilgi fmtflags türünden veri elemanının bir bitinde tutuluyor. O biti set etmemiz
	gerekiyor.setf func ı ile yaparız.

	cout.setf(ios_base::boolalpha); // bunu yazarsak, setf bu bayrakla sınıfın fmtflags türünden veri elemanını veyalıyor.
					// artık boolean değerler true false olacak. Arka planda bu bayrakla veyalayacak
					// tek yapmamız gereken bir biti 1 diğerleri 0 olan bayrağı argüman olarak göndermek.
					// Bu bayraklarda(yada bitsel maskelerde) en tepedeki taban sınıfın içinde constexpr static
					// veri elemanı olarak tanımlanmış.Bu bayrak ios_base::boolalpha. Burada sınıfın fmtflags türden
					// veri elemanını bu flag ile veyalıyor. Bundan sonra boolean değerler true false yazacak.

	---------------------------------------------------------------------------------------------------------------------------------------------

	cut.unsetf(ios_base::boolalpha); // artık clear edildi. 0 ve 1 yazacak yine
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BAŞKA ÖR:

Nasıl true false yazacağız. fmtflag taki durum bilgisinde duruyor bu.
setf isimli func var


int main()
{
	cout << hex;

	cout << 76234 << "\n"; // 129ca yazdı

	cout.setf(ios::uppercase); // ios_base::uppercase de kullanabiliriz. ios zaten kalıtımla elde edilmiş bundan
	
	cout << 76234 << "\n"; // 129CA harf karakterleri büyüdü.

	cout.unsetf(ios::uppercase); // resetledi

	cout << 76234 << "\n"; // 129ca harfleri küçük yazdı

	cout.setf(ios::showbase); // sayı sistemi tabanı gösterilsin mi

	cout << 76234 << "\n"; // 0X129CA harfleri küçük yazdı.x yazdı hexadecimal sayı sistemi.

	cout.setf(ios::uppercase | ios::showbase); //Tek seferde 2 bayrak set edilebilir. Bunu yapmanın bir yolu daha var.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SINIFIN TABAN SINIFTAN ALDIĞI FUNCTIONLARDAN BIRISI FLAGS
cout.flags()

argüman göndermeden çağırırsak fmtflags türünden değişkeni get ediyor. birde set versiyonu var.
argüman olarak fmtflags türünden değer geçersek veri elemanına bu değeri yerleştiriyor.


int main()
{
	cout.setf(ios::boolalpha);

	cout.flags(); // böyle çağırırsan fmtflags ın değerini get eder. içine yazarsam birşey set eder.

	cout.flags(cout.flags() | ios::boolalpha); //bununla ilk çağrı aynı yani cout.setf(ios::boolalpha);
	// cout.flags() ile get edip bunu boolalpha ile bitsel veya işlemine sokup tekrar cout.flags e argüman olarak gönderdik
	
	----------------------------------------------------------------------------------------------------------------------------------------------
	
	cout.unset(ios::boolalpha);
	cout.flags(cout.flags() & ~ios::boolalpha); // bununlada yukarıdaki aynı
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

void func(std::ostream& os)
{
	//boolean değerleri	nasıl yazacak ? Bunun için boolalpha biti bizim get etmemiz lazım bunun için doğrudan func yok
	if (os.flags() & std::ios::boolalpha)
	{
		std::cout << "true false olarak yazar\n";
	}
	else
		std::cout << "0 1 olarak yazar\n";
}

int main()
{
	func(std::cout);
	std::cout.setf(std::ios::boolalpha);
	func(std::cout);
	std::cout.unsetf(std::ios::boolalpha);
	func(std::cout);
}

ÇIKTI
-----
0 1 olarak yazar
true false olarak yazar
0 1 olarak yazar

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Mülakat sorusu

İş bitince formatlama değerini eski değerine getir

void print_(ostream&s)
{
	auto os_flag = os.flags(); // eski değeri tutuldu
	
	// formatlama bayraklari değiştirildi.

	os.flags(os_flag); // hatta bunu rai sınıfı olarak sarmalayan kodda yazılabilir.
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================


STD::IOS::BOOLALPHA, CONSTEXPR STATIC TMPFLAGS TÜRÜNDEN BIR SABIT

int main()
{
	cout << bitset<32>(ios::boolalpha) << "\n";
	cout << bitset<32>(ios::uppercase) << "\n";
	cout << bitset<32>(ios::showpoint) << "\n";
	cout << bitset<32>(ios::showbase) << "\n";
}

Bunlar aslında bir biti 1 diğerleri 0 olan birer tamsayıdan farklı birşey değiller.
Çıktı 
00000000000000000100000000000000
00000000000000000000000000000100
00000000000000000000000000010000
00000000000000000000000000001000

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖZET

int main()
{
	cout.setf(std::ios::boolalpha); //aşağıdaki ile aynı işi yapıyor
	cout.flags(os.flags() | std::ios::boolalpha);

	cout.unsetf(std::ios::boolalpha);//aşağıdaki ile aynı işi yapıyor
	cout.flags(std::ios::boolalpha & ~std::ios::boolalpha);

	cout.flags(os.flags() & ^std::ios::boolalpha); // boolalpha ise unset ediyor, değilsede set ediyor :D:D:D

}


=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

BU SISTEM CHAININGDE IFLAS EDIYOR :D:D:D:D

std::ostream& Boolalpha(std::ostream& os) //Bu bir manipulator
{
	os.setf(ios::boolalpha);

	return os;
}

std::ostream& NoBoolalpha(std::ostream& os) //Buda bir manipulator
{
	os.unsetf(ios::boolalpha);

	return os;
}

int main()
{
	bool b1{}, b2{},b3{};

	//cout << b1 << b2 << b3; // b1 true false olsun, b2 0-1 olsun, b3 yine true false istersen bunu yapma şansımız yok.set edersek üstte hep set olacak. unset edersek
								// hepsi unset edilir.Bunu maniplator ile yapabiliriz.

	cout << Boolalpha << b1 << NoBoolalpha << b2 << Boolalpha << b3;
}

ÇIKTI
-----
false 0 false

Originalleri boolalpha noboolalpha

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bir Örnek Daha

Hex maniplatoru bunu hexadecimal halde yazacak hale getiriyor.
uppercase ise uppercase hale getiriyor.

std::ostream& hex(std::ostream& os)
{
	os.setf(std::ios::hex);

	return os;
}

int main
{
	int x = 10;

	cout << hex << uppercase << showbase << x << "\n";  // daha çok bu tipi kullanacağız.
	// bu olmasaydı 3 kere setf çağıracaktık

	// cout.setf(std::ios::hex, ios::basefield); // 2 parametreli başka bir setf funcı
	// cout.setf(std::ios::showbase);
	// cout.setf(std::ios::uppercase); 

	for(int i = 0; i < 10; ++i)
	{
		std::cout << rand() << "\n";
	}

}


MOLA 
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

SETF NIN DİĞER OVERLOADU
------------------------
Bazı formatlama özellikleri boolean yani ya var ya yok.true -false, 0-1, nokta yazacak- yazmayacak.


int main()
{
	double dval = 34;

	cout << dval << "\n"; // double ama 34 yazdı. nokta yazmadı veya sonrasını

	//cout.setf(ios::showpoint); // bu veya aşağıdaki maniplatör aynı işi yapıyor.
	cout << showpoint;
	
	cout << dval << "\n"; // Şimdi noktalı yazdı

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SHOWPOS
Başına + koyup yazdı, pozitiv demek aslında

int main()
{
	int x = 345;

	cout << showpos;

	cout << x; // +345 yazdı
	cout << x; // +345 yazdı
	cout << x; // +345 yazdı

	// akım nesnesinin state inin bir parçası oldu bu. Bunu tekrar değiştirmem lazım eski hali için
	cout << noshowpos;
	cout << x; // 345 yazdı
	cout << x; // 345 yazdı

}

=============================================================================================================================================================================

BAZI ÖZELLIKLER RADIO BUTTON ŞEKLINDE
Yani birden fazla seçenek var, birini set edince diğerlerinide eski haline getirmek gerekiyor.

Mesela, sayı sistemi ya hex ya dec yada oct olmak zorunda.
hex 
dec
oct

Böyle durumlarda hex haline getirmek için fmtflags türünden değişkenin 3 bitinide sıfırlamamız gerekiyor ondan sonra 1 leyeceğiz.

int main()
{
	using namespace std;

	std::cout << bitset<32>(ios::dec) << "\n";
	std::cout << bitset<32>(ios::hex) << "\n";
	std::cout << bitset<32>(ios::oct) << "\n"; // bunlar 3 ayrı bit

	cout.setf(ios::hex); // hex i 1 yapar diğerine dokunmaz.Burada risk var. 2 veya 3 bit birden 1 olabilir.
	//diğerlerini sınıflayıp hexi b1 yapmamız lazım. Bunun için basefield var. Basefield yukarıdaki 3 biti barındırıyor ve hepside 1.yazdırılınca görülüyor

	cout.flags(cout.flags() & ~ios::basefield); Buradan sonrada hex maskesiyle veyalayacağız.Bunu yapmanın pratik yolu diğer setf functionu
	
	//Bunu yapmanın pratik yolu setf func
	cout.setf(ios::hex, ios::basefield); // 16lık sayi sistemi.Bİrinci parametre set edilmek istenen değer. 2. si ise sıfırlanmak istenen bitleri belirtiyoruz.Yani basefield
	
	cout.setf(ios::dec, ios::basefield); // 10luk sayı sistemi
	
	cout.setf(ios::oct, ios::basefield); // 8 lik sayı sistemi.

}

=============================================================================================================================================================================

BUNLARI ÇAĞIRAN MANIPLATOR DE ÇAĞIRABILIRIZ.

std::ostream& Hex(std::ostream& os) //klasik maniplator imzası ve return değeri
{
	os.setf(ios::hex, ios::basefield);
	return os;
}

int main()
{
	cout << hex << 47802; // ekrana baba yazdı
	cout << Hex << 47802; // Buda bizim yazdığımız
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FARKLI BİR MANİPLATOR YAZIYORUZ

std::ostream& ubhex(std::ostream& os)
{
	os.setf(ios::showbase | ios::uppercase); // Hem 16lık sayı sisstemi tabanı hemde karakterleri büyük yazacak.Bu standart değil.
	os.setf(ios::hex, ios::basefield);
	return os;
}

int main()
{
	cout << ubhex << 47802; //
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

BASEFIELD KULLANAN 3 TANE MANIPLATOR VAR

1 - ios::hex / ios::dec // ios::oct   ve alan bayrağı olarakta ios::basefield
2 - ios::left / ios::right // ios::internal   ve alan bayrağı ios::adjustfield
3 - ios::fixed / ios::scientific / ios::hexfloat // ios::defaultfloat   ve alan bayrağı olarakta ios::floatfield

2 nolu madde için açıklama

|345			   |  ios::left. önce sayıyı yazacak sonrada doldurmak karakterleri. sayı olmak zorunda da değil stringte olabilirdi.
|				345|  ios::right. Önce doldurma karakterleri sonra sayı.
|+				345|  ios::internal. İşaret başa gelecek, sayının kendisi sağa gelecek.
|-			    345|  ios::internal

3 nolu madde içn açıklama
Burada durum biraz farklı. Default olarak ikiside set edilmemiş.ikiside set edilmemişse sayının büyüklüğüne bağlı olarak fixed mi scientific mi olduğuna kendisi
karar veriyor. defaultfloat demek fixed veya scientific set edlmemiş demek. sayı büyüklüğüne göre kendisi karar veriyor.İkiside set edilmişse hexfloat modunda

=============================================================================================================================================================================
=============================================================================================================================================================================

#include <iomanip>  // parametreli maniplatörler iomanip içinde

int main()
{
	int x = 10;

	cout << setw(16) << x << "necati"; // default olarak sağa dayalı.default right

	------------------------------------------------------------------------------------------------------------------------------------------------------

	int x = 10;
	cout << left; // sola dayalı
	//cout.setf(ios::left,ios::adjustfield); // yukarıdaki ile aynı.Left aslında bu çağrıyı yapıyor.
	cout << setw(16) << x << "necati\n"; // sola dayalı
	
	------------------------------------------------------------------------------------------------------------------------------------------------------

	//cout.setf(ios::right,ios::adjustfield); // Şimdide sağa dayalı yazdı
	cout << setw(16) << x << "necati\n";
}

=============================================================================================================================================================================
=============================================================================================================================================================================

BUNLARIN HEPSİNİN BİRER DEFAULT DURUMU VAR

void print_flag(std::ostream&os)
{
	if(os.flags() & ios::left)
		std::cout << "left biti set edilmis\n";
	if(os.flags() & ios::right)
		std::cout << "right biti set edilmis\n";
	if(os.flags() & ios::internal)
		std::cout << "internal biti set edilmis\n";
}

int main()
{
	print_flag(cout); // hiçbiri set edilmemiş. Hiçbiri set edilmediyse bu default durumda right olarak yazılmasını sağlıyor.
}

Bunların hepsi dosya işlemlerinde de kullanılacak. Hiçbir farkı yok.
Dosyaya belleğe yazma işlemlerinde aynı formatlama işlemleri kullanılacak.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	cout.setf(ios::left); //sadece left
	cout.setf(ios::right); // hem left hem right ki bu doğru birşey değil
	cout.setf(ios::internal); // 3 üde set edilmiş.

	cout.setf(ios::left,ios::adjustfield);// sadece left edildi burada.2. parametre bitleri 0 lıyordu
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_flag(std::ostream&os)
{
	if(os.flags() & ios::scientific)
		std::cout << "scientific biti set edilmis\n";
	if(os.flags() & ios::fixed)
		std::cout << "fixed biti set edilmis\n";
}

int main()
{
	print_flag(cout); // default olarak ikiside set edilmemiş.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İKI BAYRAKTA SET EDILMEDIYSE SAYININ BÜYÜKLÜĞÜNE FIXED MI SCIENTIFIC MI OLDUĞUNA KENDI KARAR VERIYOR.

int main()
{
	cout << 23.24; // fixed yazdı
	cout << 12312234235.12323544356; // scientific modda yazdı
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EĞER FIX SET EDILIP SCIENTIFIC SET EDILMEDIYSE

int main()
{
	cout << fixed; // fixed maniplatoru
	cout.setf(ios::fixed, ios::floatfield); // yada aynı anlamda bunu kullanabiliriz.

	cout << 123213124.3243; // fixed yazmazya zorladık.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SCIENTIFIC YAZDIK ARTIK

int main()
{
	cout << scientific; // scientific maniplatoru
	cout.setf(ios::scientific, ios::floatfield); // yada aynı anlamda böyle yazdıysak

	cout << 123.12421; // scientific
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	cout.setf(ios::fixed |ios::scientific);
	cout << 123.4123; // ikisi birden set edildiyse sayıyı 16 lık sayı sisteminde yazıyor.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2 BITIN SET EDILMESI DURUMUNDA YANI HEM SCIENTIFIC HEMDE FIXED SET EDILDIYSE BUNA HEX FLOAT DENIYOR VE REEL SAYIYI HEXADECIMAL SAYI SISTEMINDE YAZIYOR.

int main()
{
	cout.setf(std::ios::fixed | std::ios::scientific)
	cout << hexfloat; // yukarıdaki ile bu maniplator kullanımı aynı anlamda. C++11 den önce yoktu

	cout << 123.4352;
}

=============================================================================================================================================================================
=============================================================================================================================================================================

BIR OLANAK DAHA VAR

Rdbuf ın 2 özelliği var.

1 - Bu return değerini alan bir inserter var. Bu inserter o bufferdakileri çıkış akımına veriyor.Bir dosyayı yazdırmanın en kolay yoluda bu.
	akımın bufferına bir pointer veriyor.return eğeri streambuf*.

int main()
{
	cout.rdbuf(); 
	
	ifstream ifs{"test.txt"};
	cout << ifs.rdbuf() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2 - Aynı bufferın 2 farklı cout nesnesinin paylaşması durumu

int main()
{
	ostream mycout{ cout.rdbuf() }; // Burada mycout, cout ile aynı bufferı paylaşacak
	cout<< "onur goksu\n";
	mycout<< "onur goksu\n";

	//Coutun değilde mycoutun format stateini değiştirerek aynı çıkış akımına farklı formatlama özellikleriyle yazımı gerçekleştirebilirim.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ÖR:

int main()
{
	int x = 47802;
	bool b = true;
	double d = 23.87;

	ostream mycout{cout.rdbuf()};

	mycout << boolalpha << hex << uppercase << showbase << scientific;

	cout << x << " " << b << " " << d << "\n";  // ikiside standart çıkış akımına yazdırdı.
	mycout << x << " " << b << " " << d << "\n";  // bununla yazınca başka formatlama özellikleri geldi.

}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Alan bayraklarıyla iş bitti.

ios::floatfield
ios::basefield
ios::adjustfield

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

FORMAT İLE GELEN DEĞİŞİKLİKLERDEN BİRİ DE ŞU
Yazma alanı genişliği içinde ortalamalı yazmakta var

int main()
{
	int x = 78323;

	cout << format("|{:^22}|",x); // ^ortalayan bu. Bu format state olarak akım nesnelerinde yok
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

LOCALIZASYON
Çıkış akımına verdiğimiz yazılar var, Japonya için yazıların japonca çıkması gerekiyor, türkçe için türkçe çıkacak.
Maalesef standart çıkış akımının kendi formatlama özellikleriyle bunu yapmak çok zor ama formatkütüphanesinin getirdiği en büyük avantajlardan biri

int main()
{
	int x = 35;
	double dval = 43.34;
	string name = "umut";

	cout << format("isim {} yas {} saat ucreti{}",name,x,dval) << "\n";
	cout << format("isim {0} yas {1} saat ucreti{2}",name,x,dval) << "\n";
	cout << format("isim {2} yas {1} saat ucreti{0}",name,x,dval) << "\n";

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	int x = 35;
	cout << format("{0} * {0} * {0} = {1}\n", x, x * x * x);

	---------------------------------------------------------------------------------------------------------------------------------------------------------

	AYNI FORMATLAMA İŞLEMLERİ GİRİŞ TARAFINDA DA GEÇERLİ

	std::cout << "bir tamsayi girin: ";
	int x{};
	cin>> hex; // Hex maniplatörünü standart giriş işlemleri için kullandım
	cin >> x;
	std::cout < "x = " << x << "\n";

	---------------------------------------------------------------------------------------------------------------------------------------------------------
	
	std::cout << "bir tamsayi girin: ";
	int x{};
	cin >> oct; // Oct maniplatörünü standart giriş işlemleri için kullandım
	cin >> x;
	std::cout << "x = " << x << "\n";

}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

BÜTÜN FORMATLAMA ÖZELLİKLERİ BAYRAK ŞEKLİNDE BİT SEVİYESİNDE TUTULACAK BİLGİLER DEĞİL
Bitsel seviyede tutulamayacak bilgiler için aşağıdaki formatlama özellikleri var

a - Yazma alanı genişliği
b - Doldurma karakteri(fill character, yazma alanı genişliği yazılacak karakterden fazla ise geri kalan kısıma yazılacak karakterlere doldurma karakteri deniyor,defaultta boşluk)
c - Precision

NOT : KALICI OLMAYAN TEK FORMATLAMA ÖZELLİĞİ YAZMA ALANI GENİŞLİĞİ !!!!!!!!!

Yazma alanı genişliği with ile set hemde get ediliyor

int main()
{
	auto n = cout.with(); // şuandaki yazma alanının şimdiki genişliğini verir.Defaultu 0. Her yazma işleminden sonrada yien 0 a çekiliyor. Yazma alanı genişliğ yazılacak
						  // karakter sayısından daha az olması demek, yazma alanı genişliğinin etkisiz olacağı anlamına gelir. Budama olmuyor yani.

	std::cout << "n = " << n << "\n";

	auto n = cout.with(10); // yazma alanı genişliğini set eder eski değeri get eder. n eski değeri tuttu.
	std::cout << "n = " << n << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNUN YERINE IOMANIPTEKI SETW ILE KULLANABILIRIZ

int main()
{
	YAZMA ALANI ÖRNEKLERİ

	cout << left; 
	cout << setw(20) << "necati" << "hasan"; // 20 karakterlik alana necati ve sonrasında yazma alanı genişliği 0 olacak ve hasan yazacak.

	------------------------------------------------------------------------------------------------------------------------------------------------------

	cout << left;
	cout.width(20); // yazma alanı genişliği 20 oldu. Aynı şeyi yaptı.
	cout << "necati" << "hasan";

	------------------------------------------------------------------------------------------------------------------------------------------------------

	DOLDURMA KARAKTERİ 

	auto c = cout.fill(); // c nin değeri 32 çıkar.Defaultu boşluk karakter oda ascide 32
	
	std::cout << static_cast<int>(c) << "\n"; //32

	------------------------------------------------------------------------------------------------------------------------------------------------------

	cout.fill('_'); // bununla setfill aynı

	cout << setfill('_'); // ikisinden birini kullanacağız.İkiside aynı işi yapıyor.

	cout << right;

	cout << setw(20) << "haydar"; // ____________________haydar yazdı

	------------------------------------------------------------------------------------------------------------------------------------------------------

	cout << setfill('*'); // ikisinden birini kullanacağız

	cout << left;

	cout << setw(20) << "haydar"; // haydar************************

	------------------------------------------------------------------------------------------------------------------------------------------------------

	PRECISION

	cout.precision(); // precisionun eski değeri. 6 bu değer.

	cout.presicion(15); // noktadan sonra 15 basamak yazılsın demek yada setpresicion kullanacağız. Buda iomanipte.Kuralları biraz farklı j nin kitabından bakabiliriz.

	cout << fixed << setprecision(15); // setprecision iomanip gerektiriyor.

	cout << 76.321421; // 76.321421000000001

}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================


PARAMETRELİ MANİPLATORLER
-------------------------
12 karakter boşluk 5 karakter boşluk ve 8 karakter boşluk verecek isimler arasında

int main()
{
	cout << "murat" <<sp(12) << "ali" << sp(5) << "veli" << sp(8) << 123 << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EN BASIT YÖNTEM SP NIN BIR CLASS OLMASI

class sp
{
public:
	sp(int n = 0, char c = ' ') : mx{n}, mc{ c } {  }
	friend std::ostream& operator<<(std::ostream&os, const sp& x)
	{
		int n = x.mx;
		while(n--)
		{
			os.put(x.mc);
		}
		return os;
	}
private:
	int mx;
	char mc;
};

int main()
{
	cout << "murat" <<sp(12) << "ali" << sp(5) << "veli" << sp(8) << 123 << "\n";

	cout << "murat" <<sp(12) << "ali" << sp(5) << "veli" << sp(8, '$') << 123 << "\n";
}

ÇIKTI
-----
murat            ali     veli        123
murat            ali     veli$$$$$$$$123

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int x{};
	int y{};
	int z{};
	
	std::cout.setf(ios::unitbuf);   // her yazma işleminden sonra bir kez bufferı flush ediyor.Yazma işlemi anında yapılacak yani. C den biliyoruz
}

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

CONDITION STATE
---------------
Bir akım nesnesi ya iyi durumdadır bu ne demek, bir giriş yada çıkış işlemi yapılabilir durumda,
Ya da hata durumundadır, bu durumda giriş çıkış işlemleri yapılamayacak.Bir hata oluşmuş bu hatayı ortadan kaldırıp ondan sonra giriş yada 
çıkış nesnelerini kullanmamız gerekiyor.

Giriş çıkış sınıflarının iterface inde taban snıfların interface inden alınan constexpr static veri elemanları bitsel maskeleri ve bazı üye funclar kullanılarak
akımın sağlık durumunu test edip değişiklikler yapıyoruz. Ve buna yönelik değişiklikler yapabiliyoruz.

int main()
{
	ios::iostate // akım nesnesi akımın sağlık durumuna işaret eden bir veri elemanı.bu türeş ismi. Türü mesela hocada int
	ios::fmtflags // buda int olabilir. Bunlar bitsel maske olarak kullanılacak.
}

Tepedeki taban sınıfın constexpr static veri elemanları var.Sonunda bit son eki var.Aşağıda yazıldı.
4 tane ios_base türünden maske olarak kulanılabilecek elemanlarımız var.

Goodbit = Sağlıklı bir akım nesnesinin elemanı goodbit durumunda olacak. Tüm bitler 0 demek bu. Herhangibir hata yok. Akım nesnesi kullanılabilir durumda demek.

Herhangibir hata oluştuğunda badbit, failbit veya eofbit set edilmiş durumda olabilir.

int main()
{
	std::cout << ios_base::goodbit << "\n"
	std::cout << ios_base::badbit << "\n"
	std::cout << ios_base::failbit << "\n"
	std::cout << ios_base::eofbit << "\n"
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNLARI GET VE SET EDEN FUNCLAR VAR 

RDSTATE

int main()
{
	cout << cin.rdstate(); // cin akımının streamini kontrol ettik hata yoksa 0 yazmalı

	auto state = cin.rdstate(); // return değerini değişkene atayıp

	cout << bitset<32>(state) << "\n"; //Burada bitsel seviyedeki karşılığına baktık. 0 çıktı. Akım good durumda
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GOOD DURUMUNDA OLUP OLMADIĞINI TEST ETMEK İÇİN FUNCLAR ÇAĞIRABİLİRİZ

int main()
{
	std::cout << "bir tamsayi girin\n";
	int x;
	cin>> x; // 23 hata yok. Ali için akım hata durumuna geçti.
	
	if(cin.good()) //DİKKAT
	{ 
		std::cout << "akim iyi durumda\n";
	}
	else
		std::cout << "akim hatali durumda\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Aynı şekilde operator bool functa kullanılabilir yani

if(cin) //Logic bağlamda kullanılabilir cin.operator bool() da yazılabilir aynı anlamda
	{
		std::cout << "akim iyi durumda\n";
	}
	else
		std::cout << "akim hatali durumda\n";

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIRÇOK C++ KITABININ ILK ÖRNEĞI AŞAĞIDAKI
Talihsiz bir örnek birçok şeyi bilmek gerekiyor.

int main()
{
	int x;

	while(cin>>x) // cin.operator>>(x).operator bool() bu anlama geliyor bu kod. operator bool da true dönerse döndüge kalır ve akımdakini yazdırır.
	{
		cout << "(" << x << ")";
	}
	
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Aşağıdaki gibide yazılabilir.

int main()
{
	int x;

	while((cin>>x).good()) // cin>>n in return değeri cin nesnesinin kendisi bu da ne demek her operasyondan sonra good çağır true dönerse devam et.False içe çıkar
	{
		cout << "(" << x << ")";
	}
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FAIL FUNC

int main()
{
	int x;
	
	std::cout << "bir tamsayi girin\n";

	cin >> x;

	if(!cin)  //  Bu olur
	{
		cout << "Akim hata durumunda";
	}

	if(cin.fail())  // buda olur
	{
		cout << "Akim hata durumunda";
	}
	if(!cin.good()) // buda olur aynı şekilde.Hepsi hata durumunda girecek ifler.
	{
		cout << "Akim hata durumunda";
	}

}

MOLA

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

SINIFIN DİREK 2 FUNCT I EOF BİTİNİN SET EDİLİP EDİLMEDİĞİE BAKIYOR.
Yani hatanin kaynaği, bufferda yada file da okunacak byte kalmamasindan ötürü mü buna bakiyor.
bu durumda eof biti set ediliyor.

BAD BIT = Tahmini mümkün olmayan daha ciddi hatalarda set ediliyor.Formatlama uymsuzluğu veya eof durumlarında set edilmiyor.
memory problemi falan varsa set ediliyor.veya başka durumlarda.

Basit bir func yazarak bunu test edebiliriz.


void print_state(istream& is)
{
	if(is.rdstate() == 0)
	{
		std::cout << "akim iyi durumda\n";
	}

	if(is.rdstate() & ios::failbit)
	{
		std::cout << "failbit set edilmiş\n";
	}
	
	if(is.rdstate() & ios::eofbit)
	{
		std::cout << "eofbit set edilmiş\n";
	}
	
	if(is.rdstate() & ios::badbit)
	{
		std::cout << "badbit set edilmiş\n";
	}
}

int main()
{	
	int x;
	std::cout << "giris";
	cin>> x;

	print_state(cin);
}

ctrl + z eof simulasyonu idi windowsta

=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================
=============================================================================================================================================================================

BELLEK ÜZERINDE OKUMA YAZMA IŞLEMLERI

Buradaki kullanılacak başlık dosyaları sstream. 3 tane sınıf var.
ostringstream : ostream den kalıtımla elde edilmiş. ostream im tüm interface ini almış ama ilave func ı var
istringstream : istream den kalıtımla elde edilmiş. istream interfaceini almış
stringstream : basic_iostream sınıfından kalıtımla elde edilmiş.

ostringstream yerine artık format kullanılmaya başlandı.Ç ıkış akımı nesnesi. bellekteki belli bir alan yazdırdı.

int main()
{
	ostringstream oss; // Buda bir çıkış akımı nesnesi. Ama çıkışı bellekte kendi elde ettiği alana yapıyor.
	int x = 123;

	oss << x; // yazma işlemini belleğe yapacak doğrudan

	cout << oss.str() << "\n"; // belleğe yazılan veriyi bir yazı olarak almak için str funcını kullanırız.
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <sstream>
int main()
{
	ostringstream oss;

	oss << rname() << '_' << rfname() << '.' << Irand{100,200}();

	cout << oss.str() << "\n";

	------------------------------------------------------------------------------------------------------------------------------------------------------------

	auto s = oss.str();

	reverse(s.begin(), s.end()); // ters çevirdik
	cout << s << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:
#include <ctime>
#include <iomanip>

std::string get_current_time() //Func çağrıldığı zamanki tarih zaman bilgisini yazı olarak  verecek.
{
	std::time_t timer;
	time(&timer);
	struct_tm *p = localtime(&timer);

	ostringstream oss;

	oss << setfill('0'); // boş olan yere 0 yazacak

	oss << p->tm_year + 1900 << '_' << setw(2) <<p->tm_mon + 1 << '_' << setw(2) <<
	p->tm_mday << '_' << setw(2) << p->tm_hour << '_' << setw(2) <<p->tm_min << 
	_' << setw(2) <<p->tm_sec;

	return oss.str();
}

int main()
{
	cout << get_current_time() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUNU YAPMAK IÇIN FORMAT KÜTÜPHANESINI KULLANIRIZ ASLINDA.ÇOK DAHA EFEKTİF

std::string get_current_time()
{
	std::time_t timer;
	time(&timer);
	struct_tm *p = localtime(&timer);

	ostringstream oss;

	oss << setfill('0'); // boş olan yere 0 yazacak

	return std::format("{}_{0:2}", p->tm_year + 1900, .... );   // özetle böylee yapılabilir. Formatın return değeri string
}

int main()
{
	cout << get_current_time() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	ostringstream oss;
	for(int i = 0; i < 10; ++i)
	{
		oss << i;
	}

	oss << "onur"; // onuna onur ekler

	cout << oss.str() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BUFFERI BOŞ YAZI HALINE GETIRMEK IÇIN

int main()
{
	ostringstream oss;
	for(int i = 0; i < 10; ++i)
	{
		oss << i;
	}

	oss.str(""); // akımı boş hale getirdi. Sildi.
	oss << "onur"; // sadece onur çıkar

	cout << oss.str() << "\n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Date ile küçük örnek yapıldı yazmadım

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Mülakat Sorusu

class Ndate{
public:
	Ndate(int day, int mon, int year) : d{day}, m{mon}, y{year} { }
	friend std::ostream& operator<<(std::ostream& os, const Ndate& date)
	{
		return os << date.d << " " << date.m << " " << date.y;
	}

private:
	int d, y, m;
};

int main()
{
	using namespace std;
	
	Ndate mydate{12,5,1987};

	cout << left;
	cout << setw(30) << mydate << "necati"; // böyle yazınca sapıttı, Neden ? Mydate i 30 karakterlik alana yazmak istedik aslında.Ama sadece ayın gününü bu alana yazdırdı
}


ÇÖZÜM(Format ile çözmeyeceğiz. Başka yöntemle isteniyor)

class Ndate{
public:
	Ndate(int day, int mon, int year) : d{day}, m{mon}, y{year} { }
	friend std::ostream& operator<<(std::ostream& os, const Ndate& date)
	{
		ostringstream oss;
		
		oss << date.d << " " << date.m << " " << date.y;

		return os << oss.str();
	}

private:
	int d, y, m;
};

int main()
{
	using namespace std;

	Ndate mydate{12,5,1987};

	cout << left;
	cout << setw(30) << mydate << "necati"; // ARTIK ÇALIŞIR :D:D Aslında önceki sefer sadece bir tanesine etki etmişti ama bu sefer tek bir yazıyı yazdırdığımızdan
}											// bu sorun ortadan kalkacak.



*/
