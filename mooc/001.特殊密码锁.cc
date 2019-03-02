/// @file    001.特殊密码锁.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-02 21:35:31
 
#include <iostream>
 
using namespace std;

int getBit(int value, int i) {
    return (value >> i) & 1;
}

void setBit(int &value, int i) {
    value ^= (1 << i);
}

//枚举，当前的位置的状态与目标的同一位置不一致时，需要按下一位改变
int change(int current, int target, int length) {
    if (current == target) return 0;
    int count = 0;
    for (int i = 0; i < length - 2; ++i) {
        if (getBit(current, i) != getBit(target, i)) {
            ++count;
            setBit(current, i + 1);
            setBit(current, i + 2);
        }
    } 
    if (getBit(current, length - 2) != getBit(target, length - 2) &&
        getBit(current, length - 1) != getBit(target, length - 1))
    {    
        ++count;
    }
    else {
        return -1;
    }
    return count;
}

int main() {
    int current, target;
    current = target = 0;
    string str;
    cin >> str;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '1') setBit(current, i);
    }
    cin >> str;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '1') setBit(target, i);
    }
    int count = change(current, target, str.size());
    if (count == -1) cout << "impossible";
    else cout << count;
    return 0;
}
