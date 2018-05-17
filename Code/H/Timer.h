//
// Created by ruben on 5/18/2018.
//

#ifndef ARCANOID_TIMER_H
#define ARCANOID_TIMER_H

#include <SFML/System/Clock.hpp>

class Timer {
public:
    Timer();

public: // data
    sf::Clock m_clock;
    float m_runTime;
    bool m_paused;

public: // methods
    void  reset();
    void  start();
    void  pause();
    float getElapsedSeconds();
};

#endif //ARCANOID_TIMER_H
