//
// Created by ruben on 3/25/2018.
//

#include <ArkanoidGameController.h>

ArkanoidGameController::ArkanoidGameController()
{
    m_allStates.push_back(new MainMenuState(&m_gameData, this));
    m_allStates.push_back(new PausedState(&m_gameData, this));
    m_allStates.push_back(new GamingState(&m_gameData, this));
    m_allStates.push_back(new LevelEndSatate(&m_gameData, this));

    m_gameData.engine = new ArkanoidEngine(); //TODO: singleton engine
    m_gameData.drawer = new ArkanoidDrawer();
}

State *ArkanoidGameController::nextState()
{
    return m_allStates[(m_stateMachine.statesCount() + 1) % m_allStates.size()];
}

void ArkanoidGameController::start()
{
    m_stateMachine.pushState(m_allStates[0]);
    sf::RenderWindow* mainWindow = m_gameData.drawer->getDrawingWindow();
    sf::Clock c;
    while(mainWindow->isOpen()) {
        if(c.getElapsedTime().asSeconds() > OneFrameTime) {
            c.restart();
            m_stateMachine.getActiveState()->handleInput();
            m_stateMachine.getActiveState()->update();
        }
    }
}

void ArkanoidGameController::pushNextState() {
    m_stateMachine.pushState(nextState());
}
