//
// Created by maxdu on 12/11/2025.
//

#ifndef NEWARCH_MINERSTATES_H
#define NEWARCH_MINERSTATES_H

#include "AgentState.h"

class Miner;

class EnterCaveAndMineBlocks : public AgentState<Miner>
{
    EnterCaveAndMineBlocks()
    {
    }

public:
    //copy ctor and assignment should be deleted
    EnterCaveAndMineBlocks(const EnterCaveAndMineBlocks&) = delete;
    EnterCaveAndMineBlocks& operator=(const EnterCaveAndMineBlocks&) = delete;

    //this is a singleton
    static EnterCaveAndMineBlocks* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;
};

class GoToStorageAndDepositBlocks : public AgentState<Miner>
{
    GoToStorageAndDepositBlocks()
    {
    }

public:
    //copy ctor and assignment should be deleted
    GoToStorageAndDepositBlocks(const GoToStorageAndDepositBlocks&) = delete;
    GoToStorageAndDepositBlocks& operator=(const GoToStorageAndDepositBlocks&) = delete;

    //this is a singleton
    static GoToStorageAndDepositBlocks* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;
};

class GoBackToBaseAndSleep : public AgentState<Miner>
{
    GoBackToBaseAndSleep()
    {
    }

public:
    //copy ctor and assignment should be deleted
    GoBackToBaseAndSleep(const GoBackToBaseAndSleep&) = delete;
    GoBackToBaseAndSleep& operator=(const GoBackToBaseAndSleep&) = delete;

    //this is a singleton
    static GoBackToBaseAndSleep* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;
};

class GoToVillageAndDrinkWater : public AgentState<Miner>
{
    GoToVillageAndDrinkWater()
    {
    }

public:
    //copy ctor and assignment should be deleted
    GoToVillageAndDrinkWater(const GoToVillageAndDrinkWater&) = delete;
    GoToVillageAndDrinkWater& operator=(const GoToVillageAndDrinkWater&) = delete;

    //this is a singleton
    static GoToVillageAndDrinkWater* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;
};

class GoBackToBaseAndEat : public AgentState<Miner>
{
    GoBackToBaseAndEat()
    {
    }

public:
    //copy ctor and assignment should be deleted
    GoBackToBaseAndEat(const GoBackToBaseAndEat&) = delete;
    GoBackToBaseAndEat& operator=(const GoBackToBaseAndEat&) = delete;

    //this is a singleton
    static GoBackToBaseAndEat* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;
};

#endif //NEWARCH_MINERSTATES_H