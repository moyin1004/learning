#include <concepts>
#include <iostream>
#include <type_traits>

using namespace std;

constexpr size_t max_len = 8;

template <typename T>
class On_stack {};

template <typename T>
class On_heap {};

template <typename T>
using Store = conditional_t<sizeof(T) < max_len, On_stack<T>, On_heap<T>>;

class MyAllocator {
public:
    using value_type = int;

    int* allocate(std::size_t n) { return new int[n]; }

    void deallocate(int* p, std::size_t n) { delete[] p; }

    bool operator==(const MyAllocator&) const { return true; }
};

struct MyFunc {
    int operator()(this auto&& self, int n) {
        if (n <= 1) return 1;
        return n * self(n - 1);  // 递归调用自身
    }
};

struct MyFuncWithAlloc {
    int operator()(this auto&& self, MyAllocator alloc, int n) {
        // 这里可以实际使用 alloc，例如分配内存，仅演示
        if (n <= 1) return 1;
        return n * self(alloc, n - 1);  // 继续传递 alloc
    }
};

template <typename F, typename... Args>
auto call(F f, Args... args, MyAllocator alloc) {
    if constexpr (invocable<F, decltype(alloc), Args...>) {
        std::cout << "Using allocator (size = " << sizeof(alloc) << ")\n";
        return f(alloc, args...);
    } else {
        std::cout << "Not using allocator\n";
        return f(args...);
    }
}

int main() {
    MyAllocator alloc;
    MyFunc f;
    auto a = call<decltype(f), int>(f, 5, alloc);
    cout << a << endl;
    MyFuncWithAlloc fa;
    a = call<decltype(fa), int>(fa, 5, alloc);
    cout << a << endl;
    return 0;
}