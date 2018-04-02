//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process() {

}

int ArkanoidEngine::getProgress() {
    return -1;
}

void ArkanoidEngine::movePlayer(Side side) {
    if(side == Side::SideLeft || side == Side::SideRight) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer() {
    m_playerMovementDirection = Side::SideNone;
}

LevelState ArkanoidEngine::getLevelState() {
    return LevelStateWon;
}

void ArkanoidEngine::setLevel(Level& level) {
    m_level = level;
}