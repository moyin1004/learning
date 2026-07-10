#include <iostream>
#include <source_location>

using namespace std;

template<typename T>
class Smart_pointer {
public:
    T& operator*() {
        return *ptr;
    }

    // 条件属性
    T* operator->() const requires is_class_v<T> {
        return ptr;
    }
    Smart_pointer(T* p) : ptr(p) {}
    ~Smart_pointer() {
        delete ptr;
    }
private:
    T* ptr;
};

void log(const string& mess = "", const source_location loc = source_location::current()) {
    cout << loc.function_name() << " " << loc.line() << " " << loc.file_name() << " " << mess << endl;
}

int main() {
    cout << "Hello, World!" << endl;
    log("Hello, World!");
    return 0;
}