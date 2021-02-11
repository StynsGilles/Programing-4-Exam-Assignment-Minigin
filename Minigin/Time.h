#pragma once
#include "Singleton.h"
#include <chrono>

class Time final : public dae::Singleton<Time>
{
public:
	void Update();
	float GetDeltaTime() const;
	std::chrono::steady_clock::time_point GetPreviousTime() const;
	int GetFPS() const;
	int GetMsPerFrame() const;
	
	Time(const Time& other) = delete;
	Time(Time&& other) = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& other) = delete;
private:
	friend class Singleton<Time>;
	Time() = default;

	std::chrono::steady_clock::time_point m_PreviousTime = std::chrono::high_resolution_clock::now();
	float m_DeltaTime{};
	static const int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
};
