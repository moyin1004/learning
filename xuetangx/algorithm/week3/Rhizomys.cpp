/*
描述
竹鼠养殖场有若干个小房间，有很多条双向道路连接着它们。
值得注意的是，在养殖场中，连接两个房间的道路可能不止一条。由于路上能看到的风景不同，我们认为这两条路是不同的。
同时，也可能存在一条道路是从一个房间出发又回到它自身，但我们规定，从一个房间到它自己的最短距离为0。
为了不被吃掉，竹鼠们决定开始运动，运动的方式是从一个小房间经过若干个小房间（中间经过的房间数可以为0）走到另一个小房间。
但竹鼠们也希望在锻炼过程中尽可能地偷懒，这意味着，竹鼠运动的路线总是沿最短路的。
现在，竹鼠们希望知道从1号房间分别到其他所有房间的运动路线的种数。由于它们害怕会因为写代码而被吃掉，所以它们找到了你帮忙。
输入
第一行是两个整数 N,M，表示房间个数和连接房间的道路的条数。
接下来 m 行，每行三个整数 u,v,c，表示 u 号房间与v 号房间之间存在一条长度为c 的双向道路。
输出
输出 N 行，第 i 行表示从 1 号房间到 i 号房间的运动路径的种数，由于答案可能会很大，你只需要输出它模911814的结果。
当不存在任何一条从 1 号房间到i号房间的道路时，请输出 0。
输入样例1
6 12
2 1 2
4 2 2
1 6 2
5 6 1
3 6 1
5 6 2
6 4 2
1 5 2
5 2 1
2 1 2
4 4 2
6 5 2
输出样例1
1
2
1
3
1
1
样例1解释
以下用 Ei 表示输入中的第 i 条边。
到1的最短路长度为 0，只有1条。
到2的最短路长度为 2，有2条（ E1 ， E10 ）。
到3的最短路长度为 3，只有1条（ E3→E5 ）。
到4的最短路长度为 4，有3条（ E3→E7 ， E1→E2 ， E10→E2 ）。
到5的最短路长度为 2，只有1条（ E8 ）。
到6的最短路长度为 2，只有1条（ E3 ）。
限制
对于20%的数据，1≤n≤100,1≤m≤2000；
对于50%的数据，1≤n≤1000,1≤m≤150000；
对于100%的数据，1≤n≤20000,1≤m≤500000,1≤u,v≤n,1≤c≤10。
提示
[这道题统计最短路的数目，我们不妨考虑将所有处在最短路上的边提出来]
[提出这些边后形成了原图的一张子图，显然这张子图是不会有环的，否则与最短路的定义矛盾]
[既然没有环，那我们就可以愉快地做动态规划啦~]
[请同学们思考，如果使用dijkstra算法，需要先求最短路，再拓扑排序吗？]
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int MOD = 911814;
const int MAX = 20005;
struct Data {
    int u;
    int d;
    Data(int u, int d) : u(u), d(d) {}
    bool operator < (const Data &a) const {
        return d > a.d;
    }
};

priority_queue<Data> Q;
int d[MAX], f[MAX];
bool visited[MAX];

struct Edge {
    int v;
    int w;
    Edge(int v, int w) : v(v), w(w) {}
};
typedef vector<Edge> Graph;

void dijkstra(vector<Graph> &graph, int n) {
    memset(d, 127, sizeof(d)); // 初始化一个较大的值
    d[1] = 0;
    f[1] = 1;
    Q.push(Data(1, 0));
    while (!Q.empty()) {
        int u = Q.top().u;
        Q.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        int size = graph[u].size();
        for (int i = 0; i < size; ++i) { // 遍历u连接的所有节点
            int w = graph[u][i].w, v = graph[u][i].v;
            if (d[u] + w > d[v]) {
                continue;
            }
            if (d[u] + w == d[v]) {  // 更新路径数量
                f[v] = (f[v] + f[u]) % MOD;
            }
            else {
                d[v] = d[u] + w;
                f[v] = f[u];
                Q.push(Data(v, d[v]));
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Graph> graph;
    graph.resize(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(Edge(v, w));
        graph[v].push_back(Edge(u, w));
    }
    dijkstra(graph, n);
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", f[i]);
    }
    return 0;
}