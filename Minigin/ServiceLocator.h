#pragma once
#include "ISoundSystem.h"

class ServiceLocator
{
	static std::unique_ptr<ISoundSystem> ss_service;
public:
	static std::unique_ptr<ISoundSystem>& GetSoundSystem() { return ss_service; }
	static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>& ss) { ss_service = std::move(ss); }
	static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& ss) { ss_service = std::move(ss); }
};
