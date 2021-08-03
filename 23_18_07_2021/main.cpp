/*

Exception Handlingten Devam
Biraz tekrar
Hata nedir? Bir programın çalışması sırasında olan hatalarıda ikiye ayırdık. birine programlama hataları dedik.
Bunlar yanlış kod yazılmasıya oluşan hatalar.Bunları bulup düzeltiyorduk.
Aslında buna yönelik debugger programlar var ama biz kendi hatalarımızı bulmaya yönelik kodlar ekliyoruz 
bunlar asertion idi. static assertion ve dynamic assertion olarak ikiye ayrılıyor.

Birde exceptionlar var.istisnai durumlar.Bunlar bir önceki ders bahsedildi o yüzden tam yazmıyorum.
bir func çağrılıyor ve func işini yapamayacak durumla karşılaşıyor.2 karar verecek, ya programı sonlandıracak ya da başka bir uyarı gönderecek.
Kendisini çağıran koda işini yapamadığını bildirmek zorunda.

Bunu pointer ile veya int değerleriyle gösteriyor veya global bir değişken set edilmesiyle yapılıyordu.Buraya kadar gelmiştik.

Geleneksel yöntemler biraz ilkel kalıyor.Dezavantaj içeriyorlar. 
C++ Java C# gibi diller exception handling araçlarını barındırıyorlar.Bir çok dilde benzer bir yapıya sahip.
Javada tamamen aynı değil.

=================================================================================================================================================
=================================================================================================================================================

Geleneksel Yöntemlerin Dezavantajları
--------------------------------------
1 - Return değerini sınamak zorunlu değil. (non-forcing). fopen çağırdık return değerini test etmedik. 
	Ama dosya açılmadıysa null ptr döndürüyor. bir return değer var ama yaptırımı yok. C de return değeri kullanılmış mı 
	kullanılmamış mı test eder ve buna dair bir uyarı verir.

	Daha devrimci bir araç seti ne yapar?
	Belkide işini yapamayınca işini sonlandırır. Yada başka bir kod müdahale edecek.
	Bu şekilde olağan dışı durumlar ihmale açık olmayacak.Exception handling te durum böyle.

2 - Kodun okunması ve yazılması ve değiştirilmesi zorlaşıyor.Bu çok önemli 
	Mesela 
	x = dothis();
	if(expr){
	}
	if ...
	...

	C kodlarında temel şu problem var. Aynı anlama gelen 2 farklı kod var.

	1 - İş gören kod.Mesela database e bağlan, şu dataları çek dosyaları şuraya yaz... 
	
	2 - Hata işleyen kod. Veri tabanına bağlan.Ya bağlanamazsan	şunu yap.Dosya oluşturmaya çalış, yapamazsan şunu yap...
		gibi.

		Hangi if algoritma parçası hangi if iş yapan kod?
		birbirine karışmış durumda. Değişiklik yapmakta zor.

		Bunların iç içe geçmemesini isteriz biz.Bu durumda değişiklik yapmak ta zor. Koda bakınca ne yaptığını anlayayım veya hata işleme koduna
		bakınca nasıl bir hata işleme yapılmış onu anlayayım isteriz.Burada iş gören kod ile hata işleyen kod iç içe geçmiş.

	3 - Hatayı tespit eden kod ile, hatayı işleyecek(müdahale edecek) kod arasında doğrudan bir bağlantı yok.

		Biz bizi çağırana hatayı iletiyoruz. Bir çok durumda karar verme yetkisi olan kod daha üstteki state frame de.

		Mesela user interface ile ilgili işlem yapan koddayız. Fonksiyon display_menu() gui ekranına menuyu yazıyor.
		Bu fonksiyon bu ii yaparken func çağırmış, o başkasını çağrmış,	o öbürünü çağırmış...
		f1 -> f2 -> f3 -> f4 -> f5 ...

		Menuyu yazdıramazsak bir tuşa basacağız ve program çalışacak yada devam edecek... Programın karmaşıklığı çok arttı.
		Daha iyi bir mekanizma olsaydı, f5 teki hata doğrudan f1 e iletilirdi. Öyle kod olsunki hataya müdahale eden koda hemen bu hata iletilsin.
		Hataya müdahale eden kodla hatayı tespit edecek kod arasında runtime açısından doğrudan bir link oluşturulsun.

		Bunlar major dezavantajlar.Aşağıdakilerden bahsetmiyoruz bile. Ctor ın return değeri kavramı yok.Nesneyi hayata getirme sürecinde
		hata oldu ama return değeri yok, ne yapacak ? En iyi ihtimalle flag	değişken ile kontrol edebilir.Buna zombie değer deniyor.
		Bu değer nesnenin başarılı şekilde hayata gelip gelmediğini tutabilir.


Modern Programlama dillerindeki exception handling buradaki sorunları ortadan kaldıran yenilikçi bir mekanizma.Her yerde de rahat kullanılamayabilir.
Mesela Realtime OS lerde başka sorunlar oluşabildiği için kullanılmayabilir.Gömülü sistemlerde başka hatalardan dolayı kullanılmayabilir.
Mesela implementasyon zorluğu gibi.

Artık çalışma zamanına ait kontroller exception handling ile yapılmalı. Başka istisnai durumlar yoksa.

Exception handling in kesinlikle bir maliyeti var.
Derleyticilerin zaman içinde geliştirilmesi nedeniyle maliyet düştü.
Maliyet açısından bunun kabul edilemeyeceği ortamlar olabilir.Ama az.
Maliyet faktörü yok değil ama ne verdik ve ne elde ettik buna bakmalıyız.
Bu açıdan bakınca çok çok kritik bir sistem değilse kullanılmalı.

======================================================================================================================================================
======================================================================================================================================================
======================================================================================================================================================

EXCEPTION HANDLING 3 ANA BİLEŞENİ VAR
-------------------------------------
1 - Try Blok
------------
İçinde çalışan kodlardan bir hata oluşumu test edilecek kod alanının belirlenmesi.
Bir kod bloğu oluşturuyoruz buna try block deniyor. keyword ise try.

Bu blok içerisinde olan hataları yakalar. dışındakileri değil

2 - Catch Blok
--------------
Try dan hata gelirse, programın akışı bu bloka gelsin ve hatayı bu blok içindeki kod işlesin.
keyword catch

3 - Throw Statement
-------------------
İşlem yapılamadığı zaman, bu bilgiyi kendisini çağıran koda (nesne yaratıp bunu) gönderecek kısım.
throw statement - exception throw etmek deniyor.Exception throw derken exception object throw etmek.

Ey beni çağıran kod veya çağıranı çağıranı çağıran kod, ben işimi yapamadım, bir nesne oluşturup gönderiyorum,
kim buna müdahale etmek isterse, nesneye bakıp incelesin ve müdahale etsin.
Aslında exception (object) throw ediliyor


=====================================================================================================================================
=====================================================================================================================================
=====================================================================================================================================
=====================================================================================================================================


Throw Statement
---------------
Programın akışı bu deyime gelirse, akış buradan çıkacak, bu hatayı işleyebilecek bir kod varsa oraya girecek, 
ama herhangibir hata işlemeye yönelik kod olmaması durumunda, program abnormal olarak sonlandırılacak.

Bir exception yakalanamazsa programın sonlandırılması sonucunu doğuruyor.

SENTAKS
throw expr;

throwu bir ifade izliyor.Bu ifade çoğunlukla bir sınıf türünden ifade ama başka nesnelerde olur.
Programın akışı bu throw deyimine gelince, akış bu throw deyimini içeren functan çıkacak ve buhatanın yakalanıp işlendiği yere, 
yani catch bloğuna girer ama bunu yakalayacak kod yoksa terminate isimli func a yapılacak çağrıyla sona erer.
Yani, ya hata yakalanacak ya da program sonlanacak.

throw statement ile gönderilen hata nesnesi yakalanmaz ise(catch edilmezse) program sonlanıyor. Bu bazı durumlarda kabul edilemez.
Eğer bir hata gönderilipte yakalanmazsa, programın sonlanması demek
a - Programın tekrar çalıştırılmasını gerektirebilir.
b - Ciddi kayıplar olabilir.
c - Programın sonlandırılması ciddi zararlara yol açabilir.

Yani gönderilecek tüm exceptionların yakalanması gerekir. Bunun yakalanmadan programın sonlandırılması kabul edilebilir durum değil.
2 strateji var

a - Terminative strateji.
	Sonlandırmaya yönelik.Hatayı yakaladık ama yapılabilecek birşey yok.Uyarı mesajları gönderildi ve
	kontrollü bir şekilde programın sonlandırıyoruz.Ama kontrollü bir şekilde.

b - Resumptive strateji
	Hata gönderilecek, müdahale edecek kod bunu yakalayacak ve program kayıp olmadan hizmet vermeye devam edecek.

---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------


BUNLARA BAKALIM


#include <iostream>

void f3()
{
	std::cout << "F3 cagrildi\n";
	throw 1; // throw statement sonradan ekledik
	std::cout << "F3 sona erdi\n";
}

void f2()
{
	std::cout << "F2 cagrildi\n";
	f3();
	std::cout << "F2 sona erdi\n";
}

void f1()
{
	std::cout << "F1 cagrildi\n";
	f2();
	std::cout << "F1 sona erdi\n";
}

int main()
{
	std::cout << "main basladi\n";
	f1();
	std::cout << "main sona erdi\n";
}

ÇIKTI
-----
main basladi
F1 cagrildi
F2 cagrildi
F3 cagrildi


Yukarıdaki throw yakalanabilir yada yakalanamayabilir. Bir hatanın gönderilipte yakalanamama durumuna uncaught exception(yakalanamayan hata)
Bu durumda programın çalışması sonlandırılıyor. Burada std::terminate çağrılıyor.Bu da altta abort() çağırıyor.
Çalıştırdık ve abort() çağrıldığını gördük

---------------------------------------------------------------------------------------------------------------------------------------------

Madem terimnate abort çağırıyor, Neden direkt abort kullanmıyoruz.
Nedeni, terminate davranışını özelleştirebiliyoruz olmamız.Bunu function pointer kullanılmasıyla değiştiren başka bir function kullanabilmek
için kullanıyoruz.set_terminate ile bunu yapabiliyoruz.

return değeri olmayan parametresi olamayan fonksiyon bir function adresine eşisim varmiş std library.
using terminate_handler = void(*)();
typedef void (*terminate_handler)(); yukarıdaki ile aynı.

terminate_handler set_terminate(terminate_handler); // set terminate böyle bir function.
Bu terminate davranışını değiştiriyor. buraya argüman olarak gönderilen function adresi geri dönüş değeride function pointer.
set_terminate çağırıp ona kendi oluşturduğumuz func ın adresini gönderirsek artık bu çağrıdan sonra terminate aobrtu çağırmak yerine 
bizim adresini gönderdiğimiz func ı çağıracak. return değeri ise,bu set işlemi yapılmadan önce terminate hangi func ı çağırıyorsa
onun adresi.


ÖR:
yukarıdaki f1,f2,f3 ler tanımlı

void myfunc()
{
	std::cout << "myfunc cagrildi, myfunc abortu cagiracak\n";
	abort();
}

int main()
{
	set_terminate(myfunc);
	std::cout << "main basladi\n"
	f1();
	std::cout << "main sona erdi\n"
}

Çıktı
-----
main basladi
F1 cagrildi
F2 cagrildi
F3 cagrildi
myfunc cagrildi, myfunc abortu cagiracak


Özet: 
Hata oluşupta yakalanamazsa program sonlandırılır.Nasıl ? Terminate ile.terminate te abort çağırır.
Set terminate ile terminate davranışı değiştirildiyse, abort yerine set terminate e gönderiklen function çağrılır.

Bunlar std namespace i içinde exception başlık dosyasında yer alıyor.
terminate handlera baktık cppreference tan.get_terminate e de baktık.  C++ 11 de geldi.


==================================================================================================================================
==================================================================================================================================
==================================================================================================================================

Try Block
---------
try dan sonra en az bir tane catch bloğu olmak zorunda. 1 den fazla catch bloğu olabilir. 
try içinde bir exception gönderilirse, programın akışı eğer hata yakalanırsa akış, catch bloklarından birine çekilir.

Bir try bloğu oluşturmak ile bu blok içinde çalışan kodlardan gönderilecek hata nesnesini yakalamaya aday oluyor.


int main(
{
	try
	{
		f1(); // f3 ten gelen hatayı yakalamaya aday oluyorum bu blok içinde. throw fiilen burada olması anlamında değil bu		
	}			// bu bloğun içindeki kodların çalışması sırasında bir hata gönderilirse onu yakalamaya aday demek.
}


Peki nasıl yakalıyoruz ?
Try bloğu yukarıdaki gibi olursa sentaks hatası, çünkü her try bloğunu en az bir catch bloğu daha olmalı.
Aşağıda yazdık.

int main(
{
	try{
		f1(); // f3 ten gelen hatayı yakalamaya aday oluyorum bu blok içinde
	}
	catch (int x){  // biraz fonksiyon tanımına benziyor.
	
	}
}

Catch için
1 - (int x)  olmaması sentaks hatası ama 1 den fazla parametresi olmasıda sentaks hatası.
2 - Birden fazla catch bloğu oluşturulabilir ama catch parametrelerin türü birbirinden farlı olmalı.


int main(
{
	try{
		f1(); // f3 ten gelen hatayı yakalamaya aday oluyorum bu blok içinde
	}
	catch (int){

	}
	catch (double){

	}
	catch (long){

	}

	std::cout << "main devam ediyor";
}

3 - Eğer try bloğundan gelen hatanın türü int ise catch(int) e girer, ve throw ifadesi burada tanımlanan değişkene kopyalanacak.
double ise double girer...

Bizim örnekte throw 1; olduğundan catch(int) e girecek programın akışı

4 - Eğer catch int e girdiyse daha sonra hiçbir catch e girmeyerek main devam ediyordan devam eder.

int main(
{
	try{
		f1(); // f3 ten gelen hatayı yakalamaya aday oluyorum bu blok içinde
	}
	catch (int x){
		std::cout <<  "catch (int) x = " << x << "\n" ;
	}
	catch (double){
		std::cout <<  "catch (double)";
	}
	catch (long){
		std::cout <<  "catch (long)";
	}

	std::cout << "main devam ediyor";
}

ÇIKTI
-----
f1 cagrildi
f2 cagrildi
f3 cagrildi
hata yakalandı catch int
main devam ediyor.

Programın akışı f3 ten f2 ye orada f1 e değil direkt olarak f3 ten maine çekilecek


-------------------------------------------

Hata parametresinin türünü double yaparsak

catch(double) den devam eder.

long yazarsak longdan devam eder.

-------------------------------------------


5 - Burada tür dönüşümü yok.
1u yazsaydık hata yakalanamayacaktı.

throw 1u; yakalanamaz
throw 'A'; yine yakalanamaz. Türün tamamen aynı olması gerekiyor.
Hatırlatma : Yakalanamayınca abnormal terminate ediyor.

Bu türlere ait catch bloklarını yazarsak çalışır.

6 - throw 34; dersek buradaki int  catch(int x) teki
x e atanan int olacak. yazdırarak görürüz.

---------------------------------------------------------------------------------
---------------------------------------------------------------------------------

BAZI DETAYLAR
-------------
try bloğu fiilen bir scope oluşturuyor.
try{
	int ival = 10; // ival try bloğu içerisinde kullanılabilir.
}
catch(int x){
	
	ival; //sentaks hatası olur. Try içerisinde ival geçerli.

	int ival2 = 20; // aynı durum catch içinde geçerli.Bu da bir blok.
}

ival , ival2 artık burada kullanılamaz.Scope dışına çıktılar

============================================================================================================================
============================================================================================================================
============================================================================================================================


Neden throwun gönderdiği veri tipi ile catch bloğu parametresi aynı türdense programın akışı o bloğa giriyor?
-------------------------------------------------------------------------------------------------------------
Derleyici bir throw ifadesi ile karşılaşınca aslında şöyle bir kod üretiyor.Derleyici bir nesne oluşturuyor.
Bu nesnenin türü throw ifadesinin türü yani expr türü ne ise derleyici de o türden nesne oluşturuyor.
Böyle bir throw ifadesi aslında derleyicinin böyle bir nesne oluşturması anlamına geliyor.Gönderilen hata nesnesi
derleyicinin oluşturduğu bu nesne.Derleyicinin oluşturduğu bu nesnenin bu hata handle edilene kadar yani programın akışı
catch bloğuna girene kadar bu nesnenin hayatta kalma garantisi var.

throw expr;
catch(T x){

}

psudo code
auto ex_object(expr);

-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------

f3()
{
	int ival;
	throw ival; burada throw ival in kopyasını gönderiyor.
	hatta bu kopyanın dangling referans olmaması için bazı işlemler yapılacak.
	
	throw Myclass{}; Burada da Copy elision var.
}


SONUÇLARINA GELELİM
-------------------
throw Myclass{}; throw statement ne demek.
Biz bunu hatayı bildirmek için kullanıyoruz.Burada verilen throw statement karşılığı oluşturulan nesne 
ile iletilen 2 ayrı bilgi var.

1. Nesnenin türü, bu hatanın neyle ilgili olduğunu anlatıyor.
class MathError{
};

throw MathError{}; // matematikle ilgili olduğu anlaşılıyor.

Yada
class BadDate{
};

throw BadDate{}; // burada tarihle ilgili genel bir bilgi veriyor. int le oluşturmak fazla işe yarayan mekanizma değil.
					// hatanın karakterini anlatan sınıflar oluşturuyoruz.

veya MemoryError
Yani nesne türü hata ile ilgili genel bir bilgi veriyor. 


Burada sınıf hiyerarşisi oluşturuyoruz. Bazı frameworklerde kendi hata hiyerarşilerini oluşturuyorlar.
Burada runtime polymorhism de kullanılıyor.
	
Standart library diyorki standart kütüphaneden oluşan hataların tamamı exception türünden olacak diyor ve garanti veriyor.
vector sınıfının kullanımıyla ilgili member func çağırdık ve bu exception throw etti. Gönderilen exception, exception sınıf
türünden olmak zorunda.

Veya operator kullanımında bu exception throw etti, gönderilen exception, std librarynin exception türünden olmak zorunda.
Burada is a ilişkiside dahil. Gönderilen hatanın exception türünden olması, ya bu türden olacak yada public kalıtım ile 
exception sınıfından elde edilen sınıflar türünden olacak.

class exception{
}

Burada gönerilen hata ya bu türden olacak yada exceptiondan	elde edilen sınıflar türden olacak.

Mesela aşağıda is a ilişkisi ile gönderilen hatanın türü ne olursa
olsun o tür exception sınıfından kalıtım yoluyla elde edilen sınıflardan biriyse, programın akışı buraya girecek.

try{
}
catch(exception &ex){
}


--------------------------------------------------------------------

class exception{
public:
	virtual const char *what()const; // standart exception sınıfında
};									 // bu virtual func var.

try{
	
}
catch(exception &ex)
{
	cout << "hata yakalandı " << ex.what() << "\n";
}

What hata ile ilgili bilgi veriyor.
f3-f2-f1 func ilk başta kullandığımız.
	
void f3()
{
	std::cout << "F3 cagrildi\n";

	std::string s{"ali"};
	auto c = str.at(20); // 20. index geçersiz ise exception throw ediyor.
		
	std::cout << "F3 sona erdi\n";
}
f2..
f1..
main()
{	
	try{
		f1();
	}
	catch(exception &ex){
		//20. index geçersiz olduğundan hata throw edilecek f3 içinden
		//buradaki catch onu yakalayacak.
	
		ex.What(); //Burada hangi func çağrılacak. Bu virtual func(What) ı override eden func çağrılacak.
					// bu hatayı anlatan nitelikte yazı yazar What
	}
}
	
	
Çıktı
-----
F1 cagrildi
F2 cagrildi
F3 cagrildi
invalid string position

---------------------------------------------------------------------------------------------------------------------------------

BURADA 2 NOKTAYA DİKKAT ETMEK GEREKİYOR !!!!!!!!!!!
a - Böyle bir hiyerarşi varsa (% 99 bu var) catch in parametresi referans olmak zorunda.Yoksa object slicing olur.
b - Const semantiğine dikkat.Nesne set edilmeyecekse, daha iyi optimization veya okuyucu daha iyi anlasın diye const kulanılır.

Veriyi kopyalama yoluyla gönderip, referans yoluyla yakalıyoruz !!!!!!!!!!!!!!!!

Neden rerefans yoluyla yakalamalıyız
1 - referans yluyla yapılmazsa copy ctor girecek devreye.copy ctor da exception throw edebilir. bu sebeple
2 - polimprhic hiyerarşi varsa herhangibir sanal function çağırırsak, virtual dispatch devreye girmeyecek.
	Çünkü object slicing olacak.Tür bilgisi gidecek.

Aşağıdaki gibi olur yani

try{
//....
}
catch(const Myexception &r)
{

}

-----------------------------------------------------------------------------------------


Soru: Exception object catch bloğunun sonuna kadar yaşar mı ? Evet.Exception
	  object referansa kopyalanınca yine live extension oluyor.

class Myexception{
public:
	Myexception()
	{
		std::cout << "default ctor\n";
	}
	
	~Myexception()
	{
		std::cout << "Destructor\n";
	}

	Myexception(const Myexception &other)
	{
		std::cout << "Copy Constructor\n";
	}

};

void func()
{
	throw Myexception{};
}

int main()
{
	try{
		func();
	}
	catch(Myexception&)
	{
		std::cout << "Hata yakalandi\n";
		getchar();
	}
}

ÇIKTI
-----
default ctor -> Bu copy ellisionun devreye girdiğini gösteriyor
Hata yakalandi -> hata yakalandı yazısı çıktı ve halen destructor çalışmadı.Live extension var.

---------------------------------------------------------------------------------------------------

Biraz değiştirelim

class Myexception {
public:
	Myexception()
	{
		std::cout << "default ctor\n";
	}

	~Myexception()
	{
		std::cout << "Destructor\n";
	}

	Myexception(const Myexception& other)
	{
		std::cout << "Copy Constructor\n";
	}

};


void func()
{
	Myexception mex; //BURASI DEĞİŞTİRİLDİ
	throw mex; // BURASI DEĞİŞTİRİLDİ
}

int main()
{
	try {
		func();
	}
	catch (Myexception&)
	{
		std::cout << "Hata yakalandi\n";
		getchar();
	}
}

ÇIKTI
-----
default ctor -> Nesne yaratıldı
Copy Constructor -> throw ifadesinde nesne kopyalanırdı ve kopyalanan nesne gönderilirdi.Bu sebeple copy ctor çağrıldı
Destructor -> bu destructor yerel mex nesnesi için
Hata yakalandi


-----------------------------------------------------------------------------------------------

Son değişiklik
üstteki kodları yazmadım

int main()
{
	try {
		func();
	}
	catch (Myexception) //burası değiştirildi. burada da copy elision oluyor.
	{
		std::cout << "Hata yakalandi\n";
		getchar();
	}
}

ÇIKTI
-----
default ctor
Copy Constructor
Destructor
Hata yakalandi




MOLA

==========================================================================================================================================
==========================================================================================================================================
==========================================================================================================================================

Standart kütüphane hangi durumda hangi functionun hangi sınıf türünden exception gönderdiğini dökümante ediyor.
exceptions kısmında yazıyor.

ÖR:
vector sınıfının at funcında
!(index < size) bu durum varsa std::out_of_range türünden exception throw ediyor.

mesela [] için Notes kısmında geçersiz index oluşunca UNDEFINED BEHAVIOR oluşuyor diyor

Standart kütüphanenin bir exception hiyerarşisi var.Zamanla öğreneceğiz.Bir resim var.Bunu proje dosyasına koyuyorum.
TÜm hata sınıflarının exception sınıfından kalıtımla elde edildiğini gösteriyor.
Resimdeki mavi yazılar bu sınıfların hangi başlık dosyasında tanımlı olduklarını yazıyor.	EXCEPTION.PNG
Bazıları stdexcept header file da tanımlanmış. Normalde exception header file da idi.

Bazı işlemlerde standart ibrary nin operatör seviyesindeki işlemlerden gönderdiği hata nesneleri var.Bunların
hepsi exception sınıfından kalıtım yoluyla elde edilmiş.	EXCEPTION2.PNG

==============================================================================================================
==============================================================================================================

class Myclass{
public:
	unsignec char x[1024];
};

using namespace std;
int main()
{
	vector<Myclass *>myvec;
	for(;;)
	{
		myvec.push_back(new Myclass);
	}
}

ile infinite loop a girmiş.

Burada bir süre sonra yer elde edemeyecek ve bad_alloc sınıfı türünden
hata nesnesi gönderecek, bizde bunu yakalamadığımız için uncought exception
durumu oluşacak, terminate functionu çağrılacak ve o da abortu çağıracak ve
program sonlanacak.

-----------------------------------------------------------------------------------


Burada bir try bloğu içine alsaydık ve try bloğu içinde bunu izleyen catch bloğu 
oluştursaydım ve orada da bad_alloc türünden gönderilen hataları yakalayacak
bir catch bloğu olsaydı, programın akışı bu hata durumunda bu catch e yönlenecekti.


class Myclass{
public:
	unsignec char x[1024*1024];
};

using namespace std;
int main()
{
	vector<Myclass *>myvec;
	try{
		for(;;)
		{
			myvec.push_back(new Myclass);
		std::cout << ".";
		}
	}
	catch(std::bad_alloc &ex)
	{
		std::cout << "\nhata yakalandı : "<< ex.what() << "\n"
	}
}



-----------------------------------------------------------------------------------


Normalde hata ne ise catch bloğu onu yakalar ama
Burada kullanılan catch ifadesinde bad_alloc yerine exception kullansaydık dynamic türden ötürü
bir upcasting olacaktı ve yine çalışacaktı. 



class Myclass{
public:
	unsignec char x[1024*1024];
};

using namespace std;
int main()
{
	vector<Myclass *>myvec;
	try{
		for(;;)
		{
			myvec.push_back(new Myclass);
		std::cout << ".";
		}
	}
	catch(std::exception &ex)
	{
		std::cout << "\nhata yakalandı : "<< ex.what() << "\n"
	}
}

Yine çalışır

resimdeki Hiyerarşik ilişkiye bakıldı yine.

--------------------------------------------------------------------------------


int main()
{
	try
	{
		std::string s;
		auto c = s.at(12);
	}
	catch(const std::out_of_range &ex)
	{
		std::cout << "exception cought : "<< ex.what() <<"\n";	
	}
}


BURADA OUT OF RANGE YERİNE, LOGİC ERROR YAZILDI VE HATA YİNE YAKALANDI. 
EXCEPTION YAZDIK VE YİNE YAKALADIK.
SEBEBİ LOGİC ERROR,EXCEPTİONDAN KALITIMLA ELDE EDİLMİŞ, 
OUT OF RANGE DE LOGİC ERRORDAN ELDE EDİLMİŞ.BUNLAR TABLODA VAR.



int main()
{
	try
	{
		std::string s;
		auto c = s.at(12);
	}
	catch(const std::logic_error &ex) //exception olsada yine çalışır.
	{
		std::cout << "exception cought : "<< ex.what() <<"\n";	
	}
}

-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------

Kütüphanelerin en sık kullandığı yöntem kendi hata sınıflarını oluşturmak ve hataları
özelleştirmek. Ama doğrudan out_of_range türden hata da throw edebilir. 
Çoğu durumda kullandığımız kütüphaneler, bu kütüphaneye ilişkin bir işlem nedeniyde exception
throw ettiğini vurgulamak için std librari nin exception sınıfından kalıtım yoluyla kendi sınıfını
oluşturuyor.

Mesela date ödevinde bunu yapabilirdik.Mesela logic_error classından kalıtım yoluyla bad_date i elde edebilirdim

#include <stdexcept>

class bad_date : public std::logic_error{

};

-----------------------------------------------------------------------------------------------------------------------

Dİkkat edilmesi gereken nokta
Hiyerarşideki bazı sınıfların default ctoru yok. Dolayısı ile biz onu default ctoru olmayan sadece parameteli ctoru olan
bir sınıftan kalıtım yoluyla bir sınıf elde edersek, onun taban sınıf nesnesini ctor init list ile init etmeliyiz.


#include <stdexcept>

class bad_date : public std::logic_error{
};

int main()
{
	throw bad_date{}; // NEDEN SENTAKS HATASI? Compiler diyorki delete edilmiş func ı çağırmaya çalışıyorsun
}

bad date için default ctor çağrıldı o da tabiki ilk önce taban sınıfın default ctoruna çağrı yaptı.taban sınıfın
default ctoru delete edilmiş, bu durumda türemiş sınıfında default ctoru delete edilecek.Delete edilmiş func a çağrı
sentaks hatası.

---------------------------------------------------------------------------------------------------------------------

Default ctoru kullanmak istersem default ctoru ctor init list kullanarak taban sınıf nesnesini initialize edeceğim.

#include <stdexcept>

class bad_date : public std::logic_error{
public:
	bad_Date() : std::logic_error("Gecersiz tarih\n") {  }  // DİKKAT!
	//bad_Date(const char *p) : std::logic_error(p) {}  bu şekilde de olabilirdi.
};

int main()
{
	throw bad_date{}; // ARTIK GEÇERLİ.
}

---------------------------------------------------------------------------------------------------------------------

INHERITED CTOR KULLANILABİLİRDİ.

class bad_date : public std::logic_error{
public:
	using std::logic_error::logic_error;
};

int main()
{

}

---------------------------------------------------------------------------------------------------------------------

Kaldığımız yerden devam ediyoruz.Hangi olanaklarımız var.

1 - Doğrudan standart kütüphanenin hata türlerinden biriyle throw edebiliriz.
2 - Standart kütüphanenin standart hata türlerinden kalıtım yoluyla elde edilmiş türleri kullanabiliriz.
	Yukarıdaki örnekler böyleydi.
3 - Standart kütüphaneden tamamen ayrık, ilgili frameworkün kendi sınıf hiyerarşisini kullanabiliriz.
	
	ör:
	class CsdException{

	};

	class MathException : public CsdException{

	};

	class DivideByZeroException : public MathException{

	};


---------------------------------------------------------------------------------------------------------------------

Aşağıdaki duruma dikkat!!

int main()
{
	try
	{
	
	}
	catch(const std::exception &ex)
	{

	}	
	catch(const std::logic_error &ex) // Buradaki yanlışlık, Derleyici hiçbir zaman buraya girmeyecek.Bu exceptionu zaten
	{									// bir üst catch bloğunda yakalar.
		
	}

}

Derleyiciler burada warningde verebilir.
Bubrası Özelden genele olmalı genelden özele değil.

---------------------------------------------------

Olması gereken aşağıda

int main()
{
	try
	{

	}
	catch(const std::out_of_range &ex) 
	{									

	}
	catch(const std::logic_error &ex) 
	{									

	}
	catch(const std::exception &ex)
	{

	}

}



----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------

NECATİ HATAYI YAKALADIM NE YAPAYIM ??? :D:D:D:D:D

1 - Gereksiz yere hata yakalamak.Zaten ne yapacağını bilmiyorsan yakalama onu.
2 -	İf ile try catch farkını anlamıyor birde insanlar.


HATA YAKALANDIĞINDA TİPİK SENARYOLAR 
------------------------------------
Basic Guarante
--------------
Program çalışmaya devam eder.Bu devam etme şu koşullarda olmalı.
 - Programın durumu değişebilir
 - Program tutarlı bir durumda kalacak
 - Hiçbir kaynak sızıntısı olmayacak
 - Hayatı devam eden nesneler geçersiz/invalid bir duruma gelmeyecek.	

Bu garantiye basic guarantee deniyor.Bir exception gönderildi ama bizim func ımızın çalışması kaynak sızıntısı oluşturmayacak 
ve herhangibir invalid meydana getirmeyecek.Buna deniyor.

Bu duruma exeption safe deniyor. Bir programın exception safe olması nedir?.
 - Program çalışırken hata gönderilme ihtimali olan tüm nesneleri yakalayacak. Uncought exception olmayacak.Tüm hataları yakalayacak
 - Herhangibir function bir exception gönderdiğinde yani bir throw işlemi yaptığında hiçbir kaynak sızıntısı olmayacak
   ve hayatı devam eden nesneler invalid hale gelmeyecek.

Bu garantiye basic guarante deniyor.

cppreference de exception safety kısmında ne tip bir garanti olduğu yazıyor. Mesela exception verdiğinde memory leak oluştu
bu kabul edilebilir değil. Ne STD lbirary de ne de third partide 

Minimal guarantee is Basic.
Basic guarantee nin bir üstü strong guarantee.

Nesnelerin değeri yani vectörün değeri değişmiş durumda olabilir ama geçersiz olmamalı.

Strong Guarantee
---------------
Fonksiyon expception throw ederse, func çağrılmadan önceki state ne ise o durum sağlanacak. Bu garanti zaten basic garantinin
verdiklerini verip bir de üstüne programın state ini koruma garantisi veriyor.
STD librarynin bir çok func ı strong guarantee veriyor.

Buradaki garantiye commit or rollback te deniyor aynı zamanda.

Bundan ya iş yapılmış halde çıkılacak yada exception oluşursa, bu func
çağrılmadan önceki nesnenin state i ne ise ona dönülür.

 - Programın durumu değişemez
 - Commit or rollback yani ya işini yapacak ya da eski state e geri dönecek
 - Program tutarlı bir durumda kalacak 
 
 Strong, Basic ten daha maliyetli.


Nothrow Guarantee
----------------
En güçlü garanti. Benim çalışmam sırasında exception throw edilmeyecek diyor. Buna güvenip compiler optimizasyonda yapıyor.
cppreference tan bakılabilir.

Şimdi func yazarken baştan belirlenmiş exception garatiside var.

 - Fonksiyon işini yapma garantisi veriyor.
 - Hata gönderilirse kendisi yakalayıp işini yapacak.


Burada kullanılan terimler
emit = Exceptionun dışarı sızması anlamında
propagate = Çağıran fonksiyondan dışarı çıkması demek.


---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------

Diğer Seçenekler
----------------

Bir başka seçenek hata gerçekleştiğinde programın çalışması mümkün olmayabilir. loglama yapıldı mesajlar atıldı ...
Programı terminate edebiliriz.

---------------------------------------------------------------------------------------------------------------------------------------

Diğer seçenek te Exceptionun translate edilmesi deniyor. Hatayı yakaladık kısmi müdahalede bulunduk fakat bizde exception gönderdik
Mesela bad_alloc türünden hata yakaladık gerekei yaptık ve bizde bad_databaseaccess gibi bir hata gönderebiliriz.Daha düğşük seviyeden
daha yüksek seviyede hata gönderebiliriz.

---------------------------------------------------------------------------------------------------------------------------------------

Hatayı Rethrow etmek
Yukarıdakinden farkı aynı nesne tekrar gönderiliyor. Yukarıdaki örnekte düşük seviyeden yüksek seviyeye hata gönderiyorduk.
Burada aynı hatayı geri gönderiyoruz. Rethrow bambaşka bir yapı. Bir kopya çıkarma gibi durum yok.İleride görülecek.
Sentaks
throw;

expr kısmı yok sentaxında.


Ör: f3 teki hata nerede yakalanabilir?

void f3()
{
	throw std::runtime_error{"Hata hata hata\n"};
}

void f2()
{
	f3();
}

void f1()
{
	f2();
}

int main()
{
	f1();
}


Cevap : f3 te f2 de f1 de ve mainde yani heryerde yakalanabilir.
f3 aşağıdaki gibi tanımlanırsa hata f3 te yakalanır.
void f3() 
{
	try
	{
		throw std::runtime_error{"Hata hata hata\n"};
	}
	catch(const std::exception &ex)
	{
		std::cout << "Hata f3 icinde yakalandi : " << ex.what()<< "\n";
	}
}

------------------------------------------------------------------------------------------------------------------

Bu try bloğu f2 de aynı zamanda f2 de olabilir. O zaman hata f2 içinde yakalanır.
Hatta şimdi f3 teki catch ona ait try dan gelen hatayı yakalayamasın. f2 yakalasın.
bunu yazalım


void f3()
{
	try
	{
		throw std::runtime_error{"Hata hata hata\n"};
	}
	catch(const std::logic_error &ex) // bu catch yakalayamasın diye hata sınıfı  değiştirildi.
	{
		std::cout << "Hata f3 icinde yakalandi : " << ex.what()<< "\n";
	}
}

void f2()
{
	try
	{
		f3();
	}
	catch(const std::exception &ex) // f3 teki catch yakalayamayacak ama buradaki exception hata sınıfı yakalayacak.
	{
		std::cout << "Hata f2 icinde yakalandi : " << ex.what()<< "\n";
	}
}

void f1()
{
	f2();
}

int main()
{
	f1();
}

------------------------------------------------------------------------------------------------------------------

Hatta f1 e de blok ekleyelim.

void f3()
{
	try
	{
		throw std::runtime_error{"Hata hata hata\n"};
	}
	catch(const std::logic_error &ex) // bu catch yakalayamasın diye hata sınıfı  değiştirildi.
	{
		std::cout << "Hata f3 icinde yakalandi : " << ex.what()<< "\n";
	}
}

void f2()
{
	try
	{
		f3();
	}
	catch(const std::bad_alloc &ex) // BU sefer buradakide bad_alloc sınıfı türüne çevrildi.Burada yakalanamayacak artık
	{
		std::cout << "Hata f2 icinde yakalandi : " << ex.what()<< "\n";
	}
}

void f1()
{
	try
	{
		f2();
	}
	catch(const std::exception &ex) // f3 ve f2 deki catch yakalayamayacak ama buradaki exception hata sınıfı yakalayacak.
	{
		std::cout << "Hata f1 icinde yakalandi : " << ex.what()<< "\n";
	}
}

int main()
{
	f1();
}

----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------

Rethrow Statement a geri dönelim.
throw; böyle bir statement. Bu durumda yakalanan hata nesnesinin kendisi yine throw ediliyor.Dinamik tür korunuyor.

void f3()
{
	try
	{
		throw std::out_of_range{"Hata hata hata\n"};
	}
	catch(const std::exception &ex) // 
	{
		throw ex; // bu exception throw değil. Bu yeniden throw etme işlemi yapıyor. tabi bunun bir copyası çıkarılıyor.
					// ve burada dinamik tür korunmayacak.Buradan gönderilen hatayı artık out of range türden referansla
					// yakalayamayız.Örnekle gösterilecek.

		throw;	// Burada try dan gönderilen hata nesnesi catch te yakalanacak.Aynı nesne, yeni bir hata nesnesi oluşturulmadan
	}			// f3 ten yukarı göndemiş olduk. Özellikle polimorfik hata nesneleri sözkonusu olunca hatanın türü korunmuş oldu.
				// virtual dispatch aktif halde yani.	
}


----------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------

Catch All bloğu
---------------
Standart catch
catch(T &x)
{

}
Hatanın türü T olmalı, Buna is a ilişkisi dahil.Yani dinamik tür.Upcasting

Öyle bir catch bloğu varki özel sentaksa sahip, catch yerine ... (ellipsis) kullanılıyor.
Bu şekilde oluşturulan catch bloğuna catch all deniyor.Türü ne olursa olsun

Catch all.Hertürlü hata nesnesini yakalıyor.
catch(...)
{

}
Burada yakalanan hatanın türünü bilme şansımız yok.Aşağıdakini oluşturursak şundan emin oluruz.Demekki gönderilen hata nesnesi exception
sınıfı türünden değil.

catch(std::out_of_range&)
{
}
catch(std::exception&)
{
}
catch(...) //Buraya girerse demekki standart library nin hata türünden değilde başka bir exception throw edilmiş.
{
	//...
}

----------------------------------------------------------------------------------------------------------------------------------------
ÖR

using namespace std;
void func()
{
	throw out_of_range{"aralik disi deger\n"};
}

int main()
{
	try
	{
		func();
	}
	catch(const out_of_range &ex) //burası logic_error veya exception olsaydı yine hata yakalanırdı.
	{
		std::cout << "hata yakalandı..." << ex.what() << "\n";
	}

}

----------------------------------------------------------------------------------------------------------------------------------------

Örneği genişletiyoruz.

class Myex{};

void func()
{
	throw Myex{};
}

int main()
{
	try
	{
		func();
	}
	catch(const out_of_range &ex) // Burada Aşağıdaki catch bloğu olmasaydı uncought exception olurdu.hata yakalanamazdı ve terminate edilirdi.
	{
		std::cout << "hata yakalandı..." << ex.what() << "\n";
	}
	catch(...) // Burada bu hatayı bu catch bloğu yakalar.
	{
		std::cout << "hata yakalandı bilinmeyen hata" << "\n";
	}
}

----------------------------------------------------------------------------------------------------------------------------------------

SORU: Aşağıdaki durumda gönderilen tüm hata nesnelerini yakalamış olma garantim var mı?
CEVAP: HAYIR

int main()
{
	try
	{
		// all code in main
	}
	catch(...)
	{
		
	}
}

Çünkü global değişkenler olabilir.Global değişkenler veya sınıfların static veri elemanı olan değişkenler hayata main çağrılmadan önce geliyor.
Bizim uygulamamızda static ömürlü global değişken veya bir sınıfın static veri elemanı varsa bunların ctorları mainden önce çalıştırılıyor.
Dolayısı ile o kod bu try bloğu içinde değil.Dolayısı ile onların ctorları exception gönderirse yakalama şansımız yok.

Embedded tarafta kullanılıyor bu. Bİlipte kullanmak lazım.

MOLA

==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================
==================================================================================================================================================

rethrow exceptiondan bir örneğe bakalım


void func()
{
	try
	{
		throw std::out_of_range{"Hata hata hata\n"};
	}
	catch(const std::exception &ex) //
	{
		std::cout << "hata func icinde yakalandı : " << ex.what() << "\n";
		
		//throw ex; // Bu rethrow statement değil.Böyle yaparsak derleyici yeni bir hata nesnesi oluşturacak ve dynamic type kaybedilecek.
					// artık burada oluşturulacak yeni hata nesnesi türü out_of_range değil yani artık exception.çalıştırılınca maindeki
					// exception türü olan catch yakalar.

		//throw;	//Burası ise rethrow statement.Dinamik tür korunur burada. Gönderilen hata nesnesinin kendisi tekrar gönderilir.
					// main içerisindeki out_of_Range parametreli catch bloğu yakalar.			
	}
}

int main()
{
	try
	{
		func();
	}
	catch(const std::out_of_range&)
	{
		std::cout <<"Hata yakalandı (const std::out_of_range&)\n";
	}
	catch(const std::exception&)
	{
		std::cout <<"Hata yakalandı (const std::exception&)\n";
	}

}


----------------------------------------------------------------------------------------------------------------------------------------

NOT:
1 - Bazı kodlarda idiyomatik olarak exception dispatcher denen bir yapı kullanılacak.Bu şimdi anlatılmayacak.Önemli C++ idiyomlarından biri
2 - Bir throw statement ın catch bloğu içinde olması gerekmiyor.

rethrow statement herhangibir func içinde de olabilir.Burada throw edilen hata func içindeki out_of_range hatası aslında.
bu şekilde catch dışında başka bir functa da yazılabilir.Maindeki try bloğunu izleyen out_of_range poarametreli catch bloğuna girecek.

void foo()
{
	std::cout << "foo cagrildi foo hatayi rethrow ediyor\n";
	throw;
}

void func()
{
	try
	{
		throw std::out_of_range{ "Hata hata hata\n" };
	}
	catch (const std::exception& ex) //
	{
		std::cout << "hata func icinde yakalandi : " << ex.what() << "\n";
		std::cout << "foo functionu cagriliyor\n";
		
		foo();
	}
}

int main()
{
	try
	{
		func();
	}
	catch (const std::out_of_range&)
	{
		std::cout << "Hata yakalandi (const std::out_of_range&)\n";
	}
	catch (const std::exception&)
	{
		std::cout << "Hata yakalandi (const std::exception&)\n";
	}
}

----------------------------------------------------------------------------------------------------------------------------------------

AMA !!!!!!!!!!!!!!!!!
burada herhangibir hata yakalanmamışken doğrudan main içerisinden foo() çağrılırsa ne olur.
int main()
{
	foo(); // yakalanmış bir hata yok ama rethrow statement var. Runtime da yine terminate functionu çağrılacak.
}

	
TERMİNATE İN ÇAĞRILDIĞI HER DURUMU BİLMEMİZ GEREKiR
---------------------------------------------------
1. Uncought Exception.Bir kod gönderiliyor fakat onu yakalayacak try catch blokları yok.
2. Eğer yakalanmış bir hata nesnesi yokken rethrow statement yürütülütse doğrudan terminate func çağrılır.

Konu bitene kadar sayı artacak


=========================================================================================================================================


Exception Dispatcher Idiyom
---------------------------
Ortak kodu biryere toplamak ile alakalı.

class ErrA{
};
class ErrB{
};
class ErrC{
};

void handle_exception()
{
	try
	{
		throw; // rethrow	
	}
	catch(ErrA &ex)
	{
	}
	catch(ErrB &ex)
	{
	}
	catch(ErrC &ex)
	{
	}
}

void func()
{
	try{
		//hata	
	}
	catch(...)
	{
		handle_exception();
	}
}

Burada oluşan tüm hataları ellipsis ile yakalamışız.Handle exceptiondan bu hata rethrow edilmiş ve tanımlanan 3 hata
sınıfı türünden biriyse yakalanacak, bunlardan biri değilse, burada rethrow edilen hata daha yüksek katmanlarda yakalanabilecek.

===========================================================================================================================================
===========================================================================================================================================

Throw yukarıdaki kodlara iletiliyorda kalmıştık.

throw out_of_Range{"..."};  

Hata gönderildiğinde 2 ayrı hata bildirme mekanizması var.Çok önemli!!!

1 - Ana hata bilgisi, gönderilen hata nesnesinin türü,.
	Buna what lada erişebiliriz.

2 - Sınıf türden nesne ise birde o sınıfın değeri var
	class FileReadError : public FileError{
		//..
	public:
		const char *get_file_name()const; // bu bir dosyadak okumaya çalışırken hata oluşmuş, bu bilgiyi bize verebilir.
		size_t get_line_no()const;	// hatanın okumanın hatngi satırından yapınca gerçekleştiğini söylüyor.
	};

	Bazı durumlarda hata türü yeterli olacakken, bazılarında daha spesifik bilgiyi bunu çağıran koda iletebileceğiz.Yani
	daha komplex hata sınıfı tanımlayabiliriz.


-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

RAII
----

Bu idiyomun en önemli olduğu yer belkide exception handling.
Bir function kodu çalışırken eğer bir exception throw ederse programın akışı buradan çıkacak.
Programın akışı buradan çıktığında buraya kadar oluşturulmuş çok sayıda otomatik ömürlü nesne olabilir.

class Myclass {
public:
	Myclass()
	{
		std::cout << this <<" adresinde nesne oluştu\n";
	}
	~Myclass()
	{
		std::cout << this <<" adresindeki nesne icin destructor cagrildi\n";
	}
};

void f4()
{
	Myclass x, y;
	throw 1;
}

void f3()
{
	Myclass x;
	f4();
}

void f2()
{
	Myclass a;
	f3();
}

void f1()
{
	Myclass a;
	f2();
}

int main()
{
	f1();	
}

Otomatik ömürlü nesneler bulunduğu scope tan çıkılınca hayatıda sona eren varlıklar. Burada ise bulundupu scopetan
çıkılmadan exception throw edilmiş.Hatta yakalanmazsa terminate çağrılır.scope sonuna gelmeden oluyor bunlar.

1 - Eğer uncought exception oluşmuşsa o exceptionun gönderildiği yere kadar ouşturulmul otomatk ömürlü sınıf nesneleri için desturctor 
çağrılma garantisi yok. Derleyici belki üretebilir ama hiçbir derleyicide bunu yapmıyor. Buradaki dert programın sonlanması değil,
sonalndı ama belki birsürü otomatik ömürlü sınıf nesnesi için destructor çağrılmadı. Ya bunların destructorlarının çağrılmaması kalıcı
hasar bırakıyorsa yine büyük sıkıntı.

2 - Eğer exception yakalandıysa, bunun otomatik ömürlü nesneler üzeirnde bir etkisi varmı? KESİNLİKLE VAR.
	Hata yakalamanın sağladığı en önemli garanti STACK UNWINDING  denilen süreç.

	STACK UNWINDING = STACKTE SONDAN BAŞA BAŞLAYARAK OLUŞTURULMUŞ TÜM OTOMATIK ÖMÜRLÜ NESNELER IÇIN DESTRUCTOR ÇAĞRILACAK.
	YUKARIDAKI KODA BAKALIM.MAIN KISMI AŞAĞIDAKI GIBI OLURSA.DILIN KURALLARI DIYORKI TEKTEK SONDAN BAŞA OLUŞTURULMUŞ TÜM
	OTOMATIK ÖMÜRLÜ NESNELER IÇIN DESTRUCTOR ÇAĞRILACAK. Y VE X IÇIN DTOR ÇAĞRILDI, BIR ÜSTTEKI STACK FRAME DE X, BIR ÜSTTEKINDE
	A IÇIN SONRA DIĞER A IÇIN VE ONDAN SONRA PROGRAMIN AKIŞI CATCH BLOĞUNA GIRDI.BU GARANTI ALTINDA.


	
class Myclass {
public:
	Myclass()
	{
		std::cout << this << " adresinde nesne oluştu\n";
	}
	~Myclass()
	{
		std::cout << this << " adresindeki nesne icin destructor cagrildi\n";
	}
};

void f4()
{
	Myclass x, y;
	throw 1;
}

void f3()
{
	Myclass x;
	f4();
}

void f2()
{
	Myclass a;
	f3();
}

void f1()
{
	Myclass a;
	f2();
}

int main()
{	
	try
	{
		f1();
	}
	catch(int x)
	{
		std::cout << "hata yakalandi x = " << x << "\n";
	}
}

ÇIKTI
-----
009EF9C3 adresinde nesne olu?tu
009EF8CF adresinde nesne olu?tu
009EF7DB adresinde nesne olu?tu
009EF6E7 adresinde nesne olu?tu
009EF6DB adresinde nesne olu?tu
009EF6DB adresindeki nesne icin destructor cagrildi
009EF6E7 adresindeki nesne icin destructor cagrildi
009EF7DB adresindeki nesne icin destructor cagrildi
009EF8CF adresindeki nesne icin destructor cagrildi
009EF9C3 adresindeki nesne icin destructor cagrildi
hata yakalandi x = 1

----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------
BURADAKI KILIT NOKTA, HATA YAKALANDIĞINDA OTOMATİK ÖMÜRLÜ NESNELER DAHA PROGRAMIN AKIŞI CATCH BLOĞUNA GİRMEDEN BİRER BİRER DESTRUCT EDİLECEKLER. !!!!!!!!!
----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------

EĞER HAYALANMAZSA AŞAĞIDAKİ KOD İLE
int main()
{
	try
	{
		f1();
	}
	catch(double x) // double yaptık.
	{
		std::cout << "hata yakalandi x = " << x << "\n";
	}
}

Destructorlar çağrılmadı çünkü hata yakalanmadı.Termiante.

ÇIKTI
-----
003EFA97 adresinde nesne olu?tu
003EF9A3 adresinde nesne olu?tu
003EF8AF adresinde nesne olu?tu
003EF7BB adresinde nesne olu?tu
003EF7AF adresinde nesne olu?tu


----------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------

int foo()
{
	FILE *f = fopen("aliveli.txt","w");

	bar(); //exception throw etti diyelim.

	fclose(f);
}

Burada fclose(f); a gitmeyecek kod. bar dan exception gönderilirse bile, açılan dosya kapatılmayacak, hata yakalansada kapatılmayacak.
Çünkü bu bir sınıf nesnesi değil. Destructor çağrılamaz.

Aşağıdaki gibi sınıf olsaydı.Ctroru dosya açıyor, dtoruda dosya kapatıyor.

class File{
public:
	File(const char*p);
	~File();
};

void foo()
{
	File myfile("aliveli.txt");
	//.. kodlar
	//.. kodlar 

}


1 - Bu durumda kodlar exception throw etmiyorsa en son blok sonuna gelir ve dtor çağrılır.
2 - Bu durumda ise burada çalışan kodlardan biri exception throw edecek.Programın akışı buradan çıkacak exceptionun yakalaındığı yerdeki catch bloğuna girecek
	ama oraya girmeden stack unwinding süreci, otomotik mürlü nesneler için dtor çağrılacak yani, myfile ın destructoru çağrılacak.Dtorda dosyayı kapatacak.

RAII idiyomunun en fazla fayda sağladığı yer exception handling.

*/


#include <iostream>
#include <exception>
#include <string>


class Myclass {
public:
	Myclass()
	{
		std::cout << this << " adresinde nesne oluştu\n";
	}
	~Myclass()
	{
		std::cout << this << " adresindeki nesne icin destructor cagrildi\n";
	}
};

void f4()
{
	Myclass x, y;
	throw 1;
}

void f3()
{
	Myclass x;
	f4();
}

void f2()
{
	Myclass a;
	f3();
}

void f1()
{
	Myclass a;
	f2();
}

int main()
{
	try
	{
		f1();
	}
	catch (double x)
	{
		std::cout << "hata yakalandi x = " << x << "\n";
	}
}
