//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include "Models/Level.h"
#include "Definitions/CommonDefinitions.h"
#include "Models/Interfaces/GameObject.h"

enum LevelState {
    LevelStateLost = 0,
    LevelStateWon,
    LevelStateInProcess,
};

class ArkanoidEngine {
public:
    void setLevel(Level& level);
    void process();
    int getProgress();

    void movePlayer(Side side);
    void stopPlayer();

    LevelState getLevelState();
    Level& getLevel();

private:
    Side m_playerMovementDirection = SideNone;
    Level m_level;
    LevelState m_state;
};

#endif //ARCANOID_GAMEENGINE_H
