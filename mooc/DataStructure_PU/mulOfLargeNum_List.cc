/// @file    mulOfLargeNum_List.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-09-22 15:13:53

#include <cstring>
#include <iostream>

using namespace std;

void reverse(char *data) {
    int size = strlen(data);
    for (int i = 0; i < size / 2; ++i) {
        swap(data[i], data[size - 1 - i]);
    }
}

void mulOfLagerNum(char *a, char *b, char *res) {
    int len1 = strlen(a);
    int len2 = strlen(b);
    reverse(a);
    reverse(b);
    int count = 0;
    char result[450];
    memset(result, '0', sizeof(result));
    for (int i = 0; i < len2; ++i) {
        int tmp1 = b[i] - '0';
        for (int j = 0; j < len1; ++j) {
            int tmp2 = a[j] - '0';
            int num = tmp1 * tmp2;
            result[j + i] += num % 10;       //原位
            count = j + i;
            int k = 0;
            while (result[j + i + k] > '9') {
                result[j + i + k] -= 10;
                result[j + i + k + 1] += 1;
                count = j + i + k + 1;
                ++k;
            }
            num /= 10;
            if (num != 0) {
                count = j + i + 1;
            }
            result[j + i + 1] += num;   //进位
            k = 1;
            while (result[j + i + k] > '9') {
                result[j + i + k] -= 10;
                result[j + i + k + 1] += 1;
                count = j + i + k + 1;
                ++k;
            }
        }
    }
    ++count;
    for (int i = 0; i < count; ++i) {
        res[i] = result[count - 1 - i];
    }
}

int main() {
    char a[201] = {0};
    char b[201] = {0};
    char res[450] = {0};
    scanf("%s %s", a, b);
    mulOfLagerNum(a, b, res);
    cout << res;
    return 0;
}
