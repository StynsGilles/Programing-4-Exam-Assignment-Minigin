#include "MiniginPCH.h"
#include "SoundSystem.h"
namespace dae
{
#include "audio.c"
}

SoundSystem::SoundSystem()
	: m_Volume{ 100 }
{
	dae::initAudio();
}

SoundSystem::~SoundSystem()
{
	dae::endAudio();
}

void SoundSystem::PlaySound(const std::string& soundName)
{
	dae::playSound(soundName.c_str(), m_Volume);
}

void SoundSystem::PlayMusic(const std::string& musicName)
{
	dae::playMusic(musicName.c_str(), m_Volume);
}

void SoundSystem::PauseSound()
{
	dae::pauseAudio();
}

void SoundSystem::IncreaseVolume()
{
	m_Volume += 5;
	if (m_Volume > 100)
		m_Volume = 100;
}

void SoundSystem::DecreaseVolume()
{
	m_Volume -= 5;
	if (m_Volume < 0)
		m_Volume = 0;
}
