#include "MiniginPCH.h"
#include "GameTime.h"

void GameTime::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_PreviousTime).count();
	m_PreviousTime = currentTime;
}

float GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

std::chrono::steady_clock::time_point GameTime::GetPreviousTime() const
{
	return m_PreviousTime;
}

int GameTime::GetFPS() const
{
	return static_cast<int>(1.f / m_DeltaTime);
}

int GameTime::GetMsPerFrame() const
{
	return m_MsPerFrame;
}