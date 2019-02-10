/// @file    test.cc
/// @data    2019-01-20 15:07:44

#include "TextQuery.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
 
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::unique_ptr;
 
int main() {
    string queryWord("line");
    unique_ptr<ifstream, FileCloser> ifs(new ifstream("./china_daily.txt"));
    //ifstream ifs("./china_daily.txt");
    TextQuery tq(*ifs);
    QueryResult qr = tq.query(queryWord);
    qr.print();
    cout << endl;
    qr = tq.query("Wednesday");
    qr.print();
    cout << endl;
    qr = tq.query("The");
    qr.print();
    cout << endl;
    qr = tq.query("48");
    qr.print();
    cout << endl;

    return 0;
}
