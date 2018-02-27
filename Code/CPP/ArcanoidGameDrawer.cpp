//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameDrawer.h"

ArcanoidGameDrawer::ArcanoidGameDrawer(const Size& windowSize)
{
    m_gameMainWindow = new sf::RenderWindow(sf::VideoMode(windowSize.width, windowSize.height), "Arcanoid");
    sf::Event event;
    m_gameMainWindow->pollEvent(event);
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::drawObject(unsigned objectID, const Point & position, const Size & size, int texture)
{
    string texturePath = "C:/Users/ryedigaryan/source/GitHub/Arcanoid/Arcanoid/Resources/Pictures/Bricks/";
    texturePath.append(std::to_string(texture));
    texturePath.append(".png");
    sf::Texture* go_texture = new sf::Texture();
    go_texture->loadFromFile(texturePath);

    sf::RectangleShape obj(sf::Vector2f(size.width, size.height));
    obj.setPosition(position.x, position.y);
    //obj.setFillColor(sf::Color(texture * 100, (texture + 1) * 100, (texture + 2) * 100));
    obj.setTexture(go_texture);
    m_drawnObjects.push_back(obj);
    for (list<sf::RectangleShape>::iterator it = m_drawnObjects.begin(); it != m_drawnObjects.end(); it++) {
        m_gameMainWindow->draw(*it);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Size& size)
{
    list<sf::RectangleShape>::iterator it = std::next(m_drawnObjects.begin(), objectID);

    (*it).setSize(sf::Vector2f(size.width, size.height));

    for (list<sf::RectangleShape>::iterator it = m_drawnObjects.begin(); it != m_drawnObjects.end(); it++) {
        m_gameMainWindow->draw(*it);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Point& position)
{
    list<sf::RectangleShape>::iterator it = std::next(m_drawnObjects.begin(), objectID);

    (*it).setPosition(sf::Vector2f(position.x, position.y));

    for (list<sf::RectangleShape>::iterator it = m_drawnObjects.begin(); it != m_drawnObjects.end(); it++) {
        m_gameMainWindow->draw(*it);
    }
    m_gameMainWindow->display();
}
