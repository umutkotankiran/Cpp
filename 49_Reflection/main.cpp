C++26 Reflection
----------------
1: Motivasyon - Neden Reflection?
Şu ana kadar C++'ta bir tipin yapısını programatik olarak incelemek neredeyse imkansızdı. Düşün:
cppstruct Person {
    std::string name;
    int age;
    double salary;
};
Bu struct hakkında şu soruları compile-time'da cevaplayabilir miydik?

Kaç tane member'ı var?
Member'ların isimleri ne?
Member'ların tipleri ne?

Hayır. C++ tipi bir "black box" olarak görüyordu. Tek yapabildiğin sizeof(Person) ile toplam boyutunu almaktı.
Bu yüzden şu tür işler için hep manuel kod yazıyorduk:
// Enum to string - her enum için ayrı ayrı yazılıyor
const char* to_string(Color c) {
    switch(c) {
        case Color::red: return "red";
        case Color::green: return "green";
        case Color::blue: return "blue";
    }
    return "unknown";
}

// Serialization - her struct için ayrı ayrı yazılıyor
void to_json(const Person& p, JsonWriter& w) {
    w.write("name", p.name);
    w.write("age", p.age);
    w.write("salary", p.salary);
}
```

Her yeni enum'a, her yeni struct'a aynı boilerplate. Hata yapma olasılığı yüksek, bakımı zor.

**Reflection bunu çözüyor:** Artık compiler'a "bu tipin içinde ne var?" diye sorabiliyorsun.

------------------------------------------------------------------------------------------------------------------------

2: İki Dünya - Grammatical vs Reflection

Reflection'ı anlamak için iki "dünya" arasındaki geçişi kavramak lazım:
```
┌─────────────────────┐          ┌─────────────────────┐
│  GRAMMATICAL DOMAIN │          │  REFLECTION DOMAIN  │
│  (Normal C++ kodu)  │          │  (Metadata dünyası) │
│                     │    ^     │                     │
│  int, MyClass,      │ ───────► │  std::meta::info    │
│  fonksiyonlar,      │          │  değerleri          │
│  değişkenler        │ ◄─────── │                     │
│                     │  [::]    │                     │
└─────────────────────┘          └─────────────────────┘

