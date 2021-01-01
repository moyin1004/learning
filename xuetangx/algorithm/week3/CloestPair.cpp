/*
描述
给定n个二维平面上的点，求距离最近的一对点，输出他们的距离。
输入
第一行包含一个正整数n。
接下来n行，每行包含两个整数x,y，表示一个点的坐标。
输出
输出距离最近的一对点的距离，保留两位小数。
样例1输入
10
7 9
-8 -1
-3 -1
1 4
-3 9
6 -4
7 5
6 6
-6 10
0 8
1.41
样例1解释
距离最近的点为7和8，距离为√ (( 7 − 6 )^2 + ( 5 − 6 )^2) = √ 2 ≈ 1.41
限制
对于70%的数据，2 ≤ n ≤ 2000，每个点坐标的绝对值不超过10^5；
对于100%的数据，2 ≤ n ≤ 3×10^5，每个点坐标的绝对值不超过10^9。
提示
[分治求最近点对。当然也可以用kdtree，虽然应该会超时。]
*/

#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
using namespace std;

struct Point {
    double x;
    double y;
    friend bool operator<(Point &a, Point &b) {
        return a.x < b.x;
    }
};

const double inf = 1e20;

double cul_distance(Point &a, Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double solve(vector<Point> &a, int l, int r) {
    if (r - l <= 1) return inf;
    int mi = l + (r-l) / 2;
    double ans = min(solve(a, l, mi), solve(a, mi, r));
    for (int i = mi; i < r; ++i) {
        if (fabs(a[i].x - a[mi-1].x) > ans) {
            break;
        }
        for (int j = mi - 1; j >= l; --j) {
            if (fabs(a[i].x - a[j].x) > ans) {
                break;
            }
            ans = min(ans, cul_distance(a[i], a[j]));
        }
    }
    //cout << ans << " ";
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<Point> a;
    for (int i = 0; i < n; ++i) {
        Point point;
        cin >> point.x >> point.y;
        a.push_back(point);
    }
    sort(a.begin(), a.end());
    printf("%.2f\n", solve(a, 0, n));
}