//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_VECTOR_H
#define ARCANOID_VECTOR_H

#include "../Definitions.h"

class Vector {
public:
    Vector(int module = 0, int angle = 0) : m_module(module), m_angle(angle) {}

    void rotate(int angle);

    int getProjection(Axis axis);

    int m_module;
    int m_angle;
};

#endif //ARCANOID_VECTOR_H
