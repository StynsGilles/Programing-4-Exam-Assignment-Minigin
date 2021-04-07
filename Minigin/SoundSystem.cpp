#include "MiniginPCH.h"
#include "SoundSystem.h"
namespace dae
{
#include "audio.c"
}

dae::SoundSystem::SoundSystem()
	: m_Volume{ 100 }
{
	initAudio();
	m_SoundThread = std::thread([this]() { this->Update(); });
}

dae::SoundSystem::~SoundSystem()
{
	m_ClosingGame = true;
	m_ConditionVariable.notify_one();
	endAudio();
	m_SoundThread.join();
}

void dae::SoundSystem::Update()
{
	do
	{		
		std::unique_lock<std::mutex> mLock{ m_Mutex };
		if (m_ClosingGame)
		{
			break;
		}
		
		if (!m_AudioQueue.empty())
		{
			auto audio = m_AudioQueue.front();
			m_AudioQueue.pop();

			switch (audio.AudioType)
			{
			case AudioType::Effect:
				playSound(audio.FileName.c_str(), m_Volume);
				break;
			case AudioType::Music:
				playMusic(audio.FileName.c_str(), m_Volume);
				break;
			default:
				std::cout << "Sound was not an effect or music." << std::endl;
				break;
			}
		}

		if (m_AudioQueue.empty())
			m_ConditionVariable.wait(mLock);
		
	} while (!m_AudioQueue.empty());
}

void dae::SoundSystem::PlaySound(const std::string& soundName)
{
	AudioData audioData;
	audioData.FileName = soundName;
	audioData.AudioType = AudioType::Effect;
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_AudioQueue.push(audioData);
	m_ConditionVariable.notify_one();
}

void dae::SoundSystem::PlayMusic(const std::string& musicName)
{
	AudioData audioData;
	audioData.FileName = musicName;
	audioData.AudioType = AudioType::Music;
	std::lock_guard<std::mutex> mLock{ m_Mutex };
	m_AudioQueue.push(audioData);
	m_ConditionVariable.notify_one();
}

void dae::SoundSystem::PauseSound()
{
	pauseAudio();
}

void dae::SoundSystem::UnpauseSound()
{
	unpauseAudio();
}

void dae::SoundSystem::IncreaseVolume()
{
	m_Volume += 5;
	if (m_Volume > 100)
		m_Volume = 100;
}

void dae::SoundSystem::DecreaseVolume()
{
	m_Volume -= 5;
	if (m_Volume < 0)
		m_Volume = 0;
}
