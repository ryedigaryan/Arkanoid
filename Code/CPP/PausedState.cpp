//
// Created by ruben on 3/25/2018.
//

#include "GameStates/PausedState.h"
#include "GameStates/GamingState.h"
#include "StateMachine.h"

PausedState::PausedState(GameData* gameData, const unsigned& level, const int& progress) : StaticImageState(gameData, PauseButton), m_level(level), m_progress(progress)
{
    cout << "State: Paused" << endl;
}

void PausedState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->drawLevelStartInfo(m_level, m_progress);
        m_needsRedraw = false;
    }
}