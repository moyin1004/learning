/*
描述
有n个变量和m个“相等”或“不相等”的约束条件，请你判定是否存在一种赋值方案满足所有m个约束条件。
输入
第一行一个整数T，表示数据组数。
接下来会有T组数据，对于每组数据：
第一行是两个整数n,m，表示变量个数和约束条件的个数。
接下来m行，每行三个整数a,b,e，表示第a个变量和第b个变量的关系：
若e=0则表示第a个变量不等于第b个变量；
若e=1则表示第a个变量等于第b个变量
输出
输出T行，第i行表示第i组数据的答案。若第i组数据存在一种方案则输出"Yes"；否则输出"No"（不包括引号）。
输入样例1
2
5 5
1 2 1
2 3 1
3 4 1
1 4 1
2 5 0
3 3
1 2 1
2 3 1
1 3 0
输出样例1
Yes
No
样例1解释
一共有2组数据。
对于第一组数据，有5个约束：
变量1=变量2
变量2=变量3
变量3=变量4
变量1=变量4
变量2≠变量5
显然我们可以令：
变量1=变量2=变量3=变量4=任意一个数值
变量5=任意一个和变量2不同的数值
故第一组数据输出"Yes"。 对于第二组数据，有3个约束：
变量1=变量2
变量2=变量3
变量1≠变量3
由前两个约束可推出变量1=变量3，但第三个约束表明变量1≠变量3，矛盾。
故第二组数据输出"No"。
限制
对于10%的数据，n,m ≤ 5，T ≤ 5；
对于50%的数据，n,m ≤ 1000，T ≤ 10；
对于100%的数据，1 ≤ n ≤ 300000, m ≤ 500000，1 ≤ a,b ≤ n，T ≤ 100。
保证所有数据的n总和与m总和不超过500000。
*/

#include <cstring>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int Maxn = 300005;
// Union-find Sets Question
int Set[Maxn];

int getRoot(int pos) {
    int temp = pos;
    while (Set[pos] > 0) {
        pos = Set[pos];
    }
    if (temp != pos) {     // PathCompression
        Set[temp] = pos;
    }
    return pos;
}

void insert(int a, int b) {
    if (a == b) return ;
    int root_a = getRoot(a);
    int root_b = getRoot(b);
    if (Set[root_b] == 0) {
        Set[b] = root_a;
        --Set[root_a];
    }
    else if (Set[root_a] == 0) {
        Set[a] = root_b;
        --Set[root_b];
    }
    else if (root_a != root_b) {  // Heuristic Merge
        if (Set[root_a] > Set[root_b]) {
            Set[root_b] += Set[root_a];
            Set[root_a] = root_b;
            --Set[root_b];
        }
        else {
            Set[root_a] += Set[root_b];
            Set[root_b] = root_a;
            --Set[root_a];
        }
    }
}

bool check(int a, int b) {
    if (a == b) return false;
    if (getRoot(a) == getRoot(b)) return false;
    return true;
}

int main() {
    int T = 0;
    int n = 0, m = 0;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(Set, 0, sizeof(Set));  // 初始化集合
        vector<pair<int, int> > vec;
        bool flag = true;
        for (int i = 0; i < m; ++i) {
            int a, b, op;
            cin >> a >> b >> op;
            if (op == 1) {
                insert(a, b);  // 构造集合
            }
            else {
                if (!check(a, b)) {
                    flag = false;
                }
                vec.push_back(make_pair(a, b));
            }
        }
        int size = vec.size();
        // 如果有a，b在同一个集合，则输出No
        for (int i = 0; i < size && flag; ++i) {
            if (!check(vec[i].first, vec[i].second)) {
                flag = false;
                break;
            }
        }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}
