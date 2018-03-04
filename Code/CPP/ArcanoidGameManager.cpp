//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameManager.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void ArcanoidGameManager::addLevelSpecPath(string path)
{
    m_levelSpecPaths.push_back(path);
}

void ArcanoidGameManager::addAllLevelSpecsInPath(string path, string extension, int count) {
    for (int i = 1; i <= count; i++) {
        string levelPath(path);
        levelPath.append(PathSeparator);		// append slash (/)
        levelPath.append(std::to_string(i));	// append name of level to path
        levelPath.append(ExtensionSeparator);	// append dot (.)
        levelPath.append(extension);			// append extension of level to path (lvl)
        cout << "ADDING LVL: " << levelPath << endl;
        addLevelSpecPath(levelPath);			// add path to all paths
    }
}

void ArcanoidGameManager::setEngine(ArcanoidGameEngine* engine)
{
    m_engine = engine;
    m_engine->setGameObjectDelegate(this);
    m_engine->setDelegate(this);
}

void ArcanoidGameManager::setDrawer(ArcanoidGameDrawer* drawer)
{
    m_drawer = drawer;
    m_drawer->setDelegate(this);
}

void ArcanoidGameManager::startGame()
{
    cout << "Starting Game" << endl;
    m_currentLevelSpecPath = m_levelSpecPaths.begin(); // get the first level spec
    m_currentLevelNumber++; // setting level number to 1
    m_drawer->setCurrentDrawingLayer(LayerMenu);
    m_drawer->menu(Show);
}

bool ArcanoidGameManager::hasReachedLastLevel()
{
    return m_currentLevelSpecPath == m_levelSpecPaths.end();
}

void ArcanoidGameManager::drawer_startPressed()
{
    cout << "starting level: " << *m_currentLevelSpecPath << endl;
    m_engine->prepareLevel(*m_currentLevelSpecPath);
}

void ArcanoidGameManager::drawer_donePressed()
{
    m_engine->startLevel();
    sf::Clock clock;
    while(m_drawer->getMainWindow().isOpen()) {
        sf::Event event;
        while(m_drawer->getMainWindow().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_drawer->getMainWindow().close();
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            m_engine->movePlayer(Side::Left);
                        case sf::Keyboard::Right:
                            m_engine->movePlayer(Side::Right)
                    }
                case sf::Event::KeyReleased:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                        case sf::Keyboard::Right:
                            m_engine->stopPlayerMoving();
                        default:
                            break;
                    }
                case sf::Event::Resized:break;
                default:
                    break;
            }
        }
        if (clock.getElapsedTime().asSeconds() > FrameDuration) {
            m_engine->process();
        }
    }
}

void ArcanoidGameManager::drawer_mainMenuPressed()
{
    m_drawer->setCurrentDrawingLayer(LayerMenu);
    m_drawer->menu(Show);
}

void ArcanoidGameManager::drawer_pausePressed()
{
    m_engine->pause();
}

void ArcanoidGameManager::drawer_unpausePressed()
{
    m_engine->unpause();
}

void ArcanoidGameManager::engine_willLoadLevel()
{
    if (m_currentLevelNumber == 1) {
        m_drawer->menu(Hide);
    }
    else {
        m_drawer->levelEnd(Hide);
    }
    m_drawer->setCurrentDrawingLayer(LayerLoading);
    m_drawer->loading(Show);
    // set drawing layer to game objects because now game objects will be created
    m_drawer->setCurrentDrawingLayer(LayerGameObject);
}

void ArcanoidGameManager::engine_levelLoaded()
{
    m_drawer->setCurrentDrawingLayer(LayerLoading);
    m_drawer->loading(Hide);
    m_drawer->setCurrentDrawingLayer(LayerLevelInfo);
    m_drawer->levelStart(Show, m_currentLevelNumber);
}

void ArcanoidGameManager::engine_willStartLevel()
{
    m_drawer->levelStart(Hide);
    // now game objects will move
    m_drawer->setCurrentDrawingLayer(LayerGameObject);
}

void ArcanoidGameManager::engine_paused()
{
    m_drawer->setCurrentDrawingLayer(LayerLevelInfo);
    m_drawer->levelStart(Show, m_currentLevelNumber, m_engine->getProgress());
}

void ArcanoidGameManager::engine_unpaused()
{
    m_drawer->levelStart(Hide, m_currentLevelNumber);
}

void ArcanoidGameManager::engine_levelEnded(bool hasWon)
{
    if (hasWon && hasReachedLastLevel()) {
        m_drawer->gameWon(Show);
        return;
    }
    m_drawer->levelEnd(Show, hasWon);
}

void ArcanoidGameManager::go_delegateSetted(const GameObject* go)
{
    // already in correct drawing layer
    m_drawer->drawObject(go->getIdentifier(), go->getPosition(), go->getSize(), go->m_texturePath, Hide);
}

void ArcanoidGameManager::go_moved(unsigned go_id, const Point& go_position)
{
    m_drawer->redrawObject(go_id, go_position);
    //m_drawer->moveObject(go_id, go_position);
}

void ArcanoidGameManager::go_sizeChanged(unsigned go_id, const Size & go_size)
{
    m_drawer->redrawObject(go_id, go_size);
}

void ArcanoidGameManager::go_isAtPeaceNow(unsigned go_id)
{
    m_drawer->deleteObject(go_id);
}
