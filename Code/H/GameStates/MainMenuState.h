//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_MAINMENUSTATE_H
#define ARCANOID_MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State {
public:
    explicit MainMenuState(GameData *gameData, StateDelegate* dlgate = nullptr) : State(gameData, dlgate) {}

    void handleInput() override;
    void update() override;
};

#endif //ARCANOID_MAINMENUSTATE_H
