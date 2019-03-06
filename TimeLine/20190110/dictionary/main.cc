/// @file    main.cc
/// @data    2019-01-11 22:35:09
 
#include "dictionary.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
    Dictionary *dic =  Dictionary::getInstance();
    dic->read("The_Holy_Bible.txt");
    dic->store("dictionary.txt");
    Dictionary::destory();
    return 0;
}
