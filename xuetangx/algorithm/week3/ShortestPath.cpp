/*
问题描述
给定一张 n 个点的无向带权图，节点的编号从 1 至 n，求从 S 到 T 的最短路径长度。
输入格式
第一行 4 个数 n,m,S, T，分别表示点数、边数、起点、终点。
接下来 m 行，每行 3 个正整数 u,v,w，描述一条 u 到 v 的双向边，边权为 w。
保证 1<=u,v<=n。
输出格式
输出一行一个整数，表示 S 到 T 的最短路。
样例输入
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
样例输出
7
数据范围
本题共设置 12 个测试点。
对于前 10 个测试点，保证 n<=2500，m<=6200，对于每条边有 w<=1000。这部分数据有梯度。
对于所有的 12 个测试点，保证 n<=100,000，m<=250,000。
*/

#include <iostream>
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

struct Edge {
    int v;
    int w;
    Edge(int v, int w) {
        this->v = v;
        this->w = w;
    }
};

typedef pair<int, int> pii;
typedef vector<Edge> Graph;

int shortest_path(vector<Graph> &graph, int S, int T, int n) {
    int mind[n+1];  // S到每个点的最短距离
    memset(mind, 127, sizeof(mind)); // 初始化一个较大的值
    mind[S] = 0;
    bool visit[n+1] = {0};
    priority_queue<pii, vector<pii>, greater<pii>> heap;
    heap.push(make_pair(0, S));
    while(!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if (!visit[u]) {  // 每个节点最多做一次松弛
            visit[u] = true;
            int size = graph[u].size();
            for (int i = 0; i < size; ++i) { // 遍历u连接的所有节点
                int w = graph[u][i].w, v = graph[u][i].v;
                if (mind[u] + w >= mind[v]) {
                    continue;
                }
                mind[v] = mind[u] + w;
                heap.push(make_pair(mind[v], v));
            }
        }
    }
    return mind[T];
}

int main() {
    int n, m, S, T;
    cin >> n >> m >> S >> T;
    vector<Graph> graph;
    graph.resize(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(Edge(v, w));
        graph[v].push_back(Edge(u, w));
    }
    cout << shortest_path(graph, S, T, n) << endl;
    return 0;
}
