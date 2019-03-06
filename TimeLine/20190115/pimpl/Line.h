/// @file    Line.h
/// @data    2019-01-15 21:19:08
 
#ifndef __LINE_H__
#define __LINE_H__

class Line {
public:
    Line();
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine() const;
    class LineImpl;
private:
    LineImpl *_pImpl;
};
    
#endif
