//
// Created by ryedigaryan on 3/31/2018.
//

#ifndef ARCANOID_LEVEL_H
#define ARCANOID_LEVEL_H

#include "Definitions/CommonDefinitions.h"
#include "Definitions/ModelDefinitions.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Border.h"

class ResourceManager;

class Level
{
public: // ctors, dtor
//    Level();
    explicit Level(unsigned number, Size bricksDistance, int bricksCountOnPlayer, GameObjectDelegate* go_dlg = nullptr);

    Level(const Level& other);
    Level& operator=(const Level& other);
    ~Level();

public: // public data
    float timeLimit;
    unsigned number;
    unsigned brickRowCount;
    unsigned brickColCount;
    std::list<Brick*> bricks;
    Paddle player;
    Ball ball;
    std::vector<Border> borders;

public: // interface functions
    void setGoDelegate(GameObjectDelegate* go_dlg, ObjectType goType);
    void loadFromSpec(const std::string& specPath);
    Size getSize(bool considerBorders = false) const;
    const Border& getBorder(Side sceneSide) const;
    unsigned bricksSummaryHealth() const;


    unsigned smallestIdentifier() const;
    unsigned biggestIdentifier() const;
    unsigned countOfGameObjects() const;

private: // private data
    GameObjectDelegate* go_delegate;
    ResourceManager& m_resourceManager;
    Size m_brickDistance;
    int m_bricksCountOnPlayer;
    Size m_size;

private: // helper functions
    void loadBricks(std::ifstream& specReader);
    void loadPlayer(std::ifstream& specReader);
    void loadBall(std::ifstream& specReader);
    void loadBorders(std::ifstream& specReader);
    bool isValidBrickType(unsigned id);
    Brick* createBrick(unsigned health, Point cellPos, Point offset);
};

#endif //ARCANOID_LEVEL_H
