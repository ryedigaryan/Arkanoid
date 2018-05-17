//
// Created by ryedigaryan on 5/17/2018.
//

#ifndef ARCANOID_BUTTON_H
#define ARCANOID_BUTTON_H

#include <string>
#include <SFML/Graphics/RectangleShape.hpp>

class Button {
public:
    Button(std::string text, sf::Vector2f position, sf::Vector2f size);

    std::string m_text;
    sf::RectangleShape m_body;
};

#endif //ARCANOID_BUTTON_H