- ^ operatörü: Grammatical → Reflection (kodu metadata'ya çevir)
- [::] splicer: Reflection → Grammatical (metadata'dan kod üret)

Ör:
constexpr auto r = ^int;      // int'i reflection dünyasına "kaldır"
typename[:r:] x = 42;         // reflection'dan geri "indir" → int x = 42;


Bu gidiş-geliş tek başına anlamsız görünüyor. Ama arada işlem yapabilme gücü var - işte reflection'ın değeri burada.

------------------------------------------------------------------------------------------------------------------------

3: ^ Operatörü Detaylı
^ operatörü bir C++ entity'sini alıp std::meta::info tipinde bir değer üretir.

Ne reflect edilebilir?
// Tipler
^int                      // primitive tip
^std::string              // class tip
^const int*               // compound tip

// Sınıflar ve üyeleri
^MyClass                  // class kendisi
^MyClass::member_var      // data member
^MyClass::member_func     // member function

// Fonksiyonlar
^free_function            // serbest fonksiyon
^std::sort                // template fonksiyon

// Değişkenler
^global_var               // global değişken
^MyClass::static_var      // static member

// Enum ve enumerator'lar
^Color                    // enum tipi
^Color::red               // enumerator

// Namespace'ler
^std                      // namespace
^::                       // global namespace

// Template'ler
^std::vector              // class template
^std::make_unique         // function template

Ne reflect edilemez (şu an için)?
// Expression'lar - gelecekte ^(expr) ile eklenecek
^(2 + 2)                  // HATA

// Constructor/Destructor - iterate edilebilir ama splice edilemez
^MyClass::MyClass         // HATA


Kritik nokta: ^ compile-time operatörü
constexpr auto r = ^int;  // OK - constexpr
auto r2 = ^int;           // OK - ama r2 constexpr değil, 
                          // bazı metafunction'larda kullanılamaz

Reflection değerleri constexpr veya consteval context'te en kullanışlı.

------------------------------------------------------------------------------------------------------------------------
  
4: std::meta::info Tipi
Bu opak (opaque) bir tip. İçini göremezsin, sadece metafunction'larla sorgularsın.
Temel özellikler

#include <meta>

// Default construct → null reflection
std::meta::info null_r{};
std::meta::info null_r2 = std::meta::info();

// Karşılaştırma
static_assert(^int == ^int);           // Aynı tip
static_assert(^int != ^const int);     // Farklı tipler
static_assert(^int != ^long);          // Farklı tipler

// Null kontrolü
static_assert(std::meta::info() != ^int);  // null ≠ valid
static_assert(std::meta::info() == std::meta::info());  // null == null

Alias davranışı
using Integer = int;

static_assert(^int != ^Integer);           // Farklı! Alias korunuyor
static_assert(dealias(^Integer) == ^int);  // dealias ile aynı

Bu önemli - reflection alias'ları korur. ^std::string ile ^std::basic_string<char> farklı.


------------------------------------------------------------------------------------------------------------------------

5: Splicer [::] Detaylı
Splicer, reflection değerini alıp geri koda dönüştürür. Kullanıldığı context'e göre farklı davranır.
Form 1: Genel Splicer [: r :]
Context'e göre otomatik davranır:

constexpr auto type_r = ^int;
constexpr auto var_r = ^some_global;
constexpr auto ns_r = ^std;

// Type context'te → tip üretir
[:type_r:] x = 42;                    // int x = 42;

// Expression context'te → expression üretir
int val = [:var_r:];                  // int val = some_global;

// Namespace context'te → namespace üretir
using namespace [:ns_r:];             // using namespace std; (yasak - aşağıda açıklayacağım)


------------------------------------------------------------------------------------------------------------------------

Form 2: Explicit Type Splicer typename[: r :]
Belirsizlik olduğunda tipi açıkça belirt:
template<std::meta::info R>
void foo() {
    // R dependent, compiler tip mi değişken mi bilmiyor
    typename[:R:] x;    // "Bu bir tip" diyorsun
}

Type-only context'lerde typename opsiyonel:
using MyType = [:^int:];              // OK, typename gereksiz
std::vector<[:^int:]> vec;            // OK, template arg type-only context


------------------------------------------------------------------------------------------------------------------------

Form 3: Template Splicer template[: r :]
Template isimleri için:
constexpr auto vec_template = ^std::vector;
template[:vec_template:]<int> my_vec;  // std::vector<int> my_vec;


------------------------------------------------------------------------------------------------------------------------

Form 4: Nested Name Specifier [:r:]:
Scope qualifier olarak:
constexpr auto class_r = ^MyClass;
[:class_r:]::static_member;           // MyClass::static_member


Member Access Splice
Bu çok güçlü:
struct S { int x; int y; };

consteval auto get_member(int n) {
    return std::meta::nonstatic_data_members_of(^S)[n];
}

S s{10, 20};
s.[:get_member(0):] = 100;   // s.x = 100;
s.[:get_member(1):] = 200;   // s.y = 200;


Normal member access'ten farkı:

İsim lookup yok
Access checking yok (private'a da erişebilirsin - dikkatli ol!)
Overload resolution yok

------------------------------------------------------------------------------------------------------------------------

6: Splicer Kısıtlamaları
Her yerde splice yapamazsın:
cpp// 1. Constructor splice - YASAK
constexpr auto ctor = // somehow get constructor;
[:ctor:](args);  // HATA - constructor splice edilemez

// 2. Namespace definition içinde - YASAK
namespace [:^std:] { }  // HATA

// 3. using directive'de dependent reflection - YASAK
template<std::meta::info R>
void foo() {
    using namespace [:R:];  // HATA - R dependent
}

// 4. Designated initializer'da - YASAK (şimdilik)
S s = {.[:member_r:] = 42};  // HATA - gelecekte eklenebilir

Ara Kontrol
Buraya kadar temel mekanizmayı anlattım:

^ ile kodu metadata'ya çeviriyorsun
std::meta::info bu metadata'yı tutuyor
[::] ile metadata'dan geri kod üretiyorsun


7: Metafunction'lar - Reflection'ın Kullanımı
Metafunction'lar std::meta namespace'inde tanımlı consteval fonksiyonlar. Bunlar compiler'ın iç bilgisine erişmeni sağlıyor.

7.1 Member Listeleme
En sık kullanacağın metafunction'lar bunlar:
#include <meta>

struct Person {
    std::string name;
    int age;
private:
    double salary;
public:
    static int count;
    void print() const;
};

// Tüm non-static data member'lar
constexpr auto members = std::meta::nonstatic_data_members_of(^Person);
// members[0] → name'in reflection'ı
// members[1] → age'in reflection'ı  
// members[2] → salary'nin reflection'ı (private olsa bile!)

// Static data member'lar
constexpr auto statics = std::meta::static_data_members_of(^Person);
// statics[0] → count'un reflection'ı

// Tüm üyeler (fonksiyonlar dahil)
constexpr auto all = std::meta::members_of(^Person);

Dönen tip std::vector<std::meta::info>. Evet, compile-time'da vector kullanılıyor - C++20'den beri constexpr allocation mümkün.

------------------------------------------------------------------------------------------------------------------------

7.2 Member Hakkında Bilgi Alma
Bir member'ın reflection'ını aldıktan sonra sorgulayabilirsin:

constexpr auto members = std::meta::nonstatic_data_members_of(^Person);
constexpr auto first = members[0];  // name

// İsmi al
constexpr auto isim = std::meta::name_of(first);  // "name"

// Tipini al (reflection olarak)
constexpr auto tip = std::meta::type_of(first);   // ^std::string

// Erişim belirleyici
constexpr bool pub = std::meta::is_public(first);     // true
constexpr bool priv = std::meta::is_private(first);   // false

// Layout bilgisi
constexpr auto boyut = std::meta::size_of(first);     // sizeof(std::string)
constexpr auto offset = std::meta::offset_of(first);  // 0 (ilk member)

------------------------------------------------------------------------------------------------------------------------

7.3 Enum Introspection
enum class Color { red = 1, green = 2, blue = 4 };

constexpr auto enumerators = std::meta::enumerators_of(^Color);
// enumerators[0] → red
// enumerators[1] → green
// enumerators[2] → blue

for (constexpr auto e : enumerators) {
    // std::meta::name_of(e) → "red", "green", "blue"
    // std::meta::extract<Color>(e) → Color::red, Color::green, Color::blue
}

------------------------------------------------------------------------------------------------------------------------

8: İlk Gerçek Örnek - Enum to String
Şimdi öğrendiklerimizi birleştirelim:

#include <meta>
#include <string>

template<typename E>
    requires std::is_enum_v<E>
constexpr std::string enum_to_string(E value) {
    // 1. E tipinin reflection'ını al
    // 2. Enumerator'larını listele
    // 3. Her birini kontrol et
    
    template for (constexpr auto e : std::meta::enumerators_of(^E)) {
        //         ↑                    ↑
        //    compile-time döngü    enum E'nin tüm değerleri
        
        if (value == [:e:]) {
            //         ↑
            //   reflection'dan gerçek değere dön
            
            return std::string(std::meta::name_of(e));
            //                        ↑
            //              enumerator'ın ismini al
        }
    }
    
    return "<unknown>";
}

// Kullanım
enum Color { red, green, blue };

static_assert(enum_to_string(Color::red) == "red");
static_assert(enum_to_string(Color::green) == "green");

Adım adım ne oluyor:

^E → Color tipinin reflection'ı
enumerators_of(^E) → {^red, ^green, ^blue} vector'ü
template for → compile-time'da 3 ayrı if bloğu üretir
[:e:] → reflection'dan gerçek enum değerine (örn: Color::red)
name_of(e) → string olarak isim ("red")

------------------------------------------------------------------------------------------------------------------------

Compiler açısından üretilen kod şuna benzer:
// template for açılmış hali (pseudo-code)
constexpr std::string enum_to_string(Color value) {
    if (value == Color::red) return "red";
    if (value == Color::green) return "green";
    if (value == Color::blue) return "blue";
    return "<unknown>";
}

------------------------------------------------------------------------------------------------------------------------

9: İkinci Örnek - Generic Struct Printer
Herhangi bir struct'ı yazdıran fonksiyon:

#include <meta>
#include <iostream>

template<typename T>
void print_struct(const T& obj) {
    std::cout << std::meta::name_of(^T) << " {\n";
    
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        std::cout << "  " 
                  << std::meta::name_of(member)      // member ismi
                  << " = " 
                  << obj.[:member:]                   // member değeri
                  << "\n";
    }
    
    std::cout << "}\n";
}

// Kullanım
struct Point { int x; int y; };
struct Person { std::string name; int age; };

Point p{10, 20};
print_struct(p);
// Çıktı:
// Point {
//   x = 10
//   y = 20
// }

Person per{"Ali", 30};
print_struct(per);
// Çıktı:
// Person {
//   name = Ali
//   age = 30
// }

------------------------------------------------------------------------------------------------------------------------

#include <meta>
#include <iostream>

template<typename T>
void print_struct(const T& obj) {
    std::cout << std::meta::name_of(^T) << " {\n";
    
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        std::cout << "  " 
                  << std::meta::name_of(member)      // member ismi
                  << " = " 
                  << obj.[:member:]                   // member değeri
                  << "\n";
    }
    
    std::cout << "}\n";
}

// Kullanım
struct Point { int x; int y; };
struct Person { std::string name; int age; };

Point p{10, 20};
print_struct(p);
// Çıktı:
// Point {
//   x = 10
//   y = 20
// }

Person per{"Ali", 30};
print_struct(per);
// Çıktı:
// Person {
//   name = Ali
//   age = 30
// }

Dikkat et: obj.[:member:] ile runtime'da member'a erişiyoruz, ama hangi member olduğu compile-time'da belirleniyor.

------------------------------------------------------------------------------------------------------------------------
    
Bölüm 9: İkinci Örnek - Generic Struct Printer
Herhangi bir struct'ı yazdıran fonksiyon:
#include <meta>
#include <iostream>

template<typename T>
void print_struct(const T& obj) {
    std::cout << std::meta::name_of(^T) << " {\n";
    
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        std::cout << "  " 
                  << std::meta::name_of(member)      // member ismi
                  << " = " 
                  << obj.[:member:]                   // member değeri
                  << "\n";
    }
    
    std::cout << "}\n";
}

