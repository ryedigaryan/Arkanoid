//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_POINT_H
#define ARCANOID_POINT_H

#include "../Definitions.h"

class Point {
public:
    Point(int x = PointDefaultValueX, int y = PointDefaultValueY)
            : x(x), y(y) {}

public:
    int x;
    int y;
};

#endif //ARCANOID_POINT_H
