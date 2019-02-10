/// @file    string.cc
/// @data    2019-01-07 23:32:01

#include "string.h"

#include <cstring>

#include <iostream>
 
using std::cout;
using std::endl;
 
String::String()
: _pstr(NULL) //;不加分号！！！！！！
{}

String::String(const char *pstr)
: _pstr(new char[strlen(pstr) + 1]())
{
	strcpy(_pstr, pstr);  //初始化列表只是开了空间
}

String::String(const String &rhs)
: _pstr(new char[strlen(rhs._pstr) + 1]())
{
	strcpy(_pstr, rhs._pstr);
}

String &String::operator=(const String &rhs) {
	if (this != &rhs) {//防止自复制
    	size_t len1 = strlen(rhs._pstr);
    	size_t len2 = strlen(_pstr);
    	if (len2 > len1)
    		strcpy(_pstr, rhs._pstr);
    	else{
    		delete []_pstr;
    		_pstr = new char[len1 + 1]();
    		strcpy(_pstr, rhs._pstr);
    	}
	}
    return *this;
}

String::~String() {
	if (_pstr != NULL) {
	    delete []_pstr;
    }	
	cout << "~String" << endl;
}

void String::print() const {
	if (_pstr == NULL)
		cout << "NULL" << endl;
	else
		cout << _pstr << endl;
}
