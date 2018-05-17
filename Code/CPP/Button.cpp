//
// Created by ryedigaryan on 5/17/2018.
//

#include <utility>

#include "UI/UIElements/Button.h"

Button::Button(std::string text, sf::Vector2f position, sf::Vector2f size)
{
    m_text = std::move(text);
    m_body.setPosition(position);
    m_body.setSize(size);
}
