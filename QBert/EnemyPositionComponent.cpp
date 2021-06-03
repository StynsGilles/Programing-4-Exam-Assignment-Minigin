#include "pch.h"
#include "EnemyPositionComponent.h"
#include <SDL_render.h>
#include <GameObject.h>
#include "EntityComponent.h"
#include "LevelComponent.h"
#include "LivesComponent.h"
#include "QBertComponent.h"
#include "SlickAndSamComponent.h"
#include "SceneManager.h"
#include "Scene.h"

dae::EnemyPositionComponent::EnemyPositionComponent(EnemyType enemyType, LevelComponent* pPyramid)
	: m_EnemyType(enemyType)
	, m_pPyramid(pPyramid)
{
}

dae::EnemyPositionComponent::~EnemyPositionComponent()
{
}

void dae::EnemyPositionComponent::Update()
{
}

void dae::EnemyPositionComponent::Render() const
{
}

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
			auto* qbert = pNewCube->entity->GetComponent<QBertComponent>();
			
			if (dynamic_cast<SlickAndSamComponent*>(pEntityComp) && qbert)
				qbert->KillGreen();
			else if (qbert)
				qbert->GetGameObject()->GetComponent<LivesComponent>()->LoseLives(1);

			m_pObject->Delete();
			return;
		}
		
		SDL_Rect dst;
		SDL_QueryTexture(pNewCube->pCubeTextures[pNewCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

		glm::vec3 pos = m_pCurrentCube->position;
		
		switch (m_EnemyType)
		{
		case EnemyType::top:
			m_pCurrentCube->entity = m_pObject;
			pos.x += (float)dst.w / 3.f;
			pos.y -= (float)dst.h / 4.f;
			break;
		case EnemyType::left:
		{
			auto* pLeftCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, 0);
			if (pLeftCube)
				pLeftCube->entity = m_pObject;
			pos.x -= (float)dst.w / 6.f;
			pos.y += 15.f;
			break;
		}
		case EnemyType::right:
		{
			auto* pRightCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, +1);
			if (pRightCube)
				pRightCube->entity = m_pObject;
			pos.x += ((float)dst.w / 3.f) * 2.f;
			pos.y += 15.f;
			break;
		}
		default:
			m_pCurrentCube->entity = m_pObject;
			pos.x += (float)dst.w / 3.f;
			pos.y -= 5.f;
			break;
		}
		UpdatePosition(pos);
	}
	else
		m_pObject->Delete();
}

void dae::EnemyPositionComponent::RemoveFromCurrentCube()
{
	if (m_pCurrentCube)
	{
		switch (m_EnemyType)
		{
		case EnemyType::top:
			m_pCurrentCube->entity = nullptr;
			break;
		case EnemyType::left:
		{
			auto* pLeftCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, 0);
			if (pLeftCube)
				pLeftCube->entity = nullptr;
			break;
		}
		case EnemyType::right:
		{
			auto* pRightCube = m_pPyramid->GetNextCubeNeutral(m_pCurrentCube, +1, +1);
			if (pRightCube)
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

void dae::EnemyPositionComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}