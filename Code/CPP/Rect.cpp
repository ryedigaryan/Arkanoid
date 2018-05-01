//
// Created by ruben on 4/13/2018.
//

#include "Geometry/Rect.h"

Line Rect::side(Side side) {
    switch(side) {
        case SideLeft:
            return Line(Point(left, top), Point(left, bottom()));
        case SideRight:
            return Line(Point(right(), top), Point(right(), bottom()));
        case SideUp:
            return Line(Point(left, top), Point(right(), top));
        case SideDown:
            return Line(Point(left, bottom()), Point(right(), bottom()));
        default:
            return Line(Point(), Point());
    }
}

int Rect::right() const
{
    return left + width;
}

int Rect::bottom() const
{
    return top + height;
}

bool Rect::operator==(const Rect& other) {
    return this->left == other.left && this->top == other.top && this->width == other.width && this->height == other.height;
}

bool Rect::operator!=(const Rect& other) {
    // this implementation is faster than !(*this == other)
    return this->left != other.left || this->top != other.top || this->width != other.width || this->height != other.height;
}

Point Rect::position() {
    return m_position;
}

Size Rect::size() {
    return m_size;
}
