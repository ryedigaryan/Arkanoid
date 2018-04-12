//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process()
{

}

int ArkanoidEngine::getProgress(bool change)
{
    static int p = 0;
    if(p > 100) {
        m_state = LevelStateWon;
        p = 0;
    }
    return change ? p+=20 : p;
}

void ArkanoidEngine::movePlayer(Side side) {
    if(side == SideLeft || side == SideRight) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer() {
    m_playerMovementDirection = SideNone;
}

LevelState ArkanoidEngine::getState() {
    return m_state;
}

void ArkanoidEngine::setLevel(Level& level) {
    m_level = level;
    m_state = LevelStateInProcess;
    m_delegate->engine_levelSet(m_level);
}

Level& ArkanoidEngine::getLevel() {
    return m_level;
}
