//
// Created by ruben on 3/25/2018.
//

#include "GameStates/PausedState.h"
#include "GameStates/GamingState.h"
#include "StateMachine.h"

PausedState::PausedState(GameData *gameData, const unsigned& level, const int progress) : State(gameData), m_level(level), m_progress(progress)
{
    cout << "State: Paused" << endl;
}

void PausedState::init()
{
    m_needsRedraw = true;
}

void PausedState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::P:
                    // pops himself
                    m_gameData->stateMachine->popActiveState();
                    return;
            }
        }
    }
}

void PausedState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->drawLevelStartInfo(m_level, m_progress);
        m_needsRedraw = false;
    }
}

void PausedState::pause()
{
    m_needsRedraw = false;
}

void PausedState::resume()
{
    m_needsRedraw = true;
}
