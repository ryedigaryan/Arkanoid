//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMINGSTATE_H
#define ARCANOID_GAMINGSTATE_H

#include "State.h"
#include "Interfaces/GameEngineDelegate.h"
#include "PausedState.h"
#include "LevelEndState.h"

class GamingState : public State, public GameEngineDelegate {
public:
    explicit GamingState(GameData *gameData);

    void init()        override;
    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

private:
    unsigned m_currentLevel;
};

#endif //ARCANOID_GAMINGSTATE_H
