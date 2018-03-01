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

void ArcanoidGameDrawer::drawObject(unsigned objectID, const Point& position, const Size& size, const string &texturePath, bool mustShow)
{
    auto* go_texture = new sf::Texture();
    go_texture->loadFromFile(texturePath);

    sf::RectangleShape obj(sf::Vector2f(size.width, size.height));
    obj.setPosition(position.x, position.y);
    obj.setSize(sf::Vector2f(size.width, size.height));
    obj.setTexture(go_texture);
    m_drawnObjects.push_back(obj);
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Size& size)
{
    auto it = std::next(m_drawnObjects.begin(), objectID);

    (*it).setSize(sf::Vector2f(size.width, size.height));

    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Point& position)
{
    auto it = std::next(m_drawnObjects.begin(), objectID);

    (*it).setPosition(sf::Vector2f(position.x, position.y));

    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::menu(bool mustShow) {
    if(mustShow) {
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Magenta);
        background.setPosition(0, 0);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize()));

        sf::Text playButton;
        sf::Font buttonFont;
        if(!buttonFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: menu(bool)" << endl;
        }
        playButton.setFont(buttonFont);
        playButton.setString("PLAY");
        playButton.setFillColor(sf::Color::Yellow);
        playButton.setStyle(sf::Text::Bold);
        playButton.setPosition((m_gameMainWindow->getSize().x - playButton.getCharacterSize() * 4) / 2,
                               (m_gameMainWindow->getSize().y - playButton.getCharacterSize() * 4) / 2);
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(playButton);
        m_gameMainWindow->display();
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_startPressed();
    }
    else {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::loading(bool mustShow) {
    if(mustShow) {
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Cyan);
        background.setPosition(0, 0);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize()));

        sf::Text loadingText;
        sf::Font textFont;
        if(!textFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: menu(bool)" << endl;
        }
        loadingText.setFont(textFont);
        loadingText.setString("Loading...");
        loadingText.setFillColor(sf::Color::White);
        loadingText.setPosition((m_gameMainWindow->getSize().x - loadingText.getCharacterSize() * 4) / 2,
                               (m_gameMainWindow->getSize().y - loadingText.getCharacterSize() * 4) / 2);
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(loadingText);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::levelStart(bool mustShow, int level, int progress) {
    if(mustShow) {
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Red);
        background.setPosition(10, 10);
        background.setSize(sf::Vector2f(10, 10));

        for (auto& m_drawnObject : m_drawnObjects) {
            m_gameMainWindow->draw(m_drawnObject);
        }
        m_gameMainWindow->draw(background);
        m_gameMainWindow->display();
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
    }
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    m_gameMainWindow->display();
    if(mustShow) {
        m_delegate->drawer_donePressed();
    }
}
