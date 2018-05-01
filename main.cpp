
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ArkanoidGameController.h"

using namespace std;

std::string sideName(Side side) {
    switch(side) {
        case SideLeft:
            return "SideLeft";
        case SideRight:
            return "SideRight";
        case SideUp:
            return "SideUp";
        case SideDown:
            return "SideDown";
        case SideNone:
            return "SideNone";
    }
}

void print(int val) {
    Side a = SideNone;
    Side b = SideNone;
    if((val & SideLeft) == SideLeft) {
        cout << "SideLeft";
        if(a == SideNone)
            a = SideLeft;
        else
            b = SideLeft;
    }
    if((val & SideRight) == SideRight) {
        cout << " | SideRight";
        if(a == SideNone)
            a = SideRight;
        else
            b = SideRight;
    }
    if((val & SideUp) == SideUp) {
        cout << " | SideUp";
        if(a == SideNone)
            a = SideUp;
        else
            b = SideUp;
    }
    if((val & SideDown) == SideDown) {
        cout << " | SideDown";
        if(a == SideNone)
            a = SideDown;
        else
            b = SideDown;
    }
    if((val & SideNone) == SideNone) {
        cout << " | SideNone";
        if(a == SideNone)
            a = SideNone;
        else
            b = SideNone;
    }
    cout << endl;
}

int main()
{
    int a = 10;
    const int& b = a;
//    print(SideLeft);
//    print(SideRight);
//    print(SideUp);
//    print(SideDown);
//    print(SideNone);
//    print(SideLeft | SideDown);
//    print(SideDown | SideLeft);
//    print(SideNone | SideUp);
//    print(SideUp   | SideNone);
//    print(SideDown | SideUp);
//    print(SideDown | SideLeft);
//    print(SideDown | SideLeft | SideRight);
//    print(SideDown | SideLeft | SideRight | SideLeft);
//    return 0;


    ArkanoidGameController c;
    c.start();
    return 0;
}