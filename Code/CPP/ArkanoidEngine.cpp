//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

Point ILLEGAL_POINT(INT32_MIN, INT32_MIN);
Size ILLEGAL_SIZE(INT32_MIN, INT32_MIN);
Rect ILLEGAL_RECT(ILLEGAL_POINT, ILLEGAL_SIZE); //TODO: mb rename ????

void ArkanoidEngine::process()
{
//    processPlayer();
    processBall();
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
    m_playerMovementDirection = side; // TODO: remove this line, it is for debug
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

Rect ArkanoidEngine::predictCollision(const Movable& first, const GameObject& second)
{
    Rect destinationOfFirst = first.rect();
    Rect firstRect = first.rect();
    Rect movedFirstRect = rectAfterMoving(first);
    TwoSides collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.rect());
    // first is x (left, right)
    switch(collisionSides.first) {
        case SideRight: {
            Line lineBetweenCorners = Line(Point(firstRect.right(), firstRect.top), Point(movedFirstRect.right(), movedFirstRect.top));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideLeft));
            if (intersectionPoint == NotFound) {
//                lineBetweenCorners.first.y = firstRect.bottom();
//                lineBetweenCorners.second.y = movedFirstRect.bottom();
//                intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideLeft));
//                if (intersectionPoint == NotFound) {
//                    break;
//                }
//                destinationOfFirst.left = intersectionPoint->x - destinationOfFirst.width;
//                destinationOfFirst.top = intersectionPoint->y - destinationOfFirst.height;
            } else {

.+                destinationOfFirst.left = intersectionPoint->x - destinationOfFirst.width;
                destinationOfFirst.top = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
        case SideLeft: {
            Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top), (movedFirstRect.left, movedFirstRect.top));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideRight));
            if (intersectionPoint == NotFound) {
//                lineBetweenCorners.first.y = firstRect.bottom();
//                lineBetweenCorners.second.y = movedFirstRect.bottom();
//                intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideRight));
//                if (intersectionPoint == NotFound) {
//                    break;
//                }
//                destinationOfFirst.left = intersectionPoint->x;
//                destinationOfFirst.top = intersectionPoint->y - destinationOfFirst.height;
            } else {
                destinationOfFirst.left = intersectionPoint->x;
                destinationOfFirst.top = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
    }
    // second is y (up, down)
    switch(collisionSides.second) {
        case SideUp: {
            Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top), (movedFirstRect.left, movedFirstRect.top));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideDown));
            if (intersectionPoint == NotFound) {
//                lineBetweenCorners.first.x = firstRect.right();
//                lineBetweenCorners.second.x = movedFirstRect.right();
//                intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideDown));
//                if (intersectionPoint == NotFound) {
//                    break;
//                }
//                destinationOfFirst.left = intersectionPoint->x - destinationOfFirst.width;
//                destinationOfFirst.top = intersectionPoint->y;
            } else {
                destinationOfFirst.left = intersectionPoint->x;
                destinationOfFirst.top = intersectionPoint->y;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
        case SideDown: {
            Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top + firstRect.height), (movedFirstRect.left, movedFirstRect.top + movedFirstRect.height));
            Point *intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideUp));
            if (intersectionPoint == NotFound) {
//                lineBetweenCorners.first.x = firstRect.right();
//                lineBetweenCorners.second.x = movedFirstRect.right();
//                intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideDown));
//                if (intersectionPoint == NotFound) {
//                    break;
//                }
//                destinationOfFirst.left = intersectionPoint->x - destinationOfFirst.width;
//                destinationOfFirst.top = intersectionPoint->y - destinationOfFirst.height;
            } else {
                destinationOfFirst.left = intersectionPoint->x;
                destinationOfFirst.top = intersectionPoint->y - destinationOfFirst.height;
            }
            delete intersectionPoint;
            return destinationOfFirst;
        }
            break;
    }
    // if none of sides is colliding with middle object then return ILLEGAL_RECT
    return ILLEGAL_RECT;
}

TwoSides ArkanoidEngine::predictCollisionSides(const Rect& first, const Rect& movedFirst, const Rect& second)
{
    logstream << "predictCollisionSides" << endl;
    first.log("\tfirst - ");
    movedFirst.log("\tsecnd - ");
    second.log("\tmiddl - ");
    TwoSides result(SideNone, SideNone);
    // first moves right && right side is at left of second, then first will hit on it's right side
    if(first.left < movedFirst.left && first.right() <= second.left && second.left <= movedFirst.right()) {
        result.first = SideRight;
    }
    // first moves left && left side is at right of second, then first will hit on it's left side
    else if(first.left > movedFirst.left && movedFirst.left <= second.right() && second.right() <= first.left) {
        result.first = SideLeft;
    }
    // first moves down && down side is at top of second, then first will hit on it's down side
    if(first.top < movedFirst.top && first.bottom() <= second.top && second.top <= movedFirst.bottom()) {
        result.second = SideDown;
    }
    // first moves up && up side is at down of second, then first will hit on it's up side
    else if(first.top > movedFirst.top && movedFirst.top <= second.bottom() && second.bottom() <= first.top) {
        result.second = SideUp;
    }
    logstream << "predictedSides: " << nameOf(result.first) << " " << nameOf(result.second) << endl;
    return result;
}

