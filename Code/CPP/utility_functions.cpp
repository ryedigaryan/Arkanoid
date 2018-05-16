//
// Created by ruben on 4/14/2018.
//
#include "Definitions/CommonDefinitions.h"

std::ofstream logutils::logstream("arkanoid.log.txt");

std::string logutils::nameOf(Side side)
{
    switch(side) {
        case SideLeft:
            return "SideLeft";
        case SideRight:
            return "SideRight";
        case SideUp:
            return "SideUp";
        case SideDown:
            return "SideDown";
        default:
            return "SideNone";
    }
}

std::string logutils::nameOf(ObjectType o)
{
    switch(o) {
        case ObjectTypePaddle:
            return "ObjectTypePaddle";
        case ObjectTypeBall:
            return "ObjectTypeBall";
        case ObjectTypeBorder:
            return "ObjectTypeBorder";
        case ObjectTypeBrick:
            return "ObjectTypeBrick";
        case ObjectTypeLevel:
            return "ObjectTypeLevel";
        default:
            return "ObjectTypeNone";
    }
}