#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <vector>

using namespace std;

template <typename T, typename U = T>
concept Number = requires(T x, U y) {
    x + y;
    x - y;
    x * y;
    x / y;
    x += y;
    x -= y;
    x *= y;
    x /= y;
    x = x;
    x = 0;
};

template <typename T, typename U = T>
concept Arithmetic = Number<T, U> && Number<U, T>;

template <typename S>
concept Sequence = requires(S a) {
    typename ranges::range_value_t<S>;
    typename ranges::iterator_t<S>;
    { a.begin() } -> same_as<ranges::iterator_t<S>>;
    { a.end() } -> same_as<ranges::iterator_t<S>>;
    requires input_iterator<ranges::iterator_t<S>>;  // 符合 读、单向、单次遍历
    requires same_as<ranges::range_value_t<S>, iter_value_t<S>>;
};

template <Sequence Seq, Arithmetic<ranges::range_value_t<Seq>> Num>
Num sum(Seq s, Num n) {
    for (auto i : s) {
        n += i;
    }
    return n;
}

// 概念约束auto
auto twice(Arithmetic auto x) { return x + x; }

auto same_function(int x) {
    Number auto y = twice(x);
    return y;
}

template <Number... T>
int sum(T... v) {
    // 左折叠
    return (0 + ... + v);
}

int main() {
    cout << sum(vector{1, 2, 3}, 0) << endl;
    return 0;
}