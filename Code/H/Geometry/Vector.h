//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_VECTOR_H
#define ARCANOID_VECTOR_H

#define FullAngle 360
#define StraightAngle 180

#include "Point.h"

class Vector {
public:
    explicit Vector(const int& module = 0, const int& angle = 0);
    Vector(Point from, Point to);
    Vector(const Size& projection);

    void rotate(int angle);

    int projection(const Axis &axis);
    double module();

    Vector getProjectionVector(const Axis &axis);
    Point end(const Point& start = Point());
    Point start(const Point& end = Point());

    int m_angle;

private:
    int m_x; // x projection
    int m_y; // y projection
};

#endif //ARCANOID_VECTOR_H