// Kullanım
struct Point { int x; int y; };
struct Person { std::string name; int age; };

Point p{10, 20};
print_struct(p);
// Çıktı:
// Point {
//   x = 10
//   y = 20
// }

Person per{"Ali", 30};
print_struct(per);
// Çıktı:
// Person {
//   name = Ali
//   age = 30
// }

Dikkat et: obj.[:member:] ile runtime'da member'a erişiyoruz, ama hangi member olduğu compile-time'da belirleniyor.

------------------------------------------------------------------------------------------------------------------------

Bölüm 10: Değer Reflection'ı
Sadece tipler değil, değerler de reflect edilebilir:

// Değerden reflection
constexpr auto val_r = std::meta::reflect_value(42);

// Reflection'dan değer çıkarma
constexpr int val = std::meta::extract<int>(val_r);  // 42

// Obje reflection'ı
constexpr int arr[] = {1, 2, 3};
constexpr auto obj_r = std::meta::reflect_object(arr[1]);

// Template argument'lardan reflection
template<int N, const int& R> struct S {};
constexpr auto args = std::meta::template_arguments_of(^S<42, arr[0]>);
// args[0] → 42'nin value reflection'ı
// args[1] → arr[0]'ın object reflection'ı

Bu özellikle template metaprogramming'de önemli.

