//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_MORTAL_H
#define ARCANOID_MORTAL_H

#include "GameObject.h"

class Mortal : public virtual GameObject {
public:
    virtual void harm(int damage) = 0;
    virtual int getHealth()
    {
        return m_health;
    }

protected:
    explicit Mortal(int health = 1) : GameObject(ObjectTypeNone), m_health(health) {}

    int m_health;
};

#endif //ARCANOID_MORTAL_H
