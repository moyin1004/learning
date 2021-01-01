/*
描述
有n个正整数排成一排，你要将这些数分成m份（同一份中的数字都是连续的，不能隔开），同时数字之和最大的那一份的数字之和尽量小。
输入
输入的第一行包含两个正整数n，m。
接下来一行包含n个正整数。
输出
输出一个数，表示最优方案中，数字之和最大的那一份的数字之和。
样例1输入
5 2
2 1 2 2 3
样例1输出
5
样例1解释
若分成2和1、2、2、3，则最大的那一份是1+2+2+3=8；
若分成2、1和2、2、3，则最大的那一份是2+2+3=7；
若分成2、1、2和2、3，则最大的那一份是2+1+2或者是2+3，都是5；
若分成2、1、2、2和3，则最大的那一份是2+1+2+2=7。
所以最优方案是第三种，答案为5。
限制
对于50%的数据，n ≤ 100，给出的n个正整数不超过10；
对于100%的数据，m ≤ n ≤ 300000，给出的n个正整数不超过1000000。
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool isDivid(vector<int> &vec, int m, long long d) {
    int count = 1;
    long long sum = 0;
    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        if (vec[i] > d) {
            return false;
        }
        sum += vec[i];
        if (sum > d) {
            ++count;
            sum = 0;
            --i;
        }
    }
    if (count > m) return false;
    else return true;
}

long long getAnswer(vector<int> &vec, int m, long long sum) {
    long long min = 1;
    long long max = sum;
    while (min <= max) {
        long long mid = min + (max - min) / 2;
        if (isDivid(vec, m, mid)) {
            max = mid - 1;
        }
        else {
            min = mid + 1;
        }
    }
    return max + 1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> vec;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        int temp;
        scanf("%d", &temp);
        sum += temp;
        vec.push_back(temp);
    }
    printf("%lld\n", getAnswer(vec, m, sum));
    return 0;
}