Ara Alıştırma
Şimdi sana bir görev: Aşağıdaki sum_members fonksiyonunu tamamla. Bu fonksiyon bir struct'ın tüm numeric member'larının toplamını döndürsün:

struct Stats {
    int a = 10;
    double b = 20.5;
    int c = 30;
};

template<typename T>
constexpr double sum_members(const T& obj) {
    double sum = 0.0;
    // ... burayı doldur
    return sum;
}

// Beklenen: sum_members(Stats{}) == 60.5

template for ve member splice kullanarak yaz. İpucu: önceki örneklere çok benziyor.

------------------------------------------------------------------------------------------------------------------------

11: Template İşlemleri
Reflection'ın güçlü yanlarından biri template'lerle çalışabilmesi.
Template'i ve Argümanlarını Alma

#include <meta>
#include <vector>
#include <map>

// std::vector<int> bir template specialization
constexpr auto vec_int = ^std::vector<int>;

// Hangi template'ten geldi?
constexpr auto vec_template = std::meta::template_of(vec_int);
static_assert(vec_template == ^std::vector);

// Template argümanları neler?
constexpr auto args = std::meta::template_arguments_of(vec_int);
// args[0] → ^int
// args[1] → ^std::allocator<int>  (default argüman)

static_assert(args[0] == ^int);

