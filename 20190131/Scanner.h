/// @file    Scanner.h
/// @data    2019-02-08 17:21:22
 
#ifndef __SCANNER_H__
#define __SCANNER_H__
    
#include <string>

class Scanner {
public:
    Scanner();
    void Accept();
    void Number();
    void SkipWhite();

private:
    std::string _buf;
    double _number;
    size_t _curPos;
};

#endif
