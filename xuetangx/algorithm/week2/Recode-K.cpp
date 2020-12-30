/*
背景
小粽学习了哈夫曼树之后，自己设计了贪心算法，用两个队列就过掉了《重编码》这道题。
小粽想：那堆的算法有什么用呢？为了解决小粽的疑惑，邓老师委托小莉命制了这道题目……
描述
有一篇文章，文章包含 n种单词，单词的编号从 1至 n，第 i 种单词的出现次数为 wi。
现在，我们要用一个 k进制串（即只包含 0,1,...,k−1的串） si来替换第 i种单词，使其满足如下要求：
对于任意的 1≤i<j≤n，都有 si不是 sj的前缀（这个要求是为了避免二义性）。
你的任务是对每个单词选择合适的 sj，使得替换后的文章总长度（定义为所有单词出现次数与替换它的 k 进制串的长度乘积的总和）最小。求这个最小长度。
字符串 S1（不妨假设长度为 n）被称为字符串 S2 的前缀，当且仅当：S2 的长度不小于 n，且 S1 与S2前 n个字符组组成的字符串完全相同。
输入格式
第一行两个整数 n和 k。
第 2 行到第 n+1 行，第 i+1 行包含一个正整数 wi，表示第 i 种单词的出现次数。
输出格式
表示整篇文章重编码后的最短长度
输入样例1
5 3
1
3
5
10
3
输出样例1
29
限制
对于 100% 的数据，满足 1≤n≤3×10^5,2≤k≤10,1≤wi≤10^9；
对于 40% 的数据，满足 n≤3000；
对于 35% 的数据，满足 k=2。
*/

#include <iostream>
#include <bits/stdc++.h>
//#include <fstream>

using namespace std;

// opt version, Huffman root's value is min code length
typedef long long ll;
typedef priority_queue<ll, vector<ll>, greater<ll> > Heap;
long long solve(Heap &p, int n, int k) {
    ll sum = 0;
    int r = (k - n % (k-1)) % (k-1);
    while (r--) {
        p.push(0);
    }
    while (p.size() > 1) {
        ll cur = 0;
        for (int i = 0; i < k; ++i) {
            cur += p.top();
            p.pop();
        }
        p.push(cur);
        sum += cur;
    }
    return sum;
}

int main() {
    int n, k;
    priority_queue<ll, vector<ll>, greater<ll> > p;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int temp = 0;
        scanf("%d", &temp);
        p.push(temp);
    }
    cout << solve(p, n, k) << endl;
}

#if 0
struct Node {
    long long count;
    vector<Node*> next;
};

struct Compare_Node_Pointer  {
    /* 小的优先 */
    bool operator () (Node* &a, Node* &b) const {
        return a->count > b->count;
    }
};

priority_queue<Node*, std::vector<Node*>, Compare_Node_Pointer> P; // 存自定义指针时，重载<和>会失效，使用compare

void findMin(int num) {
    if (num <= 1) return ;
    Node *node = new Node{0};
    for (int i = 0; i < num; ++i) {  // 取最小的num个
        const Node *temp = P.top();
        node->count += temp->count;
        node->next.push_back(const_cast<Node*>(temp));
        P.pop();
    }
    P.push(node);
}

long long Sum = 0;
void preOrder(Node *root, int level) {
    if (root->next.empty()) {
        Sum += level * root->count;
        delete root;  // 释放叶子结点
        return;
    }
    int size = root->next.size();
    for (int i = 0; i < size; ++i) {
        preOrder(root->next[i], level + 1);
    }
    delete root; // 释放非叶子结点
}

int main() {
    int n, k;
//    ifstream ifs("sample2.in");
//    ifs >> n >> k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        int temp = 0;
//        ifs >> temp;
        scanf("%d", &temp);
        Node *node = new Node{temp};
        P.push(node);
    }

    int start = n % (k - 1);  // 计算最深层结点数
    if (start == 0) {
        findMin(k - 1);
    } else {
        fi  ndMin(start);
    }
    while (P.size()> 1) {
        findMin(k);
    }
    Node *root = P.top();
    preOrder(root, 0);
    cout << Sum << endl;
    return 0;
}
#endif