substitute: Template Instantiation
Compile-time'da template'i farklı argümanlarla instantiate edebilirsin:

#include <meta>
#include <vector>

// std::vector template'ini al
constexpr auto vec_tmpl = ^std::vector;

// double ile instantiate et
constexpr auto vec_double = std::meta::substitute(vec_tmpl, {^double});

// Artık vec_double == ^std::vector<double>
static_assert(vec_double == ^std::vector<double>);

// Bunu tip olarak kullan
typename[:vec_double:] my_vec;  // std::vector<double> my_vec;

Pratik Örnek: make_integer_sequence
Standart kütüphanedeki std::make_integer_sequence reflection ile çok daha basit yazılabilir:

#include <meta>
#include <utility>
#include <vector>

template<typename T>
consteval std::meta::info make_integer_seq_refl(T N) {
    std::vector<std::meta::info> args;
    args.push_back(^T);  // İlk argüman: tip
    
    for (T k = 0; k < N; ++k) {
        args.push_back(std::meta::reflect_value(k));  // Değerleri ekle
    }
    
    return std::meta::substitute(^std::integer_sequence, args);
}

template<typename T, T N>
using make_integer_sequence = [:make_integer_seq_refl<T>(N):];

// Kullanım
using seq = make_integer_sequence<int, 5>;
// seq = std::integer_sequence<int, 0, 1, 2, 3, 4>

Geleneksel TMP ile bu recursive template instantiation gerektiriyordu - çok yavaş ve karmaşık.

------------------------------------------------------------------------------------------------------------------------
    
Bölüm 12: Kod Üretimi - define_class
Bu reflection'ın en güçlü özelliklerinden biri: runtime'da değil, compile-time'da yeni tipler oluşturabilirsin.
Temel Kullanım
#include <meta>

struct MyType;  // Forward declaration - incomplete

// Tamamla
consteval void complete_my_type() {
    std::vector<std::meta::info> members;
    
    // int x; member'ı ekle
    members.push_back(
        std::meta::data_member_spec(^int, {.name = "x"})
    );
    
    // double y; member'ı ekle
    members.push_back(
        std::meta::data_member_spec(^double, {.name = "y"})
    );
    
    std::meta::define_class(^MyType, members);
}

// Çağır (compile-time'da çalışır)
static_assert((complete_my_type(), true));

// Artık MyType complete
MyType obj;
obj.x = 10;
obj.y = 3.14;


Tuple Implementasyonu
std::tuple normalde çok karmaşık TMP gerektirir. Reflection ile:
#include <meta>

template<typename... Ts>
struct Tuple {
    struct storage;  // Forward declare
    
    // storage'ı Ts... tiplerinde member'larla doldur
    static_assert(std::meta::is_type(
        std::meta::define_class(^storage, {
            std::meta::data_member_spec(^Ts)...
        })
    ));
    
    storage data;
    
    Tuple() : data{} {}
    Tuple(Ts const&... vs) : data{vs...} {}
};

// Kullanım
Tuple<int, double, std::string> t{42, 3.14, "hello"};
Geleneksel std::tuple implementasyonu yüzlerce satır recursive template. Bu birkaç satır.

    
------------------------------------------------------------------------------------------------------------------------
Bölüm 13: Serialization Örneği
Şimdi gerçek dünya problemi: JSON serialization.

#include <meta>
#include <string>
#include <sstream>

template<typename T>
std::string to_json(const T& obj) {
    std::ostringstream oss;
    oss << "{";
    
    bool first = true;
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        if (!first) oss << ", ";
        first = false;
        
        // "member_name": value
        oss << "\"" << std::meta::name_of(member) << "\": ";
        
        // Tip kontrolü ile farklı formatlama
        using MemberType = typename[:std::meta::type_of(member):];
        
        if constexpr (std::is_same_v<MemberType, std::string>) {
            oss << "\"" << obj.[:member:] << "\"";
        } else {
            oss << obj.[:member:];
        }
    }
    
    oss << "}";
    return oss.str();
}

// Kullanım
struct Person {
    std::string name;
    int age;
    double salary;
};

Person p{"Ali", 30, 50000.0};
std::cout << to_json(p);
// {"name": "Ali", "age": 30, "salary": 50000}

    
------------------------------------------------------------------------------------------------------------------------

