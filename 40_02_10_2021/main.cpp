/*


STL kodlarında kullanılan biz idiyom var bu ne demek ?

ÖR:

int main()
{
    vector<int>ivec(100);
    auto iter = find(ivec.begin(),{},10);  // Bu baya yaygınlaştı.func return değerinde de argüman olarakta kullanıldığını göreceğiz.
}

Hikaye aşağıda

class myclass{
public:
    Myclass(int);
    //explicit Myclass(int);
};

int main()
{
    Myclass x = 12; // copy init explicit olsaydı bu kullanım sentaks hatasıydı zaten.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Yukarıdaki funclarda da var.

class myclass{
public:
    Myclass(int);
    //explicit Myclass(int);
};

void func(Myclass);

Myclass foo()
{
    return 15; // Yine ctor explicit olmamalı
}

int main()
{
    func(21); // Ctor explicit değilse ise böyle çağrı ok. Explicit olsaydı sentaks hatası.

    foo();
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ayrı durum sınıflarda da geçerli.

class myclass{
public:
    Myclass(); // DİKKAT DEFAULT CTOR EXPLICIT OLURSA VEYA OLMAZSA DURUMLARINA BAKIYORUZ !!!!!
    Myclass(int); 
    //explicit Myclass();
};

void func(Myclass)

Myclass foo()
{
    return {}; // Burasıda legal.{1} de yapabilirdik
}

int main()
{
    Myclass m = {}; // böyle yaptığımda default init edilsin demek bu. Default ctor explicit olursa yine geçersiz.

    Böyle durumda artık ctor explicit değilse aşağıdaki çağrı legal
    func({}); // Myclass x = {}; yapıyor aslında. {} yazmak ile Myclass{} yazmak arasında fark kalmadı
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class myclass{
public:
    Myclass(); // DİKKAT DEFAULT CTOR EXPLICIT OLURSA VEYA OLMAZSA DURUMLARINA BAKIYORUZ !!!!!
    Myclass(int);
    //explicit Myclass();
};

template <typename T>
void func(T x, T y)
{

}

int main()
{
    Myclass m1,m2;
    
    func(m1,m2);

    func(m1,{}); // Burada 2. argümandan çıkarım yapılamayacak. Birincisi Myclass türündense ikinciside myclass türünden olacak.
}

KALDIĞIMIZ YERDEN DEVAM

=================================================================================================================================================================================
=================================================================================================================================================================================
=================================================================================================================================================================================
=================================================================================================================================================================================
=================================================================================================================================================================================
=================================================================================================================================================================================

LAMBDALARDAN DEVAM
------------------

1.
Stateless Lambdaların Default Ctorlarının ve copy assignmentlarının delete edilmemesini konuştuk.Birçok templatede argüman olarak lambda ifadesini kullanmamız gerekiyordu.
Bu özellik olmasaydı ör: set containerında set<int, less<int>> yazmak yerine 

int main()
{
    auto f = [](int x, int y){ return x < y; };

    set<int, decltype(f)> myset; C++ 20 de geçerliydi
    set<int, decltype(f)> myset(f); C++ 20 öncesinde geçerli.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Bir soru üzerine,
[](){

// Burada closure type türünden nesne oluşturabilir miyiz ?
// böyle bir olasılık yok. TEST ET

}

NOT : LAMBDALARDA RECURSIVE LAMBDA OLUŞTURABİLİYORUZ.BİRKAÇ FARKLI TEKNİĞİ VAR.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2.
set<int, decltype([](int x,int y){return x > y;})> myset; //Burasıda geçerli C++20 ile 
Unevaluated context oluşturduğu için ok. Bir değişken oluşturmadan yapabiliyoruz.

Using bildirimide yapabilirz.

using m = decltype([](int x,int y){return x > y;};

set<int,m>myset;

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


C++20 ÖZELLİKLERİNİ ÖZETLERSEK
1 - Stateless lambdaların default ctor ve copy asisngment olmasını 
2 - unevaluated contexte lambda ifadelerinin kulanılabilmesi yani bir lambdaya doğrudan using bildirimi ile bir değişken oluşturmadan daha türeş ismi verilebilmesi 
3 - Template sentaksı var artık
    []<class/typename T>(T x, T y){ return x + y;};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TEMPLATE SENTAKSI

auto g = [](auto x, auto y){return x + y;}; //Burada x ve ye için çıkarım ayrı ayrı yapılıyor.Türlerinin aynı olması gerekmiyor.
auto f = [] <class T>(T x, T y){ return x + y;}; // Yukarıdaki le arasında ne fark var.

f(1, 2.4); //SENTAKS HATASI OLUR
g(1, 2.4); //SENTAKS HATASI OLMAZ

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

auto f = [] <typename T>(vector<T> x, vector<T> y){ }; 
f( ... )
Burada gönderilen argümanların aynı türden 2 tane vector olması gerekiyor.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Aşağıdaki farkı daha öncede yazmıştık İleri C++ tada görüldü.

auto f = [](auto ...args){
    foo(std::forward<decltype(args)>(args)...);
};

Template sentaksında yazım daha kolay
auto g = []<typename ...Args>(Args ...args){
    foo(std::forward<(Args)>(args)...);
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DECLTYPE AUTO
-------------
26. Derste decltype auto gösterildi.C++14 decltype auto eklendi.

int g = 10;        

int& foo()
{
    return g;
}

 const int& func()
 {
    return g;
 }


int main()
{
    foo() = 20;
    ++foo();

    std::cout << " g= " << g << "\n";

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Lambdalarda lambda nın return değerini auto çıkarım yoluyla elde ediliyor.Burada derleyici auto ile çıkaracak. Biz bunu decltype ile yapmak istiyoruz o yüzden
    decltype(auto) ile yaparsak tür çıkarımını decltype ile yapmış oluruz.

    auto f = [](){
        return foo();
    };

    f(); // bunun return değerinin int olduğu görülüyor bakınca mouse ile.
    f() = 98; // Sentaks hatası.

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    func(); // buna bakınca constlukta düştüğü görülür.

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    BURADA YAPILACAK ŞEY DECLTYPE AUTO. BU SAYEDE İFADENİN VALUE CATEGORİSİ VE CONSTLUKTA KORUNUR.
    auto f = []()->decltype(auto){
        return foo();
        // return func();   burasıda diğer func için
    };

    f(); // return değeri int &
    f(); // return değeri const int &

    f()  = 97; //Artık geçerli.
    ++f(); // Geçerli.
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Decltype auto, Decltype + auto gibi çalışıyor. Çalışması için initialize edilmeli.

int main()
{
    int x = 10;
    int &r = x;
    int *ptr = &x;

    decltype(auto) y = x; // y nin türü int. 

    decltype(auto) y = r; // y nin türü int & 
    
    decltype(auto) y = x + 5; // y nin türü int

    decltype(auto) y = *ptr; // y nin türü int &

    decltype(auto) y = std::move(x); // y nin türü int&&    
}

Bir lambda eklemeside var. lambda init capture yaparken pack expansion yapabiliyoruz. Ona girmedi.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

İKINCI PARAMETRENIN TÜRÜ BIRINCISI NE ISE O OLSUN ISTERSEK

template <typename T>
void func(T x, T y) 
{
    
}

void func(T x, decltype(T))  // Böyle olmaz sentaks hatası.

Nasıl yapılabilir ? 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

GENEL TEKNIĞE BAKALIM

C++ 20 ile geldi aşağıdaki.

template <typename T>
struct idendity
{
    using type = T;
}

template <typename T>
using idendity_t = idendity<T>::type;

int main()
{
    idendity<int>::type // Burada int türü olacak burası

    //yada bu
    idendity_t<int> //burasıda int demek. Burası ile ilgili bir soru sormuştum ben. remove_reference<T>::type yaptığımızda neden tür çıkarımı yapılamıyor demişti hoca.
}

Eskiden kendimiz yazıyorduk C++20 ile std::type_idendity eklenmiş
std::identity de eklenmiş. ikiside var. Farkına bakmak lazım.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

template<class T>
T foo(T a, T b){
    return a + b;
}

template <class T>
T bar(T a, std::type_identity_t<T> b)
{
    return a + b;
}


int main()
{
    std::cout << bar( 4.2, 2) << "\n"; // Birinci argüman 4.2 T türü double.2. parametre type idendity nin T açılımının type olduğundan o da double olacak.
}                                       // tek parametre type_idendity_t<T> olsa tür çıkarım ı yapılamaz.


==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

 SHARED PTR
 ----------
 En çok kullanılan unique ptr ama onun varlık sebebi tek sahiplik ilkesi. Exclusive ownership. Bir nesneyi bir pointer gösterebilir.
 Bunun çok özel bir durum yoksa ekstra bir maliyetide yok.

 Memory header fileda shared ptr var. Shared ptr de ise bir kaynağı paylaşımlı olarak kullanmak var.
 Bütün sahipler ise kaynakları kullanabilirler. Burada reference counting tekniği ile aynı kağnağı gösteren pointerlardan en sonuncusunun hayatı bitene kadar kaynak tutulacak ama
 onu gösteren son pointer hayatı bittiğinde ve onun dtoru çağrılınca, kaynakta sonlandırılacak. Son pointerın hayatı bitince kaynağında hayatı bitiyor yani.

 Burada ilave bir maliyet var. Reference counting uygulanıyor. Arka planda kaç tane sahibi varsa bunu tutuyor. 
 
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 FARKLILIK

 Burada deleter template tür parametresi değil.
 Burada type erasure tekniği(İleri C++ ta anlatılıyor detaylı) ile bu template parametresi olmaktan çıkarılmış ve doğrudan ctora argüman olarak gönderiliyor.

 shared_ptr<int> spx {new int}; // 1 tane tür argümanı var.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 DELETER VAR ISE ARGÜMAN OLARAK GEÇILIYOR.
 
 Deleter burada Ctorun parametresi

 int main()
 {
    {
     shared_ptr<int> spx {new int{34}, [](int *p){  std::cout  <<p <<" delete ediliyor";  delete p; } }; // Deleter bir closure type yani lambda ifadesi ve deleter olarak yazdık.
    } 
    
    std::cout << "Main devam ediyor\n";
 }

 Deleter ctor parametresi yani tür argümanı değil. Deleter burada type erasure tekniği ile yerleştiriyor sınıf. Biz sadece Ctora argüman olarak gönderiyoruz.
 Eğer Ctora argüman göndermezsek default delete kullanılıyor.

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

DEFAULT CONSTRUCT EDILEBILIYORLAR

 int main()
 {
    shared_ptr<Triple> spx; // Geçerli
    shared_ptr<Triple> spx{new Triple{1,2,3}}; //Geçerli

    if(spx)
    {
        std::cout << "Dolu\n";
    }
    else
    {
        std::cout << "Dolu\n";
    }
 }

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

KOPYALAMAYA AÇIK BIR TÜR

 int main()
 {
    shared_ptr<Triple> spx{new Triple(1,2,3)};

    {
        auto spy = spx;
        auto spz = spx;
    }

    //Burada halen spx tutuyor dinamik ömürlü nesneyi.Kaynaklar henüz geri verilmedi burada

    std::cout << "main devam ediyor\n";
    getchar();
 }

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 USE_COUNT 
 ---------

 Referans sayacının değerini get ediyor.

 Aynı kaynağı gösteren shared ptr nin use count değerleri aynı oluyor.

 int main()
 {
    shared_ptr<Triple> spx{new Triple(1,2,3)};
    std:cout << "spx.use_count() = "<< spx.use_count() << "\n"; // 1

    {
        auto spy = spx;

        std:cout << "spx.use_count() = "<< spx.use_count() << "\n"; //2
        std:cout << "spy.use_count() = "<< spy.use_count() << "\n"; //2
        std:cout << "spz.use_count() = "<< spz.use_count() << "\n"; //2

        auto spz = spx;

    }

    std::cout << "main devam ediyor\n";
    getchar();
 }

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 auto &x = spx; //Artmaz
 auto x = spx; //Artar

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

& KULLANINCA REF COUNT ARTMAZ

int main()
 {
    shared_ptr<int> spx(new int{45});

    {
        std:cout << "spx.use_count() = "<< spx.use_count() << "\n"; // 1

        auto spy = std::move(spx); //DİKKAT
        
        std:cout << "spx.use_count() = "<< spx.use_count() << "\n"; // 0
    }
}

 Taşıdığımız zaman
 auto x = std::move(spx); // spx boşa çıktı ve use countu 0 oldu.
 Bu gerekmeyecek genelde.

 Kopyalanınca count artıyor. Taşınınca boşa çıkıyor. 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 void foo(shared_ptr<Triple> p)
 {
    std::cout << p.use_count<<"\n"; // 2 oldu use count.Dİğerinden copy yoluyla elde edildi çünkü

    p->set(1,35,66); // -> ve * operatorleri var.

    std::cout << *p << "\n";
 }

 int main()
 {
    shared_ptr<Triple> spx{new Triple(1,2,3)};
    foo(spx);

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    SIZELARI FARKLI ÇÜNKÜ SHARED_PTR İÇİNDE KONTROL BLOĞUNDA BİR POİNTER TUTUYOR.REF COUNT VE BAŞKA BİLGİLER O KONTROL BLOĞU İÇİNDE

    std::cout << sizeof(unique_ptr<Triple>) << "\n"; // 4 Byte
    std::cout << sizeof(shared_ptr<Triple>) << "\n"; // 8 Byte

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    MAKE_SHARED
    -----------
    Bu bir func şablonu.

    auto sp = make_shared<triple>(10,20,30);

    Bir shared ptr nesnesi oluşturduğumuz zaman dinamik ömürlü nesne hayata geliytorsa bu kontrol bloğuda oluşturuluyor. Kontrol bloğununa adreside shared ptr içerisindeki 
    bir pointerda tutuluyor. bu blok vasıtasıyla bazı bilgilere erişiyor başında ref count var.

    make shared in bir avantajı var. shared_ptr<Triple> sp{new Triple}; Bu durumda derleyici bir optimizasyon yapamaz. Derleyici new Triple için bir dinamik bellek bloğu 
    ayarlamak zorunda, bir dinamik bellek bloğuda o kontrol bloğu kullanımı için allocate ediliyor. Operator newi kendimiz yazsak 2 kere ayrı operator new çağrısı
    göreceğiz. birincisi dinamik ömürlü triple nesnesi için ama ikincisi örtülü olarak oluşturulan kontrol bloğu için(deleter, ref count, dinamik ömürlü nesne adresi) 
    ayırıyor.

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

void* operator new(size_t n)
{
    std::cout << "operator new called n : " << n << "\n";
    void* vp = std::malloc(n);
    if (!vp) {
        throw std::bad_alloc{};
    }
    std::cout << "address of allocated block : " << vp << "\n";
    return vp;
}

struct Data {
    char buffer[1024]{};
};


void f1()
{
    std::cout << "f1 cagrildi\n";
    auto p = new Data;
    std::shared_ptr<Data> sptr(p);
    std::cout << "\n\n";
}

void f2()
{
    std::cout << "f2 cagrildi\n";
    auto sptr = std::make_shared<Data>();
    std::cout << "\n\n";
}

int main()
{
    f1();
}

ÇIKTI
-----
f1 cagrildi
operator new called n : 1024                // struct için 1024 bytelık blok allocate edildi.
address of allocated block : 008FF308
operator new called n : 16                  // Burasıda yukarıda bahsedilen kontrol bloğu için allocate edildi.(ref sayacı, zayıf ref sayacı .... için ayrıldı)
address of allocated block : 008F4858

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. çağrı

int main()
{
    f2();
}

ÇIKTI
-----
f2 cagrildi
operator new called n : 1036            Dinamik ömürlü nesne adresi + kontrık bloğu (12 + 1024)
address of allocated block : 00BCF308

make_shared, kodunu derleyiciler optimize ediyorlar. normalde 2 ayrı bellek bloğu allcoate edilirdi. En maliyetli işlemler dinamik bellek bloğu alma verme işlemi.
derleyici bunun kodunu şöyle yapıyor. Tek allocation yapıyor, hem kotnrol bloğunun hemde dinamik ömürlü data nesnesinin kulanacağı bir blok olacak.
Derleyicilerin hepsi bunu yapıyorlar. Zorunlu değil ama hepsi yapıyor.

struct içine aşağıdaki default ctoru yazarsak şunu görürüz.
Data()
{
    std::cout << " this : " << this<< "\n";
}

Operator new ile elde edilen adres ile this adresi aynı değil. Aynıda olabilirdi ama burada eşit değil çünkü bir kısmını kontrol bloğu için kullandı, bir kısmınıda 
data nesnesinin yerleştirileceği bellek bloğu adresi olarak kullandı compiler:D:D:D

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

UNIQUE PTR NIN FUNCLARI SHARED PTR YE BENZIYOR

int main()
{
    auto sp = make_shared<string>("Mustafa Korkmaz");

    sp -> push_back('!'); // burada -> kullanınca bu stringin member funcları

    sp. // . kullanınca burası shared ptr nin interface i gelir.
}

unique ptr de move assignement vardı, shared ptr de hem copy hem move var.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 C++ 17 YE KADAR SHARED PTR NIN DIZI SPECIALIZATIONU YOKTU

 int main()
 {
    shared_ptr<string[]> ptr; // C++17 ile geldi.
 }

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 int main()
 {
    unique_ptr<int> uptr{ new int{39} };
    uptr[2]; // böyle bir func yok.HATA
    *uptr; // bu var.SENTAKS HATASI DEĞİL.
    
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Kodu değiştirelim

    unique_ptr<int[]> uptr{ new int[50] };
    
    *uptr;    // sentaks hatası
    uptr[2];  // sentaks hatası değil.
 }

 [] OPERATOR FUNC I UNIQUE PTR DA VE SHARED PTR DA ARRAY SPECIALIZATION IÇIN VAR AMA PRIMARY TEMPLATE TE YOK !!!!!!!!!!!

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

WEAK_PTR
--------
Bu bir sınıf. Memory header file içerisinde yer alıyor.Weak ptr nesnesini bir shared ptr nesnesinden elde edebiliyoruz ama 
weak_ptr shared ptr nin refraans sayacını artırmıyor ve weak ptr nin * overloadu u yok. Ne işe yaradığını konunun sonunda göreceğiz.

weak_ptr<int> diye kullanılıyor

int main()
{
    weak_ptr<int> wp;
    
    wp.lock(); // reset, expired... funcları var

    NOT : C++20 de expired kaldırılacak dilden
       
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BIR WEAK_PTR YI SHARED_PTR DEN ELDE EDEBILIRIZ.

 int main()
 {
    shared_ptr<string> sp{new string{"necati ergin"}};

    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    weak_ptr<string> wp{sp}; //DİKKAT !!!

    std::cout << "sp.use_count() = " << sp.use_count() << "\n"; // REFERANS SAYACI DEĞİŞMEDİ !!!!

    weak_ptr nin interface inde -> veya * operatörleri yok. Yani weak_ptr nesnesi ile bir dnamik ömürlü nesneye erişme şansımız yok.
    
}

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

LOCK FUNC
---------
Lock functionu bize shared ptr nesnesini veriyor.

 int main()
 {
    shared_ptr<string> sp{new string{"necati ergin"}};
    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    weak_ptr<string> wp{sp}; 
    
    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    auto sptr = wp.lock(); // sonlanmamışsa shared ptr verecek.

}

EĞER WEAK_PTR YI OLUŞTURAN SHARED_PTR HALEN KAYNAĞINI KORUYORSA YANI ONUN KAYNAĞI GERI VERILMEMIŞSE, O KAYNAK SONLANDIRILMAMIŞSA, LOCK FUNCI
ÇAĞIRDIĞIMDA O KAYNAĞI GÖSTEREN YINE BIR SHARED PTR VERIYOR BANA. AKSİ TAKDİRDE NULLPTR  !!!!!!!!!!!!!!

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 int main()
 {
    shared_ptr<string> sp{new string{"necati ergin"}};
    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    weak_ptr<string> wp{sp};

    sp.reset(); // kaynak geri verildi.

    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    auto sptr = wp.lock(); // Kaynak sonlandırıldığı için shared_ptr nullptr durumuna düştü.
    if(sptr)
    {
        std::cout << "kaynak henuz sonlanmamıs\n";
        std::cout << *sptr << "\n";
    }
    else
    {
        std::cout << "kaynak sonlanmis\n";
    }
}

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
 
 EXPIRED FUNC
 ------------
 2. yol expired func. Kaynak sonlandıyusa boolean true, sonalnmamışsa boolean false döner.

 int main()
 {
    shared_ptr<string> sp{new string{"necati ergin"}};
    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    weak_ptr<string> wp{sp};

    sp.reset(); // kaynak geri verildi.

    std::cout << "sp.use_count() = " << sp.use_count() << "\n";

    if(!wp.expired()) // DİKKAT !!!!
    {
        std::cout << "kaynak henuz sonlanmamıs\n";
        std::cout << *sptr << "\n";
    }
    else
    {
        std::cout << "kaynak sonlanmis\n";
    }
}

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

a - Bir shared ptr den bir weak ptr oluşturabiliriz

b - Bu weak ptr yoluyla onu oluşturan shared ptr nin kaynağının sonlanmış olup olmadığını kontrol edebiliriz.

c - Bu kontrol 2 farklı şekilde yapılabilir.
    1 - LOCK FUNCTIONU : 
    auto sptr = wp.lock();      Return değeri shared ptr.Nullptr mi değil mi bakılır. True ise kaynak hayattadır değilse değildir.
    
    auto sptr = wp.lock();
    if(sptr)
    {

    }

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Aynı şekilde böylede bakılabilir değere.
    if(shared_ptr<string> sptr = wp.lock())
    {
        //...
    }


    NOT : if(T x = a) ... Modern C++ tan önceydi bu sentaks. Aynı şekilde if with initializer ilede bakılabilir.

    Burada yukarıdakine benzer if li örnek yapıldı ben yazmadım. 1:41
    
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    BIR LOCK FUNCTIONU ÇAĞRILMADAN DOĞRUDAN SHARED PTR, WEAK PTR DENDE OLUŞTURULABILIR AMA KAYNAK DELETE EDILMIŞSE EXCEPTION THROW EDER.

    Lock functionu çağırdığımızda boş ise nullptr döndürüyordu.

    int main()
    {
        shared_ptr<string> sp{new string{"necati ergin"}};
        std::cout << "sp.use_count() = " << sp.use_count() << "\n";

        weak_ptr<string> wp{sp};

        shared_ptr<string> spx {wp}; //GEÇERLİ !!!!
    }

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    int main()
    {
        shared_ptr<string> sp{new string{"necati ergin"}};
        std::cout << "sp.use_count() = " << sp.use_count() << "\n";

        weak_ptr<string> wp{sp};
        
        sp.reset(); 

        try{
            shared_ptr<string> spx{wp}; //  RESET ETMESEYDİK GEÇERLİYDİ. TEST EDİLEBİLİR. ŞİMDİ EXCEPTİON THROW EDER.
            std::cout << "isim : " << *spx << "\n";
        }
        catch(const std::exception&ex)
        {
            std::cout << "exception caught : " << ex.what() << '\n';
        }
    }

    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    2 - EXPIRED FUNC : true ise hayatta değildir. false ise expired olmamış yani hayatta.


    NEDİR BU ?
    Weak ptr kaynağa erişmenin yolu değil, kaynak hayatta mı bunu sorgulamanın yolu.

==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================
==================================================================================================================================================================================

WEAK_PTR NİN KULLANILDIĞI TEMEL SENARYO CYCLIC REFERENCE/ DÖNGÜSEL REFERANS 
---------------------------------------------------------------------------
Bir kaynağın sonlanması için o kaynağı gösteren tek bir shared ptr kalması gerekliyor. O tek shared ptr nin destructoru kaynağı sonlandırıyor.
Öyle durumlar oluşuyorki, ortada 2 tane shared ptr nesnesi var ama birinin kaynağı delete etmesi için öbürünün hayatının bitmesi gerekiyor, öbürünün hayatının
bitmesi içinde ötekini hayatı bitmesi gerekiyor.2 nesnede kaynağını veremiyor. Bu duruma cyclic reference kırılması için weak ptr kullanılıyor.

ÖRNEK ÜZERİNDEN GİDELİM.

#include <memory>
#include <iostream>

struct B;

struct A {
    //std::shared_ptr<B> bptr; // 1. durumda bunu kullandık
    std::weak_ptr<B> bptr; // // 2. durumda bunu kullandık
    ~A() {
        std::cout << "A destructor\n";
    }
};

struct B {
    std::shared_ptr<A> aptr;
    ~B() {
        std::cout << "B destructor\n";
    }
};

A nın içinde dinamik olarak üretilen B yi tutacak shared_ptr var, B de de A yı tutacak olan var.

int main()
{
    std::shared_ptr<A> spa{ new A };
    std::shared_ptr<B> spb{ new B };

    spa->bptr = spb; // b nin use_count u 2 oldu
    std::cout << "spb.use_count() = " << spb.use_count() << "\n";

    spb->aptr = spa; // a nın use count u da 2
    std::cout << "spa.use_count() = " << spa.use_count() << "\n";
    //getchar();
}

Çıktısında ne A nesnesinin nede B nesnesinin delete edilmediğini görürüz.
Neden edilmedi ? Cyclic reference, A nın delete edilmesi için 1 pointer onu göstermeli ama 2 tane var. B içinde aynısı var 2 tane.

KİTLENDİK :D:D:D:D

PROBLEMİN ÇÖZÜMÜ BİRTANESİNİ WEAK_PTR YAPMAK. YANİ YUKARIDA YAZDIĞIM 2. DURUM.
1. DURUM SATIRINI YORUM YAP. 2. CİYİ YORUMDAN ÇIKAR.

BU DURUMDA ÇIKTIDA DESTUCTORLAR ÇAĞRILIR VE BU GÖRÜLÜR.

DAHADA İYİ ANLAMAK İÇİN BAŞKA BİR KOD YAZALIM

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>

 // herkedinin 1 arkadaşı olabiliyor.

class Cat{
public:
    Cat(const std::string name) : m_name{name}
    {
        std::cout << m_name  << " isimli kedi olusturuldu\n";
    }
    ~Cat()
    {
        std::cout << m_name  << " isimli kedi oyundan cikti\n";
    }

    void print_info() const
    {
        if(!msp){
            std::cout << "benim ismim " << m_name << " arkadasim yok\n";
        }
        else
        {
            std::cout << "benim ismim " << m_name << " arkadasim var ismi << msp->mname << "\n";
        }
    }
    
    void make_friend(std::shared_ptr<Cat> other)
    {
        msp = other;
    }

private:
    std::string m_name;
    std::shared_ptr<Cat> msp;
    // std::weak_ptr<Cat> msp; düzeltecek bu
};

int main()
{
    auto spx = make_shared<Cat>("sarman");
    spx->print_info();

    auto spy = make_shared<Cat>("pamuk");
    spy->print_info();

    spx->make_friend(spy);
    spx->print_info();
    spy->make_friend(spx);
    spy->print_info(); // hem sarman hem pamuk oluşturuldu ikiside birbirinin arkadaşı ve hiçbiri oyundan çıkmadı. yine cyclic reference var.
                       // ikisinde de use_count 2 ve 1 e düşemiyor :D:D 
   
}

Çözüm sınıfın veri elemanını weak_ptr yapıp kodu ona göre düzenlemek.

1 - veri elemanını böyle değiştir.
std::weak_ptr<Cat> msp; 

2 - print_info yu aşağıdaki gibi düzelt
void print_info() const
{
    if(auto sp = msp.lock()){
        std::cout << "benim ismim " << m_name << " arkadasim var ismi << sp->mname << "\n";
    }
    else
    {
        std::cout << "benim ismim " << m_name << " arkadasim yok\n";  
    }
}

Artık birinin içindeki weak ptr olduğundan cyclic reference ortadan kalktı.ASIL SENARYO BU.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Containerda Shared ve unique ptr ler tutmak sık karşımıza çıkıyor.Shared in containerda tutulması daha önemli. Böylece dinamik ömürlü nesneleri birden fazla containerda
tutabiliyorum.

int main()
{

    vector<shared_ptr<string>> vec;

    for(int i = 0; i < 10; ++i)
    {
        vec.emplace_back(new string( rname() ));   // vectore 10 tane shared ptr ekledik
    }

    for(const auto &p : vec)
    {
        std::cout << *ptr << " ";
    }

    std::cout << "\n";

    list<shared_ptr<string>> ls{ vec.begin(), vec.end() };
    
    for(auto &str : ls) // isimleri değiştiriyoruz çünkü listedeki öğeler aslında aynı nesnesler.
    {
        *sp += "can";
    }

    for(const auto &p : vec)
    {
        std::cout << *ptr << " ";
    }

}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ÖR:

using svec = std::vector<std::string>;

class Booklist{
public:
    Booklist(std::initializer_list<std::string> blist) : mpvec{new svec{blist}} { }         // vector<string> i initializer list ile initialize ettik aslında

    void add_book(std::string name)
    {
        mpvec->push_back(std::move(name));
    }

    void print()const
    {
        std::cout << "listedeki kitaplar : ";

        for(const auto&s : *mpvec)
        {
            std:cout << s << "\n";
        }
    }

    void delete_book(const std::string& name)
    {
        if(auto iter = find(mpvec->begin(), mpvec->end(),name); iter != mpvec->end())
        {
            mpec->erase(iter);
        }
    }

private:
    std::shared_ptr<svec> mpvec;
};

int main()
{
    Booklist x {"savas ve baris","aclik","kara kitap","genclik"};
    x.add_book("mai ve siyah\n");
    x.print();

    x.add_book("Masumiyet");
    x.delete_book("aclik");
    x.print();

    Çalışıyor.

    --------------------------------------------------------------------------------------------------------------------------------------------------------------------

    auto y = x; // Derleyicinin yazdığı copy ctor, ynin elemanı olan share ptr yi x in veri elemanı olan shared_ptr ye initialize etti.İkisinin shared_ptrsi aynı
                // vectoru gösteriyor.

    auto z = y;
    z.add_book("cinali isbasinda");  //Hepsi aynı kaynağa ekleme yapar ve print edersek hepsi aynı şeyleri print eder

    x.print();
    y.delete_book("genclik");

    z.print();  // hepsi birbirini gösteriyor gibi bir durum var :D:D

    --------------------------------------------------------------------------------------------------------------------------------------------------------------------

    NEDEN BU KADAR ATRAKSİYONA GİRDİK? SINIFA STATIC VERİ ELEMANI OLARAK VECTOR KOYSAYDIK OLMAZ MIYDI, TÜM NESNELER AYNI STATIC ÖMÜRLÜ VECTORU KULLANSAYDI OLMAZ MIYDI??

    İkisi birbirinin aynısı değil. 

    Booklist a{"C","pascal","Cobol"};
    auto b = a;
    auto c = a;
    auto d = a; // Burada a, b,c nin listeleri ayrı liste ama yukarıdaki x,y,z nin listesi ayrı liste.

    a.add_book("python language");
    a.add_book("go language");
    a.add_book("rust language");
    
    d.print(); // d nin printi x ile alakası yok. farklı listeler. Fark bu.
    
}

MOLA


=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================

CRTP
Curiously Recurring Template Pattern

İleri C++ ta görülecek

template <typename T>
class Base {
public:
    void func()
    {
        std::cout << typeid(T).name() << "\n";
        reinterpret_cast<T&>(*this).foo();
    }
};
class Der : public Base<Der> {  //Burada base<der> aynı zamanda der sınıfının taban sınıfı.Burada T yi kullansam  
public:
    void foo()
    {
        std::cout << "Der::foo()\n";
    }
};

int main()
{
    Der myder;
    myder.func();  // Bu virtual dispatch in compile time a uyarlamış hali
}

Bunlar genel bir fikir vermeye yönelik gösterildi.İleri C++ta görülecek detaylı bir şekilde.

Shared ptr ile ilgili bir ihtiyaaç var bunun içinde crtp den faydalanılmış.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Myclass{
public:

    void func()
    {
        // Myclass sınıfı türünden bir nesne bir shared ptr tarafından kontrol ediliyor.
        // bu shared ptr nin bir kopyasını çıkarmak istiyoruz.
        // *this i gösteren shared ptr ye bir tane daha ekleyeceğiz.

        std::shared_ptr<Myclass> spy;
        std::cout << spy.use_count() << "\n";
    }
};


int main()
{
    auto sp1 = make_shared<Myclass>();
    
    sp1->func();
}

BUNUN ÇÖZÜMÜ İÇİN BİR ARAYÜZ EKLEMİŞLER.


----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Eğer bir sınıfın üye fonksiyonu içinde shared_ptr ile hayatı kontrol edilen * this nesnesini gösteren
// shared_ptr'nin kopyasını çıkartmak isterseniz sınıfınızı CRTP örüntüsü ile kalıtım yoluyla std::enable_shared_from_this
// sınıfından elde etmelisiniz

#include <memory>
#include <iostream>

using namespace std;

class Neco : public std::enable_shared_from_this<Neco> {  //CRTP !!!!!!!!!!!!!!!!!!!!
public:
    Neco()
    {
        std::cout << "Neco ctor this : " << this << "\n";
    }

    void func()
    {
        std::cout << "Neco::func() islevi : " << this << "\n";
        //ben func islevinin bir shared_ptr ile kontrol edilen dinamik Neco nesnesi icin cagrildigina eminim

        auto sptr = shared_from_this(); // Bu func aslında nesneyi gösteren shared ptr nin bir copy sini çıkarıyor.
        
        std::cout << "sptr.use_count() = " << sptr.use_count() << "\n";
    }

    ~Neco()
    {
        std::cout << "Neco destructor : " << this << "\n";
    }
};


int main()
{
    auto sp = make_shared<Neco>();
    sp->func();   // bunu çağırınca shared from this ile sp nin bir kopyası oluşacak, dinamik ömürlü sharedlerin sayısı 1 artacak.
    
    --------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    Burası exception throw eder çünkü hayatı shared ptr ye bağlanmış bir dinamik ömürlü nesne olmalı. Burada raw pointer kullanılmış.

    Neco *p = new Neco;

    try {
    	p->func();
    }
    catch (const std::exception &ex) {
    	std::cout << "hata yakalandi : " << ex.what() << "\n";
    }
}

AMAÇ : BİR ÜUE FUNCTION İÇİNDE BU ÜYE FUNC HANGİ NESNE İÇİN ÇAĞRILDIYSA ONUN SHARED PTR SİNİN BİR COPY SİNİ ÇIKARTMAK, BÖYLECE BU ÜYE FUNC İÇİNDE O KOPYAYI
KULLANABİLMEK. EN TİPİK TEMALARDAN BİRİ BUNU VERİ YAPISINA EKLEMEK. YA FUNC IN BİR PARAMETRESİ OLACAK BUNDAN BİR NESNE GÖNDERECEĞİZ YADA BU YÖNTEMİ KULLANACAĞIZ


=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================

ALIASING CONSTRUCTOR
--------------------
İnsanlar pek anlayamıyormuş bunu.Shared ptr ile kontrol edilen dinamik ömürlü bir nesne var, ama biz bu nesnenin bir elemanına / bileşenine shared ptr oluşturmak istiyoruz.
Buradaki problem, uygun yapı oluturmazsak, biz elemana shared ptr oluşturduğumuzda, dinamik ömürlü nesnenin hayatı bittiğinde pointerımız dangling hale gelecek.

struct Member{


};

struct Owner{
    
    Member mx;
};

int main()
{
    using namespace std;
    auto optr = make_shared<Owner>();
    auto opx = optr; // burada aynı kaynağı kontrol eden nesneler

    --------------------------------------------------------------------------------------------------------------------------------------------------------------------

    shared_ptr<Member> mpx{ &optr->mx }; 
    optr.reset(); // bunu yaptığımızda yukarıdaki mpx dangling hale gelir.

    // YUKARIDAKI DURUMDAN ÖTÜRÜ SINIFA ALIASING CTOR EKLEMIŞLER

}

=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================

SHARED_PTR ALIASING CONSTRUCTOR
shared_ptr ile hayatı kontrol edilen bir sınıf nesnesinin veri elemanlarından/bileşenlerinden birini başka bir shared_ptr nesnesinin göstermesini istiyoruz.
Eğer bir önlem alınmaz ise sahip olan nesneyi gösteren 	shared_ptr'nin hayatı bitince, elemanı gösteren shared_ptr dangling hale gelirdi.
Buradaki problemi çözmek için shared_ptr sınıfının "aliasing ctor" denilen ctor'u ile elemana shared_ptr oluşturuyoruz:

SENTAKS
-------
shared_ptr<Member> spm (spowner, spowner->mx);

spowner = Elemanın sahibi olan shared ptr
spowner->mx  = ilgili elemanın adresi

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <memory>

class Member {
public:
    Member()
    {
        std::cout << "Member constructor\n";
    }

    ~Member()
    {
        std::cout << "Member destructor\n";
    }
};

class Owner {
public:
    Owner()
    {
        std::cout << "Owner constructor\n";
    }

    ~Owner()
    {
        std::cout << "Owner destructor\n";
    }
    Member mx;
private:

};


using namespace std;

int main()
{
    auto sp = make_shared<Owner>(); // owner nesnesini gösteren  shared ptr

    auto spm = shared_ptr<Member>(sp, &sp->mx); // birincisi yukarıdaki shared ptr, ikincisi memberın adresi.
    // Biz ana nesnenin hayatı bitse dahi, onun elemanını gösteren bir shared ptr olduğu sürece delete edilmeyecek.

    cout << "spm.use_count() = " << spm.use_count() << "\n";
    cout << "sp.use_count()  = " << sp.use_count() << "\n";
    (void)getchar();

    sp.reset();
    cout << "after sp.reset() call\n";
    cout << "spm.use_count() = " << spm.use_count() << "\n"; // Memberın use count u halen 1 yani nesnenin dtoru halen çağrılmadı
    cout << "sp.use_count()  = " << sp.use_count() << "\n";  // owneren use count u 0 a düştü ama halen dtor çağrılmadı.Ne zaman memberı gösteren shared ptr nin hayatı bitecek,
    (void)getchar();                                         //  o zaman destroy edilecek.
}

ÖZET
----
Shared ptr ile hayatı kontrol edilen bir nesnenin bir veli elemanını gösteren bir shared ptr oluşturabiliriz ama oluşturulan shared ptr nin dangling hale gelmesini engellemek için
memberı gösteren shared ptr yhi normal ctor ile değil aliasing ctor ile hayata getirmemiz gerekiyor. bunun bir parametresi ilgili birleşik nesneyi gösteren shared ptr yi istiyor
diğer parametresi ise elemanın adresini istiyor.


=======================================================================================================================================================================================
=======================================================================================================================================================================================

ÖR:

#include <memory>
#include <vector>
#include <iostream>


using namespace std;

struct Member { };

struct Owner
{
    ~Owner()
    {
        std::cout << "owner destructor\n";
    }
    Member mx;
};


using Ovec = std::vector<Owner>;


int main()
{
    shared_ptr<Ovec> svecptr(new Ovec); // use_count == 1
    svecptr->reserve(10);

    svecptr->emplace_back();
    svecptr->emplace_back();

    cout << "[1] svecptr.use_count() = " << svecptr.use_count() << "\n";

    shared_ptr<Owner> owner_ptr1(svecptr, &svecptr->at(0)); // Aliasing Ctor. 1. cisi vectoru gösteren shared ptr, 2. si vectordeki ilk elemanın adresi.
                                                            // artık vectoru reset etse bile shared ptr halen vectorun bir elemanını gösteren shared ptr hayatta olduğu sürece
                                                             // nesnenin hayatı bitmeyecek.

    cout << "[2] svecptr.use_count() = " << svecptr.use_count() << "\n";
    cout << "[3] owner_ptr1.use_count() = " << owner_ptr1.use_count() << "\n";

    shared_ptr<Owner> owner_ptr2(svecptr, &svecptr->at(1));
    cout << "[4] svecptr.use_count() = " << svecptr.use_count() << "\n";
    cout << "[5] optr1.use_count() = " << owner_ptr1.use_count() << "\n";
    cout << "[6] owner_ptr2.use_count() = " << owner_ptr2.use_count() << "\n";

    shared_ptr<Member> member_ptr(svecptr, &svecptr->at(1).mx); //KRİTİK KISIM !!! Burada vectordeki 1 indisli öğenin memberına shared ptr<member> türünden nesne oluşturduk ve
                                                                // bu nesne o memberı tutuyor.Hepsi vector dışında aliasing ctor ile hayata geldi. Bu da vectorun içindeki owner
                                                                // nesnesinin elemanını gösteren shared ptr hiçbir zaman dangling hale gelmeyecek. Aliasing ctor bunu sağlıyor.

    cout << "[7] svecptr.use_count() = " << svecptr.use_count() << "\n";
    cout << "[8] optr1.use_count() = " << owner_ptr1.use_count() << "\n";
    cout << "[9] owner_ptr2.use_count() = " << owner_ptr2.use_count() << "\n";
    cout << "[10] member_ptr.use_count() = " << member_ptr.use_count() << "\n";

    svecptr.reset();

    cout << "[11] svecptr.use_count() = " << svecptr.use_count() << "\n";
    cout << "[12] optr1.use_count() = " << owner_ptr1.use_count() << "\n";
    cout << "[13] owner_ptr2.use_count() = " << owner_ptr2.use_count() << "\n";
    cout << "[14] member_ptr.use_count() = " << member_ptr.use_count() << "\n";
    (void)getchar();
}

=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================

UNIQUE_PTR DEN SHARED PTR OLUŞTURMAK
------------------------------------

int main()
{
    auto up = make_unique<Triple>(1,2,3);

    shared_ptr<Triple> sptr(std::move(up));

    std::cout << (up ? "dolu" : "bos") <<"\n";
    
    if(sptr)
    {
        std::cout << *sptr << "\n";
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Bunun pratikteki önemi fabrika functionları

std::unique_ptr<Triple> make_triple(int a, int b, int c)
{
    return std::make_unique<Triple>(a,b,c);
}

int main()
{
    shared_ptr<Triple> sptr{make_triple(1,2,30)};

    auto p1 = sptr;
    auto p2 = sptr;
    auto p3 = sptr;

    std::cout << p3.use_count();
}

functionun return değerinin unique ptr olması bunu kullanamayacağımız anlamına gelmiyor.



=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================
=======================================================================================================================================================================================


BİR SONRAKİ DERS IOSTREAM LIBRARY GÖRÜLECEK.



*/
