/// @file    03_02_DuplicationInArrayNoEdit.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-02 19:17:24
 
#include <iostream>
 
using namespace std;

int countRange(const int *numbers, int length, int start, int end) {
    if (numbers == nullptr) return -1;
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] >= start && numbers[i] <= end) {
            ++count;
        }
    }
    return count;
}

//时间复杂度 O(NlogN)
int duolicate(const int *numbers, int length) {
    if (numbers == nullptr || length <= 0) return -1;

    int left = 1, right = length - 1;
    while (right >= left) {
        int mid = left + ((right - left) >> 1);
        int count = countRange(numbers, length, left, mid);
        if (left == right) {
            if (count > 1) return left;
            else break;
        }
        if (count > mid - left + 1) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    int num[8] = {2, 3, 5, 4, 3, 2, 6, 7}; //{2, 3, 5, 4, 2, 6, 7} 不能找出重复
    int answer = duolicate(num, 8);
    cout << "ansewr = " << answer << endl;
}
