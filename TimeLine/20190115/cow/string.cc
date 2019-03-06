/// @file    string.cc
/// @data    2019-01-07 23:32:01

#include "string.h"
#include <cstring>
#include <iostream>
 
using std::cout;
using std::endl;

int String::refcount() const {
    return *(int*)(_pstr - 4);
}

void String::initRefcount() {
    *(int*)(_pstr - 4) = 1;
}

void String::increaseRefcount() {
    ++*(int*)(_pstr - 4);
}

void String::decreaseRefcount() {
    --*(int*)(_pstr - 4);
}

void String::release() {
    decreaseRefcount();
    if(refcount() == 0) {
        delete [](_pstr - 4);
        cout << "delete heap data" << endl;
    }
}

String::String()
: _pstr(new char[5]() + 4)
{
    initRefcount();
}

String::String(const char *pstr)
: _pstr(new char[strlen(pstr) + 5]() + 4)
{
    initRefcount();
	strcpy(_pstr, pstr);
}

String::String(const String &rhs)
: _pstr(rhs._pstr)
{
    increaseRefcount();
    cout << "String(const String &)" << endl;
}

String &String::operator=(const String &rhs) {
    cout << "String &operator=(const String &)" << endl;
	if (this != &rhs) {//防止自复制
        release();
        _pstr = rhs._pstr;
        increaseRefcount();
	}
    return *this;
}

String &String::operator=(const char *pstr) {
    release();
    _pstr = new char[strlen(pstr) + 5]() + 4;
    strcpy(_pstr, pstr);
    initRefcount();
    return *this;                                       
}                                          
                                       
//Strcow &Strcow::operator=(const char c) {
//   if (_pc) {
//       if (_str->refcount() > 1) {
//           char *ptpm = new char[_str->size() + 5] + 4;
//           strcpy(ptpm, _str->_pstr);
//           _str->decreaseRefcount();
//           _str->_pstr = ptpm;
//           _str->initRefcount();
//           _str->_pstr[pc_change] = c;
//       }
//   }
//   return *this;
//}

String::CharProxy::CharProxy(String &self, std::size_t idx)
: _self(self)
, _idx(idx)
{}

//等式返回char& 可继续赋值
char &String::CharProxy::operator=(const char &c) {
    if (_idx < _self.size()) {
        char *ptpm = new char[_self.size() + 5]() + 4;
        strcpy(ptpm, _self._pstr);
        _self.decreaseRefcount();
        _self._pstr = ptpm;
        _self.initRefcount();
        _self._pstr[_idx] = c;
        return _self._pstr[_idx];
    }
    else {
        static char nullchar = '\0';
        return nullchar;
    }
}

String::CharProxy::operator char() {
    return _self._pstr[_idx];
}
//Strcow &String::operator[](std::size_t index) { //C++容器中使用std::size_t更恰当
//    if (index < size()) {
//        _cow._pc = &_pstr[index];
//        _cow.pc_change = index;
//        _cow._str = this;
//    }
//    return _cow;
//}

String::CharProxy String::operator[](std::size_t index) { //C++容器中使用std::size_t更恰当
    return CharProxy(*this, index);
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
    release(); //refcount != 0; 不能delete，会delete其他对象的空间
}                                          
                                           
void String::print() const {           
	if (_pstr == nullptr)                     
		return;            
	else                                   
		cout << _pstr << endl;         
}                                          

std::ostream &operator<<(std::ostream &os, const String &s) {
    if (s._pstr != nullptr)
        os << s._pstr;
    return os;
}

//std::ostream &operator<<(std::ostream &os, const Strcow &c) {
//    os << *(c._pc);
//    return os;
//}

std::istream &operator>>(std::istream &is, String &s) {
    s.release();
    int loc = is.tellg();
    s._pstr = new char[loc + 5]() - 4;
    s.initRefcount();
    is >> s._pstr;
    return is;
}
