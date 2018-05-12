//
// Created by ruben on 3/25/2018.
//

#include "StateMachine.h"
#include "GameStates/State.h"

State* StateMachine::getActiveState()
{
    return m_states.top();
}

void StateMachine::popActiveState()
{
    getActiveState()->pause();
    delete m_states.top();
    m_states.pop();
    getActiveState()->resume();
}

void StateMachine::pushState(State* newState, bool isReplacing /* = false */)
{
    if(!m_states.empty()) {
        if (isReplacing) {
            popActiveState();
        } else {
            getActiveState()->pause();
        }
    }
    m_states.push(newState);
    newState->init();
}

size_t StateMachine::statesCount()
{
    return m_states.size();
}

StateMachine::~StateMachine()
{
    while(!m_states.empty()) {
        delete m_states.top();
        m_states.pop();
    }
}
