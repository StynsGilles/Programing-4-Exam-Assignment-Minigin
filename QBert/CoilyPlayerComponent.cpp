#include "pch.h"
#include "CoilyPlayerComponent.h"

dae::CoilyPlayerComponent::CoilyPlayerComponent(LevelComponent* pPyramid, float jumpInterval)
	: CoilyNPCComponent(pPyramid, jumpInterval)
{
}

dae::CoilyPlayerComponent::~CoilyPlayerComponent()
{
}

void dae::CoilyPlayerComponent::ChasePlayer()
{
	m_CanJump = true;
}
