//
// Created by maxdu on 12/11/2025.
//

#ifndef NEWARCH_AGENTMANAGER_H
#define NEWARCH_AGENTMANAGER_H

#include <map>
#include <string>

class Agent;

// Singleton class
class AgentManager
{
public:
    // deleted copy constructor and assignment operator
    AgentManager(const AgentManager&) = delete;
    AgentManager& operator=(const AgentManager&) = delete;

    // static instance of this class
    static AgentManager* Instance();

    void RegisterAgent(Agent* pNewAgent);

    Agent* GetAgentByName(const std::string& name) const;

    void RemoveAgent(const Agent* pAgent);

private:
    // private constructor
    AgentManager()
    {
    }

    std::map<std::string, Agent*> m_Agents;
};

#endif //NEWARCH_AGENTMANAGER_H
