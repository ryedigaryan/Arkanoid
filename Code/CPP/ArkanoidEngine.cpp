//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

const Point ILLEGAL_POINT(INT32_MIN, INT32_MIN);
const Size  ILLEGAL_SIZE(INT32_MIN, INT32_MIN);
const Line  ILLEGAL_LINE(ILLEGAL_POINT, ILLEGAL_POINT);
const Rect  ILLEGAL_RECT(ILLEGAL_POINT, ILLEGAL_SIZE); //TODO: mb rename ????

void ArkanoidEngine::process()
{
    processPlayer();
//    processBall();
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

Point ArkanoidEngine::predictCollision(const Movable& first, const GameObject& second)
{
    Rect firstRect = first.rect();
    Rect movedFirstRect = rectAfterMoving(first);
    Line movementTrajectory(firstRect.position(), movedFirstRect.position());
    Line collisionLine = ILLEGAL_LINE; // the line with which first will be collided
    int collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.rect()); // side of first

    m_level.getSize(false);
    Line l1, l2;
    if((collisionSides & SideRight) == SideRight) {
        collisionLine = second.rect().side(SideLeft);
        l1 = Line(Point(firstRect.top, firstRect.right()), Point(movedFirstRect.top, movedFirstRect.right()));
        l2 = Line(Point(firstRect.bottom(), firstRect.right()), Point(movedFirstRect.bottom(), movedFirstRect.right()));
        if(!collisionLine.m_start.isInside(l1, l2) && !collisionLine.m_end.isInside(l1, l2)) {
            collisionLine = ILLEGAL_LINE;
        }
    }
    if(collisionLine != ILLEGAL_LINE && (collisionSides & SideLeft) == SideLeft) {
        //TODO: add case
//        collisionLine = second.rect().side(SideRight);
    }
    if((collisionSides & SideDown) == SideDown) {
        //TODO: add case
//        collisionLine = second.rect().side(SideUp);
    }
    else if((collisionSides & SideUp) == SideUp) {
        //TODO: add case
//        collisionLine = second.rect().side(SideDown);
    }
    if(collisionLine == ILLEGAL_LINE) {
        return ILLEGAL_POINT;
    }
    return movementTrajectory.intersection(collisionLine);
}

int ArkanoidEngine::predictCollisionSides(const Rect& first, const Rect& movedFirst, const Rect& second)
{
    int result = 0;
    // first moves right && right side is at left of second, then first will hit on it's right side
    if(first.left < movedFirst.left && first.right() <= second.left && second.left <= movedFirst.right()) {
        result = SideRight;
    }
    // first moves left && left side is at right of second, then first will hit on it's left side
    else if(first.left > movedFirst.left && movedFirst.left <= second.right() && second.right() <= first.left) {
        result = SideLeft;
    }
    // first moves down && down side is at top of second, then first will hit on it's down side
    if(first.top < movedFirst.top && first.bottom() <= second.top && second.top <= movedFirst.bottom()) {
        result |= SideDown;
    }
    // first moves up && up side is at down of second, then first will hit on it's up side
    else if(first.top > movedFirst.top && movedFirst.top <= second.bottom() && second.bottom() <= first.top) {
        result |= SideUp;
    }
    return result == 0 ? SideNone : result;
}

Rect ArkanoidEngine::rectAfterMoving(const Movable& movable)
{
    Point positionAfterMoving(movable.getPosition().x + movable.getVelocity().projection(AxisX), movable.getPosition().y +
            movable.getVelocity().projection(AxisY));
    Rect b(positionAfterMoving, movable.getSize());
    return b;
}

//Point ArkanoidEngine::lineIntersection(Line l1, Line l2)
//{
//    float k1 = static_cast<float>(l1.first.y - l1.second.y) / (l1.first.x - l1.second.x);
//    float k2 = static_cast<float>(l2.first.y - l2.second.y) / (l2.first.x - l2.second.x);
//
//    float b1 = (l1.first.y - k1 * l1.first.x);
//    float b2 = (l2.first.y - k2 * l2.first.x);
//
//    float interX = (b2 - b1) / (k1 - k2);
//    float interY = k1 * interX + b1;
//
//    return Point(static_cast<int>(interX), static_cast<int>(interY));
//}

/**
 * Moves player to already defined direction, if no border abolishes its movement.
 * Movement direction sets in functions movePlayer and stopPlayer.
 */
void ArkanoidEngine::processPlayer()
{
    if(m_playerMovementDirection != SideNone) {
        const GameObject* collidableObject = nullptr;
        if(m_playerMovementDirection == SideLeft) {
            m_level.player.setVelocity(-PlayerSpeed, 0);
            collidableObject = &m_level.getBorder(SideLeft);
        }
        else if(m_playerMovementDirection == SideRight) {
            m_level.player.setVelocity(PlayerSpeed, 0);
            collidableObject = &m_level.getBorder(SideRight);
        }
        else /*TODO: remove this else, it is for debug*/ {
            if(m_playerMovementDirection == SideUp) {
                m_level.player.setVelocity(0, -PlayerSpeed);
                collidableObject = &m_level.getBorder(SideUp);
            } else {
                m_level.player.setVelocity(0, PlayerSpeed);
                collidableObject = &m_level.getBorder(SideUp);
            }
        }
        Point collPos; //TODO: if position != ILLEGAL_POINT then move to postition
        if(collidableObject != nullptr && (collPos = predictCollision(m_level.player, *collidableObject)) == ILLEGAL_POINT) {
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
        if(predictCollision(m_level.ball, *brick) == ILLEGAL_POINT) {
            m_level.ball.move();
            return;
        }
        else {
            cout << "Ball hits brick" << endl;
        }
//        if((collRect = predictCollision(m_level.ball, *brick)) != ILLEGAL_POINT) {
//            Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
//            b.setVelocity(Vector(m_level.ball.getPosition(), collRect.position()));
//            cout << "Ball hits brick: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
//            break;
//        }
    }

    for(const auto& border : m_level.borders) {
        if(predictCollision(m_level.ball, border) == ILLEGAL_POINT) {
            m_level.ball.move();
            return;
        }
        else {
            cout << "Ball hits border" << endl;
        }
//        if((collRect = predictCollision(m_level.ball, border)) != ILLEGAL_POINT) {
//            Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
//            b.setVelocity(Vector(m_level.ball.getPosition(), collRect.position()));
//            cout << "Ball hits border: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
//            break;
//        }
    }

//    if((collRect = predictCollision(m_level.ball, ((GameObject&)m_level.player))) != ILLEGAL_POINT) {
//        Movable& b = m_level.ball; //TODO: cant call super's function direct from derived
//        b.setVelocity(Vector(m_level.ball.getPosition(), collRect.position()));
//        cout << "Ball hits player: " << collRect.left << " " << collRect.top << "  " << collRect.height << " " << collRect.width << endl;
//    }

//    m_level.ball.move();
//    m_level.ball.setVelocity(10, m_level.ball.getVelocity().m_angle);
}