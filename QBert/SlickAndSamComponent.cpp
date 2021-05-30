#include "pch.h"
#include "SlickAndSamComponent.h"
#include "EnemyPositionComponent.h"
#include "GameObject.h"
#include "LevelComponent.h"

dae::SlickAndSamComponent::SlickAndSamComponent(LevelComponent* pPyramid)
	: EntityComponent(pPyramid)
{
}

dae::SlickAndSamComponent::~SlickAndSamComponent()
{
}

void dae::SlickAndSamComponent::Update()
{
	JumpUpdate();
}

void dae::SlickAndSamComponent::Jump()
{
	JumpRandomDownwards(true);
}

void dae::SlickAndSamComponent::Render() const
{
}