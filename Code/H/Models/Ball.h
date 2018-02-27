//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BALL_H
#define ARCANOID_BALL_H

#include "Models/Interfaces/GameObject.h"
#include "Models/Interfaces/Movable.h"
#include "Models/Interfaces/Attacker.h"

class Ball : public GameObject, public Movable, public Attacker {
public:
    Ball(Point position = Point(), Size size = Size(), Vector initialVelocity = Vector(), int damage = 1)
            : GameObject(position, size), Movable(initialVelocity), Attacker(damage) {}

    virtual void move(int dx, int dy) {
        m_position.x += dx;
        m_position.y += dy;
        m_delegate->go_moved(m_identifier, m_position);
    }
};

#endif //ARCANOID_BALL_H
