#pragma once

class Sentence {
public:
	Sentence(const char *p);
	Sentence(const Sentence& other);
	~Sentence();
	void print()const;
	int lenght()const // // lenght i inline olarak yazıyoruz
	{
		return mlen;
	}
private:
	char* mp;
	size_t mlen;
};