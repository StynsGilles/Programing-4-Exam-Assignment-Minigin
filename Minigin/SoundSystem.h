#pragma once
#include "ISoundSystem.h"
namespace dae
{
#include "audio.h"
}
#include <string>

class SoundSystem final : public ISoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem();

	void PlaySound(const std::string& soundName) override;
	void PauseSound() override;
	void IncreaseVolume() override;
	void DecreaseVolume() override;
	
	SoundSystem(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator= (const SoundSystem&) = delete;
	SoundSystem& operator= (const SoundSystem&&) = delete;

private:
	int m_Volume;
};
