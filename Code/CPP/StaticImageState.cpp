//
// Created by ryedigaryan on 4/2/2018.
//

#include "GameStates/StaticImageState.h"

StaticImageState::StaticImageState(GameData* gameData, sf::Keyboard::Key popKey) : State(gameData), m_popKey(popKey)
{

}

void StaticImageState::init() {
    m_needsRedraw = true;
}

void StaticImageState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            if(e.key.code == m_popKey) {
                m_gameData->stateMachine->popActiveState(); // pops himself
                return;
            } else if(e.key.code == sf::Keyboard::Escape) {
                mainWindow->close();
                return;
            }
        }
        else if(e.type == sf::Event::Closed) {
            delete m_gameData->drawer;
            m_gameData->drawer = nullptr;
        }
    }
}

void StaticImageState::pause()
{
    m_needsRedraw = false;
}

void StaticImageState::resume()
{
    m_needsRedraw = true;
}