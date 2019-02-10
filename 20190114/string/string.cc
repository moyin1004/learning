/// @file    string.cc
/// @data    2019-01-07 23:32:01

#include "string.h"
#include <cstring>
#include <iostream>
 
using std::cout;
using std::endl;
 
String::String()
: _pstr(nullptr)
{}

String::String(const char *pstr)
: _pstr(nullptr)
{
    if (pstr != nullptr) {
        _pstr = new char(strlen(pstr) + 1);
	    strcpy(_pstr, pstr);
    }
}

String::String(const String &rhs)
: _pstr(nullptr)
{
    if (rhs.size()) {
        _pstr = new char(rhs.size() + 1);
	    strcpy(_pstr, rhs._pstr);
    }
}

String &String::operator=(const String &rhs) {
	if (this != &rhs) {//防止自复制
        if (!rhs.size()) { //传入为空，赋空值
            delete _pstr;
            _pstr = nullptr;
            return *this;
        }
    	if (size() > rhs.size())
    		strcpy(_pstr, rhs._pstr);
    	else {
    		delete []_pstr;
    		_pstr = new char[rhs.size() + 1]();
    		strcpy(_pstr, rhs._pstr);
    	}
	}
    return *this;
}

String &String::operator=(const char *pstr) {
    if (pstr == nullptr) { //传入为空，赋空值
        delete _pstr;
        _pstr = nullptr;
        return *this;
    }
    size_t len1 = strlen(pstr);
    if (size() > len1) {
    	strcpy(_pstr, pstr);
    }
    else{
    	delete []_pstr;
    	_pstr = new char[len1 + 1]();
    	strcpy(_pstr, pstr);
    }
    return *this;                                       
}                                          
                                       
String &String::operator+=(const String &rhs) {
    *this = *this + rhs;
    return *this;
}

String &String::operator+=(const char *pstr) {
    *this = *this + pstr;
    return *this;
}

char &String::operator[](std::size_t index) { //C++容器中使用std::size_t更恰当
   if(index < size()) {
       return _pstr[index];
   }
   else {
       static char nullchar = '\0';
       return nullchar;
   }
}

const char &String::operator[](std::size_t index) const {
   if(index < size()) {
       return _pstr[index];
   }
   else {
       static char nullchar = '\0';
       return nullchar;
   }
}

std::size_t String::size() const {
    if (_pstr == nullptr)
        return 0;
    else
        return strlen(_pstr);
}

const char *String::c_str() const {
    return _pstr;
}

String::~String() {                        
	if (_pstr != nullptr) {                   
	    delete []_pstr;                
    }	                                   
}                                          
                                           
void String::print() const {           
	if (_pstr == nullptr)                     
		return;            
	else                                   
		cout << _pstr << endl;         
}                                          
                                           
bool operator==(const String &lhs, const String &rhs) {
    return !strcmp(lhs._pstr, rhs._pstr);
}

bool operator!=(const String &lhs, const String &rhs) {
    return strcmp(lhs._pstr, rhs._pstr);
}

bool operator<(const String &lhs, const String &rhs) {
    if (strcmp(lhs._pstr, rhs._pstr) < 0)
        return true;
    else
        return false;
}

bool operator>(const String &lhs, const String &rhs) {
    if (strcmp(lhs._pstr, rhs._pstr) > 0)
        return true;
    else
        return false;
}

bool operator<=(const String &lhs, const String &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const String &lhs, const String &rhs) {
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    if (s._pstr != nullptr)
        os << s._pstr;
    return os;
}

std::istream &operator>>(std::istream &is, String &s) {
    delete s._pstr;
    s._pstr = new char(is.tellg());
    is >> s._pstr;
    return is;
}

String operator+(const String &lhs, const String &rhs) {
    char *p = new char(lhs.size() + rhs.size() + 1);
    if (lhs.size())
        strcpy(p, lhs.c_str());
    if (rhs.size() && lhs.size())
        strcat(p, rhs.c_str());
    else if (rhs.size())
        strcpy(p, rhs.c_str());
    String str(p);
    delete p;
    return str;
}

String operator+(const String &lhs, const char *rhs) {
    String str(rhs);
    return lhs + str;
}

String operator+(const char *lhs, const String &rhs) {
    String str(lhs);
    return str + rhs;
}
