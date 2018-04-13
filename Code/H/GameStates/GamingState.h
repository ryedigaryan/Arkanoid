//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMINGSTATE_H
#define ARCANOID_GAMINGSTATE_H

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
    void pause()       override;
    void resume()      override;

    // GameObjectDelegate virtual functions
    void go_healthChanged(unsigned go_id, int go_health, int go_healthChange) override;
    void go_isAtPeaceNow(unsigned go_id)                                      override;
    void go_moved(unsigned go_id, const Point &go_position)                   override;
    void go_sizeChanged(unsigned go_id, const Size &go_size)                  override;

    // ArkanoidEngineDelegate virtual functions
    void engine_levelSet(const Level& level) override;

private: // private data
    sf::Vector2f m_scaleFactor;
    unsigned m_currentLevelNumber;
    const unsigned m_firstLevelNumber;
    const unsigned m_lastLevelNumber;
    LevelState m_currentLevelState;
    // model ID is the index
    // view ID is the value
    std::vector<unsigned> m_model2ViewBindings;
    unsigned m_bingingsOffset;

private: // helper functions
    void setEngineLevel(const unsigned& levelNumber);
    void calculateScaling();
    sf::Vector2f scale(const Point& position);
    sf::Vector2f scale(const Size& position);
    void setViewForModel(unsigned modelID, unsigned viewiD);
    unsigned getViewOfModel(unsigned modelID);
};

#endif //ARCANOID_GAMINGSTATE_H
