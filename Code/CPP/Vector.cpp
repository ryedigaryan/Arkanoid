//
// Created by ryedigaryan on 2/26/2018.
//

#include "Geometry/Vector.h"
#include <cmath>

Vector::Vector(Point from, Point to)
{
    m_x = to.x - from.x;
    m_y = to.y - from.y;
}

Vector::Vector(const double& xProjection, const double& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

double Vector::projection(const Axis &axis) const
{
    return axis == AxisX ? m_x : m_y;
}

double Vector::module() const
{
    return sqrt(m_x * m_x + m_y * m_y);
}

double Vector::angle() const
{
    return m_x == 0 ? (1 / 2 * M_PI) : atan(m_y / m_x);
}

void Vector::set(const double& module, const double& angle)
{
    m_x = module * cos(angle);
    m_y = module * sin(angle);
}

void Vector::setProjection(const double& xProjection, const double& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

Vector Vector::getProjectionVector(const Axis &axis) const
{
    return axis == AxisX ? Vector(m_x, 0) : Vector(0, m_y);
}

Point Vector::end(const Point& start) const
{
    return Point(static_cast<int>(start.x + m_x), static_cast<int>(start.y + m_y));
}

Point Vector::start(const Point& end) const
{
    return Point(static_cast<int>(end.x - m_x), static_cast<int>(end.y - m_y));
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

void Vector::rotate(double angleDelta)
{
    double angle = this->angle() + angleDelta;
    double module = this->module();
    m_x = module * cos(angle);
    m_y = module * sin(angle);
}