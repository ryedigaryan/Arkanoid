//
// Created by ryedigaryan on 3/29/2018.
//

#include <SFML/Graphics/Texture.hpp>
#include <ResourceManager.h>
#include <SFML/Graphics/Text.hpp>


ResourceManager &ResourceManager::getManager()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() {
    m_defaultFont;
    if(!m_defaultFont.loadFromFile(DefaultFontPath)) {
        cout << "FATAL ERROR: ResourceManager() - cannot load font: " << DefaultFontPath << endl;
    }

    m_defaultTexture;
    if(!m_defaultTexture.loadFromFile(DefaultTexturePath)) {
        cout << "FATAL ERROR: ResourceManager() - cannot load texture: " << DefaultTexturePath << endl;
    }

    m_loadedFonts.resize(FontReservationSize, nullptr);
    m_loadedTextures.resize(TextureReservationSize, nullptr);
}

// as the sf::Font and sf::Texture have no common interface which would help to load them, I created 2 separate functions for loading
const sf::Font& ResourceManager::getFont(Resource resource)
{
    if(m_loadedFonts[resource.id] != nullptr) {
        // if the font is in cache then return it
        return *m_loadedFonts[resource.id];
    }
    // if resource is not in cache then load it to cache
    auto font = new sf::Font();
    if(!font->loadFromFile(resource.path)) {
        cout << "Returning default font! Cause: cannot load font: " << resource.path << endl;
        // if font cannot be loaded then return default font
        return m_defaultFont;
    }
    // if font loaded successfully then return it
    m_loadedFonts[resource.id] = font;
    return *font;
}

const sf::Texture& ResourceManager::getTexture(Resource resource)
{
    if(m_loadedTextures[resource.id] != NULL) {
        // if the texture is in cache then return it
        return *m_loadedTextures[resource.id];
    }
    // if resource is not in cache then load it to cache
    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile(resource.path)) {
        cout << "Returning default texture! Cause: cannot load texture: " << resource.path << endl;
        // if font cannot be loaded then return default texture
        return m_defaultTexture;
    }
    // if texture loaded successfully then return it
    m_loadedTextures[resource.id] = texture;
    return *texture;
}
