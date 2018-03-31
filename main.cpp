#include <iostream>
#include <SFML/Graphics.hpp>
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

int main() {
    int a = 10;
    cout << "m: " << a << endl;
    f(a);

    ArkanoidGameController c;
    c.start();
    return 0;
    sf::RenderWindow w(sf::VideoMode(500, 500), "test");
    sf::RectangleShape s;
    s.setFillColor(sf::Color::Red);
    sf::Vector2f pos(10, 10);
    sf::Vector2f siz(20, 20);
    s.setPosition(pos);
    s.setSize(siz);

    while(w.isOpen()) {
        sf::Event e;
        while(w.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                w.close();
            }
            else if(e.type == sf::Event::KeyPressed) {
                switch(e.key.code) {
                    case sf::Keyboard::Left:
                        pos.x -= 10;
                        break;
                    case sf::Keyboard::Right:
                        pos.x += 10;
                        break;
                    case sf::Keyboard::Up:
                        pos.y -= 10;
                        break;
                    case sf::Keyboard::Down:
                        pos.y += 10;
                        break;
                    case sf::Keyboard::Add:
                        siz.x += 10;
                        siz.y += 10;
                        break;
                    case sf::Keyboard::Subtract:
                        siz.x -= 10;
                        siz.y -= 10;
                        break;
                }
            }
        }

        w.clear();
        s.setPosition(pos);
        s.setSize(siz);
        w.draw(s);
        w.display();
    }

}