Bölüm 14: Comparison Operators Otomatik Üretimi
C++20'de <=> geldi ama bazen daha fazla kontrol istiyorsun:

#include <meta>

template<typename T>
constexpr bool generic_equals(const T& a, const T& b) {
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        if (a.[:member:] != b.[:member:]) {
            return false;
        }
    }
    return true;
}

struct Point {
    int x;
    int y;
    int z;
};

Point p1{1, 2, 3};
Point p2{1, 2, 3};
Point p3{1, 2, 4};

static_assert(generic_equals(p1, p2));   // true
static_assert(!generic_equals(p1, p3));  // false


------------------------------------------------------------------------------------------------------------------------

Bölüm 15: Base Class Introspection
Kalıtım hiyerarşisini de inceleyebilirsin:

#include <meta>

struct Animal {
    std::string name;
};

struct Dog : Animal {
    int age;
};

// Base class'ları al
constexpr auto bases = std::meta::bases_of(^Dog);
// bases[0] → Animal'ın base class relationship'i

// Base class tipini al
constexpr auto base_type = std::meta::type_of(bases[0]);
static_assert(base_type == ^Animal);

// Public mi?
static_assert(std::meta::is_public(bases[0]));

---------------------------------------------------------------

Universal Formatter (Base + Member)
template<typename T>
void print_all(const T& obj) {
    std::cout << std::meta::name_of(^T) << " {\n";
    
    // Önce base class'ları
    template for (constexpr auto base : std::meta::bases_of(^T)) {
        using BaseType = typename[:std::meta::type_of(base):];
        std::cout << "  [base] ";
        print_all(static_cast<const BaseType&>(obj));
    }
    
    // Sonra kendi member'ları
    template for (constexpr auto mem : std::meta::nonstatic_data_members_of(^T)) {
        std::cout << "  " << std::meta::name_of(mem) 
                  << " = " << obj.[:mem:] << "\n";
    }
    
    std::cout << "}\n";
}

------------------------------------------------------------------------------------------------------------------------

Bölüm 16: Annotations
(Kullanıcı Tanımlı Metadata)Şimdiye kadar compiler'ın bildiği metadata'yı okuduk (isim, tip, erişim belirleyici).
Peki ya kendi metadata'mızı eklemek istersek?

Motivasyon
Düşün ki bir serialization kütüphanesi yazıyorsun:

cppstruct User {
    std::string username;
    std::string password;      // Bunu JSON'a yazmak istemiyorum!
    std::string email;
    int internal_id;           // Bunu da atla
};

Bazı member'ları "atla" diye işaretlemek istiyorsun. 
Geleneksel C++'ta bunu yapamazdın - ya manuel liste tutardın ya da naming convention kullanırdın (_internal_id gibi).

C++26 Annotation Syntaxcpp// Annotation tipi tanımla
enum class JsonPolicy { include, exclude };

struct User {
    std::string username;
    
    [[=JsonPolicy::exclude]]           // Annotation!
    std::string password;
    
    std::string email;
    
    [[=JsonPolicy::exclude]]
    int internal_id;
};

[[=value]] syntax'ı ile herhangi bir compile-time değeri annotation olarak ekleyebilirsin.


------------------------------------------------------------------------------------------------------------------------

Annotation'ları Okuma

#include <meta>
template<typename T>
std::string to_json_filtered(const T& obj) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        // Bu member'ın annotation'larını al
        constexpr auto annots = std::meta::annotations_of(member);
        
        // JsonPolicy::exclude var mı kontrol et
        constexpr bool should_exclude = []{
            for (auto a : annots) {
                if (std::meta::type_of(a) == ^JsonPolicy) {
                    if (std::meta::extract<JsonPolicy>(a) == JsonPolicy::exclude) {
                        return true;
                    }
                }
            }
            return false;
        }();
        
        if constexpr (should_exclude) {
            continue;  // Bu member'ı atla
        }
        
        if (!first) oss << ", ";
        first = false;
        
        oss << "\"" << std::meta::name_of(member) << "\": ";
        // ... değeri yaz
    }
    
    oss << "}";
    return oss.str();
}

------------------------------------------------------------------------------------------------------------------------

Daha Karmaşık Annotation'larAnnotation sadece enum olmak zorunda değil

Struct annotation
    
struct JsonName {
    const char* name;
};

