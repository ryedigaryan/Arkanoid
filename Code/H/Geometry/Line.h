//
// Created by ruben on 5/6/2018.
//

#ifndef ARCANOID_LINE_H
#define ARCANOID_LINE_H


#include <cmath>
#include "Definitions/CommonDefinitions.h"
#include "Point.h"

class Line
{
public: //constructors
    explicit Line(Point start = Point(), Point end = Point());

public: //fucntions
    float yAt(const float& x) const;
    float xAt(const float& y) const;
    Point intersection(const Line& other) const;
    bool  contains(Point point) const;
    bool  isInside(Line first, Line second) const;

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

public: //data
    Point m_start;
    Point m_end;

private:
    float k;
    float b;
};

#endif //ARCANOID_LINE_H
