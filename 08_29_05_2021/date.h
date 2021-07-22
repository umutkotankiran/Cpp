#ifndef DATE_H
#define DATE_H


class Date {
public:
	Date(int, int, int);
	void set(int d, int m, int y);
	void print()const;
private:
	int md, mm, my;
};


#endif