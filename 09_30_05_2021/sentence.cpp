#define _CRT_SECURE_NO_WARNINGS
#include "sentence.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

Sentence::Sentence(const char* p) : mlen{ strlen(p) }
{
	mp = static_cast<char*>(malloc((mlen + 1) * sizeof(char)));
	if (!mp)
	{
		std::cout << "Bellek yetersiz\n";
		exit(EXIT_FAILURE);
	}
	std::cout << "Edinilen bellek blogunun adresi = " << static_cast<void*>(mp) << "\n";
	strcpy(mp, p);
}

void Sentence::print()const
{
	std::cout << "(" << mp << ")"<< "\n";
}

Sentence::~Sentence()
{
	std::cout << static_cast<void *>(mp) << " adresindeki blok free ediliyor\n";
	free(mp);
}

// lenght i inline olacak yazıyoruz


/* COMPILER COPY CTOR BU ŞEKİLDE.
Sentence::Sentence(const Sentence& other) : mp{ other.mp }, mlen{ other.mlen }
{
		//Derleyicinin yazdığı copy constructor bu şekilde olduğu için hata oluştu.
		// dümdüz copy yapıyor. biri free edilse yandık.
}
*/

Sentence::Sentence(const Sentence& other) : mlen{other.mlen}
{
	mp = reinterpret_cast<char*>(malloc((other.mlen + 1) * sizeof(char)));
	if (!mp)
	{
		std::cout << "bellek yetersiz\n";
		exit(EXIT_FAILURE);
	}

	std::cout << "Edinilen bellek blogu adresi = " << reinterpret_cast<void *>(mp) << "\n";
	strcpy(mp, other.mp);

}