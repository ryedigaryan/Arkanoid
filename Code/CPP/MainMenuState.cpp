//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"

MainMenuState::MainMenuState(GameData *gameData) : State(gameData) {
    cout << "State: MainMenu" << endl;
}

void MainMenuState::init() {
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
                    m_gameData->stateMachine->pushState(new GamingState(m_gameData, FirstLevelNumber));
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
