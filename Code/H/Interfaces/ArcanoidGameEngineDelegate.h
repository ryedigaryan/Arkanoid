//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H
#define ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H

class ArcanoidGameEngineDelegate {
public:
    virtual void engine_willLoadLevel()			     = 0;
    // actually the Level also must be an object of specific type
    // but for less complexity i just think about it as part of engine
    //TODO(Low priority): separate level form engine, create delegate for it
    virtual void engine_levelSizeSet(Size levelSize) = 0;
    virtual void engine_levelLoaded()                = 0;
    virtual void engine_willStartLevel()		     = 0;
    virtual void engine_levelStarted()			     = 0;
    virtual void engine_paused()				     = 0;
    virtual void engine_unpaused()				     = 0;
    virtual void engine_levelEnded(bool hasWon)	     = 0;
};

#endif //ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H
