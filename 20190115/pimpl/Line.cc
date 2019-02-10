/// @file    Line.cc
/// @data    2019-01-15 21:22:49
 
#include "Line.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
class Line::LineImpl {
public:
    LineImpl()
    : _pt1()
    , _pt2()
    {}

    LineImpl(int x1, int y1, int x2, int y2)
    : _pt1(x1, y1)
    , _pt2(x2, y2)
    {}

    ~LineImpl() {}

    void printLine() const { //Point为private，Line不能直接调用，在这里输出
        _pt1.printPoint();
        cout << " ---> ";
        _pt2.printPoint();
        cout << endl;
    }

private:
    class Point {
    public:
        Point()
        : _ix(0)
        , _iy(0)
        {}

        Point(int ix, int iy = 0)
        : _ix(ix)
        , _iy(iy)
        {}

        ~Point() {}

        void printPoint() const {
            cout << "(" << _ix << "," << _iy << ")";
        }

    private:
        int _ix;
        int _iy;
    };
    Point _pt1;
    Point _pt2;
};

Line::Line()
: _pImpl(new LineImpl())
{}

Line::Line(int x1, int y1, int x2, int y2) 
: _pImpl(new LineImpl(x1, y1, x2, y2))
{}

Line::~Line() {
    delete _pImpl;
}

void Line::printLine() const {
    _pImpl->printLine();
}
