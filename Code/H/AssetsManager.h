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

private:
    std::vector<sf::Texture*> m_textures;
    sf::Texture* m_defaultTexture;




private: // making singleton
    AssetsManager() {
        m_defaultTexture = new sf::Texture();
        m_defaultTexture->loadFromFile(DefaultPicturePath);
    };
public: // making singleton
    AssetsManager(AssetsManager const&) = delete;
    void operator=(AssetsManager const&) = delete;
};

#endif //ARCANOID_ASSETSMANAGER_H
