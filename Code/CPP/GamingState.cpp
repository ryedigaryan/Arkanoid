//
// Created by ruben on 3/25/2018.
//

#include "GameStates/GamingState.h"

GamingState::GamingState(GameData *gameData) : State(gameData) {
    cout << "State: Gaming" << endl;
}

void GamingState::init() {
    m_currentLevel = 96;
    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevel));
}

void GamingState::handleInput() {
    Side playerMovementSide = Side::None;
    sf::Event e;
    while(m_gameData->drawer->getDrawingWindow()->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return: //TODO: temporarily case for debug
                    m_gameData->stateMachine->pushState(new LevelEndState(m_gameData, m_currentLevel, true), true);
                    return;
                case sf::Keyboard::P: //TODO: configure pause action
                    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevel));
                case sf::Keyboard::Left:
                    playerMovementSide = Side::Left;
                    break;
                case sf::Keyboard::Right:
                    playerMovementSide = Side::Right;
                    break;
            }
        }
        else if(e.type == sf::Event::KeyReleased){
            switch(e.key.code) {
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    playerMovementSide = Side::None;
            }
        }
    }
    if(playerMovementSide == Side::None) {
        m_gameData->engine->stopPlayer();
    }
    else {
        m_gameData->engine->movePlayer(playerMovementSide);
    }
}


void GamingState::update() {
    m_gameData->engine->process();
}

void GamingState::pause()
{
    cout << "TODO: GamingState::pause()" << endl;
}

void GamingState::resume()
{
    m_gameData->drawer->drawGameScene();
}
