//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_GAMEOBJECTDELEGATE_H
#define ARCANOID_GAMEOBJECTDELEGATE_H

#include "Geometry/Geometry.h"

class GameObject;

class GameObjectDelegate {
public:
    // go stands for "game object"
    virtual void go_delegateSet(const GameObject *go)								= 0;
    virtual void go_moved(unsigned go_id, const Point& go_position)						= 0;
    virtual void go_sizeChanged(unsigned go_id, const Size& go_size)					= 0;
    virtual void go_healthChanged(unsigned go_id, int go_health, int go_healthChange)	= 0;
    virtual void go_isAtPeaceNow(unsigned go_id)										= 0;
};


#endif //ARCANOID_GAMEOBJECTDELEGATE_H
