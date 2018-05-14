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
    explicit Vector(const float& xProjection = 0, const float& yProjection = 0);

    float projection(const Axis &axis) const;
    float module() const;
    float angle() const;
    void set(const float& module, const float& angle);
    void setProjection(const float& xProjection, const float& yProjection);;

    Vector getProjectionVector(const Axis& axis) const;
    Point end(const Point& start = Point()) const;
    Point start(const Point& end = Point()) const;

    // action
    void inverse(Axis axis);
    void rotate(float angleDelta);

private:
    float m_x; // x projection
    float m_y; // y projection
};

#endif //ARCANOID_VECTOR_H