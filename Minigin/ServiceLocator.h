#pragma once
#include "ISoundSystem.h"
#include "NullSoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
		static std::unique_ptr<ISoundSystem> ss_service;
		static std::unique_ptr<NullSoundSystem> ss_nullService;
	public:
		static std::unique_ptr<ISoundSystem>& GetSoundSystem() { return ss_service; }
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& ss)
		{
			ss_service = std::move(ss);
			if (ss_service == nullptr)
				ss_service = std::move(ss_nullService);
		}
	};
}


