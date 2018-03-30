//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(GameData *gameData) : State(gameData) {
    m_needsRedraw = true;
}

void MainMenuState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_gameData->stateMachine->pushState(new PausedState(m_gameData));
                    return;
                case sf::Keyboard::Escape:
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

void MainMenuState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->clearScreen();
        m_gameData->drawer->drawMenu();
        m_needsRedraw = false;
    }
}

void MainMenuState::pause()
{
    m_needsRedraw = false;
}

void MainMenuState::resume()
{
    m_needsRedraw = true;
}