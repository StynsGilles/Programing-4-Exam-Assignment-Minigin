#pragma once
#include "ISoundSystem.h"

class NullSoundSystem : public ISoundSystem
{
public:
	NullSoundSystem();
	virtual ~NullSoundSystem() = default;

	void Update() override;
	void PlaySound(const std::string&) override;
	void PlayMusic(const std::string&) override;
	void PauseSound() override;
	void UnpauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	
	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator= (const NullSoundSystem&) = delete;
	NullSoundSystem& operator= (const NullSoundSystem&&) = delete;
};

