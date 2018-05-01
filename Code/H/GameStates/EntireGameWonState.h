//
// Created by ryedigaryan on 4/2/2018.
//

#ifndef ARCANOID_ENTIREGAMEWONSTATE_H
#define ARCANOID_ENTIREGAMEWONSTATE_H

#include "StaticImageState.h"

class EntireGameWonState : public StaticImageState {
public:
    explicit EntireGameWonState(GameData* gameData);

    void draw()      override;

};

#endif //ARCANOID_ENTIREGAMEWONSTATE_H
