#ifndef __TREE__
#define __TREE__

#include "type.h"

/**
 * 顺序存储
 */
typedef struct {
    ElemType value;
    bool isEmpty;
} TreeNode;
// TreeNode t[MaxSize];

/**
 * 链式存储
 */
typedef struct BiNode {
    ElemType data;
    struct BiNode *left, *right;
    int height;
    // struct BiNode *parent;
} BiNode, *BiTree;

void InOrder(BiTree BT);             // 中序非递归
void InOrderTraversal(BiTree BT);    // 中序递归
void PreOrder(BiTree BT);            // 前序非递归
void PreOrderTraversal(BiTree BT);   // 前序递归
void PostOrder(BiTree BT);           // 后序非递归
void PostOrderTraversal(BiTree BT);  // 后序递归
void LevelOrderTraversal(BiTree BT); // 层序遍历
int TreeDeepth(BiTree T);

/**
 * 线索二叉树
 */
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;
} ThreadNode, *ThreadTree;

void CreatThread(ThreadTree T, int flag);
void InOrder(ThreadNode *T);
void RevInOrder(ThreadNode *T);

/**
 * 二叉排序树
 */
typedef struct BSTNode {
    int key;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

/**
 * 二叉平衡树
 */
typedef BiNode AVLNode;
typedef BiTree AVLTree;

AVLTree Insert(AVLTree T, ElemType X);
void DestoryAVL(AVLTree &T);


// 树的双亲表示法（顺序存储）
typedef struct {
    ElemType data;
    int parent;
} PTNode;
typedef struct {
    PTNode nodes[MaxSize];
    int n;
} PTree;

// 树的孩子表示法（顺序+链式存储）
struct CTNode {
    int child;
    struct CTNode *next;
};
typedef struct {
    ElemType data;
    struct CTNode *firstChild;
} CTBox;
typedef struct {
    CTBox nodes[MaxSize];
} CTree;

// 孩子兄弟表示法（树和二叉树的转换）
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

#endif