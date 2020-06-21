/*
题目描述
对输出进行格式化输出，是编程时经常碰到的一类问题。以浮点数为例，对这种数据类型的输出控制的常见要素有：
输出精度，即指定小数点后保留几位。
输出长度，即整体输出长度。
有许多表示格式化输出的方法。比如在C语言中，%a.bf表示输出一个浮点数（f是表示浮点数的占位符），其保留小数点后b位，
且输出长度不足a时，在左边补空格，补齐到a。当a位负数时，则表示左对齐（即在右边输出空格）。当输出长度超过a时，不进行任何操作。
比如，
printf("%10.2f", 1.23456) 将会输出######1.23。（为了方便观察，空格用#代替，但注意下面输入用的是星号）
printf("%-10.2f", 1.23456) 将会输出1.23######。（为了方便观察，空格用#代替，但注意下面输入用的是星号）
printf("%2.2f", 1) 将会输出1.00。
现在，给出一个格式化串，和一个输出结果，问输出结果是否符合格式化要求？
输入描述
输入两行。第一行为格式化字符串，第二行为输出结果。其中，所有的空格都用*代替。
输出描述
如果符合要求，则输出YES，否则，输出NO。
样例输入
%10.2f
****12.34
样例输出
NO
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    string str;
    string result;
    cin >> str >> result;
    int size = str.size();
    int count = 0, dec_count = 0;
    char format_c;
    vector<string> nums;
    if (!isdigit(str[1])) {
        format_c = str[1];
    }
    string temp;
    for (int i = 1; i < size; ++i) {
        if (isdigit(str[i])) {
            temp += str[i];
        }
        else if (!temp.empty()) {
            nums.push_back(temp);
            temp.clear();
        }
    }
    if (nums.size() > 0) {
        count = atoi(nums[0].c_str());
    }
    if (nums.size() > 1) {
        dec_count = atoi(nums[1].c_str());
    }

    int ret_size = result.size();
    int ret_count[3] = {0};  // space_count/integer_count/decimals_count
    if (ret_size < count ||  //total
        (format_c == '-' && result[0] == '*') ||  //alignment
        (format_c != '-' && result[ret_size - 1] == '*')) {
        cout << "NO" << endl;
        return 0;
    }
    int pos = 1;
    for (int i = 0; i < ret_size; ++i) {
        if (result[i] == '.') {
            pos = 2;
            continue;
        }
        if (isdigit(result[i])) {
            ++ret_count[pos];
        }
        else if (!isdigit(result[i])) {
            ++ret_count[0];
        }
    }
    if (dec_count != ret_count[2] ||
        (ret_size > count && ret_count[0] != 0)) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    return 0;
}
