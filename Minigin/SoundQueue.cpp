#include "MiniginPCH.h"
#include "SoundQueue.h"
#include "ServiceLocator.h"
#include <chrono>
#include <thread>

#include "Time.h"

void dae::SoundQueue::AddToQueue(const AudioData& audioData)
{
	m_AudioQueue.push(audioData);
}

using namespace std::chrono;
void dae::SoundQueue::ProcessQueue()
{
	while (m_Running)
	{
		while (m_AudioQueue.size() > 0)
		{
			auto audio = m_AudioQueue.front();

			switch (audio.AudioType)
			{
			case AudioType::Effect:
				ServiceLocator::GetSoundSystem()->PlaySound(audio.FileName);
				break;
			case AudioType::Music:
				ServiceLocator::GetSoundSystem()->PlayMusic(audio.FileName);
				break;
			default:
				std::cout << "Sound was not an effect or music." << std::endl;
				break;
			}

			m_AudioQueue.pop();
		}
		auto sleepTime = duration_cast<duration<float>>(Time::GetInstance().GetPreviousTime()
			+ milliseconds(int(Time::GetInstance().GetMsPerFrame())) - high_resolution_clock::now());
		std::this_thread::sleep_for(sleepTime);
	}
}

void dae::SoundQueue::StopRunning()
{
	m_Running = false;
}
