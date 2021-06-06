#include "pch.h"
#include "SlickAndSamSpawnerComponent.h"

#include <GameObject.h>
#include <GameTime.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <SceneManager.h>

#include "EnemyPositionComponent.h"
#include "GameStructs.h"
#include "LevelComponent.h"
#include "QBertComponent.h"
#include "SlickAndSamComponent.h"

dae::SlickAndSamSpawnerComponent::SlickAndSamSpawnerComponent(LevelComponent* pPyramid, float spawnInterval, float jumpCooldown)
	: BaseSpawnerComponent(pPyramid)
{
	SetSpawnRate(spawnInterval);
	SetJumpRateEntity(jumpCooldown);
}

dae::SlickAndSamSpawnerComponent::~SlickAndSamSpawnerComponent()
{}

void dae::SlickAndSamSpawnerComponent::Update()
{
	BaseSpawnerComponent::Update();
}

void dae::SlickAndSamSpawnerComponent::SpawnEnemy()
{
	auto pScene = SceneManager::GetInstance().GetCurrentScene();
	auto pNewEnemy = std::make_shared<GameObject>();
	auto* pSandSComponent = new SlickAndSamComponent(m_pPyramid, m_JumpCooldownEntity);
	auto* pPosComponent = new EnemyPositionComponent(EnemyType::top, m_pPyramid);
	RenderComponent* pRenderComponent;
	if (m_SpawnSlick)
		pRenderComponent = new RenderComponent("Slick.png");
	else
		pRenderComponent = new RenderComponent("Sam.png");
	pNewEnemy->AddComponent(pSandSComponent);
	pNewEnemy->AddComponent(pRenderComponent);
	pNewEnemy->AddComponent(pPosComponent);
	pRenderComponent->SetDimensions(m_pPyramid->GetCubeWidth() * 0.5f, m_pPyramid->GetCubeHeight() * 0.5f);
	const int randomCol = rand() % 2;
	auto* pCubeToSpawnOn = m_pPyramid->GetCube(1, randomCol);
	if (pCubeToSpawnOn->entity && !pCubeToSpawnOn->entity->GetComponent<QBertComponent>())
		pCubeToSpawnOn = m_pPyramid->GetCube(1, static_cast<int>(!static_cast<bool>(randomCol)));
	pPosComponent->SpawnOnCube(pCubeToSpawnOn);
	pScene->Add(pNewEnemy);
	m_SpawnSlick = !m_SpawnSlick;
}

void dae::SlickAndSamSpawnerComponent::Render() const
{}