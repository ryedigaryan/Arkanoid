//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_LEVELENDSTATE_H
#define ARCANOID_LEVELENDSTATE_H

#include "State.h"

class LevelEndSatate : public State {
public:
    explicit LevelEndSatate(GameData *gameData, StateDelegate* dlgate = nullptr) : State(gameData, dlgate) {}

    void handleInput() override;
    void update() override;
};

#endif //ARCANOID_LEVELENDSTATE_H
