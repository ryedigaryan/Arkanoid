//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include "Models/Level.h"
#include "Definitions/CommonDefinitions.h"
#include "Models/Interfaces/GameObject.h"

enum LevelState {
    LevelStateWon,
    LevelStateLost,
    LevelStateNone,
};

class ArkanoidEngine {
public:
    void setLevel(Level& level);
    void process();
    int getProgress();

    void movePlayer(Side side);
    void stopPlayer();

    LevelState getLevelState();

private:
    Side m_playerMovementDirection = SideNone;
    Level m_level;
};

#endif //ARCANOID_GAMEENGINE_H
