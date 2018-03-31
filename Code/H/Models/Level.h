//
// Created by ryedigaryan on 3/31/2018.
//

#ifndef ARCANOID_LEVEL_H
#define ARCANOID_LEVEL_H

#include "Definitions/CommonDefinitions.h"
#include "Definitions/ModelDefinitions.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"

class Level {
public:
    explicit Level(GameObjectDelegate* go_delegate);
    ~Level();

    GameObjectDelegate* go_delegate;

    unsigned number;
    std::list<Brick*> bricks;
    unsigned brickRowCount;
    unsigned brickColCount;

    Paddle player;
    Ball ball;

    void loadFromSpec(const std::string& specPath);
    void loadBricks(std::ifstream& specReader);
    void loadPlayer(std::ifstream& specReader);
    void loadBall(std::ifstream& specReader);
    bool isValidBrickType(unsigned id);
    Brick* createBrick(unsigned brickType, unsigned index);
};

#endif //ARCANOID_LEVEL_H
