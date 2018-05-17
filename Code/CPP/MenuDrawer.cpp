//
// Created by ryedigaryan on 5/17/2018.
//

#include "UI/Drawers/MenuDrawer.h"

MenuDrawer::MenuDrawer(sf::RenderWindow* drawingWindow, const sf::Texture* bgTexture, const unsigned& initialCapacity, const sf::Color& unmarkedButtonColor, const sf::Color& markedButtonColor)
        : Drawer(*drawingWindow, bgTexture), m_unmarkedButtonColor(unmarkedButtonColor), m_markedButtonColor(markedButtonColor), m_currentMarkedButton(0)
{
    m_buttons.reserve(initialCapacity);
}

void MenuDrawer::draw()
{
    static sf::RectangleShape helperShape(sf::Vector2f(m_window.getSize()));
    helperShape.setTexture(m_bgTexture, true);
    m_window.draw(helperShape);
//    for(sf::Text& button : m_buttons) {
//        m_window.draw(button);
//    }
    for(unsigned i = 0; i < m_buttons.size(); i++) {
        m_window.draw(m_buttons[i]);
    }
}

void MenuDrawer::display()
{
    m_window.display();
}

MenuDrawer& MenuDrawer::addButton(std::string buttonText, sf::Font font)
{
    unsigned charSize = characterSize();
    m_buttons.emplace_back(buttonText, font, charSize);
    sf::Text& button = m_buttons.back();
    button.setFillColor(m_unmarkedButtonColor);
    if(m_buttons.size() == m_buttons.capacity()) {
        resizeButtons();
    }
    else {
        sf::FloatRect bounds = button.getLocalBounds();
        button.setPosition(myutils::middle(m_window.getSize().x, bounds.width), m_buttons.size() * charSize + charSize / 2);
    }
    logutils::logstream << "bs: " << m_buttons.size() << endl;
    for(sf::Text& b : m_buttons) {
        logutils::logstream << "\tt: " << b.getString().toAnsiString() << endl;
    }
    return *this;
}

sf::Text& MenuDrawer::prevButton()
{
    return m_currentMarkedButton == 0 ? m_buttons[m_currentMarkedButton = m_buttons.size() - 1] : m_buttons[m_currentMarkedButton--];
}

sf::Text& MenuDrawer::currButton()
{
    return m_buttons[m_currentMarkedButton];
}

sf::Text& MenuDrawer::nextButton()
{
    return m_currentMarkedButton == m_buttons.size() - 1 ? m_buttons[m_currentMarkedButton = 0] : m_buttons[m_currentMarkedButton++];
}

void MenuDrawer::markPrevButton()
{
    currButton().setFillColor(m_unmarkedButtonColor);
    prevButton().setFillColor(m_markedButtonColor);
}

void MenuDrawer::markNextButton()
{
    currButton().setFillColor(m_unmarkedButtonColor);
    nextButton().setFillColor(m_markedButtonColor);
}

void MenuDrawer::resizeButtons()
{
    unsigned charSize = characterSize();
    for(unsigned i = 0; i < m_buttons.size(); i++) {
        auto button = m_buttons[i];
        button.setCharacterSize(characterSize());
        sf::Vector2f newPos;
        newPos.x = myutils::middle(m_window.getSize().x, button.getLocalBounds().width);
        newPos.y = i * charSize + charSize / 2;
        button.setPosition(newPos);
    }
}

unsigned MenuDrawer::characterSize() const
{
    return m_window.getSize().y / (m_buttons.size() + 1);
}
