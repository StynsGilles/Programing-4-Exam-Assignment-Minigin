 #pragma once

class ISoundSystem
{
public:
	ISoundSystem() = default;
	virtual ~ISoundSystem() = default;

	virtual void PlaySound(const std::string& soundName) = 0;
	virtual void PlayMusic(const std::string& musicName) = 0;
	virtual void PauseSound() = 0;
	virtual void IncreaseVolume() = 0;
	virtual void DecreaseVolume() = 0;
	
	ISoundSystem(const ISoundSystem&) = delete;
	ISoundSystem(ISoundSystem&&) = delete;
	ISoundSystem& operator= (const ISoundSystem&) = delete;
	ISoundSystem& operator= (const ISoundSystem&&) = delete;
};
