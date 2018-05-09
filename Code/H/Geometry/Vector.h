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
    explicit Vector(const double& xProjection = 0, const double& yProjection = 0);

    double projection(const Axis &axis) const;
    double module() const;
    double angle() const;
    void set(const double& module, const double& angle);
    void setProjection(const double& xProjection, const double& yProjection);;

    Vector getProjectionVector(const Axis& axis) const;
    Point end(const Point& start = Point()) const;
    Point start(const Point& end = Point()) const;

    // action
    void inverse(Axis axis);
    void rotate(double angleDelta);

private:
    double m_x; // x projection
    double m_y; // y projection
};

#endif //ARCANOID_VECTOR_H