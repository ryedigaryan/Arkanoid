//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ATTACKER_H
#define ARCANOID_ATTACKER_H

#include "Mortal.h"
#include "GameObject.h"

class Attacker : public virtual GameObject {
public:
    explicit Attacker(int damage = 0)
            : GameObject(), m_damage(damage) {}

    virtual void attack(Mortal& mortal)
    {
        mortal.harm(m_damage);
    }

protected:
    int m_damage;
};

#endif //ARCANOID_ATTACKER_H
