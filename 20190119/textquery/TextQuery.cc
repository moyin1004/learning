/// @file    TestQuery.cc
/// @data    2019-01-20 15:04:33
 
#include "TextQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using std::regex;
using std::cout;
using std::endl;
using std::istringstream;
using std::ifstream;

void TextQuery::readFile(const string filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cout << "fstream open " << filename << " error" << endl;
        return ;
    }

    string line;
    string str;
    size_t line_num = 0;
    while (getline(ifs, line)) {
        ++line_num;
        _lines.push_back(line);
        istringstream iss(line);
        while (iss >> str) {
            str = preprocess(str);
            if (str == "\0") continue;
            auto it = _dic.find(str);
            if (it != _dic.end())
                ++it->second;
            else {
                _dic[str] = 1;
            }
            _word2Line[str].insert(line_num);
        }
    }
    ifs.close();
}

void TextQuery::query(const string &word) {
    auto it1 = _dic.find(word);
    auto it2 = _word2Line.find(word);
    cout << "--------------------------------------------------" << endl;
    if (it1 != _dic.end()) {
        cout << word << " occurs " << it1->second << " times." << endl;
        for (auto &line : it2->second) {
            cout << "   (line " << line << ")" << " " << _lines[line - 1] << endl;
        }
    }
    else
        cout << "Don't have this word \"" << word << "\"." << endl;
    cout << "--------------------------------------------------" << endl;
}

string TextQuery::preprocess(const string &word) {
    string s = "[0-9]|:|;|'|\\.|,|\"";  //处理字符串中的特殊字符
    string str;
    regex r(s);
    str = regex_replace(word, r, "\0");
    return str;
}
