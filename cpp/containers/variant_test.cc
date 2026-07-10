#include <variant>
#include <iostream>

using namespace std;

struct Expression {};
struct Statement {};
struct Declaration {};

using Node = variant<Expression, Statement, Declaration>;

// 类模板参数推导（Class Template Argument Deduction）
template<typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template<typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void check(Node *p) {
    visit(overloaded([](Expression e) { cout << "Expression" << endl; },
                     [](Statement s) { cout << "Statement" << endl; },
                     [](Declaration d) { cout << "Declaration" << endl; }),
         *p);
}

int main() {
    Node n = Expression();
    check(&n);
    return 0;
}