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

enum Side {
    Left,
    Right,
    Up,
    Down,
    None
};

#endif //ARCANOID_COMMONDEFINITIONS_H
