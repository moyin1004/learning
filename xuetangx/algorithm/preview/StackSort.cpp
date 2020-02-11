#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef stack<int> Stack;

int main() {
    int N;
    Stack s, r;
    cin >> N;
    for (size_t i = 0; i < N; ++i) {
        int temp;
        cin >> temp;
        r.push(temp);
    }
    int temp = 0;
    while (!r.empty()) {
        temp = r.top();
        r.pop();
        // note stack is empty
        if (s.empty() || s.top() >= temp) {
            s.push(temp);
        }
        else {
            while (!s.empty() && s.top() < temp) {
                int num = s.top();
                s.pop();
                r.push(num);
            }
            s.push(temp);
        }
    }
    for (size_t i = 0; i < N; ++i) {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}
