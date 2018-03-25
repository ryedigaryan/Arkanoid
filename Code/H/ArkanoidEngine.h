//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEENGINE_H
#define ARCANOID_GAMEENGINE_H

class ArkanoidEngine {
public:
    virtual void process();
    virtual int getProgress();
};

#endif //ARCANOID_GAMEENGINE_H
