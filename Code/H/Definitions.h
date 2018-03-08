//
// Created by ryedigaryan on 2/26/2018.
//

#include <iostream> // just for debugging
#include <string>
#include <list>
#include <fstream>
#include <vector>
using std::string;
using std::ifstream;
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////DEFINITIONS////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#define Gray sf::Color(190, 190, 190)

// Point
#define PointDefaultValueX 0
#define PointDefaultValueY 0

// Size
#define SizeDefaultValueWidht 0
#define SizeDefaultValueHeight 0

// Vector
#define FullAngle 360
#define StraightAngle 180
#define PI 3.14159265358979323846

// Ball
#define BallDefaultTexture "Resources/Pictures/Balls/1.png"

// Brick
#define BrickDefaultInitialHealth 1

// Paddle
#define PaddleDefaultInitialHealth 3
#define PaddleDefaultTexture "Resources/Pictures/Paddles/1.png"

// ArcanoidGameEngine
#define BordersCount 3

#define LevelIncorrectWidth (-1)
#define LevelIncorrectHeight (-1)
#define LevelIncorrectSize Size(LevelIncorrectWidth, LevelIncorrectHeight)

#define LevelDefaultCornerX 10
#define LevelDefaultCornerY 10

#define BrickDefaultSizeWidth 30
#define BrickDefaultSizeHeight 15

#define PlayerDefaultSizeWidth 75
#define PlayerDefaultSizeHeight 15
#define PlayerBottomOffset 5

#define BallDefaultSizeWidth 15
#define BallDefaultSizeHeight 15

#define BorderDefaultWidth 5

#define DefaultBlockCountOnPaddle 4

// ArcanoidGameDrawer
#define Show true
#define Hide false

#define LevelSpecsPath "Resources/LevelSpecs"
#define LevelSpecExtension "lvl"
#define LevelCount 6
#define BallsPath "Resources/Pictures/Balls/"
#define BordersPath "Resources/Pictures/Borders/"
#define BricksPath "Resources/Pictures/Bricks/"
#define PaddlesPath "Resources/Pictures/Paddles/"
#define TextrueExtension "png"


// ArcanoidGameManager
#define PathSeparator "/"
#define ExtensionSeparator "."
#define LayerLoading 4
#define LayerMenu 3
#define LayerGameObject 1
#define LayerLevelInfo 2

#define FPS 30
#define FrameDuration (1.f / FPS)
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////ENUMS////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Axis_enum
#define Axis_enum
enum Axis {
    X,
    Y
};
#endif // !Axis_enum

#ifndef Dimension_enum
#define Dimension_enum
enum Dimension {
    Height,
    Width
};
#endif // !Dimension_enum

#ifndef Side_enum
#define Side_enum
enum Side {
    Left,
    Up,
    Right,
    Down
};
#endif // !Side_enum
