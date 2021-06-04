#include "pch.h"
#include "SlickAndSamSpawnerComponent.h"
#include <SceneManager.h>
#include "RenderComponent.h"
#include "SlickAndSamComponent.h"
#include "LevelComponent.h"
#include <GameObject.h>
#include "EnemyPositionComponent.h"
#include "GameTime.h"
#include "Scene.h"

dae::SlickAndSamSpawnerComponent::SlickAndSamSpawnerComponent(LevelComponent* pPyramid, float spawnInterval, float jumpCooldown)
	: BaseSpawnerComponent(pPyramid)
{
	SetSpawnRate(spawnInterval);
	SetJumpRateEntity(jumpCooldown);
}

dae::SlickAndSamSpawnerComponent::~SlickAndSamSpawnerComponent()
{
}

void dae::SlickAndSamSpawnerComponent::Update()
{
	BaseSpawnerComponent::Update();
}

void dae::SlickAndSamSpawnerComponent::SpawnEnemy()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto newEnemy = std::make_shared<GameObject>();
	auto* pSandSComponent = new SlickAndSamComponent(m_pPyramid, m_JumpCooldownEntity);
	auto* pPosComponent = new EnemyPositionComponent(EnemyType::top, m_pPyramid);
	RenderComponent* pRenderComponent;
	if (m_SpawnSlick)
		pRenderComponent = new RenderComponent("Slick.png");
	else
		pRenderComponent = new RenderComponent("Sam.png");
	newEnemy->AddComponent(pSandSComponent);
	newEnemy->AddComponent(pRenderComponent);
	newEnemy->AddComponent(pPosComponent);
	pPosComponent->SpawnOnCube(m_pPyramid->GetCube(1, rand() % 2));
	scene->Add(newEnemy);
	m_SpawnSlick = !m_SpawnSlick;
}

void dae::SlickAndSamSpawnerComponent::Render() const
{
}