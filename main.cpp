#include <iostream>
#include <afxres.h>
#include <SFML/Graphics.hpp>
#include <Models/Brick.h>
#include <Models/Interfaces/Attacker.h>
#include <Models/Ball.h>
#include <GameData.h>
#include <ArkanoidGameController.h>

using namespace std;

#define END system("pause"); return 0;

void test();
void handleInput(sf::RenderWindow* wnd);

//sf::RenderWindow window(sf::VideoMode(0, 0), "SFML works!", sf::Style::Fullscreen);

enum A {
    a,
    b,
    c
};

enum B {
    d,
    e,
    f,
    c
};
int main() {
    A vA = A::c;
    B vB = B::c;

    cout << "A: " << vA << endl;
    cout << "B: " << vB << endl;

}

void handleInput(sf::RenderWindow* wnd) {
    sf::Event e;
    while(wnd->pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            wnd->close();
        }
    }
}

void test(sf::RenderWindow &window) {
    sf::RectangleShape shape(sf::Vector2f(50, 50));
    shape.setPosition(50, 50);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape hideShape(sf::Vector2f(50, 50));
    hideShape.setFillColor(sf::Color::Black);
    bool show = true;
    int val = 10;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                cout << shape.getPosition().x << " " << shape.getPosition().y << endl;
                hideShape.setPosition(shape.getPosition());
                shape.setPosition(shape.getPosition().x + val, shape.getPosition().y + (val > 0 ? val : 2 * val));
                window.draw(shape); // draw in new place
                window.display();
                window.draw(hideShape);
                if (shape.getPosition().x + shape.getSize().x >= window.getSize().x ||
                        shape.getPosition().y + shape.getSize().y >= window.getSize().y) {
                    val = -abs(val);
                }
                else if (shape.getPosition().x <= 0 ||
                         shape.getPosition().y  <= 0) {
                    val = abs(val);
                }
            }
        }

        if(show) {
            window.clear();
            window.draw(shape);
            window.display();
            show = false;
        }
    }
}