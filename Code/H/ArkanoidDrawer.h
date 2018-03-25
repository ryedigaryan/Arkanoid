//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_ARKANOIDDRAWER_H
#define ARCANOID_ARKANOIDDRAWER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class ArkanoidDrawer {
public:
    ArkanoidDrawer();
    ~ArkanoidDrawer();

    sf::RenderWindow* getDrawingWindow();

    void drawMenu();
    void drawLevelStartInfo();
    void drawLevelEndInfo();
    void clear(sf::Color fillColor);

    void drawObject(const std::string& texturepath, sf::Vector2f position, sf::Vector2f size);
    void redrawObject(const int& id, sf::Vector2f position, sf::Vector2f size);
private:
    sf::RenderWindow* m_window;
    std::vector<sf::RectangleShape*> m_drawnObjects;
};

#endif //ARCANOID_ARKANOIDDRAWER_H
