//
// Created by ruben on 3/25/2018.
//

#include <GameStates/PausedState.h>

PausedState::PausedState(GameData *gameData, StateDelegate *dlgate) : State(gameData, dlgate)
{
    m_needsRedraw = true;
}

void PausedState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_delegate->pushNextState();
                    return;
            }
        }
    }
}

void PausedState::update()
{
    if(m_needsRedraw) {
        m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Blue);
        m_gameData->drawer->getDrawingWindow()->display();
        m_needsRedraw = false;
    }
}

void PausedState::pause()
{
    m_needsRedraw = false;
}

void PausedState::resume()
{
    m_needsRedraw = true;
}
