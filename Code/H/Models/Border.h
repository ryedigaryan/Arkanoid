//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_BORDER_H
#define ARCANOID_BORDER_H

#include "Models/Interfaces/GameObject.h"

class Border : public GameObject {
public:
    explicit Border(Point position = Point(), Size size = Size())
            : GameObject(position, size) {}
};

#endif //ARCANOID_BORDER_H
