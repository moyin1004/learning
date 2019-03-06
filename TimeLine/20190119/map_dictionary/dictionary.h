/// @file    dictionary.h
/// @data    2019-01-10 22:32:28
 
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string>
#include <map>

using std::string;
using std::map;

class Dictionary {
public:
    static Dictionary *getInstance();
    static void destory();

    void read(const string &filename);
    void store(const string &filename);
private:
    static Dictionary *_pInstance;
    map<string, int> _dic;
    Dictionary(){};
    string preprocess(const string &word);
};

#endif
