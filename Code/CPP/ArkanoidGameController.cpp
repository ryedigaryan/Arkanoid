//
// Created by ruben on 3/25/2018.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "ArkanoidGameController.h"

ArkanoidGameController::ArkanoidGameController()
{
    m_gameData.engine = new ArkanoidEngine(); //TODO: singleton engine
    m_gameData.drawer = new ArkanoidDrawer();
    m_gameData.stateMachine = new StateMachine();
    m_gameData.resourceManager = &ResourceManager::getManager();
    //TODO: resolution must be dependent from screen
    m_gameData.resourceManager->m_resolution = ResolutionMedium;
}

void ArkanoidGameController::start()
{
    StateMachine* stateMachine = m_gameData.stateMachine;
    sf::RenderWindow* mainWindow = m_gameData.drawer->getDrawingWindow();
    sf::Clock c;

    stateMachine->pushState(new MainMenuState(&m_gameData));
    while(mainWindow->isOpen()) {
        if(c.getElapsedTime().asSeconds() > OneFrameDuration) {
            c.restart();
            stateMachine->getActiveState()->handleInput();
            stateMachine->getActiveState()->update();
            stateMachine->getActiveState()->draw();
        }
    }
}