#include <cassert>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Node {
    long long count;
    vector<vector<Node>::const_iterator> next;
};
struct Data {
    int pos;
    long long count;
    friend bool operator<(Data lhs, Data rhs) {
        return lhs.count > rhs.count;
    }
};

vector<Node> Tree;
priority_queue<Data> P;

void findMin(int num) {
    if (num <= 1) return ;
    Node node = {0};
    for (int i = 0; i < num; ++i) {  // 取最小的num个
        node.count += P.top().count;
        node.next.push_back(P.top().pos);
        P.pop();
    }
    Tree.push_back(node);
    Data data = {(int)Tree.size() - 1, node.count};
    P.push(data);
}

void push(int pos, int index) {
    int num = Tree[pos].next.size();
    for (int i = 0; i < num; ++i) {
        Q[index].push_back(Tree[pos].next[i]);
    }
}

//deque<int> Q[2];
//void print(int root) { // 层序遍历
//    long long sum = 0;
//    int level = 1;
//    Q[0].clear();
//    Q[1].clear();
//    push(root, 0);
//    int index = 0;  // 层级交替
//    while (!Q[0].empty() || !Q[1].empty()) {
//        int num = Q[index].size();
//        for (int i = 0; i < num; ++i) {
//            int pos = Q[index].front();
//            Q[index].pop_front();
//            if (Tree[pos].next.empty()) {
//                sum += level * Tree[pos].count;
//            }
//            else {
//                push(pos, 1 - index);
//            }
//        }
//        index = !index;
//        ++level;
//    }
//    cout << sum << endl;
//}

long long Sum = 0;
void preOrder(int root, int level) {
    if (Tree[root].next.empty()) {
        Sum += level * Tree[root].count;
        return;
    }
    int size = Tree[root].next.size();
    for (int i = 0; i < size; ++i) {
        preOrder(Tree[root].next[i], level + 1);
    }
}

int main() {
    int n, k;
    //ifstream ifs("sample2.in");
    //ifs >> n >> k;
    scanf("%d %d", &n, &k);
    int max = 0, min = 0;
    for (int i = 0; i < n; ++i) {
        int temp = 0;
        //ifs >> temp;
        scanf("%d", &temp);
        Node node = {temp};
        Tree.push_back(node);

        Data data = {i, temp};
        P.push(data);
    }
    if (k >= n) {
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += Tree[i].count;
        }
        cout << sum << endl;
    }

    int start = n % (k - 1);  // 计算最深层结点数
    if (start == 0) {
        findMin(k - 1);
    } else {
        findMin(start);
    }
    while (P.size()> 1) {
        findMin(k);
    }
    int root = P.top().pos;
    //print(root);
    preOrder(root, 0);
    cout << Sum << endl;
    return 0;
}
