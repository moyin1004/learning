/// @file    computer.cc
/// @data    2019-01-07 22:04:45


#include "computer.h"

#include <cstdio>
#include <cstring>

#include <iostream>
 
using std::cout;
using std::endl;
 
Computer::Computer(const char *brand, float price)  //构造函数，初始化列表
: _brand(new char[strlen(brand) + 1]())
, _price(price)
{
	strcpy(_brand, brand);
	cout << "构造函数" << endl;
}

Computer::Computer(const Computer &rhs)  //深拷贝构造函数
: _brand(new char[strlen(rhs._brand) + 1]())
, _price(rhs._price)
{
	strcpy(_brand, rhs._brand);
	cout << "拷贝构造函数" << endl;
}

Computer::~Computer()     //析构函数
{
	delete [] _brand;
	cout << "~Couputer" << endl;
}

void Computer::setBrand(const char *brand) {
	size_t len1 = strlen(_brand);
	size_t len2 = strlen(brand);
	if(len1 > len2) {
		strcpy(_brand, brand);
		cout << _brand << endl;
	}
	else {
		delete []_brand;
		_brand = new char[len2 + 1]();
		strcmp(_brand, brand);
	}
}

void Computer::print() {
	printf("_brand: %p\n", _brand);
	cout << "brand: " << _brand << endl
		 << "price: " << _price << endl;
}
