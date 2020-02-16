/*
题目描述
农夫(Human)过河。一个农夫带着一只狼(Wolf)，一只羊(Sheep)和一些菜(Vegetable)过河。河边只有一条船，由于船太小，
只能装下农夫和他的一样东西。在无人看管的情况下，狼要吃羊，羊要吃菜，请问农夫如何才能使三样东西平安过河?
输入格式
没有输入
输出格式
输出一行，为最终的过河方式，方案格式为 过河人员、回来人员、过河人员、回来人员、...、过河人员。
过去和回来的人员之间，用空格隔开。
以四个生物英文的首字母代指对应的生物(H->Human,W->Wolf,S->Sheep,V->Vegetable)
具体见样例输出。
输出任意可行方案即可。
样例输入
无
样例输出
HS H HW H
注释
样例输出仅用于解释输出格式，非答案。
*/

#include <cassert>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct State {
    bool wolf;
    bool human;
    bool veg;
    bool sheep;
};

State cross_river(State s, char carry) {
    s.human = !s.human;
    if (carry == '_') {
        return s;
    }
    else if (carry == 'W') {
        s.wolf = !s.wolf;
    }
    else if (carry == 'V') {
        s.veg = !s.veg;
    }
    else if (carry == 'S') {
        s.sheep= !s.sheep;
    } else {
        assert(0);
    }
    return s;
}

bool is_invalid_state(State s) {
    if (s.human != s.sheep && s.sheep == s.wolf) return true;
    if (s.human != s.sheep && s.sheep == s.veg) return true;
    return false;
}

bool is_final_state(State s) {
    if (s.human == 1 && s.sheep == 1 && s.veg == 1 && s.wolf == 1)
        return true;
    return false;
}

char ans[1000];
bool visit[2][2][2][2] = {0};
void show_answer(int n) {
    for (int i = 0; i < n; ++i) {
        if (i != 0) printf(" ");
        printf("H");
        if (ans[i] != '_') {
            printf("%c", ans[i]);
        }
    }
}
bool solve(State s, int step) {
    if (is_invalid_state(s)) {
        return false;
    }
    if (is_final_state(s)) {
        show_answer(step);
        return true;
    }
    if (visit[s.human][s.sheep][s.veg][s.wolf] == true) {
        return false;
    }
    visit[s.human][s.sheep][s.veg][s.wolf] = true;
    State next_state;
    next_state = cross_river(s, '_');
    ans[step] = '_';
    if (solve(next_state, step+1)) return true;

    if (s.human == s.wolf) {
        ans[step] = 'W';
        next_state = cross_river(s, 'W');
        if (solve(next_state, step+1)) return true;
    }
    if (s.human == s.sheep) {
        ans[step] = 'S';
        next_state = cross_river(s, 'S');
        if (solve(next_state, step+1)) return true;
    }
    if (s.human == s.veg) {
        ans[step] = 'V';
        next_state = cross_river(s, 'V');
        if (solve(next_state, step+1)) return true;
    }
}

int main() {
    State init_state = {0};
    solve(init_state, 0);
    return 0;
}
