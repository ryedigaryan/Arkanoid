//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_VECTOR_H
#define ARCANOID_VECTOR_H

#define FullAngle 360
#define StraightAngle 180

#include "Point.h"

class Vector
{
public:
    Vector(Point from, Point to);
    explicit Vector(const int& xProjection = 0, const int& yProjection = 0);

    int projection(const Axis &axis);
    double module();
    double angle();
    void set(const int& module, const int& angle);
    void setProjection(const int& xProjection, const int& yProjection);

    Vector getProjectionVector(const Axis &axis);
    Point end(const Point& start = Point());
    Point start(const Point& end = Point());

private:
    int m_x; // x projection
    int m_y; // y projection
};

#endif //ARCANOID_VECTOR_H