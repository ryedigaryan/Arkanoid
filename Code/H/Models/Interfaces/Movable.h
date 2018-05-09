//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_MOVABLE_H
#define ARCANOID_MOVABLE_H

#include "Geometry/Vector.h"
#include "GameObject.h"

class Movable : public virtual GameObject {
public:
    virtual void move()                                        = 0;

    virtual void setVelocity(int xProjection, int yProjection) {
        m_velocity.setProjection(xProjection, yProjection);
    }

    virtual void setVelocity(Vector velocity)
    {
        setVelocity(velocity.projection(AxisX), velocity.projection(AxisY));
    }

    virtual const Vector& getVelocity() const
    {
        return m_velocity;
    }

    virtual Vector& getVelocity() {
        return m_velocity;
    }

protected:
    explicit Movable(Vector velocity) : GameObject(ObjectTypeNone), m_velocity(velocity) {}

    Vector m_velocity;
};

#endif //ARCANOID_MOVABLE_H
