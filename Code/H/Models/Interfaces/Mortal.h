//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_MORTAL_H
#define ARCANOID_MORTAL_H

class Mortal {
public:
    virtual void harm(int damage) = 0;
    //virtual void heal(int diff) = 0;

protected:
    explicit Mortal(int health = 1) : m_health(health) {}

    int m_health;
};

#endif //ARCANOID_MORTAL_H
