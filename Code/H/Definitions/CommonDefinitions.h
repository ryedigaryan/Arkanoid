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

#define FPS 60
#define OneFrameDuration (1.0 / FPS) // as seconds

#define WindowTitle "Arkanoid - by Ruben"

#define FirstLevelNumber 1
#define LastLevelNumber 6

#define Replace true // used when StateMachine must replace current active state with the new one

#define PauseButton sf::Keyboard::P
#define MoveLeftButton sf::Keyboard::Left
#define MoveRightButton sf::Keyboard::Right

#define DefaultTexturePath "Resources/Textures/default"
#define DefaultFontPath "Resources/Fonts/default"
#define LevelSpecsDir "Resources/LevelSpecs/"
#define TexturesDir "Resources/Textures/"
#define PathSeparator "/"

#define MainMenuButtonsCount 3
#define UnMarkedButtonColor sf::Color::White
#define MarkedButtonColor sf::Color::Black

#define BricksDistance Size(0, 0)
#define BricksCountOnPlayer 5

#define LeftBorder 1
#define RightBorder 2

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
    SideNone  = 0x00000000,
    SideLeft  = 0x0000000f,
    SideRight = 0x000000f0,
    SideUp    = 0x00000f00,
    SideDown  = 0x0000f000,
};

namespace logutils {
    std::string nameOf(ObjectType);
    std::string nameOf(Side);

    extern std::ofstream logstream;
}

namespace myutils {
    template<typename T>
    T randomInRange(T lowerBound, T upperBound) {
        T diff = upperBound - lowerBound;
        double percent = (rand() % 101) / 100.0;
        return lowerBound + static_cast<T>(diff * percent);
    }

    float middle(float s1, float s2);
}

#endif //ARCANOID_COMMONDEFINITIONS_H
