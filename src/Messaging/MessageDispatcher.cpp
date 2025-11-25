//
// Created by maxdu on 11/11/2025.
//

#include "MessageDispatcher.h"
#include "../AI/Agent.h"

#include <iostream>

#include "AI/AgentManager.h"

MessageDispatcher* MessageDispatcher::Instance()
{
    static MessageDispatcher instance;

    return &instance;
}

void MessageDispatcher::Discharge(Agent* pReceiver, const Telegram& telegram)
{
    bool handleResult = pReceiver->HandleMessage(telegram);

    if (handleResult == false)
        std::cout << "Message could not be handled";
}


void MessageDispatcher::DispatchMessage(double delay, std::string sender, std::string receiver, int message, void *pExtraInfo)
{
    Agent* pReceiver = AgentManager::Instance()->GetAgentByName(receiver);

    if (pReceiver == nullptr)
    {
        std::cout << "\n" << "Warning! No receiver with ID of " << receiver << " was found";
        return;
    }

    Telegram telegram(0, sender, receiver, message, pExtraInfo);

    // if there is no delay, route telegram immediately
    if (delay <= 0.0)
    {
        std::cout << "\n" << "Telegram dispatched at time: " << Clock->GetCurrentTime()
            << " by " << sender << " for " << receiver << ". Message is " << message << "";

        Discharge(pReceiver, telegram);
    }
    // else calculate the time when the telegram should be dispatched and add it to the queue
    else
    {
        double currentTime = Clock->GetCurrentTime();

        telegram.dispatchTime = currentTime + delay;

        priorityQueue.push(telegram);

        std::cout << "\n" << "Delayed telegram from " << sender << " recorded at time "
            << currentTime << " for " << receiver << ". Message is " << message << "";
    }
}

void MessageDispatcher::DispatchDelayedMessages()
{
    double currentTime = Clock->GetCurrentTime();

    //now peek at the queue to see if any telegrams need dispatching.
    //remove all telegrams from the front of the queue that have gone
    //past their sell by date
    while (priorityQueue.empty() == false &&
        priorityQueue.top().dispatchTime < currentTime &&
        priorityQueue.top().dispatchTime > 0)
    {
        //read the telegram from the front of the queue
        const Telegram& telegram = priorityQueue.top();

        //find the recipient
        Agent* pReceiver = AgentManager::Instance()->GetAgentByName(telegram.receiver);

        std::cout << "\n" << "Queued telegram ready for dispatch: Sent to "
            << telegram.receiver << ". Message is " << telegram.messageType << "";

        //send the telegram to the recipient
        Discharge(pReceiver, telegram);

        //remove it from the queue
        priorityQueue.pop();
    }
}
