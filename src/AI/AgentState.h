//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_STATE_H
#define NEWARCH_STATE_H

struct Telegram;

template<class EntityType>
class AgentState
{
public:
    virtual ~AgentState() = default;

    virtual void Enter(EntityType*) = 0;

    virtual void Execute(EntityType*) = 0;

    virtual void Exit(EntityType*) = 0;

    virtual bool OnNotification(EntityType*, const Telegram&) = 0;
};

#endif //NEWARCH_STATE_H