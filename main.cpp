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

#define WIDTH 960
#define HEIGHT 600

//sf::RenderWindow window(sf::VideoMode(0, 0), "SFML works!", sf::Style::Fullscreen);
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

struct MyRect {
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Color col;
};

MyRect randomRect() {
    MyRect r;
    r.pos.x = rand() % WIDTH;
    r.pos.y = rand() % HEIGHT;
    r.size.x = rand() % 50 + 10;
    r.size.y = rand() % 45 + 15;
    r.col.r = rand() % 256;
    r.col.g = rand() % 256;
    r.col.b = rand() % 256;
    return r;
}

sf::RectangleShape randomShape() {
    MyRect r = randomRect();
    sf::RectangleShape s;
    s.setPosition(r.pos);
    s.setSize(r.size);
    s.setFillColor(r.col);
    return s;
}

auto ballTxt = new sf::Texture();

sf::Sprite randomSprite() {
    MyRect r = randomRect();
    if(!ballTxt->loadFromFile("Resources/Pictures/Borders/1 - 50x50.png")) {
        cout << "FATAL ERROR: randomSprite()" << endl;
    }

    sf::Sprite s(*ballTxt);
    s.setPosition(0, 0);
//    s.setColor(r.col);
//    s.setTextureRect(sf::IntRect(0, 0, ballTxt->getSize().x, ballTxt->getSize().y));
    return s;
}

auto emptyTextre = new sf::Texture();

#define ShapeCount 10

sf::Texture* newTexture(std::string path) {
    auto t = new sf::Texture();
    if(!t->loadFromFile(path)) {
        cout << "FATAL ERROR: load(...) "  << endl;
    }
    return t;
}

int main() {

    sf::FloatRect prevBounds;

    sf::Sprite sprite = randomSprite();
    sf::RectangleShape shapes[ShapeCount];
    sf::RectangleShape s = randomShape();

    auto bg_txtre = newTexture("C:/Users/ryedigaryan/CLionProjects/Arkanoid/Resources/bg.jpg");

    sf::Sprite bg(*bg_txtre);
    cout << bg.getScale().x << "  " << bg.getScale().y << endl;
    cout << window.getSize().x << endl;
    cout << bg_txtre->getSize().x << endl;
    cout << window.getSize().y << endl;
    cout << bg_txtre->getSize().y << endl;
    bg.setScale(sf::Vector2f((float)window.getSize().x / bg_txtre->getSize().x, (float)window.getSize().y / bg_txtre->getSize().y));
    cout << bg.getScale().x << "  " << bg.getScale().y << endl;
    window.draw(bg);
    window.draw(sprite);
    window.display();
    window.draw(bg);
    window.display();
    window.display();


    if(!emptyTextre->loadFromFile("Resources/Pictures/Borders/empty.png")) {
        cout << "FATAL ERROR: main()" << endl;
    }


    bool draw = true;
    bool erase = false;
    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            }
            if(e.type == sf::Event::KeyPressed) {
                if(e.key.code == sf::Keyboard::S) {
                    sprite.setTexture(*ballTxt);
                    sprite.setColor(sf::Color::White);
                }
                if(e.key.code == sf::Keyboard::D) {
                    sprite.setTexture(*emptyTextre);
                    s.setTextureRect(sf::IntRect(0, 0, ballTxt->getSize().x, ballTxt->getSize().y));
                }
                if(e.key.code == sf::Keyboard::Return) {
                    bg.setPosition(prevBounds.left, prevBounds.top);
                    bg.setTextureRect(
                            sf::IntRect(prevBounds.left / bg.getScale().x, prevBounds.top / bg.getScale().y, prevBounds.width / bg.getScale().x,
                                        prevBounds.height / bg.getScale().y));
                    window.draw(bg);

                    prevBounds = sprite.getGlobalBounds();
                    sprite.move(sf::Vector2f(10, 10));

                    window.draw(sprite);
                    window.display();
                }
            }
        }
    }
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