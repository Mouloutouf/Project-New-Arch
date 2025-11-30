//
// Created by maxdu on 14/11/2025.
//

#include "WifeStates.h"

#include <iostream>

#include "AgentNames.h"
#include "Random.h"
#include "Utility.h"
#include "Wife.h"
#include "Messaging/MessageDispatcher.h"
#include "Messaging/Messages.h"

//-----------------------------------------------------------------------

// Global State

WifeGlobalState* WifeGlobalState::Instance()
{
    static WifeGlobalState instance;
    return &instance;
}

void WifeGlobalState::Enter(Wife* wife)
{
}

void WifeGlobalState::Execute(Wife* wife)
{
    // Randomly go inspect the storage (1 chance out of 10)
    bool isInsideStorage = wife->GetStateMachine()->IsInState(*InspectStorage::Instance());
    if (GetRandomFloat(0, 1) < 0.1 && isInsideStorage == false)
        wife->GetStateMachine()->ChangeState(InspectStorage::Instance());
}

void WifeGlobalState::Exit(Wife* wife)
{
}

bool WifeGlobalState::OnNotification(Wife* wife, const Telegram& msg)
{
    switch (msg.messageType)
    {
    case Msg_BackToBase:
        std::cout << "\n" << "Message handled by " << wife->Name() << " at time : " << CURRENT_TIME;
        std::cout << "\n" << wife->Name() << " : You're back early. Going to prepare food...";

        wife->GetStateMachine()->ChangeState(PrepareFood::Instance());

        return true;

    default:
        return false;
    }

    return false;
}

//-------------------------------------------------------------------------

ManageBase* ManageBase::Instance()
{
    static ManageBase instance;
    return &instance;
}

void ManageBase::Enter(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Going to work around the base...";
}

void ManageBase::Execute(Wife* wife)
{
    switch (GetRandomInt(0, 2))
    {
    case 0:
        std::cout << "\n" << wife->Name() << " : Planting seeds";
        break;

    case 1:
        std::cout << "\n" << wife->Name() << " : Crafting items";
        break;

    case 2:
        std::cout << "\n" << wife->Name() << " : Getting more wood";
        break;

    default: ;
    }
}

void ManageBase::Exit(Wife* wife)
{
}

bool ManageBase::OnNotification(Wife* wife, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------

InspectStorage* InspectStorage::Instance()
{
    static InspectStorage instance;
    return &instance;
}

void InspectStorage::Enter(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Going to inspect storage...";
}

void InspectStorage::Execute(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Everything under control";

    wife->GetStateMachine()->RevertToPreviousState();
}

void InspectStorage::Exit(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Leaving Storage...";
}

bool InspectStorage::OnNotification(Wife* wife, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------

PrepareFood* PrepareFood::Instance()
{
    static PrepareFood instance;
    return &instance;
}

void PrepareFood::Enter(Wife* wife)
{
    //if not already cooking put the stew in the oven
    if (!wife->IsCooking())
    {
        std::cout << "\n" << wife->Name() << " : Starting to prepare food...";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        MessageDispatcher::Instance()
            ->DispatchMessage(1.5,
            wife->Name(),
            wife->Name(),
            Msg_FoodReady,
            nullptr
        );

        wife->SetIsCooking(true);
    }
}

void PrepareFood::Execute(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Watching the oven wall";
}

void PrepareFood::Exit(Wife* wife)
{
    std::cout << "\n" << wife->Name() << " : Food is ready";
}

bool PrepareFood::OnNotification(Wife* wife, const Telegram& msg)
{
    switch (msg.messageType)
    {
    case Msg_FoodReady:
        std::cout << "\n" << "Message received by " << wife->Name() << " at time : " << CURRENT_TIME;
        std::cout << "\n" << wife->Name() << " : Here, take some food";

        MessageDispatcher::Instance()
            ->DispatchMessage(0,
            wife->Name(),
            AGENT_MINER,
            Msg_FoodReady,
            nullptr
        );

        wife->SetIsCooking(false);

        wife->GetStateMachine()->ChangeState(ManageBase::Instance());

        return true;

    default:
        return false;
    }

    return false;
}
