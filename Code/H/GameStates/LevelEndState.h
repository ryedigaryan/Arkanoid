//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_LEVELENDSTATE_H
#define ARCANOID_LEVELENDSTATE_H

#include "StaticImageState.h"
#include "EntireGameWonState.h"

class LevelEndState : public StaticImageState {
public:
    LevelEndState(GameData* gameData, const unsigned& level, const bool& hasWon, const unsigned& maxLevel);

    void init() override;
    void draw() override;

    bool m_hasWon;
    unsigned m_level;
    unsigned m_lastLevel;
};

#endif //ARCANOID_LEVELENDSTATE_H
