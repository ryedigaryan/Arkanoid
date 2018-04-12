//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include <Interfaces/ArkanoidEngineDelegate.h>
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
    ArkanoidEngine() : m_delegate(nullptr), m_level(Level(0, BricksDistance, BricksCountOnPlayer)), m_playerMovementDirection(SideNone)
    {

    }

public:
    void setLevel(Level& level);
    void process();
    int getProgress();

    void movePlayer(Side side);
    void stopPlayer();

    LevelState getLevelState();
    Level& getLevel();

    ArkanoidEngineDelegate* m_delegate;

private:
    Side m_playerMovementDirection;
    Level m_level;
    LevelState m_state;
};

#endif //ARCANOID_GAMEENGINE_H
