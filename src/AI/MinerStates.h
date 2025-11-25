//
// Created by maxdu on 12/11/2025.
//

#ifndef NEWARCH_MINERSTATES_H
#define NEWARCH_MINERSTATES_H

#include "AgentState.h"

class Miner;

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class EnterCaveAndMineBlocks : public AgentState<Miner>
{
public:
    // deleted copy constructor and assignment operator
    EnterCaveAndMineBlocks(const EnterCaveAndMineBlocks&) = delete;
    EnterCaveAndMineBlocks& operator=(const EnterCaveAndMineBlocks&) = delete;

    // static instance of this class
    static EnterCaveAndMineBlocks* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;

private:
    // private constructor
    EnterCaveAndMineBlocks()
    {
    }
};

// Singleton class
class GoToStorageAndDepositBlocks : public AgentState<Miner>
{
public:
    // deleted copy constructor and assignment operator
    GoToStorageAndDepositBlocks(const GoToStorageAndDepositBlocks&) = delete;
    GoToStorageAndDepositBlocks& operator=(const GoToStorageAndDepositBlocks&) = delete;

    // static instance of this class
    static GoToStorageAndDepositBlocks* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;

private:
    // private constructor
    GoToStorageAndDepositBlocks()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class GoBackToBaseAndSleep : public AgentState<Miner>
{
public:
    // deleted copy constructor and assignment operator
    GoBackToBaseAndSleep(const GoBackToBaseAndSleep&) = delete;
    GoBackToBaseAndSleep& operator=(const GoBackToBaseAndSleep&) = delete;

    // static instance of this class
    static GoBackToBaseAndSleep* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;

private:
    // private constructor
    GoBackToBaseAndSleep()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class GoToVillageAndDrinkWater : public AgentState<Miner>
{
public:
    // deleted copy constructor and assignment operator
    GoToVillageAndDrinkWater(const GoToVillageAndDrinkWater&) = delete;
    GoToVillageAndDrinkWater& operator=(const GoToVillageAndDrinkWater&) = delete;

    // static instance of this class
    static GoToVillageAndDrinkWater* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;

private:
    // private constructor
    GoToVillageAndDrinkWater()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class GoBackToBaseAndEat : public AgentState<Miner>
{
public:
    // deleted copy constructor and assignment operator
    GoBackToBaseAndEat(const GoBackToBaseAndEat&) = delete;
    GoBackToBaseAndEat& operator=(const GoBackToBaseAndEat&) = delete;

    // static instance of this class
    static GoBackToBaseAndEat* Instance();

    void Enter(Miner* miner) override;

    void Execute(Miner* miner) override;

    void Exit(Miner* miner) override;

    bool OnNotification(Miner* agent, const Telegram& message) override;

private:
    // private constructor
    GoBackToBaseAndEat()
    {
    }
};

#endif //NEWARCH_MINERSTATES_H
