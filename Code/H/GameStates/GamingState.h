//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMINGSTATE_H
#define ARCANOID_GAMINGSTATE_H

#include "State.h"

class GamingState : public State {
public:
    explicit GamingState(GameData *gameData, StateDelegate* dlgate = nullptr) : State(gameData, dlgate) {}

    void handleInput() override;
    void update() override;
};

#endif //ARCANOID_GAMINGSTATE_H
