//
// Created by ruben on 3/25/2018.
//

#include "ArkanoidEngine.h"

Point ILLEGAL_POINT(INT32_MIN, INT32_MIN);
Size ILLEGAL_SIZE(INT32_MIN, INT32_MIN);
Rect ILLEGAL_RECT(ILLEGAL_POINT, ILLEGAL_SIZE); //TODO: mb rename ????

void ArkanoidEngine::process()
{
    processPlayer();
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

Point ArkanoidEngine::predictCollision(const Movable& first, const GameObject& second)
{
    Rect firstRect = first.rect();
    Rect movedFirstRect = rectAfterMoving(first);
    Line movementTrajectory(first.getPosition(), movedFirstRect.position());
    Line collisionLine; // the line with which first will be collided
    int collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.rect());

    if((collisionSides & SideRight) == SideRight) {
        collisionLine = second.rect().side(SideLeft);
    }
    if((collisionSides & SideLeft) == SideLeft) {
        collisionLine = second.rect().side(SideRight);
    }
    if((collisionSides & SideDown) == SideDown) {
        collisionLine = second.rect().side(SideUp);
    }
    if((collisionSides & SideUp) == SideUp) {
        collisionLine = second.rect().side(SideDown);
    }

//    Point destinationPosition = first.getPosition();
//    Rect destinationOfFirst = first.rect();
//    Rect firstRect = first.rect();
//    Rect movedFirstRect = rectAfterMoving(first);
//    int collisionSides = predictCollisionSides(firstRect, movedFirstRect, second.rect());
//    if((collisionSides & SideRight) == SideRight) {
//        Line lineBetweenCorners = Line(Point(firstRect.right(), firstRect.top), Point(movedFirstRect.right(), movedFirstRect.top));
//        Point intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideLeft));
//        destinationOfFirst.left = intersectionPoint.x - destinationOfFirst.width;
//        destinationOfFirst.top = intersectionPoint.y;
//        return destinationOfFirst;
//    }
//    if((collisionSides & SideLeft) == SideLeft) {
//        Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top), (movedFirstRect.left, movedFirstRect.top));
//        Point intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideRight));
//        destinationOfFirst.left = intersectionPoint.x;
//        destinationOfFirst.top = intersectionPoint.y;
//        return destinationOfFirst;
//    }
//    if((collisionSides & SideDown) == SideDown) {
//        Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top), (movedFirstRect.left, movedFirstRect.top));
//        Point intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideDown));
//        destinationOfFirst.left = intersectionPoint.x;
//        destinationOfFirst.top = intersectionPoint.y;
//        return destinationOfFirst;
//    }
//    if((collisionSides & SideUp) == SideUp) {
//        Line lineBetweenCorners = Line(Point(firstRect.left, firstRect.top + firstRect.height), (movedFirstRect.left, movedFirstRect.top + movedFirstRect.height));
//        Point intersectionPoint = lineIntersection(lineBetweenCorners, second.rect().side(SideUp));
//        destinationOfFirst.left = intersectionPoint.x;
//        destinationOfFirst.top = intersectionPoint.y - destinationOfFirst.height;
//        return destinationOfFirst;
//    }
//    // if none of sides is colliding with middle object then return ILLEGAL_RECT
//    return destinationPosition;
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


void print(const std::string &front, Line line)
{
    logstream << front;
    logstream << "ax: " << line.first.x << " ay: " << line.first.y << "bx: " << line.second.x << " by: " << line.second.y << endl;
}

Point ArkanoidEngine::lineIntersection(Line l1, Line l2)
{
    float k1 = (float)(l1.first.y - l1.second.y) / (l1.first.x - l1.second.x);
    float k2 = (float)(l2.first.y - l2.second.y) / (l2.first.x - l2.second.x);
    float b1 =        (l1.first.y - k1 * l1.first.x);
    float b2 =        (l2.first.y - k2 * l2.first.x);
    float interX = (b2 - b1) / (k1 - k2);
    float interY = k1 * interX + b1;
    return Point(interX, interY);
}

Vector ArkanoidEngine::vector(GameObject from, Rect to) {
    Vector velocity;
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
