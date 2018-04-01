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
    explicit GamingState(GameData *gameData, unsigned startLevelNumber = FirstLevelNumber);

    // State virtual functions
    void init()        override;
    void handleInput() override;
    void update()      override;
    void pause()       override;
    void resume()      override;

    // GameObjectDelegate virtual functions
    void go_delegateSet(const GameObject *go)                                 override {}
    void go_healthChanged(unsigned go_id, int go_health, int go_healthChange) override {}
    void go_isAtPeaceNow(unsigned go_id)                                      override {}
    void go_moved(unsigned go_id, const Point &go_position)                   override {}
    void go_sizeChanged(unsigned go_id, const Size &go_size)                  override {}

private:
    unsigned m_currentLevelNumber;
    LevelState m_currentLevelState;
};

#endif //ARCANOID_GAMINGSTATE_H
