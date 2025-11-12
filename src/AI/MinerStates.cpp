//
// Created by maxdu on 12/11/2025.
//

#include "MinerStates.h"

#include <iostream>

#include "AgentNames.h"
#include "Miner.h"
#include "Messaging/MessageDispatcher.h"
#include "Messaging/Messages.h"

//------------------------------------------------------------------------methods for EnterCaveAndMineBlocks
EnterCaveAndMineBlocks* EnterCaveAndMineBlocks::Instance()
{
    static EnterCaveAndMineBlocks instance;

    return &instance;
}


void EnterCaveAndMineBlocks::Enter(Miner* pMiner)
{
    //if the miner is not already located at the Cave, he must
    //change location to the gold mine
    if (pMiner->Location() != Cave)
    {
        std::cout << "\n" << pMiner->Name() << ": " << "Walkin' to the Cave";

        pMiner->ChangeLocation(Cave);
    }
}


void EnterCaveAndMineBlocks::Execute(Miner* pMiner)
{
    //Now the miner is at the Cave he digs for gold until he
    //is carrying in excess of MaxNuggets. If he gets thirsty during
    //his digging he packs up work for a while and changes state to
    //gp to the saloon for a whiskey.
    pMiner->AddBlocksInInventory(1);

    pMiner->IncreaseFatigue();

    std::cout << "\n" << pMiner->Name() << ": " << "Pickin' up a nugget";

    //if enough gold mined, go and put it in the bank
    if (pMiner->IsAtMaximumInventory())
    {
        pMiner->GetStateMachine()->ChangeState(GoToStorageAndDepositBlocks::Instance());
    }

    if (pMiner->IsThirsty())
    {
        pMiner->GetStateMachine()->ChangeState(GoToVillageAndDrinkWater::Instance());
    }
}


void EnterCaveAndMineBlocks::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": "
        << "Ah'm leavin' the Cave with mah pockets full o' sweet gold";
}


bool EnterCaveAndMineBlocks::OnNotification(Miner* pMiner, const Telegram& message)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------methods for GoToStorageAndDepositBlocks

GoToStorageAndDepositBlocks* GoToStorageAndDepositBlocks::Instance()
{
    static GoToStorageAndDepositBlocks instance;

    return &instance;
}

void GoToStorageAndDepositBlocks::Enter(Miner* pMiner)
{
    //on entry the miner makes sure he is located at the bank
    if (pMiner->Location() != Storage)
    {
        std::cout << "\n" << pMiner->Name() << ": " << "Goin' to the bank. Yes siree";

        pMiner->ChangeLocation(Storage);
    }
}


void GoToStorageAndDepositBlocks::Execute(Miner* pMiner)
{
    //deposit the gold
    pMiner->AddBlocksInStorage(pMiner->BlocksInInventory());

    pMiner->SetBlocksInInventory(0);

    std::cout << "\n" << pMiner->Name() << ": "
        << "Depositing gold. Total savings now: " << pMiner->BlocksInStorage();

    //wealthy enough to have a well-earned rest?
    if (pMiner->BlocksInStorage() >= BLOCKS_MAX_WORKLOAD)
    {
        std::cout << "\n" << pMiner->Name() << ": "
            << "WooHoo! Rich enough for now. Back home to mah li'lle lady";

        pMiner->GetStateMachine()->ChangeState(GoBackToBaseAndSleep::Instance());
    }

    //otherwise get more gold
    else
    {
        pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
    }
}


void GoToStorageAndDepositBlocks::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Leavin' the bank";
}


bool GoToStorageAndDepositBlocks::OnNotification(Miner* pMiner, const Telegram& message)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------methods for GoBackToBaseAndSleep

GoBackToBaseAndSleep* GoBackToBaseAndSleep::Instance()
{
    static GoBackToBaseAndSleep instance;

    return &instance;
}

void GoBackToBaseAndSleep::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Base)
    {
        std::cout << "\n" << pMiner->Name() << ": " << "Walkin' home";

        pMiner->ChangeLocation(Base);

        //let the wife know I'm home
        MessageDispatcher::Instance()->DispatchMessage(0, // Time delay
                                  pMiner->Name(), // Name of sender
                                  AGENT_WIFE, // Name of receiver
                                  Msg_BackToBase, // Message
                                  nullptr); // No extra info
    }
}

void GoBackToBaseAndSleep::Execute(Miner* pMiner)
{
    //if miner is not fatigued start to dig for nuggets again.
    if (!pMiner->IsFatigued())
    {
        std::cout << "\n" << pMiner->Name() << ": "
            << "All mah fatigue has drained away. Time to find more gold!";

        pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
    }

    else
    {
        //sleep
        pMiner->DecreaseFatigue();

        std::cout << "\n" << pMiner->Name() << ": " << "ZZZZ... ";
    }
}

void GoBackToBaseAndSleep::Exit(Miner* pMiner)
{
}


bool GoBackToBaseAndSleep::OnNotification(Miner* pMiner, const Telegram& msg)
{
    switch (msg.message)
    {
    case Msg_FoodReady:
        std::cout << "\nMessage handled by " << pMiner->Name()
            << " at time: " << Clock->GetCurrentTime();

        std::cout << "\n" << pMiner->Name()
            << ": Okay Hun, ahm a comin'!";

        pMiner->GetStateMachine()->ChangeState(GoBackToBaseAndEat::Instance());

        return true;

    default:
        return false;
    }

    return false; //send message to global message handler
}

//------------------------------------------------------------------------GoToVillageAndDrinkWater

GoToVillageAndDrinkWater* GoToVillageAndDrinkWater::Instance()
{
    static GoToVillageAndDrinkWater instance;

    return &instance;
}

void GoToVillageAndDrinkWater::Enter(Miner* pMiner)
{
    if (pMiner->Location() != Village)
    {
        pMiner->ChangeLocation(Village);

        std::cout << "\n" << pMiner->Name() << ": " << "Boy, ah sure is thusty! Walking to the saloon";
    }
}

void GoToVillageAndDrinkWater::Execute(Miner* pMiner)
{
    pMiner->TradeWaterWithBlocks();

    std::cout << "\n" << pMiner->Name() << ": " << "That's mighty fine sippin' liquer";

    pMiner->GetStateMachine()->ChangeState(EnterCaveAndMineBlocks::Instance());
}


void GoToVillageAndDrinkWater::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Leaving the saloon, feelin' good";
}


bool GoToVillageAndDrinkWater::OnNotification(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------GoBackToBaseAndEat

GoBackToBaseAndEat* GoBackToBaseAndEat::Instance()
{
    static GoBackToBaseAndEat instance;

    return &instance;
}


void GoBackToBaseAndEat::Enter(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Smells Reaaal goood Elsa!";
}

void GoBackToBaseAndEat::Execute(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " << "Tastes real good too!";

    pMiner->GetStateMachine()->RevertToPreviousState();
}

void GoBackToBaseAndEat::Exit(Miner* pMiner)
{
    std::cout << "\n" << pMiner->Name() << ": " <<
        "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool GoBackToBaseAndEat::OnNotification(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}
