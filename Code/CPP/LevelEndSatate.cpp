//
// Created by ruben on 3/25/2018.
//

#include "GameStates/LevelEndState.h"

LevelEndState::LevelEndState(GameData* gameData, const unsigned& level, const bool& hasWon) : StaticImageState(gameData, sf::Keyboard::Return), m_level(level), m_hasWon(hasWon)
{
    cout << "State: LevelEnd" << endl;
}

void LevelEndState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->clearScreen(sf::Color::Red);
        m_gameData->drawer->drawLevelEndInfo(m_level, m_hasWon);
        m_gameData->drawer->clearScreen(sf::Color::Red);
        m_gameData->drawer->drawLevelEndInfo(m_level, m_hasWon);
        m_needsRedraw = false;
    }
}