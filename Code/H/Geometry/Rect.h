//
// Created by ruben on 4/13/2018.
//

#ifndef ARCANOID_RECT_H
#define ARCANOID_RECT_H

#include <utility>
#include "Definitions/CommonDefinitions.h"
#include "Point.h"
#include "Line.h"

class Rect
{
public:
    explicit Rect(Point position = Point(), Size size = Size()) noexcept
            : m_position(position), m_size(size), left(position.x), top(position.y), width(size.width), height(size.height) {}

    float left;
    float top;
    float width;
    float height;

    float   right()         const;
    float   bottom()        const;
    Point position()      const;
    Size  size()          const;
    Line  side(Side side) const;

    bool operator ==(const Rect& other);
    bool operator !=(const Rect& other);

private:
    Point m_position;
    Size m_size;
};

#endif //ARCANOID_RECT_H
