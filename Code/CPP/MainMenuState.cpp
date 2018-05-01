//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"

MainMenuState::MainMenuState(GameData* gameData) : StaticImageState(gameData, sf::Keyboard::Return)
{

}

void MainMenuState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            if(e.key.code == m_popKey) {
                m_gameData->stateMachine->pushState(new GamingState(m_gameData, FirstLevelNumber, LastLevelNumber));
                return;
            } else if(e.key.code == sf::Keyboard::Escape) {
                mainWindow->close();
                return;
            }
        }
        else if(e.type == sf::Event::Closed) {
            delete m_gameData->drawer;
            m_gameData->drawer = nullptr;
        }
    }
}

void MainMenuState::draw()
{
    if(m_needsRedraw) {
        m_gameData->drawer->clearScreen();
        m_gameData->drawer->drawMenu();
        m_needsRedraw = false;
    }
}