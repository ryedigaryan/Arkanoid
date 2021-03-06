//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BRICK_H
#define ARCANOID_BRICK_H

#include "Models/Interfaces/GameObject.h"
#include "Models/Interfaces/Mortal.h"

class Brick : public GameObject, public Mortal {
public:
    Brick(const std::string& texturePath = "", GameObjectType type = TBrick, Point position = Point(), Size size = Size(), int initialHealth = BrickDefaultInitialHealth)
            : GameObject(texturePath, type, position, size), Mortal(initialHealth) {}

    void harm(int damage) override {
        m_health -= damage;
        m_delegate->go_healthChanged(m_identifier, m_health, damage);
    };
};

#endif //ARCANOID_BRICK_H
