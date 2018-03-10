//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_ARCANOIDGAMEMANAGER_H
#define ARCANOID_ARCANOIDGAMEMANAGER_H


#include "Definitions.h"

#include "Interfaces/GameObjectDelegate.h"
#include "ArcanoidGameEngine.h"
#include "Interfaces/ArcanoidGameEngineDelegate.h"
#include "ArcanoidGameDrawer.h"
#include "Interfaces/ArcanoidGameDrawerDelegate.h"

class ArcanoidGameManager : public ArcanoidGameEngineDelegate, public ArcanoidGameDrawerDelegate, public GameObjectDelegate {
public: // static funcitons
    static ArcanoidGameManager& getManager() {
        static ArcanoidGameManager  singletonInstance;
        return singletonInstance;
    }

public: // overrides
    // ArcanoidGameEngineDelegate overriden functions
    void engine_willLoadLevel() override;
    void engine_levelLoaded() override;
    void engine_willStartLevel() override;
    void engine_levelStarted() override { /* OK */ }
    void engine_paused() override;
    void engine_unpaused() override;
    void engine_levelEnded(bool hasWon) override;

    // GameObjectDelegate overriden functions
    void go_delegateSet(const GameObject *go) override;
    void go_moved(unsigned go_id, const Point& go_position) override;
    void go_sizeChanged(unsigned go_id, const Size& go_size) override;
    void go_healthChanged(unsigned go_id, int go_health, int go_healthChange) override {/* not yet implemented */}
    void go_isAtPeaceNow(unsigned go_id) override;

    // ArcanoidGameDrawerDelegate overriden functions
    void drawer_startPressed() override;
    void drawer_donePressed() override;
    void drawer_mainMenuPressed() override;
    void drawer_pausePressed() override;
    void drawer_unpausePressed() override;

public: // instance funcitons
    // Step 1 - add levels
    void addLevelSpecPath(string path);
    void addAllLevelSpecsInPath(string path, string extension, int count);

    // Step 2 - add Engine and Drawer
    void setEngine(ArcanoidGameEngine* engine);
    void setDrawer(ArcanoidGameDrawer* drawer);

    // Step 3 - start game  ... actually this is only draws a menu
    void startGame();

private:
    list<string> m_levelSpecPaths;
    list<string>::iterator m_currentLevelSpecPath;

    ArcanoidGameEngine* m_engine = nullptr;
    ArcanoidGameDrawer* m_drawer = nullptr;
    int m_currentLevelNumber = 0;
    bool m_hasWonPreviousLevel = true;

private:
    bool hasReachedLastLevel();
    sf::Vector2f m_gameSceneOffset;

private: // making singleton
    ArcanoidGameManager() = default;
public: // making singleton
    ArcanoidGameManager(ArcanoidGameManager const&) = delete;
    void operator=(ArcanoidGameManager const&) = delete;
};

#endif //ARCANOID_ARCANOIDGAMEMANAGER_H
