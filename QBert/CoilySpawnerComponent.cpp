#include "pch.h"
#include "CoilySpawnerComponent.h"
#include "CoilyComponent.h"
#include "EnemyPositionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelComponent.h"

dae::CoilySpawnerComponent::CoilySpawnerComponent(LevelComponent* pPyramid)
	: BaseSpawnerComponent(pPyramid)
{
}

dae::CoilySpawnerComponent::~CoilySpawnerComponent()
{
}

void dae::CoilySpawnerComponent::Update()
{
	BaseSpawnerComponent::Update();
}

void dae::CoilySpawnerComponent::Render() const
{
}

void dae::CoilySpawnerComponent::SpawnEnemy()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto activeCoily = scene->GetObjectOfType <CoilyComponent>();
	if (!activeCoily)
	{
		auto coily = std::make_shared<GameObject>();
		auto* pCoilyRenderComp = new RenderComponent("Coily_Egg.png");
		auto* pCoilyPosComp = new EnemyPositionComponent(dae::EnemyType::top, m_pPyramid);
		auto* pCoilyComp = new CoilyComponent(m_pPyramid);
		coily->AddComponent(pCoilyRenderComp);
		coily->AddComponent(pCoilyPosComp);
		coily->AddComponent(pCoilyComp);
		pCoilyPosComp->ChangeCube(m_pPyramid->GetCube(2, 1), false);
		scene->Add(coily);
	}
}
