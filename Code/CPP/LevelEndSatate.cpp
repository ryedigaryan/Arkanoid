//
// Created by ruben on 3/25/2018.
//

#include "GameStates/LevelEndState.h"

LevelEndSatate::LevelEndSatate(GameData *gameData, StateDelegate *dlgate) : State(gameData, dlgate) {
    m_needsRedraw = true;
}

void LevelEndSatate::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_delegate->pushNextState();
                    return;
            }
        }
    }
}

void LevelEndSatate::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Green);
        m_gameData->drawer->getDrawingWindow()->display();
        m_needsRedraw = false;
    }
}

void LevelEndSatate::pause()
{
    m_needsRedraw = false;
}

void LevelEndSatate::resume()
{
    m_needsRedraw = true;
}


