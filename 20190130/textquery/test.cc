/// @file    test.cc
/// @data    2019-01-20 15:07:44

#include "TextQuery.h"
#include "Query.h"
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
    TextQuery tq(*ifs);

    Query query = ~Query("The") & Query("will") | Query("takeout");
    cout << query << endl;
    QueryResult qr = query.eval(tq);
    qr = query.eval(tq);
    qr.print();
    cout << endl;
    
    return 0;
}
