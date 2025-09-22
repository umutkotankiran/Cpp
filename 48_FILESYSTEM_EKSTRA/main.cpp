/*
C++ filesystem library, C++17 standardı ile birlikte dile resmi olarak dahil edilmiştir. 
Daha önce boost::filesystem olarak var olan bu kütüphane, dosya sistemi işlemlerini platform bağımsız bir şekilde gerçekleştirmeyi sağlar.
Bu kütüphane, farklı işletim sistemlerinin dosya sistemi farklılıklarını soyutlayarak, Windows, Linux, macOS gibi platformlarda aynı API 
ile çalışma imkanı sunar. Modern C++ uygulamalarında dosya ve dizin işlemleri için standart ve güvenli bir yol sağlar.

#include <filesystem>
namespace fs = std::filesystem; // Kısaltma kullanımı yaygındır

--------------------------------------------------------------------------------------------------------------------------------------------

Filesystem library'nin kalbi olan temel kavramlar, dosya sistemi işlemlerinin nasıl modelleneceğini belirler.
Bu bölümde path (yol) kavramı ve path manipülasyonu işlemlerini öğreneceğiz. Path nesneleri, dosya sistemi konumlarını temsil eden
ana abstraction'dır ve tüm filesystem işlemlerinin temelini oluşturur.

Path (Yol) Kavramı
Filesystem library'nin temelini std::filesystem::path sınıfı oluşturur.

fs::path p1 = "/home/user/document.txt";
fs::path p2 = R"(C:\Users\John\Desktop\file.txt)"; // Windows
fs::path p3 = "relative/path/file.txt";

--------------------------------------------------------------------------------------------------------------------------------------------

Path Manipülasyonu
------------------
fs::path p = "/home/user/documents/file.txt";

// Path bileşenleri
std::cout << p.root_name() << std::endl;        // "" (Unix) veya "C:" (Windows)
std::cout << p.root_directory() << std::endl;   // "/"
std::cout << p.root_path() << std::endl;        // "/" veya "C:\"
std::cout << p.relative_path() << std::endl;    // "home/user/documents/file.txt"
std::cout << p.parent_path() << std::endl;      // "/home/user/documents"
std::cout << p.filename() << std::endl;         // "file.txt"
std::cout << p.stem() << std::endl;             // "file"
std::cout << p.extension() << std::endl;        // ".txt"

--------------------------------------------------------------------------------------------------------------------------------------------

Path Birleştirme
----------------
cppfs::path base = "/home/user";
fs::path file = "documents/file.txt";
fs::path full = base / file; // "/home/user/documents/file.txt"

// Alternatif yöntem
fs::path combined = base;
combined /= file;

--------------------------------------------------------------------------------------------------------------------------------------------

Dosya ve Dizin Durumu Sorgulama
-------------------------------
Dosya sistemi işlemlerinde en temel ihtiyaçlardan biri, dosya ve dizinlerin var olup olmadığını ve türlerini kontrol etmektir. 
Bu bölümdeki fonksiyonlar, dosya sistem nesnelerinin durumunu sorgulamak için kullanılır. Bu işlemler genellikle diğer filesystem 
operasyonlarından önce güvenlik kontrolü amacıyla kullanılır.

exists() - Varlık Kontrolü
--------------------------
fs::path p = "example.txt";
if (fs::exists(p)) {
    std::cout << "Dosya mevcut" << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

is_* Fonksiyonları
------------------

fs::path p = "example";

if (fs::is_regular_file(p)) {
    std::cout << "Düzenli dosya" << std::endl;
}

if (fs::is_directory(p)) {
    std::cout << "Dizin" << std::endl;
}

if (fs::is_symlink(p)) {
    std::cout << "Sembolik link" << std::endl;
}

if (fs::is_block_file(p)) {
    std::cout << "Block cihaz dosyası" << std::endl;
}

if (fs::is_character_file(p)) {
    std::cout << "Karakter cihaz dosyası" << std::endl;
}

if (fs::is_fifo(p)) {
    std::cout << "FIFO/pipe" << std::endl;
}

if (fs::is_socket(p)) {
    std::cout << "Socket" << std::endl;
}

if (fs::is_empty(p)) {
    std::cout << "Boş dosya veya dizin" << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

file_status Kullanımı
---------------------

cppstd::error_code ec;
fs::file_status status = fs::status(p, ec);
if (!ec) {
    switch (status.type()) {
        case fs::file_type::regular:
            std::cout << "Düzenli dosya" << std::endl;
            break;
        case fs::file_type::directory:
            std::cout << "Dizin" << std::endl;
            break;
        case fs::file_type::symlink:
            std::cout << "Sembolik link" << std::endl;
            break;
        case fs::file_type::not_found:
            std::cout << "Bulunamadı" << std::endl;
            break;
        default:
            std::cout << "Diğer tip" << std::endl;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Dosya Boyutu ve Zaman Bilgileri
-------------------------------
Dosyaların metadata bilgileri, sistem yönetimi ve dosya analizi için kritik öneme sahiptir. Bu bölümde dosya boyutunu alma, son değişiklik
zamanını okuma ve değiştirme işlemlerini ele alacağız. Bu bilgiler backup sistemleri, 
senkronizasyon araçları ve dosya karşılaştırma uygulamaları için temeldir.

Dosya Boyutu
------------
cppfs::path p = "large_file.dat";
if (fs::exists(p) && fs::is_regular_file(p)) {
    std::uintmax_t size = fs::file_size(p);
    std::cout << "Dosya boyutu: " << size << " byte" << std::endl;
}

// Hata kontrolü ile
std::error_code ec;
std::uintmax_t size = fs::file_size(p, ec);
if (!ec) {
    std::cout << "Boyut: " << size << " byte" << std::endl;
} else {
    std::cout << "Hata: " << ec.message() << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Zaman Bilgileri
---------------
cppfs::path p = "example.txt";
if (fs::exists(p)) {
    auto write_time = fs::last_write_time(p);
    
    // time_t'ye dönüştürme (C++20 öncesi)
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        write_time - fs::file_time_type::clock::now() + 
        std::chrono::system_clock::now());
    std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
    
    std::cout << "Son değişiklik: " << std::ctime(&tt);
}

// Zaman değiştirme
auto new_time = fs::file_time_type::clock::now();
fs::last_write_time(p, new_time);

--------------------------------------------------------------------------------------------------------------------------------------------

Dizin İşlemleri
---------------
Dizin yapıları, dosya sisteminin organizasyonel temelini oluşturur. Bu bölümde dizin oluşturma, içerik listeleme ve dizin ağaçlarında gezinme
işlemlerini öğreneceğiz. Bu operasyonlar, dosya yöneticileri, backup sistemleri ve dosya analiz araçları için temel yapı taşlarıdır.

Dizin Oluşturma
---------------
cpp// Tek dizin oluşturma
fs::path dir = "new_directory";
if (fs::create_directory(dir)) {
    std::cout << "Dizin oluşturuldu" << std::endl;
}

// Çoklu dizin oluşturma (parent dizinler de oluşturulur)
fs::path deep_dir = "level1/level2/level3";
if (fs::create_directories(deep_dir)) {
    std::cout << "Dizin yapısı oluşturuldu" << std::endl;
}

// Hata kontrolü ile
std::error_code ec;
fs::create_directories(deep_dir, ec);
if (!ec) {
    std::cout << "Başarılı" << std::endl;
} else {
    std::cout << "Hata: " << ec.message() << std::endl;
}

Dizin İçeriğini Listeleme
-------------------------
cppfs::path dir = "/home/user";

// Basit listeleme
for (const auto& entry : fs::directory_iterator(dir)) {
    std::cout << entry.path() << std::endl;
}

// Detaylı listeleme
for (const auto& entry : fs::directory_iterator(dir)) {
    std::cout << entry.path().filename() << " - ";
    if (entry.is_regular_file()) {
        std::cout << "Dosya (" << fs::file_size(entry) << " byte)";
    } else if (entry.is_directory()) {
        std::cout << "Dizin";
    } else if (entry.is_symlink()) {
        std::cout << "Sembolik link";
    }
    std::cout << std::endl;
}

// Hata kontrolü ile
std::error_code ec;
for (const auto& entry : fs::directory_iterator(dir, ec)) {
    if (ec) {
        std::cout << "Hata: " << ec.message() << std::endl;
        break;
    }
    std::cout << entry.path() << std::endl;
}


Recursive Directory Iterator
----------------------------
cppfs::path root = "/home/user";

// Tüm alt dizinleri de dolaş
for (const auto& entry : fs::recursive_directory_iterator(root)) {
    std::cout << std::string(entry.depth() * 2, ' ') << entry.path().filename() << std::endl;
}

// Seçenekler ile
fs::recursive_directory_iterator iter(root, 
    fs::directory_options::skip_permission_denied);
for (const auto& entry : iter) {
    if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        std::cout << entry.path() << std::endl;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Dosya ve Dizin Kopyalama/Taşıma
-------------------------------
Dosya sistemi işlemlerinin en yaygın kullanım alanlarından biri, dosya ve dizinlerin kopyalanması ve taşınmasıdır.
Bu işlemler backup operasyonları, sistem migrasyonları ve dosya organizasyonu için kritiktir.
Bu bölümde güvenli kopyalama, taşıma ve yeniden adlandırma işlemlerini ele alacağız.

Dosya Kopyalama
---------------
cppfs::path source = "source.txt";
fs::path dest = "destination.txt";

// Basit kopyalama
try {
    fs::copy_file(source, dest);
    std::cout << "Dosya kopyalandı" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

// Seçenekler ile kopyalama
fs::copy_options opts = fs::copy_options::overwrite_existing | 
                        fs::copy_options::update_existing;
std::error_code ec;
bool result = fs::copy_file(source, dest, opts, ec);
if (result && !ec) {
    std::cout << "Başarılı" << std::endl;
}


Dizin Kopyalama
---------------
cppfs::path source_dir = "source_directory";
fs::path dest_dir = "destination_directory";

try {
    // Recursive kopyalama
    fs::copy(source_dir, dest_dir, fs::copy_options::recursive);
    std::cout << "Dizin kopyalandı" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}
Dosya/Dizin Taşıma ve Yeniden Adlandırma
cppfs::path old_path = "old_name.txt";
fs::path new_path = "new_name.txt";

try {
    fs::rename(old_path, new_path);
    std::cout << "Dosya taşındı/yeniden adlandırıldı" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

// Hata kontrolü ile
std::error_code ec;
fs::rename(old_path, new_path, ec);
if (!ec) {
    std::cout << "Başarılı" << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Dosya ve Dizin Silme
--------------------
Güvenli dosya silme işlemleri, sistem temizliği ve disk alanı yönetimi için gereklidir. 
Bu bölümde tekil dosya silme ve recursive dizin silme işlemlerini öğreneceğiz. 
Bu operasyonlar geri alınamaz olduğu için dikkatli hata kontrolü gerektirir.

Dosya Silme
-----------
cppfs::path file_to_remove = "unwanted.txt";

try {
    if (fs::remove(file_to_remove)) {
        std::cout << "Dosya silindi" << std::endl;
    } else {
        std::cout << "Dosya bulunamadı" << std::endl;
    }
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

Dizin Silme (Recursive)
-----------------------
cppfs::path dir_to_remove = "directory_to_delete";

try {
    std::uintmax_t removed_count = fs::remove_all(dir_to_remove);
    std::cout << removed_count << " öğe silindi" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------


Sembolik Link İşlemleri
-----------------------
Sembolik linkler, dosya sistemlerinde esneklik ve organizasyon sağlayan önemli yapılardır. 
Unix-like sistemlerde yaygın olan bu özellik, dosyalara ve dizinlere alternatif yollar oluşturmayı sağlar. 
Bu bölümde sembolik link oluşturma, okuma ve hard link işlemlerini ele alacağız.

Sembolik Link Oluşturma
-----------------------
cppfs::path target = "actual_file.txt";
fs::path link = "symbolic_link.txt";

try {
    fs::create_symlink(target, link);
    std::cout << "Sembolik link oluşturuldu" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

// Dizin için sembolik link
fs::create_directory_symlink("target_directory", "link_to_directory");
Sembolik Link Okuma
cppfs::path link = "symbolic_link.txt";

if (fs::is_symlink(link)) {
    fs::path target = fs::read_symlink(link);
    std::cout << "Link hedefi: " << target << std::endl;
    
    // Absolute path'e çevirme
    fs::path absolute_target = fs::absolute(target, link.parent_path());
    std::cout << "Mutlak hedef: " << absolute_target << std::endl;
}

Hard Link Oluşturma
-------------------
cppfs::path original = "original_file.txt";
fs::path hardlink = "hardlink_to_file.txt";

try {
    fs::create_hard_link(original, hardlink);
    std::cout << "Hard link oluşturuldu" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Path Dönüşümleri
----------------
Path dönüşümleri, farklı dosya sistemi konumları arasında ilişki kurma ve yol hesaplama işlemleri için kritiktir.
Bu bölümde relative ve absolute path dönüşümleri, canonical path hesaplama ve path'ler arası ilişki bulma işlemlerini öğreneceğiz.
Bu operasyonlar özellikle symlink çözümlemesi ve portable kod yazımı için önemlidir.

Absolute ve Canonical Path
--------------------------
cppfs::path relative = "documents/../pictures/photo.jpg";

// Mutlak yol
fs::path absolute = fs::absolute(relative);
std::cout << "Mutlak yol: " << absolute << std::endl;

// Canonical yol (sembolik linkler çözülür, . ve .. işlenir)
try {
    fs::path canonical = fs::canonical(relative);
    std::cout << "Canonical yol: " << canonical << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Dosya mevcut değil: " << ex.what() << std::endl;
}

// weakly_canonical (dosya mevcut olmasa da çalışır)
fs::path weakly_canon = fs::weakly_canonical(relative);
std::cout << "Weakly canonical: " << weakly_canon << std::endl;

Relative Path Hesaplama
-----------------------
cppfs::path from = "/home/user/documents";
fs::path to = "/home/user/pictures/photo.jpg";

fs::path relative_path = fs::relative(to, from);
std::cout << "Relative yol: " << relative_path << std::endl;
// Çıktı: "../pictures/photo.jpg"

--------------------------------------------------------------------------------------------------------------------------------------------

Proximity (Yakınlık) Hesaplama
------------------------------
cppfs::path p1 = "/a/b/c";
fs::path p2 = "/a/d/e";

fs::path relative = fs::proximate(p2, p1);
std::cout << "Proximate yol: " << relative << std::endl;

--------------------------------------------------------------------------------------------------------------------------------------------

Disk Alan Bilgileri
-------------------
Disk alanı yönetimi, sistem yönetimi ve uygulama performansı için kritik bir konudur. Bu bölümde disk kapasitesi,
kullanılabilir alan ve boş alan bilgilerini nasıl alabileceğinizi öğreneceğiz. 
Bu bilgiler backup operasyonları, log dosyası yönetimi ve sistem izleme uygulamaları için temeldir.

Space Info
----------
cppfs::path p = "/";  // Unix root veya "C:\\" Windows

try {
    fs::space_info si = fs::space(p);
    std::cout << "Toplam alan: " << si.capacity / (1024*1024*1024) << " GB" << std::endl;
    std::cout << "Boş alan: " << si.free / (1024*1024*1024) << " GB" << std::endl;
    std::cout << "Kullanılabilir alan: " << si.available / (1024*1024*1024) << " GB" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Dosya İzinleri (Permissions)
----------------------------
Dosya izinleri, sistem güvenliği ve erişim kontrolü için temel bir mekanizmadır. Unix-like sistemlerde yaygın olan bu özellik,
Windows'ta da desteklenir. Bu bölümde dosya izinlerini kontrol etme, değiştirme ve platform farklılıklarını yönetme konularını ele alacağız.

Permission Bit'leri ve Anlamları
--------------------------------
C++ filesystem library'de izinler bit flagler olarak temsil edilir:
cpp// fs::perms enum class değerleri
fs::perms::none           // 0000 - İzin yok
fs::perms::owner_read     // 0400 - Sahip okuma
fs::perms::owner_write    // 0200 - Sahip yazma  
fs::perms::owner_exec     // 0100 - Sahip çalıştırma
fs::perms::owner_all      // 0700 - Sahip tüm izinler

fs::perms::group_read     // 0040 - Grup okuma
fs::perms::group_write    // 0020 - Grup yazma
fs::perms::group_exec     // 0010 - Grup çalıştırma
fs::perms::group_all      // 0070 - Grup tüm izinler

fs::perms::others_read    // 0004 - Diğerleri okuma
fs::perms::others_write   // 0002 - Diğerleri yazma
fs::perms::others_exec    // 0001 - Diğerleri çalıştırma
fs::perms::others_all     // 0007 - Diğerleri tüm izinler

fs::perms::all            // 0777 - Herkes için tüm izinler

// Özel izinler
fs::perms::set_uid        // 4000 - Set User ID
fs::perms::set_gid        // 2000 - Set Group ID  
fs::perms::sticky_bit     // 1000 - Sticky bit

fs::perms::mask           // 7777 - Tüm izin bitleri
fs::perms::unknown        // Platform bağımlı
Permission Kontrolü ve Değişimi
cppfs::path file = "example.txt";

Mevcut izinleri görme
------------------------
fs::perms current_perms = fs::status(file).permissions();

// İzin kontrolü
if ((current_perms & fs::perms::owner_read) != fs::perms::none) {
    std::cout << "Sahip okuyabilir" << std::endl;
}

if ((current_perms & fs::perms::group_write) != fs::perms::none) {
    std::cout << "Grup yazabilir" << std::endl;
}

if ((current_perms & fs::perms::others_exec) != fs::perms::none) {
    std::cout << "Diğerleri çalıştırabilir" << std::endl;
}

İzin değiştirme
---------------
try {
    // Sahip için read/write, grup için read, diğerleri için izin yok
    fs::permissions(file, 
                   fs::perms::owner_read | fs::perms::owner_write | fs::perms::group_read,
                   fs::perm_options::replace);
    std::cout << "İzinler değiştirildi" << std::endl;
} catch (const fs::filesystem_error& ex) {
    std::cout << "Hata: " << ex.what() << std::endl;
}

İzin ekleme
-----------
fs::permissions(file, fs::perms::others_read, fs::perm_options::add);

İzin kaldırma  
-------------
fs::permissions(file, fs::perms::group_write, fs::perm_options::remove);

Permission Options (İzin Seçenekleri)
-------------------------------------
cpp// perm_options enum class
fs::perm_options::replace           // Mevcut izinleri değiştir
fs::perm_options::add              // İzin ekle (OR işlemi)
fs::perm_options::remove           // İzin kaldır (AND NOT işlemi)
fs::perm_options::nofollow         // Symlink'leri takip etme

// Örnek kullanım
fs::path file = "test.txt";

// Mevcut izinleri tamamen değiştir
fs::permissions(file, fs::perms::owner_all | fs::perms::group_read, 
                fs::perm_options::replace);

// Sadece execute izni ekle
fs::permissions(file, fs::perms::owner_exec, fs::perm_options::add);

// Group write iznini kaldır
fs::permissions(file, fs::perms::group_write, fs::perm_options::remove);

// Symlink için (link'in kendisinin iznini değiştir, hedefin değil)
fs::permissions(symlink_path, fs::perms::owner_read, 
                fs::perm_options::replace | fs::perm_options::nofollow);


--------------------------------------------------------------------------------------------------------------------------------------------

İzin Durumunu Yazdırma (Unix Tarzı)
-----------------------------------
cppstd::string permissions_to_string(fs::perms p) {
    std::string result;
    
    // Dosya türü (bu fonksiyon sadece izinleri gösteriyor)
    result += ((p & fs::perms::owner_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::owner_write) != fs::perms::none) ? "w" : "-";
    result += ((p & fs::perms::owner_exec) != fs::perms::none) ? "x" : "-";
    
    result += ((p & fs::perms::group_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::group_write) != fs::perms::none) ? "w" : "-";
    result += ((p & fs::perms::group_exec) != fs::perms::none) ? "x" : "-";
    
    result += ((p & fs::perms::others_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::others_write) != fs::perms::none) ? "w" : "-";
    result += ((p & fs::perms::others_exec) != fs::perms::none) ? "x" : "-";
    
    return result;
}

--------------------------------------------------------------------------------------------------------------------------------------------

// Gelişmiş versiyon (set_uid, set_gid, sticky_bit dahil)
std::string detailed_permissions_to_string(fs::perms p) {
    std::string result;
    
    // Owner permissions
    result += ((p & fs::perms::owner_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::owner_write) != fs::perms::none) ? "w" : "-";
    
    // Owner execute (set_uid kontrolü ile)
    if ((p & fs::perms::set_uid) != fs::perms::none) {
        result += ((p & fs::perms::owner_exec) != fs::perms::none) ? "s" : "S";
    } else {
        result += ((p & fs::perms::owner_exec) != fs::perms::none) ? "x" : "-";
    }
    
    // Group permissions
    result += ((p & fs::perms::group_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::group_write) != fs::perms::none) ? "w" : "-";
    
    // Group execute (set_gid kontrolü ile)
    if ((p & fs::perms::set_gid) != fs::perms::none) {
        result += ((p & fs::perms::group_exec) != fs::perms::none) ? "s" : "S";
    } else {
        result += ((p & fs::perms::group_exec) != fs::perms::none) ? "x" : "-";
    }
    
    // Others permissions
    result += ((p & fs::perms::others_read) != fs::perms::none) ? "r" : "-";
    result += ((p & fs::perms::others_write) != fs::perms::none) ? "w" : "-";
    
    // Others execute (sticky_bit kontrolü ile)
    if ((p & fs::perms::sticky_bit) != fs::perms::none) {
        result += ((p & fs::perms::others_exec) != fs::perms::none) ? "t" : "T";
    } else {
        result += ((p & fs::perms::others_exec) != fs::perms::none) ? "x" : "-";
    }
    
    return result;
}

// Kullanım örneği
fs::path file = "example.txt";
if (fs::exists(file)) {
    fs::perms p = fs::status(file).permissions();
    std::cout << "İzinler: " << permissions_to_string(p) << std::endl;
    std::cout << "Detaylı: " << detailed_permissions_to_string(p) << std::endl;
    
    // Octal gösterim
    auto octal_value = static_cast<unsigned>(p) & static_cast<unsigned>(fs::perms::mask);
    std::cout << "Octal: " << std::oct << octal_value << std::dec << std::endl;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Yaygın İzin Kalıpları
---------------------
cpp// Yaygın kullanılan izin kombinasyonları
namespace common_perms {
    // Dosyalar için
    constexpr fs::perms readable_file = fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read;
    constexpr fs::perms writable_file = fs::perms::owner_read | fs::perms::owner_write | fs::perms::group_read;
    constexpr fs::perms private_file = fs::perms::owner_read | fs::perms::owner_write;
    constexpr fs::perms executable_file = fs::perms::owner_read | fs::perms::owner_write | fs::perms::owner_exec | 
                                         fs::perms::group_read | fs::perms::group_exec | 
                                         fs::perms::others_read | fs::perms::others_exec;
    
    // Dizinler için
    constexpr fs::perms public_dir = fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec | 
                                    fs::perms::others_read | fs::perms::others_exec;
    constexpr fs::perms private_dir = fs::perms::owner_all;
    constexpr fs::perms shared_dir = fs::perms::owner_all | fs::perms::group_all;
}

// Kullanım
void set_common_permissions(const fs::path& file, bool is_executable = false) {
    try {
        if (fs::is_directory(file)) {
            fs::permissions(file, common_perms::public_dir, fs::perm_options::replace);
        } else if (is_executable) {
            fs::permissions(file, common_perms::executable_file, fs::perm_options::replace);
        } else {
            fs::permissions(file, common_perms::readable_file, fs::perm_options::replace);
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "İzin değiştirme hatası: " << ex.what() << std::endl;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Platform Farklılıkları
----------------------
cpp// Platform bağımlı izin kontrolü
bool check_permission_support() {
#ifdef _WIN32
    // Windows'ta izinler sınırlı desteklenir
    std::cout << "Windows: Sınırlı izin desteği" << std::endl;
    return false;
#else
    // Unix-like sistemlerde tam destek
    std::cout << "Unix-like: Tam izin desteği" << std::endl;
    return true;
#endif
}

// Platform bağımsız izin kontrolü
bool can_read_file(const fs::path& file) {
    std::error_code ec;
    fs::perms p = fs::status(file, ec).permissions();
    
    if (ec) {
        return false;
    }
    
#ifdef _WIN32
    // Windows'ta daha basit kontrol
    return fs::exists(file) && fs::is_regular_file(file);
#else
    // Unix'te detaylı izin kontrolü
    return (p & fs::perms::owner_read) != fs::perms::none ||
           (p & fs::perms::group_read) != fs::perms::none ||
           (p & fs::perms::others_read) != fs::perms::none;
#endif
}

--------------------------------------------------------------------------------------------------------------------------------------------

Güvenli izin değiştirme (platform farkını göz önünde bulundurarak)
---------------------------------------------------------------------
bool safe_set_permissions(const fs::path& file, fs::perms new_perms) {
    std::error_code ec;
    
#ifdef _WIN32
    // Windows'ta sadece read-only attribute'unu değiştirebiliriz
    bool read_only = (new_perms & fs::perms::owner_write) == fs::perms::none;
    
    // Windows API kullanarak read-only set etme (basitleştirilmiş)
    if (read_only) {
        fs::permissions(file, fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read, 
                       fs::perm_options::replace, ec);
    } else {
        fs::permissions(file, fs::perms::owner_all | fs::perms::group_read | fs::perms::others_read, 
                       fs::perm_options::replace, ec);
    }
#else
    // Unix'te doğrudan izin set etme
    fs::permissions(file, new_perms, fs::perm_options::replace, ec);
#endif
    
    return !ec;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Özel İzin Bitleri (Unix)
------------------------
cpp// Set-UID, Set-GID ve Sticky Bit kullanımı
void demonstrate_special_permissions() {
    fs::path executable = "special_program";
    
    try {
        // Set-UID bit (program çalışırken owner'ın izinleriyle çalışır)
        fs::permissions(executable, 
                       fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec | 
                       fs::perms::others_read | fs::perms::others_exec | fs::perms::set_uid,
                       fs::perm_options::replace);
        
        // Set-GID bit (program çalışırken group'un izinleriyle çalışır)
        fs::permissions(executable, 
                       fs::perms::owner_all | fs::perms::group_all | 
                       fs::perms::others_read | fs::perms::others_exec | fs::perms::set_gid,
                       fs::perm_options::replace);
        
        // Sticky bit (sadece owner silebilir, genellikle /tmp için kullanılır)
        fs::path temp_dir = "/tmp/shared_directory";
        if (fs::exists(temp_dir) && fs::is_directory(temp_dir)) {
            fs::permissions(temp_dir,
                           fs::perms::all | fs::perms::sticky_bit,
                           fs::perm_options::replace);
        }
        
    } catch (const fs::filesystem_error& ex) {
        std::cout << "Özel izin hatası: " << ex.what() << std::endl;
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

İzin bitlerini kontrol etme
------------------------------
void check_special_bits(const fs::path& file) {
    if (!fs::exists(file)) return;
    
    fs::perms p = fs::status(file).permissions();
    
    if ((p & fs::perms::set_uid) != fs::perms::none) {
        std::cout << file << " Set-UID bit'i var" << std::endl;
    }
    
    if ((p & fs::perms::set_gid) != fs::perms::none) {
        std::cout << file << " Set-GID bit'i var" << std::endl;
    }
    
    if ((p & fs::perms::sticky_bit) != fs::perms::none) {
        std::cout << file << " Sticky bit'i var" << std::endl;
    }
}


















*/
