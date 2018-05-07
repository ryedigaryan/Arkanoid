//
// Created by ruben on 4/13/2018.
//

#ifndef ARCANOID_RECT_H
#define ARCANOID_RECT_H

#include <utility>
#include "Definitions/CommonDefinitions.h"
#include "Point.h"

typedef std::pair<Point, Point> Line;

class Rect
{
public:
    explicit Rect(Point position = Point(), Size size = Size()) noexcept
            : m_position(position), m_size(size), left(position.x), top(position.y), width(size.width), height(size.height) {}

    int left;
    int top;
    int width;
    int height;
    Line side(Side side);

    int right() const;
    int bottom() const;
    Point position();
    Size size();

    bool operator ==(const Rect& other);
    bool operator !=(const Rect& other);

    void log(const std::string &front = "", const std::string &back = "\n") const {
        logstream << front;
        logstream << "left: " << left << " top: " << top << " w: " << width << " h: " << height;
        logstream << back;
    }

private:
    Point m_position;
    Size m_size;
};

#endif //ARCANOID_RECT_H
