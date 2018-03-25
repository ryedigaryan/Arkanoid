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
    explicit Vector(int module = 0, int angle = 0) : m_module(module), m_angle(angle) {}

    void rotate(int angle);

    int getProjection(const Axis& axis);
    Vector getProjectionVector(const Axis &axis);
    Point end(const Point& start = Point());
    Point start(const Point& end = Point());

    int m_module;
    int m_angle;
};

#endif //ARCANOID_VECTOR_H
