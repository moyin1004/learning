/// @file    Circle.h
/// @data    2019-01-28 19:43:00
 
#ifndef __CIRCLE_H__
#define __CIRCLE_H__
    
class Circle {
public:
    Circle();
    Circle(double);

    double getArea();
    double getPerimeter();
    void show();
private:
    double _radius;
};

class Cylinder 
: public Circle
{
public:
    Cylinder(double, double);

    double getVolume();
    void showVolume();
private:
    double _h;
};

#endif