Rect ArkanoidEngine::rectAfterMoving(const Movable& movable)
{
    Point positionAfterMoving(movable.getPosition().x + movable.getVelocity().getProjection(AxisX), movable.getPosition().y + movable.getVelocity().getProjection(AxisY));
    Rect b(positionAfterMoving, movable.getSize());
    return b;
}


void print(const std::string &front, Line line)
{
    logstream << front;
    logstream << "ax: " << line.first.x << " ay: " << line.first.y << "bx: " << line.second.x << " by: " << line.second.y << endl;
}

Point* ArkanoidEngine::lineIntersection(Line l1, Line l2)
{
    float k1 = (float)(l1.first.y - l1.second.y) / (l1.first.x - l1.second.x);
    float k2 = (float)(l2.first.y - l2.second.y) / (l2.first.x - l2.second.x);
    float b1 =        (l1.first.y - k1 * l1.first.x);
    float b2 =        (l2.first.y - k2 * l2.first.x);
    float interX = (b2 - b1) / (k1 - k2);
    float interY = k1 * interX + b1;
    return new Point(interX, interY);

//    float s1_x, s1_y, s2_x, s2_y;
//    s1_x = l1.second.x - l1.first.x;     s1_y = l1.second.y - l1.first.y;
//    s2_x = l2.second.x - l2.first.x;     s2_y = l2.second.y - l2.first.y;
//
//    float s, t;
//    s = (-s1_y * (l1.first.x - l2.first.x) + s1_x * (l1.first.y - l2.first.y)) / (-s2_x * s1_y + s1_x * s2_y);
//    t = ( s2_x * (l1.first.y - l2.first.y) - s2_y * (l1.first.x - l2.first.x)) / (-s2_x * s1_y + s1_x * s2_y);
//
//    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
//    {
//        // Collision detected
//        return new Point(l1.first.x + (t * s1_x), l1.first.y + (t * s1_y));
//    }
//    return nullptr;
}

Vector ArkanoidEngine::vector(GameObject from, Rect to) {
    return Vector();
}

/**
 * Moves player to already defined direction, if no border abolishes its movement.
 * Movement direction sets in functions movePlayer and stopPlayer.
 */
void ArkanoidEngine::processPlayer()
{
    if(m_playerMovementDirection != SideNone) {
        const GameObject* collidableObject = nullptr;
        if(m_playerMovementDirection == SideLeft) {
            m_level.player.setVelocity(PlayerSpeed, AngleLeft);
            collidableObject = &m_level.getBorder(SideLeft);
        }
        else if(m_playerMovementDirection == SideRight) {
            m_level.player.setVelocity(PlayerSpeed, AngleRight);
            collidableObject = &m_level.getBorder(SideRight);
        }
        else /*TODO: remove this else, it is for debug*/ {
            if(m_playerMovementDirection == SideUp) {
                m_level.player.setVelocity(PlayerSpeed, AngleUp);
                collidableObject = &m_level.getBorder(SideUp);
            } else {
                m_level.player.setVelocity(PlayerSpeed, AngleDown);
                collidableObject = &m_level.getBorder(SideUp);
            }
        }
        if(collidableObject != nullptr && predictCollision(m_level.player, *collidableObject) == ILLEGAL_RECT) {
            // if player must move(collidableObject != nullptr) and
            // does not collides with borders(predictCollision(m_level.player, *collidableObject) == ILLEGAL_RECT)
            // then we can move player...
            m_level.player.move();
        }
    }
}

void ArkanoidEngine::processBall()
{
    Rect collRect;
    for(auto brick : m_level.bricks) {
        if((collRect = predictCollision(m_level.ball, *brick)) != ILLEGAL_RECT) {
            predictCollision(m_level.ball, *brick);
            Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
            b.setVelocity(vector(m_level.ball, collRect));
            cout << "Ball hits brick: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
            break;
        }
    }

    for(const auto& border : m_level.borders) {
        if((collRect = predictCollision(m_level.ball, border)) != ILLEGAL_RECT) {
            Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
            b.setVelocity(vector(m_level.ball, collRect));
            cout << "Ball hits border: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
            break;
        }

        if((collRect = predictCollision(m_level.ball, ((GameObject&)m_level.player))) != ILLEGAL_RECT) {
            Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
            b.setVelocity(vector(m_level.ball, collRect));
            cout << "Ball hits player: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
            break;
        }
    }

    m_level.ball.move();
    m_level.ball.setVelocity(10, m_level.ball.getVelocity().m_angle);
}
