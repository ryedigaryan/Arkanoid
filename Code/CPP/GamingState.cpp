//
// Created by ruben on 3/25/2018.
//

#include "GameStates/GamingState.h"

GamingState::GamingState(GameData* gameData, unsigned startLevelNumber, unsigned lastLevelNumber) : State(gameData), m_firstLevelNumber(startLevelNumber), m_lastLevelNumber(lastLevelNumber)
{
    cout << "State: Gaming" << endl;
    m_gameData->engine->m_delegate = this;
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

void GamingState::setEngineLevel(const unsigned& levelNumber)
{
    Level level = m_gameData->resourceManager->getLevel(levelNumber);
    level.setGoDelegate(this, ObjectTypePaddle);
    level.setGoDelegate(this, ObjectTypeBall);
    level.setGoDelegate(this, ObjectTypeBrick);
    m_gameData->engine->setLevel(level);
    m_currentLevelState = m_gameData->engine->getLevelState();
}

void GamingState::calculateScaling()
{
    Size engineLevelSize = m_gameData->engine->getLevel().getSize();
    sf::Vector2f drawerLevelSize = m_gameData->drawer->getLevelSize();
    m_scaleFactor.x = drawerLevelSize.x / engineLevelSize.width;
    m_scaleFactor.y = drawerLevelSize.y / engineLevelSize.height;
}

std::pair<sf::Vector2f, sf::Vector2f> GamingState::scale(const Point& position, const Size &size)
{
    sf::Vector2f scaledSize(size.width * m_scaleFactor.x, size.height * m_scaleFactor.y);
    sf::Vector2f scaledPosition;
    scaledPosition.x = position.x + (scaledSize.x - size.width) / 2.f;
    scaledPosition.y = position.y + (scaledSize.y - size.height) / 2.f;
    return std::pair<sf::Vector2f, sf::Vector2f>(scaledPosition, scaledSize);
}

void GamingState::engine_levelSet(const Level &level) {
    calculateScaling();
//    std::pair<sf::Vector2f, sf::Vector2f> scaled;
    for(auto brick : level.bricks) {
        std::pair<sf::Vector2f, sf::Vector2f> scaled = scale(brick->getPosition(), brick->getSize());
        m_gameData->drawer->drawObject(scaled.first, scaled.second, m_gameData->resourceManager->getTexture(brick->getType()));
    }
}
