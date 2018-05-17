//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_POINT_H
#define ARCANOID_POINT_H

#include "Size.h"

enum Axis {
    AxisX,
    AxisY
};

class Point
{
public:
    explicit Point(float x = 0, float y = 0) noexcept
            : x(x), y(y) {}

    explicit Point(const Size& size);

    bool operator ==(const Point& other) const;
    bool operator !=(const Point& other) const;

    friend Point operator+(const Point& left, const Point& right);
    friend Point operator+(const Point& left, const Size& right);
    friend Point operator+(const Point& left, const int& right);
    friend Point operator*(const Point& left, const Size& right);

public:
    float x;
    float y;
};

#endif //ARCANOID_POINT_H
