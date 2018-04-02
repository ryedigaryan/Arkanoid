//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_PAUSEDSTATE_H
#define ARCANOID_PAUSEDSTATE_H

#include "StaticImageState.h"

class PausedState : public StaticImageState {
public:
    PausedState(GameData* gameData, const unsigned& level, const int& progress);

    void update()      override;

    unsigned m_level;
    const int m_progress;
};

#endif //ARCANOID_PAUSEDSTATE_H
