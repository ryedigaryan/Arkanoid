//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_LEVELENDSTATE_H
#define ARCANOID_LEVELENDSTATE_H

#include "StaticImageState.h"

class LevelEndState : public StaticImageState {
public:
    LevelEndState(GameData* gameData, const unsigned& level, const bool& hasWon);

    void update()      override;

    bool m_hasWon;
    unsigned m_level;
};

#endif //ARCANOID_LEVELENDSTATE_H
