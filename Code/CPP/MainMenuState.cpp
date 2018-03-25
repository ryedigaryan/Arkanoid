//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"

void MainMenuState::handleInput() {
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_delegate->pushNextState();
                    return;
                case sf::Keyboard::Escape:
                    mainWindow->close();
                    return;
            }
        }
    }
}

void MainMenuState::update() {
    m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Yellow);
    m_gameData->drawer->drawMenu();
}