//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameDrawer.h"

ArcanoidGameDrawer::ArcanoidGameDrawer(sf::Color backgroundColor)
{
    cout << "drawer: Constructor" << endl;
//    m_gameMainWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Arcanoid");
    m_gameMainWindow = new sf::RenderWindow(sf::VideoMode(), "Arcanoid", sf::Style::Fullscreen);
    // setup helpers
    this->setBackgroundColor(backgroundColor);
    if(!m_helperFont.loadFromFile(DefaultFontPath)) fail("ArcanoidGameDrawer::ArcanoidGameDrawer(sf::Color backgroundColor)");
    m_helperText.setFont(m_helperFont);
    m_helperText.setCharacterSize(m_gameMainWindow->getSize().y / 10);
    m_helperText.setFillColor(TextColor);
    // setup popups' rect
    m_popUpRect.width = (unsigned)(m_gameMainWindow->getSize().x * PopUpSizeRatio);
    m_popUpRect.height = (unsigned)(m_gameMainWindow->getSize().y * PopUpSizeRatio);
    m_popUpRect.left = (m_gameMainWindow->getSize().x - m_popUpRect.width) / 2;
    m_popUpRect.top = (m_gameMainWindow->getSize().y - m_popUpRect.height) / 2;
}

void ArcanoidGameDrawer::drawMenu(bool mustShow /*= true*/)
{
    cout << "drawer: menu(" << (mustShow ? "show" : "hide") << ")" << endl;

    // set menu background to Magenta
    m_gameMainWindow->clear(sf::Color::Magenta); // TODO: magic color

    this->drawText("PLAY", TextPosition::Middle, NotShow);
    this->drawText("Press enter to continue", TextPosition::Bottom, mustShow);

    if (mustShow) { // user can interact with menu if he/she sees menu
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_startPressed();
    }
}

void ArcanoidGameDrawer::drawLoading(bool mustShow /*= true*/)
{
    cout << "drawer: loading(" << (mustShow ? "show" : "hide") << ")" << endl;

    // set loading background to Cyan
    m_gameMainWindow->clear(sf::Color::Cyan);

    this->drawText("Loading...", TextPosition::Middle);
}

void ArcanoidGameDrawer::drawAllGameObjects(bool mustShow) {
    for(auto gameObject : m_drawnObjects) {
        m_gameMainWindow->draw(*gameObject);
    }

    if(mustShow) {
        m_gameMainWindow->display();
    }
}

void ArcanoidGameDrawer::drawLevelStartInfo(int level, int progress, bool mustShow /*= true*/)
{
    cout << "drawer: levelStart(" << (mustShow ? "show" : "hide") << ")" << endl;
    // clear and draw all object on back display
    this->clearScreen(NotShow);
    this->drawAllGameObjects(NotShow);
    // draw level info rect
    m_helperRectShape.setFillColor(PopUpColor);
    m_helperRectShape.setSize(sf::Vector2f(m_popUpRect.width, m_popUpRect.height));
    m_helperRectShape.setPosition(m_popUpRect.left, m_popUpRect.top);
    m_gameMainWindow->draw(m_helperRectShape);
    // draw level info text
    this->drawText("Progress: " + std::to_string(progress), TextPosition::Top, NotShow);
    this->drawText("Level: " + std::to_string(level), TextPosition::Middle, NotShow);
    this->drawText("Space = pause/resume", TextPosition::Bottom, mustShow);

    if(mustShow) { // user will press any key if he/she sees level info
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
}

void ArcanoidGameDrawer::drawLevelEndInfo(int level, bool hasWon, bool mustShow /*= true*/)
{
    cout << "drawer: levelEnd(" << (mustShow ? "show" : "hide") << ")" << endl;
    // draw level info rect
    m_helperRectShape.setFillColor(PopUpColor);
    m_helperRectShape.setSize(PopUpSize);
    m_helperRectShape.setPosition((m_gameMainWindow->getSize().x - m_helperRectShape.getSize().x) / 2,  (m_gameMainWindow->getSize().y - m_helperRectShape.getSize().y) / 2);
    m_gameMainWindow->draw(m_helperRectShape);
    // draw level info text
    this->drawText(string("Level ") + std::to_string(level) + (hasWon ? " WON" : " LOST"), TextPosition::Middle);

    if(mustShow) { // user will press any key if he/she sees level info
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
}

void ArcanoidGameDrawer::drawGameWon(bool mustShow /*= true*/)
{
    cout << "drawer: gameWon(" << (mustShow ? "show" : "hide") << ")" << endl;
    // draw level info rect
    m_helperRectShape.setFillColor(PopUpColor);
    m_helperRectShape.setSize(PopUpSize);
    m_helperRectShape.setPosition((m_gameMainWindow->getSize().x - m_helperRectShape.getSize().x) / 2,  (m_gameMainWindow->getSize().y - m_helperRectShape.getSize().y) / 2);
    m_gameMainWindow->draw(m_helperRectShape);
    // draw level info text
    this->drawText("CONGRATULATIONS", TextPosition::Middle);

    if(mustShow) { // user will press any key if he/she sees level info
        // wait for Enter key to be pressed
        while (m_gameMainWindow->isOpen()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
                break;
            }
        }
        m_delegate->drawer_donePressed();
    }
}


void ArcanoidGameDrawer::drawText(const string &text, TextPosition position, bool mustShow /*= true*/) {
    int charSizeDelta = (int)(abs(position) * (NonMiddleCharacterSizeRatio * m_helperText.getCharacterSize()));

    // set string and change character size to calculate drawable text's bounds correctly
    m_helperText.setString(text);
    m_helperText.setCharacterSize(m_helperText.getCharacterSize() - charSizeDelta);

    // calculate drawable text's position such that it appears in the middle of x axis
    sf::FloatRect textRect = m_helperText.getLocalBounds();
    textRect.left = (m_gameMainWindow->getSize().x - textRect.width) / 2;
    textRect.top = (m_gameMainWindow->getSize().y - textRect.height) / 2 + (position * (textRect.height + charSizeDelta + TextOffset));
    // set calculated values
    m_helperText.setPosition(textRect.left, textRect.top);

    // draw and display the text
    m_gameMainWindow->draw(m_helperText);
    if(mustShow) {
        m_gameMainWindow->display();
    }
    // return helper text's initial character size
    m_helperText.setCharacterSize(m_helperText.getCharacterSize() + charSizeDelta);

}

void ArcanoidGameDrawer::clearScreen(bool mustShow /*= true*/)
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
    m_helperRectShape.setFillColor(m_backgroundColor);
}


