//
// Created by ruben on 5/6/2018.
//

#include "Geometry/Geometry.h"

Line::Line(Point start, Point end) : m_start(start), m_end(end)
{
    m_k = static_cast<float>(m_start.y - m_end.y) / (m_start.x - m_end.x);
    m_b = (m_start.y - m_k * m_start.x);
}

float Line::yAt(const float& x) const
{
    if(isVertical()) {
        return x == m_start.x;
    }
    return m_k * x + m_b;
}

float Line::xAt(const float& y) const
{
    if(isVertical()) {
        return m_start.x;
    }
    return (y - m_b) / m_k;
}

Point Line::intersection(const Line& other, bool considerEdges) const
{
//    float k1 = static_cast<float>(m_start.y - m_end.y) / (m_start.x - m_end.x);
//    float k2 = static_cast<float>(other.m_start.y - other.m_end.y) / (other.m_start.x - other.m_end.x);
//
//    float b1 = (m_start.y - k1 * m_start.x);
//    float b2 = (other.m_start.y - k2 * other.m_start.x);

    float interX;
    float interY;

    if(isVertical()) {
        interX = m_start.x;
        interY = other.yAt(interX);
    }
    else if(other.isVertical()) {
        interX = other.m_start.x;
        interY = yAt(interX);
    }
    else {
        interX = (other.m_b - m_b) / (m_k - other.m_k);
        interY = yAt(interX);
    }

    auto result = Point(interX, interY);
    if(considerEdges) {
        if(!contains(result, true) || !other.contains(result, true)) {
            return ILLEGAL_POINT;
        }
    }
    return result;
}

bool Line::isVertical() const
{
    return m_start.x == m_end.x;
}

bool Line::contains(Point point, bool considerEdges) const
{
    if(considerEdges) {
        if(!(std::min(m_start.x, m_end.x) <= point.x && point.x <= std::max(m_start.x, m_end.x) &&
             std::min(m_start.y, m_end.y) <= point.y && point.y <= std::max(m_start.y, m_end.y))) {
            return false;
        }
    }
    return std::abs(yAt(point.x) - point.y) < Approximation;
}

bool Line::isInside(Line first, Line second) const
{
    return m_start.isInside(first, second) && m_end.isInside(first, second);
}

bool Line::operator==(const Line& other) const
{
    return m_start == other.m_start && m_end == other.m_end;
}

bool Line::operator!=(const Line &other) const
{
    return m_start != other.m_start || m_end != other.m_end;
}
