#include "pch.h"
#include "SlickAndSamComponent.h"
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
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp)
	{
		LevelCube* pCurrentCube = pPosComp->GetCurrentCube();

		if (pCurrentCube)
		{
			LevelCube*  pNextCube = m_pPyramid->GetNextCubeEnemy(pCurrentCube, 1, rand() % 2, true);
			pPosComp->ChangeCube(pNextCube);
		}
	}
}

void dae::SlickAndSamComponent::Render() const
{
}