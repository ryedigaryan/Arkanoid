//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BRICK_H
#define ARCANOID_BRICK_H

#include "Models/Interfaces/GameObject.h"
#include "Models/Interfaces/Mortal.h"

class Brick : public GameObject, public Mortal {
public:
    Brick(Point position = Point(), Size size = Size(), int texture = 0, int initialHealth = 0)
            : GameObject(position, size, texture), Mortal(initialHealth) {}

    virtual void harm(int damage) {
        m_health -= damage;
        m_delegate->go_healthChanged(m_identifier, m_health, damage);
    };
};

#endif //ARCANOID_BRICK_H
