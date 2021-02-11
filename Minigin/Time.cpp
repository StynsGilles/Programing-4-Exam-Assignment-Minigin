#include "MiniginPCH.h"
#include "Time.h"

void Time::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
	m_PreviousTime = currentTime;
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

int Time::GetFPS() const
{
	float fps = 1.f / m_DeltaTime;
	return (int)fps;
}

int Time::GetMsPerFrame() const
{
	return m_MsPerFrame;
}
