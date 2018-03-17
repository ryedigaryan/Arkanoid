//
// Created by ryedigaryan on 3/17/2018.
//

#ifndef ARCANOID_ASSETSMANAGER_H
#define ARCANOID_ASSETSMANAGER_H

#include "Definitions.h"
#include <SFML/Graphics.hpp>

class AssetsManager {
public: // static funcitons
    static AssetsManager& getManager() {
        static AssetsManager singletonInstance;
        return singletonInstance;
    }

public:
    static std::string Balsl[] = {"SDF"};

private:
    std::map<std::string, sf::Texture*> m_textures;
    sf::Texture* m_defaultTexture;
    std::map<std::string, sf::Font*> m_fonts;
    sf::Font* m_defaultFont;



private: // making singleton
    AssetsManager();

    void loadAllTextures();
    void loadTextures(GameObjectType goType);
    void loadTexture(const std::string& directory, int count);
    void loadAllFonts();
    void loadFont();
public: // making singleton
    AssetsManager(AssetsManager const&) = delete;
    void operator=(AssetsManager const&) = delete;
};

class TextureNames {
public:
    static const std::string Balls[] = {"ball"};
    static const std::string Bricks[] = {"brick_1", "brick_2", "brick_3", "brick_4", "brick_5"};
    static const std::string Paddles[] = {"paddle_1", "paddle"};
};

#endif //ARCANOID_ASSETSMANAGER_H
