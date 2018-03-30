//
// Created by ruben on 3/25/2018.
//

#include "StateMachine.h"
#include "GameStates/State.h"

State* StateMachine::getActiveState() {
    return m_states.top();
}

void StateMachine::popActiveState() {
    getActiveState()->pause();
    m_states.pop();
    getActiveState()->resume();
}

void StateMachine::pushState(State *newState, bool isReplacing /* = false */) {
    if(isReplacing) {
        popActiveState();
    }
    m_states.push(newState);
}

size_t StateMachine::statesCount() {
    return m_states.size();
}

StateMachine::~StateMachine() {
    while(!m_states.empty()) {
        delete m_states.top();
        m_states.pop();
    }
}
