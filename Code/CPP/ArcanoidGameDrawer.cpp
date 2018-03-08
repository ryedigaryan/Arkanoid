//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameDrawer.h"

ArcanoidGameDrawer::ArcanoidGameDrawer(sf::Color backgroundColor)
{
    cout << "drawer: Constructor" << endl;
    m_gameMainWindow = new sf::RenderWindow(sf::VideoMode(600, 800), "Arcanoid"/*, sf::Style::Fullscreen*/);
    this->setBackgroundColor(backgroundColor);
    sf::Font defaultFont;
    if(!defaultFont.loadFromFile(DefaultFontpath)) {
        cout << "FATAL ERROR in ArcanoidGameDrawer constructor" << endl;
        cout << "cant load from file: " << DefaultFontpath << endl;
    }
    m_helperText.setFont(defaultFont);
    m_helperText.setCharacterSize(m_gameMainWindow->getSize().y / 10);
//TODO:    m_helperRect.setFillColor(m_backgroundColor); ----> understand sf::Color::Transparent's behaviour
}

void ArcanoidGameDrawer::drawMenu(bool mustShow /*= Show*/)
{
    cout << "drawer: menu(" << (mustShow ? "show" : "hide") << ")" << endl;

    // set menu background to Magenta
    m_gameMainWindow->clear(sf::Color::Magenta); // TODO: magic color

    m_gameMainWindow->display();
    m_gameMainWindow->display();
    m_gameMainWindow->display();
    m_gameMainWindow->display();
    m_gameMainWindow->pollEvent(*(new sf::Event()));
    this->drawTextAtMiddle("PLAY", mustShow);

    m_gameMainWindow->display();
    m_gameMainWindow->display();

    // wait for Enter key to be pressed
    while (m_gameMainWindow->isOpen()) {
        sf::Event e;
        m_gameMainWindow->pollEvent(e);
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
    }
    m_delegate->drawer_startPressed();
}

void ArcanoidGameDrawer::drawLoading(bool mustShow /*= true*/)
{
    cout << "drawer: loading(" << (mustShow ? "show" : "hide") << ")" << endl;

    // set loading background to Cyan
    m_gameMainWindow->clear(sf::Color::Cyan);

    this->drawTextAtMiddle("Loading...");
    m_gameMainWindow->display();
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::drawLevelStart(int level, int progress, bool mustShow /*= Show*/)
{
    cout << "drawer: levelStart(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(*m_drawnObject);
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

void ArcanoidGameDrawer::drawLevelEnd(bool hasWon, bool mustShow /*= Show*/)
{
    cout << "drawer: levelEnd(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(*m_drawnObject);
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

void ArcanoidGameDrawer::drawGameWon(bool mustShow /*= Show*/)
{
    cout << "drawer: gameWon(" << (mustShow ? "show" : "hide") << ")" << endl;
    m_gameMainWindow->clear(Gray);
    // draw all game objects in background
    for (auto& m_drawnObject : m_drawnObjects) {
        m_gameMainWindow->draw(*m_drawnObject);
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


void ArcanoidGameDrawer::drawTextAtMiddle(const string &text, bool mustShow /*= true*/) {
    m_helperText.setString(text);
    m_helperText.setFillColor(sf::Color::White);
    m_helperText.setPosition((m_gameMainWindow->getSize().x - m_helperText.getCharacterSize() * text.size()) / 2,
                             (m_gameMainWindow->getSize().y - m_helperText.getCharacterSize()) / 2);

    m_gameMainWindow->draw(m_helperText);
    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::clearScreen(bool mustShow /*= Show*/)
{
    m_gameMainWindow->clear(m_backgroundColor);

    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::showDrawnStuff()
{
    m_gameMainWindow->display();
}

void ArcanoidGameDrawer::setBackgroundColor(sf::Color bgColor) {
    m_backgroundColor = bgColor;
    m_helperRect.setFillColor(m_backgroundColor);
}


// object drawing/redrawing functions

void ArcanoidGameDrawer::drawObject(unsigned objectID, const sf::Vector2f& position, const sf::Vector2f& size, const string &texturePath, bool mustShow)
{
    cout << "drawer: drawObject" << endl;
    // load texture
    auto texture = new sf::Texture();
    if(!texture->loadFromFile(texturePath)) {
        cout << "FATAL ERROR class - ArcanoidGameDrawer, function - drawObject(unsigned, Point, Size, string, bool)" << endl;
        cout << "cant load from file: " << texturePath << endl;
    }

    // create drawable object
    auto createdObject = new sf::RectangleShape(size);
    createdObject->setPosition(position);
    createdObject->setTexture(texture);

    // add created object to all already objects array
    m_drawnObjects.push_back(createdObject);

    // draw game on window
    m_gameMainWindow->draw(*createdObject);

    // display, if must show changes
    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::resizeObject(unsigned objectID, const sf::Vector2f& size)
{
    auto resizableObject = m_drawnObjects[objectID];

    // place helper rect to the current place of movableObject, to clear the space it was placed
    m_helperRect.setPosition(resizableObject->getPosition());
    m_helperRect.setSize(resizableObject->getSize());

    // resizing the object and drawing in a new place
    resizableObject->setSize(size);
    m_gameMainWindow->draw(*resizableObject);

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRect); // no need to display
}

void ArcanoidGameDrawer::moveObject(unsigned objectID, const sf::Vector2f &position)
{
    auto movableObject = m_drawnObjects[objectID];

    // place helper rect to the current place of movableObject, to clear the space it was placed
    m_helperRect.setPosition(movableObject->getPosition());
    m_helperRect.setSize(movableObject->getSize());

    // moving the object and drawing in a new place
    movableObject->setPosition(position);
    m_gameMainWindow->draw(*movableObject);

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRect); // no need to display
}

void ArcanoidGameDrawer::deleteObject(unsigned objectID, bool mustShow /*= Show*/)
{
    auto deletableObject = m_drawnObjects[objectID];

    // place helper rect to the current place of movableObject, to clear the space it was placed
    m_helperRect.setPosition(deletableObject->getPosition());
    m_helperRect.setSize(deletableObject->getSize());

    delete deletableObject;
    m_drawnObjects[objectID] = nullptr;

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRect); // no need to display
}

void ArcanoidGameDrawer::hideObject(unsigned objectID, bool mustShow)
{
    auto hideableObject = m_drawnObjects[objectID];

    // m_helperRect already has background's color
    m_helperRect.setPosition(hideableObject->getPosition());
    m_helperRect.setSize(hideableObject->getScale());
    m_gameMainWindow->draw(m_helperRect);

    if(mustShow) {
        m_gameMainWindow->display();
    }
}

sf::RenderWindow* ArcanoidGameDrawer::getMainWindow()
{
    return m_gameMainWindow;
}

void ArcanoidGameDrawer::setDelegate(ArcanoidGameDrawerDelegate *dlgate)
{
    m_delegate = dlgate;
}
