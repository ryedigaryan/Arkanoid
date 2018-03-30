//
// Created by ruben on 3/25/2018.
//

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ArkanoidDrawer.h"

ArkanoidDrawer::ArkanoidDrawer() {
    m_window = new sf::RenderWindow(sf::VideoMode(320, 480), WindowTitle/*, sf::Style::Fullscreen*/);
}

sf::RenderWindow* ArkanoidDrawer::getDrawingWindow() {
    return m_window;
}

ArkanoidDrawer::~ArkanoidDrawer() {
    m_window->close();
    delete m_window;
}

void ArkanoidDrawer::clearScreen(sf::Color bgCol) {
    m_window->clear(bgCol);
}

void ArkanoidDrawer::drawMenu() {
    // configure background
    m_helperSahpe.setTexture(m_resourceManager.getTexture(MainMenuBackground));
    m_helperSahpe.setSize(sf::Vector2f(m_window->getSize()));
    m_helperSahpe.setPosition(0, 0);
    // configure text
    m_helperText.setString("Press Enter");
    m_helperText.setFont(m_resourceManager.getFont(MainMenuFont));
    m_helperText.setPosition((m_window->getSize().x - m_helperText.getLocalBounds().width) / 2, (m_window->getSize().y - m_helperText.getLocalBounds().height) / 2);
    // draw main menu stuff
    m_window->draw(m_helperSahpe);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::drawLevelEndInfo(bool hasWon) {
    sf::Sprite m_helperSahpe;
    // configure pop-up background
    cout << m_window->getSize().x << " " << m_window->getSize().y << endl;
    m_helperSahpe.setTexture(*m_resourceManager.getTexture(LevelInfoBackground));
    m_helperSahpe.setScale(sf::Vector2f(0.5, 0.5));
    cout << "s size: " << m_helperSahpe.getGlobalBounds().width << " " << m_helperSahpe.getGlobalBounds().height << endl;
    m_helperSahpe.setPosition((m_window->getSize().x - m_helperSahpe.getGlobalBounds().width) / 2, (m_window->getSize().y - m_helperSahpe.getGlobalBounds().height) / 2);
    cout << "s pos : " << m_helperSahpe.getPosition().x << " " << m_helperSahpe.getPosition().y << endl;
    // configure text
    m_helperText.setString(hasWon ? "Level Won" : "Level Lost");
    m_helperText.setFont(m_resourceManager.getFont(LevelInfoFont));
    cout << "t size: "<< m_helperText.getLocalBounds().width << " " << m_helperText.getCharacterSize() << endl;
    m_helperText.setPosition((m_helperSahpe.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2, m_helperSahpe.getGlobalBounds().height * 0.5f + m_helperText.getCharacterSize() + 10);
    cout << "t pos : " << m_helperText.getPosition().x << " " << m_helperText.getPosition().y << endl;
    // draw main menu stuff
    m_window->draw(m_helperSahpe);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}