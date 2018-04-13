//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BALL_H
#define ARCANOID_BALL_H

#include "Models/Interfaces/GameObject.h"
#include "Models/Interfaces/Movable.h"
#include "Models/Interfaces/Attacker.h"

class Ball : public Movable, public Attacker {
public:
    explicit Ball(Point position = Point(), Size size = Size(), Vector initialVelocity = Vector(), int damage = 1)
            : GameObject(ObjectTypeBall, position, size), Movable(initialVelocity), Attacker(damage) {}

    void move() override {
        m_position.x += m_velocity.getProjection(AxisX);
        m_position.y += m_velocity.getProjection(AxisY);
        m_delegate->go_moved(m_identifier, m_position);
    }

    void setVelocity(int module, int angle) override {
        m_velocity.m_module = module;
        m_velocity.m_angle = angle;
    }
};

#endif //ARCANOID_BALL_H
