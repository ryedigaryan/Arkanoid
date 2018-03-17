//
// Created by ryedigaryan on 2/26/2018.
//
#ifndef Definitions
#define Definitions
#include <iostream> // just for debugging
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <map>
//using std::string;
//using std::ifstream;
//using std::list;
//using std::vector;
//using std::map;
using std::cout;
using std::cin;
using std::endl;

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////DEFINITIONS////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#define Gray sf::Color(190, 190, 190)
#define GameSceneBackgroundColor sf::Color(229, 170, 88)

// Point
#define PointDefaultValueX 0
#define PointDefaultValueY 0

// Size
#define SizeDefaultValueWidth 0
#define SizeDefaultValueHeight 0

// Vector
#define FullAngle 360
#define StraightAngle 180
#define PI 3.14159265358979323846

// Ball
#define BallDefaultTexturePath "Resources/Pictures/Balls/1.png"

// Brick
#define BrickDefaultInitialHealth 1

// Paddle
#define PaddleDefaultInitialHealth 3
#define PaddleDefaultTexturePath "Resources/Pictures/Paddles/1.png"

// ArcanoidGameDrawer
#define Show true
#define NotShow false
#define RepeatTexture true
#define NotRepeatTexture false

#define PopUpSizeRatio 0.5
#define PopUpColor sf::Color::Magenta
#define PopUpSize sf::Vector2f(1500, 500)

#define TextOffset 20
#define TextColor sf::Color::White
#define NonMiddleCharacterSizeRatio 0.5

#define DefaultFontPath "Resources/Fonts/RAVIE.TTF"
#define LevelSpecsPath "Resources/LevelSpecs"
#define LevelSpecExtension "lvl"
#define LevelCount 6
#define BallsPath "Resources/Pictures/Balls"
#define BordersPath "Resources/Pictures/Borders"
#define BricksPath "Resources/Pictures/Bricks"
#define PaddlesPath "Resources/Pictures/Paddles"
#define TextureExtension "png"

#define DefaultPicturePath "Resources/Pictures/Default.png"

// ArcanoidGameEngine
#define PathSeparator "/"
#define ExtensionSeparator "."

#define PathToTexture(dir, name) (std::string(dir) + PathSeparator + std::to_string(name) + ExtensionSeparator + TextureExtension)

#define BordersCount 3

#define LevelIncorrectWidth (-1)
#define LevelIncorrectHeight (-1)
#define LevelIncorrectSize Size(LevelIncorrectWidth, LevelIncorrectHeight)

#define LevelDefaultCornerX 10
#define LevelDefaultCornerY 10

#define BrickDefaultSizeWidth 100
#define BrickDefaultSizeHeight 50

#define PlayerDefaultSizeWidth 250
#define PlayerDefaultSizeHeight 40
#define PlayerBottomOffset 25

#define BallDefaultSizeWidth 40
#define BallDefaultSizeHeight 40

#define BorderDefaultWidth 25

#define DefaultBlockCountOnPaddle 15

// ArcanoidGameManager
//#define PathSeparator "/"
//#define ExtensionSeparator "."

#define FPS 30
#define FrameDuration (1.f / FPS)

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////ENUMS////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

enum Axis {
    X,
    Y
};

enum Dimension {
    Height,
    Width
};

enum Side {
    Left,
    Up,
    Right,
    Down
};

enum TextPosition {
    Top = -1,
    Middle,
    Bottom
};

enum GameObjectType {
    TBrick,
    TPaddle,
    TBall,
    TBorder,
    TLevel
};

void fail(const std::string& method);

#endif // !Definitions