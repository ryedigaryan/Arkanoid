//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_LEVELENDSTATE_H
#define ARCANOID_LEVELENDSTATE_H

#include "State.h"

class LevelEndState : public State {
public:
    LevelEndState(GameData *gameData, const unsigned& level, const bool& hasWon);

    void init()        override;
    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

    bool m_hasWon;
    unsigned m_level;

private:
    bool m_needsRedraw;
};

#endif //ARCANOID_LEVELENDSTATE_H
