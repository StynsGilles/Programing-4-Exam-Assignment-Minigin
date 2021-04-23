#pragma once
#include <Commands.h>
#include <iostream>
#include <GameObject.h>
#include "HealthComponent.h"
#include "ScoreComponent.h"

class Fire final : public Command
{
public:
    Fire() :Command() {}
    void Execute() override { std::cout << "Firing" << std::endl; }

    Fire(const Fire& other) = delete;
    Fire(Fire&& other) = delete;
    Fire& operator=(const Fire& other) = delete;
    Fire& operator=(Fire&& other) = delete;
};

class Duck final : public Command
{
public:
    Duck() : Command() {}
    void Execute() override { std::cout << "Ducking" << std::endl; }

    Duck(const Duck& other) = delete;
    Duck(Duck&& other) = delete;
    Duck& operator=(const Duck& other) = delete;
    Duck& operator=(Duck&& other) = delete;
};

class Jump final : public Command
{
public:
    Jump() : Command() {}
    void Execute() override { std::cout << "Jumping" << std::endl; }

    Jump(const Jump& other) = delete;
    Jump(Jump&& other) = delete;
    Jump& operator=(const Jump& other) = delete;
    Jump& operator=(Jump&& other) = delete;
};

class Fart final : public Command
{
public:
    Fart() : Command() {}
    void Execute() override { std::cout << "Farting" << std::endl; }

    Fart(const Fart& other) = delete;
    Fart(Fart&& other) = delete;
    Fart& operator=(const Fart& other) = delete;
    Fart& operator=(Fart&& other) = delete;
};

class Kill final : public Command
{
public:
    Kill(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToKill(pObject) {}
    void Execute() override
    {
        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToKill.lock())
            pSharedObject->GetComponent<dae::HealthComponent>()->LoseLives(1);
    };

    Kill(const Kill& other) = delete;
    Kill(Kill&& other) = delete;
    Kill& operator=(const Kill& other) = delete;
    Kill& operator=(Kill&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> pObjectToKill;
};

class Damage final : public Command
{
public:
    Damage(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToDamage(pObject) {}
    void Execute() override
    {
        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToDamage.lock())
            pSharedObject->GetComponent<dae::HealthComponent>()->Damage(1);
    };

    Damage(const Damage& other) = delete;
    Damage(Damage&& other) = delete;
    Damage& operator=(const Damage& other) = delete;
    Damage& operator=(Damage&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> pObjectToDamage;
};

class Score final : public Command
{
public:
    Score(std::weak_ptr<dae::GameObject> pObject) : Command(), pObjectToAwardTo(pObject) {}
    void Execute() override
    {
        //Try to see if the object still exists by acquiring shared_ptr from the weak_ptr
        if (std::shared_ptr<dae::GameObject> pSharedObject = pObjectToAwardTo.lock())
            pSharedObject->GetComponent<dae::ScoreComponent>()->AddToScore(25);
    };

    Score(const Score& other) = delete;
    Score(Score&& other) = delete;
    Score& operator=(const Score& other) = delete;
    Score& operator=(Score&& other) = delete;
private:
    std::weak_ptr<dae::GameObject> pObjectToAwardTo;
};