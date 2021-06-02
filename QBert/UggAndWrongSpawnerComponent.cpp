#include "pch.h"
#include "UggAndWrongSpawnerComponent.h"
#include "EnemyPositionComponent.h"
#include "GameTime.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "UggAndWrongComponent.h"
#include <GameObject.h>
#include "LevelComponent.h"
#include <Scene.h>

dae::UggAndWrongSpawnerComponent::UggAndWrongSpawnerComponent(LevelComponent* pPyramid)
	: BaseSpawnerComponent(pPyramid)
{
}

dae::UggAndWrongSpawnerComponent::~UggAndWrongSpawnerComponent()
{
}

void dae::UggAndWrongSpawnerComponent::Update()
{
	BaseSpawnerComponent::Update();
}

void dae::UggAndWrongSpawnerComponent::SpawnEnemy()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();

	auto maxIndex = m_pPyramid->GetPyramidSize() - 1;

	auto newEnemy = std::make_shared<GameObject>();
	auto* pEnemyComp = new UggAndWrongComponent(m_pPyramid);
	newEnemy->AddComponent(pEnemyComp);
	if (m_SpawnUgg)
	{
		auto* pUggRenderComponent = new RenderComponent("Ugg.png");
		auto* pUggPosComponent = new EnemyPositionComponent(dae::EnemyType::right, m_pPyramid);
		newEnemy->AddComponent(pUggRenderComponent);
		newEnemy->AddComponent(pUggPosComponent);
		pUggPosComponent->SpawnOnCube(m_pPyramid->GetCube(maxIndex, maxIndex));
	}
	else
	{
		auto* pWrongwayRenderComponent = new dae::RenderComponent("Wrongway.png");
		auto* pWrongwayPosComponent = new dae::EnemyPositionComponent(dae::EnemyType::left, m_pPyramid);
		newEnemy->AddComponent(pWrongwayRenderComponent);
		newEnemy->AddComponent(pWrongwayPosComponent);
		pWrongwayPosComponent->SpawnOnCube(m_pPyramid->GetCube(maxIndex, 0));
	}
	
	scene->Add(newEnemy);
	
	m_SpawnUgg = !m_SpawnUgg;
}

void dae::UggAndWrongSpawnerComponent::Render() const
{
}
