//
// Created by ruben on 3/25/2018.
//

#include <GameStates/EntireGameWonState.h>
#include "GameStates/GamingState.h"

GamingState::GamingState(GameData* gameData, unsigned startLevelNumber, unsigned lastLevelNumber) : State(gameData), m_firstLevelNumber(startLevelNumber), m_lastLevelNumber(lastLevelNumber)
{
    cout << "State: Gaming" << endl;
}

void GamingState::init()
{
    m_gameData->drawer->drawGameScene();
    m_gameData->drawer->drawGameScene();
    setEngineLevel(m_currentLevelNumber = m_firstLevelNumber);
    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress()));
}

void GamingState::handleInput()
{
    Side playerMovementSide = SideNone;
    static sf::Event e;
    while(m_gameData->drawer->getDrawingWindow()->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case PauseButton:
                    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress()));
                    return;
                case MoveLeftButton:
                    playerMovementSide = SideLeft;
                    break;
                case MoveRightButton:
                    playerMovementSide = SideRight;
                    break;
            }
        }
        else if(e.type == sf::Event::KeyReleased){
            switch(e.key.code) {
                case MoveLeftButton:
                case MoveRightButton:
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
    if(m_currentLevelState != LevelStateInProcess) {
        m_gameData->stateMachine->pushState(new LevelEndState(m_gameData, m_currentLevelNumber, m_currentLevelState, m_lastLevelNumber));
    }
    m_gameData->drawer->drawGameScene();
}

void GamingState::pause()
{
    // nothing must be done
}

void GamingState::resume()
{
    if(m_currentLevelState != LevelStateInProcess) {
        if(m_currentLevelNumber == m_lastLevelNumber) {
            m_gameData->stateMachine->popActiveState();
            return;
        }
        setEngineLevel(++m_currentLevelNumber);
    }
    // game scene must be updated 2 times because now screen may be modified (for example - pause info may be drawn)
    m_gameData->drawer->drawGameScene();
    m_gameData->drawer->drawGameScene();
}

void GamingState::setEngineLevel(const unsigned& levelNumber) {
    Level level = m_gameData->resourceManager->getLevel(levelNumber);
    level.setGoDelegate(this);
    m_gameData->engine->setLevel(level);
    m_currentLevelState = m_gameData->engine->getLevelState();
}