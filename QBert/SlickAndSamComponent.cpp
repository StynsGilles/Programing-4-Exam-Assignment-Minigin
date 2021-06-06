#include "pch.h"
#include "SlickAndSamComponent.h"

#include "LevelComponent.h"

dae::SlickAndSamComponent::SlickAndSamComponent(LevelComponent* pPyramid, float jumpInterval)
	: EntityComponent(pPyramid)
{
	SetJumpRate(jumpInterval);
}

dae::SlickAndSamComponent::~SlickAndSamComponent()
{}

void dae::SlickAndSamComponent::Update()
{
	JumpUpdate();
}

void dae::SlickAndSamComponent::Jump()
{
	JumpRandomDownwards(true);
}

void dae::SlickAndSamComponent::Render() const
{}