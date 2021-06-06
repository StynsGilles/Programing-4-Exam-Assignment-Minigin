#include "pch.h"
#include "EntityComponent.h"

#include <GameObject.h>
#include <GameTime.h>

#include "EnemyPositionComponent.h"
#include "LevelComponent.h"

dae::EntityComponent::EntityComponent(LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
{
}

dae::EntityComponent::~EntityComponent()
{
}

void dae::EntityComponent::JumpUpdate()
{
	m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

	if (m_JumpTimer >= m_JumpInterval)
	{
		Jump();
		m_JumpTimer -= m_JumpInterval;
	}
}

void dae::EntityComponent::JumpRandomDownwards(bool isSlickOrSam) const
{
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp)
	{
		LevelCube* pCurrentCube = pPosComp->GetCurrentCube();
		const EnemyType enemyType = pPosComp->GetEnemyType();
		
		if (pCurrentCube)
		{	
			bool isOccupied = false;
			bool QBertOnCube = false;
			int randomColChange = rand() % 2;
			LevelCube* pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 1, randomColChange, isOccupied, enemyType, QBertOnCube, isSlickOrSam);
			if (pNextCube)
				pPosComp->ChangeCube(pNextCube, QBertOnCube);
			else
			{
				randomColChange = static_cast<int>(!static_cast<bool>(randomColChange));
				pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 1, randomColChange, isOccupied, enemyType, QBertOnCube, isSlickOrSam);
				if (!isOccupied)
					pPosComp->ChangeCube(pNextCube, QBertOnCube);
			}
		}
	}
}

void dae::EntityComponent::SetJumpRate(float jumpInterval)
{
	m_JumpInterval = jumpInterval;
}
