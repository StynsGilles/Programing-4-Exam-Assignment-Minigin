#pragma once
#include <Commands.h>
#include <iostream>
#include <GameObject.h>
#include "CoilyPlayerComponent.h"
#include "QBertComponent.h"

class NorthEast final : public Command
{
public:
    NorthEast(std::weak_ptr<dae::GameObject> pQbert)
		: Command()
		, m_pQbert(pQbert)
    {}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(-1, 0);
        }
    }

    NorthEast(const NorthEast& other) = delete;
    NorthEast(NorthEast&& other) = delete;
    NorthEast& operator=(const NorthEast& other) = delete;
    NorthEast& operator=(NorthEast&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> m_pQbert;
};

class SouthEast final : public Command
{
public:
    SouthEast(std::weak_ptr<dae::GameObject> pQbert)
        : Command()
        , m_pQbert(pQbert)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(1, 1);
        }
    }

    SouthEast(const SouthEast& other) = delete;
    SouthEast(SouthEast&& other) = delete;
    SouthEast& operator=(const SouthEast& other) = delete;
    SouthEast& operator=(SouthEast&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> m_pQbert;
};

class NorthWest final : public Command
{
public:
    NorthWest(std::weak_ptr<dae::GameObject> pQbert)
        : Command()
        , m_pQbert(pQbert)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(-1, -1);
        }
    }

    NorthWest(const NorthWest& other) = delete;
    NorthWest(NorthWest&& other) = delete;
    NorthWest& operator=(const NorthWest& other) = delete;
    NorthWest& operator=(NorthWest&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> m_pQbert;
};

class SouthWest final : public Command
{
public:
    SouthWest(std::weak_ptr<dae::GameObject> pQbert)
        : Command()
        , m_pQbert(pQbert)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(1, 0);
        }
    }

    SouthWest(const SouthWest& other) = delete;
    SouthWest(SouthWest&& other) = delete;
    SouthWest& operator=(const SouthWest& other) = delete;
    SouthWest& operator=(SouthWest&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> m_pQbert;
};

class CoilyCommand : public Command
{
public:
    explicit CoilyCommand(std::weak_ptr<dae::GameObject> pCoily)
	    : m_pCoily(pCoily)
    {}

    void Execute() override
    {}

    void ChangeCoily(std::weak_ptr<dae::GameObject> pCoily)
    {
        m_pCoily = pCoily;
    }
	
    CoilyCommand(const CoilyCommand& other) = delete;
    CoilyCommand(CoilyCommand&& other) = delete;
    CoilyCommand& operator=(const CoilyCommand& other) = delete;
    CoilyCommand& operator=(CoilyCommand&& other) = delete;
	
protected:
    std::weak_ptr<dae::GameObject> m_pCoily;
};

class NorthEastCoily final : public CoilyCommand
{
public:
    NorthEastCoily(std::weak_ptr<dae::GameObject> pCoily)
        : CoilyCommand(pCoily)
    {}

    void Execute() override
    {
        std::cout << "doing shit" << std::endl;
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
        {
            auto* pCoilyComp = pSharedCoily->GetComponent<dae::CoilyPlayerComponent>();
            if (pCoilyComp) pCoilyComp->Move(-1, 0);
        }
    }

    NorthEastCoily(const NorthEastCoily& other) = delete;
    NorthEastCoily(NorthEastCoily&& other) = delete;
    NorthEastCoily& operator=(const NorthEastCoily& other) = delete;
    NorthEastCoily& operator=(NorthEastCoily&& other) = delete;
};

class SouthEastCoily final : public CoilyCommand
{
public:
    SouthEastCoily(std::weak_ptr<dae::GameObject> pCoily)
        : CoilyCommand(pCoily)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
        {
            auto* pCoilyComp = pSharedCoily->GetComponent<dae::CoilyPlayerComponent>();
            if (pCoilyComp) pCoilyComp->Move(1, 1);
        }
    }

    SouthEastCoily(const SouthEastCoily& other) = delete;
    SouthEastCoily(SouthEastCoily&& other) = delete;
    SouthEastCoily& operator=(const SouthEastCoily& other) = delete;
    SouthEastCoily& operator=(SouthEastCoily&& other) = delete;
};

class NorthWestCoily final : public CoilyCommand
{
public:
    NorthWestCoily(std::weak_ptr<dae::GameObject> pCoily)
        : CoilyCommand(pCoily)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
        {
            auto* pCoilyComp = pSharedCoily->GetComponent<dae::CoilyPlayerComponent>();
            if (pCoilyComp) pCoilyComp->Move(-1, -1);
        }
    }

    NorthWestCoily(const NorthWestCoily& other) = delete;
    NorthWestCoily(NorthWestCoily&& other) = delete;
    NorthWestCoily& operator=(const NorthWestCoily& other) = delete;
    NorthWestCoily& operator=(NorthWestCoily&& other) = delete;
};

class SouthWestCoily final : public CoilyCommand
{
public:
    SouthWestCoily(std::weak_ptr<dae::GameObject> pCoily)
        : CoilyCommand(pCoily)
    {}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
        {
            auto* pCoilyComp = pSharedCoily->GetComponent<dae::CoilyPlayerComponent>();
            if (pCoilyComp) pCoilyComp->Move(1, 0);
        }
    }

    SouthWestCoily(const SouthWestCoily& other) = delete;
    SouthWestCoily(SouthWestCoily&& other) = delete;
    SouthWestCoily& operator=(const SouthWestCoily& other) = delete;
    SouthWestCoily& operator=(SouthWestCoily&& other) = delete;
};