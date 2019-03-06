/// @file    functionPolymorphism.cc
/// @data    2019-01-29 23:45:29
 
#include <iostream>
#include <functional>
 
using std::cout;
using std::endl;
using std::function;
 
class Figure {
public:
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;

    //注册回调函数
    void setDisplayCallback(DisplayCallback &&cb) {  //bind返回一个右值
        _displayCallback = std::move(cb);
    }

    void setAreaCallback(AreaCallback &&cb) {
        _areaCallback = std::move(cb);
    }

    //执行回调函数
    void handleDisplayCallback() const {
        if(_displayCallback)
            return _displayCallback();
    }

    double handleAreaCallback() const {
        if (_areaCallback)
            return _areaCallback();
        else 
            return 0;
    }
private:
    DisplayCallback _displayCallback;
    AreaCallback _areaCallback;
};

class Rectangle {
public:
    Rectangle(double length, double width)
    : _length(length)
    , _width(width)
    {}

    void display(int ix) const {
        cout << "rectangle" << endl;
    }

    double area() {
        return _length * _width;
    }
private:
    double _length;
    double _width;
};

void display(Figure &figure) {
    figure.handleDisplayCallback();
    cout << "area = " << figure.handleAreaCallback() << endl;
}

int main() {
    Rectangle rectangle(100, 100);

    Figure figure;
    figure.setDisplayCallback(std::bind(&Rectangle::display, &rectangle, 4));
    figure.setAreaCallback(std::bind(&Rectangle::area, &rectangle));

    display(figure);

    return 0;
}