struct Validate {
    int min;
    int max;
};

struct Person {
    [[=JsonName{"user_name"}]]        // JSON'da farklı isim
    std::string name;
    
    [[=Validate{0, 150}]]             // Değer aralığı
    int age;
    
    [[=JsonName{"e_mail"}, =Validate{.min=5, .max=100}]]  // Birden fazla
    std::string email;
};

Okuma:

template<typename T>
void validate(const T& obj) {
    template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
        // Validate annotation'ı ara
        constexpr auto validate_annot = []() -> std::optional<Validate> {
            for (auto a : std::meta::annotations_of(member)) {
                if (std::meta::type_of(a) == ^Validate) {
                    return std::meta::extract<Validate>(a);
                }
            }
            return std::nullopt;
        }();
        
        if constexpr (validate_annot.has_value()) {
            auto val = obj.[:member:];
            if (val < validate_annot->min || val > validate_annot->max) {
                throw std::runtime_error("Validation failed for " + 
                    std::string(std::meta::name_of(member)));
            }
        }
    }
}

------------------------------------------------------------------------------------------------------------------------

17: Hata Yönetimi

Reflection metafunction'ları hata durumunda ne yapar?
Mevcut Yaklaşım: Constant Expression Failure

constexpr auto r = ^int;
// int bir template specialization değil - ne olur?
constexpr auto tmpl = std::meta::template_of(r);  // HATA!
// Constant expression değerlendirmesi başarısız olur
```

Bu bir compile-time error üretir. Mesaj genelde şöyle:
```
error: call to 'template_of' is not a constant expression
note: 'int' does not reflect a template specialization

------------------------------------------------------------------------------------------------------------------------

Güvenli Kullanım Paterni

template<typename T>
void process() {
    constexpr auto r = ^T;
    
    // Önce kontrol et
    if constexpr (std::meta::is_class(r)) {
        // Güvenle member'lara eriş
        template for (constexpr auto m : std::meta::nonstatic_data_members_of(r)) {
            // ...
        }
    }
    
    // Template mi kontrol et
    if constexpr (std::meta::has_template_arguments(r)) {
        constexpr auto tmpl = std::meta::template_of(r);
        // ...
    }
}

------------------------------------------------------------------------------------------------------------------------

Gelecekte: constexpr Exceptions
constexpr auto get_template_safe(std::meta::info r) {
    try {
        return std::optional{std::meta::template_of(r)};
    } catch (...) {
        return std::nullopt;
    }
}

------------------------------------------------------------------------------------------------------------------------

Bölüm 18: ODR ve Linkage Konuları
template<std::meta::info R>
struct Wrapper {
    using type = [:R:];
};

Wrapper<^int> w;  // OK

Ama bir kısıtlama var: internal linkage.
template<std::meta::info R>
struct S {};

int x;
S<^x> s1;  // S<^x> has internal linkage

// Başka bir translation unit'te
// S<^x> FARKLI bir tip olabilir!

------------------------------------------------------------------------------------------------------------------------
Yapılamayan                                 Neden
Constructor splice                          Güvenlik ve tasarım karmaşıklığı
Expression reflection ^(2+2)                Henüz eklenmedi, gelecekte ^(expr) ile
Runtime reflection                          Tamamen compile-time, runtime tip bilgisi yok
Private member'a dışarıdan erişim           [:m:] ile erişebilirsin ama kötü pratik
Macro reflection                            Macro'lar preprocessing'de kayboluyor
Comment reflection                          Yorumlar derlenmeden önce siliniyor

============================================================================================================================
============================================================================================================================
============================================================================================================================
  

1.Reflection Operator: ^
Bir program entity'sinin reflection değerini üretir:

^::                    // Global namespace
^int                   // Tip
^MyClass               // Class
^MyClass::member       // Member (static veya non-static)
^my_function           // Fonksiyon
^my_variable           // Değişken
^MyEnum::value         // Enumerator
^MyNamespace           // Namespace
^my_template           // Template

Dönen tip: std::meta::info (opak, scalar tip)
Şu an için desteklenmeyen:

Expression reflection (^(expr) gelecekte eklenecek)
Constructor/destructor reflection (splice edilemiyor)

------------------------------------------------------------------------------------------------------------------------

2. Splicer: [: r :]

Reflection değerinden geri kod üretir. Dört formu var:

