//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process() {

}

int ArkanoidEngine::getProgress() {
    static int p = 0;
    if(p == 3) {
        m_state = LevelStateWon;
        p = 0;
    }
    return p++;
}

void ArkanoidEngine::movePlayer(Side side) {
    if(side == SideLeft || side == SideRight) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer() {
    m_playerMovementDirection = SideNone;
}

LevelState ArkanoidEngine::getLevelState() {
    return m_state;
}

void ArkanoidEngine::setLevel(Level& level) {
    m_level = level;
    m_state = LevelStateInProcess;
}

Level &ArkanoidEngine::getLevel() {
    return m_level;
}
