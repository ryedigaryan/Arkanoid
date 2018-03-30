//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_LEVELENDSTATE_H
#define ARCANOID_LEVELENDSTATE_H

#include "State.h"

class LevelEndSatate : public State {
public:
    explicit LevelEndSatate(GameData *gameData);

    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

private:
    bool m_needsRedraw;
};

#endif //ARCANOID_LEVELENDSTATE_H
