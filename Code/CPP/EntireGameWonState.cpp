//
// Created by ryedigaryan on 4/2/2018.
//

#include "GameStates/EntireGameWonState.h"

EntireGameWonState::EntireGameWonState(GameData* gameData) : StaticImageState(gameData, sf::Keyboard::Return)
{

}

void EntireGameWonState::draw()
{
    if(m_needsRedraw) {
        m_gameData->drawer->drawCongratulations();
        m_needsRedraw = false;
    }
}
