/// @file    learn.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2021-04-14 14:00:56

#include "learn.foo.pb.h"
#include <iostream>
using namespace std;

void printHex(string &result) {
    cout << "size: " << result.size() << endl;
    for (char c : result) {
        printf("%02x ", (uint8_t)c);
    }
    cout << endl;
}

void TestData() {
    cout << "------------Serialize------------" << endl;
    learn::foo::Data data;
    data.set_id(6);
    data.set_version(64);
    data.set_type(learn::foo::Type::PC);
    data.set_http("http://www.baidu.com");
    cout << "https: " << !data.https().empty() << endl;
    string result;
    data.SerializeToString(&result);
    printHex(result);

    cout << "------------unSerialize------------" << endl;
    learn::foo::Data unserialize;
    unserialize.ParseFromString(result);
    cout << "id: " << unserialize.id() << endl;
    cout << "version: " << unserialize.version() << endl;
    cout << "url: " << unserialize.http() << endl;

    /*
    id: 08 06
    version: 10 40
    http:
        tag = (3 << 3) | 2 = 1a
        len = 20
        data = http://www.baidu.com
        1a 14 68 74 74 70 3a 2f 2f 77 77 77 2e 62 61 69 64 75 2e 63 6f 6d
    type:
        tag = (7 << 3) | 0
        data = 2
        38 02
    */
}

void TestInt32() {
    learn::foo::Tint32 data;
    // 数据0，序列化之后为空，不存储
    data.set_n(0);
    string result;
    data.SerializeToString(&result);
    printHex(result);
}

int main() {
    TestData();
    TestInt32();
    return 0;
}