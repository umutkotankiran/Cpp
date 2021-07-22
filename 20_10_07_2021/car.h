#pragma once

#include <iostream>

class Car {
public:
	Car()
	{
		std::cout << "Car Constructor\n";
		run();
	}
	virtual void start()
	{
		std::cout << "Car has just started\n";
	}
	virtual void run()
	{
		std::cout << "Car is running\n";
	}
	virtual void stop()
	{
		std::cout << "Car has stopped\n";
	}

	void maintain()
	{
		std::cout << "Araba bakima girdi calistiriliyor\n";
		start();
	}

	~Car() {
		std::cout << "Car Destructor\n";
	} //Birsonraki derste anlatılacak.
};


class Bmw : public Car {
public:
	virtual void start()override
	{
		std::cout << "BMW has just started\n";
	}
	virtual void run()override
	{
		std::cout << "BMW is running\n";
	}
	virtual void stop()override
	{
		std::cout << "BMW has stopped\n";
	}
};


class Audi : public Car {
public:
	virtual void start()override
	{
		std::cout << "Audi has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Audi is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Audi has stopped\n";
	}
};


class Mercedes : public Car {
public:
	virtual void start()override
	{
		std::cout << "Mercedes has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Mercedes is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Mercedes has stopped\n";
	}
};

class Fiat : public Car {
public:
	virtual void start()override
	{

		std::cout << "Fiat has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Fiat is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Fiat has stopped\n";
	}
};


class Fiat124 : public Fiat {
public:
	virtual void start()override
	{

		std::cout << "Fiat124 has just started\n";
	}
	/*virtual void run()override	// Bunu Eğer yorum satırı yaparsak Fiat un run functionu çalışır.
	{
		std::cout << "Fiat124 is running\n";
	}*/
	virtual void stop()override
	{
		std::cout << "Fiat124 has stopped\n";
	}
};

class Volvo : public Car {
public:
	virtual void start()override
	{

		std::cout << "Volvo has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Volvo is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Volvo has stopped\n";
	}
};

class Skoda : public Car {
public:
	virtual void start()override
	{

		std::cout << "Skoda has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Skoda is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Skoda has stopped\n";
	}
};

class Renault : public Car {
public:
	virtual void start()override
	{

		std::cout << "Renault has just started\n";
	}
	virtual void run()override
	{
		std::cout << "Renault is running\n";
	}
	virtual void stop()override
	{
		std::cout << "Renault has stopped\n";
	}
};

inline Car* create_random_car()
{
	switch (rand() % 8)
	{
	case 0: return new Bmw; // bunların hepsinde upcasting var.
	case 1: return new Mercedes;
	case 2: return new Audi;
	case 3: return new Fiat;
	case 4: return new Volvo;
	case 5: return new Fiat124;
	case 6: return new Renault;
	case 7: return new Skoda;
	}

	return nullptr;
}