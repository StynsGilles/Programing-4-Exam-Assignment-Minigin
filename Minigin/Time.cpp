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

std::chrono::steady_clock::time_point Time::GetPreviousTime() const
{
	return m_PreviousTime;
}

int Time::GetFPS() const
{
	return int(1.f / m_DeltaTime);
}

int Time::GetMsPerFrame() const
{
	return m_MsPerFrame;
}

void Time::SetMsPerFrame(const int& msPerFrame)
{
	m_MsPerFrame = msPerFrame;
}
