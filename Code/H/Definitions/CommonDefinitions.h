//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_COMMONDEFINITIONS_H
#define ARCANOID_COMMONDEFINITIONS_H

#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::cin;

#include <string>
#include <vector>
#include <stack>
#include <list>
#include <map>

#define FPS 100
#define OneFrameDuration (1.0 / FPS) // as seconds

#define WindowTitle "Arkanoid - by Ruben"

#define FirstLevelNumber 1
#define LastLevelNumber 6

#define Replace true // used when StateMachine must replace current active state with the new one
#define HasWon true
#define HasLost true

#define PauseButton sf::Keyboard::P
#define MoveLeftButton sf::Keyboard::Left
#define MoveRightButton sf::Keyboard::Right

#define DefaultTexturePath "Resources/Textures/default"
#define DefaultFontPath "Resources/Fonts/default"
#define LevelSpecsDir "Resources/LevelSpecs/"
#define TexturesDir "Resources/Textures/"
#define PathSeparator "/"

#define IDontCare 666

#define BricksDistance Size(2, 2)
#define BricksCountOnPlayer 5

#define LeftBorder 1
#define RightBorder 2

#define ConsiderBorders true

#define NotFound nullptr

enum StateType {
    StateTypeMainMenu,
    StateTypeGaming,
    StateTypePaused,
    StateTypeLevelEnd,
    StateTypeEntireGameWon,
};

enum ObjectType {
    ObjectTypePaddle,
    ObjectTypeBall,
    ObjectTypeBorder,
    ObjectTypeBrick,
    ObjectTypeLevel,
    ObjectTypeNone,
};

enum Resolution {
    ResolutionHigh,   // 2k - ∞
    ResolutionMedium, // 1920x1080 - 2k
    ResolutionLow,    // 480x640 - 1920x1080
};

enum Side {
    SideLeft  = 0x0000000f,
    SideRight = 0x000000f0,
    SideUp    = 0x00000f00,
    SideDown  = 0x0000f000,
    SideNone  = 0x000f0000,
};

typedef std::pair<Side, Side> TwoSides;

std::string nameOf(ObjectType);
std::string nameOf(Side);
extern std::ofstream logstream;

#endif //ARCANOID_COMMONDEFINITIONS_H
