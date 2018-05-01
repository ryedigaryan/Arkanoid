//
// Created by ruben on 3/25/2018.
//

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Definitions/DrawerDefinitions.h"
#include "ArkanoidDrawer.h"

ArkanoidDrawer::ArkanoidDrawer()
{
    m_window = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], WindowTitle, sf::Style::Fullscreen);
//    m_window = new sf::RenderWindow(sf::VideoMode(1920, 1000), WindowTitle, sf::Style::Default);
}

ArkanoidDrawer::~ArkanoidDrawer()
{
    m_window->close();
    delete m_window;
}

sf::RenderWindow* ArkanoidDrawer::getDrawingWindow()
{
    return m_window;
}

sf::Vector2f ArkanoidDrawer::getLevelSize(bool considerBorders /* = false */) {
    if(considerBorders) {
        return sf::Vector2f(m_backgroundRect.width + 2 * m_borderWidth, m_backgroundRect.height);
    }
    return sf::Vector2f(m_backgroundRect.width, m_backgroundRect.height);
}

void ArkanoidDrawer::clearScreen(sf::Color bgCol)
{
    m_window->clear(bgCol);
}

void ArkanoidDrawer::displayChanges()
{
    m_window->display();
    for(unsigned i = 0; i < m_drawnObjects.size(); i++) {
        if(m_drawnObjects[i]->previousArea != nullptr) {
            moveObject(i, sf::Vector2f(m_drawnObjects[i]->object->getPosition().x - m_backgroundRect.left, m_drawnObjects[i]->object->getPosition().y - m_backgroundRect.top));
            m_drawnObjects[i]->previousArea = nullptr;
        }
    }
}

void ArkanoidDrawer::drawMenu()
{
    static sf::RectangleShape helperShape(sf::Vector2f(m_window->getSize()));
    helperShape.setTexture(m_resourceManager.getTexture(StateTypeMainMenu));
    helperShape.setPosition(0, 0);
    // configure text
    m_helperText.setString("Press Enter");
    m_helperText.setFont(m_resourceManager.getFont(StateTypeMainMenu));
    m_helperText.setPosition((m_window->getSize().x - m_helperText.getLocalBounds().width) / 2, (m_window->getSize().y - m_helperText.getLocalBounds().height) / 2);
    // draw main menu stuff
    m_window->draw(helperShape);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::drawLevelStartPopUp(const unsigned &level, const int &progress)
{
    static sf::Sprite helperSprite;
    // draw pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(StateTypePaused));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    m_window->draw(helperSprite);
    // draw text: Level: xxx Won/Loast
    m_helperText.setString(std::string("Level: ") + std::to_string(level));
    m_helperText.setFont(m_resourceManager.getFont(StateTypePaused));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    m_window->draw(m_helperText);
    // draw text: Progress: xxx
    m_helperText.setString(std::string("Progress: ") + std::to_string(progress));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize()*2 + 10 + LineSpacing);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::drawGameScene(const int& progress)
{
    drawBackground(m_resourceManager.getTexture(ObjectTypeLevel), SideDown);
    drawBorder(SideLeft);
    drawBorder(SideRight);
    drawProgressBar(progress);
    drawGameScenePane(SideLeft);
    drawGameScenePane(SideRight);
    for (auto objInfo : m_drawnObjects) {
        m_window->draw(*objInfo->object);
    }
    m_window->display();
}

void ArkanoidDrawer::drawLevelEndPopUp(const unsigned &level, const bool &hasWon)
{
    static sf::Sprite helperSprite;
    // configure pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(StateTypeLevelEnd));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    // configure text
    std::string lvl("Level ");
    lvl = lvl + std::to_string(level);
    m_helperText.setString(lvl + (hasWon ? " Won" : " Lost"));
    m_helperText.setFont(m_resourceManager.getFont(StateTypeLevelEnd));
    m_helperText.setFillColor(sf::Color::Black);
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    // draw main menu stuff
    m_window->draw(helperSprite);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
    m_helperText.setFillColor(sf::Color::White);
    for(auto obj : m_drawnObjects) {
        delete obj;
    }
    m_drawnObjects.clear();
}

void ArkanoidDrawer::drawCongratulations()
{
    static sf::Sprite helperSprite;
    // draw pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(StateTypeEntireGameWon));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    m_window->draw(helperSprite);
    // draw text: Congrats!!!
    m_helperText.setFillColor(sf::Color::Red);
    m_helperText.setString("  Congrats!!!\nYou have won\n  the game");
    m_helperText.setFont(m_resourceManager.getFont(StateTypeEntireGameWon));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    m_window->draw(m_helperText);
    m_helperText.setFillColor(sf::Color::White);
    // and display all drawn stuff
    m_window->display();
    for(auto obj : m_drawnObjects) {
        delete obj;
    }
    m_drawnObjects.clear();
}

unsigned ArkanoidDrawer::drawObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture const * const texture, bool mustDisplay /* = false */)
{
    // create object which must be drawn
    auto object = new sf::RectangleShape(size);
    object->setPosition(position.x + m_backgroundRect.left, position.y + m_backgroundRect.top);
    object->setTexture(texture);
    // draw and add it to already drawn objects array
    m_window->draw(*object);
    m_drawnObjects.push_back(new ObjectInfo(object));
    // display changes if must
    if(mustDisplay) {
        m_window->display();
    }
    // return newly created object's id, which is actually it's position in m_drawnObjects array
    return m_drawnObjects.size() - 1;
}

