///@file    computer.h
///@data    2019-01-07 21:48:53
 
#ifndef __COMPUTER_H__
#define __COMPUTER_H__

class Computer{
public:
	Computer(const char *brand, float price);

	Computer(const Computer &rhs);

	void print();

	~Computer();

	void setBrand(const char *brand);

private:
	char *_brand;
	float _price;
}; //这里要有分号！！！！！！！！

#endif
