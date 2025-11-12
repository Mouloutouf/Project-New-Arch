//
// Created by maxdu on 10/11/2025.
//

#include "Miner.h"

void Miner::Update()
{
    m_Thirst += 1;

    m_pStateMachine->Update();
}

bool Miner::HandleMessage(const Telegram& message)
{
    return m_pStateMachine->HandleNotification(message);
}

void Miner::AddBlocksInInventory(int value)
{
    m_BlocksInInventory += value;

    if (m_BlocksInInventory < 0)
        m_BlocksInInventory = 0;
}

void Miner::AddBlocksInStorage(int value)
{
    m_BlocksInStorage += value;

    if (m_BlocksInStorage < 0)
        m_BlocksInStorage = 0;
}

void Miner::TradeWaterWithBlocks()
{
    m_Thirst = 0;
    m_BlocksInStorage -= 2;
}
