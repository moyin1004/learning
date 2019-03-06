/// @file    test.cc
/// @data    2019-01-20 15:07:44

#include "TextQuery.h"
#include <iostream>
#include <string>
 
using std::cout;
using std::endl;
using std::string;
 
int main() {
    string queryWord("line");
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    cout << endl;
    tq.query("Wednesday");
    cout << endl;
    tq.query("technology");
    cout << endl;
    tq.query("The");
    cout << endl;
    tq.query("48");
    cout << endl;
    tq.query("1");
    cout << endl;
    tq.query("Shenzhen-HK");
    cout << endl;

    return 0;
}
