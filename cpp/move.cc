#include <cstring>
#include <iostream>
#include <string>
#include <chrono>
#include <type_traits>

using namespace std;

class String {
public:
    String() : _pstr(nullptr) {}

    String(const char *pstr) : _pstr(nullptr) {
        if (pstr != nullptr) {
            _pstr = new char(strlen(pstr) + 1);
            strcpy(_pstr, pstr);
        }
    }

    String(const String &rhs) : _pstr(nullptr) {
        if (rhs.size()) {
            _pstr = new char(rhs.size() + 1);
            strcpy(_pstr, rhs._pstr);
        }
    }

    String(String &&rhs) : _pstr(rhs._pstr) {
        rhs._pstr = nullptr;
        cout << "String(String &&)" << endl;
    }

    String &operator=(const String &rhs) {
        if (this != &rhs) {     // 防止自复制
            if (!rhs.size()) {  // 传入为空，赋空值
                delete _pstr;
                _pstr = nullptr;
                return *this;
            }
            if (size() > rhs.size())
                strcpy(_pstr, rhs._pstr);
            else {
                delete[] _pstr;
                _pstr = new char[rhs.size() + 1]();
                strcpy(_pstr, rhs._pstr);
            }
        }
        return *this;
    }

    String &operator=(const char *pstr) {
        if (pstr == nullptr) {  // 传入为空，赋空值
            delete _pstr;
            _pstr = nullptr;
            return *this;
        }
        size_t len1 = strlen(pstr);
        if (size() > len1) {
            strcpy(_pstr, pstr);
        } else {
            delete[] _pstr;
            _pstr = new char[len1 + 1]();
            strcpy(_pstr, pstr);
        }
        return *this;
    }

    String &operator=(String &&rhs) {
        cout << "operator=(String &&)" << endl;
        if (this != &rhs) {
            delete _pstr;
            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }

    char &operator[](std::size_t index) {  // C++容器中使用std::size_t更恰当
        if (index < size()) {
            return _pstr[index];
        } else {
            static char nullchar = '\0';
            return nullchar;
        }
    }

    const char &operator[](std::size_t index) const {
        if (index < size()) {
            return _pstr[index];
        } else {
            static char nullchar = '\0';
            return nullchar;
        }
    }

    std::size_t size() const {
        if (_pstr == nullptr)
            return 0;
        else
            return strlen(_pstr);
    }

    const char *c_str() const { return _pstr; }

    ~String() {
        if (_pstr != nullptr) {
            delete[] _pstr;
        }
    }

    void print() const {
        if (_pstr == nullptr)
            return;
        else
            cout << _pstr << endl;
    }

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);

private:
    char *_pstr;
};

bool operator==(const String &lhs, const String &rhs) { return !strcmp(lhs._pstr, rhs._pstr); }

bool operator!=(const String &lhs, const String &rhs) { return strcmp(lhs._pstr, rhs._pstr); }

std::ostream &operator<<(std::ostream &os, const String &s) {
    if (s._pstr != nullptr) os << s._pstr;
    return os;
}

String test_automove(String w) {
    int n = 10;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    return w; // 编译器自动优化 等价于std::move(w)
}

String test_rvo() {
    String w = "2sfafa";
    int n = 10;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += i;
    }
    return w;
}

template<typename T>
void logAndAdd(T&& name);

template<typename T>
void logAndAddImpl(T &&name, std::false_type) {
    auto now = std::chrono::system_clock::now();
    // log();
    // names.emplace(std::forward<T>(name));
}

string nameFromIdx(int idx) {
    return "";
}

template<typename T>
void logAndAddImpl(int idx, std::true_type) {
    logAndAdd(nameFromIdx(idx));
}

template<typename T>
void logAndAdd(T&& name) {
    logAndAddImpl(std::forward<T>(name), std::is_integral<std::remove_reference_t<T>>());
}

class Person {
public:
    template<typename T, typename = typename std::enable_if_t<!std::is_base_of_v<Person, typename std::decay_t<T> > > >
    explicit Person(T&& n) : name(std:::forward<T>(n)) {
        static_assert(std::is_constructible_v<std::string, T>, "n not be construct a string");
    }
private:
    string name;
};

int main() {
    String test("222");
    auto res = test_rvo();
    cout << res << endl;
    auto res2 = test_automove(test);
    cout << res2 << endl;
    return 0;
}