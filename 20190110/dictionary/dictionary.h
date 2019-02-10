/// @file    dictionary.h
/// @data    2019-01-10 22:32:28
 
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string>
#include <vector>

using std::vector;
using std::string;

class Word {
public:  
    string _word;
    int _num;
};

class Dictionary {
public:
    static Dictionary *getInstance();
    static void destory();
    static bool cmp(Word a, Word b);

    void read(const string &filename);
    void store(const string &filename);
private:
    static Dictionary *_pInstance;
    Dictionary(){};
    vector<Word> _dic;
};

#endif
