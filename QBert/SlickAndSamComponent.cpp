#include "pch.h"
#include "SlickAndSamComponent.h"
#include <SDL_render.h>
#include <GameTime.h>

#include "EnemyPositionComponent.h"
#include "GameObject.h"
#include "LevelComponent.h"

dae::SlickAndSamComponent::SlickAndSamComponent(LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
{
}

dae::SlickAndSamComponent::~SlickAndSamComponent()
{
}

void dae::SlickAndSamComponent::Update()
{
	m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

	if(m_JumpTimer>= m_JumpInterval)
	{
		Jump();
		m_JumpTimer -= m_JumpInterval;
	}
}

void dae::SlickAndSamComponent::Jump()
{
	int randomNumber = rand() % 2;

	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp)
	{
		LevelCube* pNextCube = nullptr;
		LevelCube* pCurrentCube = pPosComp->GetCurrentCube();

		if (pCurrentCube)
		{
			switch (randomNumber)
			{
			case 0:
				pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 1, 0, true);
				break;
			case 1:
				pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 1, 1, true);
				break;
			default:
				break;
			}

			pPosComp->ChangeCube(pNextCube);
		}
	}
}

void dae::SlickAndSamComponent::Render() const
{
}