//
// Created by ryedigaryan on 3/17/2018.
//

#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    m_defaultTexture = new sf::Texture();
    if(!m_defaultTexture->loadFromFile(DefaultTexturePath)) {
        cout << "FATAL ERROR - CANNOT LOAD DEFAULT TEXTURE FROM PATH: " << DefaultTexturePath << endl;
        exit(SATANAYI_INT);
    }
    loadAllTextures();

    m_defaultFont = new sf::Font();
    if(!m_defaultFont->loadFromFile(DefaultFontPath)) {
        cout << "FATAL ERROR - CANNOT LOAD DEFAULT FONT FROM PATH: " << DefaultFontPath << endl;
        exit(SATANAYI_INT);
    }
    loadAllFonts();
}

void AssetsManager::loadAllTextures() {
    for(GameObjectType goType = TBrick; goType != TBorder; goType++) {
        loadTextures(goType);
    }
}

void AssetsManager::loadTextures(GameObjectType goType) {
    switch (goType) {
        case TBrick:
                loadTexture(BricksPath, BrickTexturesCount);
            break;
        case TPaddle:
                loadTexture(PaddlesPath, PaddleTexturesCount);
            break;
        case TBall:
                loadTexture(BallsPath, BallTexturesCount);
            break;
        case TBorder:
                loadTexture(BordersPath, BorderTexturesCount);
        default:
            break;
    }
}

void AssetsManager::loadTexture(const std::string& directory, int count) {
    for(int i = 0; i < count; i++) {
        auto texture = new sf::Texture();
        if (!texture->loadFromFile(ConstructPathToTexture(directory, std::to_string(i)))) {
            texture = m_defaultTexture;
        }
        m_textures[]
    }
}

void AssetsManager::loadAllFonts() {
    
}
