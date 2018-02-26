//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_MOVABLE_H
#define ARCANOID_MOVABLE_H

#include "../../Geometry/Vector.h"

class Movable {
public:
    virtual void move(int dx, int dy) = 0;

protected:
    Movable(Vector velocity = Vector()) : m_velocity(velocity) {}

    Vector m_velocity;
};

#endif //ARCANOID_MOVABLE_H
