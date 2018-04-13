//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process()
{
    if(m_playerMovementDirection != SideNone) {
        Rect* collision = nullptr;
        if(m_playerMovementDirection == SideLeft) {
            collision = predictCollision(m_level.player, m_level.getBorder(SideLeft));
            m_level.player.setVelocity(PlayerSpeed, StraightAngle);
        }
        else if(m_playerMovementDirection == SideRight) {
            collision = predictCollision(m_level.player, m_level.getBorder(SideRight));
            m_level.player.setVelocity(PlayerSpeed, 0);

        }
        if(collision == nullptr) {
            m_level.player.move();
        }
        delete collision;
    }
}

int ArkanoidEngine::getProgress(bool change)
{
    static int p = 0;
    if(p > 100) {
        m_state = LevelStateWon;
        p = 0;
    }
    return change ? p+=20 : p;
}

void ArkanoidEngine::movePlayer(Side side) {
    if(side == SideLeft || side == SideRight) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer() {
    m_playerMovementDirection = SideNone;
}

LevelState ArkanoidEngine::getState() {
    return m_state;
}

void ArkanoidEngine::setLevel(Level& level)
{
    m_level = level;
    m_state = LevelStateInProcess;
    m_delegate->engine_levelSet(m_level);
}

Level& ArkanoidEngine::getLevel() {
    return m_level;
}

Rect* ArkanoidEngine::predictCollision(const Movable& first, const GameObject& second)
{
    Rect* destinationOfFirst = new Rect(first.getRect());
    Rect firstRect = first.getRect();
    Rect movedFirstRect = rectAfterMoving(first);
    TwoSides collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.getRect());
    // first is x (left, right)
    switch(collisionSides.first) {
        case SideRight: {
            Line lineBetweenCorners = Line(Point(firstRect.x + firstRect.width, firstRect.y), (movedFirstRect.x + movedFirstRect.width, movedFirstRect.y));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideLeft));
            if (intersectionPoint == nullptr) {
                lineBetweenCorners.first.y += firstRect.height;
                lineBetweenCorners.second.y += movedFirstRect.height;
                intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideLeft));
                if (intersectionPoint == nullptr) {
                    break;
                }
                destinationOfFirst->x = intersectionPoint->x - destinationOfFirst->width;
                destinationOfFirst->y = intersectionPoint->y - destinationOfFirst->height;
            } else {
                destinationOfFirst->x = intersectionPoint->x - destinationOfFirst->width;
                destinationOfFirst->y = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
        case SideLeft: {
            Line lineBetweenCorners = Line(Point(firstRect.x, firstRect.y), (movedFirstRect.x, movedFirstRect.y));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideRight));
            if (intersectionPoint == nullptr) {
                lineBetweenCorners.first.y += firstRect.height;
                lineBetweenCorners.second.y += movedFirstRect.height;
                intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideRight));
                if (intersectionPoint == nullptr) {
                    break;
                }
                destinationOfFirst->x = intersectionPoint->x;
                destinationOfFirst->y = intersectionPoint->y - destinationOfFirst->height;
            } else {
                destinationOfFirst->x = intersectionPoint->x;
                destinationOfFirst->y = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
    }
    // now check vertically
    switch(collisionSides.second) {
        case SideUp: {
            Line lineBetweenCorners = Line(Point(firstRect.x, firstRect.y), (movedFirstRect.x, movedFirstRect.y));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideDown));
            if (intersectionPoint == nullptr) {
                lineBetweenCorners.first.x += firstRect.width;
                lineBetweenCorners.second.x += movedFirstRect.width;
                intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideDown));
                if (intersectionPoint == nullptr) {
                    break;
                }
                destinationOfFirst->x = intersectionPoint->x - destinationOfFirst->width;
                destinationOfFirst->y = intersectionPoint->y;
            } else {
                destinationOfFirst->x = intersectionPoint->x;
                destinationOfFirst->y = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
        case SideDown: {
            Line lineBetweenCorners = Line(Point(firstRect.x, firstRect.y + firstRect.height), (movedFirstRect.x, movedFirstRect.y + movedFirstRect.height));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideUp));
            if (intersectionPoint == nullptr) {
                lineBetweenCorners.first.x += firstRect.width;
                lineBetweenCorners.second.x += movedFirstRect.width;
                intersectionPoint = lineIntersection(lineBetweenCorners, second.getRect().getSide(SideDown));
                if (intersectionPoint == nullptr) {
                    break;
                }
                destinationOfFirst->x = intersectionPoint->x - destinationOfFirst->width;
                destinationOfFirst->y = intersectionPoint->y - destinationOfFirst->height;
            } else {
                destinationOfFirst->x = intersectionPoint->x;
                destinationOfFirst->y = intersectionPoint->y - destinationOfFirst->height;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
    }
    // if none of sides is colliding with middle object then return NULL
    return nullptr;
}

TwoSides ArkanoidEngine::predictCollisionSides(const Rect& first, const Rect& second, const Rect& middle)
{
    TwoSides result(SideNone, SideNone);
    // if we are moving right and the middle's left side is righter than our right then we may hit him on our right side
    if(first.x < second.x && first.x + first.width < middle.x) {
        result.first = SideRight;
    }
        // if we are moving left and the middle's right side is lefter than our right then we may hit him on our left side
    else if(first.x > second.x && first.x > middle.x + middle.width) {
        result.first = SideLeft;
    }
    // if we are moving down and the middle's top side is lower than our bottom then we may hit him on our bottom(down) side
    if(first.y < second.y && first.y + first.height < middle.y) {
        result.second = SideDown;
    }
        // if we are moving up and the middle's bottom side is higher than our top then we may hit him on our top(up) side
    else if(first.y > second.y && first.y > middle.y + middle.height) {
        result.second = SideUp;
    }
    return result;
}

Rect ArkanoidEngine::rectAfterMoving(const Movable &movable) {
    Point positionAfterMoving(movable.getPosition().x + movable.getVelocity().getProjection(AxisX), movable.getPosition().y + movable.getVelocity().getProjection(AxisY));
    Rect b(positionAfterMoving, movable.getSize());
    return b;

}

Point* ArkanoidEngine::lineIntersection(Line first, Line second) {
    Point* result = nullptr;
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = first.second.x - first.first.x;     s1_y = first.second.y - first.first.y;
    s2_x = second.second.y - second.first.x;     s2_y = second.second.y - second.first.y;

    float s, t;
    s = (-s1_y * (first.first.x - second.first.x) + s1_x * (first.first.y - second.first.y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (first.first.y - second.first.y) - s2_y * (first.first.x - second.first.x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        result = new Point(first.first.x + (t * s1_x), first.first.y + (t * s1_y));
    }
    return result;
}