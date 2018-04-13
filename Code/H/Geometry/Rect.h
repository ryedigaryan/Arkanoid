//
// Created by ruben on 4/13/2018.
//

#ifndef ARCANOID_RECT_H
#define ARCANOID_RECT_H

#include <utility>
#include "Definitions/CommonDefinitions.h"
#include "Point.h"

typedef std::pair<Point, Point> Line;

class Rect {
public:
    Rect(Point pos, Size siz)
            : position(pos), size(siz), x(pos.x), y(pos.y), width(size.width), height(size.height) {}

    int x;
    int y;
    int width;
    int height;
    Line getSide(Side side);

private:
    Point position;
    Size size;
};

#endif //ARCANOID_RECT_H
