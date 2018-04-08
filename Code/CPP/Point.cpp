//
// Created by ryedigaryan on 4/8/2018.
//

#include "Geometry/Point.h"

Point operator+(const Point& left, const Point& right) {
    return Point(left.x + right.x, left.y + right.y);
}

Point operator+(const Point& left, const Size& right) {
    return Point(left.x + right.width, left.y + right.height);
}

Point operator+(const Point& left, const int& right) {
    return Point(left.x + right, left.y + right);
}

Point operator*(const Point& left, const Size& right) {
    return Point(left.x * right.width, left.y * right.height);
}

Point::Point(const Size &size) {
    x = size.width;
    y = size.height;
}
