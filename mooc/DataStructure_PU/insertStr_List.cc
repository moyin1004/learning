/// @file    insertStr_List.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-09-22 14:55:53

#include <iostream>
#include <string>

using namespace std;

int main() {
    string str, substr;
    cin >> str >> substr;
    int idx = str[0];
    for (size_t i = 1; i <= str.size(); i++) {
        if (str[i] > str[idx]) {
            idx = i;
        }
    }
    str.insert(idx + 1, substr);
    cout << str;
    return 0;
}
