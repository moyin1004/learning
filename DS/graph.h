#ifndef __GRAPH__
#define __GRAPH__

#include "type.h"

#define MaxVertexNum 100
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int EdgeType;
typedef int WeightType;

// 邻接矩阵法
typedef int VertexType;
typedef struct {
    VertexType Ver[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
} MGraph;

#if 0
// 王道邻接表法（严蔚敏）
typedef struct ArcNode {
    int adjvex;            // 该弧指向的顶点的位置
    struct ArcNode *next;
} ArcNode;
typedef struct VNode {
    VertexType data;
    ArcNode *first;
} VNode, AdjList[MaxVertexNum];
typedef struct {
    AdjList vertices;      // 顶点数组
    int vexnum, arcnum;
} ALGraph;
#endif

/* 图的邻接表表示法 */
/* 边的定义 */
typedef struct ENode{
    Vertex v1, v2;      /* 有向边<v1, v2> */
    WeightType weight;  /* 权重 */
} Enode, *Edge;

/* 邻接点的定义 */
typedef struct AdjVNode{
    Vertex adjv;            /* 邻接点下标 */
    WeightType weight;      /* 边权重 */
    struct AdjVNode* next;  /* 指向下一个邻接点的指针 */
} AdjVNode;
 
/* 顶点表头结点的定义 */
typedef struct Vnode{
    AdjVNode* first;      /* 边表头指针 */
    ElemType data;        /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{  
    int vexnum;     /* 顶点数 */
    int arcnum;     /* 边数   */
    AdjList adjlist;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */
typedef LGraph Graph;

bool Adjacent(Graph G, Vertex x, Vertex y); // 判断图是否存在边<x, y>或(x, y)
bool Neighbors(Graph G, Vertex x);              // 判断图G中与结点x邻接的边
void InsertVertex(Graph G, Vertex x);           // 在图G中插入顶点x
void DeleteVertex(Graph G, Vertex x);           // 从图G中删除顶点x
bool AddEdge(Graph G, Vertex x, Vertex y);
bool AddEdge(Graph G, Vertex x, Vertex y, WeightType w);
bool RemoveEdge(Graph G, Vertex x, Vertex y);
Vertex FirstNeighbor(Graph G, Vertex x);
Vertex NextNeighbor(Graph G, Vertex x, Vertex y);
bool GetEdgeValue(Graph G, Vertex x, Vertex y);
bool SetEdgeValue(Graph G, Vertex x, Vertex y, int v);

Graph BuildGraph();
void DestoryGraph(Graph G);
void BFS(Graph G, Vertex v);
void BFSTraverse(Graph G);
void DFS(Graph G, Vertex v);
void DFSTraverse(Graph G);

void BFS_MIN_Distance(Graph G, Vertex v);
void Dijkstra(Graph G, Vertex start);

bool TopologicalSort(Graph G);

// 十字链表-有向图
typedef struct CrossArcNode {
    int tailvex, headvex, info;
    struct CrossArcNode *next;
} CrossArcNode;
typedef struct CrossVNode {
    VertexType data;
    CrossArcNode *hlink, *tlink;
} CrossVNode, CrossList[MaxVertexNum];
typedef struct {
    CrossList vertices;
    int vexnum, arcnum;
} CrossGraph;

// 邻接多重表-无向图

#endif