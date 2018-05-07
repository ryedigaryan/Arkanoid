//
// Created by ruben on 3/26/2018.
//

#ifndef ARCANOID_GAMEENGINEDELEGATE_H
#define ARCANOID_GAMEENGINEDELEGATE_H

#include "Models/Level.h"

class ArkanoidEngineDelegate
{
public:
    virtual void engine_levelSet(const Level& level) = 0;
};

#endif //ARCANOID_GAMEENGINEDELEGATE_H
