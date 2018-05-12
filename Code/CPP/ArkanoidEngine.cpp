//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process()
{
    processPlayer();
    processBall();
}

int ArkanoidEngine::getProgress()
{
    return static_cast<int>(100 - ((m_level.bricks.size() * 100.0) / m_bricksMaxCount));
}

void ArkanoidEngine::movePlayer(Side side)
{
    m_playerMovementDirection = side; // TODO: remove this line, it is for debug
    if(side == SideLeft || side == SideRight) {
        m_playerMovementDirection = side;
    }
}

void ArkanoidEngine::stopPlayer()
{
    m_playerMovementDirection = SideNone;
    m_level.player.setVelocity(0, 0);
}

LevelState ArkanoidEngine::getState()
{
    return m_state;
}

void ArkanoidEngine::setLevel(Level& level)
{
    m_level = level;
    m_state = LevelStateInProcess;
    m_bricksMaxCount = level.bricks.size();
    m_delegate->engine_levelSet(m_level);
}

Level& ArkanoidEngine::getLevel()
{
    return m_level;
}

Point ArkanoidEngine::predictCollision(const Movable& first, const GameObject& second)
{
    Rect firstRect = first.rect();
    Rect movedFirstRect = rectAfterMoving(first);
    Line movementTrajectory(firstRect.position(), movedFirstRect.position());
    Line collisionLine = ILLEGAL_LINE; // the line with which first will be collided
    int collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.rect()); // side of first

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
    return movementTrajectory.intersection(collisionLine, false);
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
        if(collidableObject != nullptr && !willCollide(m_level.player, *collidableObject)) {
            m_level.player.move();
        }
    }
}

void ArkanoidEngine::processBall()
{
    if(m_level.ball.getPosition().y > m_level.getSize().height) {
        m_state = LevelStateLost;
        return;
    }
    Rect colRect = processBallBorderCollision();
    if(colRect == ILLEGAL_RECT) {
        colRect = processBallBrickCollision();
        if(colRect == ILLEGAL_RECT) {
            colRect = processBallPlayerCollision();
        }
    }
    if(colRect == ILLEGAL_RECT) {
        m_level.ball.move();
    }
    else {
        int sides = predictCollisionSides(m_level.ball.rect(), rectAfterMoving(m_level.ball), colRect);
        if ((sides & SideRight) == SideRight || (sides & SideLeft) == SideLeft) {
             m_level.ball.getVelocity().inverse(AxisX);
        } else if ((sides & SideUp) == SideUp || (sides & SideDown) == SideDown) {
            m_level.ball.getVelocity().inverse(AxisY);
        }
    }
}

Rect ArkanoidEngine::processBallBrickCollision() {
    for(auto it_brick = m_level.bricks.begin(); it_brick != m_level.bricks.end(); it_brick++) {
        Brick& brick = **it_brick;
        if(willCollide(m_level.ball, brick)) {
            m_level.ball.attack(brick);
            unsigned brickID;
            Rect result = brick.rect();
            if(brick.getHealth() == 0) {
                brickID = brick.getIdentifier();
                m_level.bricks.erase(it_brick);
                m_delegate->engine_go_isAtPieceNow(brickID);
                if(m_level.bricks.empty()) {
                    m_state = LevelStateWon;
                }
            }
            return result;
        }
    }
    return ILLEGAL_RECT;
}

Rect ArkanoidEngine::processBallBorderCollision() {
    for(const auto& border : m_level.borders) {
        if(willCollide(m_level.ball, border)) {
            return border.rect();
        }
    }
    return ILLEGAL_RECT;
}

Rect ArkanoidEngine::processBallPlayerCollision() {
    if(willCollide(m_level.ball, m_level.player)) {
        Vector& vel = m_level.ball.getVelocity();
        double angle = m_level.ball.getVelocity().angle();
        if(m_level.player.getVelocity().projection(AxisX) > 0) {
//            m_level.ball.getVelocity().rotate(-BallDirectionChange);
            m_level.ball.getVelocity().set(vel.module(), angle + 5);
        }
        else if(m_level.player.getVelocity().projection(AxisX) < 0) {
//            m_level.ball.getVelocity().rotate(BallDirectionChange);
            m_level.ball.getVelocity().set(vel.module(), angle - 5);
        }
        return m_level.player.rect();
    }
    return ILLEGAL_RECT;
}

bool ArkanoidEngine::willCollide(const Movable &first, const GameObject &second) {
    Rect movedRect = rectAfterMoving(first);
    return areColliding(movedRect, second.rect());
}

bool ArkanoidEngine::areColliding(Rect first, Rect second) {
    return first.left < second.right() && first.right() > second.left &&
            first.top < second.bottom() && first.bottom() > second.top;
}

Side ArkanoidEngine::collisionSide(const Movable& first, const GameObject& second) {
    Rect f = first.rect();
    Rect s = second.rect();
    if(f.right() < s.left) {
        return SideRight;
    }
    if(f.left > s.right()) {
        return SideLeft;
    }
    if(f.bottom() < s.top) {
        return SideDown;
    }
    if(f.top > s.bottom()) {
        return SideUp;
    }
}

Rect ArkanoidEngine::removeBrick(std::list<Brick*>::iterator it_brick) {
    unsigned brickID;
    Brick brick = **it_brick;
    Rect result = brick.rect();
    if(brick.getHealth() == 0) {
        brickID = brick.getIdentifier();
        m_level.bricks.erase(it_brick);
        m_delegate->engine_go_isAtPieceNow(brickID);
    }
    return result;
}
