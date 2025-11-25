//
// Created by maxdu on 14/11/2025.
//

#include "Wife.h"

bool Wife::HandleMessage(const Telegram& message)
{
    return m_pStateMachine->HandleNotification(message);
}

void Wife::Update()
{
    m_pStateMachine->Update();
}
