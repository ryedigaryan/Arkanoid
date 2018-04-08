//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_GAMINGSTATE_H
#define ARCANOID_GAMINGSTATE_H

#include "State.h"
#include "Interfaces/GameEngineDelegate.h"
#include "PausedState.h"
#include "LevelEndState.h"
#include "Definitions/CommonDefinitions.h"

class GamingState : public State, public GameEngineDelegate, public GameObjectDelegate {
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
    void go_delegateSet(const GameObject* go)                                 override {
        m_gameData->drawer->drawObject(sf::Vector2f(go->get(AxisX), go->get(AxisY)), sf::Vector2f(go->get(DimensionWidth), go->get(DimensionHeight)), m_gameData->resourceManager->getTexture(go->getType()));
//        m_gameData->drawer->displayChanges();
//        m_gameData->drawer->displayChanges();
    }
    void go_healthChanged(unsigned go_id, int go_health, int go_healthChange) override {}
    void go_isAtPeaceNow(unsigned go_id)                                      override {}
    void go_moved(unsigned go_id, const Point &go_position)                   override {}
    void go_sizeChanged(unsigned go_id, const Size &go_size)                  override {}

private:
    unsigned m_currentLevelNumber;
    const unsigned m_firstLevelNumber;
    const unsigned m_lastLevelNumber;
    LevelState m_currentLevelState;

    void setEngineLevel(const unsigned& levelNumber);
};

#endif //ARCANOID_GAMINGSTATE_H
