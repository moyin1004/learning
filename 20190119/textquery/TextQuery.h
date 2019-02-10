/// @file    TestQuery.h
/// @data    2019-01-20 15:04:41

#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__
    
#include <string>
#include <set>
#include <map>
#include <vector>
using std::set;
using std::map;
using std::vector;
using std::string;

class TextQuery {
public:
    void readFile(const string filename);
    void query(const string &word);
private:
    vector<string> _lines;
    map<string, int> _dic;
    map<string, set<int>> _word2Line;

    string preprocess(const string &word);
};

#endif
