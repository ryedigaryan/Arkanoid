//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BORDER_H
#define ARCANOID_BORDER_H

#include "Models/Interfaces/GameObject.h"

class Border : public GameObject, public Mortal {
public:
    Border(const string& texturePath = "", GameObjectType type = TBorder, Point position = Point(), Size size = Size())
            : GameObject(texturePath, type, position, size) {}

    void harm(int damage) override {
        // nothing must be done ... as the border is immortal
    }
};

#endif //ARCANOID_BORDER_H
