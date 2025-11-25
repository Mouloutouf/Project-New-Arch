//
// Created by maxdu on 10/11/2025.
//

#ifndef NEWARCH_MINER_H
#define NEWARCH_MINER_H

#include "Locations.h"
#include "Agent.h"
#include "StateMachine.h"
#include "MinerStates.h"

// The amount of blocks a miner must have before he can go back to base
constexpr int BLOCKS_MAX_WORKLOAD = 5;
// The amount of blocks a miner can have in its inventory
constexpr int MAX_INVENTORY = 3;

// Above this value a miner needs to drink
constexpr int THIRST_THRESHOLD = 5;
// Above this value a miner needs to sleep
constexpr int FATIGUE_THRESHOLD = 5;

class Miner : public Agent
{
public:
    Miner(const std::string& name)
        : Agent(name), m_Location(Base), m_BlocksInInventory(0), m_BlocksInStorage(0), m_Thirst(0), m_Fatigue(0)
    {
        m_pStateMachine = new StateMachine(this);

        m_pStateMachine->SetCurrentState(GoBackToBaseAndSleep::Instance());
        /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
    }
    ~Miner() override { delete m_pStateMachine; }

    void Update() override;

    bool HandleMessage(const Telegram& message) override;

    StateMachine<Miner>* GetStateMachine() const { return m_pStateMachine; }

    LocationType Location() const { return m_Location; }
    void ChangeLocation(LocationType location) { m_Location = location; }

    int BlocksInInventory() const { return m_BlocksInInventory; }
    void SetBlocksInInventory(int value) { m_BlocksInInventory = value; }
    void AddBlocksInInventory(int value);
    bool IsAtMaximumInventory() const { return m_BlocksInInventory >= MAX_INVENTORY; }

    int BlocksInStorage() const { return m_BlocksInStorage; }
    void SetBlocksInStorage(int value) { m_BlocksInStorage = value; }
    void AddBlocksInStorage(int value);

    void DecreaseFatigue() { m_Fatigue -= 1; }
    void IncreaseFatigue() { m_Fatigue += 1; }
    bool IsFatigued() const { return m_Fatigue >= FATIGUE_THRESHOLD; }

    bool IsThirsty() const { return m_Thirst >= THIRST_THRESHOLD; }
    void TradeWaterWithBlocks();

private:
    StateMachine<Miner>* m_pStateMachine;

    LocationType m_Location;

    int m_BlocksInInventory;
    int m_BlocksInStorage;

    int m_Thirst;
    int m_Fatigue;
};

#endif //NEWARCH_MINER_H
