/// @file    001.特殊密码锁.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-02 21:35:31
 
#include <iostream>
 
using namespace std;

bool getBit(int value, int i) {
    return (value >> i) & 1;
}

void setBit(int &value, int i) {
    value ^= (1 << i);
}

//枚举，当前的位置的状态与目标的同一位置不一致时，需要按下一位改变
//考虑边界调节。首位需要改变自己
int change(int current, int target, int length) {
    if (current == target) return 0;
    int cur = current;
    int count1 = 0;
    for (int i = 0; i < length; ++i) {
        if (getBit(cur, i) != getBit(target, i)) {
            if (i == 0) {
                setBit(cur, i);
                setBit(cur, i + 1);
                ++count1;
            }
            else if (i == length - 1) count1 = -1;
            else if (i == length - 2) {
                setBit(cur, i + 1);
                ++count1;
            }
            else {
                setBit(cur, i + 1);
                setBit(cur, i + 2);
                ++count1;
            }
        }
    }
    int count2 = 1;
    cur = current;
    setBit(cur, 0);
    setBit(cur, 1);
    for (int i = 0; i < length; ++i) {
        if (getBit(cur, i) != getBit(target, i)) {
            if (i == length - 1) count2 = -1;
            else if (i == length - 2) {
                setBit(cur, i + 1);
                ++count2;
            }
            else {
                setBit(cur, i + 1);
                setBit(cur, i + 2);
                ++count2;
            }
        }
    }
    if (count1 == -1 && count2 != -1) return count2;
    else if (count1 != -1 && count2 == -1) return count1;
    else if (count1 == -1 && count2 == -1) return -1;
    else return count1 > count2 ? count2 : count1;
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
