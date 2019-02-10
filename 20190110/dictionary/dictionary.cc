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
using std::sort; 
using std::setfill;
using std::setw;
using std::ios;

Dictionary  *Dictionary::_pInstance = nullptr;

bool Dictionary::cmp(Word a, Word b) {
    return a._word < b._word;
}

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
    Word word;
    fs >> str;
    word._word = str;
    word._num = 1;
    _dic.push_back(word);
    while(fs >> str) {
        size_t temp = _dic.size();
        if(str >= "1" && str <= "9999") continue; //字符串是逐字符比较
        for (size_t i = 0; i < temp; i++) {    //用迭代器会出错，else内压入内容了，容器大小变了
            if(_dic[i]._word == str) {
                _dic[i]._num++;
                break;
            }
            else if(i == temp - 1) {
                word._word = str;
                word._num = 1;
                _dic.push_back(word);
            }
        }
    }
    fs.close();
}

void Dictionary::store(const string &filename) {
    sort(_dic.begin(), _dic.end(), cmp);
    fstream fs(filename, ios::out); //写入模式，不追加
    if(!fs) {
        cout << "fstream open " << filename << " error" << endl;
        return ;
    }
    fs << "------------------------\n";

    for (vector<Word>::iterator it = _dic.begin(); it != _dic.end(); it++) {
        fs << "|" << setw(15) << setiosflags(ios::left)  << it->_word
           << ": " << setw(5) << it->_num  << "|\n";       //格式控制
    }
    fs << "------------------------\n";
    fs.close();
}
