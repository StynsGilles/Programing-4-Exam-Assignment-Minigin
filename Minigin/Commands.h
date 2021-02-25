#pragma once
#include <iostream>

#include "GameObject.h"

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void Execute() = 0;

    Command(const Command& other) = delete;
    Command(Command&& other) = delete;
    Command& operator=(const Command& other) = delete;
    Command& operator=(Command&& other) = delete;
};

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
    Kill(std::shared_ptr<dae::GameObject> pObject) : Command(), pObjectToKill(pObject) {}
    void Execute() override
    {
        pObjectToKill->Delete();
    };

    Kill(const Kill& other) = delete;
    Kill(Kill&& other) = delete;
    Kill& operator=(const Kill& other) = delete;
    Kill& operator=(Kill&& other) = delete;

private:
    std::shared_ptr<dae::GameObject> pObjectToKill = nullptr;
};