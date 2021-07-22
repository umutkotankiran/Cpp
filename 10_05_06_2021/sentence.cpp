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
	if(mp)
		free(mp);
}

// lenght i inline olacak yazıyoruz

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

Sentence& Sentence::operator=(const Sentence& other)
{
	if (this == &other) // self assignment  BUNU EKLEDİK. x = x yazılırsa, x free edilip kullanılıyor.UB oluşuyor.
		return *this;

	std::cout << reinterpret_cast<void *>(mp)<< " Adresindeki bellek blogu ilk olarak free edildi\n";
	std::free(mp);
	
	mlen = other.mlen; // bunu copy yapmakta sakınca yok.
	mp = reinterpret_cast<char *>(std::malloc((mlen + 1) * sizeof(char)));
	if (!mp)
	{
		std::cout << "Bellek yetersiz\n";
		exit(EXIT_SUCCESS);
	}
	
	std::cout << " Edinilen bellek blogu adresi = " << reinterpret_cast<void*>(mp) << "\n";
	strcpy(mp, other.mp);

	return *this;
}


Sentence::Sentence(Sentence&& other) : mp(other.mp), mlen(other.mlen)
{
	other.mp = nullptr;
}

Sentence& Sentence::operator=(Sentence&& other)
{
	if (this == &other)
		return *this;

	free(mp);
	mp = other.mp;
	mlen = other.mlen;

	other.mp = nullptr;   // çalındığı için nullptr a atanmış.
	
	return *this;
}