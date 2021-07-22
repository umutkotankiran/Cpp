#ifndef DATE_H
#define DATE_H


class Date {
public:
	Date() : md{ 1 }, mm{ 1 }, my{ 1998 } {}  // açılan kapanan parantezlere dikkat :D:D
	Date(int d, int m, int y) : md{ d }, mm{ m }, my{ y } {}
	void set(int d, int m, int y)
	{	
		md = d;
		mm = m;
		my = y;
	}
	void print()const;
private:
	int md, mm, my;
};


#endif