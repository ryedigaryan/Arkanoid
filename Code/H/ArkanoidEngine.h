//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

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

    }

public:
    void setLevel(Level& level);
    void process();
    int getProgress();

    void movePlayer(Side side);
    void stopPlayer();

    LevelState getState();
    Level& getLevel();

    ArkanoidEngineDelegate* m_delegate;
    Side m_playerMovementDirection;

private:
    Level m_level;
    LevelState m_state;
    unsigned m_bricksMaxCount;
    int   predictCollisionSides(const Rect& first, const Rect& movedFirst, const Rect& second);
    Rect  rectAfterMoving(const Movable &movable);
    bool  willCollide(const Movable &first, const GameObject &second);
    bool  areColliding(Rect first, Rect second);
    Side  collisionSide(const Movable& first, const GameObject& second);
    void  processPlayer();
    void  processBall();
    Rect  processBallBrickCollision();
    Rect  processBallBorderCollision();
    Rect  processBallPlayerCollision();
    Rect  removeBrick(std::list<Brick*>::iterator it_brick);
};

#endif //ARCANOID_GAMEENGINE_H
