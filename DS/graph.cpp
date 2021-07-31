#include "graph.h"
#include "stack.h"
#include "queue.h"
#include "util.h"
#include <cstring>
#include <queue>

Graph CreateGraph(int VertexNum) {
    /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->vexnum = VertexNum;
    Graph->arcnum = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->vexnum; V++)
        Graph->adjlist[V].first = NULL;
    return Graph;
}

bool AddEdge(Graph G, Vertex x, Vertex y, WeightType w) {
    if (x >= G->vexnum || y >= G->vexnum) return false;
    AdjVNode *s = (AdjVNode*)malloc(sizeof(AdjVNode));
    s->adjv = y;
    s->weight = w;
    s->next = G->adjlist[x].first;
    G->adjlist[x].first = s;
    return true;
}

Graph BuildGraph() {
    int num = 0;
    cin >> num;
    Graph G = CreateGraph(num);
    int u, v, w;
    while (cin >> u >> v >> w) {
        bool ret = AddEdge(G, u, v, w);
        if (!ret) return NULL;
    }
    return G;
}

void DestoryGraph(Graph G) {
    for (Vertex i = 0; i < G->vexnum; ++i) {
        while (G->adjlist[i].first) {
            AdjVNode *p = G->adjlist[i].first;
            G->adjlist[i].first = p->next;
            free(p);
        }
    }
    free(G);
}

void Visit(Vertex v) {
    cout << v << " ";
}

void BFS(Graph G, Vertex v) {
    AdjVNode *w;
    Visit(v);
    bool visited[MaxVertexNum] = {0};
    visited[v] = true;

    Queue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (!QueueEmpty(Q)) {
        DeQueue(Q, v);
        for (w = G->adjlist[v].first; w; w = w->next) {
            if (!visited[w->adjv]) {
                Visit(w->adjv);
                visited[w->adjv] = true;
                EnQueue(Q, w->adjv);
            }
        }
    }
}

bool visit[MaxVertexNum] = {0};
void BFSTraverse(Graph G) {
    for (int i = 0; i < G->vexnum; ++i) {
        visit[i] = false;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        if (!visit[i]) BFS(G, i);
    }
}

void DFS(Graph G, Vertex v) {
    AdjVNode *w;
    Visit(v);
    visit[v] = true;

    for (w = G->adjlist[v].first; w; w = w->next) {
        if (!visit[w->adjv]) {
            visit[w->adjv] = true;
            DFS(G, w->adjv);
        }
    }
}

void DFSTraverse(Graph G) {
    for (int i = 0; i < G->vexnum; ++i) {
        visit[i] = false;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        if (!visit[i]) DFS(G, i);
    }
}

// BFS最短路径（无向图）
void BFS_MIN_Distance(Graph G, Vertex v) {
    AdjVNode *w;
    int distance[MaxVertexNum] = {0};    // 记录v到每个顶点的最短距离
    int path[MaxVertexNum] = {0};        // 记录最短路径中每个顶点的前驱顶点

    Queue Q;
    InitQueue(Q);
    EnQueue(Q, v);
    while (!QueueEmpty(Q)) {
        DeQueue(Q, v);
        for (w = G->adjlist[v].first; w; w = w->next) { // 遍历v的所有相邻顶点
            if (!distance[v]) {
                distance[w->adjv] = distance[v] + 1;
                path[w->adjv] = v;
                EnQueue(Q, w->adjv);
            }
        }
    }
}

typedef int Distance;
typedef pair<Distance, Vertex> pii;
void Dijkstra(Graph G, Vertex start) {
    int distance[MaxVertexNum];
    std::memset(distance, 127, sizeof(distance));
    bool visited[MaxVertexNum] = {0};

    priority_queue<pii, vector<pii>, greater<pii>> Q;
    distance[start] = 0;
    Q.push(make_pair(0, start));
    while (!Q.empty()) {
        Vertex u = Q.top().second;  // 选取当前最短路径所在的顶点
        Q.pop();
        if (!visited[u]) {          // 每个顶点只作一次松弛，对u顶点相邻的顶点计算最短距离
            visited[u] = true;
            // 遍历当前顶点连接的所有顶点
            for (AdjVNode *v = G->adjlist[u].first; v; v = v->next) {
                if (distance[v->adjv] <= distance[u] + v->weight) continue;
                distance[v->adjv] = distance[u] + v->weight;  // 更新最短路径
                Q.push(make_pair(distance[v->adjv], v->adjv));
            }
        }
    }
    Print(distance, G->vexnum);
}

// void Floyd(Graph G) {
//     for (int k = 0; k < G->vexnum; k++) {
//         for (int u = 0; u < G->vexnum; u++) {
//             for (int v = 0; v < G->vexnum; v++) {
//                 A[u][v] = min(A[u][v], A[u][k]+A[k][v]);
//             }
//         }
//     }
// }

void BuildIndegree(Graph G, int indegree[]) {
    for (Vertex i = 0; i < G->vexnum; ++i) {
        for (AdjVNode *w = G->adjlist[i].first; w; w = w->next) {
            ++indegree[w->adjv];
        }
    }
}

bool TopologicalSort(Graph G) {
    // 建立入度数组
    int indegree[MaxVertexNum];
    BuildIndegree(G, indegree);
    Stack S;
    InitStack(S);
    for (Vertex i = 0; i < G->vexnum; ++i) {
        if (indegree[i] == 0) Push(S, i);
    }
    int count = 0;
    while (!StackEmpty(S)) {
        Vertex v;
        Pop(S, v);
        Visit(v);
        ++count;
        for (AdjVNode *w = G->adjlist[v].first; w; w = w->next) {
            // 入度为0时，入栈
            if (!(--indegree[w->adjv])) Push(S, w->adjv);
        }
    }
    if (count < G->vexnum) return false;
    return true;
}

static bool ReTS_Visit[MaxVertexNum];
static bool ReTS_Found[MaxVertexNum];
bool DFSReTopologicalSort(Graph G, Vertex v) {
    ReTS_Found[v] = true;
    for (AdjVNode *w = G->adjlist[v].first; w; w = w->next) {
        if (!ReTS_Found[w->adjv]) {
            bool ret = DFSReTopologicalSort(G, w->adjv);
            if (!ret) return ret;
        }
        else if (ReTS_Visit[v]) return false;
    }
    Visit(v); // 输出即为逆拓扑序
    ReTS_Visit[v] = true;
    return true;
}
void DFSReTopological(Graph G) {
    for (int i = 0; i < G->vexnum; ++i) {
        ReTS_Found[i] = false;
        ReTS_Visit[i] = false;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        if (!ReTS_Found[i]) {
            bool ret = DFSReTopologicalSort(G, i);
            if (!ret) {
                cout << "failed" << endl;
                break;
            }
        }
    }
}