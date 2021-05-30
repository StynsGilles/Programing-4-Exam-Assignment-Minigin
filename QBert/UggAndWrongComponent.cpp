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
					pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, rowChange, 1);
					break;
				case 1:
					pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -rowChange, 0);
					break;
				default:
					break;
				}
				break;
			}
			case EnemyType::right:
				pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, -rand() % 2, -1);
				break;
			default:
				break;
			}
			
			pPosComp->ChangeCube(pNextCube);
		}
	}
}

void dae::UggAndWrongComponent::Render() const
{
}