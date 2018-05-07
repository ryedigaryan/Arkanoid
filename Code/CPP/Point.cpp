//
// Created by ryedigaryan on 4/8/2018.
//

#include "Geometry/Point.h"
#include "Geometry/Line.h"

Point operator+(const Point& left, const Point& right)
{
    return Point(left.x + right.x, left.y + right.y);
}

Point operator+(const Point& left, const Size& right)
{
    return Point(left.x + right.width, left.y + right.height);
}

Point operator+(const Point& left, const int& right)
{
    return Point(left.x + right, left.y + right);
}

Point operator*(const Point& left, const Size& right)
{
    return Point(left.x * right.width, left.y * right.height);
}

Point::Point(const Size& size)
{
    x = size.width;
    y = size.height;
}

bool Point::operator==(const Point& other) const
{
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const
{
    return x != other.x || y != other.y;
}

bool Point::isInside(const Line& first, const Line& second) const
{
    float top, bottom;
    float left, right;

    float tmp;
    if((top = first.yAt(x)) < (bottom = second.yAt(x))) {
        tmp = top;
        top = bottom;
        bottom = tmp;
    }

    if((left = first.xAt(y)) < (right = second.xAt(y))) {
        tmp = left;
        left = right;
        right = tmp;
    }

    return left < x && x < right && bottom < y && y < top;
}