// 1. Genel splicer - context'e göre davranır
[: r :]              // Expression, type, veya namespace üretir

// 2. Type splicer
typename[: r :]      // Tip üretir (r bir tipin reflection'ı olmalı)

// 3. Template splicer  
template[: r :]      // Template ismi üretir

// 4. Nested-name-specifier splicer
[:r:]::              // Namespace/class qualifier üretir

Örnekler:
constexpr auto r = ^int;
typename[:r:] x = 42;           // int x = 42;
typename[:^char:] c = '*';      // char c = '*';

// Type-only context'te typename opsiyonel
using MyType = [:^int:];        // using MyType = int;

// Member access
struct S { int i; int j; };
S s;
s.[:^S::j:] = 42;               // s.j = 42;

------------------------------------------------------------------------------------------------------------------------

3. std::meta::info Tipi
  
namespace std::meta {
    using info = decltype(^::);  // Opak scalar tip
}


Özellikleri:
------------
- Default construct: null reflection
- Equality/inequality karşılaştırılabilir
- Sıralama yok (no ordering)
- Template argument olarak kullanılabilir (ama internal linkage zorunlu)

static_assert(^int == ^int);
static_assert(^int != ^const int);
static_assert(std::meta::info() == std::meta::info());  // null == null
static_assert(std::meta::info() != ^int);               // null != valid

------------------------------------------------------------------------------------------------------------------------

4. Metafunction'lar (std::meta namespace)
Hepsi consteval - sadece compile-time'da çalışır.

Name ve Location
std::meta::name_of(info r) -> std::string_view
std::meta::qualified_name_of(info r) -> std::string_view
std::meta::display_name_of(info r) -> std::string_view
std::meta::source_location_of(info r) -> std::source_location

Tür sorguları
std::meta::type_of(info r) -> info           // Member'ın tipini döndürür
std::meta::parent_of(info r) -> info         // Parent class/namespace
std::meta::dealias(info r) -> info           // Alias'ı çözer

Member Listeleme
std::meta::members_of(info class_type) -> vector<info>
std::meta::nonstatic_data_members_of(info class_type) -> vector<info>
std::meta::static_data_members_of(info class_type) -> vector<info>
std::meta::bases_of(info class_type) -> vector<info>
std::meta::enumerators_of(info enum_type) -> vector<info>

Template İşlemleri
std::meta::template_of(info r) -> info                    // Template'i al
std::meta::template_arguments_of(info r) -> vector<info>  // Argümanları al
std::meta::substitute(info tmpl, span<info> args) -> info // Instantiate et

Değer İşlemleri
std::meta::reflect_value(auto val) -> info     // Değerden reflection
std::meta::reflect_object(auto& obj) -> info   // Objeden reflection
std::meta::extract<T>(info r) -> T             // Reflection'dan değer çıkar
std::meta::value_of(info r) -> info            // Obje reflection → value reflection

Tür Kontrolleri
std::meta::is_public(info r) -> bool
std::meta::is_private(info r) -> bool
std::meta::is_protected(info r) -> bool
std::meta::is_virtual(info r) -> bool
std::meta::is_const(info r) -> bool
std::meta::is_static_member(info r) -> bool
std::meta::is_type(info r) -> bool
std::meta::is_class(info r) -> bool
std::meta::is_enum(info r) -> bool
std::meta::is_namespace(info r) -> bool
std::meta::is_template(info r) -> bool
std::meta::is_value(info r) -> bool
std::meta::is_object(info r) -> bool
std::meta::is_variable(info r) -> bool

Layout Bilgisi
std::meta::size_of(info r) -> size_t
std::meta::alignment_of(info r) -> size_t
std::meta::offset_of(info r) -> size_t    // Data member için

Kod Üretimi
std::meta::define_class(info class_type, span<info> members) -> info
std::meta::data_member_spec(info type, data_member_options opts) -> info

------------------------------------------------------------------------------------------------------------------------

5. template for (Expansion Statement)

template for (constexpr auto member : std::meta::nonstatic_data_members_of(^T)) {
    // Her iterasyon ayrı instantiation
    // member farklı reflection değerleri alır
}

Bu henüz tam implement edilmediği için şu workaround kullanılıyor:
[:expand(std::meta::enumerators_of(^E)):] >> [&]<auto e>{
    // e burada her enumerator için farklı değer
};
  
