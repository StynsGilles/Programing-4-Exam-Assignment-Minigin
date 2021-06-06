#pragma once
#include <Commands.h>
#include <GameObject.h>
#include <utility>

#include "CoilyPlayerComponent.h"
#include "QBertComponent.h"

class QBertCommand : public Command
{
public:
    explicit QBertCommand(std::weak_ptr<dae::GameObject> pQbert)
        : Command()
        , m_pQbert(std::move(pQbert))
    {}

    ~QBertCommand() override
    {}

    void Execute() override
    {}

    QBertCommand(const QBertCommand& other) = delete;
    QBertCommand(QBertCommand&& other) = delete;
    QBertCommand& operator=(const QBertCommand& other) = delete;
    QBertCommand& operator=(QBertCommand&& other) = delete;
protected:
    std::weak_ptr<dae::GameObject> m_pQbert;
};

class NorthEast final : public QBertCommand
{
public:
    explicit NorthEast(const std::weak_ptr<dae::GameObject>& pQbert)
        : QBertCommand(pQbert)
    {}
	
    ~NorthEast() override
    {}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(-1, 0);
        }
    }

    NorthEast(const NorthEast& other) = delete;
    NorthEast(NorthEast&& other) = delete;
    NorthEast& operator=(const NorthEast& other) = delete;
    NorthEast& operator=(NorthEast&& other) = delete;
};

class SouthEast final : public QBertCommand
{
public:
    explicit SouthEast(const std::weak_ptr<dae::GameObject>& pQbert)
        : QBertCommand(pQbert)
    {}

    ~SouthEast() override
	{}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(1, 1);
        }
    }

    SouthEast(const SouthEast& other) = delete;
    SouthEast(SouthEast&& other) = delete;
    SouthEast& operator=(const SouthEast& other) = delete;
    SouthEast& operator=(SouthEast&& other) = delete;
};

class NorthWest final : public QBertCommand
{
public:
    explicit NorthWest(const std::weak_ptr<dae::GameObject>& pQbert)
        : QBertCommand(pQbert)
    {}

    ~NorthWest() override
	{}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(-1, -1);
        }
    }

    NorthWest(const NorthWest& other) = delete;
    NorthWest(NorthWest&& other) = delete;
    NorthWest& operator=(const NorthWest& other) = delete;
    NorthWest& operator=(NorthWest&& other) = delete;
};

class SouthWest final : public QBertCommand
{
public:
    explicit SouthWest(const std::weak_ptr<dae::GameObject>& pQbert)
        : QBertCommand(pQbert)
    {}

    ~SouthWest() override
    {}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedQbert = m_pQbert.lock())
        {
            auto* pQBertComp = pSharedQbert->GetComponent<dae::QBertComponent>();
            if (pQBertComp) pQBertComp->Move(1, 0);
        }
    }

    SouthWest(const SouthWest& other) = delete;
    SouthWest(SouthWest&& other) = delete;
    SouthWest& operator=(const SouthWest& other) = delete;
    SouthWest& operator=(SouthWest&& other) = delete;
};

class CoilyCommand : public Command
{
public:
    explicit CoilyCommand(std::weak_ptr<dae::GameObject> pCoily)
	    :Command()
		, m_pCoily(std::move(pCoily))
    {}

    ~CoilyCommand() override
	{}
	
    void Execute() override
    {}

    void ChangeCoily(std::weak_ptr<dae::GameObject> pCoily)
    {
        m_pCoily = std::move(pCoily);
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
	explicit NorthEastCoily(const std::weak_ptr<dae::GameObject>& pCoily)
        : CoilyCommand(pCoily)
    {}

    ~NorthEastCoily() override
	{}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
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
    explicit SouthEastCoily(const std::weak_ptr<dae::GameObject>& pCoily)
        : CoilyCommand(pCoily)
    {}

    ~SouthEastCoily() override
	{}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
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
    explicit NorthWestCoily(const std::weak_ptr<dae::GameObject>& pCoily)
        : CoilyCommand(pCoily)
    {}

    ~NorthWestCoily() override
	{}
	
    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
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
    explicit SouthWestCoily(const std::weak_ptr<dae::GameObject>& pCoily)
        : CoilyCommand(pCoily)
    {}

	~SouthWestCoily() override
	{}

    void Execute() override
    {
        //Try to see if the objects still exist by acquiring shared_ptr from the weak_ptr
        if (const std::shared_ptr<dae::GameObject> pSharedCoily = m_pCoily.lock())
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