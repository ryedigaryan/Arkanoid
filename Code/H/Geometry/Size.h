//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_SIZE_H
#define ARCANOID_SIZE_H

#include "Definitions.h"

class Size {
public:
    Size()
            : Size(SizeDefaultValueWidth, SizeDefaultValueHeight) {}

    Size(int width, int height)
            : width(width), height(height) {}

public:
    int width;
    int height;
};

#endif //ARCANOID_SIZE_H
