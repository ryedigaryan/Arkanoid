//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_MAINMENUSTATE_H
#define ARCANOID_MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State {
public:
    explicit MainMenuState(GameData *gameData, StateDelegate* dlgate = nullptr);

    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

private:
    bool m_needsRedraw;
};

#endif //ARCANOID_MAINMENUSTATE_H
