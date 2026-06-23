#include <iostream>
#include <string>

using namespace std;

struct Record {
    string name;
    int product_code;
};

// 使用异或组合现有的hash函数
namespace std {
template <>
struct hash<Record> {
    size_t operator()(const Record& r) const {
        return hash<string>()(r.name) ^ hash<int>()(r.product_code);
    }
};
}  // namespace 