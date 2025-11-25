//
// Created by maxdu on 11/11/2025.
//

#ifndef NEWARCH_MESSAGEDISPATCHER_H
#define NEWARCH_MESSAGEDISPATCHER_H

#include <queue>

#include "Telegram.h"

class Agent;

// Singleton class
class MessageDispatcher
{
public:
    // deleted copy constructor and assignment operator
    MessageDispatcher(const MessageDispatcher&) = delete;
    MessageDispatcher& operator=(const MessageDispatcher&) = delete;

    // static instance of this class
    static MessageDispatcher* Instance();

    void DispatchMessage(double delay, std::string sender, std::string receiver, int message, void* pExtraInfo);

    void DispatchDelayedMessages();

private:
    // private constructor
    MessageDispatcher()
    {
    }

    static void Discharge(Agent* pReceiver, const Telegram& telegram);

    std::priority_queue<Telegram> priorityQueue;
};

#endif //NEWARCH_MESSAGEDISPATCHER_H