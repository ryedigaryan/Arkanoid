//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMECONTROLLER_H
#define ARCANOID_GAMECONTROLLER_H

#include "GameStates/AllStates.h"
#include "Definitions/CommonDefinitions.h"
#include "StateMachine.h"

class ArkanoidGameController {
public:
    ArkanoidGameController();

    void start();
private:
    GameData m_gameData;
};

#endif //ARCANOID_GAMECONTROLLER_H
