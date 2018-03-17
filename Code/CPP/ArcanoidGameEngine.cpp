//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameEngine.h"

#include <iostream>
#include <afxres.h>

using namespace std;

void ArcanoidGameEngine::setGameObjectDelegate(GameObjectDelegate* go_delegate)
{
    cout << "engine: setGameObjectDelegate" << endl;
    m_go_delegate = go_delegate;
}

void ArcanoidGameEngine::prepareScene(const std::string& levelSpecFilePath)
{
    cout << "engine: prepareLevel" << endl;
    std::ifstream levelSpecReader;
    try {
        levelSpecReader.open(levelSpecFilePath);
        m_delegate->engine_willLoadLevel();
        prepareLevel(levelSpecReader);
        prepareBricks(levelSpecReader);
        preparePlayer();
        prepareBall();
        prepareBorders();
        m_isLevelPrepared = true;
    }
    catch (...) {
        cout << "FAIL. class = ArcanoidGameEngine, function = prepareLevel" << endl;
        m_isLevelPrepared = false;
        m_levelSize = LevelIncorrectSize;
    }
    levelSpecReader.close();
    Sleep(1000);
    m_delegate->engine_levelLoaded();
}

void ArcanoidGameEngine::prepareLevel(std::ifstream &levelSpecReader)
{
    cout << "engine: prepareLevel" << endl;
    // get count of rows and columns of Bricks for current level
    levelSpecReader >> m_rowCount;
    levelSpecReader >> m_columnCount;

    // calculate level size
    m_levelSize.width = m_columnCount * m_brickSize.width + 2 * BorderDefaultWidth;
    m_levelSize.height = m_rowCount * m_brickSize.height + BorderDefaultWidth + m_blocksCountOnPlayer * m_brickSize.height;
    m_delegate->engine_levelSizeSet(m_levelSize);
}

void ArcanoidGameEngine::prepareBricks(std::ifstream& levelSpecReader) {
    cout << "engine: prepareBricks" << endl;

    // ID of current Brick
    char brickID;
    // ordinal number of current Brick
    short brickNumber = 0;
    while (!levelSpecReader.eof()) {
        // get the ID of current Brick
        levelSpecReader >> brickID;
        if (isBrickID(brickID)) {
            // create Brick if it is a acceptable ID
            Brick* brick = createBrick(brickID - '0', brickNumber);
            // put the created Brick into all bricks list
            m_bricks.push_back(brick);
        }
        brickNumber++;
    }
    levelSpecReader.close();
}

void ArcanoidGameEngine::prepareBorders()
{
    cout << "engine: prepareBorders" << endl;
    for(int i = 0; i < 3; i++ ) {
        m_borders[i].m_texturePath = ConstructPathToTexture(BordersPath, 1);
    }
    m_borders[Left].setPosition(Point());
    m_borders[Left].setSize(Size(BorderDefaultWidth, m_levelSize.height));
    m_borders[Left].setDelegate(m_go_delegate);
    m_borders[Right].setPosition(Point(m_levelSize.width - BorderDefaultWidth, 0));
    m_borders[Right].setSize(Size(BorderDefaultWidth, m_levelSize.height));
    m_borders[Right].setDelegate(m_go_delegate);
    m_borders[Up].setPosition(Point(m_borders[Left].get(Width), 0));
    m_borders[Up].setSize(Size(m_levelSize.width - m_borders[Left].get(Width) - m_borders[Right].get(Width), BorderDefaultWidth));
    m_borders[Up].setDelegate(m_go_delegate);
}

void ArcanoidGameEngine::preparePlayer()
{
    cout << "engine: preparePlayer" << endl;
    // set Height and Width to default values
    m_player.set(Width, PlayerDefaultSizeWidth);
    m_player.set(Height, PlayerDefaultSizeHeight);
    // put player(paddle) in the bottom center of the screen
    m_player.set(X, (m_levelSize.width - m_player.get(Width)) / 2);
    m_player.set(Y, m_levelSize.height - m_player.get(Height) - PlayerBottomOffset);
    m_player.setDelegate(m_go_delegate);
}

void ArcanoidGameEngine::prepareBall()
{
    cout << "engine: prepareBall" << endl;
    // set Height and Width to default values
    m_ball.set(Width, BallDefaultSizeWidth);
    m_ball.set(Height, BallDefaultSizeHeight);
    // put ball on paddle(player), at the middle
    m_ball.set(X, m_player.get(X) + m_player.get(Width) / 2 - m_ball.get(Width) / 2);
    m_ball.set(Y, m_player.get(Y) - m_ball.get(Height));
    m_ball.setDelegate(m_go_delegate);
}


void ArcanoidGameEngine::startLevel()
{
    cout << "engine: startLevel" << endl;
    if (!m_isLevelPrepared) {
        cout << "WARNING! Attempting to start level while level is not yet prepared" << endl;
        return;
    }

    m_delegate->engine_willStartLevel();

    m_isLevelStarted = true;
}


void ArcanoidGameEngine::pause()
{
    cout << "engine: pause" << endl;
    if (!m_isLevelStarted) {
        cout << "WARNING: Attempting to pause game while it is not yet started" << endl;
        return;
    }
    if (m_isGamePaused) {
        cout << "WARNING: Attempting to pause already paused game" << endl;
        return;
    }

    m_isGamePaused = true;

    m_delegate->engine_paused();
}

void ArcanoidGameEngine::unpause()
{
    cout << "engine: unpause" << endl;
    if (!m_isGamePaused) {
        cout << "WARNING: Attempting to unpasue already unpaused game" << endl;
        return;
    }

    m_isGamePaused = false;

    m_delegate->engine_unpaused();
}


int ArcanoidGameEngine::getCountOfRows() {
    return m_rowCount;
}

int ArcanoidGameEngine::getCountOfColumns() {
    return m_columnCount;
}

void ArcanoidGameEngine::setDelegate(ArcanoidGameEngineDelegate* engineDelegate)
{
    cout << "engine: setDelegate" << endl;
    m_delegate = engineDelegate;
}


void ArcanoidGameEngine::process()
{
    cout << "engine: process" << endl;
    if (m_isGamePaused) {
        return;
    }

    //TODO: implement logic
    //TODO: m_delegate->levelEnded(won ?)
}


void ArcanoidGameEngine::movePlayer(Side direction) {

}

Brick* ArcanoidGameEngine::createBrick(short id, short number)
{
    cout << "engine: createBrick" << endl;
    // get the row and column number of cell, where the brick must be putted
    int rowNumber = number / m_columnCount;
    int columnNumber = number - rowNumber * m_columnCount;
    // get the position of the brick's cell
    Point position;
    position.x = m_brickSize.width * columnNumber;
    position.y = m_brickSize.height * rowNumber;

    // now id indicates Brick's health and texture
    Brick* brick = new Brick(ConstructPathToTexture(BricksPath, id), GameObjectType::TBrick, position, m_brickSize, id);
    if(m_go_delegate != nullptr) {
        brick->setDelegate(m_go_delegate);
    }
    return brick;
}

bool ArcanoidGameEngine::isBrickID(char brickID)
{
    return brickID >= '0' && brickID <= '9';
}

void ArcanoidGameEngine::stopPlayerMoving() {

}

Size ArcanoidGameEngine::getSize(GameObjectType requestObjectType, Side requestObjectSide) {
    switch (requestObjectType) {
        case TBrick:
            return m_brickSize;
        case TPaddle:
            return m_player.getSize();
        case TBall:
            return m_ball.getSize();
        case TBorder:
            return m_borders[requestObjectSide].getSize();
        case TLevel:
            return m_levelSize;
    }

}
