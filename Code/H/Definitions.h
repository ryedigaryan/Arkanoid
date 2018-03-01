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
#define BallDefaultTexture 0

// Brick
#define BrickDefaultInitialHealth 1
#define BrickDefaultTexture 0

// Paddle
#define PaddleDefaultInitialHealth 1
#define PaddleDefaultTexture 0

// ArcanoidGameEngine
#define LevelDefaultCornerX 10
#define LevelDefaultCornerY 10

#define BrcikDefaultSizeWidth 10
#define BrcikDefaultSizeHeight 5

#define PlayerDefaultSizeWidth 25
#define PlayerDefaultSizeHeight 5
#define PlayerBottomOffset 5

#define BallDefaultSizeWidth 5
#define BallDefaultSizeHeight 5

#define BorderDefaultWidth 5

#define DefaultBlockCountOnPaddle 4

// ArcanoidGameDrawer
#define Show true
#define Hide false

#define LevelSpecsPath "Resources/LevelSpecs"
#define LevelSpecExtension "lvl"
#define LevelCount 6
#define BallsPath "Resources/Pictures/Balls"
#define BordersPath "Resources/Pictures/Borders"
#define BricksPath "Resources/Pictures/Bricks"
#define PaddlesPath "Resources/Pictures/Paddles"


// ArcanoidGameManager ... when draws something
#define PathSeparator "/"
#define ExtensionSeparator "."
#define LayerLoading 4
#define LayerMenu 3
#define LayerGameObject 1
#define LayerLevelInfo 2

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
