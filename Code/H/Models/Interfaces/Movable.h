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

    virtual void setVelocity(float xProjection, float yProjection) {
        m_velocity.setProjection(xProjection, yProjection);
    }

    virtual void setVelocity(Side direction, const float& module)
    {
        switch(direction) {
            case SideLeft:
                m_velocity.setProjection(-module, 0);
                break;
            case SideRight:
                m_velocity.setProjection(module, 0);
                break;
            case SideUp:
                m_velocity.setProjection(0, -module);
                break;
            case SideDown:
                m_velocity.setProjection(0, module);
                break;
            case SideNone:
                m_velocity.setProjection(0, 0);
                break;
        }
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
