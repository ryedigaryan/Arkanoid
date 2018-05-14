//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_SIZE_H
#define ARCANOID_SIZE_H

enum Dimension {
    DimensionWidth,
    DimensionHeight
};

class Size
{
public:
    explicit Size(float width = 0, float height = 0) noexcept
            : width(width), height(height) {}

public:
    float width;
    float height;
};

#endif //ARCANOID_SIZE_H
