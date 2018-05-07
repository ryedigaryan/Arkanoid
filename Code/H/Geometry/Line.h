//
// Created by ruben on 5/6/2018.
//

#ifndef ARCANOID_LINE_H
#define ARCANOID_LINE_H

#include "Point.h"

class Line
{
public: //constructors
    Line(Point start = Point(), Point end = Point());

public: //fucntions
    Point intersection(const Line& other);

public: //data
    Point m_start;
    Point m_end;
};

#endif //ARCANOID_LINE_H
