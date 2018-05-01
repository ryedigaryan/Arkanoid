//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include "Interfaces/ArkanoidEngineDelegate.h"
#include "Geometry/Rect.h"
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
    int getProgress(bool change = true);

    void movePlayer(Side side);
    void stopPlayer();

    LevelState getState();
    Level& getLevel();

    ArkanoidEngineDelegate* m_delegate;
    Side m_playerMovementDirection;

private:
    Level m_level;
    LevelState m_state;
    Point predictCollision(const Movable& first, const GameObject& second);
    Point predictCollision(const Movable& first, const Movable& second);
    int predictCollisionSides(const Rect& first, const Rect& movedFirst, const Rect& second);
    Rect rectAfterMoving(const Movable &movable);
    Point lineIntersection(Line l1, Line l2);
    Vector vector(GameObject from, Rect to);
    void processPlayer();
    void processBall();
//    bool
};

#endif //ARCANOID_GAMEENGINE_H
