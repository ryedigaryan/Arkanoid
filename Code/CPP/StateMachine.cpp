//
// Created by ruben on 3/25/2018.
//

#include "StateMachine.h"

State* StateMachine::getActiveState() {
    return m_states.top();
}

void StateMachine::popActiveState() {
    m_states.pop();
}

void StateMachine::pushState(State *newState, bool isReplacing) {
    if(isReplacing) {
        m_states.pop();
    }
    m_states.push(newState);
}

size_t StateMachine::statesCount() {
    return m_states.size();
}
