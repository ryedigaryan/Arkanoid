//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_MAINMENUSTATE_H
#define ARCANOID_MAINMENUSTATE_H

#include <UI/Drawers/MenuDrawer.h>
#include "State.h"
#include "GameStates/GamingState.h"

class MainMenuState : public StaticImageState {
public:
    explicit MainMenuState(GameData* gameData);

    void handleInput() override;
    void draw()        override;

private:
    MenuDrawer m_drawer;
};

#endif //ARCANOID_MAINMENUSTATE_H
