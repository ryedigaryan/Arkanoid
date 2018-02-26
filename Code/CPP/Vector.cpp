//
// Created by ryedigaryan on 2/26/2018.
//

#include "../H/Geometry/Vector.h"
#include <cmath>

void Vector::rotate(int angle) {
    m_angle = (m_angle + angle) % FullAngle;
}

int Vector::getProjection(Axis axis)
{
    return (int)(axis == Axis::X ?
           m_module * cos(m_angle * PI / StraightAngle)
                           : m_module * sin(m_angle * PI / StraightAngle));

}
