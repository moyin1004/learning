#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template <class Iter>
class Sentinel {
public:
    Sentinel(int it) : end(it) {}
    Sentinel() : end(0) {}

    friend bool operator==(const Iter& p, Sentinel s) { return *p == s.end; }
    friend bool operator!=(const Iter& p, Sentinel s) { return !(p == s); }

private:
    iter_value_t<const char*> end;
};

int main() {
    static_assert(sentinel_for<Sentinel<const char *>, const char *>);
    const char aa[] = "Hello, World!\nBye for now\n";
    ranges::for_each(aa, Sentinel<const char*>('\n'), [](const char c) { cout << c; });
    return 0;
}