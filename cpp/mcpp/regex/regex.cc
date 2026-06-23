#include <iostream>
#include <regex>

void test() {
    std::string input = "aa as; asd ++e^asdf asdfg";
    std::regex pat{R"(\s+(\w+))"};
    for (std::sregex_iterator it(input.begin(), input.end(), pat); it != std::sregex_iterator();
         ++it) {
        // std::cout << (*it)[0] << std::endl;
        std::cout << (*it)[1] << std::endl;
    }
}

int main() {
    test();
    return 0;
}