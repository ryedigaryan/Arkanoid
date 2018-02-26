//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEDRAWERDELEGATE_H
#define ARCANOID_ARCANOIDGAMEDRAWERDELEGATE_H

class ArcanoidGameDrawerDelegate {
public:
    virtual void drawer_startPressed()		= 0;
    virtual void drawer_donePressed()		= 0;
    virtual void drawer_mainMenuPressed()	= 0;
    virtual void drawer_pausePressed()		= 0;
    virtual void drawer_unpausePressed()	= 0;
};

#endif //ARCANOID_ARCANOIDGAMEDRAWERDELEGATE_H
