//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMECONTROLLER_H
#define ARCANOID_GAMECONTROLLER_H

#include "GameStates/MainMenuState.h"
#include "GameStates/PausedState.h"
#include "GameStates/GamingState.h"
#include "GameStates/LevelEndState.h"
#include "Definitions/CommonDefinitions.h"
#include "GameData.h"
#include "StateMachine.h"

class ArkanoidGameController : private StateDelegate {
public:
    ArkanoidGameController();

    void start();
private:
    GameData m_gameData;
    StateMachine m_stateMachine;
    std::vector<State*> m_allStates;

    State* nextState();
    void pushNextState() override;
};

#endif //ARCANOID_GAMECONTROLLER_H
