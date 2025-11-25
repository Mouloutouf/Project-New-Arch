//
// Created by maxdu on 14/11/2025.
//

#ifndef NEWARCH_WIFESTATES_H
#define NEWARCH_WIFESTATES_H

#include "AgentState.h"

class Wife;

//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class WifeGlobalState : public AgentState<Wife>
{
public:
    // deleted copy constructor and assignment operator
    WifeGlobalState(const WifeGlobalState&) = delete;
    WifeGlobalState& operator=(const WifeGlobalState&) = delete;

    // static instance of this class
    static WifeGlobalState* Instance();

    void Enter(Wife* wife) override;

    void Execute(Wife* wife) override;

    void Exit(Wife* wife) override;

    bool OnNotification(Wife* wife, const Telegram& msg) override;

private:
    // private constructor
    WifeGlobalState()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class ManageBase : public AgentState<Wife>
{
public:
    // deleted copy constructor and assignment operator
    ManageBase(const ManageBase&) = delete;
    ManageBase& operator=(const ManageBase&) = delete;

    // static instance of this class
    static ManageBase* Instance();

    void Enter(Wife* wife) override;

    void Execute(Wife* wife) override;

    void Exit(Wife* wife) override;

    bool OnNotification(Wife* wife, const Telegram& msg) override;

private:
    // private constructor
    ManageBase()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class InspectStorage : public AgentState<Wife>
{
public:
    // deleted copy constructor and assignment operator
    InspectStorage(const InspectStorage&) = delete;
    InspectStorage& operator=(const InspectStorage&) = delete;

    // static instance of this class
    static InspectStorage* Instance();

    void Enter(Wife* wife) override;

    void Execute(Wife* wife) override;

    void Exit(Wife* wife) override;

    bool OnNotification(Wife* wife, const Telegram& msg) override;

private:
    // private constructor
    InspectStorage()
    {
    }
};
//------------------------------------------------------------------------
//

//------------------------------------------------------------------------

// Singleton class
class PrepareFood : public AgentState<Wife>
{
public:
    // deleted copy constructor and assignment operator
    PrepareFood(const PrepareFood&) = delete;
    PrepareFood& operator=(const PrepareFood&) = delete;

    // static instance of this class
    static PrepareFood* Instance();

    void Enter(Wife* wife) override;

    void Execute(Wife* wife) override;

    void Exit(Wife* wife) override;

    bool OnNotification(Wife* wife, const Telegram& msg) override;

private:
    // private constructor
    PrepareFood()
    {
    }
};

#endif //NEWARCH_WIFESTATES_H
