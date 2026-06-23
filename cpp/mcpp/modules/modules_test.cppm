// main.cpp
import std; // 导入C++标准库模块（MSVC支持）
// #include <iostream>  // 也可以与传统头文件混用

int add(int a, int b) { return a + b; }

int main() {
    std::cout << "10 + 20 = " << add(10, 20) << std::endl;
    // std::cout << "10 * 20 = " << MathUtils::multiply(10, 20) << std::endl;
    // internal_helper(); // 错误！此函数未导出，不可见
    return 0;
}