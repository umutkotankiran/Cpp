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
  
