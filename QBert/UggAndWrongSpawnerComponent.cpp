#include "pch.h"
#include "UggAndWrongSpawnerComponent.h"

#include <GameObject.h>
#include <GameTime.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <SceneManager.h>

#include "EnemyPositionComponent.h"
#include "GameStructs.h"
#include "LevelComponent.h"
#include "UggAndWrongComponent.h"

dae::UggAndWrongSpawnerComponent::UggAndWrongSpawnerComponent(LevelComponent* pPyramid, float spawnInterval, float jumpCooldown)
	: BaseSpawnerComponent(pPyramid)
{
	SetSpawnRate(spawnInterval);
	SetJumpRateEntity(jumpCooldown);
}

dae::UggAndWrongSpawnerComponent::~UggAndWrongSpawnerComponent()
{}

void dae::UggAndWrongSpawnerComponent::Update()
{
	BaseSpawnerComponent::Update();
}

void dae::UggAndWrongSpawnerComponent::SpawnEnemy()
{
	auto pScene = SceneManager::GetInstance().GetCurrentScene();

	const auto maxIndex = m_pPyramid->GetPyramidSize() - 1;

	auto pNewEnemy = std::make_shared<GameObject>();
	auto* pEnemyComp = new UggAndWrongComponent(m_pPyramid, m_JumpCooldownEntity);
	pNewEnemy->AddComponent(pEnemyComp);

	std::string fileName{};
	EnemyType spawnSide{};
	int spawnColIdx{};
	
	if (m_SpawnUgg)
	{
		fileName = "Ugg.png";
		spawnColIdx = maxIndex;
		spawnSide = EnemyType::right;
	}
	else
	{
		fileName = "Wrongway.png";
		spawnColIdx = 0;
		spawnSide = EnemyType::left;
	}

	auto* pRenderComponent = new RenderComponent(fileName);
	auto* pPosComponent = new EnemyPositionComponent(spawnSide, m_pPyramid);
	pNewEnemy->AddComponent(pRenderComponent);
	pNewEnemy->AddComponent(pPosComponent);
	pRenderComponent->SetDimensions(m_pPyramid->GetCubeWidth() * 0.5f, m_pPyramid->GetCubeHeight() * 0.5f);
	pPosComponent->SpawnOnCube(m_pPyramid->GetCube(maxIndex, spawnColIdx));
	
	pScene->Add(pNewEnemy);
	
	m_SpawnUgg = !m_SpawnUgg;
}

void dae::UggAndWrongSpawnerComponent::Render() const
{}
