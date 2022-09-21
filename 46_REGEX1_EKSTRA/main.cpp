/*

REGEX
-----
Regular Expression
Nedir neden ihtiyaç duyulur veya notasyonlar nelerdir...
Bunları ilk öğrenmemiz gerekir.

C++ ın standart regexi librarysi regexi yapma şansı tanır.
Karmaşık bir library, zaten regexin kendiside karmaşık.

Yazılarla ilgili işlemler çok sık ihtiyaç duyduğumuz işlemler.
Programlama dilleri yazılarla ilgili işlemlerle ilgili destek sağlıyorlar.
string library gibi.Yazılarla ilgili öyle işlemler varki çok daha karmaşık.
Özel algoritmaların kullanımlasını gerektiriyor.
Bunun için programlama dilleri regex library sunuyorlar.

BU öyle bir yazıki belirli bir formatta, bir yazının uyması gereken 
kuraları anlatıyor.Bunu yine bir yazıyla ifade ediyoruz.

Mesela bir posta kodu kuralı.
Bir eposta adresinin geçerliliğini gösteren bir regex ifadesi.
Bu regex ile bir kuralı betimliyoruz. BUna regex stringi diyebiliriz.

Regex stringini alarak bizim için faydalı işlemler yapan kodlara
regex engine deniyor. Asıl işi yapan regex engine.

-----------------------------------------------------------------------------------------------------------------------------

Regex engine,
1 - Validation yapıyor.
Elimizde bir yazı var, bu yazının bir kurala uygun olup olmadığını
yani geçerliliğini sınıyor.

2 - Search yapıyor.
Bir yazıda bir eposta arıyoruz diyelim. Bunu doğrudan yapamayız.
Kendimiz yazsak kodunu hem zaman harcar hemde test etmek zor.
Belirli paterne uyan yazı yada yazıları arıyoruz. Burada da 
regex engine devreye giriyor.

3 - Tokenizing yapıyor.
C de strtok ile bir yazıyı tokenlarına ayırabiliriz.
Bazı durumlarda bu tokenizing çok karmaşık olabilir. Bunu normal string
funclarıyla yapmak çok zor olabilir. Burada yine regex motoru bu imkanı verir.


4 - Replacement yapıyor
Elimizde bir yazı var, bu yazının içinde belirli paterne uyan kısımları
belirli bir şekilde başka yazılarla yer değiştireceğiz.

Mesela eposta adreslerini bulup buradakileri yahoo olarak değiştirmek.
Burda da epostalar geçerli adresler olacak tabi.

-----------------------------------------------------------------------------------------------------------------------------

Regexin maliyeti çok yüksek.
Normal string funclarıyla yapılabilecek işler için regexi kullanma.
Regex çok çok daha maliyetli.

Text editörleride regex desteği veriyor.Profesyonel ide ler mesela böyle.

Regex stringinin nasıl oluşturulacağını söyleyen kuralların tümüne regex grammer deniyor.
Farklı farklı regex grammerleri var çünkü farklı farklı regex motorları var.
Bu problemli. bir regex motorundan diğerine göre oluşturulan regex stringinin anlamı farklı olabilir.
Burada çok kaygılanmamak lazım çünkü %70-80 lik kısmı ortak.

Temel notasyonlardan birini öğrenirsek diğerlerinide aşağı yukarı 
kullanabiliriz yada alışabiliriz.

regex flavor
a - Kullandığımız regex flavora göre oluştrmamız gereken stringde
birtakım değişikler gerekebilir.

b - Bazı işlemler için destek sunulmayabilir.

-----------------------------------------------------------------------------------------------------------------------------

C std libraryde regex yok.
C++ 2011 de regex standart hale geldi.
Regex eklenmeden önce boost un regex modülü kullanılıyordu.
Halen boost regex kullanan var ama başka bir sebep sözkonusu değilse
regex işlemlerini C++ta standart library ile yapmak gerekiyor.

https://regex101.com/
TÜm örnekleri buradan test ettik.
Bu çok iyi bir site. regex stringi oluşturup validate ve search işlemleri
yapılabiliyor. 

Aynı zamanda explanation kısmında açıklamasıda var.

Birde regex özelliklerini anlatan bir referans kısmı var.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

REGEX NOTASYONU
---------------
Karakterler kendini temsil ediyor.
Ali yazarsam, bu şu demek validasyon işleminde yazı Ali ise geçerliliğini
kabul edecek engine.

Metakarakterler var ve bunların ayrı anlamları var.
Bunlar özel anlamları ifade ediyor.

Nokta(.)
--------
Bu newline dışındaki herhangibir karakter olabilir demek.
.al --> regex stringi yazsak
buna kal, mal, sal, tal, val hepsi buna uyacak.

-----------------------------------------------------------------------------------------------------------------------------

NOT!!!!!!!

Metakarakterler bazı karaketere özel anlam yükleyince başka bir problem oluyor.
mesela nokta karakterini aramak istersek ??

.xyz --> axyz, bxyz hepsi geçerli oldu ama ben gerçekten .xyz yi istiyorum :D

Burada bir yol gerekli
\.xyz --> bu şekilde yazarsak sadece .xyz geçerli olur.

Aşağıdaki meta karakterler \ ile belirtilmeli 
. ( ) [ ] { }  
Bu escape edilmesi gereken metakarakterlerin ne olduğu engineden enginee göre değişir.

ör:
a\{3\} -> şimdi a{3} geçerli.  

https://regex101.com/

-----------------------------------------------------------------------------------------------------------------------------

Köşeli Parantez []
------------------
Köşeli parantez içine birden fazla karakter yazarsak, bunlardan
herhangibir tanesi doğru demek.

[akm]u --> au, ku, mu  
hepsi valid.

[aei]ms --> ems, ams, ims 
yine valid hepsi.

-----------------------------------------------------------------------------------------------------------------------------

Caret ^
-------

[^aer] --> Bu karakterlerden biri olmayan demek
yani a, e ve r olmayacak ama başka karakter olabilir anlamında.

[^aer] --> tms, xms, yms hepsi valid
			ems valid değil ama.Çünkü e karakteri aer den biri.

-----------------------------------------------------------------------------------------------------------------------------

hyphen -
--------
Aralık belirtmek için var.

[b-f]a -> ba,ca,da,ea,fa   hepsi valid.
		  ga valid değil.

BU aralıkta olmayan
[^b-f]a -> aa valid 
		   ama bf valid değil

Dikkat boşluk verirsek başa burada boşlukta var demek
[ a-d] -> burada boşlukta var

İlki rakam ikincisi küçük harf üçüncüsü yine rakam
[0-9][a-z][0-9] --> 2b6, 4y8, 8t5 valid ama 
					2B6 da B büyük o yüzden valid değil
					aa5 bu da valid değil


Köşeli parantez içine biren fazla aralıkta yazılabilir.
[0-9][a-zA-Z][0-9] --> Şimdi büyük harfleride aldık aralığa
					   0A4 te 0a4 te valid.

[0-9][m-py][0-9]  --> m den p ye kadar olan karakterler ayrıca y de dahil

https://regex101.com/

-----------------------------------------------------------------------------------------------------------------------------

[[:alpha:]] --> alfa herhangibir karakter olabilir
[[:punct:]] --> punct karakterlerden herhangbiri olabilir.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

\ ile başlayan bazı karakterler özel anlamlara geliyor.

\d --> digit karakter demek yani [0-9] ile aynı anlamda. İki türlüde olur
\D --> rakam karakteri olmayacak demek. Buda [^0-9] ile aynı

\s --> space karakterlerden herhangibiri demek.
\S --> boşluk karakteri olmayan karakter demek.

\w --> word karakter demek.alphanumeric characters ve underscore(_) demek
\W --> Word yani alphanumeric ve underscore(_) olmayan karakter demek

ör:
\d\d\s\d --> 34 5  valid
\w;  --> ali;  valid

https://regex101.com/

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

QUANTIFIER METACHARACTER
------------------------
Bunların hepsinde önlerinde bir grup olmak zorunda
Quantifier sayısal niteleyici anlamında.

-----------------------------------------------------------------------------------------------------------------------------

Asterisk *
----------
Kendisinden önce gelen karakterden 0 yada n tane olabilir demek.
Yani kendisinden öncekini [0-n] aralığında çarpıyor.
x*y demek, y olacak ama x tende 0 ve n aralığında olabilir demek.

ÖR:
a*b -> b, ab,aab,aaaaab hepsi valid.
		b neden geçerli çünkü * ın önünde a var. a dan 0 veya n tane olabilir.
 

NOT !!! 
a\* --> bu a* ı match eder


ÖR:
a*b*k --> k, abk, aabk,aaaaabbbbbbbk, bk, aaaaak  hepsi match

-----------------------------------------------------------------------------------------------------------------------------

Soru İşareti ?
--------------
Kendisinden önce bir grup gelmeli, o grup olabilirde olmayabilirde.

a?b -> ab ve b match oldu.

ör:
x?y?z --> xyz, xz, z hepsi match oldu.

-----------------------------------------------------------------------------------------------------------------------------

Artı +
------
1 yada n tane demek. * 0 yada en tane idi. ? ise ne varsa o geliyor.
Min 1 tane olacak yani

ÖR:
t+m+k --> k match değil
		  tmk, ttttmk, tttttmmmmk match oldu.

-----------------------------------------------------------------------------------------------------------------------------

Küme Parantezi {}
-----------------
KÜme parantezi içerisinde bir sayı olursa o kadar tane demek.

t{3} --> t den 3 tane olacak ttt valid yani.
		 tts valid değil.
		 tttts bir kısmı valid oldu(ttts kısmı) 

Burada virgül olursa belirtilen sayı kadar veya daha fazla demek.
t{3,}s --> ts, tts valid değil.
		   ttts, ttttts tttttttttttts --> bunlar match oldu.

Virgülden sonra bir sayı olursa bu aralıkta olabilir 
t{3,5}a --> ttta,tttta,ttttta hepsi valid. Match eder
			ta valid değil.
			tttttta bununda ttttta kısmı match etti.

-----------------------------------------------------------------------------------------------------------------------------

ÖR:

[a-e]+k --> ak geçerli
			aecdk yine valid. + demek en az 1 tane olacak demek.

[a-k]{2} --> ab, kf, sj hepsi valid. aralıktan 2 tane olacak
			 dm match değil.
			 abc  ab kısmı match

\d{3,}p  --> 342p, 2341p, 354436p  hepsi match
		 --> 34p match değil çünkü 2 rakam charakteri var.

-----------------------------------------------------------------------------------------------------------------------------

Pipe Character |
----------------
Veya operatörü gibi.
Pipe ın önündeki de olabilir sonundakide olabilir.

ali|can --> ali veya can match durumda 

al(i)|(c)an --> Burada  | nin operandaları parantez içindeki ifadeler olacak
				operator önceliğinden ötürü.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

ANCHOR CHARACTERS
-----------------
Belirli bir koşulu sağlaması gerekiyor burada.


Boundary
-----------
Konum olarak bir koşul oluşturuyor.

\b kelime başı olacak demek
ne -> anne, neden, yine, deneme hepsi match ediyor ama

\bne --> burada kelime başı olması gerekiyor.
		  neden ve nereye valid

\B --> kelime başı olmayan demek.
\B --> anne ve yine match oldu

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!!!

Dolar $
-------
$ Satır sonu demek.
^ ise satır başı demek


-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

PARANTEZ
--------
Çok çok kritik parantez.
Regexte parantezin 2 tane ayrı önemi var.

Birincisinde parantez öncelik belirtiyor.
[a-e]{3} --> a-e aralığındaki charlardan 3 tane olacak demek

[a-e]k{3} --> Burada a-e aralığındaki karakterlerden 1 tane sonrada
			  3 tane k olacak operatör önceliğinden ötürü.

([a-e]k){3} -> artık operand parantezin içindeki grup oldu
				ekakbk bu valid. [a-e]k bundan 3 tane yani.

-----------------------------------------------------------------------------------------------------------------------------

Parantez gruplama anlamınada geliyor. Regex bazen sadece match olup olmadığını değil
o regex stringindeki parantez içine alınmış kısmıda bize ayrıca bilgi verecek.

(can)[xyz](ali) --> burada parantez olması ve olmaması arasında bir fark yok.

Ama parantez koyunca validasyon yapınca yine bulacak ama parantez içindeki kısmı ayrıca verecek.
Ör:
(?????)@(????) --> buradan @ ten sonrasını ve öncesini ayrı ayrı elde edebiliriz.

Parantez 
1 - Öncelik kazandırıyor
2 - Parantez içindeki grupla ilgili arama yada validasyon işlemlerinde
	bize kütüphanenin bilgi vermesini sağlıyor.

 Yani
 ali@yahoo.com  --> ali kısmını ayrı ve yahoo kısmını ayrı verebilecek.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

Back-Reference
--------------
Parantezin önemli olduğu başka bir yer burası.
\ den sonra sayı kullanırsak bu back reference sentaksı
\1
\2
\3 gibi

\1 -> birinci grup
\2 -> ikinci grup
\3 -> üçüncü grup demek.

(ak)[0-9]\1 --> birinci parantezin içindekinden yine bir tane daha olmak zorunda demek.
			--> ak4ak olması lazım demek.

([m-t]a[0-9]) --> ma9 match
([m-t]a[0-9])p\1 --> \1 in yerinde parantez içindekinden bir tane daha lazım
				 -->  ma9pma9 matchtir. 

[0-9]{4}a[0-9]{3}  --> 7234a123  match oldu

([0-9]{4})a([0-9]{3}) --> 7234a123 math oldu. 
						  Ayrıca group1 = 7234 ve group2 = 123

Bu sayede gruplar hakkında bilgi ediniyoruz.

-----------------------------------------------------------------------------------------------------------------------------

NON CAPTURING 

Grup olmasını değilde sadece öncelik parantezi olarak kullanmak istiyoruz.
Neden istemiyoruz çünkü grup olmasının maliyeti var bunun için.

Parantezden soru işareti ?: kullanıyoruz.

(?:[0-9]{4})a([0-9]{3}) --> artık ilk parantezi capture etmedik.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

ÖRNEKLER

1.
Hocanın kullandığı if kontrolü.
if(x>y) ; gibi birşey varsa yakalıyor
if ( x>y ) ; bunuda

if\s*\(.*\)\s*;

if olacak space karakterinden 0-n tane olacak,
parantez metakarakter o yüzden \kullandık.
. herhangibir karakter olabilir demek * ise 0-n tane herhangibir char demek.
\) parantez kapat demek.
\s boşluk karakteri demek * ile birleşince 0-n arasında boşluk karakteri var demek.


2.
[ktms][aeo]r[aei][lmnrsyz] --> kerem mesela olabilir.hepsinden sadece 1 tane olacak.


3.
^.*Necati.*$ 

^Satır başı demek .* demek herhangibir karakterden 0-n aralığında olacak demek
Necati olacak
herhangibir karakter olacak ve bundan 0-n aralığında olacak
$ da satır(string sonu) sonu demek  

gel buraya Necati hemen
ahmet Necagti'ye dedi ki  içinde necati geçen bütün satırları buldu.


4. Geçerli tarih

(0[1-9]|[12][0-9]|3[01])([-.\/])(0[1-9]|1[012])\2(19|20)\d\d

0 karakteri gelecek, 1-9 arasından biri sonrasında veya var.
Veyanın solu yada sağı match olacak.
1 veya 2 olacak ve sonrasında 0-9 arasında rakam olacak.yani 10 11 12 13 21 22 23 .. ten biri
veya gelmiş yine solu veya sağı olacak sağında 3 ve 0 veya 1 den biri olacak.(30 yada 31 olacak)
Buraya kadar olan kısım tarihin günü 

0 ve 1 -9 arası olacak veya 1 olacak sonra 0-1-2 den biri olacak
\2 back reference. yani 2. parantez([-.\/]) hangi ayıraç kullanıldıysa \2 yazan
yerde de o ayıraç kullanılacak.
ay'da bitti
DİKKAT!!!!!!!!!!!!
normalde . kullanacaksak \. yazardık ama [] içerisinde . doğrudan kullanılabildi ama
/ kullanmak için \ kullanmak zorunda kaldık


19 veya 20 olacak sonrasında 2 tane rakam karakteri.
d{2} de olabilirdi.

5.12.1998 --> geçersiz
05-1987 --> geçersiz
01.05.1999 --> geçerli


5. Geçerli gerçek sayı

[+-]?[0-9]*\.?[0-9]+  

- + den biri olacak. ? ise önüne gelen grup olabilir yada olmayabilir demek.
0 - 9 arasından 0-n tane kadar olabilir.
\. demek . karakterinin kendisi.
? bundan öncekiler olmayabilirde olabilirde demek
sonra yine 0-9 arasındaki karakterlerden + ile birşelerek 1 yada daha çok oalbilir demek.


6. Hex numbers 

\b0[xX][0-9a-fA-F]+\b
satır başı olacak. 0 olacak.
x veya X olacak.
0 - 9 arasındakilerden biri yada  a - f arasındaki charlardan biri yada
A - F arasındaki charlardan biri.
+ demek bu gruptan 1 - n arasında olacak yani 1 veya daha fazla olacak demek.
\b kelime sonu olacak.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

LOOKAHEAD
---------
Regex stringine uygun sınamayı yapacak bulacak ama bulduğu yerden sonrada özel bir patern daha olması 
gerekiyor.

(?=123) -> buna pozitif lookahead deniyor. ?= den sonraki varlık daha sonra olmak zorunda demek.

ÖR:
123(?=456) --> 123456 Burada 123 bulunacak ama daha sonrasında gelen 456 olmasaydı bunu bulmayacaktı.

NEGATIF LOOKAHEAD
-----------------
Soru işaretinden sonra ünlem konursa bu negatif lookahead.
123(?!456) --> yani aradığım regex stringi diyorki 123 olacak sonrasında 456 olmayacak
			   123456 valid değil
			   123789 Burası valid

Regex enginelerinin bir kısmı lookaheadi desteklemiyor bire kısmı ise destekliyor.


LOOKBEHIND
----------
Buda lookaheadin tam tersi

(?<=123)456 --> Aradığım 456 ama bundan önce 123 te varsa 456 yı bul.


(?<=abc)457  --> abc457 valid. 457 yi buldu
				 dsw457 burası valid değil.


NEGATIF LOOKBEHIND
------------------
(?<!abc)456 --> 456 yı buldu çünkü başında abc olmaması koşulu var.Valid
			    abc456, başında bc oldu ve bu istenmiyor.Valid değil.


-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

GREEDY VE LAZY QUANTIFIERLAR
----------------------------

Bizim quantifierlarımız
a - Greedy olabilir
	Default olarak quantifierlar greedy.
	*, +, ?, {n},{n,},{n,m} bunlar bizim quantifierlarımız.

	Mümkün olan en uzun kombinasyonu seçiyor

b - Lazy olabilir.
	Quantifierlardan sonra ? koyduğumuzda bu ssefer quantifierımız lazy hale geliyor.
	*?, +?, ??, {n}?,{n,}?,{n,m}?

	Mümkün olan en kısa kombinasyonu seçiyor.



ÖRNERKLER:

Greey Örneği
------------
a[ert]+k  --> aertk, aertertk valid durumdalar.
		arttttekk buda valid.	
		+ kendisinden önceki gruptan 1 veya daha fazla sayıda olacak demek.
		burada ert den bir tanesi seçildi. daha sonra r daha sonra t seçildi yani
		1 den fazla kez o gruptan karakter yazılmış. O yüzden valid.

Lazy Örneği
-----------
a[ert]+? --> İlk kurala uyanı bulduğunda bırakacak. 
	     aert yazınca ilk uyan ae olduğundan ae yi match olarak görüyor

Enteresan bir durum daha var!!!!!!!!!!!!
a[ert]+?k --> aertertk yazınca hepsini match gösterdi.

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

RAW STRING LITERAL
------------------
R"(ali)"

int main()
{
	"ali"
	R"(ali)" yukarıdakiyle aşağısı arasında fark yok.
}

Raw string literalinin farklı olduğu yer, "" ve \ karakterlerinin doğrudan yazılabilmesi

mesela string literalinde
\ yazmak için "\\" yazmalıyım

Raw string literalinde
R"(\)" yazabilirim.

Bir özelliğide alt satırdan devam edebiliyoruz.

R"(ali\
	veli
)"

Raw string literallerinin en çok kullanıldığı yerler regex stringleri

\\ yazmak için "\\\\" yazmalıyız mesela :D:D:D

=============================================================================================================================
=============================================================================================================================
=============================================================================================================================
=============================================================================================================================
=============================================================================================================================
	

C++ STANDART LIBRARY
--------------------
Header file regex
regexi kullanınca aslında basic_regexin in bir specializationını kullanıyoruz aslında.

basic_regex<char> için doğrudan regex kullanıyoruz.

int main()
{
	regex rgx; // Bu bizden bir regex stringi istiyor. Arkaplandaki regex motoru
		   // regex sınıfı türünden bu nesnenin temsil ettiği regex stringini kullanacak.
		   // bunu cstring olarak yada std::string olarak ctora argüman olarak geçebiliriz.


	regex rgx("[abc]+123[ef]"); 
}

-----------------------------------------------------------------------------------------------------------------------------

Regex stringinde hata varsa ctor exception throw edecek.

int main()
{
	try{
		regex rgx("[abc]+123[ef]");  // Hata yok. Hata olsaydı yakalanacaktı.
	}
	catch(const std::exception& ex)
	{
		std::cout << "hata yakalandi : " << e.what() << '\n';
	}
}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

Bu regex stringini bazı global functionlara argüman olarak gönderiyorum.
Argüman olarak gönderdiğimde o işi yapan function regex stringi olarak bizim stringimizi kullanıyor.

BU FUNCLAR
regex_match
regex_search
regex_replace

SINIFIN MARK_COUNT ISIMLI BIR FUNCI VAR.
MARK_COUNT CAPTURE GRUPLARIN SAYISINI DÖNDÜRÜYOR.
YANI REGEX STRINGI IÇINDE KAÇ TANE CAPTURE GRUP VAR.

int main()
{
	using namespace std;
	regex r1{"necati"};

	std::cout << "r1 icin alt ifade sayisi : " << r1.mark_count() << '\n'; // burada 0.Capture grup yok.

	//---------------------------------------------------------------------------------

	regex r1{"necati (erg)in"};
	std::cout << "r1 icin alt ifade sayisi : " << r1.mark_count() << '\n'; // Burada 1 tane capture grup var.
										// 1 döndürür.
	//---------------------------------------------------------------------------------

	regex r1{"(necati) (erg)in"};
	std::cout << "r1 icin alt ifade sayisi : " << r1.mark_count() << '\n'; // Burada 2 tane capture grup var.
										// 2 döndürür.

	//---------------------------------------------------------------------------------

	regex r1{"(nec(ati)ergin)"};
	std::cout << "r1 icin alt ifade sayisi : " << r1.mark_count() << '\n'; // Burada yine 2 tane capture grup var.
										// 2 döndürür.

	//---------------------------------------------------------------------------------

	regex r1{"\\(necati)\\"};
	std::cout << "r1 icin alt ifade sayisi : " << r1.mark_count() << '\n'; // 0 verir. Burada aslında \\ yazınca \ gibi evaluate ediliyor
									       // buda parantezleri escape etti. 
									       // Yani parantezler metacharacater değil artık
									       // mark count 0 verir

}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

std namespace içinde regex_constant isimli bir nested namespace var
Buradaki constexpr sabitler regex notasyonunda bazı özellşetirmeler yapmamızı sağlıyor.
Mesela desteklenen başka regex gramerini kullanmak için, regex nesnesini oluştururken
2. parametreye argüman olaran bu namespace teki sabitlerden biri geçilebilir.

int main()
{
	using namespace std;

	regex("abc",regex_constants::egrep); // engine olarak egrep notasyonu kullanılacak
	
	regex("abc"); // engine olarak default notasyon kullanılacak o da ECMAScript.
}



BAZENDE 2. PARAMETREYE GEÇILEN SABIT IŞLEMLERI ÖZELLEŞTIRMEK IÇIN.

int main()
{
	using namespace std;

	regex r1{"n(eca)ti", regex_constants::nosubs}; // Artık parantezlerden hiçbiri capture grup olarak alınmayacak.
}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

REGEX FUNCLAR

Regex nesnesi için regixin ctoruna ya bir string yada cstring geçeriz

int main()
{
	using namespace std;

	string str{"[abc]{3,}x"}; 
	
	regex rgx{str};

}



REGEX_MATCH
-----------
En kolay işlem Validasyon işlemi.regex_match ile yapılıyor.
Bu funcların birden fazla overloadları var. string ve cstring overloadları var.

1. parametreye string/cstring geçilir, 2. ye regex nesnesi geçilir
Regex matchin return değeri bool. Bulursa true bulamazsa false döner.

-----------------------------------------------------------------------------------------------------------------------------
ÖR:

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>


int main()
{
	auto svec = get_dictionary("words.txt"); // burada hcada 460000 kelime var
	std::cout << "toplam cumle sayisi: " << svec.size() << "\n";

	//burada dilediğiniz regex stringini oluşturun: 
	
	//std::string sreg{R"(^co.*ion$)" };  // satır başı olacak, 0-n arasında herhangibir char olabilir ve ion satır sonundan olacak
	//std::string sreg{R"(([aeo]).*\1)" };
	
	std::string sreg{ R"(.*[nst]ec[aeuo].*)" };

	std::regex rgx{sreg}; // Regex nesnesini oluşturduk


	for (const auto &s : svec) {
		if (std::regex_match(s, rgx)) // DİKKAT !!!
			cout << s << "\n";
	}
}

-----------------------------------------------------------------------------------------------------------------------------

ÖR:
int main()
{
	auto svec = get_dictionary("words.txt"); // burada hcada 460000 kelime var
	std::cout << "toplam cumle sayisi: " << svec.size() << "\n";

	std::string sreg{ ".*([trkma]{2,}).*\\1.*" }; // herhangibir chardan 0-n arasında sayıda
												  // sonra trkma dan 2 veya dana fazla sayıda
												  //herhangibir chardan 0 veya daha fazla tane
												  // 1. gruptan 1 tane daha yani ([trkma]{2,}) dan bir tane daha olmalı
												  // herhangibir chardan 0-n tane

	std::regex rgx{sreg}; // Regex nesnesini oluşturduk


	for (const auto &s : svec) {
		if (std::regex_match(s, rgx)) // DİKKAT !!!
			cout << s << "\n";
	}
}

Bİr mail doğrulamak için regex yazıldı.
Hoca internetten bulmuş aşırı aşırı uzun. onu yazmadım.
2:07

-----------------------------------------------------------------------------------------------------------------------------

ÖR:

int main()
{
	regex rgx("\b0[xX][0-9a-fA-F]+\b"); // \b kelime başı demek. ^ ise satır başı demek
										// bu hex formatında sayıları bulur

	string str;

	std::cout << "giris yapin : ";
	std::cin>> str;

	if(regex_match(str,rgx))
	{
		std::cout << "gecerli\n";
	}
	else
	{
		std::cout << "gecersiz\n";
	}	

}

-----------------------------------------------------------------------------------------------------------------------------

ÖR:
bir dosyadakilerin geçerli bir reel sayı olup olmadığına bakıyoruz.

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>

using namespace std;

int main()
{
	regex rgx{"[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"};
	
	ifstream ifs{"floats.txt"};
	if(!ifs)
	{
		cerr << "dosya acilamadi\n";
		return 1;
	}

	string word;
	while(ifs >> word)
	{
		if(regex_match(word,rgx))
		{
			std::cout << word << " gecerli\n";
		}
		else
		{
			std::cout << word << " gecerli\n";
		 }
	}
}

-----------------------------------------------------------------------------------------------------------------------------

ÖR:
#include <regex>
#include "nutility.h"
#include <iostream>


int main()
{
	using namespace std;
	auto svec = get_dictionary("words.txt");
	regex rgx{ ".*([ckprts]+[aeio]+).*([tcln]ion).*" }; // artık açıklamasını yazmıyorum :D

	smatch sm; // Bu görülecek

	for (auto& word : svec) {
		if (regex_match(word, sm, rgx)) // DİKKAT!!! Burasıda görülecek.
		{								

			cout << word << "  ";
			word.insert(sm.position(1), 1, '[');
			word.insert(sm.position(1) + sm.length(1) + 1, 1, ']');
			word.insert(word.begin() + sm.position(2) + 2, '[');
			word.insert(word.begin() + sm.position(2) + 3 + sm.length(2), ']');
			cout << word;
			(void)getchar();
		}
	}
}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

REGEX SEARCH
------------
Bu functionı çağırıp ona bir smatch nesnesi gönderdiğimde, regex search o nesneyi set ediyor ve 
aranan bulunduysa ben bu smatch nesnesini kullanarak submatchlere erişiyorum.
0 indisli submatch bulunan yazının kendisi, capture gruplar varsa 1,2,3 ... indsli elemanlarda
o capture grupları bana submatch olarak veriyor.
Burada amaç verdiğimiz yazının içinde o kurala uygun olan ilk yazıyı bulmak.
regex_match te mesela reel sayı olup olmadığını bulacağız,
regex_search ile yazının içindeki reel sayı varsa onu bulacağız.
Birden fazla varsa ilkini bulacak.

regex_search te boolean döndürüyor.
Bu funcın 2. parametresine referans semantiği ile smatch türünden nesne geçiyorum.

smatch kullandığımda match_results isimli bir sınıf şablonunun itearator açılımını kullanıyorum.

DİKKAT!!!
Eğer regex_search e argüman olarak string geçersek smatch sınıfını
eğer cstring geçersek cmatch sınıfı kullanılacak.
Yapacağımız şey bu sınıf türünden nesne oluşturmak.

smatch bir container aslında ve kendiside submatch türünden nesneleri içeren bir container.
Yani bu containerın herbir elemanı submatch içeren bir sınıf türünden. Dolayısı ile smatch[] şeklinde
kullanırsak eriştiğimiz nesneler submatch sınıfı türünden nesneler.
sm[0] containerda tutulan 1. submatch, sm[1] containerda tutulan 2. submatch...

Submatch sınıfının bir interfacei var. Buradaki funclar bu interface hakkında bilgi veriyorlar.

Aşağıdaki örnekten member funclara bakıyoruz.

int main()
{
	regex rgx{"[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"};

	smatch sm;

	string str;

	//regex_search(str,sm,rgx); // burada 2. parametre out parametre yani gönderdiğim nesneyi set edecek.
	
	
	// SUBMATCH MEMBER FUNCLAR	
	if(regex_search(str,sm,rgx))
	{
		sm[0].str(); // bu submatchi bir yazı olarak veriyor. 
		sm[0].length(); // bu submatch olan yazının uzunlupubu verir. 
		std::cout << sm[0] << '\n'; // hatta bir inserterıda var.
	}

	// MATCH RESULT NESNESİNİNDE MEMBER FUNCLARI VAR
	sm.str(); // yazı
	sm.pos(); // index
	sm.len(); // uzunluk veriyor.
}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

ÇOOOOK ÖNEMLİ !!!!!!!!!!!!!!!!!!!!!!!!!!!!

(\d{4}\.([a-f]{4})\.(\d{4})
1784.dcba.5653
birinci capture grup 1784
ikinci capture grup dcba
üçüncü capture grup 5653

Burada bir match result nesnesi kullanınca 
submatchlerden oluşan bir container ve bu submatchleri verecek

İnceleyelim

alican1784.dcba.5653enes

mr[0] bu eleman matchin kendisi, 1784.dcba.5653 kısmının tamamı
mr[1] 1784
mr[2] dcba
mr[3] 5653
prefix()  alican
suffix()  enes

Düzenlemeye çalışalım !
       
	    mr1 mr2  mr3
 alican1784.dcba.5653enes
prefix |		    | suffix
	   |____________|
			mr0


			
ÇOK ÖNEMLİ ÖRNEK !!!!!!!!!!!!!!!!!!!!!

int main()
{
	string s{alican1784.dcba.5653enes};
	std::cout << "regex stringi : " << s << '\n';

	string r_s{"(\\d{4})\\.([a-f]{4})\\.(\\d{4})"}; // 2 tane \ koyduk çünkü 1 tanesi escape sequence
	std::cout << "regex stringi : " << r_s << '\n';

	smatch sm;
	regex rgx{r_s};
	
	if(regex_search(s,sm,rgx)) 
	{
		std::cout << "bulundu\n";
		
		std::cout << "submatch sayisi : " << sm.size() << '\n'; // container sıze bilgisini verir yani kaç submatch var.
		
		for(size_t i = 0; i < sm.size(); ++i),
		{
			//std::cout << "submatch " << i << " = " << sm[i] << '\n'; // tüm submatchleri yazdık.
			// std::cout << sm[i].str(); // yine aynı yazıyı yazdı.
			// std::cout << sm.str(i); // yine aynı yazıyı yazdı.
			//std::cout << sm.str(); // argüman geçmezsen defaultta 0 değerini alır.

			//--------------------------------------------------------------------------------------------------

			//std::cout << sm[i].length(); // stringin uzunluğunu veriyor.
			//std::cout << sm[i].str().length(); // stringin yukarıdaki ile aynı
			//std::cout << sm.length(i); // buda aynı
			//std::cout << sm.length(); // buda defaultta 0 indexi ile çalışır

			//--------------------------------------------------------------------------------------------------

			//std::cout << sm.position(); // match in bulunduğu yerin indexini veriyor. 6
										  // Yani bizde 1784... ile başlıyor ve 1 in bulunduğu yerin indexi
										  // o da 6
			
			// std::cout << sm.position(0) << '\n'; //yukarıdaki ile aynı
			// std::cout << sm.position(1) << '\n'; //1. submatchin pozisyonu
			// std::cout << sm.position(2) << '\n'; //2. submatchin pozisyonu

			//--------------------------------------------------------------------------------------------------
			
			//std::cout << sm.prefix(); // Buda bir submatch döndürüyor ama 
									  // bu submatch, match olandan önceki kısım.
									  // Alican yazısını yazar
			
			//std::cout << sm.prefix().str(); // Yukarıdaki ile aynı
			
			//std::cout << sm.prefix().length(); // length i verir.
			
			//--------------------------------------------------------------------------------------------------

			//std::cout << sm.suffix() << '\n'; // buda suffix kısmı

			//std::cout << sm.suffix().str() << '\n'; // buda aynı yazıyı verir.

		}
	}
}

-----------------------------------------------------------------------------------------------------------------------------

DOLAŞMAK IÇIN

int main()
{
	string s{alican1784.dcba.5653enes};
	std::cout << "input stringi : " << s << '\n';

	string r_s{"(\\d{4})\\.([a-f]{4})\\.(\\d{4})"}; // 2 tane \ koyduk çünkü 1 tanesi escape sequence
	std::cout << "regex stringi : " << r_s << '\n';

	smatch sm;
	regex rgx{r_s};

	if(regex_search(s,sm,rgx))
	{
		for(size_t i = 0; i < sm.size(); ++i)
		{
			std::cout << sm[i] << '\n';
			std::cout << sm[i].length() << '\n';
			std::cout << sm[i].position() << '\n';
		}


		for(const auto &match : sm)
		{
			// böylede dolaşılabilir		
		}

		for(auto iter = sm.cbegin(); iter != sm.cend(); ++iter)
		{
			//*iter submatch nesnesinin kendisi
			//iter->str(); // burada da iterin gösteriği nesnenin(submatch) str funcını çağırdık.
		}
	}
}

-----------------------------------------------------------------------------------------------------------------------------

REGEX SEARCH İLKİNİ VERİR AMA BİZ HEPSİNİ İSTERSEK NE YAPACAĞIZ

2 yöntem var.İkinci olan yöntem daha kolay. Bu öneriliyor.  

1. yöntem regx search çağırıp indexi alacağız, ptr aritmetiği ile toplama çıkarma işlemleriyle
suffixin başladığı yeri bulup orada tekrar çağıracağız.

2. Çok daha kolay ve tercih edilir yol bir iterator sınıfını kullanmak.
Bu regex iterator.

String sınıfını kullanırsak kullanacağımız iterator sınıfı sregex_iterator
Bu biraz input iterator sınıfına benziyor.

sregex_iterator beg {s.begin(),s.end(), rgx}; // Burada bu iterator range in begini.
sregex_iterator end; //buda range in endi olarak görev yapacak.

int main()
{
	string s{alican1784.dcba.5653enes};
	
	string r_s{"(\\d{4})\\.([a-f]{4})\\.(\\d{4})"}; // 2 tane \ koyduk çünkü 1 tanesi escape sequence
	std::cout << "regex stringi : " << r_s << '\n';

	regex rgx{r_s};
	auto str = get_str_from_file("numbers.txt"); // nutility de varmış

	for(sregex_iterator iter{str.begin(), str.end(),rgx}, end; iter != end; ++iter)
	{
		// *iter match result(smatch türünden nesne)nesnesini veriyor.
		std::cout << iter->str(0) << '\n'; // yazıdaki tüm matchleri bulmuş oluyorum.
											// 1234.fbed.4356 gibi veriler yazdırı

		std::cout << iter->position(0) << '\n'; // iter->position() ile aynı.
												// her bulunan yazının indexi
												// 1234 veya 5864 gibi verileri yazar

		std::cout << iter->str(1) << '\n';  // Sadece 1. submatchleri yazar
											// 2342 gibi veriler yazar.

		std::cout << iter->str(2) << '\n';  // Sadece 2. submatchleri yazar
											// abcd  gibi verileri yazar.
	}

}

-----------------------------------------------------------------------------------------------------------------------------

ÖR:
Karmaşık bir dosyadan tüm mailleri bulacak bir kod

int main()
{
	string str{get_str_from_file("emails.txt")}; // bu func hocada var
	regex rgx {eregex()}; // buda hocada var.

	for(sregex_iterator iter{str.begin(), str.end(), rgx}, end; iter != end; ++iter)
	{
		cout << iter->str() << '\n'; // o komundaki nesnenin str funcını çağırıyoruz.
									// o konumdaki nesnes bir match resul
									// iter->str(0); değerini geçsek yine aynı ama
									// iter->str(1); varsa eğer ilk submatch geçilir.
	}
}

-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------

SREGEX_TOKEN_ITERATOR
---------------------
Adı üstünde tokenizing işlemleri için kullanılacak.
Bu sınıfı tıpkı sregex_iterator gibi kullanıyoruz.
Farkı sregex_token_iterator sınıfının constructoruna bir argümandaha gönderme şansımız var.
Farklı tarafı constrcutor son parametresine bir tamsayı değeri geçiyroum.
Bu tamsayı değerinin ne olduğuna bağlı olarak rangei dolaşırken bizi belirttiğimiz indexli
submatchlere eriştiriyor.


#include <iostream>
#include <string>
#include <regex>

int main()
{
	using namespace std;

	string str("projede projeyi basariya ulastiracak profesyonel programcilar gerekiyor");
	regex rgx("\\b(pro)([^ ]*)"); // \\b kelime başı.(pro) birinci capture grup pro olacak.
								  // daha sonra ikinci capture grupta boşluk olan karakterle başlamayacak demek.
								  // Yani boşluk olmayan karakterlerden olacak. * da 0-n arasında olacak diyor.

	sregex_token_iterator rend;

	//------------------------------------------------------------------------------------------------

	//Normal yapıyoruz
	for(sregex_iterator iter{str.begin(),str.end(), rgx}, end; iter != end; ++iter)
	{
		std::cout << iter->str() << '\n'; // pro ile başlayanları buldu burada
	}

	//------------------------------------------------------------------------------------------------

	// DİKKAT !!!!!
	// sregex_token_iterator kullanılacak.

	cout << "uyanlarin tamami\n";
	for (sregex_token_iterator iter(str.begin(), str.end(), rgx, 0); iter != rend; ++iter) // 0 burada 0 indisli submatchleri doşalıyorum demek.
		std::cout << " [" << *iter << "]";

	cout << "\n\n";

	//------------------------------------------------------------------------------------------------
	
	cout << "1. submatch'ler:";
	for (sregex_token_iterator iter(str.begin(), str.end(), rgx, 1); iter != rend; ++iter)
		std::cout << " [" << *iter << "]";  // 1 indisli submatch verir. yani pro ları yazar

	cout << "\n\n";

	//------------------------------------------------------------------------------------------------
	
	cout << "2. submatch'ler:";
	for (sregex_token_iterator iter(str.begin(), str.end(), rgx, 2); iter != rend; ++iter)
		std::cout << " [" << *iter << "]";  // jede jeyi ... bunları yazdı

	cout << "\n\n";

	//------------------------------------------------------------------------------------------------
	
	//Argüman olarak initializer list verdik
	cout << "1. ve 2. submatch'ler:";
	for (sregex_token_iterator iter(str.begin(), str.end(), rgx, { 1, 2 }); iter != rend; ++iter)
		std::cout << " [" << *iter << "]"; // pro jede pro jeyi pro fesyonel ... diye gidiyor.

	cout << "\n\n";

	//------------------------------------------------------------------------------------------------
	
	cout << "ayiraclar :";

	for (sregex_token_iterator iter(str.begin(), str.end(), rgx, -1); iter != rend; ++iter)
		std::cout << " [" << *iter << "]"; // Bu seferde bize verdiği submatchler uymayanlar :D:D

	cout << "\n\n";
}

-----------------------------------------------------------------------------------------------------------------------------

ÖNEMLİ !!!

Biz regex stringini öyle bir şekilde ayarlayacağız ki bu ayıraçları betimlesin.
Ayıraçları betimleyen bir regex nesnesi kullanarak sregex_token_iterator kullanarak
son parametreye  -1 geçersek bu seferde o ayıraçlarla ayrılmış tokenları dolaşmış oluruz.


#include <regex>
#include <string>
#include <iostream>

int main()
{
	using namespace std;
	string s = "murat, kadir, kemal ve aysenur C++ ogrendiler";

	regex rgx{ "[\\s,.]+" }; // \\s boşluk karakterlerinden herhangibiri olabilir.
							//  ayrıca virgül ve noktada olabilir. Bunlarda 1-n arasında olabilir.

	sregex_token_iterator iter{ s.begin(), s.end(), rgx, -1 }; 
	sregex_token_iterator end;
	for (; iter != end; ++iter) {
		std::cout << iter->str() << "\n";
	}
}

output
------
murat
kadir
kemal
ve
aysenur 
C++ 
ogrendiler


Eğer index olarak 0 verseydik.
., veya boşlukları verecekti


*/
