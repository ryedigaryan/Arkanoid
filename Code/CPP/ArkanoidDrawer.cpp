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
    sf::Text menu;
    menu.setString("MAIN MENU");
    sf::Font font;
    if(!font.loadFromFile("Resources/Fonts/RAVIE.ttf")) {
        cout << "EEEEEEEEEEEEEEERRRRRRRRRRRRRRROOOOOOOOOOOOOOOOORRRRRRRRRRRRRRR" << endl;
        exit(1);
    }
    menu.setFont(font);
    menu.setCharacterSize(50);
    m_window->draw(menu);
    m_window->display();
}
