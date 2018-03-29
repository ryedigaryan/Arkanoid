//
// Created by ruben on 3/25/2018.
//

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ArkanoidDrawer.h"

ArkanoidDrawer::ArkanoidDrawer() {
    m_window = new sf::RenderWindow(sf::VideoMode(500, 500), WindowTitle/*, sf::Style::Fullscreen*/);
}

sf::RenderWindow* ArkanoidDrawer::getDrawingWindow() {
    return m_window;
}

ArkanoidDrawer::~ArkanoidDrawer() {
    delete m_window;
}

void ArkanoidDrawer::drawMenu() {
    m_helperSahpe.setTexture(&m_resourceManager.getTexture(MainMenuBackground));
    m_helperSahpe.setSize(sf::Vector2f(m_window->getSize()));
    m_window->draw(m_helperSahpe);
    m_window->display();
}
