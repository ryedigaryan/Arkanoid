//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_PAUSEDSTATE_H
#define ARCANOID_PAUSEDSTATE_H

#include "State.h"

class PausedState : public State {
public:
    explicit PausedState(GameData *gameData);

    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

private:
    bool m_needsRedraw;
};

#endif //ARCANOID_PAUSEDSTATE_H
