/// @file    main.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2025-05-14 23:06:58

#include <bsoncxx/json.hpp>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>

using std::cout;
using std::endl;

// g++ main.cc $(pkg-config --cflags --libs libmongocxx)

int main() {
    mongocxx::instance inst{};
    mongocxx::v_noabi::options::client client_options;
    mongocxx::v_noabi::options::pool options;
    mongocxx::pool pool{mongocxx::uri{"mongodb://127.0.0.1:27017"}};
    mongocxx::uri uri("mongodb://127.0.0.1:27017");
    mongocxx::client client(uri);
    auto col = client.database("test").collection("testcol");
    auto ret = col.find({});
    for (auto doc : ret) {
        cout << bsoncxx::to_json(doc) << endl;
    }
}
