//
// Created by ruben on 3/25/2018.
//

#include "GameStates/LevelEndState.h"

LevelEndState::LevelEndState(GameData* gameData, const unsigned& level, const bool& hasWon, const unsigned& lastLevel)
        : StaticImageState(gameData, sf::Keyboard::Return), m_level(level), m_hasWon(hasWon), m_lastLevel(lastLevel)
{

}

void LevelEndState::init() {
    StaticImageState::init();
    if(m_level == m_lastLevel && m_hasWon) {
        m_gameData->stateMachine->pushState(new EntireGameWonState(m_gameData), Replace);
    }
}

void LevelEndState::draw()
{
    if(m_needsRedraw) {
        m_gameData->drawer->drawLevelEndPopUp(m_level, m_hasWon);
        m_needsRedraw = false;
    }
}
