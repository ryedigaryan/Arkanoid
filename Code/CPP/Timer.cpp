//
// Created by ruben on 5/18/2018.
//

#include <Timer.h>

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    m_runTime = 0;
    m_paused = false;
    m_clock.restart();
}

void Timer::start()
{
    if (m_paused) {
        m_clock.restart();
    }
    m_paused = false;
}

void Timer::pause()
{
    if (!m_paused) {
        m_runTime += m_clock.getElapsedTime().asSeconds();
    }
    m_paused = true;
}

float Timer::getElapsedSeconds()
{
    if (!m_paused) {
        return m_runTime + m_clock.getElapsedTime().asSeconds();
    }
    return m_runTime;
}
