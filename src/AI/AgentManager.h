//
// Created by maxdu on 12/11/2025.
//

#ifndef NEWARCH_AGENTMANAGER_H
#define NEWARCH_AGENTMANAGER_H

#include <map>
#include <string>

class Agent;

class AgentManager
{
    std::map<std::string, Agent*> m_Agents;

    AgentManager()
    {
    }

public:
    //copy ctor and assignment should be deleted
    AgentManager(const AgentManager&) = delete;
    AgentManager& operator=(const AgentManager&) = delete;

    static AgentManager* Instance();

    //this method stores a pointer to the entity in the std::vector
    //m_Entities at the index position indicated by the entity's ID
    //(makes for faster access)
    void RegisterAgent(Agent* pNewAgent);

    //returns a pointer to the entity with the ID given as a parameter
    Agent* GetAgentByName(const std::string& name) const;

    //this method removes the entity from the list
    void RemoveAgent(const Agent* pAgent);
};

#endif //NEWARCH_AGENTMANAGER_H