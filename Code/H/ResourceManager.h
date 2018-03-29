//
// Created by ryedigaryan on 3/29/2018.
//

#ifndef ARCANOID_RESOURCEMANAGER_H
#define ARCANOID_RESOURCEMANAGER_H

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics/Font.hpp>
#include <utility>

#define DefaultTexturePath "Resources/Textures/default"
#define DefaultFontPath "Resources/Fonts/default"

class Resource {
public:
    Resource(const std::string& p) : path(p) {
        int a = 01;
    };
    const std::string path;
    const unsigned id = nextID();
private:
    unsigned nextID() {
        static unsigned id = 0;
        return id++;
    }
};


const static Resource MainMenuFont("Resources/Fonts/default");
const static Resource LevelInfoFont("Resources/Fonts/default");

const static Resource MainMenuBackground("Resources/Textures/main_menu_bg");
const static Resource BallTexture("Resources/Textures/Balls/1");
const static Resource BorderTexture("Resources/Textures/Borders/1");
const static Resource Paddle1Texture("Resources/Textures/Paddles/1");
const static Resource Paddle2Texture("Resources/Textures/Paddles/2");
const static Resource Paddle3Texture("Resources/Textures/Paddles/3");
const static Resource Brick1Texture("Resources/Textures/Bricks/1");
const static Resource Brick2Texture("Resources/Textures/Bricks/2");
const static Resource Brick3Texture("Resources/Textures/Bricks/3");
const static Resource Brick4Texture("Resources/Textures/Bricks/4");
const static Resource Brick5Texture("Resources/Textures/Bricks/5");

// TODO: Do not forget to change definitions after adding new Resources
#define FontReservationSize 2
#define TextureReservationSize 13

class ResourceManager {
public:
    static ResourceManager& getManager();
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;
public:
    const sf::Font& getFont(Resource resource);
    const sf::Texture& getTexture(Resource resource);

private:
    sf::Font m_defaultFont;
    sf::Texture m_defaultTexture;

    std::vector<sf::Font*> m_loadedFonts;
    std::vector<sf::Texture*> m_loadedTextures;

private:
    ResourceManager();
};

#endif //ARCANOID_RESOURCEMANAGER_H
