#include <cassert>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Node {
    long long count;
    vector<int> next;
};
struct Data {
    int pos;
    int count;
};

vector<Node> Tree;
deque<int> Q[2];

bool cmp(Data &lhs, Data &rhs) {
    return lhs.count < rhs.count;
}

void increase(int root) {
}

void cul(Node &node, int index) {
    int pos = Q[index].front();
    node.count += Tree[pos].count;
    node.next.push_back(pos);
    Q[index].pop_front();
}

void findMin(int num) {
    if (num <= 1) return ;
    Node node = {0};
    long long sum = 0;
    for (int i = 0; i < num; ++i) {  // 取最小的num个
        if (!Q[0].empty() && !Q[1].empty() &&
            Tree[Q[0].front()].count >= Tree[Q[1].front()].count) {

            cul(node, 1);
        }
        else if (!Q[0].empty() && !Q[1].empty() &&
            Tree[Q[0].front()].count < Tree[Q[1].front()].count){

            cul(node, 0);
        }
        else if (!Q[0].empty() && Q[1].empty()) {
            cul(node, 0);
        }
        else if (Q[0].empty() && !Q[1].empty()) {
            cul(node, 1);
        }
        else {
            assert(0);
        }
    }
    Tree.push_back(node);
    Q[1].push_back(Tree.size() - 1);
}

void push(int pos, int index) {
    int num = Tree[pos].next.size();
    for (int i = 0; i < num; ++i) {
        Q[index].push_back(Tree[pos].next[i]);
    }
}

void print(int root, int k) {
    long long sum = 0;
    int level = 1;
    Q[0].clear();
    Q[1].clear();
    push(root, 0);
    for (int i = 0; i < k; ++i) {
        Tree[root].next[i];
    }
    int index = 0;  // 层级交替
    while (!Q[0].empty() || !Q[1].empty()) {
        int num = Q[index].size();
        for (int i = 0; i < num; ++i) {
            int pos = Q[index].front();
            Q[index].pop_front();
            if (Tree[pos].next.empty()) {
                sum += level * Tree[pos].count;
            }
            else {
                push(pos, 1 - index);
            }
        }
        index = !index;
        ++level;
    }
    cout << sum << endl;
}

int main() {
    int n, k;
    //ifstream ifs("sample2.in");
    //ifs >> n >> k;
    cin >> n >> k;
    vector<Data> vec;
    int max = 0, min = 0;
    for (int i = 0; i < n; ++i) {
        int temp = 0;
        //ifs >> temp;
        cin >> temp;
        Node node = {temp};
        Tree.push_back(node);

        Data data = {i, temp};
        vec.push_back(data);
    }
    sort(vec.begin(), vec.end(), cmp);
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        Q[0].push_back(it->pos);
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
    while (Q[0].size() + Q[1].size() > 1) {
        findMin(k);
    }
    int root = 0;
    if (!Q[0].empty()) {
        root = Q[0].front();
    }
    if (!Q[1].empty()) {
        root = Q[1].front();
    }
    print(root, k);
    return 0;
}
