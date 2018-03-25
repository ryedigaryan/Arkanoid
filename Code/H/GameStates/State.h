//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_STATE_H
#define ARCANOID_STATE_H

#include "Definitions/CommonDefinitions.h"

#include "GameData.h"
#include "Interfaces/StateDelegate.h"

class State {
public:
    State(GameData* gameData, StateDelegate* dlgate) : m_gameData(gameData), m_delegate(dlgate) {}

    virtual void handleInput() = 0;
    virtual void update() = 0;

protected:
    StateDelegate* m_delegate;
    GameData* m_gameData;
};

#endif //ARCANOID_STATE_H
