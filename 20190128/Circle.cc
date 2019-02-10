/// @file    Circle.cc
/// @data    2019-01-28 19:48:32

#include "Circle.h"
#include <cmath>
#include <iostream>
 
using std::cout;
using std::endl;

const double PI = 2 * asin(1);
 
Circle::Circle()
: _radius(0)
{}

Circle::Circle(double r)
: _radius(r)
{}

double Circle::getArea() {
    return PI * _radius * _radius;
}

double Circle::getPerimeter() {
    return 2 * PI * _radius;
}

void Circle::show() {
    cout << "radius = " << _radius << endl
         << "perimeter = " << getPerimeter() << endl
         << "area = " << getArea() << endl;
}

Cylinder::Cylinder(double r, double h)
: Circle(r)
, _h(h)
{}

double Cylinder::getVolume() {
    return getArea() * _h;
}

void Cylinder::showVolume() {
    cout << "volume = " << getVolume() << endl;
}
