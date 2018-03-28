//
// Created by ruben on 3/25/2018.
//

#include <GameStates/GamingState.h>

void GamingState::handleInput() {
    Side playerMovementSide = Side::None;
    sf::Event e;
    while(m_gameData->drawer->getDrawingWindow()->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    m_delegate->pushNextState();
                    return;
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
    m_gameData->drawer->getDrawingWindow()->clear(sf::Color::Red);
    m_gameData->drawer->getDrawingWindow()->display();
}

void GamingState::pause()
{
    cout << "TODO: GamingState::pause()" << endl;
}

void GamingState::resume()
{
    cout << "TODO: GamingState::resume()" << endl;
}
