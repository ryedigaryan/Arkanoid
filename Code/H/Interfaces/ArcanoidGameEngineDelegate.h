//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H
#define ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H

class ArcanoidGameEngineDelegate {
public:
    virtual void engine_willLoadLevel()			= 0;
    virtual void engine_levelLoaded()			= 0;
    virtual void engine_willStartLevel()		= 0;
    virtual void engine_levelStarted()			= 0;
    virtual void engine_paused()				= 0;
    virtual void engine_unpaused()				= 0;
    virtual void engine_levelEnded(bool hasWon)	= 0;
};

#endif //ARCANOID_ARCANOIDGAMEENGINEDELEGATE_H
