//
// Created by ryedigaryan on 3/29/2018.
//

#ifndef ARCANOID_RESOURCEMANAGER_H
#define ARCANOID_RESOURCEMANAGER_H

#include "Definitions/CommonDefinitions.h"
#include <SFML/Graphics.hpp>

#define DefaultTexturePath "Resources/Textures/default"
#define DefaultFontPath "Resources/Fonts/default"

class Resource {
public:
    explicit Resource(const std::string& p) : path(p) {}
    explicit Resource(std::string&& p) : path(std::move(p)) {}

    const std::string path;
    const unsigned id = nextID();
private:
    unsigned nextID() {
        static unsigned id = 0;
        return id++;
    }
};

extern const Resource MainMenuFont;
extern const Resource LevelInfoFont;

extern const Resource MainMenuBackground;
extern const Resource LevelInfoBackground;
extern const Resource BallTexture;
extern const Resource BorderTexture;
extern const Resource Paddle1Texture;
extern const Resource Paddle2Texture;
extern const Resource Paddle3Texture;
extern const Resource Brick1Texture;
extern const Resource Brick2Texture;
extern const Resource Brick3Texture;
extern const Resource Brick4Texture;
extern const Resource Brick5Texture;

// TODO: Do not forget to change definitions after adding new Resources
#define FontReservationSize 2
#define TextureReservationSize 14

class ResourceManager {
public:
    static ResourceManager& getManager();
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;
public:
    const sf::Font& getFont(Resource resource);
    const sf::Texture* getTexture(Resource resource);


private:
    sf::Font m_defaultFont;
    sf::Texture* m_defaultTexture;

    std::vector<sf::Font*> m_loadedFonts;
    std::vector<sf::Texture*> m_loadedTextures;

private:
    ResourceManager();
};

#endif //ARCANOID_RESOURCEMANAGER_H