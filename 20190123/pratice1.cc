/// @file    pratice.cc
/// @data    2019-01-23 17:48:13
 
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::sort;
 
void display(int number) {
    cout << number << " ";
}

void test1() {
    vector<int> numbers{1, 2, 3, 4, 5, 8, 9, 6, 3, 4};
    
    sort(numbers.begin(), numbers.end());
    vector<int>::reverse_iterator rit = numbers.rbegin();
    while (rit != numbers.rend()) {
        cout << *rit << " ";
        ++rit;
    }
    cout << endl;

    bool found = std::binary_search(numbers.begin(), numbers.end(), 3);
    cout << "found = " << found << endl;

    auto it2 = std::find(numbers.begin(), numbers.end(), 6);
    cout << "*it = " << *it2 << endl;

    int ret = std::count(numbers.begin(), numbers.end(), 3);
    cout << "ret = " << ret << endl;

    auto it3 = std::lower_bound(numbers.begin(), numbers.end(), 8);
    cout << "*++it3 = " << *++it3 << endl;

    std::greater<int> lt;
    numbers.erase(remove_if(numbers.begin(), numbers.end(),std::bind2nd(lt, 4)),
                  numbers.end());
    for_each(numbers.begin(), numbers.end(), display);
    cout << endl;
}

int add(int x, int y) {
    return x + y;
}

class Example {
public:
    int add2(int x, int y) {
        return x + y;
    }
    int data = 200;
};

void func(int x1, int x2, int x3, const int & x4, int x5) {
    cout << "(" << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << ")" << endl;
}

void test2() {
    auto f1 = std::bind(add, 1, 2);
    cout << "f1() = " << f1(3, 5) << endl; //绑定后不能再传参，无效
    using namespace std::placeholders;
    auto f3 = std::bind(add, 1, _1); //std::placeholders::_n 占位符占据第n个参数
    cout << "f3() = " << f3(6) << endl;

    Example e1;
    //普通函数函数名为地址，成员函数需取地址
    auto f2 = std::bind(&Example::add2, &e1, 3, 2); 
    cout << "f2() = " << f2() << endl;;

    int number = 100;
    std::function<int()> f4 = std::bind(add, 1, 3);
    cout << "f4() = " << f4() << endl;

    std::function<void(int, int, int, int, int)>  f = std::bind(func, 10, _2, _1, std::cref(number), number);
    number = 1000;
    f(11, 12, 1111, 2222, 3333);
}

void test3() {
    std::function<int()> f = std::bind(add, 1, 2);
    cout << "f() = " << f() << endl;

    Example e1;
    f = std::bind(&Example::add2, &e1, 2, 3);
    cout << "f() = " << f() << endl;

    f = std::bind(&Example::data, &e1);
    cout << "f() = " << f() << endl;
}

int main() {
    cout << "-------test1--------" << endl;
    test1();
    cout << "-------test2--------" << endl;
    test2();
    cout << "-------test3--------" << endl;
    test3();
    return 0;
}
