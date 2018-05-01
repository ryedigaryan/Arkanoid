//
// Created by ryedigaryan on 2/26/2018.
//

#include "Geometry/Vector.h"
#include <cmath>

Vector::Vector(const int& module, const int& angle) : m_angle(angle)
{
    m_x = static_cast<int>(module * cos(angle));
    m_y = static_cast<int>(module * sin(angle));
}

Vector::Vector(Point from, Point to)
{
    m_x = to.x - from.x;
    m_y = to.y - from.y;
    m_angle = static_cast<int>(atan(m_y / m_x));
}

Vector::Vector(const Size& projection)
{
    m_x = projection.width;
    m_y = projection.height;
    m_angle = static_cast<int>(atan(m_y / m_x));
}

void Vector::rotate(int angle)
{
    m_angle = (m_angle + angle) % FullAngle;
}

int Vector::projection(const Axis &axis)
{
    return axis == AxisX ? m_x : m_y;

}

double Vector::module()
{
    return m_x * m_x + m_y * m_y;
}

Vector Vector::getProjectionVector(const Axis &axis)
{
    int module = projection(axis);
    int angle = module >= 0 ? 0 : StraightAngle;
    return Vector(module, angle);
}

Point Vector::end(const Point& start)
{
    return Point(start.x + m_x, start.y + m_y);
}

Point Vector::start(const Point &end)
{
    return Point(end.x - m_x, end.y - m_y);
}