void ArkanoidDrawer::moveObject(const unsigned& id, const sf::Vector2f& newPosition)
{
    ObjectInfo* movable = m_drawnObjects[id];
    // clean up scene (only the area which necessarily)
    if(movable->previousArea == nullptr) { // for this statement previousArea declared as pointer, and initializes as nullptr
        movable->previousArea = new sf::FloatRect(movable->object->getGlobalBounds());
    }
    cleanArea(*(movable->previousArea), m_resourceManager.getTexture(ObjectTypeLevel));
    // save current area as previous for further moving
    movable->previousArea->top = movable->object->getGlobalBounds().top;
    movable->previousArea->left = movable->object->getGlobalBounds().left;
    movable->previousArea->width = movable->object->getGlobalBounds().width;
    movable->previousArea->height = movable->object->getGlobalBounds().height;
    // move the object and draw in new position
    movable->object->move(newPosition.x + m_backgroundRect.left - movable->object->getPosition().x, newPosition.y + m_backgroundRect.top - movable->object->getPosition().y);
    m_window->draw(*movable->object);
}

void ArkanoidDrawer::cleanArea(const sf::FloatRect& area, const sf::Texture* background)
{
    static sf::RectangleShape helperShape;
    helperShape.setTexture(background);
    helperShape.setTextureRect(sf::IntRect(area.left - m_backgroundRect.left, area.top - m_backgroundRect.top, area.width, area.height));
    helperShape.setPosition(area.left, area.top);
    helperShape.setSize(sf::Vector2f(area.width, area.height));
    m_window->draw(helperShape);
}

void ArkanoidDrawer::drawBackground(const sf::Texture *bgTexture, int corner)
{
    sf::RectangleShape helperShape;
    helperShape.setSize(sf::Vector2f(bgTexture->getSize()));
    helperShape.setTexture(bgTexture);
    float xPos = (m_window->getSize().x - bgTexture->getSize().x) / 2;
    float yPos = (m_window->getSize().y - bgTexture->getSize().y) / 2;;
    if((corner & SideLeft) == SideLeft) {
        xPos = 0;
    }
    if((corner & SideRight) == SideRight) {
        xPos = m_window->getSize().x - bgTexture->getSize().x;
    }
    if((corner & SideUp) == SideUp) {
        yPos = 0;
    }
    if((corner & SideDown) == SideDown) {
        yPos = m_window->getSize().y - bgTexture->getSize().y;
    }
    helperShape.setPosition(xPos, yPos);
    m_backgroundRect = helperShape.getGlobalBounds();
    m_window->draw(helperShape);
}

void ArkanoidDrawer::drawBorder(Side borderSide) {
    sf::RectangleShape border;
    const sf::Texture* texture;
    switch(borderSide) {
        case SideLeft:
            texture = m_resourceManager.getTexture(ObjectTypeBorder, LeftBorder);
            border.setTexture(texture);
            border.setSize(sf::Vector2f(texture->getSize()));
            border.setPosition(m_backgroundRect.left - border.getSize().x, m_backgroundRect.top);
            m_window->draw(border);
            m_borderWidth = border.getSize().x;
            return;
        case SideRight:
            texture = m_resourceManager.getTexture(ObjectTypeBorder, RightBorder);
            border.setTexture(texture);
            border.setSize(sf::Vector2f(texture->getSize()));
            border.setPosition(m_backgroundRect.left + m_backgroundRect.width, m_backgroundRect.top);
            m_window->draw(border);
            m_borderWidth = border.getSize().x;
            return;
    }
}

void ArkanoidDrawer::drawGameScenePane(Side side)
{
    sf::FloatRect alreadyDrawnRect(m_backgroundRect.left - m_borderWidth, m_backgroundRect.top, m_backgroundRect.width + 2 * m_borderWidth, m_backgroundRect.height);
    sf::RectangleShape shape;
    switch(side) {
        case SideLeft:
            shape.setPosition(0, alreadyDrawnRect.top);
            shape.setSize(sf::Vector2f(alreadyDrawnRect.left, alreadyDrawnRect.height));
            shape.setFillColor(sf::Color(190, 190, 190));
            m_window->draw(shape);
            break;
        case SideRight:
            shape.setPosition(alreadyDrawnRect.left + alreadyDrawnRect.width, alreadyDrawnRect.top);
            shape.setSize(sf::Vector2f(m_window->getSize().x - alreadyDrawnRect.left - alreadyDrawnRect.width, alreadyDrawnRect.height));
            shape.setFillColor(sf::Color(190, 190, 190));
            m_window->draw(shape);
            break;
    }
}

void ArkanoidDrawer::drawProgressBar(int progress)
{
    static sf::RectangleShape bg;
    bg.setPosition(0, 0);
    bg.setSize(sf::Vector2f(m_window->getSize().x, m_backgroundRect.top));
    bg.setFillColor(sf::Color::Black);
    static sf::RectangleShape bar;
    bar.setSize(sf::Vector2f((bg.getSize().x - 20.f) * (progress / 100.f), bg.getSize().y / 3.f));
    bar.setPosition(10, (bg.getSize().y - bar.getSize().y) / 2);
    bar.setFillColor(sf::Color::Green);
    m_window->draw(bg);
    m_window->draw(bar);
}