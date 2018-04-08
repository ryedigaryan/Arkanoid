#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "ArkanoidGameController.h"

using namespace std;

void g(const int&);

void f(const int &a) {
    cout << "f: " << a << endl;
    g(a);
}

void g(const int &a) {
    cout << "g: " << a << endl;
}

int v() {
    int i = 10;
}

class A {
public:
    explicit A(int i) {

    }
};

int main()
{


//    ArkanoidGameController c;
//    c.start();
//    return 0;
    sf::RenderWindow w(sf::VideoMode(500, 500), "test");
    sf::RectangleShape s;
    s.setFillColor(sf::Color::Red);
    w.clear(sf::Color::Red);

    sf::Image img;
    img.loadFromFile(ResourceManager::getManager().pathToTexture(ObjectTypeBrick, 3, ResolutionMedium));

    auto texture = new sf::Texture(*ResourceManager::getManager().getTexture(ObjectTypeBorder, 1));

    sf::RectangleShape spr;
    spr.setSize(sf::Vector2f(25, 100));
    spr.setTexture(texture);
    w.draw(spr);
    w.display();

    while(w.isOpen()) {
        sf::Event e;
        while(w.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                w.close();
            }
            else if(e.type == sf::Event::KeyPressed) {
                w.close();
            }
        }

    }

}