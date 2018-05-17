//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMINGSTATE_H
#define ARCANOID_GAMINGSTATE_H

#include <Timer.h>
#include "State.h"
#include "Interfaces/ArkanoidEngineDelegate.h"
#include "PausedState.h"
#include "LevelEndState.h"
#include "Definitions/CommonDefinitions.h"

class GamingState : public State, public ArkanoidEngineDelegate, public GameObjectDelegate {
public:
    /// @param startLevelNumber can be used to continue game from lost level
    GamingState(GameData* gameData, unsigned startLevelNumber, unsigned lastLevelNumber);

    // State virtual functions
    void init()        override;
    void handleInput() override;
    void update()      override;
    void draw()        override;
    void pause()       override;
    void resume()      override;

    // GameObjectDelegate virtual functions
    void go_healthChanged(unsigned goId, int goHealth, int goHealthChange) override;
    void engine_goIsAtPieceNow(const unsigned& goId)                       override;
    void go_moved(unsigned goId, const float& dx, const float& dy)         override;
    void go_sizeChanged(unsigned goId, const Size& goSize)                 override;

    // ArkanoidEngineDelegate virtual function
    void engine_levelSet(const Level& level)                               override;

private: // private data
    Timer m_timer;
    sf::Vector2f m_scaleFactor;
    unsigned m_currentLevelNumber;
    const unsigned m_firstLevelNumber;
    const unsigned m_lastLevelNumber;
    LevelState m_currentLevelState;
    // model ID is the index
    // view ID is the value
    std::vector<unsigned> m_model2ViewBindings;
    unsigned m_bindingsOffset;

private: // helper functions
    void setEngineLevel(const unsigned& levelNumber);
    void calculateScaling();
    sf::Vector2f scale(const Point& position);
    sf::Vector2f scale(const Size& position);
    sf::Vector2f scale(const float& x, const float& y);
    void setViewForModel(unsigned modelID, unsigned viewID);
    unsigned getViewOfModel(unsigned modelID);
};

#endif //ARCANOID_GAMINGSTATE_H
