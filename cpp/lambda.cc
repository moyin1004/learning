#include <functional>
#include <iostream>
#include <vector>

using namespace std;

std::vector<function<bool(int)>> filter;

void add() {
    static auto div = 10;
    // int div = 10;
    filter.emplace_back([](int value) { return value % div; });
}