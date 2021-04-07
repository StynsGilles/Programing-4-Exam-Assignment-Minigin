#pragma once
#include "ISoundSystem.h"
#include <string>

class MuteSoundSystem final : public ISoundSystem
{
public:
	MuteSoundSystem();
	virtual ~MuteSoundSystem() = default;
	
	void Update() override;
	void PlaySound(const std::string& soundName) override;
	void PlayMusic(const std::string& musicName) override;
	void PauseSound() override;
	void UnpauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	
	MuteSoundSystem(const MuteSoundSystem&) = delete;
	MuteSoundSystem(MuteSoundSystem&&) = delete;
	MuteSoundSystem& operator= (const MuteSoundSystem&) = delete;
	MuteSoundSystem& operator= (const MuteSoundSystem&&) = delete;
};
