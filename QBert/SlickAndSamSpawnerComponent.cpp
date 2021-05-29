#include "pch.h"
#include "SlickAndSamSpawnerComponent.h"
#include <SceneManager.h>
#include "RenderComponent.h"
#include "SlickAndSamComponent.h"
#include "LevelComponent.h"
#include <GameObject.h>

#include "GameTime.h"
#include "Scene.h"

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
		m_SpawnTimer -= m_SpawnInterval;
	}
}

void dae::SlickAndSamSpawnerComponent::SpawnEnemy() const
{
	std::cout << "spawning Slick" << std::endl;

	auto& scene = SceneManager::GetInstance().GetCurrentScene();
	auto Slick = std::make_shared<GameObject>();
	auto* pSlickComponent = new SlickAndSamComponent(m_pPyramid);
	auto* pSlickRenderComponent = new RenderComponent("Slick.png");
	Slick->AddComponent(pSlickComponent);
	Slick->AddComponent(pSlickRenderComponent);
	pSlickComponent->ChangeCube(m_pPyramid->GetCube(1, rand() % 2));
	scene.Add(Slick);
}

void dae::SlickAndSamSpawnerComponent::Render() const
{
}