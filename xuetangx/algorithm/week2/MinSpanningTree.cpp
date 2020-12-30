/*
描述
给定一个 n 个点 m 条边的无向图，求一个恰好包含了 k 条关键边的最小生成树。
注意，先满足这棵生成树恰好有 k
条关键边，再满足整棵生成树所有边（包括关键边和非关键边）的权值之和最小。 输入
第一行为三个整数 n,m,k。
接下来 m 行，每行四个整数 x,y,w,t 描述一条边，表示无向边的两个端点为 x 和
y(x≠y)，权值为 w(1≤w≤10000)， 若 t=1 则表示该条边为关键边，否则 t=0。 输出
输出满足条件的最小生成树的权值之和。保证至少存在一棵含有 k 条关键边的生成树。
样例1输入
4 1 3 0
1 2 7 1
4 3 8 0
1 3 1 1
2 1 5 0
2 4 5 1
4 6 2
样例1输出
9
样例1解释
蓝色的为关键边，打红勾的表示满足条件的最小生成树。
限制
其中 30% 的数据，20≤m,8≤n；
另外 30% 的数据，边全为关键边；
对于 100% 的数据，100000≤m,50000≤n。
保证无重边（关键边和非关键边分开算），无自环。
*/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// 并查集
vector<int> Set;

int getRoot(int pos) {
    int root = pos;
    while (Set[root] > 0) {
        root = Set[root];
    }
    if (root != pos) { // PathCompression
        Set[pos] = root;
    }
    return root;
}

void merge(int a, int b) {
    if (a == b) return ;
    int root_a = getRoot(a);
    int root_b = getRoot(b);
    if (root_a == root_b) return ;
    // Heuristic Merge
    if (Set[root_a] < Set[root_b]) swap(root_a, root_b);
    Set[root_b] += Set[root_a] - 1;
    Set[root_a] = root_b;
}

bool isSameSet(int a, int b) {
    return getRoot(a) == getRoot(b);
}

struct Edge {
    int x;
    int y;
    int w;
    bool t;
    friend bool operator<(Edge a, Edge b) {
        if (a.w == b.w) return a.t > b.t; // 优先选关键边
        return a.w < b.w;
    }
};
vector<Edge> G;

int n, m, k, num;
long long ans;

void kruskal() {
    ans = num = 0;
    for (size_t i = 0; i < Set.size(); ++i) Set[i] = 0;
    sort(G.begin(), G.end());
    for (size_t i = 0; i < G.size(); ++i) {
        const Edge &edge = G[i];
        if (isSameSet(edge.x, edge.y)) continue;
        // cout << edge.x << " " << edge.y << " " << edge.w << endl;
        merge(edge.x, edge.y);
        ans += edge.w;
        if (edge.t) ++num;
    }
    // cout << ans << endl;
}

void add(int weight) {
    size_t size = G.size();
    for (size_t i = 0; i < size; ++i) {
        if (G[i].t) G[i].w += weight;
    }
}

long long getAnswer() {
    int l = -10000, r = 11000; // l<-10000 会失败几个案例
    int mid = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        // cout << "mid = " << mid << endl;
        add(mid);
        kruskal();
        if (num > k) l = mid + 1;
        else r = mid - 1;
        add(-mid);
    }
    return ans - k * mid;
}

int main() {
    cin >> n >> m >> k;
    Set.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        Edge temp;
        cin >> temp.x >> temp.y >> temp.w >> temp.t;
        G.push_back(temp);
    }
    cout << getAnswer() << endl;

    return 0;
}