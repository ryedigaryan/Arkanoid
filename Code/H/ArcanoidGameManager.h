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
    virtual void engine_willLoadLevel();
    virtual void engine_levelLoaded();
    virtual void engine_willStartLevel();
    virtual void engine_levelStarted() { /* OK */ }
    virtual void engine_paused();
    virtual void engine_unpaused();
    virtual void engine_levelEnded(bool hasWon);

    // GameObjectDelegate overriden functions
    virtual void go_delegateSetted(const GameObject* go);
    virtual void go_moved(unsigned go_id, const Point& go_position);
    virtual void go_sizeChanged(unsigned go_id, const Size& go_size);
    virtual void go_healthChanged(unsigned go_id, int go_health, int go_healthChange) {/* not yet implemented */}
    virtual void go_isAtPeaceNow(unsigned go_id);

    // ArcanoidGameDrawerDelegate overriden functions
    virtual void drawer_startPressed();
    virtual void drawer_donePressed();
    virtual void drawer_mainMenuPressed();
    virtual void drawer_pausePressed();
    virtual void drawer_unpausePressed();

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

    ArcanoidGameEngine* m_engine;
    ArcanoidGameDrawer* m_drawer;
    int m_currentLevelNumber = 0;
    bool m_hasWonPreviousLevel = true;

private:
    bool hasReachedLastLevel();

private: // making singleton
    ArcanoidGameManager() {}
public: // making singleton
    ArcanoidGameManager(ArcanoidGameManager const&) = delete;
    void operator=(ArcanoidGameManager const&) = delete;
};

#endif //ARCANOID_ARCANOIDGAMEMANAGER_H
