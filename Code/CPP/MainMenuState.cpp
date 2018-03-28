//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"

MainMenuState::MainMenuState(GameData *gameData, StateDelegate *dlgate) : State(gameData, dlgate) {
    m_needsRedraw = true;
}

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
    if(m_needsRedraw) {
        m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Yellow);
        m_gameData->drawer->drawMenu();
        m_needsRedraw = false;
    }
}

void MainMenuState::pause() {
    m_needsRedraw = false;
}

void MainMenuState::resume() {
    m_needsRedraw = true;
}