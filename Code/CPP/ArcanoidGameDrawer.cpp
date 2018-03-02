//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameDrawer.h"

ArcanoidGameDrawer::ArcanoidGameDrawer(const Size& windowSize)
{
    cout << "drawer: Constructor" << endl;
    m_gameMainWindow = new sf::RenderWindow(sf::VideoMode(windowSize.width, windowSize.height), "Arcanoid");
    m_gameMainWindow->clear(Gray);
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::drawObject(unsigned objectID, const Point& position, const Size& size, const string &texturePath, bool mustShow)
{
    cout << "drawer: drawObject" << endl;
    // load texture
    auto* go_texture = new sf::Texture();
    if(!go_texture->loadFromFile(texturePath)) {
        cout << "FATAL ERROR class - ArcanoidGameDrawer, function - drawObject(unsigned, Point, Size, string, bool)" << endl;
        cout << "cant load from file: " << texturePath << endl;
    }

    // create drawable object
    sf::RectangleShape obj;
    obj.setPosition(position.x, position.y);
    obj.setSize(sf::Vector2f(size.width, size.height));
    obj.setTexture(go_texture);
    // add created object to all objects
    m_drawnObjects.push_back(obj);
    // draw game object
    m_gameMainWindow->draw(obj);
    // display, if must show changes
    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Size& size)
{
    cout << "drawer: redrawObject(Size)" << endl;
    // get the object by ID
    auto it = std::next(m_drawnObjects.begin(), objectID);
    // resize found object
    (*it).setSize(sf::Vector2f(size.width, size.height));

    // draw all game objects
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::redrawObject(unsigned objectID, const Point& position)
{
    cout << "drawer: redrawObject(Point)" << endl;
    // get the object by ID
    auto it = std::next(m_drawnObjects.begin(), objectID);
    // change position of found object
    (*it).setPosition(sf::Vector2f(position.x, position.y));

    // draw all game objects
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::menu(bool mustShow)
{
    cout << "drawer: menu(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    if(mustShow) {
        // create background
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Magenta);
        background.setPosition(0, 0);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize()));

        // create PLAY text
        sf::Text playButton;
        sf::Font buttonFont;
        if(!buttonFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: menu(bool)" << endl;
            cout << "cant load from file: " << "Resources/Fonts/RAVIE.TTF" << endl;
        }
        playButton.setFont(buttonFont);
        playButton.setString("PLAY");
        playButton.setFillColor(sf::Color::Yellow);
        playButton.setStyle(sf::Text::Bold);
        playButton.setPosition((m_gameMainWindow->getSize().x - playButton.getCharacterSize() * 4) / 2,
                               (m_gameMainWindow->getSize().y - playButton.getCharacterSize() * 4) / 2);
        // draw background and PLAY text
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(playButton);
        m_gameMainWindow->display();
        // wait for Enter key to be pressed
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

void ArcanoidGameDrawer::loading(bool mustShow)
{
    cout << "drawer: loading(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    if(mustShow) {
        // create background
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Cyan);
        background.setPosition(0, 0);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize()));

        // create Loading... text
        sf::Text loadingText;
        sf::Font textFont;
        if(!textFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: menu(bool)" << endl;
            cout << "cant load from file: " << "Resources/Fonts/RAVIE.TTF" << endl;
        }
        loadingText.setFont(textFont);
        loadingText.setString("Loading...");
        loadingText.setFillColor(sf::Color::White);
        loadingText.setPosition((m_gameMainWindow->getSize().x - loadingText.getCharacterSize() * 8) / 2,
                               (m_gameMainWindow->getSize().y - loadingText.getCharacterSize() * 8) / 2);
        // draw background and text
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(loadingText);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::levelStart(bool mustShow, int level, int progress)
{
    cout << "drawer: levelStart(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    if(mustShow) {
        // create a "dialog box"
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Red);
        background.setPosition(10, m_gameMainWindow->getSize().y / 2 - 15);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize().x - 20, 33));
        sf::Text levelInfo;
        sf::Font textFont;
        if(!textFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: levelStart(bool, int, int)" << endl;
            cout << "cant load from file: " << "Resources/Fonts/RAVIE.TTF" << endl;
        }
        levelInfo.setFont(textFont);
        levelInfo.setString("Lvl: " + std::to_string(level) + ", pr: " + std::to_string(progress));
        levelInfo.setFillColor(sf::Color::White);
        levelInfo.setPosition((m_gameMainWindow->getSize().x - levelInfo.getCharacterSize() * 8) / 2,
                                (m_gameMainWindow->getSize().y - levelInfo.getCharacterSize()) / 2);

        // draw "dialog box" in front
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(levelInfo);
        m_gameMainWindow->display();
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
    else {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::levelEnd(bool mustShow, bool hasWon) {
    cout << "drawer: levelEnd(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    if(mustShow) {
        // create a "dialog box"
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Red);
        background.setPosition(10, m_gameMainWindow->getSize().y / 2 - 15);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize().x - 20, 33));
        sf::Text levelInfo;
        sf::Font textFont;
        if(!textFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: levelStart(bool, int, int)" << endl;
            cout << "cant load from file: " << "Resources/Fonts/RAVIE.TTF" << endl;
        }
        levelInfo.setFont(textFont);
        levelInfo.setString(string("Lvl ") + (hasWon ? "WON" : "LOST"));
        levelInfo.setFillColor(sf::Color::White);
        levelInfo.setPosition((m_gameMainWindow->getSize().x - levelInfo.getCharacterSize() * 8) / 2,
                              (m_gameMainWindow->getSize().y - levelInfo.getCharacterSize()) / 2);

        // draw "dialog box" in front
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(levelInfo);
        m_gameMainWindow->display();
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
    else {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::gameWon(bool mustShow) {
    cout << "drawer: gameWon(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObject);
    }
    if(mustShow) {
        // create a "dialog box"
        sf::RectangleShape background(sf::Vector2f(m_gameMainWindow->getSize()));
        background.setFillColor(sf::Color::Red);
        background.setPosition(10, m_gameMainWindow->getSize().y / 2 - 15);
        background.setSize(sf::Vector2f(m_gameMainWindow->getSize().x - 20, 33));
        sf::Text levelInfo;
        sf::Font textFont;
        if(!textFont.loadFromFile("Resources/Fonts/RAVIE.TTF")) {
            cout << "FATAL ERROR Class: ArcanoidGameDrawer, function: levelStart(bool, int, int)" << endl;
            cout << "cant load from file: " << "Resources/Fonts/RAVIE.TTF" << endl;
        }
        levelInfo.setFont(textFont);
        levelInfo.setString("congrats");
        levelInfo.setFillColor(sf::Color::White);
        levelInfo.setPosition((m_gameMainWindow->getSize().x - levelInfo.getCharacterSize() * 8) / 2,
                              (m_gameMainWindow->getSize().y - levelInfo.getCharacterSize()) / 2);

        // draw "dialog box" in front
        m_gameMainWindow->draw(background);
        m_gameMainWindow->draw(levelInfo);
        m_gameMainWindow->display();
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
    else {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::moveObject(unsigned objectID, const Point &position) {
    m_gameMainWindow->clear(Gray);
    m_drawnObjects[objectID].setPosition(position.x, position.y);
    for(auto& m_drawnObj : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObj);
    }
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::deleteObject(unsigned objectID) {
    m_drawnObjects[objectID].setFillColor(sf::Color(0, 0, 0, 0));
    for(auto& m_drawnObj : m_drawnObjects) {
        m_gameMainWindow->draw(m_drawnObj);
    }
    m_gameMainWindow->display();

}
