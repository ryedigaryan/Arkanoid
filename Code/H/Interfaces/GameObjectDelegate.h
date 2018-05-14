//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMEOBJECTDELEGATE_H
#define ARCANOID_GAMEOBJECTDELEGATE_H

#include "Geometry/Geometry.h"

class GameObjectDelegate
{
public:
    // go stands for "Game Object"
    virtual void go_moved(unsigned go_id, const float& dx, const float& dy) 		    = 0;
    virtual void go_sizeChanged(unsigned go_id, const Size& go_size)					= 0;
    virtual void go_healthChanged(unsigned go_id, int go_health, int go_healthChange)	= 0;
//    virtual void go_isAtPeaceNow(unsigned go_id)										= 0;
};

#endif //ARCANOID_GAMEOBJECTDELEGATE_H
