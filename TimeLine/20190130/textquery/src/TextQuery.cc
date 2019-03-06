/// @file    TestQuery.cc
/// @data    2019-01-20 15:04:33
 
#include "TextQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <memory>

using std::regex;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::set;
using std::vector;
using std::istringstream;
using std::ifstream;
using std::unique_ptr;
using std::shared_ptr;

//函数对象实现资源的定制回收
void FileCloser::operator()(ifstream *ifs) {
    if(ifs)
        ifs->close();
    cout << "ifs.close()" << endl;
}

QueryResult::QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f)
: _sought(s)
, _lines(p)
, _file(f)
{}

void QueryResult::print() {
    cout << "--------------------------------------------------" << endl;
    cout << _sought << " occurs " << _lines->size()  << " times." << endl;
    for (auto &line : *_lines) {
        cout << "   (line " << line << ")" << " " << (*_file)[line - 1] << endl;
    }
    cout << "--------------------------------------------------" << endl;
}

shared_ptr<vector<string>> QueryResult::get_file() const {
    return _file;
}

QueryResult::line_it QueryResult::begin() const {
    return _lines->begin();
}

QueryResult::line_it QueryResult::end() const {
    return _lines->end();
}

TextQuery::TextQuery(ifstream &ifs)
: _file(new vector<string>)
{
    string line;
    string str;
    size_t line_num = 0;
    while (getline(ifs, line)) {
        ++line_num;
        _file->push_back(line);
        istringstream iss(line);
        while (iss >> str) {
            str = preprocess(str);
            if (str == "\0") continue;
            auto &lines = _wm[str];
            if(!lines) {
                lines.reset(new set<line_no>);
                lines->insert(line_num);
            }
            lines->insert(line_num);
        }
    }
}

QueryResult TextQuery::query(const string &sought) const {
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = _wm.find(sought);
    if (loc == _wm.end())
        return QueryResult(sought, nodata, _file);
    else
        return QueryResult(sought, loc->second, _file);
}

string TextQuery::preprocess(const string &word) {
    string s = "[0-9]|:|;|'|\\.|,|\"";  //处理字符串中的特殊字符
    string str;
    regex r(s);
    str = regex_replace(word, r, "\0");
    return str;
}
