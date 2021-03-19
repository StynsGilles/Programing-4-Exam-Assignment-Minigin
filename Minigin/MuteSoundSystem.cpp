#include "MiniginPCH.h"
#include "MuteSoundSystem.h"
#include "iostream"

MuteSoundSystem::MuteSoundSystem()
{
}

void MuteSoundSystem::PlaySound(const std::string& soundName)
{
	std::cout << "Playing the sound: " << soundName << std::endl;
}

void MuteSoundSystem::PauseSound()
{
	std::cout << "Pausing sounds" << std::endl;
}

void MuteSoundSystem::IncreaseVolume()
{
	std::cout << "Increasing the volume" << std::endl;
}

void MuteSoundSystem::DecreaseVolume()
{
	std::cout << "Decreasing the volume" << std::endl;
}
