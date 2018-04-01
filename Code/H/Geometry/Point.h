//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_POINT_H
#define ARCANOID_POINT_H

enum Axis {
    AxisX,
    AxisY
};

class Point {
public:
    Point(int x = 0, int y = 0)
            : x(x), y(y) {}

public:
    int x;
    int y;
};

#endif //ARCANOID_POINT_H
