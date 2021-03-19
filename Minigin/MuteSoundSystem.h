#pragma once
#include "ISoundSystem.h"
#include <string>

class MuteSoundSystem final : public ISoundSystem
{
public:
	MuteSoundSystem();
	virtual ~MuteSoundSystem() = default;
	
	void PlaySound(const std::string& soundName) override;
	void PauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	
	MuteSoundSystem(const MuteSoundSystem&) = delete;
	MuteSoundSystem(MuteSoundSystem&&) = delete;
	MuteSoundSystem& operator= (const MuteSoundSystem&) = delete;
	MuteSoundSystem& operator= (const MuteSoundSystem&&) = delete;
};
