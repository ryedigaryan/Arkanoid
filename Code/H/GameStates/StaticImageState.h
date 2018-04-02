//
// Created by ryedigaryan on 4/2/2018.
//

#ifndef ARCANOID_STATICIMAGESTATE_H
#define ARCANOID_STATICIMAGESTATE_H

#include "State.h"

class StaticImageState : public State {
public:
    StaticImageState(GameData* gameData, sf::Keyboard::Key popKey);

    void init()        override;
    void handleInput() override;
    virtual void update()      = 0;
    void pause()       override;
    void resume()      override;

protected:
    bool m_needsRedraw;
    const sf::Keyboard::Key m_popKey;
};

#endif //ARCANOID_STATICIMAGESTATE_H
