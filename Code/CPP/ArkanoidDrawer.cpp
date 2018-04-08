//
// Created by ruben on 3/25/2018.
//

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Definitions/DrawerDefinitions.h"
#include "ArkanoidDrawer.h"

ArkanoidDrawer::ArkanoidDrawer()
{
    m_window = new sf::RenderWindow(sf::VideoMode(), WindowTitle, sf::Style::Fullscreen);
}

sf::RenderWindow* ArkanoidDrawer::getDrawingWindow()
{
    return m_window;
}

ArkanoidDrawer::~ArkanoidDrawer()
{
    m_window->close();
    delete m_window;
    for(auto drawnObject : m_drawnObjects) {
        delete drawnObject;
    }
}

void ArkanoidDrawer::clearScreen(sf::Color bgCol)
{
    m_window->clear(bgCol);
}

void ArkanoidDrawer::displayChanges()
{
    m_window->display();
}

void ArkanoidDrawer::drawMenu()
{
    static sf::RectangleShape helperShape(sf::Vector2f(m_window->getSize()));
    helperShape.setTexture(m_resourceManager.getTexture(MainMenuBackground));
    helperShape.setPosition(0, 0);
    // configure text
    m_helperText.setString("Press Enter");
    m_helperText.setFont(m_resourceManager.getFont(MainMenuFont));
    m_helperText.setPosition((m_window->getSize().x - m_helperText.getLocalBounds().width) / 2, (m_window->getSize().y - m_helperText.getLocalBounds().height) / 2);
    // draw main menu stuff
    m_window->draw(helperShape);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::drawLevelStartInfo(const unsigned& level, const int& progress)
{
    static sf::Sprite helperSprite;
    // draw pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(LevelInfoBackground));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    m_window->draw(helperSprite);
    // draw text: Level: xxx Won/Loast
    m_helperText.setString(std::string("Level: ") + std::to_string(level));
    m_helperText.setFont(m_resourceManager.getFont(LevelInfoFont));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    m_window->draw(m_helperText);
    // draw text: Progress: xxx
    m_helperText.setString(std::string("Progress: ") + std::to_string(progress));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize()*2 + 10 + LineSpacing);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::drawLevelEndInfo(const unsigned& level, const bool& hasWon)
{
    drawGameScene();
    static sf::Sprite helperSprite;
    // configure pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(LevelInfoBackground));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    // configure text
    std::string lvl("Level ");
    lvl = lvl + std::to_string(level);
    m_helperText.setString(lvl + (hasWon ? " Won" : " Lost"));
    m_helperText.setFont(m_resourceManager.getFont(LevelInfoFont));
    m_helperText.setFillColor(sf::Color::Black);
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    // draw main menu stuff
    m_window->draw(helperSprite);
    m_window->draw(m_helperText);
    // and display all drawn stuff
    m_window->display();
    m_helperText.setFillColor(sf::Color::White);
}

unsigned ArkanoidDrawer::drawObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture const * const texture, bool mustDisplay /* = false */)
{
    // create object which must be drawn
    auto object = new sf::RectangleShape(size);
    object->setPosition(position);
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

void ArkanoidDrawer::moveObject(const unsigned& id, const sf::Vector2f &newPosition)
{
    ObjectInfo* movable = m_drawnObjects[id];
    // clean up scene (only the area which necessarily)
    if(movable->previousArea == nullptr) { // for this statement previousArea declared as pointer, and initializes as nullptr
        movable->previousArea = new sf::IntRect(movable->object->getGlobalBounds());
    }
    cleanArea(*(movable->previousArea), m_resourceManager.getTexture(GameSceneBackground));
    // save current area as previous for further moving
    movable->previousArea->top = static_cast<int>(movable->object->getGlobalBounds().top);
    movable->previousArea->left = static_cast<int>(movable->object->getGlobalBounds().left);
    movable->previousArea->width = static_cast<int>(movable->object->getGlobalBounds().width);
    movable->previousArea->height = static_cast<int>(movable->object->getGlobalBounds().height);
    // move the object and draw in new position
    movable->object->move(newPosition.x - movable->object->getPosition().x, newPosition.y - movable->object->getPosition().y);
    m_window->draw(*movable->object);
    m_window->display();
}

void ArkanoidDrawer::drawGameScene()
{
    static sf::RectangleShape helperShape(sf::Vector2f(m_window->getSize()));
    helperShape.setTexture(m_resourceManager.getTexture(GameSceneBackground));
    helperShape.setPosition(0, 0);
    for(int i = 1; i <= 2; i++) {
        m_window->draw(helperShape);
        for (auto objInfo : m_drawnObjects) {
            m_window->draw(*objInfo->object);
        }
        m_window->display();
    }
}

void ArkanoidDrawer::drawCongratulations()
{
    static sf::Sprite helperSprite;
    // draw pop-up background
    helperSprite.setTexture(*m_resourceManager.getTexture(LevelInfoBackground));
    helperSprite.setScale(sf::Vector2f(0.5, 0.5));
    helperSprite.setPosition((m_window->getSize().x - helperSprite.getGlobalBounds().width) / 2, (m_window->getSize().y - helperSprite.getGlobalBounds().height) / 2);
    m_window->draw(helperSprite);
    // draw text: Congrats!!!
    m_helperText.setFillColor(sf::Color::Red);
    m_helperText.setString("  Congrats!!!\nYou have won\n  the game");
    m_helperText.setFont(m_resourceManager.getFont(LevelInfoFont));
    m_helperText.setPosition((helperSprite.getGlobalBounds().width - m_helperText.getLocalBounds().width) / 2 + helperSprite.getGlobalBounds().left, helperSprite.getGlobalBounds().top + m_helperText.getCharacterSize() + 10);
    m_window->draw(m_helperText);
    m_helperText.setFillColor(sf::Color::White);
    // and display all drawn stuff
    m_window->display();
}

void ArkanoidDrawer::cleanArea(const sf::IntRect& area, const sf::Texture* background) {
    static sf::RectangleShape helperShape;
    helperShape.setTexture(background);
    helperShape.setTextureRect(area);
    helperShape.setPosition(area.left, area.top);
    helperShape.setSize(sf::Vector2f(area.width, area.height));
    m_window->draw(helperShape);
}