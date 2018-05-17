//
// Created by ryedigaryan on 5/17/2018.
//

#ifndef ARCANOID_MAINMENUDRAWER_H
#define ARCANOID_MAINMENUDRAWER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Interfaces/Drawer.h"
#include "Definitions/CommonDefinitions.h"
#include "ResourceManager.h"

class MenuDrawer : public Drawer {
public:
    MenuDrawer(sf::RenderWindow* drawingWindow, const sf::Texture* bgTexture, const unsigned& initialCapacity, const sf::Color& unmarkedButtonColor, const sf::Color& markedButtonColor);

    void draw();
    void display() override;

    MenuDrawer& addButton(const std::string& buttonText, const sf::Font& font);

    void markNextButton();
    void markPrevButton();
    unsigned currMarkedButton();

private: // data
    unsigned m_currentMarkedButton;
    std::vector<sf::Text> m_buttons;
    sf::Color m_unmarkedButtonColor;
    sf::Color m_markedButtonColor;

private: // functions
    sf::Text& prevButton();
    sf::Text& currButton();
    sf::Text& nextButton();

    void resizeButtons();
    unsigned characterSize() const;
};

#endif //ARCANOID_MAINMENUDRAWER_H
