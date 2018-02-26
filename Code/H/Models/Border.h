//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BORDER_H
#define ARCANOID_BORDER_H

#include "Interfaces/GameObject.h"

class Border : public GameObject, public Mortal {
public:
    Border(Point position = Point(), Size size = Size(), int texture = 0)
            : GameObject(position, size, texture) {}

    void harm(int damage) {
        // nothing must be done ... as the border is immortal
    }
};

#endif //ARCANOID_BORDER_H
