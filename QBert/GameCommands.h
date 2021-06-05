#pragma once
#include <Commands.h>
#include <iostream>
#include <GameObject.h>

#include "CoilyPlayerComponent.h"
#include "QBertComponent.h"

//class Fire final : public Command
//{
//public:
//    Fire() :Command() {}
//    void Execute() override { std::cout << "Firing" << std::endl; }
//
//    Fire(const Fire& other) = delete;
//    Fire(Fire&& other) = delete;
//    Fire& operator=(const Fire& other) = delete;
//    Fire& operator=(Fire&& other) = delete;
//};
//
//class Duck final : public Command
//{
//public:
//    Duck() : Command() {}
//    void Execute() override { std::cout << "Ducking" << std::endl; }
//
//    Duck(const Duck& other) = delete;
//    Duck(Duck&& other) = delete;
//    Duck& operator=(const Duck& other) = delete;
//    Duck& operator=(Duck&& other) = delete;
//};
//
//class Jump final : public Command
//{
//public:
//    Jump() : Command() {}
//    void Execute() override { std::cout << "Jumping" << std::endl; }
//
//    Jump(const Jump& other) = delete;
//    Jump(Jump&& other) = delete;
//    Jump& operator=(const Jump& other) = delete;
//    Jump& operator=(Jump&& other) = delete;
//};
//
//class Fart final : public Command
//{
//public:
//    Fart() : Command() {}
//    void Execute() override { std::cout << "Farting" << std::endl; }
//
//    Fart(const Fart& other) = delete;
//    Fart(Fart&& other) = delete;
//    Fart& operator=(const Fart& other) = delete;
//    Fart& operator=(Fart&& other) = delete;
//};
//
//class Kill final : public Command
//{
//public:
//    Kill(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToKill(pObject) {}
//    void Execute() override
//    {
//        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
//        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToKill.lock())
//            pSharedObject->GetComponent<dae::HealthComponent>()->LoseLives(1);
//    };
//
//    Kill(const Kill& other) = delete;
//    Kill(Kill&& other) = delete;
//    Kill& operator=(const Kill& other) = delete;
//    Kill& operator=(Kill&& other) = delete;
//
//private:
//    std::weak_ptr<dae::GameObject> pObjectToKill;
//};
//
//class Damage final : public Command
//{
//public:
//    Damage(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToDamage(pObject) {}
//    void Execute() override
//    {
//        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
//        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToDamage.lock())
//            pSharedObject->GetComponent<dae::HealthComponent>()->Damage(1);
//    };
//
//    Damage(const Damage& other) = delete;
//    Damage(Damage&& other) = delete;
//    Damage& operator=(const Damage& other) = delete;
//    Damage& operator=(Damage&& other) = delete;
//private:
//    std::weak_ptr<dae::GameObject> pObjectToDamage;
//};
//
//class Score final : public Command
//{
//public:
//    Score(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToAwardTo(pObject) {}
//    void Execute() override
//    {
//        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
//        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToAwardTo.lock())
//            pSharedObject->GetComponent<dae::ScoreComponent>()->AddToScore(25);
//    };
//
//    Score(const Score& other) = delete;
//    Score(Score&& other) = delete;
//    Score& operator=(const Score& other) = delete;
//    Score& operator=(Score&& other) = delete;
//private:
//    std::weak_ptr<dae::GameObject> pObjectToAwardTo;
//};

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

class NorthEastCoily final : public Command
{
public:
    NorthEastCoily(std::weak_ptr<dae::GameObject> pCoily)
        : Command()
        , m_pCoily(pCoily)
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
private:
    std::weak_ptr<dae::GameObject> m_pCoily;
};

class SouthEastCoily final : public Command
{
public:
    SouthEastCoily(std::weak_ptr<dae::GameObject> pCoily)
        : Command()
        , m_pCoily(pCoily)
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
private:
    std::weak_ptr<dae::GameObject> m_pCoily;
};

class NorthWestCoily final : public Command
{
public:
    NorthWestCoily(std::weak_ptr<dae::GameObject> pCoily)
        : Command()
        , m_pCoily(pCoily)
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
private:
    std::weak_ptr<dae::GameObject> m_pCoily;
};

class SouthWestCoily final : public Command
{
public:
    SouthWestCoily(std::weak_ptr<dae::GameObject> pCoily)
        : Command()
        , m_pCoily(pCoily)
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
private:
    std::weak_ptr<dae::GameObject> m_pCoily;
};