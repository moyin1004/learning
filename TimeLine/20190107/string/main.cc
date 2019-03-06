// @file    main.cc
/// @data    2019-01-08 11:11:14
 
#include "string.h"

#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
	String str1;
	str1.print();

	String str2 = "Hello,World";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4 = str3;
	str4.print();

	str4 = str2;
	str4.print();

	return 0;
}
