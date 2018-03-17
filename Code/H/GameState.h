//
// Created by ryedigaryan on 3/17/2018.
//

#ifndef ARCANOID_GAMESTATE_H
#define ARCANOID_GAMESTATE_H

class GameState {
public:
    GameState();
    virtual void handleInput() = 0;
    virtual void draw() = 0;
};

#endif //ARCANOID_GAMESTATE_H
