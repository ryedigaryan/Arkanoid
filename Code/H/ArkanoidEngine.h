//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

#include <Definitions/CommonDefinitions.h>

class ArkanoidEngine {
public:
    void process();
    int getProgress();

    void movePlayer(Side side);
    void stopPlayer();

private:
    Side m_playerMovementDirection = Side::None;
};

#endif //ARCANOID_GAMEENGINE_H
