#pragma once
#include <condition_variable>
#include <queue>
#include "ISoundSystem.h"
namespace dae
{
#include "audio.h"
}
#include <string>

namespace dae
{
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

	class SoundSystem final : public ISoundSystem
	{
	public:
		SoundSystem();
		virtual ~SoundSystem();

		void Update() override;
		void PlaySound(const std::string& soundName) override;
		void PlayMusic(const std::string& musicName) override;
		void PauseSound() override;
		void UnpauseSound() override;
		void IncreaseVolume() override;
		void DecreaseVolume() override;

		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = delete;
		SoundSystem& operator= (const SoundSystem&) = delete;
		SoundSystem& operator= (const SoundSystem&&) = delete;

	private:
		int m_Volume;
		std::queue<AudioData> m_AudioQueue;
		std::condition_variable m_ConditionVariable;
		std::mutex m_Mutex;
		std::thread m_SoundThread;
		bool m_ClosingGame = false;
	};
}


