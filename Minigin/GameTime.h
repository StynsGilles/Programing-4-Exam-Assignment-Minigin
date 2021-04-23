#pragma once
#include "Singleton.h"
#include <chrono>

class GameTime final : public dae::Singleton<GameTime>
{
public:
	void Update();
	float GetDeltaTime() const;
	std::chrono::steady_clock::time_point GetPreviousTime() const;
	int GetFPS() const;
	int GetMsPerFrame() const;
	
	GameTime(const GameTime& other) = delete;
	GameTime(GameTime&& other) = delete;
	GameTime& operator=(const GameTime& other) = delete;
	GameTime& operator=(GameTime&& other) = delete;
private:
	friend class Singleton<GameTime>;
	GameTime() = default;

	std::chrono::steady_clock::time_point m_PreviousTime = std::chrono::high_resolution_clock::now();
	float m_DeltaTime{};
	int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
};
