#include "pch.h"
#include "UggAndWrongComponent.h"
#include "EnemyPositionComponent.h"
#include "LevelComponent.h"
#include <GameObject.h>

dae::UggAndWrongComponent::UggAndWrongComponent(LevelComponent* pPyramid)
	: EntityComponent(pPyramid)
{
}

dae::UggAndWrongComponent::~UggAndWrongComponent()
{
}

void dae::UggAndWrongComponent::Update()
{
	JumpUpdate();
}

void dae::UggAndWrongComponent::Jump()
{
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp)
	{
		LevelCube* pCurrentCube = pPosComp->GetCurrentCube();

		if (pCurrentCube)
		{
			bool isOccupied = false;
			bool QBertOnCube = false;
			EnemyType enemyType = pPosComp->GetEnemyType();

			LevelCube* pNextCube = nullptr;

			switch (enemyType)
			{
			case EnemyType::left:
			{
				const int rowChange = rand() % 2;
				switch (rowChange)
				{
				case 0:
					pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, rowChange, 1, isOccupied, enemyType, QBertOnCube);
					if (isOccupied)
						pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -1, 0, isOccupied, enemyType, QBertOnCube);
					break;
				case 1:
					pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -rowChange, 0, isOccupied, enemyType, QBertOnCube);
					if (isOccupied)
						pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 0, 1, isOccupied, enemyType, QBertOnCube);
					break;
				default:
					break;
				}
				break;
			}
			case EnemyType::right:
			{
				int randRowChange = rand() % 2;
				pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -randRowChange, -1, isOccupied, enemyType, QBertOnCube);
				if (isOccupied)
					pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -static_cast<int>(!static_cast<bool>(randRowChange)), -1, isOccupied, enemyType, QBertOnCube);
			}
				break;
			default:
				break;
			}
			
			if (!isOccupied)
				pPosComp->ChangeCube(pNextCube, QBertOnCube);
		}
	}
}

void dae::UggAndWrongComponent::Render() const
{
}