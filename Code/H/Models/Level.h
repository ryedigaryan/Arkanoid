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

class Level {
public:
    explicit Level(GameObjectDelegate* go_delegate = nullptr);
    ~Level();

    unsigned number;
    unsigned brickRowCount;
    unsigned brickColCount;
    std::list<Brick*> bricks;
    Paddle player;
    Ball ball;

    void setGoDelegate(GameObjectDelegate* go_dlg);

    void loadFromSpec(const std::string& specPath);
    void loadBricks(std::ifstream& specReader);
    void loadPlayer(std::ifstream& specReader);
    void loadBall(std::ifstream& specReader);
    bool isValidBrickType(unsigned id);
    Brick* createBrick(unsigned brickType, unsigned index);

private:
    GameObjectDelegate* go_delegate;
};

#endif //ARCANOID_LEVEL_H
