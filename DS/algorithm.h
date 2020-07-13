#ifndef __ALGORITHM__
#define __ALGORITHM__

#include "type.h"
#include "linked_list.h"
#include "tree.h"

int FindMid(ElemType a[], ElemType b[], int n);
int FindMajority(int a[], int n);

// 线性表
// 分解链表
LinkList DisCreat_1(LinkList &A);
LinkList DisCreat_2(LinkList &A);
// 使链表无重复元素
void DeleteSame(LinkList &L);
// 归并链表
LinkList MergeList(LinkList &A, LinkList &B);
// 合并循环链表
LinkList Union(LinkList &h1, LinkList &h2);
LNode *Locate(LinkList &L, ElemType e);


// 树
// 根据先序遍历和中序遍历建立二叉链表
BiTree CreatBTreeByOrder(int preorder[], int inorder[], int n);
// 删除以x为根的子树
void DeleteXTree(BiTree &T, ElemType x);
// 最近公共祖先
BiNode* LowestCommonAncestor(BiNode* root, BiNode* p, BiNode* q);


// 图

// 查找

// 排序

#endif