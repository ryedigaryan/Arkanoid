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

#define FPS 10
#define OneFrameDuration (1 / FPS) // as seconds

#define WindowTitle "Arkanoid - by Ruben"

#define FirstLevelNumber 1
#define LastLevelNumber 6

#define Replace true // used when StateMachine must replace current active state with the new one
#define HasWon true
#define HasLost true

#define PauseButton sf::Keyboard::P
#define MoveLeftButton sf::Keyboard::Left
#define MoveRightButton sf::Keyboard::Right


enum Side {
    SideLeft,
    SideRight,
    SideUp,
    SideDown,
    SideNone
};

#endif //ARCANOID_COMMONDEFINITIONS_H
