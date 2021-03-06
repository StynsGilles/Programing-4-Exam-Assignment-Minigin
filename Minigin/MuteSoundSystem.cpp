#include "MiniginPCH.h"
#include "MuteSoundSystem.h"
#include "iostream"

MuteSoundSystem::MuteSoundSystem()
{
}

void MuteSoundSystem::Update()
{
	std::cout << "Updating the SoundSysmte" << std::endl;
}

void MuteSoundSystem::PlaySound(const std::string& soundName)
{
	std::cout << "Playing the sound: " << soundName << std::endl;
}

void MuteSoundSystem::PlayMusic(const std::string& musicName)
{
	std::cout << "Playing the music: " << musicName << std::endl;
}

void MuteSoundSystem::PauseSound()
{
	std::cout << "Pausing sounds" << std::endl;
}

void MuteSoundSystem::UnpauseSound()
{
	std::cout << "Unpausing sounds" << std::endl;
}

void MuteSoundSystem::IncreaseVolume()
{
	std::cout << "Increasing the volume" << std::endl;
}

void MuteSoundSystem::DecreaseVolume()
{
	std::cout << "Decreasing the volume" << std::endl;
}
