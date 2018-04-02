//
// Created by ruben on 3/25/2018.
//

#include "GameStates/GamingState.h"

GamingState::GamingState(GameData *gameData, unsigned startLevelNumber) : State(gameData)
{
    cout << "State: Gaming" << endl;
    m_currentLevelNumber = startLevelNumber;
    m_currentLevelState = m_gameData->engine->getLevelState();
}

void GamingState::init()
{
    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress()));
}

void GamingState::handleInput()
{
    Side playerMovementSide = SideNone;
    sf::Event e;
    while(m_gameData->drawer->getDrawingWindow()->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::P:
                    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress()));
                case sf::Keyboard::Left:
                    playerMovementSide = SideLeft;
                    break;
                case sf::Keyboard::Right:
                    playerMovementSide = SideRight;
                    break;
            }
        }
        else if(e.type == sf::Event::KeyReleased){
            switch(e.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    playerMovementSide = SideNone;
            }
        }
    }
    playerMovementSide == SideNone ? m_gameData->engine->stopPlayer()
                                   : m_gameData->engine->movePlayer(playerMovementSide);
}

void GamingState::update()
{
    m_gameData->engine->process();
    m_currentLevelState = m_gameData->engine->getLevelState();
    if(m_currentLevelState == LevelStateWon) {
        m_gameData->stateMachine->pushState(new LevelEndState(m_gameData, m_currentLevelNumber, HasWon));
    }
    else if(m_currentLevelState == LevelStateLost) {
        m_gameData->stateMachine->pushState(new LevelEndState(m_gameData, m_currentLevelNumber, HasLost));
    }
}

void GamingState::pause()
{
    cout << "TODO: GamingState::pause()" << endl;
}

void GamingState::resume()
{
    if(m_currentLevelState == LevelStateWon || m_currentLevelState == LevelStateLost) { //TODO: curState != None
        m_currentLevelNumber++;
        Level& level = m_gameData->resourceManager->getLevel(m_currentLevelNumber);
        level.setGoDelegate(this);
        m_gameData->engine->setLevel(level);
        m_currentLevelState = m_gameData->engine->getLevelState();
    }
    m_gameData->drawer->drawGameScene();
}

