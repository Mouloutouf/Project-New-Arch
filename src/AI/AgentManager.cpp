//
// Created by maxdu on 12/11/2025.
//

#include "AgentManager.h"

#include "Agent.h"

AgentManager* AgentManager::Instance()
{
    static AgentManager instance;

    return &instance;
}

void AgentManager::RegisterAgent(Agent* pNewAgent)
{
    m_Agents.insert(std::make_pair(pNewAgent->Name(), pNewAgent));
}

Agent* AgentManager::GetAgentByName(const std::string& name) const
{
    auto agentIt = m_Agents.find(name);

    if (agentIt == m_Agents.end())
        return nullptr; // And an error message

    return agentIt->second;
}

void AgentManager::RemoveAgent(const Agent* pAgent)
{
    m_Agents.erase(m_Agents.find(pAgent->Name()));
}
