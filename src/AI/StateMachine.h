//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_STATEMACHINE_H
#define NEWARCH_STATEMACHINE_H

#include <typeinfo>

#include "AgentState.h"

template <class AgentType>
class StateMachine
{
public :
    StateMachine(AgentType* pOwner)
        : m_pOwner(pOwner), m_pCurrentState(nullptr), m_pPreviousState(nullptr), m_pGlobalState(nullptr)
    {
    }

    virtual ~StateMachine() = default;

    void SetCurrentState(AgentState<AgentType>* pState) { m_pCurrentState = pState; }
    void SetGlobalState(AgentState<AgentType>* pState) { m_pGlobalState = pState; }
    void SetPreviousState(AgentState<AgentType>* pState) { m_pPreviousState = pState; }

    void Update()
    {
        if (m_pGlobalState != nullptr)
            m_pGlobalState->Execute(m_pOwner);

        if (m_pCurrentState != nullptr)
            m_pCurrentState->Execute(m_pOwner);
    }

    bool HandleNotification(const Telegram& notification)
    {
        if (m_pCurrentState && m_pCurrentState->OnNotification(m_pOwner, notification))
            return true;

        if (m_pGlobalState && m_pGlobalState->OnNotification(m_pOwner, notification))
            return true;

        return false;
    }

    void ChangeState(AgentState<AgentType>* pNewState)
    {
        if (pNewState == nullptr)
            return; // Add an error message

        m_pPreviousState = m_pCurrentState;

        m_pCurrentState->Exit(m_pOwner);

        m_pCurrentState = pNewState;

        m_pCurrentState->Enter(m_pOwner);
    }

    void RevertToPreviousState()
    {
        ChangeState(m_pPreviousState);
    }

    bool IsInState(const AgentState<AgentType>& pState) const
    {
        return typeid(*m_pCurrentState) == typeid(pState);
    }

    AgentState<AgentType>* CurrentState() const { return m_pCurrentState; }
    AgentState<AgentType>* GlobalState() const { return m_pGlobalState; }
    AgentState<AgentType>* PreviousState() const { return m_pPreviousState; }

private:
    AgentType* m_pOwner;

    AgentState<AgentType>* m_pCurrentState;

    AgentState<AgentType>* m_pPreviousState;

    AgentState<AgentType>* m_pGlobalState;
};

#endif //NEWARCH_STATEMACHINE_H
