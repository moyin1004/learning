/// @file    pureVirtualFunc.cc
/// @data    2019-01-29 23:42:18
 
#include <iostream>
 
using std::cout;
using std::endl;

class Figure {
public:
    virtual
    void display() const = 0;

    virtual
    double area() const = 0;
};

class Rectangle 
: public Figure
{
public:
    Rectangle(double length, double width)
    : _length(length)
    , _width(width)
    {}

    void display() const override {
        cout << "rectangle" << endl;
    }

    double area() const override {
        return _length * _width;
    }
private:
    double _length;
    double _width;
};

int main() {
    Rectangle rectangle(3, 3);
    Figure* figure = &rectangle;

    figure->display();
    cout << "area = " << figure->area() << endl;;

    return 0;
}
