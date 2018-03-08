//
// Created by ryedigaryan on 2/26/2018.
//

#include "ArcanoidGameManager.h"
#include <iostream>
#include <afxres.h>

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
    m_drawer->drawMenu();
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
    m_drawer->drawAllGameObjects(Show);
    m_drawer->clearScreen(NotShow);
    m_drawer->drawAllGameObjects(Show);
    Sleep(10000);
    m_engine->startLevel();
    sf::Clock clock;
    sf::RenderWindow* gameWindow = m_drawer->getMainWindow();
    while(gameWindow->isOpen()) {
        sf::Event event;
        while(gameWindow->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    gameWindow->close();
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            m_engine->movePlayer(Side::Left);
                        case sf::Keyboard::Right:
                            m_engine->movePlayer(Side::Right);
                        default:
                            break;
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
    m_drawer->drawMenu(Show);
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
    m_drawer->clearScreen();
    m_drawer->drawLoading();
}

void ArcanoidGameManager::engine_levelLoaded()
{
    m_drawer->drawLevelStartInfo(m_currentLevelNumber);
}

void ArcanoidGameManager::engine_willStartLevel()
{
    m_drawer->clearScreen();
}

void ArcanoidGameManager::engine_paused()
{
    m_drawer->drawLevelStartInfo(m_currentLevelNumber, m_engine->getProgress());
}

void ArcanoidGameManager::engine_unpaused()
{
    //TODO hide popup
    //m_drawer->levelStart(Hide, m_currentLevelNumber);
}

void ArcanoidGameManager::engine_levelEnded(bool hasWon)
{
    if (hasWon && hasReachedLastLevel()) {
        m_drawer->drawGameWon();
        return;
    }
    m_drawer->drawLevelEndInfo(hasWon);
}

void ArcanoidGameManager::go_delegateSetted(const GameObject* go)
{
    // already in correct drawing layer
    sf::Vector2f go_position = sf::Vector2f(go->get(X), go->get(Y));
    sf::Vector2f go_size = sf::Vector2f(go->get(Width), go->get(Height));
    m_drawer->drawObject(go->getIdentifier(), go_position, go_size, go->m_texturePath, NotShow);
}

void ArcanoidGameManager::go_moved(unsigned go_id, const Point& go_position)
{
    m_drawer->moveObject(go_id, sf::Vector2f(go_position.x, go_position.y));
    //m_drawer->moveObject(go_id, go_position);
}

void ArcanoidGameManager::go_sizeChanged(unsigned go_id, const Size & go_size)
{
    m_drawer->resizeObject(go_id, sf::Vector2f(go_size.width, go_size.height));
}

void ArcanoidGameManager::go_isAtPeaceNow(unsigned go_id)
{
    m_drawer->deleteObject(go_id);
}
