/*
问题描述
你有一个盒子，你可以往里面放数，也可以从里面取出数。
初始时，盒子是空的，你会依次做 Q 个操作，操作分为两类：
插入操作：询问盒子中是否存在数 x，如果不存在则把数 x 丢到盒子里。
删除操作：询问盒子中是否存在数 x，如果存在则取出 x。
对于每个操作，你需要输出是否成功插入或删除。
输入
第一行一个正整数 Q，表示操作个数。
接下来 Q 行依次描述每个操作。每行 2 个用空格隔开的非负整数 op,x 描述一个操作：op 表示操作类型，op=1 则表示这是一个插入操作，op=2 则表示这是一个删除操作；x 的意义与操作类型有关，具体见题目描述。
输出
按顺序对所有操作输出，对于每个操作输出一行，如果成功则输出“Succeeded”（不含引号），如果失败则输出“Failed”（不含引号）。
样例输入
6
1 100
1 100
2 100
1 200
2 100
2 200
样例输出
Succeeded
Failed
Succeeded
Succeeded
Failed
Succeeded
数据范围
对于 60% 的数据，保证 x<10^5。
对于 100% 的数据，保证 x<10^18，Q≤5*10^5。
对于所有数据，保证 op∈{1,2}。
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

unordered_set<long long> S;

bool check(int op, long long data) {
    auto it = S.find(data);
    if (it != S.end()) {
        if (op == 1) {
            return false;
        }
        else if (op == 2) {
            S.erase(it);
            return true;
        }
    }
    else {
        if (op == 1) {
            S.insert(data);
            return true;
        }
        else if (op == 2) {
            return false;
        }
    }
}

int main() {
    int Q = 0;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int op = 0;
        long long x = 0;
        scanf("%d %lld", &op, &x);
        puts(check(op, x) ? "Succeeded":"Failed");
    }
    return 0;
}

/* Self-implementing HashTable
typedef long long ll;
vector<vector<ll> > table;

const ll HASH_VALUE = 100007;
int Hash(ll x) {
    return x % HASH_VALUE;
}

bool check(int op, ll x) {
    int h = Hash(x);
    vector<ll>::iterator ptr = table[h].end();
    for (vector<ll>::iterator it = table[h].begin(); it != table[h].end(); ++it) {
        if (*it == x) {
            ptr = it;
            break;
        }
    }
    if (op == 1) {
        if (ptr == table[h].end()) {
            return true;
        }
        return false;
    }
    else {
        if (ptr != table[h].end()) {
            *ptr = table[h].back();  // subtle
            table[h].pop_back();
            return true;
        }
        return false;
    }
}

int main() {
    int Q = 0;
    cin >> Q;
    table.resize(HASH_VALUE+1);g+
    for (int i = 0; i < Q; ++i) {
        int op = 0;
        long long x = 0;
        scanf("%d %lld", &op, &x);
        puts(check(op, x) ? "Succeeded":"Failed");
    }
    return 0;
}
*/