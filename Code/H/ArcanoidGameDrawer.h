//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEDRAWER_H
#define ARCANOID_ARCANOIDGAMEDRAWER_H

#include "Definitions.h"
#include "Geometry/Geometry.h"
#include "Interfaces/ArcanoidGameDrawerDelegate.h"
#include <SFML/Graphics.hpp>

class ArcanoidGameDrawer {
public: // members
    ArcanoidGameDrawer(const Size& windowSize);

    void setDelegate(ArcanoidGameDrawerDelegate* dlgate) {
        m_delegate = dlgate;
    }

    void setCurrentDrawingLayer(int layer) {
        m_currentDrawingLayer = layer;
    }

    void menu(bool mustShow);
    void loading(bool mustShow);
    void levelStart(bool mustShow, int level = 0, int progress = 0);
    void levelEnd(bool mustShow, bool hasWon = true) {} ;
    void gameWon(bool mustShow) {} ;

    //DO NOT FORGET PUT DRAWED OBJECT TO m_drawnObjects LIST
    void drawObject(unsigned objectID, const Point& position, const Size& size, const string& texturePath, bool mustShow);
    void redrawObject(unsigned objectID, const Size& size);
    void redrawObject(unsigned objectID, const Point& position);
    void moveObject(unsigned objectID, const Point& position) {} ;
    void hideObject(unsigned objectID) {} ;
    void deleteObject(unsigned objectID) {} ;

    ArcanoidGameDrawerDelegate* m_delegate;
protected:
    sf::RenderWindow* m_gameMainWindow;
    int m_currentDrawingLayer = 0;
    list<sf::RectangleShape> m_drawnObjects;
};

#endif //ARCANOID_ARCANOIDGAMEDRAWER_H
