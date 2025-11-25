//
// Created by maxdu on 12/11/2025.
//

#include "MinerStates.h"

#include <iostream>

#include "AgentNames.h"
#include "Miner.h"
#include "Messaging/MessageDispatcher.h"
#include "Messaging/Messages.h"

//------------------------------------------------------------------------

EnterCaveAndMineBlocks* EnterCaveAndMineBlocks::Instance()
{
    static EnterCaveAndMineBlocks instance;
    return &instance;
}

void EnterCaveAndMineBlocks::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Cave)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Going to the Cave...";
        pMiner->ChangeLocation(Cave);
    }
}

void EnterCaveAndMineBlocks::Execute(Miner* pMiner)
{
    // Mine for blocks while increasing fatigue
    pMiner->AddBlocksInInventory(1);
    pMiner->IncreaseFatigue();

    std::cout << "\n" << pMiner->Name() << " : " << "Mining for blocks";

    // Switch to deposit blocks if at max capacity
    if (pMiner->IsAtMaximumInventory())
        pMiner->GetStateMachine()->ChangeState(GoToStorageAndDepositBlocks::Instance());

    // Switch to go to village to get water if thirsty
    if (pMiner->IsThirsty())
        pMiner->GetStateMachine()->ChangeState(GoToVillageAndDrinkWater::Instance());
}

void EnterCaveAndMineBlocks::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Leaving the Cave with a stack of blocks...";
}

bool EnterCaveAndMineBlocks::OnNotification(Miner* pMiner, const Telegram& message)
{
    return false;
}

//------------------------------------------------------------------------

GoToStorageAndDepositBlocks* GoToStorageAndDepositBlocks::Instance()
{
    static GoToStorageAndDepositBlocks instance;
    return &instance;
}

void GoToStorageAndDepositBlocks::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Storage)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Going to the Storage...";
        pMiner->ChangeLocation(Storage);
    }
}

void GoToStorageAndDepositBlocks::Execute(Miner* pMiner)
{
    // Deposit blocks in storage and clear inventory
    pMiner->AddBlocksInStorage(pMiner->BlocksInInventory());
    pMiner->SetBlocksInInventory(0);

    std::cout << "\n" << pMiner->Name() << " : " << "Depositing blocks. Total storage : " << pMiner->BlocksInStorage();

    // Return to base if enough blocks in storage
    if (pMiner->BlocksInStorage() >= BLOCKS_MAX_WORKLOAD)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Returning back to base";
        pMiner->GetStateMachine()->ChangeState(GoBackToBaseAndSleep::Instance());
    }
    // Otherwise continue mining
    else
        pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
}

void GoToStorageAndDepositBlocks::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Leaving the Storage...";
}

bool GoToStorageAndDepositBlocks::OnNotification(Miner* pMiner, const Telegram& message)
{
    return false;
}

//------------------------------------------------------------------------

GoBackToBaseAndSleep* GoBackToBaseAndSleep::Instance()
{
    static GoBackToBaseAndSleep instance;
    return &instance;
}

void GoBackToBaseAndSleep::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Base)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Going back to base...";
        pMiner->ChangeLocation(Base);

        // Notify Wife Agent
        MessageDispatcher::Instance()
            ->DispatchMessage(0,
            pMiner->Name(),
            AGENT_WIFE,
            Msg_BackToBase,
            nullptr
        );
    }
}

void GoBackToBaseAndSleep::Execute(Miner* pMiner)
{
    // Go back to mining if not fatigued
    if (pMiner->IsFatigued() == false)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Fully rested. Back to mining";
        pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
    }
    // Otherwise rest
    else
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Resting...";
        pMiner->DecreaseFatigue();
    }
}

void GoBackToBaseAndSleep::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Leaving base...";
}

bool GoBackToBaseAndSleep::OnNotification(Miner* pMiner, const Telegram& message)
{
    switch (message.messageType)
    {
    case Msg_FoodReady:
        std::cout << "\n" << "Message handled by " << pMiner->Name() << " at time : " << Clock->GetCurrentTime();
        std::cout << "\n" << pMiner->Name() << " : Roger that, coming to eat";

        pMiner->GetStateMachine()->ChangeState(GoBackToBaseAndEat::Instance());

        return true;

    default:
        return false;
    }

    return false;
}

//------------------------------------------------------------------------

GoToVillageAndDrinkWater* GoToVillageAndDrinkWater::Instance()
{
    static GoToVillageAndDrinkWater instance;
    return &instance;
}

void GoToVillageAndDrinkWater::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Village)
    {
        std::cout << "\n" << pMiner->Name() << " : " << "Going to the village for water...";
        pMiner->ChangeLocation(Village);
    }
}

void GoToVillageAndDrinkWater::Execute(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Trading my blocks for water";
    pMiner->TradeWaterWithBlocks();

    pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
}

void GoToVillageAndDrinkWater::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Leaving the village...";
}

bool GoToVillageAndDrinkWater::OnNotification(Miner* pMiner, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------

GoBackToBaseAndEat* GoBackToBaseAndEat::Instance()
{
    static GoBackToBaseAndEat instance;
    return &instance;
}

void GoBackToBaseAndEat::Enter(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Going to get food...";
}

void GoBackToBaseAndEat::Execute(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Eating...";

    pMiner->GetStateMachine()->RevertToPreviousState();
}

void GoBackToBaseAndEat::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << " : " << "Going back to previous occupation...";
}

bool GoBackToBaseAndEat::OnNotification(Miner* pMiner, const Telegram& msg)
{
    return false;
}
