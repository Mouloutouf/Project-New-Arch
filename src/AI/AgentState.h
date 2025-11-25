//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_STATE_H
#define NEWARCH_STATE_H

struct Telegram;

template<class AgentType>
class AgentState
{
public:
    virtual ~AgentState() = default;

    virtual void Enter(AgentType*) = 0;

    virtual void Execute(AgentType*) = 0;

    virtual void Exit(AgentType*) = 0;

    virtual bool OnNotification(AgentType*, const Telegram&) = 0;
};

#endif //NEWARCH_STATE_H
