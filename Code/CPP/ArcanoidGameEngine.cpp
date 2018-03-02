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

bool ArcanoidGameEngine::prepareLevel(const string& levelSpecFilePath)
{
    cout << "engine: prepareLevel" << endl;
    ifstream levelSpecReader;
    try {
        levelSpecReader.open(levelSpecFilePath);
        m_delegate->engine_willLoadLevel();
        loadLevel(levelSpecReader);
        prepareLevelSize();
        preparePlayer();
        prepareBall();
        m_isLevelPrepared = true;
    }
    catch (...) {
        cout << "FAILED WHILE PREPARING GAME!!!!" << endl;
        m_isLevelPrepared = false;
    }
    levelSpecReader.close();
    Sleep(5000);
    m_delegate->engine_levelLoaded();
    return m_isLevelPrepared;
}

void ArcanoidGameEngine::loadLevel(ifstream& levelSpecReader)
{
    cout << "engine: loadLevel" << endl;
    // get count of rows and columns of Bricks for current level
    levelSpecReader >> m_rowCount;
    levelSpecReader >> m_columnCount;

    // ID of current Brick
    char brickID;
    // ordinal number of current Brick
    short brickNumber = 0;
    while (!levelSpecReader.eof()) {
        // get the ID of current Brick
        levelSpecReader >> brickID;
        if (isBrickID(brickID)) {
            // create Brick if it is a acceptable ID
            Brick brick = createBrick(brickID - '0', brickNumber);
            // put the created Brick into all bricks list
            m_bricks.push_back(&brick);
        }
        brickNumber++;
    }
    levelSpecReader.close();
    m_isLevelLoaded = true;
}

void ArcanoidGameEngine::prepareLevelSize() {
    cout << "engine: prepareLevelSize" << endl;
    m_levelSize.width = m_columnCount * m_brickSize.width + 2 * BorderDefaultWidth;
    m_levelSize.height = m_rowCount * m_brickSize.height + BorderDefaultWidth + m_blocksCountOnPlayer * m_brickSize.height;
}

void ArcanoidGameEngine::prepareBorders()
{
    cout << "engine: prepareBorders" << endl;
    m_borders[Left].setPosition(Point());
    m_borders[Left].setSize(Size(BorderDefaultWidth, m_levelSize.height));
    m_borders[Right].setPosition(Point(m_levelSize.width - BorderDefaultWidth, 0));
    m_borders[Right].setSize(Size(BorderDefaultWidth, m_levelSize.height));
    m_borders[Up].setPosition(Point(m_borders[Left].get(Width), 0));
    m_borders[Up].setSize(Size(m_levelSize.width - m_borders[Left].get(Width) - m_borders[Right].get(Width), BorderDefaultWidth));
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


bool ArcanoidGameEngine::startLevel()
{
    cout << "engine: startLevel" << endl;
    if (!m_isLevelPrepared) {
        return false;
    }

    m_delegate->engine_willStartLevel();

    //TODO: start timer
    for(int i = 0; i < 10; i++) {
        m_ball.move(10, 10);
        Sleep(100);
    }

    m_isLevelStarted = true;

    m_delegate->engine_levelStarted();

    return m_isLevelStarted;
}


bool ArcanoidGameEngine::pause()
{
    cout << "engine: pause" << endl;
    if (!m_isLevelStarted) {
        return false;
    }
    if (m_isGamePaused) {
        return true;
    }

    // the pause action ... now only setting a boolean :D
    m_isGamePaused = true;

    m_delegate->engine_paused();

    return m_isGamePaused;
}

bool ArcanoidGameEngine::unpause()
{
    cout << "engine: unpause" << endl;
    if (!m_isGamePaused) {
        return true;
    }

    // the unpause action .. now only setting a boolean :D
    m_isGamePaused = false;

    m_delegate->engine_unpaused();

    return !m_isGamePaused;
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


Brick ArcanoidGameEngine::createBrick(short id, short number)
{
    cout << "engine: createBrick" << endl;
    // get the row and column number of cell, where the brick must be putted
    int rowNumber = number / m_columnCount;
    int columnNumber = number - rowNumber * m_columnCount;
    // get the position of the brick's cell
    Point position;
    position.x = m_brickSize.width * columnNumber;
    position.y = m_brickSize.height * rowNumber;

    // now id indicates Brick's helath and texture
    Brick brick(BricksPath + std::to_string(id) + "." + TextrueExtension, position, m_brickSize, id);
    brick.setDelegate(m_go_delegate);
    return brick;
}

bool ArcanoidGameEngine::isBrickID(char brickID)
{
    return brickID >= '0' && brickID <= '9';
}

/*
0 1 2  3
4 5 6  7
8 9 10 11
*/