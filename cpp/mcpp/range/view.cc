#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

void user(ranges::forward_range auto& r) {
    for (int x : ranges::take_view( ranges::filter_view{r, [](int x) { return x % 2 == 0; }}, 10)) {
        cout << x << endl;
    }
}

void user2(ranges::forward_range auto& r) {
    for (int x : r | ranges::views::filter([](int x) { return x % 2 == 0; }) | ranges::views::take(10)) {
        cout << x << endl;
    }
}

int main() {
    auto data = ranges::iota_view(0, 100);
    std::vector<int> v(data.begin(), data.end());
    user(v);
}