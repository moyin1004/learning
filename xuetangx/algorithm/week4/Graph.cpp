/*
描述
一个数列 a 称为合法的当且仅对于所有的位置 i, j（i < j ≤ n），都不存在一条从 aj 点连向 ai 的有向边。
现在有很多个有向无环图，请你判断每个图是否只存在唯一的合法数列。
输入
输入的第一行包含一个正整数 T ，表示数据组数。
对于每组数据，第一行包含两个正整数 n, m，表示图的节点个数和边数。
接下来 m 行，每行包含两个正整数 x, y（x, y ≤ n），表示这个图有一条从 x 到 y 的有向边。
保证没有自环和重边。
输出
输出 T 行，若所给的图存在唯一的合法数列，输出 1，否则输出 0。
样例1输入
2
3 2
1 2
2 3
3 2
1 2
1 3
样例1输出
1
0
样例1解释
第一个图只有一个合法数列：1、2、3；
第二个图有两个合法数列：1、2、3 或者 1、3、2。
样例2
请查看下发文件内的sample2_input.txt和sample2_output.txt。
限制
对于50%的数据，n, m ≤ 100；
对于100%的数据，T ≤ 100, n, m ≤ 10000。

提示
[本题就是判断一个有向无环图是否存在唯一的拓扑序列。]
[回忆一下求拓扑序列是如何做的：每一次都取一个入度为0的点，将这个点取出来放进拓扑序列里，然后将这个点连向的所有点的入度减去1。]
[可以发现，在“每一次都取一个入度为0”这一步，若入度为0的点数多于1个，则显然拓扑序不唯一。]
[因此按照这个拓扑序算法做一遍就好。]
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> Graph[n+1];
        int in[n+1] = {0};
        for (int i = 0; i < m; ++i) { // 建立入度
            int x, y;
            cin >> x >> y;
            Graph[x].push_back(y);
            ++in[y];
        }
        int pos = 0;
        bool flag = true;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) {
                if (pos != 0) {
                    cout << 0 << endl;
                    flag = false;
                    break;
                }
                pos = i;
            }
        }
        for (int i = 1; i <= n && flag; ++i) {
            int new_pos = 0;
            int size = Graph[pos].size();
            for (int j = 0; j < size; ++j) {
                int next = Graph[pos][j];
                --in[next];
                if (in[next] == 0) {
                    if (new_pos != 0) {
                        cout << 0 << endl;
                        flag = false;
                        break;
                    }
                    new_pos = next;
                }
            }
            pos = new_pos;
        }
        if (flag) cout << 1 << endl;
    }
    return 0;
}


