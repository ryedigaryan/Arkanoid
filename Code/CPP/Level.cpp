//
// Created by ryedigaryan on 3/31/2018.
//

#include "Models/Level.h"
#include "ResourceManager.h"

Level::Level(GameObjectDelegate* go_dlgate) : go_delegate(go_dlgate)
{

}

void Level::loadFromSpec(const std::string &specPath)
{
    std::ifstream levelSpecReader;
    levelSpecReader.open(specPath);
    cout << "Reading LevelSpec: " << specPath << endl;
    loadBricks(levelSpecReader);
    loadPlayer(levelSpecReader);
    loadBall(levelSpecReader);
    levelSpecReader.close();
}

void Level::loadBricks(std::ifstream &specReader)
{
    // get bricks' row and column counts
    specReader >> brickRowCount;
    specReader >> brickColCount;

    // type of current Brick
    char brickType;
    // ordinal number of current Brick
    unsigned brickNumber = 0;
    while (!specReader.eof()) {
        // get the ID of current Brick
        specReader >> brickType;
        if (isValidBrickType(brickType - '0')) {
            // create Brick if it is a acceptable ID
            Brick* brick = createBrick(brickType - '0', brickNumber);
            // put the created Brick into all bricks list
            bricks.push_back(brick);
        }
        brickNumber++;
    }
}

void Level::loadPlayer(std::ifstream &specReader)
{
    player.m_texturePath = Paddle1Texture.path;
    player.setPosition(Point((LevelWidth - PlayerWidth) / 2, LevelHeight - PlayerHeight));
    player.setSize(PlayerSize);
}

void Level::loadBall(std::ifstream &specReader)
{
    ball.m_texturePath = BallTexture.path;
    ball.setPosition(Point(player.get(AxisX) + (PlayerWidth - BallWidth) / 2, player.get(AxisY) - BallHeight));
    ball.setSize(BallSize);
}

bool Level::isValidBrickType(unsigned id)
{
    return id >= 1 && id <= 5;
}

Brick* Level::createBrick(unsigned brickType, unsigned index)
{
    // get the row and column number of cell, where the brick must be putted
    int rowNumber = index / brickColCount;
    int columnNumber = index - rowNumber * brickColCount;
    // get the position of the brick's cell
    Point position;
    position.x = BrickWidth * columnNumber;
    position.y = BrickHeight * rowNumber;
    // now brick type indicates Brick's health
    Brick* brick = new Brick(ResourceManager::getManager().getResource(ResourceTypeBrick, brickType).path, position, BrickSize, brickType);
    if(go_delegate != nullptr) {
        brick->setDelegate(go_delegate);
    }
    return brick;
}

Level::~Level() {
    for(Brick* brick : bricks) {
        delete brick;
    }
}

void Level::setGoDelegate(GameObjectDelegate *go_dlg) {
    for(auto brick : bricks) {
        brick->setDelegate(go_dlg);
    }
    player.setDelegate(go_dlg);
    ball.setDelegate(go_dlg);
}
