//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_POINT_H
#define ARCANOID_POINT_H

#include "Size.h"
//#include "Line.h"

enum Axis {
    AxisX,
    AxisY
};

class Line;

class Point
{
public:
    explicit Point(int x = 0, int y = 0) noexcept
            : x(x), y(y) {}

    explicit Point(const Size& size);

    bool isInside(const Line& first, const Line& second) const;

    bool operator ==(const Point& other) const;
    bool operator !=(const Point& other) const;

    friend Point operator+(const Point& left, const Point& right);
    friend Point operator+(const Point& left, const Size& right);
    friend Point operator+(const Point& left, const int& right);
    friend Point operator*(const Point& left, const Size& right);

public:
    int x;
    int y;
};

#endif //ARCANOID_POINT_H
