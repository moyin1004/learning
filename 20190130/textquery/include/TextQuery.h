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

class FileCloser {
public:
    void operator()(std::ifstream *ifs);
};

class QueryResult {
public:
    using line_no = std::vector<std::string>::size_type;
    using line_it = std::set<line_no>::const_iterator;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f);
    void print();

    std::shared_ptr<std::vector<std::string>> get_file() const;
    line_it begin() const;
    line_it end() const;

private:
    std::string _sought;
    std::shared_ptr<std::set<line_no>> _lines;
    std::shared_ptr<std::vector<std::string>> _file;
};

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &word) const;

private:
    std::shared_ptr<std::vector<std::string>> _file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> _wm;

    std::string preprocess(const std::string &word);
};

#endif
