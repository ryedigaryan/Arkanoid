//
// Created by ruben on 3/25/2018.
//

#include "GameStates/MainMenuState.h"

MainMenuState::MainMenuState(GameData* gameData)
        : StaticImageState(gameData, sf::Keyboard::Return), m_drawer(gameData->drawer->getDrawingWindow(), gameData->resourceManager->getTexture(StateTypeMainMenu), MainMenuButtonsCount, UnMarkedButtonColor, MarkedButtonColor)
{
    auto& mmFont = m_gameData->resourceManager->getFont(StateTypeMainMenu);
    m_drawer.addButton("New Game", mmFont)
            .addButton("Continue", mmFont)
            .addButton("About", mmFont);
}

void MainMenuState::handleInput()
{
    sf::RenderWindow* mainWindow = m_gameData->drawer->getDrawingWindow();
    sf::Event e;
    while(mainWindow->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case sf::Keyboard::Return:
                    switch(m_drawer.currMarkedButton()) {
                        case MainMenuButtonNewGame:
                            m_gameData->stateMachine->pushState(new GamingState(m_gameData, FirstLevelNumber, LastLevelNumber));
                            return;
                        case MainMenuButtonContinue:
                            m_gameData->stateMachine->pushState(new GamingState(m_gameData, m_gameData->lostLevel, LastLevelNumber));
                            return;
                        case MainMenuButtonAbout:
                            //TODO: show about...
                            return;
                    }
                    return;
                case sf::Keyboard::Escape:
                    mainWindow->close();
                    return;
                case sf::Keyboard::Down:
                    m_drawer.markNextButton();
                    return;
                case sf::Keyboard::Up:
                    m_drawer.markPrevButton();
                    return;
            }
//            if(e.key.code == m_popKey) {
//                m_gameData->stateMachine->pushState(new GamingState(m_gameData, FirstLevelNumber, LastLevelNumber));
//                return;
//            } else if(e.key.code == sf::Keyboard::Escape) {
//                mainWindow->close();
//                return;
//            }
        }
        else if(e.type == sf::Event::Closed) {
            delete m_gameData->drawer;
            m_gameData->drawer = nullptr;
        }
    }
}

void MainMenuState::draw()
{
    m_drawer.draw();
    m_drawer.display();
//    if(m_needsRedraw) {
//        m_gameData->drawer->clearScreen();
//        m_gameData->drawer->drawMenu();
//        m_needsRedraw = false;
//    }
}