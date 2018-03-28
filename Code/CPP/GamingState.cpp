//
// Created by ruben on 3/25/2018.
//

#include <GameStates/GamingState.h>

void GamingState::handleInput() {
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_delegate->pushNextState();
                    return;
                case sf::Keyboard::Left:
                    m_gameData->engine
            }
        }
    }
}


void GamingState::update() {
    m_gameData->engine->process();
    m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Red);
    m_gameData->drawer->getDrawingWindow()->display();
}