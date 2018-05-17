//
// Created by ruben on 4/13/2018.
//

#include "Geometry/Rect.h"

float Rect::right() const
{
    return left + width;
}

float Rect::bottom() const
{
    return top + height;
}

bool Rect::operator==(const Rect& other)
{
    return this->left == other.left && this->top == other.top && this->width == other.width && this->height == other.height;
}

bool Rect::operator!=(const Rect& other)
{
    // this implementation is faster than !(*this == other)
    return this->left != other.left || this->top != other.top || this->width != other.width || this->height != other.height;
}

Point Rect::position() const
{
    return m_position;
}

Size Rect::size() const
{
    return m_size;
}
