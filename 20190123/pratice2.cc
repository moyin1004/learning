/// @file    pratice2.cc
/// @data    2019-01-23 22:42:37
 
#include <iostream>
#include <algorithm>
#include <functional> 
#include <vector>

using std::cout;
using std::endl;
using std::vector;
 
class Number {
public:
    Number(int data = 1)
    :_data(data)
    {}

    void display() const {
        cout << _data << endl;
    }
private:
    int _data;
};

int main() {
    vector<Number> numbers;
    for (size_t idx = 1; idx != 10; ++ idx)
        numbers.push_back(Number(idx));

    numbers.begin()->display();
    
    std::for_each(numbers.begin(), numbers.end(), std::mem_fn(&Number::display));
    return 0;
}
