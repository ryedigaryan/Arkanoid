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
    if(side == Side::Left || side == Side::Right) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer() {
    m_playerMovementDirection = Side::None;
}

bool ArkanoidEngine::hasWon() {
    return true;
}
