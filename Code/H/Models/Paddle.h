//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_PADDLE_H
#define ARCANOID_PADDLE_H

#include "Models/Interfaces/GameObject.h"
#include "Models/Interfaces/Movable.h"
#include "Models/Interfaces/Mortal.h"

class Paddle : public GameObject, public Movable, public Mortal {
public:
    Paddle(const std::string& texturePath = "", GameObjectType type = TPaddle, Point position = Point(), Size size = Size(), Vector initialVelocity = Vector(), int initialHealth = PaddleDefaultInitialHealth)
            : GameObject(texturePath, type, position, size), Movable(initialVelocity), Mortal(initialHealth) {}

    void move(int dx, int dy) override {
        m_position.x += dx;
        m_position.y += dy;
        m_delegate->go_moved(m_identifier, m_position);
    }

    void harm(int damage) override {
        m_health -= damage;
        m_delegate->go_healthChanged(m_identifier, m_health, damage);
    };
};

#endif //ARCANOID_PADDLE_H
