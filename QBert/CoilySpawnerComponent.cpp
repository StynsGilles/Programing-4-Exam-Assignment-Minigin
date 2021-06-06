#include "pch.h"
#include "CoilySpawnerComponent.h"
#include "CoilyNPCComponent.h"
#include "CoilyPlayerComponent.h"
#include "EnemyPositionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelComponent.h"
#include "GameCommands.h"

dae::CoilySpawnerComponent::CoilySpawnerComponent(LevelComponent* pPyramid, float spawnInterval, float jumpCooldown, bool spawnPlayer)
	: BaseSpawnerComponent(pPyramid)
	, m_SpawnPlayer(spawnPlayer)
{
	SetSpawnRate(spawnInterval);
	SetJumpRateEntity(jumpCooldown);
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
	auto activeCoily = scene->GetObjectOfType <CoilyNPCComponent>();
	if (!activeCoily)
	{
		auto coily = std::make_shared<GameObject>();
		auto* pCoilyRenderComp = new RenderComponent("Coily_Egg.png");
		auto* pCoilyPosComp = new EnemyPositionComponent(dae::EnemyType::top, m_pPyramid);
		CoilyNPCComponent* pCoilyComp;

		if (m_SpawnPlayer)
			pCoilyComp = new CoilyPlayerComponent(m_pPyramid, m_JumpCooldownEntity);
		else
			pCoilyComp = new CoilyNPCComponent(m_pPyramid, m_JumpCooldownEntity);
		coily->AddComponent(pCoilyRenderComp);
		coily->AddComponent(pCoilyPosComp);
		coily->AddComponent(pCoilyComp);
		pCoilyRenderComp->SetDimensions(m_pPyramid->GetCubeWidth() * 0.5f, m_pPyramid->GetCubeHeight() * 0.5f);
		pCoilyPosComp->SpawnOnCube(m_pPyramid->GetTopCube());
		scene->Add(coily);

		auto* pInputManager = scene->GetInputManager();
		if (pInputManager)
		{
			auto& player2Commands =  pInputManager->GetPlayer2Commands();
			
			for (auto& pair : player2Commands)
			{
				auto command = dynamic_cast<CoilyCommand*>(pair.second.get());
				if (command)
					command->ChangeCoily(coily);
			}
		}
	}
}
