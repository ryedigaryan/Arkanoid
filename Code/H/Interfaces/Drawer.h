//
// Created by ryedigaryan on 5/17/2018.
//

#ifndef ARCANOID_DRAWER_H
#define ARCANOID_DRAWER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class Drawer {
public:
    Drawer(sf::RenderWindow& drawingWindow, const sf::Texture* bgTexture);
    virtual void display() = 0;

protected:
    sf::RenderWindow& m_window;
    const sf::Texture* m_bgTexture;
};

#endif //ARCANOID_DRAWER_H
