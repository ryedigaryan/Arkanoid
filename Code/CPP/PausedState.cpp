//
// Created by ruben on 3/25/2018.
//

#include <GameStates/PausedState.h>

void PausedState::handleInput()
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

void PausedState::update()
{
    m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Blue);
    m_gameData->drawer->getDrawingWindow()->display();
}