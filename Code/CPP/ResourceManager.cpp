//
// Created by ryedigaryan on 3/29/2018.
//

#include "ResourceManager.h"

const Resource MainMenuFont("Resources/Fonts/default");
const Resource LevelInfoFont("Resources/Fonts/default");

const Resource MainMenuBackground("Resources/Textures/main_menu_bg");
const Resource LevelInfoBackground("Resources/Textures/popup_bg");
const Resource GameSceneBackground("Resources/Textures/game_scene_bg");
const Resource BallTexture("Resources/Textures/Balls/1");
const Resource BorderTexture("Resources/Textures/Borders/1");
const Resource Paddle1Texture("Resources/Textures/Paddles/1");
const Resource Paddle2Texture("Resources/Textures/Paddles/2");
const Resource Paddle3Texture("Resources/Textures/Paddles/3");
const Resource Brick1Texture("Resources/Textures/Bricks/1");
const Resource Brick2Texture("Resources/Textures/Bricks/2");
const Resource Brick3Texture("Resources/Textures/Bricks/3");
const Resource Brick4Texture("Resources/Textures/Bricks/4");
const Resource Brick5Texture("Resources/Textures/Bricks/5");
const Resource Level1("Resources/LevelSpecs/1.lvl");
const Resource Level2("Resources/LevelSpecs/2.lvl");
const Resource Level3("Resources/LevelSpecs/3.lvl");
const Resource Level4("Resources/LevelSpecs/4.lvl");
const Resource Level5("Resources/LevelSpecs/5.lvl");
const Resource Level6("Resources/LevelSpecs/6.lvl");

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

    m_defaultTexture = new sf::Texture();
    if(!m_defaultTexture->loadFromFile(DefaultTexturePath)) {
        cout << "FATAL ERROR: ResourceManager() - cannot load texture: " << DefaultTexturePath << endl;
    }

    m_loadedFonts.resize(FontReservationSize, nullptr);
    m_loadedTextures.resize(TextureReservationSize, nullptr);
}

// as the sf::Font and sf::Texture have no common interface which would help to load them, I created 2 separate functions for loading
const sf::Font& ResourceManager::getFont(Resource resource)
{
    if(m_loadedFonts[resource.id] == nullptr) {
        // if resource is not in cache then load it to cache
        auto font = new sf::Font();
        if(!font->loadFromFile(resource.path)) {
            cout << "Returning default font! Cause: cannot load font: " << resource.path << endl;
            // if font cannot be loaded then return default font
            return m_defaultFont;
        }
        // if font loaded successfully then store it in cache
        m_loadedFonts[resource.id] = font;
    }
    return *m_loadedFonts[resource.id];
}

const sf::Texture* ResourceManager::getTexture(Resource resource)
{
    if(m_loadedTextures[resource.id] == nullptr) {
        // if resource is not in cache then load it to cache
        auto texture = new sf::Texture();
        if(!texture->loadFromFile(resource.path)) {
            cout << "Returning default texture! Cause: cannot load texture: " << resource.path << endl;
            // if font cannot be loaded then return default texture
            return m_defaultTexture;
        }
        // if texture loaded successfully then store it in cache
        m_loadedTextures[resource.id] = texture;
    }
    return m_loadedTextures[resource.id];
}

Level& ResourceManager::getLevel(const unsigned& number)
{
    const Resource resource = getResource(T_Level, number);
    // every time we load level from file
    auto level = new Level();
    level->loadFromSpec(resource.path);
    return *level;
}

const Resource ResourceManager::getResource(ResourceType type, int number)
{
    switch(type) {
        case T_Paddle:
            switch(number) {
                case 1:
                    return Paddle1Texture;
                case 2:
                    return Paddle2Texture;
                case 3:
                    return Paddle3Texture;
            }
        case T_Ball:
            switch(number) {
                case 1:
                    return BallTexture;
            }
        case T_Border:
            switch(number) {
                case 1:
                    return BorderTexture;
            }
        case T_Brick:
            switch(number) {
                case 1:
                    return Brick1Texture;
                case 2:
                    return Brick2Texture;
                case 3:
                    return Brick3Texture;
                case 4:
                    return Brick4Texture;
                case 5:
                    return Brick5Texture;
            }
        case T_Level:
            switch(number) {
                case 1:
                    return Level1;
                case 2:
                    return Level2;
                case 3:
                    return Level3;
                case 4:
                    return Level4;
                case 5:
                    return Level5;
                case 6:
                    return Level6;
            }
    }
}
