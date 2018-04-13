//
// Created by ryedigaryan on 3/29/2018.
//

#include "ResourceManager.h"

ResourceManager& ResourceManager::getManager()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager()
{
    m_defaultFont;
    if(!m_defaultFont.loadFromFile(DefaultFontPath)) {
        cout << "FATAL ERROR: ResourceManager() - cannot load font: " << DefaultFontPath << endl;
    }

    m_defaultTexture = new sf::Texture();
    if(!m_defaultTexture->loadFromFile(DefaultTexturePath)) {
        cout << "FATAL ERROR: ResourceManager() - cannot load texture: " << DefaultTexturePath << endl;
    }

    m_resolution = ResolutionMedium;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Functions for getting resources////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const sf::Font& ResourceManager::getFont(StateType state)
{
    if(m_loadedFonts.size() < state + 1) {
        m_loadedFonts.resize(state + 1, nullptr);
    }
    if(m_loadedFonts[state] == nullptr) {
        auto newFont = new sf::Font();
        if(!newFont->loadFromFile(pathToFont(state))) {
            cout << "FATAL ERROR: Cannot Read Font for state: " << state << " at path: " << pathToFont(state) << endl;
            return m_defaultFont;
        }
        m_loadedFonts[state] = newFont;

    }
    return *m_loadedFonts[state];
}

const sf::Texture* ResourceManager::getTexture(StateType stateType)
{
    if(m_loadedStateTextures.size() < stateType + 1) {
        m_loadedStateTextures.resize(stateType + 1, nullptr);
    }
    if(m_loadedStateTextures[stateType] == nullptr) {
        // if there is no texture for query State in cache then load it from file
        auto newTexture = new sf::Texture();
        if(!newTexture->loadFromFile(pathToTexture(stateType))) {
            cout << "FATAL ERROR: Cannot Read Texture for State: " << stateType << " at path: " << pathToTexture(stateType) << endl;
            return m_defaultTexture;
        }
        m_loadedStateTextures[stateType] = newTexture;

    }
    return m_loadedStateTextures[stateType];
}

const sf::Texture* ResourceManager::getTexture(ObjectType objectType, unsigned number /* = 1 */)
{
    if(m_loadedObjectTextures.size() < objectType + 1) {
        std::vector<sf::Texture*> emptyVector;
        m_loadedObjectTextures.resize(objectType + 1, emptyVector);
    }
    if(m_loadedObjectTextures[objectType].size() < number) {
        m_loadedObjectTextures[objectType].resize(number, nullptr);
    }
    if(m_loadedObjectTextures[objectType][number - 1] == nullptr) {
        // if there is no texture for query object in cache then load it from file
        auto newTexture = new sf::Texture();
        if(!newTexture->loadFromFile(pathToTexture(objectType, number))) {
            cout << "FATAL ERROR: Cannot Read Texture for object: " << objectType << " at path: " << pathToTexture(objectType, number) << endl;
            return m_defaultTexture;
        }
        m_loadedObjectTextures[objectType][number - 1] = newTexture;
    }
    return m_loadedObjectTextures[objectType][number - 1];
}

Level ResourceManager::getLevel(const unsigned& levelNumber)
{
    if(m_loadedLevels.size() < levelNumber) {
        m_loadedLevels.resize(levelNumber, nullptr);
    }
    if(m_loadedLevels[levelNumber - 1] == nullptr) {
        auto newLevel = new Level(levelNumber, BricksDistance, BricksCountOnPlayer);
        newLevel->loadFromSpec(pathToLevel(levelNumber));
        m_loadedLevels[levelNumber - 1] = newLevel;
    }
    return *m_loadedLevels[levelNumber - 1];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////Functions for path creating//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string ResourceManager::pathToFont(StateType state)
{
    return DefaultFontPath;
}

std::string ResourceManager::pathToTexture(StateType stateType)
{
    std::string path = TexturesDir;
    path.append(toString(m_resolution) + PathSeparator)
        .append(toString(stateType));
    return path;
}

std::string ResourceManager::pathToTexture(ObjectType objectType, unsigned number)
{
    std::string path = TexturesDir;
    path.append(toString(m_resolution) + PathSeparator)
        .append(toString(objectType) + PathSeparator)
        .append(toString(number));
    return path;
}

std::string ResourceManager::pathToLevel(unsigned levelNumber)
{
    return LevelSpecsDir + toString(levelNumber);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Functions for converting integral types to std::string/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string ResourceManager::toString(StateType stateType)
{
    switch(stateType) {
        case StateTypeMainMenu:
            return "main_menu_bg";
        case StateTypeGaming:
            return "game_scene_bg";
        case StateTypePaused:
        case StateTypeLevelEnd:
        case StateTypeEntireGameWon:
            return "popup_bg";
    }
}

std::string ResourceManager::toString(ObjectType objectType)
{
    switch(objectType) {
        case ObjectTypePaddle:
            return "Paddles";
        case ObjectTypeBall:
            return "Balls";
        case ObjectTypeBorder:
            return "Borders";
        case ObjectTypeBrick:
            return "Bricks";
        case ObjectTypeLevel:
            return "Levels";
    }
}

std::string ResourceManager::toString(Resolution resolution)
{
    switch(resolution) {
        case ResolutionHigh:
            return "ResolutionHigh";
        case ResolutionMedium:
            return "ResolutionMedium";
        case ResolutionLow:
            return "ResolutionLow";
    }
}

std::string ResourceManager::toString(unsigned number)
{
    return std::to_string(number);
}
