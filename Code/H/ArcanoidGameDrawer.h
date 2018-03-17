//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEDRAWER_H
#define ARCANOID_ARCANOIDGAMEDRAWER_H

#include <SFML/Graphics.hpp>

#include "Definitions.h"
#include "Geometry/Geometry.h"
#include "Interfaces/ArcanoidGameDrawerDelegate.h"

class ArcanoidGameDrawer {
public:
    explicit ArcanoidGameDrawer(sf::Color backgroundColor);

    void setDelegate(ArcanoidGameDrawerDelegate* dlgate);

    sf::RenderWindow* getMainWindow();

    // non-game specific drawing functions, like menu, loading, level info e.t.c.
    // these functions do not show the drawn stuff if mustShow parameter setted to false
    void drawMenu(bool mustShow = true);
    void drawLoading(bool mustShow = true);
    void drawAllGameObjects(bool mustShow = true);
    void drawLevelStartInfo(int level = 0, int progress = 0, bool mustShow = true);
    void drawLevelEndInfo(int level, bool hasWon, bool mustShow = true);
    void drawGameWon(bool mustShow = true);
    void drawText(const std::string &text, TextPosition position, bool mustShow = true);
    void clearScreen(bool mustShow = true);
    // shows(displays) all the drawn stuff
    void showDrawnStuff();
    void setBackgroundColor(sf::Color bgColor);

    // game specific drawing functions, like Brick, Paddle, Ball e.t.c. and their movement
    void drawObject(unsigned objectID, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& texturePath, bool mustShow = true, bool mustRepeatTexture = false);
    void resizeObject(unsigned objectID, const sf::Vector2f& size);
    void moveObject(unsigned objectID, const sf::Vector2f& position);
    void deleteObject(unsigned objectID, bool mustShow = true);
    void hideObject(unsigned objectID, bool mustShow = true);

    ArcanoidGameDrawerDelegate* m_delegate;
protected:
    sf::RenderWindow* m_gameMainWindow;
    std::vector<sf::RectangleShape*> m_drawnObjects;
    sf::Color m_backgroundColor;

private:
    // will be set in constructor proportionally to screen size
    // used for showing pop-ups(like level info) in their right place
    sf::Rect<unsigned> m_popUpRect;
    // those 3 variables below are performance boosters
    // used for not spending time on sf::RectangleShape initialization
    sf::RectangleShape m_helperRectShape;
    sf::Text m_helperText;
    sf::Font m_helperFont;
};

#endif //ARCANOID_ARCANOIDGAMEDRAWER_H
