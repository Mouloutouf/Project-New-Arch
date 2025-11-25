//
// Created by maxdu on 14/11/2025.
//

#ifndef NEWARCH_WIFE_H
#define NEWARCH_WIFE_H

#include "Locations.h"
#include "Agent.h"
#include "StateMachine.h"
#include "WifeStates.h"

class Wife : public Agent
{
public:
    Wife(const std::string& name)
        : Agent(name), m_Location(Base), m_IsCooking(false)
    {
        m_pStateMachine = new StateMachine(this);

        m_pStateMachine->SetCurrentState(ManageBase::Instance());
        m_pStateMachine->SetGlobalState(WifeGlobalState::Instance());
    }

    ~Wife() override { delete m_pStateMachine; }

    void Update() override;

    bool HandleMessage(const Telegram& message) override;

    StateMachine<Wife>* GetStateMachine() const { return m_pStateMachine; }

    LocationType Location() const { return m_Location; }
    void ChangeLocation(LocationType location) { m_Location = location; }

    bool IsCooking() const { return m_IsCooking; }
    void SetIsCooking(bool value) { m_IsCooking = value; }

private:
    StateMachine<Wife>* m_pStateMachine;

    LocationType m_Location;

    bool m_IsCooking;
};

#endif //NEWARCH_WIFE_H
