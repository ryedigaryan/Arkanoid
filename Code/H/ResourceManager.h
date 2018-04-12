//
// Created by ryedigaryan on 3/29/2018.
//

#ifndef ARCANOID_RESOURCEMANAGER_H
#define ARCANOID_RESOURCEMANAGER_H

#include "Definitions/CommonDefinitions.h"
#include "Models/Level.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

class ResourceManager {
public: // making singleton
    static ResourceManager& getManager();
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

public: // public interface
    Resolution m_resolution;

    // resource getters
    const sf::Font&     getFont(StateType state);
    const sf::Texture*  getTexture(StateType stateType);
    const sf::Texture*  getTexture(ObjectType objectType, unsigned number = 1);
    Level               getLevel(const unsigned& levelNumber);
    // path creators
    std::string pathToFont(StateType state);
    std::string pathToTexture(StateType stateType);
    std::string pathToTexture(ObjectType objectType, unsigned number);
    std::string pathToLevel(unsigned levelNumber);
    // helpers(converters to string)
    std::string toString(StateType objectType);
    std::string toString(ObjectType objectType);
    std::string toString(Resolution resolution);
    std::string toString(unsigned number);

private: // private data
    sf::Font m_defaultFont;
    sf::Texture* m_defaultTexture;

    std::vector<sf::Font*> m_loadedFonts;
    std::vector<sf::Texture*> m_loadedStateTextures;
    std::vector<std::vector<sf::Texture*>> m_loadedObjectTextures;
    std::vector<Level*> m_loadedLevels;


private:
    ResourceManager();
};

#endif //ARCANOID_RESOURCEMANAGER_H
