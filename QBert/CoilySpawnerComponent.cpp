#include "pch.h"
#include "CoilySpawnerComponent.h"

#include <GameObject.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <SceneManager.h>

#include "CoilyNPCComponent.h"
#include "CoilyPlayerComponent.h"
#include "EnemyPositionComponent.h"
#include "GameCommands.h"
#include "LevelComponent.h"

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
	auto pScene = SceneManager::GetInstance().GetCurrentScene();
	const auto pActiveCoily = pScene->GetObjectOfType <CoilyNPCComponent>();
	if (!pActiveCoily)
	{
		auto pCoily = std::make_shared<GameObject>();
		auto* pCoilyRenderComp = new RenderComponent("Coily_Egg.png");
		auto* pCoilyPosComp = new EnemyPositionComponent(dae::EnemyType::top, m_pPyramid);
		CoilyNPCComponent* pCoilyComp;

		if (m_SpawnPlayer)
			pCoilyComp = new CoilyPlayerComponent(m_pPyramid, m_JumpCooldownEntity);
		else
			pCoilyComp = new CoilyNPCComponent(m_pPyramid, m_JumpCooldownEntity);
		pCoily->AddComponent(pCoilyRenderComp);
		pCoily->AddComponent(pCoilyPosComp);
		pCoily->AddComponent(pCoilyComp);
		pCoilyRenderComp->SetDimensions(m_pPyramid->GetCubeWidth() * 0.5f, m_pPyramid->GetCubeHeight() * 0.5f);
		pCoilyPosComp->SpawnOnCube(m_pPyramid->GetTopCube());
		pScene->Add(pCoily);

		auto* pInputManager = pScene->GetInputManager();
		if (pInputManager)
		{
			auto& player2Commands =  pInputManager->GetPlayer2Commands();
			
			for (auto& pair : player2Commands)
			{
				auto* pCommand = dynamic_cast<CoilyCommand*>(pair.second.get());
				if (pCommand)
					pCommand->ChangeCoily(pCoily);
			}
		}
	}
}
