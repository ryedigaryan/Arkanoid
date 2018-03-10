//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEENGINE_H
#define ARCANOID_ARCANOIDGAMEENGINE_H

#include "Definitions.h"
#include "Models/AllGameObjects.h"
#include "Interfaces/ArcanoidGameEngineDelegate.h"
#include "Interfaces/GameObjectDelegate.h"


class ArcanoidGameEngine {
public: // static functions
    static ArcanoidGameEngine& getEngine() {
        static ArcanoidGameEngine singletonInstance;
        return singletonInstance;
    }

public: // instance functions
    void setGameObjectDelegate(GameObjectDelegate* go_delegate);
    Size prepareLevel(const string& levelSpecFilePath); // loads level from spec and prepares game scene
    void startLevel();	// starts timer and the fun begins :D
    void pause();		// pauses game
    void unpause();		// resumes game

    int getProgress() { return 0; }; // returns progress in percents

    int getCountOfRows();
    int getCountOfColumns();

    void setDelegate(ArcanoidGameEngineDelegate* engineDelegate);

    void process(); // game logic... the function which calls timer
    void movePlayer(Side direction);
    void stopPlayerMoving();

private: // members
    GameObjectDelegate* m_go_delegate = nullptr;
    ArcanoidGameEngineDelegate* m_delegate = nullptr;

    bool m_isLevelLoaded	= false;
    bool m_isLevelPrepared	= false;
    bool m_isLevelStarted	= false;
    bool m_isGamePaused		= false;

    list<Brick*> m_bricks;  // the list of Bricks in current level
    int m_rowCount = 0;    // count of rows of Bricks in current level
    int m_columnCount = 0; // count of columns of Bricks in current level

    Border m_borders[BordersCount];  // game scene rounded by 3 borders(Up, Down, Left, Right)
    Paddle m_player = Paddle(PaddleDefaultTexturePath);
    Ball m_ball = Ball(BallDefaultTexturePath);

    Point m_brickCorner // the left upper corner of first brick
            = Point(LevelDefaultCornerX, LevelDefaultCornerY);
    Size m_brickSize	// size of one Brick
            = Size(BrickDefaultSizeWidth, BrickDefaultSizeHeight);
    Size m_levelSize;	// size of all game scene
    //TODO: remove
    int m_borderWidth	// width of left/right border and height of up/down border
            = BorderDefaultWidth;
    int m_blocksCountOnPlayer	// distance between the lowest Brick and Paddle at the start of level
            = DefaultBlockCountOnPaddle;

private: // functions
    // prepare functions
    void loadLevel(ifstream& levelSpecReader); // reads spec file and fills m_bricks list
    void prepareLevelSize(); // calculates size of game scene considering Borders and Bricks
    void prepareBorders();   // sets sizes of 3 borders
    void preparePlayer();	 // sets player's position and size
    void prepareBall();		 // sets ball's position and size
    // utility functions
    Brick* createBrick(short id, short number); // creates a Brick in right place
    bool isBrickID(char brickID);			   // checks whether given ID is a valid Brcik ID or not

private: // making singleton
    ArcanoidGameEngine() {};
public: // making singleton
    ArcanoidGameEngine(ArcanoidGameEngine const&) = delete;
    void operator=(ArcanoidGameEngine const&) = delete;
};

#endif //ARCANOID_ARCANOIDGAMEENGINE_H
