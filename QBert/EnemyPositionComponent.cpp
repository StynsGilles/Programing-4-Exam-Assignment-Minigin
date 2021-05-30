#include "pch.h"
#include "EnemyPositionComponent.h"
#include <SDL_render.h>
#include <GameObject.h>
#include "LevelComponent.h"

dae::EnemyPositionComponent::EnemyPositionComponent(EnemyType enemyType)
	: m_EnemyType(enemyType)
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

void dae::EnemyPositionComponent::ChangeCube(LevelCube* pNewCube)
{
	m_pCurrentCube = pNewCube;
	if (m_pCurrentCube)
	{
		SDL_Rect dst;
		SDL_QueryTexture(pNewCube->pCubeTextures[pNewCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

		glm::vec3 pos = m_pCurrentCube->position;

		switch (m_EnemyType)
		{
		case EnemyType::top:
			pos.x += (float)dst.w / 3.f;
			pos.y -= (float)dst.h / 4.f;
			break;
		case EnemyType::left:
			pos.x -= (float)dst.w / 6.f;
			pos.y += 15.f;
			break;
		case EnemyType::right:
			pos.x += ((float)dst.w / 3.f) * 2.f;
			pos.y += 15.f;
			break;
		default:
			pos.x += (float)dst.w / 3.f;
			pos.y -= 5.f;
			break;
		}

		UpdatePosition(pos);
	}
	else
		m_pObject->Delete();
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
