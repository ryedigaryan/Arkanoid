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

Vector::Vector(const int& xProjection, const int& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

int Vector::projection(const Axis &axis)
{
    return axis == AxisX ? m_x : m_y;
}

double Vector::module()
{
    return m_x * m_x + m_y * m_y;
}

double Vector::angle()
{
    return atan(m_y / m_x);
}

void Vector::set(const int& module, const int& angle)
{
    m_x = static_cast<int>(module * cos(angle));
    m_y = static_cast<int>(module * sin(angle));
}

void Vector::setProjection(const int& xProjection, const int& yProjection)
{
    m_x = xProjection;
    m_y = yProjection;
}

Vector Vector::getProjectionVector(const Axis &axis)
{
    return axis == AxisX ? Vector(m_x, 0) : Vector(0, m_y);
}

Point Vector::end(const Point& start)
{
    return Point(start.x + m_x, start.y + m_y);
}

Point Vector::start(const Point& end)
{
    return Point(end.x - m_x, end.y - m_y);
}
