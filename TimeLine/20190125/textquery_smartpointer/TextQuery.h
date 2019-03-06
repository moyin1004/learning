/// @file    TestQuery.h
/// @data    2019-01-20 15:04:41

#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__
    
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>
using line_no = std::vector<std::string>::size_type;

class FileCloser {
public:
    void operator()(std::ifstream *ifs);
};

class QueryResult {
public:
    QueryResult(std::string s,
                size_t t,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f);
    void print();

private:
    std::string _sought;
    size_t _t;
    std::shared_ptr<std::set<line_no>> _lines;
    std::shared_ptr<std::vector<std::string>> _file;
};

class TextQuery {
public:
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &word) const;
private:
    std::shared_ptr<std::vector<std::string>> _file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> _wm;
    std::map<std::string, size_t> _dic;

    std::string preprocess(const std::string &word);
};

#endif
