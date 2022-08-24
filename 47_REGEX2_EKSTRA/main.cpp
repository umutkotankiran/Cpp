/*

REGEX'TEN DEVAM

Replace işlemleri kaldı sadece
regex_replace bir func. 1. parametresine string yada cstring greçilir
2. parametresine ise regex nesnesini geçiyoruz.
3. parametresine yerdeğiştirme yani replacement paterni giriliyor.

Bu func bize başka bir string döndürecek. Bu değer bizim funca gönderdiğimiz stringin replace işlemi
yapılmış hali.


ÖR:
#include <regex>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str{ "profesyonel butun programcilar projelerdeki tum yazilimsal problemleri cozebilmeli" };
	regex rgx{ "\\b(pro)([^ ]*)" };

	//auto s = regex_replace(str, rgx, ""); // matchlerin yerine boş yazı koy demek.

	//auto s = regex_replace(str, rgx, "$1"); // match olan yerlere 1. capture grubu koyacak. pro butun pro pro tum yazilimsal ...
 
	//auto s = regex_replace(str, rgx, "$1$2"); // Böyle yazarsak hiçbir değişiklik olmuyor. Çünkü $1 birinci, $2 ise ikinci capture grup.
												// dolayısıyla matchlerin yerine kendisini koymuş olduk.
	
	//auto s = regex_replace(str, rgx, "($1)($2)", regex_constants::format_first_only); // Yine matchi yazacak ama 
																						// capture 1 ve capture 2 yi parantez içinde yazacak.

	cout <<  s  << "\n";	
}

 
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------------------------------

EĞER BU FUNCLARIN SON PARAMETRESİNE(CTORLARDA DAHİL) REGEX CONSTANT NAMESPACE İ İÇİNDEKİ 
BAZI CONSTEXPR SABİTLERİ GEÇERSEK FUNCTİONUN DAVRANIŞINI ÖZELLEŞTİRİYORUZ.

 
int main()
{
	string str{ "profesyonel butun programcilar projelerdeki tum yazilimsal problemleri cozebilmeli" };
	regex rgx{ "\\b(pro)([^ ]*)" };

	//---------------------------------------------------------------------------------------------------------

	//DİKKAT
	
	// auto s = regex_replace(str,rgx,"($1)($2)", regex_constants::format_first_only); 
	// Burada kullandığımız sabit argüman olarak geçilince sadece ilk match için değişikliği yapacak.
	// defaultta tüm matchler için değişiklik yapacaktı.

	//---------------------------------------------------------------------------------------------------------

	// auto s = regex_replace(str,rgx,"($&)"); // $& demek  matchin kendisi demek. 

	// auto s = regex_replace(str,rgx,$`); // $`match haricindeki karakterleri koyacak demek match yerine
											// bu örnek pek uygun değil.

	std::cout << s << '\n'; 

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <string>
#include <regex>
#include <iostream>

using namespace std;

int main()
{
	string str = "corona virus yayiliyor,\n"
		"olu sayisinin artmasindan\r\n"
		"endise ediliyor.\n"
		"Allah ulkemizi korusun\r\n"
		"Amin!";

	regex rgx{ "\\r?\\n" }; // \\r carriage return olacak ve ? bundan olabilir ve olmayabilir demek.
						    // \\n ise \n demek yani newline

	auto line = regex_replace(str, rgx, " "); 

	cout << "[" << line << "]\n";

}

--------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <regex>

int main()
{
	using namespace std;

	string str;
	cout << "bir yazi girin: "; // mehmet   mehmet  --> tamamen match olacak


	getline(cin, str);
	regex rgx{ R"(\b(\w+)\s+\1)" }; // Raw string literal bu o yüzden \ yazmak için \\yazmadık
									// \b kelime başı demek. (w+) bu birinci capture grup, burada alphanum ve _ 
									// karakterlerden 1 veya daha fazla var. \s+ boşluk karakterlerinen 1 veya daha fazla
									// \1 ise back reference, birinci capture gruptaki yazının aynısı olması gerekiyor.


	cout << regex_replace(str, rgx, "$1") << "\n"; // $1 birinci capture grup demek.
												   // mehmet     mehmet tamamen match oldu
												   // $1 demek 1.capture grup ile replace edilecek demek
												   // yani 2 tane mehmet yerine 1. capture grup mehmet olduğundan
												   // sadece mehmet yazdı.

	// emre emre buraya gel gel hemen dedim dedim	-->	yazarsak
	// emre buraya gel hemen dedim  --> olur sonuç

}











*/