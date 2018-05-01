//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_SIZE_H
#define ARCANOID_SIZE_H

enum Dimension {
    DimensionWidth,
    DimensionHeight
};

class Point;

class Size {
public:
    explicit Size(int width = 0, int height = 0) noexcept
            : width(width), height(height) {}

public:
    int width;
    int height;
};

#endif //ARCANOID_SIZE_H
