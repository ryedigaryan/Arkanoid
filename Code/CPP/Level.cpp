//
// Created by ryedigaryan on 3/31/2018.
//

#include "Models/Level.h"
#include "ResourceManager.h"

//Level::Level() : m_resourceManager(ResourceManager::getManager()) {};

Level::Level(unsigned num, Size bricksDistance, int bricksCountOnPlayer, GameObjectDelegate* go_dlg)
        : number(num), go_delegate(go_dlg), m_brickDistance(bricksDistance), m_bricksCountOnPlayer(bricksCountOnPlayer), m_resourceManager(ResourceManager::getManager())
{

}

Level::Level(const Level& other)
        : number(other.number), brickRowCount(other.brickRowCount), brickColCount(other.brickColCount), player(other.player), ball(other.ball), borders(other.borders), timeLimit(other.timeLimit),    // publics
          go_delegate(other.go_delegate), m_brickDistance(other.m_brickDistance), m_bricksCountOnPlayer(other.m_bricksCountOnPlayer), m_size(other.m_size), m_resourceManager(other.m_resourceManager) // privates
{
    for(auto brick : other.bricks) {
        bricks.push_back(new Brick(*brick));
    }
}

Level::~Level()
{
    for(Brick* brick : bricks) {
        delete brick;
    }
}

Level& Level::operator=(const Level& other) {
    if(this != &other) {
        // publics
        timeLimit = other.timeLimit;
        number = other.number;
        brickRowCount = other.brickRowCount;
        brickColCount = other.brickColCount;
        player = other.player;
        ball = other.ball;
        bricks.clear();
        for(auto otherBrick : other.bricks) {
            bricks.push_back(new Brick(*otherBrick));
        }
        borders = other.borders;
        // privates
        go_delegate = other.go_delegate;
        m_brickDistance = other.m_brickDistance;
        m_bricksCountOnPlayer = other.m_bricksCountOnPlayer;
        m_size = other.m_size;
    }
    return *this;
}

void Level::loadFromSpec(const std::string& specPath)
{
    std::ifstream levelSpecReader;
    levelSpecReader.open(specPath);
    cout << "Reading LevelSpec: " << specPath << endl;
    loadBricks(levelSpecReader);
    loadPlayer(levelSpecReader);
    loadBall(levelSpecReader);
    loadBorders(levelSpecReader);
    timeLimit = LevelMinTime + number * 5;
    levelSpecReader.close();
}

Size Level::getSize(bool considerBorders /* = false */) const
{
    if(!considerBorders) {
        return Size(m_size.width - 2 * BorderWidth, m_size.height - BorderWidth);
    }
    return m_size;
}

const Border& Level::getBorder(Side sceneSide) const
{
    switch(sceneSide) {
        case SideLeft:
            return borders[0];
        case SideRight:
            return borders[2];
        case SideUp:
            return borders[1];
    }
    return Border();
}

unsigned Level::smallestIdentifier() const
{
    return player.getIdentifier() < ball.getIdentifier() ? player.getIdentifier() : ball.getIdentifier();
}

unsigned Level::biggestIdentifier() const
{
    // as the upper border is the last created object when loading level from spec,
    // so we assume that it has the biggest ID
    return getBorder(SideUp).getIdentifier();
}

unsigned Level::bricksSummaryHealth() const
{
    unsigned sum = 0;
    for(auto brick : bricks) {
        sum += brick->getHealth();
    }
    return sum;
}

unsigned Level::countOfGameObjects() const
{
    return biggestIdentifier() - smallestIdentifier() + 1;
}

void Level::loadBricks(std::ifstream& specReader)
{
    // set level's size to borders size
    m_size = Size(BorderWidth, BorderWidth);
    // get bricks' row and column counts
    specReader >> brickRowCount;
    specReader >> brickColCount;
    // type of current Brick
    char brickType;
    // ordinal number of current Brick
    unsigned brickNumber = 0;
    Point cellPos; // the position of current cell of brick
    for(cellPos.y = 0; cellPos.y < brickRowCount; cellPos.y++) {
        for(cellPos.x = 0; cellPos.x < brickColCount; cellPos.x++) {
            specReader >> brickType;
            if (isValidBrickType(static_cast<unsigned int>(brickType - '0'))) {
                // create Brick if it is an acceptable ID
                Brick* brick = createBrick(static_cast<unsigned int>(brickType - '0'), cellPos, Point(m_size));
                brick->setPosition(brick->getPosition() + cellPos * m_brickDistance);
                brick->setDelegate(go_delegate);
                // put the created Brick into all bricks list
                bricks.push_back(brick);
            }
            brickNumber++;
        }
    }
    // enlarge level's size as new bricks have been added
    m_size.width += brickColCount * BrickWidth + (brickColCount - 1) * m_brickDistance.width;
    m_size.height += brickRowCount * BrickHeight + (brickRowCount - 1) * m_brickDistance.height;
}

void Level::loadPlayer(std::ifstream& specReader)
{
    // enlarge the level's area from bottom (till the place where player must be putted)
    m_size.height += m_bricksCountOnPlayer * BrickHeight;
    // put player at the bottom-middle of level
    player.setPosition(Point((m_size.width - PlayerWidth) / 2, m_size.height));
    player.setSize(PlayerSize);
    // enlarge the level's area by Player's height, as it has been added to level
    m_size.height += PlayerHeight;
    player.setDelegate(go_delegate);
}

void Level::loadBall(std::ifstream& specReader)
{
    // as the ball is not added at the bottom of level, so there is no need to enlarge level's size
    ball.setPosition(Point(player.getPosition().x + (PlayerWidth + BallWidth) / 2, player.getPosition().y - BallHeight));
    ball.setSize(BallSize);
    ball.setDelegate(go_delegate);
    ball.getVelocity().setModule(BallSpeed);
}

void Level::loadBorders(std::ifstream& specReader)
{
    /*
     * creating borders like this
     *      |---|
     *      |   |
     *      |   |
     * Note: the top border is inside left and right borders
     */

    // level's size has already been enlarged for Left and Upper borders
    borders.emplace_back(Point(), Size(BorderWidth, m_size.height));                            // left border
    borders.emplace_back(Point(BorderWidth), Size(m_size.width - BorderWidth, BorderWidth));    // upper border
    borders.emplace_back(Point(m_size.width), Size(BorderWidth, m_size.height));                // right border
    // enlarge level's size as the Right border have been added
    m_size.width += BorderWidth;
    for(auto border : borders) {
        border.setDelegate(go_delegate);
    }
}

bool Level::isValidBrickType(unsigned id)
{
    return id >= 1 && id <= 5;
}

Brick* Level::createBrick(unsigned health, Point cellPos, Point offset)
{
    // get the position of the brick's cell
    Point position;
    position.x = offset.x + BrickWidth * cellPos.x;
    position.y = offset.y + BrickHeight * cellPos.y;
    return new Brick(position, BrickSize, health);
}

void Level::setGoDelegate(GameObjectDelegate *go_dlg, ObjectType goType)
{
    switch(goType) {
        case ObjectTypePaddle:
            player.setDelegate(go_dlg);
            break;
        case ObjectTypeBall:
            ball.setDelegate(go_dlg);
            break;
        case ObjectTypeBorder:
            for(auto border : borders) {
                border.setDelegate(go_dlg);
            }
            break;
        case ObjectTypeBrick:
            for(auto brick : bricks) {
                brick->setDelegate(go_dlg);
            }
            break;
    }
}