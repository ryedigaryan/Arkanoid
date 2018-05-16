//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_VECTOR_H
#define ARCANOID_VECTOR_H

#include "Point.h"
#include <cmath>

class Vector
{
public: // constructors
    Vector(Point from, Point to);
    explicit Vector(const float& xProjection = 0, const float& yProjection = 0);

public: // getters
    float projection(const Axis &axis) const;
    float module() const;
    float angle()  const;

public: // modifiers
    void setAngle(const float& angle);
    void setModule(const float& module);
    void set(const float& module, const float& angle);
    void setProjection(const float& xProjection, const float& yProjection);
    void inverse(Axis axis);
    void rotate(float angleDelta);

private: // data
    float m_x; // x projection
    float m_y; // y projection
};

#endif //ARCANOID_VECTOR_H