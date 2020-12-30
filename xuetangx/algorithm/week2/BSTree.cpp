/*
描述
给定一个1到n的排列，按顺序依次插入到一棵二叉排序树中，请你将这棵二叉树前序遍历和后序遍历输出。
输入
第一行一个整数n。
接下来一行表示为n个整数，代表1到n的一个排列。
输出
输出所建成的二叉树的前序遍历和后序遍历。
输入样例
10
2 6 9 3 5 7 10 8 4 1
输出样例
2 1 6 3 5 4 9 7 8 10
1 4 5 3 8 7 10 9 6 2
限制
对于50%的数据，1 ≤ n ≤ 100；
对于100%的数据，1 ≤ n ≤ 100000。
保证建成的树的高度不超过50。
*/

#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Btree {
    int data;
    Btree *left;
    Btree *right;
};

int N;

void PreOrder(Btree *root, int &count) {
    if (!root) return ;
    cout << root->data;
    if (--count) {
        cout << " ";
    }
    PreOrder(root->left, count);
    PreOrder(root->right, count);
}

void PostOrder(Btree *root, int &count) {
    if (!root) return ;
    PostOrder(root->left, count);
    PostOrder(root->right, count);
    cout << root->data;
    if (--count) {
        cout << " ";
    }
}

Btree *Creat(int data) {
    Btree *node = (Btree*)malloc(sizeof(Btree));
    node->data = data;
    node->right = node->left = NULL;
    return node;
}

void Destroy(Btree *root) {
    if (!root) return ;
    Destroy(root->left);
    Destroy(root->right);
    free(root);
    root = NULL;
}

void Insert(Btree *&root, int data) {
    if (!root) {
        root = Creat(data);
        return ;
    }
    Btree *node = root;
    while (node) {
        if (data < node->data) {
            if (!node->left) {
                node->left = Creat(data);
                return ;
            } else {
                node = node->left;
            }
        }
        else {
            if (!node->right) {
                node->right = Creat(data);
                return ;
            } else {
                node = node->right;
            }
        }
    }
}

int main() {
    Btree *root = NULL;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int temp = 0;
        cin >> temp;
        Insert(root, temp);
    }
    int count = N;
    PreOrder(root, count);
    cout << endl;
    count = N;
    PostOrder(root, count);
    cout << endl;
    Destroy(root);
    return 0;
}
