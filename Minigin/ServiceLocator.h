#pragma once
#include "ISoundSystem.h"

class ServiceLocator
{
	static ISoundSystem* ss_service;
public:
	static ISoundSystem* GetSoundSystem() { return ss_service; }
	static void RegisterSoundSystem(ISoundSystem* ss) { ss_service = ss; }
};

ISoundSystem* ServiceLocator::ss_service{};