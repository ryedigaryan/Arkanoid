#include <iostream>
#include <afxres.h>

#include "ArcanoidGameManager.h"

#define END system("pause"); return 0;

sf::RenderWindow window;//(sf::VideoMode(500, 800), "Testing SFML");

sf::RectangleShape obj;

void draw(float x, float y) {
    obj.setPosition(x, y);
    window.clear(sf::Color::Yellow);
    window.draw(obj);
    window.display();
}

int main() {

//    obj.setSize(sf::Vector2f(50, 50));
//    obj.setFillColor(sf::Color::Green);
//    int x = 0, y = 0;
//    while(window.isOpen()) {
//        sf::Event e;
//        while(window.pollEvent(e)) {}
//        draw(x = (x + 10) % window.getSize().x, y = (y + 10) % window.getSize().y);
//        Sleep(5);
//        cout << obj.getPosition().x << " " << obj.getPosition().y << endl;
//    }


    ArcanoidGameManager& manager = ArcanoidGameManager::getManager();
    ArcanoidGameDrawer drawer(Size(400, 440));
    ArcanoidGameEngine& engine = ArcanoidGameEngine::getEngine();
    manager.addAllLevelSpecsInPath(LevelSpecsPath, LevelSpecExtension, LevelCount);
    manager.setDrawer(&drawer);
    manager.setEngine(&engine);

    manager.startGame();

    std::cout << "Hello, World!" << std::endl;
    END
}