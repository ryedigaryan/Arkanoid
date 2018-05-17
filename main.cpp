#include "ArkanoidGameController.h"

using namespace std;

sf::RenderWindow m_window(sf::VideoMode(500, 600), "test window");

sf::Text** m_buttons = new sf::Text*[3];
int cntntntn = 0;

sf::Text * button;

void addButton(std::string buttonText, sf::Font font)
{
    unsigned charSize = 30;
    sf::Text* button = new sf::Text(buttonText, font, charSize);
    ::button = new sf::Text(buttonText, font, charSize);
    button->setFillColor(sf::Color::Green);
    sf::FloatRect bounds = button->getGlobalBounds();
    button->setPosition(myutils::middle(m_window.getSize().x, bounds.width), cntntntn * charSize + charSize / 2);
//    m_window.draw(*button);
    m_buttons[cntntntn] = button;
    cntntntn++;
}

void display() {
//    sf::RectangleShape s;
    cout << "display" << endl;
    for (unsigned i = 0; i < cntntntn; i++) {
        sf::Text* m_button = m_buttons[i];
        m_button->setFillColor(sf::Color::Blue);

        m_window.draw(*m_button);
        cout << "drawing button " << m_button->getString().toAnsiString() << endl;
        cout << "pos: " << m_button->getPosition().x << " " << m_button->getPosition().y << endl;
        cout << "siz: " << m_button->getGlobalBounds().width << " " << m_button->getGlobalBounds().height << endl;
        m_window.clear(sf::Color::Green);
    }
    m_window.draw(*::button);
    m_window.display();
    m_window.requestFocus();
}

int main()
{
//    auto b = new sf::Text("mystring", ResourceManager::getManager().getFont(StateTypeMainMenu));
//    b->setFillColor(sf::Color::Green);
//    m_window.draw(*b);
//    system("pause");
//
//    return 0;
    addButton("but1", ResourceManager::getManager().getFont(StateTypeMainMenu));
    addButton("but2", ResourceManager::getManager().getFont(StateTypeMainMenu));
    m_window.display();
    sf::Event e;;
    while(m_window.isOpen()) {
        while(m_window.pollEvent(e)) {
            if(e.type == sf::Event::KeyPressed) {
                switch(e.key.code) {
                    case sf::Keyboard::Escape:
                        m_window.close();
                        break;
                    case sf::Keyboard::E:
                        display();
                        break;
                }
            }
        }
    }
    return 0;
    ArkanoidGameController z_besTT__KAYFFF_gEneRatOR_I_HAVE_everRrRrRr_SEeEeEeNNNNNNN;
    // This line
    // runs the best
    // kayf generator ever
    // in the history
    // of humanity...
    // Just have fun...
    z_besTT__KAYFFF_gEneRatOR_I_HAVE_everRrRrRr_SEeEeEeNNNNNNN.__lEt_Ze__FuNN__begiNNZZZZZZ___();
    return 0;
}