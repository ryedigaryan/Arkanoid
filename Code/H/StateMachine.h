//
// Created by ruben on 3/25/2018.
//

#ifndef ARCANOID_STATEMACHINE_H
#define ARCANOID_STATEMACHINE_H

#include <stack>
#include "GameStates/State.h"

class StateMachine {
public:
    State* getActiveState();
    void popActiveState();
    void pushState(State *newState, bool isReplacing = false);
    size_t statesCount();

private:
    std::stack<State*> m_states;
};

#endif //ARCANOID_STATEMACHINE_H
