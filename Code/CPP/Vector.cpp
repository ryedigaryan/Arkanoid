//
// Created by ryedigaryan on 2/26/2018.
//

#include "Geometry/Vector.h"

Vector::Vector(Point from, Point to)
{
    m_x = to.x - from.x;
    m_y = to.y - from.y;
}

Vector::Vector(const float& xProjection, const float& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

float Vector::projection(const Axis &axis) const
{
    return axis == AxisX ? m_x : m_y;
}

float Vector::module() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

float Vector::angle() const
{
    if(m_x == 0) {
        return static_cast<float>(M_PI_2);
    }
    float angle = std::atan(m_y / m_x);
    if(m_x < 0) {
        return static_cast<float>(angle < 0 ? angle - M_PI_2 : angle + M_PI_2);
    }
    return angle;
}

void Vector::setAngle(const float &angle)
{
    set(module(), angle);
}

void Vector::setModule(const float &module)
{
    set(module, angle());
}

void Vector::set(const float& module, const float& angle)
{
    m_x = module * std::cos(angle);
    m_y = module * std::sin(angle);
}

void Vector::setProjection(const float& xProjection, const float& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

void Vector::inverse(Axis axis)
{
    switch(axis) {
        case AxisX:
            m_x = -m_x;
            return;
        case AxisY:
            m_y = -m_y;
            return;
    }
}

void Vector::rotate(float angleDelta)
{
    set(module(), angle() + angleDelta);
}
