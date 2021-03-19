#pragma once
#include <queue>
#include "Singleton.h"

enum class AudioType
{
	Effect,
	Music
};

struct AudioData
{
	AudioType AudioType;
	std::string FileName;
};

namespace dae
{
	class SoundQueue final : public Singleton<SoundQueue>
	{
	public:
		void AddToQueue(const AudioData& audioData);
		void ProcessQueue();
		void StopRunning();
	
	private:
		friend class Singleton<SoundQueue>;
		SoundQueue() = default;
		std::queue<AudioData> m_AudioQueue;
		bool m_Running{ true };
	};
}