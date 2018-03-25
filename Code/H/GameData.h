//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEDATA_H
#define ARCANOID_GAMEDATA_H

#include <SFML/Graphics.hpp>
#include <ArkanoidDrawer.h>
#include "ArkanoidEngine.h"

struct GameData {
    ArkanoidEngine* engine;
    ArkanoidDrawer* drawer;
};

#endif //ARCANOID_GAMEDATA_H
