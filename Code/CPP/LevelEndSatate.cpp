//
// Created by ruben on 3/25/2018.
//

#include "GameStates/LevelEndState.h"

LevelEndState::LevelEndState(GameData *gameData, const unsigned& level, const bool& hasWon) : State(gameData), m_level(level), m_hasWon(hasWon) {
    cout << "State: LevelEnd" << endl;
}

void LevelEndState::init() {
    m_needsRedraw = true;
}

void LevelEndState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    // pops himself
                    m_gameData->stateMachine->popActiveState();
                    return;
            }
        }
    }
}

void LevelEndState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->clearScreen(sf::Color::Red);
        m_gameData->drawer->drawLevelEndInfo(m_level, m_hasWon);
        m_needsRedraw = false;
    }
}

void LevelEndState::pause()
{
    m_needsRedraw = false;
}

void LevelEndState::resume()
{
    m_needsRedraw = true;
}


