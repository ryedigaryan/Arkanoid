//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include <ctime>
#include "Interfaces/ArkanoidEngineDelegate.h"
#include "Geometry/Geometry.h"
#include "Models/Level.h"
#include "Definitions/CommonDefinitions.h"
#include "Models/Interfaces/GameObject.h"

enum LevelState {
    LevelStateLost = 0,
    LevelStateWon,
    LevelStateInProcess,
};

class ArkanoidEngine
{
public:
    ArkanoidEngine() : m_delegate(nullptr), m_level(Level(0, BricksDistance, BricksCountOnPlayer)), m_playerMovementDirection(SideNone)
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

public: // actions
    void setLevel(Level& level);
    void process();
    void movePlayer(Side side);
    void stopPlayer();

public: // info getters
    int getProgress() const;
    LevelState getState() const;
    const Level& getLevel() const;

    ArkanoidEngineDelegate* m_delegate;

private: // data
    Level m_level;
    LevelState m_state;
    Side m_playerMovementDirection;
    unsigned m_bricksMaxCount;

private: // functions
    void processPlayer();
    void processBall();

    Rect processBallBrickCollision();
    Rect processBallBorderCollision();
    Rect processBallPlayerCollision();
    float ballAngleAfterHittingPlayer();

    Rect rectAfterMoving(const Movable &movable);

    int  predictCollisionSides(const Rect& first, const Rect& movedFirst, const Rect& second);
    bool willCollide(const Movable &first, const GameObject &second);
    bool areColliding(Rect first, Rect second);
};

#endif //ARCANOID_GAMEENGINE_H
