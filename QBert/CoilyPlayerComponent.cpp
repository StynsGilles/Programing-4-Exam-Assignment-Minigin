#include "pch.h"
#include "CoilyPlayerComponent.h"

#include <GameObject.h>

#include "EnemyPositionComponent.h"
#include "LevelComponent.h"

dae::CoilyPlayerComponent::CoilyPlayerComponent(LevelComponent* pPyramid, float jumpInterval)
	: CoilyNPCComponent(pPyramid, jumpInterval)
{}

dae::CoilyPlayerComponent::~CoilyPlayerComponent()
{}

void dae::CoilyPlayerComponent::Move(int rowChange, int colChange)
{
	if (!m_CanJump)
		return;

	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();
	
	if (m_pPyramid && pPosComp)
	{
		bool isOccupied = false;
		bool QBertOnCube = false;
		
		auto* pNextCube = m_pPyramid->GetNextCubeEnemy(pPosComp->GetCurrentCube(), rowChange, colChange, isOccupied, pPosComp->GetEnemyType(), QBertOnCube);

		if (!isOccupied)
		{
			pPosComp->ChangeCube(pNextCube, QBertOnCube);
			m_CanJump = false;
		}
	}
}

void dae::CoilyPlayerComponent::SetTarget(PlateComponent*, LevelCube*)
{}

void dae::CoilyPlayerComponent::ChasePlayer()
{}
