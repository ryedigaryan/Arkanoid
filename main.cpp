
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ArkanoidGameController.h"

using namespace std;
void printVec(const double& deg, const Vector& v);
void rot(Vector& v, double deg);
//std::string sideName(Side side) {
//    switch(side) {
//        case SideLeft:
//            return "SideLeft";
//        case SideRight:
//            return "SideRight";
//        case SideUp:
//            return "SideUp";
//        case SideDown:
//            return "SideDown";
//        case SideNone:
//            return "SideNone";
//    }
//}
//
//void print(int val) {
//    Side a = SideNone;
//    Side b = SideNone;
//    if((val & SideLeft) == SideLeft) {
//        cout << "SideLeft";
//        if(a == SideNone)
//            a = SideLeft;
//        else
//            b = SideLeft;
//    }
//    if((val & SideRight) == SideRight) {
//        cout << " | SideRight";
//        if(a == SideNone)
//            a = SideRight;
//        else
//            b = SideRight;
//    }
//    if((val & SideUp) == SideUp) {
//        cout << " | SideUp";
//        if(a == SideNone)
//            a = SideUp;
//        else
//            b = SideUp;
//    }
//    if((val & SideDown) == SideDown) {
//        cout << " | SideDown";
//        if(a == SideNone)
//            a = SideDown;
//        else
//            b = SideDown;
//    }
//    if((val & SideNone) == SideNone) {
//        cout << " | SideNone";
//        if(a == SideNone)
//            a = SideNone;
//        else
//            b = SideNone;
//    }
//    cout << endl;
//}

void test();

int main()
{
//    test();
//    return 0;
    ArkanoidGameController c;
    c.start();
    return 0;
}

void test() {
    Vector v(10, 0);
    rot(v, 0);
    rot(v, 180);
    rot(v, -180);
    rot(v, 45);
    rot(v, -45);
    rot(v, 90);
    rot(v, -90);
    rot(v, 90);
    rot(v, 45);
    rot(v, 45);
}

void rot(Vector& v, double deg) {
    v.rotate(deg * M_PI / 180);
    printVec(deg, v);
}

void printVec(const double& deg, const Vector& v) {
    cout << deg << ":\t" << v.projection(AxisX) << " " << v.projection(AxisY) << endl;
}


