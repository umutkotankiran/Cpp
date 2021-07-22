#pragma once

class Sentence {
public:
	Sentence(const char *p); //CTOR. DEFAULT DEĞİL
	Sentence(const Sentence& other); // COPY CTOR
	Sentence(Sentence&& other);	//MOVE CTOR
	Sentence& operator=(const Sentence& other); // COPY ASSIGNMENT
	Sentence& operator=(Sentence&& other); // MOVE ASSIGNMENT
	~Sentence(); // DESTRUCTOR
	void print()const;
	int lenght()const // // lenght i inline olarak yazıyoruz
	{
		return mlen;
	}
private:
	char* mp;
	size_t mlen;
};


/*
	KISACA SPECIAL MEMBER FUNC BİLDİRİMLERİ

	class A
	{
	public:
		A(); // DEFAULT CONSTRUCTOR
		~A(); // DESTRUCTOR
		A(const A&); // COPY CONSTRUCTOR
		A& operator=(const A&); // COPY ASSIGNMENT
		A(A&&); // MOVE CONSTRUCTOR
		A& operator=(A&&); // MOVE ASSIGNMENT
	};


*/