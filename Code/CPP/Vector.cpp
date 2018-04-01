//
// Created by ryedigaryan on 2/26/2018.
//

#include "Geometry/Vector.h"
#include <cmath>

void Vector::rotate(int angle) {
    m_angle = (m_angle + angle) % FullAngle;
}

int Vector::getProjection(const Axis& axis)
{
    return (int)(AxisX == axis ?
           m_module * cos(m_angle * M_PI / StraightAngle)
                               : m_module * sin(m_angle * M_PI / StraightAngle));

}

Vector Vector::getProjectionVector(const Axis &axis) {
    int module = getProjection(axis);
    int angle = module > 0 ? 0 : StraightAngle;
    return Vector(module, angle);
}

Point Vector::end(const Point& start) {
    return Point((int)(start.x + m_module * cos(m_angle)),
                 (int)(start.y + m_module * sin(m_angle)));
}

Point Vector::start(const Point &end) {
    return Point((int)(end.x - m_module * cos(m_angle)),
                 (int)(end.y - m_module * sin(m_angle)));
}
