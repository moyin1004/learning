/// @file    dictionary.cc
/// @data    2019-01-10 22:37:29

#include "dictionary.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::string;
using std::fstream;
using std::stringstream;
using std::cout;
using std::endl;
using std::setfill;
using std::setw;
using std::ios;

Dictionary  *Dictionary::_pInstance = nullptr;

Dictionary *Dictionary::getInstance() { 
    if(nullptr == _pInstance) {
        _pInstance = new Dictionary();
    }
    return _pInstance;
}

void Dictionary::destory() {
    if(_pInstance)
         delete _pInstance;
}

void Dictionary::read(const string &filename) {
    fstream fs(filename);
    if(!fs) {
        cout << "fstream open " << filename << " error" << endl;
        return ;
    }

    string str;
    while(fs >> str) {
        if(preprocess(str) == "\0") continue;
        auto it = _dic.find(str);
        if(it != _dic.end())
            ++it->second;
        else 
            _dic[str] = 1;
    }
    fs.close();
}

void Dictionary::store(const string &filename) {
    fstream fs(filename, ios::out); //写入模式，不追加
    if(!fs) {
        cout << "fstream open " << filename << " error" << endl;
        return ;
    }
    fs << "------------------------\n";

    for (auto it = _dic.begin(); it != _dic.end(); it++) {
        fs << "|" << setw(15) << setiosflags(ios::left)  << it->first
           << ": " << setw(5) << it->second  << "|\n";       //格式控制
    }
    fs << "------------------------\n";
    fs.close();
}

string Dictionary::preprocess(const string & word) {
    for (size_t idx = 0; idx != word.size(); ++idx) {
        if (!isalpha(word[idx])) {
            if (idx > 0)
                return word.substr(0, idx - 1);
            else
                return string();
        }
    }
    return word;
}
