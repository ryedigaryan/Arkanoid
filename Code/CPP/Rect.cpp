//
// Created by ruben on 4/13/2018.
//

#include "Geometry/Rect.h"

Line Rect::getSide(Side side) {
    switch(side) {
        case SideLeft:
            return Line(position, Point(position.x, position.y + size.height));
        case SideRight:
            return Line(Point(position.x + size.width, position.y), position + size);
        case SideUp:
            return Line(position, Point(position.x + size.width, position.y));
        case SideDown:
            return Line(Point(position.x, position.y + size.height), position + size);
        case SideNone:
            return Line(Point(), Point());
    }
}