// object drawing/redrawing functions

void ArcanoidGameDrawer::drawObject(unsigned objectID, const sf::Vector2f& position, const sf::Vector2f& size, const string &texturePath, bool mustShow /* = true*/, bool mustRepeatTexture /* = false*/)
{
    cout << "drawer: drawObject" << endl;
    // load texture
    auto texture = new sf::Texture();
    if(!texture->loadFromFile(texturePath)) {
        cout << "FATAL ERROR class - ArcanoidGameDrawer, function - drawObject(unsigned, Point, Size, string, bool)" << endl;
        cout << "cant load from file: " << texturePath << endl;
    }

    // create drawable object and set texture
    auto createdObject = new sf::RectangleShape(size);
    createdObject->setPosition(position);
    createdObject->setTexture(texture);
    if(mustRepeatTexture) {
        texture->setRepeated(mustRepeatTexture);
        createdObject->setTextureRect(sf::IntRect(createdObject->getPosition().x, createdObject->getPosition().y, createdObject->getSize().x, createdObject->getSize().y));
    }

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
    m_helperRectShape.setPosition(resizableObject->getPosition());
    m_helperRectShape.setSize(resizableObject->getSize());

    // resizing the object and drawing in a new place
    resizableObject->setSize(size);
    m_gameMainWindow->draw(*resizableObject);

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRectShape); // no need to display
}

void ArcanoidGameDrawer::moveObject(unsigned objectID, const sf::Vector2f &position)
{
    auto movableObject = m_drawnObjects[objectID];

    // place helper rect to the current place of movableObject, to clear the space it was placed
    m_helperRectShape.setPosition(movableObject->getPosition());
    m_helperRectShape.setSize(movableObject->getSize());

    // moving the object and drawing in a new place
    movableObject->setPosition(position);
    m_gameMainWindow->draw(*movableObject);

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRectShape); // no need to display
}

void ArcanoidGameDrawer::deleteObject(unsigned objectID, bool mustShow /*= true*/)
{
    auto deletableObject = m_drawnObjects[objectID];

    // place helper rect to the current place of movableObject, to clear the space it was placed
    m_helperRectShape.setPosition(deletableObject->getPosition());
    m_helperRectShape.setSize(deletableObject->getSize());

    delete deletableObject;
    m_drawnObjects[objectID] = nullptr;

    // display changes
    m_gameMainWindow->display();

    // clear the space movableObject was
    m_gameMainWindow->draw(m_helperRectShape); // no need to display
}

void ArcanoidGameDrawer::hideObject(unsigned objectID, bool mustShow)
{
    auto hideableObject = m_drawnObjects[objectID];

    // m_helperRectShape already has background's color
    m_helperRectShape.setPosition(hideableObject->getPosition());
    m_helperRectShape.setSize(hideableObject->getScale());
    m_gameMainWindow->draw(m_helperRectShape);

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
