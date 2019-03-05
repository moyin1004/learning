/// @file    05_ReplaceSpaces.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-04 20:48:30
 
#include <string.h>
#include <iostream>
 
using namespace std; 

//思路：从后往前进行插入O(N)
class Solution {
public:
    void replaceSpace(char *str, int length) {
        if (str == nullptr || length <= 0) return;
        int spaceNum = 0;
        int size = 0;
        while (str[size] != '\0') {
            if (str[size] == ' ') ++spaceNum;
            ++size;
        }
        int newsize = size + 1 + spaceNum * 2;
        if (newsize > length) return;
        for (int i = size; i >= 0; --i) {
            if (str[i] == ' ') {
                str[--newsize] = '0';
                str[--newsize] = '2';
                str[--newsize] = '%';
            }
            else {
                str[--newsize] = str[i]; //不能在if中--i直接移动字符 用else防止多个空格
            }
        }
    }
};

int main() {
    char str[20] = "We are happy";
    Solution sol;
    sol.replaceSpace(str, 20);
    cout << str << endl;
    return 0;
}
