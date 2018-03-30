//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_STATE_H
#define ARCANOID_STATE_H

#include "Definitions/CommonDefinitions.h"
#include "GameData.h"

class State {
public:
    State(GameData* gameData) : m_gameData(gameData) {}

    virtual void handleInput() = 0;
    virtual void update()      = 0;
    virtual void pause()       = 0;
    virtual void resume()      = 0;

protected:
    GameData* m_gameData;
};

#endif //ARCANOID_STATE_H
