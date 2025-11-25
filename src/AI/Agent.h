//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_AGENT_H
#define NEWARCH_AGENT_H

#include <string>

struct Telegram;

// TODO / Define if we want states to be singleton or if each state should be an instance which requires specific data
// TODO / Define a new diagram of state transitions for your two characters, with new states, to practice setting up the state machine
// TODO / Define if we want to have a hierarchical state machine for our agents, with generic states with more detailed states inside

class Agent
{
public:
    Agent(const std::string& name);
    virtual ~Agent() = default;

    virtual void Update() = 0;
    virtual bool HandleMessage(const Telegram& message) = 0;

    std::string Name() const { return m_Name; }

private:
    std::string m_Name;
};

#endif //NEWARCH_AGENT_H
