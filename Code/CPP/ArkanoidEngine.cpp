//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

void ArkanoidEngine::process()
{
    processPlayer();
    processBall();
}

int ArkanoidEngine::getProgress() const
{
    return static_cast<int>(100 - ((m_level.bricksSummaryHealth() * 100.0) / m_bricksMaxCount));
}

void ArkanoidEngine::movePlayer(Side side)
{
    m_playerMovementDirection = side;
}

void ArkanoidEngine::stopPlayer()
{
    m_playerMovementDirection = SideNone;
    m_level.player.setVelocity(0, 0);
}

LevelState ArkanoidEngine::getState() const
{
    return m_state;
}

void ArkanoidEngine::setLevel(Level& level, bool isNewGame)
{
    m_level = level;
    m_state = LevelStateInProcess;
    m_bricksMaxCount = level.bricksSummaryHealth();
    m_delegate->engine_levelSet(m_level);
    if(isNewGame) {
        m_level.ball.getVelocity().set(BallSpeed, static_cast<const float &>(M_PI / 14 + (((rand() % 100) / 100.0) * 5.2 * M_PI / 14)));
    }
}

const Level& ArkanoidEngine::getLevel() const
{
    return m_level;
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
    return result;
}

Rect ArkanoidEngine::rectAfterMoving(const Movable& movable)
{
    Point positionAfterMoving(movable.getPosition().x + movable.getVelocity().projection(AxisX), movable.getPosition().y + movable.getVelocity().projection(AxisY));
    return Rect(positionAfterMoving, movable.getSize());
}

/**
 * Moves player to already defined direction, if no border abolishes its movement.
 * Movement direction sets in functions movePlayer and stopPlayer.
 */
void ArkanoidEngine::processPlayer()
{
    if(m_playerMovementDirection != SideNone) {
        m_level.player.setVelocity(m_playerMovementDirection, PlayerSpeed);
        if(!willCollide(m_level.player, m_level.getBorder(m_playerMovementDirection))) {
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
        }
        if ((sides & SideUp) == SideUp || (sides & SideDown) == SideDown) {
            m_level.ball.getVelocity().inverse(AxisY);
        }
    }
}

Rect ArkanoidEngine::processBallBrickCollision() {
    for(auto it_brick = m_level.bricks.begin(); it_brick != m_level.bricks.end(); it_brick++) {
        Brick& brick = **it_brick;
        if(willCollide(m_level.ball, brick)) {
            m_level.ball.attack(brick);
            if(brick.getHealth() == 0) {
                m_level.bricks.erase(it_brick);
                m_delegate->engine_go_isAtPieceNow(brick.getIdentifier());
                if(m_level.bricks.empty()) {
                    m_state = LevelStateWon;
                }
            }
            Rect result = brick.rect();
            delete &brick;
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
        if(m_level.player.getVelocity().projection(AxisX) > 0) {
            m_level.ball.getVelocity().rotate(-BallDirectionChange);
        }
        else if(m_level.player.getVelocity().projection(AxisX) < 0) {
            m_level.ball.getVelocity().rotate(BallDirectionChange);
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
