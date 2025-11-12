//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_AGENT_H
#define NEWARCH_AGENT_H

#include <string>

#include "../Messaging/Telegram.h"

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