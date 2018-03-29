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
    if(!ballTxt->loadFromFile("Resources/Textures/Borders/1 - 50x50.png")) {
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

int main()
{
    std::vector<int*> i;
    i.resize(5, nullptr);
    if(i[1] != nullptr) {
        cout << "11" << endl;
    };
    if(i[1] == NULL) {
        cout << "1" << endl;
    };
    if(i[2] == nullptr) {
        cout << "212" << endl;
    };

    std::vector<int> v;
//    v.reserve(10);
    v.resize(10);
    v.insert(v.begin() + 4, 4);

    sf::RectangleShape s;
    ResourceManager& m = ResourceManager::getManager();
    s.setTexture(&m.getTexture(BallTexture));
    m.getTexture(BallTexture);
    m.getTexture(BallTexture);

    s.setPosition(50, 50);
    window.draw(s);
    window.display();
    system("pause");
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