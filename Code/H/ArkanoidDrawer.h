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
    sf::Vector2f getLevelSize(bool considerBorders = false);

    void clearScreen(sf::Color fillColor = sf::Color::Black);
    void displayChanges();
    void drawMenu();
    void drawLevelStartInfo(const unsigned& level, const int& progress);
    void drawGameScene(const int& progress);
    void drawLevelEndInfo(const unsigned& level, const bool& hasWon);
    void drawCongratulations();

    unsigned drawObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture const * const texture, bool mustDisplay = false);
    void moveObject(const unsigned& id, const sf::Vector2f& newPosition);
    void resizeObject(const unsigned& id, const sf::Vector2f& change);
private:
    float m_borderWidth;
    sf::FloatRect m_backgroundRect;
    sf::RectangleShape m_progressBar;
    ResourceManager& m_resourceManager = ResourceManager::getManager();
    sf::RenderWindow* m_window;
    std::vector<ObjectInfo*> m_drawnObjects;

    sf::Text m_helperText;

private: // helper functions
    void cleanArea(const sf::IntRect& area, const sf::Texture* background);
    void drawBackground(const sf::Texture *bgTexture, int corner);
    void drawBorder(Side borderSide);
    void drawGameScenePane(Side side);
    void drawProgressBar(int progress);
};

#endif //ARCANOID_ARKANOIDDRAWER_H
