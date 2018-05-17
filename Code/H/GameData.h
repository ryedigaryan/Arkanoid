//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEDATA_H
#define ARCANOID_GAMEDATA_H

#include "ArkanoidEngine.h"
#include "ArkanoidDrawer.h"
#include "StateMachine.h"

struct GameData {
    ArkanoidEngine* engine;
    ArkanoidDrawer* drawer;
    StateMachine* stateMachine;
    ResourceManager* resourceManager;
    unsigned lostLevel = FirstLevelNumber;
};

#endif //ARCANOID_GAMEDATA_H
