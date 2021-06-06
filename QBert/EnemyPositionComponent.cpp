#include "pch.h"
#include "EnemyPositionComponent.h"

#include <GameObject.h>
#include <RenderComponent.h>
#include <SceneManager.h>

#include "EntityComponent.h"
#include "GameStructs.h"
#include "LevelComponent.h"
#include "QBertComponent.h"
#include "SlickAndSamComponent.h"

dae::EnemyPositionComponent::EnemyPositionComponent(EnemyType enemyType, LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
	, m_EnemyType(enemyType)
{
}

dae::EnemyPositionComponent::~EnemyPositionComponent()
{}

void dae::EnemyPositionComponent::Update()
{}

void dae::EnemyPositionComponent::Render() const
{}

void dae::EnemyPositionComponent::SpawnOnCube(LevelCube* pNewCube)
{
	bool QBertOnCube{};

	switch (m_EnemyType)
	{
	case EnemyType::top:
		if (pNewCube && pNewCube->entity && pNewCube->entity->GetComponent<QBertComponent>())
			QBertOnCube = true;
		break;
	case EnemyType::left:
	case EnemyType::right:
	default:
		QBertOnCube = false;
		break;
	}
	ChangeCube(pNewCube, QBertOnCube);
}

void dae::EnemyPositionComponent::ChangeCube(LevelCube* pNewCube, bool QBertOnCube)
{
	RemoveFromCurrentCube();
	
	m_pCurrentCube = pNewCube;
	if (m_pCurrentCube)
	{
		if (QBertOnCube)
		{
			auto* pEntityComp = m_pObject->GetComponent<EntityComponent>();
			auto scene = SceneManager::GetInstance().GetCurrentScene();

			QBertComponent* pQBert = nullptr;
			LevelCube* pQBertCube;
			
			switch (m_EnemyType)
			{
			case EnemyType::left:
				pQBertCube = m_pPyramid->GetNextCubeNeutral(pNewCube, 1, 0);
				break;
			case EnemyType::right:
				pQBertCube = m_pPyramid->GetNextCubeNeutral(pNewCube, 1, 1);
				break;
			case EnemyType::top:
			default:
				pQBertCube = pNewCube;
				break;
			}
			
			if (pQBertCube)
				pQBert = pQBertCube->entity->GetComponent<QBertComponent>();
			
			if (pQBert)
			{
				if (dynamic_cast<SlickAndSamComponent*>(pEntityComp) && pQBert)
					pQBert->KillGreen();
				else if (pQBert)
					pQBert->GotHit();

				m_pObject->Delete();
				return;
			}
		}

		const float cubeWidth = m_pPyramid->GetCubeWidth();
		const float cubeHeight = m_pPyramid->GetCubeHeight();

		glm::vec3 pos = m_pCurrentCube->position;
		
		switch (m_EnemyType)
		{
		case EnemyType::top:
			m_pCurrentCube->entity = m_pObject;
			pos.x += cubeWidth / 2.f - m_pObject->GetComponent<RenderComponent>()->GetWidth() / 2.f;
			pos.y -= cubeHeight / 4.f;
			break;
		case EnemyType::left:
		{
			auto* pLeftCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, 0);
			if (pLeftCube)
				pLeftCube->entity = m_pObject;
			pos.x -= cubeWidth / 6.f;
			pos.y += cubeHeight / 2.f;
			break;
		}
		case EnemyType::right:
		{
			auto* pRightCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, +1);
			if (pRightCube)
				pRightCube->entity = m_pObject;
			pos.x += (cubeWidth / 3.f) * 2.f;
			pos.y += cubeHeight / 2.f;
			break;
		}
		default:
			m_pCurrentCube->entity = m_pObject;
			pos.x += cubeWidth / 3.f;
			pos.y -= 5.f;
			break;
		}
		UpdatePosition(pos);
	}
	else
	{
		RemoveFromCurrentCube();
		m_pObject->Delete();
	}
}

void dae::EnemyPositionComponent::RemoveFromCurrentCube() const
{
	if (m_pCurrentCube)
	{
		switch (m_EnemyType)
		{
		case EnemyType::top:
			if (m_pCurrentCube->entity == m_pObject)
				m_pCurrentCube->entity = nullptr;
			break;
		case EnemyType::left:
		{
			auto* pLeftCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, 0);
			if (pLeftCube && pLeftCube->entity == m_pObject)
				pLeftCube->entity = nullptr;
			break;
		}
		case EnemyType::right:
		{
			auto* pRightCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, +1);
			if (pRightCube && pRightCube->entity == m_pObject)
				pRightCube->entity = nullptr;
			break;
		}
		default:
			m_pCurrentCube->entity = nullptr;
			break;
		}
	}
}

dae::LevelCube* dae::EnemyPositionComponent::GetCurrentCube() const
{
	return m_pCurrentCube;
}

dae::EnemyType dae::EnemyPositionComponent::GetEnemyType() const
{
	return m_EnemyType;
}

void dae::EnemyPositionComponent::UpdatePosition(const glm::vec3& nextPosition) const
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}
