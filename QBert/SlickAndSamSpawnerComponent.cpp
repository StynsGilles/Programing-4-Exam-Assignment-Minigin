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

int counter = 0;

dae::SlickAndSamSpawnerComponent::SlickAndSamSpawnerComponent(LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
{
}

dae::SlickAndSamSpawnerComponent::~SlickAndSamSpawnerComponent()
{
}

void dae::SlickAndSamSpawnerComponent::Update()
{
	m_SpawnTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_SpawnTimer >= m_SpawnInterval)
	{
		SpawnEnemy();
		m_SpawnTimer = 0.f;
	}
}

void dae::SlickAndSamSpawnerComponent::SpawnEnemy() const
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto Slick = std::make_shared<GameObject>();
	auto* pSlickComponent = new SlickAndSamComponent(m_pPyramid);
	auto* pPosComponent = new EnemyPositionComponent();
	auto* pSlickRenderComponent = new RenderComponent("Slick.png");
	Slick->AddComponent(pSlickComponent);
	Slick->AddComponent(pSlickRenderComponent);
	Slick->AddComponent(pPosComponent);
	pPosComponent->ChangeCube(m_pPyramid->GetCube(1, rand() % 2));
	scene->Add(Slick);
	//scene->AddAtRunTime(Slick);
}

void dae::SlickAndSamSpawnerComponent::Render() const
{
}