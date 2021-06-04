#include "pch.h"
#include "BaseSpawnerComponent.h"

#include "GameTime.h"

dae::BaseSpawnerComponent::BaseSpawnerComponent(LevelComponent* pPyramid)
	:m_pPyramid(pPyramid)
{
}

dae::BaseSpawnerComponent::~BaseSpawnerComponent()
{
}

void dae::BaseSpawnerComponent::Update()
{
	m_SpawnTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_SpawnTimer >= m_SpawnInterval)
	{
		SpawnEnemy();
		m_SpawnTimer = 0.f;
	}
}

void dae::BaseSpawnerComponent::SetSpawnRate(float spawnInterval)
{
	m_SpawnInterval = spawnInterval;
}

void dae::BaseSpawnerComponent::SetJumpRateEntity(float jumpCooldown)
{
	m_JumpCooldownEntity = jumpCooldown;
}
