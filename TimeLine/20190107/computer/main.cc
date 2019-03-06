/// @file    main.cc
/// @data    2019-01-07 22:32:18
 
#include "computer.h"

#include <iostream>
 
using std::cout;
using std::endl;
 

void test1() {
	Computer pc1("Lenovo", 8888);
	pc1.print();
	cout << endl;

	Computer *pc2 = new Computer("Macbook", 11111);
	pc2->print();

	delete pc2;
}
	
void test2() {
	Computer pc1("Thinkpad", 6666);
	cout << "pc1: " << endl;
	pc1.print();

	Computer pc2 = pc1;
	cout << "pc2: " << endl;
	pc2.print();

	cout << "修改pc1: " << endl;
	pc1.setBrand("xiaomi");
	cout << "pc1: " << endl;
	pc1.print();

	cout << endl << "pc2: " << endl;
	pc2.print();
}

int main() {
	test1();
	cout << endl;
	test2();
	return 0;
}
