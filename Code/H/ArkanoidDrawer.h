//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_ARKANOIDDRAWER_H
#define ARCANOID_ARKANOIDDRAWER_H

#include "Definitions/CommonDefinitions.h"
#include "Definitions/DrawerDefinitions.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

struct ObjectInfo {
    sf::RectangleShape* object;
    sf::IntRect* previousArea;

    explicit ObjectInfo(sf::RectangleShape* obj = nullptr, sf::IntRect* prevArea = nullptr) : object(obj), previousArea(prevArea) {}

    ~ObjectInfo() {
        delete object;
        delete previousArea;
    }
};

class ArkanoidDrawer {
public:
    ArkanoidDrawer();
    ~ArkanoidDrawer();

    sf::RenderWindow* getDrawingWindow();

    void clearScreen(sf::Color fillColor = sf::Color::Black);
    void displayChanges();
    void drawMenu();
    void drawLevelStartInfo(const unsigned& level, const int& progress);
    void drawLevelEndInfo(const unsigned& level, const bool& hasWon);

    unsigned drawObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture const * const texture, bool mustDisplay = false);
    void moveObject(const unsigned& id, const sf::Vector2f& newPosition);
    void drawGameScene();
    void resizeObject(const unsigned& id, const sf::Vector2f& change);
private:
    ResourceManager& m_resourceManager = ResourceManager::getManager();
    sf::RenderWindow* m_window;
    std::vector<ObjectInfo> m_drawnObjects;

    sf::Text m_helperText;

    void cleanArea(const sf::IntRect& area, const sf::Texture* background);
};

#endif //ARCANOID_ARKANOIDDRAWER_H
