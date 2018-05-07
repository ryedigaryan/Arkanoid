//
// Created by ruben on 5/6/2018.
//

#include "Geometry/Line.h"

Line::Line(Point start, Point end) : m_start(start), m_end(end)
{
    k = static_cast<float>(m_start.y - m_end.y) / (m_start.x - m_end.x);
    b = (m_start.y - k * m_start.x);
}

float Line::yAt(const float& x) const
{
    return k * x + b;
}

float Line::xAt(const float &y) const
{
    return (y - b) / k;
}

Point Line::intersection(const Line& other) const
{
//    float k1 = static_cast<float>(m_start.y - m_end.y) / (m_start.x - m_end.x);
//    float k2 = static_cast<float>(other.m_start.y - other.m_end.y) / (other.m_start.x - other.m_end.x);
//
//    float b1 = (m_start.y - k1 * m_start.x);
//    float b2 = (other.m_start.y - k2 * other.m_start.x);

    float interX = (other.b - b) / (k - other.k);
    float interY = yAt(interX);

    return Point(static_cast<int>(interX), static_cast<int>(interY));
}

bool Line::contains(Point point) const
{
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
