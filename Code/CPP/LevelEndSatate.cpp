//
// Created by ruben on 3/25/2018.
//

#include "GameStates/LevelEndState.h"

void LevelEndSatate::handleInput() {
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

void LevelEndSatate::update() {
    m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Green);
    m_gameData->drawer->getDrawingWindow()->display();
}